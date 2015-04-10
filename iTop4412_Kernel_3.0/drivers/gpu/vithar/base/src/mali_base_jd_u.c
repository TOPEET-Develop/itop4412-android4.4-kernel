/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <base/mali_base.h>
#include <base/src/mali_base_user.h>

#define myownmax(x,y)	((x) < (y) ? (y) : (x))

static INLINE u8 base_sem_acquire(base_context *ctx)
{
	int i;
	u32 val;

	for (i = 0; i < BASEP_JD_SEM_ARRAY_SIZE; i++) {
		if (ctx->jd_context.sem[i])
			break;
	}

	if (i == BASEP_JD_SEM_ARRAY_SIZE) {
		return 0;
	}

	val = ffs(ctx->jd_context.sem[i]) - 1;
	val += BASEP_JD_SEM_PER_WORD * i;
	ctx->jd_context.sem[i] &= ~BASEP_JD_SEM_MASK_IN_WORD(val);
	
	return val;
}

static INLINE void base_sem_release(base_context *ctx, u8 s)
{
	int i;

	if (!s)
		return;

	i = BASEP_JD_SEM_WORD_NR(s);
	/* check we're not clearing something twice... */
	CDBG_ASSERT(!(ctx->jd_context.sem[i] & BASEP_JD_SEM_MASK_IN_WORD(s)));
	ctx->jd_context.sem[i] |= BASEP_JD_SEM_MASK_IN_WORD(s);
}

base_jd_atom *base_bag_get_address(const base_context *ctx,
				   const base_jd_bag *bag)
{
	CDBG_ASSERT_POINTER(ctx);
	return (struct base_jd_atom *)((char *)ctx->jd_context.pool + bag->offset);
}

mali_error base_bag_acquire_buffer(base_context *ctx,
				   base_jd_bag *bag, size_t *req_size)
{
	size_t size;
	mali_error ret = MALI_ERROR_NONE;

	CDBG_ASSERT_POINTER(ctx);
	CDBG_ASSERT_POINTER(req_size);
	CDBG_ASSERT(0 != *req_size);

	size = *req_size;
	bag->size = size; /* Let's be optmistic... */
	
	osu_mutex_lock(&ctx->jd_context.lock);

	if (ctx->jd_context.tail >= ctx->jd_context.head) {
		/* fits at the end? */
		if (size <= (ctx->jd_context.size - ctx->jd_context.tail)) {
			bag->offset = ctx->jd_context.tail;
			ctx->jd_context.tail += size;
			goto out;
		}

		/* fits at the beginning? */
		if (size < ctx->jd_context.head) {
			bag->offset = 0;
			ctx->jd_context.tail = size;
			goto out;
		}

		/* Failed */
		/* check how much we can put there*/
		if(0 == ctx->jd_context.head){
			*req_size = (ctx->jd_context.size - ctx->jd_context.tail - 1); /* at the end*/
		}
		else{
			*req_size = /* at the end, no need to leave one byte here*/
					myownmax((ctx->jd_context.size - ctx->jd_context.tail),
						/* or at the beginning */
						ctx->jd_context.head - 1);
		}


	} else {
		/* Fits between tail and head? */
		if (size <= (ctx->jd_context.head - ctx->jd_context.tail - 1)) {
			bag->offset = ctx->jd_context.tail;
			ctx->jd_context.tail += size;
			goto out;
		}

		/* Failed */
		*req_size = (ctx->jd_context.head - ctx->jd_context.tail - 1);
	}

	ret = MALI_ERROR_FUNCTION_FAILED;
out:
	if (MALI_ERROR_NONE == ret){
		CUTILS_DLIST_PUSH_BACK(&ctx->jd_context.bag_list, bag,
				       base_jd_bag, entry);
	}

	osu_mutex_unlock(&ctx->jd_context.lock);
	return ret;
}

void base_bag_release_buffer(base_context *ctx, base_jd_bag *bag)
{
	int is_first;
	base_jd_bag *tmp;
	base_jd_bag *next;
	
	CDBG_ASSERT_POINTER(ctx);

	osu_mutex_lock(&ctx->jd_context.lock);

	tmp = CUTILS_DLIST_FRONT(&ctx->jd_context.bag_list, base_jd_bag, entry);
	if (bag == tmp)
		is_first = 1;
	else
		is_first = 0;

	next = CUTILS_DLIST_REMOVE_AND_RETURN_NEXT(&ctx->jd_context.bag_list,
						   bag, base_jd_bag, entry);

	if (CUTILS_DLIST_IS_EMPTY(&ctx->jd_context.bag_list)) {
		ctx->jd_context.head = ctx->jd_context.tail;
	} else {
		if (is_first) {
			ctx->jd_context.head = next->offset;
		}
	}
	
	osu_mutex_unlock(&ctx->jd_context.lock);
}

mali_error base_dep_acquire(base_context *ctx, base_jd_dep *dep, int nr)
{
	mali_error ret = MALI_ERROR_NONE;
	int i;

	CDBG_ASSERT_POINTER(ctx);
	CDBG_ASSERT_POINTER(dep);
	CDBG_ASSERT((nr == 1) || (nr == 2));

	/* Please turn this into spin/cheap locks... */
	osu_mutex_lock(&ctx->jd_context.lock);

	for (i = 0; i < nr; i++) {
		dep->dep[i] = base_sem_acquire(ctx);
		if (!dep->dep[i])
			break;
	}

	if (i < nr) {
		if (1 == i)
		{
			base_sem_release(ctx, dep->dep[0]);
		}
		ret = MALI_ERROR_FUNCTION_FAILED;
	}

	/*
	 * If we were asked for a single dependency, make sure we wipe
	 * the second one. It helps keeping the release code simple.
	 */
	if (nr == 1)
		dep->dep[1] = 0;

	osu_mutex_unlock(&ctx->jd_context.lock);
	return ret;
}

void base_dep_release(base_context *ctx, base_jd_dep *dep)
{
	CDBG_ASSERT_POINTER(ctx);
	CDBG_ASSERT_POINTER(dep);

	osu_mutex_lock(&ctx->jd_context.lock);
	base_sem_release(ctx, dep->dep[0]);
	base_sem_release(ctx, dep->dep[1]);
	osu_mutex_unlock(&ctx->jd_context.lock);
}

base_jd_atom *base_atom_get_address(const base_context *ctx, size_t offset)
{
	CDBG_ASSERT_POINTER(ctx);
	return (base_jd_atom *)((uintptr_t)ctx->jd_context.pool + offset);
}
