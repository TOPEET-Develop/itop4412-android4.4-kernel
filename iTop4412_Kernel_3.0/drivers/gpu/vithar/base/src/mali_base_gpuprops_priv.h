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
 * @file mali_base_gpuprops_priv.h
 * Defines the Private/Protected functions available for GPU Property Query
 */


#ifndef _BASE_GPUPROPS_PRIV_H_
#define _BASE_GPUPROPS_PRIV_H_

#include <base/mali_base.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/**
 * @brief Get Number of coherent core groups
 *
 * Use this to calculate how much memory will be needed to store the
 * mali_base_gpu_props information filled by
 * basep_fill_gpu_props. Specifically, you need to know how many
 * mali_base_gpu_coherent_group structures will follow the
 * mali_base_gpu_coherent_group_info embedded structure.
 *
 * @param[in,out] ctx base context to get the core groups from
 * @return            the number of coherent groups
 */
u32 basep_gpu_props_get_num_coherent_groups( base_context *ctx );

/**
 * @brief Fill the base ctx's gpu properties information
 *
 * \a gpu_props must point to storage for a mali_base_gpu_props structure with
 * num_groups of mali_base_gpu_coherent_group structures.
 *
 * @param[out] gpu_props  pointer to storage for the gpu properties
 * @param[in]  props_size the size of the mali_base_gpu_coherent_group structure
 *                        passed into \a gpu_props
 * @param[in,out] ctx     the base context for the gpu properties
 * @return                On success, MALI_ERROR_NONE.
 * @return                On failure, some other mali_error value.
 */
mali_error basep_fill_gpu_props( struct mali_base_gpu_props *const gpu_props,
								 u32 props_size,
								 base_context *ctx ) CHECK_RESULT;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
