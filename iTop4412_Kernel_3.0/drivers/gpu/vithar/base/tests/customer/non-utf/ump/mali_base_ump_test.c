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
#include <stddef.h>
#include <unistd.h>

#include <base/mali_base.h>
#include <osu/mali_osu.h>
#include <ump/ump.h>

#include "base/src/mali_base_trace.h"


static void *event_handler(void *data)
{
	base_context *ctx = data;

	while(1)
	{
		base_jd_event event;

		base_jd_event_wait(ctx, &event);

		switch (event.event_code)
		{
			case BASE_JD_EVENT_DRV_TERMINATED:
				return NULL;
			default:
				fprintf(stderr, "Unexpected event code 0x%08X\n", event.event_code);
				break;
		}
	}
}

int main(int argc, char *argv[])
{
	osu_thread event_thread;
	ump_handle h;
	base_context ctx;
#define NUM_PAGES 4

	cdbg_print_init();
	CDBG_PRINT_BLOCK(CDBG_BASE, CDBG_CHANNEL_INFO);

	if( MALI_TRUE != base_context_init(&ctx, 0))
	{
		printf("ERROR: base_context_init failed\n");
		return EXIT_FAILURE;		
	}

	if (OSU_ERR_OK != osu_thread_create(&event_thread, event_handler,&ctx, OSU_THREAD_PRIORITY_DEFAULT))
	{
		printf("ERROR: failed to create event_handler thread\n");
		base_context_term(&ctx);
		return EXIT_FAILURE;		
	}

	if (UMP_OK == ump_open())
	{
		h = ump_allocate(NUM_PAGES << CONFIG_CPU_PAGE_SIZE_LOG2, UMP_PROT_CPU_RD | UMP_PROT_CPU_WR | UMP_HINT_CPU_RD | UMP_HINT_CPU_WR | UMP_PROT_Z_RD | UMP_PROT_Z_WR);

		if (UMP_INVALID_MEMORY_HANDLE != h)
		{
			base_tmem_handle tmem;
			u64 pages;

			printf("Got ump id %d\n", ump_secure_id_get(h));
			tmem = base_tmem_from_ump(&ctx, ump_secure_id_get(h), &pages);
			if (0ULL != tmem)
			{
				int page;
				void * mapping;
				
				ump_release(h); /* base should still have a ref */
				h = UMP_INVALID_MEMORY_HANDLE;


				/* assert here instead of printing */
				if (pages != NUM_PAGES)
				{
					printf("ERROR: !!! Wrong page count: %lld != %d\n", pages, NUM_PAGES);
				}

				for (page = 0; page < NUM_PAGES; page++)
				{
					mapping = base_tmem_map(&ctx, tmem, page << CONFIG_CPU_PAGE_SIZE_LOG2, 1ul << CONFIG_CPU_PAGE_SIZE_LOG2);
					if (NULL != mapping)
					{
						memset(mapping, 0, 1ul << CONFIG_CPU_PAGE_SIZE_LOG2);
						if (MALI_ERROR_NONE != base_tmem_unmap(&ctx, tmem, mapping, 1ul << CONFIG_CPU_PAGE_SIZE_LOG2))
						{
							printf("WARNING: base_tmem_unmap failed for page %d\n", page);
						}
					}
					else
					{
						printf("ERROR: base_tmem_map failed for page %d\n", page);
					}
				}

				base_tmem_free(&ctx, tmem);

			}
			else
			{
				ump_release(h);
			}

		}
		ump_close();
	}

	base_jd_event_term(&ctx);
	osu_thread_wait(&event_thread, NULL);

	base_context_term(&ctx);
	return EXIT_SUCCESS;
}

