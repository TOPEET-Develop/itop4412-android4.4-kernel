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
 * @file mali_base_channels_priv.h
 * 
 * Private definitions required to compile the public interface in
 * mali_base_channels.h.
 *
 * @note This file is included when the public header file mali_base_channels.h
 * is included. The definitions should be restricted to \b only those required
 * for compiling the public interface.
 */


#ifndef _BASE_CHANNELS_PRIV_H_
#define _BASE_CHANNELS_PRIV_H_

#include <plat/mali_base_plat_channels.h>
#include <cutils/ring_buffer/mali_cutils_ring_buffer.h>
#include <stdlib/mali_stdlib.h>
#include <osu/mali_osu.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Definitions for mali_base_channels_utils.c
 */

/*
 * Declaring as struct rather than defining typedef, due to need for forward
 * declaring it in mali_base_channels.h
 */
typedef struct basep_channels_emptying_ringbuffer
{
	cutils_ring_buffer ringbuf;
#if 0 != CONFIG_EMPTYING_RINGBUF_SLOW_LOCK_CHECKING
	osu_mutex lock_for_checking;
#endif
} basep_channels_emptying_ringbuffer;


/*
 * basep_channel_platform_destination is the structure representing a
 * platform-specific destination. The implementation is platform-specific, and
 * must be defined by each platform, even if it is a 'dummy' implementation.
 */
typedef struct basep_channel_platform_destination basep_channel_platform_destination;



/*
 * Definitions for mali_base_channels.c
 */

typedef enum
{
	BASEP_CHANNEL_DESTINATION_STDOUT = 0,
	BASEP_CHANNEL_DESTINATION_STDERR,
	BASEP_CHANNEL_DESTINATION_FILE,
	BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC,

	/* This must be the last in the enum. Up to 32 supported. */
	BASEP_CHANNEL_DESTINATION_COUNT
} basep_channel_destination;

typedef struct basep_destination
{
	union
	{
		struct
		{
			/* Mixing of STDLIB_<xyz>_STREAM, with stdlib_fopen() requires both
			 * a structure and a pointer */
			stdlib_file *stream_ptr;
			stdlib_file stream;
		} s;
		basep_channel_platform_destination plat_dest;
	} u;
	osu_mutex mutex;
} basep_destination;

/*
 * Declaring as struct rather than defining typedef, due to need for forward
 * declaring it in mali_base_channels.h
 */
typedef struct basep_channel_destinations_info
{
	u32 dests_enabled;
	basep_destination dests[BASEP_CHANNEL_DESTINATION_COUNT];

	/* Path for BASEP_CHANNEL_DESTINATION_FILE */
	char *file_dest_path;

	/* Type for BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC */
	base_channel_type channel_type;
	
	/* Other destination-specific data can be added here */
} basep_channel_destinations_info;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_CHANNELS_PRIV_H_ */
