/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_kbase_js_policy_rr.h
 * Round-robin Job Scheduler Policy structure definitions
 */

#ifndef _KBASE_JS_POLICY_RR_H_
#define _KBASE_JS_POLICY_RR_H_

#define KBASE_JS_POLICY_AVAILABLE_RR

/** @addtogroup base_api
 * @{ */
/** @addtogroup base_kbase_api
 * @{ */
/** @addtogroup kbase_js_policy
 * @{ */

/**
 * Internally, this policy keeps a few internal queues for different variants
 * of core requirements, which are used to decide how to schedule onto the
 * different job slots.
 *
 * Currently, one extra variant is supported: an NSS variant.
 *
 * Must be a power of 2 to keep the lookup math simple
 */
#define KBASEP_JS_MAX_NR_CORE_REQ_VARIANTS_LOG2 2
#define KBASEP_JS_MAX_NR_CORE_REQ_VARIANTS      (1u << KBASEP_JS_MAX_NR_CORE_REQ_VARIANTS_LOG2 )

/** Bits needed in the lookup to support all slots */
#define KBASEP_JS_VARIANT_LOOKUP_BITS_NEEDED (BASE_JM_MAX_NR_SLOTS * KBASEP_JS_MAX_NR_CORE_REQ_VARIANTS)
/** Number of u32s needed in the lookup array to support all slots */
#define KBASEP_JS_VARIANT_LOOKUP_WORDS_NEEDED ((KBASEP_JS_VARIANT_LOOKUP_BITS_NEEDED + 31) / 32)

typedef struct kbasep_js_policy_rr
{
	/** List of all contexts in the context queue. Hold
	 * kbasep_jd_device_data::runpool_lock whilst accessing. */
	osk_dlist ctx_queue_head;
	/** List of scheduled contexts. Hold kbasep_js_device_data::queue_lock
	 * whilst accessing */
	osk_dlist scheduled_ctxs_head;

	/** Number of valid elements in the core_req_variants member, and the
	 * kbasep_js_policy_rr_ctx::job_list_head array */
	u32 num_core_req_variants;

	/** Variants of the core requirements */
	base_jd_core_req core_req_variants[KBASEP_JS_MAX_NR_CORE_REQ_VARIANTS];

	/* Lookups per job slot against which core_req_variants match it */
	u32 slot_to_variant_lookup_ss_state[KBASEP_JS_VARIANT_LOOKUP_WORDS_NEEDED];
	u32 slot_to_variant_lookup_nss_state[KBASEP_JS_VARIANT_LOOKUP_WORDS_NEEDED];

	/* The timer tick used for rescheduling jobs */
	osk_timer timer;

	/* Is the timer running? */
	mali_bool timer_running;

	/* Tick counter, incremented on ever timer call back */
	u8 tick_count;
} kbasep_js_policy_rr;

/**
 * This policy contains a single linked list of all contexts.
 */
typedef struct kbasep_js_policy_rr_ctx
{
	/** Link implementing the Policy's Queue, and Currently Scheduled list */
	osk_dlist_item list;

	/** Run Pool job lists - only using kbasep_js_policy_rr::num_unique_slots of them */
	osk_dlist job_list_head[KBASEP_JS_MAX_NR_CORE_REQ_VARIANTS];

} kbasep_js_policy_rr_ctx;

/**
 * In this policy, each Job is part of at most one of the per_corereq lists
 */
typedef struct kbasep_js_policy_rr_job
{
	osk_dlist_item list;      /**< Link implementing the Run Pool list/Jobs owned by the ctx */
	u32 cached_variant_idx;   /**< Cached index of the list this should be entered into on re-queue */

	u8 ticks;                 /**< Number of ticks that this job has been executing for */
} kbasep_js_policy_rr_job;

/** @} */ /* end group kbase_js_policy */
/** @} */ /* end group base_kbase_api */
/** @} */ /* end group base_api */

#endif
