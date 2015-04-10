/*
 * SAMSUNG NFC N2 Controller *
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Author: Woonki Lee <woonki84.lee@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the License, or (at your
 * option) any later version.
 *
 */

#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/poll.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/nfc/s3fhrn2.h>

#define S3FHRN2_IS_LENGTH(val)	(val == S3FHRN2_LLC_LENGTH)

#ifdef CONFIG_TC4_DVT
 #define NFC_EN_ON 0
 #define NFC_EN_OFF 1
#else
 #define NFC_EN_ON 1
 #define NFC_EN_OFF 0
#endif

enum s3fhrn2_irq {
	S3FHRN2_NONE,
	S3FHRN2_INT,
};

struct s3fhrn2_info {
	struct miscdevice miscdev;
	struct i2c_client *i2c_dev;
	enum s3fhrn2_state state;
	wait_queue_head_t read_wait;
	loff_t read_offset;
	enum s3fhrn2_irq read_irq;
	struct mutex read_mutex;
	struct mutex mutex;
	u8 *buf;
	size_t buflen;
};

static irqreturn_t s3fhrn2_irq_thread_fn(int irq, void *dev_id)
{
	struct s3fhrn2_info *info = dev_id;
	struct i2c_client *client = info->i2c_dev;

	dev_dbg(&client->dev, "IRQ\n");

	mutex_lock(&info->read_mutex);
	info->read_irq = S3FHRN2_INT;
	mutex_unlock(&info->read_mutex);

	wake_up_interruptible(&info->read_wait);

	return IRQ_HANDLED;
}

static int s3fhrn2_set_state(struct s3fhrn2_info *info, enum s3fhrn2_state state)
{
	struct i2c_client *client = info->i2c_dev;
	struct s3fhrn2_platform_data *pdata = client->dev.platform_data;

	/* intfo lock is aleady getten before calling this function */
	info->read_irq = S3FHRN2_NONE;
	info->state = state;

	// TC4 
	//gpio_set_value(pdata->ven, 0);
	gpio_set_value(pdata->ven, NFC_EN_OFF);
	
	gpio_set_value(pdata->firm, 0);
	msleep(30*5);

	if (state == S3FHRN2_ST_FIRM) {
		gpio_set_value(pdata->firm, 1);
		msleep(40*5);
		
		// TC4
		//gpio_set_value(pdata->ven, 0);
		gpio_set_value(pdata->ven, NFC_EN_OFF);
		msleep(20*5);
	}

	if (state != S3FHRN2_ST_OFF) {
		// TC4
		//gpio_set_value(pdata->ven, 1);
		gpio_set_value(pdata->ven, NFC_EN_ON);
	}
	msleep(150);

	return 0;
}

static int s3fhrn2_reset(struct s3fhrn2_info *info)	
{
	struct i2c_client *client = info->i2c_dev;

	dev_err(&client->dev, "i2c failed. return resatrt to M/W\n");

	s3fhrn2_set_state(info, S3FHRN2_ST_NORM);

	return -ERESTART;
}

static ssize_t s3fhrn2_read(struct file *file, char __user *buf,
			  size_t count, loff_t *offset)
{
	struct s3fhrn2_info *info = container_of(file->private_data,
						struct s3fhrn2_info, miscdev);
	struct i2c_client *client = info->i2c_dev;
	enum s3fhrn2_irq irq;
	int min, max;
	int ret = 0;

	dev_dbg(&client->dev, "%s: info: %p, count: %zu\n", __func__,
		info, count);

	mutex_lock(&info->mutex);

	if (info->state == S3FHRN2_ST_OFF) {
		dev_err(&client->dev, "s3fhrn2 is not enabled\n");
		ret = -ENODEV;
		goto out;
	}

	mutex_lock(&info->read_mutex);
	irq = info->read_irq;
	mutex_unlock(&info->read_mutex);
	if (irq == S3FHRN2_NONE) {
		if (file->f_flags & O_NONBLOCK) {
			dev_err(&client->dev, "it is nonblock\n");
			ret = -EAGAIN;
			goto out;
		}

		if (wait_event_interruptible(info->read_wait,
					(info->read_irq == S3FHRN2_INT))) {
			ret = -ERESTARTSYS;
			goto out;
		}
	}

	/* i2c recv */
	if (count > info->buflen)
		count = info->buflen;

	min = (info->state == S3FHRN2_ST_FIRM) ?
				S3FHRN2_FIRM_MIN_SIZE : S3FHRN2_MSG_MIN_SIZE;
	max = (info->state == S3FHRN2_ST_FIRM) ?
				S3FHRN2_FIRM_MAX_SIZE : S3FHRN2_MSG_MAX_SIZE;

	if (count < min || count > max) {
		dev_dbg(&client->dev, "user required wrong size\n");
		ret = -EINVAL;
		goto out;
	}

	mutex_lock(&info->read_mutex);
	ret = i2c_master_recv(client, info->buf, count);
	dev_dbg(&client->dev, "recv size : %d\n", ret);

	if (ret == -EREMOTEIO) {
		ret = s3fhrn2_reset(info);
		goto read_error;
	} else if (ret != count) {
		dev_err(&client->dev, "read failed: return: %d count: %d\n",
			ret, count);
		ret = -EREMOTEIO;
		goto read_error;
	}

	/* Only reading data can clear read_irq state. */
	if (!S3FHRN2_IS_LENGTH(ret) || info->state == S3FHRN2_ST_FIRM)
		info->read_irq = S3FHRN2_NONE;
	/* check the length value,
		It may be doing when reading length of frame. */
	else if (info->buf[0] < min || info->buf[0] > max) {
		dev_err(&client->dev, "reciev invaild length : %x\n",
			info->buf[0]);

		/* We need to check if i2c transmit is possible */
		ret = i2c_master_send(client, "test", 1);
		if (ret == -EREMOTEIO)
			ret = s3fhrn2_reset(info);
		else
			ret = -EINVAL;

		goto read_error;
	}
	mutex_unlock(&info->read_mutex);

	*offset += ret;
	if (copy_to_user(buf, info->buf, ret)) {
		dev_err(&client->dev, "copy failed to user\n");
		ret = -EFAULT;
	}

	goto out;

read_error:
	info->read_irq = S3FHRN2_NONE;
	mutex_unlock(&info->read_mutex);
out:
	mutex_unlock(&info->mutex);

	return ret;
}

static unsigned int s3fhrn2_poll(struct file *file, poll_table *wait)
{
	struct s3fhrn2_info *info = container_of(file->private_data,
						struct s3fhrn2_info, miscdev);
	struct i2c_client *client = info->i2c_dev;
	int ret = 0;
	enum s3fhrn2_irq irq;

	dev_dbg(&client->dev, "%s: info: %p\n", __func__, info);

	mutex_lock(&info->mutex);

	if (info->state == S3FHRN2_ST_OFF) {
		dev_err(&client->dev, "s3fhrn2 is not enabled\n");
		ret = -ENODEV;
		goto out;
	}

	poll_wait(file, &info->read_wait, wait);

	mutex_lock(&info->read_mutex);
	irq = info->read_irq;
	mutex_unlock(&info->read_mutex);
	if (irq == S3FHRN2_INT)
		ret = (POLLIN | POLLRDNORM);

out:
	mutex_unlock(&info->mutex);

	return ret;
}

static ssize_t s3fhrn2_write(struct file *file, const char __user *buf,
			   size_t count, loff_t *ppos)
{
	struct s3fhrn2_info *info = container_of(file->private_data,
						struct s3fhrn2_info, miscdev);
	struct i2c_client *client = info->i2c_dev;
	int min, max;
	int ret = 0;

	dev_dbg(&client->dev, "%s: info: %p, count %zu\n", __func__,
		info, count);

	mutex_lock(&info->mutex);

	if (info->state == S3FHRN2_ST_OFF) {
		dev_err(&client->dev, "s3fhrn2 is not enabled\n");
		ret = -ENODEV;
		goto out;
	}

	if (count > info->buflen)
		count = info->buflen;

	min = (info->state == S3FHRN2_ST_FIRM) ?
				S3FHRN2_FIRM_MIN_SIZE : S3FHRN2_MSG_MIN_SIZE;
	max = (info->state == S3FHRN2_ST_FIRM) ?
				S3FHRN2_FIRM_MAX_SIZE : S3FHRN2_MSG_MAX_SIZE;

	if (count < min || count > max) {
		dev_dbg(&client->dev, "user required wrong size\n");
		ret = -EINVAL;
		goto out;
	}

	if (copy_from_user(info->buf, buf, count)) {
		dev_err(&client->dev, "copy failed from user\n");
		ret = -EFAULT;
		goto out;
	}

	usleep_range(6000, 10000);
	ret = i2c_master_send(client, info->buf, count);
	dev_dbg(&client->dev, "send: %d\n", ret);

	if (ret == -EREMOTEIO) { /* Retry */
		usleep_range(6000, 10000);
		ret = i2c_master_send(client, buf, count);
		dev_dbg(&client->dev, "send2: %d\n", ret);
		if (ret == -EREMOTEIO)
			ret = s3fhrn2_reset(info);
	}

	if (ret != count) {
		dev_dbg(&client->dev, "send failed: return: %d count: %d\n",
		ret, count);
		ret = -EREMOTEIO;
	}

out:
	mutex_unlock(&info->mutex);

	return ret;
}

static long s3fhrn2_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct s3fhrn2_info *info = container_of(file->private_data,
						struct s3fhrn2_info, miscdev);
	struct i2c_client *client = info->i2c_dev;
	unsigned int mode = (unsigned int)arg;
	int ret = 0;

	dev_dbg(&client->dev, "%s: info: %p, cmd: 0x%x\n",
			__func__, info, cmd);

	mutex_lock(&info->mutex);

	switch (cmd) {
	case S3FHRN2_SET_MODE:
		dev_dbg(&client->dev, "%s: s3fhrn2_SET_MODE\n", __func__);

		if (info->state == mode)
			break;

		if (mode >= S3FHRN2_ST_COUNT) {
			dev_err(&client->dev, "wrong state (%d)\n", mode);
			ret = -EFAULT;
			break;
		}

		ret = s3fhrn2_set_state(info, mode);
		if (ret < 0) {
			dev_err(&client->dev, "enable failed\n");
			break;
		}

		file->f_pos = info->read_offset;
		break;
	default:
		dev_err(&client->dev, "Unknow ioctl 0x%x\n", cmd);
		ret = -ENOIOCTLCMD;
		break;
	}

	mutex_unlock(&info->mutex);

	return ret;
}

static int s3fhrn2_open(struct inode *inode, struct file *file)
{
	struct s3fhrn2_info *info = container_of(file->private_data,
						struct s3fhrn2_info, miscdev);
	struct i2c_client *client = info->i2c_dev;
	int ret = 0;

	dev_dbg(&client->dev, "%s: info : %p, client %p\n", __func__,
		info, info->i2c_dev);

	mutex_lock(&info->mutex);
	if (info->state != S3FHRN2_ST_OFF) {
		dev_err(&client->dev, "s3fhrn2 is busy\n");
		ret = -EBUSY;
		goto out;
	}

	file->f_pos = info->read_offset;
	ret = s3fhrn2_set_state(info, S3FHRN2_ST_NORM);
out:
	mutex_unlock(&info->mutex);
	return ret;
}

static int s3fhrn2_close(struct inode *inode, struct file *file)
{
	struct s3fhrn2_info *info = container_of(file->private_data,
						struct s3fhrn2_info, miscdev);
	struct i2c_client *client = info->i2c_dev;

	dev_dbg(&client->dev, "%s: info: %p, client %p\n",
		__func__, info, info->i2c_dev);

	mutex_lock(&info->mutex);
	s3fhrn2_set_state(info, S3FHRN2_ST_OFF);
	mutex_unlock(&info->mutex);

	return 0;
}

static const struct file_operations s3fhrn2_fops = {
	.owner		= THIS_MODULE,
	.read		= s3fhrn2_read,
	.write		= s3fhrn2_write,
	.poll		= s3fhrn2_poll,
	.open		= s3fhrn2_open,
	.release	= s3fhrn2_close,
	.unlocked_ioctl	= s3fhrn2_ioctl,
};

#ifdef CONFIG_PM
static int s3fhrn2_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct s3fhrn2_info *info = i2c_get_clientdata(client);
	int ret = 0;

	mutex_lock(&info->mutex);

	if (info->state == S3FHRN2_ST_FIRM)
		ret = -EPERM;

	/*
		suspend sequence.
	*/
	mutex_unlock(&info->mutex);
	return ret;
}

static int s3fhrn2_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct s3fhrn2_info *info = i2c_get_clientdata(client);

	mutex_lock(&info->mutex);
	/*
		resuem sequence.
	*/
	mutex_unlock(&info->mutex);

	return 0;
}

static SIMPLE_DEV_PM_OPS(s3fhrn2_pm_ops, s3fhrn2_suspend, s3fhrn2_resume);
#endif

static int __devinit s3fhrn2_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct s3fhrn2_info *info;
	struct s3fhrn2_platform_data *pdata;
	int ret = 0;

	info = kzalloc(sizeof(struct s3fhrn2_info), GFP_KERNEL);
	if (!info) {
		dev_err(&client->dev,
			"failed to allocate memory for s3fhrn2_info\n");
		ret = -ENOMEM;
		goto err_info_alloc;
	}


	info->buflen = S3FHRN2_MAX_BUFFER_SIZE;
	info->buf = kzalloc(S3FHRN2_MAX_BUFFER_SIZE, GFP_KERNEL);
	if (!info->buf) {
		dev_err(&client->dev,
			"failed to allocate memory for s3fhrn2_info->buf\n");
		ret = -ENOMEM;
		goto err_buf_alloc;
	}

	info->i2c_dev = client;
	info->state = S3FHRN2_ST_OFF;
	info->read_irq = S3FHRN2_NONE;
	mutex_init(&info->read_mutex);
	mutex_init(&info->mutex);
	init_waitqueue_head(&info->read_wait);
	i2c_set_clientdata(client, info);
	pdata = client->dev.platform_data;
	if (!pdata) {
		dev_err(&client->dev, "No platform data\n");
		ret = -ENOMEM;
		goto err_buf_alloc;
	}

	ret = request_threaded_irq(client->irq, NULL, s3fhrn2_irq_thread_fn,
				   IRQF_TRIGGER_RISING, S3FHRN2_DRIVER_NAME,
				   info);
	if (ret < 0) {
		dev_err(&client->dev, "failed to register IRQ handler\n");
		goto err_irq_req;
	}

	info->miscdev.minor = MISC_DYNAMIC_MINOR;
	info->miscdev.name = S3FHRN2_DRIVER_NAME;
	info->miscdev.fops = &s3fhrn2_fops;
	info->miscdev.parent = &client->dev;
	ret = misc_register(&info->miscdev);
	if (ret < 0) {
		dev_err(&client->dev, "failed to register Device\n");
		goto err_dev_reg;
	}

	ret = gpio_request(pdata->ven, "nfc_ven");
	
	// TC4
	if(ret) {
		dev_err(&client->dev, "failed to get gpio ven\n");
		goto err_gpio_ven;
	}

	ret = gpio_request(pdata->firm, "nfc_firm");
	if (ret) {
		dev_err(&client->dev, "failed to get gpio firm\n");
		goto err_gpio_firm;
	}

	gpio_direction_output(pdata->ven, NFC_EN_ON);
	gpio_direction_output(pdata->firm, 0);

	dev_dbg(&client->dev, "%s: info: %p, pdata %p, client %p\n",
		__func__, info, pdata, client);

	return 0;

err_gpio_firm:
	gpio_free(pdata->ven);
err_gpio_ven:
err_dev_reg:
err_irq_req:
	kfree(info->buf);
err_buf_alloc:
	kfree(info);
err_info_alloc:
	return ret;
}

static int __devexit s3fhrn2_remove(struct i2c_client *client)
{
	struct s3fhrn2_info *info = i2c_get_clientdata(client);
	struct s3fhrn2_platform_data *pdata = client->dev.platform_data;

	dev_dbg(&client->dev, "%s\n", __func__);

	misc_deregister(&info->miscdev);

	if (info->state != S3FHRN2_ST_OFF) {
		gpio_set_value(pdata->firm, 0);
		// TC4
		//gpio_set_value(pdata->ven, 0);
		gpio_set_value(pdata->ven, NFC_EN_OFF);
		
		info->read_irq = S3FHRN2_NONE;
	}

	gpio_free(pdata->firm);
	gpio_free(pdata->ven);

	free_irq(client->irq, info);

	kfree(info->buf);
	kfree(info);

	return 0;
}

static struct i2c_device_id s3fhrn2_id_table[] = {
	{ S3FHRN2_DRIVER_NAME, 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, s3fhrn2_id_table);

static struct i2c_driver s3fhrn2_driver = {
	.driver = {
		.name = S3FHRN2_DRIVER_NAME,
#ifdef CONFIG_PM
		.pm = &s3fhrn2_pm_ops,
#endif
	},
	.probe = s3fhrn2_probe,
	.id_table = s3fhrn2_id_table,
	.remove = s3fhrn2_remove,
};

static int __init s3fhrn2_init(void)
{
	int ret;

	ret = i2c_add_driver(&s3fhrn2_driver);

	if (ret)
		return ret;

	return 0;
}

static void __exit s3fhrn2_exit(void)
{
	i2c_del_driver(&s3fhrn2_driver);
}

module_init(s3fhrn2_init);
module_exit(s3fhrn2_exit);

MODULE_DESCRIPTION("Samsung s3fhrn2 driver");
MODULE_LICENSE("GPL");
