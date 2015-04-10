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
 * @file mali_base_channels.h
 * User-side interaction with the Base Driver Portable Debug Channels
 */


#ifndef _BASE_CHANNELS_H_
#define _BASE_CHANNELS_H_

#include <malisw/mali_stdtypes.h>
#include <malisw/mali_malisw.h>
#include <base/mali_base_channels_types.h>
#include <base/src/mali_base_channels_priv.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @page page_base_user_api_channels User-side Base Portable Debug Channels
 *
 * Base Portable Debug Channels provide a low level API for:
 * - a portable abstraction for the physical destination(s) of a debug message.
 * - buffer space in which to place a debug message
 * - a means for multiple threads to output debug messages without corrupting
 * each other.
 * - an abstraction of line-endings.
 *
 * These features are provided for the Common Debug Module (CDBG), which is
 * responsible for:
 * - Formatting messages
 * - Providing a Higher-level debug messaging API to the rest of the DDK
 *
 * Finally, an API is provided for 'emergency' messages:
 * base_channel_emergency_message(). This allows 'emergency' debug messages to
 * be sent before a base channel has finished opening, or during any function
 * that the base channel relies on (to prevent re-entrancy problems).
 *
 * Refer to the following pages:
 *
 * - @subpage page_base_channels_use
 * - @subpage page_base_channels_phys_dest
 * - @subpage page_base_channels_buffers_and_threads
 * - @subpage page_base_channels_newline
 * - @subpage page_base_channels_config
 * - @subpage page_base_channels_debugger
 */


/**
 * @page page_base_channels_phys_dest Abstraction of the Physical Destination of a Debug Message
 *
 * The actual physical destination of a message is abstracted into a portable
 * 'channel type', as given in the @ref base_channel_type enum. Each channel
 * type can be configured to route messages to zero, one or many physical
 * destinations. The flexibility allows configurations such as: 
 * - Every channel outputs messages on the same physical destination
 * - Every channel outputs messages on a different physical destination
 * - Channels of certain types output messages onto more than one destination
 * - Channels of certain types do \em not output messages at all (see below)
 *
 * The physical destinations themselves are implementation specific. They may
 * include:
 * - The Stdlib Standard Output Stream, provided by STDLIB_OUTPUT_STREAM
 * - The Stdlib Standard Error Stream, provided by STDLIB_ERROR_STREAM
 * - Files on a filesystem accessed by the Stdlib File API.
 *
 * The cost of outputting to a physical destination is not specified, and might
 * vary significantly between them. If this cost affects the debugging
 * activities, then channels of certain types could be configured to \em not
 * output messages. Instead, the message is kept in the buffer that was
 * provided by the Debug Channel API (see base_channel_lock() ). Buffer space
 * is quickly re-used (to bound the memory usage), but even so, this allows the
 * DDK to record in memory the last few debug messages. This minimizes the cost
 * of the debug messages, but still allows a number of recent debug messages to
 * be seen when a debugger is attached. Refer to @ref
 * page_base_channels_debugger for more information.
 *
 * Refer to @ref page_base_channels_config for configuration of the Base
 * Portable Debug Channels.
 *
 * With regards to the Common Debug Module, there is a 1:1 relationship between
 * the services exposed there, and the services exposed here. For example:
 * - CDBG_PRINT_INFO uses a channel of type BASE_CHANNEL_INFO
 * - CDBG_PRINT_WARN uses a channel of type BASE_CHANNEL_WARN
 * - CDBG_SPEW_LOCK et al. use a channel of type BASE_CHANNEL_SPEW
 */


/**
 * @page page_base_channels_use Use of Base Portable Debug Channels
 *
 * The following is an example of opening a channel for information messages:
 * @code
	struct base_channel info_channel;
	base_channel_open( &info_channel, BASE_CHANNEL_INFO ); 
   @endcode
 *
 * Messages are written by locking the channel, as described in
 * @ref page_base_channels_buffers_and_threads :
 * @code
	struct base_channel_lock_ctx lock_ctx;
	u8 *buffer;
	u32 buffer_size

    buffer = base_channel_lock( &lock_ctx, &buffer_size, info_channel )
	@endcode
 *
 * Writes can then be done to the buffer returned by the lock function, noting
 * that they must be
 * - no larger than buffer_size
 * - NULL terminated.
 *
 * For example:
 * @code
	const char msg[] = "Buffer Size is %ul bytes\n";
	s32 chars_written;
	u32 msg_param = buffer_size;

	chars_written = cutils_cstr_snprintf( buffer, buffer_size, msg, msg_param );
	
	// mali_str_snprintf() guarentees buffer[MIN(buffer_size-1,MAX(chars_written,0))] == 0 when buffer_size > 0
   @endcode
 *
 * To notify the channel that the message is complete, you must unlock the
 * channel, and indicate how many characters (before the NULL terminator) we
 * attempted to write:
 * @code
	base_channel_unlock( &lock_ctx, chars_written );
   @endcode
 *
 * Note that the value passed into base_channel_unlock() is designed to also
 * take the error case returns from mali_str_snprintf().
 */


/**
 * @page page_base_channels_buffers_and_threads Thread-safe Writing of Messages
 *
 * All messages are written by locking the channel with
 * base_channel_lock(). This provides a buffer for the caller to write a
 * message into. The buffer will not be given to another thread whilst it is
 * locked, thus ensuring that no corruption occurs whilst other threads are
 * also writing messages. That is, the message writing is thread safe.
 *
 * The mechanism for ensuring the thread safety is implementation specific. It
 * could ensure thread safety by blocking any other thread from writing, or it
 * could have a number of buffers to allow a number of threads to write
 * concurrently (but some threads may still block if you run out of
 * buffers). In any case, locking the channel should be treated with the same
 * care as locking a mutex - refer to base_channel_lock() for more details.
 *
 * When the caller has finished writing a message, it must unlock the channel
 * with base_channel_unlock().
 *
 * The message must be NULL terminated, and the number of characters written
 * (before the NULL terminator) should be passed into the base_channel_unlock()
 * function. This is for two reasons:
 * -# The primary user of the channels is the Common Debug Module, which uses
 * mali_str_snprintf(). This function always places a NULL terminator in the
 * buffer, even during error conditions. 
 * -# it is useful to provide a NULL terminator for some physical destinations,
 * but not to others. The \a chars_used parameter to base_channel_unlock()
 * allows the physical destination to use or remove such a NULL terminator.
 *
 * @section sec_base_channels_buffers_sizelimit Buffer Size Limitation and Large Messages
 *
 * The buffer has a limited size, as returned through base_channel_lock(). This
 * means that you may need to truncate your message passed in, whilst still
 * ensuring a NULL terminator. If the buffer size is insufficient to make a
 * message useful, it can be reconfigured to be larger. However, the actual
 * memory footprint may increase by some multiple of the buffer size, since a
 * number of buffers may be retained for debugging purposes (refer to @ref
 * page_base_channels_phys_dest).
 *
 * For this reason, an extra channel is provided for taking large messages, but
 * it retains far fewer messages in memory (perhaps only the last
 * message). This is the BASE_CHANNEL_SPEW channel type, and is provided for
 * the 'spew' functionality in the Common Debug Module.
 *
 * 'Spew' messages are a good example (but not the only example) of where are
 * messages are formatted with mulitple newline characters. Refer to @ref
 * page_base_channels_newline for more information.
 */

/**
 * @page page_base_channels_newline Messages that contain newline characters
 *
 * The newline character for the messages is assumed to be '\\n'.
 *
 * On certain physical destinations, this is not the desired way of producing a
 * new line. For example, messages output to a serial port must use the
 * sequence "\r\n" (CR+LF).
 *
 * In this case, the code that interfaces with the physical destination must be
 * written to convert the '\\n' character into the desired newline sequence.
 *
 * For the user of Base Portable Debug Channel, this means that handling of
 * newlines occurs transparently, regardless of how the underlying physical
 * destination(s) will treat newlines.
 */


/**
 * @page page_base_channels_config Configuring Base Portable Debug Channels
 *
 * Configuration is stored per platform, and should be placed in a file in the
 * platform layer. The configuration allows for each channel type:
 * - 0, 1 or multiple physical destinations
 * - number of messages to keep (even for >0 destinations)
 * - max size of each message
 * - the path for file-based destinations.
 *
 * The requirement is for the platform layer to expose an array of
 * <tt>struct basep_channel_type_config</tt> structures and, of length
 * BASE_CHANNEL_COUNT.
 *
 * The following declarations will be exposed privately:
 * @code

	// Output destinations bitvec. 0 indicates none.
	#define BASEP_CHANNEL_CONFIG_STDOUT 0x00000001ul
	#define BASEP_CHANNEL_CONFIG_STDERR 0x00000002ul
	#define BASEP_CHANNEL_CONFIG_FILE   0x00000004ul

	typedef struct basep_channel_type_config
	{
		// Bit vector of BASEP_CHANNEL_CONFIG_<xyz> flags. When none are set,
		// the messages are not sent to any destination, and just kept in memory.
		u32 flags;

		// Messages to keep in memory, even when flags != 0. Must be a power of
		// 2.
		u32 messages_to_keep;

		// Must also account for space for NULL terminator
		u32 max_size_of_message;

		// Only for BASEP_CHANNEL_CONFIG_FILE
		char *path;
	} basep_channel_type_config;

	extern struct basep_channel_type_config basep_channel_config[ BASE_CHANNEL_COUNT ];
   @endcode
 * 
 * And, the platform should make the following definition:
 * @code
	basep_channel_type_config basep_channel_config[ BASE_CHANNEL_COUNT ] =
	{
		// Configuration for each channel goes here
	};

   @endcode
 */

/**
 * @page page_base_channels_debugger Using a Debugger with the Base Portable Debug Channels
 *
 * The channels can be examined in a debugger by inspecting the Common Debug
 * Module's internal global array of open channels.
 */


/**
 * @addtogroup base_api
 * @{
 */

/**
 * @addtogroup base_user_api
 * @{
 */

/**
 * @defgroup base_user_api_channels User-side Base Portable Debug Channel APIs
 * @{
 * @}
 */

/**
 * @addtogroup base_user_api_channels
 * @{
 */


/*
 * Public Types
 */

/**
 * @brief Portable Debug Channel Structure
 */
typedef struct base_channel
{
	struct
	{
		basep_channels_emptying_ringbuffer ringbuf;
		u32 cached_atom_size;

		basep_channel_destinations_info destinations;
		u32 shared_dests_in_use;

		u32 lcbuf_size;
		osu_mutex lcbuf_mutex;
		char *large_conversion_buffer;

	} basep_internal_struct;

} base_channel;

/**
 * @brief Channel Lock Context Structure
 */
typedef struct
{
	struct
	{
		base_channel *channel;
		cutils_ring_atom* atom;
	} basep_internal_struct;
} base_channel_lock_ctx;


/*
 * Public API Functions
 */

/**
 * @brief Emergency messages
 *
 * This allows you to output a message before (or during) the initialization
 * phase of the driver. For example, if an error occurs during
 * base_channel_open(), then you won't be able to use a base channel for
 * outputting a message about that error.
 *
 * Emergency Messaging must also be used for any function that is used by the
 * base channels API for its implementation. This is to prevent re-entrancy
 * problems. For example, the mutex functions used to lock a channel with
 * base_channel_lock() \b must use emergency messages if they wish to present
 * error messages.
 *
 * The emergency channel may have restricted capabilities (such as lack of
 * thread safety, number of messages that can be output, size of messages). All
 * such properties are implementation specific.
 *
 * The message must be NULL terminated at the last character in the buffer.
 * That is, message[buffer_size-1] == 0. Therefore, some processing may be
 * required from the number of characters written returned by
 * cutils_cstr_snprintf(). The message is allowed to contain NULL characters
 * elsewhere, but it is then implementation defined how much is output.
 *
 * @param[in] message a NULL terminated string to output
 * @param buffer_size the size of the buffer pointed to by \a message
 */
void base_channel_emergency_message( CONST char * message, size_t buffer_size  );

/**
 * @brief Initialize the Base Portable Debug Channels
 *
 * You must call this function before using any Base Portable Debug Channels
 * function \em except for base_channel_emergency_message().
 *
 * base_channel_emergency_message() may be used without calling this function.
 *
 * Only one thread may call this. The caller must arrange for their own mutual
 * exclusion.
 *
 * @return MALI_ERROR_NONE on success
 * @return Otherwise, a suitable mali_error value on failure.
 */
mali_error base_channel_init( void ) CHECK_RESULT;

/**
 * @brief Terminate the Base Portable Debug Channels
 *
 * You must call this function after all Portable Debug Channels have been
 * closed, to free any remaining resources.
 *
 * Only one thread may call this. The caller must arrange for their own mutual
 * exclusion.
 */
void base_channel_term( void );

/**
 * @brief Open a Portable Debug Channel
 *
 * A Debug Channel must be opened before use. The channel should only need to
 * be opened once, for the lifetime of the base context. Calling
 * base_channel_open() twice with the same value for \a type, but on different
 * \a channel structures is allowed, but:
 * - is not useful
 * - adds extra memory overhead
 * - the ordering of messages from those channels on their physical destination
 * is unpredictable.
 *
 * The type of the channel gives a portable, abstract means for specifying
 * where the message should be sent to. Refer to @ref
 * page_base_channels_phys_dest.
 *
 * @param[out] channel A channel structure to initialize, to represent the channel
 *                     being opened in future calls to the Portable Debug
 *                     Channels API.
 * @param type         The type of the channel. Refer to @ref
 *                     page_base_channels_phys_dest for more information. 
 * @return MALI_ERROR_NONE on success, a suitable mali_error code on failure.
 */
mali_error base_channel_open( base_channel * CONST channel, base_channel_type type ) CHECK_RESULT;

/**
 * @brief Close a Portable Debug Channel
 *
 * Closes a Portable Debug Channel. This should be done at the time of
 * deinitializing the base context.
 *
 * Resources associated with the channel will be released.
 *
 * The channel structure pointed to by \a channel becomes invalid after this
 * operation.
 *
 * It is an error to close a channel that is currently locked by
 * base_channel_lock().
 *
 * @param[in] channel The channel to close, as opened by base_channel_open().
 */
void base_channel_close( base_channel *channel );

/**
 * @brief Lock a Portable Debug Channel, to write a message to it
 *
 * This function provides a thread-safe way of writing messages to a
 * channel. The message should be written into returned pointer, and no
 * more than \a *size bytes must be written to this buffer. Refer to
 * @ref page_base_channels_buffers_and_threads for more information.
 *
 * Messages written must be NULL terminated - refer to base_channel_unlock().
 *
 * In a message, a '\\n' character is treated as a newline, and will be
 * re-interpreted as necessary for the underlying physical destination(s).
 *
 * Locking the channel should be treated with the same care as locking a
 * mutex. Specifically:
 * - Do not lock it twice in succession from the same thread, as it will
 * deadlock
 * - When locking more than one channel, you must ensure that every
 * thread locks the channels in the same order, otherwise a deadlock could
 * occur between threads. To be consistant across the driver, the order is
 * defined by the @ref base_channel_type enum, and the lowest numbered channel
 * must be locked first.
 * 
 * Note that it is acceptable to lock different channels at the same time, to
 * output on multiple channels (if necessary).
 *
 * If there is insufficient buffer space, then this function will block until
 * some buffer space becomes free for use. It never returns a NULL pointer.
 *
 * @param[out] ctx    A Channel lock context structure to initialize, to be
 *                    passed to base_channel_unlock() when you have finished
 *                    writing the message.
 * @param[out] size   Pointer to storage to return the size of the buffer.
 * @param[in] channel The channel to lock.
 * @return a Non-NULL pointer to a buffer of size \a *size, for writing the
 * message into.
 */
char *base_channel_lock( base_channel_lock_ctx * CONST ctx, u32 * CONST size, base_channel *channel );


/**
 * @brief Notify the channel that you have finished writing a message, and
 * unlock the channel.
 *
 * The message should must be completely written into the buffer passed by
 * base_channel_lock(). This buffer becomes invalid by the end of this function
 * call.
 *
 * The message must be NULL terminated. Refer to @ref
 * page_base_channels_buffers_and_threads for the design decisions behind this.
 *
 * The value passed into \a chars_used is designed to be that returned from
 * mali_str_snprintf(). That is:
 * - if <tt>chars_used < 0</tt>, then there was an error in mali_str_snprintf(). An
 * implementation-specific message will be output on the channel to indicate
 * that there was a problem. However, the buffer must still contain a NULL
 * termination character somewhere in it. NULL termination in this way is the
 * normal operation of mali_str_snprintf() on error.
 * - if <tt>0 <= chars_used < buffer_size</tt>, then the message is output to its
 * destination(s), as normal. The NULL termination character must be at index
 * \a chars_used in the buffer. That is, <tt>buffer[chars_used]</tt> must be zero.
 * - if <tt>chars_used >= buffer_size</tt>, then this is used to indicate by
 * mali_str_snprintf() that the message would've been bigger than the buffer,
 * but was truncated to the size of the buffer. The message is output to the
 * destination. An implementation-specfic message will be output on the channel
 * to notify of the truncation. The buffer must be NULL terminated at the last
 * index. That is, <tt>buffer[buffer_size-1]</tt> must be zero.
 *
 * @illegal It is illegal to pass a message to a base channel without
 * terminating it correctly, or without supplying \a chars_used correctly, as
 * per the rules listed in base_channel_unlock().
 *
 * @param[in] ctx    The lock context structure that was intialized by a call
 *                   to base_channel_lock().
 * @param chars_used The number of characters that were/would be written, as
 *                   would be returned by mali_str_snprintf()
 * @return MALI_ERROR_NONE indicates that the message was output to its physical
 * destination(s) successfully. Any other mali_error value indicates that there
 * was a failure during output, and a corrupted message may appear on one or
 * more of the physical destination(s).
 */
mali_error base_channel_unlock( base_channel_lock_ctx * ctx, s32 chars_used ) CHECK_RESULT;



/** @} end group base_user_api_channels */
/** @} end group base_user_api */
/** @} end group base_api */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_CHANNELS_H_ */
