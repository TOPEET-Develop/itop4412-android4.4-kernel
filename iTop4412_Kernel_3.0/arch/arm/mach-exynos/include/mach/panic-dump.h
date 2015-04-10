/* linux/arch/arm/mach-exynos4/include/mach/memory.h
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS4 - Memory definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_PANIC_DUMP_H
#define __ASM_PANIC_DUMP_H __FILE__
#include <mach/regs-pmu.h>
#define PANIC_MEM_POOL_ADDR_PA	0x50000000
#define PANIC_MEM_POOL_SIZE		0x100000	// 9MB ring buffer 1.125M for each panic

#define PANIC_MEM_POOL_LOGGER_ADDR1_PA	(PANIC_MEM_POOL_ADDR_PA+PANIC_MEM_POOL_SIZE)
#define PANIC_MEM_POOL_LOGGER_ADDR2_PA	(PANIC_MEM_POOL_LOGGER_ADDR1_PA+PANIC_MEM_POOL_SIZE)
#define PANIC_MEM_POOL_STEP	 0x80000 //0x120000 
#define PANIC_MEM_POOL_LOGGER_STEP	 0x40000 //0x120000 
#define PANIC_MEM_POOL_ADDR_VA	S3C_VA_KMSG_DUMP//phys_to_virt(PANIC_MEM_POOL_ADDR_PA)
#define PANIC_MEM_POOL_LOGGER_ADDR_VA S3C_VA_LOGGER1_DUMP	//S3C_ADDR(0x00700000)	/* kmsg */
//#define PANIC_MEM_POOL_LOGGER_ADDR2_VA  S3C_VA_LOGGER2_DUMP	//S3C_ADDR(0x00800000)	/* kmsg */
//#define PANIC_INFO_DUMP_START_OFFSET	0x4	// Leave 4 byte for symbol reserve
//#define PANIC_SYMBOL		0x12345678
//#define PANIC_INFO_LENGTH	0xC000		// 48KB for all information except the pc etc.

#define PANIC_INFO_ADDR S5P_INFORM6
#define PANIC_SYMBOL		0xe412
//#define PANIC_LOGCAT_ADDR S5P_INFORM7

extern void panic_dump_info_set(void);
extern char * panic_dump_buffer(unsigned index);
extern char * panic_logger_buffer(unsigned index);
extern int panic_file_create(void);
extern void reserve_panic_dump_area(void);
extern void panic_dump_test(void);
//extern void panic_info_dump_to_mem(void);
#endif /* __ASM_ARCH_MEMORY_H */
