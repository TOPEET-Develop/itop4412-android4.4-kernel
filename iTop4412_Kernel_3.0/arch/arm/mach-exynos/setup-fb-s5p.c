/* linux/arch/arm/mach-exynos/setup-fb-s5p.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Base FIMD controller configuration
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/io.h>

#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>
#include <mach/map.h>
#include <mach/gpio.h>

#include <plat/clock.h>
#include <plat/gpio-cfg.h>
#include <plat/cpu.h>

struct platform_device; /* don't need the contents */
/* 
 LVDS Power Up Sequence from the SN75LVDS83BZQLR TI's specification

  1. Turn OFF the LVDS using GPE4_3(LVDS_PWDN)
  //2. Fill the frame buffer with block color ;
  3. Tunr ON the PMIC BUCK6(VDD33_LCD)
  4. Wait for 10ms using mDelay()
  5. Turn ON the LCD controller (VIDCON0[1] : ENVID)
  6. Wait for 1ms using mDelay()
  7. Turn ON the LVDS using GPE4_3(LVDS_PWDN)
  8. Wait for 1.2ms using mDelay() or 1200us using uDelay()
  9. Set the VLED_EN(GPE1_5) to the "Output HIGH"
 10. Wait for 10ms using mDelay() or 10000us using uDelay()
 11. Set the LED_PWM(GPD0_1) to the "Output HIGH"
 12. Wait for 10ms using mDelay() or 10000us using uDelay()
 13. Set the LEN_EN18(GPE1_4) to the "Output HIGH"
*/

#ifdef CONFIG_FB_S5P
static void s3cfb_gpio_setup_24bpp(unsigned int start, unsigned int size,
		unsigned int cfg, s5p_gpio_drvstr_t drvstr)
{
	u32 reg;

	s3c_gpio_cfgrange_nopull(start, size, cfg);

	for (; size > 0; size--, start++)
		s5p_gpio_set_drvstr(start, drvstr);

	/* Set FIMD0 bypass */
	reg = __raw_readl(S3C_VA_SYS + 0x0210);
	reg |= (1<<1);
	__raw_writel(reg, S3C_VA_SYS + 0x0210);
}

#if defined(CONFIG_FB_S5P_WA101S) || defined(CONFIG_FB_S5P_LTE480WV)
void s3cfb_cfg_gpio(struct platform_device *pdev)
{
	int err;
	
	/* add by cym 20150120 */
#if 1
	err = gpio_request(EXYNOS4_GPC0(2), "VGA_EN");
        if (err) {
                printk(KERN_ERR "failed to request VGA_EN\n");
                return err;
        }

        gpio_direction_output(EXYNOS4_GPC0(2), 0);

        s3c_gpio_cfgpin(EXYNOS4_GPC0(2), S3C_GPIO_OUTPUT);
        gpio_free(EXYNOS4_GPC0(2));
	msleep(250);

        err = gpio_request(EXYNOS4_GPL0(4), "BK_VDD_EN");
        if (err) {
                printk(KERN_ERR "failed to request BK_VDD_EN\n");
                //return err;
        }

        gpio_direction_output(EXYNOS4_GPL0(4), 1);
        s3c_gpio_cfgpin(EXYNOS4_GPL0(4), S3C_GPIO_OUTPUT);
        gpio_free(EXYNOS4_GPL0(4));

        printk("(%s, %d): BK_VDD_ON\n", __FUNCTION__, __LINE__);
	msleep(100);
#endif
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF0(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF1(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF2(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF3(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
#if 1	// TC4
	//LVDS_PWDN
	err = gpio_request(EXYNOS4_GPL1(0), "GPL1_0");
	if (err) {
		printk(KERN_ERR "failed to request GPL1 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPL1(0), 1);

	s3c_gpio_cfgpin(EXYNOS4_GPL1(0), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPL1(0));

	printk("(%s, %d): LCD_PWDN ON\n", __FUNCTION__, __LINE__);
#endif
}
#elif defined(CONFIG_FB_S5P_AMS369FG06)
void s3cfb_cfg_gpio(struct platform_device *pdev)
{
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF0(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF1(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF2(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF3(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
}
#elif defined(CONFIG_FB_S5P_LMS501KF03)
void s3cfb_cfg_gpio(struct platform_device *pdev)
{
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF0(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF1(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF2(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF3(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
}
#elif defined(CONFIG_FB_S5P_HT101HD1)
void s3cfb_cfg_gpio(struct platform_device *pdev)
{
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF0(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF1(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF2(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	s3cfb_gpio_setup_24bpp(EXYNOS4_GPF3(0), 6, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
}
#endif
#endif

int s3cfb_clk_on(struct platform_device *pdev, struct clk **s3cfb_clk)
{
	struct clk *sclk = NULL;
	struct clk *mout_mpll = NULL;
	struct clk *lcd_clk = NULL;

	u32 rate = 0;
	int ret = 0;

	lcd_clk = clk_get(&pdev->dev, "lcd");
	if (IS_ERR(lcd_clk)) {
		dev_err(&pdev->dev, "failed to get operation clk for fimd\n");
		goto err_clk0;
	}

	ret = clk_enable(lcd_clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to clk_enable of lcd clk for fimd\n");
		goto err_clk0;
	}
	clk_put(lcd_clk);

	sclk = clk_get(&pdev->dev, "sclk_fimd");
	if (IS_ERR(sclk)) {
		dev_err(&pdev->dev, "failed to get sclk for fimd\n");
		goto err_clk1;
	}

	if (soc_is_exynos4210())
		mout_mpll = clk_get(&pdev->dev, "mout_mpll");
	else
		mout_mpll = clk_get(&pdev->dev, "mout_mpll_user");

	if (IS_ERR(mout_mpll)) {
		dev_err(&pdev->dev, "failed to get mout_mpll for fimd\n");
		goto err_clk2;
	}

	ret = clk_set_parent(sclk, mout_mpll);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to clk_set_parent for fimd\n");
		goto err_clk2;
	}

	ret = clk_set_rate(sclk, 800000000);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to clk_set_rate of sclk for fimd\n");
		goto err_clk2;
	}
	dev_dbg(&pdev->dev, "set fimd sclk rate to %d\n", rate);

	clk_put(mout_mpll);

	ret = clk_enable(sclk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to clk_enable of sclk for fimd\n");
		goto err_clk2;
	}

	*s3cfb_clk = sclk;

	return 0;

err_clk2:
	clk_put(mout_mpll);
err_clk1:
	clk_put(sclk);
err_clk0:
	clk_put(lcd_clk);

	return -EINVAL;
}

int s3cfb_clk_off(struct platform_device *pdev, struct clk **clk)
{
	struct clk *lcd_clk = NULL;

	lcd_clk = clk_get(&pdev->dev, "lcd");
	if (IS_ERR(lcd_clk)) {
		printk(KERN_ERR "failed to get ip clk for fimd0\n");
		goto err_clk0;
	}

	clk_disable(lcd_clk);
	clk_put(lcd_clk);

	clk_disable(*clk);
	clk_put(*clk);

	*clk = NULL;

	return 0;

err_clk0:
	clk_put(lcd_clk);

	return -EINVAL;
}

void s3cfb_get_clk_name(char *clk_name)
{
	strcpy(clk_name, "sclk_fimd");
}

#define EXYNOS4_GPD_0_0_TOUT_0  (0x2)
#define EXYNOS4_GPD_0_1_TOUT_1  (0x2 << 4)
#define EXYNOS4_GPD_0_2_TOUT_2  (0x2 << 8)
#define EXYNOS4_GPD_0_3_TOUT_3  (0x2 << 12)

#if defined(CONFIG_FB_S5P_WA101S)
int s3cfb_backlight_on(struct platform_device *pdev)
{
	int err;

#if 0	
	//VLED_EN
	err = gpio_request(EXYNOS4_GPC1(2), "GPC1_2");
	if (err) {
		printk(KERN_ERR "failed to request GPC1_2 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPC1(2), 1);

	s3c_gpio_cfgpin(EXYNOS4_GPC1(2), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPC1(2));

	mdelay(5);
	printk("(%s, %d): BK_LCD_EN\n", __FUNCTION__, __LINE__);
#endif
	/*modify by cym 20121017 */
#if 0
	//VLED_ON
	err = gpio_request(EXYNOS4_GPC0(1), "GPC0_1");
	if (err) {
		printk(KERN_ERR "failed to request GPC0_1 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPC0(1), 1);

	s3c_gpio_cfgpin(EXYNOS4_GPC0(1), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPC0(1));

	mdelay(5);
	//err = gpio_request(EXYNOS4_GPD0(1), "GPD0_1");
	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
		//return err;
	}
#if !defined(CONFIG_BACKLIGHT_PWM)
	gpio_direction_output(EXYNOS4_GPD0(1), 1);
	gpio_free(EXYNOS4_GPD0(1));
#else

	gpio_direction_output(EXYNOS4_GPD0(1), 0);

	s3c_gpio_cfgpin(EXYNOS4_GPD0(1), EXYNOS4_GPD_0_1_TOUT_1);

	//gpio_free(EXYNOS4_GPD0(1));
#endif
	mdelay(5);
	//LED_EN18
	err = gpio_request(EXYNOS4_GPC1(1), "GPC1_1");
	if (err) {
		printk(KERN_ERR "failed to request GPC1_1 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPC1(1), 1);

	s3c_gpio_cfgpin(EXYNOS4_GPC1(1), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPC1(1));
	mdelay(5);
#else
	//VLED_ON
#if 0
	err = gpio_request(EXYNOS4_GPC0(1), "GPC0_1");
	if (err) {
		printk(KERN_ERR "failed to request GPC0_1 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPC0(1), 1);

	s3c_gpio_cfgpin(EXYNOS4_GPC0(1), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPC0(1));
	printk("(%s, %d): VLED_ON\n", __FUNCTION__, __LINE__);
#endif	
	//mdelay(5);
        
	mdelay(250);
	//PWM
	err = gpio_request(EXYNOS4_GPD0(1), "GPD0_1");
	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
		//return err;
	}
#if !defined(CONFIG_BACKLIGHT_PWM)
	gpio_direction_output(EXYNOS4_GPD0(1), 1);
	gpio_free(EXYNOS4_GPD0(1));
#else
/* modify by cym 20130417 for TSC2007 TouchScreen */
//#ifdef CONFIG_TOUCHSCREEN_TSC2007
//	gpio_direction_output(EXYNOS4_GPD0(1), 0);
//#else
	gpio_direction_output(EXYNOS4_GPD0(1), 0);

	s3c_gpio_cfgpin(EXYNOS4_GPD0(1), EXYNOS4_GPD_0_1_TOUT_1);

	gpio_free(EXYNOS4_GPD0(1));
	printk("(%s, %d): LCD_PWM_ON\n", __FUNCTION__, __LINE__);
//#endif
/* end modify */
#endif
	mdelay(5);
#if 0
	//TP1_EN
	err = gpio_request(EXYNOS4_GPL0(2), "TP1_EN");
	if (err) {
		printk(KERN_ERR "failed to request TP1_EN for "
			"I2C control\n");
		return err;
	}
	//because in uboot we enable,we want to enable it again we must disable it    20121109
	//gpio_direction_output(EXYNOS4_GPL0(2), 0); 20130508
	//mdelay(100);
	gpio_direction_output(EXYNOS4_GPL0(2), 1);

	s3c_gpio_cfgpin(EXYNOS4_GPL0(2), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPL0(2));

	printk("(%s, %d): TP1_EN_ON\n", __FUNCTION__, __LINE__);
	mdelay(5);
#endif
#endif
#if 1
	err = gpio_request_one(EXYNOS4_GPC0(2), 0, "GPC0_2");
        if (err) {
                printk(KERN_ERR "failed to request GPC0_2 for "
                                "4.3 LCD control\n");
                return err;
        }

        s3c_gpio_setpull(EXYNOS4_GPC0(2), S3C_GPIO_PULL_UP);
        //gpio_set_value(EXYNOS4_GPC0(2), 0);

        //mdelay(10);

        gpio_set_value(EXYNOS4_GPC0(2), 1);

        gpio_free(EXYNOS4_GPC0(2));
#endif		
#if 0
	err = gpio_request_one(EXYNOS4_GPL1(1), 0, "GPL1_1");
        if (err) {
                printk(KERN_ERR "failed to request GPL1_1 for "
                                "4.3 LCD control\n");
                return err;
        }

        s3c_gpio_setpull(EXYNOS4_GPL1(1), S3C_GPIO_PULL_UP);
        gpio_set_value(EXYNOS4_GPL1(1), 0);

        gpio_free(EXYNOS4_GPL1(1));
#endif
	/*end modify */

	/* add by cym 20141125 */
	err = gpio_request(EXYNOS4_GPC0(2), "VGA_EN");
        if (err) {
                printk(KERN_ERR "failed to request VGA_EN\n");
                return err;
        }

	gpio_direction_output(EXYNOS4_GPC0(2), 1);

	s3c_gpio_cfgpin(EXYNOS4_GPC0(2), S3C_GPIO_OUTPUT);
        gpio_free(EXYNOS4_GPC0(2));

	printk("(%s, %d): VGA_EN_ON\n", __FUNCTION__, __LINE__);
	/* end add */

	return 0;
}

int s3cfb_backlight_off(struct platform_device *pdev)
{

	int err;

	//err = gpio_request(EXYNOS4_GPD0(1), "GPD0");
	//if (err) {
	//	printk(KERN_ERR "failed to request GPD0 for "
	//		"lcd backlight control\n");
	//	return err;
	//}
	/* modify by cym 20121017 */
#if 0
	gpio_direction_output(EXYNOS4_GPD0(1), 0);
	//gpio_free(EXYNOS4_GPD0(1));

		//LED_EN18
	err = gpio_request(EXYNOS4_GPC1(1), "GPC1_1");
	if (err) {
		printk(KERN_ERR "failed to request GPC1_1 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPC1(1), 0);

	s3c_gpio_cfgpin(EXYNOS4_GPC1(1), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPC1(1));

	//VLED_EN
	err = gpio_request(EXYNOS4_GPC1(2), "GPC1_2");
	if (err) {
		printk(KERN_ERR "failed to request GPC1_2 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPC1(2), 0);

	s3c_gpio_cfgpin(EXYNOS4_GPC1(2), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPC1(2));
	//VLED_ON
	err = gpio_request(EXYNOS4_GPC0(1), "GPC0_1");
	if (err) {
		printk(KERN_ERR "failed to request GPC0_1 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPC0(1), 0);

	s3c_gpio_cfgpin(EXYNOS4_GPC0(1), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPC0(1));
#else
	//gpio_direction_output(EXYNOS4_GPD0(1), 0);
	//gpio_free(EXYNOS4_GPD0(1));
	//printk("(%s, %d): LCD_PWM_OFF\n", __FUNCTION__, __LINE__);
#if 0	
	//TP1_EN
	err = gpio_request(EXYNOS4_GPL0(2), "TP1_EN");
	if (err) {
		printk(KERN_ERR "failed to request TP1_EN for "
			"I2C control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPL0(2), 0);

	s3c_gpio_cfgpin(EXYNOS4_GPL0(2), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPL0(2));

	mdelay(5);
	printk("(%s, %d): TP1_EN_OFF\n", __FUNCTION__, __LINE__);
#endif
	//VLED_ON
#if 0
	err = gpio_request(EXYNOS4_GPC0(1), "GPC0_1");
	if (err) {
		printk(KERN_ERR "failed to request GPC0_1 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPC0(1), 0);

	s3c_gpio_cfgpin(EXYNOS4_GPC0(1), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPC0(1));
	printk("(%s, %d): VLED_OFF\n", __FUNCTION__, __LINE__);
#endif
#endif
	/* end modify */

	/* add by cym 20150120 */
#if 1
        err = gpio_request(EXYNOS4_GPD0(1), "GPD0_1");
        if (err) {
                printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
                //return err;
        }

        gpio_direction_output(EXYNOS4_GPD0(1), 0);
        s3c_gpio_cfgpin(EXYNOS4_GPD0(1), S3C_GPIO_OUTPUT);
        gpio_free(EXYNOS4_GPD0(1));

        printk("(%s, %d): LCD_PWM_OFF\n", __FUNCTION__, __LINE__);
#endif
	
	//LVDS_PWDN
	err = gpio_request(EXYNOS4_GPL1(0), "GPL1_0");
	if (err) {
		printk(KERN_ERR "failed to request GPL1 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPL1(0), 0);

	s3c_gpio_cfgpin(EXYNOS4_GPL1(0), S3C_GPIO_OUTPUT);
	gpio_free(EXYNOS4_GPL1(0));

#if 0
        err = gpio_request_one(EXYNOS4_GPL1(1), 0, "GPL1_1");
        if (err) {
                printk(KERN_ERR "failed to request GPL1_1 for "
                                "4.3 LCD control\n");
                return err;
        }

        s3c_gpio_setpull(EXYNOS4_GPL1(1), S3C_GPIO_PULL_UP);
        gpio_set_value(EXYNOS4_GPL1(1), 1);

        gpio_free(EXYNOS4_GPL1(1));
#endif

	/* add by cym 20141125 */
        err = gpio_request(EXYNOS4_GPC0(2), "VGA_EN");
        if (err) {
                printk(KERN_ERR "failed to request VGA_EN\n");
                      
                return err;
        }

        gpio_direction_output(EXYNOS4_GPC0(2), 0);

        s3c_gpio_cfgpin(EXYNOS4_GPC0(2), S3C_GPIO_OUTPUT);
        gpio_free(EXYNOS4_GPC0(2));

        printk("(%s, %d): VGA_EN_OFF\n", __FUNCTION__, __LINE__);
        /* end add */

	/* add by cym 20150120 */
        err = gpio_request(EXYNOS4_GPL0(4), "BK_VDD_EN");
        if (err) {
                printk(KERN_ERR "failed to request BK_VDD_EN for\n");
                return err;
        }

        gpio_direction_output(EXYNOS4_GPL0(4), 0);

        s3c_gpio_cfgpin(EXYNOS4_GPL0(4), S3C_GPIO_OUTPUT);
        gpio_free(EXYNOS4_GPL0(4));

        printk("(%s, %d): BK_VDD_OFF\n", __FUNCTION__, __LINE__);
        /* end add */

	return 0;
}

int s3cfb_lcd_on(struct platform_device *pdev)
{
	return 0;
}

int s3cfb_lcd_off(struct platform_device *pdev)
{
	return 0;
}

#elif defined(CONFIG_FB_S5P_LTE480WV)
int s3cfb_backlight_on(struct platform_device *pdev)
{
#if !defined(CONFIG_BACKLIGHT_PWM)
	int err;

	err = gpio_request_one(EXYNOS4_GPD0(1), GPIOF_OUT_INIT_HIGH, "GPD0");
	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
		return err;
	}
	gpio_free(EXYNOS4_GPD0(1));
#endif
	return 0;
}

int s3cfb_backlight_off(struct platform_device *pdev)
{
#if !defined(CONFIG_BACKLIGHT_PWM)
	int err;

	err = gpio_request_one(EXYNOS4_GPD0(1), GPIOF_OUT_INIT_LOW, "GPD0");
	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
		return err;
	}
	gpio_free(EXYNOS4_GPD0(1));
#endif
	return 0;
}

int s3cfb_lcd_on(struct platform_device *pdev)
{
	int err;
#if 0
	err = gpio_request_one(EXYNOS4_GPX0(6), GPIOF_OUT_INIT_HIGH, "GPX0");
	if (err) {
		printk(KERN_ERR "failed to request GPX0 for "
			"lcd reset control\n");
		return err;
	}
	msleep(100);

	gpio_set_value(EXYNOS4_GPX0(6), 0);
	msleep(10);

	gpio_set_value(EXYNOS4_GPX0(6), 1);
	msleep(10);

	gpio_free(EXYNOS4_GPX0(6));
#endif
	return 0;
}

int s3cfb_lcd_off(struct platform_device *pdev)
{
	return 0;
}
#elif defined(CONFIG_FB_S5P_HT101HD1)
int s3cfb_backlight_on(struct platform_device *pdev)
{
#if !defined(CONFIG_BACKLIGHT_PWM)
	int err;

	/* Backlight High */
	err = gpio_request_one(EXYNOS4_GPD0(0), GPIOF_OUT_INIT_HIGH, "GPD0");
	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
		return err;
	}
	gpio_free(EXYNOS4_GPD0(0));

	/* LED_EN (SPI1_MOSI) High */
	err = gpio_request_one(EXYNOS4_GPB(2), GPIOF_OUT_INIT_HIGH, "GPB");
	if (err) {
		printk(KERN_ERR "failed to request GPB for "
			"lcd LED_EN control\n");
		return err;
	}
	gpio_free(EXYNOS4_GPB(2));
#endif
	return 0;
}

int s3cfb_backlight_off(struct platform_device *pdev)
{
#if !defined(CONFIG_BACKLIGHT_PWM)
	int err;

	/* Backlight Low */
	err = gpio_request_one(EXYNOS4_GPD0(0), GPIOF_OUT_INIT_LOW, "GPD0");
	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
		return err;
	}
	gpio_free(EXYNOS4_GPD0(0));

	/* LED_EN (SPI1_MOSI) Low */
	err = gpio_request_one(EXYNOS4_GPB(2), GPIOF_OUT_INIT_LOW, "GPB");
	if (err) {
		printk(KERN_ERR "failed to request GPB for "
			"lcd LED_EN control\n");
		return err;
	}
	gpio_free(EXYNOS4_GPB(2));
#endif
	return 0;
}

int s3cfb_lcd_on(struct platform_device *pdev)
{
	int err;

	err = gpio_request_one(EXYNOS4_GPH0(1), GPIOF_OUT_INIT_HIGH, "GPH0");
	if (err) {
		printk(KERN_ERR "failed to request GPH0 for "
			"lcd reset control\n");
		return err;
	}

	gpio_set_value(EXYNOS4_GPH0(1), 0);
	gpio_set_value(EXYNOS4_GPH0(1), 1);

	gpio_free(EXYNOS4_GPH0(1));

	return 0;
}

int s3cfb_lcd_off(struct platform_device *pdev)
{
	return 0;
}
#elif defined(CONFIG_FB_S5P_AMS369FG06) || defined(CONFIG_FB_S5P_LMS501KF03)
int s3cfb_backlight_on(struct platform_device *pdev)
{
#if !defined(CONFIG_BACKLIGHT_PWM)
	int err;

	err = gpio_request_one(EXYNOS4_GPD0(1), GPIOF_OUT_INIT_HIGH, "GPD0");
	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
		return err;
	}
	gpio_free(EXYNOS4_GPD0(1));
#endif
	return 0;
}

int s3cfb_backlight_off(struct platform_device *pdev)
{
#if !defined(CONFIG_BACKLIGHT_PWM)
	int err;

	err = gpio_request_one(EXYNOS4_GPD0(1), GPIOF_OUT_INIT_LOW, "GPD0");
	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
		return err;
	}
	gpio_free(EXYNOS4_GPD0(1));
#endif
	return 0;
}

int s3cfb_lcd_on(struct platform_device *pdev)
{
	int err;

#ifdef CONFIG_MACH_SMDKC210
	err = gpio_request_one(EXYNOS4_GPX0(6), GPIOF_OUT_INIT_HIGH, "GPX0");
	if (err) {
		printk(KERN_ERR "failed to request GPX0 for "
			"lcd reset control\n");
		return err;
	}

	gpio_set_value(EXYNOS4_GPX0(6), 0);
	mdelay(1);

	gpio_set_value(EXYNOS4_GPX0(6), 1);

	gpio_free(EXYNOS4_GPX0(6));
#elif defined (CONFIG_MACH_SMDK4X12)
#if 0
	err = gpio_request_one(EXYNOS4_GPX1(5), GPIOF_OUT_INIT_HIGH, "GPX0");
	if (err) {
		printk(KERN_ERR "failed to request GPX0 for "
			"lcd reset control\n");
		return err;
	}

	gpio_set_value(EXYNOS4_GPX1(5), 0);
	mdelay(1);

	gpio_set_value(EXYNOS4_GPX1(5), 1);

	gpio_free(EXYNOS4_GPX1(5));
#endif
#endif

	return 0;
}

int s3cfb_lcd_off(struct platform_device *pdev)
{
	return 0;
}

#else
void s3cfb_cfg_gpio(struct platform_device *pdev)
{
	return;
}
int s3cfb_backlight_on(struct platform_device *pdev)
{
	return 0;
}

int s3cfb_backlight_off(struct platform_device *pdev)
{
	return 0;
}

int s3cfb_lcd_on(struct platform_device *pdev)
{
	return 0;
}

int s3cfb_lcd_off(struct platform_device *pdev)
{
	return 0;
}
#endif
