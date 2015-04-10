/*
 * Samsung C2C driver
 *
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Author: Kisang Lee <kisang80.lee@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/cma.h>
#include <linux/sysfs.h>
#ifdef ENABLE_C2CSTATE_TIMER
#include <linux/timer.h>
#endif
#ifdef CONFIG_C2C_IPC_ENABLE
#include <linux/vmalloc.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#endif
#include <asm/mach-types.h>
#include <linux/mm.h>

#include <mach/c2c.h>
#include <mach/regs-c2c.h>
#include <mach/regs-pmu.h>
#include <mach/regs-pmu5.h>
#include <mach/pmu.h>
#include <plat/cpu.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include "samsung-c2c.h"

#define DEBUG_PORT 1
#define XMM6262_WRITE_NVM

#ifdef XMM6262_WRITE_NVM
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/workqueue.h>
#include <linux/wakelock.h>
#define XMM6262_FW "/data/xmm6262_fw.bin"
#define FILE_NVM_STATIC "/data/nvm_static.bin"
#define FILE_NVM_DYNAMIC "/data/nvm_dynamic.bin"
#define FILE_NVM_CAL "/data/nvm_cal.bin"
enum cp_nvm_type {
	CP_NVM_STATIC = 0,
	CP_NVM_DYNAMIC = 1,
	CP_NVM_CAL = 2,	
};
#endif

void (*exynos_c2c_request_pwr_mode)(enum c2c_pwr_mode mode);
static void c2c_md_reset(void);

#ifdef ENABLE_C2CSTATE_TIMER
struct timer_list c2c_status_timer;

static void c2c_timer_func(unsigned long data)
{
	/* Check C2C state */
	struct exynos_c2c_platdata *pdata = (struct exynos_c2c_platdata *)data;
	static int old_state = 0xff;
	int current_state = 0;

	if (pdata->get_c2c_state() != NULL) {
		current_state = pdata->get_c2c_state();
		if (current_state != old_state) {
			dev_info(c2c_con.c2c_dev, "C2C state is chaged (0x%x --> 0x%x)\n",
				old_state, current_state);
			old_state = current_state;
		}
	}
	c2c_status_timer.expires = jiffies + (HZ/5);
	add_timer(&c2c_status_timer);
}
#endif

void c2c_reset_ops(void)
{
	/* This function will be only used for EVT0 or EVT0.1 */
	u32 set_clk = 0;

	if (c2c_con.opp_mode == C2C_OPP100)
		set_clk = c2c_con.clk_opp100;
	else if (c2c_con.opp_mode == C2C_OPP50)
		set_clk = c2c_con.clk_opp50;
	else if (c2c_con.opp_mode == C2C_OPP25)
		set_clk = c2c_con.clk_opp25;

	dev_info(c2c_con.c2c_dev, "c2c_reset_ops()\n");
	clk_set_rate(c2c_con.c2c_sclk, (set_clk + 1) * MHZ);
	c2c_set_func_clk(set_clk);

	/* First phase - C2C block reset */
	c2c_set_reset(C2C_CLEAR);
	c2c_set_reset(C2C_SET);
	/* Second phase - Clear clock gating */
	c2c_set_clock_gating(C2C_CLEAR);
	/* Third phase - Retention reg */
	c2c_writel(c2c_con.retention_reg, EXYNOS_C2C_IRQ_EN_SET1);
	c2c_writel(set_clk, EXYNOS_C2C_FCLK_FREQ);
	c2c_writel(set_clk, EXYNOS_C2C_RX_MAX_FREQ);
	/* Last phase - Set clock gating */
	c2c_set_clock_gating(C2C_SET);
}

static ssize_t c2c_ctrl_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	int ret = 0;

	ret = sprintf(buf, "C2C State");
	ret += sprintf(&buf[ret], "SysReg : 0x%x\n",
			readl(c2c_con.c2c_sysreg));
	ret += sprintf(&buf[ret], "Port Config : 0x%x\n",
			c2c_readl(EXYNOS_C2C_PORTCONFIG));
	ret += sprintf(&buf[ret], "FCLK_FREQ : %d\n",
			c2c_readl(EXYNOS_C2C_FCLK_FREQ));
	ret += sprintf(&buf[ret], "RX_MAX_FREQ : %d\n",
			c2c_readl(EXYNOS_C2C_RX_MAX_FREQ));
        ret += sprintf(&buf[ret], "TX_MAX_FREQ : %d\n",
                       c2c_readl(EXYNOS_C2C_TX_MAX_FREQ));
        ret += sprintf(&buf[ret], "RX_MAX_FREQ_ACK : %d\n",
                       c2c_readl(EXYNOS_C2C_TX_MAX_FREQ+4));
	ret += sprintf(&buf[ret], "IRQ_EN_SET1 : 0x%x\n",
			c2c_readl(EXYNOS_C2C_IRQ_EN_SET1));
	ret += sprintf(&buf[ret], "Get C2C sclk rate : %ld\n",
			clk_get_rate(c2c_con.c2c_sclk));
	ret += sprintf(&buf[ret], "Get C2C aclk rate : %ld\n",
			clk_get_rate(c2c_con.c2c_aclk));
        ret += sprintf(&buf[ret], "CLK_DIV_DMC1 is : %x\n",
                       readl(ioremap(0x10040504,4)));
        ret += sprintf(&buf[ret], "CP FCLK_FREQ : %d\n",
                       readl(ioremap(0x10580000+0x40,4)));
	ret += sprintf(&buf[ret], "CP RX_MAX_FREQ : %d\n",
                       readl(ioremap(0x10580000+0x44,4)));
        ret += sprintf(&buf[ret], "CP TX_MAX_FREQ : %d\n",
                       readl(ioremap(0x10580000+0x48,4))); 
        ret += sprintf(&buf[ret], "CP RX_MAX_FREQ_ACK : %d\n",
                       readl(ioremap(0x10580000+0x4c,4))); 

        
	return ret;
}
#ifdef XMM6262_WRITE_NVM
static int c2c_write_nvm_data(enum cp_nvm_type nvm)
{
	dma_addr_t phy_cpmem, vir_cpmem;
	struct file *fp_nvm;
        mm_segment_t fs;
	int ret = 0;

	/* CMA allocation to read NVM region */
	phy_cpmem = cma_alloc(c2c_con.c2c_dev, "c2c_shdmem", 64 * 1024 * 1024, 0);
	if (IS_ERR_VALUE(phy_cpmem)) {
		dev_info(c2c_con.c2c_dev, "CMA allocation is failed in write NVM.\n");
		return NULL;
	}
	vir_cpmem = phys_to_virt(phy_cpmem);

	/* File Open */
        fs = get_fs();
        set_fs(KERNEL_DS);

	switch(nvm) {
	case CP_NVM_STATIC: /* 128KB */
		fp_nvm = filp_open(FILE_NVM_STATIC, O_RDWR, 0);	
		ret = vfs_write(fp_nvm, vir_cpmem + 0x1F80000, 0x20000, &fp_nvm->f_pos);
		break;
	case CP_NVM_DYNAMIC: /* 256KB */
		fp_nvm = filp_open(FILE_NVM_DYNAMIC, O_RDWR, 0);	
		ret = vfs_write(fp_nvm, vir_cpmem + 0x1FA0000, 0x40000, &fp_nvm->f_pos);
		break;
	case CP_NVM_CAL: /* 128KB */
		fp_nvm = filp_open(FILE_NVM_CAL, O_RDWR, 0);	
		ret = vfs_write(fp_nvm, vir_cpmem + 0x1FE0000, 0x20000, &fp_nvm->f_pos);
		break;
	default :
		dev_info(c2c_con.c2c_dev, "Wrong NVM Type!!!\n");
	}
	filp_close(fp_nvm, NULL);
	set_fs(fs);
	cma_free(phy_cpmem);

	return ret;
}
#endif

static ssize_t c2c_ctrl_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	int ops_num, opp_val, req_clk;
	int len = 0;
	sscanf(buf, "%d", &ops_num);

	switch (ops_num) {
	case 1:
		c2c_reset_ops();
		break;
	case 2:
	case 3:
	case 4:
		opp_val = ops_num - 1;
		req_clk = 0;
		dev_info(c2c_con.c2c_dev, "Set current OPP mode (%d)\n", opp_val);

		if (opp_val == C2C_OPP100)
			req_clk = c2c_con.clk_opp100;
		else if (opp_val == C2C_OPP50)
			req_clk = c2c_con.clk_opp50;
		else if (opp_val == C2C_OPP25)
			req_clk = c2c_con.clk_opp25;

		if (opp_val == 0 || req_clk == 1) {
			dev_info(c2c_con.c2c_dev, "This mode is not reserved in OPP mode.\n");
		} else {
			c2c_set_clock_gating(C2C_CLEAR);
			if (c2c_con.opp_mode > opp_val) { /* increase case */
				clk_set_rate(c2c_con.c2c_sclk, (req_clk + 1) * MHZ);
				c2c_writel(req_clk, EXYNOS_C2C_FCLK_FREQ);
				c2c_set_func_clk(req_clk);
				c2c_writel(req_clk, EXYNOS_C2C_RX_MAX_FREQ);
			} else if (c2c_con.opp_mode < opp_val) { /* decrease case */
				c2c_writel(req_clk, EXYNOS_C2C_RX_MAX_FREQ);
				clk_set_rate(c2c_con.c2c_sclk, (req_clk + 1) * MHZ);
				c2c_writel(req_clk, EXYNOS_C2C_FCLK_FREQ);
				c2c_set_func_clk(req_clk);
			} else{
				dev_info(c2c_con.c2c_dev, "Requested same OPP mode\n");
			}
			c2c_con.opp_mode = opp_val;
			c2c_set_clock_gating(C2C_SET);
		}

		dev_info(c2c_con.c2c_dev, "Get C2C sclk rate : %ld\n",
					clk_get_rate(c2c_con.c2c_sclk));
		dev_info(c2c_con.c2c_dev, "Get C2C aclk rate : %ld\n",
					clk_get_rate(c2c_con.c2c_aclk));
		break;


	case 5: /* xmm6262 reset */ 
		c2c_md_reset();
		break;
#ifdef XMM6262_WRITE_NVM
	case 6: /* update static nvm data */
		len = c2c_write_nvm_data(CP_NVM_STATIC);
		dev_info(c2c_con.c2c_dev, "Write Static NVM(%d bytes)\n", len);
		break;
	case 7: /* update dynaic nvm data */
		len = c2c_write_nvm_data(CP_NVM_DYNAMIC);
		dev_info(c2c_con.c2c_dev, "Write Dynamic NVM(%d bytes)\n", len);
		break;
	case 8: /* update calibration nvm data */
		len = c2c_write_nvm_data(CP_NVM_CAL);
		dev_info(c2c_con.c2c_dev, "Write Calibration NVM(%d bytes)\n", len);
		break;
	case 9: /* update all nvm data */
		len = c2c_write_nvm_data(CP_NVM_STATIC);
		dev_info(c2c_con.c2c_dev, "Write Static NVM(%d bytes)\n", len);
		len = c2c_write_nvm_data(CP_NVM_DYNAMIC);
		dev_info(c2c_con.c2c_dev, "Write Dynamic NVM(%d bytes)\n", len);
		len = c2c_write_nvm_data(CP_NVM_CAL);
		dev_info(c2c_con.c2c_dev, "Write Calibration NVM(%d bytes)\n", len);
		break;
#endif
	default:
		dev_info(c2c_con.c2c_dev, "Wrong C2C operation number\n");
		dev_info(c2c_con.c2c_dev, "---C2C Operation Number---\n");
		dev_info(c2c_con.c2c_dev, "1. C2C Reset\n");
		dev_info(c2c_con.c2c_dev, "2. Set OPP25\n");
		dev_info(c2c_con.c2c_dev, "3. Set OPP50\n");
		dev_info(c2c_con.c2c_dev, "4. Set OPP100\n");
                dev_info(c2c_con.c2c_dev, "5. XMM6262 Reset\n");
#ifdef XMM6262_WRITE_NVM
                dev_info(c2c_con.c2c_dev, "6. Update XMM6262 static nvm data\n");
                dev_info(c2c_con.c2c_dev, "7. Update XMM6262 dynamic nvm data\n");
                dev_info(c2c_con.c2c_dev, "8. Update XMM6262 calibration nvm data\n");
                dev_info(c2c_con.c2c_dev, "9. Update XMM6262 all nvm data\n");
#endif
		break;
	}
	return count;
}

static DEVICE_ATTR(c2c_ctrl, 0644, c2c_ctrl_show, c2c_ctrl_store);
#if DEBUG_PORT
static ssize_t debug_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
        return 0;
}

static ssize_t debug_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
        unsigned int arg,value,*addr;
        int opp_val, req_clk;
	int len = 0;
	sscanf(buf, "%x", &arg);
        //        printk("Contet at addr %x .\n",addr);
        addr = ioremap(arg,4);
        value = readl(addr);
        printk("Content at addr %x is %x.\n",arg,value);
        iounmap(addr);
        return count;
}

static DEVICE_ATTR(debug_attr, 0644, debug_show, debug_store);
#endif

int c2c_open(struct inode *inode, struct file *filp)
{
	/* This function is not needed.(Test Function) */
	dev_info(c2c_con.c2c_dev, "C2C chrdrv Opened.\n");

	return 0;
}

int c2c_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long physical = C2C_CP_RGN_ADDR + (vma->vm_pgoff << PAGE_SHIFT);
	unsigned long size = vma->vm_end - vma->vm_start;

	vma->vm_flags |= (VM_IO | VM_RESERVED);

	physical = __phys_to_pfn(physical);

	if (remap_pfn_range(vma, vma->vm_start, physical, size,
			vma->vm_page_prot)) {
		dev_info(c2c_con.c2c_dev, KERN_ERR "MMAP remap_pfn_range error!\n");
		return -EAGAIN;
	}

	printk("vm_pgoff		[%08x]\n", vma->vm_pgoff << PAGE_SHIFT);
	printk("vm_start		[%08x]\n", vma->vm_start);
	printk("vm_end			[%08x]\n", vma->vm_end);
	printk("vm_flags		[%08x]\n", vma->vm_flags);

	return 0;
}

static long c2c_ioctl(struct file *filp, unsigned int cmd,
		unsigned long arg)
{
 	switch (cmd) {
	case 1:
		c2c_reset_ops();
		break;
	case 5: /* cp reset */  
		c2c_md_reset();
		break;
        default:
		dev_info(c2c_con.c2c_dev, "Wrong C2C operation number\n");
        }
	return 0;
}

static const struct file_operations c2c_fops = {
	.owner	= THIS_MODULE,
	.unlocked_ioctl	= c2c_ioctl,
	.open	= c2c_open,
	.mmap	= c2c_mmap,
};

static struct miscdevice char_dev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= C2C_DEV_NAME,
	.fops	= &c2c_fops
};

static int c2c_set_sharedmem(enum c2c_shrdmem_size size, u32 addr)
{
	dev_info(c2c_con.c2c_dev, "Set BaseAddr(0x%x) and Size(%d)\n",
				addr, 1 << (2 + size));

	/* Set DRAM Base Addr & Size */
	c2c_set_shdmem_size(size);
	c2c_set_base_addr((addr >> 22));

	return 0;
}

static void c2c_set_interrupt(u32 genio_num, enum c2c_interrupt set_int)
{
	u32 cur_int_reg, cur_lev_reg;

	cur_int_reg = c2c_readl(EXYNOS_C2C_GENO_INT);
	cur_lev_reg = c2c_readl(EXYNOS_C2C_GENO_LEVEL);

	switch (set_int) {
	case C2C_INT_TOGGLE:
		cur_int_reg &= ~(0x1 << genio_num);
		c2c_writel(cur_int_reg, EXYNOS_C2C_GENO_INT);
		break;
	case C2C_INT_HIGH:
		cur_int_reg |= (0x1 << genio_num);
		cur_lev_reg |= (0x1 << genio_num);
		c2c_writel(cur_int_reg, EXYNOS_C2C_GENO_INT);
		c2c_writel(cur_lev_reg, EXYNOS_C2C_GENO_LEVEL);
		break;
	case C2C_INT_LOW:
		cur_int_reg |= (0x1 << genio_num);
		cur_lev_reg &= ~(0x1 << genio_num);
		c2c_writel(cur_int_reg, EXYNOS_C2C_GENO_INT);
		c2c_writel(cur_lev_reg, EXYNOS_C2C_GENO_LEVEL);
		break;
	}
}

static irqreturn_t c2c_sscm0_irq(int irq, void *data)
{
	/* TODO : This function will be used other type boards */
	return IRQ_HANDLED;
}

static irqreturn_t c2c_sscm1_irq(int irq, void *data)
{
	/* TODO : It is just temporary code. It will be modified. */
	u32 raw_irq, latency_val, opp_val, req_clk;
	raw_irq = c2c_readl(EXYNOS_C2C_IRQ_EN_STAT1);

#ifdef CONFIG_C2C_IPC_ENABLE
	if (raw_irq & 0x1) {
		dev_info(c2c_con.c2c_dev, "IPC interrupt occured : GENO[0]\n");
		if (c2c_con.hd.handler)
			c2c_con.hd.handler(c2c_con.hd.data);

		/* Interrupt Clear */
		c2c_writel(0x1, EXYNOS_C2C_IRQ_EN_STAT1);
	}
#endif
	if ((raw_irq >> C2C_GENIO_OPP_INT) & 1) { /* OPP Change */
		/*
		    OPP mode GENI/O bit definition[29:27]
		    OPP100 GENI/O[29:28] : 1 1
		    OPP50  GENI/O[29:28] : 1 0
		    OPP25  GENI/O[29:28] : 0 1
		    GENI[27] is only used for making interrupt.
		*/
		opp_val = (c2c_readl(EXYNOS_C2C_GENO_STATUS) >> 28) & 3;
		req_clk = 0;
		dev_info(c2c_con.c2c_dev, "OPP interrupt occured (%d)\n", opp_val);

		if (opp_val == C2C_OPP100)
			req_clk = c2c_con.clk_opp100;
		else if (opp_val == C2C_OPP50)
			req_clk = c2c_con.clk_opp50;
		else if (opp_val == C2C_OPP25)
			req_clk = c2c_con.clk_opp25;

		if (opp_val == 0 || req_clk == 1) {
			dev_info(c2c_con.c2c_dev, "This mode is not reserved in OPP mode.\n");
		} else {
			if (c2c_con.opp_mode > opp_val) { /* increase case */
				clk_set_rate(c2c_con.c2c_sclk, (req_clk + 1) * MHZ);
				c2c_writel(req_clk, EXYNOS_C2C_FCLK_FREQ);
				c2c_set_func_clk(req_clk);
				c2c_writel(req_clk, EXYNOS_C2C_RX_MAX_FREQ);
			} else if (c2c_con.opp_mode < opp_val) { /* decrease case */
				c2c_writel(req_clk, EXYNOS_C2C_RX_MAX_FREQ);
				clk_set_rate(c2c_con.c2c_sclk, (req_clk + 1) * MHZ);
				c2c_writel(req_clk, EXYNOS_C2C_FCLK_FREQ);
				c2c_set_func_clk(req_clk);
			} else{
				dev_info(c2c_con.c2c_dev, "Requested same OPP mode\n");
			}
			c2c_con.opp_mode = opp_val;
		}

		/* Interrupt Clear */
		c2c_writel((0x1 << C2C_GENIO_OPP_INT), EXYNOS_C2C_IRQ_EN_STAT1);
	}

	/* Memory I/F latency change */
	if ((raw_irq >> C2C_GENIO_LATENCY_INT) & 1) {
		latency_val = (c2c_readl(EXYNOS_C2C_GENO_STATUS) >> 30) & 3;
                dev_info(c2c_con.c2c_dev,"C2C Latency INT occured\n");	//ylk
		switch (latency_val) {
		case 3:
			dev_info(c2c_con.c2c_dev, "Set Min latency\n");
			if (exynos_c2c_request_pwr_mode != NULL)
				exynos_c2c_request_pwr_mode(MIN_LATENCY);
			break;
		case 1:
			dev_info(c2c_con.c2c_dev, "Set Short latency\n");
			if (exynos_c2c_request_pwr_mode != NULL)
				exynos_c2c_request_pwr_mode(SHORT_LATENCY);
			break;
		case 0:
			dev_info(c2c_con.c2c_dev, "Set Max latency\n");
			if (exynos_c2c_request_pwr_mode != NULL)
				exynos_c2c_request_pwr_mode(MAX_LATENCY);
			break;
		}
		/* Interrupt Clear */
		c2c_writel((0x1 << C2C_GENIO_LATENCY_INT), EXYNOS_C2C_IRQ_EN_STAT1);
	}

	return IRQ_HANDLED;
}

static void set_c2c_device(struct platform_device *pdev)
{
	struct exynos_c2c_platdata *pdata = pdev->dev.platform_data;
	u32 default_clk;

	c2c_con.c2c_sysreg = pdata->c2c_sysreg;
	c2c_con.rx_width = pdata->rx_width;
	c2c_con.tx_width = pdata->tx_width;
	c2c_con.clk_opp100 = pdata->clk_opp100;
	c2c_con.clk_opp50 = pdata->clk_opp50;
	c2c_con.clk_opp25 = pdata->clk_opp25;
	c2c_con.opp_mode = pdata->default_opp_mode;
#ifdef CONFIG_C2C_IPC_ENABLE
	c2c_con.shd_pages = NULL;
	c2c_con.hd.data = NULL;
	c2c_con.hd.handler = NULL;
#endif
	c2c_con.c2c_sclk = clk_get(&pdev->dev, "sclk_c2c");
	c2c_con.c2c_aclk = clk_get(&pdev->dev, "aclk_c2c");

	if (soc_is_exynos4212())
		exynos_c2c_request_pwr_mode = exynos4_c2c_request_pwr_mode;
	else if (soc_is_exynos4412()) {
		exynos_c2c_request_pwr_mode = exynos4_c2c_request_pwr_mode;
		if (samsung_rev() >= EXYNOS4412_REV_1_0)
			writel(C2C_SYSREG_DEFAULT, c2c_con.c2c_sysreg);
	} else if (soc_is_exynos5250())
		exynos_c2c_request_pwr_mode = NULL;

	/* Set clock to default mode */
	if (c2c_con.opp_mode == C2C_OPP100)
		default_clk = c2c_con.clk_opp100;
	else if (c2c_con.opp_mode == C2C_OPP50)
		default_clk = c2c_con.clk_opp50;
	else if (c2c_con.opp_mode == C2C_OPP25)
		default_clk = c2c_con.clk_opp25;
	else {
		dev_info(c2c_con.c2c_dev, "Default OPP mode is not selected.\n");
		c2c_con.opp_mode = C2C_OPP50;
		default_clk = c2c_con.clk_opp50;
	}

	clk_set_rate(c2c_con.c2c_sclk, (default_clk + 1)  * MHZ);
	clk_set_rate(c2c_con.c2c_aclk, ((default_clk / 2) + 1) * MHZ);

        //ylk 20120307
        dev_info(c2c_con.c2c_dev,"CLK_DIV_DMC1 is %x\n",readl(ioremap(0x10040504,4)));

        dev_info(c2c_con.c2c_dev, "Get C2C sclk rate : %ld\n",
				clk_get_rate(c2c_con.c2c_sclk));
	dev_info(c2c_con.c2c_dev, "Get C2C aclk rate : %ld\n",
				clk_get_rate(c2c_con.c2c_aclk));
	if (pdata->setup_gpio)
		pdata->setup_gpio(pdata->rx_width, pdata->tx_width);

	c2c_set_sharedmem(pdata->shdmem_size, pdata->shdmem_addr);

	/* Set SYSREG to memdone */
	c2c_set_memdone(C2C_SET);
	c2c_set_clock_gating(C2C_CLEAR);

	/* Set C2C clock register to OPP50 */
	c2c_writel(default_clk, EXYNOS_C2C_FCLK_FREQ);
	c2c_writel(default_clk, EXYNOS_C2C_RX_MAX_FREQ);
	c2c_set_func_clk(default_clk);

	/* Set C2C buswidth */
	c2c_writel(((pdata->rx_width << 4) | (pdata->tx_width)),
					EXYNOS_C2C_PORTCONFIG);
	c2c_set_tx_buswidth(pdata->tx_width);
	c2c_set_rx_buswidth(pdata->rx_width);

	/* Enable all of GENI/O Interrupt */
	c2c_writel((0x1 << C2C_GENIO_OPP_INT), EXYNOS_C2C_IRQ_EN_SET1);
	c2c_con.retention_reg = (0x1 << C2C_GENIO_OPP_INT);

	if (exynos_c2c_request_pwr_mode != NULL)
		exynos_c2c_request_pwr_mode(MAX_LATENCY);

	c2c_set_interrupt(C2C_GENIO_OPP_INT, C2C_INT_HIGH);

	dev_info(c2c_con.c2c_dev, "Port Config : 0x%x\n",
				c2c_readl(EXYNOS_C2C_PORTCONFIG));
	dev_info(c2c_con.c2c_dev, "FCLK_FREQ register : %d\n",
				c2c_readl(EXYNOS_C2C_FCLK_FREQ));
	dev_info(c2c_con.c2c_dev, "RX_MAX_FREQ register : %d\n",
				c2c_readl(EXYNOS_C2C_RX_MAX_FREQ));
        dev_info(c2c_con.c2c_dev, "TX_MAX_FREQ register : %d\n",
                 c2c_readl(EXYNOS_C2C_TX_MAX_FREQ));
	dev_info(c2c_con.c2c_dev, "IRQ_EN_SET1 register : 0x%x\n",
				c2c_readl(EXYNOS_C2C_IRQ_EN_SET1));

	c2c_set_clock_gating(C2C_SET);
}

#ifdef CONFIG_C2C_IPC_ENABLE
void __iomem *c2c_request_cp_region(unsigned int cp_addr,
		unsigned int size)
{
	dma_addr_t phy_cpmem;

	phy_cpmem = cma_alloc(c2c_con.c2c_dev, "c2c_shdmem", size, 0);
	if (IS_ERR_VALUE(phy_cpmem)) {
		dev_info(c2c_con.c2c_dev, KERN_ERR "C2C CMA Alloc Error!!!");
		return NULL;
	}

	return phys_to_virt(phy_cpmem);
}
EXPORT_SYMBOL(c2c_request_cp_region);

void c2c_release_cp_region(void *rgn)
{
	dma_addr_t phy_cpmem;

	phy_cpmem = virt_to_phys(rgn);

	cma_free(phy_cpmem);
}
EXPORT_SYMBOL(c2c_release_cp_region);

void __iomem *c2c_request_sh_region(unsigned int sh_addr,
		unsigned int size)
{
	int i;
	struct page **pages;
	void *pv;

	pages = kmalloc((size >> PAGE_SHIFT) * sizeof(*pages), GFP_KERNEL);
	for (i = 0; i < (size >> PAGE_SHIFT); i++) {
		pages[i] = phys_to_page(sh_addr);
		sh_addr += PAGE_SIZE;
	}

	c2c_con.shd_pages = (void *)pages;

	pv = vmap(pages, size >> PAGE_SHIFT, VM_MAP,
					pgprot_noncached(PAGE_KERNEL));

	return (void __iomem *)pv;
}
EXPORT_SYMBOL(c2c_request_sh_region);

void c2c_release_sh_region(void *rgn)
{
	vunmap(rgn);
	kfree(c2c_con.shd_pages);
	c2c_con.shd_pages = NULL;
}
EXPORT_SYMBOL(c2c_release_sh_region);

int c2c_register_handler(void (*handler)(void *), void *data)
{
	if (!handler)
		return -EINVAL;

	c2c_con.hd.data = data;
	c2c_con.hd.handler = handler;

	c2c_reset_interrupt();

	return 0;
}
EXPORT_SYMBOL(c2c_register_handler);

int c2c_unregister_handler(void (*handler)(void *))
{
	if (!handler || (c2c_con.hd.handler != handler))
		return -EINVAL;

	c2c_con.hd.data = NULL;
	c2c_con.hd.handler = NULL;
	return 0;
}
EXPORT_SYMBOL(c2c_unregister_handler);

void c2c_send_interrupt(void)
{
	c2c_writel(c2c_readl(EXYNOS_C2C_GENI_CONTROL) ^ 0x1,
			EXYNOS_C2C_GENI_CONTROL);
}
EXPORT_SYMBOL(c2c_send_interrupt);

void c2c_reset_interrupt(void)
{
	c2c_writel(c2c_readl(EXYNOS_C2C_IRQ_EN_SET1) | 0x1,
			EXYNOS_C2C_IRQ_EN_SET1);
	c2c_con.retention_reg |= 0x1;
}
EXPORT_SYMBOL(c2c_reset_interrupt);
#endif
static void c2c_md_reset(void)
{
#ifdef CONFIG_SMM6260_MODEM
	printk("It is not suggested to reset modem in C2C.(xujie)\n");
#else
        if(gpio_request(EXYNOS4_GPC0(2) ,"MD_RSTN"))
        {
          printk("Request GPIO GPC0_2 err!\r\n");
          goto poweron_err;
        }
        else
        {
          gpio_direction_output(EXYNOS4_GPC0(2),1);
        }

        if(gpio_request(EXYNOS4_GPL2(1) ,"MD_RESETBB"))
        { 
          printk("Request GPIO GPL2_1 err!\r\n");
          goto poweron_err;
        }
        else
        {
          gpio_direction_output(EXYNOS4_GPL2(1),1);
        }

        mdelay(5);

        /* generate a pulse for GPC0_0 to boot Modem */
        if(gpio_request(EXYNOS4_GPC0(0) ,"MD_PWON"))
        {
          printk("Request GPIO GPC0_0 err!\r\n");
          goto poweron_err;
        }
        else
        {
          gpio_direction_output(EXYNOS4_GPC0(0),1);
        }

        mdelay(5);

        printk("****************************************\n");
        printk("* 6260  power on successfully!!!********\n");
        printk("****************************************\n");

        gpio_free(EXYNOS4_GPC0(0));
        gpio_free(EXYNOS4_GPL2(1));
        gpio_free(EXYNOS4_GPC0(2));
#endif
        return ;

poweron_err:
        printk("*** 6260  power on failed!!! ***\n");
}

static int __devinit samsung_c2c_probe(struct platform_device *pdev)
{
	struct exynos_c2c_platdata *pdata = pdev->dev.platform_data;
	struct resource *res = NULL;
	struct resource *res1 = NULL;
	int sscm_irq0, sscm_irq1;
	int err = 0;

        c2c_con.c2c_dev = &pdev->dev;

	/* resource for AP's SSCM region */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "no memory resource defined(AP's SSCM)\n");
		return -ENOENT;
	}
	res = request_mem_region(res->start, resource_size(res), pdev->name);
	if (!res) {
		dev_err(&pdev->dev, "failded to request memory resource(AP)\n");
		return -ENOENT;
	}
	pdata->ap_sscm_addr = ioremap(res->start, resource_size(res));
	if (!pdata->ap_sscm_addr) {
		dev_err(&pdev->dev, "failded to request memory resource(AP)\n");
		goto release_ap_sscm;
	}
	c2c_con.ap_sscm_addr = pdata->ap_sscm_addr;

	/* resource for CP's SSCM region */
	res1 = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res1) {
		dev_err(&pdev->dev, "no memory resource defined(AP's SSCM)\n");
		goto unmap_ap_sscm;
	}
	res1 = request_mem_region(res1->start, resource_size(res1), pdev->name);
	if (!res1) {
		dev_err(&pdev->dev, "failded to request memory resource(AP)\n");
		goto unmap_ap_sscm;
	}
	pdata->cp_sscm_addr = ioremap(res1->start, resource_size(res1));
	if (!pdata->cp_sscm_addr) {
		dev_err(&pdev->dev, "failded to request memory resource(CP)\n");
		goto release_cp_sscm;
	}
	c2c_con.cp_sscm_addr = pdata->cp_sscm_addr;

	/* Request IRQ */
	sscm_irq0 = platform_get_irq(pdev, 0);
	if (sscm_irq0 < 0) {
		dev_err(&pdev->dev, "no irq specified\n");
		goto unmap_cp_sscm;
	}
	err = request_irq(sscm_irq0, c2c_sscm0_irq, 0, pdev->name, pdev);
	if (err) {
		dev_err(&pdev->dev, "Can't request SSCM0 IRQ\n");
		goto unmap_cp_sscm;
	}
	/* SSCM0 irq will be only used for master(CP) device */
	disable_irq(sscm_irq0);

	sscm_irq1 = platform_get_irq(pdev, 1);
	if (sscm_irq1 < 0) {
		dev_err(&pdev->dev, "no irq specified\n");
		goto release_sscm_irq0;
	}
	err = request_irq(sscm_irq1, c2c_sscm1_irq, 1, pdev->name, pdev);
	if (err) {
		dev_err(&pdev->dev, "Can't request SSCM1 IRQ\n");
		goto release_sscm_irq0;
	}

	err = misc_register(&char_dev);
	if (err) {
		dev_err(&pdev->dev, "Can't register chrdev!\n");
		goto release_sscm_irq0;
	}

	set_c2c_device(pdev);

#ifdef ENABLE_C2CSTATE_TIMER
	/* Timer for debugging to check C2C state */
	init_timer(&c2c_status_timer);
	c2c_status_timer.expires = jiffies + HZ;
	c2c_status_timer.data = (unsigned long)pdata;
	c2c_status_timer.function = &c2c_timer_func;
	add_timer(&c2c_status_timer);
#endif

	/* Create sysfs file for C2C debug */
	err = device_create_file(&pdev->dev, &dev_attr_c2c_ctrl);
	if (err) {
		dev_err(&pdev->dev, "Failed to create sysfs for C2C\n");
		goto release_sscm_irq1;
	}

        if(c2c_con.c2c_sysreg) 
          printk("samsung-c2c: the AP side C2C SYSREG = %x\n",*(int *)c2c_con.c2c_sysreg);

        printk("0x1004109C: %x, 0x10042000: %x\n", readl(ioremap(0x1004109C,4)),readl(ioremap(0x10042000,4)));
#if DEBUG_PORT
        device_create_file(&pdev->dev,&dev_attr_debug_attr);
#endif        
        return 0;

release_sscm_irq1:
	free_irq(sscm_irq1, pdev);

release_sscm_irq0:
	free_irq(sscm_irq0, pdev);

unmap_cp_sscm:
	iounmap(pdata->cp_sscm_addr);

release_cp_sscm:
	release_mem_region(res1->start, resource_size(res1));

unmap_ap_sscm:
	iounmap(pdata->ap_sscm_addr);

release_ap_sscm:
	release_mem_region(res->start, resource_size(res));

	return err;
}

static int __devexit samsung_c2c_remove(struct platform_device *pdev)
{
	/* TODO */
	return 0;
}

#ifdef CONFIG_PM
static int samsung_c2c_suspend(struct platform_device *dev, pm_message_t pm)
{
	/* TODO */
	return 0;
}

static int samsung_c2c_resume(struct platform_device *dev)
{
        struct exynos_c2c_platdata *pdata = dev->dev.platform_data;

	if ((soc_is_exynos4212() || soc_is_exynos4412())
		&& samsung_rev() == EXYNOS4412_REV_0) {
		/* Set SYSREG */
		c2c_set_sharedmem(pdata->shdmem_size, pdata->shdmem_addr);
		c2c_set_memdone(C2C_SET);
	} else if (soc_is_exynos5250()) {
		/* Set SYSREG */
		c2c_set_sharedmem(pdata->shdmem_size, pdata->shdmem_addr);
		c2c_set_memdone(C2C_SET);
	}

	return 0;
}
#else
#define samsung_c2c_suspend NULL
#define samsung_c2c_resume NULL
#endif

static struct platform_driver samsung_c2c_driver = {
	.probe		= samsung_c2c_probe,
	.remove		= __devexit_p(samsung_c2c_remove),
	.suspend	= samsung_c2c_suspend,
	.resume		= samsung_c2c_resume,
	.driver		= {
		.name	= "samsung-c2c",
		.owner	= THIS_MODULE,
	},
};

static int __init samsung_c2c_init(void)
{
	return platform_driver_register(&samsung_c2c_driver);
}
module_init(samsung_c2c_init);

static void __exit samsung_c2c_exit(void)
{
	platform_driver_unregister(&samsung_c2c_driver);
}
module_exit(samsung_c2c_exit);

MODULE_DESCRIPTION("Samsung C2C driver");
MODULE_AUTHOR("Kisang Lee <kisang80.lee@samsung.com>");
MODULE_LICENSE("GPL");
