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
 * @file mali_osu_globalenums.h
 * DDK-Global OSU Enumerations
 */

#ifndef _OSU_GLOBALENUMS_H_
#define _OSU_GLOBALENUMS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \addtogroup osuapi
 * @{
 */

/**
 * \addtogroup osumutex
 * @{
 */

/**
 * @brief Identifiers for osu_mutex_static_get().
 *
 * Any part of the DDK may allocate a Static Mutex by adding an enumeration to
 * this type.
 *
 * The lock order of the mutex must be added to:
 * - @ref osu_lock_order
 * - The @ref osup_static_mutex_lock_order array
 *
 * Refer to the enumeration identifiers prefixed with 'OSU_LOCK_ORDER_STATIC_'
 * in @ref osu_lock_order, and @ref osup_static_mutex_lock_order itself.
 */
typedef enum
{
	/**
	 * The static mutex used for Base 'One-time' init.
	 */
	OSU_STATIC_MUTEX_BASE_ONETIME_INIT = 0,

	/**
	 * The static mutex used for CDBG 'One-time' init.
	 * @since 1.5
	 */
	OSU_STATIC_MUTEX_CDBG_ONETIME_INIT,

	/**
	 * Another static mutex used for CDBG 'One-time' init.
	 * @since 1.8
	 */
	OSU_STATIC_MUTEX_CDBG_NO_REENTRY,

	/**
	 * The static mutex used for UMP global state locking.
	 * @since 2.1
	 */
	OSU_STATIC_MUTEX_UMP_GLOBAL_STATE,

	/**
	* The static mutex used for locking the display in EGL. Used to prevent a situation where
	* eglTerminate() and other entrypoint using the same display are being executed at the same time
	* in different threads.
	*/
	OSU_STATIC_MUTEX_EGL_DISPLAY,

	/**
	 * The number of static mutexes present. Must be the last in the enum.
	 */
	OSU_STATIC_MUTEX_COUNT
} osu_static_mutex_id;

/**
 * @brief Lock orders for osu_mutex_init() and osu_spinlock_init()
 *
 * Locks must be obtained from highest (first) order to lowest (last) order,
 * to prevent deadlocks. Locks are permitted to share the same order,
 * providing they are not obtained at the same time.
 *
 * Refer to @ref osumutex_lockorder for more information.
 *
 * Enumeration identifiers prefixed with 'OSU_LOCK_ORDER_STATIC_' are reserved
 * for static mutexes - see @ref osu_static_mutex_id and
 * @ref osu_mutex_static_get().
 *
 * @note Lock ordering only manages the sequence of \em obtaining mutexes whilst
 * others are held, and not the sequence in which mutexes are \em created whilst
 * others are held. There are no OSU restrictions on creating mutexes in a
 * certain sequence whilst other mutexes are held.
 */
typedef enum
{
	/**
	 * Reserved mutex order, effectively bypassing any test.
	 * Do not use in production code.
	 */
	OSU_LOCK_ORDER_NONE			= -1,

	/**
	 * Reserved mutex order, indicating that the mutex will be the last to be
	 * locked, and no more DDK mutexes will be obtained whilst this is held.
	 */
	OSU_LOCK_ORDER_LAST = 0,

	/**
	 * Lock order for CDBG failure reentry mutex, reentry mutex should not be locked
	 * before locking failure lock.
	 *
	 * @since 1.8
	 * @deprecated No longer required because the failure simulation mechanism is
	 *             now unlocked before printing debugging information.
	 */
	OSU_LOCK_ORDER_CDBG_FAILURE_REENTRY,

	/**
	 * For failure simulation mechanism (when debugging error recovery paths).
	 *
	 * @since 1.8
	 */
	OSU_LOCK_ORDER_CDBG_FAILURE,

	/**
	 * For debugging features control.
	 *
	 * @since 1.10
	 */
	OSU_LOCK_ORDER_CDBG_CONTROL,

	/**
	 * To prevent debugging initialization recursion.
	 *
	 * @sa OSU_LOCK_ORDER_STATIC_CDBG_ONETIME_INIT
	 * @since 1.8
	 */
	OSU_LOCK_ORDER_STATIC_CDBG_NO_REENTRY,

	/**
	 * Static mutex for "one time" initialization of CDBG.
	 *
	 * The common debugging module can be initialized in any thread on the
	 * first use of CDBG macros, so the lock order of this mutex must be less
	 * than most other mutexes.
	 *
	 * @since 1.5
	 */
	OSU_LOCK_ORDER_STATIC_CDBG_ONETIME_INIT,

	/**
	 * Lock order for Base Channels physical destinations.
	 *
	 * The physical destinations (Stdlib File APIs) do not themselves hold
	 * locks defined in the DDK, neither to they call into other functions that
	 * take DDK-defined locks, and so the lock order of the Physical
	 * Destinations can be the lowest in the DDK.
	 *
	 * Indeed, it needs to have a lower value than the One-time init lock in
	 * Base, because once Portable Debug Channels have been initialized inside
	 * the One-time initialization, debug messaging can be used by other
	 * modules that use one-time initialization
	 *
	 * All Base Channel physical destinations may use the same lock order,
	 * because no two destinations are obtained at the same time by the same
	 * thread 
	 */
	OSU_LOCK_ORDER_BASE_CHANNELS_DESTINATIONS,

	/**
	 * Lock order for the Base Channels Large Conversion Buffer.
	 *
	 * This is a shared buffer between all threads using a channel. It must be
	 * higher than that of OSU_LOCK_ORDER_BASE_CHANNELS_DESTINATIONS.
	 */
	OSU_LOCK_ORDER_BASE_CHANNELS_LARGE_CONVERSION_BUFFER,

	/**
	 * Lock order for the internal mutex used by CUTILS::Ringbuffer, when the
	 * ringbuffer is used by the Base Portable Debug Channels. The lock order
	 * must be lower than that of the channels, because channels are locked
	 * before the ringbuffer's own mutex is obtained.
	 *
	 * Potentially, the lock order for the ringbuffer's internal lock can be
	 * lower than OSU_LOCK_ORDER_BASE_CHANNELS_DESTINATIONS.
	 *
	 * @note IMPORTANT: Ringbuffers created by other code may require a higher
	 * value for the lock order.
	 */
	OSU_LOCK_ORDER_BASE_CHANNELS_RINGBUFFER,

	/* 
	 * Lock orders for the Base Channels channel types (info, warn, error)
	 * must be:
	 * - higher than OSU_LOCK_ORDER_BASE_CHANNELS_LARGE_CONVERSION_BUFFER
	 * - lower than any locks held by code that uses CDBG debug
	 * messages/asserts
	 *
	 * Note: the lock order for spew messages is separate from these, and
	 * higher than KBase. This allows for calls into KBase for hw!=2 builds
	 * whilst the spew channel is locked.
	 */

	/**
	 * Lock order for @ref BASE_CHANNEL_INFO.
	 */
	OSU_LOCK_ORDER_BASE_CHANNELS_INFO,

	/**
	 * Lock order for @ref BASE_CHANNEL_WARN.
	 */
	OSU_LOCK_ORDER_BASE_CHANNELS_WARN,

	/**
	 * Lock order for @ref BASE_CHANNEL_ERROR.
	 */
	OSU_LOCK_ORDER_BASE_CHANNELS_ERROR,

	/**
	 * UMP resize lock.
	 * Lock held while resizing any memory.
	 * Shared lock used by all allocations to avoid having a lock per allocation (32k locks would be expensive)
	 */
	OSU_LOCK_ORDER_UMP_RESIZE_LOCK,

	OSU_LOCK_ORDER_UMP_IDMAP_LOCK,

	OSU_LOCK_ORDER_UMP_SESSION_LOCK,

	/**
	 * Static mutex for UMP global state locking.
	 * UMP only uses UK and CDBG while holding this lock.
	 *
	 * @since 2.1
	 */
	OSU_LOCK_ORDER_STATIC_UMP_GLOBAL_STATE,

	/**
	 * Base kernel base lock order.
	 */
	OSU_LOCK_ORDER_BASE_KERN		= 16,

	/**
	 * For fast queue management, with very little processing and
	 * no other lock held within the critical section.
	 */
	OSU_LOCK_ORDER_BASE_KERN_QUEUE_MGMT	= OSU_LOCK_ORDER_BASE_KERN + 1,

	/**
	 * For register trace buffer access in kernel space
	 */
	OSU_LOCK_ORDER_BASE_KERN_TB		= OSU_LOCK_ORDER_BASE_KERN + 2,

	/**
	 * For modiciation of the MMU mask register, which is done as a read-modify-write
	 */
	OSU_LOCK_ORDER_BASE_KERN_MMU_MASK = OSU_LOCK_ORDER_BASE_KERN + 3,

	/**
	 * For hardware counters collection setup
	 */
	OSU_LOCK_ORDER_BASE_KERN_HWCNT	= OSU_LOCK_ORDER_BASE_KERN + 5,

	/**
	 * AS lock, used to access kbase_as structure.
	 *
	 * This must be held after:
	 * - Job Scheduler Run Pool lock (OSK_LOCK_ORDER_RUNPOOL)
	 *
	 * This is an IRQ lock, and so must be held after all sleeping locks
	 *
	 * @since OSU 1.9
	 */
	OSU_LOCK_ORDER_BASE_KERN_AS = OSU_LOCK_ORDER_BASE_KERN + 8,

	/**
	 * Job Scheduling Run Pool lock
	 *
	 * This must be held after:
	 * - Job Scheduling Context Lock (OSK_LOCK_ORDER_JS_CTX)
	 * - Job Slot management lock (OSK_LOCK_ORDER_JSLOT)
	 *
	 * This is an IRQ lock, and so must be held after all sleeping locks
	 *
	 * @since OSU 1.9
	 */
	OSU_LOCK_ORDER_BASE_KERN_JS_RUNPOOL = OSU_LOCK_ORDER_BASE_KERN + 10,

	/**
	 * For job slot management
	 *
	 * This is an IRQ lock, and so must be held after all sleeping locks
	 */
	OSU_LOCK_ORDER_BASE_KERN_JSLOT_MGMT	= OSU_LOCK_ORDER_BASE_KERN + 12,

	/**
	 * Job Scheduling Policy Queue lock
	 *
	 * This must be held after Job Scheduling Context Lock (OSK_LOCK_ORDER_JS_CTX).
	 *
	 * Currently, there's no restriction on holding this at the same time as the  JSLOT/JS_RUNPOOL locks - but, this doesn't happen anyway.
	 *
	 * @since OSU 1.9
	 */
	OSU_LOCK_ORDER_BASE_KERN_JS_QUEUE = OSU_LOCK_ORDER_BASE_KERN + 15,

	/**
	 * For memory mapping management
	 */
	OSU_LOCK_ORDER_BASE_KERN_MEM_REG	= OSU_LOCK_ORDER_BASE_KERN + 20,
	
	/**
	 * Old name to keep until kbase is merged
	 */
	OSU_LOCK_ORDER_BASE_KERN_MEM_MAP        = OSU_LOCK_ORDER_BASE_KERN_MEM_REG,

	/**
	 * Job Scheduling Context Lock
	 *
	 * This must be held after Job Dispatch lock (OSK_LOCK_ORDER_JCTX), but before:
	 * - The Job Slot lock (OSK_LOCK_ORDER_JSLOT)
	 * - The Run Pool lock (OSK_LOCK_ORDER_JS_RUNPOOL)
	 * - The Policy Queue lock (OSK_LOCK_ORDER_JS_QUEUE)
	 *
	 * In addition, it must be held before the VM Region Lock (OSK_LOCK_ORDER_MEM_REG),
	 * because at some point need to modify the MMU registers to update the address
	 * space on scheduling in the context.
	 *
	 * @since OSU 1.9
	 */
	OSU_LOCK_ORDER_BASE_KERN_JS_CTX = OSU_LOCK_ORDER_BASE_KERN + 28,


	/**
	 * For job dispatch management
	 */
	OSU_LOCK_ORDER_BASE_KERN_JDISP_CTXT	= OSU_LOCK_ORDER_BASE_KERN + 30,

	/* End of OSU_LOCK_ORDER_BASE_KERN Range */



	/**
	 * Lock order for @ref BASE_CHANNEL_SPEW. This must be the highest of the
	 * channels, to allow debug messaging whilst a spew lock is held
	 *
	 * @note This has a higher order than the Base Kernel (KBase) locks, to
	 * allow the kernel side to be called by a thread whilst it has the spew
	 * channel locked. This only affects buildling KBase for user-side (hw!=2).
	 *
	 * @note Since OSK does not provide an API for doing Spew Debug messages,
	 * KBase cannot use the Spew channel anyway, and so there is no lost
	 * functionality in preventing KBase from using Spew Debug messages.
	 */
	OSU_LOCK_ORDER_BASE_CHANNELS_SPEW,

	/**
	 * Base user base lock order.
	 */
	OSU_LOCK_ORDER_BASE_USER		= 128,

	/**
	 * For ring-buffer and JC dependency management
	 */
	OSU_LOCK_ORDER_BASE_USER_JDISP_CTXT	= OSU_LOCK_ORDER_BASE_USER,

	/**
	 * For locking CMAR context object lists whilst operating on them.
	 *
	 * @since 3.0.
	 */
	OSU_LOCK_ORDER_CMAR_CONTEXT_CREATE_OBJECT,

	/**
	 * For locking CMAR flush chains and render signals.
	 *
	 * @since 3.0.
	 */
	OSU_LOCK_ORDER_CMAR_TUBE,

	/**
	 * For locking a CMAR event's status
	 *
	 * @since 3.0.
	 */
	OSU_LOCK_ORDER_CMAR_EVENT_STATUS,

	/**
	 * For locking a CMAR command's dependency list.
	 *
	 * @since 4.0
	 */
	OSU_LOCK_ORDER_CMAR_DEPENDENCY_LIST,

	/**
	 * For locking a CMAR command queue's last blocking event.
	 *
	 * @since 3.0.
	 */
	OSU_LOCK_ORDER_CMAR_LAST_BLOCKING_EVENT,

	/**
	 * For locking a CMAR command queue's pending flush chain.
	 *
	 * @since 3.0.
	 */
	OSU_LOCK_ORDER_CMAR_PENDING,

	/**
	 * @brief For locking COBJ templates and instances.
	 *
	 * @since 1.7
	 */
	OSU_LOCK_ORDER_COBJ_OBJECT,

	/**
	 * For locking GLES fragment shaders.
	 *
	 * @since 1.5.
	 */
	OSU_LOCK_ORDER_GLES_FRAGMENT_SHADER,

	/**
	 * For locking GLES vertex shaders.
	 *
	 * @since 1.5.
	 */
	OSU_LOCK_ORDER_GLES_VERTEX_SHADER,

	/**
	 * For locking GLES programs.
	 *
	 * @since 1.4.
	 */
	OSU_LOCK_ORDER_GLES_PROGRAM,

	/**
	 * For locking individual GLES texture masters.
	 *
	 * @since 1.2.
	 */
	OSU_LOCK_ORDER_GLES_OBJECT_MASTER,

	/**
	 * For locking GLES share lists.
	 *
	 * @since 1.3.
	 */
	OSU_LOCK_ORDER_GLES_OBJECT_LIST,

	/**
	 * For locking CL memory object destructor callback lists.
	 */
	OSU_LOCK_ORDER_CL_MEM_CALLBACK_LIST,

	/**
	 *	For locking VG objects
	 */
	OSU_LOCK_ORDER_VG_OBJECT,

	/**
	 * 	For locking VG shared handle list
	 */
	OSU_LOCK_ORDER_VG_HANDLE_LIST,

	/**
	 * Static mutex for "One-time initialization", used by CCTX for one-time
	 * initialization. It's unlikely that any non-static mutexes can be created
	 * before CCTX init, so this is safe as an 'obtained first' lock.
	 */
	OSU_LOCK_ORDER_STATIC_BASE_ONETIME_INIT,

	/*
	 * The static mutex used for locking the display in EGL. Used to prevent a situation where
	 * eglTerminate() and other entrypoint using the same display are being executed at the same time
	 * in different threads.
	 */
	OSU_LOCK_ORDER_STATIC_EGL_DISPLAY,

	/**
	 * Reserved mutex order, indicating that the mutex will be the first to be
	 * locked, and all other DDK mutexes are obtained after this one.
	 */
	OSU_LOCK_ORDER_FIRST = 0x7FFFFFFF
} osu_lock_order;

/* @} end group osumutex */

/* @} End of group osuapi */


#ifdef __cplusplus
}
#endif

#endif /* _OSU_GLOBALENUMS_H_ */
