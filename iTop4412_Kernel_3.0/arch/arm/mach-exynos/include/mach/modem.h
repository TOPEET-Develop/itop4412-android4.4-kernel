/* linux/arch/arm/mach-s5pv310/include/mach/modem.h
 *
 * Copyright (c) 2011 Samsung Electronics Co.Ltd
 *		
 *
 *
 * Based on arch/arm/mach-s5p6442/include/mach/io.h
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __MODEM_H
#define __MODEM_H

/* modify by cym 20130419 */
#if 0
#define GPIO_PHONE_ON		EXYNOS4_GPC0(0)	//power on cp
#define GPIO_PHONE_ACTIVE	S5PV310_GPX0(7)	// NC
#define GPIO_PDA_ACTIVE		S5PV310_GPK1(0)	// NC
#define GPIO_CP_DUMP_INT	S5PV310_GPL0(5)	// NC
#define GPIO_CP_RST			EXYNOS4_GPL2(1)	//reset cp
#define GPIO_CP_PMU_RST	EXYNOS4_GPC0(2)	//reset cp pmu
#define GPIO_CP_REQ_RST	S5PV310_GPL0(6)	// NC
#define GPIO_CP_ABNORMAL_RESET_INT	S5PV310_GPX1(3)	//NC lisw //cp -> ap abnormal reset
#define GPIO_IPC_SLAVE_WAKEUP	EXYNOS4_GPC0(4)	//ap -> cp wakeup slave
#define GPIO_IPC_HOST_WAKEUP	EXYNOS4_GPX2(5)	//cp -> ap wakeup host
#define GPIO_SUSPEND_REQUEST	EXYNOS4_GPX1(6)	//cp -> ap request sleep
#define GPIO_ISP_INT		S5PV310_GPL0(7)	// NC
#define GPIO_ACTIVE_STATE	EXYNOS4_GPC0(3)		//ap active state
#define GPIO_CP_RESET_REPORT	EXYNOS4_GPX3(2)		//CP reset ,CP->AP

#define GPIO_XUJIE_MONITOR    EXYNOS4_GPL2(6)		//test

#define IRQ_PHONE_ACTIVE	IRQ_EINT7 //NC
#define IRQ_SUSPEND_REQUEST	IRQ_EINT12
#define IRQ_IPC_HOST_WAKEUP	IRQ_EINT14
#else
#define GPIO_PHONE_ON		EXYNOS4_GPX2(6) // daohang EXYNOS4_GPX3(3)	//power on cp	diff

#define GPIO_CP_RST			EXYNOS4_GPL2(1)	//reset cp
#define GPIO_CP_PMU_RST	EXYNOS4_GPC0(2)	//reset cp pmu

#define GPIO_CP_ABNORMAL_RESET_INT	S5PV310_GPX1(3)	//NC lisw //cp -> ap abnormal reset
#define GPIO_IPC_SLAVE_WAKEUP	EXYNOS4_GPC0(4)	//ap -> cp wakeup slave

#define GPIO_IPC_HOST_WAKEUP	EXYNOS4_GPX2(4) //daohang sch EXYNOS4_GPX3(0)	//cp -> ap wakeup host		diff

#define GPIO_SUSPEND_REQUEST	EXYNOS4_GPX1(6)	//cp -> ap request sleep

#define GPIO_ACTIVE_STATE	EXYNOS4_GPC0(3)		//ap active state
#define GPIO_CP_RESET_REPORT	EXYNOS4_GPX3(4)//daohang EXYNOS4_GPX3(2)		//CP reset ,CP->AP

#define GPIO_XUJIE_MONITOR    EXYNOS4_GPL2(6)		//test

#define IRQ_PHONE_ACTIVE	IRQ_EINT7 //NC
#define IRQ_SUSPEND_REQUEST	IRQ_EINT12
#define IRQ_IPC_HOST_WAKEUP	IRQ_EINT14
#endif

#define HOST_WUP_LEVEL 0

struct modem_ops {
	void (*modem_on)(void);
	void (*modem_off)(void);
	void (*modem_reset)(void);
	void (*modem_boot)(void);
	void (*modem_suspend)(void);
	void (*modem_resume)(void);
	void (*modem_cfg)(void);
};

struct modem_platform_data {
	const char *name;
	unsigned gpio_phone_on;
	unsigned gpio_phone_active;
	unsigned gpio_pda_active;
	unsigned gpio_cp_reset;
	unsigned gpio_usim_boot;
	unsigned gpio_flm_sel;
	unsigned gpio_cp_req_reset;	/*HSIC*/
	unsigned gpio_ipc_slave_wakeup;
	unsigned gpio_ipc_host_wakeup;
	unsigned gpio_suspend_request;
	unsigned gpio_active_state;
	unsigned gpio_cp_dump_int;
	unsigned gpio_cp_reset_int;
	int wakeup;
	struct modem_ops ops;
};

extern struct platform_device smm6260_modem;
extern int smm6260_is_on(void);
extern int smm6260_is_host_wakeup(void);
extern int smm6260_set_active_state(int val);
extern int smm6260_set_slave_wakeup(int val);
#endif//__MODEM_H
