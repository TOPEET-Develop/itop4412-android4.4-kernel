/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include <base/src/mali_base_channels_utils.h>

/*
 * The following setting allows for a newline character in 1 in every 10
 * characters.
 */
#define EMERGENCY_CHANNEL_CONV_BUF_SIZE ( (CONFIG_BDBGP_PRINT_BUFFER_SIZE) + ((CONFIG_BDBGP_PRINT_BUFFER_SIZE)/10) )

/*
 * Protected functions
 */

/*
 * Implementation of a 'dummy' platform-specific destination, for testing
 * purposes only. Later on, this will be removed.
 *
 * It requires BASEP_CHANNEL_DESTINATION_SHARED set, because we only support
 * one actual destination - 'type' is ignored.
 */

mali_error basep_channel_platform_destination_open(
	basep_channel_platform_destination * const plat_channel,
	base_channel_type type )
{
	BDBG_ASSERT_POINTER( plat_channel );
	BDBG_ASSERT_RANGE( type, 0, BASE_CHANNEL_COUNT-1 );

	/* This platform ignores the channel type */
	UNUSED( type );

	plat_channel->file_ptr = fopen( CONFIG_CHANNEL_PLATSPECIFIC_FILE, "w" );

	if ( NULL == plat_channel->file_ptr )
	{
		return MALI_ERROR_FUNCTION_FAILED;
	}

	return MALI_ERROR_NONE;
}

void basep_channel_platform_destination_close(
	basep_channel_platform_destination *plat_channel )
{
	int err;
	BDBG_ASSERT_POINTER( plat_channel );
	
	err = fclose( plat_channel->file_ptr );
	
	if ( 0 != err )
	{
		/* Nothing we can do, but warn about it */
		BDBG_PRINT_WARN( CDBG_BASE,
						 "fclose() failed; returned %d on " CONFIG_CHANNEL_PLATSPECIFIC_FILE ". Continuing regardless.",
						 err );
	}
}

mali_error basep_channel_platform_destination_write( 
	basep_channel_platform_destination *plat_channel,
	const char *msg,
	u32 size )
{
	int err1;
	int err2;

	BDBG_ASSERT_POINTER( plat_channel );
	BDBG_ASSERT( 0 != size && NULL != msg && 0 == msg[size-1] );
	
	UNUSED( size );
	
	/* This platform uses NULL-terminated strings */
	err1 = fputs( msg, plat_channel->file_ptr );

	err2 = fflush( plat_channel->file_ptr );

	/* fputs() return a non-negative number on success, or EOF on error.
	 * fflush returns 0 on success, EOF on error*/
	if ( err1 < 0 || 0 != err2 )
	{
		return MALI_ERROR_FUNCTION_FAILED;
	}

	return MALI_ERROR_NONE;
}

/*
 * Public functions
 */

/*
 * The emergency channel for this platform is stderr
 * 
 * No DDK asserts can be made in this function or any that it calls
 */
void base_channel_emergency_message( CONST char * message, size_t buffer_size  )
{
	char *final_msg;
#if 0 == CONFIG_CHANNEL_DISABLE_REDUNDANT_PATHS
	char conversion_buffer[EMERGENCY_CHANNEL_CONV_BUF_SIZE];
	basep_channel_conversion_args conv_args;
	u32 bytes_written;
#endif
	
	/* For testing purposes, we do the newline conversion */
#if 0 == CONFIG_CHANNELS_DISABLE_REDUNDANT_PATHS
	conv_args.dest = &conversion_buffer[0];
	conv_args.dest_size = sizeof(conversion_buffer);
	conv_args.src = message;
	conv_args.src_size = (u32)buffer_size;
	/* Messages that are too long get truncated to zero */
	if ( conv_args.src_size < buffer_size )
	{
		conv_args.src_size = 0;
	}
	conv_args.flags = 0; /* No newline conversion */

	bytes_written = basep_channel_convert_newlines( &conv_args );

	UNUSED( bytes_written );

	final_msg = &conversion_buffer[0];
#else
	final_msg = message;
	UNUSED( buffer_size );
#endif

	/* Nothing can be done if either of these fail, because we are the 'last
	 * resort' debug messaging path */
	fputs( final_msg, stderr );
	fflush( stderr );
}
