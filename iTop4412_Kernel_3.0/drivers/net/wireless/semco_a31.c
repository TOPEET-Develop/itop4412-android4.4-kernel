#include <linux/delay.h>
#include <linux/gpio.h>

#include <plat/devs.h>
#include <plat/sdhci.h>
#include <plat/gpio-cfg.h>
#include <mach/regs-gpio.h>
#include <mach/gpio.h>

void s3c_config_gpio_alive_table(int array_size, unsigned int (*gpio_table)[4])
{
	u32 i, gpio;

	for (i = 0; i < array_size; i++) {
		gpio = gpio_table[i][0];
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(gpio_table[i][1]));
		s3c_gpio_setpull(gpio, gpio_table[i][3]);
		if (gpio_table[i][2] != GPIO_LEVEL_NONE)
		    gpio_set_value(gpio, gpio_table[i][2]);
	}
}

#define GPIO_BT_RESET		EXYNOS4_GPZ(6)
#define GPIO_BT_RESET_AF	1

unsigned char bt_power_status = 0;
static int bt_sysfs_probe(struct platform_device *pdev);
static int bt_sysfs_remove(struct platform_device *pdev);

static struct platform_driver bt_sysfs_driver = {
	.driver = {
		.name = "bt-sysfs",
		.owner = THIS_MODULE,
	},
	.probe 		= bt_sysfs_probe,
	.remove 	= bt_sysfs_remove,
//	.suspend	= bt_sysfs_suspend,
//	.resume		= bt_sysfs_resume,
};

static	ssize_t get_bt_power	(struct device *dev, struct device_attribute *attr, char *buf);
static 	ssize_t set_bt_power	(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);
static	DEVICE_ATTR(bt_power, S_IRUGO|S_IWUSR, get_bt_power, set_bt_power);

static struct attribute *bt_sysfs_entries[] = {
	&dev_attr_bt_power.attr,
	NULL
};

static struct attribute_group bt_sysfs_attr_group = {
	.name   = NULL,
	.attrs  = bt_sysfs_entries,
};

static unsigned int bt_on_gpio_table[][4] = {
        {GPIO_BT_RESET , GPIO_BT_RESET_AF, GPIO_LEVEL_HIGH, S3C_GPIO_PULL_NONE},
};

static unsigned int bt_off_gpio_table[][4] = {
        {GPIO_BT_RESET , GPIO_BT_RESET_AF, GPIO_LEVEL_LOW, S3C_GPIO_PULL_NONE},
};

static ssize_t get_bt_power(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s : %d\n", __func__, bt_power_status);
}

static ssize_t set_bt_power(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned int on;


	if(!(sscanf(buf, "%u\n", &on)))
		return	-EINVAL;

	printk("[semco] %s %s\n", __func__, on ? "on" : "off");

	if (on) {
		printk("[semco] BT Turn On\r\n");
		s3c_config_gpio_alive_table(ARRAY_SIZE(bt_on_gpio_table), bt_on_gpio_table);
		bt_power_status = 1;
	} else {
		printk("[semco] BT Turn Off\r\n");
		s3c_config_gpio_alive_table(ARRAY_SIZE(bt_off_gpio_table), bt_off_gpio_table);
		bt_power_status = 0;
	}

	return count;
}

static int bt_sysfs_probe(struct platform_device *pdev)	
{
	return sysfs_create_group(&pdev->dev.kobj, &bt_sysfs_attr_group);
}

static int bt_sysfs_remove(struct platform_device *pdev)	
{
	sysfs_remove_group(&pdev->dev.kobj, &bt_sysfs_attr_group);

	return 0;
}

static int __init bt_sysfs_init(void)
{	
	return platform_driver_register(&bt_sysfs_driver);
}
module_init(bt_sysfs_init);

static void __exit bt_sysfs_exit(void)
{
	platform_driver_unregister(&bt_sysfs_driver);
}
module_exit(bt_sysfs_exit);

///WIFI POWER SETUP
void setup_semco_wlan_power(int on)
{
    int chip_pwd_low_val;

    printk("[semco] +++ %s : wlan power %s\n",__func__, on?"on":"off");

    if (on) {
        chip_pwd_low_val = 1; 
    } else {
        chip_pwd_low_val = 0;
    }
    
	if (gpio_request(EXYNOS4_GPZ(5),  "wlan_chip_pwd_l")!=0) {
        printk("[semco] ERROR:Cannot request CHIP_PWD GPIO\n");
    } else {
        gpio_direction_output(EXYNOS4_GPZ(5), 1);/* WLAN_CHIP_PWD */
        gpio_set_value(EXYNOS4_GPZ(5), chip_pwd_low_val);
        mdelay(100);
        gpio_free(EXYNOS4_GPZ(5));
	}

	printk("[semco] --- %s\n",__func__);

}

EXPORT_SYMBOL(setup_semco_wlan_power);

extern void semco_a31_detection(void);
extern void semco_a31_removal(void);

void setup_semco_wlan_power_for_onoff(int on)
{
    int chip_pwd_low_val;

    printk("[semco] +++ %s : wlan power %s\n",__func__, on?"on":"off");

    if (on) {
        chip_pwd_low_val = 1; 
    } else {
        chip_pwd_low_val = 0;
    }
    
    if (gpio_request(EXYNOS4_GPZ(5),  "wlan_chip_pwd_l")!=0) {
        printk("[semco] ERROR:Cannot request CHIP_PWD GPIO\n");
    } else {
        gpio_direction_output(EXYNOS4_GPZ(5), 1);/* WLAN_CHIP_PWD */
        gpio_set_value(EXYNOS4_GPZ(5), chip_pwd_low_val);
        mdelay(100);
        gpio_free(EXYNOS4_GPZ(5));
   }

   if(on == 1)
   {
        semco_a31_detection();		
   }else
   {
        semco_a31_removal();
   }
   
   printk("[semco] --- %s\n",__func__);

}

EXPORT_SYMBOL(setup_semco_wlan_power_for_onoff);

