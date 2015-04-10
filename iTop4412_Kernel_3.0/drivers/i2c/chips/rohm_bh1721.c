/* drivers/input/touchscreen/rohm_bh1771.c
 *
 * ROHM BH1771 Light Sensor driver
 *
 * Copyright (C) 2010 ROHM SEMICONDUCTOR Co. Ltd.
 *
 * Author:  Tracy Wen <tracy-wen@rohm.com.cn> 
 */

#include <linux/slab.h>	// shengliang: for kzalloc() etc.
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/input.h>
//#include <linux/input-polldev.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <asm/irq.h>
#include <linux/platform_device.h>
#include <linux/i2c/rohm_bh1721.h>

#define PS_TH_L_LED1	60
#define PS_TH_L_LED2	60
#define PS_TH_L_LED3	60
#define PS_TH_H_LED1	80
#define PS_TH_H_LED2	80
#define PS_TH_H_LED3	80
//#define PS_TH_L_LED		60
//#define PS_TH_H_LED		90
#define DATA_MAX	200
#define DATA_MIN	4

#define ABS(X)	((X>0)? X:(0-X))

static struct workqueue_struct *rohm_wq;
static int data_count=0;
static unsigned int ps_1[DATA_MAX];
static unsigned int ps_2[DATA_MAX];
static unsigned int ps_3[DATA_MAX];

//static struct i2c_client bh1721_i2c_client;

struct rohm_ls_data 
{
	uint16_t addr;
	struct i2c_client *client;
	struct input_dev *input_dev;
	//struct input_polled_dev *input_polled_dev;
	int use_irq;
	struct hrtimer timer;
	struct work_struct  work;
	uint32_t flags;
	short lux;
	int (*power)(int on);
};
/*
static int bh1721_write(unsigned char val)
{

	unsigned char  msg1[4] = {(val)&0xff};

	struct i2c_msg msgs[1] = {
		{ .addr = ROHM_I2C_ADDR, .flags = 0	   , .len = 1, .buf = msg1 }
	};
	
		
	if (i2c_transfer(bh1721_i2c_client.adapter, &msgs[0], 1) != 1) {
		printk("Robin: i2c_transfer error\n");
		return -EIO;
	}


	return 0;
		
}

static int bh1721_read(unsigned char * pVal)
{
	
	unsigned char  msg1[2] = {};
	unsigned char  msg2[2];

	struct i2c_msg msgs[2] = {
		{ .addr = ROHM_I2C_ADDR, .flags = 0	   , .len = 0, .buf = msg1 },
		{ .addr = ROHM_I2C_ADDR, .flags = I2C_M_RD, .len = 1, .buf = msg2 }
	};
	

	if (i2c_transfer(bh1721_i2c_client.adapter, &msgs[0], 2) != 2) {
		printk("Robin: i2c_transfer error\n");
		return -EIO;
	}
	pVal[0] = msg2[0];
	

	return 0;
		
}
*/
static void rohm_ls_work_func(struct work_struct *work)
{

	unsigned int highbyte = 0 ;
	unsigned int lowbyte = 0 ;

	short lux = 0;
	int ret;

	struct rohm_ls_data *ls = container_of(work, struct rohm_ls_data, work);

	struct i2c_msg msg[1];
	uint8_t buf[2];
	static int bias = 1;

	msg[0].addr = ls->client->addr;
	msg[0].flags = I2C_M_RD;
	msg[0].len = 2;
	msg[0].buf = buf;
	ret = i2c_transfer(ls->client->adapter, msg, 1);

	highbyte = buf[0];
	lowbyte = buf[1];

	//	highbyte = i2c_smbus_read_byte_data(ls->client, 0x4D);

	lux = (highbyte<<8) + lowbyte;

	if (ret < 0) 
	{
	//	printk("light sensor error!\n");		
		return;
	} 
	else
	{
		if (lux != ls->lux)
		{
			ls->lux = lux;
		}
		else
		{
			ls->lux = lux + bias;
			bias *= -1;
			if (ls->lux < 0)
				ls->lux = 0;
		}
		//printk("%d lux -> %d lux\n", lux, ls->lux);
		input_report_abs(ls->input_dev, ABS_X, ls->lux);
		input_sync(ls->input_dev);
	}
}

static enum hrtimer_restart rohm_ls_timer_func(struct hrtimer *timer)
{
	struct rohm_ls_data *ls = container_of(timer, struct rohm_ls_data, timer);
	queue_work(rohm_wq, &ls->work);
	hrtimer_start(&ls->timer, ktime_set(0, 20000000), HRTIMER_MODE_REL);	//report rate 1/20000000=50Hz
	return HRTIMER_NORESTART;
}

static irqreturn_t rohm_ls_irq_handler(int irq, void *dev_id)
{
	struct rohm_ls_data *ls = dev_id;
	//printk("Rohm_ls_irq_handler\n"); 
	disable_irq(ls->client->irq);
	queue_work(rohm_wq, &ls->work);

	return IRQ_HANDLED;
}

int bh1721_input_open(struct input_dev *input)
{
	struct rohm_ls_data *bh1721 = input_get_drvdata(input);

	printk("%s\n", __FUNCTION__);
	return 0;//lsm303dlhc_acc_enable(acc);
}

void bh1721_input_close(struct input_dev *dev)
{
	struct rohm_ls_data *bh1721 = input_get_drvdata(dev);

	printk("%s\n", __FUNCTION__);
	//lsm303dlhc_acc_disable(acc);
}

#if 0
static void bh1721_input_poll_func(struct input_polled_dev *dev)
{
	struct rohm_ls_data *bh1721 = dev->private;
	struct input_dev *input = bh1721->input_polled_dev->input;
	input_report_abs(input, ABS_X, bh1721->lux);
	input_sync(input);
}
#endif

static int bh1721_input_init(struct rohm_ls_data *bh1721)
{
	int err = -1;
	bh1721->input_dev = input_allocate_device();
	if (!bh1721->input_dev) {
		err = -ENOMEM;
		dev_err(&bh1721->client->dev, "input dev alloc failed\n");
		goto err0;
	}

#if 0
	bh1721->input_polled_dev->private = bh1721;
	bh1721->input_polled_dev->poll = bh1721_input_poll_func;
	bh1721->input_polled_dev->poll_interval = 10;
	input = bh1721->input_polled_dev->input;
	input->open = bh1721_input_open;
	input->close = bh1721_input_close;
	input->id.bustype = BUS_I2C;
	input->dev.parent = &bh1721->client->dev;
	input_set_drvdata(bh1721->input_polled_dev->input, bh1721);
	set_bit(EV_ABS, input->evbit);
	input_set_abs_params(input, ABS_X, -1024, 1024, 0,0);
	input->name = ROHM_I2C_NAME;
	err = input_register_polled_device(bh1721->input_polled_dev);
#else
	bh1721->input_dev->open = bh1721_input_open;
	bh1721->input_dev->close = bh1721_input_close;
	bh1721->input_dev->name = ROHM_I2C_NAME;
	bh1721->input_dev->id.bustype = BUS_I2C;
	bh1721->input_dev->dev.parent = &bh1721->client->dev;

	input_set_drvdata(bh1721->input_dev, bh1721);

	set_bit(EV_ABS, bh1721->input_dev->evbit);
	//set_bit(ABS_MISC, bh1721->input_dev->absbit);
	input_set_abs_params(bh1721->input_dev, ABS_X, 0, 1024, 0, 0);

	err = input_register_device(bh1721->input_dev);
	if (err) {
		dev_err(&bh1721->client->dev,"unable to register input dev %s\n", bh1721->input_dev->name);
		goto err1;
	}
#endif
	return 0;
err1:
	input_free_device(bh1721->input_dev);
err0:
	return err;
}

static void bh1721_input_cleanup(struct rohm_ls_data *bh1721)
{
	input_unregister_device(bh1721->input_dev);
	input_free_device(bh1721->input_dev);
}

static int rohm_ls_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct rohm_ls_data *ls;
	int ret = 0;
	struct ROHM_I2C_platform_data *pdata;
	//int i;

	printk(KERN_ERR "ROHM BH1771 rohm_ls_probe!!\n");
	printk("%s: addr=0x%x @ IIC%d, irq=%d\n",client->name,client->addr,client->adapter->nr,client->irq);
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) 
	{
		printk(KERN_ERR "Rohm_ls_probe: need I2C_FUNC_I2C\n");
		ret = -ENODEV;
		goto err_check_functionality_failed;
	}

	ls = kzalloc(sizeof(*ls), GFP_KERNEL);
	if (ls == NULL) 
	{
		ret = -ENOMEM;
		goto err_alloc_data_failed;
	}
	INIT_WORK(&ls->work, rohm_ls_work_func);
	ls->client = client;
	i2c_set_clientdata(client, ls);
	pdata = client->dev.platform_data;
	if (pdata)
		ls->power = pdata->power;
	if (ls->power) 
	{
		ret = ls->power(1);
		if (ret < 0) 
		{
			printk(KERN_ERR "Rohm_ls_probe power on failed\n");
			goto err_power_failed;
		}
	}

/*
	memcpy(&bh1721_i2c_client, client, sizeof(struct i2c_client));
	bh1721_write(0x01);
	bh1721_write(0x49);
	bh1721_write(0x6C);
	bh1721_write(0x10);
*/	

	////////////////////////////////////////////////////////////////////////
	// Init BH1721
	////////////////////////////////////////////////////////////////////////
	i2c_smbus_write_byte(ls->client, 0x01);	//0000 0001,	Power on
	i2c_smbus_write_byte(ls->client, 0x49);	//0100 1001,	
	i2c_smbus_write_byte(ls->client, 0x6C);	//0110 1100,	transimission rate is 100%
	i2c_smbus_write_byte(ls->client, 0x10);	//0001 0000,	1lx/step H-Res Continuously
	////////////////////////////////////////////////////////////////////////
	// Init end
	////////////////////////////////////////////////////////////////////////

	
	if(client->irq) 
	{	
		ret = request_irq(client->irq, rohm_ls_irq_handler, IRQF_TRIGGER_FALLING, client->name, ls);  	
		//Trigger status used IRQF_TRIGGER_FALLING ; ref \linux\interrupt.h
		// IRQF_TRIGGER_NONE	
		// IRQF_TRIGGER_RISING	
		// IRQF_TRIGGER_FALLING	
		// IRQF_TRIGGER_HIGH
		// IRQF_TRIGGER_LOW
		// IRQF_TRIGGER_PROBE
		/////////////////////////////

		printk("Request IRQ Failed==>ret : %d\n", ret);
		if (ret == 0) 
		{
			ls->use_irq = 0;	//1 : interrupt mode/0 : polling mode
			//free_irq(client->irq, ls);
		}
		else 
		{
			ls->use_irq = 0;	//1 set 1 : interrupt mode/0 : polling mode
			//dev_err(&client->dev, "request_irq failed\n");
		}	
	}

	if (!ls->use_irq) 
	{
		hrtimer_init(&ls->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		ls->timer.function = rohm_ls_timer_func;
		hrtimer_start(&ls->timer, ktime_set(1, 0), HRTIMER_MODE_REL);
	}
	else
	{
		hrtimer_init(&ls->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		ls->timer.function = rohm_ls_timer_func;
	}

	printk(KERN_INFO "==>:BH1771 in %s mode\n",ls->use_irq ? "interrupt" : "polling");

	//	printk(KERN_INFO "==>:Touchscreen Up %s in %s mode\n", ls->input_dev->name, ls->use_irq ? "interrupt" : "polling");

	ret = bh1721_input_init(ls);
	if (ret < 0) {
		dev_err(&client->dev, "input init failed\n");
		return ret;
	}

	return 0;
	/*
	err_input_register_device_failed:
	input_free_device(ls->input_dev);

	err_input_dev_alloc_failed:
	//err_detect_failed:
	*/
err_power_failed:
	kfree(ls);
err_alloc_data_failed:
err_check_functionality_failed:
	return ret;
}

static int rohm_ls_remove(struct i2c_client *client)
{
	struct rohm_ls_data *ls = i2c_get_clientdata(client);

	if (ls->use_irq)
		free_irq(client->irq, ls);
	else
		hrtimer_cancel(&ls->timer);
	/*	input_unregister_device(ls->input_dev);*/
	bh1721_input_cleanup(ls);
	kfree(ls);
	return 0;
}

static const struct i2c_device_id rohm_ls_id[] = 
{
	{ ROHM_I2C_NAME, 0 },
	{ }
};

static struct i2c_driver rohm_ls_driver = 
{
	.probe		= rohm_ls_probe,
	.remove		= rohm_ls_remove,
	.id_table	= rohm_ls_id,
	.driver = {
		.name	= ROHM_I2C_NAME,
	},
};

static int __devinit rohm_ls_init(void)
{

	rohm_wq = create_singlethread_workqueue("rohm_wq");
	if (!rohm_wq)
	{
		//printk(KERN_ERR "BU21018 create_singlethread_workqueue ERROR!!\n");
		return -ENOMEM;
	}	
	return i2c_add_driver(&rohm_ls_driver);
}

static void __exit rohm_ls_exit(void)
{
	i2c_del_driver(&rohm_ls_driver);
	if (rohm_wq)
		destroy_workqueue(rohm_wq);
}

module_init(rohm_ls_init);
module_exit(rohm_ls_exit);

MODULE_DESCRIPTION("Rohm Light Sensor Driver");
MODULE_LICENSE("GPL");
