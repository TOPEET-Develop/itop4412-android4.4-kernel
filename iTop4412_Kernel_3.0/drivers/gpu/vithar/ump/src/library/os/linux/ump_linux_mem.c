/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file ump_linux_mem.c
 *
 * This file implements the user space API of the UMP API.
 * It relies heavily on a arch backend to do the communication with the UMP device driver.
 */

#define _LARGEFILE64_SOURCE 1

#include <ump/ump.h>
#include <ump/src/ump_uku.h>
#include <ump/src/library/common/ump_user.h>
#include <ump/src/devicedrv/linux/ump_arch_mem_common.h>

#include <stdlib/mali_stdlib.h>
#include <osu/mali_osu.h>
#include <cdbg/mali_cdbg_assert.h>

#include <sys/mman.h>
#include <unistd.h>

#ifdef ANDROID
/* Android does not provide a mmap64 function, it is implemented directly here using the __mmap2 syscall */
extern void *__mmap2(void *, size_t, int, int, int, size_t);

static void *mmap64( void *addr, size_t size, int prot, int flags, int fd, off64_t offset )
{
	return __mmap2(addr, size, prot, flags, fd, offset >> CONFIG_CPU_PAGE_SIZE_LOG2);
}
#endif

MALI_EXPORT void * ump_map(ump_handle memh, u64 offset, size_t size)
{
	ump_mem * mem = (ump_mem *)memh;
	void * addr;
	size_t page_mask = (1ul << CONFIG_CPU_PAGE_SIZE_LOG2) - 1;
	mali_size64 map_offset;
	size_t map_size;
	off64_t arg;

	CDBG_ASSERT(UMP_INVALID_MEMORY_HANDLE != memh);
	CDBG_ASSERT_POINTER(mem);
	CDBG_ASSERT((mem->id & UMP_LINUX_ID_MASK) == mem->id);

	/* make size a multiple of pages, correcting any rounding down we do to the offset */
	map_size = (size + (offset & page_mask) + page_mask) & ~page_mask;
	/* round down to a page boundary */
	map_offset = offset >> CONFIG_CPU_PAGE_SIZE_LOG2;

	/* 64-bit (really 52 bits) encoding: 15 bits for the ID, 37 bits for the offset */
	CDBG_ASSERT( (map_offset & UMP_LINUX_OFFSET_MASK) == map_offset);
	arg = ((((u64)mem->id) << UMP_LINUX_OFFSET_BITS) | (map_offset)) << CONFIG_CPU_PAGE_SIZE_LOG2;

	addr = mmap64(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, *(int*)uku_driver_context(&ump_uk_ctx), arg);
	if (MAP_FAILED == addr) return NULL;
	return (u8*)addr + (offset & page_mask);

}

MALI_EXPORT void ump_unmap(ump_handle memh, void* address, size_t size)
{
	ump_mem * mem = (ump_mem *)memh;
	size_t page_mask = (1ul << CONFIG_CPU_PAGE_SIZE_LOG2) - 1;

	CDBG_ASSERT(UMP_INVALID_MEMORY_HANDLE != memh);
	CDBG_ASSERT_POINTER(mem);
	CDBG_ASSERT(0 != mem->id);
	CDBG_ASSERT((mem->id & UMP_LINUX_ID_MASK) == mem->id);
	
	UNUSED(mem);

	size = ((size + ((uintptr_t)address & page_mask)) + page_mask) & ~page_mask;
	address = (void*)((uintptr_t)address & ~page_mask);
	munmap((void*)address, size);
}

