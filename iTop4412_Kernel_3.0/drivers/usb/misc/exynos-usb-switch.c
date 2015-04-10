/*
 * exynos-usb-switch.c - USB switch driver for Exynos
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 * Yulgon Kim <yulgon.kim@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>

#include <plat/devs.h>
#include <plat/ehci.h>
#include <plat/usbgadget.h>

#include <mach/regs-clock.h>

#include <plat/gpio-cfg.h>

#include "../gadget/s3c_udc.h"
#include "exynos-usb-switch.h"

#define DRIVER_DESC "Exynos USB Device Driver"

static const char switch_name[] = "exynos_usb_Device";

#ifdef CONFIG_PM
static int exynos_usbswitch_suspend(struct device *dev)
{
	struct s3c_udc *udc = the_controller;

        udc->gadget.ops->vbus_session(&udc->gadget, 0);

#if 1 //cym
#ifdef CONFIG_CPU_TYPE_SCP
	#define GPIO_HUB_RESET EXYNOS4212_GPM2(4)
	#define GPIO_HUB_CONNECT EXYNOS4212_GPM3(3)
#else
	#define GPIO_HUB_RESET EXYNOS4_GPL2(2)
	//#define GPIO_HUB_CONNECT EXYNOS4_GPK3(2)
#endif
        gpio_request(GPIO_HUB_RESET, "GPIO_HUB_RESET");
        gpio_direction_output(GPIO_HUB_RESET, 0);
        s3c_gpio_setpull(GPIO_HUB_RESET, S3C_GPIO_PULL_NONE);
        gpio_free(GPIO_HUB_RESET);

        // HUB_CONNECT
#ifdef CONFIG_CPU_TYPE_SCP
        gpio_request(GPIO_HUB_CONNECT, "GPIO_HUB_CONNECT");
        gpio_direction_output(GPIO_HUB_CONNECT, 0);
        s3c_gpio_setpull(GPIO_HUB_CONNECT, S3C_GPIO_PULL_NONE);
        gpio_free(GPIO_HUB_CONNECT);
#endif
#endif

	return 0;
}

static int exynos_usbswitch_resume(struct device *dev)
{
	struct s3c_udc *udc = the_controller;

	printk("USB_DEVICE_ATTACHED\n");
	udc->gadget.ops->vbus_session(&udc->gadget, 1);
	return 0;
}
#else
#define exynos_usbswitch_suspend	NULL
#define exynos_usbswitch_resume		NULL
#endif

static int __devinit exynos_usbswitch_probe(struct platform_device *pdev)
{
	struct s3c_udc *udc = the_controller;

	printk("USB_DEVICE_ATTACHED\n");
	udc->gadget.ops->vbus_session(&udc->gadget, 1);

	return 0;
}

static int __devexit exynos_usbswitch_remove(struct platform_device *pdev)
{
	return 0;
}

static const struct dev_pm_ops exynos_usbswitch_pm_ops = {
	.suspend                = exynos_usbswitch_suspend,
	.resume                 = exynos_usbswitch_resume,
};

static struct platform_driver exynos_usbswitch_driver = {
	.probe		= exynos_usbswitch_probe,
	.remove		= __devexit_p(exynos_usbswitch_remove),
	.driver		= {
		.name	= "exynos-usb-switch",
		.owner	= THIS_MODULE,
		.pm	= &exynos_usbswitch_pm_ops,
	},
};

static int __init exynos_usbswitch_init(void)
{
	int ret;

	ret = platform_device_register(&s5p_device_usbswitch);
	if (ret < 0)
		return ret;

	ret = platform_driver_register(&exynos_usbswitch_driver);
	if (!ret)
		printk(KERN_INFO "%s: " DRIVER_DESC "\n", switch_name);

	return ret;
}
late_initcall(exynos_usbswitch_init);

static void __exit exynos_usbswitch_exit(void)
{
	platform_driver_unregister(&exynos_usbswitch_driver);
}
module_exit(exynos_usbswitch_exit);

MODULE_DESCRIPTION("Exynos USB device driver");
MODULE_AUTHOR("<caoym@topeet.com>");
MODULE_LICENSE("GPL");
