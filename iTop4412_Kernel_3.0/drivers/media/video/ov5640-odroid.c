/* linux/drivers/media/video/ov5640.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *	         http://www.samsung.com/
 *
 * Driver for OV5640 (SXGA camera) from Samsung Electronics
 * 1/6" 1.3Mp CMOS Image Sensor SoC with an Embedded Image Processor
 * supporting MIPI CSI-2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/init.h>   //ryj add
#include <linux/module.h> //ryj add
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/slab.h>
#include <media/v4l2-chip-ident.h>
#include <media/v4l2-device.h>
#include <media/v4l2-subdev.h>
//#include <media/v4l2-i2c-drv.h> //no this .h
//#include <media/ov5640_platform.h>
//#include <media/sekede_camera.h> //ryj modify  // cancel by dg
#include <linux/gpio.h>  //ryj add
#include <plat/gpio-cfg.h> //ryj add
//#include <mach/gpio-skd4x12.h> //ryj add   //cancel by dg

#include <linux/videodev2.h>


#ifdef CONFIG_VIDEO_SAMSUNG_V4L2
#include <linux/videodev2_samsung.h>
#endif

#include  <media/ov5640.h>

#define OV5640_DRIVER_NAME	"ov5640"


//#define PRINTK(x,y...) do{if(x<1) v4l_info(client, y);}while(0)
//#define PRINTK(x,y...) do{if(x<1) printk(y);}while(0)
#define PRINTK(x,y...) do{if(x>0) printk(y);}while(0)



/* Default resolution & pixelformat. plz ref ov5640_platform.h */
#define FORMAT_FLAGS_COMPRESSED		0x3


//----------------ryj add---------------------------
#if defined(FEATURE_YUV_CAPTURE)
/* JPEG MEMORY SIZE */
#define SENSOR_JPEG_OUTPUT_MAXSIZE	0x29999A /*2726298bytes, 2.6M */
#define EXTRA_MEMSIZE			(0 * SZ_1K)
#define SENSOR_JPEG_SNAPSHOT_MEMSIZE 	0x99C600
#define SENSOR_JPEG_THUMB_MAXSIZE		0xFC00
#define SENSOR_JPEG_POST_MAXSIZE		0xBB800
#endif
//-------------------ryj add----------------------------------

//#define SENSOR_JPEG_SNAPSHOT_MEMSIZE	0x410580



#define DEFAULT_PIX_FMT		V4L2_PIX_FMT_UYVY	/* YUV422 */
#define DEFUALT_MCLK        24000000		/* 24MHz default */

#define OV5640_QSXGA_WIDTH        2592//2560 ryj modify
#define OV5640_QSXGA_HEIGHT       1944//1920 ryj modify
#define OV5640_QXGA_WIDTH         2048
#define OV5640_QXGA_HEIGHT        1536
#define OV5640_UXGA_WIDTH         1600
#define OV5640_UXGA_HEIGHT        1200
#define OV5640_SXGA_WIDTH         1280
#define OV5640_SXGA_HEIGHT        960
#define OV5640_720P_WIDTH         1280
#define OV5640_720P_HEIGHT        720
#define OV5640_XGA_WIDTH          1024
#define OV5640_XGA_HEIGHT         768
#define OV5640_SVGA_WIDTH         800
#define OV5640_SVGA_HEIGHT        600
#define OV5640_VGA_WIDTH          640
#define OV5640_VGA_HEIGHT         480
#define OV5640_QVGA_WIDTH         320
#define OV5640_QVGA_HEIGHT        240
#define OV5640_QCIF_WIDTH         176
#define OV5640_QCIF_HEIGHT        144

/*
 * Specification
 * Parallel : ITU-R. 656/601 YUV422, RGB565, RGB888 (Up to VGA), RAW10
 * Serial : MIPI CSI2 (single lane) YUV422, RGB565, RGB888 (Up to VGA), RAW10
 * Resolution : 1280 (H) x 1024 (V)
 * Image control : Brightness, Contrast, Saturation, Sharpness, Glamour
 * Effect : Mono, Negative, Sepia, Aqua, Sketch
 * FPS : 15fps @full resolution, 30fps @VGA, 24fps @720p
 * Max. pixel clock frequency : 48MHz(upto)
 * Internal PLL (6MHz to 27MHz input frequency)
 */

static int ov5640_init(struct v4l2_subdev *sd, u32 val);


/* result values returned to HAL */
enum ov5640_param_type {
    OV5640_PARAM_CONTRAST = 0,
    OV5640_PARAM_EFFECT,
    OV5640_PARAM_BRIGHTNESS,
    OV5640_PARAM_SATURATION,
    OV5640_PARAM_SHARPNESS,
    OV5640_PARAM_WHITEBALANCE,
    OV5640_PARAM_FOCUS,
    OV5640_PARAM_ISO,
    OV5640_PARAM_METERING,
    OV5640_PARAM_FPS,
    OV5640_PARAM_MAX,
};

enum {
    AUTO_FOCUS_FAILED,
    AUTO_FOCUS_DONE,
    AUTO_FOCUS_CANCELLED,
};

enum af_operation_status {
    AF_NONE = 0,
    AF_START,
    AF_CANCEL,
};

enum ov5640_opmode {
    OV5640_OPMODE_VIDEO = 0,
    OV5640_OPMODE_IMAGE = 1,
};

enum ov5640_preview_frame_size{
    OV5640_PREVIEW_QCIF = 0,	/* 176x144 */
    //OV5640_PREVIEW_CIF,		    /* 352x288 */
    OV5640_PREVIEW_QVGA,      /*320x240*/ //ryj add
    OV5640_PREVIEW_VGA,		    /* 640x480 */
    OV5640_PREVIEW_D1,		    /* 720x480 */
    OV5640_PREVIEW_WVGA,		/* 800x480 */
    OV5640_PREVIEW_SVGA,		/* 800x600 */
    OV5640_PREVIEW_HD1080,
};

enum ov5640_capture_frame_size {
    OV5640_CAPTURE_VGA = 0,	    /* 640x480 */
    OV5640_CAPTURE_WVGA,		/* 800x480 */
    OV5640_CAPTURE_SVGA,		/* 800x600 */
    OV5640_CAPTURE_WSVGA,		/* 1024x600 */
    OV5640_CAPTURE_1MP,		    /* 1280x960 */
    OV5640_CAPTURE_W1MP,		/* 1600x960 */
    OV5640_CAPTURE_2MP,		    /* UXGA  - 1600x1200 */
    OV5640_CAPTURE_W2MP,		/* 35mm Academy Offset Standard 1.66 */
    /* 2048x1232, 2.4MP */
    OV5640_CAPTURE_3MP,		    /* QXGA  - 2048x1536 */
    OV5640_CAPTURE_W4MP,		/* WQXGA - 2560x1536 */
    OV5640_CAPTURE_5MP,		    /* ryj modify 2560x1920 --> 2562x1944*/
    OV5640_CAPTURE_MAX,
};

struct ov5640_framesize {
    unsigned int index;
    unsigned int width;
    unsigned int height;
};

static const struct ov5640_framesize ov5640_preview_framesize_list[] = {
    //{ OV5640_PREVIEW_QCIF,	    176,  144 },
    //{ OV5640_PREVIEW_CIF,		352,  288 }, OV5640_PREVIEW_QVGA
{ OV5640_PREVIEW_QVGA,		320,  240 }, //ryj add
{ OV5640_PREVIEW_VGA,		640,  480 },
//{ OV5640_PREVIEW_D1,		720,  480 },
{OV5640_CAPTURE_SVGA,		800,  600},
};

static const struct ov5640_framesize ov5640_capture_framesize_list[] = {
{ OV5640_CAPTURE_VGA,		640,  480 },
{ OV5640_CAPTURE_SVGA,		800, 600 },
{ OV5640_CAPTURE_2MP,		1600, 1200 },
//{ OV5640_CAPTURE_3MP,		2048, 1536 },
//{ OV5640_CAPTURE_5MP,		2560, 1920 },
{ OV5640_CAPTURE_5MP,		2592, 1944 },  //ryj modify
};

struct ov5640_version {
    u32 major;
    u32 minor;
};

struct ov5640_date_info {
    u32 year;
    u32 month;
    u32 date;
};

enum ov5640_runmode {
    OV5640_RUNMODE_NOTREADY,
    OV5640_RUNMODE_IDLE,
    OV5640_RUNMODE_RUNNING,
    OV5640_RUNMODE_CAPTURE,
};

struct ov5640_jpeg_param {
    u32 enable;
    u32 quality;
    u32 main_size;		/* Main JPEG file size */
    u32 thumb_size;		/* Thumbnail file size */
    u32 main_offset;
    u32 thumb_offset;
    u32 postview_offset;
};


/* Camera functional setting values configured by user concept */
struct ov5640_userset {
    signed int exposure_bias;	/* V4L2_CID_EXPOSURE */
    unsigned int ae_lock;
    unsigned int awb_lock;
    unsigned int auto_wb;	/* V4L2_CID_CAMERA_WHITE_BALANCE */
    unsigned int manual_wb;	/* V4L2_CID_WHITE_BALANCE_PRESET */
    unsigned int wb_temp;	/* V4L2_CID_WHITE_BALANCE_TEMPERATURE */
    unsigned int effect;	/* Color FX (AKA Color tone) */
    unsigned int contrast;	/* V4L2_CID_CAMERA_CONTRAST */
    unsigned int saturation;/* V4L2_CID_CAMERA_SATURATION */
    unsigned int sharpness;	/* V4L2_CID_CAMERA_SHARPNESS */
    unsigned int glamour;
};

struct ov5640_info {
    //struct ov5640_platform_data *pdata;
    struct sekede_camera_data *pdata; //ryj modify
    struct v4l2_subdev sd;
    struct v4l2_pix_format req_fmt;//ryj midify tongyi s5kegcx//pix;
    struct v4l2_fract timeperframe;
    struct v4l2_streamparm strm;

    struct ov5640_framesize *preview;
    struct ov5640_framesize *capture;

    struct ov5640_userset userset;
    struct mutex ctrl_lock;
    enum ov5640_runmode runmode;     /* preview/snapshot/raw */
    //enum ov5640_opmode opmode;      /* preview/snapshot/raw */  ryj comment
    //enum v4l2_sensor_mode sensor_mode;  //ryj add
    struct ov5640_jpeg_param jpeg;
    enum v4l2_pix_format_mode format_mode;  //ryj add
    enum af_operation_status af_status;
    //int preview_framesize_index;
    //int capture_framesize_index;
    int freq;	/* MCLK in KHz */
    int is_mipi;
    int isize;
    int ver;
    int fps;
    int check_previewdata;
    int check_dataline;
    u32 initialized:1;
};

/*static const struct v4l2_fmtdesc capture_fmts[] = {
        {
                .index		= 0,
                .type		= V4L2_BUF_TYPE_VIDEO_CAPTURE,
                .flags		= FORMAT_FLAGS_COMPRESSED,
                .description	= "JPEG + Postview",
                .pixelformat	= V4L2_PIX_FMT_JPEG,
        },
};*/


//-----------ryj modify--------------------
static const struct v4l2_mbus_framefmt capture_fmts[] = {
{
    .code		= V4L2_MBUS_FMT_FIXED,
    .colorspace	= V4L2_COLORSPACE_JPEG,
},
};

//------------------------------------------


static inline struct ov5640_info *to_sensor_info(struct v4l2_subdev *sd)
{
    return container_of(sd, struct ov5640_info, sd);
}

static int ov5640_read_byte(struct v4l2_subdev *sd, u16 subaddr, u8 *value)
{
    struct i2c_msg msg[2];
    struct i2c_client *c = v4l2_get_subdevdata(sd);
    u16 addr;
    u8 data;
    int ret;

    addr = ((subaddr & 0xff00) >> 8) | ((subaddr & 0xff) << 8);

    /* Read needs two message to go */
    msg[0].addr = c->addr;
    msg[0].flags = 0;
    msg[0].buf = (void *)&addr;
    msg[0].len = 2;

    msg[1].addr = c->addr;
    msg[1].flags = I2C_M_RD;
    msg[1].buf = (u8 *)&data;
    msg[1].len = 1;

    ret = i2c_transfer(c->adapter, msg, 2);
    *value = data;
    ret = (ret == 2) ? 0 : -1;
    return ret;
}

static inline int ov5640_write_byte(struct v4l2_subdev *sd, u16 addr, u8 value)
{
    struct i2c_msg msg;
    struct i2c_client *c = v4l2_get_subdevdata(sd);
    int ret, i;
    u8 msgbuf[3] = {0};

    /* Writing only needs one message */
    //memset(&msg, 0, sizeof (msg));
    i = 0;
    msgbuf[i++] = addr >> 8;
    msgbuf[i++] = addr;
    msgbuf[i++] = value;

    msg.addr = c->addr;
    msg.flags = 0;
    msg.buf = msgbuf;
    msg.len = i;

    ret = i2c_transfer(c->adapter, &msg, 1);

    /* If this is a reset register, wait for 1ms */
    if (addr == 0x3008 && (value & 0x80))
        msleep(10);
    ret = (ret == 1) ? 0 : -1;
    
    return ret;
}

static int ov5640_i2c_write(struct v4l2_subdev *sd, unsigned char *i2c_data,
                            unsigned char length)
{
    unsigned char *buf, i;
    int ret = 0;
    struct i2c_client *client = v4l2_get_subdevdata(sd);
    struct i2c_msg msg = {client->addr, 0, length, buf};

    buf = kzalloc(length, GFP_KERNEL);
    if (NULL == buf) return -ENOMEM;

    for (i = 0; i < length; i++)
        buf[i] = i2c_data[i];

    ret = i2c_transfer(client->adapter, &msg, 1) == 1? 0 : -EIO;
    kfree(buf);

    return ret;

}

static int ov5640_set_from_table(struct v4l2_subdev *sd, struct regval_list *table, int size)
{
    int err = 0;
    int i;

    for(i=0; i<size; i++){
        err += ov5640_write_byte(sd, table[i].reg_num, table[i].value);
    }

    return err;
}



static const struct ov5640_framesize *ov5640_get_framesize
        (const struct ov5640_framesize *frmsizes,
         u32 frmsize_count, u32 index)
        {
            int i = 0;

            for (i = 0; i < frmsize_count; i++) {
                if (frmsizes[i].index == index)
                    return &frmsizes[i];
            }

            return NULL;
        }




        /* This function is called from the g_ctrl api
 *
 * This function should be called only after the s_fmt call,
 * which sets the required width/height value.
 *
 * It checks a list of available frame sizes and sets the
 * most appropriate frame size.
 *
 * The list is stored in an increasing order (as far as possible).
 * Hence the first entry (searching from the beginning) where both the
 * width and height is more than the required value is returned.
 * In case of no perfect match, we set the last entry (which is supposed
 * to be the largest resolution supported.)
 */
        static void ov5640_set_framesize(struct v4l2_subdev *sd,
                                         const struct ov5640_framesize *frmsize,
                                         u32 num_frmsize, bool preview)
        {
            struct ov5640_info *info = to_sensor_info(sd);
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            const struct ov5640_framesize **found_frmsize = NULL;
            u32 width = info->req_fmt.width;
            u32 height = info->req_fmt.height;
            int i;

            PRINTK(1,"%s: Requested Res %dx%d\n", __func__,
                   width, height);

            found_frmsize = (const struct ov5640_framesize **)
                    (preview ? &info->preview : &info->capture);

            for(i=0; i<num_frmsize; i++){
                if (frmsize[i].width >= info->req_fmt.width &&
                        frmsize[i].height >= info->req_fmt.height){

                    *found_frmsize = &frmsize[i];
                    //ryj comment save to info->preview and info->capture by address
                    break;
                }
            }

            //set a default fortmate size for preview and capture
            if (*found_frmsize == NULL) {
                PRINTK(1,"%s: ERROR, invalid frame size %dx%d\n", __func__,
                       width, height);
                *found_frmsize = preview ?
                            ov5640_get_framesize(frmsize, num_frmsize,
                                                 OV5640_PREVIEW_VGA) :
                            ov5640_get_framesize(frmsize, num_frmsize,
                                                 OV5640_CAPTURE_5MP);

                //BUG_ON(!(*found_frmsize));
            }


            if (preview) {
                PRINTK(1,"Preview Res Set: %dx%d, index %d\n",
                       (*found_frmsize)->width, (*found_frmsize)->height,
                       (*found_frmsize)->index);
            }
            else {
                PRINTK(1,"Capture Res Set: %dx%d, index %d\n",
                       (*found_frmsize)->width, (*found_frmsize)->height,
                       (*found_frmsize)->index);
            }


        }

        static int ov5640_set_contrast(struct v4l2_subdev *sd, int val)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            int err = 0;
            uint8_t temp = 0;

            ov5640_write_byte(sd, 0x5001, 0xff);
            ov5640_read_byte(sd, 0x5580, &temp);
            temp |= 0x04;
            ov5640_write_byte(sd, 0x5580, temp);

            switch(val){
            case CONTRAST_MINUS_2:
                ov5640_write_byte(sd, 0x5586, 0x10);
                ov5640_write_byte(sd, 0x5585, 0x10);
                break;
            case CONTRAST_MINUS_1:
                ov5640_write_byte(sd, 0x5586, 0x18);
                ov5640_write_byte(sd, 0x5585, 0x18);
                break;
            case CONTRAST_DEFAULT:
                ov5640_write_byte(sd, 0x5586, 0x20);
                ov5640_write_byte(sd, 0x5585, 0x20);
                break;
            case CONTRAST_PLUS_1:
                ov5640_write_byte(sd, 0x5586, 0x28);
                ov5640_write_byte(sd, 0x5585, 0x28);
                break;
            case CONTRAST_PLUS_2:
                ov5640_write_byte(sd, 0x5586, 0x30);
                ov5640_write_byte(sd, 0x5585, 0x30);
                break;
            default:
                PRINTK(1, "%s: value %d not supported\n", __func__, val);
                return err;
            }
            ov5640_write_byte(sd, 0x5588, 0x41);

            return err;
        }

        static int ov5640_set_brightness(struct v4l2_subdev *sd, int val)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            int err = 0;
            uint8_t temp = 0;

            ov5640_write_byte(sd, 0x5001, 0xff);

            switch(val){
            case EV_MINUS_4:
                ov5640_write_byte(sd, 0x5587, 0x40);
                ov5640_read_byte(sd, 0x5580, &temp);
                temp |= 0x04;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_read_byte(sd, 0x5588, &temp);
                temp |= 0x09;
                ov5640_write_byte(sd, 0x5588, temp);
                break;
            case EV_MINUS_3:
                ov5640_write_byte(sd, 0x5587, 0x30);
                ov5640_read_byte(sd, 0x5580, &temp);
                temp |= 0x04;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_read_byte(sd, 0x5588, &temp);
                temp |= 0x09;
                ov5640_write_byte(sd, 0x5588, temp);
                break;
            case EV_MINUS_2:
                ov5640_write_byte(sd, 0x5587, 0x20);
                ov5640_read_byte(sd, 0x5580, &temp);
                temp |= 0x04;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_read_byte(sd, 0x5588, &temp);
                temp |= 0x09;
                ov5640_write_byte(sd, 0x5588, temp);
                break;
            case EV_MINUS_1:
                ov5640_write_byte(sd, 0x5587, 0x10);
                ov5640_read_byte(sd, 0x5580, &temp);
                temp |= 0x04;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_read_byte(sd, 0x5588, &temp);
                temp |= 0x09;
                ov5640_write_byte(sd, 0x5588, temp);
                break;
            case EV_DEFAULT:
                ov5640_write_byte(sd, 0x5587, 0x00);
                ov5640_read_byte(sd, 0x5580, &temp);
                temp |= 0x04;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_read_byte(sd, 0x5588, &temp);
                temp |= 0x01; temp &= 0xf7;
                ov5640_write_byte(sd, 0x5588, temp);
                break;
            case EV_PLUS_1:
                ov5640_write_byte(sd, 0x5587, 0x10);
                ov5640_read_byte(sd, 0x5580, &temp);
                temp |= 0x04;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_read_byte(sd, 0x5588, &temp);
                temp |= 0x01; temp &= 0xf7;
                ov5640_write_byte(sd, 0x5588, temp);
                break;
            case EV_PLUS_2:
                ov5640_write_byte(sd, 0x5587, 0x20);
                ov5640_read_byte(sd, 0x5580, &temp);
                temp |= 0x04;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_read_byte(sd, 0x5588, &temp);
                temp |= 0x01; temp &= 0xf7;
                ov5640_write_byte(sd, 0x5588, temp);
                break;
            case EV_PLUS_3:
                ov5640_write_byte(sd, 0x5587, 0x30);
                ov5640_read_byte(sd, 0x5580, &temp);
                temp |= 0x04;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_read_byte(sd, 0x5588, &temp);
                temp |= 0x01; temp &= 0xf7;
                ov5640_write_byte(sd, 0x5588, temp);
                break;
            case EV_PLUS_4:
                ov5640_write_byte(sd, 0x5587, 0x40);
                ov5640_read_byte(sd, 0x5580, &temp);
                temp |= 0x04;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_read_byte(sd, 0x5588, &temp);
                temp |= 0x01; temp &= 0xf7;
                ov5640_write_byte(sd, 0x5588, temp);
                break;
            default:
                PRINTK(1, "%s: value %d not supported\n", __func__, val);
                return err;
            }

            return err;
        }

        static int ov5640_set_effect(struct v4l2_subdev *sd, int val)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            int err = 0;
            u8 temp;

            ov5640_write_byte(sd, 0x5001, 0xff);
            switch(val){
            case IMAGE_EFFECT_NONE:
                ov5640_read_byte(sd, 0x5580, &temp);
                temp &= 0x06;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_write_byte(sd, 0x5583, 0x40);
                ov5640_write_byte(sd, 0x5584, 0x40);
                break;
            case IMAGE_EFFECT_BNW:
                ov5640_read_byte(sd, 0x5580, &temp);
                temp &= ~0x40; temp |= 0x18;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_write_byte(sd, 0x5583, 0x80);
                ov5640_write_byte(sd, 0x5584, 0x80);
                break;
            case IMAGE_EFFECT_SEPIA:
                ov5640_read_byte(sd, 0x5580, &temp);
                temp &= ~0x40; temp |= 0x18;
                ov5640_write_byte(sd, 0x5580, temp);
                ov5640_write_byte(sd, 0x5583, 0x40);
                ov5640_write_byte(sd, 0x5584, 0xa0);
                break;
            case IMAGE_EFFECT_NEGATIVE:
                ov5640_read_byte(sd, 0x5580, &temp);
                temp |= 0x40;
                ov5640_write_byte(sd, 0x5580, temp);
                break;
            case IMAGE_EFFECT_AQUA:
            case IMAGE_EFFECT_ANTIQUE:
            case IMAGE_EFFECT_SHARPEN:
            default:
                PRINTK(1, "%s: value %d not supported\n", __func__, val);
                return err;
            }

            return err;
        }

        static int ov5640_set_saturation(struct v4l2_subdev *sd, int val)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            int err = 0;
            uint8_t temp = 0;

            ov5640_write_byte(sd, 0x5001, 0xff);

            switch(val){
            case SATURATION_MINUS_2:
                ov5640_write_byte(sd, 0x5583, 0x00);
                ov5640_write_byte(sd, 0x5584, 0x00);
                break;
            case SATURATION_MINUS_1:
                ov5640_write_byte(sd, 0x5583, 0x20);
                ov5640_write_byte(sd, 0x5584, 0x20);
                break;
            case SATURATION_DEFAULT:
                ov5640_write_byte(sd, 0x5583, 0x40);
                ov5640_write_byte(sd, 0x5584, 0x40);
                break;
            case SATURATION_PLUS_1:
                ov5640_write_byte(sd, 0x5583, 0x60);
                ov5640_write_byte(sd, 0x5584, 0x60);
                break;
            case SATURATION_PLUS_2:
                ov5640_write_byte(sd, 0x5583, 0x80);
                ov5640_write_byte(sd, 0x5584, 0x80);
                break;
            default:
                PRINTK(1, "%s: value %d not supported\n", __func__, val);
                return err;
            }
            ov5640_read_byte(sd, 0x5580, &temp);
            temp |= 0x02;
            ov5640_write_byte(sd, 0x5580, temp);
            ov5640_write_byte(sd, 0x5588, 0x41);

            return err;
        }

        static int ov5640_set_sharpness(struct v4l2_subdev *sd, int val)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            int err = 0;

            ov5640_write_byte(sd, 0x5308, 0x65);
            switch(val){
            case SHARPNESS_MINUS_2:
                ov5640_write_byte(sd, 0x5302, 0x00);
                break;
            case SHARPNESS_MINUS_1:
                ov5640_write_byte(sd, 0x5302, 0x04);
                break;
            case SHARPNESS_DEFAULT:
                ov5640_write_byte(sd, 0x5302, 0x0c);
                break;
            case SHARPNESS_PLUS_1:
                ov5640_write_byte(sd, 0x5302, 0x14);
                break;
            case SHARPNESS_PLUS_2:
                ov5640_write_byte(sd, 0x5302, 0x20);
                break;
            default:
                PRINTK(1, "%s: value %d not supported\n", __func__, val);
                return err;
            }

            return err;
        }

        static int ov5640_set_wb(struct v4l2_subdev *sd, int val)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            int err = 0;

            switch(val){
            case WHITE_BALANCE_AUTO:
                ov5640_write_byte(sd, 0x3406, 0x00);
                break;
            case WHITE_BALANCE_SUNNY:
                ov5640_write_byte(sd, 0x3406, 0x01);
                ov5640_write_byte(sd, 0x3400, 0x07);
                ov5640_write_byte(sd, 0x3401, 0x32);
                ov5640_write_byte(sd, 0x3402, 0x04);
                ov5640_write_byte(sd, 0x3403, 0x00);
                ov5640_write_byte(sd, 0x3404, 0x05);
                ov5640_write_byte(sd, 0x3405, 0x36);
                break;
            case WHITE_BALANCE_CLOUDY:
                ov5640_write_byte(sd, 0x3406, 0x01);
                ov5640_write_byte(sd, 0x3400, 0x04);
                ov5640_write_byte(sd, 0x3401, 0x88);
                ov5640_write_byte(sd, 0x3402, 0x04);
                ov5640_write_byte(sd, 0x3403, 0x00);
                ov5640_write_byte(sd, 0x3404, 0x08);
                ov5640_write_byte(sd, 0x3405, 0xb6);
                break;
            case WHITE_BALANCE_TUNGSTEN:
                ov5640_write_byte(sd, 0x3406, 0x01);
                ov5640_write_byte(sd, 0x3400, 0x04);
                ov5640_write_byte(sd, 0x3401, 0x88);
                ov5640_write_byte(sd, 0x3402, 0x04);
                ov5640_write_byte(sd, 0x3403, 0x00);
                ov5640_write_byte(sd, 0x3404, 0x08);
                ov5640_write_byte(sd, 0x3405, 0x36);
                break;
            case WHITE_BALANCE_FLUORESCENT:
                ov5640_write_byte(sd, 0x3406, 0x01);
                ov5640_write_byte(sd, 0x3400, 0x06);
                ov5640_write_byte(sd, 0x3401, 0x13);
                ov5640_write_byte(sd, 0x3402, 0x04);
                ov5640_write_byte(sd, 0x3403, 0x00);
                ov5640_write_byte(sd, 0x3404, 0x07);
                ov5640_write_byte(sd, 0x3405, 0xe2);
                break;
            default:
                PRINTK(1, "%s: value %d not supported\n", __func__, val);
                return err;
            }

            return err;
        }

        static int ov5640_set_focus(struct v4l2_subdev *sd, int val)
        {
            int err = 0;

            return err;
        }

        static int ov5640_set_iso(struct v4l2_subdev *sd, int val)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            int err = 0;

            switch(val){
            case ISO_AUTO:
                ov5640_write_byte(sd, 0x3a18, 0x00);
                ov5640_write_byte(sd, 0x3a19, 0xfc);
                break;
            case ISO_100:
                ov5640_write_byte(sd, 0x3a18, 0x00);
                ov5640_write_byte(sd, 0x3a19, 0x6c);
                break;
            case ISO_200:
                ov5640_write_byte(sd, 0x3a18, 0x00);
                ov5640_write_byte(sd, 0x3a19, 0x6c);
                break;
            case ISO_400:
                ov5640_write_byte(sd, 0x3a18, 0x00);
                ov5640_write_byte(sd, 0x3a19, 0xcc);
                break;
            case ISO_800:
                ov5640_write_byte(sd, 0x3a18, 0x00);
                ov5640_write_byte(sd, 0x3a19, 0xfc);
                break;
            case ISO_1600:
                ov5640_write_byte(sd, 0x3a18, 0x01);
                ov5640_write_byte(sd, 0x3a19, 0xfc);
                break;
            default:
                PRINTK(1, "%s: value %d not supported\n", __func__, val);
                return err;
            }

            return err;
        }

        static int ov5640_set_metering(struct v4l2_subdev *sd, int val)
        {
            int err = 0;

            return err;
        }

        static int ov5640_set_fps(struct v4l2_subdev *sd, int val)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            int err = 0;

            ov5640_write_byte(sd, 0x5001, 0xff);

            switch(val){
            case FRAME_RATE_AUTO:
                break;
            case FRAME_RATE_15:
                break;
            case FRAME_RATE_30:
                break;
            case FRAME_RATE_60:
                break;

            default:
                PRINTK(1, "%s: value %d not supported\n", __func__, val);
                return err;
            }

            return err;
        }

        static int ov5640_auto_focus_onoff(struct v4l2_subdev *sd, int onoff)
        {
            int err = 0;
            struct ov5640_info *info = to_sensor_info(sd);
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            struct sec_cam_parm *parms =
                    (struct sec_cam_parm *)&info->strm.parm.raw_data;
                    u8 af_status=0;

                    PRINTK(1, "%s: start SINGLE AF operation, flash mode %d\n",
                           __func__, parms->flash_mode);
                    PRINTK(1,"%s: auto fucus status = %d, set onoff %d\n", __func__, info->af_status, onoff);
                    // AFC control registers start at 0x6000
                    if(onoff)
                    {
                        ov5640_write_byte(sd, 0x3023, 0x01);
                        ov5640_write_byte(sd, 0x3022, 0x03);
                        do{
                            ov5640_read_byte(sd, 0x3023, &af_status);
                        }while(af_status != 0x00);

                        ov5640_read_byte(sd, 0x3028, &af_status);
                        if(af_status != 0)	//af success
                        {
                            info->af_status = AF_START;
                        }
                        else
                            PRINTK(1,"%s set af failed\n", __func__);
                        PRINTK(1, "%s: af_status set to start\n", __func__);	}
                    else
                    {
                        //cancel autofocus mode
                        PRINTK(1,
                               "%s: sending Single_AF_Off commands to sensor\n", __func__);


                        /* wait until the other thread has completed
                 * aborting the auto focus and restored state
                 */
                        PRINTK(1, "%s: wait AF cancel done start\n", __func__);

                        ov5640_write_byte(sd, 0x3023, 0x01);
                        ov5640_write_byte(sd, 0x3022, 0x08);
                        do{
                            ov5640_read_byte(sd, 0x3023, &af_status);
                        }while(af_status != 0x00);

                        info->af_status = AF_CANCEL;
                        PRINTK(1, "%s: wait AF cancel done finished\n", __func__);
                    }
                    return err;
        }

        static int ov5640_dump_reg(struct v4l2_subdev *sd)
        {
            unsigned int addr;
            unsigned char temp;

            for(addr = 0x3800; addr<0x3816; addr++)
            {
                ov5640_read_byte(sd, addr, &temp);
                PRINTK(1,"%s: [0x%x] = 0x%x\n", __func__, addr, temp);
            }
            return 0;
        }

#define XVCLK 2400
#define AE_Target 52
        static int AE_low, AE_high;
        static int preview_sysclk, preview_HTS;
        static int OV5640_get_sysclk(struct v4l2_subdev *sd)
        {
            // calculate sysclk
            u8 temp1, temp2;
            int Multiplier, PreDiv, VCO, SysDiv, Pll_rdiv, Bit_div2x, sclk_rdiv, sysclk;

            int sclk_rdiv_map[] = {
                1, 2, 4, 8};

            ov5640_read_byte(sd, 0x3034, &temp1);
            temp2 = temp1 & 0x0f;
            if (temp2 == 8 || temp2 == 10) {
                Bit_div2x = temp2 / 2;
            }

            ov5640_read_byte(sd, 0x3035, &temp1);
            SysDiv = temp1>>4;
            if(SysDiv == 0) {
                SysDiv = 16;
            }

            ov5640_read_byte(sd, 0x3036, &temp1);
            Multiplier = temp1;

            ov5640_read_byte(sd, 0x3037, &temp1);
            PreDiv = temp1 & 0x0f;
            Pll_rdiv = ((temp1 >> 4) & 0x01) + 1;

            ov5640_read_byte(sd, 0x3108, &temp1);
            temp2 = temp1 & 0x03;
            sclk_rdiv = sclk_rdiv_map[temp2];

            VCO = XVCLK * Multiplier / PreDiv;

            sysclk = VCO / SysDiv / Pll_rdiv * 2 / Bit_div2x / sclk_rdiv;

            return sysclk;
        }

        static int OV5640_get_HTS(struct v4l2_subdev *sd)
        {
            // read HTS from register settings
            int HTS;
            u8 temp1, temp2;

            ov5640_read_byte(sd, 0x380c, &temp1);
            ov5640_read_byte(sd, 0x380d, &temp2);
            HTS = (temp1<<8) + temp2;

            return HTS;
        }

        static int OV5640_get_VTS(struct v4l2_subdev *sd)
        {
            // read VTS from register settings
            int VTS;
            u8 temp1, temp2;

            ov5640_read_byte(sd, 0x380e, &temp1);
            ov5640_read_byte(sd, 0x380f, &temp2);
            VTS = (temp1<<8) + temp2;

            return VTS;
        }

        static int OV5640_set_VTS(int VTS, struct v4l2_subdev *sd)
        {
            // write VTS to registers
            int temp;

            temp = VTS & 0xff;
            ov5640_write_byte(sd, 0x380f, temp);

            temp = VTS>>8;
            ov5640_write_byte(sd, 0x380e, temp);

            return 0;
        }

        static int OV5640_get_shutter(struct v4l2_subdev *sd)
        {
            // read shutter, in number of line period
            int shutter;
            u8 temp;

            ov5640_read_byte(sd, 0x3500, &temp);
            shutter = (temp & 0x0f);
            ov5640_read_byte(sd, 0x3501, &temp);
            shutter = (shutter<<8) + temp;
            ov5640_read_byte(sd, 0x3502, &temp);
            shutter = (shutter<<4) + (temp>>4);

            return shutter;
        }

        static int OV5640_set_shutter(int shutter, struct v4l2_subdev *sd)
        {
            // write shutter, in number of line period
            u8 temp;

            shutter = shutter & 0xffff;
            temp = (shutter & 0x0f)<<4;
            ov5640_write_byte(sd, 0x3502, temp);

            temp = (shutter & 0xfff)>>4;
            ov5640_write_byte(sd, 0x3501, temp);

            temp = shutter>>12;
            ov5640_write_byte(sd, 0x3500, temp);

            return 0;
        }

        static int OV5640_get_gain16(struct v4l2_subdev *sd)
        {
            // read gain, 16 = 1x
            int gain16;
            u8 temp;

            ov5640_read_byte(sd, 0x350a, &temp);
            gain16 = temp & 0x03;
            ov5640_read_byte(sd, 0x350b, &temp);
            gain16 = (gain16<<8) + temp;

            return gain16;
        }

        static int OV5640_set_gain16(int gain16, struct v4l2_subdev *sd)
        {
            // write gain, 16 = 1x
            u8 temp;
            gain16 = gain16 & 0x3ff;

            temp = gain16 & 0xff;
            ov5640_write_byte(sd, 0x350b, temp);

            temp = gain16>>8;
            ov5640_write_byte(sd, 0x350a, temp);

            return 0;
        }

        static int OV5640_get_light_frequency(struct v4l2_subdev *sd)
        {
            // get banding filter value
            u8 temp, temp1;
            int light_frequency;

            ov5640_read_byte(sd, 0x3c01, &temp);

            if (temp & 0x80) {
                // manual
                ov5640_read_byte(sd, 0x3c00, &temp1);
                if (temp1 & 0x04) {
                    // 50Hz
                    light_frequency = 50;
                }
                else {
                    // 60Hz
                    light_frequency = 60;
                }
            }
            else {
                // auto
                ov5640_read_byte(sd, 0x3c0c, &temp1);
                if (temp1 & 0x01) {
                    // 50Hz
                    light_frequency = 50;
                }
                else {
                    // 60Hz
                }
            }
            return light_frequency;
        }

        static void OV5640_set_bandingfilter(struct v4l2_subdev *sd)
        {
            int preview_VTS;
            int band_step60, max_band60, band_step50, max_band50;

            // read preview PCLK
            preview_sysclk = OV5640_get_sysclk(sd);

            // read preview HTS
            preview_HTS = OV5640_get_HTS(sd);

            // read preview VTS
            preview_VTS = OV5640_get_VTS(sd);

            // calculate banding filter
            // 60Hz
            band_step60 = preview_sysclk * 100/preview_HTS * 100/120;
            ov5640_write_byte(sd, 0x3a0a, (band_step60 >> 8));
            ov5640_write_byte(sd, 0x3a0b, (band_step60 & 0xff));

            max_band60 = (int)((preview_VTS-4)/band_step60);
            ov5640_write_byte(sd, 0x3a0d, max_band60);

            // 50Hz
            band_step50 = preview_sysclk * 100/preview_HTS;
            ov5640_write_byte(sd, 0x3a08, (band_step50 >> 8));
            ov5640_write_byte(sd, 0x3a09, (band_step50 & 0xff));

            max_band50 = (int)((preview_VTS-4)/band_step50);
            ov5640_write_byte(sd, 0x3a0e, max_band50);
        }

        static int OV5640_set_AE_target(int target, struct v4l2_subdev *sd)
        {
            // stable in high
            int fast_high, fast_low;
            AE_low = target * 23 / 25;	// 0.92
            AE_high = target * 27 / 25;	// 1.08

            fast_high = AE_high<<1;
            if(fast_high>255)
                fast_high = 255;

            fast_low = AE_low>>1;

            ov5640_write_byte(sd, 0x3a0f, AE_high);
            ov5640_write_byte(sd, 0x3a10, AE_low);
            ov5640_write_byte(sd, 0x3a1b, AE_high);
            ov5640_write_byte(sd, 0x3a1e, AE_low);
            ov5640_write_byte(sd, 0x3a11, fast_high);
            ov5640_write_byte(sd, 0x3a1f, fast_low);

            return 0;
        }

        static void OV5640_set_night_mode(int NightMode, struct v4l2_subdev *sd)
        {
            u8 temp;
            switch (NightMode)
            {
            case 0://Off
                ov5640_read_byte(sd, 0x3a00, &temp);
                temp = temp & 0xfb;   // night mode off, bit[2] = 0
                ov5640_write_byte(sd, 0x3a00, temp);
                break;
            case 1:// On
                ov5640_read_byte(sd, 0x3a00, &temp);
                temp = temp | 0x04;   // night mode on, bit[2] = 1
                ov5640_write_byte(sd, 0x3a00, temp);
                break;
            default:
                break;
            }
        }

        static int OV5640_capture(struct regval_list *table, int array_size, struct v4l2_subdev *sd)
        {
            // set OV5640 to capture mode

            int preview_shutter, preview_gain16;
            u8 average,preview_uv/*temp*/;
            int capture_shutter, capture_gain16;
            int capture_sysclk, capture_HTS, capture_VTS;
            int light_frequency, capture_bandingfilter, capture_max_band;
            long capture_gain16_shutter;

            //auto focus
            //	 OV5640_auto_focus();

            //disable aec
            ov5640_write_byte(sd, 0x3503, 0x07);

            // read preview PCLK
            preview_sysclk = OV5640_get_sysclk(sd);

            // read preview HTS
            preview_HTS = OV5640_get_HTS(sd);

            // read preview shutter
            preview_shutter = OV5640_get_shutter(sd);


            // read preview gain
            preview_gain16 = OV5640_get_gain16(sd);
            //	 PRINTK("preview_shutter=0x%x, preview_gain16=0x%x\n", preview_shutter, preview_gain16);
            ov5640_read_byte(sd, 0x558c, &preview_uv);

            // get average
            ov5640_read_byte(sd, 0x56a1, &average);
            //	 PRINTK("preview avg=0x%x\n", average);

            // turn off night mode for capture
            OV5640_set_night_mode(0, sd);

            // turn off overlay
            // ov5640_write_byte(sd, 0x3022, 0x06);

            // Write capture setting
            //	 OV5640_capture_setting();
            ov5640_set_from_table(sd, table, array_size);

            // read capture VTS
            capture_VTS = OV5640_get_VTS(sd);
            capture_HTS = OV5640_get_HTS(sd);
            capture_sysclk = OV5640_get_sysclk(sd);
            //	 PRINTK("capture_VTS=0x%x, capture_HTS=0x%x, capture_sysclk=%ul\n", capture_VTS, capture_HTS,capture_sysclk);
            // calculate capture banding filter
            light_frequency = OV5640_get_light_frequency(sd);
            if (light_frequency == 60) {
                // 60Hz
                capture_bandingfilter = capture_sysclk * 100 / capture_HTS * 100 / 120;
            }
            else {
                // 50Hz
                capture_bandingfilter = capture_sysclk * 100 / capture_HTS;
            }
            capture_max_band = (int)((capture_VTS - 4)/capture_bandingfilter);
            preview_shutter = preview_shutter *5/4;

            // calculate capture shutter/gain16
            if (average > AE_low && average < AE_high) {
                // in stable range
                //		 PRINTK("average0\n");
                capture_gain16_shutter = preview_gain16 * preview_shutter * capture_sysclk/preview_sysclk * preview_HTS/capture_HTS * AE_Target / average;
            }
            else {
                //		 PRINTK("average1\n");
                capture_gain16_shutter = preview_gain16 * preview_shutter * capture_sysclk/preview_sysclk * preview_HTS/capture_HTS;
            }
            PRINTK(1," preview_HTS=0x%x, preview_sysclk=%ul\n", preview_HTS,preview_sysclk);
            // gain to shutter
            if(capture_gain16_shutter < (capture_bandingfilter * 16)) {
                // shutter < 1/100
                //		 PRINTK("gain0\n");
                capture_shutter = capture_gain16_shutter/16;
                if(capture_shutter <1)
                    capture_shutter = 1;

                capture_gain16 = capture_gain16_shutter/capture_shutter;
                if(capture_gain16 < 16){
                    // 			 PRINTK("gain00\n");
                    capture_gain16 = 16;
                }
            }
            else {
                //		 PRINTK("gain1\n");
                if(capture_gain16_shutter > (capture_bandingfilter*capture_max_band*16)) {
                    // exposure reach max
                    //		 PRINTK("gain10\n");
                    capture_shutter = capture_bandingfilter*capture_max_band;
                    capture_gain16 = capture_gain16_shutter / capture_shutter;
                }
                else {
                    // 1/100 < capture_shutter =< max, capture_shutter = n/100
                    //		 PRINTK("gain11\n");
                    capture_shutter = (int)(capture_gain16_shutter/16/capture_bandingfilter) * capture_bandingfilter;
                    capture_gain16 = capture_gain16_shutter / capture_shutter;
                }
            }

            // write capture gain
            OV5640_set_gain16(capture_gain16, sd);

            // write capture shutter
            PRINTK(1,"%s shutter=0x%x, capture_VTS=0x%x\n", __func__, capture_shutter, capture_VTS);
            if (capture_shutter > (capture_VTS - 4)) {
                capture_VTS = capture_shutter + 4;
                OV5640_set_VTS(capture_VTS, sd);
            }
            OV5640_set_shutter(capture_shutter, sd);
            msleep(600);
            ov5640_read_byte(sd, 0x56a1, &average);
            //	PRINTK("capture avg=0x%x\n", average);
            //	ov5640_read_byte(sd, 0x5588, &temp);
            //	ov5640_write_byte(sd, 0x5588, temp|0x40);
            //	ov5640_write_byte(sd, 0x5583, preview_uv);
            //	ov5640_write_byte(sd, 0x5584, preview_uv);

            // skip 2 vysnc

            // start capture at 3rd vsync

            return 0;
        }

        static int ov5640_set_preview_start(struct v4l2_subdev *sd)
        {
            int err;
            struct ov5640_info *info = to_sensor_info(sd);
            //struct i2c_client *client = v4l2_get_subdevdata(sd);


            if (!info->req_fmt.width || !info->req_fmt.height ||
                    !info->strm.parm.capture.timeperframe.denominator)
                return -EINVAL;

            // OV5640_set_night_mode(1, sd);
            // state: idle -> preview
            PRINTK(1, "%s: sending Preview_Return cmd\n", __func__);
            PRINTK(1,"%s: set PreviewSize %d, %d\n", __func__, info->req_fmt.width, info->req_fmt.height);

            if((info->req_fmt.width == OV5640_SXGA_WIDTH)&&(info->req_fmt.height == OV5640_SXGA_HEIGHT)){
                err = ov5640_set_from_table(sd, ov5640_preview_sxga_tbl, ARRAY_SIZE(ov5640_preview_sxga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                    return -EIO;
                }
            }
            else if((info->req_fmt.width == OV5640_720P_WIDTH)&&(info->req_fmt.height == OV5640_720P_HEIGHT)){
                err = ov5640_set_from_table(sd, ov5640_preview_720p_tbl, ARRAY_SIZE(ov5640_preview_720p_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                    return -EIO;
                }
            }
            else if((info->req_fmt.width == OV5640_XGA_WIDTH)&&(info->req_fmt.height == OV5640_XGA_HEIGHT)){
                err = ov5640_set_from_table(sd, ov5640_preview_xga_tbl, ARRAY_SIZE(ov5640_preview_xga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                    return -EIO;
                }
            }
            else if((info->req_fmt.width == OV5640_SVGA_WIDTH)&&(info->req_fmt.height == OV5640_SVGA_HEIGHT)){
                err = ov5640_set_from_table(sd, ov5640_preview_svga_tbl, ARRAY_SIZE(ov5640_preview_svga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                    return -EIO;
                }
            }
            else if((info->req_fmt.width == OV5640_VGA_WIDTH)&&(info->req_fmt.height == OV5640_VGA_HEIGHT)){
                err = ov5640_set_from_table(sd, ov5640_preview_vga_tbl, ARRAY_SIZE(ov5640_preview_vga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                    return -EIO;
                }
            }
            else if((info->req_fmt.width == OV5640_QVGA_WIDTH)&&(info->req_fmt.height == OV5640_QVGA_HEIGHT)){  //ryj modify QCIF to QVAG
                err = ov5640_set_from_table(sd, ov5640_preview_qvga_tbl, ARRAY_SIZE(ov5640_preview_qvga_tbl)); //ryj modif QCIF to QVGA
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                    return -EIO;
                }
            }
            else
                PRINTK(1,"[%s] Preview size [%d, %d] NOT supported!\n", __func__, info->req_fmt.width, info->req_fmt.height);

            info->runmode = OV5640_RUNMODE_RUNNING;

            PRINTK(1,"\n%s: runmode now change to %d\n", __func__, info->runmode);

            return 0;

        }


        static int ov5640_set_capture_start(struct v4l2_subdev *sd)
        {

            int err;
            struct ov5640_info *info = to_sensor_info(sd);
            //struct i2c_client *client = v4l2_get_subdevdata(sd);



            PRINTK(1, "%s: runmode = %d\n",	__func__, info->runmode);
            PRINTK(1,"%s: set CaptureSize %d, %d\n", __func__, info->req_fmt.width, info->req_fmt.height);
            // state: capture mode preview

            if (!info->req_fmt.width || !info->req_fmt.height ||
                    !info->strm.parm.capture.timeperframe.denominator)
                return -EINVAL;

            info->preview = NULL;  //Set capture size

            if((info->req_fmt.width == OV5640_QSXGA_WIDTH)&&(info->req_fmt.height == OV5640_QSXGA_HEIGHT)){
                err = OV5640_capture(ov5640_capture_qsxga_tbl, ARRAY_SIZE(ov5640_capture_qsxga_tbl), sd);
                //				err = ov5640_set_from_table(sd, ov5640_capture_qsxga_tbl, ARRAY_SIZE(ov5640_capture_qsxga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                    return -EIO;
                }
            }
            else if((info->req_fmt.width == OV5640_QXGA_WIDTH)&&(info->req_fmt.height == OV5640_QXGA_HEIGHT)){
                err = OV5640_capture(ov5640_capture_qxga_tbl, ARRAY_SIZE(ov5640_capture_qxga_tbl), sd);
                //				err = ov5640_set_from_table(sd, ov5640_capture_qxga_tbl, ARRAY_SIZE(ov5640_capture_qxga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                    return -EIO;
                }
            }
            else if((info->req_fmt.width == OV5640_UXGA_WIDTH)&&(info->req_fmt.height == OV5640_UXGA_HEIGHT)){
                err = OV5640_capture(ov5640_capture_uxga_tbl, ARRAY_SIZE(ov5640_capture_uxga_tbl), sd);
                //				err = ov5640_set_from_table(sd, ov5640_capture_uxga_tbl, ARRAY_SIZE(ov5640_capture_uxga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                    return -EIO;
                }
            }
            else if((info->req_fmt.width == OV5640_SXGA_WIDTH)&&(info->req_fmt.height == OV5640_SXGA_HEIGHT)){
                err = OV5640_capture(ov5640_preview_sxga_tbl, ARRAY_SIZE(ov5640_preview_sxga_tbl), sd);
                //				err = ov5640_set_from_table(sd, ov5640_preview_sxga_tbl, ARRAY_SIZE(ov5640_preview_sxga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                    return -EIO;
                }
            }
            else if((info->req_fmt.width == OV5640_XGA_WIDTH)&&(info->req_fmt.height == OV5640_XGA_HEIGHT)){
                err = OV5640_capture(ov5640_preview_xga_tbl, ARRAY_SIZE(ov5640_preview_xga_tbl), sd);
                //				err = ov5640_set_from_table(sd, ov5640_preview_xga_tbl, ARRAY_SIZE(ov5640_preview_xga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                    return -EIO;
                }
            }

            else if((info->req_fmt.width == OV5640_SVGA_WIDTH)&&(info->req_fmt.height == OV5640_SVGA_HEIGHT)){
                err = OV5640_capture(ov5640_preview_xga_tbl, ARRAY_SIZE(ov5640_preview_xga_tbl), sd);
                //				err = ov5640_set_from_table(sd, ov5640_preview_xga_tbl, ARRAY_SIZE(ov5640_preview_xga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                    return -EIO;
                }
            }


            else if((info->req_fmt.width == OV5640_VGA_WIDTH)&&(info->req_fmt.height == OV5640_VGA_HEIGHT)){
                err = OV5640_capture(ov5640_preview_vga_tbl, ARRAY_SIZE(ov5640_preview_vga_tbl), sd);
                //				err = ov5640_set_from_table(sd, ov5640_preview_vga_tbl, ARRAY_SIZE(ov5640_preview_vga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                    return -EIO;
                }
            }
            else if((info->req_fmt.width == OV5640_QVGA_WIDTH)&&(info->req_fmt.height == OV5640_QVGA_HEIGHT)){
                err = OV5640_capture(ov5640_preview_qvga_tbl, ARRAY_SIZE(ov5640_preview_qvga_tbl), sd);
                //				err = ov5640_set_from_table(sd, ov5640_preview_qvga_tbl, ARRAY_SIZE(ov5640_preview_qvga_tbl));
                if (err < 0) {
                    PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                    return -EIO;
                }
            }
            else
                PRINTK(1,"[%s] Capture size [%d, %d] NOT supported!\n", __func__, info->req_fmt.width, info->req_fmt.height);

            info->runmode = OV5640_RUNMODE_CAPTURE;

            return 0;

        }




        static int ov5640_preview_onoff(struct v4l2_subdev *sd, int onoff)
        {
            int err;
            struct ov5640_info *info = to_sensor_info(sd);
            //struct i2c_client *client = v4l2_get_subdevdata(sd);

            PRINTK(1, "%s: runmode = %d\n",	__func__, info->runmode);
            //PRINTK(1,"%s: runmode = %d, onoff %d\n",	__func__, info->runmode, onoff);

            if(onoff)
            {
                if (!info->req_fmt.width || !info->req_fmt.height ||
                        !info->strm.parm.capture.timeperframe.denominator)
                    return -EINVAL;

                if (info->runmode == OV5640_RUNMODE_CAPTURE) {
                    PRINTK(1,"%s: set CaptureSize %d, %d\n", __func__, info->req_fmt.width, info->req_fmt.height);
                    // state: capture mode preview
                    if((info->req_fmt.width == OV5640_QSXGA_WIDTH)&&(info->req_fmt.height == OV5640_QSXGA_HEIGHT)){
                        err = OV5640_capture(ov5640_capture_qsxga_tbl, ARRAY_SIZE(ov5640_capture_qsxga_tbl), sd);
                        //				err = ov5640_set_from_table(sd, ov5640_capture_qsxga_tbl, ARRAY_SIZE(ov5640_capture_qsxga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else if((info->req_fmt.width == OV5640_QXGA_WIDTH)&&(info->req_fmt.height == OV5640_QXGA_HEIGHT)){
                        err = OV5640_capture(ov5640_capture_qxga_tbl, ARRAY_SIZE(ov5640_capture_qxga_tbl), sd);
                        //				err = ov5640_set_from_table(sd, ov5640_capture_qxga_tbl, ARRAY_SIZE(ov5640_capture_qxga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else if((info->req_fmt.width == OV5640_UXGA_WIDTH)&&(info->req_fmt.height == OV5640_UXGA_HEIGHT)){
                        err = OV5640_capture(ov5640_capture_uxga_tbl, ARRAY_SIZE(ov5640_capture_uxga_tbl), sd);
                        //				err = ov5640_set_from_table(sd, ov5640_capture_uxga_tbl, ARRAY_SIZE(ov5640_capture_uxga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else if((info->req_fmt.width == OV5640_SXGA_WIDTH)&&(info->req_fmt.height == OV5640_SXGA_HEIGHT)){
                        err = OV5640_capture(ov5640_preview_sxga_tbl, ARRAY_SIZE(ov5640_preview_sxga_tbl), sd);
                        //				err = ov5640_set_from_table(sd, ov5640_preview_sxga_tbl, ARRAY_SIZE(ov5640_preview_sxga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else if((info->req_fmt.width == OV5640_XGA_WIDTH)&&(info->req_fmt.height == OV5640_XGA_HEIGHT)){
                        err = OV5640_capture(ov5640_preview_xga_tbl, ARRAY_SIZE(ov5640_preview_xga_tbl), sd);
                        //				err = ov5640_set_from_table(sd, ov5640_preview_xga_tbl, ARRAY_SIZE(ov5640_preview_xga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                            return -EIO;
                        }
                    }

                    else if((info->req_fmt.width == OV5640_SVGA_WIDTH)&&(info->req_fmt.height == OV5640_SVGA_HEIGHT)){
                        err = OV5640_capture(ov5640_preview_xga_tbl, ARRAY_SIZE(ov5640_preview_xga_tbl), sd);
                        //				err = ov5640_set_from_table(sd, ov5640_preview_xga_tbl, ARRAY_SIZE(ov5640_preview_xga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                            return -EIO;
                        }
                    }


                    else if((info->req_fmt.width == OV5640_VGA_WIDTH)&&(info->req_fmt.height == OV5640_VGA_HEIGHT)){
                        err = OV5640_capture(ov5640_preview_vga_tbl, ARRAY_SIZE(ov5640_preview_vga_tbl), sd);
                        //				err = ov5640_set_from_table(sd, ov5640_preview_vga_tbl, ARRAY_SIZE(ov5640_preview_vga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else if((info->req_fmt.width == OV5640_QVGA_WIDTH)&&(info->req_fmt.height == OV5640_QVGA_HEIGHT)){
                        err = OV5640_capture(ov5640_preview_qvga_tbl, ARRAY_SIZE(ov5640_preview_qvga_tbl), sd);
                        //				err = ov5640_set_from_table(sd, ov5640_preview_qvga_tbl, ARRAY_SIZE(ov5640_preview_qvga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Capture_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else
                        PRINTK(1,"[%s] Capture size [%d, %d] NOT supported!\n", __func__, info->req_fmt.width, info->req_fmt.height);
                }
                else {
                    //			OV5640_set_night_mode(1, sd);
                    // state: idle -> preview
                    PRINTK(1, "%s: sending Preview_Return cmd\n", __func__);
                    PRINTK(1,"%s: set PreviewSize %d, %d\n", __func__, info->req_fmt.width, info->req_fmt.height);
                    if((info->req_fmt.width == OV5640_SXGA_WIDTH)&&(info->req_fmt.height == OV5640_SXGA_HEIGHT)){
                        err = ov5640_set_from_table(sd, ov5640_preview_sxga_tbl, ARRAY_SIZE(ov5640_preview_sxga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else if((info->req_fmt.width == OV5640_720P_WIDTH)&&(info->req_fmt.height == OV5640_720P_HEIGHT)){
                        err = ov5640_set_from_table(sd, ov5640_preview_720p_tbl, ARRAY_SIZE(ov5640_preview_720p_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else if((info->req_fmt.width == OV5640_XGA_WIDTH)&&(info->req_fmt.height == OV5640_XGA_HEIGHT)){
                        err = ov5640_set_from_table(sd, ov5640_preview_xga_tbl, ARRAY_SIZE(ov5640_preview_xga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else if((info->req_fmt.width == OV5640_SVGA_WIDTH)&&(info->req_fmt.height == OV5640_SVGA_HEIGHT)){
                        err = ov5640_set_from_table(sd, ov5640_preview_svga_tbl, ARRAY_SIZE(ov5640_preview_svga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else if((info->req_fmt.width == OV5640_VGA_WIDTH)&&(info->req_fmt.height == OV5640_VGA_HEIGHT)){
                        err = ov5640_set_from_table(sd, ov5640_preview_vga_tbl, ARRAY_SIZE(ov5640_preview_vga_tbl));
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else if((info->req_fmt.width == OV5640_QVGA_WIDTH)&&(info->req_fmt.height == OV5640_QVGA_HEIGHT)){  //ryj modify QCIF to QVAG
                        err = ov5640_set_from_table(sd, ov5640_preview_qvga_tbl, ARRAY_SIZE(ov5640_preview_qvga_tbl)); //ryj modif QCIF to QVGA
                        if (err < 0) {
                            PRINTK(1, "%s: failed: ov5640_Preview_Return\n", __func__);
                            return -EIO;
                        }
                    }
                    else
                        PRINTK(1,"[%s] Preview size [%d, %d] NOT supported!\n", __func__, info->req_fmt.width, info->req_fmt.height);
                    info->runmode = OV5640_RUNMODE_RUNNING;
                }
                PRINTK(1,"\n%s: runmode now change to %d\n", __func__, info->runmode);
            }
            else
            {
                if((info->runmode == OV5640_RUNMODE_RUNNING)||(info->runmode == OV5640_RUNMODE_CAPTURE))
                    info->runmode = OV5640_RUNMODE_IDLE;
                PRINTK(1,"%s: runmode now IDLE\n", __func__);
            }
            return 0;
        }
#if 0
        static int ov5640_adjust_exposure(struct v4l2_subdev *sd)
        {
            unsigned char gain;
            unsigned char exposure_low, exposure_mid, exposure_high;
            int preview_framerate=30, capture_framerate=5;
            int preview_maxline=980, capture_maxline=1964;
            unsigned int lines_10ms, capture_gain;
            unsigned long preview_exposure, capture_exposure, capture_exposure_gain;

            ov5640_write_byte(sd, 0x3503, 0x07);
            ov5640_read_byte(sd, 0x350b, &gain);
            ov5640_read_byte(sd, 0x3502, &exposure_low);
            ov5640_read_byte(sd, 0x3501, &exposure_mid);
            ov5640_read_byte(sd, 0x3500, &exposure_high);
            PRINTK("%s: preview_gain=0x%x, exposure_low=0x%x, exposure_mid=0x%x, exposure_high=0x%x\n",
                   __func__, gain, exposure_low, exposure_mid, exposure_high);

            lines_10ms = capture_framerate*capture_maxline/100;
            preview_exposure = (exposure_high<<16)+(exposure_mid<<8)+(exposure_low);
            capture_exposure = ((preview_exposure*capture_framerate*capture_maxline)
                                /(preview_framerate*preview_maxline));
            PRINTK("%s: preview_exposure=0x%x, capture_exposure=0x%x, lines_10ms=0x%x\n",
                   __func__, preview_exposure, capture_exposure, lines_10ms);

            capture_exposure_gain = capture_exposure*gain;

            if(capture_exposure_gain < (capture_maxline))
            {
                capture_exposure = 16*lines_10ms;
            }
            else
            {
                capture_exposure = capture_maxline;
            }

            if(capture_exposure == 0)
                capture_exposure = 1;

            capture_gain = capture_exposure_gain/capture_exposure;
            exposure_low = capture_exposure && 0xff;
            exposure_mid = (capture_exposure>>8) && 0xff;
            exposure_high = (capture_exposure>>16) && 0xff;
            gain = (char)capture_gain;
            PRINTK("%s: capture_gain=0x%x, exposure_low=0x%x, exposure_mid=0x%x, exposure_high=0x%x\n",
                   __func__, capture_gain, exposure_low, exposure_mid, exposure_high);
            ov5640_write_byte(sd, 0x350b, 0x44);
            ov5640_write_byte(sd, 0x3502, 0x50);
            ov5640_write_byte(sd, 0x3501, 0x37);
            ov5640_write_byte(sd, 0x3500, 0);
        }
#endif

        static int ov5640_start_capture(struct v4l2_subdev *sd)
        {
            //int err;
            struct ov5640_info *info = to_sensor_info(sd);

            info->runmode = OV5640_RUNMODE_CAPTURE;
            //	ov5640_adjust_exposure(sd);
            return 0;
        }

        static int ov5640_set_parameter(struct v4l2_subdev *sd,
                                        int *current_value_ptr,	int new_value,
                                        enum ov5640_param_type type)
        {
            int err = 0;
            // struct i2c_client *client = v4l2_get_subdevdata(sd);

            if (*current_value_ptr == new_value)
                return 0;

            switch(type){
            case OV5640_PARAM_CONTRAST:
                err = ov5640_set_contrast(sd, new_value);
                break;
            case OV5640_PARAM_EFFECT:
                err = ov5640_set_effect(sd, new_value);
                break;
            case OV5640_PARAM_BRIGHTNESS:
                err = ov5640_set_brightness(sd, new_value);
                break;
            case OV5640_PARAM_SATURATION:
                err = ov5640_set_saturation(sd, new_value);
                break;
            case OV5640_PARAM_SHARPNESS:
                err = ov5640_set_sharpness(sd, new_value);
                break;
            case OV5640_PARAM_WHITEBALANCE:
                err = ov5640_set_wb(sd, new_value);
                break;
            case OV5640_PARAM_ISO:
                err = ov5640_set_iso(sd, new_value);
                break;
            case OV5640_PARAM_METERING:
                err = ov5640_set_metering(sd, new_value);
                break;
            case OV5640_PARAM_FPS:
                err = ov5640_set_fps(sd, new_value);
                break;
            default:
                PRINTK(1, "mode %d not supported\n", type);
                return err;
            }

            if (!err) *current_value_ptr = new_value;

            return err;
        }



        //------------------------ryj modify-----------------------------------
        //--s5k4ecgx_s_mbus_fmt---
        static int ov5640_s_mbus_fmt(struct v4l2_subdev *sd,
                                     struct v4l2_mbus_framefmt *fmt)
        {
            struct ov5640_info *info = to_sensor_info(sd);
            //struct i2c_client *client = v4l2_get_subdevdata(sd);

            if(!info->initialized) return -1;

            PRINTK(1,"%s: pixelformat = 0x%x, colorspace = 0x%x\n",__func__, fmt->code, fmt->colorspace);

            PRINTK(1,"%s:width = %d, height = %d\n",__func__, fmt->width, fmt->height);

            v4l2_fill_pix_format(&info->req_fmt, fmt);

            if(fmt->colorspace == V4L2_COLORSPACE_JPEG)
                info->format_mode = V4L2_PIX_FMT_MODE_CAPTURE;
            else
                info->format_mode = V4L2_PIX_FMT_MODE_PREVIEW;


            if (info->format_mode != V4L2_PIX_FMT_MODE_CAPTURE) {
                /*if(info->pdata->set_power) {
                        info->pdata->set_power(0);
                        mdelay(100);
                        info->pdata->set_power(1);
                        ov5640_init(sd, 0);

                }*/


                /*ov5640_set_framesize(sd, ov5640_capture_framesize_list,
                                ARRAY_SIZE(ov5640_capture_framesize_list),
                                true);*/

                ov5640_set_framesize(sd, ov5640_preview_framesize_list,
                                     ARRAY_SIZE(ov5640_preview_framesize_list),
                                     true);





            } else {
                /*
                 * In case of image capture mode,
                 * if the given image resolution is not supported,
                 * use the next higher image resolution. */

                /*ov5640_set_framesize(sd, ov5640_preview_framesize_list,
                                                ARRAY_SIZE(ov5640_preview_framesize_list),
                                                true);*/

                ov5640_set_framesize(sd, ov5640_capture_framesize_list,
                                     ARRAY_SIZE(ov5640_capture_framesize_list),
                                     false);

            }
            return 0;
        }


        //-----------------------------------------------------------------

        //------------------ryj add--------------------------------------
        static int ov5640_try_fmt(struct v4l2_subdev *sd,
                                  struct v4l2_mbus_framefmt *fmt)
        {
            int num_entries;
            int i;

            num_entries = ARRAY_SIZE(capture_fmts);

            PRINTK(1,"%s: code = 0x%x , colorspace = 0x%x, num_entries = %d\n",
                   __func__, fmt->code, fmt->colorspace, num_entries);

            for (i = 0; i < num_entries; i++) {
                if (capture_fmts[i].code == fmt->code &&
                        capture_fmts[i].colorspace == fmt->colorspace) {
                    PRINTK(1,"%s: match found, returning 0\n", __func__);
                    return 0;
                }
            }

            PRINTK(1,"%s: no match found, returning -EINVAL\n", __func__);
            return -EINVAL;
        }
        //-------------------------------------------------------------------

        //----ryj add--------------------------------------------------------
        static int ov5640_enum_fmt(struct v4l2_subdev *sd, unsigned int index,
                                   enum v4l2_mbus_pixelcode *code)
        {
            PRINTK(1,"%s: index = %d\n", __func__, index);

            if (index >= ARRAY_SIZE(capture_fmts))
                return -EINVAL;

            *code = capture_fmts[index].code;

            return 0;
        }
        //-----------------------------------------------------------------

        static int ov5640_g_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *param)
        {
            return 0;
        }



        static int ov5640_s_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *param)
        {
            int err = 0;
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            struct ov5640_info *info = to_sensor_info(sd);
            struct sec_cam_parm *new_parms =
                    (struct sec_cam_parm *)&param->parm.raw_data;
                    struct sec_cam_parm *parms =
                            (struct sec_cam_parm *)&info->strm.parm.raw_data;

                            PRINTK(1, "%s: start\n", __func__);

                            if (param->parm.capture.timeperframe.numerator !=
                                    parms->capture.timeperframe.numerator ||
                                    param->parm.capture.timeperframe.denominator !=
                                    parms->capture.timeperframe.denominator) {

                                int fps = 0;
                                int fps_max = 30;

                                if (param->parm.capture.timeperframe.numerator &&
                                        param->parm.capture.timeperframe.denominator)
                                    fps =
                                            (int)(param->parm.capture.timeperframe.denominator /
                                                  param->parm.capture.timeperframe.numerator);
                                else
                                    fps = 0;

                                if (fps <= 0 || fps > fps_max) {
                                    PRINTK(1,
                                           "%s: Framerate %d not supported,"
                                           " setting it to %d fps.\n",
                                           __func__, fps, fps_max);
                                    fps = fps_max;
                                }

                                /*
                 * Don't set the fps value, just update it in the state
                 * We will set the resolution and
                 * fps in the start operation (preview/capture) call
                 */
                                parms->capture.timeperframe.numerator = 1;
                                parms->capture.timeperframe.denominator = fps;
                            }

                            /* we return an error if one happened but don't stop trying to
         * set all parameters passed
         */
                            err = ov5640_set_parameter(sd, &parms->contrast, new_parms->contrast,
                                                       OV5640_PARAM_CONTRAST);
                            err |= ov5640_set_parameter(sd, &parms->effects, new_parms->effects,
                                                        OV5640_PARAM_EFFECT);
                            err |= ov5640_set_parameter(sd, &parms->brightness,	new_parms->brightness,
                                                        OV5640_PARAM_BRIGHTNESS);
                            err |= ov5640_set_focus(sd, new_parms->focus_mode);
                            err |= ov5640_set_parameter(sd, &parms->iso, new_parms->iso,
                                                        OV5640_PARAM_ISO);
                            err |= ov5640_set_parameter(sd, &parms->metering, new_parms->metering,
                                                        OV5640_PARAM_METERING);
                            err |= ov5640_set_parameter(sd, &parms->saturation,	new_parms->saturation,
                                                        OV5640_PARAM_SATURATION);
                            err |= ov5640_set_parameter(sd, &parms->sharpness,	new_parms->sharpness,
                                                        OV5640_PARAM_SHARPNESS);
                            err |= ov5640_set_parameter(sd, &parms->white_balance, new_parms->white_balance,
                                                        OV5640_PARAM_WHITEBALANCE);
                            err |= ov5640_set_parameter(sd, &parms->fps, new_parms->fps,
                                                        OV5640_PARAM_FPS);

                            /*
        if (parms->scene_mode == SCENE_MODE_NIGHTSHOT)
                info->one_frame_delay_ms = NIGHT_MODE_MAX_ONE_FRAME_DELAY_MS;
        else
                info->one_frame_delay_ms = NORMAL_MODE_MAX_ONE_FRAME_DELAY_MS;
                */

                            PRINTK(1, "%s: returning %d\n", __func__, err);
                            return err;
        }


        static int ov5640_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            struct ov5640_info *info = to_sensor_info(sd);
            struct sec_cam_parm *parms =
                    (struct sec_cam_parm *)&info->strm.parm.raw_data;
                    int err = 0;
                    int value = ctrl->value;


                    PRINTK(1, "#--ryj---#%s: V4l2 control ID =0x%x, val = %d\n",
                           __func__, ctrl->id, value);

                    PRINTK(1, "%s: V4l2 control ID =%d\n",
                           __func__, ctrl->id - V4L2_CID_PRIVATE_BASE);



                    /*
        if (!info->initialized) {
                dev_err(&client->dev,
                        "%s: return error because uninitialized\n", __func__);
                return -ENODEV;
        }
        */

                    mutex_lock(&info->ctrl_lock);

                    switch (ctrl->id) {
                    case V4L2_CID_CAMERA_WHITE_BALANCE:
                        ctrl->value = parms->white_balance;
                        break;

                    case V4L2_CID_COLORFX:
                        break;

                    case V4L2_CID_CAMERA_CONTRAST:
                        ctrl->value = parms->contrast;
                        break;

                    case V4L2_CID_CAMERA_SATURATION:
                        ctrl->value = parms->saturation;
                        break;

                    case V4L2_CID_CAMERA_SHARPNESS:
                        ctrl->value = parms->sharpness;
                        break;

                    case V4L2_CID_CAM_JPEG_MEMSIZE:
                        //ctrl->value = SENSOR_JPEG_SNAPSHOT_MEMSIZE;
                        ctrl->value = SENSOR_JPEG_SNAPSHOT_MEMSIZE +
                                SENSOR_JPEG_THUMB_MAXSIZE + SENSOR_JPEG_POST_MAXSIZE; //ryj modify
                        break;

                    case V4L2_CID_CAM_JPEG_MAIN_OFFSET:
                        ctrl->value = info->jpeg.main_offset;
                        break;

                    case V4L2_CID_CAM_JPEG_POSTVIEW_OFFSET:
                        ctrl->value = info->jpeg.postview_offset;
                        break;

                    case V4L2_CID_CAM_JPEG_MAIN_SIZE:
                        ctrl->value = info->jpeg.main_size;
                        break;

                    case V4L2_CID_CAM_JPEG_QUALITY:
                        ctrl->value = info->jpeg.quality;
                        break;
                    case V4L2_CID_CAM_JPEG_THUMB_SIZE:
                        ctrl->value = info->jpeg.thumb_size;
                        break;
                    case V4L2_CID_CAM_JPEG_THUMB_OFFSET:
                        ctrl->value = info->jpeg.thumb_offset;
                        break;

                    case V4L2_CID_CAMERA_EXIF_ISO:
                        ctrl->value = 0;
                        break;

                    case V4L2_CID_CAMERA_EXIF_TV:
                        ctrl->value = 0;
                        break;

                    case V4L2_CID_CAMERA_EXIF_BV:
                        ctrl->value = 0;
                        break;

                    case V4L2_CID_CAMERA_EXIF_EBV:
                        ctrl->value = 0;
                        break;

                    case V4L2_CID_CAMERA_AUTO_FOCUS_RESULT://103 ryj modify V4L2_CID_CAMERA_AUTO_FOCUS_RESULT:
                        ctrl->value = info->af_status;
                        break;

                        //-------------------up to s5kegcx---------
                    case V4L2_CID_CAMERA_EFFECT:
                        ctrl->value = parms->effects;
                        break;

                    case V4L2_CID_CAM_DATE_INFO_YEAR:
                        ctrl->value = 2013;
                        break;
                    case V4L2_CID_CAM_DATE_INFO_MONTH:
                        ctrl->value = 8;
                        break;
                    case V4L2_CID_CAM_DATE_INFO_DATE:
                        ctrl->value = 16;
                        break;
                    case V4L2_CID_CAM_SENSOR_VER:
                        ctrl->value = 1;
                        break;
                  //  case V4L2_CID_CAMERA_GET_ISO:
                      //  ctrl->value = parms->iso;
                    //    break;

                    case V4L2_CID_CAMERA_OBJ_TRACKING_STATUS:
                    case V4L2_CID_CAMERA_SMART_AUTO_STATUS:
                    case V4L2_CID_CAM_FW_MINOR_VER:
                    case V4L2_CID_CAM_FW_MAJOR_VER:
                  //  case V4L2_CID_ESD_INT:
                  //  case V4L2_CID_CAMERA_GET_FLASH_ONOFF:
                 //   case V4L2_CID_CAMERA_GET_SHT_TIME:
                        ctrl->value = 0;
                        break;

                    default:
                        err = -ENOIOCTLCMD;
                        PRINTK(1, "%s: unknown ctrl id 0x%x\n",	__func__, ctrl->id);
                        break;
                    }

                    mutex_unlock(&info->ctrl_lock);

                    return err;
        }

        static int ov5640_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            struct ov5640_info *info = to_sensor_info(sd);
            struct sec_cam_parm *parms =
                    (struct sec_cam_parm *)&info->strm.parm.raw_data;

                    //int err = 0;

                    int err = -ENOIOCTLCMD; //ryj modify

                    int value = ctrl->value;


                    PRINTK(1, "#--ryj---#%s: V4l2 control ID =0x%x, val = %d\n",
                           __func__, ctrl->id, value);


                    PRINTK(1, "%s: V4l2 control ID =%d, val = %d\n",
                           __func__, ctrl->id - V4L2_CID_PRIVATE_BASE, value);

                    if (ctrl->id != V4L2_CID_CAMERA_SET_AUTO_FOCUS)
                        mutex_lock(&info->ctrl_lock);

                    switch (ctrl->id) {
                    case V4L2_CID_CAMERA_OBJECT_POSITION_X:
                        err = 0;
                        break;
                    case V4L2_CID_CAMERA_OBJECT_POSITION_Y:
                        err = 0;
                        break;
                    case V4L2_CID_CAMERA_FOCUS_MODE:
                        err = ov5640_set_focus(sd, value);
                        break;

                    case V4L2_CID_CAMERA_SET_AUTO_FOCUS:
                        err = ov5640_auto_focus_onoff(sd, value);
                        break;

                    case V4L2_CID_CAMERA_FLASH_MODE:
                        err = 0;
                        break;

                    case V4L2_CID_CAMERA_BRIGHTNESS:
                        if (info->runmode == OV5640_RUNMODE_RUNNING) {
                            err = ov5640_set_parameter(sd, &parms->brightness, value, OV5640_PARAM_BRIGHTNESS);
                        } else {
                            PRINTK(1,
                                   "%s: trying to set brightness when not in preview mode\n", __func__);
                            err = -EINVAL;
                        }
                        break;
                    case V4L2_CID_CAMERA_WHITE_BALANCE:
                        if (info->runmode == OV5640_RUNMODE_RUNNING) {
                            err = ov5640_set_parameter(sd, &parms->white_balance, value, OV5640_PARAM_WHITEBALANCE);
                        } else {
                            PRINTK(1, "%s: trying to set white balance when not "
                                      "in preview mode\n", __func__);
                            err = -EINVAL;
                        }
                        break;
                    case V4L2_CID_CAMERA_EFFECT:
                        if (info->runmode == OV5640_RUNMODE_RUNNING) {
                            err = ov5640_set_parameter(sd, &parms->effects, value, OV5640_PARAM_EFFECT);
                        } else {
                            PRINTK(1, "%s: trying to set effect when not "
                                      "in preview mode\n", __func__);
                            err = -EINVAL;
                        }
                        break;

                    case V4L2_CID_CAMERA_METERING: //ok
                        if (info->runmode == OV5640_RUNMODE_RUNNING) {
                            err = ov5640_set_parameter(sd, &parms->metering, value, OV5640_PARAM_METERING);
                        } else {
                            PRINTK(1, "%s: trying to set metering when not "
                                      "in preview mode\n", __func__);
                            err = -EINVAL;
                        }
                        break;
                    case V4L2_CID_CAMERA_CONTRAST: //ok
                        err = ov5640_set_parameter(sd, &parms->contrast, value, OV5640_PARAM_CONTRAST);
                        break;
                    case V4L2_CID_CAMERA_SATURATION: //ok
                        err = ov5640_set_parameter(sd, &parms->saturation, value, OV5640_PARAM_SATURATION);
                        break;
                    case V4L2_CID_CAMERA_SHARPNESS: //ok
                        err = ov5640_set_parameter(sd, &parms->sharpness, value, OV5640_PARAM_SHARPNESS);
                        break;

                    case V4L2_CID_CAMERA_SCENE_MODE:
                        err=0;
                        break;

                    case V4L2_CID_CAMERA_CAPTURE:  //ryj add
                        err = 0;
                        break;

                    case V4L2_CID_CAM_JPEG_QUALITY:  //ryj add
                        err = 0;
                        break;

                    case V4L2_CID_CAMERA_ISO: //gan guang set
                        if (info->runmode == OV5640_RUNMODE_RUNNING) {
                            err = ov5640_set_parameter(sd, &parms->iso, value, OV5640_PARAM_ISO);
                        } else {
                            PRINTK(1, "%s: trying to set iso when not "
                                      "in preview mode\n", __func__);
                            err = -EINVAL;
                        }
                        break;


                    case V4L2_CID_CAMERA_FRAME_RATE: //ok
                        PRINTK(1, "%s: camera frame rate request for %d fps\n",
                               __func__, value);
                        err = ov5640_set_parameter(sd, &parms->fps,	value, OV5640_PARAM_FPS);
                        break;
                        /*case V4L2_CID_CAMERA_CAPTURE://V4L2_CID_CAM_CAPTURE: ryj  50
                err = ov5640_start_capture(sd);
                break;*/
                        /*case V4L2_CID_STREAM_PAUSE:
            break;  ryj comment*/

                        /* Used to start / stop preview operation.
         * This call can be modified to START/STOP operation,
         * which can be used in image capture also
         */
                        /*case V4L2_CID_CAM_PREVIEW_ONOFF:
            err = ov5640_preview_onoff(sd, value);
                break;  //ryj comment*/

                    case V4L2_CID_CAMERA_ZOOM:
                        break;

                    default:
                        PRINTK(1, "%s: unknown set ctrl id 0x%x\n",	__func__, ctrl->id);
                        err = -ENOIOCTLCMD;
                        break;
                    }

                    if (err < 0)
                        PRINTK(1, "%s: videoc_s_ctrl failed %d\n", __func__, err);

                    if (ctrl->id != V4L2_CID_CAMERA_SET_AUTO_FOCUS)
                        mutex_unlock(&info->ctrl_lock);

                    PRINTK(1, "%s: videoc_s_ctrl returning %d\n", __func__, err);

                    return err;
        }

        static int ov5640_detect(struct v4l2_subdev *sd)
        {
            struct i2c_client *client = v4l2_get_subdevdata(sd);
            struct i2c_adapter *adapter = client->adapter;
            u8 value=0;

            PRINTK(1, "Now start ov5640 detect\n");
            PRINTK(1,"i2c: addr: 0x%x name: %s\n", client->addr, client->name);

            if (!i2c_check_functionality(adapter, I2C_FUNC_I2C)) {
                PRINTK(1, "i2c not function to detect ov5640\n");
                return -ENODEV;
            }

            ov5640_read_byte(sd, 0x300b, &value);

            PRINTK(1, "#--RYJ--#value =  (0x%x) for ov5640 \n",value);

            if (value != 0x40) {
                PRINTK(1, "unexpected PID (0x%x) for ov5640 (0x%x)\n",
                       value, 0x40);
                return -ENODEV;
            }
            return 0;
        }


        static void ov5640_init_parameters(struct v4l2_subdev *sd)
        {
            struct ov5640_info *info = to_sensor_info(sd);
            struct sec_cam_parm *parms =
                    (struct sec_cam_parm *)&info->strm.parm.raw_data;

                    info->strm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    info->af_status = AF_NONE;
                    parms->capture.capturemode = 0;
                    parms->capture.timeperframe.numerator = 1;
                    parms->capture.timeperframe.denominator = 30;
                    parms->contrast = CONTRAST_DEFAULT;
                    parms->effects = IMAGE_EFFECT_NONE;
                    parms->brightness = EV_DEFAULT;
                    parms->flash_mode = FLASH_MODE_AUTO;
                    parms->focus_mode = FOCUS_MODE_AUTO;
                    parms->iso = ISO_AUTO;
                    parms->metering = METERING_CENTER;
                    parms->saturation = SATURATION_DEFAULT;
                    parms->scene_mode = SCENE_MODE_NONE;
                    parms->sharpness = SHARPNESS_DEFAULT;
                    parms->white_balance = WHITE_BALANCE_AUTO;
        }

        static int ov5640_init(struct v4l2_subdev *sd, u32 val)
        {
            int ret = 0;
            struct i2c_client *c = v4l2_get_subdevdata(sd);
            struct ov5640_info *info = to_sensor_info(sd);
            //struct ov5640_platform_data *pdata;
            //struct sekede_camera_data *pdata;  //ryj modify

            ov5640_detect(sd);

            //pdata = c->dev.platform_data;
            v4l_info(c, "%s: camera initialization start for state: %d\n", __func__, val);

            info->initialized = 0;

            /* Fill the configuration structure */
            /* Note this default configuration value */
            ov5640_init_parameters(sd);

            /* Set registers into default config value */
            ret = ov5640_set_from_table(sd, ov5640_init_tbl, ARRAY_SIZE(ov5640_init_tbl));

            /* download autofucus firmware */
            ret = ov5640_set_from_table(sd, ov5640_firmware_tbl, ARRAY_SIZE(ov5640_firmware_tbl));

            info->runmode = OV5640_RUNMODE_IDLE;

            info->initialized = 1;

            msleep(20);

            return ret;
        }

        /*
 * s_config subdev ops
 * With camera device, we need to re-initialize every single opening time
 * therefor,it is not necessary to be initialized on probe time.
 * except for version checking
 * NOTE: version checking is optional
 */
        static int ov5640_s_config(struct v4l2_subdev *sd, int irq, void *platform_data)
        {
            //struct i2c_client *client = v4l2_get_subdevdata(sd);
            struct ov5640_info *info = to_sensor_info(sd);
            //struct ov5640_platform_data *pdata;
            //struct sekede_camera_data *pdata; //ryj modify

            PRINTK(1, "fetching platform data\n");

            if (!platform_data) {
                printk("%s: ERROR, no platform data\n", __func__);
                return -ENODEV;
            }

            info->pdata = platform_data;

            /*
         * Assign default format and resolution
         * Use configured default information in platform data
         * or without them, use default information in driver
         */
            info->req_fmt.width = info->pdata->default_width;
            info->req_fmt.height = info->pdata->default_height;

            if (!info->pdata->pixelformat)
                info->req_fmt.pixelformat = DEFAULT_PIX_FMT;
            else
                info->req_fmt.pixelformat = info->pdata->pixelformat;

            if (!info->pdata->freq)
                info->freq = DEFUALT_MCLK;	/* 24MHz default */
            else
                info->freq = info->pdata->freq;


            info->preview = info->capture = NULL;
            info->format_mode = V4L2_PIX_FMT_MODE_PREVIEW;//ryj add
            //info->sensor_mode = SENSOR_CAMERA;


            //------------------ryj add  for jpeg----------------------
#if defined(FEATURE_YUV_CAPTURE)
            info->jpeg.enable = 0;
            info->jpeg.quality = 100;
            info->jpeg.main_offset = 0; /* 0x500 */

            /* Maximum size 2592 * 1944 * 2 = 10077696 */
            info->jpeg.main_size = SENSOR_JPEG_SNAPSHOT_MEMSIZE;

            info->jpeg.thumb_size = SENSOR_JPEG_THUMB_MAXSIZE; /* 0x27C */
            info->jpeg.thumb_offset = SENSOR_JPEG_SNAPSHOT_MEMSIZE; /* 0x27C */

            info->jpeg.postview_offset = SENSOR_JPEG_SNAPSHOT_MEMSIZE + SENSOR_JPEG_THUMB_MAXSIZE;

#endif
            //-----------------------------------------------------------

            return 0;
        }

        static int ov5640_sleep(struct v4l2_subdev *sd)
        {
            struct i2c_client *client = v4l2_get_subdevdata(sd);
            int err =0;

            v4l_info(client, "%s: sleep mode\n", __func__);

            return err;
        }

        static int ov5640_wakeup(struct v4l2_subdev *sd)
        {
            struct i2c_client *client = v4l2_get_subdevdata(sd);
            int err = 0;

            v4l_info(client, "%s: wakeup mode\n", __func__);

            return err;
        }


        //-----------------ryj modify-------------------------
        static int ov5640_s_stream(struct v4l2_subdev *sd, int enable)
        {
            /*if (enable) {
        msleep(1000);
        ov5640_write_byte(sd, 0x3008, 0x02);
        msleep(1000);
    } else {
        ov5640_write_byte(sd, 0x3008, 0x42);
    }*/

            //---------------ryj add-------------------------------


            struct ov5640_info *info = to_sensor_info(sd);

            if(!info->initialized)
            {
                printk("#--ryj--#---ov5640_s_stream is error /n");
            }

            PRINTK(1, "---- ov5640_s_stream -enable =%d--info->format_mode = %d\n",enable,info->format_mode);

            if(enable) {
                /*	msleep(1000);
                ov5640_write_byte(sd, 0x3008, 0x02);
                msleep(1000);*/

                if (info->format_mode == V4L2_PIX_FMT_MODE_CAPTURE)
                    //ov5640_start_capture(sd);
                    //ov5640_preview_onoff(sd,enable);
                    ov5640_set_capture_start(sd);
                else
                    //ov5640_preview_onoff(sd,enable);
                    ov5640_set_preview_start(sd);
            }
            /*else
                ov5640_write_byte(sd, 0x3008, 0x42); */
            return 0;
        }
        //----------------------------------------------

        static int ov5640_enum_framesizes(struct v4l2_subdev *sd, struct v4l2_frmsizeenum *fsize)
        {
            struct ov5640_info *info = to_sensor_info(sd);

            PRINTK(1,"%s is called...\n", __func__);

            /* The camera interface should read this value, this is the resolution
         * at which the sensor would provide framedata to the camera i/f
         *
         * In case of image capture,
         * this returns the default camera resolution (QSXGA)
         */
            /*  fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
    fsize->discrete.width = info->req_fmt.width;
    fsize->discrete.height = info->req_fmt.height;
 */

            if (info->format_mode != V4L2_PIX_FMT_MODE_CAPTURE) {
                if (unlikely(info->preview == NULL)) {
                    printk("%s: ERROR\n", __func__);
                    return -EFAULT;
                }

                fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
                fsize->discrete.width = info->preview->width;
                fsize->discrete.height = info->preview->height;
            } else {
                if (unlikely(info->capture == NULL)) {
                    printk("%s: ERROR\n", __func__);
                    return -EFAULT;
                }

                fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
                fsize->discrete.width = info->capture->width;
                fsize->discrete.height = info->capture->height;
            }

            return 0;
        }

        /*
static int
ov5640_enum_frameintervals(struct v4l2_subdev *sd,
                           struct v4l2_frmivalenum *fival)
{
        int err = 0;

        PRINTK(1,"%s is called...\n", __func__);

        return err;
}
*/


        /*
static int
ov5640_g_chip_ident(struct v4l2_subdev *sd, struct v4l2_dbg_chip_ident *chip)
{
    struct i2c_client *client = v4l2_get_subdevdata(sd);

#define V4L2_IDENT_OV5640 8244
    return v4l2_chip_ident_i2c_client(client, chip, V4L2_IDENT_OV5640, 0);
}
*/


#ifdef CONFIG_VIDEO_ADV_DEBUG
        static int
        ov5640_g_register(struct v4l2_subdev *sd, struct v4l2_dbg_register *reg)
        {
            struct i2c_client *client = v4l2_get_subdevdata(sd);
            unsigned char val = 0;
            int ret;

            if (!v4l2_chip_match_i2c_client(client, &reg->match))
                return -EINVAL;
            if (!capable(CAP_SYS_ADMIN))
                return -EPERM;

            ret = ov5640_read_byte(client, reg->reg & 0xffff, &val);
            reg->val = val;
            reg->size = 1;
            return ret;
        }

        static int
        ov5640_s_register(struct v4l2_subdev *sd, struct v4l2_dbg_register *reg)
        {
            struct i2c_client *client = v4l2_get_subdevdata(sd);

            if (!v4l2_chip_match_i2c_client(client, &reg->match))
                return -EINVAL;
            if (!capable(CAP_SYS_ADMIN))
                return -EPERM;

            ov5640_write_byte(client, reg->reg & 0xffff, reg->val & 0xff);
            return 0;
        }
#endif


        static const struct v4l2_subdev_core_ops ov5640_core_ops = {
            .init = ov5640_init,
            // .s_config = ov5640_s_config,	/* Fetch platform data */  no this ops
            //.g_chip_ident = ov5640_g_chip_ident,
            .g_ctrl = ov5640_g_ctrl,
            .s_ctrl = ov5640_s_ctrl,
#ifdef CONFIG_VIDEO_ADV_DEBUG
            .g_register = ov5640_g_register,
            .s_register = ov5640_s_register,
#endif
        };

        static const struct v4l2_subdev_video_ops ov5640_video_ops = {
            /*.s_crystal_freq = ov5640_s_crystal_freq,*/

            .s_mbus_fmt = ov5640_s_mbus_fmt,//ov5640_s_fmt,//ryj add   .s_fmt = ov5640_s_fmt,  no this op
            .enum_framesizes = ov5640_enum_framesizes,
            .enum_mbus_fmt = ov5640_enum_fmt, //ryj add  .enum_fmt = ov5640_enum_fmt, no this op ryj
            .try_mbus_fmt = ov5640_try_fmt, //ryj add  .try_fmt = ov5640_try_fmt,  no this op  ryj
            .g_parm = ov5640_g_parm,
            .s_parm = ov5640_s_parm,
            .s_stream = ov5640_s_stream,


            //.s_mbus_fmt = ov5640_set_fmt,
            //.g_mbus_fmt = ov5640_get_fmt,
            // .g_fmt = ov5640_g_fmt, no this op
            //.enum_frameintervals = ov5640_enum_frameintervals,
        };

        static const struct v4l2_subdev_ops ov5640_ops = {
            .core = &ov5640_core_ops,
            .video = &ov5640_video_ops,
        };

        /* ----------------------------------------------------------------------- */
        static int ov5640_probe(struct i2c_client *client, const struct i2c_device_id *id)
        {
            struct v4l2_subdev *sd;
            struct ov5640_info *info;
            //struct ov5640_platform_data *pdata = client->dev.platform_data;
            struct sekede_camera_data *pdata = client->dev.platform_data;
            int ret = 0;
            int err = -EINVAL;

            if ((pdata == NULL)) {
                PRINTK(1, "%s: bad platform data\n", __func__);
                return -ENODEV;
            }

            printk("====>Probing OV5640...\n");
            info = kzalloc(sizeof (struct ov5640_info), GFP_KERNEL);
            if (info == NULL)
                return -ENOMEM;

            mutex_init(&info->ctrl_lock);

            info->runmode = OV5640_RUNMODE_NOTREADY;
            sd = &info->sd;
            strcpy(sd->name, OV5640_DRIVER_NAME);

            /* Make sure it's an ov5640 */
            v4l2_i2c_subdev_init(sd, client, &ov5640_ops);

            //--------------ryj add------------------------------------------
            err = ov5640_s_config(sd, 0, client->dev.platform_data);

            if(err < 0)
            {
                PRINTK(1, "%s: fail to s_config\n", __func__);
                goto error;
            }

            //----------------------------------------------------------------

            PRINTK(1, "ov5640 has been probed\n");

            return ret;

error:
            if (info) kfree(info);
            return ret;
        }

        static int ov5640_remove(struct i2c_client *client)
        {
            struct v4l2_subdev *sd = i2c_get_clientdata(client);

            v4l2_device_unregister_subdev(sd);
            kfree(to_sensor_info(sd));
            return 0;
        }

        static const struct i2c_device_id ov5640_id[] = {
        {OV5640_DRIVER_NAME, 0},
        {}
        };

        MODULE_DEVICE_TABLE(i2c, ov5640_id);

        static struct i2c_driver ov5640_i2c_driver = {
            .driver = {
                .name	= OV5640_DRIVER_NAME,
            },
            .probe		= ov5640_probe,
            .remove		= ov5640_remove,
            .id_table	= ov5640_id,
        };

        static int __init ov5640_mod_init(void)
        {
            return i2c_add_driver(&ov5640_i2c_driver);
        }

        static void __exit ov5640_mod_exit(void)
        {
            i2c_del_driver(&ov5640_i2c_driver);
        }
        module_init(ov5640_mod_init);
        module_exit(ov5640_mod_exit);



        MODULE_AUTHOR("ryj <ryj_wyy1983@163.com>");
        MODULE_DESCRIPTION("OV5640 Camera Driver");
        MODULE_LICENSE("GPL");
        MODULE_VERSION("1.0");



