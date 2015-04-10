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
 * @file mali_base_gpuprops.h
 * Defines the user-side interaction with the Base Driver Property Query system
 */


#ifndef _BASE_GPUPROPS_H_
#define _BASE_GPUPROPS_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @page page_base_user_api_gpuprops User-side Base GPU Property Query API
 *
 * The User-side Base GPU Property Query API encapsulates a number of
 * sub-modules:
 *
 * - @ref base_user_api_gpuprops_dyn "Dynamic GPU Properties"
 * - @ref base_plat_config_gpuprops "Base Platform Config GPU Properties"
 * - @ref midg_gpuprops_static "Midgard Compile-time GPU Properties"
 *
 * The compile-time properties (Platform Config, Midgard Compile-time
 * properties) are exposed as pre-processor macros.
 *
 * Complementing the compile-time properties are the Dynamic GPU
 * Properties, which act as a conduit for the Midgard Configuration
 * Discovery.
 *
 * In general, the dynamic properties are present to verify that the platform
 * has been configured correctly with the right set of Platform Config
 * Compile-time Properties.
 *
 * As a consistant guide across the entire DDK, the choice for dynamic or
 * compile-time should consider the following, in order:
 * -# Can the code be written so that it doesn't need to know the
 * implementation limits at all?
 * -# If you need the limits, get the information from the Dynamic Property
 * lookup. This should be done once as you fetch the context, and then cached
 * as part of the context data structure, so it's cheap to access.
 * -# If there's a clear and arguable inefficiency in using Dynamic Properties,
 * then use a Compile-Time Property (Platform Config, or Midgard Compile-time
 * property). Examples of where this might be sensible follow:
 *  - Part of a critical inner-loop
 *  - Frequent re-use throughout the driver, causing significant extra load
 * instructions or control flow that would be worthwhile optimizing out.
 * 
 * We cannot provide an exhaustive set of examples, neither can we provide a
 * rule for every possible situation. Use common sense, and think about: what
 * the rest of the driver will be doing; how the compiler might represent the
 * value if it is a compile-time constant; whether an OEM shipping multiple
 * devices would benefit much more from a single DDK binary, instead of
 * insignificant micro-optimizations.
 *
 * @section sec_base_user_api_gpuprops_dyn Dynamic GPU Properties
 *
 * Dynamic GPU properties are presented in two sets:
 * -# the commonly used properties in @ref mali_base_gpu_props, which have been
 * unpacked from GPU register bitfields.
 * -# The full set of raw, unprocessed properties in @ref midg_raw_gpu_props
 * (also a member of @ref mali_base_gpu_props). All of these are presented in
 * the packed form, as presented by the GPU  registers themselves.
 *
 * @usecase The raw properties in @ref midg_raw_gpu_props are necessary to
 * allow a user of the Mali Tools (e.g. PAT) to determine "Why is this device
 * behaving differently?". In this case, all information about the
 * configuration is potentially useful, but it <b>does not need to be processed
 * by the driver</b>. Instead, the raw registers can be processed by the Mali
 * Tools software on the host PC.
 *
 * The properties returned extend the Midgard Configuration Discovery
 * registers. For example, GPU clock speed is not specified in the Midgard
 * Architecture, but is <b>necessary for OpenCL's clGetDeviceInfo() function</b>.
 *
 * The GPU properties are obtained by a call to
 * _mali_base_get_gpu_props(). This simply returns a pointer to a const
 * mali_base_gpu_props structure. It is constant for the life of a base
 * context. Multiple calls to _mali_base_get_gpu_props() to a base context
 * return the same pointer to a constant structure. This avoids cache pollution
 * of the common data.
 *
 * This pointer must not be freed, because it does not point to the start of a
 * region allocated by the memory allocator; instead, just close the @ref
 * base_context.
 *
 *
 * @section sec_base_user_api_gpuprops_config Platform Config Compile-time Properties
 * 
 * The Platform Config File sets up gpu properties that are specific to a
 * certain platform. Properties that are 'Implementation Defined' in the
 * Midgard Architecture spec are placed here.
 *
 * @note Reference configurations are be provided for Midgard Implementations, such as
 * Mali-T600. The customer need not repeat this information, and can select one of
 * these reference configurations. For example, VA_BITS, PA_BITS and the
 * maximum number of samples per pixel might vary between Midgard Implementations, but
 * \b not for platforms using the \b same Midgard Implementation. This are placed in
 * the reference configuration files.
 *
 * The System Integrator creates the following structure:
 * - platform_XYZ
 * - platform_XYZ/plat
 * - platform_XYZ/plat/plat_config.h
 * 
 * They then edit plat_config.h, using the example plat_config.h files as a
 * guide.
 *
 * At the very least, the customer must set @ref CONFIG_GPU_CORE_TYPE, and will
 * receive a helpful \#error message if they do not do this correctly. This
 * selects the Reference Configuration for the Midgard Implementation. The rationale
 * behind this decision (against asking the customer to write \#include
 * <gpus/mali_t600.h> in their plat_config.h) is as follows: 
 * - This mechanism 'looks' like a regular config file (such as Linux's
 * .config)
 * - It is difficult to get wrong in a way that will produce strange build
 * errors: 
 *  - They need not know where the mali_t600.h, other_midg_gpu.h etc. files are stored - and
 *  so they won't accidentally pick another file with 'mali_t600' in its name
 *  - When the build doesn't work, the System Integrator may think the DDK is
 *  doesn't work, and attempt to fix it themselves:
 *   - For the @ref CONFIG_GPU_CORE_TYPE mechanism, the only way to get past the
 *   error is to set @ref CONFIG_GPU_CORE_TYPE, and this is what the \#error tells
 *   you.
 *   - For a \#include mechanism, checks must still be made elsewhere, which the
 *   System Integrator may try working around by setting \#defines (such as
 *   VA_BITS) themselves in their plat_config.h. In the  worst case, they may
 *   set the prevention-mechanism \#define of
 *   "A_CORRECT_MIDGARD_CORE_WAS_CHOSEN".
 *   - In this case, they would believe they are on the right track, because
 *   the build progresses with their fix, but with errors elsewhere.
 *
 * However, there is nothing to prevent the customer using \#include to organize
 * their own configurations files hierarchically. 
 *
 * The mechanism for the header file processing is as follows:
 *
 * @dot
   digraph plat_config_mechanism {
	   rankdir=BT
	   size="6,6"

       "mali_base.h";
	   "midg/midg.h";

	   node [ shape=box ];
	   {
	       rank = same; ordering = out; 

		   "midg/midg_gpu_props.h";
		   "base/midg_gpus/mali_t600.h";
		   "base/midg_gpus/other_midg_gpu.h";
	   }
	   { rank = same; "plat/plat_config.h"; }
	   {
	       rank = same;
		   "midg/midg.h" [ shape=box ];
		   gpu_chooser [ label="" style="invisible" width=0 height=0 fixedsize=true ];
		   select_gpu [ label="Mali-T600 | Other\n(select_gpu.h)" shape=polygon,sides=4,distortion=0.25 width=3.3 height=0.99 fixedsize=true ] ;
	   }
	   node [ shape=box ];
	   { rank = same; "plat/plat_config.h"; }
	   { rank = same; "mali_base.h"; }

	   
	   
	   "mali_base.h" -> "midg/midg.h" -> "midg/midg_gpu_props.h";
	   "mali_base.h" -> "plat/plat_config.h" ;
	   "mali_base.h" -> select_gpu ;

	   "plat/plat_config.h" -> gpu_chooser [style="dotted,bold" dir=none weight=4] ;
	   gpu_chooser -> select_gpu [style="dotted,bold"] ;

	   select_gpu -> "base/midg_gpus/mali_t600.h" ;
	   select_gpu -> "base/midg_gpus/other_midg_gpu.h" ;
   }
   @enddot
 * 
 *
 * @section sec_base_user_api_gpuprops_kernel Kernel Operation
 *
 * During Base Context Create time, user-side makes two kernel calls:
 * - A call to determine the sizes of GPU information structures 
 * - A call to fill user memory with GPU information structures
 *
 * For a large part of the information, the kernel-side will fill the provided
 * buffer with the raw register values from the GPU. The user-side Base driver
 * will then process this data to produce the final @ref mali_base_gpu_props
 * structure. the Data Structure Builder in user-side will be used for data
 * that can be easily un-packed.
 *
 * Coherency groups must be derived from the bitmasks, but this can be done
 * kernel side, and just once at kernel startup: Coherency groups must already
 * be known kernel-side, to support chains that specify a 'Only Coherent Group'
 * SW requirement, or 'Only Coherent Group with Tiler' SW requirement. The
 * kernel chain scheduling policy can also expose which groups will be available
 * to which user-side priorities. Indeed, assuming that a process' priority
 * will not change, it has the option of removing or adding entire core groups
 * for high/low priviledged processes.
 *
 * For the extended instrumented/debug, user-mode can indicate this at
 * context-create time, and simply request a wider set of registers to receive
 * (in addition to the Coherency group data)
 *
 * @section sec_base_user_api_gpuprops_cocalc Coherency Group calculation
 * Creation of the coherent group data is done at device-driver startup, and so
 * is one-time. This will most likely involve a loop with CLZ, shifting, and
 * bit clearing on the L2_PRESENT or L3_PRESENT masks, depending on whether the
 * system is L2 or L2+L3 Coherent. The number of shader cores is done by a
 * population count, since faulty cores may be disabled during production,
 * producing a non-contiguous mask. A 4-bit LUT helper for the population count
 * will most likely find the population count in a few cycles (after shifting
 * the u64), with modest memory usage (16 bytes).
 *
 * Minimum priority to access the coherent group is assigned later on by the
 * Chain Scheduling Policy. For example, it may implement "1/4th of the cores can
 * be used for priority==Long-running chains", which could be used to remove
 * entire core groups if necessary. However, to prevent NULL core restriction
 * masks, any coherent groups exposed must allow at least one core to be used
 * at any time - or allow at least one core to be powered up in that group.
 *
 * The memory requirements for this algoirthm can be determined either by a u64
 * population count on the L2/L3_PRESENT masks (a LUT helper already is
 * requried for the above), or simple assumption that there can be no more than
 * 16 coherent groups, since core groups are typically 4 cores. 
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
 * @addtogroup base_user_api_gpuprops User-side Base GPU Property Query APIs
 * @{
 */


/**
 * @addtogroup base_user_api_gpuprops_dyn Dynamic HW Properties
 * @{
 */


#define BASE_GPU_NUM_TEXTURE_FEATURES_REGISTERS 3

struct mali_base_gpu_core_props
{
    midg_product_id product_id;
	u16 minor_revision;
    u16 major_revision;

	/**
	 * @usecase GPU clock speed is not specified in the Midgard Architecture, but is
	 * <b>necessary for OpenCL's clGetDeviceInfo() function</b>.
	 */
	u32 gpu_speed_mhz;

	/**
	 * Size of the shader program counter, in bits.
	 */
	u32 log2_program_counter_size;

	/**
	 * TEXTURE_FEATURES_x registers, as exposed by the GPU. This is a
	 * bitpattern where a set bit indicates that the format is supported.
	 *
	 * Before using a texture format, it is recommended that the corresponding
	 * bit be checked.
	 */
	u32 texture_features[BASE_GPU_NUM_TEXTURE_FEATURES_REGISTERS];

	/**
	 * Theoretical maximum memory available to the GPU. It is unlikely that a
	 * client will be able to allocate all of this memory for their own
	 * purposes, but this at least provides an upper bound on the memory
	 * available to the GPU.
	 *
	 * This is required for OpenCL's clGetDeviceInfo() call when
	 * CL_DEVICE_GLOBAL_MEM_SIZE is requested, for OpenCL GPU devices. The
	 * client will not be expecting to allocate anywhere near this value.
	 */
	u64 gpu_available_memory_size;

	/**
	 * @usecase Version string: For use by glGetString( GL_RENDERER ); (and similar
	 * for other APIs)
	 */
	const char * version_string;
};

/**
 *
 * More information is possible - but associativity and bus width are not
 * required by upper-level apis.

 */
struct mali_base_gpu_cache_props
{
	u32 log2_line_size;
	u32 log2_cache_size;
};

struct mali_base_gpu_tiler_props
{
	u32 bin_size_bytes; /* Max is 4*2^15 */
	u32 max_active_levels; /* Max is 2^15 */
};

/**
 * @brief descriptor for a coherent group
 * 
 * \c core_mask exposes all cores in that coherent group, and \c num_cores
 * provides a cached population-count for that mask.
 *
 * @note Whilst all cores are exposed in the mask, not all may be available to
 * the application, depending on the Kernel Job Scheduler policy. Therefore,
 * the application should not further restrict the core mask itself, as it may
 * result in an empty core mask. However, it can guarentee that there will be
 * at least one core available for each core group exposed .
 * 
 * The user-side chain priority required to access the core group is given in
 * priority_required.
 *
 * @usecase Chains marked at certain user-side priorities (e.g. the Long-running
 * (batch) priority ) can be prevented from running on entire core groups by the
 * Kernel Chain Scheduler policy.
 *
 * @note if u64s must be 8-byte aligned, then this structure has 32-bits of wastage.
 */
struct mali_base_gpu_coherent_group
{
	u64 core_mask;         /**< Core restriction mask required for the group */
	u16 num_cores;         /**< Number of cores in the group */
	u16 priority_required; /**< User-side Chain Priority required to access the group */
};

/**
 * @brief Coherency group information
 *
 * Note that the sizes of the members could be reduced. However, the \c group
 * member might be 8-byte aligned to ensure the u64 core_mask is 8-byte
 * aligned, thus leading to wastage if the other members sizes were reduced.
 *
 * The groups are sorted by core mask. The core masks are non-repeating and do
 * not intersect.
 */
struct mali_base_gpu_coherent_group_info
{
	u32 num_groups;

	/**
	 * Number of core groups (coherent or not) in the GPU. Equivalent to the number of L2 Caches.
	 *
	 * The GPU Counter dumping writes 2048 bytes per core group, regardless of
	 * whether the core groups are coherent or not. Hence this member is needed
	 * to calculate how much memory is required for dumping.
	 *
	 * @note Do not use it to work out how many valid elements are in the
	 * group[] member. Use num_groups instead.
	 */
	u32 num_core_groups;

	/** 
	 * Coherency features of the memory, accessed by @ref midg_mem_features
	 * methods
	 */
	midg_mem_features coherency;

	/**
	 * Must be the last member in this structure. num_groups of
	 * @ref mali_base_gpu_coherent_group start at this offset
	 */
	struct mali_base_gpu_coherent_group group[1];
};


/**
 * A complete description of the GPU's Hardware Configuration Discovery
 * registers.
 *
 * The information is presented inefficiently for access. For frequent access,
 * the values should be better expressed in an unpacked form in the
 * mali_base_gpu_props structure.
 *
 * @usecase The raw properties in @ref midg_raw_gpu_props are necessary to
 * allow a user of the Mali Tools (e.g. PAT) to determine "Why is this device
 * behaving differently?". In this case, all information about the
 * configuration is potentially useful, but it <b>does not need to be processed
 * by the driver</b>. Instead, the raw registers can be processed by the Mali
 * Tools software on the host PC.
 *
 */
struct midg_raw_gpu_props
{
	u64 shader_present;
	u64 tiler_present;
	u64 l2_present;
	u64 l3_present;

	midg_cache_features l2_features;
	midg_cache_features l3_features;
	midg_mem_features mem_features;
	midg_mmu_features mmu_features;

	midg_as_present as_present;

	u32 js_present;
	midg_js_features js_features[MIDG_MAX_JOB_SLOTS];
	midg_tiler_features tiler_features;
};



/**
 * Return structure for _mali_base_get_gpu_props().
 *
 */
struct mali_base_gpu_props
{
	struct mali_base_gpu_core_props core_props;
	struct mali_base_gpu_cache_props l2_props;
	struct mali_base_gpu_cache_props l3_props;
	struct mali_base_gpu_tiler_props tiler_props;

	/** This member is large, likely to be 128 bytes */
	struct midg_raw_gpu_props raw_props;

	/** This must be last member of the structure */
	struct mali_base_gpu_coherent_group_info coherency_info;
};

/**
 * Obtain a pointer to the gpu properties
 *
 * The information is setup on base context init. This function only works
 * when a valid base context is provided. Therefore, NULL should never be
 * returned.
 *
 * The pointer returned is to a <b>constant structure</b>. The same pointer will be
 * returned for each call to this function on the same base context.
 *
 * The pointer returned must not be freed, because it does not point to the
 * start of a region allocated by the memory allocator; instead, just close the
 * @ref base_context.
 *
 * It is a programming error to provide an invalid base context.
 *
 * @param[in] ctx a @ref base_context to get a pointer to the GPU properties
 *            from.
 * @return    a pointer to a constant mali_base_gpu_props structure.
 */
const struct mali_base_gpu_props *_mali_base_get_gpu_props( base_context *ctx );


/** @} end group base_user_api_gpuprops_dyn */

/** @} end group base_user_api_gpuprops */
/** @} end group base_user_api */


/**
 * @addtogroup base_plat_config_gpuprops Base Platform Config GPU Properties
 * @{
 *
 * C Pre-processor macros are exposed here to do with Platform
 * Config.
 * 
 * These include:
 * - GPU Properties that are constant on a particular Midgard Family
 * Implementation e.g. Maximum samples per pixel on Mali-T600.
 * - General platform config for the GPU, such as the GPU major and minor
 * revison.
 */

/** @} end group base_plat_config_gpuprops */

/** @} end group base_api */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_GPUPROPS_H_ */
