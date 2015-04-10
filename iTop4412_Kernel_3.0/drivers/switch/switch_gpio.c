/*
 *  drivers/switch/switch_gpio.c
 *
 * Copyright (C) 2008 Google, Inc.
 * Author: Mike Lockwood <lockwood@android.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
*/

/*******************************************************
	modify by cym support for switch head 20130409
********************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/switch.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/slab.h>

#include <linux/err.h>
#include <linux/delay.h>

/*
 * GPIO pin description for Switch
 *
 * - HP_DET   : GPX2_2 (WAKEUP_INT2[2])
 * - HOOK_DET : GPX1_3 (WAKEUP_INT1[3])
 * - UART_SW  : GPC1_0
 */


/*
 * HeadSet type definition
 */
//#define BIT_HEADSET             (1<<0)  // Speaker and Mic
//define BIT_HEADSET_NO_MIC      (1<<1)  // Only Speaker

static int switch_gpio_active = 0;
/*wenpin.cui: because initial detecion code has been moved to wm8994 driver, 
so initial state 0 will bring problem*/
static int switch_current_state = -1;

struct gpio_switch_data {
        struct switch_dev sdev;
        unsigned gpio;
        const char *name_on;
        const char *name_off;
        const char *state_on;
        const char *state_off;
        int irq;
        struct delayed_work work;
};

static int debug2hs_show(char *val, struct kernel_param *kp)
{
        int value = 0;
        int ret = param_set_int(val, kp);
        if(ret < 0) {
                printk(KERN_ERR"%s: Error param_set_int.\n", __FUNCTION__);
                return -EINVAL;
        }

        value = *((int*)kp->arg);
        printk(KERN_ALERT"\r\nxx value(%d) arg(%d)\r\n\r\n", value, switch_gpio_active);
        return 0;
}
#if 0
/*
 * on:
 *      true: Headset on
 *      false: UART on
 */
void debug_switch_to_hs(const unsigned int on)
{
	int ret = 0;
/* remove by cym 20130408 support for MT6600 PWU_EN */
#if 0
	ret = gpio_request(EXYNOS4_GPC1(0), "GPC1");
	if (ret < 0) {
		printk(KERN_ERR"fail to request S5PV310_GPC1(0) for UART_SW\n ");
		return;
	}

	s3c_gpio_cfgpin(EXYNOS4_GPC1(0), S3C_GPIO_OUTPUT);
	s3c_gpio_setpull(EXYNOS4_GPC1(0), S3C_GPIO_PULL_NONE);
	gpio_set_value(EXYNOS4_GPC1(0), ((!!on)? 1: 0));
	gpio_free(EXYNOS4_GPC1(0));
#endif
/* end remove */
	return;
}
#endif

static int debug2hs_store(const char *val, struct kernel_param *kp)
{
	int value;
	int ret = param_set_int(val, kp);

	if(ret < 0) {
		printk(KERN_ERR"%s: Error param_set_int.\n", __FUNCTION__);
		return -EINVAL;
	}

	value = *((int*)kp->arg);
	printk(KERN_ALERT"xx value = %d\n",value);
	//debug_switch_to_hs(value);
	return 0; 
}

static void gpio_switch_work(struct work_struct *work)
{
	int state = 0;
	struct delayed_work *dwork =  to_delayed_work(work);
	struct gpio_switch_data	*data =
		container_of(dwork, struct gpio_switch_data, work);

	// Get "physical" level(0: HS inserted, 1: HS removed)
	state = gpio_get_value(data->gpio);
	mdelay(10); 	// Wait before 2nd sampling to detect the changed status of HP_DET.
	if (state != gpio_get_value(data->gpio))
		return;

	//state = !state;	// Get the state from "physical" level(0: HS removed, 1: HS inserted)

	//debug_switch_to_hs(state? true: false);	/* switch between uart/hp */ 
	if (switch_current_state != state)
	{
		// Set the state and make the uevent to platfrom(HeadsetObserver).
		switch_set_state(&data->sdev, state);
		switch_current_state = state;
	}
	return;
}

static irqreturn_t gpio_irq_handler(int irq, void *dev_id)
{
	struct gpio_switch_data *switch_data =
		(struct gpio_switch_data *)dev_id;
#if 0
	if (switch_current_state) 
		;
	else /* noise coming */
		/* Turn off uart first to avoid noise made by trace */
		debug_switch_to_hs(true);
#endif
	/* wait for a long time to make sure voltage is stable*/
	schedule_delayed_work(&switch_data->work, HZ/2);
	return IRQ_HANDLED;
}

static ssize_t switch_gpio_print_state(struct switch_dev *sdev, char *buf)
{
#if 0
	struct gpio_switch_data	*switch_data =
		container_of(sdev, struct gpio_switch_data, sdev);
	const char *state;

	if (switch_get_state(sdev))
		state = switch_data->state_on;
	else
		state = switch_data->state_off;

	if (state)
		return sprintf(buf, "%s\n", state);
#endif
#if 0	
	if(0 == sdev->state)
		return sprintf(buf, "%s\n", "0");
	else
		return sprintf(buf, "%s\n", "1");
#else
	return sprintf(buf, "%s\n", "1");
#endif
	//return -1;
}

static int gpio_switch_probe(struct platform_device *pdev)
{
	struct gpio_switch_platform_data *pdata = pdev->dev.platform_data;
	struct gpio_switch_data *switch_data;
	int ret = 0;

	if (!pdata)
		return -EBUSY;

	switch_data = kzalloc(sizeof(struct gpio_switch_data), GFP_KERNEL);
	if (!switch_data)
		return -ENOMEM;

	switch_data->sdev.name = pdata->name;
	switch_data->gpio = pdata->gpio;
	switch_data->name_on = pdata->name_on;
	switch_data->name_off = pdata->name_off;
	switch_data->state_on = pdata->state_on;
	switch_data->state_off = pdata->state_off;
	switch_data->sdev.print_state = switch_gpio_print_state;

	ret = switch_dev_register(&switch_data->sdev);
	if (ret < 0)
		goto err_switch_dev_register;

	ret = gpio_request(switch_data->gpio, "GPX2");
	if (ret < 0)
		goto err_request_gpio;

	ret = gpio_direction_input(switch_data->gpio);
	if (ret < 0)
		goto err_set_gpio_input;

	s3c_gpio_setpull(switch_data->gpio, S3C_GPIO_PULL_NONE);

	INIT_DELAYED_WORK(&switch_data->work, gpio_switch_work);

	switch_data->irq = platform_get_irq(pdev, 0);   // WAKEUP_INT2[2]
	if (switch_data->irq < 0) {
		ret = switch_data->irq;
		goto err_detect_irq_num_failed;
	}

	ret = request_irq(switch_data->irq, gpio_irq_handler,
		(IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING), pdev->name, switch_data);

	if (ret < 0)
		goto err_request_irq;

	schedule_delayed_work(&switch_data->work, HZ/2);/*wenpin.cui: init check*/
	//debug_switch_to_hs(true);
		
	return 0;

err_request_irq:
err_detect_irq_num_failed:
err_set_gpio_input:
	gpio_free(switch_data->gpio);
err_request_gpio:
	switch_dev_unregister(&switch_data->sdev);
err_switch_dev_register:
	kfree(switch_data);

        return ret;
}

static int __devexit gpio_switch_remove(struct platform_device *pdev)
{
	struct gpio_switch_data *switch_data = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&switch_data->work);
	gpio_free(switch_data->gpio);
	switch_dev_unregister(&switch_data->sdev);
	kfree(switch_data);

	return 0;
}

static struct platform_driver gpio_switch_driver = {
	.probe		= gpio_switch_probe,
	.remove		= __devexit_p(gpio_switch_remove),
	.driver		= {
		.name	= "switch-gpio",
		.owner	= THIS_MODULE,
	},
};

static int __init gpio_switch_init(void)
{
	return platform_driver_register(&gpio_switch_driver);
}

static void __exit gpio_switch_exit(void)
{
	platform_driver_unregister(&gpio_switch_driver);
}


module_param_call(switch_gpio_active, debug2hs_store, debug2hs_show, &switch_gpio_active, (S_IRUSR | S_IWUSR));

module_init(gpio_switch_init);
module_exit(gpio_switch_exit);

MODULE_AUTHOR("Mike Lockwood <lockwood@android.com>");
MODULE_DESCRIPTION("GPIO Switch driver");
MODULE_LICENSE("GPL");
