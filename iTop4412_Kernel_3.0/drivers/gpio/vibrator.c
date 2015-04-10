/*
 * Vibrator driver
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

//#include <mach/gpio-v8.h>

/* Variables */
static struct delayed_work vib_delayed_work;

/* Definitions */
#define VIB_TEST	0

#define GPIO_VIBCTL		EXYNOS4_GPD0(0)

#define CFG_VIB_CTRL	do {\
	gpio_request(GPIO_VIBCTL, "MOTOR_PWM");\
	s3c_gpio_cfgpin(GPIO_VIBCTL,S3C_GPIO_OUTPUT);\
	s3c_gpio_setpull(GPIO_VIBCTL,S3C_GPIO_PULL_NONE);\
} while(0)

#define VIB_START do {\
	gpio_set_value(GPIO_VIBCTL, 1);\
} while(0)

#define VIB_STOP do {\
	gpio_set_value(GPIO_VIBCTL, 0);\
} while(0)

#define RELEASE_VIB do {\
	gpio_free(GPIO_VIBCTL);\
} while(0)

#ifndef CONFIG_TC4_DVT
 #define USE_MOTOR_8997
#else
 #undef USE_MOTOR_8997
#endif

#ifdef USE_MOTOR_8997
extern void motor8997_on(int on);
#endif

/* Functions */
static void vib_delayed_work_func(struct work_struct *work)
{
#ifdef USE_MOTOR_8997
	motor8997_on(0);
#else
	VIB_STOP;
#endif
}

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

static ssize_t vib_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	return printk("write a number in to vibrate\n");
}

static ssize_t vib_store(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t count)
{
	int retval;
	int value;
	value = strtoint(buf,count);
#if VIB_TEST
	printk("count:%d, buf:%s",count,buf);
	printk("inv:%d ms\n",value);
#endif
	retval = count;
	if(value)
	{
#ifdef USE_MOTOR_8997
		motor8997_on(1);
#else
		VIB_START;
#endif
		schedule_delayed_work(&vib_delayed_work, msecs_to_jiffies(value));
	}
	else
	{
#ifdef USE_MOTOR_8997
		motor8997_on(0);
#else
		VIB_STOP;
#endif
	}
	return retval;
}

/*
 * sysfs: /sys/devices/platform/s5p-vib
 * usage: echo ms > /sys/devices/platform/s5p-vib/vib
 */
static DEVICE_ATTR(vib, S_IRUGO | S_IWUSR, vib_show, vib_store);

static int __devinit s3c_vib_probe(struct platform_device *pdev)
{
	int err;
	err = device_create_file(&pdev->dev, &dev_attr_vib);
	if (err)
		goto error1;

	/* delayed work */
	INIT_DELAYED_WORK(&vib_delayed_work, vib_delayed_work_func);

	CFG_VIB_CTRL;

#if VIB_TEST
#ifdef USE_MOTOR_8997
	motor8997_on(1);
#else
	VIB_START;
#endif
	schedule_delayed_work(&vib_delayed_work, msecs_to_jiffies(1000));
#endif
	printk("vibrator probe success\n");

	return 0;

error1:
	return err;
}

static int __devexit s3c_vib_remove(struct platform_device *dev)
{
	RELEASE_VIB;
	return 0;
}

#ifdef CONFIG_PM
static int s3c_vib_suspend(struct platform_device *pdev, pm_message_t state)
{
#ifdef USE_MOTOR_8997
	motor8997_on(0);
#else
	VIB_STOP;
#endif
	return 0;
}

static int s3c_vib_resume(struct platform_device *pdev)
{
	return 0;
}
#else
#define s3c_vib_suspend NULL
#define s3c_vib_resume  NULL
#endif

static struct platform_driver s5p_vib_driver = {
	.probe		= s3c_vib_probe,
	.remove		= __devexit_p(s3c_vib_remove),
	.suspend	= s3c_vib_suspend,
	.resume		= s3c_vib_resume,
	.driver		= {
		.name	= "s5p-vib",
		.owner	= THIS_MODULE,
	},
};

static char __initdata banner[] = "S5P VIBRATOR\n";

static int __init s3c_vib_init(void)
{
	printk(banner);
	return platform_driver_register(&s5p_vib_driver);
}

static void __exit s3c_vib_exit(void)
{
	printk("%s()\n",__FUNCTION__);
	platform_driver_unregister(&s5p_vib_driver);
}

module_init(s3c_vib_init);
module_exit(s3c_vib_exit);

MODULE_DESCRIPTION("Samsung S3C Vibrator Driver");
MODULE_AUTHOR("Sheng Liang <liang.sheng@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s5p-vib");
