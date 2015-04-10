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
 * @file mali_base.h
 * Master base driver include file
 */

#ifndef _BASE_H_
#define _BASE_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <malisw/mali_stdtypes.h>
#include <midg/mali_midg.h>
#include <base/mali_base_compatibility.h>
#include <plat/plat_config.h>
#include <mali_base_hwconfig.h>

#include <cutils/linked_list/mali_cutils_dlist.h>

/* The following include depends on values defined in plat/plat_config.h: */
#include <base/midg_gpus/select_gpu.h>

#include <base/mali_base_types.h>
#include <base/mali_base_kernel.h>
#include <base/mali_base_memory.h>
#include <base/mali_base_jd.h>
#include <base/mali_base_context.h>
#include <base/mali_base_gpuprops.h>
#include <base/mali_base_channels.h>

#define MALI_MODULE_BASE_MAJOR	3
#define MALI_MODULE_BASE_MINOR	1

/**
 * @page page_base_user_main User-side Base APIs
 *
 * The User-side Base APIs are divided up as follows:
 * - @subpage page_base_user_api_core
 * - @subpage page_base_user_api_mem
 * - @subpage page_base_user_api_gpuprops
 * - @subpage page_base_api_job_dispatch
 * - @subpage page_base_user_api_channels
 * - Reference your API's page as a \@subpage here - for this to work, the
 * \@page sections \b must be outside any \@group / \@addtogroup sections.
 *
 *
 * @req Dummy Requirement using \@req defined in 'ALIASES' in Doxyfile:
 * - Which can use an entire paragraph
 * - So you can put lists in the requirement.
 *
 * @usecase Dummy Use-case using \@usecase defined in 'ALIASES' in Doxyfile.
 * - Again, can contain a paragraph
 * - and therefore, a list
 */

/**
 * @defgroup base_api Base APIs
 */

/**
 * @defgroup base_user_api User-side Base APIs
 */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_H_ */
