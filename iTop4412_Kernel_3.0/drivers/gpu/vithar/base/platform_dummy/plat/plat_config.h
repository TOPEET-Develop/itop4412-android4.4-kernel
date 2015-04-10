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
 * @file plat_config.h
 * Platform Config file for an Example Mali-T600 Platform
 */

#ifndef __PLAT_CONFIG_H__
#define __PLAT_CONFIG_H__

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

/**
 * Choose one Midgard Family Product.
 *
 * The options (defined in @ref midg_gpuprops_static) are:
 * - MIDG_GPU_ID_MALI_T600
 */
#define CONFIG_GPU_CORE_TYPE MIDG_GPU_ID_MALI_T600

/*
 * @name config_gpu_core_revision Config GPU Core Revision 
 *
 * Choose the Midgard Core Revision, in the form R<major>P<minor>. For example,
 * the following defines a R0P1 GPU revision:
 * - CONFIG_GPU_REVISION_MAJOR 0
 * - CONFIG_GPU_REVISION_MINOR 1
 *
 * @{
 */

/**
 * Choose the Midgard Core Revision, in the form R<major>P<minor>. For example,
 * the following defines a R0P1 GPU revision:
 * - CONFIG_GPU_REVISION_MAJOR 0
 * - CONFIG_GPU_REVISION_MINOR 1
 */
#define CONFIG_GPU_REVISION_MAJOR 0

/** @copydoc CONFIG_GPU_REVISION_MAJOR */
#define CONFIG_GPU_REVISION_MINOR 0
/* @@} */

/** @} end group base_user_api_config_gpuprops */


/** @} end group base_api */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PLAT_CONFIG_H__ */
