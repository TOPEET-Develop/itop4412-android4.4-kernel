/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _KBASE_H_
#define _KBASE_H_

#include <base/mali_base.h>
#include <kbase/src/common/mali_kbase_uku.h>

/**
 * OS specific ringbuffer mapper helper.
 * Must map the ringbuffer into the jd_context substructure of the passed base_ctx
 * The kernel connection can be found from the context.
 * It's an error to call this while a ringbuffer is already mapped.
 *
 * @param base_ctx The base context for which to map the ringbuffer
 * @return MALI_ERROR_NONE if mapped, MALI_ERROR_FUNCTION_FAILED if unable to map
 */
mali_error basep_map_ringbuffer(base_context * base_ctx) CHECK_RESULT;

/**
 * OS specific ringbuffer unmapping helper.
 * Must unmap the ringbuffer previously mapped via basep_map_ringbuffer.
 * It's a programming error to call this without first having mapped the ringbuffer.
 * After having unmapped the ringbuffer can be remapped by a call to basep_map_ringbuffer.
 *
 * @param base_ctx The base context for which to unmap the ringbuffer for
 */
void basep_unmap_ringbuffer(base_context * base_ctx);

/**
 * OS specific register trace buffer mapper helper.
 * Must map the register trace buffer and into the jd_context substructure of the passed base_ctx.
 * The kernel connection can be found from the context.
 * 
 * @param base_ctx The base context for which to map the register trace buffer
 * @param tb_size Size in bytes of the trace buffer
 * @return MALI_ERROR_NONE if trace enable and mapped, MALI_ERROR_FUNCTION_FAILED if unable to trace
 */
mali_error basep_map_trace_buffer(base_context * base_ctx, size_t tb_size);

/**
 * OS specific register trace buffer unmapping helper.
 * Must unmap the register trace buffer and disable the register trace.
 * It's a programming error to call this without first having enable register tracing.
 * After unammping the register tracing can be reenabled again by a call to ::basep_map_trace_buffer
 *
 * @param base_ctx The base context for which to disable register tracing for.
 */
void basep_unmap_trace_buffer(base_context * base_ctx);

/**
 * Free call dispatch helper.
 * Common code call to ask the kernel side to free a memory object represented by the passed handle.
 *
 * @param uk_ctx The UK context to do the free call in
 * @param handle Handle of the memory object to free
 *
 * @return Error code as returned by the OS specific kernel side function.
 */
mali_error basep_do_mem_free(uku_context *uk_ctx, u64 handle) CHECK_RESULT;

#endif /* _KBASE_H_ */
