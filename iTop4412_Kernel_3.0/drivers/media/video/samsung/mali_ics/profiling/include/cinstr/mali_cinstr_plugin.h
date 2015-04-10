/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_CINSTR_PLUGIN_H_
#define _MALI_CINSTR_PLUGIN_H_

#include <cinstr/mali_cinstr_common.h>

/** \file mali_cinstr_plugin.h
 *
 * Describes functions that must be exported by an Instrumentation Plugin.
 */

/**
 * \addtogroup cinstr_ipi_plugin Instrumentation Plugin Interface Plugin APIs
 * \{
 */

#if 0
/**
 * \brief Initialize an Instrumentation Plugin
 *
 * Runs any setup routines that the Instrumentation Plugin requires are start up
 *
 * \param core_data           A pointer to a struct containing the version of the
 *                            Instrumentation Core that is attempting to load the Plugin.
 *                            also contains a structure of methods and fields that the
 *                            Plugin will need to call on the Instrumentation Core.
 *
 * \param plugin              A pointer to the instance structure for the plugin. Should
 *                            the call complete successfully, this will point to a struct
 *                            containing the function pointers to plugin functions.
 *
 * \return                    Zero indicates success, and Instrumentation is enabled. If
 *                            the app does not need to be instrumented, a non-zero return
 *                            is returned.
 */
cinstr_error_t cinstr_plugin_init(cinstr_core_data *core_data, cinstr_plugin_instance *plugin);

#endif


/** \} end group cinstr_ipi_plugin */


#endif /* _MALI_CINSTR_PLUGIN_H_ */
