/* linux/arch/arm/mach-exynos/include/mach/pm-core.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Based on arch/arm/mach-s3c2410/include/mach/pm-core.h,
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * EXYNOS4210 - PM core support for arch/arm/plat-s5p/pm.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
#include <mach/regs-pmu.h>
#include <mach/regs-gpio.h>	//yulu

static inline void s3c_pm_debug_init_uart(void)
{
	/* nothing here yet */
}

static inline void s3c_pm_arch_prepare_irqs(void)
{
	//unsigned int tmp;
#if 0
	tmp = __raw_readl(S5P_WAKEUP_MASK);
	tmp &= ~(1 << 31);
	__raw_writel(tmp, S5P_WAKEUP_MASK);
#else

	s3c_irqwake_intmask &= ~(0xFFF << 20);
	s3c_irqwake_intmask |= (0x3F << 20);//Robin, Mask IRQ2/IRQ3/FIQ2/FIQ3 of external GIC
	s3c_irqwake_eintmask &=~(0x1 << 2);	//yulu

	/* add by cym 20140812 */
#ifdef CONFIG_BOARD_TYPE_FULL_FUNCTION
	s3c_irqwake_eintmask &=~(0x1 << 26);//enable IRQ26
#else
	s3c_irqwake_eintmask &=~(0x1 << 27);//enable IRQ27
#endif
	/* end add */

#endif
	__raw_writel(s3c_irqwake_intmask, S5P_WAKEUP_MASK);
	/* modify by cym 20130409 for MT6600 */
#if 0
	__raw_writel(s3c_irqwake_eintmask, S5P_EINT_WAKEUP_MASK);
#else
#if defined(CONFIG_MTK_COMBO_COMM) || defined(CONFIG_MTK_COMBO_COMM_MODULE)
	__raw_writel(s3c_irqwake_eintmask|(0x30<<16), S5P_EINT_WAKEUP_MASK); //mask EINT20 and EINT21
#else
	__raw_writel(s3c_irqwake_eintmask, S5P_EINT_WAKEUP_MASK);
#endif
#endif
}

static inline void s3c_pm_arch_stop_clocks(void)
{
	/* nothing here yet */
}

static inline void s3c_pm_arch_show_resume_irqs(void)
{
	//yulu
	pr_info("WAKEUP_STAT: 0x%x\n", __raw_readl(S5P_WAKEUP_STAT));
	pr_info("WAKUP_INT0_PEND: 0x%x\n", __raw_readl(S5P_EINT_PEND(0)));
	pr_info("WAKUP_INT1_PEND: 0x%x\n", __raw_readl(S5P_EINT_PEND(1)));
	pr_info("WAKUP_INT2_PEND: 0x%x\n", __raw_readl(S5P_EINT_PEND(2)));
	pr_info("WAKUP_INT3_PEND: 0x%x\n", __raw_readl(S5P_EINT_PEND(3)));
	//Robin Wang, Clear Pendings...
	__raw_writel(__raw_readl(S5P_EINT_PEND(0)),S5P_EINT_PEND(0));
	//__raw_writel(__raw_readl(S5P_EINT_PEND(1)),S5P_EINT_PEND(1));
	//__raw_writel(__raw_readl(S5P_EINT_PEND(2)),S5P_EINT_PEND(2));
	//__raw_writel(__raw_readl(S5P_EINT_PEND(3)),S5P_EINT_PEND(3));
}

static inline void s3c_pm_arch_update_uart(void __iomem *regs,
					   struct pm_uart_save *save)
{
	/* nothing here yet */
}

static inline void s3c_pm_restored_gpios(void)
{
	/* nothing here yet */
}

static inline void s3c_pm_saved_gpios(void)
{
	/* nothing here yet */
}
