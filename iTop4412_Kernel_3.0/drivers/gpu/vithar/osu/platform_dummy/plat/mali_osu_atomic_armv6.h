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
 * @file mali_osu_atomic_armv6.h
 * armv6-specific atomic functions for the OSU module
 */

#ifndef _OSU_ATOMIC_ARMV6_H_
#define _OSU_ATOMIC_ARMV6_H_

#define dmb()	__asm__ volatile("mcr p15, 0, %0, c7, c10, 5" \
				 : : "r" (0) : "memory")

#include <plat/mali_osu_atomic_arm.h>

#define OSUP_PROVIDES_ATOMIC 1

#endif /* _OSU_ATOMIC_ARMV6_H_ */
