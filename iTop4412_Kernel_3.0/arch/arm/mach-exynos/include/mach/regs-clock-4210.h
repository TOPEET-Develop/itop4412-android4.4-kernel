/* linux/arch/arm/mach-exynos4/include/mach/regs-clock-4210.h
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS4 - 4210 Clock register definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_REGS_CLOCK_4210_H
#define __ASM_ARCH_REGS_CLOCK_4210_H __FILE__

#define S5P_CLKSRC_LCD1			S5P_CLKREG(0x0C238)

#define S5P_CLKSRC_MASK_LCD1		S5P_CLKREG(0x0C338)

#define S5P_CLKDIV_LCD1			S5P_CLKREG(0x0C538)

#define S5P_CLKDIV_STAT_TOP		S5P_CLKREG(0x0C610)
#define S5P_CLKDIV_STAT_MFC		S5P_CLKREG(0x0C628)

#define S5P_CLKGATE_IP_IMAGE		S5P_CLKREG(0x0C930)
#define S5P_CLKGATE_IP_LCD1		S5P_CLKREG(0x0C938)
#define S5P_CLKGATE_IP_MAUDIO		S5P_CLKREG(0x0C93C)
#define S5P_CLKGATE_IP_PERIR		S5P_CLKREG(0x0C960)

#define S5P_MPLL_LOCK			S5P_CLKREG(0x14004)
#define S5P_MPLL_CON0			S5P_CLKREG(0x14108)
#define S5P_MPLL_CON1			S5P_CLKREG(0x1410C)

#endif /* __ASM_ARCH_REGS_CLOCK_4210_H */
