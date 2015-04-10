/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2008-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _UMP_KERNEL_UK_H_
#define _UMP_KERNEL_UK_H_

#include <uk/mali_uk.h>
#include <uk/mali_ukk.h>

mali_error ump_dispatch(ukk_call_context *ukk_ctx, void *args, u32 args_size);

#endif /* _UMP_KERNEL_UK_H_ */

