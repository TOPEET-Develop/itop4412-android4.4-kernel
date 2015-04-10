
/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
*
* File Name          : lsm303dlhc_sysfs.h
* Authors            : MH - C&I BU - Application Team
*		     : Carmine Iascone (carmine.iascone@st.com)
*		     : Matteo Dameno (matteo.dameno@st.com)
* Version            : V 1.0.6
* Date               : 15/11/2010
*
********************************************************************************
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
* THE PRESENT SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES
* OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, FOR THE SOLE
* PURPOSE TO SUPPORT YOUR APPLICATION DEVELOPMENT.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOFTWARE IS SPECIFICALLY DESIGNED FOR EXCLUSIVE USE WITH ST PARTS.
*
*******************************************************************************/
/*******************************************************************************
Version History.

Revision 1-0-6 10/11/2010
	ioclt not supported
	sysfs support

*******************************************************************************/

#ifndef	__LSM303DLHC_H__
#define	__LSM303DLHC_H__

#include	<linux/input.h>

#define SAD0L			0x00
#define SAD0H			0x01
#define LSM303DLHC_ACC_I2C_SADROOT	0x0C
#define LSM303DLHC_ACC_I2C_SAD_L	((LSM303DLHC_ACC_I2C_SADROOT<<1)|SAD0L)
#define LSM303DLHC_ACC_I2C_SAD_H	((LSM303DLHC_ACC_I2C_SADROOT<<1)|SAD0H)
#define	LSM303DLHC_ACC_DEV_NAME		"lsm303dlhc_acc"
#if 0	// shengliang, choose only one addr!
  #define LSM303DLHC_ACC_I2C_ADDR		LSM303DLHC_ACC_I2C_SAD_L
#else
  #define LSM303DLHC_ACC_I2C_ADDR		LSM303DLHC_ACC_I2C_SAD_H
#endif


/************************************************/
/* 	Accelerometer defines section	 	*/
/************************************************/

/* Accelerometer Sensor Full Scale */
#define	LSM303DLHC_ACC_FS_MASK		0x30
#define LSM303DLHC_ACC_G_2G 		0x00
#define LSM303DLHC_ACC_G_4G 		0x10
#define LSM303DLHC_ACC_G_8G 		0x20
#define LSM303DLHC_ACC_G_16G		0x30

/************************************************/
/* 	Magnetometer section defines	 	*/
/************************************************/

#define	LSM303DLHC_MAG_DEV_NAME		"lsm303dlhc_mag"
#define LSM303DLHC_MAG_I2C_ADDR		(0x3C>>1)	// shengliang

/* Magnetometer Sensor Full Scale */
#define LSM303DLHC_H_1_3G		0x20
#define LSM303DLHC_H_1_9G		0x40
#define LSM303DLHC_H_2_5G		0x60
#define LSM303DLHC_H_4_0G		0x80
#define LSM303DLHC_H_4_7G		0xA0
#define LSM303DLHC_H_5_6G		0xC0
#define LSM303DLHC_H_8_1G		0xE0

/* Magnetic Sensor Operating Mode */
#define LSM303DLHC_MAG_NORMAL_MODE	0x00
#define LSM303DLHC_MAG_POS_BIAS		0x01
#define LSM303DLHC_MAG_NEG_BIAS		0x02
#define LSM303DLHC_MAG_CC_MODE		0x00
#define LSM303DLHC_MAG_SC_MODE		0x01
#define LSM303DLHC_MAG_SLEEP_MODE	0x03

#define GM_AXIS_MAP_X 0
#define GM_AXIS_MAP_Y 1
#define GM_AXIS_MAP_Z 2
#define GM_NEGATE_X 0
#define GM_NEGATE_Y 1
#define GM_NEGATE_Z 1

#ifdef	__KERNEL__
struct lsm303dlhc_acc_platform_data {
	int poll_interval;
	int min_interval;

	u8 g_range;

	u8 axis_map_x;
	u8 axis_map_y;
	u8 axis_map_z;

	u8 negate_x;
	u8 negate_y;
	u8 negate_z;

	int (*init)(void);
	void (*exit)(void);
	int (*power_on)(void);
	int (*power_off)(void);

	int gpio_int1;
	int gpio_int2;
};


struct lsm303dlhc_mag_platform_data {

	int poll_interval;
	int min_interval;

	u8 h_range;

	u8 axis_map_x;
	u8 axis_map_y;
	u8 axis_map_z;

	u8 negate_x;
	u8 negate_y;
	u8 negate_z;

	int (*init)(void);
	void (*exit)(void);
	int (*power_on)(void);
	int (*power_off)(void);

};
#endif	/* __KERNEL__ */

#endif	/* __LSM303DLHC_H__ */



