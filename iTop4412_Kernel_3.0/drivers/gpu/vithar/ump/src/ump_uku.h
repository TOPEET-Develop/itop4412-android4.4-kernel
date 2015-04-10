/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2008-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _UMP_UKU_H_
#define _UMP_UKU_H

#include <uk/mali_uk.h>
#include <uk/mali_uku.h>
#include <ump/ump.h>
#include <malisw/mali_malisw.h>

/*
 * The order and size of the members of these have been chosen so the structures look the same in 32-bit and 64-bit builds.
 * If any changes are done build the ump_struct_size_checker test for 32-bit and 64-bit targets. Both must compile successfully to commit.
 */

/** 32/64-bit neutral way to represent pointers */
typedef union ump_pointer
{
	void * value; /**< client should store their pointers here */
	u32 compat_value; /**< 64-bit kernels should fetch value here when handling 32-bit clients */
	u64 sizer; /**< Force 64-bit storage for all clients regardless */
} ump_pointer;

/**
 * UMP allocation request.
 * Used when performing ump_allocate
 */
typedef struct ump_uk_allocate
{
	uk_header  header; /**< [in,out] Generic uk header */
	u64 size; /**< [in] Size in bytes to allocate */
	ump_secure_id secure_id; /**< [out] Secure ID of allocation on success */
	ump_alloc_flags alloc_flags; /**< [in] Flags to use when allocating */
} ump_uk_allocate;

/**
 * UMP resize request.
 * Used then performing ump_resize
 */
typedef struct ump_uk_resize
{
	uk_header header; /**< [in,out] Generic uk header */
	s64 size_diff; /**< [in] Resize delta. Negative to shrink, positive to expand */
	u64 new_size; /**< [out] Size after resize */
	ump_secure_id secure_id; /**< [in] ID of allocation to resize */
	u32 padding; /* don't remove */
} ump_uk_resize;

/**
 * UMP size query request.
 * Used when performing ump_size_get
 */
typedef struct ump_uk_sizequery
{
	uk_header header; /**< [in,out] Generic uk header */
	u64 size; /**< [out] Size of allocation */
	ump_secure_id secure_id; /**< [in] ID of allocation to query the size of */
	u32 padding; /* don't remove */
} ump_uk_sizequery;

/**
 * UMP cache synchronization request.
 * Used when performing ump_cpu_msync_now
 */
typedef struct ump_uk_msync
{
	uk_header header; /**< [in,out] Generic uk header */
	ump_pointer mapped_ptr; /**< [in] CPU VA to perform cache operation on */
	ump_secure_id secure_id; /**< [in] ID of allocation to perform cache operation on */
	ump_cpu_msync_op cache_operation; /**< [in] Cache operation to perform */
	u64 size; /**< [in] Size in bytes of the range to synchronize */
} ump_uk_msync;

/**
 * UMP memory map request.
 * Used when performing ump_map
 */
typedef struct ump_uk_map
{
	uk_header header; /**< [in,out] Generic uk header */
	u64 offset; /**< [in] Offset (in bytes) from the start of the allocation */
	ump_pointer mapped_ptr; /**< [out] Pointer to mapping created */
	u64 size; /**< [in] Size in bytes to map */
	ump_secure_id secure_id; /**< ID of allocation to map */
	u32 padding; /* don't remove */
} ump_uk_map;

/**
 * UMP memory unmap request.
 * Used when performing ump_unmap
 */
typedef struct ump_uk_unmap
{
	uk_header header; /**< [in,out] Generic uk header */
	ump_pointer mapped_ptr; /**< [in] Pointer to apping to unmap */
	ump_secure_id secure_id; /**< [in] ID of the allocation to unmap */
	u32 padding; /* don't remove */
} ump_uk_unmap;

/**
 * UMP memory retain request.
 * Used when performing ump_retain
 */
typedef struct ump_uk_retain
{
	uk_header header; /**< [in,out] Generic uk header */
	ump_secure_id secure_id; /**< [in] ID of allocation to retain a reference to */
	u32 padding; /* don't remove */
} ump_uk_retain;

/**
 * UMP memory release request.
 * Used when performing ump_release
 */
typedef struct ump_uk_release
{
	uk_header header; /**< [in,out] Generic uk header */
	ump_secure_id secure_id; /**< [in] ID of allocation to release a reference to */
	u32 padding; /* don't remove */
} ump_uk_release;

/**
 * ump_context type. Returned from ump_open and operated on in all functions taking a context argument (all others) */
typedef uku_context ump_context;

/**
 * ID codes of the UK functions
 */
typedef enum ump_uk_function_id
{
	/* handle by the core */
	UMP_FUNC_ALLOCATE = (UK_FUNC_ID + 0),
	UMP_FUNC_RESIZE,
	UMP_FUNC_SIZEQUERY,
	UMP_FUNC_MSYNC,
	UMP_FUNC_RETAIN,
	UMP_FUNC_RELEASE,
	/* OS specific, IDs reserved for those OSes which will use uk to perform them */
	UMP_FUNC_MAP,
	UMP_FUNC_UNMAP
} ump_uk_function_id;

#endif /* _UMP_UKU_H_ */
