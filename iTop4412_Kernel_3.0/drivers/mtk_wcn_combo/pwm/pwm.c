#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/miscdevice.h>


#define DEVICE_NAME     "pwm_test"

static struct semaphore lock;

/* freq:  pclk/50/16/65536 ~ pclk/50/16 
  * if pclk = 50MHz, freq is 1Hz to 62500Hz
  * human ear : 20Hz~ 20000Hz
  */
static void PWM_Set_Freq( unsigned long freq )
{
#if 0
	unsigned long tcon;
	unsigned long tcnt;
	unsigned long tcfg1;
	unsigned long tcfg0;

	struct clk *clk_p;
	unsigned long pclk;

	unsigned tmp;

	tmp = readl(S3C64XX_GPFCON);
	//tmp &= ~(0x3U << 28);
	//tmp |=  (0x2U << 28);

         tmp &=~(0x3U << 30);
         tmp |=  (0x2U << 30);

	writel(tmp, S3C64XX_GPFCON);

	tcon = __raw_readl(S3C_TCON);
	tcfg1 = __raw_readl(S3C_TCFG1);
	tcfg0 = __raw_readl(S3C_TCFG0);

	//prescaler = 50
	tcfg0 &= ~S3C_TCFG_PRESCALER0_MASK;
	tcfg0 |= (50 - 1); 

	//mux = 1/16
	tcfg1 &= ~S3C_TCFG1_MUX0_MASK;
	tcfg1 |= S3C_TCFG1_MUX0_DIV16;

	__raw_writel(tcfg1, S3C_TCFG1);
	__raw_writel(tcfg0, S3C_TCFG0);

	clk_p = clk_get(NULL, "pclk");
	pclk  = clk_get_rate(clk_p);
	tcnt  = (pclk/50/16)/freq;
	
	__raw_writel(tcnt, S3C_TCNTB(0));
	__raw_writel(tcnt/2, S3C_TCMPB(0));
				
	tcon &= ~0x1f;
	tcon |= 0xb;		//disable deadzone, auto-reload, inv-off, update TCNTB0&TCMPB0, start timer 0
	__raw_writel(tcon, S3C_TCON);
	
	tcon &= ~2;			//clear manual update bit
	__raw_writel(tcon, S3C_TCON);
#endif
}

void PWM_Stop( void )
{
#if 0
	unsigned tmp;
	tmp = readl(S3C64XX_GPFCON);
	//tmp &= ~(0x3U << 28);
        tmp &= ~(0x3U << 30);

	writel(tmp, S3C64XX_GPFCON);
#endif
}

static int s3c64xx_pwm_open(struct inode *inode, struct file *file)
{
	printk("%s, line:%d\n", __FUNCTION__, __LINE__);

	return 0;
}


static int s3c64xx_pwm_close(struct inode *inode, struct file *file)
{
	printk("%s, line:%d\n", __FUNCTION__, __LINE__);

	return 0;
}


static long s3c64xx_pwm_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	printk("%s\n", __FUNCTION__);
#if 0
	switch (cmd) {
		case PWM_IOCTL_SET_FREQ:
			if (arg == 0)
				return -EINVAL;
			PWM_Set_Freq(arg);
			break;

		case PWM_IOCTL_STOP:
		default:
			PWM_Stop();
			break;
	}
#endif
	return 0;
}


static struct file_operations dev_fops = {
    .owner			= THIS_MODULE,
    .open			= s3c64xx_pwm_open,
    .release		= s3c64xx_pwm_close, 
    .unlocked_ioctl	= s3c64xx_pwm_ioctl,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};

static int __init dev_init(void)
{
	int ret;

	ret = misc_register(&misc);

	printk (DEVICE_NAME"\tinitialized\n");
    	return ret;
}

static void __exit dev_exit(void)
{
	misc_deregister(&misc);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("FORLINX Inc.");
MODULE_DESCRIPTION("S3C6410 PWM Driver");
