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
 * Base memory APIs
 */

#ifndef _BASE_MEMORY_H_
#define _BASE_MEMORY_H_

#include <ump/ump.h>
#include <plat/mali_base_plat_memory.h>
#include <base/mali_base_kernel.h>

/**
 * @page page_base_user_api_mem User-side Base Memory APIs
 *
 * The main goal of the Base Memory APIs is to provide the upper layers
 * with flexible block allocators. These block allocators are in turn
 * used by the common layer to implement finer grained allocators.
 *
 * Refer to the @ref base_user_api_memory "User-side Base Memory APIs module"
 * for detailed API information.
 *
 * @section mem_types Memory types
 *
 * The memory APIs offers several memory types, as well as several
 * options to ensure memory coherency.
 *
 * The basic memory types are:
 * @li @a Permanent memory (aka pmem): A range of memory being permanently
 * mapped on both CPU and GPU address spaces, at the same virtual address.
 * Mapping occurs upon allocation, and unmapping occurs upon freeing
 * the region. This is a relatively scarse resource, and it must not be
 * abused. It also cannot be shared between different processes.
 * @li @a Transient memory (aka tmem): A range of memory being permanently
 * mapped on the GPU side, and a transient/partial mapping on the CPU side.
 * Mapping on the CPU side does not have the same virtual address as on the
 * GPU side. On the GPU side, the virtual address of a tmem region is
 * always a 64bit value.
 * A tmem region can either be fully backed with physical
 * pages, or only partially populated (with more physical pages being added
 * over time). It is then called a @a growable tmem.
 *
 * It must be noted that @a permanent is here as opposed to @a transient,
 * and only describe the mapping of memory in the CPU virtual address
 * space.
 *
 * The allocators for these memory types accept @a hints that are used to
 * decide upon the cacheability of the memory region. The API offers no
 * direct control over the cacheability, so cache coherency operations
 * must always be carried out, though they might be eliminated at runtime
 * if possible (if memory is not cached for example).
 *
 * For both types of memory, it is possible to enforce memory
 * coherency over a memory range by synchronizing to the GPU (cache
 * clean on the CPU side) or to the CPU (cache clean on the GPU side,
 * invalidate on CPU side). The GPU-side cache maintenance is assumed
 * to be handled by job(chain) authors.
 *
 * Furthermore, @a tmem offers a map/unmap interface to control which
 * part of a memory region is visible on the CPU side.
 *
 * All cache synchronization operations must be done explicitly.
 * Failure to do so will result in data loss. The only exceptions are
 * the map/unmap operations which ensure proper invalidation/write-back.
 *
 * @section defered_coherency Defered coherency
 *
 * Memory regions are inherently linked to job-chains, either by containing
 * the jobs themselves, or by being referred indirectly by job descriptors.
 * Thus, it is necessary to execute memory coherency operations before
 * starting a job (making sure the GPU has access to the most recent data)
 * and after it is done (making sure the CPU has access to the most recent
 * data).
 *
 * There is two different options to maintain memory coherency:
 * @li by executing memory coherency each time a memory region is touched
 * (which might be very expensive in the long run),
 * @li by batching memory coherency operations associated with a memory region.
 *
 * In the second case, it is possible to associate @a deferred sync sets with
 * a region (the sync operations won't be triggered yet). When the
 * associated job is ready to be run, the sync sets are then @a transferred
 * to the job.
 *
 * The memory operations (sync sets)  are split in two groups, depending on
 * when they are executed with respect to the job execution:
 * @li job start:  executes "sync to GPU" and "unmap",
 * @li job end: executes "sync to CPU" and "map".
 *
 * The file mali_base_jd_test.c, found under the "Examples" tab, shows
 * the API being used.
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
 * @addtogroup base_user_api_cpu User-side Base CPU APIs
 * @{
 */

/** @} end group base_user_api_cpu */

/**
 * @addtogroup base_user_api_memory User-side Base Memory APIs
 * @{
 */

/**
 * @brief Sync a mapped region for GPU usage
 *
 * Perform the necessary memory coherency operations on a given memory
 * region, so that after the call, changes in memory is correctly seen
 * by the GPU. Any change made to memory after that call may not be seen
 * by the GPU.
 *
 * The handle is checked to be valid in the given base context.
 * If the handle is found to not exist in the base context nothing happens.
 * The cpu_address is checked to be a valid mapping of the memory handle given.
 * If the cpu_address is found to not be a mapping of the given handle 
 * nothing happens.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx         The Base Context used for the allocation.
 * @param     handle      Generic memory handle on which to operate
 * @param[in] cpu_address The CPU address where to start the sync operation.
 *                        The address might be rounded down to a cache line
 *                        boundary by this function if necessary.
 * @param     size        The number of bytes to be synced.
 *                        Might be rounded up to a cache line boundary by this
 *                        function if necessary.
 */
void base_sync_to_gpu_now(base_context *ctx, base_mem_handle handle,
                          void *cpu_address, size_t size);

/**
 * @brief Sync a mapped region for CPU usage
 *
 * Perform the necessary memory coherency operations on a given memory
 * region, so that after the call, changes in memory is correctly seen
 * by the CPU. Any change made to this region by the CPU before that call
 * may be lost.
 *
 * The handle is checked to be valid in the given base context.
 * If the handle is found to not exist in the base context nothing happens.
 * The cpu_address is checked to be a valid mapping of the memory handle given.
 * If the cpu_address is found to not be a mapping of the given handle 
 * nothing happens.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in]  ctx         The Base Context used for the allocation.
 * @param      handle      Generic memory handle on which to operate
 * @param[out] cpu_address The CPU address where to start the sync operation.
 *                         The address might be rounded down to a cache line
 *                         boundary by this function if necessary.
 * @param      size        The number of bytes to be synced.
 *                         Might be rounded up to a cache line boundary by this
 *                         function if necessary.
 */
void base_sync_to_cpu_now(base_context *ctx, base_mem_handle handle,
                          void *cpu_address, size_t size);

/**
 * @brief Map a GPU region for dumping.
 *
 * Map a GPU region onto the CPU to read for dumping. The mapping should be
 * considered read-only. This function may return a pointer to an existing
 * mapping (which may not be read-only) instead of creating a new mapping.
 * This function must only be called when the address is known to be mapped
 * onto the GPU (for example when @ref base_context_mmu_snapshot_take has
 * returned it as part of the GPU's page tables). Calling on an address that
 * is not mapped has undefined behavior (e.g. an invalid pointer may be
 * returned). Equally causing the page to be unmapped using other base
 * functions may cause this pointer to become invalid before @ref
 * base_memory_dumping_unmap is called.
 *
 * The returned pointer must be freed using @ref base_memory_dumping_unmap
 * when it is finished with. This should occur before the memory is
 * deallocated by other base functions.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx       The Base Context to use.
 * @param     gpu_addr  The GPU virtual address to map.
 * @param     pages     The number of pages to map (must be greater than 0).
 *
 * @return A pointer to the mapped memory or NULL on error.
 */
void * base_memory_dumping_map(base_context *ctx, mali_addr64 gpu_addr,
                               size_t pages);

/**
 * @brief Free a mapping previously returned from @ref
 * base_memory_dumping_map.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx       The Base Context to use.
 * @param     gpu_addr  The GPU virtual address passed to @ref
 *                      base_memory_dumping_map
 * @param[in] mapping   The address returned from @ref base_memory_dumping_map
 * @param     pages     The number of pages originally passed to @ref
 *                      base_memory_dumping_map
 */
void base_memory_dumping_unmap(base_context *ctx, mali_addr64 gpu_addr,
                               void *mapping, size_t pages);

/**
 * @addtogroup base_user_api_memory_pmem User-side Base Permanently Mapped Memory APIs
 * @{
 */

/**
 * @brief Permanently mapped memory allocator
 *
 * Creates a memory region, and map it permanently in both CPU and GPU
 * virtual address spaces. the resulting memory region is guaranteed
 * to be page aligned.
 * The allocation can fail due to:
 * @li No contiguous CPU VA was large enough to hold the allocation
 * @li No contiguous GPU VA was large enough to hold the allocation
 * @li OS resource policies denied the allocation
 * @li Not enough physical memory to back the allocation
 * All these error cases results in NULL being returned.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx or handle parameter.
 *
 * @param[in]  ctx    The Base Context used for the allocation.
 * @param      pages  The size of the requested region, in pages.
 * @param      flags  An or-ed combination of ::base_mem_alloc_flags flags
 *                    defining the access rights as well as hints on how
 *                    the memory region is used (affects cacheability).
 * @param[out] handle A pointer to a variable which will hold the handle
 *                    to the memory region
 * @return A pointer to the mapped region, or NULL if failed
 */
void *base_pmem_alloc(base_context *ctx, u32 pages, u32 flags,
                      base_pmem_handle *handle);

/**
 * @brief Permanently mapped memory destructor
 *
 * Destroy a permanently mapped region.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx     The Base Context used for the allocation.
 * @param     handle  The pmem handle to be released
 * @param     pages   The size of the region to free, in pages.
 */
void base_pmem_free(base_context * ctx, base_pmem_handle handle, u32 pages);

/**
 * @brief Get permanently mapped region CPU address
 *
 * Obtain the virtual address for this region.
 * @param handle The pmem handle on which the VA is queried.
 * @return The VA of the considered region, or NULL if invalid.
 */
void *base_pmem_get_cpu_address(base_pmem_handle handle);

/**
 * @brief Get permanently mapped region GPU address
 *
 * Obtain the virtual address for this region.
 * @param handle The pmem handle on which the VA is queried.
 * @param offset An offset (in bytes) within the pmem region
 * @return The GPU virtual address of @a offset within the pmem region,
 *         or 0 if failed.
 */
mali_addr64 base_pmem_get_gpu_address(base_pmem_handle handle, size_t offset);

/**
 * @brief Convert CPU address to GPU address for a pmem region
 *
 * Obtain the GPU virtual address for this region.
 * @param     handle  The pmem handle on which the VA is queried.
 * @param[in] addr    A CPU VA within the pmem region
 * @return The GPU virtual address corresponding to @a address within
 *         the pmem region, or 0 if failed.
 */
mali_addr64 base_pmem_cpu_address_to_gpu(base_pmem_handle handle,
                                         const void *addr);

/** @} end group base_user_api_memory_pmem */

/**
 * @addtogroup base_user_api_memory_tmem User-side Base Transient Mapped Memory APIs
 * @{
 */

/**
 * @brief Transient mapped growable memory allocator
 *
 * Creates a virtual memory region, and map it permanently in the GPU
 * address space.
 * Only a part of the mapping is initially backed by physical memory, and
 * can be automatically backed by more pages if an extent size is provided.
 * The allocation can fail due to:
 * @li No contiguous GPU VA was large enough to hold the allocation
 * @li OS resource policies denied the allocation
 * @li Not enough physical memory to back the allocation
 * All these error cases results in BASE_TMEM_INVALID_HANDLE being returned.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx          The Base Context used for the allocation.
 * @param     max_pages    The size of the requested region, in pages.
 * @param     init_pages   The size of the initial physical backing store, in pages.
 * @param     extent_pages The amount of physical backing (in pages) that
 *                         will automatically be provided if the GPU
 *                         generates a page fault in this region (up to the
 *                         size of the region).
 *                         Requires the ::BASE_MEM_GROW_ON_GPF flags.
 * @param     flags        An or-ed combination of ::base_mem_alloc_flags flags
 *                         defining the access rights as well as hints on
 *                         how the memory region is used (affects
 *                         cacheability).
 * @return A tmem handle, or BASE_TMEM_INVALID_HANDLE if failed.
 */
base_tmem_handle base_tmem_alloc_growable(base_context *ctx, u32 max_pages,
                                          u32 init_pages, u32 extent_pages,
                                          u32 flags) CHECK_RESULT;

/**
 * @brief Transient mapped memory allocator
 *
 * Creates a virtual memory region, fully backed by physical memory, and
 * map it permanently in the GPU address space.
 * The allocation can fail due to:
 * @li No contiguous GPU VA was large enough to hold the allocation
 * @li OS resource policies denied the allocation
 * @li Not enough physical memory to back the allocation
 * All these error cases results in BASE_TMEM_INVALID_HANDLE being returned.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx   The Base Context used for the allocation.
 * @param     pages The size of the requested region, in pages.
 * @param     flags An or-ed combination of ::base_mem_alloc_flags flags
 *                  defining the access rights as well as hints on how the
 *                  memory region is used (affects cacheability).
 * @return A tmem handle, or BASE_TMEM_INVALID_HANDLE if failed.
 */
static INLINE CHECK_RESULT base_tmem_handle base_tmem_alloc(base_context *ctx,
                                                            u32 pages,
                                                            u32 flags)
{
	CDBG_ASSERT_POINTER(ctx);
	return base_tmem_alloc_growable(ctx, pages, pages, 0,
	                                flags & ~BASE_MEM_GROW_ON_GPF);
}

/**
 * @brief Transient mapped memory destructor
 *
 * Destroy a transient mapped region. Calling this function while
 * the region is either
 * @li mapped
 * @li in use by the GPU
 * 
 * is illegal, and has unpredictable consequences.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx     The Base Context used for the allocation.
 * @param     handle  The tmem handle to be released
 */
void base_tmem_free(base_context * ctx, base_tmem_handle handle);


/**
 * @brief Manage the size of the backing store allocated to a tmem region
 *
 * Allow to obtain, increase or reduce the size of the backing store
 * associated with a tmem region.
 *
 * If an error occurs, the size of the backing store remains unchanged.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param      ctx         The context the tmem belongs to
 * @param      handle      The tmem handle on which to operate.
 * @param      page_delta  @li If positive, the number of pages to add to the backing store.
 *                         @li if negative, the number of pages to remove from the backing store.
 *                         @li if 0, returns the current size (in pages) of the backing-store.
 * @param[out] pages       The new or current size of the backing store, in pages.
 * @return BASE_BACKING_THRESHOLD_OK on success. Any other value indicates failure,
 * @see ::base_backing_threshold_status.
 *
 */
base_backing_threshold_status base_tmem_set_backing_threshold(base_context *ctx,
                                                              base_tmem_handle handle,
                                                              s32 page_delta,
                                                              u32 *pages) CHECK_RESULT;


/**
 * @brief Partially map a tmem region in CPU address space.
 *
 * Map a tmem region in CPU virtual address space, and perform the
 * necessary memory operations so that the mapped region has a view
 * of what is currently in memory.
 *
 * Overlapping mappings are supported and will be coherent with each other.
 * To identify the correct mapping when unmapping the returned pointer
 * must be passed to ::base_tmem_unmap
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx    The context the tmem belongs to
 * @param     handle The region to be mapped

 * @param     offset An offset (in bytes) in the region at which the mapping begins.
 *                   This might be rounded down to a page boundary. In
 *                   such a case, the returned address will reflect
 *                   this correction.
 * @param     size   The number of bytes to be mapped. This might be rounded
 *                   up to a page boundary.
 * @return The CPU address at which the region has been mapped, or NULL
 * if failed.
 */
void *base_tmem_map(base_context * ctx, base_tmem_handle handle, mali_size64 offset, size_t size) CHECK_RESULT;

/**
 * @brief Unmap a tmem region from CPU address space.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx     The context the memory belongs to
 * @param     handle  The region to be unmapped.
 * @param[in] address The CPU virtual address at which the region has been
 *                    mapped.  This must be the address as returned by
 *                    ::base_tmem_map, as it is internally used as the mapping
 *                    identifier.
 * @param size        The number of bytes to be unmapped. This will be
 *                    rounded up to a page boundary.
 * @return MALI_ERROR_NONE on success. Any other value indicates failure.
 */
mali_error base_tmem_unmap(base_context * ctx, base_tmem_handle handle, const void *address, size_t size); 

/**
 * @brief Get a GPU address for a tmem region.
 *
 * Obtain a GPU address for a given tmem region. The region doesn't have
 * to be mapped in the CPU virtual address space.
 *
 * @param handle The region on which to operate.
 * @param offset An offset (in bytes) within the tmem region
 * @return The GPU virtual address of @a offset within the tmem
 * region, or 0 if failed.
 */
mali_addr64 base_tmem_get_gpu_address(base_tmem_handle handle,
				      mali_size64 offset);

/**
 * @brief Use UMP memory as tmem.
 *
 * Obtain a base_tmem_handle from an ump_secure_id.
 * If the ID isn't valid or if permission is denied a BASE_TMEM_INVALID_HANDLE handle will be returned.
 * The tmem will be non-growable.
 * Any GPU or CPU permissions and usage hints we be queried from the UMP object.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx    The context to create the tmem in
 * @param     ump_id The UMP secure ID to create a tmem from
 * @param[in] pages  Pointer to a u64 where the size (in pages) of the tmem will be stored. Can be NULL if the size isn't needed.
 * @return A tmem handle, or BASE_TMEM_INVALID_HANDLE if failed.
 */
base_tmem_handle base_tmem_from_ump(base_context *ctx, ump_secure_id ump_id, u64 * const pages) CHECK_RESULT;

/** @} end group base_user_api_memory_tmem */

/**
 * @addtogroup base_user_api_memory_defered User-side Base Defered Memory Coherency APIs
 * @{
 */


/**
 * @brief Deferred sync of a mapped region for GPU usage
 *
 * Deferred equivalent to ::base_sync_to_gpu_now. Instead of being
 * directly executed, the synchronization request is stored in the
 * provided ::base_syncset, and executed when the job referencing
 * this sync set will be executed.
 *
 * @param[in] sset     a pointer to the sync set containing the map operation
 * @param     handle   pmem/tmem handle on which to operate
 * @param[in] addr     the CPU address where to start the sync operation.
 *                     The address might be rounded down to a cache line boundary.
 * @param size         the number of bytes to be synced
 * Might be rounded up to a cache line boundary.
 */
static INLINE void base_syncset_to_gpu(base_syncset *sset,
                                       const base_mem_handle handle,
                                       const void *addr,
                                       const size_t size)
{
	CDBG_ASSERT(sset);
	sset->basep_sset.mem_handle = handle;
	sset->basep_sset.size       = size;
	sset->basep_sset.user_addr  = (uintptr_t)addr;
	sset->basep_sset.type       = BASE_SYNCSET_OP_MSYNC;
}

/**
 * @brief Deferred sync of a mapped region for CPU usage
 *
 * Deferred equivalent to ::base_sync_to_cpu_now. Instead of being
 * directly executed, the synchronization request is stored in the
 * provided ::base_syncset, and executed when the job referencing
 * this sync set will be completed.
 *
 * @param[in]  sset    a pointer to the sync set containing the map operation
 * @param      handle  pmem/tmem handle on which to operate
 * @param[out] addr    The CPU address where to start the sync operation.
 *                     The address might be rounded down to a cache line
 *                     boundary.
 * @param size         The number of bytes to be synced.
 *                     Might be rounded up to a cache line boundary.
 */
static INLINE void base_syncset_to_cpu(base_syncset *sset,
                                       const base_mem_handle handle,
                                       const void *addr,
                                       const size_t size)
{
	CDBG_ASSERT(sset);
	sset->basep_sset.mem_handle = handle;
	sset->basep_sset.size       = size;
	sset->basep_sset.user_addr  = (uintptr_t)addr;
	sset->basep_sset.type       = BASE_SYNCSET_OP_CSYNC;
}

/**
 * @brief Return the type of an initialised syncset
 *
 * Returns the type of a syncset that has previously been initialised
 * by calling @ref base_syncset_to_gpu or @ref base_syncset_to_cpu.
 *
 * @param[in] sset  The syncset to return the type of
 * @return          The syncset type (either @ref BASE_SYNCSET_OP_MSYNC
 *                  or @ref BASE_SYNCSET_OP_CSYNC)
 */
static INLINE u8 base_syncset_get_type(base_syncset *sset)
{
	return sset->basep_sset.type;
}

/**
 * @brief Return the size of an initialised syncset
 *
 * Returns the size of a syncset that has previously been initialised
 * by calling @ref base_syncset_to_gpu or @ref base_syncset_to_cpu.
 *
 * @param[in] sset  The syncset to return the type of
 * @return          The syncset size in bytes (note that the actual
 *                  sync might be rounded up to a cache line boundary)
 */
static INLINE u32 base_syncset_get_size(base_syncset *sset)
{
	return sset->basep_sset.size;
}

/**
 * @brief Return the memory handle of an initialised syncset
 *
 * Returns the memory handle of a syncset that has previously been initialised
 * by calling @ref base_syncset_to_gpu or @ref base_syncset_to_cpu.
 *
 * @param[in] sset  The syncset to return the type of
 * @return          The memory handle that the syncst was initialised with
 */
static INLINE base_mem_handle base_syncset_get_handle(base_syncset *sset)
{
	return sset->basep_sset.mem_handle;
}

/**
 * @brief Return the CPU address of an initialised syncset
 *
 * Returns the CPU address of a syncset that has previously been initialised
 * by calling @ref base_syncset_to_gpu or @ref base_syncset_to_cpu.
 *
 * @param[in] sset  The syncset to return the type of
 * @return          The CPU address where the sync operation should start
 *                  (Note that the actual sync may be rounded down to a
 *                  cache line boundary)
 */
static INLINE void *base_syncset_get_address(base_syncset *sset)
{
	return (void*)(uintptr_t)sset->basep_sset.user_addr;
}

/**
 * @brief An element of a syncset list to be passed to Base.
 */
typedef struct base_syncset_list_entry
{
	struct base_syncset_list_entry  *next;    /**< Next syncset in the list */
	base_syncset                    syncset;  /**< A basic memory operation, see ::base_syncset */
} base_syncset_list_entry;

/**
 * @brief A syncset list to be passed to Base.
 *
 * This structure defines a list of syncsets passed to Base, usually
 * together with a job-chain descriptor. Once the list has been
 * consumed by Base, the @a dtor destructor is called with the
 * pointer to the list itself as parameter.

 */
typedef struct base_syncset_list
{
	struct base_syncset_list *next;           /**< Next list of syncsets */
	base_syncset_list_entry  *list;           /**< Head of the syncset list */
	u32                      nr_syncsets;     /**< Number of syncset in the list */
	void                     (*dtor)(struct base_syncset_list *); /**< Destructor function */
} base_syncset_list;

/**
 * @brief Immediately execute lists of syncsets
 *
 * Perform  ::base_sync_to_cpu_now or ::base_sync_to_gpu_now  on lists
 * of syncsets.
 *
 * The destructor function associated with each base_syncset_list is called 
 * once the sync operations for that list are complete. The memory associated with 
 * the base_syncset_list object may then be freed from the destructor.
 *
 * It is a programming error to pass an invalid pointer (including NULL) through the ctx parameter.
 *
 * @param[in] ctx  A pointer to the base context associated with the syncsets
 * @param[in] list The lists of syncsets to be executed
 * @post the destructor function for each base_syncset_list has been called
 */
void base_syncset_sync_list_now(base_context *ctx, base_syncset_list *list);

/** @} end group base_user_api_memory_defered */
/** @} end group base_user_api_memory */
/** @} end group base_user_api */
/** @} end group base_api */
#if (1 == MALI_BASE_TRACK_MEMLEAK)
#include <base/mali_base_memory_wrapper.h>
#endif
#endif /* __MALI_BASE_MEMORY_H__ */
