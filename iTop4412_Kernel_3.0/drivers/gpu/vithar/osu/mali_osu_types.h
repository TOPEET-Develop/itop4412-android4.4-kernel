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
 * Defines the types for OSU.
 *
 * These must be available before <plat/mali_osu_platform.h> is included.
 */

#ifndef _OSU_TYPES_H_
#define _OSU_TYPES_H_

#include <osu/mali_osu_compatibility.h>
#include <osu/mali_osu_globalenums.h>
#include <plat/mali_osu_plat_types.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup base_api
 * @{
 */

/**
 * @addtogroup osuapi
 * @{
 */

/**
 * @brief OSU Error return type
 *
 * This is used for OSU functions where it is more natural to return 0 for
 * success, and non-zero for failure. This avoids translation to mali_bool when
 * the underlying implementation uses 0 for success.
 *
 * The use is similar to that of mali_bool, in that you should only ever
 * compare with OSU_ERR_OK. Fault codes are any value not equal to
 * OSU_ERR_OK.
 *
 */
typedef int osu_errcode;

/** 
 * @brief Generic success error code for OSU apis, \b guarenteed to be zero.
 */
#define OSU_ERR_OK      ((osu_errcode)0)

/** 
 * @brief Private generic fault error code for OSU apis.
 *
 * @note This should only be used by OSU implementations, and \b not by the
 * caller of the OSU API. To check for a fault, compare for not equal to
 * OSU_ERR_OK instead.
 */
#define OSUP_ERR_FAULT  ((osu_errcode)1)


/**
 * @addtogroup osuatomic
 * @{
 */

/** @brief Public type of atomic variables.
 *
 * This is public for allocation on stack. It always implements exactly 32 bits
 * of unsigned integer storage.
 */
typedef struct osu_atomic
{
	struct
	{
		volatile u32 val;
	} osup_internal_struct;
} osu_atomic;
/** @} end group osuatomic */

/**
 * @addtogroup osuthread
 * @{
 */

/** @brief Type for thread structure.
 * This structure has public visibility to allow OSU clients to embed it in
 * their own data structures. It is padded so that it is the same size
 * regardless of the target OS. This allows clients to layout structures that
 * contain OSU primitives in such a way that they are D-Cacheline efficient, on
 * all target OSs.
 *
 * You must not attempt to make your own copies of this structure, nor should
 * you attempt to move its location.
 */
typedef union osu_thread
{
	osup_platform_thread osup_internal_struct;
	char padding[OSUP_PLATFORM_THREAD_STRUCT_PADDING];
} osu_thread;

/** @brief Entry point for a thread.
 *
 * @param arg pointer to an object passed on to thread entry point
 */
typedef void * (*osu_threadproc)(void *arg);

/** @brief Type for a thread ID.
 * This is an opaque type abstracting how a particular OS represents a thread ID.
 */
typedef osup_platform_thread_id osu_thread_id;

/** @brief Enumeration for thread priorities.
 * Used by osu_thread_create() to choose the priority for created threads.
 */
typedef enum
{
	/** The 'default' thread priority, as determined by the system. This may
	 * depend on the priority of the caller thread. */
	OSU_THREAD_PRIORITY_DEFAULT,

	/** A High thread priority for the system */
	OSU_THREAD_PRIORITY_HIGH,

	/** A Low thread priority for the system */
	OSU_THREAD_PRIORITY_LOW
} osu_thread_priority;

/** @} end group osuthread */

/**
 * @addtogroup osusync
 * @{
 */

/** @brief Type for semaphore structure.
 * This structure has public visibility to allow OSU clients to embed it in
 * their own data structures. It is padded so that it is the same size
 * regardless of the target OS. This allows clients to layout structures that
 * contain OSU primitives in such a way that they are D-Cacheline efficient, on
 * all target OSs.
 *
 * You must not attempt to make your own copies of this structure, nor should
 * you attempt to move its location.
 */
typedef union osu_sem
{
	osup_platform_sem osup_internal_struct;
	char padding[OSUP_PLATFORM_SEM_STRUCT_PADDING];
} osu_sem;
/** @} end group osusync */

/**
 * @addtogroup osumutex
 * @{
 */

/** @brief Type for mutex structure.
 * This structure has public visibility to allow OSU clients to embed it in
 * their own data structures. It is padded so that it is the same size
 * regardless of the target OS. This allows clients to layout structures that
 * contain OSU primitives in such a way that they are D-Cacheline efficient, on
 * all target OSs.
 *
 * You must not attempt to make your own copies of this structure, nor should
 * you attempt to move its location.
 */
typedef union osu_mutex
{
	osup_platform_mutex osup_internal_struct;
	char padding[OSUP_PLATFORM_MUTEX_STRUCT_PADDING];
} osu_mutex;

/** @brief Type for spinlock structure.
 * This structure has public visibility to allow OSU clients to embed it in
 * their own data structures. It is padded so that it is the same size
 * regardless of the target OS. This allows clients to layout structures that
 * contain OSU primitives in such a way that they are D-Cacheline efficient, on
 * all target OSs.
 *
 * You must not attempt to make your own copies of this structure, nor should
 * you attempt to move its location.
 */
typedef union osu_spinlock
{
	osup_platform_spinlock osup_internal_struct;
	char padding[OSUP_PLATFORM_SPINLOCK_STRUCT_PADDING];
} osu_spinlock;
/** @} end group osumutex */


/**
 * @addtogroup osucpuprops
 * @{
 */

/*
 * CPU Property Flags
 */

/** 
 * @brief CPU Property Flag for osu_cpu_props::cpu_flags, indicating a
 * Little Endian System. If not set in osu_cpu_props::cpu_flags, then the
 * system is Big Endian.
 *
 * The compile-time equivalent is @ref CONFIG_CPU_LITTLE_ENDIAN.
 */
#define OSU_CPU_PROPERTY_FLAG_LITTLE_ENDIAN F_BIT_0

/** @brief Platform Dynamic CPU properties structure */
typedef struct osu_cpu_props {
	u32 nr_cores;            /**< Number of CPU cores */

	/**
	 * CPU page size as a Logarithm to Base 2. The compile-time
	 * equivalent is @ref CONFIG_CPU_PAGE_SIZE_LOG2
	 */
	u32 cpu_page_size_log2;

	/**
	 * CPU L1 Data cache line size as a Logarithm to Base 2. The compile-time
	 * equivalent is @ref CONFIG_CPU_L1_DCACHE_LINE_SIZE_LOG2.
	 */
	u32 cpu_l1_dcache_line_size_log2;

	/**
	 * CPU L1 Data cache size, in bytes. The compile-time equivalient is
	 * @ref CONFIG_CPU_L1_DCACHE_SIZE.
	 *
	 * This CPU Property is mainly provided to implement OpenCL's
	 * clGetDeviceInfo(), which allows the CL_DEVICE_GLOBAL_MEM_CACHE_SIZE
	 * hint to be queried.
	 */
	u32 cpu_l1_dcache_size;

	/**
	 * CPU Property Flags bitpattern.
	 *
	 * This is a combination of bits as specified by the macros prefixed with
	 * 'OSU_CPU_PROPERTY_FLAG_'.
	 */
	u32 cpu_flags;

    /**
	 * Maximum clock speed in MHz.
	 * @usecase 'Maximum' CPU Clock Speed information is required by OpenCL's
	 * clGetDeviceInfo() function for the CL_DEVICE_MAX_CLOCK_FREQUENCY hint.
	 */
	u32 max_cpu_clock_speed_mhz;

	/**
	 * Available memory, in bytes.
	 *
	 * This is required for OpenCL's clGetDeviceInfo() call when
	 * CL_DEVICE_GLOBAL_MEM_SIZE is requested, for OpenCL CPU devices.
	 */
	u64 available_memory_size;
} osu_cpu_props;

/** @} end group osucpuprops */

/*
 *
 * Global Private Variable Declarations
 *
 * These must occur before plat/mali_osu_platform.h is included, and so
 * mali_osu_types.h is the natrual place for it.
 *
 */


/**
 * @addtogroup osumutex
 * @{
 */

/**
 * @brief Lock orders for static mutexes
 *
 * The lock orders for static mutexes are defined in this array, and are common
 * to all platforms.
 *
 * The lock order must be defined \b both in the @ref osu_lock_order enum, \b
 * and in this array.
 *
 * To lookup the lock order for a certain @ref osu_static_mutex_id identifier,
 * use that identifier as the index into this array.
 *
 * A compile-time assert is made on the array size. For this to work, we must
 * declare the array as having an unknown size.
 */
extern const osu_lock_order osup_static_mutex_lock_order[];

/** @} end group osumutex */


/** @} End of group osuapi */

/** @} */ /* end group base_api */

#ifdef __cplusplus
}
#endif

#endif /* _OSU_TYPES_H_ */
