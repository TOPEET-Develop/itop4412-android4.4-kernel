/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#define _LARGEFILE64_SOURCE 1
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include "mali_base_kbase.h"

#if (1 == MALI_BASE_TRACK_MEMLEAK)
#undef base_pmem_alloc
#undef base_tmem_alloc
#undef base_pmem_free
#undef base_tmem_free
#undef base_tmem_alloc_growable
#endif

#ifdef ANDROID
/* Android does not provide a mmap64 function, it is implemented directly here using the __mmap2 syscall */
extern void *__mmap2(void *, size_t, int, int, int, size_t);

static void *mmap64( void *addr, size_t size, int prot, int flags, int fd, off64_t offset )
{
	return __mmap2(addr, size, prot, flags, fd, offset >> 12);
}
#endif

#define CONTEXT_MMU_SNAP_OFFSET 4096
#define CONTEXT_TRACE_BUFFER_OFFSET 8192

mali_error basep_map_ringbuffer(base_context * base_ctx)
{
	if ( BDBG_SIMULATE_FAILURE( CDBG_BASE ) )
	{ 
		base_ctx->jd_context.pool = NULL;
		return MALI_ERROR_FUNCTION_FAILED;
	}

	base_ctx->jd_context.pool = mmap64(NULL, base_ctx->jd_context.size, PROT_READ | PROT_WRITE, MAP_SHARED, *(int *)uku_driver_context(&base_ctx->uk_ctx), 0);
	if (base_ctx->jd_context.pool == MAP_FAILED)
	{
		base_ctx->jd_context.pool = NULL;
		return MALI_ERROR_FUNCTION_FAILED;
	}
	else
	{
		return MALI_ERROR_NONE;
	}
}

void basep_unmap_ringbuffer(base_context * base_ctx)
{
	munmap(base_ctx->jd_context.pool, base_ctx->jd_context.size);
	base_ctx->jd_context.pool = NULL;
}

mali_error basep_map_trace_buffer(base_context * base_ctx, size_t tb_size)
{
	base_ctx->jd_context.tb_size = tb_size;
	base_ctx->jd_context.tb = mmap64(NULL, tb_size << CONFIG_CPU_PAGE_SIZE_LOG2, PROT_READ, MAP_SHARED, *(int *)uku_driver_context(&base_ctx->uk_ctx), CONTEXT_TRACE_BUFFER_OFFSET);
	if (base_ctx->jd_context.tb == MAP_FAILED)
	{
		base_ctx->jd_context.tb = NULL;
		return MALI_ERROR_FUNCTION_FAILED;
	}
	else
	{
		return MALI_ERROR_NONE;
	}
}

void basep_unmap_trace_buffer(base_context * base_ctx)
{
	munmap(base_ctx->jd_context.tb, base_ctx->jd_context.tb_size);
	base_ctx->jd_context.tb = NULL;
}

void *base_pmem_alloc(base_context *base_ctx, u32 pages, u32 flags, base_pmem_handle *handle)
{
	mali_error err;
	kbase_uk_pmem_alloc pmem;

	CDBG_ASSERT_POINTER(base_ctx);
	CDBG_ASSERT_POINTER(handle);
	CDBG_ASSERT(0 == (flags & BASEP_MEM_IS_CACHED));

	if ( BDBG_SIMULATE_FAILURE( CDBG_BASE ))
	{
		return NULL;
	}

	pmem.header.id	= KBASE_FUNC_PMEM_ALLOC;
	pmem.vsize	= pages;
	pmem.flags	= flags;

	err = uku_call(&base_ctx->uk_ctx, &pmem, sizeof(pmem));
	if (MALI_ERROR_NONE == err)
	{
		err = pmem.header.ret;
		if (MALI_ERROR_NONE == err)
		{
			void * mapping = mmap64(NULL, pages << 12, PROT_READ | PROT_WRITE, MAP_SHARED, *(int *)uku_driver_context(&base_ctx->uk_ctx), pmem.cookie << 12);
			if (mapping != MAP_FAILED)
			{
				*handle = (mali_addr64)(uintptr_t)mapping;
				return mapping;
			}

			err = basep_do_mem_free(&base_ctx->uk_ctx, pmem.cookie);
			CDBG_ASSERT(MALI_ERROR_NONE == err);
		}
	}

	return NULL;
}

void base_pmem_free(base_context * base_ctx, base_pmem_handle handle, u32 pages)
{
	CDBG_ASSERT_POINTER(base_ctx);
	munmap((void*)(uintptr_t)handle, pages << 12);
}

void *base_tmem_map(base_context * base_ctx, base_tmem_handle handle, mali_size64 offset, size_t size)
{
	void * addr;
	int page_mask;
	mali_size64 map_offset;
	size_t map_size;

	CDBG_ASSERT_POINTER(base_ctx);
	page_mask = getpagesize() - 1;

	/* make size a multiple of pages, correcting any rounding down we do to the offset */
	map_size = (size + (offset & page_mask) + page_mask) & ~page_mask;
	/* round down to a page boundary */
	map_offset = offset & ~page_mask;

	addr = mmap64(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, *(int *)uku_driver_context(&base_ctx->uk_ctx), handle + map_offset);
	if (MAP_FAILED == addr) return NULL;
	return (u8*)addr + (offset & page_mask);
}

mali_error base_tmem_unmap(base_context * base_ctx, base_tmem_handle handle, const void *address, size_t size)
{
	int page_mask;
	CDBG_ASSERT_POINTER(base_ctx);

	page_mask = getpagesize() - 1;
	size = ((size + ((uintptr_t)address & page_mask)) + page_mask) & ~page_mask;
	address = (void*)((uintptr_t)address & ~page_mask);
	munmap((void*)address, size);
	return MALI_ERROR_NONE;
}

void base_jd_event_wait(base_context *base_ctx, base_jd_event *event)
{
	int err;
	CDBG_ASSERT_POINTER(base_ctx);

	err = read(*(int *)uku_driver_context(&base_ctx->uk_ctx), event, sizeof(*event));
	if (err < 0)
	{
		/* mark driver as terminated on all errors */
		event->event_code = BASE_JD_EVENT_DRV_TERMINATED;

		/* Report errors other that EBADF (driver closed or never opened) */
		if (errno != EBADF)
		{
			/* unexpected error */
			perror("read");
			CDBG_ASSERT(0);
		}
	}

	if (event->event_code == BASE_JD_EVENT_DRV_TERMINATED)
		osu_sem_post(&base_ctx->shutdown_sem);
}

void *base_context_mmu_snapshot_take( base_context *ctx, size_t dump_size_max)
{
	void *addr;
	
	CDBG_ASSERT_POINTER(ctx);

	addr = mmap64(NULL, dump_size_max, PROT_READ, MAP_SHARED, *(int*)uku_driver_context(&ctx->uk_ctx), CONTEXT_MMU_SNAP_OFFSET);
	if (addr != MAP_FAILED)
	{
		return addr;
	}
	else
	{
		return NULL;
	}
}

void base_context_mmu_snapshot_release( base_context *ctx, void *snapshot,
                                        size_t dump_size_max)
{
	CDBG_ASSERT_POINTER(ctx);
	munmap(snapshot, dump_size_max);
}

/* For 64 bit this will need changing */
#define BASE_ZONE_TMEM_BASE     (1ULL << 32)

void * base_memory_dumping_map(base_context *ctx, mali_addr64 gpu_addr,
                               size_t pages)
{
	void *addr;

	CDBG_ASSERT(pages > 0);
	CDBG_ASSERT(ctx != NULL);

	if (gpu_addr < BASE_ZONE_TMEM_BASE)
	{
		/* PMEM */
		return (void*)(uintptr_t)gpu_addr;
	}

	addr = mmap64(NULL, pages<<CONFIG_CPU_PAGE_SIZE_LOG2, PROT_READ, MAP_SHARED,
	              *(int*)uku_driver_context(&ctx->uk_ctx), gpu_addr);
	if (addr == MAP_FAILED)
	{
		addr = NULL;
	}
	return addr;
}

void base_memory_dumping_unmap(base_context *ctx, mali_addr64 gpu_addr,
                               void *mapping, size_t pages)
{
	CDBG_ASSERT(pages > 0);
	CDBG_ASSERT(ctx != NULL);
	CDBG_ASSERT(mapping != NULL);

	if (gpu_addr < BASE_ZONE_TMEM_BASE)
	{
		/* PMEM - this is a no-op */
		return;
	}

	munmap(mapping, pages<<CONFIG_CPU_PAGE_SIZE_LOG2);
}
