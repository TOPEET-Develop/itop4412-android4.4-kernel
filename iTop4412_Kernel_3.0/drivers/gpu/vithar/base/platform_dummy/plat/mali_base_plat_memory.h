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
 * @file mali_base_plat_memory.h
 *
 * Platform-specific configuration for Base memory
 */


#ifndef _BASE_PLAT_MEMORY_H_
#define _BASE_PLAT_MEMORY_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @addtogroup base_user_api_memory User-side Base Memory APIs
 * @{
 */

/**
 * @brief Generic memory handle
 *
 * ::base_mem_handle is an abstract type to designate a memory region.
 * It has no direct allocator. Instead, it is created as part of
 * the pmem/tmem allocation. It is possible to obtain a ::base_mem_handle
 * from the ::base_tmem_to_mem and ::base_pmem_to_mem operators.
 */
typedef mali_addr64 base_mem_handle;

/**
 * @addtogroup base_user_api_memory_pmem User-side Base Permanently Mapped Memory APIs
 * @{
 */

/**
 * @brief Permanently mapped memory handle (pmem)
 *
 * A pmem handle tracks a memory region that is permanently mapped
 * in both the CPU and GPU virtual address spaces. It is obtained by
 * allocating such a memory region, and is destroyed by releasing the
 * region. CPU and GPU virtual addresses are guaranteed to be the same.
 * As virtual address space can be a scarce resource on some platforms,
 * it is recommended that the total memory allocated through pmem handles
 * is kept as low as possible.
 */
typedef base_mem_handle base_pmem_handle;

/**
 * Platform specific invalid pmem handle
 */
#define BASE_PMEM_INVALID_HANDLE 0UL

/**
 * @brief Obtain a generic memory handle from a pmem handle
 *
 * This function returns a generic memory handle from an existing
 * pmem handle, to be used with memory synchronisation primitives
 * (eg ::base_sync_to_gpu_now, ::base_syncset_to_gpu).
 *
 * @param handle a valid base_pmem_handle
 * @return the generic memory handle associated to the base_pmem_handle
 */
static INLINE base_mem_handle base_pmem_to_mem(base_pmem_handle handle)
{
	return (base_mem_handle)handle;
}
/** @} end group base_user_api_memory_pmem */

/**
 * @addtogroup base_user_api_memory_tmem User-side Base Transient Mapped Memory APIs
 * @{
 */

/**
 * @brief Transient mapped memory handle (tmem)
 *
 * A tmem handle tracks a memory region that is permanently mapped
 * on the GPU side, but only rarely/partially mapped on the CPU side.
 * It is obtained by allocating such a memory region, and is destroyed
 * by releasing the region.
 * The nature of transient mapped memory is such that CPU and GPU do not
 * have the same view of the address at which the region is mapped.
 * Furthermore, a tmem GPU virtual address is @a not a CPU pointer. 
 */
typedef base_mem_handle base_tmem_handle;

/**
 * Platform specific invalid tmem handle
 */
#define BASE_TMEM_INVALID_HANDLE 0UL

/**
 * @brief Obtain a generic memory handle from a tmem handle
 *
 * This function returns a generic memory handle from an existing
 * tmem handle, to be used with memory synchronisation primitives
 * (eg ::base_sync_to_gpu_now, ::base_syncset_to_gpu).
 *
 * @param handle a valid base_tmem_handle
 * @return the generic memory handle associated to the base_tmem_handle
 */
static INLINE base_mem_handle base_tmem_to_mem(base_tmem_handle handle)
{
	return (base_mem_handle)handle;
}
/** @} end group base_user_api_memory_tmem */

/** @} end group base_user_api_memory */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_PLAT_MEMORY_H_ */
