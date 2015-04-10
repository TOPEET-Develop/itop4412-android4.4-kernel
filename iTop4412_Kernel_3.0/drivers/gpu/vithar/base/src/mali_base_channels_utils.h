/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


#ifndef _BASE_CHANNELS_UTILS_H_
#define _BASE_CHANNELS_UTILS_H_


#include <malisw/mali_malisw.h>

#include <base/mali_base_channels.h>
#include <base/mali_base_debug.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Begin: Types
 */

/*
 * General
 */

/*
 * Error messages to insert during snprintf failure/print buffer truncation
 *
 * Size includes the NULL terminator.
 */
#define BDBGP_TRUNCATION_MESSAGE "\n***MESSAGE TRUNCATED***\n"
#define BDBGP_TRUNCATION_MESSAGE_SIZE (sizeof(BDBGP_TRUNCATION_MESSAGE))

#define BDBGP_ERROR_MESSAGE      "\n***FORMATTING ERROR***\n"
#define BDBGP_ERROR_MESSAGE_SIZE (sizeof(BDBGP_ERROR_MESSAGE))


/*
 * Config Block
 */
#define BASEP_CHANNEL_DESTINATION_BIT( dest ) ( 1UL << ((int)dest) )

/*
 * Importantant: keep the BASEP_NEWLINE_CONVERSION_FLAGS_BASE in sync with this
 */
#define BASEP_NEWLINE_CONVERSION_FLAGS_BASE 0

/** Flag to indicate that newline conversion is required, specifically to CRLF */
#define BASEP_CHANNEL_DESTINATION_FLAG_NEWLINE_CRLF F_BIT_0
/** Bit 1 reserved to allow other LF->xxyy conversions */
#define BASEP_CHANNEL_DESTINATION_FLAG_RESERVED_1   F_BIT_1

/** Flag to indicate whether the destination requires a mutex */
#define BASEP_CHANNEL_DESTINATION_FLAG_MUTEX_NEEDED F_BIT_2


/**
 * Flag to indicate that a destination will be shared across any channels using
 * it.
 *
 * The implications are:
 * - The physical destination will only be initialized once
 * - One mutex protects the destination across all channels
 *
 * Otherwise, this flag not being set means:
 * - The physical destination will be initialized once for each channel that
 * uses it
 * - There is one mutex \em per channel that uses the destination.
 * 
 * The use cases are as follows:
 * - The Stdout destination is shared by channels, so the mutex protects use by
 * any of these channels
 * - The same is true of the Stderr destination
 * - Platform-specific destinations that do not use the 'type' parameter should
 * set this, otherwise they will be initialized multiple times.
 * 
 * Conversely, the file destination is unlikely to set this, because each
 * channel can output to different files. It could be set if and only if all
 * channels wanted to output to the same file.
 */
#define BASEP_CHANNEL_DESTINATION_FLAG_SHARED     F_BIT_3



/* Any of these flags set indicates conversion required */
#define BASEP_NEWLINE_CONVERSION_FLAGS_MASK \
	( BASEP_CHANNEL_DESTINATION_FLAG_NEWLINE_CRLF | BASEP_CHANNEL_DESTINATION_FLAG_RESERVED_1 )

/* 2 Conversion formats are supported; LF->LF, and LF->CRLF */
#define BASEP_CHANNELS_CONVERSION_FORMAT_NONE 0
#define BASEP_CHANNELS_CONVERSION_FORMAT_CRLF 1
#define BASEP_CHANNELS_CONVERSION_FORMAT_COUNT 2


typedef struct basep_channel_type_config
{
	/*
	 * Messages to keep in memory, as a logarithm to base 2.
	 */
	u32 messages_to_keep_log2;

	/*
	 * Size of each message. Must also account for NULL termination character.
	 * Must be large enough for SNPRINTF_TRUNCATION_MESSAGE and
	 * SNPRINTF_ERROR_MESSAGE (see mali_base_channels.c)
	 */
	u32 max_size_of_message;

	/*
	 * Large conversion buffer size, for when messages are much longer than
	 * CONFIG_CHANNEL_CONVERSION_BUFFER_SIZE. 0 if not required.
	 */
	u32 large_conversion_size;

	/*
	 * Bitstring of destinations enabled. Each bit corresponds to a destination
	 * in basep_channel_destination.
	 */
	u32 destinations_enabled;

    /*
	 * Only required for BASEP_CHANNEL_DESTINATION_FILE
	 */
	char *path;
} basep_channel_type_config;

typedef struct basep_channel_destination_config
{
	/*
	 * Bitwise combination of macros prefixed with
	 * BASEP_CHANNEL_DESTINATION_FLAG_
	 */
	u32 flags;

} basep_channel_destination_config;

/*
 * Emptying Ringbuffer Block
 */
/*
 * Newline Conversion block
 */
#define BASEP_NEWLINE_CHAR_DEFAULT '\n'


typedef struct basep_channel_conversion_args
{
	char *dest;
	u32 dest_size;

	const char * src;
	u32 src_size;

	u32 flags;
} basep_channel_conversion_args;

/*
 * Platform-Specific messaging Block
 */

/*
 * End: Types
 */

/*
 * Begin: Variable Declarations
 */

/*
 * @brief Variable containing the array of channel configs for the platform.
 *
 * The definition of this variable is placed in the platform layer, usually as
 * base/platform_<platform_name>/mali_base_plat_channels_config.c
 */
extern CONST basep_channel_type_config basep_plat_channel_config[BASE_CHANNEL_COUNT];

/*
 * @brief Variable containing the array of channel destination configs for the
 * platform.
 *
 * The definition of this variable is placed in the platform layer, usually as
 * base/platform_<platform_name>/mali_base_plat_channels_config.c
 */
extern CONST basep_channel_destination_config basep_plat_channel_destination_config[BASEP_CHANNEL_DESTINATION_COUNT];


/*
 * End: Variable Declarations
 */



/*
 * Begin: Function/Macro Declarations
 */

/*
 * Config Block
 */
static INLINE const basep_channel_type_config *basep_channel_get_config(
	base_channel_type type )
{
	BDBG_ASSERT_RANGE( type, 0, BASE_CHANNEL_COUNT-1 );

	return &basep_plat_channel_config[ type ];
}

static INLINE const basep_channel_destination_config *basep_channel_destination_get_configs( void )
{
	return &basep_plat_channel_destination_config[0];
}

/*
 * Emptying Ringbuffer Block
 */
mali_error basep_emptying_ringbuf_init(
	basep_channels_emptying_ringbuffer* const ringbuf,
	const u32 atom_size, const u32 num_atoms_order,
	base_channel_type channel_type
	) CHECK_RESULT;

void basep_emptying_ringbuf_term( basep_channels_emptying_ringbuffer* ringbuf );

cutils_ring_atom* basep_emptying_ringbuf_write_lock(
	basep_channels_emptying_ringbuffer* const ringbuf ) CHECK_RESULT;

void basep_emptying_ringbuf_write_unlock(
	basep_channels_emptying_ringbuffer* const ringbuf,
	cutils_ring_atom* atom );

/*
 * Newline Conversion block
 */

/**
 * @brief Copies bytes from src to dest, converting newlines as specified in
 * the conversion type flags.
 * 
 * No more than dest_size bytes are written into dest. The size of src is
 * src_size bytes, and the last character must be a NULL termination
 * character. That is, src[src_size-1] == 0. If there was insufficient buffer
 * space to perform the conversion in dest, then the result is truncated. dest
 * is always NULL terminated. The function returns the number of bytes written
 * (including the NULL termination character). @note All bytes from src in
 * src_size bytes are copied (up to dest_size), even if NULL bytes exist
 * anywhere in src.
 *
 * It is a programming error to pass dest_size as 0.
 * 
 * It is a programming error to overlap the src and dest buffers. In-place
 * conversion is not supported.
 * 
 * flags specifies the type of the conversion, and is a combination of
 * BASEP_CHANNEL_DESTINATION_FLAG macros. Flags other than those for newline
 * conversion are ignored, allowing you to pass them in directly from the
 * basep_channel_destination_config structure.
 * 
 * If flags does not have any newline conversion flags set, then src is copied
 * to dest without conversion.
 *
 * The conversion potentially doubles the size of the source string, but that
 * can only happen if the source string only contains newline characters. The
 * worst use-case is expected to be on the Spew channel.
 * 
 * @note Important: Newline conversion can be used by
 * base_channel_emergency_message(), and so cannot make use of CDBG Asserts,
 * CDBG debug messaging, or Portable Debug Channel Emergency Messaging itself.
 *
 * Newline conversion ensures that the message ends in a newline character.
 */
u32 basep_channel_convert_newlines( basep_channel_conversion_args *args );

/**
 * Allocate a channel's the Large conversion buffer for newline conversion,
 * including its mutex
 *
 * When convbuf_size is 0, the conversion buffer is not allocated, but the
 * function returns success.
 *
 * channel->basep_internal_struct.lcbuf_size will be set appropriately on
 * success. To use free_conversion_buffer() from error path code (even before
 * alloc_conversion_buffer has been called), then zero this value beforehand,
 * and you will get the correct behavior.
 */
mali_error basep_alloc_newline_conversion_buffer( base_channel * const channel, u32 convbuf_size ) CHECK_RESULT;

/**
 * Deallocate conversion buffer resources.
 *
 * It is a programming error to call this when alloc_conversion_buffer()
 * *did not* return MALI_ERROR_NONE.
 */
void basep_free_newline_conversion_buffer( base_channel * const channel );

/**
 * Lock the conversion buffer, for access.
 * Do not call this when no conversion buffer was allocated
 * ( channel->basep_internal_struct.lcbuf_size == 0 )
 *
 * This always returns a non-NULL value - it will block until it can.
 */
char *basep_lock_newline_conversion_buffer( base_channel * const channel );

/**
 * Unlock the conversion buffer, releasing it to allow other threads access.
 * Do not call this when no conversion buffer was allocated
 * ( channel->basep_internal_struct.lcbuf_size == 0 )
 */
void basep_unlock_newline_conversion_buffer( base_channel * const channel );


/*
 * Platform-Specific messaging Block
 */

/**
 * basep_channel_platform_destination_open() opens a platform specific
 * destination for a type channel type. This provides an opportunity for
 * platform-specific initialization to occur. The implementation need not do
 * anything, but returns MALI_ERROR_NONE on success, and a suitable mali_error
 * otherwise. 
 */
mali_error basep_channel_platform_destination_open(
	basep_channel_platform_destination * const plat_channel,
	base_channel_type type ) CHECK_RESULT;

/**
 * basep_channel_platform_destination_close() closes the platform specific
 * destination, allow platform-specific de-initialization to occur, if
 * necessary.
 */
void basep_channel_platform_destination_close(
	basep_channel_platform_destination *plat_channel );

/**
 * basep_channel_platform_destination_write() writes a message to the specified
 * platform-specific destination. The message is of size bytes in length, and
 * is NULL terminated. That is, msg[size-1] == 0. On success, it returns
 * MALI_ERROR_NONE, otherwise a suitbale mali_error value on failure. This
 * function need not ensure mutual exclusion is resepected on any of the
 * platform-specific channels when BASEP_CHANNEL_DESTINATION_FLAG_MUTEX_NEEDED
 * is set for BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC in the
 * basep_channel_destination_config returned by
 * basep_channel_destination_get_configs(). Otherwise, mutual exclusion must be
 * managed by this function for all platform-specific channels that are
 * implemented.
 */
mali_error basep_channel_platform_destination_write( 
	basep_channel_platform_destination *plat_channel,
	const char *msg,
	u32 size ) CHECK_RESULT;

/*
 * General
 */

/**
 * A slow reference implementation of memcpy that doesn't make any asserts,
 * and so can be used within the 'emergency' messaging path.
 *
 * src and dst have no alignment restrictions.
 * 
 * Performance is not required for the 'emergency' messaging path, otherwise
 * we would place this in the porting layer (platform-specific messaging).
 *
 */
void *basep_channel_slow_memcpy_nonassert( void *dst, CONST void *src, size_t len );

/**
 * Correct the value from chars_written as received from snprintf, and insert
 * message indicators (such as 'truncation' or 'formatting error' )
 *
 * This function does not make any asserts, and so can be used within the 
 * 'emergency' messaging path.
 *
 * It is assumed that size is at least that of:
 * - BDBGP_ERROR_MESSAGE_SIZE
 * - BDBGP_TRUNCATION_MESSAGE_SIZE
 */
void basep_correct_snprintf_for_error( char *buf, u32 size, s32 *chars_written_ptr );

/**
 * Ensure that a message ends in a newline ('\n') character, placing it after
 * the end of the message if there is space, or overwriting the last non-NULL
 * character otherwise.
 *
 * size must be greater than 0.
 * chars_written represents the number of characters written not including the
 * NULL terminator, and must already be in the range 0 <= chars_written < size.
 * 
 * This function does not make any asserts, and so can be used within the 
 * 'emergency' messaging path.
 */
void basep_ensure_message_ends_in_newline( char *buf, u32 size, s32 *chars_written_ptr );


/*
 * End: Function/Macro Declarations
 */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_CHANNELS_UTILS_H_ */
