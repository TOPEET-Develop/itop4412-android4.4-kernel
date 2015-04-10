/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include <malisw/mali_malisw.h>
#include <cdbg/mali_cdbg.h>
#include <base/mali_base.h>
#include <osu/mali_osu.h>
#include <base/src/mali_base_uk.h>
#include <base/src/mali_base_user.h>
#include <kbase/src/common/mali_kbase_uku.h>
#include "mali_base_kbase.h"

#if (1 == MALI_BASE_TRACK_MEMLEAK)
#undef base_pmem_alloc
#undef base_tmem_alloc
#undef base_pmem_free
#undef base_tmem_free
#undef base_tmem_alloc_growable
#endif

void base_jd_submit_bag(base_context *base_ctx, const base_jd_bag *bag)
{
	mali_error err;
	kbase_uk_job_submit ukbag;

	CDBG_ASSERT_POINTER(base_ctx);
	CDBG_ASSERT(MALI_FALSE == base_ctx->dispatch_disabled);
	CDBG_ASSERT_MSG( 0u == bag->core_restriction, "Use of core_restriction is deprecated" );

	ukbag.header.id = KBASE_FUNC_JOB_SUBMIT;

	ukbag.bag_uaddr = (uintptr_t)bag;
	ukbag.core_restriction = 0u;
	ukbag.offset = bag->offset;
	ukbag.size = bag->size;
	ukbag.nr_atoms = bag->nr_atoms;

	err = uku_call(&base_ctx->uk_ctx, &ukbag, sizeof(ukbag));

	CDBG_ASSERT_MSG(
		err == MALI_ERROR_NONE && ukbag.header.ret == MALI_ERROR_NONE,
		"bag submission error swallowed (%d, %d)", err, ukbag.header.ret
		);
		
	return;
}

static int post_term(uku_context * uk_ctx)
{
	kbase_uk_post_term post_request;
	mali_error err;

	post_request.header.id = KBASE_FUNC_POST_TERM;

	err = uku_call(uk_ctx, &post_request, sizeof(post_request));

	return (err == MALI_ERROR_NONE);
}

void base_jd_event_term(base_context *base_ctx)
{
	CDBG_ASSERT_POINTER(base_ctx);

	base_ctx->dispatch_disabled = MALI_TRUE;
	post_term(&base_ctx->uk_ctx);
	/* wait for term recvd */
	osu_sem_wait(&base_ctx->shutdown_sem, 0);
	osu_sem_term(&base_ctx->shutdown_sem);
}

mali_error base_uk_ctx_alloc(base_context * base_ctx, u32 flags)
{
	size_t pool_size = BASEP_JCTX_RB_NRPAGES << 12;

	uku_client_version client_version;
	uku_open_status open_status;

	CDBG_ASSERT_POINTER(base_ctx);

	if ( BDBG_SIMULATE_FAILURE( CDBG_BASE ) )
	{ 
		return MALI_ERROR_FUNCTION_FAILED;
	}

	if(OSU_ERR_OK != osu_sem_init(&base_ctx->shutdown_sem, 0) )
	{
		goto fail_sem_init;
	}
	base_ctx->jd_context.size = pool_size;

	client_version.major = BASE_UK_VERSION_MAJOR;
	client_version.minor = BASE_UK_VERSION_MINOR;
	open_status = uku_open(UK_CLIENT_MALI_T600_BASE, 0, &client_version, &base_ctx->uk_ctx);
	if (UKU_OPEN_OK != open_status)
	{
		goto fail_open;
	}
	if (MALI_ERROR_NONE != basep_map_ringbuffer(base_ctx))
	{
		goto fail_rb_map;
	}

	return MALI_ERROR_NONE;

fail_rb_map:
	uku_close(&base_ctx->uk_ctx);
fail_open:
	osu_sem_term(&base_ctx->shutdown_sem);
fail_sem_init:
	return MALI_ERROR_FUNCTION_FAILED;
}

void base_uk_ctx_terminate(base_context * base_ctx)
{
	CDBG_ASSERT_POINTER(base_ctx);

	basep_unmap_ringbuffer(base_ctx);
	uku_close(&base_ctx->uk_ctx);
}

void base_uk_ctx_free(base_context *base_ctx)
{
	CDBG_ASSERT_POINTER(base_ctx);
}


mali_error base_context_reg_trace_enable(base_context *ctx, size_t trace_buffer_size, void** mapping)
{
	mali_error err;

	CDBG_ASSERT_POINTER(ctx);
	CDBG_ASSERT_POINTER(mapping);
	CDBG_ASSERT(NULL == ctx->jd_context.tb);

	err = basep_map_trace_buffer(ctx, trace_buffer_size);

	if (MALI_ERROR_NONE != err)
	{
		return err;
	}

	*mapping = ctx->jd_context.tb;

	return MALI_ERROR_NONE;

}

void base_context_reg_trace_disable(base_context * ctx)
{
	CDBG_ASSERT_POINTER(ctx);
	CDBG_ASSERT(NULL != ctx->jd_context.tb);
	if (NULL == ctx->jd_context.tb)
	{
		/* ignore the unmatched disable call */
		return;
	}
	basep_unmap_trace_buffer(ctx);
}


mali_error base_context_hwcnt_enable(base_context* base_ctx, mali_addr64 dump_addr, u32 jm_bm, u32 shader_bm, u32 tiler_bm, u32 l3_cache_bm, u32 mmu_l2_bm)
{
	mali_error err;
	kbase_uk_hwcnt_setup hwcnt_setup;

	CDBG_ASSERT_POINTER(base_ctx);
	CDBG_ASSERT(0 == (dump_addr & (2048-1))); /* alignment check */

	hwcnt_setup.header.id = KBASE_FUNC_HWCNT_SETUP;
	hwcnt_setup.dump_buffer = dump_addr;
	hwcnt_setup.jm_bm = jm_bm;
	hwcnt_setup.shader_bm = shader_bm;
	hwcnt_setup.tiler_bm = tiler_bm;
	hwcnt_setup.l3_cache_bm = l3_cache_bm;
	hwcnt_setup.mmu_l2_bm = mmu_l2_bm;

	err = uku_call(&base_ctx->uk_ctx, &hwcnt_setup, sizeof(hwcnt_setup));

	if (MALI_ERROR_NONE == err)
	{
		err = hwcnt_setup.header.ret;
	}

	return err;
}

mali_error base_context_hwcnt_dump(base_context * base_ctx)
{
	mali_error err;
	kbase_uk_hwcnt_dump dump;

	CDBG_ASSERT_POINTER(base_ctx);

	dump.header.id = KBASE_FUNC_HWCNT_DUMP;
	err = uku_call(&base_ctx->uk_ctx, &dump, sizeof(dump));

	if (MALI_ERROR_NONE == err)
	{
		err = dump.header.ret;
	}

	return err;
}

void base_context_hwcnt_disable(base_context * base_ctx)
{
	kbase_uk_hwcnt_setup hwcnt_setup;
	mali_error err;

	CDBG_ASSERT_POINTER(base_ctx);
	hwcnt_setup.header.id = KBASE_FUNC_HWCNT_SETUP;
	hwcnt_setup.dump_buffer = 0ULL;
	err = uku_call(&base_ctx->uk_ctx, &hwcnt_setup, sizeof(hwcnt_setup));
	CDBG_ASSERT_MSG(
		err == MALI_ERROR_NONE && hwcnt_setup.header.ret == MALI_ERROR_NONE, 
		"disabling hw counter failed; swallowing error (%d, %d)", err, hwcnt_setup.header.ret
		);
}

mali_addr64 base_pmem_cpu_address_to_gpu(base_pmem_handle handle, const void *addr)
{
	return (mali_addr64)(uintptr_t)addr;
}

mali_error basep_do_mem_free(uku_context *uk_ctx, u64 handle)
{
	mali_error err;
	kbase_uk_mem_free mem;

	mem.header.id	= KBASE_FUNC_MEM_FREE;
	mem.gpu_addr	= handle;

	err = uku_call(uk_ctx, &mem, sizeof(mem));
	if (MALI_ERROR_NONE == err)
	{
		err = mem.header.ret;
	}

	return err;
}


void *base_pmem_get_cpu_address(base_pmem_handle handle)
{
	return (void*)(uintptr_t)handle;
}

mali_addr64 base_pmem_get_gpu_address(base_pmem_handle handle, size_t offset)
{
	return handle + offset;
}

base_tmem_handle base_tmem_alloc_growable(base_context *base_ctx, u32 max_pages,
					  u32 init_pages, u32 extent_pages,
					  u32 flags)
{
	mali_error err;
	kbase_uk_tmem_alloc tmem;

	CDBG_ASSERT_POINTER(base_ctx);
	CDBG_ASSERT(0 == (flags & BASEP_MEM_IS_CACHED));

	if ( BDBG_SIMULATE_FAILURE( CDBG_BASE ) )
	{
		return BASE_TMEM_INVALID_HANDLE;
	}

	tmem.header.id  = KBASE_FUNC_TMEM_ALLOC;
	tmem.vsize  = max_pages;
#if MALI_HW_TYPE == 2
	tmem.psize  = init_pages;
#else
	tmem.psize = max_pages;
#endif
	tmem.extent = extent_pages;
	tmem.flags  = flags;

	err = uku_call(&base_ctx->uk_ctx, &tmem, sizeof(tmem));
	if (MALI_ERROR_NONE == err)
	{
		err = tmem.header.ret;
		if (MALI_ERROR_NONE == err)
		{
			return tmem.gpu_addr;
		}
	}

	return 0ULL;
}

base_tmem_handle base_tmem_from_ump(base_context *ctx, ump_secure_id ump_id, u64 * const pages)
{
	mali_error err;

	kbase_uk_tmem_from_ump tmem_ump;

	CDBG_ASSERT_POINTER(ctx);

	tmem_ump.header.id = KBASE_FUNC_TMEM_FROM_UMP;
	tmem_ump.id = ump_id;

	err = uku_call(&ctx->uk_ctx, &tmem_ump, sizeof(tmem_ump));
	if (MALI_ERROR_NONE == err)
	{
		err = tmem_ump.header.ret;
		if (MALI_ERROR_NONE == err)
		{
			if (NULL != pages)
				*pages = tmem_ump.pages;
			
			return tmem_ump.gpu_addr;
		}
	}

	return 0ULL;
}

base_backing_threshold_status base_tmem_set_backing_threshold(base_context * base_ctx,
        base_tmem_handle handle, s32 page_delta, u32 *pages)
{
	mali_error err;
	kbase_uk_tmem_resize tmem;

	CDBG_ASSERT(base_ctx);
	CDBG_ASSERT(pages);

	if ( BDBG_SIMULATE_FAILURE( CDBG_BASE ) )
	{
		return BASE_BACKING_THRESHOLD_ERROR_OOM;
	}

	tmem.header.id  = KBASE_FUNC_TMEM_RESIZE;
	tmem.gpu_addr   = handle;
	tmem.delta      = page_delta;
	
	err = uku_call(&base_ctx->uk_ctx, &tmem, sizeof(tmem));
	if (MALI_ERROR_NONE == err)
	{
		err = tmem.header.ret;
		if (MALI_ERROR_NONE == err)
		{
			*pages = tmem.size;
			return BASE_BACKING_THRESHOLD_OK;
		}
		else
		{
			return tmem.result_subcode;
		}
	}
	return BASE_BACKING_THRESHOLD_ERROR_INVALID_ARGUMENTS;
}

void base_tmem_free(base_context * base_ctx, base_tmem_handle handle)
{
	mali_error err;
	CDBG_ASSERT_POINTER(base_ctx);

	err = basep_do_mem_free(&base_ctx->uk_ctx, handle);
	CDBG_ASSERT(MALI_ERROR_NONE == err);
}

mali_addr64 base_tmem_get_gpu_address(base_tmem_handle handle, mali_size64 offset)
{
	return handle + offset;
}

#if MALI_INSTRUMENTATION_LEVEL == 2
/* These function definitions must match the strong symbols defined by the
   cinstr module. ('Weak' symbols are a GCC extension.) */
void __attribute__ ((weak)) cinstr_base_dump_syncset_to_gpu(base_context *ctx, mali_addr64 gpu_va, void *data, size_t size);

void __attribute__ ((weak)) cinstr_base_dump_syncset_to_cpu(base_context *ctx, mali_addr64 gpu_va, void *data, size_t size);
#endif /* MALI_INSTRUMENTATION_LEVEL == 2 */

/**
 * @brief Record a memory coherency operation for the instrumented driver.
 *
 * @param[in] base_ctx  The Base context used for the allocation.
 * @param[in] sset      Pointer to a descriptor for a single memory
 *                      coherency operation (sync-set).
 */
#if MALI_INSTRUMENTATION_LEVEL == 2
static void basep_syncset_dump( base_context *base_ctx, base_syncset *sset )
{
	mali_error                err;
	kbase_uk_find_cpu_mapping find;

	CDBG_ASSERT_POINTER( base_ctx );
	CDBG_ASSERT_POINTER( sset );

	/* Call the kernel module to find the relevant CPU mapping of the memory
	   allocation within which synchronization is required. This call is
	   separate from KBASE_FUNC_SYNC so we can dump syncset information in
	   user mode. */
	find.header.id = KBASE_FUNC_FIND_CPU_MAPPING;

	find.gpu_addr = sset->basep_sset.mem_handle;
	find.cpu_addr = sset->basep_sset.user_addr;
	find.size = sset->basep_sset.size;

	err = uku_call(&base_ctx->uk_ctx, &find, sizeof(find));

	if ( MALI_ERROR_NONE == err )
	{
		mali_size64 sync_offset, map_offset;
		mali_addr64 gpu_va;

		/* Calculate the offset (in bytes) of the cache coherency operation from the
		   start of the sub-region mapped for CPU access. */
		CDBG_ASSERT_LEQ_U( find.uaddr, sset->basep_sset.user_addr );
		sync_offset = sset->basep_sset.user_addr - find.uaddr;
		
		/* Calculate the offset (in bytes) of the sub-region mapped for CPU access
		   from the start of the allocation. */
		CDBG_ASSERT_LEQ_U( find.page_off, U64_MAX >> CONFIG_CPU_PAGE_SIZE_LOG2 );
		map_offset = find.page_off << CONFIG_CPU_PAGE_SIZE_LOG2;

		/* Calculate the GPU virtual address of the start of the memory to be
		   synchronized, assuming the memory handle is actually the GPU virtual
		   address of the start of the allocation. */
		CDBG_ASSERT_LEQ_U( map_offset, U64_MAX - sync_offset );
		CDBG_ASSERT_LEQ_U( sset->basep_sset.mem_handle, U64_MAX - sync_offset - map_offset );
		gpu_va = sset->basep_sset.mem_handle + map_offset + sync_offset;

		switch ( sset->basep_sset.type )
		{
			case BASE_SYNCSET_OP_MSYNC:
				cinstr_base_dump_syncset_to_gpu( base_ctx,
				                                 gpu_va,
				                                 (void *)(uintptr_t)sset->basep_sset.user_addr,
				                                 sset->basep_sset.size );
				break;
	
			case BASE_SYNCSET_OP_CSYNC:
				cinstr_base_dump_syncset_to_cpu( base_ctx,
				                                 gpu_va,
				                                 (void *)(uintptr_t)sset->basep_sset.user_addr,
				                                 sset->basep_sset.size );
				break;
	
			default:
				CDBG_PRINT_ERROR( CDBG_BASE, "Unknown memory coherency operation type" );
				break;
		}
	}
}
#else
#define basep_syncset_dump( base_ctx, sset ) CSTD_NOP( base_ctx, sset )
#endif /* MALI_INSTRUMENTATION_LEVEL == 2 */

/**
 * @brief Synchronize a mapped region for CPU or GPU usage
 *
 * @param[in] base_ctx  The Base context used for the allocation.
 * @param[in] sset      Pointer to a descriptor for a single memory
 *                      coherency operation (sync-set).
 *
 * @warning May synchronize more memory than specified by @p sset if
 *          not aligned to cache line boundaries.
 */
static void basep_syncset_sync_now(base_context *base_ctx, base_syncset *sset)
{
	kbase_uk_sync_now sn;
	mali_error err;

	CDBG_ASSERT_POINTER( base_ctx );
	CDBG_ASSERT_POINTER( sset );

	basep_syncset_dump( base_ctx, sset );

	sn.header.id = KBASE_FUNC_SYNC;
	sn.sset = *sset;

	err = uku_call(&base_ctx->uk_ctx, &sn, sizeof(sn));

	CDBG_ASSERT_MSG(
		err == MALI_ERROR_NONE && sn.header.ret == MALI_ERROR_NONE, 
		"sync now error swallowed (%d, %d)", err, sn.header.ret
		);
}

/**
 * @brief Synchronize a mapped region for CPU or GPU usage
 *
 * Performs the specified memory coherency operation on the CPU virtual
 * address range specified by @p cpu_address and @p size. Internally, the
 * start address is rounded down to the nearest cache line boundary and the
 * end address is rounded upward similarly. Does not output the true start
 * address and size of the region synchronized.
 *
 * @param[in]     base_ctx    The Base context used for the allocation.
 * @param[in]     handle      Handle of the memory allocation within which
 *                            synchronization is required.
 * @param[in,out] cpu_address Pointer to the start of the memory to be
 *                            synchronized.
 * @param[in]     size        Number of bytes to be synchronized.
 * @param[in]     type        Type of memory coherency operation
 *                            (e.g. BASE_SYNCSET_OP_MSYNC).
 *
 * @warning May synchronize more memory than specified if @p cpu_address
 *          and @p size aren't aligned to cache line boundaries.
 */
static void basep_sync_now(base_context    *base_ctx,
                           base_mem_handle  handle,
                           void            *cpu_address,
                           size_t           size,
                           u8               type)
{
	base_syncset sset;

	CDBG_ASSERT_POINTER( base_ctx );
	CDBG_ASSERT( handle != 0 );
	CDBG_ASSERT_POINTER( cpu_address );

	/* Initialize a structure describing a basic memory coherency operation. */
	sset.basep_sset.mem_handle = handle;
	sset.basep_sset.user_addr = PTR_TO_U64( cpu_address );
	CDBG_ASSERT_LEQ_U( size, U32_MAX ); /* Due to MIDBASE-806 */
	sset.basep_sset.size = size;
	sset.basep_sset.type = type;

	basep_syncset_sync_now( base_ctx, &sset );
}

void base_sync_to_cpu_now(base_context *base_ctx, base_mem_handle handle,
			  void *cpu_address, size_t size)
{
	CDBG_ASSERT_POINTER(base_ctx);
	basep_sync_now(base_ctx,handle, cpu_address, size, BASE_SYNCSET_OP_CSYNC);
}

void base_sync_to_gpu_now(base_context *base_ctx, base_mem_handle handle,
			  void *cpu_address, size_t size)
{
	CDBG_ASSERT_POINTER(base_ctx);
	basep_sync_now(base_ctx, handle, cpu_address, size, BASE_SYNCSET_OP_MSYNC);
}

void base_syncset_sync_list_now(base_context *ctx, base_syncset_list *list)
{
	CDBG_ASSERT_POINTER(ctx);
	while(list)
	{
		base_syncset_list_entry *entry = list->list;
		base_syncset_list *next;
		int i;

		for (i = 0; i < list->nr_syncsets; i++)
		{
			basep_syncset_sync_now(ctx, &entry->syncset);
			entry = entry->next;
		}

		next = list->next;
		if (list->dtor)
			list->dtor(list);
		list = next;
	}
}

