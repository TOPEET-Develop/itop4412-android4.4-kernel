/* tc4-regulator-consumer.c
 *
 * Copyright (C) 2011 Samsung Electronics
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
#include <linux/module.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/regulator/machine.h>
 
#include <linux/sysfs.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/suspend.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <plat/pm.h>
#include <mach/regs-clock.h>
#include <mach/regs-pmu.h>
#include <mach/pmu.h>
#include <mach/gpio.h>
#include <mach/smc.h>
#include <mach/clock-domain.h>
#include <mach/regs-audss.h>
#include <linux/wakelock.h>

#define LOCAL_SYSFS 1

#ifdef LOCAL_SYSFS
/*vdd_lcd*/
ssize_t show_vdd_lcd_attri(struct device *dev, struct device_attribute *attr, char *buf)
{
  struct regulator *vdd_lcd_regulator;
  vdd_lcd_regulator = regulator_get(NULL, "vdd33_lcd");
  if (IS_ERR(vdd_lcd_regulator)) {
	pr_err("%s: failed to get %s\n", __func__, "vdd33_lcd");
  }

  if (regulator_is_enabled(vdd_lcd_regulator))
    sprintf(buf, "1\n");
  else
    sprintf(buf, "0\n");

  regulator_put(vdd_lcd_regulator);

  return strlen(buf);
}

ssize_t store_vdd_lcd_attri(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
  int32_t ctl;
  struct regulator *vdd_lcd_regulator;
  vdd_lcd_regulator = regulator_get(NULL, "vdd33_lcd");
  if (IS_ERR(vdd_lcd_regulator)) {
	pr_err("%s: failed to get %s\n", __func__, "vdd33_lcd");
  }

  sscanf(buf, "%d",&ctl);

  if (ctl)
    {
      if (!regulator_is_enabled(vdd_lcd_regulator))
        regulator_enable(vdd_lcd_regulator);
    }
  else
    {
	regulator_force_disable(vdd_lcd_regulator);
    }

  regulator_put(vdd_lcd_regulator);
  
  return strlen(buf);
}

static DEVICE_ATTR(vdd_lcd, 0644, show_vdd_lcd_attri, store_vdd_lcd_attri);

#endif
#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
static struct early_suspend vdd_consumer_early_suspend;

static void consumer_early_suspend(struct early_suspend *handler)
{
  struct regulator *vdd18_abb1_regulator;
  struct regulator *vdd18_abb02_regulator;
	unsigned int tmp;

#if 0
vdd18_abb1_regulator = regulator_get(NULL, "vdd18_abb1");
  if (IS_ERR(vdd18_abb1_regulator)) {
	pr_err("%s: failed to get %s\n", __func__, "vdd18_abb1");
  }
  if (!regulator_force_disable(vdd18_abb1_regulator))
    printk("vdd18_abb1 is turned off!\n");

  vdd18_abb02_regulator = regulator_get(NULL, "vdd18_abb02");
  if (IS_ERR(vdd18_abb02_regulator)) {
	pr_err("%s: failed to get %s\n", __func__, "vdd18_abb02");
  }
  if (!regulator_force_disable(vdd18_abb02_regulator))
    printk("vdd18_abb02 is turned off!\n");
#endif

  regulator_put(vdd18_abb1_regulator); 
  regulator_put(vdd18_abb02_regulator);   


#if 0

	printk("cam domain = 0x%x\n",__raw_readl(S5P_PMU_CAM_CONF));
	printk("tv domain = 0x%x\n",__raw_readl(S5P_PMU_TV_CONF));
	printk("mfc domain = 0x%x\n",__raw_readl(S5P_PMU_MFC_CONF));
	printk("g3d domain = 0x%x\n",__raw_readl(S5P_PMU_G3D_CONF));	
	printk("lcd domain = 0x%x\n",__raw_readl(S5P_PMU_LCD0_CONF));
	printk("gps domain = 0x%x\n",__raw_readl(S5P_PMU_GPS_CONF));
	
	tmp = __raw_readl(EXYNOS4_CLKGATE_IP_CAM);	//all off
	printk("~EXYNOS4_CLKGATE_IP_CAM = 0x%x\n",tmp);

	tmp = __raw_readl(EXYNOS4_CLKGATE_IP_TV);	//all off
	printk("~EXYNOS4_CLKGATE_IP_TV = 0x%x\n",tmp);

	tmp = __raw_readl(EXYNOS4_CLKGATE_IP_G3D);	//g3d [0]
	printk("~EXYNOS4_CLKGATE_IP_G3D = 0x%x\n",tmp);

	tmp = __raw_readl(EXYNOS4_CLKGATE_IP_GPS);
	printk("~EXYNOS4_CLKGATE_IP_GPS = 0x%x\n",tmp);
	__raw_writel(tmp&(~0x7),EXYNOS4_CLKGATE_IP_GPS);//gate off gps 
	tmp = __raw_readl(EXYNOS4_CLKGATE_IP_GPS);
	printk("~EXYNOS4_CLKGATE_IP_GPS = 0x%x\n",tmp);

	tmp = __raw_readl(EXYNOS4_CLKGATE_IP_PERIR_4212);
	__raw_writel(tmp&(~0x7e0),EXYNOS4_CLKGATE_IP_PERIR_4212);	//trustzone
	tmp = __raw_readl(EXYNOS4_CLKGATE_IP_PERIR_4212);	
	printk("~EXYNOS4_CLKGATE_IP_PERIR_4212 = 0x%x\n",tmp);	

	tmp = __raw_readl(EXYNOS4_CLKGATE_IP_DMC1);
	__raw_writel(tmp&(~0xf),EXYNOS4_CLKGATE_IP_DMC1);	//trustzone
	tmp = __raw_readl(EXYNOS4_CLKGATE_IP_DMC1);	
	printk("~EXYNOS4_CLKGATE_IP_DMC1 = 0x%x\n",tmp);	

#endif
}


static void consumer_early_resume(struct early_suspend *handler)
{
  struct regulator *vdd18_abb1_regulator;
  struct regulator *vdd18_abb02_regulator;
#if 0
  vdd18_abb1_regulator = regulator_get(NULL, "vdd18_abb1");
  if (IS_ERR(vdd18_abb1_regulator)) {
	pr_err("%s: failed to get %s\n", __func__, "vdd18_abb1");
  }
  if (!regulator_is_enabled(vdd18_abb1_regulator))
    if (!regulator_enable(vdd18_abb1_regulator))
      printk("vdd18_abb1 is on now!\n");
 
  vdd18_abb02_regulator = regulator_get(NULL, "vdd18_abb02");
  if (IS_ERR(vdd18_abb02_regulator)) {
	pr_err("%s: failed to get %s\n", __func__, "vdd18_abb02");
  }
  if (!regulator_is_enabled(vdd18_abb02_regulator))
    if (!regulator_enable(vdd18_abb02_regulator))
      printk("vdd18_abb02 is on now!\n");

  regulator_put(vdd18_abb1_regulator);
  regulator_put(vdd18_abb02_regulator);
  
  mdelay(50);
#endif
}

#endif

static int tc4_enable_regulator_device(bool enable)
{

	int ret = 0;

#ifdef CONFIG_REGULATOR_MAX8997
	struct regulator *vdd18_abb_regulator;
	struct regulator *vdd_arm_regulator;
	struct regulator *vdd_int_regulator;
	struct regulator *vdd_pll_regulator;
	struct regulator *vdd_g3d_regulator;
	struct regulator *vddq_m12_regulator;
	struct regulator *vdd_50_regulator;
	struct regulator *vdd12_5m_regulator;
	struct regulator *vdd_lcd_regulator;
	struct regulator *vdd10_ush_regulator;
	struct regulator *vdd33_uotg_regulator;
	struct regulator *vdd18_a31_regulator;
	struct regulator *vdd10_mipi_regulator;
	struct regulator *vdd18_cam_regulator;
	struct regulator *vdd28_cam_regulator;
	struct regulator *vdd28_af_regulator;
	struct regulator *vdd33_a31_regulator;
	struct regulator *vdd18_mipi_regulator;

	vdd_arm_regulator = regulator_get(NULL, "vdd_arm");
	if (IS_ERR(vdd_arm_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd_arm");
		ret = -ENODEV;
		goto out3;
	}

	vdd_int_regulator = regulator_get(NULL, "vdd_int");
	if (IS_ERR(vdd_int_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd_int");
		ret = -ENODEV;
		goto out2;
	}

	vdd18_abb_regulator = regulator_get(NULL, "vdd18_abb");
	if (IS_ERR(vdd18_abb_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd18_abb");
		ret = -ENODEV;
		goto out4;
	}


	vdd_pll_regulator = regulator_get(NULL, "vdd_pll");
	if (IS_ERR(vdd_pll_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd_pll");
		ret = -ENODEV;
		goto out1;
	}
	
	vdd_g3d_regulator = regulator_get(NULL, "vdd_g3d");
	if (IS_ERR(vdd_g3d_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd_g3d");
		ret = -ENODEV;
		goto out1;
	}

	vddq_m12_regulator = regulator_get(NULL, "vddq_m12");
	if (IS_ERR(vddq_m12_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vddq_m12");
		ret = -ENODEV;
		goto out1;
	}
	
	vdd_50_regulator = regulator_get(NULL, "vdd_50");
	if (IS_ERR(vdd_50_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd_50");
		ret = -ENODEV;
		goto out1;
	}

	vdd12_5m_regulator = regulator_get(NULL, "vdd12_5m");
	if (IS_ERR(vdd12_5m_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd12_5m");
		ret = -ENODEV;
		goto out1;
	}

	vdd_lcd_regulator = regulator_get(NULL, "vdd33_lcd");
	if (IS_ERR(vdd_lcd_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd33_lcd");
		ret = -ENODEV;
		goto out1;
	}
	
	vdd10_ush_regulator = regulator_get(NULL, "vdd10_ush");
	if (IS_ERR(vdd10_ush_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd10_ush");
		ret = -ENODEV;
		goto out1;
	}

	vdd33_uotg_regulator = regulator_get(NULL, "vdd33_uotg");
	if (IS_ERR(vdd33_uotg_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd33_uotg");
		ret = -ENODEV;
		goto out1;
	}

	vdd18_a31_regulator = regulator_get(NULL, "vdd18_a31");
	if (IS_ERR(vdd18_a31_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd18_a31");
		ret = -ENODEV;
		goto out1;
	}
	
	vdd10_mipi_regulator = regulator_get(NULL, "vdd10_mipi");
	if (IS_ERR(vdd10_mipi_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd10_mipi");
		ret = -ENODEV;
		goto out1;
	}

	vdd18_cam_regulator = regulator_get(NULL, "vdd18_cam");
	if (IS_ERR(vdd18_cam_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd18_cam");
		ret = -ENODEV;
		goto out1;
	}

	vdd28_cam_regulator = regulator_get(NULL, "vdd28_cam");
	if (IS_ERR(vdd28_cam_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd28_cam");
		ret = -ENODEV;
		goto out1;
	}

	vdd28_af_regulator = regulator_get(NULL, "vdd28_af");
	if (IS_ERR(vdd28_af_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd28_af");
		ret = -ENODEV;
		goto out1;
	}
	
	vdd33_a31_regulator = regulator_get(NULL, "vdd33_a31");
	if (IS_ERR(vdd33_a31_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd33_a31");
		ret = -ENODEV;
		goto out1;
	}

	vdd18_mipi_regulator = regulator_get(NULL, "vdd18_mipi");
	if (IS_ERR(vdd18_mipi_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd18_mipi");
		ret = -ENODEV;
		goto out1;
	} 


	if (enable) {
		pr_info("%s: enable LDOs\n", __func__);
		//printk("%s: enable LDOs\n", __func__);

		if (!regulator_is_enabled(vdd18_abb_regulator))
			regulator_enable(vdd18_abb_regulator);
		if (!regulator_is_enabled(vdd_arm_regulator))
			regulator_enable(vdd_arm_regulator);
		if (!regulator_is_enabled(vdd_int_regulator))
			regulator_enable(vdd_int_regulator);
		if (!regulator_is_enabled(vdd_pll_regulator))
			regulator_enable(vdd_pll_regulator);
		if (!regulator_is_enabled(vdd_g3d_regulator))
			regulator_enable(vdd_g3d_regulator);
		if (!regulator_is_enabled(vddq_m12_regulator))
			regulator_enable(vddq_m12_regulator);
		if (!regulator_is_enabled(vdd_50_regulator))
			regulator_enable(vdd_50_regulator);
		if (!regulator_is_enabled(vdd12_5m_regulator))
			regulator_enable(vdd12_5m_regulator);
		if (!regulator_is_enabled(vdd_lcd_regulator))
			regulator_enable(vdd_lcd_regulator);
		if (!regulator_is_enabled(vdd18_a31_regulator))
			regulator_enable(vdd18_a31_regulator);
		if (!regulator_is_enabled(vdd10_ush_regulator))
			regulator_enable(vdd10_ush_regulator);
		if (!regulator_is_enabled(vdd33_uotg_regulator))
			regulator_enable(vdd33_uotg_regulator);
		if (!regulator_is_enabled(vdd18_a31_regulator))
			regulator_enable(vdd18_a31_regulator);
		if (!regulator_is_enabled(vdd10_mipi_regulator))
			regulator_enable(vdd10_mipi_regulator);
		if (!regulator_is_enabled(vdd18_cam_regulator))
			regulator_enable(vdd18_cam_regulator);
		if (!regulator_is_enabled(vdd28_cam_regulator))
			regulator_enable(vdd28_cam_regulator);
		if (!regulator_is_enabled(vdd28_af_regulator))
			regulator_enable(vdd28_af_regulator);
		if (!regulator_is_enabled(vdd33_a31_regulator))
			regulator_enable(vdd33_a31_regulator);
		if (!regulator_is_enabled(vdd18_mipi_regulator))
			regulator_enable(vdd18_mipi_regulator);

	} else {
		
		pr_info("%s: disable LDOs\n", __func__);
		//printk("%s: disable LDOs\n", __func__);

		regulator_force_disable(vdd12_5m_regulator);
		regulator_force_disable(vdd_lcd_regulator);
		regulator_force_disable(vdd10_ush_regulator);
		regulator_force_disable(vdd33_uotg_regulator);
		regulator_force_disable(vdd18_a31_regulator);
		regulator_force_disable(vdd10_mipi_regulator);
		regulator_force_disable(vdd18_cam_regulator);
		regulator_force_disable(vdd28_cam_regulator);
		regulator_force_disable(vdd28_af_regulator);
		regulator_force_disable(vdd33_a31_regulator);
		regulator_force_disable(vdd18_mipi_regulator);
		regulator_force_disable(vdd_50_regulator);
		regulator_force_disable(vddq_m12_regulator);
		regulator_force_disable(vdd_g3d_regulator);
		regulator_force_disable(vdd_pll_regulator);
		regulator_force_disable(vdd_int_regulator);
		regulator_force_disable(vdd_arm_regulator);
		regulator_force_disable(vdd18_abb_regulator);

	}

		regulator_put(vdd18_abb_regulator);
		regulator_put(vdd_arm_regulator);
		regulator_put(vdd_int_regulator);
		regulator_put(vdd_pll_regulator);
		regulator_put(vdd_g3d_regulator);
		regulator_put(vddq_m12_regulator);
		regulator_put(vdd_50_regulator);
		regulator_put(vdd18_mipi_regulator);
		regulator_put(vdd33_a31_regulator);
		regulator_put(vdd28_af_regulator);
		regulator_put(vdd28_cam_regulator);
		regulator_put(vdd18_cam_regulator);
		regulator_put(vdd10_mipi_regulator);
		regulator_put(vdd18_a31_regulator);
		regulator_put(vdd33_uotg_regulator);
		regulator_put(vdd10_ush_regulator);
		regulator_put(vdd_lcd_regulator);
		regulator_put(vdd12_5m_regulator);

out1:
out2:
out3:
out4:

#endif



#ifdef CONFIG_REGULATOR_S5M8767

	struct regulator *vdd18_mipi_regulator;
	struct regulator *vdd10_mipi_regulator;
	struct regulator *vdd18_hsic_regulator;
	struct regulator *vdd33_a31_regulator;
	struct regulator *vdd18_a31_regulator;

	vdd18_mipi_regulator = regulator_get(NULL, "vdd18_mipi");
	if (IS_ERR(vdd18_mipi_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd18_mipi");
		ret = -ENODEV;
		goto out3;
	}

	vdd10_mipi_regulator = regulator_get(NULL, "vdd10_mipi");
	if (IS_ERR(vdd10_mipi_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd10_mipi");
		ret = -ENODEV;
		goto out3;
	}

	vdd33_a31_regulator = regulator_get(NULL, "vdd33_a31");
	if (IS_ERR(vdd33_a31_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd33_a31");
		ret = -ENODEV;
		goto out3;
	}

	vdd18_a31_regulator = regulator_get(NULL, "vdd18_a31");
	if (IS_ERR(vdd18_a31_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd18_a31");
		ret = -ENODEV;
		goto out3;
	}

	vdd18_hsic_regulator = regulator_get(NULL, "vdd18_hsic");
	if (IS_ERR(vdd18_hsic_regulator)) {
		pr_err("%s: failed to get %s\n", __func__, "vdd18_hsic");
		ret = -ENODEV;
		goto out3;
	}

	if (enable) {
		pr_info("%s: enable LDOs\n", __func__);
	
		if (!regulator_is_enabled(vdd18_hsic_regulator))
			regulator_enable(vdd18_hsic_regulator);
		if (!regulator_is_enabled(vdd18_mipi_regulator))
			regulator_enable(vdd18_mipi_regulator);
		if (!regulator_is_enabled(vdd10_mipi_regulator))
			regulator_enable(vdd10_mipi_regulator);
		if (!regulator_is_enabled(vdd18_a31_regulator))
			regulator_enable(vdd18_a31_regulator);
			
	} else{

			regulator_force_disable(vdd18_hsic_regulator);
			regulator_force_disable(vdd18_mipi_regulator);
			regulator_force_disable(vdd10_mipi_regulator);
	
	}

	regulator_put(vdd18_mipi_regulator);
	regulator_put(vdd10_mipi_regulator);
	regulator_put(vdd18_hsic_regulator);
	regulator_put(vdd33_a31_regulator);
	regulator_put(vdd18_a31_regulator);


out3:
#endif

	return ret;

}
#ifdef LOCAL_SYSFS
static int regulator_consumer_probe(struct platform_device *pdev)
{
        int err = 0;
	printk("%s: loading tc4-regulator-consumer\n", __func__);

	err = device_create_file(&(pdev->dev),&dev_attr_vdd_lcd);
	if (err)
	  printk("%s: failed to create sysfs file vdd_lcd\n",__func__);

#ifdef CONFIG_HAS_EARLYSUSPEND
	vdd_consumer_early_suspend.level = EARLY_SUSPEND_LEVEL_DISABLE_FB;
	vdd_consumer_early_suspend.suspend = consumer_early_suspend;
	vdd_consumer_early_suspend.resume = consumer_early_resume;
	register_early_suspend(&vdd_consumer_early_suspend);
	pr_info(" Register vdd_consumer_early_suspend done\n");
#endif

	return err;
}

#else

static int regulator_consumer_probe(struct platform_device *pdev)
{
	pr_info("%s: loading tc4-regulator-consumer\n", __func__);
	return 0;
}
#endif

#ifdef CONFIG_PM
static int regulator_consumer_suspend(struct device *dev)
{
	tc4_enable_regulator_device(false);
	return 0;
}

static int regulator_consumer_resume(struct device *dev)
{
	tc4_enable_regulator_device(true);
	return 0;
}
#endif /* CONFIG_PM */

static const struct dev_pm_ops regulator_consumer_pm_ops = {
#ifdef CONFIG_PM
	.suspend = regulator_consumer_suspend,
	.resume = regulator_consumer_resume,
#endif /* CONFIG_PM */
};

static struct platform_driver regulator_consumer_driver = {
	.probe = regulator_consumer_probe,
	.driver = {
		   .owner = THIS_MODULE,
		   .name = "tc4-regulator-consumer",
		   .pm = &regulator_consumer_pm_ops,
	},
};

static int __init regulator_consumer_init(void)
{
#if defined(CONFIG_REGULATOR_S5M8767) || defined(CONFIG_REGULATOR_MAX8997)
	platform_driver_register(&regulator_consumer_driver);
#endif

	return 0;
}
module_init(regulator_consumer_init);


MODULE_AUTHOR("xiebin.wang@samsung.com");
MODULE_DESCRIPTION("TC4 regulator consumer driver");
MODULE_LICENSE("GPL");

