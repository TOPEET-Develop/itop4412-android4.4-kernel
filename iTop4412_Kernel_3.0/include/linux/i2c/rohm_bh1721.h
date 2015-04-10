/*   ADA0167
 * include/linux/i2c/rohm_i2c.h - platform data structure for at0937a sensor
 *
 * Copyright (C) 2008 Google, Inc.
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

#ifndef _LINUX_I2C_ROHM_BH1721_H
#define _LINUX_I2C_ROHM_BH1721_H

#define ROHM_I2C_NAME "rohm-i2c"
#define ROHM_I2C_ADDR (0x23) //7 bits slave address 010 0011

struct ROHM_I2C_platform_data {
	int (*power)(int on);	/* Only valid in first array entry */
	uint32_t flags;
	uint32_t fuzz_x; /* 0x10000 = screen width */
	uint32_t fuzz_y; /* 0x10000 = screen height */
	int fuzz_p;
	int fuzz_w;
};

#endif /* _LINUX_ROHM_I2C */
