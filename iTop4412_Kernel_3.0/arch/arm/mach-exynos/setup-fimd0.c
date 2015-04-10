/* linux/arch/arm/mach-exynos/setup-fimd0.c
 *
 * Copyright (c) 2009-2011 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com
 *
 * Base Exynos4 FIMD 0 configuration
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fb.h>
#include <linux/gpio.h>
#include <linux/clk.h>

#include <plat/fb.h>
#include <plat/gpio-cfg.h>
#include <plat/clock.h>

#include <mach/regs-clock.h>
#include <mach/map.h>

#include <linux/delay.h>

#ifdef CONFIG_FB_S3C

static void exynos4_fimd0_cfg_gpios(unsigned int base, unsigned int nr,
		unsigned int cfg, s5p_gpio_drvstr_t drvstr)
{
	s3c_gpio_cfgrange_nopull(base, nr, cfg);

	for (; nr > 0; nr--, base++)
		s5p_gpio_set_drvstr(base, drvstr);
}

void exynos4_fimd0_gpio_setup_24bpp(void)
{
	unsigned int reg = 0;
	int err = 0;
	
#if defined(CONFIG_LCD_WA101S) || defined(CONFIG_LCD_LTE480WV)
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF0(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF1(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF2(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF3(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
#elif defined(CONFIG_LCD_AMS369FG06)
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF0(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF1(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF2(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF3(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
#elif defined(CONFIG_LCD_LMS501KF03)
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF0(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF1(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF2(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	exynos4_fimd0_cfg_gpios(EXYNOS4_GPF3(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
#endif
	/*
	 * Set DISPLAY_CONTROL register for Display path selection.
	 *
	 * DISPLAY_CONTROL[1:0]
	 * ---------------------
	 *  00 | MIE
	 *  01 | MDINE
	 *  10 | FIMD : selected
	 *  11 | FIMD
	 */
	reg = __raw_readl(S3C_VA_SYS + 0x0210);
	reg |= (1 << 1);
	__raw_writel(reg, S3C_VA_SYS + 0x0210);

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
#endif

	
}

#endif

int __init exynos4_fimd0_setup_clock(struct device *dev, const char *parent,
					unsigned long clk_rate)
{
#ifndef CONFIG_FB_S3C

	struct clk *clk_parent;
	struct clk *sclk;

	sclk = clk_get(dev, "sclk_fimd");
	if (IS_ERR(sclk))
		return PTR_ERR(sclk);

	clk_parent = clk_get(NULL, parent);
	if (IS_ERR(clk_parent)) {
		clk_put(sclk);
		return PTR_ERR(clk_parent);
	}

	if (clk_set_parent(sclk, clk_parent)) {
		pr_err("Unable to set parent %s of clock %s.\n",
				clk_parent->name, sclk->name);
		clk_put(sclk);
		clk_put(clk_parent);
		return PTR_ERR(sclk);
	}

	if (!clk_rate)
		clk_rate = 134000000UL;

	if (clk_set_rate(sclk, clk_rate)) {
		pr_err("%s rate change failed: %lu\n", sclk->name, clk_rate);
		clk_put(sclk);
		clk_put(clk_parent);
		return PTR_ERR(sclk);
	}

	clk_put(sclk);
	clk_put(clk_parent);

	return 0;
#else

	struct clk *sclk = NULL;
	struct clk *mout_mpll = NULL;
	struct clk *lcd_clk = NULL;

	u32 rate = 0;
	int ret = 0;

	lcd_clk = clk_get(dev, "lcd");
	if (IS_ERR(lcd_clk)) {
		dev_err(dev, "failed to get operation clk for fimd\n");
		goto err_clk0;
	}

	ret = clk_enable(lcd_clk);
	if (ret < 0) {
		dev_err(dev, "failed to clk_enable of lcd clk for fimd\n");
		goto err_clk0;
	}
	clk_put(lcd_clk);

	sclk = clk_get(dev, "sclk_fimd");
	if (IS_ERR(sclk)) {
		dev_err(dev, "failed to get sclk for fimd\n");
		goto err_clk1;
	}

	/*if (soc_is_exynos4210())
		mout_mpll = clk_get(&pdev->dev, "mout_mpll");
	else*/
		mout_mpll = clk_get(dev, "mout_mpll_user");

	if (IS_ERR(mout_mpll)) {
		dev_err(dev, "failed to get mout_mpll for fimd\n");
		goto err_clk2;
	}

	ret = clk_set_parent(sclk, mout_mpll);
	if (ret < 0) {
		dev_err(dev, "failed to clk_set_parent for fimd\n");
		goto err_clk2;
	}

	ret = clk_set_rate(sclk, 800000000);
	if (ret < 0) {
		dev_err(dev, "failed to clk_set_rate of sclk for fimd\n");
		goto err_clk2;
	}
	dev_dbg(dev, "set fimd sclk rate to %d\n", rate);

	clk_put(mout_mpll);

	ret = clk_enable(sclk);
	if (ret < 0) {
		dev_err(dev, "failed to clk_enable of sclk for fimd\n");
		goto err_clk2;
	}

	//*s3cfb_clk = sclk;

	return 0;

err_clk2:
	clk_put(mout_mpll);
err_clk1:
	clk_put(sclk);
err_clk0:
	clk_put(lcd_clk);

	return -EINVAL;



#endif

}


