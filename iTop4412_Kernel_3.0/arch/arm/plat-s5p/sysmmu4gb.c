/* Copyright (c) 2011 Samsung Electronics Co, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/interrupt.h>

#include <mach/map.h>

#include <plat/sysmmu.h>
#include <plat/map-s5p.h>

/*
 *  0 : S5P_PA_SYSMMU_MDMA		(0x10A40000),
 *  1 : S5P_PA_SYSMMU_SSS		(0x10A50000),
 *  2 : S5P_PA_SYSMMU_FIMC0		(0x11A20000),
 *  3 : S5P_PA_SYSMMU_FIMC1		(0x11A30000),
 *  4 : S5P_PA_SYSMMU_FIMC2		(0x11A40000),
 *  5 : S5P_PA_SYSMMU_FIMC3		(0x11A50000),
 *  6 : S5P_PA_SYSMMU_JPEG		(0x11A60000),
 *  7 : S5P_PA_SYSMMU_FIMD0		(0x11E20000),
 *  8 : S5P_PA_SYSMMU_FIMD1		(0x12220000),
 *  9 : S5P_PA_SYSMMU_PCIe		(0x12620000),
 * 10 : S5P_PA_SYSMMU_G2D		(0x12A20000),
 * 11 : S5P_PA_SYSMMU_ROTATOR		(0x12A30000),
 * 12 : S5P_PA_SYSMMU_MDMA2		(0x12A40000),
 * 13 : S5P_PA_SYSMMU_TV		(0x12E20000),
 * 14 : S5P_PA_SYSMMU_MFC_L		(0x13620000),
 * 15 : S5P_PA_SYSMMU_MFC_R		(0x13630000)
*/
/*
#define S5P_PA_SYSMMU_G2D		(0x10A40000)
#define S5P_PA_SYSMMU_SSS		(0x10A50000)
#define S5P_PA_SYSMMU_FIMC0		(0x11A20000)
#define S5P_PA_SYSMMU_FIMC1		(0x11A30000)
#define S5P_PA_SYSMMU_FIMC2		(0x11A40000)
#define S5P_PA_SYSMMU_FIMC3		(0x11A50000)
#define S5P_PA_SYSMMU_JPEG		(0x11A60000)
#define S5P_PA_SYSMMU_FIMD0		(0x11E20000)

//#define S5P_PA_SYSMMU_FIMC_ISP		(0x12260000)
//#define S5P_PA_SYSMMU_FIMC_DRC		(0x12270000)
//#define S5P_PA_SYSMMU_FIMC_FD		(0x122A0000)
//#define S5P_PA_SYSMMU_ISPCPU		(0x122B0000)
//#define S5P_PA_SYSMMU_FIMC_LITE0		(0x123B0000)
//#define S5P_PA_SYSMMU_FIMC_LITE1		(0x123C0000)


#define S5P_PA_SYSMMU_GPS		(0x12730000)
#define S5P_PA_SYSMMU_ROTATOR		(0x12A30000)
#define S5P_PA_SYSMMU_MDMA2		(0x12A40000)
#define S5P_PA_SYSMMU_TV		(0x12E20000)
*/
#ifdef CONFIG_VIDEO_FIMG2D
extern int g2d_sysmmu_fault();
#else
     int g2d_sysmmu_fault(unsigned int faulted_addr, unsigned int pt_base)
    	{
		return 1;
	}
#endif

static char *sysmmu_ips_name[S5P_SYSMMU_TOTAL_IPNUM] = {
	"SYSMMU_G2D"	,
	"SYSMMU_SSS"	,
	"SYSMMU_FIMC0"	,
	"SYSMMU_FIMC1"	,
	"SYSMMU_FIMC2"	,
	"SYSMMU_FIMC3"	,
	"SYSMMU_JPEG"	,
	"SYSMMU_FIMD0"	,
	"SYSMMU_GPS"	,
	"SYSMMU_ROTATOR",
	"SYSMMU_MDMA2"	,
	"SYSMMU_TV"	,
	"SYSMMU_MFC_L"	,
	"SYSMMU_MFC_R"	,
};

typedef void (*pg_ft_handler)(sysmmu_ips ips, sysmmu_controller_t *sysmmuconp);	/* Page fault callback */
typedef void (*mh_ft_handler)(sysmmu_ips ips, sysmmu_controller_t *sysmmuconp);	/* Multi hit fault callback */
typedef void (*st_ft_handler)(sysmmu_ips ips, sysmmu_controller_t *sysmmuconp);	/* Security fault callback */
typedef void (*as_ft_handler)(sysmmu_ips ips, sysmmu_controller_t *sysmmuconp);	/* Access fault callback */

struct sysmmu_fsr_info {
	void (*pg_fault)(sysmmu_ips ips, sysmmu_controller_t *sysmmuconp);
	void (*mh_fault)(sysmmu_ips ips, sysmmu_controller_t *sysmmuconp);
	void (*st_fault)(sysmmu_ips ips, sysmmu_controller_t *sysmmuconp);
	void (*as_fault)(sysmmu_ips ips, sysmmu_controller_t *sysmmuconp);
	const char *name;
};

static void sysmmu_pg_fault(sysmmu_ips ips, sysmmu_controller_t *sysmmuconp)
{
	printk(KERN_INFO "%s: ips: %s\n", __func__, sysmmuconp->name);
}

static void  sysmmu_do_bad(sysmmu_ips ips, sysmmu_controller_t *sysmmuconp)
{
	printk(KERN_INFO "%s: ips: %s\n", __func__, sysmmuconp->name);
}

	/* Page fault,		Multi fit fault,Security fault,	Access fault,	"ips handler name"	*/
struct sysmmu_fsr_info isysmmu_fsr_info[S5P_SYSMMU_TOTAL_IPNUM] = {
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu g2d fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu sss fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu fimc0 fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu fimc1 fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu fimc2 fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu fimc3 fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu jpeg fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu fimd0 fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu gps fault handler"	},
	//{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu pcle fault handler"	},
	//{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu g2d fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu rotator fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu mdma2 fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu tv fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu mfc_l fault handler"	},
	{ sysmmu_pg_fault,	sysmmu_do_bad,	sysmmu_do_bad,	sysmmu_do_bad,	"sysmmu mfc_r fault handler"	},
};

/*
int s5p_sysmmu_enable(struct device *owner, unsigned long pgd)
{}
void s5p_sysmmu_disable(struct device *owner)
{}
void s5p_sysmmu_set_tablebase_pgd(struct device *owner, unsigned long pgd)
{}
void s5p_sysmmu_tlb_invalidate(struct device *owner)
{}

*/

sysmmu_controller_t s5p_sysmmu_cntlrs[S5P_SYSMMU_TOTAL_IPNUM];

void sysmmu_set_pg_fault(sysmmu_ips ips, pg_ft_handler callback)
{
	isysmmu_fsr_info[ips].pg_fault = callback;
}

void sysmmu_set_mh_fault(sysmmu_ips ips, mh_ft_handler callback)
{
	isysmmu_fsr_info[ips].mh_fault = callback;
}

void sysmmu_set_st_fault(sysmmu_ips ips, st_ft_handler callback)
{
	isysmmu_fsr_info[ips].st_fault = callback;
}

void sysmmu_set_as_fault(sysmmu_ips ips, as_ft_handler callback)
{
	isysmmu_fsr_info[ips].as_fault = callback;
}

/**
 * sysmmu_irq - [GENERIC] irq service routine
 * @irq: irq number
 * @dev_id: pointer to private data
 *
 */
static irqreturn_t sysmmu_irq(int irq, void *dev_id)
{
	sysmmu_controller_t *sysmmuconp;
	unsigned int i;

	unsigned int reg_MMU_CTRL;
	unsigned int reg_MMU_STATUS;
	unsigned int reg_PT_BASE_ADDR;
	unsigned int reg_INT_STATUS;
	unsigned int reg_PAGE_FAULT_ADDR;
	unsigned int reg;

	for (i = 0; i < S5P_SYSMMU_TOTAL_IPNUM; i++) {
		sysmmuconp = &s5p_sysmmu_cntlrs[i];

		if (sysmmuconp->enable == true) {
			reg_INT_STATUS = readl(sysmmuconp->regs + S5P_INT_STATUS);

			if (reg_INT_STATUS & 0xFF) {
				reg_MMU_CTRL = readl(sysmmuconp->regs + S5P_MMU_CTRL);
				reg_MMU_STATUS = readl(sysmmuconp->regs + S5P_MMU_STATUS);
				reg_PT_BASE_ADDR = readl(sysmmuconp->regs + S5P_PT_BASE_ADDR);
				reg_PAGE_FAULT_ADDR = readl(sysmmuconp->regs + S5P_PAGE_FAULT_ADDR);

				printk(KERN_DEBUG "%s: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", __func__);
				printk(KERN_DEBUG "%s: sysmmu irq : ip%2d, ips:%s\n", __func__, i, sysmmuconp->name);

				printk(KERN_DEBUG "%s: MMU_CTRL:0x%X, MMU_STATUS:0x%X, PT_BASE_ADDR:0x%X\n", __func__, reg_MMU_CTRL, reg_MMU_STATUS, reg_PT_BASE_ADDR);
				printk(KERN_DEBUG "%s: INT_STATUS:0x%X, PAGE_FAULT_ADDR:0x%X\n", __func__, reg_INT_STATUS, reg_PAGE_FAULT_ADDR);

				switch (reg_INT_STATUS & 0xFF) {
				case 0x1:
					printk(KERN_DEBUG "%s: Page fault\n", __func__);
					printk(KERN_DEBUG "%s: Virtual address causing last page fault or bus error : 0x%x\n", __func__ , reg_PAGE_FAULT_ADDR);
					isysmmu_fsr_info[i].pg_fault((sysmmu_ips)i, sysmmuconp);
					
					if((sysmmu_ips)i == SYSMMU_G2D) {
						g2d_sysmmu_fault(reg_PAGE_FAULT_ADDR, reg_PT_BASE_ADDR);
						reg = readl(sysmmuconp->regs + S5P_MMU_CTRL);
						reg &= ~((0x1<<2) | (0x1<<0));	/* Disable interrupt, Disable MMU */
						writel(reg, sysmmuconp->regs + S5P_MMU_CTRL);
					}
					break;
				case 0x2:
					printk(KERN_DEBUG "%s: AR multi-hit fault\n", __func__);
					isysmmu_fsr_info[i].mh_fault((sysmmu_ips)i, sysmmuconp);
					break;
				case 0x4:
					printk(KERN_DEBUG "%s: AW multi-hit fault\n", __func__);
					isysmmu_fsr_info[i].mh_fault((sysmmu_ips)i, sysmmuconp);
					break;
				case 0x8:
					printk(KERN_DEBUG "%s: Bus error\n", __func__);
					break;
				case 0x10:
					printk(KERN_DEBUG "%s: AR Security protection fault\n", __func__);
					isysmmu_fsr_info[i].as_fault((sysmmu_ips)i, sysmmuconp);
					break;
				case 0x20:
					printk(KERN_DEBUG "%s: AR Access protection fault\n", __func__);
					isysmmu_fsr_info[i].as_fault((sysmmu_ips)i, sysmmuconp);
					break;
				case 0x40:
					printk(KERN_DEBUG "%s: AW Security protection fault\n", __func__);
					isysmmu_fsr_info[i].st_fault((sysmmu_ips)i, sysmmuconp);
					break;
				case 0x80:
					printk(KERN_DEBUG "%s: AW Access protection fault\n", __func__);
					isysmmu_fsr_info[i].st_fault((sysmmu_ips)i, sysmmuconp);
					break;
				}

				printk(KERN_DEBUG "%s: before clear - MMU_CTRL:0x%X, MMU_STATUS:0x%X\n", __func__, reg_MMU_CTRL , reg_MMU_STATUS);
				writel(reg_INT_STATUS, sysmmuconp->regs + S5P_INT_CLEAR);	/* Clear INT */

				reg_INT_STATUS = readl(sysmmuconp->regs + S5P_INT_STATUS);
				printk(KERN_DEBUG "%s: After Clear : INT_STATUS:0x%X, PAGE_FAULT_ADDR:0x%X\n", __func__, reg_INT_STATUS, reg_PAGE_FAULT_ADDR);
				printk(KERN_DEBUG "%s: <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", __func__);
			}
		}
	}
	return IRQ_HANDLED;
}

/*
static void sysmmu_get_info(int ipnum, sysmmu_controller_t *sysmmuconp)
{
	sysmmuconp = &s5p_sysmmu_cntlrs[ipnum];
}
*/

int sysmmu_set_tablebase_pgd(sysmmu_ips ips, unsigned long pgd)
{
	sysmmu_controller_t *sysmmuconp = NULL;
	unsigned int reg;
	
	sysmmuconp = &s5p_sysmmu_cntlrs[ips];	/* sysmmu_get_info(ipnum, sysmmuconp); */

	if (ips == SYSMMU_G2D) {
		reg = readl(sysmmuconp->regs + S5P_MMU_CTRL);
		if ((reg & 0x1) == 0) {
			reg |= ((0x1<<2)|(0x1<<0));	/* Enable interrupt, Enable MMU */
			writel(reg, sysmmuconp->regs + S5P_MMU_CTRL);
		}
	}

	sysmmu_debug("Start, %s\n", sysmmuconp->name);

	writel(pgd, sysmmuconp->regs + S5P_PT_BASE_ADDR);	/* Set sysmmu TTBase */

	if (sysmmu_tlb_invalidate(ips) != 0)
		printk(KERN_ERR "%s: failed sysmmu_tlb_invalidate\n", __func__);

	sysmmu_debug("Done, %s\n", sysmmuconp->name);

	return 0;
}

static int sysmmu_set_tablebase(sysmmu_ips ips)
{
	unsigned int pg;
	sysmmu_controller_t *sysmmuconp;

	sysmmuconp = &s5p_sysmmu_cntlrs[ips];	/* sysmmu_get_info(ipnum, sysmmuconp); */

	sysmmu_debug("Start, %s\n", sysmmuconp->name);

	if (sysmmuconp->table_type == SHARED) {

		__asm__("mrc	p15, 0, %0, c2, c0, 0"	\
				: "=r" (pg) : : "cc");		\
			pg &= ~0x3fff;

		printk(KERN_INFO "%s: CP15 TTBR0 : 0x%x\n", __func__, pg);

		printk(KERN_INFO "%s: %s sysmmuconp->regs + S5P_PT_BASE_ADDR:0x%X\n", __func__, sysmmuconp->name, (unsigned int)(sysmmuconp->regs + S5P_PT_BASE_ADDR));

		writel(pg, sysmmuconp->regs + S5P_PT_BASE_ADDR);	/* Set sysmmu TTBase */
	} else {
		writel(sysmmuconp->tt_info->pgd_paddr, sysmmuconp->regs + S5P_PT_BASE_ADDR);	/* Set sysmmu TTBase */
	}

	sysmmu_debug("Done, %s\n", sysmmuconp->name);

	return 0;
}

int sysmmu_on(sysmmu_ips ips)
{
	unsigned int reg;

	sysmmu_controller_t *sysmmuconp;

	sysmmuconp = &s5p_sysmmu_cntlrs[ips];	/* sysmmu_get_info(ipnum, sysmmuconp); */

	sysmmu_debug("Start, %s\n", sysmmuconp->name);

	if (sysmmuconp == NULL) {
		printk(KERN_ERR "%s: failed to get ip's sysmmu info\n", __func__);
		return -EINVAL;
	}

	sysmmu_set_tablebase(ips);

	reg = readl(sysmmuconp->regs + S5P_MMU_CFG);
	reg |= (0x1<<0);		/* replacement policy : LRU */
	writel(reg, sysmmuconp->regs + S5P_MMU_CFG);

	reg = readl(sysmmuconp->regs + S5P_MMU_CTRL);
	reg |= ((0x1<<2)|(0x1<<0));	/* Enable interrupt, Enable MMU */

	printk(KERN_INFO "%s:%s sysmmuconp->regs + S5P_MMU_CTRL:0x%X, reg:0x%X\n", __func__, sysmmuconp->name, (unsigned int)(sysmmuconp->regs + S5P_MMU_CTRL), reg);

	writel(reg, sysmmuconp->regs + S5P_MMU_CTRL);

	sysmmuconp->enable = true;
	sysmmu_debug("Done, %s\n", sysmmuconp->name);

	return 0;
}

int sysmmu_off(sysmmu_ips ips)
{
	unsigned int reg;

	sysmmu_controller_t *sysmmuconp = NULL;

	if (ips > S5P_SYSMMU_TOTAL_IPNUM) {
		printk(KERN_ERR "%s: failed to get ips parameter\n", __func__);
		return -EINVAL;
	}

	sysmmuconp = &s5p_sysmmu_cntlrs[ips];	/* sysmmu_get_info(ipnum, sysmmuconp); */

	sysmmu_debug("Start, %s\n", sysmmuconp->name);

	reg = readl(sysmmuconp->regs + S5P_MMU_CFG);
	reg |= (0x1<<0);		/* replacement policy : LRU */
	writel(reg, sysmmuconp->regs + S5P_MMU_CFG);

	reg = readl(sysmmuconp->regs + S5P_MMU_CTRL);
	reg &= ~(0x1);			/* Disable MMU */

	writel(reg, sysmmuconp->regs + S5P_MMU_CTRL);

	sysmmuconp->enable = false;
	sysmmu_debug("Done, %s\n", sysmmuconp->name);

	return 0;
}

int sysmmu_tlb_invalidate(sysmmu_ips ips)
{
	unsigned int reg;
	sysmmu_controller_t *sysmmuconp = NULL;

	sysmmuconp = &s5p_sysmmu_cntlrs[ips];	/* sysmmu_get_info(ipnum, sysmmuconp); */

	sysmmu_debug("Start, %s\n", sysmmuconp->name);

	reg = readl(sysmmuconp->regs + S5P_MMU_CTRL);
	reg |= (0x1<<1);
	writel(reg, sysmmuconp->regs + S5P_MMU_CTRL);	/* Block MMU */

	writel(0x1, sysmmuconp->regs + S5P_MMU_FLUSH);	/* Flush_entry */

	reg = readl(sysmmuconp->regs + S5P_MMU_CTRL);
	reg &= ~(0x1<<1);
	writel(reg, sysmmuconp->regs + S5P_MMU_CTRL);	/* Un-block MMU */

	sysmmu_debug("Done, %s\n", sysmmuconp->name);

	return 0;
}

static int sysmmu_probe(struct platform_device *pdev)
{
	int i;
	int ret;
	struct resource *res;
	sysmmu_controller_t *sysmmuconp;
	sysmmu_table_type_t table_type;
	sysmmu_ips ips;

	sysmmu_debug("Start\n");

	for (i = 0; i < S5P_SYSMMU_TOTAL_IPNUM; i++) {
		sysmmuconp = &s5p_sysmmu_cntlrs[i];

		sysmmuconp->name = sysmmu_ips_name[i];

		/* memory region */
		res = platform_get_resource(pdev, IORESOURCE_MEM, i);
		if (!res) {
			printk(KERN_ERR "%s: failed to get resource\n", __func__);
			ret = -ENOENT;
			goto err_res;
		}

		sysmmuconp->mem = request_mem_region(res->start,
				((res->end) - (res->start)) + 1, pdev->name);
		if (!sysmmuconp->mem) {
			printk(KERN_ERR "%s: failed to request memory region\n", __func__);
			ret = -ENOMEM;
			goto err_region;
		}

		/* ioremap */
		sysmmuconp->regs = ioremap(res->start, res->end - res->start + 1);
		if (!sysmmuconp->regs) {
			printk(KERN_ERR "%s: failed to ioremap\n", __func__);
			ret = -ENOENT;
			goto err_map;
		}

		sysmmu_debug("loop - i:%d res->start:0x%x, res->end:0x%x, sysmmuconp->regs:0x%x, ip:%s\n", i, res->start, res->end, (unsigned int)(sysmmuconp->regs), sysmmuconp->name);

		/* irq */
		sysmmuconp->irq = platform_get_irq(pdev, i);
		if (!sysmmuconp->irq) {
			printk(KERN_ERR "%s: failed to get irq resource\n", __func__);
			ret = -ENOENT;
			goto err_map;
		}

		ret = request_irq(sysmmuconp->irq, sysmmu_irq, IRQF_DISABLED, pdev->name, sysmmuconp);
		if (ret) {
			printk(KERN_ERR "%s: failed to request irq\n", __func__);
			ret = -ENOENT;
			goto err_irq;
		}

		table_type = SHARED;
		/* table_type = SEPARATED; */
		ips = (sysmmu_ips)i;

		sysmmuconp->ips = ips;
		sysmmuconp->table_type = table_type;

		/* if (sysmmuconp->table_type == SEPARATED)
			sysmmu_init_table(sysmmuconp); */
	}

	printk("sysmmu_probe() Done\n");

	/* sysmmu_on(SYSMMU_G2D); */
	/* sysmmu_tlb_invalidate(SYSMMU_G2D); */
	/* sysmmu_off(SYSMMU_G2D); */

	return 0;

err_res:
err_region:
err_map:
err_irq:
	sysmmu_debug("Fail!!\n");
	return ret;
}

static int sysmmu_remove(struct platform_device *pdev)
{
	int ret = 0;
	/* sysmmu_controller_t *sysmmuconp; */

	/* sysmmuconp = &s5p_sysmmu_cntlrs[ips]; */	/* sysmmu_get_info(ipnum, sysmmuconp); */
	/* sysmmu_off(sysmmuconp); */
	return ret;
}

static int sysmmu_suspend(struct platform_device *pdev, pm_message_t state)
{
	int ret = 0;

	return ret;
}

static int sysmmu_resume(struct platform_device *pdev)
{
	int ret = 0;

	return ret;
}

/* pdev */
static struct platform_driver s5p_sysmmu_driver = {
	.probe = sysmmu_probe,
	.remove = sysmmu_remove,
	.suspend = sysmmu_suspend,
	.resume = sysmmu_resume,
	.driver = {
		.owner = THIS_MODULE,
		.name = "s5p-sysmmu",
	},
};

static int __init sysmmu_register(void)
{
	int ret;

	ret = platform_driver_register(&s5p_sysmmu_driver);

	if (ret)
		printk(KERN_ERR "%s: failed to register sysmmu driver\n", __func__);

	return ret;
}

static void __exit sysmmu_unregister(void)
{
	platform_driver_unregister(&s5p_sysmmu_driver);
}

module_init(sysmmu_register);
module_exit(sysmmu_unregister);

MODULE_AUTHOR("Donguk Ryu <du.ryu@samsung.com>");
MODULE_DESCRIPTION("Samsung System MMU driver");
MODULE_LICENSE("GPL");
