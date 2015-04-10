/*
 * Copyright (c) 2011 PIXTREE, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable PIXTREE license agreement.
 */ 

#include <linux/errno.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/mach-types.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/map.h>

#include <asm/atomic.h>

#include "pix_i2c.h"

#define PIN_SDA			EXYNOS4_GPX0(5)
#define PIN_SCL			EXYNOS4_GPX0(6)
#define PIX_I2C_MINOR	(249)

#define SDA_IN			gpio_direction_input(PIN_SDA)
#define SDA_OUT			gpio_direction_output(PIN_SDA,1)
#define SDA_LOW			gpio_set_value(PIN_SDA, 0)
#define SDA_HIGH		gpio_set_value(PIN_SDA, 1)
#define SDA_DETECT		gpio_get_value(PIN_SDA)

#define SCL_LOW			gpio_set_value(PIN_SCL, 0)
#define SCL_HIGH		gpio_set_value(PIN_SCL, 1)
#define SCL_OUT			gpio_direction_output(PIN_SCL,1)

#define I2C_DELAY		udelay(2)
#define I2C_DELAY_LONG	udelay(50)

static atomic_t scull_available = ATOMIC_INIT(1);


int InitGPIO(void)
{
	gpio_request(PIN_SDA,"SDA");
	gpio_request(PIN_SCL,"SCL");

	s3c_gpio_cfgpin(PIN_SDA, S3C_GPIO_OUTPUT);
	s3c_gpio_cfgpin(PIN_SCL, S3C_GPIO_OUTPUT);

	s3c_gpio_setpull(PIN_SDA, S3C_GPIO_PULL_UP);
	s3c_gpio_setpull(PIN_SCL, S3C_GPIO_PULL_UP);

	gpio_direction_output(PIN_SCL,1);
	gpio_direction_output(PIN_SDA,1);
	return 0;
}

void ReleaseGPIO(void)
{
	gpio_free(PIN_SDA);
	gpio_free(PIN_SCL);

	return;
}

void I2c_start(void)
{
	SDA_HIGH;
	I2C_DELAY;
	I2C_DELAY;
	SCL_HIGH;
	I2C_DELAY;
	SDA_LOW;
	I2C_DELAY;
	SCL_LOW;
	I2C_DELAY;
}

void I2c_stop(void)
{
	SDA_LOW;
	I2C_DELAY;
	SCL_HIGH;
	I2C_DELAY;
	SDA_HIGH;
	I2C_DELAY_LONG;
}

unsigned char I2c_ack_detect(void)
{
	SDA_IN;	// SDA Input Mode
	I2C_DELAY;
	SCL_HIGH;
	I2C_DELAY;
	if (SDA_DETECT)
	{
		SDA_OUT;
		return ERROR_CODE_FALSE; // false
	}
	I2C_DELAY;
	SCL_LOW;
	SDA_OUT;
	return ERROR_CODE_TRUE; // true
}

void I2c_ack_send(void)
{
	SDA_OUT;
	SDA_LOW;
	I2C_DELAY;
	SCL_HIGH;
	I2C_DELAY;
	SCL_LOW;
	I2C_DELAY;
}

unsigned char I2c_write_byte(unsigned char data)
{
	int i;

	for(i = 0; i< 8; i++)
	{
		if( (data << i) & 0x80) SDA_HIGH;
		else SDA_LOW;
		I2C_DELAY;
		SCL_HIGH;
		I2C_DELAY;
		SCL_LOW;
		I2C_DELAY;
	}

	if(I2c_ack_detect()!=ERROR_CODE_TRUE) {
		return ERROR_CODE_FALSE;
	}
	return ERROR_CODE_TRUE;
}

unsigned char I2c_read_byte(void)
{
	int i;
	unsigned char data;

	data = 0;
	SDA_IN;
	for(i = 0; i< 8; i++){
		data <<= 1;
		I2C_DELAY;
		SCL_HIGH;
		I2C_DELAY;
		if (SDA_DETECT) data |= 0x01;
		SCL_LOW;
		I2C_DELAY;
	}
	I2c_ack_send();
	return data;
}

unsigned char I2c_write(unsigned char device_addr, unsigned char sub_addr, unsigned char *buff, int ByteNo)
{
	int i;

	I2c_start();
	I2C_DELAY;
	if(I2c_write_byte(device_addr)) {
		I2c_stop();
		return ERROR_CODE_WRITE_ADDR;
	}
	if(I2c_write_byte(sub_addr)) {
		I2c_stop();
		return ERROR_CODE_WRITE_ADDR;
	}
	for(i = 0; i<ByteNo; i++) {
		if(I2c_write_byte(buff[i])) {
			I2c_stop();
			return ERROR_CODE_WRITE_DATA;
		}
	}
	I2C_DELAY;
	I2c_stop();
	I2C_DELAY_LONG;
	return ERROR_CODE_TRUE;
}

unsigned char I2c_read(unsigned char device_addr, unsigned char sub_addr, unsigned char *buff, int ByteNo)
{
	int i;
	I2c_start();
	I2C_DELAY;
	if(I2c_write_byte(device_addr)) {
		I2c_stop();
		DPRINTK("Fail to write device addr\n");
		return ERROR_CODE_READ_ADDR;
	}
	if(I2c_write_byte(sub_addr)) {
		I2c_stop();
		DPRINTK("Fail to write sub addr\n");
		return ERROR_CODE_READ_ADDR;
	}
	I2c_start();
	I2C_DELAY;
	if(I2c_write_byte(device_addr+1)) {
		I2c_stop();
		DPRINTK("Fail to write device addr+1\n");
		return ERROR_CODE_READ_ADDR;
	}
	for(i = 0; i<ByteNo; i++) buff[i] = I2c_read_byte();
	I2C_DELAY;
	I2C_DELAY_LONG;
	I2c_stop();
	I2C_DELAY_LONG;
	return ERROR_CODE_TRUE;
}

int PixI2cWrite(unsigned char device_addr, unsigned char sub_addr, void *ptr_data, unsigned int ui_data_length)
{
	unsigned char uc_return;
	if((uc_return = I2c_write(device_addr, sub_addr, (unsigned char*)ptr_data, ui_data_length))!=ERROR_CODE_TRUE)
	{
		DPRINTK("[Write]error code = %d\n",uc_return);
		return -1;
	}
	return 0;
}

int PixI2cRead(unsigned char device_addr, unsigned char sub_addr, void *ptr_data, unsigned int ui_data_length)
{
	unsigned char uc_return;
	if((uc_return=I2c_read(device_addr, sub_addr, (unsigned char*)ptr_data, ui_data_length))!=ERROR_CODE_TRUE)
	{
		DPRINTK("[Read]error code = %d\n",uc_return);
		return -1;
	}
	return 0;
}

static int PixI2c_Ioctl(struct inode *inode, struct file *fp, unsigned int cmd, unsigned long arg)
{
	PPIX_IIC_DATA ptr_user_data;
	unsigned int ui_data_length;
	unsigned char uc_device_addr;
	unsigned char uc_sub_addr;
	void *ptr_data=NULL;
	int i_return=0;

	switch(cmd)
	{
		case IOCTL_PIX_I2C_INIT:
			InitGPIO();
			break;
		case IOCTL_PIX_I2C_TERMINATE:
			ReleaseGPIO();
			break;
		case IOCTL_PIX_I2C_READ:
			ptr_user_data = (PPIX_IIC_DATA)arg;
			if((i_return=get_user(uc_device_addr, &ptr_user_data->device_addr))<0)
			{
				goto ERROR_IOCTL;
			}
			if((i_return=get_user(uc_sub_addr, &ptr_user_data->sub_addr))<0)
			{
				goto ERROR_IOCTL;
			}
			if((i_return=get_user(ui_data_length, &ptr_user_data->ui_data_length))<0)
			{
				goto ERROR_IOCTL;
			}
			ptr_data = kmalloc(ui_data_length,GFP_KERNEL);
			if((i_return=PixI2cRead(uc_device_addr, uc_sub_addr, ptr_data, ui_data_length))<0)
				goto ERROR_IOCTL;
			if((i_return=copy_to_user((void*)ptr_user_data->ptr_data, ptr_data, ui_data_length))<0)
				goto ERROR_IOCTL;
			break;
		case IOCTL_PIX_I2C_WRITE:
			ptr_user_data = (PPIX_IIC_DATA)arg;
			if((i_return=get_user(uc_device_addr, &ptr_user_data->device_addr))<0)
				goto ERROR_IOCTL;
			if((i_return=get_user(uc_sub_addr, &ptr_user_data->sub_addr))<0)
				goto ERROR_IOCTL;
			if((i_return=get_user(ui_data_length, &ptr_user_data->ui_data_length))<0)
				goto ERROR_IOCTL;
			ptr_data = kmalloc(ui_data_length,GFP_KERNEL);
			if((i_return=copy_from_user(ptr_data, (const void*)ptr_user_data->ptr_data, ui_data_length))<0)
				goto ERROR_IOCTL;
			if((i_return=PixI2cWrite(uc_device_addr, uc_sub_addr, ptr_data, ui_data_length))<0)
				goto ERROR_IOCTL;
			break;
		default:	i_return=-EINVAL; break;
	}
ERROR_IOCTL:
	KERNEL_FREE(ptr_data);
	return i_return;
}

static int PixI2c_Open(struct inode *pInode, struct file *pFile)
{
	int i_return = -ENODEV;
	int iNum= MINOR(pInode->i_rdev);

	if(!atomic_dec_and_test(&scull_available))
	{
		atomic_inc(&scull_available);
		return -EBUSY;
	}
	if(!try_module_get(THIS_MODULE))
	{
		DPRINTK("Failed iic driver for pixtree\n");
		goto OUT;
	}
	i_return = 0;
	DPRINTK("open iic driver for pixtree minor : %d\n",iNum);
OUT:
	return i_return;
}

static int PixI2c_Release(struct inode *inode, struct file *file)
{
	module_put(THIS_MODULE);
	DPRINTK("release iic driver for pixtree\n");
	atomic_inc(&scull_available);
	return 0;
}

static const struct file_operations pix_iic_fops=
{
	.owner    = THIS_MODULE,
	.open     = PixI2c_Open,
	.ioctl    = PixI2c_Ioctl,
	.release	= PixI2c_Release,
};
static struct miscdevice pix_i2c_dev={
	.minor	= PIX_I2C_MINOR,
	.name	= "pix_i2c",
	.fops	= &pix_iic_fops,
};
int __init PixI2c_Init(void)
{
	int nResult;
	nResult = misc_register(&pix_i2c_dev);
	if(nResult)
	{
		DPRINTK("[init PixI2c_Init]fail to regist dev...................!!!!!!!!!!!!!!!!!\n");
		return nResult;
	}
	InitGPIO();

	return 0;
}

void __exit PixI2c_Exit(void)
{
	misc_deregister(&pix_i2c_dev);
}

#ifndef MODULE
__initcall(PixI2c_Init);
#else
module_init(PixI2c_Init);
module_exit(PixI2c_Exit);
#endif

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Pixtree, Inc.");
MODULE_DESCRIPTION("for IIC communication");
