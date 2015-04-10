/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include <ump/ump_kernel_interface.h>
#include <common/ump_kernel_core.h>
#include <uk/mali_ukk.h>
#include <ump/src/ump_uku.h>

static mali_error do_ump_dd_allocate(ukk_call_context * ukk_ctx, ump_uk_allocate * params)
{
	ump_dd_handle new_allocation;
	new_allocation = ump_dd_allocate(params->size, params->alloc_flags, NULL, NULL, NULL);

	if (UMP_DD_INVALID_MEMORY_HANDLE != new_allocation)
	{
		umpp_session_memory_usage * tracker;

		tracker = osk_malloc(sizeof(*tracker));
		if (NULL != tracker)
		{
			umpp_session * session;

			/* update the return struct with the new ID */
			params->secure_id = ump_dd_secure_id_get(new_allocation);

			tracker->mem = new_allocation;
			tracker->id = params->secure_id;
			osk_atomic_set(&tracker->process_usage_count, 1);

			/* link it into the session in-use list */
			session = CONTAINER_OF(ukk_session_get(ukk_ctx), umpp_session, ukk_session);
			osk_mutex_lock(&session->session_lock);
			OSK_DLIST_PUSH_FRONT(&session->memory_usage, tracker, umpp_session_memory_usage, link);
			osk_mutex_unlock(&session->session_lock);

			return UMP_OK;
		}
		ump_dd_release(new_allocation);
	}

	OSK_PRINT_WARN(OSK_UMP, "Allocation FAILED\n");
	return UMP_ERROR;
}

static mali_error do_ump_dd_retain(ukk_call_context * ukk_ctx, ump_uk_retain * params)
{
	umpp_session * session;
	umpp_session_memory_usage * it;

	session = CONTAINER_OF(ukk_session_get(ukk_ctx), umpp_session, ukk_session);

	osk_mutex_lock(&session->session_lock);

	/* try to find it on the session usage list */
	OSK_DLIST_FOREACH(&session->memory_usage, umpp_session_memory_usage, link, it)
	{
		if (it->id == params->secure_id)
		{
			/* found to already be in use, just add a process local ref */
			osk_atomic_inc(&it->process_usage_count);
			osk_mutex_unlock(&session->session_lock);
			return UMP_OK;
		}
	}

	/* try to look it up globally */
	
	it = osk_malloc(sizeof(*it));

	if (NULL != it)
	{
		it->mem = ump_dd_from_secure_id(params->secure_id);
		if (UMP_DD_INVALID_MEMORY_HANDLE != it->mem)
		{
			/* found, add it to the session usage list */
			it->id = params->secure_id;
			osk_atomic_set(&it->process_usage_count, 1);
			OSK_DLIST_PUSH_FRONT(&session->memory_usage, it, umpp_session_memory_usage, link);
		}
		else
		{
			/* not found */
			osk_free(it);
			it = NULL;
		}
	}

	osk_mutex_unlock(&session->session_lock);

	return (NULL != it) ? UMP_OK : UMP_ERROR;
}


static mali_error do_ump_dd_release(ukk_call_context * ukk_ctx, ump_uk_release * params)
{
	umpp_session * session;
	umpp_session_memory_usage * it;
	mali_error result = UMP_ERROR;

	session = CONTAINER_OF(ukk_session_get(ukk_ctx), umpp_session, ukk_session);

	osk_mutex_lock(&session->session_lock);

	/* only do a release if found on the session list */
	OSK_DLIST_FOREACH(&session->memory_usage, umpp_session_memory_usage, link, it)
	{
		if (it->id == params->secure_id)
		{
			/* found, a valid call */
			result = UMP_OK;

			if (0 == osk_atomic_dec(&it->process_usage_count))
			{
				/* last ref in this process remove from the usage list and remove the underlying ref */
				OSK_DLIST_REMOVE(&session->memory_usage, it, link);
				ump_dd_release(it->mem);
				osk_free(it);
			}

			break;
		}
	}
	
	osk_mutex_unlock(&session->session_lock);

	return result;
}

static mali_error do_ump_dd_sizequery(ukk_call_context * ukk_ctx, ump_uk_sizequery * params)
{
	umpp_session * session;
	umpp_session_memory_usage * it;
	mali_error result = UMP_ERROR;

	session = CONTAINER_OF(ukk_session_get(ukk_ctx), umpp_session, ukk_session);

	osk_mutex_lock(&session->session_lock);

	/* only valid if found on the session list */
	OSK_DLIST_FOREACH(&session->memory_usage, umpp_session_memory_usage, link, it)
	{
		if (it->id == params->secure_id)
		{
			/* found, a valid call */
			params->size = ump_dd_size_get(it->mem);
			result = UMP_OK;
			break;
		}

	}
	osk_mutex_unlock(&session->session_lock);

	return result;
}

static mali_error do_ump_dd_resize(ukk_call_context * ukk_ctx, ump_uk_resize * params)
{
	umpp_session * session;
	umpp_session_memory_usage * it;
	mali_error result = UMP_ERROR;

	session = CONTAINER_OF(ukk_session_get(ukk_ctx), umpp_session, ukk_session);

	osk_mutex_lock(&session->session_lock);

	/* only valid if found on the session list */
	OSK_DLIST_FOREACH(&session->memory_usage, umpp_session_memory_usage, link, it)
	{
		if (it->id == params->secure_id)
		{
			/* found, attempt the call */
			result = ump_dd_resize(it->mem, params->size_diff, &params->new_size);
			break;
		}

	}
	osk_mutex_unlock(&session->session_lock);

	return result;

}

static mali_error do_ump_dd_msync_now(ukk_call_context * ukk_ctx, ump_uk_msync * params)
{
	umpp_session * session;
	umpp_session_memory_usage * it;
	mali_error result = UMP_ERROR;

	session = CONTAINER_OF(ukk_session_get(ukk_ctx), umpp_session, ukk_session);

	osk_mutex_lock(&session->session_lock);

	/* only valid if found on the session list */
	OSK_DLIST_FOREACH(&session->memory_usage, umpp_session_memory_usage, link, it)
	{
		if (it->id == params->secure_id)
		{
			/* found, do the cache op */
#if 0
			/* waiting for OSK api as requested in MIDBASE-515 */
#if defined CONFIG_64BIT && CONFIG_64BIT
			if (is_compat_task())
			{
				umpp_dd_cpu_msync_now(it->mem, params->cache_operation, params->mapped_ptr.compat_value, params->size);
				result = UMP_OK;
			}
			else
			{
#endif
#endif
				umpp_dd_cpu_msync_now(it->mem, params->cache_operation, params->mapped_ptr.value, params->size);
				result = UMP_OK;
#if 0
				/* waiting for OSK api as requested in MIDBASE-515 */
#if defined CONFIG_64BIT && CONFIG_64BIT
			}
#endif
#endif
			break;
		}
	}
	osk_mutex_unlock(&session->session_lock);

	return result;
}

mali_error ump_dispatch(ukk_call_context *ukk_ctx, void *args, u32 args_size)
{
	uk_header *header = (uk_header *)args;

	switch (header->id)
	{
		case UMP_FUNC_ALLOCATE:
			header->ret = do_ump_dd_allocate(ukk_ctx, args);
			return MALI_ERROR_NONE;
		
		case UMP_FUNC_RESIZE:
			header->ret = do_ump_dd_resize(ukk_ctx, args);
			return MALI_ERROR_NONE;

		case UMP_FUNC_SIZEQUERY:
			header->ret = do_ump_dd_sizequery(ukk_ctx, args);
			return MALI_ERROR_NONE;

		case UMP_FUNC_MSYNC:
			header->ret = do_ump_dd_msync_now(ukk_ctx, args);
			return MALI_ERROR_NONE;

#if 0
			/* not used by Linux */
		case UMP_FUNC_MAP:
			header->ret = do_ump_dd_map(ukk_ctx, args);
			return MALI_ERROR_NONE;

			/* not used by Linux */
		case UMP_FUNC_UNMAP:
			header->ret = do_ump_dd_unmap(ukk_ctx, args);
			return MALI_ERROR_NONE;
#endif
		case UMP_FUNC_RETAIN:
			header->ret = do_ump_dd_retain(ukk_ctx, args);
			return MALI_ERROR_NONE;

		case UMP_FUNC_RELEASE:
			header->ret = do_ump_dd_release(ukk_ctx, args);
			return MALI_ERROR_NONE;

		default:
			/* not ours */
			return !MALI_ERROR_NONE;
	}
}

