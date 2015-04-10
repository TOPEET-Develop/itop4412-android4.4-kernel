/* linux/drivers/video/samsung/s3cfb_wa101s.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * 101WA01S 10.1" Landscape LCD module driver for the SMDK
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include "s3cfb.h"

static struct s3cfb_lcd wa101 = {
#if 0//smdk
//	.width	= 1366,
	.width	= 1360,
	.height	= 768,
	.bpp	= 24,
	.freq	= 60,

	.timing = {
		.h_fp	= 48,
		.h_bp	= 80,
		.h_sw	= 32,
		.v_fp	= 3,
		.v_fpe	= 0,
		.v_bp	= 14,
		.v_bpe	= 0,
		.v_sw	= 5,
	},

	.polarity = {
		.rise_vclk	= 1,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
#else
//TA4
#if 0  //modify by cym 20121009
	.width	= 1280,
	.height = 800,
#else
/* add by cym 20130417 for TSC2007 TouchScreen */
#ifdef CONFIG_TOUCHSCREEN_TSC2007
	.width	= 800,
	.height = 480,
#else
	.width	= 1024,
	.height = 768,
#endif
#endif
	.bpp	= 24,
	.freq	= 70,//70,

#if 0	//modify by cym 20121019
	.timing = {
		.h_fp	= 30,
		.h_bp	= 30,
		.h_sw	= 9, //100
	
		.v_fp	= 10,
		.v_fpe	= 0,
		.v_bp	= 6,
		.v_bpe	= 0,
		.v_sw	= 7,
	},
#else
	.timing = {
		.h_fp	= 48,
		.h_bp	= 80,
		.h_sw	= 32,
		.v_fp	= 3,
		.v_fpe	= 0,
		.v_bp	= 14,
		.v_bpe	= 0,
		.v_sw	= 5,
	},
#endif

	.polarity = {
		.rise_vclk	= 1,
		.inv_hsync	= 0,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},

#endif
};

extern int get_lcd_type();

void s3cfb_setup_lcd()
{
#if 1
	int type = get_lcd_type();
	//printk("************** type = %d\n", type);
	if(0x0 == type)        //9.7
        {
		//printk("99999999999999999999999999999999\n");
		wa101.width = 1024;
                wa101.height = 768;
                wa101.bpp       = 24;
                wa101.freq = 70;//70;
        }
        else if(0x1 == type)   //7.0
        {
		wa101.width = 800;
                wa101.height = 1280;
                wa101.bpp       = 24;
                wa101.freq = 50;//70;
        }
        else if(0x2 == type)   //4.3
        {
                wa101.width = 480;
                wa101.height = 272;
                wa101.bpp       = 24;
                wa101.freq = 60;

                wa101.timing.h_fp   = 10;//48,
                wa101.timing.h_bp   = 30;//80,
                wa101.timing.h_sw   = 41;//32,

                wa101.timing.v_fp   = 10;//2,//3,
                wa101.timing.v_fpe  = 0;
                wa101.timing.v_bp   = 10;//2,//14,
                wa101.timing.v_bpe  = 0;
                wa101.timing.v_sw   = 10;//5,

                wa101.polarity.rise_vclk      = 0;//1,
                wa101.polarity.inv_hsync      = 0;
                wa101.polarity.inv_vsync      = 0;//1,
                wa101.polarity.inv_vden       = 0;//0,
        }
	else if(0x3 == type)	//1080p
	{
		wa101.width = 1920;
                wa101.height = 1080;
	}
#endif
}

/* name should be fixed as 's3cfb_set_lcd_info' */
void s3cfb_set_lcd_info(struct s3cfb_global *ctrl)
{
	s3cfb_setup_lcd();

	wa101.init_ldi = NULL;
	ctrl->lcd = &wa101;
}

/* add by cym 20140516 */
#if 0
static int __init s3cfb_setup_lcd(char *str)
{
	//int i;

	if (!strncasecmp("9.7", str, 3)) {
		//printk("000000000000000000000000\n");
		wa101.width = 1024;
		wa101.height = 768;
		wa101.bpp	= 24;
		wa101.freq = 70;
	}
	else if(!strncasecmp("7.0", str, 3))
	{
		//printk("1111111111111111111111111\n");
		wa101.width = 800;
		wa101.height = 1280;
		wa101.bpp	= 24;
		wa101.freq = 70;
	}

	printk("%s selected\n", __FUNCTION__);
	return 0;
}

early_param("lcd", s3cfb_setup_lcd);
#endif
/* end add */
