/*
 * SMM6260 GPIO driver
 * Author: Sheng Liang <liang.sheng@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/io.h>
#include <linux/gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/regs-gpio.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>

/* Definitions */
#define SMM6260_DOWNLOAD_MODE 0

#define SMM6260_DBG_LEVEL_ON 1
#define SMM6260_DBG_LEVEL_FUNC 2
#define SMM6260_DBG_LEVEL_DATA 4
int dbg_level = SMM6260_DBG_LEVEL_ON | SMM6260_DBG_LEVEL_FUNC | SMM6260_DBG_LEVEL_DATA;
#define SMM6260_DBG(level, fmt, args...)  do{ if( (level&dbg_level)>0 ) \
	printk( KERN_INFO "[SMM6260]: " fmt, ## args); }while(0)

/* Modem MU739 / SMM6260
 *
 * GPC0_0 MD_PWON
 * GPC0_2 MD_RSTN
 * GPL2_1 MD_RESETBB
 */
 /* modify by cym 20130419 */
#if 0
#define GPIO_MD_PWON	EXYNOS4_GPC0(0)
#define GPIO_MD_RSTN	EXYNOS4_GPC0(2)
#define GPIO_MD_RESETBB	EXYNOS4_GPL2(1)
#else
#define GPIO_MD_PWON	EXYNOS4_GPX3(3)
#define GPIO_MD_RSTN	EXYNOS4_GPC0(2)
#define GPIO_MD_RESETBB	EXYNOS4_GPL2(1)
#endif
/* end modify */

/* Modem GPIO
 *
 * GPC0_3	AP_SLEEP		HSIC_HOST_ACTIVE
 * GPC0_4	AP_WAKEUP_MD		HSIC_SLAVE_WAKEUP
 * GPX2_5	MD_WAKEUP_AP		HSIC_HOST_WAKEUP
 * GPX1_6	MD_SLEEP_REQUEST	HSIC_HOST_SUSREQ
 */
#define HSIC_HOST_ACTIVE	EXYNOS4_GPC0(3)
#define HSIC_SLAVE_WAKEUP	EXYNOS4_GPC0(4)
/* modify by cym 20130419 */
#if 0
#define HSIC_HOST_WAKEUP	EXYNOS4_GPX2(5)
#else
#define HSIC_HOST_WAKEUP	EXYNOS4_GPX3(0)
#endif
/* end modify */
#define HSIC_HOST_SUSREQ	EXYNOS4_GPX1(6)

/* remove by cym 20130419 */
#if 0
#define NFC_EN1		EXYNOS4_GPL0(3)
#endif
/* end remove */
// I don't know what are those used for...
/* modify by cym 20130419 */
#if 0
#define GPIO_MD_B14	EXYNOS4_GPX2(4)
#define GPIO_MD_L15		EXYNOS4_GPX3(5)
#define GPIO_MD_G15	EXYNOS4_GPF3(5)
#else
#define GPIO_MD_B14	EXYNOS4_GPX3(1)
#define GPIO_MD_L15		EXYNOS4_GPX0(1)
#define GPIO_MD_G15	EXYNOS4_GPF3(5)
#endif

/* Variables */
//static struct delayed_work smm6260_gpio_delayed_work;
//static struct completion smm6260_done;

/* Functions */
static void smm6260_gpio_cfg()
{
	int err = 0;

	SMM6260_DBG(SMM6260_DBG_LEVEL_FUNC, "%s()\n", __FUNCTION__);
	// Modem power
	err = gpio_request(GPIO_MD_PWON, "GPIO_MD_PWON");
	if (err)
		printk("fail to request gpio %s\n", "GPIO_MD_PWON");
	else
	{
		gpio_direction_output(GPIO_MD_PWON, 1);
		s3c_gpio_setpull(GPIO_MD_PWON, S3C_GPIO_PULL_NONE);
	}

	err = gpio_request(GPIO_MD_RSTN, "GPIO_MD_RSTN");
	if (err)
		printk("fail to request gpio %s\n", "GPIO_MD_RSTN");
	else
	{
		gpio_direction_output(GPIO_MD_RSTN, 1);
		s3c_gpio_setpull(GPIO_MD_RSTN, S3C_GPIO_PULL_NONE);// TODO, liang
	}

	err = gpio_request(GPIO_MD_RESETBB, "GPIO_MD_RESETBB");
	if (err)
		printk("fail to request gpio %s\n", "GPIO_MD_RESETBB");
	else
	{
		gpio_direction_output(GPIO_MD_RESETBB, 1);
		s3c_gpio_setpull(GPIO_MD_RESETBB, S3C_GPIO_PULL_NONE);// TODO, liang
	}

#if 1
	gpio_request(GPIO_MD_B14, "GPIO_MD_B14");
	s3c_gpio_setpull(GPIO_MD_B14, S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(GPIO_MD_B14, S3C_GPIO_INPUT);
	gpio_free(GPIO_MD_B14);

	gpio_request(GPIO_MD_L15, "GPIO_MD_L15");
	s3c_gpio_setpull(GPIO_MD_L15, S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(GPIO_MD_L15, S3C_GPIO_INPUT);
	gpio_free(GPIO_MD_L15);

	gpio_request(GPIO_MD_G15, "GPIO_MD_G15");
	s3c_gpio_setpull(GPIO_MD_G15, S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(GPIO_MD_G15, S3C_GPIO_INPUT);
	gpio_free(GPIO_MD_G15);

/* remove by cym 20130419 */
#if 0
	gpio_request(NFC_EN1, "NFC_EN1");
	gpio_direction_output(NFC_EN1, 1);
	s3c_gpio_setpull(NFC_EN1, S3C_GPIO_PULL_NONE);
	gpio_free(NFC_EN1);
#endif
/* end remove */
#endif

#if SMM6260_DOWNLOAD_MODE// all input, for download test only.
	gpio_request(HSIC_HOST_ACTIVE, "HSIC_HOST_ACTIVE");
	s3c_gpio_setpull(HSIC_HOST_ACTIVE, S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(HSIC_HOST_ACTIVE, S3C_GPIO_INPUT);
	gpio_free(HSIC_HOST_ACTIVE);

	gpio_request(HSIC_SLAVE_WAKEUP, "HSIC_SLAVE_WAKEUP");
	s3c_gpio_setpull(HSIC_SLAVE_WAKEUP, S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(HSIC_SLAVE_WAKEUP, S3C_GPIO_INPUT);
	gpio_free(HSIC_SLAVE_WAKEUP);

	gpio_request(HSIC_HOST_WAKEUP, "HSIC_HOST_WAKEUP");
	s3c_gpio_setpull(HSIC_HOST_WAKEUP, S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(HSIC_HOST_WAKEUP, S3C_GPIO_INPUT);
	gpio_free(HSIC_HOST_WAKEUP);

	gpio_request(HSIC_HOST_SUSREQ, "HSIC_HOST_SUSREQ");
	s3c_gpio_setpull(HSIC_HOST_SUSREQ, S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(HSIC_HOST_SUSREQ, S3C_GPIO_INPUT);
	gpio_free(HSIC_HOST_SUSREQ);
#else
	// Modem GPIOs
	err = gpio_request(HSIC_SLAVE_WAKEUP, "HSIC_SLAVE_WAKEUP");
	if (err)
		printk("fail to request gpio %s\n", "HSIC_SLAVE_WAKEUP");
	else
	{
		gpio_direction_output(HSIC_SLAVE_WAKEUP, 0);
		//s3c_gpio_cfgpin(HSIC_SLAVE_WAKEUP, S3C_GPIO_OUTPUT);
		s3c_gpio_setpull(HSIC_SLAVE_WAKEUP, S3C_GPIO_PULL_NONE);
	}

#if 1// EINT
	s3c_gpio_cfgpin(HSIC_HOST_WAKEUP, S3C_GPIO_SFN(0xf));
	s3c_gpio_setpull(HSIC_HOST_WAKEUP, S3C_GPIO_PULL_DOWN);
#else
	err = gpio_request(HSIC_HOST_WAKEUP, "HSIC_HOST_WAKEUP");
	if (err)
		printk("fail to request gpio %s\n", "HSIC_HOST_WAKEUP");
	else
	{
		gpio_direction_output(HSIC_HOST_WAKEUP, 0);
		s3c_gpio_cfgpin(HSIC_HOST_WAKEUP, S3C_GPIO_INPUT);
		s3c_gpio_setpull(HSIC_HOST_WAKEUP, S3C_GPIO_PULL_DOWN);
	}
#endif

	err = gpio_request(HSIC_HOST_SUSREQ, "HSIC_HOST_SUSREQ");
	if (err)
		printk("fail to request gpio %s\n", "HSIC_HOST_SUSREQ");
	else
	{
		gpio_direction_output(HSIC_HOST_SUSREQ, 0);
		s3c_gpio_cfgpin(HSIC_HOST_SUSREQ, S3C_GPIO_INPUT);
		s3c_gpio_setpull(HSIC_HOST_SUSREQ, S3C_GPIO_PULL_DOWN);
	}

	err = gpio_request(HSIC_HOST_ACTIVE, "HSIC_HOST_ACTIVE");
	if (err)
		printk("fail to request gpio %s\n", "HSIC_HOST_ACTIVE");
	else
	{
		gpio_direction_output(HSIC_HOST_ACTIVE, 0);
		//s3c_gpio_cfgpin(HSIC_HOST_ACTIVE, S3C_GPIO_OUTPUT);
		s3c_gpio_setpull(HSIC_HOST_ACTIVE, S3C_GPIO_PULL_NONE);
	}
#endif
}

void set_hsic_host_active(int val)
{
	SMM6260_DBG(SMM6260_DBG_LEVEL_DATA, "%s %s\n", __FUNCTION__, val?"high":"low");
	if(val)
		gpio_set_value(HSIC_HOST_ACTIVE, 1);
	else
		gpio_set_value(HSIC_HOST_ACTIVE, 0);
}

#if 0
#ifdef CONFIG_USB_EHCI_S5P
extern void exynos4412_ehci_power(int power_on);
#endif
static void smm6260_gpio_delayed_work_func(struct work_struct *work)
{
	int val = 0;
	int i = 0;

	SMM6260_DBG(SMM6260_DBG_LEVEL_FUNC, "%s()\n", __FUNCTION__);

	//smm6260_gpio_cfg();

#if SMM6260_DOWNLOAD_MODE
	//gpio_set_value(GPIO_MD_RSTN, 1);
//	gpio_set_value(GPIO_MD_RESETBB, 1);
	//msleep(10);
	//gpio_set_value(GPIO_MD_PWON, 1);
#else
	/* Step 1. AP powered up and completed OS boot up. HSIC EHCI controller is OFF at this stage.
	 * AP drives HSIC_HOST_ACTIVE GPIO signal low (0V).
	 */
#ifdef CONFIG_USB_EHCI_S5P
//	SMM6260_DBG(SMM6260_DBG_LEVEL_FUNC, "ehci power off\n");
//	exynos4412_ehci_power(0);
#endif
//	gpio_set_value(HSIC_HOST_ACTIVE, 0);
//	msleep(100);
	enable_irq_wake(gpio_to_irq(HSIC_HOST_WAKEUP));

#if 0
	val = gpio_get_value(HSIC_HOST_WAKEUP);
	printk("step 1. HSIC_HOST_WAKEUP: %d\n", val);
#endif

	/* Step 2. At any given time, AP powers CP on.
	 * CP drives HSIC_HOST_WAKEUP GPIO signal high (1.8V) and then low (0V) during boot up phase.
	 */
	// Must set reset high first, otherwise Modem may die...
//	SMM6260_DBG(SMM6260_DBG_LEVEL_FUNC, "smm6260 modem power on\n");
//	gpio_set_value(GPIO_MD_RESETBB, 1);
//	msleep(1);
//	gpio_set_value(GPIO_MD_RSTN, 1);
//	msleep(50);
//	gpio_set_value(GPIO_MD_PWON, 1);
	
//	msleep(100);

#if 0
	val = gpio_get_value(HSIC_HOST_WAKEUP);
	printk("step 2. HSIC_HOST_WAKEUP: %d\n", val);
#endif

	/* Step 3. CP completed boot up and starts HSIC Extended Link Power Management (ELPM) initialization
	 * During ELPM initialization, CP drives HSIC_HOST_WAKEUP high again.
	 */
//	msleep(5000);
#if 0
	val = gpio_get_value(HSIC_HOST_WAKEUP);
	printk("step 3. HSIC_HOST_WAKEUP: %d\n", val);
#endif

	/* Step 4. CP completed ELPM initialization
	 * Now, CP drives HSIC_HOST_WAKEUP low. CP HSIC device controller is OFF at this stage.
	 * Note: The AP can use the HSIC_HOST_WAKEUP falling edge (of stage 4) to trigger the transition to steps 5.
	 */

	/* Step 5. AP turns on HSIC EHCI controller.
	 * Note: Make sure that EHCI controller is ready (IDLE on the bus) before continuing step 6.
	 */
#ifdef CONFIG_USB_EHCI_S5P
	SMM6260_DBG(SMM6260_DBG_LEVEL_FUNC, "ehci power on\n");
//	exynos4412_ehci_power(1);
#endif
//	msleep(100);

	/* Step 6. AP drives HSIC_HOST_ACTIVE high.
	 */
	gpio_set_value(HSIC_HOST_ACTIVE, 1);
	//msleep(100);

	/* Step 7. CP detects HSIC_HOST_ACTIVE goes high interrupt.
	 * Upon detection, CP turns on HSIC device controller.
	 * Then CP sets CONNECT bus state.
	 * AP sends RESET, SOF, GET DESCRIPTOR, etc...
	 */

	/* Step 8. Upon successful completion of the enumeration sequence, CP drives the HSIC_HOST_WAKEUP high.
	 */

#endif
}
#endif
#if 0
int strtoint(const char *str,int len)
{
	int result = 0;
	int i = 0;
	char c;
	while(i <= len-1)
	{   
		c = str[i++];
		if(c<'0' || c>'9')
			break;
		result = 10*result + c - '0';
	}
	return result;
}
#endif

static ssize_t smm6260_gpio_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s()\n", __FUNCTION__);
}

static ssize_t smm6260_gpio_store(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t count)
{
	int retval = 0;
	printk("%d : %s\n", count, buf);
	return retval;
}

/*
 * sysfs: /sys/devices/platform/smm6260-gpio
 * usage: echo x > /sys/devices/platform/smm6260-gpio/smm6260-gpio
 */
static DEVICE_ATTR(smm6260_gpio, S_IRUGO | S_IWUGO, smm6260_gpio_show, smm6260_gpio_store);

static irqreturn_t modem_resume_thread(int irq, void *dev_id)
{
	int val = gpio_get_value(HSIC_HOST_WAKEUP);
	SMM6260_DBG(SMM6260_DBG_LEVEL_DATA, "%s(), HSIC_HOST_WAKEUP: %d\n", __FUNCTION__, val);
	return IRQ_HANDLED;
}

static int __devinit smm6260_gpio_probe(struct platform_device *pdev)
{
	int err;
	int irq;

	err = device_create_file(&pdev->dev, &dev_attr_smm6260_gpio);
	if (err)
		goto error1;

	//INIT_DELAYED_WORK(&smm6260_gpio_delayed_work, smm6260_gpio_delayed_work_func);
	//schedule_delayed_work(&smm6260_gpio_delayed_work, msecs_to_jiffies(5000));

	//init_completion(&smm6260_done);

#if 1
	irq = gpio_to_irq(HSIC_HOST_WAKEUP);
	err = request_threaded_irq(irq, NULL, modem_resume_thread,
			IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			"IPC_HOST_WAKEUP", NULL);
	if(err)
	{
		dev_err(&pdev->dev, "Resume thread Failed to allocate an interrupt(%d)\n", irq);
		goto error2;
	}
	//disable_irq_wake(irq);
	enable_irq_wake(irq);
#endif

	smm6260_gpio_cfg();

	SMM6260_DBG(SMM6260_DBG_LEVEL_ON, "%s() success\n", __FUNCTION__);

	return 0;

error2:
	device_remove_file(&pdev->dev, &dev_attr_smm6260_gpio);
error1:
	return err;
}

static int __devexit smm6260_gpio_remove(struct platform_device *dev)
{
	return 0;
}

#ifdef CONFIG_PM
static int smm6260_gpio_suspend(struct platform_device *pdev, pm_message_t state)
{
	return 0;
}

static int smm6260_gpio_resume(struct platform_device *pdev)
{
	return 0;
}
#else
#define smm6260_gpio_suspend NULL
#define smm6260_gpio_resume  NULL
#endif

static struct platform_driver smm6260_gpio_driver = {
	.probe		= smm6260_gpio_probe,
	.remove		= __devexit_p(smm6260_gpio_remove),
	.suspend	= smm6260_gpio_suspend,
	.resume		= smm6260_gpio_resume,
	.driver		= {
		.name	= "smm6260-gpio",
		.owner	= THIS_MODULE,
	},
};

static char __initdata banner[] = "SMM6260 GPIO\n";

static int __init smm6260_gpio_init(void)
{
	printk(banner);
	return platform_driver_register(&smm6260_gpio_driver);
}

static void __exit smm6260_gpio_exit(void)
{
	platform_driver_unregister(&smm6260_gpio_driver);
}

module_init(smm6260_gpio_init);
module_exit(smm6260_gpio_exit);

MODULE_DESCRIPTION("GPIO for SMM6260");
MODULE_AUTHOR("Sheng Liang <liang.sheng@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:smm6260-gpio");
