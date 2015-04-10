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
 * @file mali_base_jd.h
 * Base Job Dispatch APIs.
 */

#ifndef _BASE_JD_H_
#define _BASE_JD_H_

#include <cutils/linked_list/mali_cutils_dlist.h>

/**
 * @page page_base_api_job_dispatch User-side Base Job Dispatch APIs
 *
 * @par Goals and constraints:
 *
 * The goal of the Base Job Dispatch API (JD) is to submit job-chains
 * to the kernel with a number of constraints:
 *
 * @li Limit the number of syscalls to submit multiple job-chains
 * @li Reduce the number of copies from user-space to kernel
 * @li Support (limited) dependencies between job-chains:
 *  - ensure that dependent job-chains running on different job-slots
 *    are properly sequenced
 * @li Support for parallelism among job-chains:
 *  - ensure that non-dependent job-chains running on different
 *    job-slots can run in parallel
 *
 * @par Data structures:
 *
 * @li Use a ring-buffer (shared memory) between user-space and kernel
 *  - Pack flattened data structures called @e atom (job-chain
 *  pointer, memory coherency operations, dependency information,
 *  see ::base_jd_atom).
 *  - No user pointer interpreted by the kernel.
 *  - No syscall to populate the buffer.
 * @li Group job-chains in a @a bag
 *  - The bag describes a contiguous region in the ring-buffer
 *  (refer to ::base_bag_acquire_buffer, ::base_bag_release_buffer,
 *  ::base_bag_get_address, ::base_atom_get_address).
 *  - Job-chains described in that region are submitted in one go
 *  (one single syscall, see ::base_jd_submit_bag)
 *  - Job-chains in a single bag can be part of a dependency chain, or
 *  be completely independent, as long as they have the same core
 *  restrictions requirements (see ::base_jd_bag).
 * @li Use kernel events to inform user-space of the completion of jobs
 * and bags.
 *  - Refer to ::base_jd_event_wait
 *
 * Cons: it's not always easy to estimate the size required in the
 * ring buffer for a bag, as job instances have variable sizes
 * (because of batched memory coherency operations). Refer to
 * ::base_jd_atom_size.
 *
 * @par Expressing dependencies between job-chains:
 *
 * @li Kernel understands a binary DAG (each job-chain depends on at
 * most two other job-chains, and satisfy at most two dependencies).
 * @li Convert original n-ary graph (such as the one coming from the
 * Marshal layer) to binary by inserting special job-chains for
 * additionnal dependencies (see ::BASE_JD_REQ_DEP).
 * @li Tagging edges between job-chains results in a simple dependency
 * system that can be implemented efficiently.
 * @li Dependencies take the form of an 8bit integer
 *  - see ::base_dep_acquire, ::base_dep_release
 * @li Each job-chain has pre- and post-dependencies
 *  - pre-deps are the edges pointing towards this job-chain,
 *  - post-deps are the edges pointing towards other job-chains.
 *  - post-deps of a job-chain are the pre-deps of other
 *  job-chains.
 * @li A job-chain can be scheduled for execution when its pre-deps
 * are satisfied.
 * @li A job-chain satisfies its post-deps when it is completed
 * (possibly triggering other job-chain execution).
 * @li Job-chains with no pre-dependencies can run immediately
 * @li Dependencies can cross the bag barriers
 *
 * @dotfile jd_graph.dot "Example of a dependency graph"
 *
 * In this example, nodes represent job-chains, while edges represent
 * dependencies. The number associated with each edge allows to track
 * the state of the dependency. An edge tagged with the value 0
 * indicates the absence of dependency (or a dependency that is always
 * satisfied). Nodes <em>a, b, c, d, e, f</em> and @e n form a single
 * @e bag.
 *
 * @li Nodes e and f have no pre-dependencies (their inbound edges
 * are tags with the value 0). They can be executed right away,
 * possibly in parallel.
 * @li Nodes <em>b, c</em> and @e d have a single pre-dependency (b
 * and c depend on e, d depends on f).
 * @li Nodes @e a and @e n have a dual pre-dependency.
 * @li Node @e a has a single post-dependency that points outside of
 * the bag for inter-bag dependency.
 *
 * @par Storage:
 *
 * @dotfile rb_graph.dot
 *
 * In this example, we have the same DAG as previously exposed (bag
 * #0), except that it almost shows the structures as they would be
 * laid out in memory. Each data structure, containing a payload,
 * dependencies and sync sets, is called an @a atom (see
 * ::base_jd_atom for more details). The only restriction is the order
 * in which atoms are layed out in the bag: <em> atoms that have
 * pre-dependencies must appear after atoms that satisfy those
 * dependencies.</em> Here, node @e c cannot appear before @e e, as @e
 * c depends on @e e for its completion.
 *
 * The file mali_base_jd_test.c, found under the "Examples" tab, shows
 * the API being used.
 *
 * @example mali_base_jd_test.c
 */

/**
 * @addtogroup base_api
 * @{
 */

/**
 * @addtogroup base_user_api
 * @{
 */

/**
 * @addtogroup base_user_api_job_dispatch User-side Base Job Dispatcher APIs
 * @{
 */

/**
 * @brief A collection of job-chains to be run, all sharing the same core
 * restrictions.
 *
 * A bag is a container for job-chains to be submitted to the kernel.
 * It describes a region in the base context ring-buffer, which contains
 * a number of job-chains (::base_jd_atom). All the job-chains in a single
 * bag share the same core restriction.
 */
typedef struct base_jd_bag
{
	cutils_dlist_item   entry;          /**< Bookkeeping information */
	/** Mask describing the midgard core restriction
	 *
	 * @deprecated This member was deprecated in Base v3.1. Use
	 * BASE_JD_REQ_COHERENT_GROUP instead. Setting this to anything other than
	 * 0 will cause an ASSERT. */
	u64             core_restriction;
	size_t          offset;     /**< Offset for this bag in the ring-buffer.
	                                 Must be a multiple of the alignment requirement of
	                                 ::base_jd_atom. */
	size_t          size;       /**< The size of the region in the ring-buffer */
	u32             nr_atoms;   /**< Number of ::base_jd_atom in the bag */
} base_jd_bag;

/**
 * @brief Obtain the address of the first atom in a bag
 *
 * Obtain the address of the first atom in a bag that has been allocated in
 * the base context ring-buffer. The caller can then populate the bag.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx the context containing the ring-buffer where the
 *            bag has been allocated.
 * @param[in] bag the allocated bag
 * @return the address of the first ::base_jd_atom in the bag.
 */
base_jd_atom *base_bag_get_address(const base_context *ctx,
                                   const base_jd_bag *bag);

/**
 * @brief Obtain the address of the atom at a given offset in the ring
 * buffer
 *
 * Obtain the address of the atom at a given offset in the base
 * context ring-buffer. The offset is usually obtained by a
 * ::BASE_JD_EVENT_DONE event.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx the base context containing the ring-buffer.
 * @param offset the offset in the ring buffer where the atom is.
 * @return the address of the ::base_jd_atom in the ring buffer.
 */
base_jd_atom *base_atom_get_address(const base_context *ctx,
                                    size_t offset);

/**
 * @brief Ring-buffer region allocator
 *
 * This function allocates a contiguous region for atoms
 * (::base_jd_atom) belonging to a bag in the ring-buffer.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx          the base context
 * @param[in] bag          the bag that will reference the allocated region
 * @param[in,out] req_size a pointer to the required size (in bytes),
 *                         which must include the atoms and their
 *                         associated syncsets. The
 *                         ::base_jd_atom_size function should be used
 *                         to compute the size of each atom, and
 *                         *req_size should represent the sum of all
 *                         ::base_jd_atom_size calls for this bag.
 * @return MALI_ERR_NONE on success.
 * Any other value indicates failure (out of ring buffer space).
 * @post On failure, *req_size will contain the maximum free size in
 * the ring buffer at the time of failure.
 */
mali_error base_bag_acquire_buffer(base_context *ctx,
                                   base_jd_bag *bag, size_t *req_size);

/**
 * @brief Ring-buffer region release
 *
 * This function frees a region allocated to a bag for atom storage.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx the base context
 * @param[in] bag the bag that references the allocated region
 */
void base_bag_release_buffer(base_context *ctx, base_jd_bag *bag);

/**
 * @brief Inter job-chain dependency allocator
 *
 * This function allocates inter job-chain dependencies. Up to two
 * dependencies can be requested.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx or dep parameter.
 *
 * @param[in] ctx  the base context
 * @param[out] dep a pointer to a ::base_jd_dep that will hold the
 *                 dependency information. It is usually a pointer to
 *                 a base_jd_atom::post_dep. The dependency tags
 *                 contained in the base_jd_dep::dep array can be
 *                 then used as pre dependency information for other
 *                 atoms (base_jd_atom::pre_dep).
 * @param nr       the number of required dependencies. Must be either 1
 *                 (for a single dependency, or 2 (dual dependency).
 * @return MALI_ERR_NONE on success.
 * Any other value indicates failure (no free dependency).
 */
mali_error base_dep_acquire(base_context *ctx, base_jd_dep *dep, int nr);

/**
 * @brief Inter job-chain dependency delease
 *
 * This function releases inter job-chain dependencies. As
 * dependencies are a relatively scarce resource for a given base
 * context, they should be released as soon as a job-chain has
 * completed (usually in the ::base_jd_event_wait handler).
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx or dep parameter.
 *
 * @param[in] ctx the base context
 * @param[in] dep a pointer to a ::base_jd_dep that holds the
 *                dependency information. It is usually a pointer to a
 *                base_jd_atom::post_dep.
 */
void base_dep_release(base_context *ctx, base_jd_dep *dep);

/**
 * @brief Bag submission interface
 *
 * Submit a bag containing ::base_jd_atom elements to the GPU.
 * The function will return when the job-chains have been queued.
 * 
 * This function asserts when a bag is submitted for a base context
 * whose event system is shutdown with base_jd_event_term().
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx the base context used to run job-chains
 * @param[in] bag the bag containing the job-chains to be run on the GPU
 */
void base_jd_submit_bag(base_context *ctx, const base_jd_bag *bag);

/**
 * @brief Wait for a kernel event to append
 *
 * Blocks until an event (::base_jd_event) is reported by the kernel
 * driver. It is usually called in a loop, pumping events from the kernel
 * independently from bag submission.
 *
 * A ::BASE_JD_EVENT_DRV_TERMINATED event code indicate that the driver
 * is being terminated, and that this function should not be called anymore
 * with the same base context parameter.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx    the base driver used to run job-chains and to listen
 *                   to events
 * @param[out] event a valid pointer to a ::base_jd_event that will contain
 *                   the event description when returning from the call.
 */
void base_jd_event_wait(base_context *ctx, base_jd_event *event);

/**
 * @brief Terminates the kernel event system
 *
 * Informs the kernel driver to terminate its event system. The kernel
 * driver will report a last event with ::BASE_JD_EVENT_DRV_TERMINATED
 * event code to wake up the thread that is receiving events from the
 * kernel driver. This thread must not wait for any events from the
 * kernel driver from then on (for the base context provided).
 *
 * This function will return once the thread has received the last
 * event.
 * 
 * Once the kernel driver has shutdown its event system for the provided
 * base context, the base context will be marked as not capable to
 * start jobs anymore. Any attempt to submit jobs for this base context
 * will trigger an assertion.
 *
 * This function cannot be called from the event thread itself.
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx    the base driver used to run job-chains and to listen
 *                   to events
 */
void base_jd_event_term(base_context *ctx);

/**
 * @brief Determine whether a base_jd_event_code is in fact an error code
 *
 * @return MALI_FALSE if the event is NOT an error
 * @return any other value if the event IS and error
 */
static INLINE mali_bool base_jd_event_code_is_error( base_jd_event_code event )
{
	/* These ranges should be adjacent for our comparisons to work */
    CDBG_ASSERT_EQ_S( BASE_JD_EVENT_RANGE_HW_NONFAULT_END, BASE_JD_EVENT_RANGE_HW_FAULT_OR_SW_ERROR_START );
	/* Our comparison won't work on negative values */
    CDBG_ASSERT_LEQ_S( 0, BASE_JD_EVENT_RANGE_HW_NONFAULT_START );

	/* These values should never appear in user-space */
	CDBG_ASSERT( event != BASE_JD_EVENT_NOT_STARTED );
	CDBG_ASSERT( event != BASE_JD_EVENT_STOPPED );
	CDBG_ASSERT( event != BASE_JD_EVENT_ACTIVE );
	CDBG_ASSERT( event <  BASE_JD_EVENT_RANGE_SW_SUCCESS_END );

    if ( event != BASE_JD_EVENT_DONE && event < BASE_JD_EVENT_RANGE_HW_FAULT_OR_SW_ERROR_END )
	{
		/* Ensure that any fault is a TERMINATED or in the HW/SW Fault range */
		CDBG_ASSERT( event == BASE_JD_EVENT_TERMINATED || event >= BASE_JD_EVENT_RANGE_HW_FAULT_OR_SW_ERROR_START );
	}

	return (mali_bool)( event != BASE_JD_EVENT_DONE && event < BASE_JD_EVENT_RANGE_HW_FAULT_OR_SW_ERROR_END );
}

/** @} end group base_user_api_job_dispatch */

/** @} end group base_user_api */

/** @} end group base_api */

#endif
