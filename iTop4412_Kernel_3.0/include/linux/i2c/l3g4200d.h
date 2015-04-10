/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
*
* File Name		: l3g4200d.h
* Authors		: MH - C&I BU - Application Team
*			: Carmine Iascone (carmine.iascone@st.com)
*			: Matteo Dameno (matteo.dameno@st.com)
* Version		: V 1.0 sysfs
* Date			: 19/11/2010
* Description		: L3G4200D digital output gyroscope sensor API
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
********************************************************************************
* REVISON HISTORY
*
* VERSION | DATE 	| AUTHORS	     | DESCRIPTION
*
* 1.0	  | 19/11/2010	| Carmine Iascone    | First Release
*
*******************************************************************************/

#ifndef __L3G4200D_H__
#define __L3G4200D_H__

#define L3G4200D_DEV_NAME	"l3g4200d_gyr"
#define L3G4200D_I2C_SADROOT	0x34
#define L3G4200D_I2C_SA0_L	0x00
#define L3G4200D_I2C_SA0_H	0x01
#if 1	// shengliang, choose only one addr!
  #define L3G4200D_I2C_ADDR	((L3G4200D_I2C_SADROOT<<1)|L3G4200D_I2C_SA0_L)
#else
  #define L3G4200D_I2C_ADDR	((L3G4200D_I2C_SADROOT<<1)|L3G4200D_I2C_SA0_H)
#endif

#define L3G4200D_FS_250DPS	0x00
#define L3G4200D_FS_500DPS	0x10
#define L3G4200D_FS_2000DPS	0x30

#define L3G4200D_ENABLED	1
#define L3G4200D_DISABLED	0

#define GYRO_AXIS_MAP_X 1
#define GYRO_AXIS_MAP_Y 0
#define GYRO_AXIS_MAP_Z 2
#define GYRO_NEGATE_X 1
#define GYRO_NEGATE_Y 0
#define GYRO_NEGATE_Z 0

#ifdef __KERNEL__
struct l3g4200d_gyr_platform_data {
	int poll_interval;
	int min_interval;

	u8 fs_range;

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

#endif /* __KERNEL__ */

#endif  /* __L3G4200D_H__ */
