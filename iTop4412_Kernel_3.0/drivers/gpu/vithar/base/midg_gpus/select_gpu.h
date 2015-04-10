/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


#ifndef __MIDG_GPUS__SELECT_GPU_H__
#define __MIDG_GPUS__SELECT_GPU_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


#if   CONFIG_GPU_CORE_TYPE == MIDG_GPU_ID_MALI_T600
#include <base/midg_gpus/mali_t600.h>
#else
#error You must choose a Midgard Family Product for CONFIG_GPU_CORE_TYPE in your platform`s plat_config.h.
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MIDG_GPUS__SELECT_GPU_H__ */
