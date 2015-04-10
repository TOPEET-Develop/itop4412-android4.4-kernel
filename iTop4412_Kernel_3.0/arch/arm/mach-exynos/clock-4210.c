/* linux/arch/arm/mach-exynos/clock-4210.c
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS4 - 4210 Clock support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifdef CONFIG_PM
static struct sleep_save exynos4_clock_save_4210[] = {
	/* CMU side */
	SAVE_ITEM(S5P_CLKSRC_IMAGE),
	SAVE_ITEM(S5P_CLKSRC_LCD1),
	SAVE_ITEM(S5P_CLKDIV_IMAGE),
	SAVE_ITEM(S5P_CLKDIV_LCD1),
	SAVE_ITEM(S5P_CLKSRC_MASK_LCD1),
	SAVE_ITEM(S5P_CLKGATE_IP_IMAGE),
	SAVE_ITEM(S5P_CLKGATE_IP_LCD1),
};
#endif

static struct clk init_clocks_off_4210[] = {
	{
		.name		= "sataphy",
		.id		= -1,
		.parent		= &clk_aclk_133.clk,
		.enable		= exynos4_clk_ip_fsys_ctrl,
		.ctrlbit	= (1 << 3),
	}, {
		.name		= "sata",
		.id		= -1,
		.parent		= &clk_aclk_133.clk,
		.enable		= exynos4_clk_ip_fsys_ctrl,
		.ctrlbit	= (1 << 10),
	},
};

static struct clksrc_clk clksrcs_4210[] = {
	{
		.clk		= {
			.name		= "sclk_sata",
			.id		= -1,
			.enable		= exynos4_clksrc_mask_fsys_ctrl,
			.ctrlbit	= (1 << 24),
		},
		.sources = &clkset_mout_corebus,
		.reg_src = { .reg = S5P_CLKSRC_FSYS, .shift = 24, .size = 1 },
		.reg_div = { .reg = S5P_CLKDIV_FSYS0, .shift = 20, .size = 4 },
	},
};

static void exynos4210_clock_init(void)
{
	s3c_register_clksrc(clksrcs_4210, ARRAY_SIZE(clksrcs_4210));

	s3c_register_clocks(init_clocks_off_4210, ARRAY_SIZE(init_clocks_off_4210));
	s3c_disable_clocks(init_clocks_off_4210, ARRAY_SIZE(init_clocks_off_4210));
}
