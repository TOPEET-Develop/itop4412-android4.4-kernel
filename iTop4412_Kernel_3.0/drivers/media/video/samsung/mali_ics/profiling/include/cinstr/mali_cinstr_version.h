/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _CINSTR_VERSION_H_
#define _CINSTR_VERSION_H_

#define MALI_MODULE_CINSTR_MAJOR 1
#define MALI_MODULE_CINSTR_MINOR 0

#define MALI_CINSTR_VERSION_MAKE(major, minor) (u32)(((major & 0xFFFF) << 16) | (minor & 0xFFFF))
#define MALI_CINSTR_VERSION_GET_MAJOR(version) (u32)(version >> 16)
#define MALI_CINSTR_VERSION_GET_MINOR(version) (u32)(version & 0xFFFF)

#endif /*_CINSTR_VERSION_H_*/
