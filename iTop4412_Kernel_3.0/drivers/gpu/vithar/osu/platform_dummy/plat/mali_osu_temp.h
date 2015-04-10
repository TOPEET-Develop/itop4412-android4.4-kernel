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
 * @file mali_osu_temp.h
 * Temporaray set of inline-to-non-inline wrapper functions
 */
#ifndef _OSU_TEMP_H_
#define _OSU_TEMP_H_

/* #includes go here */

#include <base/mali_base_debug.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Function prototypes */
u32 osu_noninline_atomic_sub( osu_atomic *atom, u32 value );
u32 osu_noninline_atomic_add( osu_atomic *atom, u32 value );
void osu_noninline_atomic_set( osu_atomic *atom, u32 val );
u32 osu_noninline_atomic_get( const osu_atomic *atom );
u32 osu_noninline_atomic_compare_and_swap( osu_atomic *atom, u32 old_value, u32 new_value );
void osu_noninline_thread_data_set( void *value );
void *osu_noninline_thread_data_get(void);
osu_thread_id osu_noninline_thread_get_current_id(void);
mali_bool osu_noninline_thread_id_match( osu_thread_id t1, osu_thread_id t2);
osu_errcode osu_noninline_thread_create(osu_thread *thread, osu_threadproc threadproc,
							  void *start_param, osu_thread_priority priority);
void osu_noninline_thread_wait(osu_thread *thread, void **exitcode);
osu_errcode osu_noninline_sem_init(osu_sem *sem, u32 value);
void osu_noninline_sem_term(osu_sem *sem);
osu_errcode osu_noninline_sem_wait(osu_sem *sem, u64 timeout_nsec);
void osu_noninline_sem_post(osu_sem *sem);
osu_errcode osu_noninline_mutex_init(osu_mutex *mutex, osu_lock_order order);
void osu_noninline_mutex_term(osu_mutex *mutex);
void osu_noninline_mutex_lock(osu_mutex *mutex);
void osu_noninline_mutex_unlock(osu_mutex *mutex);
osu_mutex *osu_noninline_mutex_static_get(osu_static_mutex_id id);
osu_errcode osu_noninline_spinlock_init(osu_spinlock *lock, osu_lock_order order);
void osu_noninline_spinlock_term(osu_spinlock *lock);
void osu_noninline_spinlock_lock(osu_spinlock *lock);
void osu_noninline_spinlock_unlock(osu_spinlock *lock);
u64 osu_noninline_get_time_nsec(void);
osu_errcode osu_noninline_cpu_props_get(osu_cpu_props *props);

#if CDBG_SIMULATE_FAILURES
void osu_noninline_debug_failure_flag_set( void *value );
void *osu_noninline_debug_failure_flag_get(void);
#endif


#if 0
static INLINE u32 osu_atomic_sub( osu_atomic *atom, u32 value )
{
	BDBG_ASSERT_POINTER(atom);

	return osu_noninline_atomic_sub( atom, value );
}

static INLINE u32 osu_atomic_add( osu_atomic *atom, u32 value )
{
	BDBG_ASSERT_POINTER(atom);

	return osu_noninline_atomic_add( atom, value );
}

static INLINE void osu_atomic_set( osu_atomic *atom, u32 val )
{
	BDBG_ASSERT_POINTER(atom);

	osu_noninline_atomic_set( atom, val );
}

static INLINE u32 osu_atomic_get( const osu_atomic *atom )
{
	BDBG_ASSERT_POINTER(atom);

	return osu_noninline_atomic_get( atom );
}

static INLINE u32 osu_atomic_compare_and_swap( osu_atomic *atom, u32 old_value, u32 new_value )
{
	BDBG_ASSERT_POINTER(atom);

	return osu_noninline_atomic_compare_and_swap( atom, old_value, new_value );
}
#endif
static INLINE void osu_thread_data_set( void *value )
{
	osu_noninline_thread_data_set( value );
}

static INLINE void *osu_thread_data_get(void)
{
	return osu_noninline_thread_data_get();
}
#if CDBG_SIMULATE_FAILURES
static INLINE void osu_debug_failure_flag_set( void *value )
{
	osu_noninline_debug_failure_flag_set( value );
}

static INLINE void *osu_debug_failure_flag_get(void)
{
	return osu_noninline_debug_failure_flag_get();
}
#endif
static INLINE osu_thread_id osu_thread_get_current_id(void)
{
	return osu_noninline_thread_get_current_id();
}

static INLINE mali_bool osu_thread_id_match( osu_thread_id t1, osu_thread_id t2)
{
	return osu_noninline_thread_id_match( t1, t2 );
}

static INLINE osu_errcode osu_thread_create(osu_thread *thread, osu_threadproc threadproc,
											void *start_param, osu_thread_priority priority)
{
	BDBG_ASSERT_POINTER(thread);
	BDBG_ASSERT_POINTER(threadproc);

	return osu_noninline_thread_create( thread, threadproc, start_param, priority );
}

static INLINE void osu_thread_wait(osu_thread *thread, void **exitcode)
{
	BDBG_ASSERT_POINTER(thread);

	osu_noninline_thread_wait( thread, exitcode );
}

static INLINE osu_errcode osu_sem_init(osu_sem *sem, u32 value)
{
	if ( BDBG_SIMULATE_FAILURE( CDBG_OSU ) )
	{ 
		return OSUP_ERR_FAULT;
	}
	else
	{
		BDBG_ASSERT_POINTER(sem);

		return osu_noninline_sem_init( sem, value );
	}
}

static INLINE void osu_sem_term(osu_sem *sem)
{
	BDBG_ASSERT_POINTER(sem);

	osu_noninline_sem_term( sem );
}

static INLINE osu_errcode osu_sem_wait(osu_sem *sem, u64 timeout_nsec)
{
	BDBG_ASSERT_POINTER(sem);

	return osu_noninline_sem_wait( sem, timeout_nsec );
}

static INLINE void osu_sem_post(osu_sem *sem)
{
	BDBG_ASSERT_POINTER(sem);

	osu_noninline_sem_post( sem );
}

static INLINE osu_errcode osu_mutex_init(osu_mutex *mutex, osu_lock_order order)
{
	BDBG_ASSERT_POINTER(mutex);

	return osu_noninline_mutex_init( mutex, order );
}

static INLINE void osu_mutex_term(osu_mutex *mutex)
{
	BDBG_ASSERT_POINTER(mutex);

	osu_noninline_mutex_term( mutex );
}

static INLINE void osu_mutex_lock(osu_mutex *mutex)
{
	BDBG_ASSERT_POINTER(mutex);

	osu_noninline_mutex_lock( mutex );
}

static INLINE void osu_mutex_unlock(osu_mutex *mutex)
{
	BDBG_ASSERT_POINTER(mutex);

	osu_noninline_mutex_unlock( mutex );
}

static INLINE osu_mutex *osu_mutex_static_get(osu_static_mutex_id id)
{
	return osu_noninline_mutex_static_get( id );
}

static INLINE osu_errcode osu_spinlock_init(osu_spinlock *lock, osu_lock_order order)
{
	BDBG_ASSERT_POINTER(lock);

	return osu_noninline_spinlock_init( lock, order );
}

static INLINE void osu_spinlock_term(osu_spinlock *lock)
{
	BDBG_ASSERT_POINTER(lock);

	osu_noninline_spinlock_term( lock );
}

static INLINE void osu_spinlock_lock(osu_spinlock *lock)
{
	BDBG_ASSERT_POINTER(lock);

	osu_noninline_spinlock_lock( lock );
}

static INLINE void osu_spinlock_unlock(osu_spinlock *lock)
{
	BDBG_ASSERT_POINTER(lock);

	osu_noninline_spinlock_unlock( lock );
}

static INLINE u64 osu_get_time_nsec(void)
{
	return osu_noninline_get_time_nsec();
}

static INLINE osu_errcode osu_cpu_props_get(osu_cpu_props *props)
{
	BDBG_ASSERT_POINTER(props);

	return osu_noninline_cpu_props_get( props );
}

#ifdef __cplusplus
}
#endif

#endif /* _OSU_TEMP_H_ */
