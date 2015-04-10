/*
 * SAMSUNG NFC N2 Controller
 *
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Author: Woonki Lee <woonki84.lee@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the License, or (at your
 * option) any later version.
 *
 */

#include <linux/platform_device.h>

#define S3FHRN2_DRIVER_NAME		"snfc-n2"

#define S3FHRN2_MAX_BUFFER_SIZE	512

/* ioctl */
#define S3FHRN2_MAGIC	'S'
#define S3FHRN2_GET_MODE	_IOW(S3FHRN2_MAGIC, 0, unsigned int)
#define S3FHRN2_SET_MODE	_IOW(S3FHRN2_MAGIC, 1, unsigned int)

/* size */
#define S3FHRN2_LLC_LENGTH		1
#define S3FHRN2_MSG_MIN_SIZE	1 /* LLC length header is 1*/
#define S3FHRN2_MSG_MAX_SIZE	0x21
#define S3FHRN2_FIRM_MIN_SIZE	1
#define S3FHRN2_FIRM_MAX_SIZE	129 /* length (1) + FW DATA (128) */

/* check */
#define S3FHRN2_IS_LENGTH(val)	(val == S3FHRN2_LLC_LENGTH)

/* gpio pin configuration */
struct s3fhrn2_platform_data {
	unsigned int irq;
	unsigned int ven;
	unsigned int firm;
	void	(*cfg_gpio)(struct platform_device *dev);
};

enum s3fhrn2_state {
	S3FHRN2_ST_OFF = 0,
	S3FHRN2_ST_NORM,
	S3FHRN2_ST_FIRM,
	S3FHRN2_ST_COUNT,
};

