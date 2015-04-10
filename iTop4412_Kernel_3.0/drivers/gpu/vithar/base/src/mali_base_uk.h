/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/** @file mali_base_uk.h */

#ifndef _BASE_UK_H_
#define _BASE_UK_H_

mali_error base_uk_ctx_alloc(base_context * base_ctx, u32 flags);
void base_uk_ctx_terminate(base_context * base_ctx);
void base_uk_ctx_free(base_context *base_ctx);

#endif /* _BASE_UK_H_ */
