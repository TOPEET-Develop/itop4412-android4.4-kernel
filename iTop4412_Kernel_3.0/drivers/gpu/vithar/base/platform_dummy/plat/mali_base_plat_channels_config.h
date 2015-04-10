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
 * @file mali_base_plat_channels_config.h
 *
 * Platform-specific configuration for Base Channels
 * Also see base/platform_&lt;platform_name&gt;/mali_base_plat_channels_config.c
 */


#ifndef _BASE_PLAT_CHANNELS_CONFIG_H_
#define _BASE_PLAT_CHANNELS_CONFIG_H_


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Default message size for info, warning and error channels
 *
 * This value is not part of the Config API, and is just a convenience for
 * this platform's setting of CONFIG_CHANNEL_CONVERSION_BUFFER_SIZE and
 * this platform's implementation of mali_base_plat_channels_config.c. It
 * might not be needed on other platforms.
 */
#define CONFIG_CHANNEL_DEFAULT_MSG_SIZE 512

/*
 * This platform uses a file for its platform-specific destination. This value
 * determines the file name.
 *
 * This value is not part of the Config API, and might not be needed on other
 * platforms.
 */
#define CONFIG_CHANNEL_PLATSPECIFIC_FILE "mali_this_file_is_for_testing_purposes_only.out"

/**
 * @brief Size of the BDBG messaging system print buffer.
 *
 * It is most likely (but not guarenteed) that a buffer of up to this size is
 * likely to be passed to base_channel_emergency_message().
 */
#define CONFIG_BDBGP_PRINT_BUFFER_SIZE CONFIG_CHANNEL_DEFAULT_MSG_SIZE

/**
 * @brief Size of the Newline conversion buffer used.
 *
 * Messages smaller than the size of this buffer will be truncated. The
 * truncation allows space for the NULL termination character in the buffer.
 *
 * The buffer is allocated on the stack, and its size is in bytes.
 *
 * This size should be related to the configured max_size_of_message for 
 * channels in mali_base_plat_channels_config.c that have large_conversion_size
 * set to zero.
 *
 * The following setting allows for a newline character in 1 in every 10
 * characters.
 */
#define CONFIG_CHANNEL_CONVERSION_BUFFER_SIZE \
	((CONFIG_CHANNEL_DEFAULT_MSG_SIZE) + ((CONFIG_CHANNEL_DEFAULT_MSG_SIZE)/10))

/**
 * @brief Disable redundant code paths in Portable Debug Channels.
 *
 * This improves efficiency, but at the expense of reduced coverage of code that
 * is used on other platforms.
 */
#define CONFIG_CHANNEL_DISABLE_REDUNDANT_PATHS 0

/**
 * @brief Enables lock checking on the Emptying Ringbuffers
 *
 * The emptying ringbuffers behave differently to CUTILS::Ringbuffers, because
 * they wait - and so could potentially deadlock.
 *
 * Deadlock checking on ringbuffer can be enabled to check for this, by taking
 * a lock around the ringbuffer, and enabling Lock order checking in
 * OSU. However, it removes any performance gains given by the ringbuffers, and
 * so should only be used to check for locking problems.
 *
 * Disabled when 0, enabled when non-zero
 */
#define CONFIG_EMPTYING_RINGBUF_SLOW_LOCK_CHECKING 1

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_PLAT_CHANNELS_CONFIG_H_ */
