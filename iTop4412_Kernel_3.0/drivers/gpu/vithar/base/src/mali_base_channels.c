/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include "mali_base_channels_utils.h"

/*
 * NOTE on loop contstructs:
 *
 * We often use 'for ( i = max; i-- > 0 ; ), because it is a counting down loop
 * construct that runs from max-1 to 0, regardless of whether i is signed or
 * unsigned. Therefore, you don't have to go and check whether i is signed or
 * not.
 */

/*
 * Private state
 */
STATIC basep_channel_destinations_info shared_destinations;

/* 
 * Array of bitstrings representing newline conversion equivalence groups for
 * destinations. Each element in the array corresponds to a set of
 * destinations that require a certain type of newline conversion.
 */
STATIC u32 dest_conversion_groups[BASEP_CHANNELS_CONVERSION_FORMAT_COUNT];



/*
 * Function protos
 */
STATIC void prepare_shared_dests( basep_channel_destinations_info * const phys_destinations,
								 const basep_channel_destination_config *dest_config_array );

STATIC mali_error open_a_dest( basep_channel_destinations_info * phys_destinations,
							   basep_channel_destination dest_idx ) CHECK_RESULT;
STATIC void close_a_dest( basep_channel_destinations_info * phys_destinations,
						  basep_channel_destination dest_idx );

STATIC void init_destinations( basep_channel_destinations_info *phys_destinations,
							  const basep_channel_destination_config *dest_config_array );
STATIC void term_destinations( basep_channel_destinations_info *phys_destinations );

STATIC mali_error write_to_channels( basep_channel_destinations_info *dest_info,
									 u32 dests_to_access,
									 const char *destbuf,
									 u32 destbuf_size ) CHECK_RESULT;
STATIC mali_error channel_write_worker( basep_channel_conversion_args *conv_args,
										basep_channel_destinations_info *dest_info,
										u32 current_shared_newline_group,
										u32 current_per_channel_newline_group ) CHECK_RESULT;
/*
 * Private functions/macros
 */

/*
 * The channel type used for when the platform destination is shared
 */
#define CHANNEL_TYPE_FOR_SHARED_PLATFORM_DEST BASE_CHANNEL_INFO

/*
 * Error messages to insert for base_channel_unlock
 *
 * Size includes the NULL terminator.
 *
 * Note: after newline conversion, the messages may be longer. This may require
 * separate macros if we want conversion truncation messages
 */
#define SNPRINTF_TRUNCATION_MESSAGE "\n***MESSAGE TRUNCATED***\n"
#define SNPRINTF_TRUNCATION_MESSAGE_SIZE (sizeof(SNPRINTF_TRUNCATION_MESSAGE))

#define SNPRINTF_ERROR_MESSAGE "\n***FORMATTING ERROR***\n"
#define SNPRINTF_ERROR_MESSAGE_SIZE (sizeof(SNPRINTF_ERROR_MESSAGE))


/*
 * Get the shared dests, storing them in phys_destinations, and update any
 * destination-specific data, such as file_dest_path.
 * 
 * The destination specific data is taken from the first destination that
 * uses it.
 */
STATIC void prepare_shared_dests( basep_channel_destinations_info * const phys_destinations,
								  const basep_channel_destination_config *dest_config_array )
{
	u32 shared_dests;
	u32 all_enabled_dests;
	int i;
	
	BDBG_ASSERT_POINTER( phys_destinations );
	BDBG_ASSERT_POINTER( dest_config_array );

	shared_dests = 0;
	for ( i = BASEP_CHANNELS_CONVERSION_FORMAT_COUNT; i-- > 0 ; ) /* See Note at top of file */
	{
		dest_conversion_groups[i] = 0;
	}

	/*
	 * Build a bit-string of shared destinations
	 * At the same time, work out the newline-conversion equivalency groups
	 */
	for ( i = BASEP_CHANNEL_DESTINATION_COUNT; i-- > 0 ; )  /* See Note at top of file */
	{
		u32 dest_flags;
		int group_idx;
		shared_dests <<= 1; /* No-ops on the first iteration, as required */
		
		dest_flags = dest_config_array[i].flags;

		/* Build shared destinations bit-string */
		if ( 0 != (dest_flags & BASEP_CHANNEL_DESTINATION_FLAG_SHARED) )
		{
			shared_dests |= 1;
		}

		/* Build newline conversion equivalence group bitstrings */
		group_idx = (dest_flags & BASEP_NEWLINE_CONVERSION_FLAGS_MASK) >> BASEP_NEWLINE_CONVERSION_FLAGS_BASE;
		BDBG_ASSERT_RANGE( group_idx, 0, BASEP_CHANNELS_CONVERSION_FORMAT_COUNT-1 );

		dest_conversion_groups[ group_idx ] |= (1 << i);
	}

	/* Build a bit-string of enabled destinations across all channel types */
	all_enabled_dests = 0;
	for ( i = BASE_CHANNEL_COUNT; i-- > 0 ; )  /* See Note at top of file */
	{
		const basep_channel_type_config *channel_config;
		u32 dests_enabled;

		channel_config = basep_channel_get_config( (base_channel_type)i );

		dests_enabled = channel_config->destinations_enabled;

		all_enabled_dests |= dests_enabled;

		/*
		 * Handle any destination-specific data
		 * Due to the order of enumeration, this results in the dest-specific
		 * data being set to that of the last channel to require such data.
		 */

		if ( 0 != (dests_enabled & BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_FILE )) )
		{
			phys_destinations->file_dest_path = channel_config->path;
		}
		if ( 0 != (dests_enabled & BASEP_CHANNEL_DESTINATION_BIT( BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC )) )
		{
			phys_destinations->channel_type = (base_channel_type)i;
		}

	}

	phys_destinations->dests_enabled = shared_dests & all_enabled_dests;
	
	/* Success */
}

/*
 * Open a destination, handling its dynamic nature. Doesn't handle the static
 * parts, such as mutex allocation.
 */
STATIC mali_error open_a_dest( basep_channel_destinations_info * phys_destinations,
							   basep_channel_destination dest_idx )
{
	mali_error err = MALI_ERROR_NONE;
	basep_destination *current_dest;

	BDBG_ASSERT_POINTER( phys_destinations );

	current_dest = &phys_destinations->dests[ dest_idx ];

	/* MIDBASE-107: Use function pointers for standardised 'open', 'close', 'write' methods,
	 * instead of slower switch statement */
	switch ( dest_idx )
	{
		case BASEP_CHANNEL_DESTINATION_STDOUT:
			/* This can't fail: */
			current_dest->u.s.stream_ptr = STDLIB_OUTPUT_STREAM();			
			break;

		case BASEP_CHANNEL_DESTINATION_STDERR:
			/* This can't fail: */
			current_dest->u.s.stream_ptr = STDLIB_ERROR_STREAM();
			break;

		case BASEP_CHANNEL_DESTINATION_FILE:
			{
				stdlib_errcode stdlib_err;
				current_dest->u.s.stream_ptr = &current_dest->u.s.stream;
				stdlib_err = stdlib_fopen( current_dest->u.s.stream_ptr,
										   STDLIB_DIRECTORY_RESULTS,
										   phys_destinations->file_dest_path,
										   STDLIB_FILE_MODE_WRITE );

				if ( STDLIB_ERR_OK != stdlib_err )
				{
					/* indicate failure */
					/* MIDBASE-109: unify erroring */
					err = MALI_ERROR_FUNCTION_FAILED;
				}
			}

			break;

		case BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC:
			err = basep_channel_platform_destination_open( &current_dest->u.plat_dest,
														   phys_destinations->channel_type );
														   
			break;

		default:
			BDBG_ASSERT_MSG( MALI_FALSE, "Unreachable" );
			break;
	}

	return err;
}

STATIC void close_a_dest( basep_channel_destinations_info * phys_destinations,
						  basep_channel_destination dest_idx )
{
	basep_destination *current_dest;

	BDBG_ASSERT_POINTER( phys_destinations );

	current_dest = &phys_destinations->dests[ dest_idx ];

	/* MIDBASE-107: Use function pointers for standardised 'open', 'close', 'write' methods,
	 * instead of slower switch statement */
	switch ( dest_idx )
	{
		/* Just flush these: */
		case BASEP_CHANNEL_DESTINATION_STDOUT:
		case BASEP_CHANNEL_DESTINATION_STDERR:
			{
				stdlib_errcode stdlib_err;
				stdlib_err = stdlib_fflush( current_dest->u.s.stream_ptr );

				BDBG_PRINT_WARN_ON( STDLIB_ERR_OK != stdlib_err, CDBG_BASE,
									"Failed to flush stdout/stderr on close - some stream data may be lost" );
			}
			
			break;

		case BASEP_CHANNEL_DESTINATION_FILE:
			{
				stdlib_errcode stdlib_err;
				stdlib_err = stdlib_fclose( current_dest->u.s.stream_ptr );

				BDBG_PRINT_WARN_ON( STDLIB_ERR_OK != stdlib_err, CDBG_BASE,
									"Error during close file stream - some stream data may be lost" );
			}

			break;

		case BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC:
			basep_channel_platform_destination_close( &current_dest->u.plat_dest );
														   
			break;

		default:
			BDBG_ASSERT_MSG( MALI_FALSE, "Unreachable" );
			break;
	}
}

/*
 * phys_destinations is [in,out] - must initialize with destination-specific
 * data, such as file_dest_path.
 *
 * phys_destinations->dests_enabled is [in,out] - input tells us what to init,
 * output tells us what was successfully init
 */
STATIC void init_destinations( basep_channel_destinations_info *phys_destinations,
							   const basep_channel_destination_config *dest_config_array )
{
	u32 dests_success_init = 0;
	int i;
	u32 current_dest_bit;
	u32 dests_to_access;

	BDBG_ASSERT_POINTER( phys_destinations );
	BDBG_ASSERT_POINTER( dest_config_array );

	dests_to_access = phys_destinations->dests_enabled;

	/* MIDBASE-108: Optimize loop start with stdlib_clz */
	for ( i = BASEP_CHANNEL_DESTINATION_COUNT, current_dest_bit = 1<<(i-1);
		  i-- > 0;  /* See Note at top of file */
		  current_dest_bit >>= 1 )
	{
		if ( 0 != (dests_to_access & current_dest_bit) )
		{
			mali_error current_dest_err = MALI_ERROR_NONE;
			u32 dest_flags = dest_config_array[ i ].flags;

			/* Two stage initialization: */

			/* 1: Open the actual destination */
			current_dest_err = open_a_dest( phys_destinations, (basep_channel_destination)i );

			/* 2: If it needs a mutex, Initialize it (providing no failures so far) */
			if ( MALI_ERROR_NONE == current_dest_err &&
				 0 != (dest_flags & BASEP_CHANNEL_DESTINATION_FLAG_MUTEX_NEEDED) )
			{
				basep_destination *current_dest = &phys_destinations->dests[ i ];
				osu_errcode osu_err;

				osu_err = osu_mutex_init( &current_dest->mutex, OSU_LOCK_ORDER_BASE_CHANNELS_DESTINATIONS );
				if ( OSU_ERR_OK != osu_err )
				{
					/* On error, rollback any destination opening */
					close_a_dest( phys_destinations, (basep_channel_destination)i );

					current_dest_err = MALI_ERROR_FUNCTION_FAILED;
				}				
			}

			/* Finally, store whether success occured for this dest */
			if ( MALI_ERROR_NONE == current_dest_err )
			{
				dests_success_init |= current_dest_bit;
			}
		}
	}

	/* Overwrite the enabled dests with those that succeded */
	phys_destinations->dests_enabled = dests_success_init;
}


STATIC void term_destinations( basep_channel_destinations_info *phys_destinations )
{
	int i;
	u32 current_dest_bit;
	u32 dests_to_access;
	const basep_channel_destination_config *dest_config_array ;

	BDBG_ASSERT_POINTER( phys_destinations );

	/* This call should efficiently inline: */
	dest_config_array = basep_channel_destination_get_configs();

	dests_to_access = phys_destinations->dests_enabled;

	/* MIDBASE-108: Optimize loop start with stdlib_clz */
	for ( i = BASEP_CHANNEL_DESTINATION_COUNT, current_dest_bit = 1<<(i-1);
		  i-- > 0;  /* See Note at top of file */
		  current_dest_bit >>= 1 )
	{
		if ( 0 != (dests_to_access & current_dest_bit) )
		{
			basep_destination *current_dest = &phys_destinations->dests[ i ];
			u32 dest_flags = dest_config_array[ i ].flags;

			if ( 0 != (dest_flags & BASEP_CHANNEL_DESTINATION_FLAG_MUTEX_NEEDED) )
			{
				osu_mutex_term( &current_dest->mutex );
			}
			close_a_dest( phys_destinations, (basep_channel_destination)i );
		}
	}

	phys_destinations->dests_enabled = 0;
}

STATIC mali_error write_to_channels( basep_channel_destinations_info *dest_info,
									 u32 dests_to_access,
									 const char *destbuf,
									 u32 destbuf_size )
{
	int i;
	u32 current_dest_bit;

	/* This will contain the first error that occurred */
	mali_error first_err = MALI_ERROR_NONE;
	const basep_channel_destination_config *dest_config_array;

	BDBG_ASSERT_POINTER( dest_info );
	BDBG_ASSERT_POINTER( destbuf );

	/* For some optional extra safety, ensure that the destinations to print on are enabled */
	BDBG_ASSERT( dests_to_access == (dests_to_access & dest_info->dests_enabled ) );
	
	/* This is a cheap-inline, and will give better d-cache usage */
	dest_config_array = basep_channel_destination_get_configs();
	
	/* MIDBASE-108: Optimize loop start with stdlib_clz */
	for ( i = BASEP_CHANNEL_DESTINATION_COUNT, current_dest_bit = 1<<(i-1);
		  i-- > 0;  /* See Note at top of file */
		  current_dest_bit >>= 1 )
	{
		if ( 0 != (dests_to_access & current_dest_bit) )
		{
			basep_destination *current_dest;
			u32 needs_mutex_flag = ( dest_config_array[i].flags & BASEP_CHANNEL_DESTINATION_FLAG_SHARED );

			current_dest = &dest_info->dests[ i ];

			if ( 0 != needs_mutex_flag )
			{
				osu_mutex_lock( &current_dest->mutex );
			}

			/* MIDBASE-107: Use function pointers for standardised 'open', 'close', 'write' methods,
			 * instead of slower switch statement */
			switch ( (basep_channel_destination)i )
			{
				case BASEP_CHANNEL_DESTINATION_STDOUT:
				case BASEP_CHANNEL_DESTINATION_STDERR:
				case BASEP_CHANNEL_DESTINATION_FILE:
					{
						size_t bytes_written;
						u32 length_bytes = destbuf_size - 1; /* Exclude NULL terminator */
						stdlib_errcode stdlib_err;

						bytes_written = stdlib_fwrite( destbuf, 1, length_bytes, current_dest->u.s.stream_ptr );
						if ( bytes_written != length_bytes && first_err == MALI_ERROR_NONE )
						{
							/* Write failed. No way of distinguishing a real error from needing
							 * a retry after no bytes written, so just report an error for later */
							first_err = MALI_ERROR_FUNCTION_FAILED;
						}
						stdlib_err = stdlib_fflush( current_dest->u.s.stream_ptr );

						if ( STDLIB_ERR_OK != stdlib_err && first_err == MALI_ERROR_NONE )
						{
							/* Flush failed (possibly delayed write failed). */
							first_err = MALI_ERROR_FUNCTION_FAILED;
						}

					}
					break;

				case BASEP_CHANNEL_DESTINATION_PLATFORM_SPECIFIC:
					{
						mali_error plat_err;
						/* Pass in size (including NULL terminator), not string length, as
						 * required by function contract */
						plat_err = basep_channel_platform_destination_write( &current_dest->u.plat_dest,
																			 destbuf,
																			 destbuf_size );
						
						if ( first_err == MALI_ERROR_NONE  )
						{
							first_err = plat_err;
						}
					}
														   
					break;

				default:
					BDBG_ASSERT_MSG( MALI_FALSE, "Unreachable" );
					break;
			}
			
			if ( 0 != needs_mutex_flag )
			{
				osu_mutex_unlock( &current_dest->mutex );
			}

		}
	}
	return first_err;
}


STATIC mali_error channel_write_worker( basep_channel_conversion_args *conv_args,
										basep_channel_destinations_info *dest_info,
										u32 current_shared_newline_group,
										u32 current_per_channel_newline_group )
{
	u32 destbuf_size;
	char *destbuf;

	mali_error err1;
	mali_error err2;

	/* Do the conversion */
#if 0 != CONFIG_CHANNEL_DISABLE_REDUNDANT_PATHS
	if ( 0 == (conv_args.flags & BASEP_NEWLINE_CONVERSION_FLAGS_MASK) )
	{
		destbuf = conv_args->src;
		destbuf_size = conv_args->src_size;
	}
	else
#endif
	{
		destbuf = conv_args->dest;
		destbuf_size = basep_channel_convert_newlines( conv_args );	
	}
	
	/* Now write out destbuf to all the channels */

	/*
	 * Caller has determined that at least one of {current_shared_newline_group,
	 * current_per_channel_newline_group} was non-zero, and so there is useful
	 * work to do
	 */
	err1 = write_to_channels( &shared_destinations, current_shared_newline_group, destbuf, destbuf_size );
	err2 = write_to_channels( dest_info, current_per_channel_newline_group, destbuf, destbuf_size );

	/* Return the first error */
	if ( MALI_ERROR_NONE == err1 )
	{
		return err1;
	}
	
	return err2;
}

/*
 * Public Functions
 */
mali_error base_channel_init( void )
{
	const basep_channel_destination_config *dest_config_array;

	u32 requested_shared_dests;
	
	mali_error err = MALI_ERROR_NONE;

	u32 dests_success; /* Bitstring of dests that succeeded to init */

	dest_config_array = basep_channel_destination_get_configs();

	prepare_shared_dests( &shared_destinations, dest_config_array );
	requested_shared_dests = shared_destinations.dests_enabled;

	/* 
	 * get_enabled_shared_dests has setup any dest-specific data, ready for
	 * init_destinations() 
	 */

	/* Initialize each destination */
	init_destinations( &shared_destinations, dest_config_array );
	dests_success = shared_destinations.dests_enabled;

	/* 
	 * If those that succeeded aren't the ones we got, then indicate an error.
	 * This is because code in the base_channel_open relies on the *enabled*
	 * shared destinations to determine whether a destination is shared or not.
	 */
	if ( dests_success != requested_shared_dests )
	{
		BDBG_PRINT_WARN( CDBG_BASE, "Initing shared dests 0x%x: failed to init 0x%x, ",
						 requested_shared_dests,
						 requested_shared_dests & (~dests_success) );

		term_destinations( &shared_destinations );
		err = MALI_ERROR_FUNCTION_FAILED;
	}

	return err;
}

void base_channel_term( void )
{
	term_destinations( &shared_destinations );
}


mali_error base_channel_open( base_channel * CONST channel, base_channel_type type )
{
	const basep_channel_type_config *channel_config;
	const basep_channel_destination_config *dest_config_array;
	u32 dest_enabled;
	u32 shared_dests;
	u32 per_channel_dests;
	u32 msg_size;
	u32 convbuf_size;

	basep_channel_destinations_info *channel_dest_info;
	mali_error convbuf_err;

	/* Bitstring of dests that succeeded to init. When 0, no dests to cleanup */
	u32 dests_success;

	/* This is used to determine cleanup */
	mali_error ringbuf_err;

	BDBG_ASSERT_POINTER( channel );
	BDBG_ASSERT_RANGE( type, 0, BASE_CHANNEL_COUNT-1 );

	/* Initialize any values necessary for the error-path */
	dests_success = 0;
	ringbuf_err = MALI_ERROR_FUNCTION_FAILED;
	channel->basep_internal_struct.lcbuf_size = 0;

	/* Obtain the config, and the destinations */
	channel_config = basep_channel_get_config( type );

	dest_config_array = basep_channel_destination_get_configs();
	
	dest_enabled = channel_config->destinations_enabled;

	/* Split dest_enabled into shared dests, and per-channel dests */
	shared_dests = dest_enabled & shared_destinations.dests_enabled;
	per_channel_dests = dest_enabled & (~shared_destinations.dests_enabled);


	/* Prepare the channel data for initialization; just the per_channel_dests */
	channel_dest_info = &channel->basep_internal_struct.destinations;

	channel_dest_info->dests_enabled = per_channel_dests;
	channel_dest_info->file_dest_path = channel_config->path;
	channel_dest_info->channel_type = type;

	init_destinations( channel_dest_info, dest_config_array );

	/* dests_success used to determine cleanup action */
	dests_success = channel_dest_info->dests_enabled;

	if ( dests_success != per_channel_dests )
	{
		BDBG_PRINT_WARN( CDBG_BASE, "Initing dest bitpattern 0x%x for channel %d: failed dests bitpattern is 0x%x",
						 per_channel_dests,
						 type,
						 per_channel_dests & (~dests_success));

		goto cleanup_err;
	}
	channel->basep_internal_struct.shared_dests_in_use = shared_dests;
	/*
	 * Channel's destinations now initialized
	 */

	/*
	 * Initialize the Ringbuffer
	 */

	msg_size = channel_config->max_size_of_message;
	/* ringbuf_err used for cleanup actions */
	ringbuf_err = basep_emptying_ringbuf_init( &channel->basep_internal_struct.ringbuf,
											   msg_size,
											   channel_config->messages_to_keep_log2,
											   type );

	if ( MALI_ERROR_NONE != ringbuf_err )
	{
		goto cleanup_err;
	}
	channel->basep_internal_struct.cached_atom_size = msg_size;

	/*
	 * Newline conversion buffer, if required
	 */
	convbuf_size = channel_config->large_conversion_size;
	convbuf_err = basep_alloc_newline_conversion_buffer( channel, convbuf_size );
	if ( MALI_ERROR_NONE != convbuf_err )
	{
		goto cleanup_err;
	}
	channel->basep_internal_struct.lcbuf_size = convbuf_size;

	/* Initialization complete - success */

	return MALI_ERROR_NONE;
 cleanup_err:
	/* 
	 * Initialization of channel->basep_internal_struct.lcbuf_size to zero
	 * allows us to call this directly 
	 */
	basep_free_newline_conversion_buffer( channel );

	if ( MALI_ERROR_NONE == ringbuf_err )
	{
		basep_emptying_ringbuf_term( &channel->basep_internal_struct.ringbuf );
	}

	if ( 0 != dests_success )
	{
		term_destinations( &channel->basep_internal_struct.destinations );
	}

	return MALI_ERROR_FUNCTION_FAILED;
}


void base_channel_close( base_channel *channel )
{
	BDBG_ASSERT_POINTER( channel );

	basep_free_newline_conversion_buffer( channel );
	basep_emptying_ringbuf_term( &channel->basep_internal_struct.ringbuf );
	term_destinations( &channel->basep_internal_struct.destinations );
}


char *base_channel_lock( base_channel_lock_ctx * CONST ctx, u32 * CONST size, base_channel *channel )
{
	cutils_ring_atom* atom;

 	BDBG_ASSERT_POINTER( channel );
 	BDBG_ASSERT_POINTER( ctx );

	/* Obtain the ringbuffer atom */
	atom = basep_emptying_ringbuf_write_lock( &channel->basep_internal_struct.ringbuf );

	/* Fill the lock ctx structure */
	ctx->basep_internal_struct.channel = channel;
	ctx->basep_internal_struct.atom = atom;

	/* The size of the atom is that of the channel's message size */
	*size = channel->basep_internal_struct.cached_atom_size;

	return atom->data;
}

mali_error base_channel_unlock( base_channel_lock_ctx * ctx, s32 chars_used )
{
	int i;
	base_channel *channel;
	basep_channel_conversion_args conv_args;
	basep_channel_destinations_info *dest_info;
	u32 shared_dests_in_use;
	u32 per_channel_dests;
	u32 buffer_size;
	char * src_data;

	mali_error first_error = MALI_ERROR_NONE;

	BDBG_ASSERT_POINTER( ctx );
	
	channel = ctx->basep_internal_struct.channel;
	dest_info = &channel->basep_internal_struct.destinations;
	buffer_size = channel->basep_internal_struct.cached_atom_size;
	src_data = ctx->basep_internal_struct.atom->data;

	BDBG_ASSERT_LEQ( 1, buffer_size );
	BDBG_ASSERT_LEQ( BDBGP_TRUNCATION_MESSAGE_SIZE, buffer_size );
	BDBG_ASSERT_LEQ( BDBGP_ERROR_MESSAGE_SIZE, buffer_size );

	
	/* 
	 * The following can overwrite data in the atom, which is fine because the
	 * caller is no longer writing to it
	 */
	basep_correct_snprintf_for_error( src_data, buffer_size, &chars_used );

	/* 
	 * Certain platforms will enforce a newline for you if you don't, so we
	 * do this ourseleves so that the messages look the same on any platform.
	 *
	 * This may also occur during the newline-conversion phase, because newline
	 * conversion might truncate the message.
	 */
	basep_ensure_message_ends_in_newline( src_data, buffer_size, &chars_used );

	/* chars_used now in range. Cast is safe due to above checks */
	conv_args.src_size = (u32)(chars_used) + 1;
	conv_args.src = src_data;

	shared_dests_in_use = channel->basep_internal_struct.shared_dests_in_use;
	per_channel_dests = dest_info->dests_enabled;

	/* Divide up the destinations into their newline-equivalence groups */
	for ( i = 0 ; i < BASEP_CHANNELS_CONVERSION_FORMAT_COUNT; ++ i )
	{
		u32 current_shared_newline_group = shared_dests_in_use;
		u32 current_per_channel_newline_group = per_channel_dests; 

		u32 current_newline_group = dest_conversion_groups[ i ];

		conv_args.flags = i;

		current_shared_newline_group &= current_newline_group;
		current_per_channel_newline_group &= current_newline_group;

		/* Only proceed if there's anything *enabled*, and in the newline group */
		if ( 0 != current_shared_newline_group || 0 != current_per_channel_newline_group )
		{
			mali_error current_error;

			if ( 0 == channel->basep_internal_struct.lcbuf_size )
			{
				/* Use stack's conversion buffer */
				char conv_buf[CONFIG_CHANNEL_CONVERSION_BUFFER_SIZE];

				conv_args.dest = &conv_buf[0];
				conv_args.dest_size = CONFIG_CHANNEL_CONVERSION_BUFFER_SIZE;

				current_error = channel_write_worker( &conv_args,
													  dest_info,
													  current_shared_newline_group,
													  current_per_channel_newline_group );
			}
			else
			{
				/* Use large conversion buffer */
				char *conv_buf = basep_lock_newline_conversion_buffer( channel );

				conv_args.dest = &conv_buf[0];
				conv_args.dest_size = channel->basep_internal_struct.lcbuf_size;

				current_error = channel_write_worker( &conv_args,
													  dest_info,
													  current_shared_newline_group,
													  current_per_channel_newline_group );

				basep_unlock_newline_conversion_buffer( channel );
			}

			if ( MALI_ERROR_NONE == first_error )
			{
				first_error = current_error;
			}
		}
	}

	/* Finished writing out, now unlock the ringbuffer */
	basep_emptying_ringbuf_write_unlock( &channel->basep_internal_struct.ringbuf,
										 ctx->basep_internal_struct.atom );

	/* Nothing to de-init in the ctx */

	return first_error;
}
