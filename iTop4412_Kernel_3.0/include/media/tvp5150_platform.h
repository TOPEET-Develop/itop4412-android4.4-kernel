/*
 * Driver for NOON130PC20 (SXGA camera) from Samsung Electronics
 * 
 * 1/6" 1.3Mp CMOS Image Sensor SoC with an Embedded Image Processor
 *
 * Copyright (C) 2009, Dongsoo Nathaniel Kim<dongsoo45.kim@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

struct tvp5150_platform_data {
	unsigned int default_width;
	unsigned int default_height;
	unsigned int pixelformat;
	int freq;	/* MCLK in KHz */

	/* This SoC supports Parallel & CSI-2 */
	int is_mipi;

	/* Board specific power pin control */
	int (*cam_power)(int onoff);
};

