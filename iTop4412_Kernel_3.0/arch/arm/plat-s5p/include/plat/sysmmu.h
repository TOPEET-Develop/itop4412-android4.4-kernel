/* linux/arch/arm/plat-s5p/include/plat/sysmmu.h
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Samsung System MMU driver for S5P platform
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM__PLAT_SYSMMU_H
#define __ASM__PLAT_SYSMMU_H

#if defined(CONFIG_TC4_GB)
/* debug macro */
#ifdef CONFIG_S5P_SYSMMU_DEBUG
#define sysmmu_debug(fmt, arg...)	printk(KERN_INFO "[%s] " fmt, __FUNCTION__, ## arg)
#else
#define sysmmu_debug(fmt, arg...)	do { } while (0)
#endif

#define S5P_SYSMMU_TOTAL_IPNUM          (14)

struct s5p_sysmmu_platdata {

	unsigned int version;
};


typedef enum {
	SYSMMU_G2D     = 0,
	SYSMMU_SSS      = 1,
	SYSMMU_FIMC0    = 2,
	SYSMMU_FIMC1    = 3,
	SYSMMU_FIMC2    = 4,
	SYSMMU_FIMC3    = 5,
	SYSMMU_JPEG     = 6,
	SYSMMU_FIMD0    = 7,
	SYSMMU_GPS    = 8,
	SYSMMU_ROTATOR     = 9,
	SYSMMU_MDMA2      = 10,
	SYSMMU_TV  = 11,
	SYSMMU_MFC_L    = 12,
	SYSMMU_MFC_R       = 13,
	//SYSMMU_MFC_L    = 14,
	//SYSMMU_MFC_R    = 15,
} sysmmu_ips;

/*
* SysMMU enum
*/
typedef enum sysmmu_pagetable_type sysmmu_table_type_t;
enum sysmmu_pagetable_type {
	SHARED,
	SEPARATED,
};

/*
 * SysMMU struct
*/
typedef struct sysmmu_tt_info sysmmu_tt_info_t;
typedef struct sysmmu_controller sysmmu_controller_t;

struct sysmmu_tt_info {
	unsigned long *pgd;
	unsigned long pgd_paddr;
	unsigned long *pte;
};

struct sysmmu_controller {
	const char		*name;
	void __iomem		*regs;		/* channels registers */
	unsigned int		irq;		/* channel irq */
	sysmmu_ips              ips;            /* SysMMU controller type */
	sysmmu_table_type_t	table_type;	/* SysMMU table type: shared or separated */
	sysmmu_tt_info_t	*tt_info;	/* Translation Table Info. */
	struct resource *mem;
	struct device *dev;
	bool			enable;		/* SysMMU controller enable - true : enable */
};

int sysmmu_on(sysmmu_ips ips);
int sysmmu_off(sysmmu_ips ips);
int sysmmu_set_tablebase_pgd(sysmmu_ips ips, unsigned long pgd);
int sysmmu_tlb_invalidate(sysmmu_ips ips);


//int s5p_sysmmu_enable(struct device *owner, unsigned long pgd);
//void s5p_sysmmu_disable(struct device *owner);
//void s5p_sysmmu_set_tablebase_pgd(struct device *owner, unsigned long pgd);
//void s5p_sysmmu_tlb_invalidate(struct device *owner);



#else

#include <linux/list.h>
#include <linux/atomic.h>
#include <linux/spinlock.h>

enum S5P_SYSMMU_INTERRUPT_TYPE {
	SYSMMU_PAGEFAULT,
	SYSMMU_AR_MULTIHIT,
	SYSMMU_AW_MULTIHIT,
	SYSMMU_BUSERROR,
	SYSMMU_AR_SECURITY,
	SYSMMU_AR_ACCESS,
	SYSMMU_AW_SECURITY,
	SYSMMU_AW_PROTECTION, /* 7 */
	SYSMMU_FAULT_UNKNOWN,
	SYSMMU_FAULTS_NUM
};

/*
 * @itype: type of fault.
 * @pgtable_base: the physical address of page table base. This is 0 if @itype
 *                is SYSMMU_BUSERROR.
 * @fault_addr: the device (virtual) address that the System MMU tried to
 *             translated. This is 0 if @itype is SYSMMU_BUSERROR.
 */
typedef int (*s5p_sysmmu_fault_handler_t)(enum S5P_SYSMMU_INTERRUPT_TYPE itype,
			unsigned long pgtable_base, unsigned long fault_addr);

#ifdef CONFIG_S5P_SYSTEM_MMU
/**
 * s5p_sysmmu_enable() - enable system mmu
 * @owner: The device whose System MMU is about to be enabled.
 * @pgd: Base physical address of the 1st level page table
 *
 * This function enable system mmu to transfer address
 * from virtual address to physical address.
 * Return non-zero if it fails to enable System MMU.
 */
int s5p_sysmmu_enable(struct device *owner, unsigned long pgd);

/**
 * s5p_sysmmu_disable() - disable sysmmu mmu of ip
 * @owner: The device whose System MMU is about to be disabled.
 *
 * This function disable system mmu to transfer address
 * from virtual address to physical address
 */
void s5p_sysmmu_disable(struct device *owner);

/**
 * s5p_sysmmu_set_tablebase_pgd() - set page table base to refer page table
 * @owner: The device whose System MMU.
 * @pgd: The page table base address.
 *
 * This function set page table base address
 * When system mmu transfer address from virtaul address to physical address,
 * system mmu refer address information from page table
 */
void s5p_sysmmu_set_tablebase_pgd(struct device *owner, unsigned long pgd);

/**
 * s5p_sysmmu_tlb_invalidate() - flush all TLB entry in system mmu
 * @owner: The device whose System MMU.
 *
 * This function flush all TLB entry in system mmu
 */
void s5p_sysmmu_tlb_invalidate(struct device *owner);

/** s5p_sysmmu_set_fault_handler() - Fault handler for System MMUs
 * Called when interrupt occurred by the System MMUs
 * The device drivers of peripheral devices that has a System MMU can implement
 * a fault handler to resolve address translation fault by System MMU.
 * The meanings of return value and parameters are described below.

 * return value: non-zero if the fault is correctly resolved.
 *         zero if the fault is not handled.
 */
void s5p_sysmmu_set_fault_handler(struct device *sysmmu,
					s5p_sysmmu_fault_handler_t handler);
#else /* !CONFIG_S5P_SYSTEM_MMU */
#define s5p_sysmmu_enable(owner, pgd) do { } while (0)
#define s5p_sysmmu_disable(owner) do { } while (0)
#define s5p_sysmmu_set_tablebase_pgd(owner, pgd) do { } while (0)
#define s5p_sysmmu_tlb_invalidate(owner) do { } while (0)
#define s5p_sysmmu_set_fault_handler(sysmmu, handler) do { } while (0)

#endif

#endif //CONFIG_TC4_GB

#endif /* __ASM_PLAT_SYSMMU_H */
