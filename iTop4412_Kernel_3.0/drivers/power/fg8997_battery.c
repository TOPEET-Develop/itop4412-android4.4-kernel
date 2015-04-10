/*
 *  fg8997_battery.c
 *  fuel-gauge systems for lithium-ion (Li+) batteries
 *
 *  Copyright (C) 2009 Samsung Electronics
 *  Sheng Liang <liang.sheng@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mutex.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/power_supply.h>
#include <linux/fg8997_battery.h>
#include <linux/gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/regs-gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/interrupt.h>

#define FG8997_RETRY_COUNT	3
#define FG8997_DELAY		0//1000
#define FG8997_BATTERY_FULL	98
#define FUEL_ALRT EXYNOS4_GPX3(2)

#define FUEL_ALRT_THRESHOLD 5

//#define FG8997_LOWVOL_TEST

#define FG8997_DBG_LEVEL_INIT	0x1
#define FG8997_DBG_LEVEL_FUNC	0x2
#define FG8997_DBG_LEVEL_DATA	0x4

//int fg8997_dbg_level = 0x1 | 0x2 | 0x4;
int fg8997_dbg_level = 0x0;	/*modify by wenpin.cui:delete debug message*/
#define fg8997_dbg(level, fmt, args...) do{\
	if((level&fg8997_dbg_level)>0)\
		printk("[fg8997]: "fmt, ## args); }\
	while(0)

struct fg8997_battery_info {
	int tech;	// always = POWER_SUPPLY_TECHNOLOGY_LION
	//int adc;	// ADC value of voltage, not used
	int vcell;	// battery voltage * 1000, unit mV
	int soc;	// battery capacity
	int temperature;	// temperature
	int charging_source;	// battery? usb? ac?
	int health;	// always = POWER_SUPPLY_HEALTH_GOOD
	int status;	// charging?
	// private data
	int saved_rcomp0;
	int saved_tempco;
};

struct fg8997_chip {
	struct i2c_client		*client;
	struct delayed_work		work;
	struct power_supply		battery[3];//0 for battery, 1 for USB, 2 for AC
	struct fg8997_battery_info	bat_info;
};
static struct fg8997_chip *this_chip = NULL;
static int s5p_battery_initial = 0;

typedef enum {
	CHARGER_BATTERY = 0,
	CHARGER_USB,
	CHARGER_AC,
	CHARGER_DISCHARGE
} charger_type_t;

static void fg8997_get_status()
{
	struct fg8997_chip *chip = this_chip;

	if (chip->bat_info.charging_source == CHARGER_USB
			|| chip->bat_info.charging_source == CHARGER_AC) {
		if(chip->bat_info.soc >= FG8997_BATTERY_FULL) {
			chip->bat_info.status = POWER_SUPPLY_STATUS_FULL;
			chip->bat_info.soc = 100;
		}
		else
			chip->bat_info.status = POWER_SUPPLY_STATUS_CHARGING;
	}
	else
		chip->bat_info.status = POWER_SUPPLY_STATUS_NOT_CHARGING;

}
int  is_charger_online()
{
	struct fg8997_chip *chip = this_chip;
	return  (chip->bat_info.charging_source == CHARGER_USB
				|| chip->bat_info.charging_source == CHARGER_AC);
}
static int s5p_cable_status_update(int source)
{
	int ret = 0;

	if(!s5p_battery_initial)
		return -EPERM;

	switch(source) {
		case CHARGER_BATTERY:
			this_chip->bat_info.charging_source = CHARGER_BATTERY;
			break;
		case CHARGER_USB:
			this_chip->bat_info.charging_source = CHARGER_USB;
			break;
		case CHARGER_AC:
			this_chip->bat_info.charging_source = CHARGER_AC;
			break;
		case CHARGER_DISCHARGE:
			this_chip->bat_info.charging_source = CHARGER_DISCHARGE;
			break;
		default:
			printk("%s : Nat supported status\n", __func__);
			ret = -EINVAL;
	}

	if(!ret)
	{
		fg8997_get_status();
	}

	/* if the power source changes, all power supplies may change state */
	power_supply_changed(&(this_chip->battery[CHARGER_BATTERY]));
	/*
	   power_supply_changed(&(this_chip->battery[CHARGER_USB]));
	   power_supply_changed(&(this_chip->battery[CHARGER_AC]));
	   */
	return ret;
}

void s5p_cable_check_status(int flag)
{
	charger_type_t status = 0;

	if (0 == flag)  // Battery
		status = CHARGER_BATTERY;
	else if(1 == flag)   // USB
		status = CHARGER_USB;
	else if(2 == flag)	// AC
		status = CHARGER_AC;
	s5p_cable_status_update(status);
}
EXPORT_SYMBOL(s5p_cable_check_status);

static int fg8997_get_property(struct power_supply *psy,
		enum power_supply_property psp,
		union power_supply_propval *val)
{
	struct fg8997_chip *chip = container_of(psy,
			struct fg8997_chip, battery);

	//printk("%s(),%d\n",__FUNCTION__,psp);
	switch (psp) {
		case POWER_SUPPLY_PROP_STATUS:
			val->intval = chip->bat_info.status;
			break;
		case POWER_SUPPLY_PROP_VOLTAGE_NOW:
			val->intval = chip->bat_info.vcell;
			break;
		case POWER_SUPPLY_PROP_CAPACITY:
			val->intval = chip->bat_info.soc;
			break;
		case POWER_SUPPLY_PROP_HEALTH:
			val->intval = chip->bat_info.health;// POWER_SUPPLY_HEALTH_GOOD;
			break;
		case POWER_SUPPLY_PROP_TECHNOLOGY:
			val->intval = chip->bat_info.tech;// POWER_SUPPLY_TECHNOLOGY_LION;
			break;
		case POWER_SUPPLY_PROP_PRESENT:
			val->intval = 1;
			break;
		//ly: not supported on tc4
		//case POWER_SUPPLY_PROP_TEMP:
		//	val->intval = chip->bat_info.temperature;
		//	break;
		default:
			return -EINVAL;
	}
	return 0;
}

static int s5p_power_get_property(struct power_supply *bat_ps, 
		enum power_supply_property psp, 
		union power_supply_propval *val)
{
	charger_type_t charger = this_chip->bat_info.charging_source;

	switch (psp) {
		case POWER_SUPPLY_PROP_ONLINE:
			if (bat_ps->type == POWER_SUPPLY_TYPE_MAINS)
				val->intval = (charger == CHARGER_AC ? 1 : 0);
			else if (bat_ps->type == POWER_SUPPLY_TYPE_USB)
				val->intval = (charger == CHARGER_USB ? 1 : 0);
			else
				val->intval = 0;
			break;
		default:
			return -EINVAL;
	}

	return 0;
}

#if 0
static int fg8997_write_reg(struct i2c_client *client, int reg, u8 value)
{
	int ret;

	ret = i2c_smbus_write_byte_data(client, reg, value);

	if (ret < 0)
		dev_err(&client->dev, "%s: err %d\n", __func__, ret);

	return ret;
}

static int fg8997_read_reg(struct i2c_client *client, int reg)
{
	int ret;

	ret = i2c_smbus_read_byte_data(client, reg);

	if (ret < 0)
		dev_err(&client->dev, "%s: err %d\n", __func__, ret);

	return ret;
}
#endif

/*

static int fg8997_i2c_rx_data_test(unsigned char addr,unsigned char * buf)
{
	uint8_t i;
	struct i2c_client *fg8997_client = this_chip->client;
	unsigned char  msg1[2] = { addr & 0xff };
	unsigned char  msg2[2]={0};
	struct i2c_msg msgs[] = {
		{
			.addr	= 0x36,
			.flags	= 0,
			.len	= 1,
			.buf	= msg1,
		},
		{
			.addr	= 0x36,
			.flags	= I2C_M_RD,
			.len	= 1,
			.buf	= msg2	,
		}
	};
	if(NULL == this_chip || NULL == fg8997_client || NULL == fg8997_client->addr)
		return -EIO;

	for (i = 0; i < FG8997_RETRY_COUNT; i++) {
		if (i2c_transfer(fg8997_client->adapter, msgs, 2) > 0) {
			break;
		}
		mdelay(10);
	}
	buf[0] = msg2[0];
	if (i >= FG8997_RETRY_COUNT) {
		pr_err("%s: retry over %d\n", __FUNCTION__, FG8997_RETRY_COUNT);
		return -EIO;
	}

	return 0;
}
*/


static int fg8997_i2c_rx_data(char *buf, int len)
{
	uint8_t i;
	struct i2c_client *fg8997_client = this_chip->client;
	struct i2c_msg msgs[] = {
		{
			.addr	= fg8997_client->addr,
			.flags	= 0,
			.len	= 1,
			.buf	= buf,
		},
		{
			.addr	= fg8997_client->addr,
			.flags	= I2C_M_RD,
			.len	= len,
			.buf	= buf,
		}
	};
	if(NULL == this_chip || NULL == fg8997_client || NULL == fg8997_client->addr)
		return -EIO;

	for (i = 0; i < FG8997_RETRY_COUNT; i++) {
		if (i2c_transfer(fg8997_client->adapter, msgs, 2) > 0) {
			break;
		}
		mdelay(10);
	}

	if (i >= FG8997_RETRY_COUNT) {
		pr_err("%s: retry over %d\n", __FUNCTION__, FG8997_RETRY_COUNT);
		return -EIO;
	}

	return 0;
}

static int fg8997_i2c_tx_data(char *buf, int len)
{
	uint8_t i;
	struct i2c_client *fg8997_client = this_chip->client;
	struct i2c_msg msg[] = {
		{
			.addr	= fg8997_client->addr,
			.flags	= 0,
			.len	= len,
			.buf	= buf,
		}
	};
	if(NULL == this_chip || NULL == fg8997_client || NULL == fg8997_client->addr)
		return -EIO;

	for (i = 0; i < FG8997_RETRY_COUNT; i++) {
		if (i2c_transfer(fg8997_client->adapter, msg, 1) > 0) {
			break;
		}
		mdelay(10);
	}

	if (i >= FG8997_RETRY_COUNT) {
		pr_err("%s: retry over %d\n", __FUNCTION__, FG8997_RETRY_COUNT);
		return -EIO;
	}

	return 0;
}

static int fg8997_i2c_tx_data_verify(char *buf, int len)
{
	int ret;
	char *temp = NULL;
	do {
		ret = fg8997_i2c_tx_data(buf,len);
		if(!ret)
			return ret;

		if(NULL == temp)
			temp = kzalloc(len, GFP_KERNEL);
		if (!temp)
		{
			printk("%s() alloc mem fail\n", __FUNCTION__);
			break;//return -ENOMEM;
		}
		temp[0] = buf[0];
		ret = fg8997_i2c_rx_data(temp,len-1);
	} while(!memcpy(temp, buf+1, len-1));
	if (!temp)
		kfree(temp);
	return 0;
}

static int fg8997_get_temperature()
{
	unsigned char data[2] = {0,0};
	unsigned int temperature;
	int ret;
#if 0
	data[0] = 0x08;
	ret = fg8997_i2c_rx_data(data, 2);
	if (ret)
	{
		printk("%s() error\n", __FUNCTION__);
		return ret;
	}

	temperature = data[1];
	fg8997_dbg(FG8997_DBG_LEVEL_DATA, "temperature:0x%x,0x%x->%d C\n", data[0], data[1], temperature);
	return temperature;
#else
	return 22;
#endif
}

static int fg8997_get_vcell()
{
	unsigned char data[2] = {0,0};
	unsigned int vcell;
	int ret;

	data[0] = 0xEE;
	ret = fg8997_i2c_rx_data(data, 2);
	if (ret)
	{
		printk("%s() error\n", __FUNCTION__);
		return ret;
	}

	vcell = (data[1]<<8) + data[0];
	vcell = vcell >> 4;
	vcell = (vcell*5)>>2;
	fg8997_dbg(FG8997_DBG_LEVEL_DATA, "vcell:0x%x,0x%x->%d mV\n", data[0], data[1], vcell);
	return vcell;
}

int fg8997_get_soc()
{
	unsigned char data[2] = {0,0};
	unsigned int soc;
	int ret;

	data[0] = 0xFF;
	ret = fg8997_i2c_rx_data(data, 2);
	if (ret)
	{
		printk("%s() error\n", __FUNCTION__);
		return ret;
	}

	soc = data[1];
	fg8997_dbg(FG8997_DBG_LEVEL_DATA, "soc:0x%x,0x%x->%d %%\n", data[0], data[1], soc);
	if (soc > 100)
		soc = 100;
        if (soc < 20)
		printk("fg8997:soc:0x%x,0x%x->%d %%\n", data[0], data[1], soc);
	return soc;
}
EXPORT_SYMBOL(fg8997_get_soc);

static int fg8997_save_learned_param()
{
	unsigned char data[4] = {0,0,0,0};
	int ret;
	// Step 16. Save Learned Parameters
	data[0] = 0x38;// RCOMP0
	ret = fg8997_i2c_rx_data(data, 2);
	if (ret)
	{
		printk("%s() error1\n", __FUNCTION__);
		return ret;
	}
	this_chip->bat_info.saved_rcomp0 = (data[1]<<8) + data[0];
	data[0] = 0x39;// TempCo
	ret = fg8997_i2c_rx_data(data, 2);
	if (ret)
	{
		printk("%s() error2\n", __FUNCTION__);
		return ret;
	}
	this_chip->bat_info.saved_tempco = (data[1]<<8) + data[0];
	return 0;
}

static int fg8997_restore_learned_param()
{
	unsigned char data[4] = {0,0,0,0};
	int ret;
	// Step 17. Restore Learned Parameters
	data[0] = 0x38;// RCOMP0
	data[1] = this_chip->bat_info.saved_rcomp0 & 0xff;
	data[2] = (this_chip->bat_info.saved_rcomp0 >> 8) & 0xff;
	ret = fg8997_i2c_tx_data_verify(data, 3);
	if (ret)
	{
		printk("%s() error1\n", __FUNCTION__);
		return ret;
	}
	data[0] = 0x39;// TempCo
	data[1] = this_chip->bat_info.saved_tempco & 0xff;
	data[2] = (this_chip->bat_info.saved_tempco >> 8) & 0xff;
	ret = fg8997_i2c_tx_data_verify(data, 3);
	if (ret)
	{
		printk("%s() error2\n", __FUNCTION__);
		return ret;
	}
	// Step 18. Wait 350mS
	mdelay(350);
	return 0;
}

static int fg8997_init_reg()
{
	unsigned char data[64] = {0,0,0,0};
	//unsigned char data1[32] = {0,0,0,0};
	int i;
	int ret;
	int vfsoc;
	int locked;
	printk("**fg8997_init_reg ****\n");
	// Step 0. Check for POR
	data[0] = 0;// STATUS
	ret = fg8997_i2c_rx_data(data, 2);
	if (ret)
	{
		printk("%s() error1\n", __FUNCTION__);
		return ret;
	}
	if (data[0] & (0x01<<1))// POR
	{
		// Step 1. Delay 500mS
		mdelay(500);
		// Step 2. Initialize Configuration
		data[0] = 0x1D;// CONFIG
		data[1] = 0x10;
		data[2] = 0x22;
		ret = fg8997_i2c_tx_data(data, 3);
		if (ret)
		{
			printk("%s() error2\n", __FUNCTION__);
			return ret;
		}
		// Step 4. Unlock Model Access
		data[0] = 0x62;
		data[1] = 0x59;
		data[2] = 0x00;
		ret = fg8997_i2c_tx_data(data,3);
		if (ret)
		{
			printk("%s() error3\n", __FUNCTION__);
			return ret;
		}
		data[0] = 0x63;
		data[1] = 0xC4;
		data[2] = 0x00;
		ret = fg8997_i2c_tx_data(data,3);
		if (ret)
		{
			printk("%s() error4\n", __FUNCTION__);
			return ret;
		}
		// Step 5. Write/Read/Verify the Custom Model
		data[0] = 0x80;
		data[2] = 0x7E; data[1] = 0x00;
		data[4] = 0xB5; data[3] = 0x80;
		data[6] = 0xB8; data[5] = 0x30;
		data[8] = 0xB9; data[7] = 0x00;
		data[10] = 0xBB; data[9] = 0x10;
		data[12] = 0xBC; data[11] = 0x20;
		data[14] = 0xBC; data[13] = 0x80;
		data[16] = 0xBC; data[15] = 0xE0;
		data[18] = 0xBD; data[17] = 0xB0;
		data[20] = 0xBE; data[19] = 0x90;
		data[22] = 0xC0; data[21] = 0x60;
		data[24] = 0xC2; data[23] = 0x10;
		data[26] = 0xC4; data[25] = 0x00;
		data[28] = 0xC7; data[27] = 0x40;
		data[30] = 0xCB; data[29] = 0xE0;
		data[32] = 0xCF; data[31] = 0xF0;
		do {
			ret = fg8997_i2c_tx_data_verify(data,33);
			if (ret)
			{
				printk("%s() error5\n", __FUNCTION__);
				return ret;
			}
			/*
			data1[0] = 0x80;
			ret = fg8997_i2c_rx_data(data1,32);
			if (ret)
			{
				printk("%s() error6\n", __FUNCTION__);
				return ret;
			}
			*/
		} while(0);//memcmp(data+1, data1, 32));
		data[0] = 0x90;
		data[2] = 0x00; data[1] = 0x80;
		data[4] = 0x09; data[3] = 0x00;
		data[6] = 0x19; data[5] = 0x00;
		data[8] = 0x0B; data[7] = 0x00;
		data[10] = 0x13; data[9] = 0x00;
		data[12] = 0x2E; data[11] = 0x00;
		data[14] = 0x2E; data[13] = 0x00;
		data[16] = 0x2A; data[15] = 0x10;
		data[18] = 0x1C; data[17] = 0xA0;
		data[20] = 0x0B; data[19] = 0xE0;
		data[22] = 0x0D; data[21] = 0xE0;
		data[24] = 0x0A; data[23] = 0xD0;
		data[26] = 0x0C; data[25] = 0xD0;
		data[28] = 0x08; data[27] = 0xF0;
		data[30] = 0x09; data[29] = 0xD0;
		data[32] = 0x09; data[31] = 0xD0;
		do {
			ret = fg8997_i2c_tx_data_verify(data,33);
			if (ret)
			{
				printk("%s() error7\n", __FUNCTION__);
				return ret;
			}
			/*
			data1[0] = 0x90;
			ret = fg8997_i2c_rx_data(data1,32);
			if (ret)
			{
				printk("%s() error8\n", __FUNCTION__);
				return ret;
			}
			*/
		} while(0);//memcmp(data+1, data1, 32));
		data[0] = 0xA0;
		data[2] = 0x01; data[1] = 0x00;
		data[4] = 0x01; data[3] = 0x00;
		data[6] = 0x01; data[5] = 0x00;
		data[8] = 0x01; data[7] = 0x00;
		data[10] = 0x01; data[9] = 0x00;
		data[12] = 0x01; data[11] = 0x00;
		data[14] = 0x01; data[13] = 0x00;
		data[16] = 0x01; data[15] = 0x00;
		data[18] = 0x01; data[17] = 0x00;
		data[20] = 0x01; data[19] = 0x00;
		data[22] = 0x01; data[21] = 0x00;
		data[24] = 0x01; data[23] = 0x00;
		data[26] = 0x01; data[25] = 0x00;
		data[28] = 0x01; data[27] = 0x00;
		data[30] = 0x01; data[29] = 0x00;
		data[32] = 0x01; data[31] = 0x00;
		do {
			ret = fg8997_i2c_tx_data_verify(data,33);
			if (ret)
			{
				printk("%s() error9\n", __FUNCTION__);
				return ret;
			}
			/*
			data1[0] = 0xA0;
			ret = fg8997_i2c_rx_data(data1,32);
			if (ret)
			{
				printk("%s() error10\n", __FUNCTION__);
				return ret;
			}
			*/
		} while(0);//memcmp(data+1, data1, 32));
		// Step 8. Lock Model Access
		do {
		data[0] = 0x62;
		data[1] = 0x00;
		data[2] = 0x00;
		ret = fg8997_i2c_tx_data(data,3);
		if (ret)
		{
			printk("%s() error11\n", __FUNCTION__);
			return ret;
		}
		data[0] = 0x63;
		data[1] = 0x00;
		data[2] = 0x00;
		ret = fg8997_i2c_tx_data(data,3);
		if (ret)
		{
			printk("%s() error12\n", __FUNCTION__);
			return ret;
		}
		// Step 9. Verify the Model Access is locked
		locked = 1;
		data[0] = 0x80;
		ret = fg8997_i2c_rx_data(data,32);
		if (ret)
		{
			printk("%s() error13\n", __FUNCTION__);
			return ret;
		}
		for(i=0;i<32;i++)
		{
			if(data[i] != 0)
			{
				locked = 0;
				break;
			}
		}
		if(!locked)
			continue;
		data[0] = 0x90;
		ret = fg8997_i2c_rx_data(data,32);
		if (ret)
		{
			printk("%s() error14\n", __FUNCTION__);
			return ret;
		}
		for(i=0;i<32;i++)
		{
			if(data[i] != 0)
			{
				locked = 0;
				break;
			}
		}
		if(!locked)
			continue;
		data[0] = 0xA0;
		ret = fg8997_i2c_rx_data(data,32);
		if (ret)
		{
			printk("%s() error15\n", __FUNCTION__);
			return ret;
		}
		for(i=0;i<32;i++)
		{
			if(data[i] != 0)
			{
				locked = 0;
				break;
			}
		}
		if(!locked)
			continue;
		} while(!locked);
		// Step 10. Write Custom Parameters
		data[0] = 0x38;// RCOMP0
		data[1] = 0x82;
		data[2] = 0x00;
		ret = fg8997_i2c_tx_data_verify(data, 3);
		if (ret)
		{
			printk("%s() error16\n", __FUNCTION__);
			return ret;
		}
		data[0] = 0x39;// TempCo
		data[1] = 0x74;
		data[2] = 0x30;
		ret = fg8997_i2c_tx_data_verify(data, 3);
		if (ret)
		{
			printk("%s() error17\n", __FUNCTION__);
			return ret;
		}
		// Step 11. Delay at least 350mS
		mdelay(400);
		// Step 12. Initialization Complete
		data[0] = 0x00;// STATUS
		ret = fg8997_i2c_rx_data(data, 2);
		if (ret)
		{
			printk("%s() error18\n", __FUNCTION__);
			return ret;
		}
		data[2] = data[1];
		data[1] = data[0] & 0xFD;
		data[0] = 0;// STATUS
		ret = fg8997_i2c_tx_data_verify(data, 3);
		if (ret)
		{
			printk("%s() error19\n", __FUNCTION__);
			return ret;
		}
		// Step 15. Read VFSOC
		data[0] = 0xFF;// VFSOC
		ret = fg8997_i2c_rx_data(data, 2);
		if (ret)
		{
			printk("%s() error20\n", __FUNCTION__);
			return ret;
		}

		//vfsoc = (data[1]>>1) + (data[0]>>7);
		//fg8997_dbg(FG8997_DBG_LEVEL_DATA, "vfsoc: %d %%\n", vfsoc);
		fg8997_dbg(FG8997_DBG_LEVEL_DATA, "vfsoc: 0x%x,0x%x\n", data[0], data[1]);
#if 0
		// Step 16. Save Learned Parameters
#endif
	}
	else
	{
		printk("no POR!!!\n");
	}
////////////////////////////////////////////////////////
//ly 20110907 for low power

		//clear pending.

		data[0]=0x00;
		fg8997_i2c_rx_data(data, 2);
		//printk("STATUS: ***data 0 is %d ****data1 is %d*******\n",data[0],data[1]);


		//data[1]&=~0x1;
		data[1]&=~(0x1<<2);
		data[2]=data[1];
		data[1]=data[0];
		data[0]=0x00;
		ret = fg8997_i2c_tx_data_verify(data, 3);
		if (ret)
		{
			printk("%s() error17\n", __FUNCTION__);
			return ret;
		}

		// enable alert threshold trigger for fuel gauge
		
		
		data[0]=0x1d;
		fg8997_i2c_rx_data(data, 2);
		fg8997_dbg(FG8997_DBG_LEVEL_DATA, "***data 0 is %d ****data1 is %d*******\n",data[0],data[1]);/*modify by wenpin.cui:delete useless log*/
		data[0]|=(0x1<<2);
		data[0]&=~(0x1<<5);

		data[2] =data[1];//high 8bit 4500mv
		data[1] = data[0];//low 8bit :3600mv
		data[0] = 0x1d;// reg: VALRT_TH
		ret = fg8997_i2c_tx_data_verify(data, 3);
		if (ret)
		{
			printk("%s() error17\n", __FUNCTION__);
			return ret;
		}

		//data[0]=0x1d;
		//fg8997_i2c_rx_data(data, 2);
		//printk("(***data 0 is %d ****data1 is %d*******\n",data[0],data[1]);
		

#if 0

		data[0]=0x01;
		fg8997_i2c_rx_data(data, 2);
		printk("(***data 0 is %d ****data1 is %d*******\n",data[0],data[1]);


		//ly: set vol and soc max/min val
		data[0] = 0x01;// reg: VALRT_TH
		data[1] = 0x00;//low 8bit :3600mv
		data[2] = 0xff;//high 8bit 4500mv
		ret = fg8997_i2c_tx_data_verify(data, 3);
		if (ret)
		{
			printk("%s() error17\n", __FUNCTION__);
			return ret;
		}
		data[0]=0x01;
		fg8997_i2c_rx_data(data, 2);
		printk("(***data0 is %d ****data1 is %d*******\n",data[0],data[1]);

#endif
#if 1
		data[0]=0x03;
		fg8997_i2c_rx_data(data, 2);
		//printk("(***data0 is %d ****data1 is %d*******\n",data[0],data[1]);


		//ly: set vol and soc max/min val
		data[0] = 0x03;// reg: VALRT_TH
		data[1] = FUEL_ALRT_THRESHOLD;//low 8bit :84
		data[2] = 0xff;//high 8bit 
		ret = fg8997_i2c_tx_data_verify(data, 3);
		if (ret)
		{
			printk("%s() error17\n", __FUNCTION__);
			return ret;
		}
		//data[0]=0x03;
		//fg8997_i2c_rx_data(data, 2);
		//printk("(***data 0 is %d ****data1 is %d*******\n",data[0],data[1]);

#endif		

///////////////////////////////////////////////////////		


	
	return 0;
}

static void fg8997_work(struct work_struct *work)
{
	struct fg8997_chip *chip = this_chip;
	int ret;
	int someerror = 0;
#ifdef FG8997_LOWVOL_TEST
	static int flag = 0;
#endif
	char data[3]={0};

	fg8997_dbg(FG8997_DBG_LEVEL_FUNC, "%s()\n", __FUNCTION__);

	if(NULL == chip)
		printk("Error in %s(), chip is NULL!!!\n",__FUNCTION__);

	ret = fg8997_get_temperature();
	if (ret<0)
		chip->bat_info.temperature = ret;

	ret = fg8997_get_vcell();
	if (ret<0)
		chip->bat_info.vcell = 3800*1000;// error
	else
		chip->bat_info.vcell = ret*1000;
	ret = fg8997_get_soc();
	if (ret<0)
	{
		chip->bat_info.soc = 80;// error
		someerror = 1;
	}
	else
		chip->bat_info.soc = ret;

//////////////////////////////////////////////////////////
//ly for low power
	if (chip->bat_info.soc >= FUEL_ALRT_THRESHOLD){
		unsigned char data[3]={0};
		//clear pending.

		//////////////////////////////////////////////////////////
		data[0]=0x00;
		fg8997_i2c_rx_data(data, 2);
		//printk("STATUS: ***data 0 is %d ****data1 is %d*******\n",data[0],data[1]);
		if(data[1] & (0x1<<2)){

				//data[1]&=~0x1;
				data[1]&=~(0x1<<2);
				data[2]=data[1];
				data[1]=data[0];
				data[0]=0x00;
				ret = fg8997_i2c_tx_data_verify(data, 3);
				if (ret)
				{
					printk("%s() error17\n", __FUNCTION__);
					return ret;
				}
		  }
	}
		//data[0]=0x00;
		//fg8997_i2c_rx_data(data, 2);
		//printk("STATUS: ***data 0 is %d ****data1 is %d*******\n",data[0],data[1]);

/////////////////////////

#ifdef FG8997_LOWVOL_TEST
	flag++;
	if (flag > 4)
		chip->bat_info.soc = 5;
	else if(flag > 3)
		chip->bat_info.soc = 10;
	else if(flag > 2)
		chip->bat_info.soc = 15;
#endif

	fg8997_get_status();

	power_supply_changed(&(chip->battery[CHARGER_BATTERY]));

	if (someerror)
		schedule_delayed_work(&chip->work, msecs_to_jiffies(1000));
	else
		schedule_delayed_work(&chip->work, msecs_to_jiffies(30000));
}

static enum power_supply_property fg8997_battery_props[] = {
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_PRESENT,
	//POWER_SUPPLY_PROP_TEMP,
};

static enum power_supply_property s5p_power_props[] = {
	POWER_SUPPLY_PROP_ONLINE,
};

static char *supply_list[] = {
	"battery",
};
//ly 20110907 for low power 
static irqreturn_t irq_handler(int irqno, void *param)
{
	//printk("***********************************************\n");
	//printk("**************fg8997:  irq_handler****************\n");
	//printk("***********************************************\n");


	__cancel_delayed_work(&this_chip->work);/* in irq context, should use this API instead*/
	schedule_delayed_work(&this_chip->work, 0);

	
	return IRQ_HANDLED; 

}

static int __devinit fg8997_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct fg8997_chip *chip;
	char version[2];
	int ret;
	int i;
	printk("**fg8997_probe****\n");
	fg8997_dbg(FG8997_DBG_LEVEL_INIT, "name=%s, addr=0x%x @ IIC%d, irq=%d\n",
			client->name,client->addr,client->adapter->nr,client->irq);
	if (!i2c_check_functionality(adapter, I2C_FUNC_I2C))//I2C_FUNC_SMBUS_BYTE
		return -EIO;

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	this_chip = chip;
	chip->client = client;

	i2c_set_clientdata(client, chip);

	chip->battery[CHARGER_BATTERY].name		= "battery";
	chip->battery[CHARGER_BATTERY].type		= POWER_SUPPLY_TYPE_BATTERY;
	chip->battery[CHARGER_BATTERY].get_property	= fg8997_get_property;
	chip->battery[CHARGER_BATTERY].properties	= fg8997_battery_props;
	chip->battery[CHARGER_BATTERY].num_properties	= ARRAY_SIZE(fg8997_battery_props);

	chip->battery[CHARGER_USB].name		= "usb";
	chip->battery[CHARGER_USB].type		= POWER_SUPPLY_TYPE_USB;
	chip->battery[CHARGER_USB].supplied_to	= supply_list;
	chip->battery[CHARGER_USB].num_supplicants = ARRAY_SIZE(supply_list);
	chip->battery[CHARGER_USB].get_property	= s5p_power_get_property;
	chip->battery[CHARGER_USB].properties	= s5p_power_props;
	chip->battery[CHARGER_USB].num_properties	= ARRAY_SIZE(s5p_power_props);

	chip->battery[CHARGER_AC].name		= "ac";
	chip->battery[CHARGER_AC].type		= POWER_SUPPLY_TYPE_MAINS;
	chip->battery[CHARGER_AC].supplied_to	= supply_list;
	chip->battery[CHARGER_AC].num_supplicants = ARRAY_SIZE(supply_list);
	chip->battery[CHARGER_AC].get_property	= s5p_power_get_property;
	chip->battery[CHARGER_AC].properties	= s5p_power_props;
	chip->battery[CHARGER_AC].num_properties	= ARRAY_SIZE(s5p_power_props);

	chip->bat_info.charging_source = CHARGER_BATTERY;
	chip->bat_info.health = POWER_SUPPLY_HEALTH_GOOD;
	chip->bat_info.tech = POWER_SUPPLY_TECHNOLOGY_LION;

	for(i=0;i<ARRAY_SIZE(chip->battery);i++)
	{
		ret = power_supply_register(&client->dev, &(chip->battery[i]));
		if (ret) {
				printk("**failed to register power supply****\n");
			dev_err(&client->dev, "failed to register power supply %d\n",i);
			i2c_set_clientdata(client, NULL);
			kfree(chip);
			return ret;
		}
	}



	version[0] = 0x21;
	fg8997_i2c_rx_data(version, 2);
	if (version[0]!=0x92 || version[1]!=0)
		printk("fg8997 wrong firmware version: %02x%02x!\n", version[1], version[0]);
	else
		fg8997_dbg(FG8997_DBG_LEVEL_INIT, "firmware version: %02x%02x\n", version[1], version[0]);

	fg8997_init_reg();

	s5p_battery_initial = 1;

	INIT_DELAYED_WORK_DEFERRABLE(&chip->work, fg8997_work);
	schedule_delayed_work(&chip->work, msecs_to_jiffies(10));

/////////////////////////////////////////////////////////
//ly for low power 
	ret=gpio_request(FUEL_ALRT, "fuel alrt");
	if(ret){
		printk("erro request fuel alart io!!");
		goto err;
		}

	gpio_direction_input(FUEL_ALRT);
	ret = request_irq(gpio_to_irq(FUEL_ALRT), irq_handler,
			IRQF_SAMPLE_RANDOM|IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
			"fuel alrt",NULL);
	if (ret < 0)
	{
		printk("request_irq(FUEL_ALRT) failed  !!!\n");
		gpio_free(FUEL_ALRT);
		goto err;
	}
	enable_irq_wake(gpio_to_irq(FUEL_ALRT));
	
	//enable_irq(gpio_to_irq(FUEL_ALRT));
		
///////////////////////////////////////////////////////	
	
	printk("**probe finished !!****\n");
	return 0;
err:
	return ret;
}

static int __devexit fg8997_remove(struct i2c_client *client)
{
	struct fg8997_chip *chip = i2c_get_clientdata(client);
	int i;

	for(i=0;i<ARRAY_SIZE(chip->battery);i++)
		power_supply_unregister(&(chip->battery[i]));
	cancel_delayed_work(&chip->work);
	i2c_set_clientdata(client, NULL);
	kfree(chip);
	return 0;
}

#ifdef CONFIG_PM
static int fg8997_suspend(struct i2c_client *client,
		pm_message_t state)
{
	struct fg8997_chip *chip = i2c_get_clientdata(client);
	cancel_delayed_work_sync(&chip->work);
	
	return 0;
}

static int fg8997_resume(struct i2c_client *client)
{
	struct fg8997_chip *chip = i2c_get_clientdata(client);

	schedule_delayed_work(&chip->work, FG8997_DELAY);

	return 0;
}
#else
#define fg8997_suspend NULL
#define fg8997_resume NULL
#endif /* CONFIG_PM */

static const struct i2c_device_id fg8997_id[] = {
	{ FG8997_I2C_NAME, 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, fg8997_id);

static struct i2c_driver fg8997_i2c_driver = {
	.driver	= {
		.name	= FG8997_I2C_NAME,
	},
	.probe		= fg8997_probe,
	.remove		= __devexit_p(fg8997_remove),
	.suspend	= fg8997_suspend,
	.resume		= fg8997_resume,
	.id_table	= fg8997_id,
};

static int __init fg8997_init(void)
{
	fg8997_dbg(FG8997_DBG_LEVEL_INIT, "init\n");
	return i2c_add_driver(&fg8997_i2c_driver);
}
module_init(fg8997_init);

static void __exit fg8997_exit(void)
{
	i2c_del_driver(&fg8997_i2c_driver);
}
module_exit(fg8997_exit);

MODULE_AUTHOR("Sheng Liang <liang.sheng@samsung.com>");
MODULE_DESCRIPTION("MAX8997 Fuel Gauge");
MODULE_LICENSE("GPL");
