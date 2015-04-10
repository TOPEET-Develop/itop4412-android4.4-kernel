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
 * @file mali_base_map_test_quick.c
 * Test base_tmem_map() interface by allocating two pages and
 * testing in linear runtime:
 * - All byte start addresses over the memory range
 * - All byte sizes over the memory range
 *
 * Appropriate syncops will be used on the write and read of the mapped memory.
 *
 * In addition, we'll test a corner case:
 * - 2 byte range crossing a page boundary
 *
 * Note that the first set of tests already cover the following corner cases:
 * - The first page only
 * - The first page + the 1st byte of the second page
 * - The second page only
 * - The second page only + the last byte of the first page
 *
 * This is quicker than running mali_base_map_test.c and
 * mali_base_map_test_ex.c, which are quadratic on runtime.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <base/mali_base.h>
#include <cdbg/mali_cdbg.h>

typedef struct test_context
{
	base_context *ctx;
	base_tmem_handle th;
	size_t nrb; /**< number of bytes */
	u8 *template;
} test_context;

/*
 * Function protos
 */
static void die(char *str);
static void *event_handler(void *data);
static void test_range( test_context *test_ctx, size_t ofs, size_t sz );



/*
 * Private functions
 */
static void die(char *str)
{
	fprintf(stderr, "Unexpected failure: %s\n", str);
	exit(EXIT_FAILURE);
}



/*
 * This is the event handler. It is required even if you don't need one.
 */
static void *event_handler(void *data)
{
	base_context *ctx = data;

	while(1) {
		base_jd_event event;

		base_jd_event_wait(ctx, &event);

		switch (event.event_code) {
			case BASE_JD_EVENT_DRV_TERMINATED:
				return NULL;

			default:
				break;
		}
	}

	/* Not reached */
	return NULL;
}



static void test_range( test_context *test_ctx, size_t ofs, size_t sz )
{
	base_context *ctx = test_ctx->ctx;

	base_tmem_handle th = test_ctx->th;

	u8 *template = test_ctx->template;

	u8 *mapping;

	mapping = base_tmem_map(ctx, th, ofs, sz);
	if ( NULL == mapping )
	{
		die("test failed - base_tmem_map returned NULL\n");
	}

	base_sync_to_cpu_now(ctx, base_tmem_to_mem(th), mapping, sz);

	if ( 0 != memcmp(template + ofs, mapping, sz) )
	{
		CDBG_PRINT_ERROR( CDBG_BASE, "Comparison failed for offset=%d size=%d", ofs, sz );
	}

	if ( MALI_ERROR_NONE != base_tmem_unmap(ctx, th, mapping, sz) )
	{
		die("base_tmem_unmap failed - cannot continue!\n");
	}
}

/*
 * Public functions
 */
int main(int argc, char *argv[])
{
	base_tmem_handle th;
	size_t ofs, sz;
	int nrp = 2;
	size_t nrb;
	base_context ctx;
	u8 * mapping;
	u8 * template;
	int i;
	test_context test_ctx;
	size_t page_size = getpagesize();
	osu_thread event_thread;
	mali_error err;

	cdbg_print_init();
	CDBG_PRINT_BLOCK(CDBG_BASE, CDBG_CHANNEL_INFO);

	nrb = nrp * page_size;

	if( MALI_TRUE != base_context_init(&ctx, 0) )
	{
		die("base_context_init failed - cannot continue!\n");
	}

	if( OSU_ERR_OK != osu_thread_create(&event_thread, event_handler,
			  &ctx, OSU_THREAD_PRIORITY_DEFAULT) )
	{
		die("osu_thread_create failed - cannot continue!\n");
	}

	th = base_tmem_alloc(&ctx, nrp,
			     BASE_MEM_PROT_CPU_RD | BASE_MEM_PROT_CPU_WR |
			     BASE_MEM_PROT_GPU_RD | BASE_MEM_PROT_GPU_WR |
			     BASE_MEM_HINT_CPU_RD | BASE_MEM_HINT_CPU_WR);


	template = malloc(nrb);
	if ( NULL == template )
	{
		die("malloc failed - cannot continue!\n");
	}

	for (i = 0; i < nrb/2; i++)
	{
		u16 * t = (u16*)template;
		t[i] = i;
	}
	mapping = base_tmem_map(&ctx, th, 0, nrb);
	CDBG_ASSERT_POINTER(mapping);
	memcpy(mapping, template, nrb);

	base_sync_to_gpu_now(&ctx, base_tmem_to_mem(th), mapping, nrb);

	if ( MALI_ERROR_NONE != base_tmem_unmap(&ctx, th, mapping, nrb) )
	{
		die("base_tmem_unmap failed - cannot continue!\n");
	}
	/* prepare the test ctx */
	test_ctx.ctx = &ctx;
	test_ctx.th = th;
	test_ctx.nrb = nrb;
	test_ctx.template = template;

	/* Case 1: all start addresses */
	err = CDBG_SPEW_LOCK();
	if (err == MALI_ERROR_NONE)
	{
		CDBG_SPEW_PRINT("Testing all start addresses from offset %d to %d bytes\n", 0, test_ctx.nrb);
		CDBG_SPEW_UNLOCK();
	}
	for (ofs = 0; ofs < nrb; ofs++)
	{
		test_range( &test_ctx, ofs, test_ctx.nrb - ofs );
	}

	/* Case 2: all sizes of memory */
	err = CDBG_SPEW_LOCK();
	if (err == MALI_ERROR_NONE)
	{
		CDBG_SPEW_PRINT("Testing all sizes of memory from %d to %d bytes\n", 0, test_ctx.nrb);
		CDBG_SPEW_UNLOCK();
	}
	for (sz = 1; sz <= test_ctx.nrb; sz++)
	{
		test_range( &test_ctx, 0, sz );
	}

	/* Case 3: all sizes of memory */
	err = CDBG_SPEW_LOCK();
	if (err == MALI_ERROR_NONE)
	{
		CDBG_SPEW_PRINT("Testing corner case (2 bytes crossing a page boundary)\n");
		CDBG_SPEW_UNLOCK();
	}
	test_range( &test_ctx, page_size - 1, 2 );

	/* All done */
	err = CDBG_SPEW_LOCK();
	if (err == MALI_ERROR_NONE)
	{
		CDBG_SPEW_PRINT("Cleaning up...\n");
		CDBG_SPEW_UNLOCK();
	}
	base_tmem_free(&ctx, th);

	base_jd_event_term(&ctx);
	osu_thread_wait(&event_thread, NULL);

	base_context_term(&ctx);
	err = CDBG_SPEW_LOCK();
	if (err == MALI_ERROR_NONE)
	{
		CDBG_SPEW_PRINT("Done!\n");
		CDBG_SPEW_UNLOCK();
	}

	free(template);

	return EXIT_SUCCESS;
}

