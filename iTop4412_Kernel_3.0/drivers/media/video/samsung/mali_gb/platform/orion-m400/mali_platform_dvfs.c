/*
 * Copyright (C) 2010 ARM Limited. All rights reserved.
 * 
 * This program is free software and is provided to you under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation, and any use by you of this program is subject to the terms of such GNU licence.
 * 
 * A copy of the licence is included with the program, and can also be obtained from Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * @file mali_platform_dvfs.c
 * Platform specific Mali driver dvfs functions
 */
 
#include "mali_kernel_common.h"
#include "mali_osk.h"
#include "mali_platform.h"

#include <linux/clk.h>
#include <linux/err.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>

#include <asm/io.h>

#ifdef CONFIG_S5PV310_ASV
#include <mach/asv.h>
#include <mach/regs-clock.h>
#endif

#include "mali_device_pause_resume.h"
#include <linux/workqueue.h>

#define MALI_DVFS_STEPS 2 // 4
#define MALI_DVFS_WATING 10 // msec
#define MALI_DVFS_STAY_AFTER_CHANGE 1 // stay count after clock change

#define MALI_DVFS_CLK_DEBUG 0
#define MALI_CLK_VERIFICATION 0
#define MALI_DVFS_PAUSE_RESUME_TEST 0
//#define MALI_DVFS_AGRESSIVE_POLICY

#if MALI_CLK_VERIFICATION
#define NUM_OF_TEST_LOOP 2
#endif

#if MALI_DVFS_PAUSE_RESUME_TEST // fast switch (only test)
	#define GPU_DVFS_UP_THRESHOLD    120 //((int)((255*50)/100))   // 50%
	#define GPU_DVFS_DOWN_THRESHOLD  90 //((int)((255*30)/100))   // 30%
#else
#ifdef MALI_DVFS_AGRESSIVE_POLICY
	#define GPU_DVFS_UP_THRESHOLD	((int)((255*55)/100))   // 55%
	#define GPU_DVFS_DOWN_THRESHOLD	((int)((255*25)/100))   // 25%
#else
	#define GPU_DVFS_UP_THRESHOLD	((int)((255*65)/100))   // 60%
	#define GPU_DVFS_DOWN_THRESHOLD	((int)((255*30)/100))   // 30%
#endif
#endif
static int bMaliDvfsRun=0;

typedef struct mali_dvfs_tableTag{
    unsigned int clock;
    unsigned int freq;
    unsigned int vol;        
}mali_dvfs_table;

typedef struct mali_dvfs_statusTag{
    unsigned int currentStep;
    mali_dvfs_table * pCurrentDvfs;

}mali_dvfs_status;

/*dvfs status*/
mali_dvfs_status maliDvfsStatus;
int mali_dvfs_control=0;

/*dvfs table*/

mali_dvfs_table mali_dvfs[MALI_DVFS_STEPS]={
/* For the worst-case, voltage table for the SS-corner(maximum voltage) is selected */
#ifdef CONFIG_CPU_S5PV310_EVT1
                   /*step 0*/{260  ,1000000    ,1100000},
                   /*step 1*/{330  ,1000000    ,1200000} };    
#else
		   /*step 0*/{260  ,1000000    ,1100000},
                   /*step 1*/{440  ,1000000    ,1200000} };    //330, yyd- 111028               
#endif                 

#ifdef CONFIG_S5PV310_ASV
static mali_bool asv_applied = MALI_FALSE;

mali_dvfs_table mali_dvfs_SS[MALI_DVFS_STEPS]={
                   /*step 0*/{260  ,1000000    ,1100000},
                   /*step 1*/{330  ,1000000    ,1200000} };
                         
mali_dvfs_table mali_dvfs_A[MALI_DVFS_STEPS]={
                   /*step 0*/{260  ,1000000    ,1100000},
                   /*step 1*/{330  ,1000000    ,1200000} };

mali_dvfs_table mali_dvfs_B[MALI_DVFS_STEPS]={
                   /*step 0*/{260  ,1000000    ,1100000},
                   /*step 1*/{330  ,1000000    ,1200000} };

mali_dvfs_table mali_dvfs_C[MALI_DVFS_STEPS]={
                   /*step 0*/{260  ,1000000    ,1100000},
                   /*step 1*/{330  ,1000000    ,1200000} };
                    
mali_dvfs_table mali_dvfs_D[MALI_DVFS_STEPS]={
                   /*step 0*/{260  ,1000000    ,1100000},
                   /*step 1*/{330  ,1000000    ,1200000} };
#endif   

static u32 mali_dvfs_utilization = 255;

static void mali_dvfs_work_handler(struct work_struct *w);

static struct workqueue_struct *mali_dvfs_wq = 0;
extern mali_io_address clk_register_map;

static DECLARE_WORK(mali_dvfs_work, mali_dvfs_work_handler);

static unsigned int get_mali_dvfs_staus(void)
{

//#ifdef CONFIG_REGULATOR
#if 0 //Robin Wang
#if MALI_CLK_VERIFICATION
    unsigned long clk_rate=0;
    int voltage=0;
#endif
#endif

#if MALI_CLK_VERIFICATION
    int stepIndex=0;
    unsigned int testLoop=NUM_OF_TEST_LOOP;
#endif

    /*set extra parameters here in the future
    */

#if MALI_CLK_VERIFICATION
    while(testLoop--)
    {

        /*loop tests for avoiding fluctuation*/

        /*get current clk rate and voltage*/
        clk_rate = mali_clk_get_rate();
        voltage = regulator_get_voltage(g3d_regulator);   

        for(stepIndex=0;stepIndex<MALI_DVFS_STEPS;stepIndex++)
        {
            if(mali_dvfs[stepIndex].vol ==voltage)
            {
                if(mali_dvfs[stepIndex].clock == clk_rate/mali_dvfs[stepIndex].freq)
                {
                    maliDvfsStatus.currentStep=stepIndex;
                    maliDvfsStatus.pCurrentDvfs=&mali_dvfs[stepIndex];
                    return maliDvfsStatus.currentStep;
                }
            }
        }
    }
    
    MALI_DEBUG_PRINT(1, ("[DVFS]invalid step in get-->reset to default step \n"));
    /*error handling for current status -> set default step*/
//#ifdef CONFIG_REGULATOR
#if 0 //Robin Wang
    /*change the voltage*/
    mali_regulator_set_voltage(mali_dvfs[MALI_DVFS_DEFAULT_STEP].vol, mali_dvfs[MALI_DVFS_DEFAULT_STEP].vol);
#endif
    /*change the clock*/
    mali_clk_set_rate(mali_dvfs[MALI_DVFS_DEFAULT_STEP].clock, mali_dvfs[MALI_DVFS_DEFAULT_STEP].freq);

	mali_clk_put();
	//clk_put(mali_parent_clock);
	//clk_put(mpll_clock);
	maliDvfsStatus.currentStep = MALI_DVFS_DEFAULT_STEP;
#endif /*MALI_CLK_VERIFICATION*/

	return maliDvfsStatus.currentStep;

}

static mali_bool set_mali_dvfs_staus(u32 step,mali_bool boostup)
{
    u32 validatedStep=step;
//#ifdef CONFIG_REGULATOR
#if 0 //Robin Wang
#if MALI_CLK_VERIFICATION
    unsigned long clk_rate=0;
    int voltage=0;
#endif
#endif
#if MALI_DVFS_CLK_DEBUG
    unsigned int *pRegMaliClkDiv;
    unsigned int *pRegMaliMpll;
#endif

#if MALI_CLK_VERIFICATION
    unsigned int testLoop=NUM_OF_TEST_LOOP;
#endif

//#ifdef CONFIG_REGULATOR
#if 0 //Robin Wang

#if 1
    if( mali_regulator_get_usecount()==0)
    {
        MALI_DEBUG_PRINT(1, ("regulator use_count is 0 \n"));
        return MALI_FALSE;
    }
#else
    int enabled=0;
    enabled = regulator_is_enabled(g3d_regulator);
    if(enabled < 0)
    {
        MALI_DEBUG_PRINT(1, ("regulator is enabled \n"));
    }
    else
    {
        mali_regulator_enable();
        MALI_DEBUG_PRINT(1, ("enable regulator\n"));    
    }
#endif
#endif

    if(boostup)
    {
//#ifdef CONFIG_REGULATOR
#if 0 //Robin Wang

        /*change the voltage*/
        mali_regulator_set_voltage(mali_dvfs[step].vol, mali_dvfs[step].vol);
#endif
        /*change the clock*/
        mali_clk_set_rate(mali_dvfs[step].clock, mali_dvfs[step].freq);
    }
    else
    {
        /*change the clock*/
        mali_clk_set_rate(mali_dvfs[step].clock, mali_dvfs[step].freq);
//#ifdef CONFIG_REGULATOR
#if 0 //Robin Wang

        /*change the voltage*/
        mali_regulator_set_voltage(mali_dvfs[step].vol, mali_dvfs[step].vol);
#endif        
    }

	mali_clk_put();
	//clk_put(mali_parent_clock);
	//clk_put(mpll_clock);
#if MALI_DVFS_CLK_DEBUG
    pRegMaliClkDiv = ioremap(0x1003c52c,32);
    pRegMaliMpll = ioremap(0x1003c22c,32);
    MALI_PRINT( ("Mali MPLL reg:%d, CLK DIV: %d \n",*pRegMaliMpll, *pRegMaliClkDiv));
#endif

#if MALI_CLK_VERIFICATION
    while(testLoop--)
    {
        /*loop tests for avoiding fluctuation*/    

        clk_rate = mali_clk_get_rate();
        voltage = regulator_get_voltage(g3d_regulator);   

        if((mali_dvfs[step].vol== voltage)||(mali_dvfs[step].clock== clk_rate/mali_dvfs[step].freq))
        { 
            maliDvfsStatus.currentStep = validatedStep;
            /*for future use*/
            maliDvfsStatus.pCurrentDvfs = &mali_dvfs[validatedStep];         
            return MALI_TRUE;
        }

    }

    MALI_DEBUG_PRINT(1, ("[DVFS]invalid step set dvfs -->reset to default step \n"));
    /*error handling for current status -> set default step*/
//#ifdef CONFIG_REGULATOR
#if 0 //Robin Wang

    /*change the voltage*/
    mali_regulator_set_voltage(mali_dvfs[MALI_DVFS_DEFAULT_STEP].vol, mali_dvfs[MALI_DVFS_DEFAULT_STEP].vol);
#endif
    /*change the clock*/
    mali_clk_set_rate(mali_dvfs[MALI_DVFS_DEFAULT_STEP].clock, mali_dvfs[MALI_DVFS_DEFAULT_STEP].freq);

    mali_clk_put();
    //clk_put(mali_parent_clock);
    //clk_put(mpll_clock);

    validatedStep = MALI_DVFS_DEFAULT_STEP;
#endif /*MALI_CLK_VERIFICATION*/

    maliDvfsStatus.currentStep = validatedStep;
    /*for future use*/
    maliDvfsStatus.pCurrentDvfs = &mali_dvfs[validatedStep]; 
    
    return MALI_TRUE;
}

static void mali_platform_wating(u32 msec)
{
    /*sample wating
    change this in the future with proper check routine.
    */
	unsigned int read_val;
	while(1)
	{
		read_val = _mali_osk_mem_ioread32(clk_register_map, 0x00);
		if ((read_val & 0x8000)==0x0000) break;
		
        _mali_osk_time_ubusydelay(100); // 1000 -> 100 : 20101218
	}
    /* _mali_osk_time_ubusydelay(msec*1000);*/
}

static mali_bool change_mali_dvfs_staus(u32 step, mali_bool boostup )
{

	MALI_DEBUG_PRINT(1, ("> change_mali_dvfs_staus: %d, %d \n",step, boostup));     
#if MALI_DVFS_PAUSE_RESUME_TEST
	MALI_PRINT( ("> mali_dev_pause\n"));
	if(mali_dev_pause())
	{
		MALI_DEBUG_PRINT(1, ("error on mali_dev_dvfs_pause in change_mali_dvfs_staus"));       
		return MALI_FALSE;   
	}    
	MALI_PRINT( ("< mali_dev_pause\n"));
#endif

    if(!set_mali_dvfs_staus(step, boostup))
    {
        MALI_DEBUG_PRINT(1, ("error on set_mali_dvfs_staus: %d, %d \n",step, boostup));     
        return MALI_FALSE;            
    }

    /*wait until clock and voltage is stablized*/
    mali_platform_wating(MALI_DVFS_WATING); /*msec*/

#if MALI_DVFS_PAUSE_RESUME_TEST
	MALI_PRINT( ("> mali_dev_resume\n"));
	if(mali_dev_resume())
	{
		MALI_DEBUG_PRINT(1, ("error on mali_dev_dvfs_resume in change_mali_dvfs_staus"));       
		return MALI_FALSE;       
	}
	MALI_PRINT( ("< mali_dev_resume\n"));
#endif
    return MALI_TRUE;  
}

static unsigned int decideNextStatus(unsigned int utilization)
{
    unsigned int level=0; // 0:stay, 1:up 
	if(!mali_dvfs_control)
	{
	    if( utilization>GPU_DVFS_UP_THRESHOLD && maliDvfsStatus.currentStep==0 )
	        level=1;
	    else if( utilization<GPU_DVFS_DOWN_THRESHOLD && maliDvfsStatus.currentStep==1 )
	        level=0;
	    else
	        level = maliDvfsStatus.currentStep;
	}
	else
	{
		if((1 == mali_dvfs_control)||(( mali_dvfs_control > 2) && (mali_dvfs_control < 161)))
		{
			level=0;
		}
		else 
		{
			level=1;
		}
	}
    return level;
}

#ifdef CONFIG_S5PV310_ASV

static mali_bool mali_dvfs_table_update(unsigned int asv_group)
{
    unsigned int i;
    for(i = 0 ; i < MALI_DVFS_STEPS ; i++) {
        switch(asv_group)
	    {
		    case 0:
		        mali_dvfs[i].vol = mali_dvfs_SS[i].vol;
		        break;
		    case 1:
		    case 2:
		        mali_dvfs[i].vol = mali_dvfs_A[i].vol;
		        break;
		    case 3:
		    case 4:
		        mali_dvfs[i].vol = mali_dvfs_B[i].vol;
		        break;
		    case 5:
		    case 6:
		        mali_dvfs[i].vol = mali_dvfs_C[i].vol;
		        break;
		    case 7:
		        mali_dvfs[i].vol = mali_dvfs_D[i].vol;
		        break;
		    default :
			    MALI_PRINT(("mali asv level is invalid %d", asv_group));
			    return MALI_FALSE;
	    }
	    MALI_PRINT(("ASV(%d) voltage_table[%d].mali_volt = %d\n",asv_group,
				i, mali_dvfs[i].vol));
	}

	return MALI_TRUE;
}
#endif

static mali_bool mali_dvfs_staus(u32 utilization)
{
	unsigned int nextStatus=0;
	unsigned int curStatus=0;
	mali_bool boostup=0;
#ifdef CONFIG_S5PV310_ASV
	static unsigned int tmp, asv_group=0;
#endif	
	static int stay_count =0; // to prevent frequent switch

	MALI_DEBUG_PRINT(1, ("> mali_dvfs_staus: %d \n",utilization));

#ifdef CONFIG_S5PV310_ASV
	if (asv_applied == MALI_FALSE)
	{
	    tmp = __raw_readl(S5P_INFORM2);
	    if((tmp >> ASV_ID_SHIFT)!= ASV_ID) {
	        printk(KERN_ERR "INFORM Register for ASV has invalid data(0x%x)\n",tmp);
	        return MALI_TRUE;
	    }
        asv_group = tmp & 0xf;
        printk(KERN_INFO "ASV group(%d) detect with MALI\n", asv_group);
		mali_dvfs_table_update(asv_group);
    	change_mali_dvfs_staus(0,0);
		asv_applied = MALI_TRUE;

		return MALI_TRUE; // first 3D DVFS with ASV -> just change the table and base setting.
	}
#endif

#if 1
    /*decide next step*/
    curStatus = get_mali_dvfs_staus();
    nextStatus = decideNextStatus(utilization);    

    MALI_DEBUG_PRINT(1, ("= curStatus %d, nextStatus %d, maliDvfsStatus.currentStep %d \n", curStatus, nextStatus, maliDvfsStatus.currentStep));
    /*if next status is same with current status, don't change anything*/
    if(curStatus!=nextStatus && stay_count==0)
	{
        /*check if boost up or not*/
        if(nextStatus > maliDvfsStatus.currentStep) boostup = 1;

        /*change mali dvfs status*/
        if(!change_mali_dvfs_staus(nextStatus,boostup))
        {
            MALI_DEBUG_PRINT(1, ("error on change_mali_dvfs_staus \n")); 
            return MALI_FALSE;               
        }
		stay_count = MALI_DVFS_STAY_AFTER_CHANGE;
    }
	else 
	{
		if( stay_count>0 )
			stay_count--;
	}
#endif
    return MALI_TRUE;
}



int mali_dvfs_is_running(void)
{
	return bMaliDvfsRun;  
}



void mali_dvfs_late_resume(void)
{
	// set the init clock as low when resume
	set_mali_dvfs_staus(0,0);  
}


static void mali_dvfs_work_handler(struct work_struct *w)
{
    bMaliDvfsRun=1;

    MALI_DEBUG_PRINT(3, ("=== mali_dvfs_work_handler\n")); 

    if(!mali_dvfs_staus(mali_dvfs_utilization))
        MALI_DEBUG_PRINT(1,( "error on mali dvfs status in mali_dvfs_work_handler"));

    bMaliDvfsRun=0;
}

mali_bool init_mali_dvfs_staus(int step)
{
    /*default status 
    add here with the right function to get initilization value.
    */
    if (!mali_dvfs_wq)                
        mali_dvfs_wq = create_singlethread_workqueue("mali_dvfs");        

    /*add a error handling here*/
    maliDvfsStatus.currentStep = step;
    return MALI_TRUE;
}

void deinit_mali_dvfs_staus(void)
{
    if (mali_dvfs_wq)                
        destroy_workqueue(mali_dvfs_wq);
    mali_dvfs_wq = NULL;
}

mali_bool mali_dvfs_handler(u32 utilization)
{
    mali_dvfs_utilization = utilization;
    queue_work_on(0, mali_dvfs_wq,&mali_dvfs_work);

    /*add error handle here*/
    return MALI_TRUE;
}


