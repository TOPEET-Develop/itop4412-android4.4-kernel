/*
 *  Copyright (C) 2009 Samsung Electronics
 *  Minkyu Kang <mk7.kang@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __MAX17040_BATTERY_H_
#define __MAX17040_BATTERY_H_
#define MAX17040_I2C_NAME	"max17040"
#define MAX17040_I2C_ADDR	(0x6c>>1)

struct max17040_platform_data {
	int (*battery_online)(void);
	int (*charger_online)(void);
	int (*charger_enable)(void);
};

#endif
