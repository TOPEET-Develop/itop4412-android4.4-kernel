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
 * @file mali_osu_atomic_armv7.h
 * armv7-specific atomic functions for the OSU module
 */

#ifndef _OSU_ATOMIC_ARMV7_H_
#define _OSU_ATOMIC_ARMV7_H_

#define dmb()	__asm__ volatile("dmb" : : : "memory")

#include <plat/mali_osu_atomic_arm.h>

#define OSUP_PROVIDES_ATOMIC 1

#endif /* _OSU_ATOMIC_ARMV7_H_ */
