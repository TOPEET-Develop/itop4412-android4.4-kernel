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
 * @file mali_base_compatibility.h
 * File for resolving compatibility issues between base and other modules
 */

#ifndef _BASE_COMPATIBILITY_H_
#define _BASE_COMPATIBILITY_H_

/*
 * Resolve incompatibility with early versions of MIDG module
 */
#if (0 == MALI_MODULE_MIDG_MAJOR) && (0 == MALI_MODULE_MIDG_MINOR)

#define MIDG_PRODUCT_MALI_T600 26966
#define MIDG_GPU_ID_MALI_T600 0x6956

#endif /* (0 == MALI_MODULE_MIDG_MAJOR) && (0 == MALI_MODULE_MIDG_MINOR) */

/* Other incompatibilities go here */

#endif /* _BASE_COMPATIBILITY_H_ */
