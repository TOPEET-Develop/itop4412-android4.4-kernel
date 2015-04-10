/*
 * Copyright (c) 2011 PIXTREE, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable PIXTREE license agreement.
 */ 
 
#ifndef __HPI_DRV_H__20080501
#define __HPI_DRV_H__20080501

#ifdef __cplusplus
#define EXTERN extern "C"
#else 
#define EXTERN extern
#endif

//#define DEBUG_MESG
#ifdef DEBUG_MESG
#define DPRINTK(fmt, args...) printk(KERN_INFO "%s: " fmt, __FUNCTION__ , ## args)
#else
#define DPRINTK(fmt, args...)
#endif

#define KERNEL_FREE(X)	if(X){kfree(X);X=NULL;}

typedef struct _PIX_IIC_DATA
{
	unsigned char device_addr;
	unsigned char sub_addr;
	unsigned char *ptr_data;
	unsigned int ui_data_length;
}__attribute__((packed)) PIX_IIC_DATA, *PPIX_IIC_DATA;

#define ERROR_CODE_TRUE			0
#define ERROR_CODE_FALSE		1
#define ERROR_CODE_WRITE_ADDR	10
#define ERROR_CODE_WRITE_DATA	20
#define ERROR_CODE_READ_ADDR	30
#define ERROR_CODE_READ_DATA	40
#define ERROR_CODE_START_BIT	50
#define ERROR_CODE_APROCESS		60
#define ERROR_CODE_DENY			70


#define IOCTL_I2C_SEED            'b'
#define IOCTL_PIX_I2C_INIT					_IO(IOCTL_I2C_SEED,	0)
#define IOCTL_PIX_I2C_TERMINATE				_IO(IOCTL_I2C_SEED,	1)
#define IOCTL_PIX_I2C_READ					_IOWR(IOCTL_I2C_SEED,	2, PIX_IIC_DATA)
#define IOCTL_PIX_I2C_WRITE					_IOWR(IOCTL_I2C_SEED,	3, PIX_IIC_DATA)
#endif
