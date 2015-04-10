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
 * @file mali_base_context.h
 * Base context dependent APIs.
 */

#ifndef _BASE_CONTEXT_H_
#define _BASE_CONTEXT_H_

#include <base/mali_base_types.h>

/**
 * @page page_base_user_api_core User-side Base Core APIs
 *
 * The core APIs of the User-side Base APIs contain only the concept of the Base Context.
 *
 * A Base context is the top-level instance in a Base driver object tree.
 * Other object instances belong to a single Base Context instance.
 * A Base context consists of both a user-side part and a kernel-side part.
 * Each of the other subsystems (job dispatch, memory management) track their data in a Base context,
 * thus all other objects are scoped to a Base context.
 * 
 * The user-side Base context only tracks simple things like the connection to the kernel-side,
 * a cache of the GPU properties obtained from the kernel-side for quick lookup,
 * in addition to tracking data for the other subsystems.
 *
 * The only subsystem storing data in the user-side context is the job manager.
 * It tracks usage of the job dependency semaphores and the ringbuffer.
 *
 * The kernel-side component of the Base context is where the most critical property of a base context
 * can be found. In the kernel-side component the memory management subsystem implements the MMU page tables.
 * This means that each Base context has a separate GPU VA space. 
 * This causes GPU memory addresses to just be valid in the Base context the memory was allocated from.
 * A different Base Context might or might not use the same address, and it will reference a different memory allocation if it exist.
 *
 * The job dispatch subsystem also stores data in the kernel-side object, where it tracks queued jobs and their dependency information.
 *
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
 * @addtogroup base_user_api_core User-side Base core APIs
 * @{
 */

/**
 * \enum base_context_create_flags
 *
 * Flags to pass to ::base_context_init.
 * Flags can be ORed together to enable multiple things.
 */
enum base_context_create_flags
{
	BASE_CONTEXT_CREATE_FLAG_NONE                      = 0      /**< No flags set */
};

/**
 * @brief Base context initialization
 * Establishes a connection to the privileged part of the driver
 * and creates a GPU virtual address space.
 *
 * Multiple base_contexts might exist in a process (each having a separate GPU VA space).
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[out] ctx pointer to the context to initialize
 * @param flags   flags enabling certain features for the base context,
 *                @see ::base_context_create_flags
 *
 * @return MALI_TRUE if context creation is successful, MALI_FALSE if it fails.
 */
mali_bool base_context_init( base_context * const ctx, u32 flags ) CHECK_RESULT;

/**
 * @brief Hardware counters collection enable.
 *
 * The collecting of hardware counters is an exclusive operation
 * and can fail if another client is using it.
 *
 * Each enable call must be paired with a matching call to ::base_context_hwcnt_disable
 * to allow other clients to collect hardware counters.
 *
 * On setup the hardware counters are reset to 0 and
 * they start to collect once this function returns.
 *
 * A memory address is given to indicate where calls to ::base_context_hwcnt_dump
 * will write to.
 * The memory address given must be allocated in the base context specified.
 * The memory address must be 2048 byte aligned.
 * The memory address to dump at must be writeable by the GPU.
 * The size of the dump buffer is 2048 bytes multiple by the number of core groups.
 *
 * 32-bit bitmaps are used to select subsets of the performance counters to collect.
 * Each bit in the bitmaps applies to four consecutive performance counters,
 * so that bit n when set enables counters 4*n-4 through to 4*n-1, inclusive.
 * If the bit is unset, the counters neither count nor are they written to memory
 * when ::base_context_hwcnt_dump is called.
 * Bit 0 controls the writing of the performance metadata - time stamp and enable mask.
 *
 * There are a 5 bitmaps:
 * @li Job manager
 * @li Shader cores
 * @li Tiler cores
 * @li Level 3 caches
 * @li Memory management units and Level 2 caches
 *
 * The function can fail due:
 * @li Hardware counters already being collected
 * @li Security policies denied access to collecting counters
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the base_ctx parameter.
 *
 * @param base_ctx Base context to enable collecting of counters for
 * @param dump_addr Memory address to dump at during ::base_context_hwcnt_dump
 * @param jm_bm Job manager bitmap
 * @param shader_bm Shader cores bitmap
 * @param tiler_bm Tiler cores bitmap
 * @param l3_cache_bm Level 3 caches bitmap
 * @param mmu_l2_bm MMU and Level 2 caches bitmap
 * @return MALI_ERROR_NONE - Counters enabled, collection started, ready to be dumped
 *         MALI_ERROR_FUNCTION_FAILED - Counters could not be enabled
 */
mali_error base_context_hwcnt_enable(base_context* base_ctx, mali_addr64 dump_addr, u32 jm_bm, u32 shader_bm, u32 tiler_bm, u32 l3_cache_bm, u32 mmu_l2_bm);

/**
 * @brief Dump hardware counters to memory.
 * Can only be called after successful call to ::base_context_hwcnt_enable
 * The counters will be reset after the dump.
 * Only the counters selected via ::base_context_hwcnt_enable will be written out.
 * The counters will be written to the buffer specified to ::base_context_hwcnt_enable.
 * If the dump resulted in a page fault (buffer too small or read-only memory) the call will fail.
 * If called without a matching call to ::base_context_hwcnt_enable the call will fail.
 * It is a programming error to pass an invalid pointer (including NULL) through the base_ctx parameter.

 * @param base_ctx The base context to dump the counters for
 * @return MALI_ERROR_NONE - Counters successfully dumped and reset
 *         MALI_ERROR_FUNCTION_FAILED - Counters failed to dump
 */
mali_error base_context_hwcnt_dump(base_context * base_ctx);

/**
 * @brief Hardware counters collection disable.
 * Releases the hardware counters collection interface
 * and allows other clients to use it.
 * Must be called for every call to ::base_context_hwcnt_enable.
 * In QA builds the driver will ASSERT if the counters are already disabled.
 * Callers should ensure that counters are disabled when they are not needed,
 * however for non-QA builds the counters will be disabled automatically as
 * part of the context cleanup to allow other contexts to use the counters
 * even if the disable call has not occurred (e.g. due to application crash).
 * It is a programming error to pass an invalid pointer (including NULL) through the base_ctx parameter.
 *
 * @param base_ctx The base context to stop collecting hardware counters for
 */
void base_context_hwcnt_disable(base_context * base_ctx);


/**
 * @brief Base context register trace enable.
 * Enable register trace for this base context.
 * Traces all register access done on behalf of this context, both reads and writes, once this function returns.
 *
 * The mapping contains a header and the actual register trace.
 * The register trace is circular.
 * The 64-bit header:
 * @li 31:0 - Magic - 0x45435254 (TRCE in ASCII)
 * @li 32 - Buffer transaction active - 0 for idle, 1 if an add is in progress
 * @li 47:33 - Circular buffer wrap count - 0 to 32767
 * @li 63:48 - Offset of last written register - 0 to 65535
 *
 * Following the header are registers, each occupying 8 bytes.
 * The count of registers is ((@p trace_buffer_size * OSK_PAGE_SIZE)/8)-1.
 * As the trace buffer is circular the logging of the registers can wrap and start to overwrite previous entries.
 * The client need to keep track of the wrap count and its last sampled offset to know if it has lost data or not due to the this.
 *
 * Each register access is stored in this 64-bit format:
 * @li 0 - Register read (0) or write (1)
 * @li 1 - RAZ
 * @li 31:2 - Register word offset
 * @li 63:32 - Register value read/written
 *
 * A call to enable the trace buffer must be matched with a call to ::base_context_reg_trace_disable.
 * After disable the trace buffer can be reenabled again.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 * Calling ::base_context_reg_trace_enable while trace is already active is considered a programming error.
 * The driver will assert on this in QA builds.
 * The function will return MALI_ERROR_FUNCTION_FAILED if this is detected for non-QA builds.
 *
 * @param[in] ctx The Base context to enable the register tracing for
 * @param trace_buffer_size Size, in pages, of the trace buffer, including the header
 * @param[out] mapping Returns a CPU mapping of the register trace buffer, with header.
 *
 * @return MALI_ERROR_FUNCTION_FAILED if the register trace could not be enabled for any reason
 *         MALI_ERROR_NONE if the trace was enabled correctly.
 */
mali_error base_context_reg_trace_enable(base_context *ctx, size_t trace_buffer_size, void** mapping);

/**
 * @brief Base context register trace disable.
 * Disables register tracing.
 * The previously returned mapping is no longer valid.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 * Calling ::base_context_reg_trace_disable while no tracing is enabled is considered a programming error.
 * The driver will assert on this in debug builds and silently ignore it for release builds.
 *
 * @param[in] ctx The Base context to disable the register tracing for
 */
void base_context_reg_trace_disable(base_context * ctx);

/**
 *
 * @brief Base context termination
 *
 * Releases the GPU virtual address space and releases the connection
 * to the privileged part of the driver.
 *
 * A thread that processes events for the base context must be woken up
 * and cease receiving events for the base context before the base context
 * is terminated. This is done by calling base_jd_event_term() before
 * the base context is terminated. In debug builds an assert triggers
 * if base_jd_event_term() hasn't been called before base_context_term().
 *
 * After termination the context object can be reinitialized again by calling ::base_context_init.
 *
 * You can only call ::base_context_term on a context object a previous call to ::base_context_init returned success for.
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx pointer to the context to terminate
 */
void base_context_term( base_context * const ctx );

/** Take a snapshot of the current (at time of API call) page tables.
 *
 * This function will return a buffer containing a dump of the MMU tables that the GPU uses. Each table is dumped as a 
 * 64 bit (modified) physical address followed by 512 64 bit page table entries dumped directly from memory (see the 
 * Midgard Architecture Specification for the meaning of these entries). The tables are dumped using a depth first 
 * traversal and are terminated by the value 64 bit value 0xFFULL, any data after this value should be ignored.
 *
 * The physical address that preceeds each table has the table level encoded in the bottom 12 bits (which would 
 * otherwise always be zero). The encoding is as follows:
 *
 * @li 0x00 - Page directory (level 0)
 * @li 0x01 - Level 1
 * @li 0x02 - Level 2
 * @li 0x03 - Level 3
 * @li 0xFF - Marker representing the end of the MMU dump
 *
 * For example a dump may look like the following:
 * @verbatim
 * 8 bytes - Physical address of page directory
 * 4096 bytes - Contents of page directory
 * 8 bytes - Physical address of a L1 page table (bottom 12 bits set to 0x01)
 * 4096 bytes - Contents of L1 page table
 * 8 bytes - Physical address of a L2 page table (bottom 12 bits set to 0x02)
 * 4096 bytes - Contents of L2 page table
 * 8 bytes - Physical address of a L3 page table (bottom 12 bits set to 0x03)
 * 4096 bytes - Contents of L3 page table
 * 8 bytes - Physical address of another L3 page table (bottom 12 bits set to 0x03)
 * 4096 bytes - Contents of L3 page table
 * <potentially more entries>
 * 8 bytes - End marker (0xFFULL)
 * @endverbatim
 *
 * @note If the number of virtual address bits used by the GPU is less than 40 then the page directory will not exist 
 * in the dump, instead the dump will start with the main L1 page table.
 *
 * This function will return NULL on failure, for example if the @c dump_size_max parameter is not large enough to fit 
 * the entire page table dump.
 *
 * When the buffer has been finished with, the memory should be freed by calling @ref 
 * base_context_mmu_snapshot_release.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx Base context to create the snapshot for
 * @param[in] dump_size_max The maximum size of the page table dump (specified in bytes, and
 * a multiple of OSK_PAGE_SIZE).
 * @return NULL if dumping failed due to error, otherwise a pointer to the snapshot
 */
void * base_context_mmu_snapshot_take(base_context * ctx, size_t dump_size_max);

/** Release MMU snapshot.
 *
 * This function frees the memory allocated by @ref base_context_mmu_snapshot_take.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx Base context the snapshot belongs to
 * @param[in] snapshot The snapshot to release
 * @param[in] dump_size_max The size that was originally passed into @ref base_context_mmu_snapshot_take
 */
void base_context_mmu_snapshot_release(base_context * ctx, void * snapshot, size_t dump_size_max);

/** @} end group base_user_api_core */

/** @} end group base_user_api */

/** @} end group base_api */

#endif
