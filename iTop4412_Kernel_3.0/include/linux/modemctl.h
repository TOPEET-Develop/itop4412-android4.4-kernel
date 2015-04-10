/*
 * Modem control driver
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Author: Suchang Woo <suchang.woo@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */
#ifdef CONFIG_HAS_WAKELOCK
#include <linux/wakelock.h>
#endif

#ifndef __MODEM_CONTROL_H__
#define __MODEM_CONTROL_H__

#define MC_SUCCESS 0
#define MC_HOST_HIGH 1
#define MC_HOST_TIMEOUT 2
#define MC_CP_RESET 3      //xujie, CP reset happened


#define RESET_STATE_OFFSET		1
#define CRASH_STATE_OFFSET	2
#define DUMP_STATE_OFFSET		3

#define MODEM_POWER_MAIN_CMD		0xC0//_IOWR('M', 0, int)
#define MODEM_POWER_FLASH_CMD		0xC1//_IOWR('M', 1, int)
#define MODEM_POWER_OFF_CMD			0xC2//_IOWR('M', 2, int)
#define MODEM_POWER_ON_CMD			0xC3//_IOWR('M', 3, int)
#define MODEM_POWER_RESET_CMD		0xC4//_IOWR('M', 4, int)

struct modemctl {
	int irq[3];
	int in_l3_state;
	int gModemPowerState;
	int gCdcAcmSimpleEnumeratinoState;
	struct timer_list	reset_judge_timer;	/*for judging a modem reset event */
	
	unsigned gpio_phone_on;
	unsigned gpio_phone_active;
	unsigned gpio_pda_active;
	unsigned gpio_cp_reset;
	unsigned gpio_usim_boot;
	unsigned gpio_flm_sel;

	unsigned gpio_cp_req_reset;
	unsigned gpio_ipc_slave_wakeup;
	unsigned gpio_ipc_host_wakeup;
	unsigned gpio_suspend_request;
	unsigned gpio_active_state;
	unsigned gpio_cp_reset_int;
	struct modem_ops *ops;
	struct regulator *vcc;

	struct device *dev;
	const struct attribute_group *group;

	struct delayed_work work;
	struct work_struct resume_work;
	struct work_struct cpreset_work;
	struct work_struct do_reset_work;
	int wakeup_flag; /*flag for CP boot GPIO sync flag*/
	wait_queue_head_t		wq;
	
	int cpcrash_flag;
	int cpreset_flag;
	int cpdump_flag;
	int boot_done;
	int ready_to_boot;
	int reset_flag;
	int reset_count;
	struct completion *l2_done;
	struct completion *l3_done;
	struct completion *wait_boot_done;
#ifdef CONFIG_HAS_WAKELOCK
	struct wake_lock reset_lock;
#endif
	int debug_cnt;
};

extern struct platform_device modemctl;


void crash_event(int type);
extern int mc_is_suspend_request(void);
extern int mc_prepare_resume(int);
extern int mc_reconnect_gpio(void);
#endif /* __MODEM_CONTROL_H__ */
