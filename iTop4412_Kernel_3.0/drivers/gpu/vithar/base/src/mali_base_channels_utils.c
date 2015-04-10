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
#include <cutils/cstr/mali_cutils_cstr.h>

/*
 * NOTE on loop contstructs:
 *
 * We often use 'for ( i = max; i-- > 0 ; ), because it is a counting down loop
 * construct that runs from max-1 to 0, regardless of whether i is signed or
 * unsigned. Therefore, you don't have to go and check whether i is signed or
 * not.
 */

#define BASEP_NEWLINE_CHAR_CRLF_1 '\r'
#define BASEP_NEWLINE_CHAR_CRLF_2 '\n'

STATIC CONST osu_lock_order ringbuf_lock_order_mapping[] =
{
	OSU_LOCK_ORDER_BASE_CHANNELS_INFO,
	OSU_LOCK_ORDER_BASE_CHANNELS_WARN,
	OSU_LOCK_ORDER_BASE_CHANNELS_ERROR,
	OSU_LOCK_ORDER_BASE_CHANNELS_SPEW
};

/*
 * Function protos
 */
STATIC u32 basep_do_2byte_newline_conversion( basep_channel_conversion_args *args );
STATIC void ensure_message_ends_in_crlf( char *buf, u32 size, s32 *chars_written_ptr );

/*
 * Private Functions
 */

/*
 * This function must not use any BDBG messaging or BDBG asserts.
 */
STATIC u32 basep_do_2byte_newline_conversion( basep_channel_conversion_args *args )
{
	u32 bytes_written;

	u32 src_remain;
	u32 dest_remain;
	
	char *dest_start;
	char *dest_ptr;
	const char *src_ptr;

	char conv_char_1;
	char conv_char_2;
	s32 chars_written;

	src_remain = args->src_size;
	dest_remain = args->dest_size;

	dest_start = args->dest;
	src_ptr = args->src;

	dest_ptr = dest_start;

	conv_char_1 = BASEP_NEWLINE_CHAR_CRLF_1;
	conv_char_2 = BASEP_NEWLINE_CHAR_CRLF_2;

	while ( (dest_remain-- > 0) && (src_remain-- > 0) ) /* See Note at top of file */
	{
		char char_to_copy;

		char_to_copy = *src_ptr++;
		if ( BASEP_NEWLINE_CHAR_DEFAULT == char_to_copy )
		{
			*dest_ptr++ = conv_char_1;

			if ( dest_remain > 0 )
			{
				dest_remain--;
				*dest_ptr++ = conv_char_2;
			}
		}
		else
		{
			*dest_ptr++ = char_to_copy;
		}
	}

	/* dest_ptr now points to the character after the one that was last written */
	chars_written = (dest_ptr - dest_start) - 1;

	/*
	 * Force NULL termination - noting that for the case of src shorter than
	 * dest, we don't place the NULL character at *dest_ptr, because last byte
	 * copied from src would've been the NULL terminator, by function contract.
	 */
	if ( chars_written >= 0 )
	{
		*(dest_ptr - 1) = 0;
	}
	else
	{
		/* NOTE: API contract says dest_size==0 is not allowed */
		*dest_start = 0;
		chars_written = 0;
	}
	ensure_message_ends_in_crlf( dest_start, args->dest_size, &chars_written  );

	bytes_written = chars_written + 1;

	return bytes_written;
}


/*
 * Protected functions
 */

/*
 * Newline Conversion Block
 */

/*
 * This function must not use any CDBG/BDBG messaging/asserts, or call any
 * other functions that use CDBG/BDBG messaging/asserts
 */
u32 basep_channel_convert_newlines( basep_channel_conversion_args *args )
{
	u32 bytes_written = 0;

	switch ( args->flags & BASEP_NEWLINE_CONVERSION_FLAGS_MASK )
	{
		/* Non-trivial conversion */
		case BASEP_CHANNEL_DESTINATION_FLAG_NEWLINE_CRLF:
			/* This also ensures the message ends in the correct newline sequence */
			bytes_written = basep_do_2byte_newline_conversion( args );
			break;

		/* Trivial conversion */
		case 0:
			{
				u32 size_to_copy = MIN( args->dest_size, args->src_size );
				s32 chars_written;

				if ( size_to_copy > 0 )
				{
					/* Trivial conversion */
					basep_channel_slow_memcpy_nonassert( args->dest, args->src, size_to_copy );

					/* Enforce NULL-termination */
					args->dest[size_to_copy-1] = 0;

					chars_written = size_to_copy-1;

				}
				else
				{
					args->dest[0] = 0;
					chars_written = 0;
				}

				/* Ensure this ends in a newline */
				basep_ensure_message_ends_in_newline( args->dest, args->dest_size, &chars_written );

				bytes_written = chars_written + 1;
				break;
			}

		default:
			BDBG_ASSERT( MALI_FALSE ); /* unreachable */
			break;
	}

	return bytes_written;
}

mali_error basep_alloc_newline_conversion_buffer( base_channel * const channel, u32 convbuf_size )
{
	BDBG_ASSERT_POINTER( channel );

	if ( convbuf_size > 0 )
	{
		void *buf;
		osu_errcode osu_err;
		/*
		 * NOTE: We can't use CMEM from here, because we need the debug
		 * messaging path initialized before CMEM is. This is so that CMEM can
		 * use CDBG messages
		 */
		buf = stdlib_malloc( convbuf_size );

		if ( NULL == buf )
		{
			return MALI_ERROR_FUNCTION_FAILED;
		}

		/* Allocate the mutex */
		osu_err = osu_mutex_init( &channel->basep_internal_struct.lcbuf_mutex,
								  OSU_LOCK_ORDER_BASE_CHANNELS_LARGE_CONVERSION_BUFFER );

		if ( osu_err != OSU_ERR_OK )
		{
			stdlib_free( buf );
			return MALI_ERROR_FUNCTION_FAILED;
		}

		channel->basep_internal_struct.large_conversion_buffer = buf;
	}

	/* Cache the buffer size, only on success */
	channel->basep_internal_struct.lcbuf_size = convbuf_size;

	return MALI_ERROR_NONE;
}

void basep_free_newline_conversion_buffer( base_channel * const channel )
{
	BDBG_ASSERT_POINTER( channel );
	
	if ( channel->basep_internal_struct.lcbuf_size > 0 )
	{
		osu_mutex_term( &channel->basep_internal_struct.lcbuf_mutex );
		stdlib_free( channel->basep_internal_struct.large_conversion_buffer );
	}
}

char *basep_lock_newline_conversion_buffer( base_channel * const channel )
{
	BDBG_ASSERT( channel->basep_internal_struct.lcbuf_size > 0 );

	osu_mutex_lock( &channel->basep_internal_struct.lcbuf_mutex );

	return channel->basep_internal_struct.large_conversion_buffer;
}

void basep_unlock_newline_conversion_buffer( base_channel * const channel )
{
	BDBG_ASSERT( channel->basep_internal_struct.lcbuf_size > 0 );

	osu_mutex_unlock( &channel->basep_internal_struct.lcbuf_mutex );
}

/*
 * Emptying Ringbuffer Block
 */

mali_error basep_emptying_ringbuf_init(
	basep_channels_emptying_ringbuffer* const ringbuf,
	const u32 atom_size, const u32 num_atoms_order,
	base_channel_type channel_type
	)
{
	mali_error mali_err;
	BDBG_ASSERT_POINTER( ringbuf );
	BDBG_ASSERT_RANGE( channel_type, 0, BASE_CHANNEL_COUNT-1 );

	mali_err = cutils_ring_buffer_new( &ringbuf->ringbuf, atom_size, num_atoms_order );
	if ( MALI_ERROR_NONE != mali_err )
	{
		return mali_err;
	}

#if 0 != CONFIG_EMPTYING_RINGBUF_SLOW_LOCK_CHECKING
	{
		osu_errcode osu_err;
		osu_lock_order lock_order = ringbuf_lock_order_mapping[channel_type];

		osu_err = osu_mutex_init( &ringbuf->lock_for_checking, lock_order );
		if ( osu_err != OSU_ERR_OK )
		{
			/* Cleanup */
			cutils_ring_buffer_delete( &ringbuf->ringbuf );
			return MALI_ERROR_FUNCTION_FAILED;
		}
	}
#endif

	return MALI_ERROR_NONE;
}

void basep_emptying_ringbuf_term( basep_channels_emptying_ringbuffer* ringbuf )
{
	BDBG_ASSERT_POINTER( ringbuf );

#if 0 != CONFIG_EMPTYING_RINGBUF_SLOW_LOCK_CHECKING
	osu_mutex_term( &ringbuf->lock_for_checking );
#endif

	cutils_ring_buffer_delete( &ringbuf->ringbuf );	
}

cutils_ring_atom *basep_emptying_ringbuf_write_lock(
	basep_channels_emptying_ringbuffer* const ringbuf )
{
	cutils_ring_atom *result = NULL;

	BDBG_ASSERT_POINTER( ringbuf );

#if 0 != CONFIG_EMPTYING_RINGBUF_SLOW_LOCK_CHECKING
	osu_mutex_lock( &ringbuf->lock_for_checking );
#endif

	result = cutils_ring_buffer_write_lock( &ringbuf->ringbuf );

	while ( NULL == result )
	{
		/* Do a 'dummy read' to free a slot, by locking and unlocking: */
		result = cutils_ring_buffer_read_lock( &ringbuf->ringbuf );

		if ( NULL != result )
		{
			cutils_ring_buffer_read_unlock( &ringbuf->ringbuf, result );
		}
		/*
		 * NOTE: if the read failed (e.g. a writer taking a long time to
		 * complete), we could block here until reading can commence. Instead,
		 * we'll just spin trying to obtain a write lock instead.
		 *
		 * Occurances of spinning can be reduced by increasing the channel's
		 * messages_to_keep_log2 configuration value.
		 */

		result = cutils_ring_buffer_write_lock( &ringbuf->ringbuf );
	}

	return result;
}

void basep_emptying_ringbuf_write_unlock(
	basep_channels_emptying_ringbuffer* const ringbuf,
	cutils_ring_atom* atom )
{
	cutils_ring_buffer_write_unlock( &ringbuf->ringbuf, atom );

#if 0 != CONFIG_EMPTYING_RINGBUF_SLOW_LOCK_CHECKING
	osu_mutex_unlock( &ringbuf->lock_for_checking );
#endif

}

/*
 * General
 */

/* This must not make asserts */
void *basep_channel_slow_memcpy_nonassert( void *dst, const void *src, size_t len )
{
	char *dst_char_ptr = (char*)dst;
	const char *src_char_ptr = (const char*)src;
	while ( len-- > 0 )  /* See Note at top of file */
	{
		*dst_char_ptr++ = *src_char_ptr++;
	}

	return dst;
}

/* This must not make asserts */
void basep_correct_snprintf_for_error( char *buf, u32 size, s32 *chars_written_ptr )
{
	s32 chars_written;

	chars_written = *chars_written_ptr;

	if ( chars_written < 0 )
	{
		u32 insert_pos;
		/* There was an error, so find out how big the string written was */
		insert_pos = cutils_cstr_len( buf, size );

		if ( insert_pos + BDBGP_ERROR_MESSAGE_SIZE > size )
		{
			insert_pos = size - BDBGP_ERROR_MESSAGE_SIZE;
		}
		/* No asserts about insert_pos can be made here */

		basep_channel_slow_memcpy_nonassert( buf + insert_pos, BDBGP_ERROR_MESSAGE, BDBGP_ERROR_MESSAGE_SIZE );

		chars_written = size - 1;
		/* Make doubly sure of NULL termination: */
		buf[chars_written] = 0;

		*chars_written_ptr = chars_written;
	}
	else if ( chars_written >= size )
	{
		/* Use the entire buffer */
		u32 insert_pos;
		
		insert_pos = size - BDBGP_TRUNCATION_MESSAGE_SIZE;
		/* No asserts about insert_pos can be made here */

		/* Copy in the truncation message */
		basep_channel_slow_memcpy_nonassert( buf + insert_pos,
											 BDBGP_TRUNCATION_MESSAGE,
											 BDBGP_TRUNCATION_MESSAGE_SIZE );

		chars_written = size - 1;

		*chars_written_ptr = chars_written;
	}
}


/* This must not make asserts */
void basep_ensure_message_ends_in_newline( char *buf, u32 size, s32 *chars_written_ptr )
{
	s32 chars_written = *chars_written_ptr;

	/* NULL term is at chars_written, last char written is at chars_written-1 */
	if ( 0 == chars_written || buf[chars_written-1] != BASEP_NEWLINE_CHAR_DEFAULT )
	{
		/* last character was not a newline - determine where to add one */
		if ( chars_written < size-1 )
		{
			/* There's space to place an extra char at the NULL terminator */
			buf[chars_written++] = BASEP_NEWLINE_CHAR_DEFAULT;
			buf[chars_written] = 0;
		}
		else
		{
			/* No space to put an extra character, just overwrite the last one */
			buf[chars_written-1] = BASEP_NEWLINE_CHAR_DEFAULT;
		}

		/* chars_written is now at most size-1 */
		*chars_written_ptr = chars_written;
	}
}

/* This must not make asserts */
void ensure_message_ends_in_crlf( char *buf, u32 size, s32 *chars_written_ptr )
{
	s32 chars_written = *chars_written_ptr;

	/* NULL term is at chars_written, last char written is at chars_written-1 */
	if ( chars_written <= 1
		 || buf[chars_written-1] != BASEP_NEWLINE_CHAR_CRLF_2
		 || buf[chars_written-2] != BASEP_NEWLINE_CHAR_CRLF_1 )
	{
		/* last characters were not newline - determine where to add one */

		if ( chars_written < size-2 )
		{
			/* There's space to place an extra char at the NULL terminator */
			buf[chars_written++] = BASEP_NEWLINE_CHAR_CRLF_1;
			buf[chars_written++] = BASEP_NEWLINE_CHAR_CRLF_2;
			buf[chars_written] = 0;
		}
		else
		{
			/* No space to put an extra character, just overwrite the last two, if space */
			if ( chars_written >= 2 )
			{
				buf[chars_written-2] = BASEP_NEWLINE_CHAR_CRLF_1;
				buf[chars_written-1] = BASEP_NEWLINE_CHAR_CRLF_2;
			}
			/* NOTE: we don't handle the case of a 3-byte buffer with 1 character written.
			 * Instead, increase your buffer size.*/
		}

		/* chars_written is now at most size-1 */
		*chars_written_ptr = chars_written;
	}
}
