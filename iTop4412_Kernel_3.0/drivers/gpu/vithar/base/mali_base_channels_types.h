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
 * @file mali_base_channels_types.h
 * Types necessary to declare before private types are declared
 */

#ifndef _BASE_CHANNELS_TYPES_H_
#define _BASE_CHANNELS_TYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @addtogroup base_api
 * @{
 */

/**
 * @addtogroup base_user_api
 * @{
 */

/**
 * @addtogroup base_user_api_channels
 * @{
 */

/**
 * @brief Channel Types
 *
 * Refer to @ref page_base_channels_phys_dest for more information.
 *
 * The enum values are explicitly specified, because the numeric value of the
 * channel type is used to determine locking order - see @ref
 * base_channel_lock().
 */
typedef enum
{
	/** The channel for Information-severity Debug Messages: */
	BASE_CHANNEL_INFO = 0,

	/** The channel for Warning-severity Debug Messages. */
	BASE_CHANNEL_WARN = 1,

	/** The channel for Error-severity Debug Messages. */
	BASE_CHANNEL_ERROR = 2,

	/**
	 * The channel for 'Debug Spew', as defined by the Common Debug Module. The
	 * size of the message buffer is much larger than Info, Warn and Error
	 * channels.
	 */
	BASE_CHANNEL_SPEW = 3,

	/* Add more channel types here */

	/** The number of channels supported. This must be the last member of the
	 * enum */
	BASE_CHANNEL_COUNT
} base_channel_type;


/** @} end group base_user_api_channels */
/** @} end group base_user_api */
/** @} end group base_api */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_CHANNELS_TYPES_H_ */
