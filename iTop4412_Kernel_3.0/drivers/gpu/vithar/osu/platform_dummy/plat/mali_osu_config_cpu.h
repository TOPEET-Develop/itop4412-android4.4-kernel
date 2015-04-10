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
 * @file mali_osu_config_cpu.h
 * Platform Config file for the CPU Properties of an Example Platform
 */

#ifndef _OSU_CPUPROPS_H_
#define _OSU_CPUPROPS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup osuapi
 * @{
 */

/**
 * @addtogroup osucpuprops
 * @{
 */

/*
 * Refer to the doxygen documentation for a description of these values.
 */

#define CONFIG_CPU_PAGE_SIZE_LOG2 12

#define CONFIG_CPU_L1_DCACHE_LINE_SIZE_LOG2 6
#define CONFIG_CPU_L1_DCACHE_SIZE C_SIZE_32KB

#define CONFIG_CPU_COHERENCY_SIZE_LOG2 6

#define CONFIG_CPU_LITTLE_ENDIAN 1
/** @} end group osucpuprops */

/** 
 * @} end group osuapi
 */

#ifdef __cplusplus
}
#endif

#endif /* _OSU_CPUPROPS_H_ */
