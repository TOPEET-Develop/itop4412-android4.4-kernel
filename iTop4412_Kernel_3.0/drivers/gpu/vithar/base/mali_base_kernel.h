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
 * @file
 * Base structures shared with the kernel.
 */

#ifndef _BASE_KERNEL_H_
#define _BASE_KERNEL_H_

#include <base/src/mali_base_mem_priv.h>

/*
 * Dependency stuff, keep it private for now. May want to expose it if
 * we decide to make the number of semaphores a configurable
 * option.
 */
#define BASEP_JD_SEM_PER_WORD_LOG2	5
#define BASEP_JD_SEM_PER_WORD		(1 << BASEP_JD_SEM_PER_WORD_LOG2)
#define BASEP_JD_SEM_WORD_NR(x)		((x) >> BASEP_JD_SEM_PER_WORD_LOG2)
#define BASEP_JD_SEM_MASK_IN_WORD(x)	(1 << ((x) & (BASEP_JD_SEM_PER_WORD - 1)))
#define BASEP_JD_SEM_ARRAY_SIZE		BASEP_JD_SEM_WORD_NR(256)

/* Size of the ring buffer */
#define BASEP_JCTX_RB_NRPAGES	16


/**
 * @addtogroup base_user_api User-side Base APIs
 * @{
 */

/**
 * @addtogroup base_user_api_memory User-side Base Memory APIs
 * @{
 */

/**
 * @brief Memory allocation, access/hint flags
 *
 * A combination of MEM_PROT/MEM_HINT flags must be passed to each allocator
 * in order to determine the best cache policy. Some combinations are
 * of course invalid (eg @c MEM_PROT_CPU_WR | @c MEM_HINT_CPU_RD),
 * which defines a @a write-only region on the CPU side, which is
 * heavily read by the CPU...
 * Other flags are only meaningful to a particular allocator.
 * More flags can be added to this list, as long as they don't clash
 * (see ::BASE_MEM_FLAGS_NR_BITS for the number of the first free bit).
 */
typedef u32 base_mem_alloc_flags;


/**
 * @brief Memory allocation, access/hint flags
 *
 * See ::base_mem_alloc_flags.
 *
 */
enum
{
	BASE_MEM_PROT_CPU_RD =	(1U << 0), /**< Read access CPU side */
	BASE_MEM_PROT_CPU_WR =	(1U << 1), /**< Write access CPU side */
	BASE_MEM_PROT_GPU_RD =	(1U << 2), /**< Read access GPU side */
	BASE_MEM_PROT_GPU_WR =	(1U << 3), /**< Write access GPU side */
	BASE_MEM_PROT_GPU_EX =	(1U << 4), /**< Execute allowed on the GPU side */

	BASE_MEM_HINT_CPU_RD =	(1U << 5), /**< Heavily read CPU side */
	BASE_MEM_HINT_CPU_WR =	(1U << 6), /**< Heavily written CPU side */
	BASE_MEM_HINT_GPU_RD =	(1U << 7), /**< Heavily read GPU side */
	BASE_MEM_HINT_GPU_WR =	(1U << 8), /**< Heavily written GPU side */

	BASE_MEM_GROW_ON_GPF =	(1U << 9), /**< Grow backing store on GPU Page Fault */

	BASEP_MEM_IS_CACHED =	(1U << 10) /**< Is cached (Kernel hint only) */
};

/**
 * @brief Number of bits used as flags for base memory management
 *
 * Must be kept in sync with the ::base_mem_alloc_flags flags
 */
#define BASE_MEM_FLAGS_NR_BITS	11

/**
 * @brief Result codes of changing the size of the backing store allocated to a tmem region
 */
typedef enum base_backing_threshold_status
{
	BASE_BACKING_THRESHOLD_OK = 0,                      /**< Resize successful */
	BASE_BACKING_THRESHOLD_ERROR_NOT_GROWABLE = -1,     /**< Not a growable tmem object */
	BASE_BACKING_THRESHOLD_ERROR_OOM = -2,              /**< Increase failed due to an out-of-memory condition */
	BASE_BACKING_THRESHOLD_ERROR_MAPPED = -3,           /**< Resize attempted on buffer while it was mapped, which is not permitted */
	BASE_BACKING_THRESHOLD_ERROR_INVALID_ARGUMENTS = -4 /**< Invalid arguments (not tmem, illegal size request, etc.) */
} base_backing_threshold_status;

/**
 * @addtogroup base_user_api_memory_defered User-side Base Defered Memory Coherency APIs
 * @{
 */

/**
 * @brief a basic memory operation (sync-set).
 *
 * The content of this structure is private, and should only be used
 * by the accessors.
 */
typedef struct base_syncset
{
	basep_syncset basep_sset;
} base_syncset;

/** @} end group base_user_api_memory_defered */

/** @} end group base_user_api_memory */

/**
 * @addtogroup base_user_api_job_dispatch User-side Base Job Dispatcher APIs
 * @{
 */

/**
 * @brief A pre- or post- dual dependency.
 *
 * This structure is used to express either
 * @li a single or dual pre-dependency (a job depending on one or two
 * other jobs),
 * @li a single or dual post-dependency (a job resolving a dependency
 * for one or two other jobs).
 *
 * The dependency itself is specified as a u8, where 0 indicates no
 * dependency. A single dependency is expressed by having one of the
 * dependencies set to 0.
 */
typedef struct base_jd_dep {
	u8		dep[2]; /**< pre/post dependencies */
} base_jd_dep;

/**
 * @brief Per-job data
 *
 * This structure is used to store per-job data, and is completly unused
 * by the Base driver. It can be used to store things such as callback
 * function pointer, data to handle job completion. It is guaranteed to be
 * untouched by the Base driver.
 */
typedef struct base_jd_udata
{
	u64		blob[2]; /**< per-job data array */
} base_jd_udata;

/**
 * @brief Job chain hardware requirements.
 *
 * A job chain must specify what GPU features it needs to allow the
 * driver to schedule the job correctly.  By not specifying the
 * correct settings can/will cause an early job termination.  Multiple
 * values can be ORed together to specify multiple requirements.
 * Special case is ::BASE_JD_REQ_DEP, which is used to express complex
 * dependencies, and that doesn't execute anything on the hardware.
 */
typedef u8 base_jd_core_req;

/* Requirements that come from the HW */
#define	BASE_JD_REQ_DEP	0		/**< No requirement, dependency only */
#define	BASE_JD_REQ_FS	(1U << 0)	/**< Requires fragment shaders */
#define	BASE_JD_REQ_CS	(1U << 1)	/**< Requires compute shaders */
#define	BASE_JD_REQ_T	(1U << 2)	/**< Requires tiling */
#define	BASE_JD_REQ_CF	(1U << 3)	/**< Requires cache flushes */
#define	BASE_JD_REQ_V	(1U << 4)	/**< Requires value writeback */

/* SW-only requirements - the HW does not expose these as part of the job slot capabilities */
/**
 * SW Only requirement: this job chain might not be soft-stoppable (Non-Soft
 * Stoppable), and so must be scheduled separately from all other job-chains
 * that are soft-stoppable.
 *
 * In absence of this requirement, then the job-chain is assumed to be
 * soft-stoppable. That is, if it does not release the GPU "soon after" it is
 * soft-stopped, then it will be killed. In contrast, NSS job chains can
 * release the GPU "a long time after" they are soft-stopped.
 *
 * "soon after" and "a long time after" are implementation defined, and
 * configurable in the device driver by the system integrator.
 */
#define	BASE_JD_REQ_NSS (1U << 5)

/**
 * SW Only requirement: the job chain requires a coherent core group. We don't
 * mind which coherent core group is used.
 */
#define	BASE_JD_REQ_COHERENT_GROUP (1U << 6)


/**
 * This requirement is currently unused - but it's the last one available in
 * our base_jd_core_req (currently a u8)
 */
#define	BASEP_JD_REQ_RESERVED (1U << 7)

/**
 * @brief A single job chain, with pre/post dependendencies and mem ops
 *
 * This structure is used to describe a single job-chain to be submitted
 * as part of a bag.
 * It contains all the necessary information for Base to take care of this
 * job-chain, including core requirements, priority, syncsets and
 * dependencies.
 */
typedef struct base_jd_atom
{
	base_jd_udata		udata;		/**< user data */
	mali_addr64		jc;		/**< job-chain GPU address */
	base_jd_dep		pre_dep;	/**< pre-dependencies */
	base_jd_dep		post_dep;	/**< post-dependencies */
	u16			nr_syncsets;	/**< nr of syncsets following the atom */
	base_jd_core_req	core_req;	/**< core requirements */

	/** @brief Relative priority.
	 *
	 * A positive value requests a lower priority, whilst a negative value
	 * requests a higher priority. Only privileged processes may request a
	 * higher priority. For unprivileged processes, a negative priority will
	 * be interpreted as zero.
	 */
	s8			prio;
} base_jd_atom;

/* Lot of hacks to cope with the fact that C89 doesn't allow arrays of size 0 */
typedef struct basep_jd_atom_ss
{
	base_jd_atom	atom;
	base_syncset	syncsets[1];
} basep_jd_atom_ss;

/**
 * @brief Atom size evaluator
 *
 * This function returns the size in bytes of a ::base_jd_atom
 * containing @a n syncsets. It must be used to compute the size of a
 * bag before allocation.
 *
 * @param nr the number of syncsets for this atom
 * @return the atom size in bytes
 */
static INLINE size_t base_jd_atom_size(u32 nr)
{
	return nr ? offsetof(basep_jd_atom_ss, syncsets[nr]) : sizeof(base_jd_atom);
}

/**
 * @brief Atom syncset accessor
 *
 * This function returns a pointer to the nth syncset allocated
 * together with an atom.
 *
 * @param[in] atom The allocated atom
 * @param     n    The number of the syncset to be returned
 * @return a pointer to the nth syncset.
 */
static INLINE base_syncset *base_jd_get_atom_syncset(base_jd_atom *atom, int n)
{
	return &((basep_jd_atom_ss *)atom)->syncsets[n];
}

/**
 * @brief Next atom accessor
 *
 * This function returns a pointer to the next allocated atom. It
 * relies on the fact that the current atom has been correctly
 * initialized (relies on the base_jd_atom::nr_syncsets field).
 *
 * @param[in] atom The allocated atom
 * @return a pointer to the next atom.
 */
static INLINE base_jd_atom *base_jd_get_next_atom(base_jd_atom *atom)
{
	return (base_jd_atom *)base_jd_get_atom_syncset(atom, atom->nr_syncsets);
}

/**
 * @brief Job chain event codes
 *
 * HW and low-level SW events are represented by event codes.
 * The status of jobs which succeeded are also represented by
 * an event code (see ::BASE_JD_EVENT_DONE).
 * Events are usually reported as part of a ::base_jd_event.
 *
 * Events are split up into ranges as follows:
 * - BASE_JD_EVENT_RANGE_\<description\>_START
 * - BASE_JD_EVENT_RANGE_\<description\>_END
 *
 * \a code is in \<description\>'s range when:
 * - <tt>BASE_JD_EVENT_RANGE_\<description\>_START <= code < BASE_JD_EVENT_RANGE_\<description\>_END </tt>
 *
 * Ranges can be asserted for adjacency by testing that the END of the previous
 * is equal to the START of the next. This is useful for optimizing some tests
 * for range.
 *
 * A limitation is that the last member of this enum must explicitly be handled
 * (with an assert-unreachable statement) in switch statements that use
 * variables of this type. Otherwise, the compiler warns that we have not
 * handled that enum value.
 */
typedef enum base_jd_event_code
{
	/* HW defined exceptions */

	/** Start of HW Non-fault status codes
	 *
	 * @note Obscurely, BASE_JD_EVENT_TERMINATED indicates a real fault,
	 * because the job was hard-stopped
	 */
	BASE_JD_EVENT_RANGE_HW_NONFAULT_START = 0x00,

	/* non-fatal exceptions */
	BASE_JD_EVENT_NOT_STARTED = 0x00, /**< Can't be seen by userspace, treated as 'previous job done' */
	BASE_JD_EVENT_DONE = 0x01, 
	BASE_JD_EVENT_STOPPED = 0x03,     /**< Can't be seen by userspace, becomes TERMINATED, DONE or JOB_CANCELLED */
	BASE_JD_EVENT_TERMINATED = 0x04,  /**< This is actually a fault status code - the job was hard stopped */
	BASE_JD_EVENT_ACTIVE = 0x08,      /**< Can't be seen by userspace, jobs only returned on complete/fail/cancel */

	/** End of HW Non-fault status codes
	 *
	 * @note Obscurely, BASE_JD_EVENT_TERMINATED indicates a real fault,
	 * because the job was hard-stopped
	 */
	BASE_JD_EVENT_RANGE_HW_NONFAULT_END = 0x40,

	/** Start of HW fault and SW Error status codes */
	BASE_JD_EVENT_RANGE_HW_FAULT_OR_SW_ERROR_START = 0x40,

	/* job exceptions */
	BASE_JD_EVENT_JOB_CONFIG_FAULT = 0x40,
	BASE_JD_EVENT_JOB_POWER_FAULT = 0x41,
	BASE_JD_EVENT_JOB_READ_FAULT = 0x42,
	BASE_JD_EVENT_JOB_WRITE_FAULT = 0x43,
	BASE_JD_EVENT_JOB_AFFINITY_FAULT = 0x44,
	BASE_JD_EVENT_JOB_BUS_FAULT = 0x48,
	BASE_JD_EVENT_INSTR_INVALID_PC = 0x50,
	BASE_JD_EVENT_INSTR_INVALID_ENC = 0x51,
	BASE_JD_EVENT_INSTR_TYPE_MISMATCH = 0x52,
	BASE_JD_EVENT_INSTR_OPERAND_FAULT = 0x53,
	BASE_JD_EVENT_INSTR_TLS_FAULT = 0x54,
	BASE_JD_EVENT_INSTR_BARRIER_FAULT = 0x55,
	BASE_JD_EVENT_INSTR_ALIGN_FAULT = 0x56,
	BASE_JD_EVENT_DATA_INVALID_FAULT = 0x58,
	BASE_JD_EVENT_TILE_RANGE_FAULT = 0x59,
	BASE_JD_EVENT_STATE_FAULT = 0x5A,
	BASE_JD_EVENT_OUT_OF_MEMORY = 0x60,
	
	/* GPU exceptions */
	BASE_JD_EVENT_DELAYED_BUS_FAULT = 0x80,
	BASE_JD_EVENT_SHAREABILITY_FAULT = 0x88,
	
	/* MMU exceptions */
	BASE_JD_EVENT_TRANSLATION_FAULT_LEVEL1	= 0xC1,
	BASE_JD_EVENT_TRANSLATION_FAULT_LEVEL2	= 0xC2,
	BASE_JD_EVENT_TRANSLATION_FAULT_LEVEL3	= 0xC3,
	BASE_JD_EVENT_TRANSLATION_FAULT_LEVEL4	= 0xC4,
	BASE_JD_EVENT_PERMISSION_FAULT		= 0xC8,
	BASE_JD_EVENT_TRANSTAB_BUS_FAULT_LEVEL1	= 0xD1,
	BASE_JD_EVENT_TRANSTAB_BUS_FAULT_LEVEL2	= 0xD2,
	BASE_JD_EVENT_TRANSTAB_BUS_FAULT_LEVEL3	= 0xD3,
	BASE_JD_EVENT_TRANSTAB_BUS_FAULT_LEVEL4	= 0xD4,
	BASE_JD_EVENT_ACCESS_FLAG		= 0xD8,

	/* SW defined exceptions */
	BASE_JD_EVENT_MEM_GROWTH_FAILED = 0x8000,
	BASE_JD_EVENT_TIMED_OUT         = 0x8001,
	BASE_JD_EVENT_BAG_DONE_BUT_INSTRUMENTATION_FAILED = 0x8005,
	BASE_JD_EVENT_JOB_CANCELLED     = 0x8006,
	BASE_JD_EVENT_BAG_INVALID       = 0x8007,

	/** End of HW fault and SW Error status codes */
	BASE_JD_EVENT_RANGE_HW_FAULT_OR_SW_ERROR_END = 0x9000,

	/** Start of SW Success status codes */
	BASE_JD_EVENT_RANGE_SW_SUCCESS_START = 0x9000,

	BASE_JD_EVENT_PROGRESS_REPORT   = 0x9000,
	BASE_JD_EVENT_BAG_DONE          = 0x9001,
	BASE_JD_EVENT_DRV_TERMINATED    = 0x9002,

	/** End of SW Success status codes */
	BASE_JD_EVENT_RANGE_SW_SUCCESS_END = 0xA000,

	/** Start of Kernel-only status codes. Such codes are never returned to user-space */
	BASE_JD_EVENT_RANGE_KERNEL_ONLY_START = 0xA000,
	BASE_JD_EVENT_REMOVED_FROM_NEXT = 0xA000,

	/** End of Kernel-only status codes. */
	BASE_JD_EVENT_RANGE_KERNEL_ONLY_END = 0xB000
} base_jd_event_code;

/**
 * @brief Event reporting structure
 *
 * This structure is used by the kernel driver to report information
 * about GPU events. The can either be HW-specific events or low-level
 * SW events, such as job-chain completion.
 *
 * Each event is reported together with event-specific data:
 * @li ::BASE_JD_EVENT_DONE : the offset in the ring-buffer for the completed
 * job-chain.
 * @li ::BASE_JD_EVENT_BAG_DONE : The address of the ::base_jd_bag that has
 * been completed (ie all contained job-chains have been completed).
 * @li ::BASE_JD_EVENT_BAG_DONE_BUT_INSTRUMENTATION_FAILED : same as
 * BASE_JD_EVENT_BAG_DONE, but the instrumentation sampling failed due
 * to a policy decision or log buffer exception, so the log buffer
 * content can't be trusted.
 * @li ::BASE_JD_EVENT_BAG_INVALID : The address of the ::base_jd_bag that has
 * been found invalid and canceled.
 * @li ::BASE_JD_EVENT_DRV_TERMINATED : Indicate that the driver has
 * been terminated.
 */
typedef struct base_jd_event
{
	base_jd_event_code	event_code;	/**< event code */
	void			*data;		/**< event specific data */
} base_jd_event;

/** @} end group base_user_api_job_dispatch */

/** @} end group base_user_api */

/** @} end group base_api */

#endif /* _BASE_KERNEL_H_ */
