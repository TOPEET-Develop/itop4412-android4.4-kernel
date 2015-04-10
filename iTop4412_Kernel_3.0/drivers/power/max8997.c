/*
 *  drivers/power/max8997.c
 *
 *  PMU Device driver for Max8997 @ TA4,S5PC210
 *
 *  Copyright (C) 2008 Samsung Electronics
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Author: robin.wang(xiebin.wang@samsung.com)
 * Date: 2011.05.09
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mutex.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/power_supply.h>
#include <linux/max17040_battery.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/signal.h>
#include <linux/ioport.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/kmod.h>
#include <linux/vmalloc.h>
#include <linux/init.h>
#include <asm/io.h>
#include <asm/page.h>
#include <mach/irqs.h>
#include <linux/semaphore.h>
#include <mach/map.h>

#include <linux/miscdevice.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/platform_device.h>
#include <plat/gpio-cfg.h>
#include <mach/regs-gpio.h>
#include <mach/gpio.h>

#include <mach/max8997.h>
#include <linux/i2c/max8997.h>


#define S5P_PMIC_MINOR	250

static struct i2c_client max8997_i2c_client;

static int max8997_write(unsigned char address,unsigned char val)
{

	unsigned char  msg1[4] = { address & 0xff,(val)&0xff};

	struct i2c_msg msgs[1] = {
		{ .addr = MAX8997_ADDR, .flags = 0	   , .len = 2, .buf = msg1 }
	};
	
		
	if (i2c_transfer(max8997_i2c_client.adapter, &msgs[0], 1) != 1) {
		printk("Robin: i2c_transfer error\n");
		return -EIO;
	}


	return 0;
		
}

static int max8997_read(unsigned char address,unsigned char * pVal)
{
	
	unsigned char  msg1[2] = { address & 0xff };
	unsigned char  msg2[2];

	struct i2c_msg msgs[2] = {
		{ .addr = MAX8997_ADDR, .flags = 0	   , .len = 1, .buf = msg1 },
		{ .addr = MAX8997_ADDR, .flags = I2C_M_RD, .len = 1, .buf = msg2 }
	};
	

	if (i2c_transfer(max8997_i2c_client.adapter, &msgs[0], 2) != 2) {
		printk("Robin: i2c_transfer error\n");
		return -EIO;
	}
	pVal[0] = msg2[0];
	

	return 0;
		
}


static int  max8997_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	unsigned char val;
	int i;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
		return -EIO;
	memcpy(&max8997_i2c_client,client,sizeof(struct i2c_client));

	max8997_read(0,&val);
	if(val == 0x77)
	{
		printk("Robin:The Connect( I2C1<--->Max8997 ) IS OK \n");
	}
	else
	{
		printk("Robin: The Connect(I2C<-->Max8997) IS ERROR. Pls Check......\n");
	}

	/*
	* BUCK 5: 1.1 --> 1.2V
	* BUCK 6: hw pin -> sw bit control
	* LDO 1: 3.3 --> 1.8V 
	* LDO 8: 3.0 --> 3.3V
	* LDO 5: 1.2 --> 1.8V
	* LDO 9: 2.8 --> 3.0V
	* LDO 11: 2.8 --> 1.0V
	* LDO 12: 1.2 --> 1.8V
	* LDO 13: 2.8 --> 1.0V
	* LDO 16: 3.3 --> 2.8V
	* LDO 18: 3.3 --> 1.8V
	*/
	//
	max8997_write(0x50,0x24);
	max8997_write(0x51,0x14);

	//BUCK1
	// 1.0 --> 1.2v  
	max8997_read(MAX8997_BUCK1_DVS,&val);
	val &= ~(0x3f);
	val |= 0x16;   
	max8997_write(MAX8997_BUCK1_DVS,val);
	//The DVS is enable, so maybe the gpio config is not correct.
	//Currently,We just set all BUCK1 DVS to 1.2v
	//Need implement later for all the DVS.
	for(i = 1; i < 8; i++)
	max8997_write(MAX8997_BUCK1_DVS + i,val); 
	
	//BUCK2
	max8997_read(MAX8997_BUCK2_DVS,&val);
	val &= ~(0x3f);
	val |= 0x12;
	max8997_write(MAX8997_BUCK2_DVS,val);

	//The G3D is setting to 1.15v~~ need optimize later.
	//BUCK3,1.15v
	max8997_read(MAX8997_BUCK3_DVS,&val);
	val &= ~(0x3f);
	val |= 0x8;
	max8997_write(MAX8997_BUCK3_DVS,val);
	
	
	//BUCK 5: 1.1-->1.2V
	max8997_read(MAX8997_BUCK5_DVS,&val);
	val &= ~(0x3f);
	val |= 0x16;//1.1v
	max8997_write(MAX8997_BUCK5_DVS,val);

	//BUCK 6:
	//0x38---0x43.
	max8997_write(MAX8997_BUCK6_CTRL + 1,0x43);
	//BUCK 6, hardware pin control --> ENBUCK6 bit control
	max8997_read(MAX8997_BUCK6_CTRL,&val);
	val |= 0x2;//hw pin --> ENBUCK 6 bit control
	max8997_write(MAX8997_BUCK6_CTRL,val);

	//LDO5, 1.2V --> 1.8V
	max8997_read(MAX8997_LDO5_CTRL,&val);
	val &= ~(0x3f);
	val |= 0x14; 
	max8997_write(MAX8997_LDO5_CTRL,val);	

	//LDO 9, 2.8V -->3.0V,VDD_TF
/*	max8997_read(MAX8997_LDO9_CTRL,&val);
	val &= ~(0x3f);
	val |= 0x2c;//3.2v, 0x32-->3.3v, 0x2c-->3.0v
	max8997_write(MAX8997_LDO9_CTRL,val);*/
	
	//LDO1, 3.3V --> 1.8V
	max8997_read(MAX8997_LDO1_CTRL,&val);
	val &= ~(0x3f);
	val |= 0x14; 
	max8997_write(MAX8997_LDO1_CTRL,val);	

	//LDO8, 3.0V --> 3.3V
	max8997_read(MAX8997_LDO8_CTRL,&val);
	val &= ~(0x3f);
	val |= 0x2c; 
	max8997_write(MAX8997_LDO8_CTRL,val);	

	//LDO 11, 2.8V -->1.0V
	max8997_read(MAX8997_LDO11_CTRL,&val);
	val &= ~(0x3f);
	val |= 0x04; 
	max8997_write(MAX8997_LDO11_CTRL,val);

	//LDO 12, 1.2V -->1.8V
	max8997_read(MAX8997_LDO12_CTRL,&val);
	val &= ~(0x3f);
	val |= 0x14;//1.1v
	max8997_write(MAX8997_LDO12_CTRL,val);

	//LDO 13, 2.8V -->1.0V
	max8997_read(MAX8997_LDO13_CTRL,&val);
	val &= ~(0x3f);
	val |= 0x04;//1.8v
	max8997_write(MAX8997_LDO13_CTRL,val);
	
	//LDO 16, 3.3V -->2.8V
	max8997_read(MAX8997_LDO16_CTRL,&val);
	val &= ~(0x3f);
	val |= 0x28;//2.8v
	max8997_write(MAX8997_LDO16_CTRL,val);

	//LDO 18, 3.3V -->1.8V
	max8997_read(MAX8997_LDO18_CTRL,&val);
	val &= ~(0x3f);
	val |= 0x14;//1.8v
	max8997_write(MAX8997_LDO18_CTRL,val);

	max8997_write(MAX8997_BOOST_CNTL,0x1D);//output 5.0v
	/*			 
	*	default     power up
	*	BUCK 4 : OFF   ->   ON
	*	BUCK 6 : OFF   -> 	  ON  (maybe it will power on in the u-boot)
	*	LDO 11~LDO18: OFF -> ON
	*	others   : ON    --> ?/ON
	*/

	// All the LDOs&&BUCKs ARE PowerON.........
	/*
     PMIC_CONTROL_VDD12_5M,// 0x03,BUCK4
    PMIC_CONTROL_VDD_M12,// 0x04
    PMIC_CONTROL_VDD_LCD,// 0x05,BUCK 6
    PMIC_CONTROL_VDD33_UOTG,//0x0c,LDO8
    PMIC_CONTROL_VDD10_USH,//0xf,LDO 11
    PMIC_CONTROL_VDD18_CAM,//0x10,LDO 12
    PMIC_CONTROL_VDD10_MIPI,//0x11,LDO 13
    PMIC_CONTROL_VDD18_MIPI,//0X12,LDO 14
    PMIC_CONTROL_VDD28_AF,//0x13,LDO 15
    PMIC_CONTROL_VDD28_CAM,//0x14,LDO 16
    PMIC_CONTROL_VDD33_A31,//0x15,LDO 17
    PMIC_CONTROL_VDD18_A31,//0x16,LDO 18
    */


	//PMIC_Control_Set(PMIC_CONTROL_VDD33_UOTG,POWERON);
	//Robin: For VDD18_CAM & VDD28_CAM, Power On then when call camera reset.
	//Attention: xiebin.wang@20110530 Must power on all the camera module here...

    	PMIC_Control_Set(PMIC_CONTROL_VDD12_5M,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD_M12,POWERON);
	//PMIC_Control_Set(PMIC_CONTROL_VDD10_USH,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD18_CAM,POWERON);	
	PMIC_Control_Set(PMIC_CONTROL_VDD10_MIPI,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD18_MIPI,POWERON);	
	PMIC_Control_Set(PMIC_CONTROL_VDD28_AF,POWERON);	
	PMIC_Control_Set(PMIC_CONTROL_VDD28_CAM,POWERON);	
	PMIC_Control_Set(PMIC_CONTROL_VDD33_A31,POWERON);
   	PMIC_Control_Set(PMIC_CONTROL_VDD18_A31,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD_LCD,POWERON);
#if 1
	//printk("shengliang test for USB Host\n");
	PMIC_Control_Set(PMIC_CONTROL_VDD50,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD10_USH,POWERON);
#endif

	printk("Robin: All The Bucks & LDOs Are Power On, Plz Check them ....\n");

//from swkim : temp.
//close wifi ;temp
#if 1
	//Currently, PowerON the WIFI here...
	//Need optimize later....
	printk("Wifi: PWDN (LOW--->HIGH) ---GPZ(5)\n"); 
	  //chip_pwd_l  output 0             
	 s3c_gpio_setpull(EXYNOS4_GPZ(5), S3C_GPIO_PULL_UP);
	 gpio_set_value(EXYNOS4_GPZ(5), 0);
	 s3c_gpio_cfgpin(EXYNOS4_GPZ(5), S3C_GPIO_SFN(1));
     	mdelay(300);  
     	//chip_pwd_l  output 1  
	 gpio_set_value(EXYNOS4_GPZ(5), 1);
#endif		 
	return 0;
}

static int __devexit max8997_remove(struct i2c_client *client)
{
	return 0;
}

#ifdef CONFIG_PM

static int max8997_suspend(struct i2c_client *client,
		pm_message_t state)
{
	
	return 0;
}

static int max8997_resume(struct i2c_client *client)
{
	
	return 0;
}

#else

#define max8997_suspend NULL
#define max8997_resume NULL

#endif /* CONFIG_PM */



int PMIC_Control_Set(PMIC_FUN_TYPE type, int flag)
{
	unsigned char value;
		

	switch(type)
	{
		case PMIC_CONTROL_VDDARM:
			//BUCK1, 1,25V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_BUCK1_CTRL,(unsigned char *)&value);
				value &= ~BUCK_MASK;
				max8997_write(MAX8997_BUCK1_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_BUCK1_CTRL,(unsigned char *)&value);
				value &= ~BUCK_MASK;
				value |= BUCK_ON;
				max8997_write(MAX8997_BUCK1_CTRL,value);
				
			}
			
			break;
		case PMIC_CONTROL_VDDINT:
			//BUCK2, 1,1V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_BUCK2_CTRL,(unsigned char *)&value);
				value &= ~BUCK_MASK;
				max8997_write(MAX8997_BUCK2_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_BUCK2_CTRL,(unsigned char *)&value);
				value &= ~BUCK_MASK;
				value |= BUCK_ON;
				max8997_write(MAX8997_BUCK2_CTRL,value);
				
			}
			
			break;
		case PMIC_CONTROL_VDDG3D:
			//BUCK3, 1.2V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_BUCK3_CTRL,(unsigned char *)&value);
				value &= ~BUCK_MASK;
				max8997_write(MAX8997_BUCK3_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_BUCK3_CTRL,(unsigned char *)&value);
				value &= ~BUCK_MASK;
				value |= BUCK_ON;
				max8997_write(MAX8997_BUCK3_CTRL,value);
				
			}
			
			break;
		case PMIC_CONTROL_VDD12_5M:
			//BUCK4 : 1.2
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_BUCK4_CTRL,(unsigned char *)&value);
				value &= ~BUCK_MASK;
				max8997_write(MAX8997_BUCK4_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_BUCK4_CTRL,(unsigned char *)&value);
				value &= ~BUCK_MASK;
				value |= BUCK_ON;
				max8997_write(MAX8997_BUCK4_CTRL,value);
				
			}
			break;
		case PMIC_CONTROL_VDD_M12:
			//BUCK 5, 1.1V
			printk("Robin: Implement Later...\n");
			break;
		case PMIC_CONTROL_VDD_LCD:
			//BUCK6, 3.3V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_BUCK6_CTRL,(unsigned char *)&value);
				value &= ~BUCK_MASK;
				max8997_write(MAX8997_BUCK6_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_BUCK6_CTRL,(unsigned char *)&value);
				value &= ~BUCK_MASK;
				value |= BUCK_ON;
				max8997_write(MAX8997_BUCK6_CTRL,value);
				
			}
			break;

			
		case PMIC_CONTROL_VDD_BUCK7:
			//Robin: Currently, only turn on/off the power. Don't  change the Voltage..
			//BUCK 7 :2.0V
			printk("Robin: Implement Later...\n");
			break;
			
		case PMIC_CONTROL_VDD18_HSIC:
			//LDO1 3.3V ---->  1.8V 
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO1_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= (0x1<<6); //  It's controled by PWREN
				max8997_write(MAX8997_LDO1_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO1_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO1_CTRL,value);
				
			}		
			break;
		case PMIC_CONTROL_VDD_ALIVE:
			//Robin: Currently, only turn on/off the power. Don't  change the Voltage..
			//LDO2  1.1V
			printk("Robin: Implement Later...\n");
			
			break;

		case PMIC_CONTROL_VDD18_ABB:
			//LDO 5: 1.2 V----> 1.8V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO5_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO5_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO5_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO5_CTRL,value);
				
			}
			break;
		case PMIC_CONTROL_VDDIOAP_18:
			//LDO 6: 1.8V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO6_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO6_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO6_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO6_CTRL,value);
				
			}
			break;
    	case PMIC_CONTROL_VDDIOPERI_18:
			//LDO 7: 1.8V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO7_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO7_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO7_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO7_CTRL,value);
				
			}
			break;
		case PMIC_CONTROL_VDD33_UOTG:
			//LDO 8: 3.3V 
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO8_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO8_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO8_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO8_CTRL,value);
				
			}
			break;
		case PMIC_CONTROL_VDD_TF:
			//LDO 9: 2.8V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO9_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO9_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO9_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO9_CTRL,value);
				
			}
			break;
			
		case PMIC_CONTROL_VDD_PLL:
			//LDO 10: 1.1V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO10_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= (0x1<<6); //  It's controled by PWREN
				max8997_write(MAX8997_LDO10_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO10_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO10_CTRL,value);
				
			}
			
			break;
		case PMIC_CONTROL_VDD10_USH:
			//LDO 11: 2.8V ----> 1.0V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO11_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO11_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO11_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO11_CTRL,value);
				
			}
			
			break;
		case PMIC_CONTROL_VDD18_CAM:
			//LDO 12: default off, 1.8V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO12_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO12_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO12_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO12_CTRL,value);
				
			}
			
			break;
		case PMIC_CONTROL_VDD10_MIPI:
			//LDO 13,default off,(1.2-->1.0V)
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO13_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO13_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO13_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO13_CTRL,value);
				
			}
			
			break;
		case PMIC_CONTROL_VDD18_MIPI:
			//LDO 14: default off, (3.3 -->1.8V)
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO14_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO14_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO14_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO14_CTRL,value);
				
			}
			break;
			
		case PMIC_CONTROL_VDD28_AF:
			//LDO 15: default off,(3.3-->2.8V)
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO15_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO15_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO15_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO15_CTRL,value);
				
			}
			break;
		case PMIC_CONTROL_VDD28_CAM:
			//LDO 16: default off, 2.8V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO16_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO16_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO16_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO16_CTRL,value);
				
			}
			break;
		case PMIC_CONTROL_VDDQ_M12:
			//LDO 21: 1.2V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO21_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= (0x1<<6); //  It's controled by PWREN
				max8997_write(MAX8997_LDO21_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO21_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO21_CTRL,value);
				
			}
			break;
		case PMIC_CONTROL_VDD33_A31:
			//LDO 17: default off,3.3V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO17_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO17_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO17_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO17_CTRL,value);
				
			}
			
			break;
			
	case PMIC_CONTROL_VDD18_A31:
			//LDO 18 : default off ,1.8V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_LDO18_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				max8997_write(MAX8997_LDO18_CTRL,value);
			}
			else
			{
				max8997_read(MAX8997_LDO18_CTRL,(unsigned char *)&value);
				value &= ~LDO_MASK;
				value |= LDO_ON;
				max8997_write(MAX8997_LDO18_CTRL,value);
				
			}

			
			break;

		case PMIC_CONTROL_VDD50:
			//BOOST ,5V
			if(flag == POWEROFF)
			{	
				max8997_read(MAX8997_BOOST_CNTL,(unsigned char *)&value);
				value &= ~BOOST_MASK;
				max8997_write(MAX8997_BOOST_CNTL,value);
			}
			else
			{
				max8997_read(MAX8997_BOOST_CNTL,(unsigned char *)&value);
				value &= ~BOOST_MASK;
				value |= BOOST_EN;
				max8997_write(MAX8997_BOOST_CNTL,value);
				
			}
			
			break;
			
		default:
			printk("Robin: MAX8997 PMIC Control....Invalid PMIC FUNC Type\n");
			break;
	}
	

	return 0;
    
}
EXPORT_SYMBOL_GPL(PMIC_Control_Set);


int s5p_pmic_open(struct inode *inode, struct file *file)
{

	printk("s5p_pmic_open()\n");	

	return 0;
}
int s5p_pmic_release(struct inode *inode, struct file *file)
{
	printk("s5p_pmic_release()\n");
	return 0;
}

int s5p_pmic_mmap(struct file* filp, struct vm_area_struct *vma) 
{
	
	return 0;
}
ssize_t s5p_pmic_read ( struct file *file, char __user *userbuf, size_t count, loff_t *f_pos )
{
	return 0;
}
ssize_t s5p_pmic_write ( struct file *file, const char __user *userbuf, size_t count, loff_t *f_pos )
{
	return 0;
}

static int s5p_pmic_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{


	return 0;
}

const struct file_operations s5p_pmic_fops = {
	.owner      = THIS_MODULE,
	.open       = s5p_pmic_open,
	.release    = s5p_pmic_release,
	.mmap       = s5p_pmic_mmap,
	.read		= s5p_pmic_read,
	.write		= s5p_pmic_write,
	.unlocked_ioctl      = s5p_pmic_ioctl,
};

static struct miscdevice s5p_pmic_dev = {
	.minor		= S5P_PMIC_MINOR,
	.name		= "s5p-pmic",
	.fops		= &s5p_pmic_fops,
};

int s5p_pmic_probe(struct platform_device *pdev)
{
	int ret;

	printk("s5p_pmic_probe called\n");

	ret = misc_register(&s5p_pmic_dev);
	if (ret) {
		printk (KERN_ERR "cannot register miscdev on minor=%d (%d)\n", S5P_PMIC_MINOR, ret);
		return ret;
	}

	printk("s5p_pmic_probe success\n");

	return 0;  
}

static int s5p_pmic_remove(struct platform_device *dev)
{
	
	misc_deregister(&s5p_pmic_dev);

	return 0;
}

#ifdef CONFIG_PM

static int s5p_pmic_suspend(struct platform_device *dev, pm_message_t state)

{
		printk("s5p_pmic_suspend()\n");

		/*
		    PMIC_CONTROL_VDDARM = 0x00,
		    PMIC_CONTROL_VDDINT, // 0x01
		    PMIC_CONTROL_VDDG3D, // 0x02
		    PMIC_CONTROL_VDD12_5M,// 0x03,BUCK4
		    PMIC_CONTROL_VDD_M12,// 0x04
		    PMIC_CONTROL_VDD_LCD,// 0x05,BUCK 6
		    PMIC_CONTROL_VDD_BUCK7,// 0x06,BUCK 7
		    PMIC_CONTROL_VDD18_HSIC,// 0x07,LDO 1
		    PMIC_CONTROL_VDD_ALIVE,// 0x08,LDO 2
		    PMIC_CONTROL_VDD18_ABB,//0x09,LDO5
		    PMIC_CONTROL_VDDIOAP_18,// 0x0a,LDO 6,
		    PMIC_CONTROL_VDDIOPERI_18,//0xb,LDO 7,
		    PMIC_CONTROL_VDD33_UOTG,//0x0c,LDO8
		    PMIC_CONTROL_VDD_TF,//0xd,LDO 9
		    PMIC_CONTROL_VDD_PLL,//0xe,LDO 10
		    PMIC_CONTROL_VDD10_USH,//0xf,LDO 11
		    PMIC_CONTROL_VDD18_CAM,//0x10,LDO 12
		    PMIC_CONTROL_VDD10_MIPI,//0x11,LDO 13
		    PMIC_CONTROL_VDD18_MIPI,//0X12,LDO 14
		    PMIC_CONTROL_VDD28_AF,//0x13,LDO 15
		    PMIC_CONTROL_VDD28_CAM,//0x14,LDO 16
		    PMIC_CONTROL_VDD33_A31,//0x15,LDO 17
		    PMIC_CONTROL_VDD18_A31,//0x16,LDO 18
		    PMIC_CONTROL_VDDQ_M12,//0x17,LDO 21
		    PMIC_CONTROL_VDD50, // 0X18, boost_cntrl
	*/
		
		PMIC_Control_Set(PMIC_CONTROL_VDD12_5M,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDD_LCD,POWEROFF);


		PMIC_Control_Set(PMIC_CONTROL_VDD10_USH,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDD33_UOTG,POWEROFF);
	
		PMIC_Control_Set(PMIC_CONTROL_VDD18_A31,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDD10_MIPI,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDD18_CAM,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDD28_CAM,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDD28_AF,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDD33_A31,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDD18_MIPI,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDD50,POWEROFF);
		
		PMIC_Control_Set(PMIC_CONTROL_VDDQ_M12,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDDG3D,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDD_PLL,POWEROFF);
		PMIC_Control_Set(PMIC_CONTROL_VDDINT,POWEROFF); 
 		PMIC_Control_Set(PMIC_CONTROL_VDDARM,POWEROFF); 
		PMIC_Control_Set(PMIC_CONTROL_VDD18_ABB,POWEROFF);

	return 0;
}

static int s5p_pmic_resume(struct platform_device *pdev)

{
	printk("s5p_pmic_resume()\n");
	PMIC_Control_Set(PMIC_CONTROL_VDD18_ABB,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDDARM,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDDINT,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD_PLL,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDDG3D,POWERON);	
	PMIC_Control_Set(PMIC_CONTROL_VDDQ_M12,POWERON);

	PMIC_Control_Set(PMIC_CONTROL_VDD50,POWERON);
	
	PMIC_Control_Set(PMIC_CONTROL_VDD12_5M,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD_LCD,POWERON);

	PMIC_Control_Set(PMIC_CONTROL_VDD10_USH,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD33_UOTG,POWERON);

	PMIC_Control_Set(PMIC_CONTROL_VDD18_A31,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD10_MIPI,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD18_CAM,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD28_CAM,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD28_AF,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD33_A31,POWERON);
	PMIC_Control_Set(PMIC_CONTROL_VDD18_MIPI,POWERON);

	return 0;
}

#else

#define s5p_pmic_suspend NULL
#define s5p_pmic_resume NULL

#endif /* CONFIG_PM */

static const struct i2c_device_id max8997_id[] = {
	{ MAX8997_I2C_NAME, 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, max8997_id);

static struct i2c_driver max8997_i2c_driver = {
	.driver	= {
		.name	= MAX8997_I2C_NAME,
	},
	.probe		= max8997_probe,
	.remove		= __devexit_p(max8997_remove),
	.suspend	= max8997_suspend,
	.resume		= max8997_resume,
	.id_table	= max8997_id,
};

static struct platform_driver s5p_pmic_driver = {
       .probe          = s5p_pmic_probe,
       .remove         = s5p_pmic_remove,
       .suspend        = s5p_pmic_suspend,
       .resume         = s5p_pmic_resume,
       .driver		= {
		    .owner	= THIS_MODULE,
		    .name	= "s5p-pmic",
	},
};


static int __init max8997_init(void)
{
	int ret;
	
	i2c_add_driver(&max8997_i2c_driver);

	ret = platform_driver_register(&s5p_pmic_driver);
	if( ret != 0) {
		printk(KERN_ERR "s5p_pmic_driver platform device register failed\n");
		return -1;
	}
	else		
		printk("s5p_pmic_driver platform device register successful\n");
	
	return 0;
}
subsys_initcall(max8997_init);

static void __exit max8997_exit(void)
{
	i2c_del_driver(&max8997_i2c_driver);
}
module_exit(max8997_exit);

MODULE_AUTHOR("Robin Wang <xiebin.wang@samsung.com>");
MODULE_DESCRIPTION("MAX8997 PMU");
MODULE_LICENSE("GPL");

