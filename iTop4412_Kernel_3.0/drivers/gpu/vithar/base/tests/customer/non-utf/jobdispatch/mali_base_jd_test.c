/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/*
 * Convoluted unit test for Base JD API.
 *
 * NOTE: This file is used as an example, and so cannot be used as input to
 * doxygen aswell.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <base/mali_base.h>
#include <midg/mali_midg.h>
#include <osu/mali_osu.h>

#include "base/src/mali_base_trace.h"

/*
 * This file is only sample code to test the Job Dispatch API. It
 * builds a single bag containing two "strands" of 32 interdependant
 * job-chains like this:
 *
 *            @     @
 *            |\   /|
 *            | \ / |
 *            |  x  |
 *            | / \ |
 *            |/   \|
 *            @     @
 *            |\   /|
 *            | \ / |
 *            |  x  |
 *            | / \ |
 *            |/   \|
 *            @     @
 *            |\   /|
 *            | \ / |
 *            |  x  |
 *            | / \ |
 *            |/   \|
 *            @     @
 *              ...
 *
 * Job-chains have semi-random core requirements, including being
 * VOID. The bag is then submited and kernel events are consumed by a
 * separate thread.
 *
 * No, this doesn't follow MCS/PCS yet. Not sure if it will ever. It
 * also uses all kinds of non-supported OS API... Once we write a
 * proper test suite, I expect this to be be simply dropped.
 */
 
static osu_sem done_sem;

/*
 * This is the event handler. It pumps event from the kernel and acts
 * accordingly.
 */
static void *event_handler(void *data)
{
	base_context *ctx = data;

	while(1) {
		base_jd_event event;

		base_jd_event_wait(ctx, &event);

		switch (event.event_code) {
		case BASE_JD_EVENT_DONE: {
			/*
			 * A job-chain has completed. Release the
			 * dependency tags.
			 */
			base_jd_atom *atom;

			atom = base_atom_get_address(ctx, (size_t)event.data);
			beenthere("BASE_JD_EVENT_DONE %p[%d,%d][%d,%d]",
				  (void *)atom,
				  atom->pre_dep.dep[0],
				  atom->pre_dep.dep[1],
				  atom->post_dep.dep[0],
				  atom->post_dep.dep[1]);
			base_dep_release(ctx, &atom->post_dep);
			break;
		}

		case BASE_JD_EVENT_BAG_DONE: {
			/*
			 * The whole bag has completed. Release the
			 * buffer, free the bag, and synchronize with
			 * the rest of the program.
			 */
			base_jd_bag *bag = event.data;
			beenthere("BASE_JD_EVENT_BAG_DONE %p", (void *) bag);
			base_bag_release_buffer(ctx, bag);
			free(bag);
			osu_sem_post(&done_sem);
			break;
		}

		case BASE_JD_EVENT_DRV_TERMINATED:
			/*
			 * We're going down...
			 */
			beenthere("%s", "Terminating event thread");
			return NULL;
			
		default:
			beenthere("Unknown event code %08x", event.event_code);
		}
	}

	/* Not reached */
	return NULL;
}

static void die(char *str)
{
	fprintf(stderr, "Unexpected failure: %s\n", str);
	exit(EXIT_FAILURE);
}

/* Utility function to populate an atom, allocate a null job... */
static void *build_atom(base_context *ctx, base_jd_atom *atom,
			base_pmem_handle ph, midg_null_job *cmd_buf,
			u8 predep0, u8 predep1)
{
	u8 core;

	core = random() % 4;
	atom->core_req		= core ? (1 << (core - 1)) : 0;
	atom->prio		= 0;

	atom->pre_dep.dep[0]	= predep0;
	atom->pre_dep.dep[1]	= predep1;

	/*
	 * In some random cases, omit one of the dependencies... That
	 * triggered some interresting race conditions in the past...
	 */

	if( MALI_ERROR_NONE != base_dep_acquire(ctx, &atom->post_dep, (!!(random() % 11)) + 1) )
	{
		die("base_dep_acquire failure\n");
	}

	if (atom->core_req != BASE_JD_REQ_DEP) {
		/*
		 * This is a null job-chain. Add the mandatory
		 * syncsets to ensure memory coherency
		 */
		midg_null_job_init(cmd_buf);
		atom->jc	  = base_pmem_cpu_address_to_gpu(ph, cmd_buf);
		atom->nr_syncsets = 2;
		base_syncset_to_gpu(base_jd_get_atom_syncset(atom, 0),
				    base_pmem_to_mem(ph),
				    cmd_buf, sizeof(*cmd_buf));
		base_syncset_to_cpu(base_jd_get_atom_syncset(atom, 1),
				    base_pmem_to_mem(ph),
				    cmd_buf, sizeof(*cmd_buf));
		cmd_buf = (void *)((char *)cmd_buf + 64);
	} else {
		/*
		 * VOID job. Not a lot to say about it...
		 */
		atom->nr_syncsets	= 0;
		atom->jc		= (mali_addr64)0;
	}

	return cmd_buf;
}

static void run_test(base_context *ctx, base_pmem_handle ph)
{
	void *cmd_buf;
	base_jd_bag *bag;
	base_jd_atom *atom;
	base_jd_dep dep_left  = { { 0, 0, }, };
	base_jd_dep dep_right = { { 0, 0, }, };
	size_t bag_size = 64 * base_jd_atom_size(2); /* 64 jobs, two syncsets per job. */
	int i;

	cmd_buf = base_pmem_get_cpu_address(ph);
	bag = malloc(sizeof(*bag));
	if ( NULL == bag )
	{
		die( "Malloc failed - cannot continue!\n" );
	}

	if (base_bag_acquire_buffer(ctx, bag, &bag_size)) {
		beenthere("oops... max free size in ring buffer = %ld", (unsigned long)bag_size);
		die("out of buffer space");
	}

	atom = base_bag_get_address(ctx, bag);

	for (i = 0; i < 32; i++) {
		base_jd_dep new_dep_left;
		mali_error err;

		/* left node */
		cmd_buf = build_atom(ctx, atom, ph, cmd_buf,
				     dep_left.dep[0], dep_right.dep[0]);

		new_dep_left = atom->post_dep;

		err = CDBG_SPEW_LOCK();
		if (err == MALI_ERROR_NONE)
		{
			CDBG_SPEW_PRINT("[%d,%d]%d(%d)[%d,%d]\n",
					dep_left.dep[0], dep_right.dep[0],
					2*i, atom->core_req,
					atom->post_dep.dep[0], atom->post_dep.dep[1]);
			CDBG_SPEW_UNLOCK();
		}

		atom = base_jd_get_next_atom(atom);

		/* right node */
		cmd_buf = build_atom(ctx, atom, ph, cmd_buf,
				     dep_left.dep[1], dep_right.dep[1]);

		err = CDBG_SPEW_LOCK();
		if (err == MALI_ERROR_NONE)
		{
			CDBG_SPEW_PRINT("[%d,%d]%d(%d)[%d,%d]\n",
					dep_left.dep[1], dep_right.dep[1],
					2*i + 1, atom->core_req,
					atom->post_dep.dep[0], atom->post_dep.dep[1]);
			CDBG_SPEW_UNLOCK();
		}

		dep_right = atom->post_dep;
		dep_left = new_dep_left;
		atom = base_jd_get_next_atom(atom);
	}


	bag->core_restriction	= 0;
	bag->nr_atoms		= 64;

	base_jd_submit_bag(ctx, bag);
}

int main(int argc, char *argv[])
{
	int i = 32;
	base_pmem_handle ph;
	base_context ctx;
	osu_thread event_thread;

	cdbg_print_init();
	CDBG_PRINT_BLOCK(CDBG_BASE, CDBG_CHANNEL_INFO);

	if( MALI_TRUE != base_context_init(&ctx, 0) )
	{
		die("base_context_init failed - cannot continue!\n");
	}

	if ( OSU_ERR_OK != osu_sem_init(&done_sem, 0) )
	{
		die( "osu_sem_init failed - cannot continue!\n" );
	}

	if( OSU_ERR_OK != osu_thread_create(&event_thread, event_handler,
			  &ctx, OSU_THREAD_PRIORITY_DEFAULT) )
	{
		die("osu_thread_create failed - cannot continue!\n");
	}

	srandom(getpid());

	base_pmem_alloc(&ctx, 1,
			BASE_MEM_PROT_CPU_RD | BASE_MEM_PROT_CPU_WR |
			BASE_MEM_PROT_GPU_RD | BASE_MEM_PROT_GPU_WR |
			BASE_MEM_HINT_CPU_RD | BASE_MEM_HINT_CPU_WR,
			&ph);
	while (--i) {
		run_test(&ctx, ph);

		osu_sem_wait(&done_sem, 0);
	}
	osu_sem_term(&done_sem);

	base_pmem_free( &ctx, ph, 1 );

	base_jd_event_term(&ctx);
	osu_thread_wait(&event_thread, NULL);

	base_context_term(&ctx);

	return EXIT_SUCCESS;
}

