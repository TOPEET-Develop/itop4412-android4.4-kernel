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
 * @file mali_base_debug.c
 * Base's equivalent of Debug Messaging, which is copied and
 * renamed from the CDBG module
 */

#include "mali_base_channels_utils.h"

#include <cutils/cstr/mali_cutils_cstr.h>
#include <cdbg/mali_cdbg.h>

#include <stdarg.h>


/* Compile-time assert that CONFIG_BDBGP_PRINT_BUFFER_SIZE is large enough for
 * these messages: */
static INLINE void __compile_time_asserts( void )
{
	CDBG_COMPILE_ASSERT( BDBGP_TRUNCATION_MESSAGE_SIZE <= CONFIG_BDBGP_PRINT_BUFFER_SIZE );
	CDBG_COMPILE_ASSERT( BDBGP_ERROR_MESSAGE_SIZE <= CONFIG_BDBGP_PRINT_BUFFER_SIZE );
}

/*
 * Function prototypes
 */

STATIC void vsnprintf_concat( char *buf, u32 size, s32 *chars_written, const char *format, va_list ap );
STATIC void snprintf_concat( char *buf, u32 size, s32 *chars_written, const char *format, ... );

/*
 * Private Functions
 */
STATIC void vsnprintf_concat( char *buf, u32 size, s32 *chars_written, const char *format, va_list ap )
{
	s32 current_chars_written;

	current_chars_written = *chars_written;

	/* Below cast is allowed, because only happens when
	 * current_chars_written > 0 */
	if ( 0 <= current_chars_written && (u32)current_chars_written < size ) 
	{
		s32 new_chars_written;

		new_chars_written = cutils_cstr_vsnprintf( buf+current_chars_written,
												   size-current_chars_written,
												   format,
												   ap);

		if ( new_chars_written >= 0 )
		{
			*chars_written += new_chars_written;
		}
		else
		{
			/* error case */
			*chars_written = new_chars_written;
		}
	}	
}

STATIC void snprintf_concat( char *buf, u32 size, s32 *chars_written, const char *format, ... )
{
	va_list ap;

	va_start(ap, format);
	vsnprintf_concat( buf, size, chars_written, format, ap );
	va_end(ap);
}
/*
 * Public functions
 */

void bdbgp_print_to_info_channel(const char* func, const char* msg, ...)
{
	va_list args;
	char buf[CONFIG_BDBGP_PRINT_BUFFER_SIZE];
	s32 chars_written = 0;
	const u32 buf_size = CONFIG_BDBGP_PRINT_BUFFER_SIZE;

	/* NOTE: No asserts can be made in this function */

	/* Print preamble */
	snprintf_concat( &buf[0], buf_size, &chars_written, "%s: ", func );

	/* Print Arguments */
	va_start(args, msg);
	vsnprintf_concat( &buf[0], buf_size, &chars_written, msg, args );
	va_end(args);

	/* Print CDBG_STOP_MSG */
	snprintf_concat( &buf[0], buf_size, &chars_written, "%s", CDBG_STOP_MSG );

	/* __compile_time_asserts ensure buf_size is big enough */
	basep_correct_snprintf_for_error( &buf[0], buf_size, &chars_written );

	base_channel_emergency_message( &buf[0], chars_written+1 );

}
void bdbgp_print_to_important_channel(u32 channel_idx, const char* type, const char* module, const char* trace, const char* func, const char* msg, ...)
{
	va_list args;
	char buf[CONFIG_BDBGP_PRINT_BUFFER_SIZE];
	s32 chars_written = 0;
	const u32 buf_size = CONFIG_BDBGP_PRINT_BUFFER_SIZE;

	/* NOTE: No asserts can be made in this function */
	UNUSED( channel_idx );

	/* Print preamble */
	snprintf_concat( &buf[0], buf_size, &chars_written, "%s[%s] %s: %s %s\n", CDBG_START_MSG, type, module, trace, func);

	/* Print Arguments */
	va_start(args, msg);
	vsnprintf_concat( &buf[0], buf_size, &chars_written, msg, args);
	va_end(args);

	/* Print CDBG_STOP_MSG */
	snprintf_concat( &buf[0], buf_size, &chars_written, "%s", CDBG_STOP_MSG );

	/* __compile_time_asserts ensure buf_size is big enough */
	basep_correct_snprintf_for_error( &buf[0], buf_size, &chars_written );

	base_channel_emergency_message( &buf[0], chars_written+1 );
}
