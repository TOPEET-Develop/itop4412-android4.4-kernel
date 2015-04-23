/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 * 
 * MediaTek Inc. (C) 2010. All rights reserved.
 * 
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <mach/io.h>
#include <asm/mach-types.h>
//#include <plat/gpio-cfg.h>

#include "bt_hwctl.h"


/****************************************************************************
 *                           C O N S T A N T S                              *
*****************************************************************************/
#define MODULE_TAG         "[BT-PLAT] "

/* SMDK platform PIN definition */
#define GPIO_BT_PWR_EN_PIN	46
#define GPIO_BT_RESET_PIN	46 //if pwr_en & reset not connect can use this pin
#define GPIO_BT_EINT_PIN	49
//#define GPIO_BT_URXD_PIN ( EXYNOS4_GPA0(0) )  //wenhui: due to panda has configed uart interface
//#define GPIO_BT_UTXD_PIN ( EXYNOS4_GPA0(1) )

//wenhui:should add bt uart cts/rts gpio config
//#define GPIO_BT_HOST_UART_CTS		123


static struct gpio_set bt_gpio_set[2] = {// wenhui modify
    { GPIO_BT_PWR_EN_PIN, 0, "BT_PWR_EN" },
//    { GPIO_BT_RESET_PIN,  0, "BT_RESET"  },
    { GPIO_BT_EINT_PIN,   0, "BT_EINT"   }//,
//    { GPIO_BT_URXD_PIN,   0, "BT_URXD"   },
//    { GPIO_BT_UTXD_PIN,   0, "BT_UTXD"   }
};

static unsigned char irq_requested = 0;//wenhui add 
static int irq_num;
// to avoid irq enable and disable not match
static unsigned int irq_mask;
//static spinlock_t bt_irq_lock;
extern void omap_mux_set_gpio(u16 val, int gpio);
/****************************************************************************
 *                       I R Q   F U N C T I O N S                          *
*****************************************************************************/
static int mt_bt_request_irq(void)
{
    int iRet;
    irq_mask = 0;
    
    iRet = request_irq(irq_num, mt_bt_eirq_handler, 
        IRQF_TRIGGER_HIGH, "BT_INT_B", NULL);
    if (iRet){
        printk(KERN_ALERT MODULE_TAG "request_irq IRQ%d fails, errno %d\n", irq_num, iRet);
    }
    else{
        printk(KERN_INFO MODULE_TAG "request_irq IRQ%d success\n", irq_num);
        mt_bt_disable_irq();
        /* enable irq when driver init complete, at hci_uart_open */
    }
    irq_requested = 1; //wenhui add
    return iRet;
}

static void mt_bt_free_irq(void)
{
    if(irq_requested) {
	free_irq(irq_num, NULL);
	irq_mask = 0;
	irq_requested = 0;
    }
}

void mt_bt_enable_irq(void)
{
    printk(KERN_INFO MODULE_TAG "enable_irq, mask %d\n", irq_mask);
    if (irq_mask){
        irq_mask = 0;
        enable_irq(irq_num);
    }
}
EXPORT_SYMBOL(mt_bt_enable_irq);

void mt_bt_disable_irq(void)
{
    printk(KERN_INFO MODULE_TAG "disable_irq_nosync, mask %d\n", irq_mask);
    if (!irq_mask){
        irq_mask = 1;
        disable_irq_nosync(irq_num);
    }
}
EXPORT_SYMBOL(mt_bt_disable_irq);

/****************************************************************************
 *                      P O W E R   C O N T R O L                           *
*****************************************************************************/
void mt_bt_gpio_init(void)
{
    int i;
    for(i = 0; i < 2; i++){
        if (gpio_request(bt_gpio_set[i].gpio, bt_gpio_set[i].label)){
            /* GPIO pin is already requested, check who is using now */
            printk(KERN_ALERT MODULE_TAG "GPIO%d is busy!\n", bt_gpio_set[i].gpio);
        }
        else{
            printk(KERN_INFO MODULE_TAG "GPIO%d is requested as %s\n", bt_gpio_set[i].gpio, bt_gpio_set[i].label);
            bt_gpio_set[i].requested = 1;
        }
    }
}
EXPORT_SYMBOL(mt_bt_gpio_init);

void mt_bt_gpio_release(void)
{
    int i;
    for(i = 0; i < 2; i++){
        if (bt_gpio_set[i].requested){
            /* GPIO pin is requested by BT, release it */
            gpio_free(bt_gpio_set[i].gpio);
            bt_gpio_set[i].requested = 0;
        }
    }
}
EXPORT_SYMBOL(mt_bt_gpio_release);


int mt_bt_power_on(void)
{
    int error;
    printk(KERN_INFO MODULE_TAG "mt_bt_power_on ++\n");
    
/************************************************************
 *  Make sure BT_PWR_EN is default gpio output low when
 *  system boot up, otherwise MT6622 gets actived unexpectedly 
 ************************************************************/
    
    // URXD, UTXD
//    s3c_gpio_cfgpin(GPIO_BT_URXD_PIN, S3C_GPIO_SFN(0x2));
//    s3c_gpio_cfgpin(GPIO_BT_UTXD_PIN, S3C_GPIO_SFN(0x2));
    
    // PCMIN, PCMOUT, PCMCLK, PCMSYNC
    /* not configured since SMDK4x12 has no modem */
    
    // EINT

    // EINT
    /* set to EINT mode */
    gpio_direction_input(GPIO_BT_EINT_PIN);/////////important
    irq_num = gpio_to_irq(GPIO_BT_EINT_PIN);

    printk("GPIO_BT_PWR_EN_PIN before config(out_h: %d) \n", gpio_get_value(GPIO_BT_PWR_EN_PIN));
// PWR_EN & RESET pull high
    omap_mux_set_gpio(3, GPIO_BT_PWR_EN_PIN);
    gpio_direction_output(GPIO_BT_PWR_EN_PIN, 1);
    printk("GPIO_BT_PWR_EN_PIN after config(out_h: %d) \n", gpio_get_value(GPIO_BT_PWR_EN_PIN));
    msleep(1000);

    // PWR_EN & RESET
    /* PWR_EN pin output high */
//    s3c_gpio_cfgpin(GPIO_BT_PWR_EN_PIN, S3C_GPIO_SFN(0x1));
//    gpio_direction_output(GPIO_BT_PWR_EN_PIN, 1);
    /* RESET pin set to low */
//    s3c_gpio_cfgpin(GPIO_BT_RESET_PIN, S3C_GPIO_SFN(0x1));
//    gpio_direction_output(GPIO_BT_RESET_PIN, 0);
    
//    msleep(15);
    /* RESET pin pull up */
//    gpio_direction_output(GPIO_BT_RESET_PIN, 1);
//    msleep(1000);
    
    error = mt_bt_request_irq();
    if (error){
        /* Clear GPIO configurations */
        gpio_direction_output(GPIO_BT_PWR_EN_PIN, 0);
//        gpio_direction_output(GPIO_BT_RESET_PIN, 0);
//	omap_mux_set_gpio(3, GPIO_BT_EINT_PIN);
	gpio_direction_output(GPIO_BT_EINT_PIN, 0);
//        s3c_gpio_cfgpin(GPIO_BT_EINT_PIN, S3C_GPIO_SFN(0x1));
//        gpio_direction_output(GPIO_BT_EINT_PIN, 0);
//        s3c_gpio_cfgpin(GPIO_BT_URXD_PIN, S3C_GPIO_SFN(0x1));
//        gpio_direction_output(GPIO_BT_URXD_PIN, 0);
//        s3c_gpio_cfgpin(GPIO_BT_UTXD_PIN, S3C_GPIO_SFN(0x1));
//        gpio_direction_output(GPIO_BT_UTXD_PIN, 0);
        return error;
    }
    
    printk(KERN_INFO MODULE_TAG "mt_bt_power_on --\n");
    
    return 0;
}

EXPORT_SYMBOL(mt_bt_power_on);


void mt_bt_power_off(void)
{
    printk(KERN_INFO MODULE_TAG "mt_bt_power_off ++\n");
    
    // PWR_EN and RESET
    gpio_direction_output(GPIO_BT_PWR_EN_PIN, 0);
//    gpio_direction_output(GPIO_BT_RESET_PIN, 0);
    
    // 32k CLK
    // EINT
//    s3c_gpio_cfgpin(GPIO_BT_EINT_PIN, S3C_GPIO_SFN(0x1));
    gpio_direction_output(GPIO_BT_EINT_PIN, 0);
    
    // PCMIN, PCMOUT, PCMCLK, PCMSYNC
    // URXD, UTXD
//    s3c_gpio_cfgpin(GPIO_BT_URXD_PIN, S3C_GPIO_SFN(0x1));
//    gpio_direction_output(GPIO_BT_URXD_PIN, 0);
//    s3c_gpio_cfgpin(GPIO_BT_UTXD_PIN, S3C_GPIO_SFN(0x1));
//    gpio_direction_output(GPIO_BT_UTXD_PIN, 0);
    
    mt_bt_free_irq();
    
    printk(KERN_INFO MODULE_TAG "mt_bt_power_off --\n");
}

EXPORT_SYMBOL(mt_bt_power_off);
