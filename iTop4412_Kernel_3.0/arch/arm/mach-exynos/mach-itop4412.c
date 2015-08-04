/* linux/arch/arm/mach-exynos/mach-itop4412.c
 *
 * Copyright (c) 2011 Topeet Electronics Co., Ltd.
 *		http://www.topeetboard.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/platform_device.h>
#include <linux/serial_core.h>
#include <linux/spi/spi.h>
#include <linux/spi/spi_gpio.h>
#include <linux/clk.h>
#include <linux/lcd.h>
#include <linux/gpio.h>
#include <linux/gpio_event.h>
#include <linux/i2c.h>

#include <linux/pwm_backlight.h>
#include <linux/input.h>
#include <linux/mmc/host.h>
#include <linux/regulator/machine.h>

#include <linux/regulator/max8649.h>

#include <linux/regulator/fixed.h>

#include <linux/v4l2-mediabus.h>
#include <linux/memblock.h>
#include <linux/delay.h>
#if defined(CONFIG_S5P_MEM_CMA)
#include <linux/cma.h>
#endif
#ifdef CONFIG_ANDROID_PMEM
#include <linux/android_pmem.h>
#endif
#include <linux/notifier.h>
#include <linux/reboot.h>

#include <asm/mach/arch.h>
#include <asm/mach-types.h>

#include <plat/regs-serial.h>
#include <plat/exynos4.h>
#include <plat/cpu.h>
#include <plat/clock.h>
#include <plat/keypad.h>
#include <plat/devs.h>
#include <plat/fb.h>
#include <plat/fb-s5p.h>
#include <plat/fb-core.h>
#include <plat/regs-fb-v4.h>
#include <plat/backlight.h>
#include <plat/gpio-cfg.h>
#include <plat/regs-adc.h>
#include <plat/adc.h>
#include <plat/iic.h>
#include <plat/pd.h>
#include <plat/sdhci.h>
#include <plat/mshci.h>
#include <plat/ehci.h>
#include <plat/usbgadget.h>
#include <plat/s3c64xx-spi.h>
#if defined(CONFIG_VIDEO_FIMC)
#include <plat/fimc.h>
#elif defined(CONFIG_VIDEO_SAMSUNG_S5P_FIMC)
#include <plat/fimc-core.h>
#include <media/s5p_fimc.h>
#endif
#if defined(CONFIG_VIDEO_FIMC_MIPI)
#include <plat/csis.h>
#elif defined(CONFIG_VIDEO_S5P_MIPI_CSIS)
#include <plat/mipi_csis.h>
#endif
#include <plat/tvout.h>
#include <plat/media.h>
#include <plat/regs-srom.h>
#include <plat/tv-core.h>

#include <media/exynos_flite.h>
#include <media/exynos_fimc_is.h>
#include <video/platform_lcd.h>
#include <mach/board_rev.h>
#include <mach/map.h>
#include <mach/spi-clocks.h>
#include <mach/exynos-ion.h>
#include <mach/regs-pmu.h>
#ifdef CONFIG_EXYNOS4_DEV_DWMCI
#include <mach/dwmci.h>
#endif
#ifdef CONFIG_SMM6260_MODEM
#include <mach/modem.h>
#endif
#include <mach/map.h>
#include <mach/regs-pmu.h>
#ifdef CONFIG_VIDEO_S5K4ECGX
#include <media/s5k4ecgx.h>
#define temp_width 640
#define temp_height 480
#endif

/* add by cym 20130605 */
//#ifdef CONFIG_VIDEO_OV5640 CONFIG_SOC_CAMERA_GC2035
#if defined(CONFIG_VIDEO_OV5640)
#include <media/soc_camera.h>
#include <media/ov5640.h>
//#define temp_width 800
//#define temp_height 600
#endif
//end add

/* add by cym 20140915 */
#ifdef CONFIG_VIDEO_TVP5150
#include <media/tvp5150_platform.h>
#endif
/* end add*/

/* add by cym 20130619 */
#ifdef CONFIG_KEYBOARD_GPIO
#include <linux/gpio_keys.h>
#endif
/* end add */

/* add by cym 20121114 */
#ifdef CONFIG_VIDEO_SR200PC20
#include <media/sr200pc20_platform.h>
#endif
/* end add */

/* add by cym 20130417 for TSC2007 TouchScreen */
#ifdef CONFIG_TOUCHSCREEN_TSC2007
#include <linux/i2c/tsc2007.h>
#endif
/* end add */

#ifdef CONFIG_EXYNOS4_CONTENT_PATH_PROTECTION
#include <mach/secmem.h>
#endif
#include <mach/dev.h>
#include <mach/ppmu.h>
#ifdef CONFIG_EXYNOS_C2C
#include <mach/c2c.h>
#endif
#if defined(CONFIG_VIDEO_SAMSUNG_S5P_MFC) || defined(CONFIG_VIDEO_MFC5X)
#include <plat/s5p-mfc.h>
#endif

#ifdef CONFIG_FB_S5P_MIPI_DSIM
#include <mach/mipi_ddi.h>
#include <mach/dsim.h>
#include <../../../drivers/video/samsung/s3cfb.h>
#endif
#include <plat/fimg2d.h>
#ifdef CONFIG_TC4_GB
#include <mach/sysmmu.h>
#else
#include <mach/dev-sysmmu.h>
#include <plat/sysmmu.h>

#endif


#ifdef CONFIG_MTK_COMBO_MT66XX
#include <linux/combo_mt66xx.h>
#endif


#if defined(CONFIG_KERNEL_PANIC_DUMP)		//panic-dump
#include <mach/panic-dump.h>
#endif

#ifdef CONFIG_TC4_GB// liang
#include <linux/mpu.h>
#if defined(CONFIG_MPU_SENSORS_MPU3050) || defined(CONFIG_MPU_SENSORS_MPU3050_MODULE)

#define SENSOR_MPU_NAME "mpu3050"
#define MPUGPIO (EXYNOS4_GPX3(3))

static struct mpu3050_platform_data mpu_data = {
    .int_config  = 0x10,
#ifdef CONFIG_TC4_PORTRAIT_MODE
    .orientation = {  0,  1,  0,
                      1,  0,  0,
                      0,  0, -1 },
#else
    .orientation = {  -1,  0,  0,
                      0,  1,  0,
                      0,  0, -1 },
#endif
    /* accel */
    .accel = {
    #ifdef CONFIG_MPU_SENSORS_MPU3050_MODULE
        .get_slave_descr = NULL,
    #else
        .get_slave_descr = get_accel_slave_descr,
    #endif
        .adapt_num   = 5,
        .bus         = EXT_SLAVE_BUS_SECONDARY,
        .address     = (0x30>>1),//0x0F,
    #ifdef CONFIG_TC4_PORTRAIT_MODE
        .orientation = {  1,  0,  0,
                          0,  -1,  0,
                          0,  0, -1 },
    },
#else
        .orientation = {  0,  1,  0,
                          1,  0,  0,
                          0,  0, -1 },
    },
#endif
    /* compass */
    .compass = {
    #ifdef CONFIG_MPU_SENSORS_MPU3050_MODULE
        .get_slave_descr = NULL,
    #else
        .get_slave_descr = get_compass_slave_descr,
    #endif
        .adapt_num   = 5,
        .bus         = EXT_SLAVE_BUS_PRIMARY,
        .address     = (0x3c>>1),//0x0E,
    #ifdef CONFIG_TC4_PORTRAIT_MODE
        .orientation = { -1, 0, 0,
                         0, 1, 0,
                         0, 0, 1 },
    },
#else
        .orientation = { 0, -1, 0,
                         -1, 0, 0,
                         0, 0, -1 },
    },
#endif
    /* pressure */
    .pressure = {
    #ifdef CONFIG_MPU_SENSORS_MPU3050_MODULE
        .get_slave_descr = NULL,
    #else
        .get_slave_descr = get_pressure_slave_descr,
    #endif
        .adapt_num   = 2,
        .bus         = EXT_SLAVE_BUS_PRIMARY,
        .address     = 0x77,
        .orientation = { 1, 0, 0,
                         0, 1, 0,
                         0, 0, 1 },
    },
};
#endif

#if defined(CONFIG_MPU_SENSORS_MPU6000) || defined(CONFIG_MPU_SENSORS_MPU6000_MODULE)

#define SENSOR_MPU_NAME "mpu6000"

static struct mpu3050_platform_data mpu_data = {
    .int_config  = 0x10,
    .orientation = {  -1,  0,  0,
                      0,  1,  0,
                      0,  0, -1 },
    /* accel */
    .accel = {
    #ifdef CONFIG_MPU_SENSORS_MPU6000_MODULE
        .get_slave_descr = NULL,
    #else
        .get_slave_descr = get_accel_slave_descr,
    #endif
        .adapt_num   = 2,
        .bus         = EXT_SLAVE_BUS_PRIMARY,
        .address     = 0x68,
        .orientation = {  -1,  0,  0,
                          0,  1,  0,
                          0,  0, -1 },
    },
    /* compass */
    .compass = {
    #ifdef CONFIG_MPU_SENSORS_MPU6000_MODULE
        .get_slave_descr = NULL,
    #else
        .get_slave_descr = get_compass_slave_descr,
    #endif
        .adapt_num   = 2,
        .bus         = EXT_SLAVE_BUS_SECONDARY,
        .address     = 0x0E,
        .orientation = { 1, 0, 0,
                         0, 1, 0,
                         0, 0, 1 },
    },
    /* pressure */
    .pressure = {
    #ifdef CONFIG_MPU_SENSORS_MPU6000_MODULE
        .get_slave_descr = NULL,
    #else
        .get_slave_descr = get_pressure_slave_descr,
    #endif
        .adapt_num   = 2,
        .bus         = EXT_SLAVE_BUS_PRIMARY,
        .address     = 0x77,
        .orientation = { 1, 0, 0,
                         0, 1, 0,
                         0, 0, 1 },
    },

};
#endif
#endif

#ifdef CONFIG_TC4_ICS
#include <linux/mpu.h>

#ifdef CONFIG_MPU_SENSORS_MPU6050B1
void sensor_hw_init(void)
{
    printk("%s: line = %d\n", __FUNCTION__, __LINE__);

    if (gpio_request(EXYNOS4_GPX3(3), "MPU6050 INT"))
        printk(KERN_WARNING "MPU6050 INT(GPX3.3) Port request error!!!\n");
    else    {
        s3c_gpio_setpull(EXYNOS4_GPX3(3), S3C_GPIO_PULL_NONE);
        s3c_gpio_cfgpin(EXYNOS4_GPX3(3), S3C_GPIO_SFN(0));
        gpio_direction_input(EXYNOS4_GPX3(3));
        gpio_free(EXYNOS4_GPX3(3));
    }

    /* Sensor AK8975 DRDY */
    /*      if (gpio_request(EXYNOS4_GPX1(4), "AK8975 RDY"))
                printk(KERN_WARNING "AK8975 RDY(GPX1.4) Port request error!!!\n");
        else    {
                s3c_gpio_setpull(EXYNOS4_GPX1(4), S3C_GPIO_PULL_NONE);
                s3c_gpio_cfgpin(EXYNOS4_GPX1(4), S3C_GPIO_SFN(0));
                gpio_direction_input(EXYNOS4_GPX1(4));
                gpio_free(EXYNOS4_GPX1(4));
        }
        //enable_irq(IRQ_EINT(27));
*/
}

static struct mpu_platform_data mpu6050_data = {
    .int_config = 0x10,
    .orientation = {
        0, -1, 0,
        -1, 0, 0,
        0, 0, -1},

    .level_shifter = 0,
};
static struct ext_slave_platform_data inv_mpu_compass_data = {
    .bus = EXT_SLAVE_BUS_PRIMARY,
    .orientation = {
        -1, 0, 0,
        0, 1, 0,
        0, 0, -1},
};
#else
static struct mpu_platform_data mpu3050_data = {
    .int_config  = 0x10,
#ifdef CONFIG_TC4_PORTRAIT_MODE
    .orientation = {  0,  1,  0,
                      1,  0,  0,
                      0,  0, -1 },
#else
    .orientation = {  -1,  0,  0,
                      0,  1,  0,
                      0,  0, -1 },
#endif
};

/* accel */
static struct ext_slave_platform_data inv_mpu_bma250_data = {
    .bus         = EXT_SLAVE_BUS_SECONDARY,
#ifdef CONFIG_TC4_PORTRAIT_MODE
    .orientation = {  1,  0,  0,
                      0,  -1,  0,
                      0,  0, -1 },
#else
    .orientation = {  0,  1,  0,
                      1,  0,  0,
                      0,  0, -1 },
#endif
};
#endif
#endif

/* add by cym 20131114 */
#ifdef CONFIG_USB_NET_DM9620
static void __init dm9620_reset(void)
{
    int err = 0;

    err = gpio_request_one(EXYNOS4_GPC0(1), GPIOF_OUT_INIT_HIGH, "DM9620_RESET");
    if (err)
        pr_err("failed to request GPC0_1 for DM9620 reset control\n");

    s3c_gpio_setpull(EXYNOS4_GPC0(1), S3C_GPIO_PULL_UP);
    gpio_set_value(EXYNOS4_GPC0(1), 0);

    mdelay(1000);//dg change 5 ms to 1000ms for test dm9621

    gpio_set_value(EXYNOS4_GPC0(1), 1);
    gpio_free(EXYNOS4_GPC0(1));
}
#endif
/* end add */

#include <linux/i2c-gpio.h>	

#ifdef CONFIG_VIDEO_SAMSUNG_S5P_FIMC
#include <plat/fimc-core.h>
#include <media/s5p_fimc.h>
#endif

#if defined(CONFIG_VIDEO_SAMSUNG_S5P_MFC)
#include <plat/s5p-mfc.h>
#endif

#if defined (CONFIG_VIDEO_JPEG_V2X) || defined(CONFIG_VIDEO_JPEG)
#include <plat/jpeg.h>
#endif
#ifdef CONFIG_REGULATOR_S5M8767
#include <linux/mfd/s5m87xx/s5m-core.h>
#include <linux/mfd/s5m87xx/s5m-pmic.h>
#endif

#if defined(CONFIG_EXYNOS_SETUP_THERMAL) 
#include <plat/s5p-tmu.h> 
#endif
#define REG_INFORM4            (S5P_INFORM4)

/* Following are default values for UCON, ULCON and UFCON UART registers */
#define SMDK4X12_UCON_DEFAULT	(S3C2410_UCON_TXILEVEL |	\
    S3C2410_UCON_RXILEVEL |	\
    S3C2410_UCON_TXIRQMODE |	\
    S3C2410_UCON_RXIRQMODE |	\
    S3C2410_UCON_RXFIFO_TOI |	\
    S3C2443_UCON_RXERR_IRQEN)

#define SMDK4X12_ULCON_DEFAULT	S3C2410_LCON_CS8

#define SMDK4X12_UFCON_DEFAULT	(S3C2410_UFCON_FIFOMODE |	\
    S5PV210_UFCON_TXTRIG4 |	\
    S5PV210_UFCON_RXTRIG4)

static struct s3c2410_uartcfg smdk4x12_uartcfgs[] __initdata = {
    [0] = {
    .hwport		= 0,
    .flags		= 0,
    .ucon		= SMDK4X12_UCON_DEFAULT,
    .ulcon		= SMDK4X12_ULCON_DEFAULT,
    .ufcon		= SMDK4X12_UFCON_DEFAULT,
},
[1] = {
    .hwport		= 1,
    .flags		= 0,
    .ucon		= SMDK4X12_UCON_DEFAULT,
    .ulcon		= SMDK4X12_ULCON_DEFAULT,
    .ufcon		= SMDK4X12_UFCON_DEFAULT,
},
[2] = {
    .hwport		= 2,
    .flags		= 0,
    .ucon		= SMDK4X12_UCON_DEFAULT,
    .ulcon		= SMDK4X12_ULCON_DEFAULT,
    .ufcon		= SMDK4X12_UFCON_DEFAULT,
},
[3] = {
    .hwport		= 3,
    .flags		= 0,
    .ucon		= SMDK4X12_UCON_DEFAULT,
    .ulcon		= SMDK4X12_ULCON_DEFAULT,
    .ufcon		= SMDK4X12_UFCON_DEFAULT,
},
};


#define WRITEBACK_ENABLED

#if defined(CONFIG_VIDEO_FIMC) || defined(CONFIG_VIDEO_SAMSUNG_S5P_FIMC)
/*
 * External camera reset
 * Because the most of cameras take i2c bus signal, so that
 * you have to reset at the boot time for other i2c slave devices.
 * This function also called at fimc_init_camera()
 * Do optimization for cameras on your platform.
*/
#if defined(CONFIG_ITU_B) || defined(CONFIG_CSI_D) || defined(CONFIG_VIDEO_SR200PC20) || defined(CONFIG_VIDEO_OV5640)
static int smdk4x12_cam1_reset(int dummy)
{
    /* remove by cym 20130426 */
#if 0
    int err;
#endif
    /* end remove */

    return 0;
}
#if 1//ndef CONFIG_TC4_EVT

extern struct regulator *tv_regulator_vdd18 ;	//added by yulu for controlling mipi voltage 	
extern struct regulator *tv_regulator_vdd10 ;	
extern bool cam_mipi_en;
#endif


#endif
#endif

#ifdef CONFIG_VIDEO_FIMC
/* add by cym 20121114 */
#ifdef CONFIG_VIDEO_SR200PC20
struct sr200pc20_platform_data sr200pc20_plat = {
    .default_width = DEFAULT_PREVIEW_WIDTH,
    .default_height = DEFAULT_PREVIEW_HEIGHT,
    .pixelformat = DEFAULT_FMT,
    .freq = 24000000,
    .is_mipi = 0,
    .streamoff_delay = 50,
    .dbg_level = CAMDBG_LEVEL_DEFAULT,
};

static struct i2c_board_info  sr200pc20_i2c_info = {
    I2C_BOARD_INFO("SR200PC20", 0x20),
    .platform_data = &sr200pc20_plat,
};

static struct s3c_platform_camera sr200pc20 = {
    .id 	= CAMERA_PAR_A,
    .clk_name	= "sclk_cam0",
    .i2c_busnum = 7,
    .cam_power	= smdk4x12_cam1_reset,

    .type		= CAM_TYPE_ITU,
    .fmt		= ITU_601_YCBCR422_8BIT,
    .order422	= CAM_ORDER422_8BIT_YCBYCR,
    .info		= &sr200pc20_i2c_info,
    .pixelformat	= DEFAULT_FMT,
    .srclk_name = "xusbxti",
    .clk_rate	= 24000000,
    .line_length	= 1920,
    .width		= DEFAULT_PREVIEW_WIDTH,
    .height 	= DEFAULT_PREVIEW_HEIGHT,
    .window 	= {
        .left	= 0,
        .top	= 0,
        .width	= DEFAULT_PREVIEW_WIDTH,
        .height = DEFAULT_PREVIEW_HEIGHT,
    },

    /* Polarity */
    .inv_pclk	= 0,
    .inv_vsync	= 1,
    .inv_href	= 0,
    .inv_hsync	= 0,
    .reset_camera	= 1,
    .initialized	= 0,
    .layout_rotate = 0,//270 for shuping, //180,
};
#endif
/* end add */

/*
 * Guide for Camera Configuration for Crespo board
 * ITU CAM CH A: LSI s5k4ecgx
 */

#ifdef CONFIG_VIDEO_S5K4ECGX
static struct s5k4ecgx_platform_data s5k4ecgx_plat = {
    .default_width = temp_width,
    .default_height = temp_height,
    .pixelformat = V4L2_PIX_FMT_UYVY,
    .freq = 24000000,

    .is_mipi = 1,
};

static struct i2c_board_info  s5k4ecgx_i2c_info = {
#if 0
    I2C_BOARD_INFO("S5K4ECGX", 0x2D),		//0x5A>>1
#else
    I2C_BOARD_INFO("S5K4ECGX", 0xAC>>1),
#endif
    .platform_data = &s5k4ecgx_plat,
};

static struct s3c_platform_camera s5k4ecgx = {
    .id = CAMERA_CSI_D,
    .type = CAM_TYPE_MIPI,
    .fmt = MIPI_CSI_YCBCR422_8BIT,
    .order422 = CAM_ORDER422_8BIT_CBYCRY,
    .i2c_busnum = 6,
    .info = &s5k4ecgx_i2c_info,
    .pixelformat = V4L2_PIX_FMT_UYVY,
    .srclk_name ="xusbxti",
    .clk_name = "sclk_cam0",
    .clk_rate = 24000000,
    .line_length = 1920,
    .width = temp_width,
    .height = temp_height,
    .window = {
        .left = 0,
        .top = 0,
        .width = temp_width,
        .height = temp_height,
    },

    .mipi_lanes = 2, //add
    .mipi_settle = 12, //add
    .mipi_align = 32, //add

    /* Polarity */
    .inv_pclk = 0,
    .inv_vsync = 1,
    .inv_href = 0,
    .inv_hsync = 0,

    .initialized = 0,
    .layout_rotate = 0,//90 hengping, //180 for shuping,
    .cam_power = smdk4x12_cam1_reset,

};
#endif

/* add by cym 20140124 */
#ifdef CONFIG_VIDEO_OV5640
struct soc_camera_device ov5640_plat = {
    .user_width = 640,
    .user_height = 480,
};
static struct i2c_board_info  ov5640_i2c_info = {
    I2C_BOARD_INFO("ov5640", 0x78>>1),
    .platform_data = &ov5640_plat,
};

static struct s3c_platform_camera ov5640 = {
    .id 	= CAMERA_PAR_A,
    .clk_name	= "sclk_cam0",
    .i2c_busnum = 7,
    .cam_power	= smdk4x12_cam1_reset,

    .type		= CAM_TYPE_ITU,
    .fmt		= ITU_601_YCBCR422_8BIT,
    .order422	= CAM_ORDER422_8BIT_CBYCRY,
    .info		= &ov5640_i2c_info,
    .pixelformat	= V4L2_PIX_FMT_UYVY, //modify by cym V4L2_PIX_FMT_UYVY,
    .srclk_name = "xusbxti",
    .clk_rate	= 24000000,
    .line_length	= 1920,
    .width		= 640,
    .height 	= 480,
    .window 	= {
        .left	= 0,
        .top	= 0,
        .width	= 640,
        .height = 480,
    },

    /* Polarity */
    .inv_pclk	= 0,
    .inv_vsync	= 1,
    .inv_href	= 0,
    .inv_hsync	= 0,
    .reset_camera	= 1,
    .initialized	= 0,
    .layout_rotate = 0 //for shuping, //180,
};
#endif
/* end add */

/* add by cym 20140915 */
#ifdef CONFIG_VIDEO_TVP5150
static int smdk4x12_cam0_tvp5150_reset(int on)
{
#if 0
    /* Camera A */
    printk("Open TVP5150 camema sensor\n");
    s3c_gpio_setpull(EXYNOS4_GPX3(4), S3C_GPIO_PULL_NONE);
    s3c_gpio_cfgpin(EXYNOS4_GPX3(4), S3C_GPIO_SFN(1));

    gpio_set_value(EXYNOS4_GPX3(4), 1);
    mdelay(10);
    gpio_set_value(EXYNOS4_GPX3(4), 0);
    mdelay(10);
#endif
    return 0;
}

static struct tvp5150_platform_data tvp5150_plat = {
    .default_width = 640,//720,
    .default_height = 480,//525,
    .pixelformat = V4L2_PIX_FMT_YUYV,
    .freq = 27000000,
    .is_mipi = 0,

    .cam_power = smdk4x12_cam0_tvp5150_reset,
};

static struct i2c_board_info tvp5150_i2c_info = {
    I2C_BOARD_INFO("tvp5150", 0xBA>>1),
    .platform_data = &tvp5150_plat,
};

static struct s3c_platform_camera tvp5150 = {
    .id             = CAMERA_PAR_A,
    .clk_name       = "sclk_cam0",
    .i2c_busnum     = 7,
    .cam_power      = smdk4x12_cam0_tvp5150_reset,
    .type           = CAM_TYPE_ITU,
    .fmt            = ITU_656_YCBCR422_8BIT,
    .order422       = CAM_ORDER422_8BIT_CBYCRY,
    .info           = &tvp5150_i2c_info,
    .pixelformat = V4L2_PIX_FMT_UYVY,
    .srclk_name     = "xusbxti",
    .clk_rate       = 27000000,
    .line_length = 720,
    .width          = 640,//720,
    .height         = 480,//576,
    .window         = {
        .left   = 0,
        .top    = 0,
        .width  = 640,//720,
        .height = 480,//576,
    },

    /* Polarity */
    .inv_pclk       = 0,//1,
    .inv_vsync      = 0,//1,
    .inv_href       = 1,
    .inv_hsync      = 1,
    .reset_camera = 1,
    .initialized = 0,
    //.layout_rotate = 0 //for shuping, //180,
};
#endif
/* end add */

/* 2 MIPI Cameras */
#ifdef WRITEBACK_ENABLED
static struct i2c_board_info writeback_i2c_info = {
    I2C_BOARD_INFO("WriteBack", 0x0),
};

static struct s3c_platform_camera writeback = {
    .id		= CAMERA_WB,
    .fmt		= ITU_601_YCBCR422_8BIT,
    .order422	= CAM_ORDER422_8BIT_CBYCRY,
    .i2c_busnum	= 0,
    .info		= &writeback_i2c_info,
    .pixelformat	= V4L2_PIX_FMT_YUV444,
    .line_length	= 800,
    .width		= 480,
    .height		= 800,
    .window		= {
        .left	= 0,
        .top	= 0,
        .width	= 480,
        .height	= 800,
    },

    .initialized	= 0,
};
#endif

/* Interface setting */
static struct s3c_platform_fimc fimc_plat = {
#ifdef CONFIG_ITU_A
    .default_cam	= CAMERA_PAR_A,
#endif
#ifdef CONFIG_ITU_B
    .default_cam	= CAMERA_PAR_B,
#endif
#ifdef CONFIG_CSI_C
    .default_cam	= CAMERA_CSI_C,
#endif
#ifdef CONFIG_CSI_D
    .default_cam	= CAMERA_CSI_D,
#endif
#ifdef WRITEBACK_ENABLED
    .default_cam	= CAMERA_WB,
#endif
    .camera		= {

    #if 0 //added yqf, adjust for middleware request
    #ifdef CONFIG_VIDEO_S5K4ECGX
        &s5k4ecgx,
    #endif
    #else
        //for S5K4EC back
    #ifdef CONFIG_VIDEO_S5K4ECGX
        &s5k4ecgx,
    #endif

    #ifdef CONFIG_VIDEO_OV5640
        &ov5640,
    #endif

        /* add by cym 20140915 */
    #ifdef CONFIG_VIDEO_TVP5150
        &tvp5150,
    #endif
        /* end add */

        //front
        /* add by cym 20121114 */
    #ifdef CONFIG_VIDEO_SR200PC20
        &sr200pc20,
    #endif
        /* end add */

    #endif

    #ifdef WRITEBACK_ENABLED
        &writeback,
    #endif
    },
    .hw_ver		= 0x51,
};
#endif /* CONFIG_VIDEO_FIMC */


#ifdef CONFIG_S3C64XX_DEV_SPI
#if 0	//remove by cym 20130529
static struct s3c64xx_spi_csinfo spi0_csi[] = {
    [0] = {
    .line = EXYNOS4_GPB(1),
    .set_level = gpio_set_value,
    .fb_delay = 0x2,
},
};

static struct spi_board_info spi0_board_info[] __initdata = {
{
    .modalias = "spidev",
    .platform_data = NULL,
    .max_speed_hz = 10*1000*1000,
    .bus_num = 0,
    .chip_select = 0,
    .mode = SPI_MODE_0,
    .controller_data = &spi0_csi[0],
}
};

#ifndef CONFIG_FB_S5P_LMS501KF03
static struct s3c64xx_spi_csinfo spi1_csi[] = {
    [0] = {
    .line = EXYNOS4_GPB(5),
    .set_level = gpio_set_value,
    .fb_delay = 0x2,
},
};

static struct spi_board_info spi1_board_info[] __initdata = {
{
    .modalias = "spidev",
    .platform_data = NULL,
    .max_speed_hz = 10*1000*1000,
    .bus_num = 1,
    .chip_select = 0,
    .mode = SPI_MODE_3,
    .controller_data = &spi1_csi[0],
}
};
#endif
#endif

#ifdef CONFIG_CAN_MCP251X
#include <linux/can/platform/mcp251x.h>

static int mcp251x_ioSetup(struct spi_device *spi)
{
    int err;

    printk("mcp251x: setup gpio pins CS and External Int\n");
    err = gpio_request_one(EXYNOS4_GPX0(0), GPIOF_IN, "mcp251x_INT");
    if (err) {
        printk(KERN_ERR "failed to request mcp251x_INT\n");
        return -1;
    }

    //s3c_gpio_cfgpin(EXYNOS4_GPX0(0), S3C_GPIO_SFN(0xF));
    //s3c_gpio_setpull(EXYNOS4_GPX0(0), S3C_GPIO_PULL_NONE);

    s3c_gpio_cfgpin(EXYNOS4_GPX0(0), S3C_GPIO_SFN(0xf));
    s3c_gpio_setpull(EXYNOS4_GPX0(0), S3C_GPIO_PULL_NONE);
    gpio_free(EXYNOS4_GPX0(0));

    return 0;
}

static struct mcp251x_platform_data mcp251x_info = {
    .oscillator_frequency = 8000000,
    .board_specific_setup = mcp251x_ioSetup,
};
#endif

static struct s3c64xx_spi_csinfo spi2_csi[] = {
    [0] = {
    .line = EXYNOS4_GPC1(2),
    .set_level = gpio_set_value,
    .fb_delay = 0x2,
},
};

static struct spi_board_info spi2_board_info[] __initdata = {
#if 0	//remove by cym 20130529
{
    .modalias = "spidev",
    .platform_data = NULL,
    .max_speed_hz = 10*1000*1000,
    .bus_num = 2,
    .chip_select = 0,
    .mode = SPI_MODE_0,
    .controller_data = &spi2_csi[0],
}
#endif
#ifdef CONFIG_CAN_MCP251X
{
    .modalias = "mcp2515",
    .platform_data = &mcp251x_info,
    .irq = IRQ_EINT(0),
    .max_speed_hz = 10*1000*1000,
    .bus_num = 2,
    .chip_select = 0,
    .mode = SPI_MODE_0,
    .controller_data = &spi2_csi[0],
}
#endif
};
#endif

static int exynos4_notifier_call(struct notifier_block *this,
                                 unsigned long code, void *_cmd)
{
    int mode = 0;

    if ((code == SYS_RESTART) && _cmd)
        if (!strcmp((char *)_cmd, "recovery"))
            mode = 0xf;

    __raw_writel(mode, REG_INFORM4);

    return NOTIFY_DONE;
}

static struct notifier_block exynos4_reboot_notifier = {
    .notifier_call = exynos4_notifier_call,
};


#ifdef CONFIG_S3C_DEV_HSMMC
static struct s3c_sdhci_platdata smdk4x12_hsmmc0_pdata __initdata = {
    .cd_type		= S3C_SDHCI_CD_INTERNAL,
    .clk_type		= S3C_SDHCI_CLK_DIV_EXTERNAL,
#ifdef CONFIG_EXYNOS4_SDHCI_CH0_8BIT
    .max_width		= 8,
    .host_caps		= MMC_CAP_8_BIT_DATA,
#endif
};
#endif

#ifdef CONFIG_S3C_DEV_HSMMC1
static struct s3c_sdhci_platdata smdk4x12_hsmmc1_pdata __initdata = {
    .cd_type		= S3C_SDHCI_CD_INTERNAL,
    .clk_type		= S3C_SDHCI_CLK_DIV_EXTERNAL,
};
#endif

#ifdef CONFIG_S3C_DEV_HSMMC2
static struct s3c_sdhci_platdata smdk4x12_hsmmc2_pdata __initdata = {
    .cd_type		= S3C_SDHCI_CD_GPIO,//lisw sd    S3C_SDHCI_CD_INTERNAL,
    .ext_cd_gpio            =EXYNOS4_GPX0(7), //lisw sd
    .ext_cd_gpio_invert     = 1,//lisw sd
    .clk_type		= S3C_SDHCI_CLK_DIV_EXTERNAL,
#ifdef CONFIG_EXYNOS4_SDHCI_CH2_8BIT
    .max_width		= 8,
    .host_caps		= MMC_CAP_8_BIT_DATA,
#endif
};
#endif

#ifdef CONFIG_S3C_DEV_HSMMC3

static struct s3c_sdhci_platdata smdk4x12_hsmmc3_pdata __initdata = {
    // SEMCO
    /* modify by cym 20130408 */
    //#if 0
#ifdef CONFIG_MTK_COMBO_MT66XX
    /* end modify */
    .cd_type		= S3C_SDHCI_CD_INTERNAL,
    .clk_type		= S3C_SDHCI_CLK_DIV_EXTERNAL,
#else
    .cd_type		= S3C_SDHCI_CD_PERMANENT,
    .clk_type		= S3C_SDHCI_CLK_DIV_EXTERNAL,
#endif
};


#endif


// USB3503A, HSIC1 -> USB Host
/* modify by cym 20130826 */
#ifdef CONFIG_CPU_TYPE_SCP
#define GPIO_HUB_RESET EXYNOS4212_GPM2(4)
#define GPIO_HUB_CONNECT EXYNOS4212_GPM3(3)
#else
#define GPIO_HUB_RESET EXYNOS4_GPL2(2)
#define GPIO_HUB_CONNECT EXYNOS4_GPK3(2)
#endif

//add by dg 2015-04-14
#if defined(CONFIG_MTK_COMBO_MT66XX)


void setup_mt6620_wlan_power_for_onoff(int on)
{

    int chip_pwd_low_val;
    int outValue;

    printk("[mt6620] +++ %s : wlan power %s\n",__func__, on?"on":"off");

    if (on) {
        outValue = 0;
    } else {
        outValue = 1;
    }

    if (gpio_request(EXYNOS4_GPX3(2),  "6260_GPIO2")!=0) {
        printk("[mt6620] ERROR:Cannot request 6260_GPIO2\n");
    } else {
        gpio_direction_output(EXYNOS4_GPX3(2), 1);/* WLAN_CHIP_PWD */
        gpio_set_value(EXYNOS4_GPX3(2), outValue);
        mdelay(100);
        gpio_free(EXYNOS4_GPX3(2));
    }

    printk("[mt6620] --- %s\n",__func__);

}
EXPORT_SYMBOL(setup_mt6620_wlan_power_for_onoff);


static struct mtk_wmt_platform_data mtk_wmt_pdata = {
    .pmu =EXYNOS4_GPC1(0), //RK30SDK_WIFI_GPIO_POWER_N,//RK30_PIN0_PB5, //MUST set to pin num in target system
    .rst = EXYNOS4_GPC1(1),//RK30SDK_WIFI_GPIO_RESET_N,//RK30_PIN3_PD0, //MUST set to pin num in target system
    .bgf_int = EXYNOS4_GPX2(4), //IRQ_EINT(20),//RK30SDK_WIFI_GPIO_BGF_INT_B,//RK30_PIN0_PA5,//MUST set to pin num in target system if use UART interface.
    .urt_cts = -EINVAL, // set it to the correct GPIO num if use common SDIO, otherwise set it to -EINVAL.
    .rtc = -EINVAL, //Optipnal. refer to HW design.
    .gps_sync = -EINVAL, //Optional. refer to HW design.
    .gps_lna = -EINVAL, //Optional. refer to HW design.
};
static struct mtk_sdio_eint_platform_data mtk_sdio_eint_pdata = {
    .sdio_eint = EXYNOS4_GPX2(5),//IRQ_EINT(21) ,//RK30SDK_WIFI_GPIO_WIFI_INT_B,//53, //MUST set pin num in target system.
};
static struct platform_device mtk_wmt_dev = {
    .name = "mtk_wmt",
    .id = 1,
    .dev = {


        .platform_data = &mtk_wmt_pdata,
    },
};
static struct platform_device mtk_sdio_eint_dev = {
    .name = "mtk_sdio_eint",
    .id = 1,
    .dev = {
        .platform_data = &mtk_sdio_eint_pdata,
    },
};
static void __init mtk_combo_init(void)
{

    //MT66XX PMUEN
    if(gpio_request(EXYNOS4_GPC1(0), "GPC1_0"))
    {
        printk(KERN_ERR "failed to request GPC1_0 for MT6620  PMUEN control\n");

    }

    //MT66XX SYSRST
    if(gpio_request(EXYNOS4_GPC1(1), "GPC1_1"))
    {
        printk(KERN_ERR "failed to request GPC1_1 for MT6620  SYSRST control\n");

    }


    s3c_gpio_cfgpin(EXYNOS4_GPC1(0), S3C_GPIO_OUTPUT);
    s3c_gpio_cfgpin(EXYNOS4_GPC1(1), S3C_GPIO_OUTPUT);

    gpio_direction_output(EXYNOS4_GPC1(0), 0);
    gpio_direction_output(EXYNOS4_GPC1(1), 0);


    gpio_free(EXYNOS4_GPC1(0));
    gpio_free(EXYNOS4_GPC1(1));

    mdelay(5);


    //need config eint models for Wifi & BGA Interupt
    if (gpio_request(EXYNOS4_GPX2(5), "WiFi INT"))
        printk(KERN_WARNING "MT6620 WiFi INT(GPX2.5) Port request error!!!\n");
    else    {
        s3c_gpio_setpull(EXYNOS4_GPX2(5), S3C_GPIO_PULL_NONE);
        s3c_gpio_cfgpin(EXYNOS4_GPX2(5), S3C_GPIO_SFN(0xF));
        gpio_free(EXYNOS4_GPX2(5));
    }

    if (gpio_request(EXYNOS4_GPX2(4), "BGF INT"))
        printk(KERN_WARNING "MT6620 BGA INT(GPX2.4) Port request error!!!\n");
    else    {
        s3c_gpio_setpull(EXYNOS4_GPX2(4), S3C_GPIO_PULL_NONE);
        s3c_gpio_cfgpin(EXYNOS4_GPX2(4), S3C_GPIO_SFN(0xF));
        gpio_free(EXYNOS4_GPX2(4));
    }


    //normal it is high level
    if (gpio_request(EXYNOS4_GPX3(2),  "6260_GPIO2")!=0) {
        printk("[mt6620] ERROR:Cannot request 6260_GPIO2\n");
    } else {
        gpio_direction_output(EXYNOS4_GPX3(2), 1);/* WLAN_CHIP_PWD */
        gpio_set_value(EXYNOS4_GPX3(2), 1);
        mdelay(100);
        gpio_free(EXYNOS4_GPX3(2));
    }




    return;
}


static int  itop4412_wifi_combo_module_gpio_init(void)
{

    mtk_combo_init();
    platform_device_register(&mtk_wmt_dev);
    platform_device_register(&mtk_sdio_eint_dev);
}

#endif---//#if defined(CONFIG_MTK_COMBO_MT66XX)




#ifdef CONFIG_S5P_DEV_MSHC
static struct s3c_mshci_platdata exynos4_mshc_pdata __initdata = {
    .cd_type		= S3C_MSHCI_CD_PERMANENT,
    .clk_type		= S3C_MSHCI_CLK_DIV_EXTERNAL, //lisw ms
    .has_wp_gpio		= true,
    .wp_gpio		= 0xffffffff,
#if defined(CONFIG_EXYNOS4_MSHC_8BIT) && \
    defined(CONFIG_EXYNOS4_MSHC_DDR)
    .max_width		= 8,
    .host_caps		= MMC_CAP_8_BIT_DATA | MMC_CAP_1_8V_DDR |
            MMC_CAP_UHS_DDR50,
#elif defined(CONFIG_EXYNOS4_MSHC_8BIT)
    .max_width		= 8,
    .host_caps		= MMC_CAP_8_BIT_DATA,
#elif defined(CONFIG_EXYNOS4_MSHC_DDR)
    .host_caps		= MMC_CAP_1_8V_DDR | MMC_CAP_UHS_DDR50,
#endif
};
#endif

#ifdef CONFIG_USB_EHCI_S5P
static struct s5p_ehci_platdata smdk4x12_ehci_pdata;

static void __init smdk4x12_ehci_init(void)
{
    struct s5p_ehci_platdata *pdata = &smdk4x12_ehci_pdata;

    s5p_ehci_set_platdata(pdata);
}

/* end modify */
#ifndef CONFIG_TC4_DVT
#ifndef CONFIG_CAN_MCP251X
#define I2C_SDA6 EXYNOS4_GPC1(3)
#define I2C_SCL6 EXYNOS4_GPC1(4)
#endif
#endif
void usb_hub_gpio_init(/*add by cym 20130426 */ void /* end add */)
{
    //printk("shengliang set HUB_RESET & HUB_CONNECT\n");
    // HUB_RESET

    /* add by cym 20121114 */
    static char flags = 0;

#if 1
    if(0 == flags)
    {
        gpio_request(GPIO_HUB_RESET, "GPIO_HUB_RESET");
        gpio_direction_output(GPIO_HUB_RESET, 1);
        s3c_gpio_setpull(GPIO_HUB_RESET, S3C_GPIO_PULL_NONE);
        gpio_free(GPIO_HUB_RESET);

        /*****************************************************************************************************************/
        //dg add  macro '#ifdef CONFIG_CPU_TYPE_SCP' on 2015-05-20
        //pop coreboard on wifi mt6620 chip need that ,pop wifi/bluetooth use EXYNOS4_GPK3(2)  pin, it is more important.
        //on pop core board  EXYNOS4_GPK3(2) is used for mt6620 wifi chip and usb3503A usb hub too.  SCP  is not that.
        //on pop usb3503A is  needed must.
        /*****************************************************************************************************************/
        // HUB_CONNECT
#ifndef CONFIG_CPU_TYPE_SCP //POP corebord
#ifdef  CONFIG_MTK_COMBO_MT66XX    // wifi module

        //do nothing  GPIO_HUB_CONNECT is input pin.
#else
        //usb hub work
        gpio_request(GPIO_HUB_CONNECT, "GPIO_HUB_CONNECT");
        gpio_direction_output(GPIO_HUB_CONNECT, 1);
        s3c_gpio_setpull(GPIO_HUB_CONNECT, S3C_GPIO_PULL_NONE);
        gpio_free(GPIO_HUB_CONNECT);
#endif//end CONFIG_MTK_COMBO_MT66XX
#else //SCP core board
        gpio_request(GPIO_HUB_CONNECT, "GPIO_HUB_CONNECT");
        gpio_direction_output(GPIO_HUB_CONNECT, 1);
        s3c_gpio_setpull(GPIO_HUB_CONNECT, S3C_GPIO_PULL_NONE);
        gpio_free(GPIO_HUB_CONNECT);
#endif //end CONFIG_CPU_TYPE_SCP


        flags = 1;
    }
#ifndef CONFIG_TC4_DVT
#ifndef CONFIG_CAN_MCP251X
    // I2C_SDA6
    gpio_request(I2C_SDA6, "I2C_SDA6");
    gpio_direction_output(I2C_SDA6,1);
    s3c_gpio_setpull(I2C_SDA6, S3C_GPIO_PULL_NONE);
    gpio_free(I2C_SDA6);

    // I2C_SCL6
    gpio_request(I2C_SCL6, "I2C_SCL6");
    gpio_direction_output(I2C_SCL6,1);
    s3c_gpio_setpull(I2C_SCL6, S3C_GPIO_PULL_NONE);
    gpio_free(I2C_SCL6);
#endif
#endif
#endif
    /* end remove */

    /* add by cym 20140115 for USI 3G Power On*/
#ifdef CONFIG_UNAPLUS
#if 1
    if(gpio_request(EXYNOS4_GPK1(0), "GPK1_0"))
    {
        printk(KERN_ERR "failed to request GPK1_0 for "
                        "USI control\n");
        //return err;
    }
    gpio_direction_output(EXYNOS4_GPK1(0), 1);

    s3c_gpio_cfgpin(EXYNOS4_GPK1(0), S3C_GPIO_OUTPUT);
    gpio_free(EXYNOS4_GPK1(0));
    mdelay(5);
#endif
#endif
    /* end add */
}
#endif

#ifdef CONFIG_USB_OHCI_S5P
static struct s5p_ohci_platdata smdk4x12_ohci_pdata;

static void __init smdk4x12_ohci_init(void)
{
    struct s5p_ohci_platdata *pdata = &smdk4x12_ohci_pdata;

    s5p_ohci_set_platdata(pdata);
}
#endif

/* USB GADGET */
#ifdef CONFIG_USB_GADGET
static struct s5p_usbgadget_platdata smdk4x12_usbgadget_pdata;

static void __init smdk4x12_usbgadget_init(void)
{
    struct s5p_usbgadget_platdata *pdata = &smdk4x12_usbgadget_pdata;

    s5p_usbgadget_set_platdata(pdata);
}
#endif

static struct platform_device tc4_regulator_consumer = 
{	.name = "tc4-regulator-consumer",
        .id = -1,
};


#ifdef CONFIG_REGULATOR_S5M8767
/* S5M8767 Regulator */
static int s5m_cfg_irq(void)
{
    /* AP_PMIC_IRQ: EINT15 */
    s3c_gpio_cfgpin(EXYNOS4_GPX1(7), S3C_GPIO_SFN(0xF));
    s3c_gpio_setpull(EXYNOS4_GPX1(7), S3C_GPIO_PULL_UP);
    return 0;
}
//static struct regulator_consumer_supply s5m8767_ldo1_supply[] = {
//	REGULATOR_SUPPLY("vdd_alive", NULL),
//};

static struct regulator_consumer_supply s5m8767_ldo2_supply[] = {
    REGULATOR_SUPPLY("vddq_m12", NULL),
};

//static struct regulator_consumer_supply s5m8767_ldo3_supply[] = {
//	REGULATOR_SUPPLY("vddioap_18", NULL),
//};

//static struct regulator_consumer_supply s5m8767_ldo4_supply[] = {
//	REGULATOR_SUPPLY("vddq_pre", NULL),
//};

static struct regulator_consumer_supply s5m8767_ldo5_supply[] = {
    REGULATOR_SUPPLY("vdd18_2m", NULL),
};

//static struct regulator_consumer_supply s5m8767_ldo6_supply[] = {
//	REGULATOR_SUPPLY("vdd10_mpll", NULL),
//};

//static struct regulator_consumer_supply s5m8767_ldo7_supply[] = {
//	REGULATOR_SUPPLY("vdd10_xpll", NULL),
//};

static struct regulator_consumer_supply s5m8767_ldo8_supply[] = {
    REGULATOR_SUPPLY("vdd10_mipi", NULL),
};

static struct regulator_consumer_supply s5m8767_ldo9_supply[] = {
    REGULATOR_SUPPLY("vdd33_lcd", NULL),
};

static struct regulator_consumer_supply s5m8767_ldo10_supply[] = {
    REGULATOR_SUPPLY("vdd18_mipi", NULL),
};

//static struct regulator_consumer_supply s5m8767_ldo11_supply[] = {
//	REGULATOR_SUPPLY("vdd18_abb1", NULL),
//};

static struct regulator_consumer_supply s5m8767_ldo12_supply[] = {
    REGULATOR_SUPPLY("vdd33_uotg", NULL),
};

//static struct regulator_consumer_supply s5m8767_ldo13_supply[] = {
//	REGULATOR_SUPPLY("vddioperi_18", NULL),
//};

//static struct regulator_consumer_supply s5m8767_ldo14_supply[] = {
//	REGULATOR_SUPPLY("vdd18_abb02", NULL),
//};

static struct regulator_consumer_supply s5m8767_ldo15_supply[] = {
    REGULATOR_SUPPLY("vdd10_ush", NULL),
};

static struct regulator_consumer_supply s5m8767_ldo16_supply[] = {
    REGULATOR_SUPPLY("vdd18_hsic", NULL),
};

//static struct regulator_consumer_supply s5m8767_ldo17_supply[] = {
//	REGULATOR_SUPPLY("vddioap_mmc012_28", NULL),
//};
static struct regulator_consumer_supply s5m8767_ldo18_supply[] = {
    REGULATOR_SUPPLY("vddioperi_28", NULL),
};

static struct regulator_consumer_supply s5m8767_ldo19_supply[] = {
    REGULATOR_SUPPLY("dc33v_tp", NULL),		//cym 20130227
};


static struct regulator_consumer_supply s5m8767_ldo20_supply[] = {
    REGULATOR_SUPPLY("vdd28_cam", NULL),
};
static struct regulator_consumer_supply s5m8767_ldo21_supply[] = {
    REGULATOR_SUPPLY("vdd28_af", NULL),
};

static struct regulator_consumer_supply s5m8767_ldo22_supply[] = {
    REGULATOR_SUPPLY("vdda28_2m", NULL),
};

static struct regulator_consumer_supply s5m8767_ldo23_supply[] = {
    REGULATOR_SUPPLY("vdd_tf", NULL),
};


static struct regulator_consumer_supply s5m8767_ldo24_supply[] = {
    REGULATOR_SUPPLY("vdd33_a31", NULL),
};

static struct regulator_consumer_supply s5m8767_ldo25_supply[] = {
    REGULATOR_SUPPLY("vdd18_cam", NULL),
};

static struct regulator_consumer_supply s5m8767_ldo26_supply[] = {
    REGULATOR_SUPPLY("vdd18_a31", NULL),
};
static struct regulator_consumer_supply s5m8767_ldo27_supply[] = {
    REGULATOR_SUPPLY("gps_1v8", NULL),
};
static struct regulator_consumer_supply s5m8767_ldo28_supply[] = {
    REGULATOR_SUPPLY("dvdd12", NULL),
};


static struct regulator_consumer_supply s5m8767_buck1_consumer =
        REGULATOR_SUPPLY("vdd_mif", NULL);

static struct regulator_consumer_supply s5m8767_buck2_consumer =
        REGULATOR_SUPPLY("vdd_arm", NULL);

static struct regulator_consumer_supply s5m8767_buck3_consumer =
        REGULATOR_SUPPLY("vdd_int", NULL);

static struct regulator_consumer_supply s5m8767_buck4_consumer =
        REGULATOR_SUPPLY("vdd_g3d", NULL);

static struct regulator_consumer_supply s5m8767_buck5_consumer =
        REGULATOR_SUPPLY("vdd_m12", NULL);
static struct regulator_consumer_supply s5m8767_buck6_consumer =
        REGULATOR_SUPPLY("vdd12_5m", NULL);

static struct regulator_consumer_supply s5m8767_buck9_consumer =
        REGULATOR_SUPPLY("vddf28_emmc", NULL);



#define REGULATOR_INIT(_ldo, _name, _min_uV, _max_uV, _always_on, _ops_mask,\
    _disabled) \
    static struct regulator_init_data s5m8767_##_ldo##_init_data = {		\
    .constraints = {					\
    .name	= _name,				\
    .min_uV = _min_uV,				\
    .max_uV = _max_uV,				\
    .always_on	= _always_on,			\
    .boot_on	= _always_on,			\
    .apply_uV	= 1,				\
    .valid_ops_mask = _ops_mask,			\
    .state_mem	= {				\
    .disabled	= _disabled,		\
    .enabled	= !(_disabled),		\
    }						\
    },							\
    .num_consumer_supplies = ARRAY_SIZE(s5m8767_##_ldo##_supply),	\
    .consumer_supplies = &s5m8767_##_ldo##_supply[0],			\
    };

//REGULATOR_INIT(ldo1, "VDD_ALIVE", 1100000, 1100000, 1,
//		REGULATOR_CHANGE_STATUS, 0);
/* modify by cym 20130709 */
#ifdef CONFIG_CPU_TYPE_SCP
REGULATOR_INIT(ldo2, "VDDQ_M12", 1500000, 1500000, 1,
               REGULATOR_CHANGE_STATUS, 1)
#else
REGULATOR_INIT(ldo2, "VDDQ_M12", 1200000, 1200000, 1,
               REGULATOR_CHANGE_STATUS, 1);//sleep controlled by pwren
#endif
/* end modify */
//REGULATOR_INIT(ldo3, "VDDIOAP_18", 1800000, 1800000, 1,
//		REGULATOR_CHANGE_STATUS, 0);
//REGULATOR_INIT(ldo4, "VDDQ_PRE", 1800000, 1800000, 1,
//		REGULATOR_CHANGE_STATUS, 1); //sleep controlled by pwren

REGULATOR_INIT(ldo5, "VDD18_2M", 1800000, 1800000, 0,
               REGULATOR_CHANGE_STATUS, 1);
//REGULATOR_INIT(ldo6, "VDD10_MPLL", 1000000, 1000000, 1,
//		REGULATOR_CHANGE_STATUS, 1);//sleep controlled by pwren
//REGULATOR_INIT(ldo7, "VDD10_XPLL", 1000000, 1000000, 1,
//		REGULATOR_CHANGE_STATUS, 1);//sleep controlled by pwren
REGULATOR_INIT(ldo8, "VDD10_MIPI", 1000000, 1000000, 0,
               REGULATOR_CHANGE_STATUS, 1);
#ifdef CONFIG_TOUCHSCREEN_TSC2007
REGULATOR_INIT(ldo9, "VDD33_LCD", 3300000, 3300000, 1,
               REGULATOR_CHANGE_STATUS, 1);
#else
REGULATOR_INIT(ldo9, "VDD33_LCD", 3300000, 3300000, 1,
               REGULATOR_CHANGE_STATUS, 1);
#endif

REGULATOR_INIT(ldo10, "VDD18_MIPI", 1800000, 1800000, 0,
               REGULATOR_CHANGE_STATUS, 1);
//REGULATOR_INIT(ldo11, "VDD18_ABB1", 1800000, 1800000, 1,
//		REGULATOR_CHANGE_STATUS, 0); //???
REGULATOR_INIT(ldo12, "VDD33_UOTG", 3300000, 3300000, 1,
               REGULATOR_CHANGE_STATUS, 0);
//REGULATOR_INIT(ldo13, "VDDIOPERI_18", 1800000, 1800000, 1,
//		REGULATOR_CHANGE_STATUS, 0);//???
//REGULATOR_INIT(ldo14, "VDD18_ABB02", 1800000, 1800000, 1,
//		REGULATOR_CHANGE_STATUS, 0); //???
REGULATOR_INIT(ldo15, "VDD10_USH", 1000000, 1000000, 1,
               REGULATOR_CHANGE_STATUS, 1);

//liang, VDD18_HSIC must be 1.8V, otherwise USB HUB 3503A can't be recognized
REGULATOR_INIT(ldo16, "VDD18_HSIC", 1800000, 1800000, 1,
               REGULATOR_CHANGE_STATUS, 1);
//REGULATOR_INIT(ldo17, "VDDIOAP_MMC012_28", 2800000, 2800000, 1,
//		REGULATOR_CHANGE_STATUS, 0); //???
REGULATOR_INIT(ldo18, "VDDIOPERI_28", 3300000, 3300000, 1,
               REGULATOR_CHANGE_STATUS, 0);//???
REGULATOR_INIT(ldo19, "DC33V_TP", 3300000, 3300000, 0,
               REGULATOR_CHANGE_STATUS, 1); //??
//#ifdef CONFIG_VIDEO_OV5640
#if defined(CONFIG_VIDEO_OV5640) || defined(CONFIG_VIDEO_TVP5150)
REGULATOR_INIT(ldo20, "VDD28_CAM", 1800000, 1800000, 0,
               REGULATOR_CHANGE_STATUS, 1);
#else
REGULATOR_INIT(ldo20, "VDD28_CAM", 2800000, 2800000, 0,
               REGULATOR_CHANGE_STATUS, 1);
#endif

/* modify by cym 20141106 */
#ifdef CONFIG_VIDEO_TVP5150
//REGULATOR_INIT(ldo21, "VDD28_AF", 3300000, 3300000, 0,
//             REGULATOR_CHANGE_STATUS, 1);

//dg change for tvp5150 IO_DVDD Pin10, datasheet show need 3.3V,but real 3.3v not work,why?
REGULATOR_INIT(ldo21, "VDD28_AF", 1800000, 1800000, 0,
               REGULATOR_CHANGE_STATUS, 1);

#else
REGULATOR_INIT(ldo21, "VDD28_AF", 2800000, 2800000, 0,
               REGULATOR_CHANGE_STATUS, 1);
#endif
REGULATOR_INIT(ldo22, "VDDA28_2M", 2800000, 2800000, 0,
               REGULATOR_CHANGE_STATUS, 1);
REGULATOR_INIT(ldo23, "VDD28_TF", 2800000, 2800000, 1,
               REGULATOR_CHANGE_STATUS, 1);//sleep controlled by pwren

#if 0
REGULATOR_INIT(ldo24, "VDD33_A31", 3300000, 3300000, 1,
               REGULATOR_CHANGE_STATUS, 0);
#else
#if defined(CONFIG_MTK_COMBO_COMM) || defined(CONFIG_MTK_COMBO_COMM_MODULE) || defined(CONFIG_MTK_COMBO_MT66XX)
REGULATOR_INIT(ldo24, "VDD33_A31", 2800000, 2800000, 1,
               REGULATOR_CHANGE_STATUS, 0);
#else
REGULATOR_INIT(ldo24, "VDD33_A31", 3300000, 3300000, 1,
               REGULATOR_CHANGE_STATUS, 0);
#endif
#endif

REGULATOR_INIT(ldo25, "VDD18_CAM", 1800000, 1800000, 0,
               REGULATOR_CHANGE_STATUS, 1);
REGULATOR_INIT(ldo26, "VDD18_A31", 1800000, 1800000, 1,
               REGULATOR_CHANGE_STATUS, 0);
REGULATOR_INIT(ldo27, "GPS_1V8", 1800000, 1800000, 1,
               REGULATOR_CHANGE_STATUS, 1);
REGULATOR_INIT(ldo28, "DVDD12", 1200000, 1200000, 0,
               REGULATOR_CHANGE_STATUS, 1);


static struct regulator_init_data s5m8767_buck1_data = {
    .constraints	= {
        .name		= "vdd_mif range",
        .min_uV		= 900000,
        .max_uV		= 1100000,
        .valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
        REGULATOR_CHANGE_STATUS,
        .state_mem	= {
            .disabled	= 1,
        },
    },
    .num_consumer_supplies	= 1,
    .consumer_supplies	= &s5m8767_buck1_consumer,
};

static struct regulator_init_data s5m8767_buck2_data = {
    .constraints	= {
        .name		= "vdd_arm range",
        .min_uV		=  850000,
        .max_uV		= 1450000,
        .valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
        REGULATOR_CHANGE_STATUS,
        .state_mem	= {
            .disabled	= 1,
        },
    },
    .num_consumer_supplies	= 1,
    .consumer_supplies	= &s5m8767_buck2_consumer,
};

static struct regulator_init_data s5m8767_buck3_data = {
    .constraints	= {
        .name		= "vdd_int range",
        .min_uV		=  875000,
        .max_uV		= 1200000,
        .apply_uV	= 1,
        .valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
        REGULATOR_CHANGE_STATUS,
        .state_mem	= {
            //.uV		= 1100000,
            .mode		= REGULATOR_MODE_NORMAL,
            .disabled	= 1,
        },
    },
    .num_consumer_supplies	= 1,
    .consumer_supplies	= &s5m8767_buck3_consumer,
};

static struct regulator_init_data s5m8767_buck4_data = {
    .constraints	= {
        .name		= "vdd_g3d range",
        .min_uV		= 750000,
        .max_uV		= 1500000,
        .valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
        REGULATOR_CHANGE_STATUS,
        .state_mem	= {
            .disabled	= 1,
        },
    },
    .num_consumer_supplies = 1,
    .consumer_supplies = &s5m8767_buck4_consumer,
};

static struct regulator_init_data s5m8767_buck5_data = {
    .constraints	= {
        .name		= "vdd_m12 range",
        .min_uV		= 750000,
        .max_uV		= 1500000,
        .apply_uV	= 1,
        .boot_on	= 1,
        .valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
        REGULATOR_CHANGE_STATUS,
        .state_mem	= {
            .enabled	= 1,
        },
    },
    .num_consumer_supplies = 1,
    .consumer_supplies = &s5m8767_buck5_consumer,
};
static struct regulator_init_data s5m8767_buck6_data = {
    .constraints	= {
        .name		= "vdd12_5m range",
        .min_uV		= 750000,
        .max_uV		= 1500000,
        .boot_on	= 0,
        .apply_uV	= 1,
        .valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
        REGULATOR_CHANGE_STATUS,
        .state_mem	= {
            .disabled	= 1,
        },
    },
    .num_consumer_supplies = 1,
    .consumer_supplies = &s5m8767_buck6_consumer,
};
static struct regulator_init_data s5m8767_buck9_data = {
    .constraints	= {
        .name		= "vddf28_emmc range",
        .min_uV		= 750000,
        .max_uV		= 3000000,
        .boot_on	= 1,
        .apply_uV	= 1,
        .valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
        REGULATOR_CHANGE_STATUS,
        .state_mem	= {
            .disabled	= 1,
        },
    },
    .num_consumer_supplies = 1,
    .consumer_supplies = &s5m8767_buck9_consumer,
};




static struct s5m_regulator_data pegasus_regulators[] = {
{ S5M8767_BUCK1, &s5m8767_buck1_data },
{ S5M8767_BUCK2, &s5m8767_buck2_data },
{ S5M8767_BUCK3, &s5m8767_buck3_data },
{ S5M8767_BUCK4, &s5m8767_buck4_data },
{ S5M8767_BUCK5, &s5m8767_buck5_data },
{ S5M8767_BUCK6, &s5m8767_buck6_data },
{ S5M8767_BUCK9, &s5m8767_buck9_data },

//{ S5M8767_LDO1, &s5m8767_ldo1_init_data },
{ S5M8767_LDO2, &s5m8767_ldo2_init_data },
//{ S5M8767_LDO3, &s5m8767_ldo3_init_data },
//{ S5M8767_LDO4, &s5m8767_ldo4_init_data },
{ S5M8767_LDO5, &s5m8767_ldo5_init_data },
//{ S5M8767_LDO6, &s5m8767_ldo6_init_data },
//{ S5M8767_LDO7, &s5m8767_ldo7_init_data },
{ S5M8767_LDO8, &s5m8767_ldo8_init_data },
{ S5M8767_LDO9, &s5m8767_ldo9_init_data },
{ S5M8767_LDO10, &s5m8767_ldo10_init_data },

//{ S5M8767_LDO11, &s5m8767_ldo11_init_data },
{ S5M8767_LDO12, &s5m8767_ldo12_init_data },
//{ S5M8767_LDO13, &s5m8767_ldo13_init_data },
//{ S5M8767_LDO14, &s5m8767_ldo14_init_data },
{ S5M8767_LDO15, &s5m8767_ldo15_init_data },
{ S5M8767_LDO16, &s5m8767_ldo16_init_data },
//{ S5M8767_LDO17, &s5m8767_ldo17_init_data },
{ S5M8767_LDO18, &s5m8767_ldo18_init_data },
{ S5M8767_LDO19, &s5m8767_ldo19_init_data },
{ S5M8767_LDO20, &s5m8767_ldo20_init_data },

{ S5M8767_LDO21, &s5m8767_ldo21_init_data },
{ S5M8767_LDO22, &s5m8767_ldo22_init_data },
{ S5M8767_LDO23, &s5m8767_ldo23_init_data },
{ S5M8767_LDO24, &s5m8767_ldo24_init_data },
{ S5M8767_LDO25, &s5m8767_ldo25_init_data },
{ S5M8767_LDO26, &s5m8767_ldo26_init_data },
{ S5M8767_LDO27, &s5m8767_ldo27_init_data },
{ S5M8767_LDO28, &s5m8767_ldo28_init_data },


};

static struct s5m_platform_data exynos4_s5m8767_pdata = {
    .device_type		= S5M8767X,
    .irq_base		= IRQ_BOARD_START,
    .num_regulators		= ARRAY_SIZE(pegasus_regulators),
    .regulators		= pegasus_regulators,
    .cfg_pmic_irq		= s5m_cfg_irq,

    .buck_ramp_delay        = 10,
};
/* End of S5M8767 */
#endif


/* ly 20111102 : i2c devs mapping: 
  * i2c0 : HDMI
  * i2c1 : max8997: PMIC & RTC & motor
  * i2c2 : not used
  * i2c3 : touch
  * i2c4 : max8997 fuel gauge & wm8960
  * i2c5 : sensor: MPU3050
  * i2c6 : camera & HSIC
  * i2c7 : light sensor
  */
static struct i2c_board_info i2c_devs0[] __initdata = {
#ifdef CONFIG_VIDEO_TVOUT
{
    I2C_BOARD_INFO("s5p_ddc", (0x74 >> 1)),
},
#endif
};

static struct i2c_board_info i2c_devs1[] __initdata = {
{
#ifdef CONFIG_REGULATOR_S5M8767

    I2C_BOARD_INFO("s5m87xx", 0xCC >> 1),
    .platform_data = &exynos4_s5m8767_pdata,
    .irq		= IRQ_EINT(15),
#endif
},
};
#if 1 //iic 2 : nfc
static struct i2c_board_info i2c_devs2[] __initdata = {

};
#endif
// For S5K4EC(using i2c6)
#ifndef CONFIG_CAN_MCP251X
static struct i2c_board_info i2c_devs6[] __initdata = {

};
#endif

/* add by cym 20130515 */
#ifdef CONFIG_TOUCHSCREEN_FT5X0X
#include <plat/ft5x0x_touch.h>
static struct ft5x0x_i2c_platform_data ft5x0x_pdata = {
    .gpio_irq               = EXYNOS4_GPX0(4),
    .irq_cfg                = S3C_GPIO_SFN(0xf),
    .screen_max_x   = 768,
    .screen_max_y   = 1024,
    .pressure_max   = 255,
};
#if 0
static int __init setup_width_height(char *str)
{
    if (!strncasecmp("9.7", str, 3)) {
        //printk("000000000000000000000000\n");
        ft5x0x_pdata.screen_max_x = 768;
        ft5x0x_pdata.screen_max_y = 1024;

    }
    else if(!strncasecmp("7.0", str, 3))
    {
        //printk("1111111111111111111111111\n");
        ft5x0x_pdata.screen_max_x = 1280;//1280;
        ft5x0x_pdata.screen_max_y = 800;//800;
    }

    printk("%s\n", __FUNCTION__);
}
early_param("lcd", setup_width_height);
#endif
#endif
/* end add */
void init_lcd_type()
{
    int err;

    if(gpio_request(EXYNOS4_GPC0(3), "GPC0_3"))
        printk(KERN_WARNING "GPC0_3 Port request error!!!\n");
    else    {
        s3c_gpio_setpull(EXYNOS4_GPC0(3), S3C_GPIO_PULL_NONE);
        s3c_gpio_cfgpin(EXYNOS4_GPC0(3), S3C_GPIO_SFN(0));
        gpio_direction_input(EXYNOS4_GPC0(3));
        //gpio_free(EXYNOS4_GPC0(3));
    }

    if(gpio_request(EXYNOS4_GPX0(6), "GPX0_6"))
        printk(KERN_WARNING "GPX0_6 Port request error!!!\n");
    else    {
        s3c_gpio_setpull(EXYNOS4_GPX0(6), S3C_GPIO_PULL_NONE);
        s3c_gpio_cfgpin(EXYNOS4_GPX0(6), S3C_GPIO_SFN(0));
        gpio_direction_input(EXYNOS4_GPX0(6));
        //gpio_free(EXYNOS4_GPX0(6));
    }
}

int get_lcd_type()
{
    int value1, value2, type = 0;
    int flags = 0;

    //if(0 == flags)
    //{
    //	init_lcd_type();
    //	flags = 1;
    //}
#if 0
    if(gpio_request(EXYNOS4_GPC0(3), "GPC0_3"))
        printk(KERN_WARNING "GPC0_3 Port request error!!!\n");
    else
    {
        value1 = gpio_get_value(EXYNOS4_GPC0(3));
        gpio_free(EXYNOS4_GPC0(3));
    }

    if(gpio_request(EXYNOS4_GPX0(6), "GPX0_6"))
        printk(KERN_WARNING "GPX0_6 Port request error!!!\n");
    else
    {
        value2 = gpio_get_value(EXYNOS4_GPX0(6));
        gpio_free(EXYNOS4_GPC0(3));
    }
#else
    value1 = gpio_get_value(EXYNOS4_GPC0(3));

    value2 = gpio_get_value(EXYNOS4_GPX0(6));
#endif	
    type = (value1<<1)|value2;

    printk("value1 = %d, value2 = %d, type = 0x%x\n", value1, value2, type);

    return type;
}
EXPORT_SYMBOL(get_lcd_type);

void setup_ft5x_width_height()
{
    int type = get_lcd_type();

    if(0x00 == type)	//9.7
    {
#if defined(CONFIG_TOUCHSCREEN_FT5X0X)
        ft5x0x_pdata.screen_max_x = 768;
        ft5x0x_pdata.screen_max_y = 1024;
#endif
        ;
    }
    else if(0x01 == type)	//7.0
    {
#if defined(CONFIG_TOUCHSCREEN_FT5X0X)
        ft5x0x_pdata.screen_max_x = 800;//1280;//1280;
        ft5x0x_pdata.screen_max_y = 1280;//800;//800;
#endif
        ;
    }
    else if(0x02 == type)	//4.3
    {
        ;
    }
}

static struct i2c_board_info i2c_devs3[] __initdata = {
    /* add by cym 20130318 support for FT5X0X TouchScreen */
#if defined(CONFIG_TOUCHSCREEN_FT5X0X)
{
    I2C_BOARD_INFO("ft5x0x_ts", 0x70>>1),
    .irq = IRQ_EINT(4),
    .platform_data = &ft5x0x_pdata,
},
#endif
/* end add */
};

#ifdef CONFIG_SND_SOC_WM8960
#include <sound/wm8960.h>
static struct wm8960_data wm8960_pdata = {
    .capless		= 0,
    .dres			= WM8960_DRES_400R,
};
#endif

/* I2C4 */
static struct i2c_board_info i2c_devs4[] __initdata = {
#ifdef CONFIG_SND_SOC_WM8960
{
    I2C_BOARD_INFO("wm8960", 0x1a),
    .platform_data	= &wm8960_pdata,
},
#endif
};


/* I2C5 */
static struct i2c_board_info i2c_devs5[] __initdata = {
#ifdef CONFIG_TC4_GB// liang
#if defined(CONFIG_MPU_SENSORS_MPU3050) || defined(CONFIG_MPU_SENSORS_MPU3050_MODULE)
    // liang
{
    I2C_BOARD_INFO(SENSOR_MPU_NAME, 0x68),
    //.irq = gpio_to_irq(MPUGPIO),
    .irq = IRQ_EINT(27),
    .platform_data = &mpu_data,
},
#endif  //yulu for test sleep
#endif
#ifdef CONFIG_TC4_ICS
#ifdef CONFIG_MPU_SENSORS_MPU6050B1
{
    I2C_BOARD_INFO("mpu6050", 0x68),
    .platform_data = &mpu6050_data,
    .irq = EXYNOS4_GPX3(3),
},
/*
        {
                I2C_BOARD_INFO("ak8975", 0x0C),
                .platform_data = &inv_mpu_compass_data,
                .irq = EXYNOS4_GPX1(4),
        }
*/
#else
// gyro
{
    I2C_BOARD_INFO(MPU_NAME, 0x68),
    .irq = IRQ_EINT(27),
    .platform_data = &mpu3050_data,
},
// accel
{
    I2C_BOARD_INFO("bma250", (0x30>>1)),
    //.irq = IRQ_EINT(24),// 25?
    .platform_data = &inv_mpu_bma250_data,
},
#endif
#endif
};

/* add by cym 20130417 for TSC2007 TouchScreen */
#ifdef CONFIG_TOUCHSCREEN_TSC2007
#define GPIO_TSC_PORT EXYNOS4_GPX0(0)
static int ts_get_pendown_state(void)
{
    int val;

    val = gpio_get_value(GPIO_TSC_PORT);

    return !val;
}

static int ts_init(void)
{
    int err;

    err = gpio_request_one(EXYNOS4_GPX0(0), GPIOF_IN, "TSC2007_IRQ");
    if (err) {
        printk(KERN_ERR "failed to request TSC2007_IRQ pin\n");
        return -1;
    }

    s3c_gpio_cfgpin(EXYNOS4_GPX0(0), S3C_GPIO_SFN(0xF));
    s3c_gpio_setpull(EXYNOS4_GPX0(0), S3C_GPIO_PULL_NONE);
    gpio_free(EXYNOS4_GPX0(0));

    return 0;
}

static struct tsc2007_platform_data tsc2007_info = {
    .model			= 2007,
    .x_plate_ohms		= 180,
    .get_pendown_state	= ts_get_pendown_state,
    .init_platform_hw	= ts_init,
};
#endif
/* end add */

/* I2C7 */
static struct i2c_board_info i2c_devs7[] __initdata = {
    /* add by cym 20130417 for TSC2007 TouchScreen */
#ifdef CONFIG_TOUCHSCREEN_TSC2007
{
    I2C_BOARD_INFO("tsc2007", 0x48),
    .type		= "tsc2007",
    .platform_data	= &tsc2007_info,
    .irq = IRQ_EINT(0),
}
#endif
/* end add */
};


#ifdef CONFIG_ANDROID_PMEM
static struct android_pmem_platform_data pmem_pdata = {
    .name		= "pmem",
    .no_allocator	= 1,
    .cached		= 0,
    .start		= 0,
    .size		= 0
};

static struct android_pmem_platform_data pmem_gpu1_pdata = {
    .name		= "pmem_gpu1",
    .no_allocator	= 1,
    .cached		= 0,
    .start		= 0,
    .size		= 0,
};

static struct platform_device pmem_device = {
    .name	= "android_pmem",
    .id	= 0,
    .dev	= {
        .platform_data = &pmem_pdata
    },
};

static struct platform_device pmem_gpu1_device = {
    .name	= "android_pmem",
    .id	= 1,
    .dev	= {
        .platform_data = &pmem_gpu1_pdata
    },
};

static void __init android_pmem_set_platdata(void)
{
#if defined(CONFIG_S5P_MEM_CMA)
    pmem_pdata.size = CONFIG_ANDROID_PMEM_MEMSIZE_PMEM * SZ_1K;
    pmem_gpu1_pdata.size = CONFIG_ANDROID_PMEM_MEMSIZE_PMEM_GPU1 * SZ_1K;
#endif
}
#endif

/* s5p-pmic interface */
static struct resource s5p_pmic_resource[] = {

};


struct platform_device s5p_device_pmic = {
    .name             = "s5p-pmic",
    .id               = -1,
    .num_resources    = ARRAY_SIZE(s5p_pmic_resource),
    .resource         = s5p_pmic_resource,



};

EXPORT_SYMBOL(s5p_device_pmic);

#ifdef CONFIG_SWITCH_GPIO
#include <linux/switch.h>
static struct gpio_switch_platform_data headset_switch_data = {
    .name = "h2w",
    .gpio = EXYNOS4_GPX2(2), // "GPX2"
};

static struct resource switch_gpio_resource[] = {
    [0] = {
    .start  = IRQ_EINT(18), // WAKEUP_INT2[2]
    .end    = IRQ_EINT(18),
    .flags  = IORESOURCE_IRQ,
},
};

static struct platform_device headset_switch_device = {
    .name             = "switch-gpio",
    .dev = {
        .platform_data    = &headset_switch_data,
    },
    .num_resources  = ARRAY_SIZE(switch_gpio_resource),
    .resource = switch_gpio_resource,
};
#endif

#if 0
static struct gpio_event_direct_entry smdk4x12_keypad_key_map[] = {
{
    .gpio   = EXYNOS4_GPX0(0),
    .code   = KEY_POWER,
}
};

static struct gpio_event_input_info smdk4x12_keypad_key_info = {
    .info.func              = gpio_event_input_func,
    .info.no_suspend        = true,
    .debounce_time.tv64	= 5 * NSEC_PER_MSEC,
    .type                   = EV_KEY,
    .keymap                 = smdk4x12_keypad_key_map,
    .keymap_size            = ARRAY_SIZE(smdk4x12_keypad_key_map)
};

static struct gpio_event_info *smdk4x12_input_info[] = {
    &smdk4x12_keypad_key_info.info,
};

static struct gpio_event_platform_data smdk4x12_input_data = {
    .names  = {
        "smdk4x12-keypad",
        NULL,
    },
    .info           = smdk4x12_input_info,
    .info_count     = ARRAY_SIZE(smdk4x12_input_info),
};

static struct platform_device smdk4x12_input_device = {
    .name   = GPIO_EVENT_DEV_NAME,
    .id     = 0,
    .dev    = {
        .platform_data = &smdk4x12_input_data,
    },
};
#endif
static void __init smdk4x12_gpio_power_init(void)
{
    /* add by cym 20130417 for TSC2007 TouchScreen */
#ifndef CONFIG_TOUCHSCREEN_TSC2007
    /* end add */
    int err = 0;

    err = gpio_request_one(EXYNOS4_GPX0(0), 0, "GPX0");
    if (err) {
        printk(KERN_ERR "failed to request GPX0 for "
                        "suspend/resume control\n");
        return;
    }
    s3c_gpio_setpull(EXYNOS4_GPX0(0), S3C_GPIO_PULL_NONE);

    gpio_free(EXYNOS4_GPX0(0));

    /* add by cym 20130417 for TSC2007 TouchScreen */
#endif
    /* end add */

#ifdef CONFIG_TOUCHSCREEN_TSC2007
    int err = 0;
#if 0
    err = gpio_request_one(EXYNOS4_GPL1(1), 0, "GPL1_1");
    if (err) {
        printk(KERN_ERR "failed to request GPL1_1 for "
                        "4.3 LCD backlight\n");
        return;
    }

    s3c_gpio_setpull(EXYNOS4_GPL1(1), S3C_GPIO_PULL_UP);

    gpio_set_value(EXYNOS4_GPL1(1), 1);

    gpio_free(EXYNOS4_GPL1(1));
    mdelay(5);
#endif
#if 0
    err = gpio_request_one(EXYNOS4_GPC0(2), 0, "GPC0_2");
    if (err) {
        printk(KERN_ERR "failed to request GPC0_2 for "
                        "4.3 LCD control\n");
        return;
    }

    s3c_gpio_setpull(EXYNOS4_GPC0(2), S3C_GPIO_PULL_UP);
    gpio_set_value(EXYNOS4_GPC0(2), 0);

    mdelay(10);

    gpio_set_value(EXYNOS4_GPC0(2), 0);

    gpio_free(EXYNOS4_GPC0(2));
#endif
#endif
}

/* add by cym 20130619 */
#ifdef CONFIG_KEYBOARD_GPIO
static struct gpio_keys_button gpio_buttons[] = {
{
    .gpio		= EXYNOS4_GPX1(1),
    //.code		= 10,
    .code		= KEY_HOMEPAGE,
    .desc		= "BUTTON1",
    .active_low	= 1,
    .wakeup		= 0,
},
{
    .gpio		= EXYNOS4_GPX1(2),
    //.code		= 24,
    .code		= KEY_BACK,
    .desc		= "BUTTON2",
    .active_low	= 1,
    .wakeup		= 0,
},
{
    .gpio		= EXYNOS4_GPX3(3),
    //.code		= 38,
    .code		= KEY_POWER,
    .desc		= "BUTTON3",
    .active_low	= 1,
    .wakeup		= 0,
},

{
    .gpio           = EXYNOS4_GPX2(0),
    //.code         = 38,
    .code           = KEY_VOLUMEDOWN,
    .desc           = "BUTTON4",
    .active_low     = 1,
    .wakeup         = 0,
},

{
    .gpio           = EXYNOS4_GPX2(1),
    //.code         = 38,
    .code           = KEY_VOLUMEUP,
    .desc           = "BUTTON5",
    .active_low     = 1,
    .wakeup         = 0,
}
};

static struct gpio_keys_platform_data gpio_button_data = {
    .buttons	= gpio_buttons,
    .nbuttons	= ARRAY_SIZE(gpio_buttons),
};

static struct platform_device gpio_button_device = {
    .name		= "gpio-keys",
    .id		= -1,
    .num_resources	= 0,
    .dev		= {
        .platform_data	= &gpio_button_data,
    }
};
#endif
/* end add */

#ifdef CONFIG_SAMSUNG_DEV_KEYPAD
static uint32_t smdk4x12_keymap[] __initdata = {
    /* KEY(row, col, keycode) */
    #if 0
    /*KEY(0, 0, KEY_VOLUMEUP), KEY(0, 1, KEY_VOLUMEDOWN),*/ KEY(0, 2, KEY_HOME), KEY(0, 3, KEY_MENU), KEY(0, 4, KEY_BACK),KEY(0, 5, KEY_POWER)	//volume up ---volume down
    #else
    KEY(8, 0, KEY_1), KEY(8, 3, KEY_2), KEY(8, 5, KEY_3), KEY(8, 6, KEY_4),
    KEY(6, 0, KEY_5), KEY(6, 3, KEY_6), KEY(6, 5, KEY_7), KEY(6, 6, KEY_8),
    KEY(7, 0, KEY_9), KEY(7, 3, KEY_0), KEY(7, 5, KEY_A), KEY(7, 6, KEY_B),
    KEY(13, 0, KEY_C), KEY(13, 3, KEY_D), KEY(13, 5, KEY_E), KEY(13, 6, KEY_F)
    #endif
};

static struct matrix_keymap_data smdk4x12_keymap_data __initdata = {
    .keymap		= smdk4x12_keymap,
    .keymap_size	= ARRAY_SIZE(smdk4x12_keymap),
};

static struct samsung_keypad_platdata smdk4x12_keypad_data __initdata = {
    .keymap_data	= &smdk4x12_keymap_data,
#if 0
    .rows		= 2,
    .cols		= 1,
#else
    .rows		= 14,
    .cols		= 7,
#endif
};
#endif

#ifdef CONFIG_WAKEUP_ASSIST
static struct platform_device wakeup_assist_device = {
    .name   = "wakeup_assist",
};
#endif

#ifdef CONFIG_VIDEO_FIMG2D
static struct fimg2d_platdata fimg2d_data __initdata = {
    .hw_ver = 0x41,
    .parent_clkname = "mout_g2d0",
    .clkname = "sclk_fimg2d",
    .gate_clkname = "fimg2d",
    .clkrate = 267 * 1000000,	/* 266 Mhz */
};
#endif

#ifdef CONFIG_EXYNOS_C2C
struct exynos_c2c_platdata smdk4x12_c2c_pdata = {
    .setup_gpio	= NULL,
    .shdmem_addr	= C2C_SHAREDMEM_BASE,
    .shdmem_size	= C2C_MEMSIZE_64,
    .ap_sscm_addr	= NULL,
    .cp_sscm_addr	= NULL,
    .rx_width	= C2C_BUSWIDTH_16,
    .tx_width	= C2C_BUSWIDTH_16,
    .clk_opp100	= 400,
    .clk_opp50	= 266,
    .clk_opp25	= 0,
    .default_opp_mode	= C2C_OPP50,
    .get_c2c_state	= NULL,
    .c2c_sysreg	= S5P_VA_CMU + 0x12000,
};
#endif

#ifdef CONFIG_BUSFREQ_OPP
/* BUSFREQ to control memory/bus*/
static struct device_domain busfreq;
#endif

static struct platform_device exynos4_busfreq = {
    .id = -1,
    .name = "exynos-busfreq",
};

// SEMCO
/* The sdhci_s3c_sdio_card_detect function is used for detecting
   the WiFi/BT module when the menu for enabling the WiFi is
   selected.
   The semco_a31_detection function is called by ar6000's probe function.

   The call sequence is

   ar6000_pm_probe() -> plat_setup_power_for_onoff() -> detect_semco_wlan_for_onoff()
   -> setup_semco_wlan_power_onoff() -> semco_a31_detection()

   The mmc_semco_a31_sdio_remove function is used for removing the mmc driver
   when the menu for disabling the WiFi is selected.
   The semco_a31_removal function is called by ar6000's remove function.

   The call sequence is

   ar6000_pm_remove() -> plat_setup_power_for_onoff() -> detect_semco_wlan_for_onoff()
   -> setup_semco_wlan_power_onoff() -> semco_a31_removal()

   The setup_semco_wlan_power function is only used for sleep/wakeup. It controls only
   the power of A31 module only(Do not card detection/removal function)
*/


void semco_a31_detection(void)
{
    extern void sdhci_s3c_sdio_card_detect(struct platform_device *pdev);

    sdhci_s3c_sdio_card_detect(&s3c_device_hsmmc3);
}
EXPORT_SYMBOL(semco_a31_detection);

#if 0
extern void mmc_semco_a31_sdio_remove(void);
void semco_a31_removal(void)
{
    mmc_semco_a31_sdio_remove();
}
EXPORT_SYMBOL(semco_a31_removal);

#endif
static struct platform_device s3c_wlan_ar6000_pm_device = {
    .name           = "wlan_ar6000_pm_dev",
    .id             = 1,
    .num_resources  = 0,
    .resource       = NULL,
};

static struct platform_device bt_sysfs = {
    .name = "bt-sysfs",
    .id = -1,
};
// END SEMCO

struct platform_device s3c_device_gps = {
    .name   = "si_gps",
    .id             = -1,
};

#ifdef CONFIG_MAX485_CTL
struct platform_device s3c_device_max485_ctl = {
    .name   = "max485_ctl",
    .id             = -1,
};
#endif

#ifdef CONFIG_LEDS_CTL
struct platform_device s3c_device_leds_ctl = {
    .name   = "leds",
    .id             = -1,
};
#endif

#ifdef CONFIG_BUZZER_CTL
struct platform_device s3c_device_buzzer_ctl = {
    .name   = "buzzer_ctl",
    .id             = -1,
};
#endif

#ifdef CONFIG_ADC_CTL
struct platform_device s3c_device_adc_ctl = {
    .name			= "adc_ctl",
    .id				= -1,
};
#endif


static  struct  i2c_gpio_platform_data  i2c0_platdata = {
    .sda_pin                = EXYNOS4_GPD1(0),
    .scl_pin                = EXYNOS4_GPD1(1),
    .udelay                 = 1 ,
    .sda_is_open_drain      = 0,
    .scl_is_open_drain      = 0,
    .scl_is_output_only     = 0,
    //      .scl_is_output_only     = 1,
};

static struct platform_device s3c_device_i2c0_gpio = {
    .name                           = "i2c-gpio",
    .id                                     = 0,
    .dev.platform_data      = &i2c0_platdata,
};

#ifdef CONFIG_VIBRATOR
struct platform_device s5p_vib_dev = {
    .name	= "s5p-vib",
    .id	= -1,
};
#endif

/* add by cym 20140826 */
#ifdef CONFIG_EXYNOS_MEDIA_DEVICE
struct platform_device exynos_device_md0 = {
    .name = "exynos-mdev",
    .id = -1,
};
#endif
/* end add */

#if defined (CONFIG_S5P_SYSTEM_MMU) && defined(CONFIG_TC4_GB)

extern struct platform_device s5p_device_sysmmu;
#endif
static struct platform_device *smdk4412_devices[] __initdata = {
    &s3c_device_adc,
};

static struct platform_device *smdk4x12_devices[] __initdata = {
#ifdef CONFIG_ANDROID_PMEM
    &pmem_device,
    &pmem_gpu1_device,
#endif
    /* Samsung Power Domain */
    &exynos4_device_pd[PD_MFC],
    &exynos4_device_pd[PD_G3D],
    &exynos4_device_pd[PD_LCD0],
    &exynos4_device_pd[PD_CAM],
    &exynos4_device_pd[PD_TV],
    &exynos4_device_pd[PD_GPS],
    &exynos4_device_pd[PD_GPS_ALIVE],
#ifdef CONFIG_VIDEO_EXYNOS_FIMC_IS
    &exynos4_device_pd[PD_ISP],
#endif
#ifdef CONFIG_FB_MIPI_DSIM
    &s5p_device_mipi_dsim,
#endif
    /* mainline fimd */
#ifdef CONFIG_FB_S3C
    &s5p_device_fimd0,
#if defined(CONFIG_LCD_AMS369FG06) || defined(CONFIG_LCD_LMS501KF03)
    &s3c_device_spi_gpio,
#elif defined(CONFIG_LCD_WA101S)
    &smdk4x12_lcd_wa101s,
#elif defined(CONFIG_LCD_LTE480WV)
    &smdk4x12_lcd_lte480wv,
#elif defined(CONFIG_LCD_MIPI_S6E63M0)
    &smdk4x12_mipi_lcd,
#endif
#endif
    /* legacy fimd */
#ifdef CONFIG_FB_S5P
    &s3c_device_fb,
#ifdef CONFIG_FB_S5P_LMS501KF03
    &s3c_device_spi_gpio,
#endif
#endif
    &s3c_device_wdt,
    &s3c_device_rtc,
    //&s3c_device_i2c0,
    &s3c_device_i2c0_gpio, //added yqf
    &s3c_device_i2c1,
    //&s3c_device_i2c2,
    &s3c_device_i2c3,
    &s3c_device_i2c4,
    &s3c_device_i2c5,
#ifndef CONFIG_CAN_MCP251X
    &s3c_device_i2c6,//For S5K4EC
#endif
    &s3c_device_i2c7,

    //#ifdef CONFIG_PWM_CTL
    //	&s3c_device_timer[0],
    //#endif

#if !defined(CONFIG_REGULATOR_MAX8997)	
    &s5p_device_pmic,
#endif	

    &tc4_regulator_consumer,

    //robin, no need&s3c_device_adc,//wenpin.cui

#ifdef CONFIG_USB_EHCI_S5P
    &s5p_device_ehci,
#endif
#ifdef CONFIG_USB_OHCI_S5P
    &s5p_device_ohci,
#endif
#ifdef CONFIG_USB_GADGET
    &s3c_device_usbgadget,
#endif
#ifdef CONFIG_USB_ANDROID_RNDIS
    &s3c_device_rndis,
#endif
#ifdef CONFIG_USB_ANDROID
    &s3c_device_android_usb,
    &s3c_device_usb_mass_storage,
#endif
    // SEMCO
    &s3c_wlan_ar6000_pm_device,
    &bt_sysfs,
    // END SEMCO

#ifdef CONFIG_S5P_DEV_MSHC
    &s3c_device_mshci,//lisw sd mshci should be probe before hsmmc
#endif
#ifdef CONFIG_S3C_DEV_HSMMC
    //	&s3c_device_hsmmc0,
#endif
#ifdef CONFIG_S3C_DEV_HSMMC1
    //	&s3c_device_hsmmc1,
#endif
#ifdef CONFIG_S3C_DEV_HSMMC2
    &s3c_device_hsmmc2,
#endif
#ifdef CONFIG_S3C_DEV_HSMMC3
    &s3c_device_hsmmc3,
#endif
#ifdef CONFIG_EXYNOS4_DEV_DWMCI
    &exynos_device_dwmci,
#endif
#ifdef CONFIG_SND_SAMSUNG_AC97
    &exynos_device_ac97,
#endif
#ifdef CONFIG_SND_SAMSUNG_I2S
    &exynos_device_i2s0,
#endif
#ifdef CONFIG_SND_SAMSUNG_PCM
    &exynos_device_pcm0,
#endif
#ifdef CONFIG_SND_SAMSUNG_SPDIF
    &exynos_device_spdif,
#endif
#if defined(CONFIG_SND_SAMSUNG_RP) || defined(CONFIG_SND_SAMSUNG_ALP)
    &exynos_device_srp,
#endif
#ifdef CONFIG_VIDEO_EXYNOS_FIMC_IS
    &exynos4_device_fimc_is,
#endif
#ifdef CONFIG_VIDEO_TVOUT
    &s5p_device_tvout,
    &s5p_device_cec,
    &s5p_device_hpd,
#endif
#ifdef CONFIG_VIDEO_EXYNOS_TV
    &s5p_device_i2c_hdmiphy,
    &s5p_device_hdmi,
    &s5p_device_sdo,
    &s5p_device_mixer,
    &s5p_device_cec,
#endif
#if defined(CONFIG_VIDEO_FIMC)
    &s3c_device_fimc0,
    &s3c_device_fimc1,
    &s3c_device_fimc2,
    &s3c_device_fimc3,
    /* CONFIG_VIDEO_SAMSUNG_S5P_FIMC is the feature for mainline */
#elif defined(CONFIG_VIDEO_SAMSUNG_S5P_FIMC)
    &s5p_device_fimc0,
    &s5p_device_fimc1,
    &s5p_device_fimc2,
    &s5p_device_fimc3,
#endif
#if defined(CONFIG_VIDEO_FIMC_MIPI)
    &s3c_device_csis0,
    &s3c_device_csis1,
#elif defined(CONFIG_VIDEO_S5P_MIPI_CSIS)
    &s5p_device_mipi_csis0,
    &s5p_device_mipi_csis1,
#endif
#ifdef CONFIG_VIDEO_S5P_MIPI_CSIS
    &mipi_csi_fixed_voltage,
#endif

#if defined(CONFIG_VIDEO_MFC5X) || defined(CONFIG_VIDEO_SAMSUNG_S5P_MFC)
    &s5p_device_mfc,
#endif
#ifdef CONFIG_S5P_SYSTEM_MMU
#ifdef CONFIG_TC4_GB
    &s5p_device_sysmmu,
#else
    &SYSMMU_PLATDEV(g2d_acp),
    &SYSMMU_PLATDEV(fimc0),
    &SYSMMU_PLATDEV(fimc1),
    &SYSMMU_PLATDEV(fimc2),
    &SYSMMU_PLATDEV(fimc3),
    &SYSMMU_PLATDEV(jpeg),
    &SYSMMU_PLATDEV(mfc_l),
    &SYSMMU_PLATDEV(mfc_r),
    &SYSMMU_PLATDEV(tv),
#ifdef CONFIG_VIDEO_EXYNOS_FIMC_IS
    &SYSMMU_PLATDEV(is_isp),
    &SYSMMU_PLATDEV(is_drc),
    &SYSMMU_PLATDEV(is_fd),
    &SYSMMU_PLATDEV(is_cpu),
#endif
#endif //CONIG_TC4_GB
#endif /* CONFIG_S5P_SYSTEM_MMU */

#ifdef CONFIG_ION_EXYNOS
    &exynos_device_ion,
#endif
#ifdef CONFIG_VIDEO_EXYNOS_FIMC_LITE
    &exynos_device_flite0,
    &exynos_device_flite1,
#endif
#ifdef CONFIG_VIDEO_FIMG2D
    &s5p_device_fimg2d,
#endif
#ifdef CONFIG_EXYNOS_MEDIA_DEVICE
    &exynos_device_md0,
#endif
#if	defined(CONFIG_VIDEO_JPEG_V2X) || defined(CONFIG_VIDEO_JPEG)

    &s5p_device_jpeg,
#endif
    &samsung_asoc_dma,
    &samsung_asoc_idma,
#ifdef CONFIG_BATTERY_SAMSUNG
    &samsung_device_battery,
#endif
    &samsung_device_keypad,
#ifdef CONFIG_WAKEUP_ASSIST
    &wakeup_assist_device,
#endif
#ifdef CONFIG_EXYNOS_C2C
    &exynos_device_c2c,
#endif

    /* add by cym 20130619 */
#ifdef CONFIG_KEYBOARD_GPIO
    &gpio_button_device,
#endif
    /* end add */

    //&smdk4x12_input_device, yulu
#ifdef CONFIG_S3C64XX_DEV_SPI
#if 0	//remove by cym 20130529
    &exynos_device_spi0,
#ifndef CONFIG_FB_S5P_LMS501KF03
    &exynos_device_spi1,
#endif
#endif
    &exynos_device_spi2,
#endif
#ifdef CONFIG_EXYNOS_SETUP_THERMAL
    &exynos_device_tmu,
#endif
#ifdef CONFIG_S5P_DEV_ACE
    &s5p_device_ace,
#endif
    &exynos4_busfreq,
#ifdef CONFIG_SWITCH_GPIO
    &headset_switch_device,
#endif
    &s3c_device_gps,
    //&smm6260_modem,

#ifdef CONFIG_MAX485_CTL
    &s3c_device_max485_ctl ,
#endif

#ifdef CONFIG_LEDS_CTL
    &s3c_device_leds_ctl,
#endif

#ifdef CONFIG_BUZZER_CTL
    &s3c_device_buzzer_ctl,
#endif

#ifdef CONFIG_ADC_CTL
    &s3c_device_adc_ctl,
#endif

#ifdef CONFIG_SMM6260_MODEM
    &smm6260_modem,
#endif	
#ifdef CONFIG_VIBRATOR
    &s5p_vib_dev,
#endif
};
#ifdef CONFIG_EXYNOS_SETUP_THERMAL
/* below temperature base on the celcius degree */
struct tmu_data exynos_tmu_data __initdata = {
    .ts = {
        .stop_throttle  = 82,
        .start_throttle = 85,
        .stop_warning  = 95,
        .start_warning = 103,
        .start_tripping = 110, /* temp to do tripping */
    },
    .efuse_value = 55,
    .slope = 0x10008802,
    .mode = 0,
};
#endif


#if defined(CONFIG_VIDEO_TVOUT)
static struct s5p_platform_hpd hdmi_hpd_data __initdata = {

};
static struct s5p_platform_cec hdmi_cec_data __initdata = {

};
#endif
#ifdef CONFIG_VIDEO_EXYNOS_HDMI_CEC
static struct s5p_platform_cec hdmi_cec_data __initdata = {

};
#endif


#ifdef CONFIG_VIDEO_EXYNOS_FIMC_LITE
static void __set_flite_camera_config(struct exynos_platform_flite *data,
                                      u32 active_index, u32 max_cam)
{
    data->active_cam_index = active_index;
    data->num_clients = max_cam;
}

static void __init smdk4x12_set_camera_flite_platdata(void)
{
    int flite0_cam_index = 0;
    int flite1_cam_index = 0;

    __set_flite_camera_config(&exynos_flite0_default_data, 0, flite0_cam_index);
    __set_flite_camera_config(&exynos_flite1_default_data, 0, flite1_cam_index);
}
#endif

#if defined(CONFIG_S5P_MEM_CMA)
static void __init exynos4_cma_region_reserve(
        struct cma_region *regions_normal,
        struct cma_region *regions_secure)
{
    struct cma_region *reg;
    phys_addr_t paddr_last = 0xFFFFFFFF;

    for (reg = regions_normal; reg->size != 0; reg++) {
        phys_addr_t paddr;

        if (!IS_ALIGNED(reg->size, PAGE_SIZE)) {
            pr_err("S5P/CMA: size of '%s' is NOT page-aligned\n",
                   reg->name);
            reg->size = PAGE_ALIGN(reg->size);
        }


        if (reg->reserved) {
            pr_err("S5P/CMA: '%s' alread reserved\n", reg->name);
            continue;
        }

        if (reg->alignment) {
            if ((reg->alignment & ~PAGE_MASK) ||
                    (reg->alignment & ~reg->alignment)) {
                pr_err("S5P/CMA: Failed to reserve '%s': "
                       "incorrect alignment 0x%08x.\n",
                       reg->name, reg->alignment);
                continue;
            }
        } else {
            reg->alignment = PAGE_SIZE;
        }

        if (reg->start) {
            if (!memblock_is_region_reserved(reg->start, reg->size)
                    && (memblock_reserve(reg->start, reg->size) == 0))
                reg->reserved = 1;
            else
                pr_err("S5P/CMA: Failed to reserve '%s'\n",
                       reg->name);

            continue;
        }

        paddr = memblock_find_in_range(0, MEMBLOCK_ALLOC_ACCESSIBLE,
                                       reg->size, reg->alignment);
        if (paddr != MEMBLOCK_ERROR) {
            if (memblock_reserve(paddr, reg->size)) {
                pr_err("S5P/CMA: Failed to reserve '%s'\n",
                       reg->name);
                continue;
            }

            reg->start = paddr;
            reg->reserved = 1;
        } else {
            pr_err("S5P/CMA: No free space in memory for '%s'\n",
                   reg->name);
        }

        if (cma_early_region_register(reg)) {
            pr_err("S5P/CMA: Failed to register '%s'\n",
                   reg->name);
            memblock_free(reg->start, reg->size);
        } else {
            paddr_last = min(paddr, paddr_last);
        }
    }

    if (regions_secure && regions_secure->size) {
        size_t size_secure = 0;
        size_t align_secure, size_region2, aug_size, order_region2;

        for (reg = regions_secure; reg->size != 0; reg++)
            size_secure += reg->size;

        reg--;

        /* Entire secure regions will be merged into 2
                 * consecutive regions. */
        align_secure = 1 <<
                            (get_order((size_secure + 1) / 2) + PAGE_SHIFT);
        /* Calculation of a subregion size */
        size_region2 = size_secure - align_secure;
        order_region2 = get_order(size_region2) + PAGE_SHIFT;
        if (order_region2 < 20)
            order_region2 = 20; /* 1MB */
        order_region2 -= 3; /* divide by 8 */
        size_region2 = ALIGN(size_region2, 1 << order_region2);

        aug_size = align_secure + size_region2 - size_secure;
        if (aug_size > 0)
            reg->size += aug_size;

        size_secure = ALIGN(size_secure, align_secure);

        if (paddr_last >= memblock.current_limit) {
            paddr_last = memblock_find_in_range(0,
                                                MEMBLOCK_ALLOC_ACCESSIBLE,
                                                size_secure, reg->alignment);
        } else {
            paddr_last -= size_secure;
            paddr_last = round_down(paddr_last, align_secure);
        }

        if (paddr_last) {
            while (memblock_reserve(paddr_last, size_secure))
                paddr_last -= align_secure;

            do {
                reg->start = paddr_last;
                reg->reserved = 1;
                paddr_last += reg->size;

                if (cma_early_region_register(reg)) {
                    memblock_free(reg->start, reg->size);
                    pr_err("S5P/CMA: "
                           "Failed to register secure region "
                           "'%s'\n", reg->name);
                } else {
                    size_secure -= reg->size;
                }
            } while (reg-- != regions_secure);

            if (size_secure > 0)
                memblock_free(paddr_last, size_secure);
        } else {
            pr_err("S5P/CMA: Failed to reserve secure regions\n");
        }
    }
}

static void __init exynos4_reserve_mem(void)
{
    static struct cma_region regions[] = {
#ifdef CONFIG_ANDROID_PMEM_MEMSIZE_PMEM
    {
        .name = "pmem",
                .size = CONFIG_ANDROID_PMEM_MEMSIZE_PMEM * SZ_1K,
                .start = 0,
    },
#endif
#ifdef CONFIG_ANDROID_PMEM_MEMSIZE_PMEM_GPU1
    {
        .name = "pmem_gpu1",
                .size = CONFIG_ANDROID_PMEM_MEMSIZE_PMEM_GPU1 * SZ_1K,
                .start = 0,
    },
#endif
#ifndef CONFIG_VIDEOBUF2_ION
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_TV
    {
        .name = "tv",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_TV * SZ_1K,
                .start = 0
    },
#endif
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_JPEG
    {
        .name = "jpeg",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_JPEG * SZ_1K,
                .start = 0
    },
#endif
#ifdef CONFIG_AUDIO_SAMSUNG_MEMSIZE_SRP
    {
        .name = "srp",
                .size = CONFIG_AUDIO_SAMSUNG_MEMSIZE_SRP * SZ_1K,
                .start = 0,
    },
#endif
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMG2D
    {
        .name = "fimg2d",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMG2D * SZ_1K,
                .start = 0
    },
#endif
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMD
    {
        .name = "fimd",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMD * SZ_1K,
                .start = 0
    },
#endif
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMC0
    {
        .name = "fimc0",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMC0 * SZ_1K,
                .start = 0
    },
#endif
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMC2
    {
        .name = "fimc2",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMC2 * SZ_1K,
                .start = 0
    },
#endif
#if !defined(CONFIG_EXYNOS4_CONTENT_PATH_PROTECTION) && \
    defined(CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMC3)
    {
        .name = "fimc3",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMC3 * SZ_1K,
    },
#endif
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMC1
    {
        .name = "fimc1",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMC1 * SZ_1K,
                .start = 0
    },
#endif
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_MFC1
    {
#ifdef CONFIG_EXYNOS4_CONTENT_PATH_PROTECTION
        .name = "mfc-normal",
        #else
        .name = "mfc1",
        #endif
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_MFC1 * SZ_1K,
        { .alignment = 1 << 17 },
        },
#endif
#if !defined(CONFIG_EXYNOS4_CONTENT_PATH_PROTECTION) && \
    defined(CONFIG_VIDEO_SAMSUNG_MEMSIZE_MFC0)
    {
        .name = "mfc0",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_MFC0 * SZ_1K,
        { .alignment = 1 << 17 },
        },
#endif
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_MFC
    {
        .name = "mfc",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_MFC * SZ_1K,
        { .alignment = 1 << 17 },
        },
#endif
#ifdef CONFIG_VIDEO_EXYNOS_FIMC_IS
    {
        .name = "fimc_is",
                .size = CONFIG_VIDEO_EXYNOS_MEMSIZE_FIMC_IS * SZ_1K,
        {
            .alignment = 1 << 26,
        },
        .start = 0
    },
#ifdef CONFIG_VIDEO_EXYNOS_FIMC_IS_BAYER
    {
        .name = "fimc_is_isp",
                .size = CONFIG_VIDEO_EXYNOS_MEMSIZE_FIMC_IS_ISP * SZ_1K,
                .start = 0
    },
#endif
#endif
#if !defined(CONFIG_EXYNOS4_CONTENT_PATH_PROTECTION) && \
    defined(CONFIG_VIDEO_SAMSUNG_S5P_MFC)
    {
        .name		= "b2",
                .size		= 32 << 20,
        { .alignment	= 128 << 10 },
        },
    {
        .name		= "b1",
                .size		= 32 << 20,
        { .alignment	= 128 << 10 },
        },
    {
        .name		= "fw",
                .size		= 1 << 20,
        { .alignment	= 128 << 10 },
        },
#endif
#else /* !CONFIG_VIDEOBUF2_ION */
#ifdef CONFIG_FB_S5P
#error CONFIG_FB_S5P is defined. Select CONFIG_FB_S3C, instead
#endif
    {
        .name	= "ion",
                .size	= CONFIG_ION_EXYNOS_CONTIGHEAP_SIZE * SZ_1K,
    },
#endif /* !CONFIG_VIDEOBUF2_ION */
    {
        .size = 0
    },
};
#ifdef CONFIG_EXYNOS4_CONTENT_PATH_PROTECTION
    static struct cma_region regions_secure[] = {
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMD_VIDEO
    {
        .name = "video",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMD_VIDEO * SZ_1K,
    },
#endif
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMC3
    {
        .name = "fimc3",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_FIMC3 * SZ_1K,
    },
#endif
#ifdef CONFIG_VIDEO_SAMSUNG_MEMSIZE_MFC0
    {
        .name = "mfc-secure",
                .size = CONFIG_VIDEO_SAMSUNG_MEMSIZE_MFC0 * SZ_1K,
    },
#endif
    {
        .name = "sectbl",
                .size = SZ_1M,
        {
            .alignment = SZ_64M,
        },
    },
    {
        .size = 0
    },
};
#else /* !CONFIG_EXYNOS4_CONTENT_PATH_PROTECTION */
    struct cma_region *regions_secure = NULL;
#endif
    static const char map[] __initconst =
        #ifdef CONFIG_EXYNOS_C2C
            "samsung-c2c=c2c_shdmem;"
        #endif
            "android_pmem.0=pmem;android_pmem.1=pmem_gpu1;"
            "s3cfb.0/fimd=fimd;exynos4-fb.0/fimd=fimd;"
        #ifdef CONFIG_EXYNOS4_CONTENT_PATH_PROTECTION
            "s3cfb.0/video=video;exynos4-fb.0/video=video;"
        #endif
            "s3c-fimc.0=fimc0;s3c-fimc.1=fimc1;s3c-fimc.2=fimc2;s3c-fimc.3=fimc3;"
            "exynos4210-fimc.0=fimc0;exynos4210-fimc.1=fimc1;exynos4210-fimc.2=fimc2;exynos4210-fimc.3=fimc3;"
        #ifdef CONFIG_VIDEO_MFC5X
            "s3c-mfc/A=mfc0,mfc-secure;"
            "s3c-mfc/B=mfc1,mfc-normal;"
            "s3c-mfc/AB=mfc;"
        #endif
        #ifdef CONFIG_VIDEO_SAMSUNG_S5P_MFC
            "s5p-mfc/f=fw;"
            "s5p-mfc/a=b1;"
            "s5p-mfc/b=b2;"
        #endif
            "samsung-rp=srp;"
            "s5p-jpeg=jpeg;"
            "exynos4-fimc-is/f=fimc_is;"
        #ifdef CONFIG_VIDEO_EXYNOS_FIMC_IS_BAYER
            "exynos4-fimc-is/i=fimc_is_isp;"
        #endif
            "s5p-mixer=tv;"
            "s5p-fimg2d=fimg2d;"
            "ion-exynos=ion,fimd,fimc0,fimc1,fimc2,fimc3,fw,b1,b2;"
        #ifdef CONFIG_EXYNOS4_CONTENT_PATH_PROTECTION
            "s5p-smem/video=video;"
            "s5p-smem/sectbl=sectbl;"
        #endif
            "s5p-smem/mfc=mfc0,mfc-secure;"
            "s5p-smem/fimc=fimc3;"
            "s5p-smem/mfc-shm=mfc1,mfc-normal;";

    cma_set_defaults(NULL, map);

    exynos4_cma_region_reserve(regions, regions_secure);
}
#endif

/* LCD Backlight data */
static struct samsung_bl_gpio_info smdk4x12_bl_gpio_info = {
    .no = EXYNOS4_GPD0(1),
    .func = S3C_GPIO_SFN(2),
};

static struct platform_pwm_backlight_data smdk4x12_bl_data = {
    .pwm_id = 1,
#ifdef CONFIG_FB_S5P_LMS501KF03
    .pwm_period_ns  = 1000,
#endif
};

static void __init smdk4x12_map_io(void)
{
    clk_xusbxti.rate = 24000000;
    s5p_init_io(NULL, 0, S5P_VA_CHIPID);
    s3c24xx_init_clocks(24000000);
    s3c24xx_init_uarts(smdk4x12_uartcfgs, ARRAY_SIZE(smdk4x12_uartcfgs));

#if defined(CONFIG_S5P_MEM_CMA)
    exynos4_reserve_mem();
#endif
}

#ifndef CONFIG_TC4_GB
static void __init exynos_sysmmu_init(void)
{
    ASSIGN_SYSMMU_POWERDOMAIN(fimc0, &exynos4_device_pd[PD_CAM].dev);
    ASSIGN_SYSMMU_POWERDOMAIN(fimc1, &exynos4_device_pd[PD_CAM].dev);
    ASSIGN_SYSMMU_POWERDOMAIN(fimc2, &exynos4_device_pd[PD_CAM].dev);
    ASSIGN_SYSMMU_POWERDOMAIN(fimc3, &exynos4_device_pd[PD_CAM].dev);
    ASSIGN_SYSMMU_POWERDOMAIN(jpeg, &exynos4_device_pd[PD_CAM].dev);
    ASSIGN_SYSMMU_POWERDOMAIN(mfc_l, &exynos4_device_pd[PD_MFC].dev);
    ASSIGN_SYSMMU_POWERDOMAIN(mfc_r, &exynos4_device_pd[PD_MFC].dev);
    ASSIGN_SYSMMU_POWERDOMAIN(tv, &exynos4_device_pd[PD_TV].dev);
#ifdef CONFIG_VIDEO_FIMG2D
    sysmmu_set_owner(&SYSMMU_PLATDEV(g2d_acp).dev, &s5p_device_fimg2d.dev);
#endif
#if defined(CONFIG_VIDEO_SAMSUNG_S5P_MFC) || defined(CONFIG_VIDEO_MFC5X)
    sysmmu_set_owner(&SYSMMU_PLATDEV(mfc_l).dev, &s5p_device_mfc.dev);
    sysmmu_set_owner(&SYSMMU_PLATDEV(mfc_r).dev, &s5p_device_mfc.dev);
#endif
#if defined(CONFIG_VIDEO_FIMC)
    sysmmu_set_owner(&SYSMMU_PLATDEV(fimc0).dev, &s3c_device_fimc0.dev);
    sysmmu_set_owner(&SYSMMU_PLATDEV(fimc1).dev, &s3c_device_fimc1.dev);
    sysmmu_set_owner(&SYSMMU_PLATDEV(fimc2).dev, &s3c_device_fimc2.dev);
    sysmmu_set_owner(&SYSMMU_PLATDEV(fimc3).dev, &s3c_device_fimc3.dev);
#elif defined(CONFIG_VIDEO_SAMSUNG_S5P_FIMC)
    sysmmu_set_owner(&SYSMMU_PLATDEV(fimc0).dev, &s5p_device_fimc0.dev);
    sysmmu_set_owner(&SYSMMU_PLATDEV(fimc1).dev, &s5p_device_fimc1.dev);
    sysmmu_set_owner(&SYSMMU_PLATDEV(fimc2).dev, &s5p_device_fimc2.dev);
    sysmmu_set_owner(&SYSMMU_PLATDEV(fimc3).dev, &s5p_device_fimc3.dev);
#endif
#ifdef CONFIG_VIDEO_EXYNOS_TV
    sysmmu_set_owner(&SYSMMU_PLATDEV(tv).dev, &s5p_device_mixer.dev);
#endif
#ifdef CONFIG_VIDEO_TVOUT
    sysmmu_set_owner(&SYSMMU_PLATDEV(tv).dev, &s5p_device_tvout.dev);
#endif
#ifdef CONFIG_VIDEO_JPEG_V2X
    sysmmu_set_owner(&SYSMMU_PLATDEV(jpeg).dev, &s5p_device_jpeg.dev);
#endif
#ifdef CONFIG_VIDEO_EXYNOS_FIMC_IS
    ASSIGN_SYSMMU_POWERDOMAIN(is_isp, &exynos4_device_pd[PD_ISP].dev);
    ASSIGN_SYSMMU_POWERDOMAIN(is_drc, &exynos4_device_pd[PD_ISP].dev);
    ASSIGN_SYSMMU_POWERDOMAIN(is_fd, &exynos4_device_pd[PD_ISP].dev);
    ASSIGN_SYSMMU_POWERDOMAIN(is_cpu, &exynos4_device_pd[PD_ISP].dev);

    sysmmu_set_owner(&SYSMMU_PLATDEV(is_isp).dev,
                     &exynos4_device_fimc_is.dev);
    sysmmu_set_owner(&SYSMMU_PLATDEV(is_drc).dev,
                     &exynos4_device_fimc_is.dev);
    sysmmu_set_owner(&SYSMMU_PLATDEV(is_fd).dev,
                     &exynos4_device_fimc_is.dev);
    sysmmu_set_owner(&SYSMMU_PLATDEV(is_cpu).dev,
                     &exynos4_device_fimc_is.dev);
#endif
}

#endif
// zsb: wait for i2c5 bus idle before software reset
extern int wait_for_i2c_idle(struct platform_device *pdev);
static void smdk4x12_power_off(void)
{
    //int ret = 0;

    /* modify by cym 20130419 */
#if 0
    //shengliang
    gpio_set_value(EXYNOS4_GPC0(0), 0);// MD_PWON low
#else
    gpio_set_value(EXYNOS4_GPX3(3), 0);// MD_PWON low
#endif
    /* end modify */
#if 0
    msleep(10);
    gpio_set_value(EXYNOS4_GPC0(2), 0);// MD_RSTN low
    gpio_set_value(EXYNOS4_GPL2(1), 0);// MD_RESETBB low
    msleep(10);
#endif
    /* PS_HOLD --> Output Low */
    printk(KERN_EMERG "%s : setting GPIO_PDA_PS_HOLD low.\n", __func__);
    /* PS_HOLD output High --> Low  PS_HOLD_CONTROL, R/W, 0xE010_E81C */
    writel(0x5200, S5P_PS_HOLD_CONTROL);

    while(1);

    printk(KERN_EMERG "%s : should not reach here!\n", __func__);
}

#if 1
extern void (*s3c_config_sleep_gpio_table)(void);
#include <plat/gpio-core.h>

int s3c_gpio_slp_cfgpin(unsigned int pin, unsigned int config)
{
    struct s3c_gpio_chip *chip = s3c_gpiolib_getchip(pin);
    void __iomem *reg;
    unsigned long flags;
    int offset;
    u32 con;
    int shift;

    if (!chip)
        return -EINVAL;

    if ((pin >= EXYNOS4_GPX0(0)) && (pin <= EXYNOS4_GPX3(7)))
        return -EINVAL;

    if (config > S3C_GPIO_SLP_PREV)
        return -EINVAL;

    reg = chip->base + 0x10;

    offset = pin - chip->chip.base;
    shift = offset * 2;

    local_irq_save(flags);

    con = __raw_readl(reg);
    con &= ~(3 << shift);
    con |= config << shift;
    __raw_writel(con, reg);

    local_irq_restore(flags);
    return 0;
}

int s3c_gpio_slp_setpull_updown(unsigned int pin, unsigned int config)
{
    struct s3c_gpio_chip *chip = s3c_gpiolib_getchip(pin);
    void __iomem *reg;
    unsigned long flags;
    int offset;
    u32 con;
    int shift;

    if (!chip)
        return -EINVAL;

    if ((pin >= EXYNOS4_GPX0(0)) && (pin <= EXYNOS4_GPX3(7)))
        return -EINVAL;

    if (config > S3C_GPIO_PULL_UP)
        return -EINVAL;

    reg = chip->base + 0x14;

    offset = pin - chip->chip.base;
    shift = offset * 2;

    local_irq_save(flags);

    con = __raw_readl(reg);
    con &= ~(3 << shift);
    con |= config << shift;
    __raw_writel(con, reg);

    local_irq_restore(flags);

    return 0;
}

static void config_sleep_gpio_table(int array_size, unsigned int (*gpio_table)[3])
{
    u32 i, gpio;

    for (i = 0; i < array_size; i++) {
        gpio = gpio_table[i][0];
        s3c_gpio_slp_cfgpin(gpio, gpio_table[i][1]);
        s3c_gpio_slp_setpull_updown(gpio, gpio_table[i][2]);
    }
}

/*sleep gpio table for TC4*/
static unsigned int tc4_sleep_gpio_table[][3] = {
    #if 1 //zhangdong reduce sleep current
    { EXYNOS4_GPA0(0),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //BT_TXD
    { EXYNOS4_GPA0(1),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //BT_RXD
    { EXYNOS4_GPA0(2),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //BT_RTS
    { EXYNOS4_GPA0(3),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //BT_CTS

    { EXYNOS4_GPA0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //AC100_TXD,SMM6260
    { EXYNOS4_GPA0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //AC100_RXD
    { EXYNOS4_GPA0(6),	S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //AC100_RTS
    { EXYNOS4_GPA0(7),	S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //AC100_CTS


    { EXYNOS4_GPA1(0),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //DEBUG
    { EXYNOS4_GPA1(1),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //DEBUG
    { EXYNOS4_GPA1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},  //I2C_SDA3
    { EXYNOS4_GPA1(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C_SCL3
    #ifdef CONFIG_TC4_EVT
    { EXYNOS4_GPA1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //TP1_RST
    { EXYNOS4_GPA1(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //TestPoint
    #endif
    #ifdef CONFIG_TC4_DVT
    { EXYNOS4_GPA1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //GPS_TXD
    { EXYNOS4_GPA1(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //GPS_RXD
    #endif

    { EXYNOS4_GPB(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C_SDA4
    { EXYNOS4_GPB(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C_SCL4
    { EXYNOS4_GPB(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C_SDA5
    { EXYNOS4_GPB(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C_SCL5
    { EXYNOS4_GPB(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //GPS_RST
    { EXYNOS4_GPB(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //PMIC_SET1
    { EXYNOS4_GPB(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //PMIC_SET2
    { EXYNOS4_GPB(7),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //PMIC_SET3


    #ifdef CONFIG_SMM6260_MODEM
    //{ EXYNOS4_GPC0(0),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //MD_PWON
    { EXYNOS4_GPX3(3),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //MD_PWON
    #else
    //{ EXYNOS4_GPC0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //MD_PWON
    { EXYNOS4_GPX3(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //MD_PWON
    #endif
    { EXYNOS4_GPC0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //VLED_ON
    { EXYNOS4_GPC0(2),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //MD_RSTN
    #ifdef CONFIG_SMM6260_MODEM
    //{ EXYNOS4_GPC0(3),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //AP_SLEEP
    { EXYNOS4_GPC0(4),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //AP_WAKEUP_MD
    //{ EXYNOS4_GPX2(5),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //MD_WAKEUP_AP
    { EXYNOS4_GPX3(0),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //MD_WAKEUP_AP
    #else
    { EXYNOS4_GPC0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //AP_SLEEP
    { EXYNOS4_GPC0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //AP_WAKEUP_MD
    #endif

    { EXYNOS4_GPC1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //UART_SW  config as hp  out1??
    { EXYNOS4_GPC1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //LED_EN18
    { EXYNOS4_GPC1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //VLED_EN
    { EXYNOS4_GPC1(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C6_SDA
    { EXYNOS4_GPC1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C6_SCL

    { EXYNOS4_GPD0(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE}, // MOTOR-PWM
    { EXYNOS4_GPD0(1),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE}, //XPWMOUT1
    { EXYNOS4_GPD0(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},  //I2C7_SDA
    { EXYNOS4_GPD0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C7_SCL

    { EXYNOS4_GPD1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C0_SDA
    { EXYNOS4_GPD1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C0_SCL
    { EXYNOS4_GPD1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C1_SDA
    { EXYNOS4_GPD1(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C1_SCL

    { EXYNOS4_GPF0(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_HSYNC
    { EXYNOS4_GPF0(1),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_VSYNC
    { EXYNOS4_GPF0(2),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_VDEN
    { EXYNOS4_GPF0(3),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_VCLK
    { EXYNOS4_GPF0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CAM2M_RST
    { EXYNOS4_GPF0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CAM2M_PWDN
    { EXYNOS4_GPF0(6),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_D2
    { EXYNOS4_GPF0(7),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_D3

    { EXYNOS4_GPF1(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_D4
    { EXYNOS4_GPF1(1),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_D5
    { EXYNOS4_GPF1(2),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D6
    { EXYNOS4_GPF1(3),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D7
    { EXYNOS4_GPF1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CAM5M_RST
    { EXYNOS4_GPF1(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CAM5M_PWDN
    { EXYNOS4_GPF1(6),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D10
    { EXYNOS4_GPF1(7),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D11

    { EXYNOS4_GPF2(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D12
    { EXYNOS4_GPF2(1),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D13
    { EXYNOS4_GPF2(2),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D14
    { EXYNOS4_GPF2(3),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D15
    { EXYNOS4_GPF2(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPF2(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPF2(6),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D18
    { EXYNOS4_GPF2(7),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D19

    { EXYNOS4_GPF3(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D20
    { EXYNOS4_GPF3(1),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D21
    { EXYNOS4_GPF3(2),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D22
    { EXYNOS4_GPF3(3),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D23
    { EXYNOS4_GPF3(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPF3(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//MD_G15

    { EXYNOS4212_GPJ0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CAM_CLK
    { EXYNOS4212_GPJ0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CAM_VSYNC
    { EXYNOS4212_GPJ0(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CAM_HREF
    { EXYNOS4212_GPJ0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA0
    { EXYNOS4212_GPJ0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA1
    { EXYNOS4212_GPJ0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA2
    { EXYNOS4212_GPJ0(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA3
    { EXYNOS4212_GPJ0(7),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA4

    { EXYNOS4212_GPJ1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA5
    { EXYNOS4212_GPJ1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA6
    { EXYNOS4212_GPJ1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA7
    { EXYNOS4212_GPJ1(3),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//CAM_CLK_OUT
    { EXYNOS4212_GPJ1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC

    { EXYNOS4_GPK0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_CLK
    { EXYNOS4_GPK0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_CMD
    { EXYNOS4_GPK0(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_CDn
    { EXYNOS4_GPK0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA0
    { EXYNOS4_GPK0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA1
    { EXYNOS4_GPK0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA2
    { EXYNOS4_GPK0(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA3
    #ifdef CONFIG_TC4_EVT
    { EXYNOS4_GPK1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPK1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    #endif
    #ifdef CONFIG_TC4_DVT
    { EXYNOS4_GPK1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//ANX7805_PD
    { EXYNOS4_GPK1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//VDD50_EN
    #endif

    { EXYNOS4_GPK1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPK1(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA4
    { EXYNOS4_GPK1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA5
    { EXYNOS4_GPK1(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA6
    { EXYNOS4_GPK1(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA7

    { EXYNOS4_GPK2(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//TF_CLK
    { EXYNOS4_GPK2(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//TF_CMD
    { EXYNOS4_GPK2(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//ANX7805_RSTN
    { EXYNOS4_GPK2(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//TF_DATA0
    { EXYNOS4_GPK2(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//TF_DATA1
    { EXYNOS4_GPK2(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//TF_DATA2
    { EXYNOS4_GPK2(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//TF_DATA3

    // dg change  for debug sdio wifi
    #ifdef CONFIG_MTK_COMBO_MT66XX
    { EXYNOS4_GPK3(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//WIFI_CLK
    { EXYNOS4_GPK3(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//WIFI_CMD
    { EXYNOS4_GPK3(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//HUB_CONNECT
    { EXYNOS4_GPK3(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//WIFI_DATA0
    { EXYNOS4_GPK3(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//WIFI_DATA1
    { EXYNOS4_GPK3(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//WIFI_DATA2
    { EXYNOS4_GPK3(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//WIFI_DATA3
    #endif

    { EXYNOS4_GPL0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//BUCK6_EN
    #ifdef CONFIG_TC4_EVT
    { EXYNOS4_GPL0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//VDD50_EN
    #endif
    #ifdef CONFIG_TC4_DVT
    { EXYNOS4_GPL0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//6260_GPIO3
    #endif

    { EXYNOS4_GPL0(2), /* S3C_GPIO_SLP_PREV*/S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//TP1_EN
    { EXYNOS4_GPL0(3),  S3C_GPIO_SLP_OUT1,	S3C_GPIO_PULL_NONE},	//NFC_EN1  out1

    { EXYNOS4_GPL0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CHG_EN
    { EXYNOS4_GPL0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NO THIS PIN
    { EXYNOS4_GPL0(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//HDMI_IIC_EN
    { EXYNOS4_GPL0(7),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC

    { EXYNOS4_GPL1(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE}, 	//LVDS_PWDN  out0
    { EXYNOS4_GPL1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPL1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC

    { EXYNOS4_GPL2(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//KP_COL0
    #ifdef CONFIG_SMM6260_MODEM
    { EXYNOS4_GPL2(1),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE},	//MD_RESETBB
    #else
    { EXYNOS4_GPL2(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//MD_RESETBB
    #endif
    { EXYNOS4_GPL2(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//HUB_RESET
    { EXYNOS4_GPL2(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//NFC_SCL
    { EXYNOS4_GPL2(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//NFC_SDA
    { EXYNOS4_GPL2(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NFC_GPIO4
    #ifdef CONFIG_TC4_EVT
    { EXYNOS4_GPL2(6),	S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//ANX7805_PWON
    { EXYNOS4_GPL2(7),	S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//TP
    #endif

    #ifdef CONFIG_TC4_DVT
    //GPM4(2) --ISP_SCL1
    //GPM4(3)--ISP_SDA1
    //GPM3(5)--PMIC_DS2
    //GPM3(6)--PMIC_DS3
    //GPM3(7)--PMIC_DS4
    #endif


    #if 1
    { EXYNOS4_GPY0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPY0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC

    { EXYNOS4_GPY0(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */

    { EXYNOS4_GPY1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY1(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */

    { EXYNOS4_GPY2(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY2(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY2(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY2(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY2(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY2(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */

    { EXYNOS4_GPY3(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPY3(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPY3(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* MHL_SCL_1.8V */
    { EXYNOS4_GPY3(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY3(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY3(5),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY3(6),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY3(7),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN},

    { EXYNOS4_GPY4(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(3),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY4(5),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(7),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},

    { EXYNOS4_GPY5(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */

    { EXYNOS4_GPY6(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    #endif
    { EXYNOS4_GPZ(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	//I2S0_SCLK
    { EXYNOS4_GPZ(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	//I2S0_CDCLK
    { EXYNOS4_GPZ(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //I2S0_LRCK
    { EXYNOS4_GPZ(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //I2S0_SDI
    { EXYNOS4_GPZ(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //I2S0_SDO0
    { EXYNOS4_GPZ(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //WIFI_PWDN
    { EXYNOS4_GPZ(6),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE},	//BT_RST

    #else
    { EXYNOS4_GPA0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //BT_TXD
    { EXYNOS4_GPA0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //BT_RXD
    { EXYNOS4_GPA0(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //BT_RTS
    { EXYNOS4_GPA0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //BT_CTS

    { EXYNOS4_GPA0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //AC100_TXD,SMM6260
    { EXYNOS4_GPA0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //AC100_RXD
    { EXYNOS4_GPA0(6),	S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //AC100_RTS
    { EXYNOS4_GPA0(7),	S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //AC100_CTS


    { EXYNOS4_GPA1(0),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //DEBUG
    { EXYNOS4_GPA1(1),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE}, //DEBUG
    { EXYNOS4_GPA1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},  //I2C_SDA3
    { EXYNOS4_GPA1(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C_SCL3
    #ifdef CONFIG_TC4_EVT
    { EXYNOS4_GPA1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //TP1_RST
    { EXYNOS4_GPA1(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //TestPoint
    #endif
    #ifdef CONFIG_TC4_DVT
    { EXYNOS4_GPA1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //GPS_TXD
    { EXYNOS4_GPA1(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //GPS_RXD
    #endif

    { EXYNOS4_GPB(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C_SDA4
    { EXYNOS4_GPB(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C_SCL4
    { EXYNOS4_GPB(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C_SDA5
    { EXYNOS4_GPB(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C_SCL5
    { EXYNOS4_GPB(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //GPS_RST
    { EXYNOS4_GPB(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //PMIC_SET1
    { EXYNOS4_GPB(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //PMIC_SET2
    { EXYNOS4_GPB(7),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //PMIC_SET3


    { EXYNOS4_GPC0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //MD_PWON
    { EXYNOS4_GPC0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //VLED_ON
    #ifdef CONFIG_SMM6260_MODEM
    { EXYNOS4_GPC0(2),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE}, //MD_RSTN  //lisw_2012.029 for Modem do not go into L3
    #else
    { EXYNOS4_GPC0(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //MD_RSTN
    #endif
    { EXYNOS4_GPC0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //AP_SLEEP
    { EXYNOS4_GPC0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //AP_WAKEUP_MD

    { EXYNOS4_GPC1(0),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE}, //UART_SW  config as hp  out1??
    { EXYNOS4_GPC1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //LED_EN18
    { EXYNOS4_GPC1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN}, //VLED_EN
    { EXYNOS4_GPC1(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C6_SDA
    { EXYNOS4_GPC1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C6_SCL

    { EXYNOS4_GPD0(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE}, // MOTOR-PWM
    { EXYNOS4_GPD0(1),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE}, //XPWMOUT1
    { EXYNOS4_GPD0(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},  //I2C7_SDA
    { EXYNOS4_GPD0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C7_SCL

    { EXYNOS4_GPD1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C0_SDA
    { EXYNOS4_GPD1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C0_SCL
    { EXYNOS4_GPD1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C1_SDA
    { EXYNOS4_GPD1(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE}, //I2C1_SCL

    { EXYNOS4_GPF0(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_HSYNC
    { EXYNOS4_GPF0(1),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_VSYNC
    { EXYNOS4_GPF0(2),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_VDEN
    { EXYNOS4_GPF0(3),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_VCLK
    { EXYNOS4_GPF0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//CAM2M_RST
    { EXYNOS4_GPF0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//CAM2M_PWDN
    { EXYNOS4_GPF0(6),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_D2
    { EXYNOS4_GPF0(7),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_D3

    { EXYNOS4_GPF1(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_D4
    { EXYNOS4_GPF1(1),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//LCD_D5
    { EXYNOS4_GPF1(2),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D6
    { EXYNOS4_GPF1(3),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D7
    { EXYNOS4_GPF1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//CAM5M_RST
    { EXYNOS4_GPF1(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//CAM5M_PWDN
    { EXYNOS4_GPF1(6),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D10
    { EXYNOS4_GPF1(7),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D11

    { EXYNOS4_GPF2(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D12
    { EXYNOS4_GPF2(1),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D13
    { EXYNOS4_GPF2(2),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D14
    { EXYNOS4_GPF2(3),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D15
    { EXYNOS4_GPF2(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPF2(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPF2(6),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D18
    { EXYNOS4_GPF2(7),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D19

    { EXYNOS4_GPF3(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D20
    { EXYNOS4_GPF3(1),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D21
    { EXYNOS4_GPF3(2),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D22
    { EXYNOS4_GPF3(3),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//D23
    { EXYNOS4_GPF3(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPF3(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//MD_G15

    { EXYNOS4212_GPJ0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CAM_CLK
    { EXYNOS4212_GPJ0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CAM_VSYNC
    { EXYNOS4212_GPJ0(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//CAM_HREF
    { EXYNOS4212_GPJ0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA0
    { EXYNOS4212_GPJ0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA1
    { EXYNOS4212_GPJ0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA2
    { EXYNOS4212_GPJ0(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA3
    { EXYNOS4212_GPJ0(7),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA4

    { EXYNOS4212_GPJ1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA5
    { EXYNOS4212_GPJ1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA6
    { EXYNOS4212_GPJ1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//DATA7
    { EXYNOS4212_GPJ1(3),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE},	//CAM_CLK_OUT
    { EXYNOS4212_GPJ1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC

    { EXYNOS4_GPK0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_CLK
    { EXYNOS4_GPK0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_CMD
    { EXYNOS4_GPK0(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_CDn
    { EXYNOS4_GPK0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA0
    { EXYNOS4_GPK0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA1
    { EXYNOS4_GPK0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA2
    { EXYNOS4_GPK0(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA3
    #ifdef CONFIG_TC4_EVT
    { EXYNOS4_GPK1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPK1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    #endif
    #ifdef CONFIG_TC4_DVT
    { EXYNOS4_GPK1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//ANX7805_PD
    { EXYNOS4_GPK1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//VDD50_EN
    #endif

    { EXYNOS4_GPK1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPK1(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA4
    { EXYNOS4_GPK1(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA5
    { EXYNOS4_GPK1(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA6
    { EXYNOS4_GPK1(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//eMMC_DATA7

    { EXYNOS4_GPK2(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//TF_CLK
    { EXYNOS4_GPK2(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//TF_CMD
    { EXYNOS4_GPK2(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//ANX7805_RSTN
    { EXYNOS4_GPK2(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//TF_DATA0
    { EXYNOS4_GPK2(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//TF_DATA1
    { EXYNOS4_GPK2(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//TF_DATA2
    { EXYNOS4_GPK2(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//TF_DATA3
    #ifdef CONFIG_MTK_COMBO_MT66XX
    { EXYNOS4_GPK3(0),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE},	//WIFI_CLK
    { EXYNOS4_GPK3(1),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE},	//WIFI_CMD
    { EXYNOS4_GPK3(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//HUB_CONNECT
    { EXYNOS4_GPK3(3),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE},	//WIFI_DATA0
    { EXYNOS4_GPK3(4),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE},	//WIFI_DATA1
    { EXYNOS4_GPK3(5),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE},	//WIFI_DATA2
    { EXYNOS4_GPK3(6),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE},	//WIFI_DATA3
    #endif

    { EXYNOS4_GPL0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//BUCK6_EN
    #ifdef CONFIG_TC4_EVT
    { EXYNOS4_GPL0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//VDD50_EN
    #endif
    #ifdef CONFIG_TC4_DVT
    { EXYNOS4_GPL0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//6260_GPIO3
    #endif

    { EXYNOS4_GPL0(2),  S3C_GPIO_SLP_PREV,	S3C_GPIO_PULL_NONE},	//TP1_EN
    { EXYNOS4_GPL0(3),  S3C_GPIO_SLP_OUT1,	S3C_GPIO_PULL_NONE},	//NFC_EN1  out1

    { EXYNOS4_GPL0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//CHG_EN
    { EXYNOS4_GPL0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//NO THIS PIN
    { EXYNOS4_GPL0(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//HDMI_IIC_EN
    { EXYNOS4_GPL0(7),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//NC

    { EXYNOS4_GPL1(0),  S3C_GPIO_SLP_OUT0,	S3C_GPIO_PULL_NONE}, 	//LVDS_PWDN  out0
    { EXYNOS4_GPL1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//NC
    { EXYNOS4_GPL1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//NC

    { EXYNOS4_GPL2(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//KP_COL0
    { EXYNOS4_GPL2(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//MD_RESETBB
    { EXYNOS4_GPL2(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//HUB_RESET
    { EXYNOS4_GPL2(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//NFC_SCL
    { EXYNOS4_GPL2(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_NONE},	//NFC_SDA
    { EXYNOS4_GPL2(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NFC_GPIO4
    #ifdef CONFIG_TC4_EVT
    { EXYNOS4_GPL2(6),	S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//ANX7805_PWON
    { EXYNOS4_GPL2(7),	S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//TP
    #endif

    #ifdef CONFIG_TC4_DVT
    //GPM4(2) --ISP_SCL1
    //GPM4(3)--ISP_SDA1
    //GPM3(5)--PMIC_DS2
    //GPM3(6)--PMIC_DS3
    //GPM3(7)--PMIC_DS4
    #endif


    #if 1
    { EXYNOS4_GPY0(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPY0(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC

    { EXYNOS4_GPY0(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY0(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY0(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY0(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */

    { EXYNOS4_GPY1(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY1(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY1(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY1(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */

    { EXYNOS4_GPY2(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY2(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY2(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY2(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY2(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY2(5),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */

    { EXYNOS4_GPY3(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPY3(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	//NC
    { EXYNOS4_GPY3(2),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* MHL_SCL_1.8V */
    { EXYNOS4_GPY3(3),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY3(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY3(5),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY3(6),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY3(7),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN},

    { EXYNOS4_GPY4(0),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(1),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(3),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(4),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY4(5),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(6),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},
    { EXYNOS4_GPY4(7),  S3C_GPIO_SLP_INPUT,	S3C_GPIO_PULL_DOWN},

    { EXYNOS4_GPY5(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY5(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */

    { EXYNOS4_GPY6(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    { EXYNOS4_GPY6(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	/* NC */
    #endif
    { EXYNOS4_GPZ(0),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE},	//I2S0_SCLK
    { EXYNOS4_GPZ(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},	//I2S0_CDCLK
    { EXYNOS4_GPZ(2),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE}, //I2S0_LRCK
    { EXYNOS4_GPZ(3),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE}, //I2S0_SDI
    { EXYNOS4_GPZ(4),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE}, //I2S0_SDO0
    { EXYNOS4_GPZ(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //WIFI_PWDN
    { EXYNOS4_GPZ(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},	//BT_RST
    #endif
};
#ifdef CONFIG_TC4_DVT
//GPX0(0) ---NC
//GPX2(6) --6260_GPIO1
//GPX3(2) --6260_GPIO2
#endif
/* remove by cym 20130426 because no use */
#if 0
static unsigned int tc4_sleep_alive_gpio_table[][4] =
{//ly 20111118 modified it for eint wakeup
 {EXYNOS4_GPX0(0), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //ANX7805_INIT
 {EXYNOS4_GPX0(1), S3C_GPIO_SLP_OUT1,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //ANX7805_PD
 //{EXYNOS4_GPX0(2), S3C_GPIO_OUTPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //ONO
 {EXYNOS4_GPX0(3), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//CABLE_DET
 {EXYNOS4_GPX0(4), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//TP1_INT
 {EXYNOS4_GPX0(5), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//PIX_SDA
 {EXYNOS4_GPX0(6), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //PIX_SCL
 //{EXYNOS4_GPX0(7), S3C_GPIO_SFN(0xf),	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //TF_CDN

 {EXYNOS4_GPX1(0), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},  //CHG_FLT
 {EXYNOS4_GPX1(1), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//NFC_INT
 {EXYNOS4_GPX1(2), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//KP_LED
 {EXYNOS4_GPX1(3), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //HOOK_DET
 {EXYNOS4_GPX1(4), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//WIFI_WOW
 //{EXYNOS4_GPX1(5), S3C_GPIO_SFN(0xf),	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//CHG_UOK
 //{EXYNOS4_GPX1(6), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//MD_SLEEP_REQUEST
 {EXYNOS4_GPX1(7), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //IRQ_PMIC


 {EXYNOS4_GPX2(0), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//KP_ROW0
 {EXYNOS4_GPX2(1), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//KP_ROW1
 {EXYNOS4_GPX2(2), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//HP_DET
 {EXYNOS4_GPX2(3), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//HUB_INIT_N
 {EXYNOS4_GPX2(4), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //MD_B14
 //{EXYNOS4_GPX2(5), S3C_GPIO_SFN(0xf),	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //MD_WAKEUP_AP
 //{EXYNOS4_GPX2(6), S3C_GPIO_SFN(0xf),	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //CHG_DOK
 {EXYNOS4_GPX2(7), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //CHG_COK

 {EXYNOS4_GPX3(0), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//GM_INT1
 {EXYNOS4_GPX3(1), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //GM_INI2
 //{EXYNOS4_GPX3(2), S3C_GPIO_SFN(0xf),	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //FUEL_ALRT
 {EXYNOS4_GPX3(3), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//GYRO_INT
 {EXYNOS4_GPX3(4), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //COMPASS_RDY
 {EXYNOS4_GPX3(5), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //MD_L15
 {EXYNOS4_GPX3(6), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, //HDMI_CEC
 {EXYNOS4_GPX3(7), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//HDMI_HPD

};
#endif
/* end remove */

//added by yulu
static void tc4_config_sleep_gpio_table(void)
{
    /* remove by cym 20130426 */
#if 0
    int i,gpio;
#endif
    /* end remove */
    /*
        [Fix Me] Below codes are sample GPIO initialization and review codes
        for target platform if needed.
*/
#if 0
    for (i = 0; i < ARRAY_SIZE(tc4_sleep_alive_gpio_table); i++)
    {
        gpio = tc4_sleep_alive_gpio_table[i][0];

        s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(tc4_sleep_alive_gpio_table[i][1]));
        if (tc4_sleep_alive_gpio_table[i][2] != S3C_GPIO_SETPIN_NONE)
        {
            gpio_set_value(gpio, tc4_sleep_alive_gpio_table[i][2]);
        }
        s3c_gpio_setpull(gpio, tc4_sleep_alive_gpio_table[i][3]);
    }


#endif
    config_sleep_gpio_table(ARRAY_SIZE(tc4_sleep_gpio_table),
                            tc4_sleep_gpio_table); ///yulu
}

#endif
#define SMDK4412_REV_0_0_ADC_VALUE 0
#define SMDK4412_REV_0_1_ADC_VALUE 443
int samsung_board_rev;

static int get_samsung_board_rev(void)
{
    int		ret = 0;

    ret = 1;

#if 0 //It's only for smdk
    int 		adc_val = 0;
    struct clk	*adc_clk;
    struct resource	*res;
    void __iomem	*adc_regs;
    unsigned int	con;
    int		ret;

    if ((soc_is_exynos4412() && samsung_rev() < EXYNOS4412_REV_1_0) ||
            (soc_is_exynos4212() && samsung_rev() < EXYNOS4212_REV_1_0))
        return SAMSUNG_BOARD_REV_0_0;

    adc_clk = clk_get(NULL, "adc");
    if (unlikely(IS_ERR(adc_clk)))
        return SAMSUNG_BOARD_REV_0_0;

    clk_enable(adc_clk);

    res = platform_get_resource(&s3c_device_adc, IORESOURCE_MEM, 0);
    if (unlikely(!res))
        goto err_clk;

    adc_regs = ioremap(res->start, resource_size(res));
    if (unlikely(!adc_regs))
        goto err_clk;

    writel(S5PV210_ADCCON_SELMUX(3), adc_regs + S5PV210_ADCMUX);

    con = readl(adc_regs + S3C2410_ADCCON);
    con &= ~S3C2410_ADCCON_MUXMASK;
    con &= ~S3C2410_ADCCON_STDBM;
    con &= ~S3C2410_ADCCON_STARTMASK;
    con |=  S3C2410_ADCCON_PRSCEN;

    con |= S3C2410_ADCCON_ENABLE_START;
    writel(con, adc_regs + S3C2410_ADCCON);

    udelay (50);

    adc_val = readl(adc_regs + S3C2410_ADCDAT0) & 0xFFF;
    writel(0, adc_regs + S3C64XX_ADCCLRINT);

    iounmap(adc_regs);
err_clk:
    clk_disable(adc_clk);
    clk_put(adc_clk);

    ret = (adc_val < SMDK4412_REV_0_1_ADC_VALUE/2) ?
                SAMSUNG_BOARD_REV_0_0 : SAMSUNG_BOARD_REV_0_1;

    pr_info ("SMDK MAIN Board Rev 0.%d (ADC value:%d)\n", ret, adc_val);
#endif
    return ret;
}

static void __init smdk4x12_machine_init(void)
{
#ifdef CONFIG_S3C64XX_DEV_SPI
    unsigned int gpio;
    struct clk *sclk = NULL;
    struct clk *prnt = NULL;
#if 0	//remove by cym 20130529
    struct device *spi0_dev = &exynos_device_spi0.dev;
#ifndef CONFIG_FB_S5P_LMS501KF03
    struct device *spi1_dev = &exynos_device_spi1.dev;
#endif
#endif
    struct device *spi2_dev = &exynos_device_spi2.dev;
#endif
    /* remove by cym 20130426 */
#if 0
    int err;
#endif
    /* end remove */

    pm_power_off = smdk4x12_power_off;
    s3c_config_sleep_gpio_table = tc4_config_sleep_gpio_table;
    samsung_board_rev = get_samsung_board_rev();

#if defined(CONFIG_EXYNOS_DEV_PD) && defined(CONFIG_PM_RUNTIME)
    exynos_pd_disable(&exynos4_device_pd[PD_MFC].dev);
    exynos_pd_disable(&exynos4_device_pd[PD_G3D].dev);
    exynos_pd_disable(&exynos4_device_pd[PD_LCD0].dev);
    exynos_pd_disable(&exynos4_device_pd[PD_CAM].dev);
    exynos_pd_disable(&exynos4_device_pd[PD_TV].dev);
    exynos_pd_disable(&exynos4_device_pd[PD_GPS].dev);
    exynos_pd_disable(&exynos4_device_pd[PD_GPS_ALIVE].dev);
    exynos_pd_disable(&exynos4_device_pd[PD_ISP].dev);
#elif defined(CONFIG_EXYNOS_DEV_PD)
    /*
         * These power domains should be always on
         * without runtime pm support.
         */
    exynos_pd_enable(&exynos4_device_pd[PD_MFC].dev);
    exynos_pd_enable(&exynos4_device_pd[PD_G3D].dev);
    exynos_pd_enable(&exynos4_device_pd[PD_LCD0].dev);
    exynos_pd_enable(&exynos4_device_pd[PD_CAM].dev);
    exynos_pd_enable(&exynos4_device_pd[PD_TV].dev);
    exynos_pd_enable(&exynos4_device_pd[PD_GPS].dev);
    exynos_pd_enable(&exynos4_device_pd[PD_GPS_ALIVE].dev);
    exynos_pd_enable(&exynos4_device_pd[PD_ISP].dev);
#endif
    s3c_i2c0_set_platdata(NULL);
    i2c_register_board_info(0, i2c_devs0, ARRAY_SIZE(i2c_devs0));

    s3c_i2c1_set_platdata(NULL);
    i2c_register_board_info(1, i2c_devs1, ARRAY_SIZE(i2c_devs1));

    s3c_i2c2_set_platdata(NULL);
    i2c_register_board_info(2, i2c_devs2, ARRAY_SIZE(i2c_devs2));

    init_lcd_type();
    get_lcd_type();
    setup_ft5x_width_height();

    s3c_i2c3_set_platdata(NULL);
    i2c_register_board_info(3, i2c_devs3, ARRAY_SIZE(i2c_devs3));

    s3c_i2c4_set_platdata(NULL);
    i2c_register_board_info(4, i2c_devs4, ARRAY_SIZE(i2c_devs4));

#ifdef CONFIG_MPU_SENSORS_MPU6050B1
    sensor_hw_init();
#endif

    s3c_i2c5_set_platdata(NULL);
    i2c_register_board_info(5, i2c_devs5, ARRAY_SIZE(i2c_devs5));

    //For S5K4EC (using i2c6)
#ifndef CONFIG_CAN_MCP251X
    s3c_i2c6_set_platdata(NULL);
    i2c_register_board_info(6, i2c_devs6, ARRAY_SIZE(i2c_devs6));
#endif

    s3c_i2c7_set_platdata(NULL);
    i2c_register_board_info(7, i2c_devs7, ARRAY_SIZE(i2c_devs7));

#ifdef CONFIG_ANDROID_PMEM
    android_pmem_set_platdata();
#endif
#if defined(CONFIG_FB_S5P_MIPI_DSIM)
    mipi_fb_init();
#endif
#ifdef CONFIG_FB_S3C
    dev_set_name(&s5p_device_fimd0.dev, "s3cfb.0");
    clk_add_alias("lcd", "exynos4-fb.0", "lcd", &s5p_device_fimd0.dev);
    clk_add_alias("sclk_fimd", "exynos4-fb.0", "sclk_fimd", &s5p_device_fimd0.dev);
    s5p_fb_setname(0, "exynos4-fb");
#if defined(CONFIG_LCD_AMS369FG06) || defined(CONFIG_LCD_LMS501KF03)
    spi_register_board_info(spi_board_info, ARRAY_SIZE(spi_board_info));
#endif
    s5p_fimd0_set_platdata(&smdk4x12_lcd0_pdata);
#ifdef CONFIG_FB_MIPI_DSIM
    s5p_device_mipi_dsim.dev.parent = &exynos4_device_pd[PD_LCD0].dev;
#endif
#ifdef CONFIG_EXYNOS_DEV_PD
    s5p_device_fimd0.dev.parent = &exynos4_device_pd[PD_LCD0].dev;
#endif
#endif
#ifdef CONFIG_FB_S5P
#ifdef CONFIG_FB_S5P_LMS501KF03
    spi_register_board_info(spi_board_info, ARRAY_SIZE(spi_board_info));
    s3cfb_set_platdata(&lms501kf03_data);
#else
    s3cfb_set_platdata(NULL);
#endif
#ifdef CONFIG_FB_S5P_MIPI_DSIM
    s5p_device_dsim.dev.parent = &exynos4_device_pd[PD_LCD0].dev;
#endif
#ifdef CONFIG_EXYNOS_DEV_PD
    s3c_device_fb.dev.parent = &exynos4_device_pd[PD_LCD0].dev;
#endif
#endif
#ifdef CONFIG_USB_EHCI_S5P
    smdk4x12_ehci_init();
#endif
#ifdef CONFIG_USB_OHCI_S5P
    smdk4x12_ohci_init();
#endif
#ifdef CONFIG_USB_GADGET
    smdk4x12_usbgadget_init();
#endif

    samsung_bl_set(&smdk4x12_bl_gpio_info, &smdk4x12_bl_data);

#ifdef CONFIG_EXYNOS4_DEV_DWMCI
    exynos_dwmci_set_platdata(&exynos_dwmci_pdata);
#endif

#ifdef CONFIG_VIDEO_EXYNOS_FIMC_IS
    exynos4_fimc_is_set_platdata(NULL);
#ifdef CONFIG_EXYNOS_DEV_PD
    exynos4_device_fimc_is.dev.parent = &exynos4_device_pd[PD_ISP].dev;
#endif
#endif
#ifdef CONFIG_S3C_DEV_HSMMC
    s3c_sdhci0_set_platdata(&smdk4x12_hsmmc0_pdata);
#endif
#ifdef CONFIG_S3C_DEV_HSMMC1
    s3c_sdhci1_set_platdata(&smdk4x12_hsmmc1_pdata);
#endif
#ifdef CONFIG_S3C_DEV_HSMMC2
    s3c_sdhci2_set_platdata(&smdk4x12_hsmmc2_pdata);
#endif

#ifdef CONFIG_S3C_DEV_HSMMC3
    s3c_sdhci3_set_platdata(&smdk4x12_hsmmc3_pdata);
#endif


#ifdef  CONFIG_MTK_COMBO_MT66XX
    itop4412_wifi_combo_module_gpio_init();
#endif



#ifdef CONFIG_S5P_DEV_MSHC
    s3c_mshci_set_platdata(&exynos4_mshc_pdata);
#endif
#if defined(CONFIG_VIDEO_EXYNOS_TV) && defined(CONFIG_VIDEO_EXYNOS_HDMI)
    dev_set_name(&s5p_device_hdmi.dev, "exynos4-hdmi");
    clk_add_alias("hdmi", "s5p-hdmi", "hdmi", &s5p_device_hdmi.dev);
    clk_add_alias("hdmiphy", "s5p-hdmi", "hdmiphy", &s5p_device_hdmi.dev);
    s5p_tv_setup();

    /* setup dependencies between TV devices */
    s5p_device_hdmi.dev.parent = &exynos4_device_pd[PD_TV].dev;
    s5p_device_mixer.dev.parent = &exynos4_device_pd[PD_TV].dev;

    s5p_i2c_hdmiphy_set_platdata(NULL);
#ifdef CONFIG_VIDEO_EXYNOS_HDMI_CEC
    s5p_hdmi_cec_set_platdata(&hdmi_cec_data);
#endif
#endif
#ifdef CONFIG_VIDEO_EXYNOS_FIMC_LITE
    smdk4x12_set_camera_flite_platdata();
    s3c_set_platdata(&exynos_flite0_default_data,
                     sizeof(exynos_flite0_default_data), &exynos_device_flite0);
    s3c_set_platdata(&exynos_flite1_default_data,
                     sizeof(exynos_flite1_default_data), &exynos_device_flite1);
#ifdef CONFIG_EXYNOS_DEV_PD
    exynos_device_flite0.dev.parent = &exynos4_device_pd[PD_ISP].dev;
    exynos_device_flite1.dev.parent = &exynos4_device_pd[PD_ISP].dev;
#endif
#endif
#ifdef CONFIG_EXYNOS_SETUP_THERMAL
    s5p_tmu_set_platdata(&exynos_tmu_data);
#endif
#ifdef CONFIG_VIDEO_FIMC
    s3c_fimc0_set_platdata(&fimc_plat);
#ifdef CONFIG_TC4_GB
    s3c_fimc1_set_platdata(NULL);
    s3c_fimc2_set_platdata(&fimc_plat);
#else
    s3c_fimc1_set_platdata(&fimc_plat);
    s3c_fimc2_set_platdata(NULL);
#endif
    s3c_fimc3_set_platdata(NULL);
#ifdef CONFIG_EXYNOS_DEV_PD
    s3c_device_fimc0.dev.parent = &exynos4_device_pd[PD_CAM].dev;
    s3c_device_fimc1.dev.parent = &exynos4_device_pd[PD_CAM].dev;
    s3c_device_fimc2.dev.parent = &exynos4_device_pd[PD_CAM].dev;
    s3c_device_fimc3.dev.parent = &exynos4_device_pd[PD_CAM].dev;
#ifdef CONFIG_EXYNOS4_CONTENT_PATH_PROTECTION
    secmem.parent = &exynos4_device_pd[PD_CAM].dev;
#endif
#endif
#ifdef CONFIG_VIDEO_FIMC_MIPI
    s3c_csis0_set_platdata(NULL);
    s3c_csis1_set_platdata(NULL);
#ifdef CONFIG_EXYNOS_DEV_PD
    s3c_device_csis0.dev.parent = &exynos4_device_pd[PD_CAM].dev;
    s3c_device_csis1.dev.parent = &exynos4_device_pd[PD_CAM].dev;
#endif
#endif

#if defined(CONFIG_ITU_A) || defined(CONFIG_CSI_C) \
    || defined(CONFIG_S5K3H1_CSI_C) || defined(CONFIG_S5K3H2_CSI_C) \
    || defined(CONFIG_S5K6A3_CSI_C)
    smdk4x12_cam0_reset(1);
#endif
#if defined(CONFIG_ITU_B) || defined(CONFIG_CSI_D) \
    || defined(CONFIG_S5K3H1_CSI_D) || defined(CONFIG_S5K3H2_CSI_D) \
    || defined(CONFIG_VIDEO_OV5640) \
    || defined(CONFIG_S5K6A3_CSI_D)
    smdk4x12_cam1_reset(1);
#endif
#endif /* CONFIG_VIDEO_FIMC */

#ifdef CONFIG_VIDEO_SAMSUNG_S5P_FIMC
    smdk4x12_camera_config();
    smdk4x12_subdev_config();

    dev_set_name(&s5p_device_fimc0.dev, "s3c-fimc.0");
    dev_set_name(&s5p_device_fimc1.dev, "s3c-fimc.1");
    dev_set_name(&s5p_device_fimc2.dev, "s3c-fimc.2");
    dev_set_name(&s5p_device_fimc3.dev, "s3c-fimc.3");

    clk_add_alias("fimc", "exynos4210-fimc.0", "fimc", &s5p_device_fimc0.dev);
    clk_add_alias("sclk_fimc", "exynos4210-fimc.0", "sclk_fimc",
                  &s5p_device_fimc0.dev);
    clk_add_alias("fimc", "exynos4210-fimc.1", "fimc", &s5p_device_fimc1.dev);
    clk_add_alias("sclk_fimc", "exynos4210-fimc.1", "sclk_fimc",
                  &s5p_device_fimc1.dev);
    clk_add_alias("fimc", "exynos4210-fimc.2", "fimc", &s5p_device_fimc2.dev);
    clk_add_alias("sclk_fimc", "exynos4210-fimc.2", "sclk_fimc",
                  &s5p_device_fimc2.dev);
    clk_add_alias("fimc", "exynos4210-fimc.3", "fimc", &s5p_device_fimc3.dev);
    clk_add_alias("sclk_fimc", "exynos4210-fimc.3", "sclk_fimc",
                  &s5p_device_fimc3.dev);

    s3c_fimc_setname(0, "exynos4210-fimc");
    s3c_fimc_setname(1, "exynos4210-fimc");
    s3c_fimc_setname(2, "exynos4210-fimc");
    s3c_fimc_setname(3, "exynos4210-fimc");
    /* FIMC */
    s3c_set_platdata(&s3c_fimc0_default_data,
                     sizeof(s3c_fimc0_default_data), &s5p_device_fimc0);
    s3c_set_platdata(&s3c_fimc1_default_data,
                     sizeof(s3c_fimc1_default_data), &s5p_device_fimc1);
    s3c_set_platdata(&s3c_fimc2_default_data,
                     sizeof(s3c_fimc2_default_data), &s5p_device_fimc2);
    s3c_set_platdata(&s3c_fimc3_default_data,
                     sizeof(s3c_fimc3_default_data), &s5p_device_fimc3);
#ifdef CONFIG_EXYNOS_DEV_PD
    s5p_device_fimc0.dev.parent = &exynos4_device_pd[PD_CAM].dev;
    s5p_device_fimc1.dev.parent = &exynos4_device_pd[PD_CAM].dev;
    s5p_device_fimc2.dev.parent = &exynos4_device_pd[PD_CAM].dev;
    s5p_device_fimc3.dev.parent = &exynos4_device_pd[PD_CAM].dev;
#endif
#ifdef CONFIG_VIDEO_S5P_MIPI_CSIS
    dev_set_name(&s5p_device_mipi_csis0.dev, "s3c-csis.0");
    dev_set_name(&s5p_device_mipi_csis1.dev, "s3c-csis.1");
    clk_add_alias("csis", "s5p-mipi-csis.0", "csis",
                  &s5p_device_mipi_csis0.dev);
    clk_add_alias("sclk_csis", "s5p-mipi-csis.0", "sclk_csis",
                  &s5p_device_mipi_csis0.dev);
    clk_add_alias("csis", "s5p-mipi-csis.1", "csis",
                  &s5p_device_mipi_csis1.dev);
    clk_add_alias("sclk_csis", "s5p-mipi-csis.1", "sclk_csis",
                  &s5p_device_mipi_csis1.dev);
    dev_set_name(&s5p_device_mipi_csis0.dev, "s5p-mipi-csis.0");
    dev_set_name(&s5p_device_mipi_csis1.dev, "s5p-mipi-csis.1");

    s3c_set_platdata(&s5p_mipi_csis0_default_data,
                     sizeof(s5p_mipi_csis0_default_data), &s5p_device_mipi_csis0);
    s3c_set_platdata(&s5p_mipi_csis1_default_data,
                     sizeof(s5p_mipi_csis1_default_data), &s5p_device_mipi_csis1);
#ifdef CONFIG_EXYNOS_DEV_PD
    s5p_device_mipi_csis0.dev.parent = &exynos4_device_pd[PD_CAM].dev;
    s5p_device_mipi_csis1.dev.parent = &exynos4_device_pd[PD_CAM].dev;
#endif
#endif
#if defined(CONFIG_ITU_A) || defined(CONFIG_CSI_C) \
    || defined(CONFIG_S5K3H1_CSI_C) || defined(CONFIG_S5K3H2_CSI_C) \
    || defined(CONFIG_S5K6A3_CSI_C)
    smdk4x12_cam0_reset(1);
#endif
#if defined(CONFIG_ITU_B) || defined(CONFIG_CSI_D) \
    || defined(CONFIG_S5K3H1_CSI_D) || defined(CONFIG_S5K3H2_CSI_D) \
    || defined(CONFIG_S5K6A3_CSI_D)
    smdk4x12_cam1_reset(1);
#endif
#endif

#if defined(CONFIG_VIDEO_TVOUT)
    s5p_hdmi_hpd_set_platdata(&hdmi_hpd_data);
    s5p_hdmi_cec_set_platdata(&hdmi_cec_data);
#ifdef CONFIG_EXYNOS_DEV_PD
    s5p_device_tvout.dev.parent = &exynos4_device_pd[PD_TV].dev;
    exynos4_device_pd[PD_TV].dev.parent= &exynos4_device_pd[PD_LCD0].dev;
#endif
#endif

#if	defined(CONFIG_VIDEO_JPEG_V2X) || defined(CONFIG_VIDEO_JPEG)
#ifdef CONFIG_EXYNOS_DEV_PD
    s5p_device_jpeg.dev.parent = &exynos4_device_pd[PD_CAM].dev;
    exynos4_jpeg_setup_clock(&s5p_device_jpeg.dev, 160000000);
#endif
#endif

#ifdef CONFIG_ION_EXYNOS
    exynos_ion_set_platdata();
#endif

#if defined(CONFIG_VIDEO_MFC5X) || defined(CONFIG_VIDEO_SAMSUNG_S5P_MFC)
#ifdef CONFIG_EXYNOS_DEV_PD
    s5p_device_mfc.dev.parent = &exynos4_device_pd[PD_MFC].dev;
#endif
    if (soc_is_exynos4412() && samsung_rev() >= EXYNOS4412_REV_1_0)
        exynos4_mfc_setup_clock(&s5p_device_mfc.dev, 200 * MHZ);
    else
        exynos4_mfc_setup_clock(&s5p_device_mfc.dev, 267 * MHZ);
#endif

#if defined(CONFIG_VIDEO_SAMSUNG_S5P_MFC)
    dev_set_name(&s5p_device_mfc.dev, "s3c-mfc");
    clk_add_alias("mfc", "s5p-mfc", "mfc", &s5p_device_mfc.dev);
    s5p_mfc_setname(&s5p_device_mfc, "s5p-mfc");
#endif

#ifdef CONFIG_VIDEO_FIMG2D
    s5p_fimg2d_set_platdata(&fimg2d_data);
#endif

#ifdef CONFIG_SAMSUNG_DEV_KEYPAD
    samsung_keypad_set_platdata(&smdk4x12_keypad_data);
#endif

    /* add by cym 20131114 */
#ifdef CONFIG_USB_NET_DM9620
    dm9620_reset();
#endif
    /* end add */

#ifdef CONFIG_EXYNOS_C2C
    exynos_c2c_set_platdata(&smdk4x12_c2c_pdata);
#endif
#ifndef CONFIG_TC4_GB
    exynos_sysmmu_init();
#endif
    smdk4x12_gpio_power_init();

    platform_add_devices(smdk4x12_devices, ARRAY_SIZE(smdk4x12_devices));
    if (soc_is_exynos4412())
        platform_add_devices(smdk4412_devices, ARRAY_SIZE(smdk4412_devices));

#ifdef CONFIG_FB_S3C
    exynos4_fimd0_setup_clock(&s5p_device_fimd0.dev, "mout_mpll_user",
                              800 * MHZ);
#endif
#ifdef CONFIG_S3C64XX_DEV_SPI
#if 0	//remove by cym 20130529
    sclk = clk_get(spi0_dev, "dout_spi0");
    if (IS_ERR(sclk))
        dev_err(spi0_dev, "failed to get sclk for SPI-0\n");
    prnt = clk_get(spi0_dev, "mout_mpll_user");
    if (IS_ERR(prnt))
        dev_err(spi0_dev, "failed to get prnt\n");
    if (clk_set_parent(sclk, prnt))
        printk(KERN_ERR "Unable to set parent %s of clock %s.\n",
               prnt->name, sclk->name);

    clk_set_rate(sclk, 800 * 1000 * 1000);
    clk_put(sclk);
    clk_put(prnt);

    if (!gpio_request(EXYNOS4_GPB(1), "SPI_CS0")) {
        gpio_direction_output(EXYNOS4_GPB(1), 1);
        s3c_gpio_cfgpin(EXYNOS4_GPB(1), S3C_GPIO_SFN(1));
        s3c_gpio_setpull(EXYNOS4_GPB(1), S3C_GPIO_PULL_UP);
        exynos_spi_set_info(0, EXYNOS_SPI_SRCCLK_SCLK,
                            ARRAY_SIZE(spi0_csi));
    }

    for (gpio = EXYNOS4_GPB(0); gpio < EXYNOS4_GPB(4); gpio++)
        s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV3);

    spi_register_board_info(spi0_board_info, ARRAY_SIZE(spi0_board_info));

#ifndef CONFIG_FB_S5P_LMS501KF03
    sclk = clk_get(spi1_dev, "dout_spi1");
    if (IS_ERR(sclk))
        dev_err(spi1_dev, "failed to get sclk for SPI-1\n");
    prnt = clk_get(spi1_dev, "mout_mpll_user");
    if (IS_ERR(prnt))
        dev_err(spi1_dev, "failed to get prnt\n");
    if (clk_set_parent(sclk, prnt))
        printk(KERN_ERR "Unable to set parent %s of clock %s.\n",
               prnt->name, sclk->name);

    clk_set_rate(sclk, 800 * 1000 * 1000);
    clk_put(sclk);
    clk_put(prnt);

    if (!gpio_request(EXYNOS4_GPB(5), "SPI_CS1")) {
        gpio_direction_output(EXYNOS4_GPB(5), 1);
        s3c_gpio_cfgpin(EXYNOS4_GPB(5), S3C_GPIO_SFN(1));
        s3c_gpio_setpull(EXYNOS4_GPB(5), S3C_GPIO_PULL_UP);
        exynos_spi_set_info(1, EXYNOS_SPI_SRCCLK_SCLK,
                            ARRAY_SIZE(spi1_csi));
    }

    for (gpio = EXYNOS4_GPB(4); gpio < EXYNOS4_GPB(8); gpio++)
        s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV3);

    spi_register_board_info(spi1_board_info, ARRAY_SIZE(spi1_board_info));
#endif
#endif

    sclk = clk_get(spi2_dev, "dout_spi2");
    if (IS_ERR(sclk))
        dev_err(spi2_dev, "failed to get sclk for SPI-2\n");
    prnt = clk_get(spi2_dev, "mout_mpll_user");
    if (IS_ERR(prnt))
        dev_err(spi2_dev, "failed to get prnt\n");
    if (clk_set_parent(sclk, prnt))
        printk(KERN_ERR "Unable to set parent %s of clock %s.\n",
               prnt->name, sclk->name);

    clk_set_rate(sclk, 800 * 1000 * 1000);
    clk_put(sclk);
    clk_put(prnt);

    if (!gpio_request(EXYNOS4_GPC1(2), "SPI_CS2")) {
        gpio_direction_output(EXYNOS4_GPC1(2), 1);
        s3c_gpio_cfgpin(EXYNOS4_GPC1(2), S3C_GPIO_SFN(1));
        s3c_gpio_setpull(EXYNOS4_GPC1(2), S3C_GPIO_PULL_UP);
        exynos_spi_set_info(2, EXYNOS_SPI_SRCCLK_SCLK,
                            ARRAY_SIZE(spi2_csi));
    }

    for (gpio = EXYNOS4_GPC1(1); gpio < EXYNOS4_GPC1(5); gpio++)
        s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV3);

    spi_register_board_info(spi2_board_info, ARRAY_SIZE(spi2_board_info));
#endif
#ifdef CONFIG_BUSFREQ_OPP
    dev_add(&busfreq, &exynos4_busfreq.dev);
    ppmu_init(&exynos_ppmu[PPMU_DMC0], &exynos4_busfreq.dev);
    ppmu_init(&exynos_ppmu[PPMU_DMC1], &exynos4_busfreq.dev);
    ppmu_init(&exynos_ppmu[PPMU_CPU], &exynos4_busfreq.dev);
#endif
    register_reboot_notifier(&exynos4_reboot_notifier);

}

#ifdef CONFIG_EXYNOS_C2C
static void __init exynos_c2c_reserve(void)
{
    static struct cma_region region = {
        .name = "c2c_shdmem",
                .size = 64 * SZ_1M,
        { .alignment	= 64 * SZ_1M },
        .start = C2C_SHAREDMEM_BASE
    };

    BUG_ON(cma_early_region_register(&region));
    BUG_ON(cma_early_region_reserve(&region));
}
#endif
#ifdef CONFIG_TC4_GB
MACHINE_START(SMDK4212, "SMDK4212")
.boot_params	= S5P_PA_SDRAM + 0x100,
.init_irq	= exynos4_init_irq,
.map_io		= smdk4x12_map_io,
.init_machine	= smdk4x12_machine_init,
.timer		= &exynos4_timer,
#if defined(CONFIG_KERNEL_PANIC_DUMP)		//mj for panic-dump
.reserve		= reserve_panic_dump_area,
#endif

#ifdef CONFIG_EXYNOS_C2C
.reserve	= &exynos_c2c_reserve,
#endif
MACHINE_END

MACHINE_START(SMDK4412, "SMDK4212")
.boot_params	= S5P_PA_SDRAM + 0x100,
.init_irq	= exynos4_init_irq,
.map_io		= smdk4x12_map_io,
.init_machine	= smdk4x12_machine_init,
.timer		= &exynos4_timer,

#if defined(CONFIG_KERNEL_PANIC_DUMP)		//mj for panic-dump
.reserve		= reserve_panic_dump_area,
#endif

#ifdef CONFIG_EXYNOS_C2C
.reserve	= &exynos_c2c_reserve,
#endif
MACHINE_END
#endif

#ifdef CONFIG_TC4_ICS
MACHINE_START(SMDK4212, "SMDK4X12")
//MACHINE_START(SMDK4212, "SC1_DVT1")
.boot_params	= S5P_PA_SDRAM + 0x100,
.init_irq	= exynos4_init_irq,
.map_io		= smdk4x12_map_io,
.init_machine	= smdk4x12_machine_init,
.timer		= &exynos4_timer,
#if defined(CONFIG_KERNEL_PANIC_DUMP)		//mj for panic-dump
.reserve		= reserve_panic_dump_area,
#endif

#ifdef CONFIG_EXYNOS_C2C
.reserve	= &exynos_c2c_reserve,
#endif
MACHINE_END

MACHINE_START(SMDK4412, "SMDK4X12")
//MACHINE_START(SMDK4412, "SC1_DVT1")
.boot_params	= S5P_PA_SDRAM + 0x100,
.init_irq	= exynos4_init_irq,
.map_io		= smdk4x12_map_io,
.init_machine	= smdk4x12_machine_init,
.timer		= &exynos4_timer,

#if defined(CONFIG_KERNEL_PANIC_DUMP)		//mj for panic-dump
.reserve		= reserve_panic_dump_area,
#endif

#ifdef CONFIG_EXYNOS_C2C
.reserve	= &exynos_c2c_reserve,
#endif
MACHINE_END
#endif


