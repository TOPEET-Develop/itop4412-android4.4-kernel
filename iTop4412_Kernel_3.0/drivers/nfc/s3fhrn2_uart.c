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
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/mutex.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/nfc/s3fhrn2.h>

#define S3FHRN2_IS_LENGTH(val)	(val == S3FHRN2_LLC_LENGTH)

struct s3fhrn2_info {
	struct miscdevice miscdev;
	struct device *dev;
	struct s3fhrn2_platform_data *pdata;
	enum s3fhrn2_state state;
	struct mutex mutex;
};

static int s3fhrn2_set_state(struct s3fhrn2_info *info, enum s3fhrn2_state state)
{
	struct s3fhrn2_platform_data *pdata = info->pdata;

	/* intfo lock is aleady getten before calling this function */
	info->state = state;

	gpio_set_value(pdata->ven, 0);
	gpio_set_value(pdata->firm, 0);
	msleep(30);

	if (state == S3FHRN2_ST_FIRM) {
		gpio_set_value(pdata->firm, 1);
		msleep(40);
		gpio_set_value(pdata->ven, 0);
		msleep(20);
	}

	if (state != S3FHRN2_ST_OFF)
		gpio_set_value(pdata->ven, 1);

	msleep(150);

	return 0;
}

static ssize_t s3fhrn2_write(struct file *file, const char __user *buf,
			   size_t count, loff_t *ppos)
{
	struct s3fhrn2_info *info = container_of(file->private_data,
						struct s3fhrn2_info, miscdev);
	int mode;
	int ret = 0;
	
	mode = (int)simple_strtoul(buf, NULL, 10);
	
	if (info->state == mode)
		goto out;

	if (mode >= S3FHRN2_ST_COUNT) {
		dev_err(info->dev, "wrong state (%d)\n", mode);
		ret = -EFAULT;
	}

	ret = s3fhrn2_set_state(info, mode);
	if (ret < 0)
		dev_err(info->dev, "enable failed\n");

out:
	return ret;
}

static long s3fhrn2_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct s3fhrn2_info *info = container_of(file->private_data,
						struct s3fhrn2_info, miscdev);
	unsigned int mode = (unsigned int)arg;
	int ret = 0;

	dev_dbg(info->dev, "%s: info: %p, cmd: 0x%x\n",
			__func__, info, cmd);

	mutex_lock(&info->mutex);

	switch (cmd) {
	case S3FHRN2_SET_MODE:
		dev_dbg(info->dev, "%s: s3fhrn2_SET_MODE\n", __func__);

		if (info->state == mode)
			break;

		if (mode >= S3FHRN2_ST_COUNT) {
			dev_err(info->dev, "wrong state (%d)\n", mode);
			ret = -EFAULT;
			break;
		}

		ret = s3fhrn2_set_state(info, mode);
		if (ret < 0) {
			dev_err(info->dev, "enable failed\n");
			break;
		}

		break;
	default:
		dev_err(info->dev, "Unknow ioctl 0x%x\n", cmd);
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
	int ret = 0;

	dev_dbg(info->dev, "%s: info : %p" , __func__, info);

	mutex_lock(&info->mutex);

	mutex_unlock(&info->mutex);

	return ret;
}

static int s3fhrn2_close(struct inode *inode, struct file *file)
{
	struct s3fhrn2_info *info = container_of(file->private_data,
						struct s3fhrn2_info, miscdev);

	dev_dbg(info->dev, "%s: info : %p" , __func__, info);

	mutex_lock(&info->mutex);

	mutex_unlock(&info->mutex);

	return 0;
}

static const struct file_operations s3fhrn2_fops = {
	.owner		= THIS_MODULE,
	.write		= s3fhrn2_write,
	.open		= s3fhrn2_open,
	.release	= s3fhrn2_close,
	.unlocked_ioctl	= s3fhrn2_ioctl,
};

#ifdef CONFIG_PM
static int s3fhrn2_suspend(struct device *dev)
{
	int ret = 0;
	/*
	mutex_lock(&info->mutex);

	if (info->state == S3FHRN2_ST_FIRM)
		ret = -EPERM;
	*/

	/*
		suspend sequence.
	*/
	/*
	mutex_unlock(&info->mutex);
	*/
	return ret;
}

static int s3fhrn2_resume(struct device *dev)
{
	/*
	mutex_lock(&info->mutex);
	*/
	/*
		resuem sequence.
	*/
	/*
	mutex_unlock(&info->mutex);
	*/

	return 0;
}

static SIMPLE_DEV_PM_OPS(s3fhrn2_pm_ops, s3fhrn2_suspend, s3fhrn2_resume);
#endif

static int __devinit s3fhrn2_probe(struct platform_device *pdev)
{
	struct s3fhrn2_info *info;
	struct s3fhrn2_platform_data *pdata = pdev->dev.platform_data;
	int ret = 0;
	
	if (!pdata) {
		dev_err(&pdev->dev, "No platform data\n");
		ret = -ENOMEM;
		goto err_pdata;
	}

	info = kzalloc(sizeof(struct s3fhrn2_info), GFP_KERNEL);
	if (!info) {
		dev_err(&pdev->dev,
			"failed to allocate memory for s3fhrn2_info\n");
		ret = -ENOMEM;
		goto err_info_alloc;
	}
	info->dev = &pdev->dev;
	info->pdata = pdata;

	mutex_init(&info->mutex);
	dev_set_drvdata(&pdev->dev, info);

	info->miscdev.minor = MISC_DYNAMIC_MINOR;
	info->miscdev.name = S3FHRN2_DRIVER_NAME;
	info->miscdev.fops = &s3fhrn2_fops;
	info->miscdev.parent = &pdev->dev;
	ret = misc_register(&info->miscdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to register Device\n");
		goto err_dev_reg;
	}

	pdata->cfg_gpio(pdev);

	ret = gpio_request(pdata->ven, "nfc_ven");
	if (ret) {
		dev_err(&pdev->dev, "failed to get gpio ven\n");
		goto err_gpio_ven;
	}

	ret = gpio_request(pdata->firm, "nfc_firm");
	if (ret) {
		dev_err(&pdev->dev, "failed to get gpio firm\n");
		goto err_gpio_firm;
	}

	gpio_direction_output(pdata->ven, 0);
	gpio_direction_output(pdata->firm, 0);

	dev_dbg(&pdev->dev, "%s: info: %p, pdata %p\n",
		__func__, info, pdata);

	return 0;

err_gpio_firm:
	gpio_free(pdata->ven);
err_gpio_ven:
err_dev_reg:
err_info_alloc:
	kfree(info);
err_pdata:
	return ret;
}

static int __devexit s3fhrn2_remove(struct platform_device *pdev)
{
	struct s3fhrn2_info *info = dev_get_drvdata(&pdev->dev);
	struct s3fhrn2_platform_data *pdata = pdev->dev.platform_data;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	misc_deregister(&info->miscdev);

	if (info->state != S3FHRN2_ST_OFF) {
		gpio_set_value(pdata->firm, 0);
		gpio_set_value(pdata->ven, 0);
	}

	gpio_free(pdata->firm);
	gpio_free(pdata->ven);

	kfree(info);

	return 0;
}

static struct platform_device_id s3fhrn2_id_table[] = {
	{ S3FHRN2_DRIVER_NAME, 0 },
	{ }
};
MODULE_DEVICE_TABLE(platform, s3fhrn2_id_table);

static struct platform_driver s3fhrn2_driver = {
	.probe		= s3fhrn2_probe,
	.id_table	= s3fhrn2_id_table,
	.remove		= s3fhrn2_remove,
	.driver = {
		.name	= S3FHRN2_DRIVER_NAME,
#ifdef CONFIG_PM
		.pm	= &s3fhrn2_pm_ops,
#endif
	},
};

static int __init s3fhrn2_init(void)
{
	return platform_driver_register(&s3fhrn2_driver);
}

static void __exit s3fhrn2_exit(void)
{
	platform_driver_unregister(&s3fhrn2_driver);
}

module_init(s3fhrn2_init);
module_exit(s3fhrn2_exit);

MODULE_DESCRIPTION("Samsung s3fhrn2 driver");
MODULE_LICENSE("GPL");
