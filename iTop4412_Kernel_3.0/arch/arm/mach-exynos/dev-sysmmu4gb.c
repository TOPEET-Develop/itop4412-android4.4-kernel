/* linux/arch/arm/mach-exynos/dev-sysmmu.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS - System MMU support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/platform_device.h>
#include <linux/dma-mapping.h>

#include <mach/map.h>
#include <mach/irqs.h>
#include <mach/sysmmu.h>
#include <plat/s5p-clock.h>
#ifdef CONFIG_S5P_SYSTEM_MMU
/* SYSMMU Device */
static struct resource s5p_sysmmu_resource[] = {
	[0] = {
		.start	= S5P_PA_SYSMMU_G2D,
		.end	= S5P_PA_SYSMMU_G2D + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_SYSMMU_2D_0,
		.end	= IRQ_SYSMMU_2D_0,
		.flags	= IORESOURCE_IRQ,
	},
	[2] = {
		.start	= S5P_PA_SYSMMU_SSS,
		.end	= S5P_PA_SYSMMU_SSS + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[3] = {
		.start	= IRQ_SYSMMU_SSS_0,
		.end	= IRQ_SYSMMU_SSS_0,
		.flags	= IORESOURCE_IRQ,
	},
	[4] = {
		.start	= S5P_PA_SYSMMU_FIMC0,
		.end	= S5P_PA_SYSMMU_FIMC0 + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[5] = {
		.start	= IRQ_SYSMMU_FIMC0_0,
		.end	= IRQ_SYSMMU_FIMC0_0,
		.flags	= IORESOURCE_IRQ,
	},
	[6] = {
		.start	= S5P_PA_SYSMMU_FIMC1,
		.end	= S5P_PA_SYSMMU_FIMC1 + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[7] = {
		.start	= IRQ_SYSMMU_FIMC1_0,
		.end	= IRQ_SYSMMU_FIMC1_0,
		.flags	= IORESOURCE_IRQ,
	},
	[8] = {
		.start	= S5P_PA_SYSMMU_FIMC2,
		.end	= S5P_PA_SYSMMU_FIMC2 + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[9] = {
		.start	= IRQ_SYSMMU_FIMC2_0,
		.end	= IRQ_SYSMMU_FIMC2_0,
		.flags	= IORESOURCE_IRQ,
	},
	[10] = {
		.start	= S5P_PA_SYSMMU_FIMC3,
		.end	= S5P_PA_SYSMMU_FIMC3 + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[11] = {
		.start	= IRQ_SYSMMU_FIMC3_0,
		.end	= IRQ_SYSMMU_FIMC3_0,
		.flags	= IORESOURCE_IRQ,
	},
	[12] = {
		.start	= S5P_PA_SYSMMU_JPEG,
		.end	= S5P_PA_SYSMMU_JPEG + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[13] = {
		.start	= IRQ_SYSMMU_JPEG_0,
		.end	= IRQ_SYSMMU_JPEG_0,
		.flags	= IORESOURCE_IRQ,
	},
	[14] = {
		.start	= S5P_PA_SYSMMU_FIMD0,
		.end	= S5P_PA_SYSMMU_FIMD0 + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[15] = {
		.start	= IRQ_SYSMMU_LCD0_M0_0,
		.end	= IRQ_SYSMMU_LCD0_M0_0,
		.flags	= IORESOURCE_IRQ,
	},

#if 0
	[16] = {
		.start	= S5P_PA_SYSMMU_FIMC_ISP,
		.end	= S5P_PA_SYSMMU_FIMC_ISP + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[17] = {
		.start	= IRQ_SYSMMU_FIMC_ISP_0,
		.end	= IRQ_SYSMMU_FIMC_ISP_0,
		.flags	= IORESOURCE_IRQ,
	},
	[18] = {
		.start	= S5P_PA_SYSMMU_FIMC_DRC,
		.end	= S5P_PA_SYSMMU_FIMC_DRC + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[19] = {
		.start	= IRQ_SYSMMU_FIMC_DRC_0,
		.end	= IRQ_SYSMMU_FIMC_DRC_0,
		.flags	= IORESOURCE_IRQ,
	},
	[20] = {
		.start	= S5P_PA_SYSMMU_FIMC_FD,
		.end	= S5P_PA_SYSMMU_FIMC_FD + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[21] = {
		.start	= IRQ_SYSMMU_FIMC_FD_0,
		.end	= IRQ_SYSMMU_FIMC_FD_0,
		.flags	= IORESOURCE_IRQ,
	},


	[22] = {
		.start	= S5P_PA_SYSMMU_ISPCPU,
		.end	= S5P_PA_SYSMMU_ISPCPU + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[23] = {
		.start	= IRQ_SYSMMU_ISPCPU_0,
		.end	= IRQ_SYSMMU_ISPCPU_0,
		.flags	= IORESOURCE_IRQ,
	},
	[24] = {
		.start	= S5P_PA_SYSMMU_FIMC_LITE0,
		.end	= S5P_PA_SYSMMU_FIMC_LITE0 + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[25] = {
		.start	= IRQ_SYSMMU_FIMC_LITE0_0,
		.end	= IRQ_SYSMMU_FIMC_LITE0_0,
		.flags	= IORESOURCE_IRQ,
	},
	[26] = {
		.start	= S5P_PA_SYSMMU_FIMC_LITE1,
		.end	= S5P_PA_SYSMMU_FIMC_LITE1 + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[27] = {
		.start	= IRQ_SYSMMU_FIMC_LITE1_0,
		.end	= IRQ_SYSMMU_FIMC_LITE1_0,
		.flags	= IORESOURCE_IRQ,
	},

#endif	
	[16] = {
		.start	= S5P_PA_SYSMMU_GPS,
		.end	= S5P_PA_SYSMMU_GPS + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[17] = {
		//.start	= IRQ_SYSMMU_GPS_0,
		//.end	= IRQ_SYSMMU_GPS_0,
		//.flags	= IORESOURCE_IRQ,
	},
	
	[18] = {
		.start	= S5P_PA_SYSMMU_ROTATOR,
		.end	= S5P_PA_SYSMMU_ROTATOR + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[19] = {
		.start	= IRQ_SYSMMU_ROTATOR_0,
		.end	= IRQ_SYSMMU_ROTATOR_0,
		.flags	= IORESOURCE_IRQ,
	},

	[20] = {
		.start	= S5P_PA_SYSMMU_MDMA2,
		.end	= S5P_PA_SYSMMU_MDMA2 + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[21] = {
		//.start	= IRQ_SYSMMU_MDMA1_1,
		//.end	= IRQ_SYSMMU_MDMA1_1,
		//.flags	= IORESOURCE_IRQ,
	},

		
	[22] = {
		.start	= S5P_PA_SYSMMU_TV,
		.end	= S5P_PA_SYSMMU_TV + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[23] = {
		.start	= IRQ_SYSMMU_TV_M0_0,
		.end	= IRQ_SYSMMU_TV_M0_0,
		.flags	= IORESOURCE_IRQ,
	},

		
		
	[24] = {
		.start	= S5P_PA_SYSMMU_MFC_L,
		.end	= S5P_PA_SYSMMU_MFC_L + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[25] = {
		.start	= IRQ_SYSMMU_MFC_M0_0,
		.end	= IRQ_SYSMMU_MFC_M0_0,
		.flags	= IORESOURCE_IRQ,
	},
	[26] = {
		.start	= S5P_PA_SYSMMU_MFC_R,
		.end	= S5P_PA_SYSMMU_MFC_R + S5P_SZ_SYSMMU - 1,
		.flags	= IORESOURCE_MEM,
	},
	[27] = {
		.start	= IRQ_SYSMMU_MFC_M1_0,
		.end	= IRQ_SYSMMU_MFC_M1_0,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device s5p_device_sysmmu = {
	.name		= "s5p-sysmmu",
	.id		= 32,
	.num_resources	= ARRAY_SIZE(s5p_sysmmu_resource),
	.resource	= s5p_sysmmu_resource,
};
EXPORT_SYMBOL(s5p_device_sysmmu);
#endif

