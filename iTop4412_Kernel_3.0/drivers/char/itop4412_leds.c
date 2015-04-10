#include <linux/init.h>
#include <linux/module.h>

#include <linux/kernel.h>
#include <linux/fs.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
//#include <mach/gpio-bank.h>
#include <mach/regs-gpio.h>
#include <asm/io.h>
#include <linux/regulator/consumer.h>
//#include "gps.h"
#include <linux/delay.h>

#define LEDS_DEBUG
#ifdef LEDS_DEBUG
#define DPRINTK(x...) printk("LEDS_CTL DEBUG:" x)
#else
#define DPRINTK(x...)
#endif

#define DRIVER_NAME "leds"

static int led_gpios[] = {
	EXYNOS4_GPL2(0),
	EXYNOS4_GPK1(1),
};

#define LED_NUM		ARRAY_SIZE(led_gpios)

int leds_open(struct inode *inode,struct file *filp)
{
	DPRINTK("Device Opened Success!\n");
	return nonseekable_open(inode,filp);
}

int leds_release(struct inode *inode,struct file *filp)
{
	DPRINTK("Device Closed Success!\n");
	return 0;
}

int leds_pm(bool enable)
{
	int ret = 0;
	printk("debug: LEDS PM return %d\r\n" , ret);
	return ret;
};

long leds_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	printk("debug: leds_ioctl cmd is %d\n" , cmd);

	switch(cmd)
	{
		case 0:
		case 1:
			if (arg > LED_NUM) {
				return -EINVAL;
			}

			gpio_set_value(led_gpios[arg], cmd);
			break;

		default:
			return -EINVAL;
	}

	return 0;
}

static struct file_operations leds_ops = {
	.owner 	= THIS_MODULE,
	.open 	= leds_open,
	.release= leds_release,
	.unlocked_ioctl 	= leds_ioctl,
};

static struct miscdevice leds_dev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.fops	= &leds_ops,
	.name	= "leds",
};


static int leds_probe(struct platform_device *pdev)
{
	int ret, i;
	char *banner = "leds Initialize\n";

	printk(banner);

	for(i=0; i<LED_NUM; i++)
	{
		ret = gpio_request(led_gpios[i], "LED");
		if (ret) {
			printk("%s: request GPIO %d for LED failed, ret = %d\n", DRIVER_NAME,
					led_gpios[i], ret);
			return ret;
		}

		s3c_gpio_cfgpin(led_gpios[i], S3C_GPIO_OUTPUT);
		gpio_set_value(led_gpios[i], 1);
	}

	ret = misc_register(&leds_dev);
	if(ret<0)
	{
		printk("leds:register device failed!\n");
		goto exit;
	}

	return 0;

exit:
	misc_deregister(&leds_dev);
	return ret;
}

static int leds_remove (struct platform_device *pdev)
{
	misc_deregister(&leds_dev);	

	return 0;
}

static int leds_suspend (struct platform_device *pdev, pm_message_t state)
{
	DPRINTK("leds suspend:power off!\n");
	return 0;
}

static int leds_resume (struct platform_device *pdev)
{
	DPRINTK("leds resume:power on!\n");
	return 0;
}

static struct platform_driver leds_driver = {
	.probe = leds_probe,
	.remove = leds_remove,
	.suspend = leds_suspend,
	.resume = leds_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	},
};

static void __exit leds_exit(void)
{
	platform_driver_unregister(&leds_driver);
}

static int __init leds_init(void)
{
	return platform_driver_register(&leds_driver);
}

module_init(leds_init);
module_exit(leds_exit);

MODULE_LICENSE("Dual BSD/GPL");
