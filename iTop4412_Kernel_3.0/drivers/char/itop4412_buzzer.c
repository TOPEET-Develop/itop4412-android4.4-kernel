/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/backlight.h>
#include <linux/err.h>
#include <linux/pwm.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>

#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>

#include <asm/uaccess.h>


#define DEVICE_NAME				"buzzer_ctl"
#define DRIVER_NAME "buzzer_ctl"


#define BUZZER_GPIO			EXYNOS4_GPD0(0)



static int itop4412_buzzer_open(struct inode *inode, struct file *file) {
		return 0;
}

static int itop4412_buzzer_close(struct inode *inode, struct file *file) {
	return 0;
}

static long itop4412_buzzer_ioctl(struct file *filep, unsigned int cmd,
		unsigned long arg)
{
	printk("%s: cmd = %d\n", __FUNCTION__, cmd);
	switch(cmd) {
		case 0:
			gpio_set_value(BUZZER_GPIO, 0);
			break;
		case 1:
			gpio_set_value(BUZZER_GPIO, 1);
			break;
		default:
			return -EINVAL;
	}

	return 0;
}

static ssize_t itop4412_buzzer_write(struct file *filp, char *buffer, size_t count, loff_t *ppos)
{
	char str[20];

	memset(str, 0, 20);

	if(copy_from_user(str, buffer, count))
	{
		printk("Error\n");

		return -EINVAL;
	}

	printk("%s", str);
#if 1
	if(!strncmp(str, "1", 1))
		gpio_set_value(BUZZER_GPIO, 1);
	else
		gpio_set_value(BUZZER_GPIO, 0);
#endif
	//gpio_set_value(BUZZER_GPIO, 1);
	return count;
}

static struct file_operations itop4412_buzzer_ops = {
	.owner			= THIS_MODULE,
	.open			= itop4412_buzzer_open,
	.release		= itop4412_buzzer_close, 
	.unlocked_ioctl	= itop4412_buzzer_ioctl,
	.write			= itop4412_buzzer_write,
};

static struct miscdevice itop4412_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &itop4412_buzzer_ops,
};

static int itop4412_buzzer_probe(struct platform_device *pdev)
{
	int ret;

	ret = gpio_request(BUZZER_GPIO, DEVICE_NAME);
	if (ret) {
		printk("request GPIO %d for pwm failed\n", BUZZER_GPIO);
		return ret;
	}

	s3c_gpio_cfgpin(BUZZER_GPIO, S3C_GPIO_OUTPUT);
	gpio_set_value(BUZZER_GPIO, 0);

	ret = misc_register(&itop4412_misc_dev);

	printk(DEVICE_NAME "\tinitialized\n");

	return 0;
}

static int itop4412_buzzer_remove (struct platform_device *pdev)
{
	misc_deregister(&itop4412_misc_dev);
	gpio_free(BUZZER_GPIO);	

	return 0;
}

static int itop4412_buzzer_suspend (struct platform_device *pdev, pm_message_t state)
{
	printk("buzzer_ctl suspend:power off!\n");
	return 0;
}

static int itop4412_buzzer_resume (struct platform_device *pdev)
{
	printk("buzzer_ctl resume:power on!\n");
	return 0;
}

static struct platform_driver itop4412_buzzer_driver = {
	.probe = itop4412_buzzer_probe,
	.remove = itop4412_buzzer_remove,
	.suspend = itop4412_buzzer_suspend,
	.resume = itop4412_buzzer_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	},
};

static int __init itop4412_buzzer_dev_init(void) {
	return platform_driver_register(&itop4412_buzzer_driver);
}

static void __exit itop4412_buzzer_dev_exit(void) {
	platform_driver_unregister(&itop4412_buzzer_driver);
}

module_init(itop4412_buzzer_dev_init);
module_exit(itop4412_buzzer_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TOPEET Inc.");
MODULE_DESCRIPTION("Exynos4 BUZZER Driver");

