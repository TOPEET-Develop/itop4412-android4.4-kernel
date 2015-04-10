/*
 * wm8310.h  --  pmic driver for wm8310 @s5p6442 
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 */

#ifndef _MAX8997_H_
#define _MAX8997_H_

#define BUCK_MASK (1<<0)
#define BUCK_ON (1<<0)
#define BUCK_OFF (0<<0)
#define BUCK_DVS_ON (0x1<<1)
#define BUCK_DVS_OFF (0x0<<1)

#define MAX8997_BUCK1_CTRL  (0x18) 
#define MAX8997_BUCK1_DVS	(0x19)


#define MAX8997_BUCK2_CTRL  (0x21) 
#define MAX8997_BUCK2_DVS	(0x22)


#define MAX8997_BUCK3_CTRL  (0x2a) 
#define MAX8997_BUCK3_DVS	(0x2b)




#define MAX8997_BUCK4_CTRL  (0x2c) 
#define MAX8997_BUCK4_DVS	(0x2d)

#define MAX8997_BUCK5_CTRL  (0x2e) 
#define MAX8997_BUCK5_DVS	(0x2f)

#define MAX8997_BUCK6_CTRL  (0x37) 

#define MAX8997_BUCK7_CTRL  (0x39) 

#define LDO_MASK (0x3<<6)

#define LDO_ON (0x3<<6)
#define LDO_OFF (0x0<<6)

//LDO control
/*
LDO 1: 3.3V
Bit[7:6]
Enable Mode Control.
00: Output OFF (regardless of PWREN)
01: Output ON/OFF controlled by PWREN
PWREN=1: Output ON in normal mode
PWREN=0: Output OFF
10: Output On with Green Mode by PWREN
[ PWREN=1 : Output On with Normal Mode ]
[ PWREN=0: Output On with Low Power Mode ]
11: Output ON with Normal Mode (regardless of PWREN)
*/
#define MAX8997_LDO1_CTRL (0x3b) 

/*
LDO 2: 1.1V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO2_CTRL (0x3c) 
/*
LDO 3: 1.1V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO3_CTRL (0x3d) 

/*
LDO 4: 1.8V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO4_CTRL (0x3e) 
/*
LDO 5: 1.2V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO5_CTRL (0x3f) 

/*
LDO 6: 1.8V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO6_CTRL (0x40) 
/*
LDO 7: 1.8V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO7_CTRL (0x41) 
/*
LDO 8: 3.3V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO8_CTRL (0x42) 

/*
LDO 9: 2.8V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO9_CTRL (0x43) 

/*
LDO 10: 1.1V
Enable Mode Control.
00: Output OFF (regardless of PWREN)
01: Output ON/OFF controlled by PWREN
PWREN=1: Output ON in normal mode
PWREN=0: Output OFF
10: Output On with Green Mode by PWREN
[ PWREN=1 : Output On with Normal Mode ]
[ PWREN=0: Output On with Green Mode ]
11: Output ON with Normal Mode (regardless of PWREN)


*/
#define MAX8997_LDO10_CTRL (0x44) 

/*
@@@default is off
LDO 11: 2.8V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO11_CTRL (0x45) 
/*
@@@default is off
LDO 12: 1.2V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO12_CTRL (0x46) 

/*
@@@default is off
LDO 13: 2.8V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO13_CTRL (0x47) 

/*
@@@default is off
LDO 14: 1.8V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO14_CTRL (0x48) 
/*
@@@default is off
LDO 15: 2.8V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO15_CTRL (0x49) 
/*
@@@default is off
LDO 16: 3.3V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO16_CTRL (0x4a) 
/*
@@@default is off
LDO 17: 3.3V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO17_CTRL (0x4b) 
/*
@@@default is off
LDO 18: 3.3V
Enable Mode Control
00: Output off
01: Output On with Green Mode
10: Output On
with Green Mode if PWREN=0.
with Normal Mode if PWREN=1.
11: Output On with Normal Mode

*/
#define MAX8997_LDO18_CTRL (0x4c) 
/*
LDO 21: 1.2V

Enable Mode Control.
00: Output OFF (regardless of PWREN)
01: Output ON/OFF controlled by PWREN
PWREN=1: Output ON in normal mode
PWREN=0: Output OFF
10: Output On with Green Mode by PWREN
[ PWREN=1 : Output On with Normal Mode ]
[ PWREN=0: Output On with Green Mode ]
11: Output ON with Normal Mode (regardless of PWREN)
*/
#define MAX8997_LDO21_CTRL (0x4d) 

#define MAX8997_BOOST_CNTL (0x67)

#define BOOST_EN (1<<6)
#define BOOST_MASK (1<<6)

#define POWERON 1
#define POWEROFF 0

typedef enum {   
#if 0  //yulu ta4
	PMIC_CONTROL_VDDARM = 0x00,
    PMIC_CONTROL_VDDINT, // 0x01
    PMIC_CONTROL_VDDG3D, // 0x02
    PMIC_CONTROL_VDD_ISP11,// 0x03,BUCK4
    PMIC_CONTROL_VDD_M12,// 0x04
    PMIC_CONTROL_VDD_LCD,// 0x05,BUCK 6
    PMIC_CONTROL_VDD_BUCK7,// 0x06,BUCK 7
    PMIC_CONTROL_VDD33_ABB,// 0x07,LDO 1
    PMIC_CONTROL_VDD_ALIVE,// 0x08,LDO 2
    PMIC_CONTROL_VDD11_USH,// 0x09,LDO 3
    PMIC_CONTROL_VDDIO2_18,// 0x0a,LDO 4
    PMIC_CONTROL_VDDIO1_18,// 0x0b,LDO 6,
    PMIC_CONTROL_VDDIO3_18,//0xc,LDO 7,
    PMIC_CONTROL_VDD33_USH,//0xd,LDO 8
    PMIC_CONTROL_VDD_TF,//0xe,LDO 9
    PMIC_CONTROL_VDD_PLL,//0xf,LDO 10

	PMIC_CONTROL_VDD18_A31,//0x10,LDO 11
    PMIC_CONTROL_VDD11_MIPI,//0x11,LDO 12
    PMIC_CONTROL_VDD18_ISP,//0x12,LDO 13
    PMIC_CONTROL_VDD18_CAM,//0x13,LDO 14
    PMIC_CONTROL_VDD28_CAM,//0x14,LDO 15
    PMIC_CONTROL_VDD28_AF,//0x15,LDO 16
    PMIC_CONTROL_VDD33_A31,//0x16,LDO 17
    PMIC_CONTROL_VDD18_MIPI,//0x17,LDO 18
    
    PMIC_CONTROL_VDDQ_M12,//0x18,LDO 21
    PMIC_CONTROL_VDD50, // 0X19, boost_cntrl
    
	/* TODO */
#else
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
    
	/* TODO */

#endif
    
}PMIC_FUN_TYPE;


#ifndef _IO
# define _IO(x,y)	(((x)<<8)|y)
#endif



typedef enum {
	PM_STATE_BOOT = -1,
	PM_STATE_OFF = 0,
	PM_STATE_ON =1,
}PM_STATE;


/*For APP use*/
#define PM_MAGIC_IOC  'P'
#define PM_DEVICE_POST_INIT	(0x20)


#define PM_IOC_VDD18_A31              	_IO(PM_MAGIC_IOC, PMIC_CONTROL_VDD18_A31)
#define PM_IOC_VDD33_A31             _IO(PM_MAGIC_IOC, PMIC_CONTROL_VDD33_A31)




/*******************************************************************************
* STRUCTURES
*******************************************************************************/

/*******************************************************************************
* UNIONS
*******************************************************************************/

/*******************************************************************************
* EXTERNALS
*******************************************************************************/

/*******************************************************************************
* MACRO FUNCTIONS
*******************************************************************************/

/*******************************************************************************
* FUNCTION PROTOTYPES
*******************************************************************************/
extern int PMIC_Control_Set(PMIC_FUN_TYPE type, int val);



#endif
