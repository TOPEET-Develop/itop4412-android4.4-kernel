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
 * mali_base_gpuprops_priv.h includes base/mali_base.h: General base
 * definitions, midg defines, and plat config defines:
 */
#include "mali_base_gpuprops_priv.h"

#include <cdbg/mali_cdbg.h>
#include <stdlib/mali_stdlib.h>

/*
 * Private definitions 
 */

/*
 * The following 'Dummy' defines are configurable:
 */
#define BASEP_DUMMY_GPU_SPEED_MHZ 123

#ifndef BASEP_DUMMY_GPU_CORES
/* Mali-T600 allows 1,2,3,4,6,8 */
#define BASEP_DUMMY_GPU_CORES 4
#endif

#ifndef BASEP_DUMMY_GPU_PC_SIZE_LOG2
/* This setting required for FPGA. It also works for 'real' Mali-T600s, but is
 * sub-optimal */
#define BASEP_DUMMY_GPU_PC_SIZE_LOG2 16U
#endif /* BASEP_DUMMY_GPU_PC_SIZE_LOG2 */


/* job dispatch only supports s8 for priority */
#define BASEP_DUMMY_DEFAULT_JOB_PRIORITY_FOR_COREGROUP ((u16)0)
#define BASEP_DUMMY_MIN_JOB_PRIORITY_FOR_COREGROUP ((u16)0)

/* 
 * Mali-T600 allows:
 * 1 core: 32kB
 * 2 cores: 64kB, 128kB
 * 3,4,6,8 cores: 128kB, 256 kB
 */
#if 1 == BASEP_DUMMY_GPU_CORES
#define BASEP_DUMMY_GPU_L2_CACHE_SIZE_LOG2 0x0F /* ==15, 2^15 == 32K */
#else
#define BASEP_DUMMY_GPU_L2_CACHE_SIZE_LOG2 0x11 /* ==17, 2^17 == 128K */
#endif

/*
 * The following defines are fixed for the Mali-T600
 */

/* Mali-T600 only allows 64 bytes */
#define BASEP_T600_L2_LINE_SIZE_LOG2 6U /* 2^6 == 64 */

/* Mali-T600 has no L3 */
#define BASEP_T600_L3_LINE_SIZE_LOG2 0U
#define BASEP_T600_L3_CACHE_SIZE_LOG2 0U

/* Mali-T600 Tiler Bin size is always 2^9 (TILER_FEATURES reset value) */
#define BASEP_T600_TILER_BIN_SIZE 512

/* Mali-T600 Tiler Max Active Levels is always 8 (TILER_FEATURES reset value) */
#define BASEP_T600_TILER_MAX_ACTIVE_LEVELS 8U

/* Mali-T600 is always Core-group coherent, but never core-supergroup coherent */
#define BASEP_T600_CORE_GROUP_COHERENT_BOOL MALI_TRUE
#define BASEP_T600_CORE_SUPERGROUP_COHERENT_BOOL MALI_FALSE

#define TEXTURE_FEATURES_0 0x000FFFFEu /* Formats 1..19 */
#define TEXTURE_FEATURES_1 0x0000FFFFu /* Formats 32..47 */
#define TEXTURE_FEATURES_2 0x9F81FFFFu /* Formats 64..80, 87..92, 95 */

/*
 * Function prototypes
 */
STATIC mali_error basep_gpu_props_construct_coherency( struct mali_base_gpu_coherent_group_info * const group_info,
													   u32 group_info_size,
													   base_context *ctx ) CHECK_RESULT;

STATIC u32 get_num_core_groups( base_context *ctx );


/*
 * Static structures
 */

STATIC CONST struct mali_base_gpu_props basep_gpu_props_template =
{
	/* core props */
	{
		MIDG_PRODUCT_MALI_T600, /* product_id */
		CONFIG_GPU_REVISION_MINOR, /* minor_revision */
		CONFIG_GPU_REVISION_MAJOR, /* major_revision */
		BASEP_DUMMY_GPU_SPEED_MHZ,
		BASEP_DUMMY_GPU_PC_SIZE_LOG2,
		/* texture_features[] */
		{
			TEXTURE_FEATURES_0,
			TEXTURE_FEATURES_1,
			TEXTURE_FEATURES_2
		},
		0u, /* gpu_available_memory_size */
		CONFIG_GPU_VERSION_STRING
	},

	/* l2_props */
	{
		BASEP_T600_L2_LINE_SIZE_LOG2,
		BASEP_DUMMY_GPU_L2_CACHE_SIZE_LOG2
	},

	/* l3_props */
	{
		BASEP_T600_L3_LINE_SIZE_LOG2,
		BASEP_T600_L3_CACHE_SIZE_LOG2
	},

	/* tiler_props */
	{
		BASEP_T600_TILER_BIN_SIZE,
		BASEP_T600_TILER_MAX_ACTIVE_LEVELS
	},

	/* raw_props */
	/* 
	 * NOTE: This information is only for passing out to Mali Tools, and should not be
	 * read directly by the driver. For this reason, they are all zero at this stage
	 */
	{
		0ULL, /* u64 shader_present; */
		0ULL, /* u64 tiler_present; */
		0ULL, /* u64 l2_present; */
		0ULL, /* u64 l3_present; */

		0U, /* midg_cache_features l2_features; */
		0U, /* midg_cache_features l3_features; */
		0U, /* midg_mem_features mem_features; */
		0U, /* midg_mmu_features mmu_features; */

		0U, /* midg_as_present as_present; */

		0U, /* u32 js_present; */

		/* js_features[MIDG_MAX_JOB_SLOTS]; */
		{
			0U,
			0U,
			0U,
			0U,

			0U,
			0U,
			0U,
			0U,

			0U,
			0U,
			0U,
			0U,

			0U,
			0U,
			0U,
			0U,			
		},
		0U /* midg_tiler_features tiler_features; */
	},
	
	/* coherency_info */
	/* Dummy coherency information required just to initialize the structure */
	{
		0U, /* num_groups */
		0U, /* num_core_groups */
		0U, /* coherency */
		/* array of 1 struct mali_base_gpu_coherent_group follows */
		{
			/* dummy group follows */
			{
				0ULL,
				0U,
				0U
			}
		}
	}
};


STATIC u32 get_num_core_groups( base_context *ctx )
{
	CDBG_ASSERT_POINTER( ctx );

	UNUSED( ctx );

	switch ( BASEP_DUMMY_GPU_CORES )
	{
		case 1:
		case 2:
		case 3:
		case 4:
			return 1;

		case 6:
		case 8:
			return 2;

		default:
			CDBG_ASSERT_MSG( MALI_FALSE, "Unreachable\n" );
			break;
	}

	return 0;
}

/*
 * Fill the coherency information for Mali-T600 cores
 *
 * group_info must point to storage for a mali_base_gpu_coherent_group_info
 * structure which is up to group_info_size bytes in length.
 */
STATIC mali_error basep_gpu_props_construct_coherency( struct mali_base_gpu_coherent_group_info * const group_info,
													   u32 group_info_size,
													   base_context *ctx )
{
	u8 *end_of_mem_ptr; /* For debug checks */
	struct mali_base_gpu_coherent_group *current_group;
	u32 num_groups;

	CDBG_ASSERT_POINTER( group_info );
	CDBG_ASSERT_POINTER( ctx );

	end_of_mem_ptr = ((u8*)group_info) + group_info_size;

	UNUSED( ctx );

	/* 
	 * This assert assumes at least one coherent group, and structure padding
	 * has been allocated for the single group case
	 */
	CDBG_ASSERT_LEQ( (uintptr_t)(group_info+1), (uintptr_t)end_of_mem_ptr );

	num_groups = basep_gpu_props_get_num_coherent_groups( ctx );

	group_info->num_groups = num_groups;
	group_info->num_core_groups = get_num_core_groups( ctx );

	/* Set coherency, using data structure builder functions. Must be
	 * initialized to zero first. */
	STDLIB_MEMSET( &group_info->coherency, 0, sizeof(group_info->coherency) );
	midg_mem_features_set_coherent_core_group( &group_info->coherency, 
											   BASEP_T600_CORE_GROUP_COHERENT_BOOL );
	midg_mem_features_set_coherence_supergroup( &group_info->coherency,
												BASEP_T600_CORE_SUPERGROUP_COHERENT_BOOL );


	current_group = &group_info->group[0];
	
	switch ( BASEP_DUMMY_GPU_CORES )
	{
		case 1:
		case 2:
		case 3:
		case 4:
			CDBG_ASSERT_LEQ( (uintptr_t)(current_group+1), (uintptr_t)end_of_mem_ptr );
			current_group->core_mask = (1ULL << BASEP_DUMMY_GPU_CORES) - 1ULL;
			current_group->num_cores = BASEP_DUMMY_GPU_CORES;
			current_group->priority_required = BASEP_DUMMY_DEFAULT_JOB_PRIORITY_FOR_COREGROUP;
			/* NOTE: 1 L2 cache present */
			
			break;

		case 6:
		case 8:
			{
				u32 cores_per_group = BASEP_DUMMY_GPU_CORES/2;

				CDBG_ASSERT_LEQ( (uintptr_t)(current_group+1), (uintptr_t)end_of_mem_ptr );
				current_group->core_mask = (1ULL << cores_per_group) - 1ULL;
				current_group->num_cores = cores_per_group;
				current_group->priority_required = BASEP_DUMMY_DEFAULT_JOB_PRIORITY_FOR_COREGROUP;

				++current_group;

				/*
				 * 6-core systems have a 'gap' in the core mask, meaning that
				 * the 2nd coregroup starts at offset 4.
				 * 8-core systems naturally have the 2nd coregroup at offset 4 
				 */
				CDBG_ASSERT_LEQ( (uintptr_t)(current_group+1), (uintptr_t)end_of_mem_ptr );
				current_group->core_mask = ((1ULL << cores_per_group) - 1ULL) << 4;
				current_group->num_cores = cores_per_group;
				current_group->priority_required = BASEP_DUMMY_MIN_JOB_PRIORITY_FOR_COREGROUP;

				/* NOTE: 2 L2 caches present */
			}
			break;

		default:
			CDBG_ASSERT_MSG( MALI_FALSE, "Unreachable\n" );
			break;
	}

	/* groups_size only used for debug checks */
	UNUSED( end_of_mem_ptr );

	return MALI_ERROR_NONE;
}

STATIC u64 get_available_gpu_memory(  base_context *ctx )
{
	osu_errcode err;
	osu_cpu_props props;
	CDBG_ASSERT_POINTER( ctx );

	UNUSED( ctx );

	/* Assumes all OS Memory. Does not account for dedicated allocators */
	err = osu_cpu_props_get( &props );

	if ( err != OSU_ERR_OK )
	{
		CDBG_PRINT_WARN( CDBG_BASE, "osu_cpu_props_get() failed, available gpu memory will be reported as 0" );
		return 0;
	}

	return props.available_memory_size;
}

/*
 * Protected functions
 */

u32 basep_gpu_props_get_num_coherent_groups( base_context *ctx )
{
	CDBG_ASSERT_POINTER( ctx );

	UNUSED( ctx );

	switch ( BASEP_DUMMY_GPU_CORES )
	{
		case 1:
		case 2:
		case 3:
		case 4:
			return 1;

		case 6:
		case 8:
			return 2;

		default:
			CDBG_ASSERT_MSG( MALI_FALSE, "Unreachable\n" );
			break;
	}

	return 0;
}

mali_error basep_fill_gpu_props( struct mali_base_gpu_props *const gpu_props,
								 u32 props_size,
								 base_context *ctx )
{
	mali_error err;

	CDBG_ASSERT_POINTER( gpu_props );
	CDBG_ASSERT_POINTER( ctx );


	/* Copy everything but the coherency information */
	STDLIB_MEMCPY( gpu_props, &basep_gpu_props_template, offsetof(struct mali_base_gpu_props, coherency_info) );

	/* Modify members that need an update */
	gpu_props->core_props.gpu_available_memory_size = get_available_gpu_memory( ctx );

	/* Construct the Coherency information */
	
	err = basep_gpu_props_construct_coherency( &gpu_props->coherency_info,
											   props_size-offsetof(struct mali_base_gpu_props, coherency_info),
											   ctx );
	return err;
}

/*
 * Public functions
 */
const struct mali_base_gpu_props *_mali_base_get_gpu_props( base_context *ctx )
{
	CDBG_ASSERT_POINTER( ctx );
	/* Just return the information cached in the base ctx */
	return ctx->gpu_props;
}
