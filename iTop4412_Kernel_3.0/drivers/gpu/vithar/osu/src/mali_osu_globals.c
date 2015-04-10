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
 * @file mali_osu_globals.c
 * Storage for globals common to every OS
 */

#include <osu/mali_osu.h>
#include <cdbg/mali_cdbg.h>

/*
 * A compile-time assert is made on the array size. For this to work, we must
 * declare the array as having an unknown size. See osup_globals_compile_time_asserts().
 * The lock order for all the enumeration identifiers of @ref osu_static_mutex_id are added to 
 * the lock order array. The enum values are used as array index.
 */
const osu_lock_order osup_static_mutex_lock_order[] =
{
	OSU_LOCK_ORDER_STATIC_BASE_ONETIME_INIT,
	OSU_LOCK_ORDER_STATIC_CDBG_ONETIME_INIT,
	OSU_LOCK_ORDER_STATIC_CDBG_NO_REENTRY,
	OSU_LOCK_ORDER_STATIC_UMP_GLOBAL_STATE,
	OSU_LOCK_ORDER_STATIC_EGL_DISPLAY
};

#if 0 == BDBG_DISABLE_ASSERTS
void osup_globals_compile_time_asserts( void )
{
	/*
	 * We use this assert, because "If the array has fixed size ... if there
	 * are fewer [initializers than members of the array], the trailing members
	 * are initialized with 0".
	 */
	CDBG_COMPILE_ASSERT( OSU_STATIC_MUTEX_COUNT == NELEMS(osup_static_mutex_lock_order) );
}
#endif
