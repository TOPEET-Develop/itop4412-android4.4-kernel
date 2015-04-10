/* linux/arch/arm/mach-exynos/clock-4212.c
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS4 - 4212 Clock support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifdef CONFIG_PM
static struct sleep_save exynos4_clock_save_4212[] = {
	/* CMU side */
	SAVE_ITEM(S5P_CLKSRC_CAM1),
	SAVE_ITEM(S5P_CLKSRC_ISP),
	SAVE_ITEM(S5P_CLKDIV_CAM1),
	SAVE_ITEM(S5P_CLKDIV_ISP),
	SAVE_ITEM(S5P_CLKSRC_MASK_ISP),
	SAVE_ITEM(S5P_CLKGATE_IP_ISP),
	SAVE_ITEM(S5P_CLKGATE_IP_DMC1),
};

static struct sleep_save exynos4_epll_save_4212[] = {
	SAVE_ITEM(S5P_EPLL_CON2),
};

static struct sleep_save exynos4_vpll_save_4212[] = {
	SAVE_ITEM(S5P_VPLL_CON2),
};
#endif

static struct clksrc_clk clk_mout_mpll_4212 = {
	.clk = {
		.name		= "mout_mpll",
		.id		= -1,
	},
	.sources	= &clk_src_mpll,
	.reg_src	= { .reg = S5P_CLKSRC_DMC, .shift = 12, .size = 1 },
};

static struct clk *clk_src_mpll_user_list[] = {
	[0] = &clk_fin_mpll,
	[1] = &clk_mout_mpll.clk,
};

static struct clksrc_sources clk_src_mpll_user = {
	.sources        = clk_src_mpll_user_list,
	.nr_sources     = ARRAY_SIZE(clk_src_mpll_user_list),
};

static struct clksrc_clk clk_mout_mpll_user = {
	.clk = {
		.name		= "mout_mpll_user",
		.id		= -1,
	},
	.sources	= &clk_src_mpll_user,
	.reg_src	= { .reg = S5P_CLKSRC_CPU, .shift = 24, .size = 1 },
};

static struct clk *clkset_aclk_lrbus_user_list[] = {
	[0] = &clk_fin_mpll,
	[1] = &clk_mout_mpll.clk,
};

static struct clksrc_sources clkset_aclk_lrbus_user = {
	.sources        = clkset_aclk_lrbus_user_list,
	.nr_sources     = ARRAY_SIZE(clkset_aclk_lrbus_user_list),
};

static struct clksrc_clk clk_aclk_gdl_user = {
	.clk    = {
		.name           = "aclk_gdl_user",
		.id             = -1,
	},
	.sources        = &clkset_aclk_lrbus_user,
	.reg_src        = { .reg = S5P_CLKSRC_LEFTBUS, .shift = 4, .size = 1 },
};

static struct clksrc_clk clk_aclk_gdr_user = {
	.clk    = {
		.name           = "aclk_gdr_user",
		.id             = -1,
	},
	.sources        = &clkset_aclk_lrbus_user,
	.reg_src        = { .reg = S5P_CLKSRC_RIGHTBUS, .shift = 4, .size = 1 },
};

static struct clksrc_clk *sysclks_4212[] = {
	&clk_mout_mpll_user,
	&clk_aclk_gdl_user,
	&clk_aclk_gdr_user,
};

static struct clk init_clocks_off_4212[] = {
	{
		.name		= "mipihsi",
		.id		= -1,
		.parent		= &clk_aclk_133.clk,
		.enable		= exynos4_clk_ip_fsys_ctrl,
		.ctrlbit	= (1 << 10),
	},
};

static struct clksrc_clk clksrcs_4212[] = {
	{
		.clk		= {
			.name		= "sclk_mipihsi",
			.id		= -1,
			.enable		= exynos4_clksrc_mask_fsys_ctrl,
			.ctrlbit	= (1 << 24),
		},
		.sources = &clkset_mout_corebus,
		.reg_src = { .reg = S5P_CLKSRC_FSYS, .shift = 24, .size = 1 },
		.reg_div = { .reg = S5P_CLKDIV_FSYS0, .shift = 20, .size = 4 },
	},
};

static void exynos4212_clock_init(void)
{
	int ptr;

	for (ptr = 0; ptr < ARRAY_SIZE(sysclks_4212); ptr++)
		s3c_register_clksrc(sysclks_4212[ptr], 1);

	s3c_register_clksrc(clksrcs_4212, ARRAY_SIZE(clksrcs_4212));

	s3c_register_clocks(init_clocks_off_4212, ARRAY_SIZE(init_clocks_off_4212));
	s3c_disable_clocks(init_clocks_off_4212, ARRAY_SIZE(init_clocks_off_4212));
}
