/*
 * Copyright (C) 2010 ARM Limited. All rights reserved.
 * 
 * This program is free software and is provided to you under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation, and any use by you of this program is subject to the terms of such GNU licence.
 * 
 * A copy of the licence is included with the program, and can also be obtained from Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "mali_kernel_common.h"
#include "mali_osk.h"
#include "mali_platform.h"


_mali_osk_errcode_t mali_platform_init(_mali_osk_resource_t *resource)
{
#if MALI_DVFS_ENABLED
    if(!init_mali_dvfs_staus())
        MALI_DEBUG_PRINT(1, ("mali_platform_init failed\n"));        
#endif
    MALI_SUCCESS;
}

_mali_osk_errcode_t mali_platform_deinit(_mali_osk_resource_type_t *type)
{
#if MALI_DVFS_ENABLED
    deinit_mali_dvfs_staus();
#endif
    MALI_SUCCESS;
}

_mali_osk_errcode_t mali_platform_powerdown(u32 cores)
{
    MALI_SUCCESS;
}

_mali_osk_errcode_t mali_platform_powerup(u32 cores)
{
    MALI_SUCCESS;
}

void mali_gpu_utilization_handler(u32 utilization)
{
#if MALI_DVFS_ENABLED
    if(!mali_dvfs_handler(utilization))
        MALI_DEBUG_PRINT(1,( "error on mali dvfs status in utilization\n"));
#endif
	MALI_DEBUG_PRINT( 1, ("==>PLATFORM mali400-pmm : utilization %d \% \n", utilization * 100 / 255 ) );
}

#if MALI_POWER_MGMT_TEST_SUITE
u32 pmu_get_power_up_down_info(void)
{
	return 4095;

}
#endif
