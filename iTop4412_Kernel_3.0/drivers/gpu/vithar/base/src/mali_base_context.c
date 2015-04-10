/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <base/mali_base.h>
#include <stdlib/mali_stdlib.h>

#include "base/src/mali_base_user.h"
#include "base/src/mali_base_uk.h"

/* Function prototypes */
STATIC mali_error basep_alloc_gpu_props( base_context *ctx ) CHECK_RESULT;

/*
 * Private functions
 */

STATIC mali_error basep_alloc_gpu_props( base_context *ctx )
{
	struct mali_base_gpu_props *gpu_props = NULL;
	u32 num_groups;
	u32 gpu_props_size;
	mali_error err;

	if ( BDBG_SIMULATE_FAILURE( CDBG_BASE ) )
	{ 
		return MALI_ERROR_OUT_OF_MEMORY;
	}
	/* 
	 * Calculate the size of the gpu props, based on the number of coherency
	 * groups
	 */

	num_groups = basep_gpu_props_get_num_coherent_groups( ctx );

	/* The size of the gpu props structure with zero groups (one group
	 * implicitly in the structure) */
	gpu_props_size = sizeof( struct mali_base_gpu_props ) - sizeof( struct mali_base_gpu_coherent_group );

	/* Add the number of groups in */
	gpu_props_size += num_groups * sizeof( struct mali_base_gpu_coherent_group );

	gpu_props = ( struct mali_base_gpu_props * )stdlib_malloc( gpu_props_size );
	if ( NULL == gpu_props )
	{
		err = MALI_ERROR_OUT_OF_MEMORY;
		goto err_cleanup;
	}

	err = basep_fill_gpu_props( gpu_props, gpu_props_size, ctx );

	if ( MALI_ERROR_NONE != err )
	{
		goto err_cleanup;
	}

	/* Success, writeout */
	ctx->gpu_props = gpu_props;

	return MALI_ERROR_NONE;

 err_cleanup:
	stdlib_free( gpu_props );
	return err;
}

/*
 * Public functions 
 */

mali_bool base_context_init( base_context *ctx, u32 flags )
{
	int i;
	mali_error err;

	CDBG_ASSERT_POINTER( ctx );

	if (MALI_ERROR_NONE != base_uk_ctx_alloc(ctx, flags))
	{
		goto fail_uk;
	}

	ctx->dispatch_disabled = MALI_FALSE;

	ctx->jd_context.head = 0;
	ctx->jd_context.tail = 0;
	ctx->jd_context.tb = NULL;

	CUTILS_DLIST_INIT(&ctx->jd_context.bag_list);

	for (i = 0; i < BASEP_JD_SEM_ARRAY_SIZE; i++)
		ctx->jd_context.sem[i] = ~(i == 0);

	if (OSU_ERR_OK != osu_mutex_init(&ctx->jd_context.lock, OSU_LOCK_ORDER_BASE_USER_JDISP_CTXT))
	{
		goto fail_mutex;
	}

	err = basep_alloc_gpu_props( ctx );
	if ( MALI_ERROR_NONE != err )
	{
		goto fail_gpu_props;
	}

	return MALI_TRUE;

fail_gpu_props:
	osu_mutex_term(&ctx->jd_context.lock);
fail_mutex:
	base_uk_ctx_terminate(ctx);
	base_uk_ctx_free(ctx);
fail_uk:
	return MALI_FALSE;
}

void base_context_term( base_context *ctx )
{
	CDBG_ASSERT_POINTER( ctx );

	/* Assert if event system hasn't been shutdown yet (using base_jd_event_term()) */
	CDBG_ASSERT_MSG(MALI_TRUE == ctx->dispatch_disabled, "Event system was not shutdown yet with base_jd_event_term()");

	base_uk_ctx_terminate(ctx);
	stdlib_free(ctx->gpu_props);
	base_uk_ctx_free(ctx);
}

