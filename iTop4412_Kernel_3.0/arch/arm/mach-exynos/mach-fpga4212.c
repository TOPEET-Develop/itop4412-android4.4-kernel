/* linux/arch/arm/mach-exynos4/mach-fpga4212.c
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

#include <asm/mach/arch.h>
#include <asm/mach-types.h>

#include <plat/regs-serial.h>
#include <plat/exynos4.h>
#include <plat/cpu.h>
#include <plat/clock.h>

#include <mach/map.h>

#include <plat/devs.h>
#include <mach/sysmmu.h>
#include <plat/fimg2d.h>

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

static struct s3c2410_uartcfg smdkv310_uartcfgs[] __initdata = {
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

#ifdef CONFIG_VIDEO_FIMG2D
static struct fimg2d_platdata fimg2d_data __initdata = {
	.hw_ver = 41,
	.parent_clkname = "mout_g2d0",
	.clkname = "sclk_fimg2d",
	.gate_clkname = "fimg2d",
	.clkrate = 267 * 1000000,	/* 266 Mhz */
};
#endif

static struct platform_device *smdkv310_devices[] __initdata = {
#ifdef CONFIG_S5P_SYSTEM_MMU
	&exynos_device_sysmmu[SYSMMU_MDMA],
	&exynos_device_sysmmu[SYSMMU_SSS],
	&exynos_device_sysmmu[SYSMMU_FIMC0],
	&exynos_device_sysmmu[SYSMMU_FIMC1],
	&exynos_device_sysmmu[SYSMMU_FIMC2],
	&exynos_device_sysmmu[SYSMMU_FIMC3],
	&exynos_device_sysmmu[SYSMMU_JPEG],
	&exynos_device_sysmmu[SYSMMU_FIMD0],
	&exynos_device_sysmmu[SYSMMU_FIMD1],
	&exynos_device_sysmmu[SYSMMU_PCIe],
	&exynos_device_sysmmu[SYSMMU_G2D],
	&exynos_device_sysmmu[SYSMMU_ROTATOR],
	&exynos_device_sysmmu[SYSMMU_MDMA2],
	&exynos_device_sysmmu[SYSMMU_TV],
	&exynos_device_sysmmu[SYSMMU_MFC_L],
	&exynos_device_sysmmu[SYSMMU_MFC_R],
#endif
#ifdef CONFIG_VIDEO_FIMG2D
	&s5p_device_fimg2d,
#endif
};

static void __init smdkv310_map_io(void)
{
	clk_xusbxti.rate = 12000000;
	s5p_init_io(NULL, 0, S5P_VA_CHIPID);
	s3c24xx_init_clocks(12000000);
	s3c24xx_init_uarts(smdkv310_uartcfgs, ARRAY_SIZE(smdkv310_uartcfgs));
}

static void __init smdkv310_machine_init(void)
{
#ifdef CONFIG_VIDEO_FIMG2D
	s5p_fimg2d_set_platdata(&fimg2d_data);
#ifdef CONFIG_EXYNOS4_DEV_PD
	s5p_device_fimg2d.dev.parent = &exynos4_device_pd[PD_LCD0].dev;
#endif
#endif
	platform_add_devices(smdkv310_devices, ARRAY_SIZE(smdkv310_devices));
}

MACHINE_START(FPGA4212, "FPGA4212")
	.boot_params	= S5P_PA_SDRAM + 0x100,
	.init_irq	= exynos4_init_irq,
	.map_io		= smdkv310_map_io,
	.init_machine	= smdkv310_machine_init,
	.timer		= &exynos4_timer,
MACHINE_END
