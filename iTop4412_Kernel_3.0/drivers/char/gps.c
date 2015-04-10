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
#include <linux/regulator/consumer.h>	//cwp, PMIC interafce
#include "gps.h"
#include <linux/delay.h>

#define GPS_DEBUG
#ifdef GPS_DEBUG
#define DPRINTK(x...) printk("GPS DEBUG:" x)
#else
#define DPRINTK(x...)
#endif

#define DRIVER_NAME "si_gps"
static int isstart = -1;
int gps_open(struct inode *inode,struct file *filp)
{
	DPRINTK("Device Opened Success!\n");
	return nonseekable_open(inode,filp);
}

int gps_release(struct inode *inode,struct file *filp)
{
	DPRINTK("Device Closed Success!\n");
	return 0;
}

int gps_pm(bool enable)
{
	int ret = 0;
#ifdef CONFIG_GPS_PM
	printk("firecxx debug: GPS PM\r\n");
/* modify by cym 20120921 */
#if 0
	struct regulator *gps_1v8_regulator = regulator_get(NULL , "gps_1v8");	
	do{
		if (IS_ERR(gps_1v8_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "gps_1v8");
		ret = -ENODEV;
		break;}

		if(enable){
			if (!regulator_is_enabled(gps_1v8_regulator))
			regulator_enable(gps_1v8_regulator);
			printk("power on gps ok\r\n");}
		else{			
			regulator_force_disable(gps_1v8_regulator);
			printk("power off gps ok\r\n");}
	}while(0);
#else
	if(enable)
	{
		s3c_gpio_setpull(EXYNOS4_GPK2(2), S3C_GPIO_PULL_UP);
		gpio_set_value(EXYNOS4_GPK2(2), 1);
		s3c_gpio_cfgpin(EXYNOS4_GPK2(2), S3C_GPIO_SFN(1));	//output mode
	
		printk("GPS_POWER GPIO Enable!\n");
	}
	else
	{
		s3c_gpio_setpull(EXYNOS4_GPK2(2), S3C_GPIO_PULL_DOWN);
		gpio_set_value(EXYNOS4_GPK2(2), 0);
		s3c_gpio_cfgpin(EXYNOS4_GPK2(2), S3C_GPIO_SFN(1));
	
		printk("GPS_POWER GPIO Enable!\n");
	}
#endif
/* end modify */
#endif
	printk("firecxx debug: GPS PM return %d\r\n" , ret);
	return ret;
};

int gps_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	printk("firecxx debug: gps_ioctl cmd is %d\n iocmd is %d" , cmd , RST_HIGH);
	if(_IOC_TYPE(cmd)!=IOCTRL_IOC_MAGIC)		
		return -ENOTTY;
	if(_IOC_NR(cmd)>IOCTRL_IOC_MAXNR)
		return -ENOTTY;
//	if(!isstart)return 0;
	switch(cmd)
	{
		case POWER_ON:
			return gps_pm(true);			
		case POWER_OFF:
			return gps_pm(false);			
		case RST_HIGH:
			//gpio_direction_output(S5PV310_GPB(4),0);			
			//mdelay(500);	
			if(gpio_request(EXYNOS4_GPB(4) ,"GPS_power"))
				DPRINTK("GPS GPIO err!\r\n");
			else{
				gpio_direction_output(EXYNOS4_GPB(4),0);                      
                        	mdelay(500); 
				gpio_direction_output(EXYNOS4_GPB(4),1);			
				DPRINTK("GPS_RSTn Set High!\n");
				gpio_free(EXYNOS4_GPB(4));}
			break;
		case RST_LOW:
			if(gpio_request(EXYNOS4_GPB(4) ,"GPS_power"))
				DPRINTK("GPS GPIO err!\r\n");
			else{			
				gpio_direction_output(EXYNOS4_GPB(4),0);
				DPRINTK("GPS_RSTn Set Low!\n");
				gpio_free(EXYNOS4_GPB(4));}			
			break;
		default:
			DPRINTK("GPS:IOCTRL COMMAND ERROR!\n");
			return -ENOTTY;
	}
	/*s3c_gpio_cfgpin(S5PV310_GPJ0(6),S3C_GPIO_OUTPUT);//GPS_EN SET OUTPUT
	s3c_gpio_cfgpin(S5PV310_GPB(6),S3C_GPIO_OUTPUT);//GPS_RST SET OUTPUT*/
 //       isstart =0;
	return 0;
}

static struct file_operations gps_ops = {
	.owner 	= THIS_MODULE,
	.open 	= gps_open,
	.release= gps_release,
	.unlocked_ioctl 	= gps_ioctl,
};

static struct miscdevice gps_dev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.fops	= &gps_ops,
	.name	= "AGPS",
};


static int gps_probe(struct platform_device *pdev)
{
	int ret;
	char *banner = "SI GPS Initialize\n";

	printk(banner);

	ret = misc_register(&gps_dev);
	if(ret<0)
	{
		printk("GPS:register device failed!\n");
		goto exit;
	}

	return 0;

exit:
	misc_deregister(&gps_dev);
	return ret;
}

static int gps_remove (struct platform_device *pdev)
{
	misc_deregister(&gps_dev);	
//	Modules_PowerUpDown(GPS_MODULE,POWEROFF);
	return 0;
}

static int gps_suspend (struct platform_device *pdev, pm_message_t state)
{
	DPRINTK("GPS suspend:power off!\n");
	return 0;
}

static int gps_resume (struct platform_device *pdev)
{
	DPRINTK("GPS resume:power on!\n");
	return 0;
}

static struct platform_driver gps_driver = {
	.probe = gps_probe,
	.remove = gps_remove,
	.suspend = gps_suspend,
	.resume = gps_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	},
};

static void __exit gps_exit(void)
{
	platform_driver_unregister(&gps_driver);
}

static int __init gps_init(void)
{
	return platform_driver_register(&gps_driver);
}

module_init(gps_init);
module_exit(gps_exit);

MODULE_LICENSE("Dual BSD/GPL");
