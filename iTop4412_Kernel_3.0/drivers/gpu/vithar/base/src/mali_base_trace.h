/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include <cdbg/mali_cdbg.h>

#define beenthere(f, a...)						\
	do {								\
		CDBG_PRINT_INFO(CDBG_BASE, f, ##a);	\
	} while(0)

#define KCALL(x)							\
	do {								\
		beenthere("%s", "--> kernel");					\
		x;							\
		beenthere("%s", "--> user");				\
	} while(0)

