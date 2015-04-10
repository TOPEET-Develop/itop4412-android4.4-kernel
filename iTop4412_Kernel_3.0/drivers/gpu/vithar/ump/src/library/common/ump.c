/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2008-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file ump.c
 *
 * This file implements the user space API of the UMP API.
 * It relies heavily on a arch backend to do the communication with the UMP device driver.
 */

#include <ump/ump.h>
#include <ump/src/ump_uku.h>
#include <ump/src/library/common/ump_user.h>

#include <stdlib/mali_stdlib.h>
#include <osu/mali_osu.h>
#include <cdbg/mali_cdbg_assert.h>
#include <malisw/mali_malisw.h>

/** Pointer to an OS-Specific context that we should pass in _uku_ calls */
ump_context ump_uk_ctx;

/** Reference counting of ump_arch_open() and ump_arch_close(). */
STATIC unsigned long ump_ref_count = 0;

#define UMP_STATIC_MUTEX_NR OSU_STATIC_MUTEX_UMP_GLOBAL_STATE
#define UMP_PAGE_SIZE (1u << CONFIG_CPU_PAGE_SIZE_LOG2)

__attribute__((always_inline)) STATIC INLINE ump_result do_call(void * arg, size_t arg_size)
{
	mali_error result;
	uk_header * header = (uk_header*)arg;

	CDBG_ASSERT(ump_ref_count > 0);

	result = uku_call(&ump_uk_ctx, arg, arg_size);
	if (MALI_ERROR_NONE == result)
	{
		result = header->ret;
	}

	return result;
}

STATIC INLINE ump_result umpp_retain(ump_secure_id id)
{
	ump_uk_retain call_arg;

	/* set up uku call */
	call_arg.header.id = UMP_FUNC_RETAIN;

	/* our payload */
	call_arg.secure_id = id;

	return do_call(&call_arg, sizeof(call_arg));
}

STATIC INLINE void umpp_release(ump_secure_id id)
{
	ump_uk_release call_arg;
	ump_result result;

	/* set up uku call */
	call_arg.header.id = UMP_FUNC_RELEASE;

	/* our payload */
	call_arg.secure_id = id;

	result = do_call(&call_arg, sizeof(call_arg));

	CDBG_ASSERT_MSG( (UMP_OK == result) && (MALI_ERROR_NONE == call_arg.header.ret),
	                 "Release call failed, no way to recover from this, memory has been leaked!"
	               );
	
	(void)result; /* quiet release builds */
}

MALI_EXPORT ump_result ump_open(void)
{
	osu_mutex * ump_lock = osu_mutex_static_get(UMP_STATIC_MUTEX_NR);
	ump_result res = UMP_OK;

	osu_mutex_lock(ump_lock);

	if (ump_ref_count == ULONG_MAX)
	{
		/* too many opens */
		return UMP_ERROR;
	}

	if (1 == ++ump_ref_count)
	{
		uku_client_version ump_version;
		uku_open_status open_status;
		
		/* first open call, do the actual backend open */
		ump_version.major = UMP_VERSION_MAJOR;
		ump_version.minor = UMP_VERSION_MINOR;
		open_status = uku_open(UK_CLIENT_UMP, 0, &ump_version, &ump_uk_ctx);
		if (UKU_OPEN_OK != open_status)
		{
			ump_ref_count--; /* undo the increment we did */
			res = UMP_ERROR;
		}
	}

	osu_mutex_unlock(ump_lock);

	return res;
}

MALI_EXPORT void ump_close(void)
{
	osu_mutex * ump_lock = osu_mutex_static_get(UMP_STATIC_MUTEX_NR);

	CDBG_ASSERT(0 < ump_ref_count);

	osu_mutex_lock(ump_lock);

	if (ump_ref_count && 0 == --ump_ref_count)
	{
		/* last close call, do the actual backend close */
		uku_close(&ump_uk_ctx);
	}

	osu_mutex_unlock(ump_lock);
}


MALI_EXPORT ump_handle ump_allocate(u64 size, ump_alloc_flags flags)
{
	ump_uk_allocate call_arg;
	ump_handle result = UMP_INVALID_MEMORY_HANDLE;

	CDBG_ASSERT(0 == (flags & UMPP_ALLOCBITS_UNUSED));

	/* round up to a page size */
	size = (size + (UMP_PAGE_SIZE - 1)) & ~(UMP_PAGE_SIZE - 1);

	/* set up uku call */
	call_arg.header.id = UMP_FUNC_ALLOCATE;

	/* our payload */
	call_arg.secure_id = UMP_INVALID_SECURE_ID;
	call_arg.size = size;
	call_arg.alloc_flags = flags;
	
	if (UMP_OK == do_call(&call_arg, sizeof(call_arg)))
	{
		/* got an allocation, create a handle for it */
		ump_mem * mem;

		/* if this fails the backend has violated the API and we have no way of cleaning up */
		CDBG_ASSERT(UMP_INVALID_SECURE_ID != call_arg.secure_id);

		mem = stdlib_malloc(sizeof(*mem));

		if (NULL != mem)
		{
			mem->id = call_arg.secure_id;
			osu_atomic_set(&mem->refcnt, 1);
			result = (ump_handle)mem;
		}
		else
		{
			umpp_release(call_arg.secure_id);
		}
	}

	return result;
}

MALI_EXPORT ump_resize_result ump_resize(ump_handle memh, s64 size_diff, u64 * new_size)
{
	ump_mem * mem = (ump_mem*)memh;
	ump_resize_result result;

	CDBG_ASSERT(UMP_INVALID_MEMORY_HANDLE != mem);
	CDBG_ASSERT(NULL != new_size);

	if (0 == size_diff)
	{
		/* size query */
		ump_uk_sizequery call_arg;

		call_arg.header.id = UMP_FUNC_SIZEQUERY;
		call_arg.secure_id = mem->id;
		call_arg.size = 0;

		result = (ump_resize_result)do_call(&call_arg, sizeof(call_arg));

		if (UMP_RESIZE_OK == result)
		{
			*new_size = call_arg.size;
		}
		else
		{
			*new_size = 0;
		}
	}
	else
	{
		ump_uk_resize call_arg;

		if (size_diff < 0)
		{
			/* asked to shrink the allocation */
			/* round to a page multiple */
			if (size_diff & (UMP_PAGE_SIZE - 1))
			{
				size_diff |= (UMP_PAGE_SIZE - 1);
				size_diff++;
			}
		}
		else
		{
			/* asked to expand the allocation */
			/* round up to a page multiple */
			size_diff = (size_diff + (UMP_PAGE_SIZE - 1)) & ~(UMP_PAGE_SIZE - 1);
		}

		call_arg.header.id = UMP_FUNC_RESIZE;

		/* our payload */
		call_arg.secure_id = mem->id;
		call_arg.size_diff = size_diff;
		call_arg.new_size = 0;

		result = (ump_resize_result)do_call(&call_arg, sizeof(call_arg));

		if (UMP_RESIZE_OK == result)
		{
			*new_size = call_arg.new_size;
		}
	}

	return result;
}

MALI_EXPORT ump_secure_id ump_secure_id_get(const ump_handle memh)
{
	const ump_mem * mem = (const ump_mem *)memh;

	if (UMP_INVALID_MEMORY_HANDLE == memh)
	{
		return UMP_INVALID_SECURE_ID;
	}

	CDBG_ASSERT_POINTER(mem);
	CDBG_ASSERT(mem->id != UMP_INVALID_SECURE_ID);
	CDBG_ASSERT(osu_atomic_get(&mem->refcnt) != 0);

	return mem->id;
}

MALI_EXPORT ump_handle ump_from_secure_id(ump_secure_id secure_id)
{
	ump_handle result = UMP_INVALID_MEMORY_HANDLE;

	if (UMP_INVALID_SECURE_ID == secure_id)
	{
		return result;
	}

	if (UMP_OK == umpp_retain(secure_id))
	{
		ump_mem * mem;

		/* handle validated and attached to this process */
		mem = stdlib_malloc(sizeof(*mem));

		if (NULL != mem)
		{
			mem->id = secure_id;
			osu_atomic_set(&mem->refcnt, 1);

			result = (ump_handle)mem;
		}
		else
		{
			/* remove our ref */
			umpp_release(secure_id);
		}
	}

	return result;
}

MALI_EXPORT u64 ump_size_get(const ump_handle memh)
{
	ump_uk_sizequery call_arg;
	const ump_mem * mem = (const ump_mem *)memh;

	CDBG_ASSERT(UMP_INVALID_MEMORY_HANDLE != mem);
	CDBG_ASSERT_POINTER(mem);

	call_arg.header.id = UMP_FUNC_SIZEQUERY;

	call_arg.secure_id = mem->id;
	call_arg.size = 0;

	if (UMP_OK == do_call(&call_arg, sizeof(call_arg)))
	{
		return call_arg.size;
	}
	else
	{
		CDBG_PRINT_ERROR(CDBG_BASE, "Failed to query the size, 0 size will be reported");
		return 0;
	}
}

MALI_EXPORT void ump_cpu_msync_now(ump_handle memh, ump_cpu_msync_op op, void * address, size_t size)
{
	ump_mem * mem = (ump_mem *)memh;
	ump_uk_msync call_arg;
	ump_result res;

	CDBG_ASSERT(UMP_INVALID_MEMORY_HANDLE != memh);
	CDBG_ASSERT_POINTER(mem);

	call_arg.header.id = UMP_FUNC_MSYNC;

	/* our payload */
	call_arg.secure_id = mem->id;
	call_arg.cache_operation = op;
	call_arg.mapped_ptr.value = address;
	call_arg.size = size;

	res = do_call(&call_arg, sizeof(call_arg));

	CDBG_ASSERT_MSG(UMP_OK == res, "Cache sync failed, no way to recover");
}

MALI_EXPORT void ump_retain(ump_handle memh)
{
	ump_mem * mem = (ump_mem *)memh;

	CDBG_ASSERT(UMP_INVALID_MEMORY_HANDLE != memh);
	CDBG_ASSERT_POINTER(mem);

	osu_atomic_inc(&mem->refcnt);
}

MALI_EXPORT void ump_release(ump_handle memh)
{
	ump_mem * mem = (ump_mem * )memh;

	if (UMP_INVALID_MEMORY_HANDLE == memh)
	{
		/* swallow this to ease error handlers */
		return;
	}

	if (0 == osu_atomic_dec(&mem->refcnt))
	{
		umpp_release(mem->id);
		stdlib_free(mem);
	}
}

