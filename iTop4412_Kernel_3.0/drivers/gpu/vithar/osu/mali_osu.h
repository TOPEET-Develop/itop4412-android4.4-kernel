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
 * @file mali_osu.h
 * Defines the OS abstraction layer for the base driver
 */

#ifndef _OSU_H_
#define _OSU_H_

#include <malisw/mali_malisw.h>

#include <osu/mali_osu_compatibility.h>

#include <osu/mali_osu_types.h>
#include <plat/mali_osu_platform.h>
#include <base/mali_base_debug.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup base_api
 * @{
 */

/**
 * @defgroup osuapi User-side OSU APIs
 *
 * The OSU abstracts user-side OS functionality associated with threading, synchronization,
 * mutual exclusion and atomic access. It also provides an API that allows a client to discover
 * platform properties such as endianness, CPU page size and CPU cache line size.
 */
/**
 * @addtogroup osuapi
 * @{
 */

/**
 * @defgroup osuthread Threading
 *
 * Functions related to threading
 */

/**
 * @defgroup osusync Synchronization
 *
 * Inter-thread synchronization is based on semaphores. A semaphore is an
 * object with a value that cannot fall below zero. Threads are blocked
 * when calling osu_sem_wait() with a semaphore object that has a
 * value of zero; an OS-specific number of threads can be
 * waiting on the same semaphore object. Threads are released when
 * osu_sem_post() is called from another thread in the same process.
 * A semaphore created in one process cannot be accessed by another
 * process, it can only be used to synchronize between threads in the
 * same process.
 *
 * The value of a semaphore may not exceed S32_MAX.
 */

/**
 * @defgroup osumutex Mutual Exclusion
 *
 * A mutex is used to control access to a shared resource, where only one
 * thread is allowed access at any one time. A thread must lock the mutex
 * to gain access; other threads that attempt to lock the same mutex will
 * block. As with semaphores, mutexes can only be accessed by threads
 * within the same process. Unlike semaphores, where any thread can post,
 * mutexes can only be unlocked by the thread that holds the lock.
 *
 * The OSU provides a fixed number of static mutexes;
 * these are initialized when the process is created. They are provided to
 * cope with the case where a section of code must be run once only, but
 * where more than one thread may attempt to execute the code. In such
 * instances, a mutex initialized by a call to osu_mutex_init() would not
 * be suitable, as one or more threads could succeed in initializing a mutex
 * and locking it.
 * 
 * @note OSU mutexes are intended for use in a situation where access to the
 * shared resource is likely to be contended. OSU mutexes make use of the
 * mutual exclusion primitives provided by the target OS, which often
 * need to perform a user-kernel function call. As such, they are considered
 * "heavyweight".
 *
 * OSU spinlocks are also used to control access to a shared resource and
 * enforce that only one thread has access at any one time. They differ from
 * OSU mutexes in that they poll the mutex in userspace a bounded number of
 * times to obtain the lock. If the spinlock exceeds its bound on spins, then
 * it will revert to the OS's mechanisms for blocking, thus saving cycles.
 * 
 * Spinlocks are considered 'lightweight': for the uncontended cases, the mutex
 * can be obtained quickly. For the lightly-contended cases on Multiprocessor
 * systems, the mutex can be obtained quickly without resorting to
 * "heavyweight" OS primitives. Providing that the mutex is <b>only lightly
 * contended</b> then an expensive user-kernel call can be avoided on all
 * OSs.
 *
 * @anchor osumutex_spinlockdetails
 * @par Important details of OSU Spinlocks.
 *
 * OSU spinlocks are not intended for high-contention cases. However, in
 * contrast to pure-spinlocks, OSU spinlocks have a bounded spin to limit the
 * potential for CPU cycles being wasted in high-contention cases. This means
 * that an occasional high-contention case does not seriously impact
 * performance - it will revert to the OS's mechanism for blocking instead.
 *
 * @note If high-contention usecases occurs frequently for a
 * particular spinlock, then it is wise to consider using an OSU Mutex instead.
 *
 * @note An especially important reason for not using OSU Spinlocks in highly
 * contended cases is that they defeat the OS's Priority Inheritance mechanisms
 * that would normally alleviate Priority Inversion problems. This is because
 * once the spinlock is obtained, the OS usually does not know which thread has
 * obtained the lock, and so cannot know which thread must have its priority
 * boosted to alleviate the Priority Inversion.
 *
 * The bound for the number of spins before blocking on an OS primitive is
 * implementation dependent. On Uniprocessor systems, only a bound of one is
 * sensible.
 *
 * As a guide, use a spinlock when CPU-bound for a short period of time
 * (thousands of cycles). CPU-bound operations include reading/writing of
 * memory or registers. Do not use a spinlock when IO bound (e.g. user input,
 * buffered IO reads/writes, calls involving significant device driver IO
 * calls).
 * 
 * @anchor osumutex_lockorder
 * @par Lock ordering for Mutexes and Spinlocks
 *
 * When an OSU Mutex or Spinlock is initialized, it is given a locking order.
 * This is a number that is checked in QA builds to detect possible deadlock
 * conditions. The order is checked when a thread calls
 * osu_mutex_lock()/osu_spinlock_lock(). If the calling thread already holds a
 * lock with an order less than that of the object being locked, an
 * assertion failure will occur. 
 *
 * Lock ordering must be respected between OSU Mutexes, and OSU
 * Spinlocks. That is, when obtaining an OSU Mutex or Spinlock, its lock order
 * must be lower than any other OSU Mutex held by the current thread, \b and it
 * must be lower than any other OSU Spinlock held by the current thread.
 *
 */

/**
 * @defgroup osuatomic Atomic Access
 *
 * @anchor osuatomic_important
 * @par Important Information on Atomic variables
 *
 * Atomic variables are objects that can be modified by only one thread at a time.
 * For use in SMP systems, strongly ordered access is enforced using memory
 * barriers.
 *
 * An atomic variable implements an unsigned integer counter which is exactly
 * 32 bits long. Arithmetic on it is the same as on u32 values, which is the
 * arithmetic of integers modulo 2^32. For example, incrementing past
 * 0xFFFFFFFF rolls over to 0, decrementing past 0 rolls over to
 * 0xFFFFFFFF. That is, overflow is a well defined condition (unlike signed
 * integer arithmetic in C).
 */

/**
 * @defgroup osucpuprops Dynamic and Platform Config CPU Properties
 *
 * The Platform Config CPU  properties are exposed as pre-processor
 * macros. These macros have the prefix 'CONFIG_CPU_'.
 *
 * Complementing the Platform Config properties are the Dynamic CPU
 * Properties, which can be obtained by calling the osu_cpu_props_get()
 * function.
 *
 * In general, the Dynamic CPU Properties are present to verify that the
 * platform has been configured correctly with the right set of Platform Config
 * CPU Properties.
 *
 * Refer to the <b>User-side Base GPU Property Query API</b> for a discussion
 * on the choice between use of dynamic verses platform config (static)
 * properties.
 */

/**
 * @defgroup osumisc Miscellaneous
 */


/**
 * @brief OSU major version
 */
#define MALI_MODULE_OSU_MAJOR 1

/**
 * @brief OSU minor version
 */
#define MALI_MODULE_OSU_MINOR 10


/**
 * @addtogroup osuatomic
 * @{
 */

/** @brief Subtract a value from an atomic variable and return the new value.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a atom parameter.
 *
 * @note Please refer to @ref osuatomic_important Important Information on Atomic
 * variables.
 *
 * @param atom pointer to an atomic variable
 * @param value value to subtract from \a atom
 * @return value of atomic variable after \a value has been subtracted from it.
 */
static INLINE u32 osu_atomic_sub( osu_atomic *atom, u32 value );

/** @brief Add a value to an atomic variable and return the new value.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a atom parameter.
 *
 * @note Please refer to @ref osuatomic_important Important Information on Atomic
 * variables.
 *
 * @param atom pointer to an atomic variable
 * @param value value to add to \a atom
 * @return value of atomic variable after \a value has been added to it.
 */
static INLINE u32 osu_atomic_add( osu_atomic *atom, u32 value );

/** @brief Decrement an atomic variable and return its decremented value.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a atom parameter.
 *
 * @note This function is provided as a convenience wrapper of
 * osu_atomic_sub(). It does not need to be ported.
 *
 * @note Please refer to @ref osuatomic_important Important Information on Atomic
 * variables.
 *
 * @param atom pointer to an atomic variable
 * @return decremented value of atomic variable
 */
static INLINE u32 osu_atomic_dec( osu_atomic *atom )
{
	BDBG_ASSERT_POINTER(atom);

	return osu_atomic_sub( atom, 1 );
}

/** @brief Increment an atomic variable and return its incremented value.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a atom parameter.
 *
 * @note This function is provided as a convenience wrapper of
 * osu_atomic_add(). It does not need to be ported.
 *
 * @note Please refer to @ref osuatomic_important Important Information on Atomic
 * variables.
 *
 * @param atom pointer to an atomic variable
 * @return incremented value of atomic variable
 */
static INLINE u32 osu_atomic_inc( osu_atomic *atom )
{
	BDBG_ASSERT_POINTER(atom);

	return osu_atomic_add( atom, 1 );
}

/** @brief Initialize the value of an atomic variable.
 *
 * This function allows an atomic variable to be initialized. After
 * initialization, you should not use this when multiple threads could access
 * the atomic variable. Instead, use osu_atomic_compare_and_swap().
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a atom parameter.
 *
 * @note Please refer to @ref osuatomic_important Important Information on Atomic
 * variables.
 *
 * @param atom pointer to an atomic variable
 * @param val the value to set
 */
static INLINE void osu_atomic_set( osu_atomic *atom, u32 val );

/** @brief Return the value of an atomic variable.
 *
 * This function is intended to be used in conjunction with
 * osu_atomic_compare_and_swap() to implement read-modify-write of atomic
 * variables.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a atom parameter.
 *
 * @note Please refer to @ref osuatomic_important Important Information on Atomic
 * variables.
 *
 * @param atom pointer to an atomic variable
 * @return value of the atomic variable
 */
static INLINE u32 osu_atomic_get( const osu_atomic *atom );

/** @brief Compare the value of an atomic variable, and atomically exchange it
 * if the comparison succeeds.
 *
 * This function implements the Atomic Compare-And-Swap operation (CAS). It
 * atomically does the following: compare \a atom with \a old_value and sets \a
 * atom to \a new_value if the comparison was true.
 *
 * Regardless of the outcome of the comparison, the initial value of \a atom is
 * returned - hence the reason for this being a 'swap' operation. If the value
 * returned is equal to \a old_value, then the atomic operation succeeded. Any
 * other value shows that the atomic operation failed, and should be repeated
 * based upon the returned value.
 *
 * This function is intended to be used in conjunction with
 * osu_atomic_get() to implement read-modify-write of atomic
 * variables.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a atom parameter.
 *
 * @note Please refer to @ref osuatomic_important Important Information on Atomic
 * variables.
 *
 * @param atom pointer to an atomic variable
 * @param old_value The value to make the comparison with \a atom
 * @param new_value The value to atomically write to atom, depending on whether
 * the comparison succeeded.
 * @return The \em initial value of \a atom, before the operation commenced.
 */
static INLINE u32 osu_atomic_compare_and_swap( osu_atomic *atom, u32 old_value, u32 new_value );

/** @} end group osuatomic */

/**
 * @addtogroup osuthread
 * @{
 */

/** @brief Set data stored in the TLS slot of the current thread.
 *
 * The TLS slot is allocated at Library Load time, and freed at Library Unload
 * time. This is because a single slot must be allocated into all threads in
 * the process. There is no way for the OS to free this slot on some threads,
 * but not others, hence why the slot is freed at Library Unload time.
 *
 * @note It \b is acceptable to pass NULL into this function, to clear the TLS slot.
 *
 * @note This function is likely to operate slowly on some OSs. Therefore,
 * modules should be designed to avoid making too many TLS calls.
 *
 * @param value The value to store in the slot
 */
static INLINE void osu_thread_data_set( void *value );

/** @brief Get data stored in the TLS slot of the current thread.
 *
 * The TLS slot is allocated at Library Load time, and freed at Library Unload
 * time. This is because a single slot must be allocated into all threads in
 * the process. There is no way for the OS to free this slot on some threads,
 * but not others, hence why the slot is freed at Library Unload time.
 *
 * @note This function is likely to operate slowly on some OSs. Therefore,
 * modules should be designed to avoid making too many TLS calls.
 *
 * @return The value stored in the slot. If the slot has never been set, then
 * the value returned is NULL.
 */
static INLINE void *osu_thread_data_get(void);

/** @brief Get current thread identifier.
 *
 * @return A thread identifier, which is unique for all threads in the
 * current process. For operating systems which do not support the threads within a
 * process model, the identifier is unique to all threads in the system.
 */
static INLINE osu_thread_id osu_thread_get_current_id(void);

/** @brief Test if two thread IDs are the same.
 *
 * @param t1 ID of the first thread
 * @param t2 ID of the second thread
 * @return MALI_TRUE if the thread IDs are the same
 * @return MALI_FALSE if the thread IDs are different
 */
static INLINE mali_bool osu_thread_id_match( osu_thread_id t1, osu_thread_id t2);

/** @brief Create a thread.
 *
 * A new thread is created executing the function \a threadproc with \a start_param passed
 * in as sole argument. The thread finishes when \a threadproc returns.
 *
 * Every thread created by osu_thread_create() must be waited upon exactly
 * once, to fully release the resources associated with it. To do otherwise
 * will cause a leak, even if you can determine by other means that the thread
 * has finished. Refer to osu_thread_wait() for more information.
 *
 * @param thread pointer to storage for the created thread object
 * @param threadproc entry point of the thread
 * @param start_param pointer to object passed as parameter to \a threadproc
 * @param priority Enumeration representing the priority of the created thread.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a thread or \a threadproc parameters.
 *
 * @return OSU_ERR_OK if the thread was created successfully
 * @return a value not equal to OSU_ERR_OK if the thread could not be created
 */
static INLINE osu_errcode osu_thread_create(osu_thread *thread, osu_threadproc threadproc,
											void *start_param, osu_thread_priority priority) CHECK_RESULT;

/** @brief Wait for \a thread to finish.
 *
 * The calling thread is blocked waiting on \a thread to finish. If \a thread refers
 * to a thread that has already finished, the function returns immediately.
 *
 * Every thread created by osu_thread_create() must be waited upon exactly
 * once, to fully release the resources associated with it. To do otherwise
 * will cause a leak, even if you can determine by other means that the thread
 * has finished. For example, calling osu_thread_create() in a loop whilst
 * waiting for each thread to exit by sleeping will cause a memory leak,
 * because osu_thread_wait() has not been used to notify the OS that we no
 * longer require any resources associated with it.
 *
 * It is a programming error for a thread to wait upon itself.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a thread parameter.
 *
 * @illegal It is illegal for more than one thread to call osu_thread_wait() on
 * the same @ref osu_thread value. That is, each osu_thread must be waited upon
 * by exactly one other thread (the main thread cannot be waited upon).
 *
 * @param thread pointer to a thread object
 * @param exitcode pointer to storage for the exit code of the finished thread.
 * This pointer may be NULL if there is no interest in the exit code.
 *
 */
static INLINE void osu_thread_wait(osu_thread *thread, void **exitcode);
/** @} end group osuthread */

/**
 * @addtogroup osusync
 * @{
 */

/** @brief Initialize a semaphore.
 *
 * Initialize a semaphore structure with an initial value of \a value.
 * The client must allocate the memory for the @ref osu_sem
 * structure, which is then populated within this function. If the OS-specific
 * semaphore referenced from the structure cannot be initialized, an error is
 * returned.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a sem parameter.
 *
 * @illegal It is illegal to provide an initial \a value to osu_sem_init() that
 * exceeds S32_MAX.
 *
 * @param sem pointer to a valid semaphore structure
 * @param value Initial value of the semaphore
 * @return OSU_ERR_OK on success
 * @return a value not equal to OSU_ERR_OK if the OS-specific semaphore cannot
 * be initialized 
 */
static INLINE osu_errcode osu_sem_init(osu_sem *sem, u32 value) CHECK_RESULT;

/**
 * @brief Terminate a semaphore.
 *
 * Terminate the semaphore pointed to by \a sem. The OS-specific semaphore
 * referenced from the osu_sem structure is terminated.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a sem parameter.
 *
 * @illegal It is illegal to call osu_sem_term() on a semaphore that has
 * threads blocked on it.
 *
 * @param sem pointer to the semaphore 
 */
static INLINE void osu_sem_term(osu_sem *sem);

/**
 * @brief Block if a semaphore is not signalled.
 *
 * Any thread, and any number of threads can wait on a semaphore to be
 * signalled.
 *
 * If the value of the semaphore pointed to by \a sem is zero, the
 * calling thread blocks if \a timeout_nsec is zero. If the value of the semaphore
 * is non-zero, it is decremented by one and the function returns immediately.
 *
 * When \a timeout_nsec is non-zero and the semaphore is currently non-signalled,
 * then a thread attempting to wait on the semaphore will wait for \a timeout_nsec
 * nanoseconds for the semaphore to become signalled. If the semaphore is
 * signalled before the timeout is exceeded, then the function returns
 * immediately (without waiting for the timeout to be exceeded). If the
 * semaphore was not signalled within the timeout period, then at some point
 * after this time interval, the function will return, whether the semaphore
 * was signalled or not. If the semaphore was not in the signalled state when
 * the function returned, then this is indicated in the error code return
 * value.
 *
 * @note Since not all systems support nanosecond granularity timeouts, the
 * timeout may be internally rounded-up to the system's
 * synchronization-primitive timeout precision. Therefore, this function may
 * wait for longer than expected, but it is guarenteed to wait for a finite
 * time.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a sem parameter.
 *
 * @param sem pointer to the semaphore
 * @param timeout_nsec timeout in nanoseconds to wait for
 * @return if \a timeout_nsec == 0, then OSU_ERR_OK is always returned.
 * @return if \a timeout_nsec != 0, then OSU_ERR_OK indicates that the semaphore
 * was signalled within the timeout period. Otherwise, a value not equal to
 * OSU_ERR_OK indicates that the timeout expired, and the semaphore was not
 * signalled.
 */
static INLINE osu_errcode osu_sem_wait(osu_sem *sem, u64 timeout_nsec);

/**
 * @brief Signal a semaphore
 *
 * If one or more threads are blocked waiting on the semaphore object, one
 * thread is unblocked and allowed to return from its call to
 * osu_sem_wait(). It is not defined which thread is unblocked
 * when more than one thread is waiting.
 *
 * @note It is not defined \em when a waiting thread is unblocked. For example,
 * a thread calling osu_sem_post() followed by osu_sem_wait() may (or may not)
 * consume the signal, preventing other threads from being released. Neither
 * the 'immediately releasing', nor the 'delayed releasing' behavior of
 * osu_sem_post() can be relied upon. If such behavior is required, then you
 * must implement it yourself, such as by using a second synchronization
 * primitve. 
 * 
 * If no threads are waiting, the value of the semaphore
 * object is incremented by one and the function returns immediately.
 *
 * Any thread in the current process can signal a semaphore.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a sem parameter.
 *
 * @illegal It is illegal to call osu_sem_post() on a semaphore in such a way
 * that would cause its value to exceed S32_MAX.
 *
 * @param sem pointer to the semaphore object
 */
static INLINE void osu_sem_post(osu_sem *sem);
 
/** @} end group osusync */

/**
 * @addtogroup osumutex
 * @{
 */

/** @brief Initialize a mutex.
 *
 * Initialize a mutex structure. If the function returns successfully, the
 * mutex is in the unlocked state.
 *
 * The caller must allocate the memory for the @ref osu_mutex
 * structure, which is then populated within this function. If the OS-specific
 * mutex referenced from the structure cannot be initialized, an error is
 * returned.
 *
 * The mutex must be terminated when no longer required, by using
 * osu_mutex_term(). Otherwise, a resource leak may result in the OS.
 *
 * The mutex is initialized with a lock order parameter, \a order. Refer to
 * @ref osumutex_lockorder for more information on Mutex/Spinlock lock
 * ordering.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a mutex parameter.
 *
 * It is a programming error to attempt to initialize a mutex that is
 * currently initialized. This includes the static mutexes returned by
 * osu_mutex_static_get(), which are always initialized.
 *
 * @param mutex pointer to a valid mutex structure
 * @param order the locking order of the mutex
 * @return OSU_ERR_OK on success
 * @return a value not equal to OSU_ERR_OK if the OS-specific mutex cannot be
 * initialized.
 */
static INLINE osu_errcode osu_mutex_init(osu_mutex *mutex, osu_lock_order order) CHECK_RESULT;

/** @brief Terminate a mutex.
 *
 * Terminate the mutex pointed to by \a mutex, which must be
 * a pointer to a valid unlocked mutex. When the mutex is terminated, the
 * OS-specific mutex is freed.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a mutex parameter.
 *
 * It is a programming error to attempt to terminate a mutex that is currently
 * terminated.
 *
 * It is a programming error to terminate the static mutexes returned by
 * osu_mutex_static_get().
 *
 * @illegal It is illegal to call osu_mutex_term() on a locked mutex.
 *
 * @param mutex pointer to the mutex
 */
static INLINE void osu_mutex_term(osu_mutex *mutex);

/** @brief Lock a mutex.
 *
 * Lock the mutex pointed to by \a mutex. If the mutex is currently unlocked,
 * the calling thread returns with the mutex locked. If a second thread
 * attempts to lock the same mutex, it blocks until the first thread
 * unlocks the mutex. If two or more threads are blocked waiting on the first
 * thread to unlock the mutex, it is undefined as to which thread is unblocked
 * when the first thread unlocks the mutex. 
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a mutex parameter.
 *
 * It is a programming error to lock a mutex or spinlock with an order that is
 * higher than any mutex or spinlock held by the current thread. Mutexes and
 * spinlocks must be locked in the order of highest to lowest, to prevent
 * deadlocks. Refer to @ref osumutex_lockorder for more information.
 *
 * It is a programming error to exit a thread while it has a locked mutex.
 *
 * @illegal It is illegal to call osu_mutex_lock() on a mutex that is currently
 * locked by the caller thread. That is, it is illegal for the same thread to
 * lock a mutex twice, without unlocking it in between. 
 *
 * @param mutex pointer to the mutex
 */
static INLINE void osu_mutex_lock(osu_mutex *mutex);

/** @brief Unlock a mutex.
 *
 * Unlock the mutex pointed to by \a mutex. The calling thread must be the
 * same thread that locked the mutex. If no other threads are waiting on the
 * mutex to be unlocked, the function returns immediately, with the mutex
 * unlocked. If one or more threads are waiting on the mutex to be unlocked,
 * then this function returns, and a thread waiting on the mutex can be
 * unblocked. It is undefined as to which thread is unblocked.
 *
 * @note It is not defined \em when a waiting thread is unblocked. For example,
 * a thread calling osu_mutex_unlock() followed by osu_mutex_lock() may (or may
 * not) obtain the lock again, preventing other threads from being
 * released. Neither the 'immediately releasing', nor the 'delayed releasing'
 * behavior of osu_mutex_unlock() can be relied upon. If such behavior is
 * required, then you must implement it yourself, such as by using a second
 * synchronization primitve. 
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a mutex parameter.
 *
 * @illegal It is illegal for a thread to call osu_mutex_unlock() on a mutex
 * that it has not locked, even if that mutex is currently locked by another
 * thread. That is, it is illegal for any thread other than the 'owner' of the
 * mutex to unlock it. And, you must not unlock an already unlocked mutex.
 *
 * @param mutex pointer to the mutex
 */
static INLINE void osu_mutex_unlock(osu_mutex *mutex);

/** @brief Obtain a pointer to a static mutex.
 *
 * Obtain a pointer to a static mutex, initialized when the process was
 * created. Refer to @ref osu_static_mutex_id for the list of registered Static
 * mutexes. Static mutexes are initialized in the unlocked state. The lock
 * order of static mutexes is defined by the enumeration identifiers prefixed
 * with 'OSU_LOCK_ORDER_STATIC_' in @ref osu_lock_order. Refer to
 * @ref osumutex_lockorder for more information on Mutex/Spinlock lock
 * ordering.
 *
 * It is a programming error to pass into \a id numbers outside of the range 0
 * <= id < OSU_STATIC_MUTEX_COUNT.
 *
 * @param id the identifier of the static mutex
 * @return pointer to a mutex or NULL
 */
static INLINE osu_mutex *osu_mutex_static_get(osu_static_mutex_id id);

/** @brief Initialize a spinlock. If the function returns successfully, the
 * spinlock is in the unlocked state.
 *
 * The caller must allocate the memory for the @ref osu_spinlock
 * structure, which is then populated within this function. An OS primitive
 * will be allocated to allow the spinlock to block if it spins for too
 * long. If this OS-specific primitive cannot be initialized, an error is
 * returned.
 *
 * Refer to @ref osumutex_spinlockdetails for important information on
 * OSU Spinlocks, compared with OSU Mutexes.
 *
 * The spinlock must be terminated when no longer required, by using
 * osu_spinlock_term(). Otherwise, a resource leak may result in the OS.
 *
 * The mutex is initialized with a lock order parameter, \a order. Refer to
 * @ref osumutex_lockorder for more information on Mutex/Spinlock lock
 * ordering.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a lock parameter.
 *
 * It is a programming error to attempt to initialize a spinlock that is
 * currently initialized.
 *
 * @param lock pointer to the spinlock
 * @param order the locking order of the mutex
 * @return OSU_ERR_OK on success
 * @return a value not equal to OSU_ERR_OK if the OS-specific mutex cannot be
 * initialized.
 */
static INLINE osu_errcode osu_spinlock_init(osu_spinlock *lock, osu_lock_order order) CHECK_RESULT;

/** @brief Terminate a spinlock.
 *
 * Terminate the spinlock pointed to by \a mutex, which must be
 * a pointer to a valid unlocked spinlock. When the spinlock is terminated,
 * the OS-specific primitive is freed.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a lock parameter.
 *
 * It is a programming error to attempt to terminate a spinlock that is currently
 * terminated.
 *
 * @illegal It is illegal to call osu_spinlock_term() on a locked spinlock.
 *
 * @param lock pointer to the spinlock
 */
static INLINE void osu_spinlock_term(osu_spinlock *lock);

/** @brief Lock a spinlock.
 *
 * Lock the spinlock pointed to by \a lock. If the spinlock is currently unlocked,
 * the calling thread returns quickly with the mutex locked, without using the
 * spinlock's OS primitive. If a second thread attempts to lock the same spinlock,
 * it polls the lock for a bounded number of tries to obtain the lock. Should
 * this bound be exceeded, then the thread blocks on the spinlock's OS
 * primitive until the first thread unlocks the spinlock. If two or more threads
 * are waiting on the first thread to unlock the spinlock, it is undefined as
 * to which thread is unblocked when the first thread unlocks the spinlock.
 *
 * Refer to @ref osumutex_spinlockdetails for important information on
 * OSU Spinlocks, compared with OSU Mutexes.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a lock parameter.
 *
 * It is a programming error to lock a mutex or spinlock with an order that is
 * higher than any mutex or spinlock held by the current thread. Mutexs and
 * spinlocks must be locked in the order of highest to lowest, to prevent
 * deadlocks. Refer to @ref osumutex_lockorder for more information.
 *
 * It is a programming error to exit a thread while it has a locked spinlock.
 *
 * @illegal It is illegal to call osu_spinlock_lock() on a spinlock that is
 * currently locked by the caller thread. That is, it is illegal for the same
 * thread to lock a spinlock twice, without unlocking it in between. 
 *
 * @param lock pointer to the spinlock
 */
static INLINE void osu_spinlock_lock(osu_spinlock *lock);

/** @brief Unlock a spinlock.
 *
 * Unlock the spinlock pointed to by \a lock. The calling thread must be the
 * same thread that locked the spinlock. If no other threads are blocked on the
 * spinlock's OS primitive, the function returns immediately, with the spinlock
 * unlocked. If one or more threads are blocked on the spinlock's OS primitive,
 * this OS primitive is signalled, allowing precisely one thread to be
 * unblocked and obtain the spinlock. It is undefined as to which thread is
 * unblocked.
 *
 * @note It is not defined \em when a waiting thread is unblocked. For example,
 * a thread calling osu_spinlock_unlock() followed by osu_spinlock_lock() may
 * (or may not) obtain the lock again, preventing other threads from being
 * released. Neither the 'immediately releasing', nor the 'delayed releasing'
 * behavior of osu_spinlock_unlock() can be relied upon. If such behavior is
 * required, then you must implement it yourself, such as by using a second
 * synchronization primitve. 
 *
 * Refer to @ref osumutex_spinlockdetails for important information on
 * OSU Spinlocks, compared with OSU Mutexes.
 *
 * It is a programming error to pass an invalid pointer (including NULL)
 * through the \a lock parameter.
 *
 * @illegal It is illegal for a thread to call osu_spinlock_unlock() on a spinlock
 * that it has not locked, even if that spinlock is currently locked by another
 * thread. That is, it is illegal for any thread other than the 'owner' of the
 * spinlock to unlock it. 
 *
 * @param lock pointer to the spinlock
 */
static INLINE void osu_spinlock_unlock(osu_spinlock *lock);

/** @} end group osumutex */

/**
 * @addtogroup osumisc
 * @{
 */

/** @brief Get a timer with at most, nanosecond precision.
 *
 * Intended usage is instrumented functions, and Khronos APIs that specify
 * nanoseconds. Using nanoseconds as units means that the timer will rollover
 * after 584 years.
 *
 * The function is a wrapper to get the time from the system.
 * It either has the precision of nanoseconds, or the precision that is
 * supported by the underlying system - whichever is lower.
 *
 * If the system does not have a timer the function returns Zero.
 *
 * The returned value will be nanoseconds since some platform-dependant date,
 * and so cannot be used as a platform independent way of determining the current
 * time/date. Only the difference in time between two events may be measured.
 *
 * @return A 64bit counter with nanosecond precision, or zero.
 */
static INLINE u64 osu_get_time_nsec(void);

/** @} end group osumisc */

/**
 * @addtogroup osudebug
 * @{
 */

#if CDBG_SIMULATE_FAILURES
/** @brief Call to this function sets the thread specific \c osu_private_tls_key to \c value
 * This function should not be used directly. It is only used in @ref BDBG_SET_FAIL_OFF
 * @ref BDBG_SET_FAIL_ON and @ref BDBG_IS_FAIL_ON
 */
static INLINE void osu_debug_failure_flag_set( void *value );

/** @brief Get the contents for thread specific \c osu_private_tls_key.
 * This function should not be used directly. It is only used in @ref BDBG_SET_FAIL_OFF
 * @ref BDBG_SET_FAIL_ON and @ref BDBG_IS_FAIL_ON
 * @return A value that is present in thread specific slot.
 */
static INLINE void *osu_debug_failure_flag_get(void);
#endif

/** @} end group osudebug */

/**
 * @addtogroup osucpuprops
 * @{
 */


/**
 * @def CONFIG_CPU_PAGE_SIZE_LOG2
 * @brief CPU Physical Page Size, in the form of a Logarithm to base 2.
 * 
 * This property tells you the size of Physical Pages of Memory on the system.
 *
 * The page size in bytes is given by 1<<CONFIG_CPU_PAGE_SIZE_LOG2.
 */

/**
 * @def CONFIG_CPU_L1_DCACHE_LINE_SIZE_LOG2
 * @brief CPU L1 Data Cache Line size, in the form of a Logarithm to base 2.
 *
 * This CPU Property is mainly provided to implement OpenCL's
 * clGetDeviceInfo(), which allows the CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE
 * hint to be queried.
 *
 * The cache line size in bytes is given by
 * 1<<CONFIG_CPU_L1_DCACHE_LINE_SIZE_LOG2.
 * 
 * Do not use this for determining the size of whole items that might be sync'd
 * with memory and the cache  - use @ref CONFIG_CPU_COHERENCY_SIZE_LOG2
 * instead. 
 */

/**
 * @def CONFIG_CPU_L1_DCACHE_SIZE
 * @brief CPU L1 Data Cache size, in bytes.
 *
 * This CPU Property is mainly provided to implement OpenCL's
 * clGetDeviceInfo(), which allows the CL_DEVICE_GLOBAL_MEM_CACHE_SIZE
 * hint to be queried.
 */


/**
 * @def CONFIG_CPU_COHERENCY_SIZE_LOG2
 * @brief Size of whole items in the CPU Cache that will be synced with memory,
 * in the form of a Logarithm to base 2.
 * 
 * This property tells you the size and alignment of data in the CPU Cache that
 * will be synced with main memory. For example, in ARM L1 caches, a single
 * byte written into a cache line will cause the entire cache line to be
 * written back to main memory on a cache flush/cache line eviction. This means
 * that the coherency size is at least that of the L1 cache line size (given by
 * CONFIG_CPU_L1_DCACHE_LINE_SIZE_LOG2), but may be larger depending on the
 * system and OS constraints.
 *
 * The coherency size in bytes is given by 1<<CONFIG_CPU_COHERENCY_SIZE_LOG2.
 */

/**
 * @def CONFIG_CPU_LITTLE_ENDIAN
 * @brief Describes whether the system is a Little Endian or Big Endian
 * system.
 * 
 * When this macro has a non-zero value, it is a Little Endian System.
 * When this macro has a value of zero, it is a Big Endian System.
 */


/** @brief CPU Property Query - Obtain CPU platform properties
 *
 * This function populates a structure with a number of CPU platform properties;
 * many are effectively hard-coded values as many are defined by hardware.
 * It allows clients of the OSU the ability to make run-time decisions
 * depending on how the platform has been configured.
 *
 * @note \e Platform in this context includes any hardware or OS properties
 * that are not concerned with the GPU. GPU properties are queried via a Base
 * driver API.
 *
 * Certain platform properties may vary if osu_cpu_props_get() is called
 * more than once.
 *
 * @param props pointer to a platform properties structure
 * @return On success, OSU_ERR_OK is returned.
 * @return On failure, a value not equal to OSU_ERR_OK is returned, and the
 * structure pointed to by props may contain invalid information.
 */
static INLINE osu_errcode osu_cpu_props_get(osu_cpu_props *props) CHECK_RESULT;
/** @} end group osucpuprops */

/** @} End of group osuapi */

/** @} */ /* end group base_api */

#ifdef __cplusplus
}
#endif

#endif /* _OSU_H_ */
