/*
 * drivers/power/motor8997.c
 *
 * Motor8997 driver
 * 
 * Author: Sheng Liang <liang.sheng@samsung.com>
 *
 * V1.0: 2011-9-6
 * 	Initial version
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mutex.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/i2c/max8997.h>

static struct i2c_client motor8997_i2c_client;

static int motor8997_write(unsigned char address,unsigned char val)
{

	unsigned char  msg1[4] = { address & 0xff,(val)&0xff};

	struct i2c_msg msgs[1] = {
		{ .addr = MOTOR8997_ADDR, .flags = 0	   , .len = 2, .buf = msg1 }
	};
	
		
	if (i2c_transfer(motor8997_i2c_client.adapter, &msgs[0], 1) != 1) {
		printk("Robin: i2c_transfer error\n");
		return -EIO;
	}


	return 0;
		
}

static int motor8997_read(unsigned char address,unsigned char * pVal)
{
	
	unsigned char  msg1[2] = { address & 0xff };
	unsigned char  msg2[2];

	struct i2c_msg msgs[2] = {
		{ .addr = MOTOR8997_ADDR, .flags = 0	   , .len = 1, .buf = msg1 },
		{ .addr = MOTOR8997_ADDR, .flags = I2C_M_RD, .len = 1, .buf = msg2 }
	};
	

	if (i2c_transfer(motor8997_i2c_client.adapter, &msgs[0], 2) != 2) {
		printk("Robin: i2c_transfer error\n");
		return -EIO;
	}
	pVal[0] = msg2[0];
	

	return 0;
		
}

void motor8997_on(int on)
{
#define MOTOR_ON (0x01<<6)
	if (on != 0)
	{
		motor8997_write(0x02, MOTOR_ON);
	}
	else
	{
		motor8997_write(0x02, 0);
	}
#undef MOTOR_ON
}
EXPORT_SYMBOL(motor8997_on);

static int  motor8997_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);

	printk("%s: addr=0x%x @ IIC%d, irq=%d\n",client->name,client->addr,client->adapter->nr,client->irq);

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
	{
		printk("i2c_check_functionality err\n");
		return -EIO;
	}
	memcpy(&motor8997_i2c_client, client, sizeof(struct i2c_client));
	//motor8997_on(1);
	//mdelay(1000);
	motor8997_on(0);
	return 0;
}

static int __devexit motor8997_remove(struct i2c_client *client)
{
	return 0;
}


#if 0//def CONFIG_PM
static int motor8997_suspend(struct i2c_client *client,
		pm_message_t state)
{
	
	return 0;
}

static int motor8997_resume(struct i2c_client *client)
{
	
	return 0;
}
#else
#define motor8997_suspend NULL
#define motor8997_resume NULL
#endif

static const struct i2c_device_id motor8997_id[] = {
	{ MOTOR8997_I2C_NAME, 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, motor8997_id);

static struct i2c_driver motor8997_i2c_driver = {
	.driver = {
		.name = MOTOR8997_I2C_NAME,
	},
	.probe = motor8997_probe,
	.remove = __devexit_p(motor8997_remove),
	.suspend = motor8997_suspend,
	.resume = motor8997_resume,
	.id_table = motor8997_id,
};

static int __init motor8997_init(void)
{
	printk("%s()\n", __FUNCTION__);

	return i2c_add_driver(&motor8997_i2c_driver);
}
subsys_initcall(motor8997_init);

static void __exit motor8997_exit(void)
{
	i2c_del_driver(&motor8997_i2c_driver);
}

module_exit(motor8997_exit);

MODULE_AUTHOR("Sheng Liang <liang.sheng@samsung.com>");
MODULE_DESCRIPTION("MOTOR8997");
MODULE_LICENSE("GPL");
