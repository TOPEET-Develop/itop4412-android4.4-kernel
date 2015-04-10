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
 * @file mali_osu_platform.h
 * Platform-specific header files for the OSU module
 *
 * There is one mali_osu_platform.h for each platform
 */
#ifndef _OSU_PLATFORM_H_
#define _OSU_PLATFORM_H_

/* Platform Config CPU Properties */
#include <plat/mali_osu_config_cpu.h>

/* Add includes here for this platform's OSU inline functions */
#ifdef __GNUC__

/* GCC specific atomic ops */

#if defined(__x86_64__) || defined(__i486__) || defined(__i386__)
#include <plat/mali_osu_atomic_x86.h>
#endif

#if defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6__)
#include <plat/mali_osu_atomic_armv6.h>
#endif

#if defined(__ARM_ARCH_7A__)
#include <plat/mali_osu_atomic_armv7.h>
#endif

#endif /* __GNUC__ */

#ifndef OSUP_PROVIDES_ATOMIC
#error "No atomic support, please fix your OSU platform support"
#endif

#include <plat/mali_osu_temp.h>

#endif /* _OSU_PLATFORM_H_ */
