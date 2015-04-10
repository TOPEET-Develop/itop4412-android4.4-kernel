/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/** @file mali_base_types.h */

#ifndef _BASE_TYPES_H_
#define _BASE_TYPES_H_

/**
 * @brief Mali driver context type
 *
 * A base driver context represents a GPU virtual address space.
 * Using the base context one can allocate memory and run jobs which
 * references the memory.  A job can't reference memory allocated from
 * two different base contexts.
 */
typedef struct base_context base_context;

#include <cutils/linked_list/mali_cutils_dlist.h>
#include <base/mali_base_kernel.h>
#include <base/mali_base_memory.h>
#include <base/mali_base_jd.h>
#include <osu/mali_osu.h>
#include <uk/mali_uku.h>

/**
 * @addtogroup base_api
 * @{
 */

/**
 * @addtogroup base_user_api
 * @{
 */

/* Implementation dependent structures. Not part of the API. */
struct basep_jd_context
{
	cutils_dlist            bag_list;

	size_t                  tb_size; /* register trace buffer size */
	void                    *tb;     /* register trace buffer mapping */

	void                    *pool;
	size_t                  size;
	size_t                  head;
	size_t                  tail;
	u32                     sem[BASEP_JD_SEM_ARRAY_SIZE]; /* 1 = free, 0 = busy */
	osu_mutex               lock;
};

struct base_context
{
	struct basep_jd_context  jd_context;
	/* Should be attached to the fd, kernel side. */
	uku_context              uk_ctx;
	/* Shutdown semaphore */
	osu_sem	                 shutdown_sem;
	/* When the kernel event system is disabled no more jobs may be dispatched */
	mali_bool                dispatch_disabled;

	/* GPU Property information */
	struct mali_base_gpu_props *gpu_props;
};

/** @} end group base_user_api */
/** @} end group base_api */

#endif /* _BASE_TYPES_H_ */
