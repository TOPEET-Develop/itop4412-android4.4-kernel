#ifndef _MEDIA_OV5640_H
#define _MEDIA_OV5640_H

#include <media/v4l2-subdev.h>

#define V4L2_CTRL_CLASS_IMAGE_PROC      0x009f0000      

#define V4L2_CID_IMAGE_PROC_CLASS_BASE          (V4L2_CTRL_CLASS_IMAGE_PROC | 0x900)
#define V4L2_CID_IMAGE_PROC_CLASS               (V4L2_CTRL_CLASS_IMAGE_PROC | 1)

#define V4L2_CID_PIXEL_RATE                     (V4L2_CID_IMAGE_PROC_CLASS_BASE + 2)

struct ov5640_platform_data {
      int (*s_power)(struct v4l2_subdev *subdev, int on);
};

#endif

