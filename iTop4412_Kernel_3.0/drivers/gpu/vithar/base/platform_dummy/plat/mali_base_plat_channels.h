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
 * @file mali_base_plat_channels.h
 *
 * Platform-specific configuration for Base Channels
 */


#ifndef _BASE_PLAT_CHANNELS_H_
#define _BASE_PLAT_CHANNELS_H_

#include <malisw/mali_malisw.h>
#include "mali_base_plat_channels_config.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Select between Android and Linux:
 * NOTE: This is a stopgap until a 'proper' platform layer is produced
 */
#if 0 != CSTD_OS_ANDROID
#include "mali_base_plat_channels_android.h"
#else /* 0 != CSTD_OS_ANDROID */
#include "mali_base_plat_channels_linux.h"
#endif /* 0 != CSTD_OS_ANDROID */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_PLAT_CHANNELS_H_ */
