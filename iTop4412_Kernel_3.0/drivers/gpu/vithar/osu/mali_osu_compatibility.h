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
 * @file mali_osu_compatibility.h
 * 
 * File to resolve transient compatibility issues with other modules
 */


#ifndef _OSU_COMPATIBILITY_H_
#define _OSU_COMPATIBILITY_H_

/*
 * Include here any modules whose definitions will be checked for. For example:
 * 
 */

#define OSUP_PLATFORM_THREAD_STRUCT_PADDING 1
#define OSUP_PLATFORM_SEM_STRUCT_PADDING 1
#define OSUP_PLATFORM_MUTEX_STRUCT_PADDING 1
#define OSUP_PLATFORM_SPINLOCK_STRUCT_PADDING 1

#endif /* _OSU_COMPATIBILITY_H_ */
