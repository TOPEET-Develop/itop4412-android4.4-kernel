/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2008-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _UMP_USER_H_
#define _UMP_USER_H_

#include <ump/ump.h>
#include <osu/mali_osu.h>

typedef struct ump_mem
{
	ump_secure_id id; /* secure id of the allocation */
	osu_atomic refcnt; /* handle local usage count (to avoid uneeded kernel calls) */
} ump_mem;

extern ump_context ump_uk_ctx;

#endif /* _UMP_USER_H_ */
