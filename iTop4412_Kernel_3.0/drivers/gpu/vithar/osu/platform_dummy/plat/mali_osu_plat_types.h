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
 * @file mali_osu_types.h
 * Platform-specific types for the OSU module
 */
#ifndef _OSU_PLAT_TYPES_H_
#define _OSU_PLAT_TYPES_H_

#include <pthread.h>
#include <semaphore.h>

#if MALI_UNIT_IMPOSTERS
	#include "osu/tests/internal/unit_tests/imposters/mali_base_osu_pthread_imposter.h"
#endif
typedef struct osup_platform_thread
{
	pthread_t	thr;
} osup_platform_thread;

typedef pthread_t osup_platform_thread_id;

typedef struct osup_platform_sem
{
	sem_t		sem;
} osup_platform_sem;

typedef struct osup_platform_mutex
{
#if BDBG_DISABLE_ASSERTS == 0
	struct osup_platform_mutex	*next;
	osu_lock_order			order;
#endif
	pthread_mutex_t			lock;
} osup_platform_mutex;

typedef osup_platform_mutex osup_platform_spinlock;

#endif
