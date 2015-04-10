#include <linux/gpio.h>
#include <plat/gpio-cfg.h>
#include <plat/devs.h>
#include <mach/regs-gpio.h>
#include <mach/gpio.h>
#include <mach/irqs.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/workqueue.h>
#include <linux/regulator/consumer.h>
#include <linux/modemctl.h>

#ifdef CONFIG_HAS_WAKELOCK
#include <linux/wakelock.h>
#endif
#include <mach/modem.h>

extern void usb_host_phy_init(void);
extern void usb_host_phy_off(void);
extern void usb_host_phy_suspend(void);
extern int usb_host_phy_resume(void);

int smm6260_is_on(void)
{
	return gpio_get_value(GPIO_PHONE_ON);
}
EXPORT_SYMBOL_GPL(smm6260_is_on);

int smm6260_set_active_state(int val)
{
	int err;
	
	err = gpio_request(GPIO_ACTIVE_STATE, "ACTIVE_STATE");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n", "ACTIVE_STATE");
	} else {
		gpio_direction_output(GPIO_ACTIVE_STATE, val ? 1 : 0);
		s3c_gpio_setpull(GPIO_ACTIVE_STATE, S3C_GPIO_PULL_NONE);
		gpio_set_value(GPIO_ACTIVE_STATE, val ? 1 : 0);
		gpio_free(GPIO_ACTIVE_STATE);
	}
	
	printk("%s: AP>>CP:   ACTIVE_STATE:%d,%d\n", __func__, val ? 1 : 0, gpio_get_value(GPIO_ACTIVE_STATE));
	return 0;
}
EXPORT_SYMBOL_GPL(smm6260_set_active_state);

int smm6260_set_slave_wakeup(int val)
{
	int err;
	
	err = gpio_request(GPIO_IPC_SLAVE_WAKEUP, "IPC_SLAVE_WAKEUP");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n", "IPC_SLAVE_WAKEUP");
	} else {
		gpio_direction_output(GPIO_IPC_SLAVE_WAKEUP, val ? 1 : 0);
		s3c_gpio_setpull(GPIO_IPC_SLAVE_WAKEUP, S3C_GPIO_PULL_NONE);
		gpio_set_value(GPIO_IPC_SLAVE_WAKEUP, val ? 1 : 0);
		gpio_free(GPIO_IPC_SLAVE_WAKEUP);
	}

	printk("%s: AP>>CP:   SLAV_WUP:%d,%d\n", __func__, val ? 1 : 0,	gpio_get_value(GPIO_IPC_SLAVE_WAKEUP));
	return 0;
}
EXPORT_SYMBOL_GPL(smm6260_set_slave_wakeup);

int smm6260_is_host_wakeup(void)
{
	return ((gpio_get_value(GPIO_IPC_HOST_WAKEUP)) ==HOST_WUP_LEVEL)? 1 : 0;
}
EXPORT_SYMBOL_GPL(smm6260_is_host_wakeup);


void smm6260_cfg(void)
{
	static int smm6260_initialed=0;
	int err = 0;

        if(smm6260_initialed)
		return;
	/*TODO: check uart init func AP FLM BOOT RX -- */
      
	err = gpio_request(GPIO_CP_PMU_RST, "CP_PMU_RST");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n", "CP_PMU_RST");
	} else {
		gpio_direction_output(GPIO_CP_PMU_RST, 0);
		s3c_gpio_setpull(GPIO_CP_PMU_RST, S3C_GPIO_PULL_NONE);
		gpio_free(GPIO_CP_PMU_RST);
	}
	
	err = gpio_request(GPIO_PHONE_ON, "PHONE_ON");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n", "PHONE_ON");
	} else {
		gpio_direction_output(GPIO_PHONE_ON, 0);
		s3c_gpio_setpull(GPIO_PHONE_ON, S3C_GPIO_PULL_NONE);
		gpio_free(GPIO_PHONE_ON);
	}
	
	err = gpio_request(GPIO_CP_RST, "CP_RST");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n", "CP_RST");
	} else {
		gpio_direction_output(GPIO_CP_RST, 0);
		s3c_gpio_setpull(GPIO_CP_RST, S3C_GPIO_PULL_NONE);
		gpio_free(GPIO_CP_RST);
	}

	err = gpio_request(GPIO_IPC_SLAVE_WAKEUP, "IPC_SLAVE_WAKEUP");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n",
			"IPC_SLAVE_WAKEUP");
	} else {
		gpio_direction_output(GPIO_IPC_SLAVE_WAKEUP, 0);
		s3c_gpio_setpull(GPIO_IPC_SLAVE_WAKEUP, S3C_GPIO_PULL_NONE);
		gpio_free(GPIO_IPC_SLAVE_WAKEUP);
	}

	err = gpio_request(GPIO_IPC_HOST_WAKEUP, "IPC_HOST_WAKEUP");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n", "IPC_HOST_WAKEUP");
	} else {
		gpio_direction_output(GPIO_IPC_HOST_WAKEUP, 0);
		s3c_gpio_cfgpin(GPIO_IPC_HOST_WAKEUP, S3C_GPIO_INPUT);
		s3c_gpio_setpull(GPIO_IPC_HOST_WAKEUP, S3C_GPIO_PULL_NONE);
		gpio_free(GPIO_IPC_HOST_WAKEUP);
	}
	
	err = gpio_request(GPIO_SUSPEND_REQUEST, "IPC_SUSPEND_REQUEST");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n", "IPC_SUSPEND_REQUEST");
	} else {
		gpio_direction_output(GPIO_SUSPEND_REQUEST, 0);
		s3c_gpio_cfgpin(GPIO_SUSPEND_REQUEST, S3C_GPIO_INPUT);
		s3c_gpio_setpull(GPIO_SUSPEND_REQUEST, S3C_GPIO_PULL_NONE);
		gpio_free(GPIO_SUSPEND_REQUEST);
	}	
	
	err = gpio_request(GPIO_ACTIVE_STATE, "ACTIVE_STATE");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n", "ACTIVE_STATE");
	} else {
		gpio_direction_output(GPIO_ACTIVE_STATE, 0);
		s3c_gpio_setpull(GPIO_ACTIVE_STATE, S3C_GPIO_PULL_NONE);
		gpio_free(GPIO_ACTIVE_STATE);
	}

	err = gpio_request(GPIO_CP_RESET_REPORT, "CP_RESET_REPORT");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n", "CP_RESET_REPORT");
	} else {
		gpio_direction_output(GPIO_CP_RESET_REPORT, 0);
		s3c_gpio_cfgpin(GPIO_CP_RESET_REPORT, S3C_GPIO_INPUT);
		s3c_gpio_setpull(GPIO_CP_RESET_REPORT, S3C_GPIO_PULL_NONE);
		gpio_free(GPIO_CP_RESET_REPORT);
	}	

	err = gpio_request(GPIO_XUJIE_MONITOR, "XUJIE_MONITOR");
	if (err) {
		printk(KERN_ERR "fail to request gpio %s\n", "XUJIE_MONITOR");
	} else {
		gpio_direction_output(GPIO_XUJIE_MONITOR, 0);
		s3c_gpio_setpull(GPIO_XUJIE_MONITOR, S3C_GPIO_PULL_NONE);
		gpio_free(GPIO_XUJIE_MONITOR);
	}	

	smm6260_initialed = 1;
	printk("\n---%s(): finish\n",__FUNCTION__);
}
static void smm6260_vcc_init(void)
{

}

static void smm6260_vcc_off(void)
{

}

extern struct modemctl *global_mc;

static void smm6260_on(void)
{
	int count =1000;
	printk("%s: start\n", __func__);
	
	smm6260_vcc_init();

	if(global_mc->gModemPowerState==1){
		printk("---not the first time modem power on\n");

		gpio_set_value(GPIO_CP_RST, 0);
		msleep(100);
		gpio_set_value(GPIO_CP_RST, 1);
		mdelay(1);
		gpio_set_value(GPIO_CP_PMU_RST, 1);
		mdelay(2);
		gpio_set_value(GPIO_PHONE_ON, 1);
		//udelay(60);
		//gpio_set_value(GPIO_PHONE_ON, 0);
		}
	else{
		global_mc->gModemPowerState=1;
		
		gpio_set_value(GPIO_CP_PMU_RST, 0);
		gpio_set_value(GPIO_PHONE_ON, 0);
		msleep(100);
		
		gpio_set_value(GPIO_CP_RST, 0);
		msleep(100);
		gpio_set_value(GPIO_CP_RST, 1);
		mdelay(1);
		gpio_set_value(GPIO_CP_PMU_RST, 1);
		mdelay(2);
		gpio_set_value(GPIO_PHONE_ON, 1);
		udelay(60);
		//gpio_set_value(GPIO_PHONE_ON, 0);
		printk("---the first time modem power on\n");
		}
//from intel Khai
	printk("\n\n---%s(): finish\n", __FUNCTION__);
}

static void smm6260_off(void)
{
	printk("%s\n", __func__);
	gpio_set_value(GPIO_CP_RST, 0);
	gpio_set_value(GPIO_CP_PMU_RST, 0);
	gpio_set_value(GPIO_PHONE_ON, 0);
	msleep(2000);
	//gpio_set_value(GPIO_PHONE_ON, 1);
	//msleep(1500);

}
extern void do_modem_reset();

 void smm6260_reset(void)
{
	printk("%s\n", __func__);
	
	do_modem_reset(); 
}

/* move the PDA_ACTIVE Pin control to sleep_gpio_table */
static void smm6260_suspend(void)
{
	smm6260_vcc_off();
}

static void smm6260_resume(void)
{
	smm6260_vcc_init();
}

static struct modem_platform_data smm6260_data = {
	.name = "smm6260",
	.gpio_phone_on = GPIO_PHONE_ON,
	.gpio_cp_reset = GPIO_CP_RST,
	.gpio_ipc_slave_wakeup = GPIO_IPC_SLAVE_WAKEUP,
	.gpio_ipc_host_wakeup = GPIO_IPC_HOST_WAKEUP,
	.gpio_suspend_request = GPIO_SUSPEND_REQUEST,
	.gpio_active_state = GPIO_ACTIVE_STATE,
	.gpio_cp_reset_int = GPIO_CP_RESET_REPORT,
	.ops = {
		.modem_on = smm6260_on,
		.modem_off = smm6260_off,
		.modem_reset = smm6260_reset,
		.modem_suspend = smm6260_suspend,
		.modem_resume = smm6260_resume,
		.modem_cfg = smm6260_cfg,
	}
};

struct platform_device smm6260_modem = {
	.name = "smm_modem",
	.id = -1,

	.dev = {
		.platform_data = &smm6260_data,
	},
};
EXPORT_SYMBOL(smm6260_modem);

