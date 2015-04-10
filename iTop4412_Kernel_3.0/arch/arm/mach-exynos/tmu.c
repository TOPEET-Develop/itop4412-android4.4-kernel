/* linux/arch/arm/mach-exynos/tmu.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *      http://www.samsung.com
 *
 * EXYNOS4210 - Thermal Management support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/interrupt.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/irq.h>

#include <asm/irq.h>

#include <mach/regs-tmu.h>
#include <mach/cpufreq.h>
#include <plat/s5p-tmu.h>

#define THD_TEMP 80
#define TRIGGER_LEV0 5      /* Throttling temperature */
#define TRIGGER_LEV1 20     /* Waring temperature */
#define TRIGGER_LEV2 30     /* Tripping temperature */
#define TRIGGER_LEV3 0xFF   /* Not used */

#define TMU_SAVE_NUM   10
#define VREF_SLOPE     0x07000F02
#define TMU_EN         0x1
#define TMU_DC_VALUE   25
#define EFUSE_MIN_VALUE 60
#define EFUSE_AVG_VALUE 80
#define EFUSE_MAX_VALUE 100

static struct resource *s5p_tmu_mem;
static int irq_tmu = NO_IRQ;
unsigned int tmu_save[TMU_SAVE_NUM];

enum tmu_status_t {
	TMU_STATUS_NORMAL = 0,
	TMU_STATUS_THROTTLED,
	TMU_STATUS_WARNING,
	TMU_STATUS_TRIPPED,
};

static struct s5p_tmu *tz;
static struct workqueue_struct  *tmu_wq;
static struct delayed_work tmu_work;

static int tmu_tripped_cb(void)
{
	struct power_supply *psy = power_supply_get_by_name("battery");
	union power_supply_propval value;

	if (!psy) {
		pr_err("%s:fail to get batter ps\n", __func__);
		return -ENODEV;
		}

	value.intval = TMU_STATUS_TRIPPED;
	return psy->set_property(psy, POWER_SUPPLY_PROP_TEMP_AMBIENT, &value);
}

static void tmu_monitor(struct work_struct *work)
{
	unsigned char cur_temp, thr_temp;
	unsigned char warning_temp, tripped_temp;

	cur_temp = __raw_readb(tz->tmu_base + CURRENT_TEMP);
	cur_temp = cur_temp - tz->data.te1 + TMU_DC_VALUE;

	thr_temp = __raw_readb(tz->tmu_base + THRESHOLD_TEMP);
	thr_temp = thr_temp - tz->data.te1 + TMU_DC_VALUE;

	warning_temp = thr_temp + TRIGGER_LEV1;
	tripped_temp = thr_temp + TRIGGER_LEV2;

	pr_info("Current: %dc, Cooling: %dc\n",
			cur_temp, tz->data.cooling);

	switch (tz->data.tmu_flag) {
	case TMU_STATUS_NORMAL:
		cancel_delayed_work(&tmu_work);
		enable_irq(irq_tmu);
		return;
	case TMU_STATUS_THROTTLED:
		if (cur_temp >= warning_temp)
			tz->data.tmu_flag = TMU_STATUS_WARNING;
		else if (cur_temp >= tz->data.cooling && cur_temp < warning_temp)
			exynos_cpufreq_upper_limit(DVFS_LOCK_ID_TMU, L2);
		else {
			tz->data.tmu_flag = TMU_STATUS_NORMAL;
			exynos_cpufreq_upper_limit_free(DVFS_LOCK_ID_TMU);
		}
		queue_delayed_work_on(0, tmu_wq, &tmu_work, usecs_to_jiffies(500 * 1000));
		return;
	case TMU_STATUS_WARNING:
		if (cur_temp >= tripped_temp)
			tz->data.tmu_flag = TMU_STATUS_TRIPPED;
		else if (cur_temp > tz->data.cooling && cur_temp < tripped_temp)
			exynos_cpufreq_upper_limit(DVFS_LOCK_ID_TMU, L3);
		else {
			tz->data.tmu_flag = TMU_STATUS_NORMAL;
			exynos_cpufreq_upper_limit_free(DVFS_LOCK_ID_TMU);
		}
		queue_delayed_work_on(0, tmu_wq, &tmu_work, usecs_to_jiffies(500 * 1000));
		return;
	case TMU_STATUS_TRIPPED:
		tmu_tripped_cb();
		queue_delayed_work_on(0, tmu_wq, &tmu_work, msecs_to_jiffies(10000 * 1000));
	default:
		return;
	}
}

static void s5p_pm_tmu_save(struct s5p_tmu *tz)
{
	tmu_save[0] = __raw_readl(tz->tmu_base + TMU_CON0);
	tmu_save[1] = __raw_readl(tz->tmu_base + SAMPLING_INTERNAL);
	tmu_save[2] = __raw_readl(tz->tmu_base + CNT_VALUE0);
	tmu_save[3] = __raw_readl(tz->tmu_base + CNT_VALUE1);
	tmu_save[4] = __raw_readl(tz->tmu_base + THRESHOLD_TEMP);
	tmu_save[5] = __raw_readl(tz->tmu_base + INTEN);
	tmu_save[6] = __raw_readl(tz->tmu_base + TRG_LEV0);
	tmu_save[7] = __raw_readl(tz->tmu_base + TRG_LEV1);
	tmu_save[8] = __raw_readl(tz->tmu_base + TRG_LEV2);
	tmu_save[9] = __raw_readl(tz->tmu_base + TRG_LEV3);
}

static void s5p_pm_tmu_restore(struct s5p_tmu *tz)
{
	__raw_writel(tmu_save[0], tz->tmu_base + TMU_CON0);
	__raw_writel(tmu_save[1], tz->tmu_base + SAMPLING_INTERNAL);
	__raw_writel(tmu_save[2], tz->tmu_base + CNT_VALUE0);
	__raw_writel(tmu_save[3], tz->tmu_base + CNT_VALUE1);
	__raw_writel(tmu_save[4], tz->tmu_base + THRESHOLD_TEMP);
	__raw_writel(tmu_save[5], tz->tmu_base + INTEN);
	__raw_writel(tmu_save[6], tz->tmu_base + TRG_LEV0);
	__raw_writel(tmu_save[7], tz->tmu_base + TRG_LEV1);
	__raw_writel(tmu_save[8], tz->tmu_base + TRG_LEV2);
	__raw_writel(tmu_save[9], tz->tmu_base + TRG_LEV3);
}

static int tmu_initialize(struct platform_device *pdev)
{
	struct s5p_tmu *tz = platform_get_drvdata(pdev);
	unsigned int en;
	unsigned int te_temp;

	en = (__raw_readl(tz->tmu_base + TMU_STATUS) & 0x1);

	if (!en) {
		dev_err(&pdev->dev, "failed to start tmu drvier\n");
		return -ENOENT;
	}

	/* get the compensation parameter */
	te_temp = __raw_readl(tz->tmu_base + TRIMINFO);
	tz->data.te1 = te_temp & TRIM_TEMP_MASK;
	tz->data.te2 = ((te_temp >> 8) & TRIM_TEMP_MASK);

	if ((EFUSE_MIN_VALUE > tz->data.te1) || (tz->data.te1 > EFUSE_MAX_VALUE)
		||  (tz->data.te2 != 0))
		tz->data.te1 = EFUSE_AVG_VALUE;

	/* Need to initail regsiter setting after getting parameter info */
	/* [28:23] vref [11:8] slope - Tunning parameter */
	__raw_writel(VREF_SLOPE, tz->tmu_base + TMU_CON0);

	return 0;
}

static void tmu_start(struct platform_device *pdev)
{
	struct s5p_tmu *tz = platform_get_drvdata(pdev);
	unsigned int con, thr_temp;

	__raw_writel(INTCLEARALL, tz->tmu_base + INTCLEAR);

	/*Get Threshold value */
	thr_temp = THD_TEMP + tz->data.te1 - TMU_DC_VALUE;

	/* Set interrupt trigger level */
	__raw_writel(thr_temp, tz->tmu_base + THRESHOLD_TEMP);
	__raw_writel(TRIGGER_LEV0, tz->tmu_base + TRG_LEV0);
	__raw_writel(TRIGGER_LEV1, tz->tmu_base + TRG_LEV1);
	__raw_writel(TRIGGER_LEV2, tz->tmu_base + TRG_LEV2);
	__raw_writel(TRIGGER_LEV3, tz->tmu_base + TRG_LEV3);

	/* TMU core enable */
	con = __raw_readl(tz->tmu_base + TMU_CON0);
	con |= TMU_EN;

	__raw_writel(con, tz->tmu_base + TMU_CON0);

	/*LEV0 LEV1 LEV2 interrupt enable */
	__raw_writel(INTEN0|INTEN1|INTEN2, tz->tmu_base + INTEN);

	pr_info("Cooling: %dc  Throttling: %dc Warning: %dc  Tripping: %dc\n",
	tz->data.cooling,
	THD_TEMP + TRIGGER_LEV0,
	THD_TEMP + TRIGGER_LEV1,
	THD_TEMP + TRIGGER_LEV2);
}

static irqreturn_t s5p_tmu_irq(int irq, void *id)
{
	struct s5p_tmu *tz = id;
	unsigned int status;

	disable_irq_nosync(irq);

	status = __raw_readl(tz->tmu_base + INTSTAT);

	if (status & INTSTAT0) {
		pr_info("Throtting interrupt occured!!!!\n");
		__raw_writel(INTCLEAR0, tz->tmu_base + INTCLEAR);
		tz->data.tmu_flag = TMU_STATUS_THROTTLED;
		queue_delayed_work_on(0, tmu_wq, &tmu_work, usecs_to_jiffies(500 * 1000));
	} else if (status & INTSTAT1) {
		pr_info("Warning interrupt occured!!!!\n");
		__raw_writel(INTCLEAR1, tz->tmu_base + INTCLEAR);
		tz->data.tmu_flag = TMU_STATUS_WARNING;
		queue_delayed_work_on(0, tmu_wq, &tmu_work, usecs_to_jiffies(500 * 1000));
	} else if (status & INTSTAT2) {
		pr_info("Tripping interrupt occured!!!!\n");
		__raw_writel(INTCLEAR2, tz->tmu_base + INTCLEAR);
		tmu_tripped_cb();
	} else {
		pr_err("%s: TMU interrupt error\n", __func__);
		return -ENODEV;
	}

	return IRQ_HANDLED;
}

static int __devinit s5p_tmu_probe(struct platform_device *pdev)
{
	struct s5p_tmu *tz = platform_get_drvdata(pdev);
	struct resource *res;
	int	ret = 0;

	pr_debug("%s: probe=%p\n", __func__, pdev);

	irq_tmu = platform_get_irq(pdev, 0);
	if (irq_tmu < 0) {
		dev_err(&pdev->dev, "no irq for thermal\n");
		return -ENOENT;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "failed to get memory region resource\n");
		return -ENOENT;
	}

	s5p_tmu_mem = request_mem_region(res->start,
					res->end-res->start+1,
					pdev->name);
	if (s5p_tmu_mem == NULL) {
		dev_err(&pdev->dev, "failed to reserve memory region\n");
		ret = -ENOENT;
		goto err_nores;
	}

	tz->tmu_base = ioremap(res->start, (res->end - res->start) + 1);
	if (tz->tmu_base == NULL) {
		dev_err(&pdev->dev, "failed ioremap()\n");
		ret = -EINVAL;
		goto err_nomap;
	}

	ret = request_irq(irq_tmu, s5p_tmu_irq,
			IRQF_DISABLED,  "s5p-tmu interrupt", tz);
	if (ret) {
		dev_err(&pdev->dev, "IRQ%d error %d\n", irq_tmu, ret);
		goto err_noirq;
	}

	ret = tmu_initialize(pdev);
	if (ret)
		goto err_noinit;

	tmu_start(pdev);

	return ret;

err_noinit:
	free_irq(irq_tmu, tz);
err_noirq:
	iounmap(tz->tmu_base);
err_nomap:
	release_resource(s5p_tmu_mem);
err_nores:
	return ret;
}

static int __devinit s5p_tmu_remove(struct platform_device *pdev)
{
	struct s5p_tmu *tz = platform_get_drvdata(pdev);

	free_irq(irq_tmu, (void *)pdev);
	iounmap(tz->tmu_base);

	pr_info("%s is removed\n", dev_name(&pdev->dev));
	return 0;
}

#ifdef CONFIG_PM
static int s5p_tmu_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct s5p_tmu *tz = platform_get_drvdata(pdev);
	s5p_pm_tmu_save(tz);

	return 0;
}

static int s5p_tmu_resume(struct platform_device *pdev)
{
	struct s5p_tmu *tz = platform_get_drvdata(pdev);
	s5p_pm_tmu_restore(tz);

	return 0;
}

#else
#define s5p_tmu_suspend	NULL
#define s5p_tmu_resume	NULL
#endif

static struct platform_driver s5p_tmu_driver = {
	.probe		= s5p_tmu_probe,
	.remove		= s5p_tmu_remove,
	.suspend	= s5p_tmu_suspend,
	.resume		= s5p_tmu_resume,
	.driver		= {
		.name	=	"s5p-tmu",
		.owner	=	THIS_MODULE,
		},
};

static int __init s5p_tmu_driver_init(void)
{
	int ret;

	tmu_wq = create_workqueue("tmu");
	if (!tmu_wq) {
		pr_err(" creation of tmu failed\n");
		ret = -EFAULT;
		goto out;
	}

	INIT_DELAYED_WORK_DEFERRABLE(&tmu_work, tmu_monitor);
	ret =  platform_driver_register(&s5p_tmu_driver);
	if (ret) {
		pr_err("registeration of tmu_driver failed\n");
		destroy_workqueue(tmu_wq);
		goto out;
	}
out:
	return ret;
}

arch_initcall(s5p_tmu_driver_init);

