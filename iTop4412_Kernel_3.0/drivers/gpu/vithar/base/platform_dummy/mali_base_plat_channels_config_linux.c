/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


/*
 * Platform configuration structures for this platform are placed within this
 * file.
 */

#include <base/src/mali_base_channels_utils.h>

/* Spew channel message size - enough for a page of 80x25 text */
#define BASEP_SPEW_CHANNEL_MSG_SIZE 2048
/* Spew channel conversion buffer size - allows 1 newline every 10 characters */
#define BASEP_SPEW_CHANNEL_CONV_BUFFER  ((BASEP_SPEW_CHANNEL_MSG_SIZE) + ((BASEP_SPEW_CHANNEL_MSG_SIZE)/10))


CONST basep_channel_type_config basep_plat_channel_config[BASE_CHANNEL_COUNT] =
{
	/* BASE_CHANNEL_INFO configuration */
	{
		/* messages_to_keep_log2; 2^4 == 16 */
		4,

		/* 
		 * max_size_of_message; On this platform, it is the same as the Newline
		 * conversion buffer size
		 */
		CONFIG_CHANNEL_DEFAULT_MSG_SIZE,
		
		/*
		 * large_conversion_size; Not required for this channel, due to
		 * max_size_of_message being same size as the Newline conversion buffer
		 * size
		 */
		0,
		
		/* 
		 * destinations_enabled; Stdout, file.
		 *
		 * NOTE: Platform specific destination enabled for testing purposes.
		 */
		BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_STDOUT )
		| BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_FILE )
		| BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC ),

		/* path; */
		"mali.out"
	},

	/* BASE_CHANNEL_WARN configuration */
	{
		/* messages_to_keep_log2; 2^4 == 16 */
		4,

		/* 
		 * max_size_of_message; On this platform, it is the same as the Newline
		 * conversion buffer size
		 */
		CONFIG_CHANNEL_DEFAULT_MSG_SIZE,
		
		/*
		 * large_conversion_size; Not required for this channel, due to
		 * max_size_of_message being same size as the Newline conversion buffer
		 * size
		 */
		0,
		
		/* 
		 * destinations_enabled; Stderr, file.
		 *
		 * NOTE: Platform specific destination enabled for testing purposes.
		 */
		BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_STDERR )
		| BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_FILE )
		| BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC ),

		/* path; */
		"mali.warn"
	},

	/* BASE_CHANNEL_ERROR configuration */
	{
		/* messages_to_keep_log2; 2^4 == 16 */
		4,

		/* 
		 * max_size_of_message; On this platform, it is the same as the Newline
		 * conversion buffer size
		 */
		CONFIG_CHANNEL_DEFAULT_MSG_SIZE,
		
		/*
		 * large_conversion_size; Not required for this channel, due to
		 * max_size_of_message being same size as the Newline conversion buffer
		 * size
		 */
		0,
		
		/* 
		 * destinations_enabled; Stderr, file.
		 *
		 * NOTE: Platform specific destination enabled for testing purposes.
		 */
		BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_STDERR )
		| BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_FILE )
		| BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC ),

		/* path; */
		"mali.err"
	},

	/* BASE_CHANNEL_SPEW configuration */
	{
		/* messages_to_keep_log2; 2^0 == 1 */
		0,

		/* 
		 * max_size_of_message; Large enough for spew messages. Assuming 2048
		 * bytes (large enough for 80x25 terminal), with 10% allowance
		 */
		BASEP_SPEW_CHANNEL_MSG_SIZE,
		
		/*
		 * large_conversion_size; Not required for this channel, due to
		 * max_size_of_message being same size as the Newline conversion buffer
		 * size
		 */
		BASEP_SPEW_CHANNEL_CONV_BUFFER,
		
		/* 
		 * destinations_enabled; Stdout, file.
		 */
		BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_STDOUT )
		| BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_FILE ),

		/* path; */
		"mali.spew"
	},

};


CONST basep_channel_destination_config basep_plat_channel_destination_config[BASEP_CHANNEL_DESTINATION_COUNT] =
{
	/* BASEP_CHANNEL_DESTINATION_STDOUT */
	{
		/* stdout needs a mutex, and the same stdout is shared by channels */
		BASEP_CHANNEL_DESTINATION_FLAG_MUTEX_NEEDED | BASEP_CHANNEL_DESTINATION_FLAG_SHARED
	},
	
	/* BASEP_CHANNEL_DESTINATION_STDERR */
	{
		/* stderr needs a mutex, and the same stderr is shared by channels */
		BASEP_CHANNEL_DESTINATION_FLAG_MUTEX_NEEDED | BASEP_CHANNEL_DESTINATION_FLAG_SHARED
	},

	/* BASEP_CHANNEL_DESTINATION_FILE */
	{
		/* 
		 * files require a mutex, but each file is *not* shared by channels
		 */
		BASEP_CHANNEL_DESTINATION_FLAG_MUTEX_NEEDED
	},

	/* BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC */
	{
		/*
		 * The 'artificial' platform specific destination on this platform needs a mutex.
		 * On this platform, it is shared by all channels. 
		 *
		 * Newline conversion to CRLF is used for testing purposes.
		 */
		BASEP_CHANNEL_DESTINATION_FLAG_NEWLINE_CRLF
		| BASEP_CHANNEL_DESTINATION_FLAG_MUTEX_NEEDED
		| BASEP_CHANNEL_DESTINATION_FLAG_SHARED
	}
};
