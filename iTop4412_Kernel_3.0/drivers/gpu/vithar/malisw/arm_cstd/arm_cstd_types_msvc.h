/*
 * Copyright:
 * ----------------------------------------------------------------------------
 * This confidential and proprietary software may be used only as authorized
 * by a licensing agreement from ARM Limited.
 *       (C) COPYRIGHT 2009-2011 ARM Limited , ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorized copies and
 * copies may only be made to the extent permitted by a licensing agreement
 * from ARM Limited.
 * ----------------------------------------------------------------------------
 */

#ifndef _ARM_CSTD_TYPES_MSVC_H_
#define _ARM_CSTD_TYPES_MSVC_H_

/* ============================================================================
	Includes
============================================================================ */
/* Suppress some of the less common API includes for faster compiles. */
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN 1
#endif

/* Suppress the deprecation warnings for standard C library functions. The MS
 * safe alternatives are non-standard and non-portable. */
#ifndef _CRT_SECURE_NO_DEPRECATE
	#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <windows.h>
#include <stddef.h>
#include <limits.h>

/* ============================================================================
	Type Definitions
============================================================================ */
typedef unsigned char           uint8_t;
typedef signed char             int8_t;
typedef unsigned short          uint16_t;
typedef signed short            int16_t;
typedef unsigned int            uint32_t;
typedef signed int              int32_t;
typedef unsigned __int64        uint64_t;
typedef signed __int64          int64_t;

typedef ptrdiff_t               intptr_t;
typedef size_t                  uintptr_t;
typedef uint32_t                bool_t;

/* The TRUE macro defaults to the correctly value in MSVC windows.h header */
/* The FALSE macro defaults to the correctly value in MSVC windows.h header */

/* ============================================================================
	Keywords
============================================================================ */
/* Doxygen documentation for these is in the RVCT header. */
#define ASM                     __asm

#define INLINE                  __inline

#define FORCE_INLINE            __forceinline

#define NEVER_INLINE            __declspec(noinline)

#define PURE

#define PACKED

/* The UNALIGNED macro defaults to the correct value in MSVC toolchain */

#define RESTRICT                __restrict

#define CHECK_RESULT

#define CSTD_FUNC               __FUNCTION__

#endif /* End (_ARM_CSTD_TYPES_MSVC_H_) */
