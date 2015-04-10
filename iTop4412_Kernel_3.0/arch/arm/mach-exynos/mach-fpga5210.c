/* linux/arch/arm/mach-exynos/mach-fpga5210.c
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/platform_device.h>
#include <linux/serial_core.h>
#include <linux/fb.h>
#if defined(CONFIG_S5P_MEM_CMA)
#include <linux/cma.h>
#endif

#include <asm/mach/arch.h>
#include <asm/mach-types.h>

#include <plat/regs-serial.h>
#include <plat/regs-fb-v4.h>
#include <plat/exynos5.h>
#include <plat/cpu.h>
#include <plat/clock.h>
#include <plat/devs.h>
#include <plat/fb.h>
#include <plat/dp.h>
#if defined(CONFIG_VIDEO_SAMSUNG_S5P_MFC)
#include <plat/s5p-mfc.h>
#endif

#include <mach/map.h>

/* Following are default values for UCON, ULCON and UFCON UART registers */
#define SMDKV310_UCON_DEFAULT	(S3C2410_UCON_TXILEVEL |	\
				 S3C2410_UCON_RXILEVEL |	\
				 S3C2410_UCON_TXIRQMODE |	\
				 S3C2410_UCON_RXIRQMODE |	\
				 S3C2410_UCON_RXFIFO_TOI |	\
				 S3C2443_UCON_RXERR_IRQEN)

#define SMDKV310_ULCON_DEFAULT	S3C2410_LCON_CS8

#define SMDKV310_UFCON_DEFAULT	(S3C2410_UFCON_FIFOMODE |	\
				 S5PV210_UFCON_TXTRIG4 |	\
				 S5PV210_UFCON_RXTRIG4)

static struct s3c2410_uartcfg fpga5210_uartcfgs[] __initdata = {
	[0] = {
		.hwport		= 0,
		.flags		= 0,
		.ucon		= SMDKV310_UCON_DEFAULT,
		.ulcon		= SMDKV310_ULCON_DEFAULT,
		.ufcon		= SMDKV310_UFCON_DEFAULT,
	},
	[1] = {
		.hwport		= 1,
		.flags		= 0,
		.ucon		= SMDKV310_UCON_DEFAULT,
		.ulcon		= SMDKV310_ULCON_DEFAULT,
		.ufcon		= SMDKV310_UFCON_DEFAULT,
	},
	[2] = {
		.hwport		= 2,
		.flags		= 0,
		.ucon		= SMDKV310_UCON_DEFAULT,
		.ulcon		= SMDKV310_ULCON_DEFAULT,
		.ufcon		= SMDKV310_UFCON_DEFAULT,
	},
	[3] = {
		.hwport		= 3,
		.flags		= 0,
		.ucon		= SMDKV310_UCON_DEFAULT,
		.ulcon		= SMDKV310_ULCON_DEFAULT,
		.ufcon		= SMDKV310_UFCON_DEFAULT,
	},
};

#ifdef CONFIG_S5P_DP
static struct s3c_fb_pd_win smdkc210_fb_win0 = {
	.win_mode = {
		.left_margin	= 98,
		.right_margin	= 48,
		.upper_margin	= 23,
		.lower_margin	= 1,
		.hsync_len	= 128,
		.vsync_len	= 4,
		.xres		= 800,
		.yres		= 600,
	},
	.max_bpp		= 32,
	.default_bpp		= 24,
};
#else
static struct s3c_fb_pd_win smdkc210_fb_win0 = {
	.win_mode = {
		.left_margin	= 13,
		.right_margin	= 8,
		.upper_margin	= 7,
		.lower_margin	= 5,
		.hsync_len	= 3,
		.vsync_len	= 1,
		.xres		= 800,
		.yres		= 480,
	},
	.max_bpp		= 32,
	.default_bpp		= 24,
};
#endif

static void exynos_fimd_gpio_setup(void)
{
	unsigned int reg = 0;

	reg = __raw_readl(S3C_VA_SYS + 0x0214);
	reg |= (1 << 15);
	__raw_writel(reg, S3C_VA_SYS + 0x0214);
}

static struct s3c_fb_platdata smdkc210_lcd1_pdata __initdata = {
	.win[0]		= &smdkc210_fb_win0,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
#ifdef CONFIG_S5P_DP
	.vidcon1	= VIDCON1_INV_VCLK,
#else
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
#endif
	.setup_gpio	= exynos_fimd_gpio_setup,
};

#ifdef CONFIG_S5P_DP
static struct video_info fpga5210_dp_config = {
	.name			= "DELL U2410, for FPGA TEST",

	.h_total		= 1074,
	.h_active		= 800,
	.h_sync_width		= 128,
	.h_back_porch		= 98,
	.h_front_porch		= 48,

	.v_total		= 628,
	.v_active		= 600,
	.v_sync_width		= 4,
	.v_back_porch		= 23,
	.v_front_porch		= 1,

	.v_sync_rate		= 5,

	.mvid			= 0,
	.nvid			= 0,

	.h_sync_polarity	= 0,
	.v_sync_polarity	= 0,
	.interlaced		= 0,

	.color_space		= COLOR_RGB,
	.dynamic_range		= VESA,
	.ycbcr_coeff		= COLOR_YCBCR601,
	.color_depth		= COLOR_8,

	.sync_clock		= 0,
	.even_field		= 0,

	.refresh_denominator	= REFRESH_DENOMINATOR_1,

	.test_pattern		= COLORBAR_32,
	.link_rate		= LINK_RATE_1_62GBPS,
	.lane_count		= LANE_COUNT1,

	.video_mute_on		= 0,

	.master_mode		= 0,
	.bist_mode		= 0,
};

static struct s5p_dp_platdata fpga5210_dp_data __initdata = {
	.video_info	= &fpga5210_dp_config,
	.phy_init	= s5p_dp_phy_init,
	.phy_exit	= s5p_dp_phy_exit,
};
#endif

static struct platform_device *fpga5210_devices[] __initdata = {
#ifdef CONFIG_S5P_DP
	&s5p_device_dp,
#endif
	&s5p_device_fimd1,
#if defined(CONFIG_VIDEO_SAMSUNG_S5P_MFC)
	&s5p_device_mfc,
#endif
};

#if defined(CONFIG_S5P_MEM_CMA)
static void __init exynos5_reserve_mem(void)
{
	static struct cma_region regions[] = {
#ifdef CONFIG_VIDEO_SAMSUNG_S5P_MFC
		{
			.name		= "fw",
			.size		= 1 << 20,
			{ .alignment	= 128 << 10 },
			.start		= 0x44000000,
		},
		{
			.name		= "b1",
			.size		= 32 << 20,
			.start		= 0x45000000,
		},
		{
			.name		= "b2",
			.size		= 32 << 20,
			.start		= 0x51000000,
		},
#endif
		{
			.size = 0
		},
	};

	static const char map[] __initconst =
#ifdef CONFIG_VIDEO_SAMSUNG_S5P_MFC
		"s5p-mfc-v6/f=fw;"
		"s5p-mfc-v6/a=b1;"
		"s5p-mfc-v6/b=b2;";
#endif
	cma_set_defaults(regions, map);
	cma_early_regions_reserve(NULL);
}
#endif

static void __init fpga5210_map_io(void)
{
	clk_xusbxti.rate = 8000000;
	s5p_init_io(NULL, 0, S5P_VA_CHIPID);
	s3c24xx_init_clocks(8000000);
	s3c24xx_init_uarts(fpga5210_uartcfgs, ARRAY_SIZE(fpga5210_uartcfgs));
#if defined(CONFIG_S5P_MEM_CMA)
		exynos5_reserve_mem();
#endif
}

static void __init fpga5210_machine_init(void)
{
	s5p_fimd1_set_platdata(&smdkc210_lcd1_pdata);
#ifdef CONFIG_S5P_DP
	s5p_dp_set_platdata(&fpga5210_dp_data);
#endif
#if defined(CONFIG_VIDEO_SAMSUNG_S5P_MFC)
	s5p_mfc_setname(&s5p_device_mfc, "s5p-mfc-v6");
#endif
	platform_add_devices(fpga5210_devices, ARRAY_SIZE(fpga5210_devices));
}

MACHINE_START(FPGA5210, "FPGA5210")
	.boot_params	= S5P_PA_SDRAM + 0x100,
	.init_irq	= exynos5_init_irq,
	.map_io		= fpga5210_map_io,
	.init_machine	= fpga5210_machine_init,
	.timer		= &exynos4_timer,
MACHINE_END
