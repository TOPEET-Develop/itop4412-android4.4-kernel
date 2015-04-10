/* linux/arch/arm/mm/cache-perf.c
 *
 * Copyright 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/dma-mapping.h>
#include <linux/types.h>
#include <linux/math64.h>

#include <asm/outercache.h>
#include <asm/cacheflush.h>

static unsigned int try_cnt = 1;
module_param(try_cnt, uint, S_IRUGO);
MODULE_PARM_DESC(try_cnt, "Try count to test");

static bool l1 = 1;
module_param(l1, bool, S_IRUGO);
MODULE_PARM_DESC(l1, "Set for L1 check");

static bool l2 = 1;
module_param(l2, bool, S_IRUGO);
MODULE_PARM_DESC(l2, "Set for L2 check");

static bool mset;
module_param(mset, bool, S_IRUGO);
MODULE_PARM_DESC(mset, "Set for Memset");

static bool cops = 1;
module_param(cops, bool, S_IRUGO);
MODULE_PARM_DESC(cops, "Set for Clean");

static bool iops = 1;
module_param(iops, bool, S_IRUGO);
MODULE_PARM_DESC(iops, "Set for Invalidate");

static bool fops = 1;
module_param(fops, bool, S_IRUGO);
MODULE_PARM_DESC(fops, "Set for Flush");

static bool all = 1;
module_param(all, bool, S_IRUGO);
MODULE_PARM_DESC(all, "Set for all flush");

struct task_struct *cacheperf_task;
static bool thread_running;

#define START_SIZE (32)
#define END_SIZE (SZ_2M)

static void print_result(u32 xfer_size, struct timespec lhs,
			 struct timespec rhs)
{
	long us;
	struct timespec ts;

	ts = timespec_sub(rhs, lhs);
	us = ts.tv_sec*USEC_PER_SEC + ts.tv_nsec/NSEC_PER_USEC;

	printk(KERN_INFO "%u: %lu\n", xfer_size, us);
}

static long update_timeval(struct timespec lhs, struct timespec rhs)
{
	long val;
	struct timespec ts;

	ts = timespec_sub(rhs, lhs);
	val = ts.tv_sec*NSEC_PER_SEC + ts.tv_nsec;

	return val;
}

bool buf_compare(u32 src[], u32 dst[], unsigned int bytes)
{
	unsigned int i;

	for (i = 0; i < bytes / 4; i++) {
		if (src[i] != dst[i]) {
			printk(KERN_ERR "Failed to compare: %d, %x:%x-%x:%x\n",
			       i, (u32) src, src[i], (u32) dst, dst[i]);
			return false;
		}
	}

	return true;
}

static int cacheperf(void)
{
	u32 xfer_size;
	int i = 0;
	void *vbuf;
	phys_addr_t pbuf;
	u32 bufend;
	struct timespec beforets;
	struct timespec afterts;
	long timeval;
	vbuf = kmalloc(END_SIZE, GFP_KERNEL);
	pbuf = virt_to_phys(vbuf);

	if (mset) {
		printk(KERN_INFO "## Memset perf (ns)\n");

		xfer_size = START_SIZE;
		while (xfer_size <= END_SIZE) {
			bufend = pbuf + xfer_size;

			getnstimeofday(&beforets);
			for (i = 0; i < try_cnt; i++)
				memset(vbuf, i, xfer_size);
			getnstimeofday(&afterts);
			print_result(xfer_size, beforets, afterts);
			xfer_size *= 2;
		}
	}

	if (cops) {
		printk(KERN_INFO "## Clean perf (ns)\n");

		xfer_size = START_SIZE;
		while (xfer_size <= END_SIZE) {
			bufend = pbuf + xfer_size;
			timeval = 0;

			for (i = 0; i < try_cnt; i++) {
				memset(vbuf, i, xfer_size);
				getnstimeofday(&beforets);
				if (l1)
					dmac_map_area(vbuf, xfer_size,
							DMA_TO_DEVICE);
				if (l2)
					outer_clean_range(pbuf, bufend);
				getnstimeofday(&afterts);
				timeval += update_timeval(beforets, afterts);
				xfer_size *= 2;
			}
			printk(KERN_INFO "%lu\n", timeval);
		}
	}

	if (iops) {
		printk(KERN_INFO "## Invalidate perf (ns)\n");

		xfer_size = START_SIZE;
		while (xfer_size <= END_SIZE) {
			bufend = pbuf + xfer_size;
			timeval = 0;

			for (i = 0; i < try_cnt; i++) {
				memset(vbuf, i, xfer_size);
				getnstimeofday(&beforets);
				if (l2)
					outer_inv_range(pbuf, bufend);
				if (l1)
					dmac_unmap_area(vbuf, xfer_size,
							DMA_FROM_DEVICE);
				getnstimeofday(&afterts);
				timeval += update_timeval(beforets, afterts);
				xfer_size *= 2;
			}
			printk(KERN_INFO "%lu\n", timeval);
		}
	}

	if (fops) {
		printk(KERN_INFO "## Flush perf (ns)\n");

		xfer_size = START_SIZE;
		while (xfer_size <= END_SIZE) {
			bufend = pbuf + xfer_size;
			timeval = 0;

			for (i = 0; i < try_cnt; i++) {
				memset(vbuf, i, xfer_size);
				getnstimeofday(&beforets);
				if (l1)
					dmac_flush_range(vbuf,
					(void *)((u32) vbuf + xfer_size));
				if (l2)
					outer_flush_range(pbuf, bufend);
				getnstimeofday(&afterts);
				timeval += update_timeval(beforets, afterts);
				xfer_size *= 2;
			}
			printk(KERN_INFO "%lu\n", timeval);
		}
	}


	if (all) {
		printk(KERN_INFO "## Flush all perf (ns)\n");

		xfer_size = START_SIZE;
		while (xfer_size <= END_SIZE) {
			bufend = pbuf + xfer_size;
			timeval = 0;

			for (i = 0; i < try_cnt; i++) {
				memset(vbuf, i, xfer_size);
				getnstimeofday(&beforets);
					if (l1)
						flush_cache_all();
					if (l2)
						outer_flush_all();
				getnstimeofday(&afterts);
				timeval += update_timeval(beforets, afterts);
				xfer_size *= 2;
			}
			printk(KERN_INFO "%lu\n", timeval);
		}
	}

	kfree(vbuf);

	return 0;
}

static int thread_func(void *data)
{
	thread_running = 1;
	cacheperf();
	thread_running = 0;

	return 0;
}

int __init cacheperf_init(void)
{
#ifndef CONFIG_OUTER_CACHE
	l2 = 0;
#endif

	printk(KERN_ERR "Test condition: l1: %d, l2: %d, try_cnt:%d, (%dB ~ %dMB)\n",
				l1, l2, try_cnt, START_SIZE, END_SIZE/SZ_1M);

	cacheperf_task = kzalloc(sizeof(struct task_struct), GFP_KERNEL);
	cacheperf_task = kthread_run(thread_func, NULL, "cacheperf_thread");
	if (IS_ERR(cacheperf_task))
			printk(KERN_INFO "Failed to create module\n");

	return 0;
}
module_init(cacheperf_init)

void cacheperf_exit(void)
{
	if (thread_running)
		kthread_stop(cacheperf_task);

	kfree(cacheperf_task);
}
module_exit(cacheperf_exit);
MODULE_LICENSE("GPL");
