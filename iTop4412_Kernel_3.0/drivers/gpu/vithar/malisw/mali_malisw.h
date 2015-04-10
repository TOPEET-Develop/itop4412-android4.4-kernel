/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALISW_H_
#define _MALISW_H_

#define MALI_MODULE_MALISW_MAJOR 2
#define MALI_MODULE_MALISW_MINOR 4

/**
 * @file mali_malisw.h
 * Driver-wide include for common macros and types.
 */

/**
 * @defgroup malisw Mali software definitions and types
 * @{
 */

#include <stddef.h>

#include "mali_stdtypes.h"
#include "mali_version_macros.h"

/** @brief Gets the container object when given a pointer to a member of an object. */
#define CONTAINER_OF(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type,member)))

/** @brief Gets the number of elements of type s in a fixed length array of s */
#define NELEMS(s)       (sizeof(s)/sizeof((s)[0]))

/**
 * @brief The lesser of two values.
 * May evaluate its arguments more than once.
 * @see CSTD_MIN
 */
#define MIN(x,y) CSTD_MIN(x,y)

/**
 * @brief The greater of two values.
 * May evaluate its arguments more than once.
 * @see CSTD_MAX
 */
#define MAX(x,y) CSTD_MAX(x,y)

/**
 * @brief Clamp value x to within min and max inclusive
 * May evaluate its arguments more than once.
 * @see CSTD_CLAMP
 */
#define CLAMP( x, min, max ) CSTD_CLAMP( x, min, max )

/**
 * @brief Convert a pointer into a u64 for storing in a data structure.
 * This is commonly used when pairing a 32-bit CPU with a 64-bit peripheral,
 * such as a Midgard GPU. C's type promotion is complex and a straight cast
 * does not work reliably as pointers are often considered as signed.
 */
#define PTR_TO_U64( x ) CSTD_PTR_TO_U64( x )

/**
 * @name Mali library linkage specifiers 
 * These directly map to the cstd versions described in detail here: @ref arm_cstd_linkage_specifiers
 * @{
 */
#define MALI_IMPORT CSTD_LINK_IMPORT
#define MALI_EXPORT CSTD_LINK_EXPORT
#define MALI_IMPL   CSTD_LINK_IMPL 
#define MALI_LOCAL  CSTD_LINK_LOCAL
/** @} */

/**
 * Flag a cast as a reinterpretation, usually of a pointer type.
 * @see CSTD_REINTERPRET_CAST
 */
#define REINTERPRET_CAST(type) CSTD_REINTERPRET_CAST(type)

/**
 * Flag a cast as casting away const, usually of a pointer type.
 * @see CSTD_CONST_CAST
 */
#define CONST_CAST(type) (type) CSTD_CONST_CAST(type)

/**
 * Flag a cast as a (potentially complex) value conversion, usually of a numerical type.
 * @see CSTD_STATIC_CAST
 */
#define STATIC_CAST(type) (type) CSTD_STATIC_CAST(type)


/** @} */

#endif /* _MALISW_H_ */
