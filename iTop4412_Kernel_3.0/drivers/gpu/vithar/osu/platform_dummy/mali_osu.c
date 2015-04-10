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
 * @file mali_osu.c
 * Implementation of the osu interfaces
 */

#include <time.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>

#include <malisw/mali_malisw.h>
#include <osu/mali_osu.h>
#include <cdbg/mali_cdbg.h>
#include <base/mali_base_debug.h>

static pthread_key_t osu_user_tls_key;

#if CDBG_SIMULATE_FAILURES
static pthread_key_t osu_private_tls_key;
#endif
#if BDBG_DISABLE_ASSERTS == 0
static pthread_key_t osu_debug_mutex_key;

static __attribute__((constructor)) void osu_debug_mutex_setup(void)
{
	int err = pthread_key_create(&osu_debug_mutex_key, NULL);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
}

static __attribute__((destructor)) void osu_debug_mutex_teardown(void)
{
	int err = pthread_key_delete(osu_debug_mutex_key);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
}

static void osu_mutex_debug_init(osup_platform_mutex *mutex, osu_lock_order order)
{
	mutex->order = order;
	mutex->next = NULL;
}

static void osu_mutex_debug_lock(osup_platform_mutex *mutex)
{
	osup_platform_mutex *osu_debug_mutex_stack;

	if (mutex->order == OSU_LOCK_ORDER_NONE)
		return;

	osu_debug_mutex_stack = pthread_getspecific(osu_debug_mutex_key);
	if (osu_debug_mutex_stack)
	{
		BDBG_ASSERT(osu_debug_mutex_stack->order > mutex->order);
	}

	mutex->next = osu_debug_mutex_stack;
	pthread_setspecific(osu_debug_mutex_key, mutex);
}

static void osu_mutex_debug_unlock(osup_platform_mutex *mutex)
{
	osup_platform_mutex *osu_debug_mutex_stack;

	if (mutex->order == OSU_LOCK_ORDER_NONE)
		return;

	osu_debug_mutex_stack = pthread_getspecific(osu_debug_mutex_key);
	BDBG_ASSERT(osu_debug_mutex_stack == mutex);
	pthread_setspecific(osu_debug_mutex_key, mutex->next);
}

osu_errcode osu_noninline_mutex_init(osu_mutex *mutex, osu_lock_order order)
{
	osu_errcode ret = OSU_ERR_OK;
	pthread_mutexattr_t mutex_attr;

	if (  BDBG_SIMULATE_FAILURE( CDBG_OSU ) )
	{ 
		return OSUP_ERR_FAULT;
	}

	if (pthread_mutexattr_init(&mutex_attr))
	{
		ret = OSUP_ERR_FAULT;
		goto finish;
	}

	if (pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_ERRORCHECK))
	{
		ret = OSUP_ERR_FAULT;
		goto destroy_mutexattr;
	}

	osu_mutex_debug_init(&mutex->osup_internal_struct, order);
	if (pthread_mutex_init(&mutex->osup_internal_struct.lock, &mutex_attr))
	{
		ret = OSUP_ERR_FAULT;
	}

destroy_mutexattr:
	pthread_mutexattr_destroy(&mutex_attr);

finish:
	return ret;
}

osu_errcode osu_noninline_spinlock_init(osu_spinlock *lock, osu_lock_order order)
{
	osu_errcode ret = OSU_ERR_OK;
	pthread_mutexattr_t mutex_attr;

	if (pthread_mutexattr_init(&mutex_attr))
	{
		ret = OSUP_ERR_FAULT;
		goto finish;
	}

	if (pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_ERRORCHECK))
	{
		ret = OSUP_ERR_FAULT;
		goto destroy_mutexattr;
	}

	osu_mutex_debug_init(&lock->osup_internal_struct, order);
	if (pthread_mutex_init(&lock->osup_internal_struct.lock, &mutex_attr))
	{
		ret = OSUP_ERR_FAULT;
	}

destroy_mutexattr:
	pthread_mutexattr_destroy(&mutex_attr);

finish:
	return ret;
}

#else
static INLINE void osu_mutex_debug_init(osup_platform_mutex *mutex, osu_lock_order order)
{
}

static INLINE void osu_mutex_debug_lock(osup_platform_mutex *mutex)
{
}

static INLINE void osu_mutex_debug_unlock(osup_platform_mutex *mutex)
{
}

osu_errcode osu_noninline_mutex_init(osu_mutex *mutex, osu_lock_order order)
{
	osu_errcode ret = OSU_ERR_OK;

	osu_mutex_debug_init(&mutex->osup_internal_struct, order);
	if (pthread_mutex_init(&mutex->osup_internal_struct.lock, NULL))
	{
		ret = OSUP_ERR_FAULT;
	}

	return ret;
}

osu_errcode osu_noninline_spinlock_init(osu_spinlock *lock, osu_lock_order order)
{
	osu_errcode ret = OSU_ERR_OK;

	osu_mutex_debug_init(&lock->osup_internal_struct, order);
	if (pthread_mutex_init(&lock->osup_internal_struct.lock, NULL))
	{
		ret = OSUP_ERR_FAULT;
	}

	return ret;
}

#endif

static osu_mutex static_mutexes[OSU_STATIC_MUTEX_COUNT];

static __attribute__((constructor)) void osu_startup(void)
{
	int i;
	int err = pthread_key_create(&osu_user_tls_key, NULL);
	BDBG_PRINT_ERROR_ON(err != 0, BDBG_OSU, "Failed to setup TLS");
#if CDBG_SIMULATE_FAILURES
	err = pthread_key_create(&osu_private_tls_key, NULL);
	BDBG_PRINT_ERROR_ON(err != 0, BDBG_OSU, "Failed to setup TLS");
#endif
    BDBG_SET_FAIL_OFF();
	for (i = 0; i < OSU_STATIC_MUTEX_COUNT; i++)
	{
		int err = osu_mutex_init(&static_mutexes[i],
					 osup_static_mutex_lock_order[ i ] );
		BDBG_PRINT_ERROR_ON(err != OSU_ERR_OK, BDBG_OSU, "Failed to init static mutexes");
	}
	BDBG_SET_FAIL_ON();
}

static __attribute__((destructor)) void osu_teardown(void)
{
	int i;
	int err = pthread_key_delete(osu_user_tls_key);
	BDBG_ASSERT(err == 0);
#if CDBG_SIMULATE_FAILURES
	err = pthread_key_delete(osu_private_tls_key);
	BDBG_ASSERT(err == 0);
#endif
	CSTD_UNUSED( err );
	for (i = 0; i < OSU_STATIC_MUTEX_COUNT; i++)
	{
		osu_mutex_term(&static_mutexes[i]);
	}
}

void *osu_noninline_thread_data_get(void)
{
	return pthread_getspecific(osu_user_tls_key);
}

void osu_noninline_thread_data_set(void *val)
{
	int err = pthread_setspecific(osu_user_tls_key, val);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
}

#if CDBG_SIMULATE_FAILURES

void *osu_noninline_debug_failure_flag_get(void)
{
	return pthread_getspecific(osu_private_tls_key);
}

void osu_noninline_debug_failure_flag_set(void *val)
{
	int err = pthread_setspecific(osu_private_tls_key, val);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
}

#endif

osu_mutex *osu_noninline_mutex_static_get(osu_static_mutex_id id)
{
	BDBG_ASSERT(id >= 0 && id < OSU_STATIC_MUTEX_COUNT);
	return &static_mutexes[id];
}

u64 osu_noninline_get_time_nsec(void)
{
	struct timespec ts;
	int err;

	err = clock_gettime(CLOCK_REALTIME, &ts);
	BDBG_ASSERT(err == 0);

	return ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

osu_errcode osu_noninline_cpu_props_get(osu_cpu_props *props)
{
	props->nr_cores = sysconf(_SC_NPROCESSORS_ONLN);
	props->cpu_page_size_log2 = ffs(sysconf(_SC_PAGESIZE))-1;
	props->cpu_l1_dcache_line_size_log2 = CONFIG_CPU_L1_DCACHE_LINE_SIZE_LOG2;
	props->cpu_l1_dcache_size = CONFIG_CPU_L1_DCACHE_SIZE;
	props->cpu_flags = OSU_CPU_PROPERTY_FLAG_LITTLE_ENDIAN;
	props->max_cpu_clock_speed_mhz = 100;
	props->available_memory_size = ((unsigned long)sysconf(_SC_AVPHYS_PAGES)) << props->cpu_page_size_log2;

	return OSU_ERR_OK;
}

osu_thread_id osu_noninline_thread_get_current_id(void)
{
	return pthread_self();
}

mali_bool osu_noninline_thread_id_match( osu_thread_id t1, osu_thread_id t2)
{
	return (t1 == t2) ? MALI_TRUE : MALI_FALSE;
}

osu_errcode osu_noninline_thread_create(osu_thread *thread,
					osu_threadproc threadproc,
					void *start_param,
					osu_thread_priority priority)
{
	osu_errcode err = OSU_ERR_OK;

	/* Don't care about priority for the time being... */
	if (pthread_create(&thread->osup_internal_struct.thr, NULL,
			   threadproc, start_param))
	{
		err = OSUP_ERR_FAULT;
	}

	return err;
}

void osu_noninline_thread_wait(osu_thread *thread, void **exitcode)
{
	int err = pthread_join(thread->osup_internal_struct.thr, exitcode);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
}

osu_errcode osu_noninline_sem_init(osu_sem *sem, u32 value)
{
	osu_errcode err = OSU_ERR_OK;

	if (sem_init(&sem->osup_internal_struct.sem, 0, value))
	{
		err = OSUP_ERR_FAULT;
	}

	return err;
}

void osu_noninline_sem_term(osu_sem *sem)
{
	int err = sem_destroy(&sem->osup_internal_struct.sem);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
}

osu_errcode osu_noninline_sem_wait(osu_sem *sem, u64 timeout_nsec)
{
	osu_errcode ret = OSU_ERR_OK;
	int err;

	if (timeout_nsec)
	{
		struct timespec tmo;
		err = clock_gettime(CLOCK_REALTIME, &tmo);

		BDBG_ASSERT(err == 0);
		
		tmo.tv_sec  += timeout_nsec / 1000000000U;
		tmo.tv_nsec += timeout_nsec % 1000000000U;

		if (tmo.tv_nsec >= 1000000000U)
		{
			tmo.tv_nsec -= 1000000000U;
			tmo.tv_sec++;
		}

		do
		{
			err = sem_timedwait(&sem->osup_internal_struct.sem, &tmo);
		} while (err == -1 && errno == EINTR);

		if (err == -1)
		{
			BDBG_ASSERT(errno == ETIMEDOUT);
			ret = OSUP_ERR_FAULT;
		}

	}
	else
	{
		do
		{
			err = sem_wait(&sem->osup_internal_struct.sem);
		} while (err == -1 && errno == EINTR);

		if (err == -1)
		{
			ret = OSUP_ERR_FAULT;
		}
	}


	return ret;
}

void osu_noninline_sem_post(osu_sem *sem)
{
	int err = sem_post(&sem->osup_internal_struct.sem);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
}

void osu_noninline_mutex_term(osu_mutex *mutex)
{
	int err = pthread_mutex_destroy(&mutex->osup_internal_struct.lock);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
}

void osu_noninline_mutex_lock(osu_mutex *mutex)
{
	int err = pthread_mutex_lock(&mutex->osup_internal_struct.lock);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
	osu_mutex_debug_lock(&mutex->osup_internal_struct);
}

void osu_noninline_mutex_unlock(osu_mutex *mutex)
{
	int err;
	osu_mutex_debug_unlock(&mutex->osup_internal_struct);
	err = pthread_mutex_unlock(&mutex->osup_internal_struct.lock);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
}



void osu_noninline_spinlock_term(osu_spinlock *lock)
{
	int err = pthread_mutex_destroy(&lock->osup_internal_struct.lock);
	BDBG_ASSERT(err == 0);
	CSTD_UNUSED( err );
}

#define OSU_SPIN_COUNT_MAX	100

void osu_noninline_spinlock_lock(osu_spinlock *lock)
{
	int err;
	int i = OSU_SPIN_COUNT_MAX;

	while(--i)
	{
		err = pthread_mutex_trylock(&lock->osup_internal_struct.lock);
		if (err == EBUSY)
		{
			continue;
		}

		goto out;
	}

	err = pthread_mutex_lock(&lock->osup_internal_struct.lock);
out:
	BDBG_ASSERT(err == 0);
	osu_mutex_debug_lock(&lock->osup_internal_struct);
	return;
}

void osu_noninline_spinlock_unlock(osu_spinlock *lock)
{
	int err;
	osu_mutex_debug_unlock(&lock->osup_internal_struct);
	err = pthread_mutex_unlock(&lock->osup_internal_struct.lock);
	BDBG_ASSERT(err == 0);
}

