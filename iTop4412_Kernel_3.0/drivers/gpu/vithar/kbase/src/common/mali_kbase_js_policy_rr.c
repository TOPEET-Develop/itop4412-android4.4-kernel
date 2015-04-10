/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/*
 * Job Scheduler: Round Robin Policy Implementation
 */

#include <kbase/src/common/mali_kbase.h>
#include <kbase/src/common/mali_kbase_jm.h>
#include <kbase/src/common/mali_kbase_js.h>
#include <kbase/src/common/mali_kbase_js_policy_rr.h>

#define LOOKUP_VARIANT_MASK ((1u<<KBASEP_JS_MAX_NR_CORE_REQ_VARIANTS) - 1u)

/** The frequency of the timer tick in milliseconds */
#define TIMER_FREQUENCY 34

/** The number of ticks that must pass before soft-stopping a job */
#define SOFT_STOP_TICKS 1

/** The number of ticks that must pass before hard-stopping a job
 *
 * Should be strictly greater than SOFT_STOP_TICKS.
 */
#define HARD_STOP_TICKS 10

/* core_req variants are ordered by least restrictive first, so that our
 * algorithm in cached_variant_idx_init picks the least restrictive variant for
 * each job */
static const base_jd_core_req core_req_variants[] ={

	BASE_JD_REQ_FS | BASE_JD_REQ_CF | BASE_JD_REQ_V,
	BASE_JD_REQ_CS | BASE_JD_REQ_CF | BASE_JD_REQ_V,
	BASE_JD_REQ_CS | BASE_JD_REQ_T  | BASE_JD_REQ_CF | BASE_JD_REQ_V,
	BASE_JD_REQ_CS | BASE_JD_REQ_CF | BASE_JD_REQ_V | BASE_JD_REQ_NSS
};

#define NUM_CORE_REQ_VARIANTS NELEMS(core_req_variants)

static const u32 variants_supported_ss_state[] =
{
	(1u << 0),             /* js[0] uses variant 0 (FS list)*/
	(1u << 2) | (1u << 1), /* js[1] uses variants 1 and 2 (CS and CS+T lists)*/
	(1u << 1)              /* js[2] uses variant 1 (CS list). NOTE: could set to 0 */
};

static const u32 variants_supported_nss_state[] =
{
	(1u << 0),             /* js[0] uses variant 0 (FS list)*/
	(1u << 2) | (1u << 1), /* js[1] uses variants 1 and 2 (CS and CS+T lists)*/
	(1u << 3)              /* js[2] uses variant 3 (NSS list) */
};

/* Defines for easy asserts 'is scheduled'/'is queued'/'is neither queued norscheduled' */
#define KBASEP_JS_CHECKFLAG_QUEUED       (1u << 0) /**< Check the queued state */
#define KBASEP_JS_CHECKFLAG_SCHEDULED    (1u << 1) /**< Check the scheduled state */
#define KBASEP_JS_CHECKFLAG_IS_QUEUED    (1u << 2) /**< Expect queued state to be set */
#define KBASEP_JS_CHECKFLAG_IS_SCHEDULED (1u << 3) /**< Expect scheduled state to be set */

enum
{
	KBASEP_JS_CHECK_NOTQUEUED     = KBASEP_JS_CHECKFLAG_QUEUED,
	KBASEP_JS_CHECK_NOTSCHEDULED  = KBASEP_JS_CHECKFLAG_SCHEDULED,
	KBASEP_JS_CHECK_QUEUED        = KBASEP_JS_CHECKFLAG_QUEUED | KBASEP_JS_CHECKFLAG_IS_QUEUED,
	KBASEP_JS_CHECK_SCHEDULED     = KBASEP_JS_CHECKFLAG_SCHEDULED | KBASEP_JS_CHECKFLAG_IS_SCHEDULED
};

typedef u32 kbasep_js_check;

/*
 * Private Functions
 */

STATIC void kbasep_js_debug_check( kbasep_js_policy_rr *policy_info, kbase_context *kctx, kbasep_js_check check_flag )
{
	/* This function uses the ternary operator and non-explicit comparisons,
	 * because it makes for much shorter, easier to read code */

	if ( check_flag & KBASEP_JS_CHECKFLAG_QUEUED )
	{
		mali_bool is_queued;
		mali_bool expect_queued;
		is_queued = ( OSK_DLIST_MEMBER_OF( &policy_info->ctx_queue_head,
		                                   kctx,
		                                   jctx.sched_info.runpool.policy_ctx.rr.list ) )? MALI_TRUE: MALI_FALSE;

		expect_queued = ( check_flag & KBASEP_JS_CHECKFLAG_IS_QUEUED ) ? MALI_TRUE : MALI_FALSE;

		OSK_ASSERT_MSG( expect_queued == is_queued,
		                "Expected context %p to be %s but it was %s\n",
		                kctx,
		                (expect_queued)   ?"queued":"not queued",
		                (is_queued)       ?"queued":"not queued" );

	}

	if ( check_flag & KBASEP_JS_CHECKFLAG_SCHEDULED )
	{
		mali_bool is_scheduled;
		mali_bool expect_scheduled;
		is_scheduled = ( OSK_DLIST_MEMBER_OF( &policy_info->scheduled_ctxs_head,
		                                      kctx,
		                                      jctx.sched_info.runpool.policy_ctx.rr.list ) )? MALI_TRUE: MALI_FALSE;

		expect_scheduled = ( check_flag & KBASEP_JS_CHECKFLAG_IS_SCHEDULED ) ? MALI_TRUE : MALI_FALSE;
		OSK_ASSERT_MSG( expect_scheduled == is_scheduled,
		                "Expected context %p to be %s but it was %s\n",
		                kctx,
		                (expect_scheduled)?"scheduled":"not scheduled",
		                (is_scheduled)    ?"scheduled":"not scheduled" );

	}

}

STATIC INLINE void set_slot_to_variant_lookup( u32 *bit_array, u32 slot_idx, u32 variants_supported )
{
	u32 overall_bit_idx = slot_idx * KBASEP_JS_MAX_NR_CORE_REQ_VARIANTS;
	u32 word_idx = overall_bit_idx / 32;
	u32 bit_idx = overall_bit_idx % 32;

	OSK_ASSERT( slot_idx < BASE_JM_MAX_NR_SLOTS );
	OSK_ASSERT( (variants_supported & ~LOOKUP_VARIANT_MASK) == 0 );

	bit_array[word_idx] |= variants_supported << bit_idx;
}


STATIC INLINE u32 get_slot_to_variant_lookup( u32 *bit_array, u32 slot_idx )
{
	u32 overall_bit_idx = slot_idx * KBASEP_JS_MAX_NR_CORE_REQ_VARIANTS;
	u32 word_idx = overall_bit_idx / 32;
	u32 bit_idx = overall_bit_idx % 32;

	u32 res;

	OSK_ASSERT( slot_idx < BASE_JM_MAX_NR_SLOTS );

	res = bit_array[word_idx] >> bit_idx;
	res &= LOOKUP_VARIANT_MASK;

	return res;
}

/* Check the core_req_variants: make sure that every job slot is satisifed by
 * one of the variants. This checks that cached_variant_idx_init will produce a
 * valid result for jobs that make maximum use of the job slots. */
#if MALI_DEBUG
STATIC void debug_check_core_req_variants( kbase_device *kbdev, kbasep_js_policy_rr *policy_info )
{
	kbasep_js_device_data *js_devdata;
	int i;
	int j;

	js_devdata = &kbdev->js_data;

	for ( j = 0 ; j < kbdev->nr_job_slots ; ++j )
	{
		base_jd_core_req job_core_req;
		mali_bool found = MALI_FALSE;

		job_core_req =  js_devdata->js_reqs[j];
		for ( i = 0; i < policy_info->num_core_req_variants ; ++i )
		{
			base_jd_core_req var_core_req;
			var_core_req = policy_info->core_req_variants[i];

			if ( (var_core_req & job_core_req) == job_core_req )
			{
				found = MALI_TRUE;
				break;
			}
		}

		/* Early-out on any failure */
		OSK_ASSERT_MSG( found != MALI_FALSE,
		                "Job slot %d features 0x%x not matched by core_req_variants. "
		                "Rework core_req_variants and vairants_supported_<...>_state[] to match\n",
		                j,
		                job_core_req );
	}
}
#endif

STATIC void build_core_req_variants( kbase_device *kbdev, kbasep_js_policy_rr *policy_info )
{
	OSK_ASSERT( kbdev != NULL );
	OSK_ASSERT( policy_info != NULL );

	/* Assume a static set of variants */
	OSK_MEMCPY( policy_info->core_req_variants, core_req_variants, sizeof(core_req_variants) );

	policy_info->num_core_req_variants = NUM_CORE_REQ_VARIANTS;

	OSK_DEBUG_CODE( debug_check_core_req_variants( kbdev, policy_info ) );
}


STATIC void build_slot_lookups( kbase_device *kbdev, kbasep_js_policy_rr *policy_info )
{
	kbasep_js_device_data *js_devdata;
	int i;

	js_devdata = &kbdev->js_data;

	/* Given the static set of variants, provide a static set of lookups */
	for ( i = 0; i < kbdev->nr_job_slots; ++i )
	{
		set_slot_to_variant_lookup( policy_info->slot_to_variant_lookup_ss_state,
		                            i,
		                            variants_supported_ss_state[i] );

		set_slot_to_variant_lookup( policy_info->slot_to_variant_lookup_nss_state,
		                            i,
		                            variants_supported_nss_state[i] );
	}

}

STATIC void cached_variant_idx_init( kbasep_js_policy_rr *policy_info, kbase_jd_atom *atom )
{
	kbasep_js_policy_rr_job *job_info;
	u32 i;
	base_jd_core_req job_core_req;

	OSK_ASSERT( policy_info != NULL );
	OSK_ASSERT( atom != NULL );

	job_info = &atom->sched_info.rr;
	job_core_req = atom->atom->core_req;

	/* Pick a core_req variant that matches us. Since they're ordered by least
	 * restrictive first, it picks the least restrictive variant */
	for ( i = 0; i < policy_info->num_core_req_variants ; ++i )
	{
		base_jd_core_req var_core_req;
		var_core_req = policy_info->core_req_variants[i];
		
		if ( (var_core_req & job_core_req) == job_core_req )
		{
			job_info->cached_variant_idx = i;
			return;
		}
	}

	/* NOTE: Here we must handle jobs with non-matching requirements. At present, we just assert. */
	OSK_ASSERT_MSG( MALI_FALSE, "Couldn't handle core_req=0x%x\n", job_core_req  );
	job_info->cached_variant_idx = 0;
}

static void timer_callback(void *data)
{
	kbase_device *kbdev = (kbase_device*)data;
	kbasep_js_device_data *js_devdata;
	kbasep_js_policy_rr *policy_info;
	int s;
	mali_bool jobs_active = MALI_FALSE;
	mali_bool contexts_queued;
	osk_error osk_err;

	OSK_ASSERT(kbdev != NULL);

	js_devdata = &kbdev->js_data;
	policy_info = &js_devdata->policy.rr;

	osk_spinlock_irq_lock( &js_devdata->runpool_lock);
	contexts_queued = !OSK_DLIST_IS_EMPTY( &policy_info->ctx_queue_head );
	osk_spinlock_irq_unlock( &js_devdata->runpool_lock);

	/* Loop through the slots */
	for(s=0; s<kbdev->nr_job_slots; s++)
	{
		kbase_jm_slot *slot = &kbdev->jm_slots[s];

		osk_spinlock_irq_lock(&slot->lock);
		
		if (kbasep_jm_nr_jobs_submitted(slot) > 0)
		{
			jobs_active = MALI_TRUE;
		}

		if (contexts_queued && kbasep_jm_nr_jobs_submitted(slot) > 0)
		{
			kbase_jd_atom *atom = kbasep_jm_peek_idx_submit_slot(slot, 0);
			int ticks = atom->sched_info.rr.ticks ++;
			if (ticks == HARD_STOP_TICKS)
			{
				/* Job has been scheduled for at least HARD_STOP_TICKS ticks, hard stop the slot */
				kbase_job_slot_hardstop(kbdev, s);
			}
			else if (ticks == SOFT_STOP_TICKS)
			{
				/* Job has been scheduled for at least SOFT_STOP_TICKS ticks, soft stop the slot */
				kbase_job_slot_softstop(kbdev, s);
			}
		}

		osk_spinlock_irq_unlock(&slot->lock);
	}

	if (jobs_active)
	{
		osk_err = osk_timer_start(&policy_info->timer, TIMER_FREQUENCY);
		if (OSK_ERR_NONE != osk_err)
		{
			osk_spinlock_irq_lock( &js_devdata->runpool_lock);
			policy_info->timer_running = MALI_FALSE;
			osk_spinlock_irq_unlock( &js_devdata->runpool_lock);
		}
	}
	else
	{
		osk_spinlock_irq_lock( &js_devdata->runpool_lock);
		policy_info->timer_running = MALI_FALSE;
		osk_spinlock_irq_unlock( &js_devdata->runpool_lock);
	}
}

/*
 * Non-private functions
 */

mali_error kbasep_js_policy_init( kbase_device *kbdev )
{
	kbasep_js_device_data *js_devdata;
	kbasep_js_policy_rr *policy_info;

	OSK_ASSERT( kbdev != NULL );
	js_devdata = &kbdev->js_data;
	policy_info = &js_devdata->policy.rr;

	OSK_DLIST_INIT( &policy_info->ctx_queue_head );
	OSK_DLIST_INIT( &policy_info->scheduled_ctxs_head );

	if (osk_timer_init(&policy_info->timer) != OSK_ERR_NONE)
	{
		return MALI_ERROR_FUNCTION_FAILED;
	}

	osk_timer_callback_set( &policy_info->timer, timer_callback, kbdev );

	policy_info->timer_running = MALI_FALSE;

	/* Build up the core_req variants */
	build_core_req_variants( kbdev, policy_info );
	/* Build the slot to variant lookups */
	build_slot_lookups(kbdev, policy_info );


	return MALI_ERROR_NONE;
}

void kbasep_js_policy_term( kbasep_js_policy *js_policy )
{
	kbasep_js_policy_rr     *policy_info;

	OSK_ASSERT( js_policy != NULL );
	policy_info = &js_policy->rr;

	/* ASSERT that there are no contexts queued */
	OSK_ASSERT( OSK_DLIST_IS_EMPTY( &policy_info->ctx_queue_head ) != MALI_FALSE );
	/* ASSERT that there are no contexts scheduled */
	OSK_ASSERT( OSK_DLIST_IS_EMPTY( &policy_info->scheduled_ctxs_head ) != MALI_FALSE );

	osk_timer_stop(&policy_info->timer);
	osk_timer_term(&policy_info->timer);
}

mali_error kbasep_js_policy_init_ctx( kbasep_js_policy *js_policy, kbase_context *kctx )
{
	kbasep_js_policy_rr_ctx *ctx_info;
	kbasep_js_policy_rr     *policy_info;
	int i;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( kctx != NULL );

	policy_info = &js_policy->rr;
	ctx_info = &kctx->jctx.sched_info.runpool.policy_ctx.rr;

	for ( i = 0 ; i < policy_info->num_core_req_variants ; ++i )
	{
		OSK_DLIST_INIT( &ctx_info->job_list_head[i] );
	}

	return MALI_ERROR_NONE;
}

void kbasep_js_policy_term_ctx( kbasep_js_policy *js_policy, kbase_context *kctx )
{
	kbasep_js_policy_rr_ctx *ctx_info;
	kbasep_js_policy_rr     *policy_info;
	int i;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( kctx != NULL );

	policy_info = &js_policy->rr;
	ctx_info = &kctx->jctx.sched_info.runpool.policy_ctx.rr;

	/* ASSERT that no jobs are present */
	for ( i = 0 ; i < policy_info->num_core_req_variants ; ++i )
	{
		OSK_ASSERT( OSK_DLIST_IS_EMPTY( &ctx_info->job_list_head[i] ) != MALI_FALSE );
	}

	/* No work to do */
}


/*
 * Context Management
 */

void kbasep_js_policy_enqueue_ctx( kbasep_js_policy *js_policy, kbase_context *kctx )
{
	kbasep_js_policy_rr     *policy_info;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( kctx != NULL );

	policy_info = &js_policy->rr;

	/* ASSERT about scheduled-ness/queued-ness */
	kbasep_js_debug_check( policy_info, kctx, KBASEP_JS_CHECK_NOTQUEUED );

	/* All enqueued contexts go to the back of the queue */
	OSK_DLIST_PUSH_BACK( &policy_info->ctx_queue_head,
	                     kctx,
	                     kbase_context,
	                     jctx.sched_info.runpool.policy_ctx.rr.list );
}

mali_bool kbasep_js_policy_dequeue_head_ctx( kbasep_js_policy *js_policy, kbase_context **kctx_ptr )
{
	kbasep_js_policy_rr     *policy_info;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( kctx_ptr != NULL );

	policy_info = &js_policy->rr;

	if ( OSK_DLIST_IS_EMPTY( &policy_info->ctx_queue_head ) != MALI_FALSE )
	{
		/* Nothing to dequeue */
		return MALI_FALSE;
	}

	/* Contexts are dequeued from the front of the queue */
	*kctx_ptr = OSK_DLIST_POP_FRONT( &policy_info->ctx_queue_head,
	                                 kbase_context,
	                                 jctx.sched_info.runpool.policy_ctx.rr.list );


	return MALI_TRUE;
}

mali_bool kbasep_js_policy_try_evict_ctx( kbasep_js_policy *js_policy, kbase_context *kctx )
{
	kbasep_js_policy_rr_ctx *ctx_info;
	kbasep_js_policy_rr     *policy_info;
	mali_bool is_present;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( kctx != NULL );

	policy_info = &js_policy->rr;
	ctx_info = &kctx->jctx.sched_info.runpool.policy_ctx.rr;

	/* Check the queue to see if it's found */
	is_present = OSK_DLIST_MEMBER_OF( &policy_info->ctx_queue_head,
	                                  kctx,
	                                  jctx.sched_info.runpool.policy_ctx.rr.list );

	if ( is_present != MALI_FALSE )
	{
		OSK_DLIST_REMOVE( &policy_info->ctx_queue_head,
		                  kctx,
		                  jctx.sched_info.runpool.policy_ctx.rr.list );
	}

	return is_present;
}

void kbasep_js_policy_kill_all_ctx_jobs( kbasep_js_policy *js_policy, kbase_context *kctx )
{
	kbasep_js_policy_rr *policy_info;
	kbasep_js_policy_rr_ctx *ctx_info;
	u32 i;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( kctx != NULL );

	policy_info = &js_policy->rr;
	ctx_info = &kctx->jctx.sched_info.runpool.policy_ctx.rr;

	/* Kill jobs on each variant in turn */
	for ( i = 0; i < policy_info->num_core_req_variants; ++i )
	{
		osk_dlist *job_list;
		job_list = &ctx_info->job_list_head[i];

		/* Call kbase_jd_cancel() on all kbase_jd_atoms in this list, whilst removing them from the list */
		OSK_DLIST_EMPTY_LIST( job_list, kbase_jd_atom, sched_info.rr.list, kbase_jd_cancel );
	}

}

void kbasep_js_policy_runpool_add_ctx( kbasep_js_policy *js_policy, kbase_context *kctx )
{
	kbasep_js_policy_rr_ctx *ctx_info;
	kbasep_js_policy_rr     *policy_info;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( kctx != NULL );

	policy_info = &js_policy->rr;
	ctx_info = &kctx->jctx.sched_info.runpool.policy_ctx.rr;

	/* ASSERT about scheduled-ness/queued-ness */
	kbasep_js_debug_check( policy_info, kctx, KBASEP_JS_CHECK_NOTSCHEDULED );

	/* All enqueued contexts go to the back of the runpool */
	OSK_DLIST_PUSH_BACK( &policy_info->scheduled_ctxs_head,
	                     kctx,
	                     kbase_context,
	                     jctx.sched_info.runpool.policy_ctx.rr.list );

}

void kbasep_js_policy_runpool_remove_ctx( kbasep_js_policy *js_policy, kbase_context *kctx )
{
	kbasep_js_policy_rr_ctx *ctx_info;
	kbasep_js_policy_rr     *policy_info;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( kctx != NULL );

	policy_info = &js_policy->rr;
	ctx_info = &kctx->jctx.sched_info.runpool.policy_ctx.rr;

	/* ASSERT about scheduled-ness/queued-ness */
	kbasep_js_debug_check( policy_info, kctx, KBASEP_JS_CHECK_SCHEDULED );

	/* No searching or significant list maintenance required to remove this context */
	OSK_DLIST_REMOVE( &policy_info->scheduled_ctxs_head,
	                  kctx,
	                  jctx.sched_info.runpool.policy_ctx.rr.list );
}

mali_bool kbasep_js_policy_should_remove_ctx( kbasep_js_policy *js_policy, kbase_context *kctx )
{
	kbasep_js_policy_rr     *policy_info;

	OSK_ASSERT( js_policy != NULL );

	policy_info = &js_policy->rr;

	if ( OSK_DLIST_IS_EMPTY( &policy_info->ctx_queue_head ) )
	{
		/* There are no other contexts to run - so we keep the current context */
		return MALI_FALSE;
	}
	return MALI_TRUE;
}

kbase_context* kbasep_js_policy_runpool_lookup_ctx( kbasep_js_policy *js_policy, int as_nr )
{
	kbasep_js_policy_rr *policy_info;
	kbase_context *kctx;

	policy_info = &js_policy->rr;

	OSK_DLIST_FOREACH( &policy_info->scheduled_ctxs_head,
	                   kbase_context,
	                   jctx.sched_info.runpool.policy_ctx.rr.list,
	                   kctx )
	{
		if ( kctx->as_nr == as_nr )
		{
			return kctx;
		}
	}

	return NULL;
}



/*
 * Job Chain Management
 */

void kbasep_js_policy_init_job( kbasep_js_policy *js_policy, kbase_jd_atom *atom )
{
	kbasep_js_policy_rr_job *job_info;
	kbasep_js_policy_rr_ctx *ctx_info;
	kbasep_js_policy_rr *policy_info;
	kbase_context *parent_ctx;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( atom != NULL );
	parent_ctx = atom->kctx;
	OSK_ASSERT( parent_ctx != NULL );

	job_info = &atom->sched_info.rr;

	ctx_info = &parent_ctx->jctx.sched_info.runpool.policy_ctx.rr;
	policy_info = &js_policy->rr;

	/* Determine the job's index into the job list head */
	cached_variant_idx_init( policy_info, atom );
	/* NOTE: Here we must handle atoms that don't have matching requirements */

	OSK_DLIST_PUSH_BACK( &ctx_info->job_list_head[job_info->cached_variant_idx],
	                     atom,
	                     kbase_jd_atom,
	                     sched_info.rr.list );
}

void kbasep_js_policy_term_job( kbasep_js_policy *js_policy, kbase_jd_atom *atom )
{
	kbasep_js_policy_rr_job *job_info;
	kbasep_js_policy_rr_ctx *ctx_info;
	kbase_context *parent_ctx;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( atom != NULL );
	parent_ctx = atom->kctx;
	OSK_ASSERT( parent_ctx != NULL );

	job_info = &atom->sched_info.rr;
	ctx_info = &parent_ctx->jctx.sched_info.runpool.policy_ctx.rr;

	/* This policy is simple enough that nothing is required */

	/* In any case, we'll ASSERT that this job was correctly removed from the relevant lists */
	OSK_ASSERT( OSK_DLIST_MEMBER_OF( &ctx_info->job_list_head[job_info->cached_variant_idx],
	                                 atom,
	                                 sched_info.rr.list ) == MALI_FALSE );
}


mali_bool kbasep_js_policy_dequeue_job( kbase_device *kbdev,
                                        int job_slot_idx,
                                        kbase_jd_atom **katom_ptr )
{
	kbasep_js_device_data *js_devdata;
	kbasep_js_policy_rr *policy_info;
	kbase_context *kctx;
	u32 variants_supported;
	osk_error osk_err;

	OSK_ASSERT( kbdev != NULL );
	OSK_ASSERT( katom_ptr != NULL );
	OSK_ASSERT( job_slot_idx < BASE_JM_MAX_NR_SLOTS );

	js_devdata = &kbdev->js_data;
	policy_info = &js_devdata->policy.rr;

	/* Get the variants for this slot */
	if ( js_devdata->nr_nss_ctxs_running == 0 )
	{
		/* SS-state */
		variants_supported = get_slot_to_variant_lookup( policy_info->slot_to_variant_lookup_ss_state, job_slot_idx );
	}
	else
	{
		/* NSS-state */
		variants_supported = get_slot_to_variant_lookup( policy_info->slot_to_variant_lookup_nss_state, job_slot_idx );
	}

	/* Choose the first context that has a job ready matching the requirements */
	OSK_DLIST_FOREACH( &policy_info->scheduled_ctxs_head,
	                   kbase_context,
	                   jctx.sched_info.runpool.policy_ctx.rr.list,
	                   kctx )
	{
		u32 test_variants = variants_supported;
		kbasep_js_policy_rr_ctx *ctx_info;
		ctx_info = &kctx->jctx.sched_info.runpool.policy_ctx.rr;

		/* Only submit jobs from contexts that are allowed*/
		if ( kbasep_js_is_submit_allowed( js_devdata, kctx ) != MALI_FALSE )
		{
			/* Check each variant in turn */
			while ( test_variants != 0 )
			{
				long variant_idx;
				osk_dlist *job_list;
				variant_idx = osk_find_first_set_bit( test_variants );
				job_list = &ctx_info->job_list_head[variant_idx];

				if ( OSK_DLIST_IS_EMPTY( job_list ) == MALI_FALSE )
				{
					/* Found a context with a matching job */
					*katom_ptr = OSK_DLIST_POP_FRONT( job_list, kbase_jd_atom, sched_info.rr.list );

					if (!OSK_DLIST_IS_EMPTY( &policy_info->ctx_queue_head ) &&
					    policy_info->timer_running == MALI_FALSE)
					{
						osk_err = osk_timer_start(&policy_info->timer, TIMER_FREQUENCY);
						if (OSK_ERR_NONE == osk_err)
						{
							policy_info->timer_running = MALI_TRUE;
						}
					}

					(*katom_ptr)->sched_info.rr.ticks = 0;

					return MALI_TRUE;
				}

				test_variants &= ~(1u << variant_idx);
			}
			/* All variants checked by here */
		}

	}

	/* By this point, no contexts had a matching job */

	return MALI_FALSE;
}

mali_bool kbasep_js_policy_dequeue_job_irq( kbase_device *kbdev,
                                            int job_slot_idx,
                                            kbase_jd_atom **katom_ptr )
{
	/* IRQ and non-IRQ variants of this are the same (though, the IRQ variant could be made faster) */
	return kbasep_js_policy_dequeue_job( kbdev, job_slot_idx, katom_ptr );
}


void kbasep_js_policy_requeue_job( kbasep_js_policy *js_policy, kbase_jd_atom *katom )
{
	kbasep_js_policy_rr_job *job_info;
	kbasep_js_policy_rr_ctx *ctx_info;
	kbase_context *parent_ctx;

	OSK_ASSERT( js_policy != NULL );
	OSK_ASSERT( katom != NULL );
	parent_ctx = katom->kctx;
	OSK_ASSERT( parent_ctx != NULL );

	job_info = &katom->sched_info.rr;
	ctx_info = &parent_ctx->jctx.sched_info.runpool.policy_ctx.rr;

	OSK_DLIST_PUSH_BACK( &ctx_info->job_list_head[job_info->cached_variant_idx],
	                     katom,
	                     kbase_jd_atom,
	                     sched_info.rr.list );
}

void kbasep_js_policy_log_job_result( kbasep_js_policy *js_policy, kbase_jd_atom *katom, u32 time_spent_us )
{
	OSK_ASSERT(katom);
}
