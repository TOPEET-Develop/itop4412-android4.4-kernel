/* linux/arch/arm/mach-exynos4/include/mach/sysmmu.h
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Samsung sysmmu driver for EXYNOS4
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARM_ARCH_SYSMMU_H
#define __ASM_ARM_ARCH_SYSMMU_H __FILE__

enum exynos_sysmmu_ips {
	SYSMMU_MDMA,
	SYSMMU_SSS,
	SYSMMU_FIMC0,
	SYSMMU_FIMC1,
	SYSMMU_FIMC2,
	SYSMMU_FIMC3,
	SYSMMU_JPEG,
	SYSMMU_FIMD0,
	SYSMMU_FIMD1,
	SYSMMU_PCIe,
	SYSMMU_G2D,
	SYSMMU_ROTATOR,
	SYSMMU_MDMA2,
	SYSMMU_TV,
	SYSMMU_MFC_L,
	SYSMMU_MFC_R,
	EXYNOS_SYSMMU_TOTAL_IPNUM,
};

#define S5P_SYSMMU_TOTAL_IPNUM		EXYNOS_SYSMMU_TOTAL_IPNUM

typedef enum exynos_sysmmu_ips sysmmu_ips;

static inline const char *get_sysmmu_name(sysmmu_ips ips)
{
#ifdef CONFIG_S5P_SYSTEM_MMU
	extern const char *sysmmu_ips_name[EXYNOS_SYSMMU_TOTAL_IPNUM];
	return sysmmu_ips_name[ips];
#else
	return "NO_SYSMMU_LOADED";
#endif
}

#ifdef CONFIG_S5P_SYSTEM_MMU
struct device;
void sysmmu_clk_init(sysmmu_ips ips, struct device *dev);
void sysmmu_clk_enable(sysmmu_ips ips);
void sysmmu_clk_disable(sysmmu_ips ips);
#else
#define sysmmu_clk_init(ips, dev) do { } while (0)
#define sysmmu_clk_enable(ips) do { } while (0)
#define sysmmu_clk_disable(ips) do { } while (0)
#endif

#endif /* __ASM_ARM_ARCH_SYSMMU_H */
