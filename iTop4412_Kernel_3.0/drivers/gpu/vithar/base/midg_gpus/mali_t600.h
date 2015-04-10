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
 * @file mali_t600.h
 * Platform Config file common to every Mali-T600 Platform
 */

#ifndef _MIDG_GPUS__MALI_T600_H_
#define _MIDG_GPUS__MALI_T600_H_


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/** @addtogroup base_api
 * @{ */

/**
 * @addtogroup base_plat_config_gpuprops
 * @{
 */

#define CONFIG_GPU_VA_BITS            48
#define CONFIG_GPU_PA_BITS            40

/**
 * The value to report for GL_SAMPLES - MultiSample Anti-Aliasing samples per
 * pixel.
 *
 * No more than @ref MIDG_MAX_SAMPLES_PER_PIXEL
 */
#define CONFIG_GPU_MAX_SAMPLES_PER_PIXEL  4

/**
 * Point size Maximum - this is the maximum value supported in the HW.
 */
#define CONFIG_GPU_MAX_POINT_SIZE_F 4095.9375f

/**
 * Point size Minimum - the smallest point size supported in the HW
 */
#define CONFIG_GPU_MIN_POINT_SIZE_F 0.0625f

/**
 * @see MIDG_MAX_PRIMARY_ATTRIBUTES for Architecture maximum
 */
#define CONFIG_GPU_MAX_PRIMARY_ATTRIBUTES  ( 1U << 9 )

/**
 * @see MIDG_MAX_SECONDARY_ATTRIBUTES for Architecture maximum
 */
#define CONFIG_GPU_MAX_SECONDARY_ATTRIBUTES ( 1U << 9 )

/**
 * The maximum number of work items supported in a work group for this HW.
 *
 * @see MIDG_MAX_COMPUTE_JOB_WORKGROUP_SIZE for Architecture maximum
 */
#define CONFIG_GPU_MAX_COMPUTE_JOB_WORKGROUP_SIZE 256

/**
 * Number of working registers for a T600 core
 * MIDBASE-556: For future cores in the family this may change
 */
#define CONFIG_GPU_WORKING_REGISTERS  1024

/* This is one of the Mali-T600 family of GPUs */
#define CONFIG_GPU_VERSION_STRING     "Mali-T600"

/** @} end group base_user_api_config_gpuprops */


/** @} end group base_api */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MIDG_GPUS__MALI_T600_H_ */
