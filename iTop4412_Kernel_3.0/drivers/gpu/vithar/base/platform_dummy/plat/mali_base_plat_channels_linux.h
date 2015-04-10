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
 * @file mali_base_plat_channels_linux.h
 *
 * Linux-specific configuration for Base Channels
 */


#ifndef _BASE_PLAT_CHANNELS_LINUX_H_
#define _BASE_PLAT_CHANNELS_LINUX_H_

#include "mali_base_plat_channels_config.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * Platform specific channel structure
 *
 * This platform has a 'dummy' platform-specific destination, which is a file.
 * This will be removed later.
 */
struct basep_channel_platform_destination
{
	FILE *file_ptr;
};


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_PLAT_CHANNELS_LINUX_H_ */
