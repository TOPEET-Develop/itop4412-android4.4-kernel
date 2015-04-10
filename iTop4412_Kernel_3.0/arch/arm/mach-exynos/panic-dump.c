/* linux/arch/arm/mach-exynos4/panic-dump.c
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *		jun.ma@samsung.com:init version
 *		yang81.li@samsung.com 20120412: add sysfs interface to save log to a file, mempool managment , logcat parse
 * EXYNOS4 - 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/


#include <linux/bootmem.h>
#include <linux/proc_fs.h>
#include <mach/panic-dump.h>
#include <linux/memblock.h>
#include <linux/seq_file.h>
#include <asm/io.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/sysfs.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#define PANIC_FILE_NAME	"panic_info_dump"
//extern char * gp_log_buf ;

//static char panic_buf[PANIC_INFO_LENGTH*10];
//char * panic_log_buf =panic_buf;
// bool panic_enabled=0;
//extern void *cma_get_virt(dma_addr_t phys, dma_addr_t size, int noncached);
//#define PANIC_MEM_POOL_ADDR_VA	cma_get_virt(PANIC_MEM_POOL_ADDR_PA,PANIC_MEM_POOL_STEP,1)
//static char*  PANIC_MEM_POOL_ADDR_VA=NULL;

void panic_dump_info_set(void)
{
	volatile unsigned int info=__raw_readl(PANIC_INFO_ADDR);
	volatile unsigned int num=info & 0xffff;
	printk("panic_dump_info_set: 0x %x\n",info);
	if(((info>>16)& 0xffff)!= PANIC_SYMBOL){
		info=(1 | (PANIC_SYMBOL<<16));
				printk("first 0x%x\n",info);
		}
	else
		{
		printk("num is : 0x%x ,   num after is 0x%x, is %d (0x%x)\n",num ,(num +1),(num+0x1),(num+0x1));
		
		info=((num+1) | (PANIC_SYMBOL<<16));
		printk("second: 0x%x \n",info);
		}
	while(__raw_readl(PANIC_INFO_ADDR)!= info)
		__raw_writel(info,PANIC_INFO_ADDR);
	

	printk("info is : 0x%x \n",info);

	//printk("OK\n");
	//panic_enabled=1;
	//outer_cache.disable();


}
#if 0
char * panic_dump_kmsg_buffer(void)
{
	static char *buffer_head=NULL:
	if(buffer_head ==NULL){
		if(((info>>16)& 0xffff)!= PANIC_SYMBOL)
				buffer_head=PANIC_MEM_POOL_ADDR_VA;
		else
				buffer_head=PANIC_MEM_POOL_ADDR_VA+((info & 0xffff) %5)*PANIC_MEM_POOL_STEP;
		}
	return buffer_head+;
}
#endif
char * panic_dump_buffer(unsigned index)
{
	//printk("panic_dump_buffer\n");
	//static char*  PANIC_MEM_POOL_ADDR_VA;
	static char *buffer_head=NULL;
	if(buffer_head ==NULL){
		
		volatile unsigned int info=__raw_readl(PANIC_INFO_ADDR);
		//printk("info: 0x%x \n",info);
		if(((info>>16)& 0xffff)!= PANIC_SYMBOL)
				buffer_head=PANIC_MEM_POOL_ADDR_VA;
		else{
				unsigned int panic_num=info & 0xffff;
				buffer_head=PANIC_MEM_POOL_ADDR_VA+(panic_num%2)*PANIC_MEM_POOL_STEP;
			}

		memset(buffer_head,0,PANIC_MEM_POOL_STEP);


	}
	#if 0
	if(panic_enabled)
		{
		 return ioremap(PANIC_MEM_POOL_ADDR_PA,PANIC_MEM_POOL_STEP);
		}
	#endif
		
	return buffer_head/*+index*256*1024*/;
}

char * panic_logger_buffer(unsigned index)
{
	//printk("panic_dump_buffer\n");
	//static char*  PANIC_MEM_POOL_ADDR_VA;
	static char *buffer_head=NULL;
	if(buffer_head ==NULL){
		
		volatile unsigned int info=__raw_readl(PANIC_INFO_ADDR);
		//printk("info: 0x%x \n",info);
		if(((info>>16)& 0xffff)!= PANIC_SYMBOL)
				buffer_head=PANIC_MEM_POOL_LOGGER_ADDR_VA;
		else{
				unsigned int panic_num=info & 0xffff;
				buffer_head=PANIC_MEM_POOL_LOGGER_ADDR_VA+(panic_num%2)*PANIC_MEM_POOL_SIZE;
			}

		memset(buffer_head,0,PANIC_MEM_POOL_SIZE);


	}
	#if 0
	if(panic_enabled)
		{
		 return ioremap(PANIC_MEM_POOL_ADDR_PA,PANIC_MEM_POOL_STEP);
		}
	#endif
		
	return buffer_head+index*256*1024;
}
#if 0
void panic_info_dump_to_mem(void)
{
	//volatile void *regs=PANIC_INFO_DUMP_ADD_VA;

	//outer_cache.disable();
	//		__raw_writel(mode, S5P_INFORM5); //mj : factory reset mode 
	__raw_writel(PANIC_SYMBOL, PANIC_INFO_DUMP_ADD_VA);

	return;
	#if 0
	volatile void *regs=PANIC_INFO_DUMP_ADD;
//	int symbol=0;
//	char panic_num=0,current_num = 0;

//	outer_cache.disable();

//	regs=phys_to_virt(PANIC_INFO_DUMP_ADD);
	//symbol = *(int *)regs;
	//panic_num =(symbol>>4) & 0xF; //get the totall num
	//symbol = ((symbol>>8)&0xffffff);
	//printk(KERN_INFO "[mjdbg]cheecksymbol: %x PANIC_SYMBOL:%x \n", symbol,PANIC_SYMBOL);

	if((*(int *)regs) != PANIC_SYMBOL)
	{
	#if 0
		panic_num = 1;
		current_num = panic_num;
		symbol = ((PANIC_SYMBOL<<8)|(panic_num<<4)|(current_num));
	#else

		 (*(int *)regs) = PANIC_SYMBOL;
		//volatile int tmp =PANIC_SYMBOL;
		//memcpy(regs,&tmp,sizeof(int));
		//__raw_writel(PANIC_SYMBOL, phys_to_virt(PANIC_INFO_DUMP_ADD));

		printk("********SET!!********\n");
	printk("**********************************************************\n");
	printk(" panic_info_dump_to_mem SET(0x%x): 0x%x!!!\n",(int *)phys_to_virt(PANIC_INFO_DUMP_ADD),*(int *)regs);
	printk("**********************************************************\n");
		
	#endif
		//printk(KERN_INFO "[mjdbg]This is the %d panic:0x%x : 0x%x.\n", current_num,(int *)regs,*(int *)regs);
	}
	#if 0
	else
	{
		panic_num += 1;
		/* update the symbol in PANIC_INFO_DUMP_ADD */
		symbol = ((PANIC_SYMBOL<<8)|(panic_num<<4)|1);
		*(int *)regs = symbol;
		
		/* write the symbol */
		current_num = panic_num;
		symbol = ((PANIC_SYMBOL<<8)|(panic_num<<4)|(current_num));
		regs = regs + ((current_num-1) *PANIC_INFO_LENGTH );
		//printk(KERN_INFO "[mjdbg]MEM Check:0x%x : 0x%x.\n", (int *)regs,*(int *)regs);
	}
	
	*(int *)regs = symbol;
	#endif
	//printk(KERN_INFO "[mjdbg]This is the %d panic:0x%x : 0x%x.\n", current_num,(int *)regs,*(int *)regs);
	//char *flag="success\0";
	//char *dest;
	//regs=ioremap(0x50000000,0x100000);
	//*(int *)regs = PANIC_SYMBOL;
	//strcpy(dest, flag);
	
	/*save all information including the normal statsu*/
	//memcpy((0x50000000+0x4),gp_log_buf,1024);	//this can be used to trigger exception
	//***memcpy((regs+PANIC_INFO_DUMP_START_OFFSET),gp_log_buf,PANIC_INFO_LENGTH);
	/* only save the panic information*/
#endif
}
//#if 1
void panic_dump_test(void)
{
	void *regs;
	int symbol=0;
	char panic_num=0;
	
	regs=PANIC_INFO_DUMP_ADD_VA;//phys_to_virt(PANIC_INFO_DUMP_ADD);
	symbol = *(int *)regs;
	//panic_num =(symbol>>4) & 0xF;
	//symbol = ((symbol>>8)&0xffffff);
	__raw_writel(PANIC_SYMBOL, PANIC_INFO_DUMP_ADD_VA);
	
	printk(KERN_INFO "[mjdbg]MEM Check-final:0x%x : 0x%x.\n", (int *)regs,*(int *)regs);
	if((symbol == PANIC_SYMBOL)/*&&(panic_num>0)*/)
	{
		printk(KERN_INFO "[mjdbg]System recovery:0x%x : 0x%x.\n", (int *)regs,*(int *)regs);
	}
	else
	{
		//outer_cache.disable();
		panic("mjdbg78No init found.  Try passing init= option to kernel.");
	}

}
#endif

void panic_dump_test(void)
{
		unsigned int panic_num=0;
	unsigned int symbol=0;
	volatile unsigned int info=__raw_readl(PANIC_INFO_ADDR);
		symbol=(info>>16)& 0xffff;
	printk("**********panic_dump_test****************\n");
		if(symbol != PANIC_SYMBOL)
		{
			printk("There is no valid panic information in memory\n");
			//panic("test");
		}
		else
		{
			panic_num=info & 0xffff;
			printk("There are %d valid panic information in memory\n",panic_num);
		}
		printk("**************************\n");
}
void  reserve_panic_dump_area(void)
{
	#if 0
	if(reserve_bootmem(PANIC_INFO_DUMP_ADD,PANIC_INFO_AREA,BOOTMEM_EXCLUSIVE) != 0)
	{
		printk("reserve fail----\n");
	}
	else
	{
		printk("we reserve boot meme of 0x%s -->0x%s for PANIC---\n",PANIC_INFO_DUMP_ADD,(PANIC_INFO_DUMP_ADD+PANIC_INFO_AREA));
	}
	#else
	
	int ret = 0;
	printk("**************************\n");
	printk("reserve_panic_dump_area!!\n");
	printk("**************************\n");
	ret = memblock_reserve(PANIC_MEM_POOL_ADDR_PA,PANIC_MEM_POOL_SIZE);
	ret = memblock_reserve(PANIC_MEM_POOL_LOGGER_ADDR1_PA,PANIC_MEM_POOL_SIZE);
	ret = memblock_reserve(PANIC_MEM_POOL_LOGGER_ADDR2_PA,PANIC_MEM_POOL_SIZE);

	//PANIC_MEM_POOL_ADDR_VA=ioremap(PANIC_MEM_POOL_ADDR_PA,PANIC_MEM_POOL_STEP);
	//printk("OK: 0x %x!!\n",PANIC_MEM_POOL_ADDR_VA);
	#if 0
	if(ret !=0)
		printk("[Be Careful]Reserve PANIC MEM fail----\n");
	else
		printk("Reserve MEM of 0x%s -->0x%s for PANIC---\n",PANIC_MEM_POOL_ADDR_PA,(PANIC_MEM_POOL_ADDR_PA+PANIC_MEM_POOL_SIZE));
	
	#endif
	#endif

}
 
static int panicinfo_proc_show(struct seq_file *m, void *v)
{
		//void *regs;
		unsigned int symbol=0;
		//char panic_num=0;
		unsigned int panic_num=0;
		char *buffer_head=NULL;

		volatile unsigned int info=__raw_readl(PANIC_INFO_ADDR);
		symbol=(info>>16)& 0xffff;

		if(symbol != PANIC_SYMBOL)
		{
			seq_printf(m, "There is no valid panic information in memory\n");

		}
		else
		{
			panic_num=info & 0xffff;
			seq_printf(m,"There are %d valid panic information in memory\n",panic_num);
			if(panic_num==0){
				__raw_writel(0,PANIC_INFO_ADDR);
				BUG();
			}
		#if 1
		buffer_head=PANIC_MEM_POOL_ADDR_VA+((panic_num-1) %2)*PANIC_MEM_POOL_STEP;
		seq_printf(m, "*****************************************************\n");
		seq_printf(m,"PANIC SYMBOL:[panic buf: 0x %x] (current : 0x%x)\n", buffer_head,panic_dump_buffer(0));
		seq_printf(m,"*****************************************************\n");
		seq_printf(m, "<1>%s\n", buffer_head/*+1024*1024*/);
#else

		buffer_head=PANIC_MEM_POOL_LOGGER_ADDR_VA+((panic_num-1) %2)*PANIC_MEM_POOL_SIZE;
		seq_printf(m, "*****************************************************\n");
		seq_printf(m,"PANIC SYMBOL:[panic buf: 0x %x] (current : 0x%x)\n", buffer_head,panic_logger_buffer(0));
		seq_printf(m,"*****************************************************\n");
		seq_printf(m, "<1>%s\n", buffer_head/*+1024*1024*/);
#endif
		
		#if 0
				seq_printf(m, "*****************************************************\n");
						seq_printf(m, "*****************************************************\n");
		seq_printf(m, "<2>%s\n", buffer_head+64*1024/*+1024*1024*/);
				seq_printf(m, "*****************************************************\n");
						seq_printf(m, "*****************************************************\n");
		seq_printf(m, "<3>%s\n", buffer_head+64*1024*2);
						seq_printf(m, "*****************************************************\n");
						seq_printf(m, "*****************************************************\n");

		seq_printf(m, "<4>%s\n", buffer_head+64*1024*3);
						seq_printf(m, "*****************************************************\n");
						seq_printf(m, "*****************************************************\n");

		seq_printf(m, "<5>%s\n", buffer_head+64*1024*4);
		//	seq_printf(m, "%s\n", buffer_head/*+1024*1024*/);
		#endif
		}
		#if 0
	if(((info>>16)& 0xffff)!= PANIC_SYMBOL)
		info=(1 | (PANIC_SYMBOL<<16));
	else
		info=((info & 0xffff +1) | (PANIC_SYMBOL<<16));
	__raw_writel(info,PANIC_INFO_ADDR);


	
		//regs=phys_to_virt(PANIC_INFO_DUMP_ADD);
		symbol_bak=symbol = *(int *)regs;
		//panic_num =(symbol>>4) & 0xF;
		//symbol = ((symbol>>8)&0xffffff);
		
		/*
		for(i=0;i<PANIC_INFO_LENGTH;i++)
		{
			panic_buf[i] = *(char *)(regs+i);
		}*/
		//memcpy(panic_buf,(regs+PANIC_INFO_DUMP_START_OFFSET),PANIC_INFO_LENGTH);
		if(symbol == PANIC_SYMBOL)
		{
			seq_printf(m,"There are %d valid panic information in memory\n",panic_num);

		}
		else
		{
			seq_printf(m, "There is no valid panic information in memory\n");
		}
		#if 0
		seq_printf(m,"*****************************************************\n");
		seq_printf(m,"PANIC_INFO_DUMP_ADD:[0x%x]\n", PANIC_INFO_DUMP_ADD);
		seq_printf(m,"PANIC_INFO_AREA:[0x%x]\n", PANIC_INFO_AREA);
		seq_printf(m, "PANIC_INFO_DUMP_START_OFFSET:[0x%x]\n", PANIC_INFO_DUMP_START_OFFSET);
		seq_printf(m, "PANIC_SYMBOL:[0x%x]\n", PANIC_SYMBOL);
		seq_printf(m, "PANIC_INFO_LENGTH:[0x%x]\n", PANIC_INFO_LENGTH);
		seq_printf(m, "*****************************************************\n");
		#endif
		seq_printf(m, "*****************************************************\n");
		seq_printf(m,"PANIC SYMBOL:[%x]\n", symbol_bak);
		seq_printf(m,"*****************************************************\n");
		seq_printf(m, "%s\n", panic_log_buf);
		#endif
		return 0;
}


 static int panicinfo_proc_open(struct inode *inode, struct file *file)
{
	//printk(KERN_INFO "  panic dump  open: 0x%x!!!\n",(*(int *)phys_to_virt(PANIC_INFO_DUMP_ADD)));

	
	
	//symbol = *(int *)regs;
	//panic_num =(symbol>>4) & 0xF; //get the totall num
	//symbol = ((symbol>>8)&0xffffff);
	//printk(KERN_INFO "[mjdbg]cheecksymbol: %x PANIC_SYMBOL:%x \n", symbol,PANIC_SYMBOL);

	
	return single_open(file, panicinfo_proc_show, NULL);
}
int panicinfo_proc_write(struct seq_file *seq, const void *data, size_t len)
{
	if (seq->count + len < seq->size) {
		memcpy(seq->buf + seq->count, data, len);
		seq->count += len;
		return 0;
	}
	seq->count = seq->size;
	return -1;
}
static const struct file_operations panic_dump_fops = {
	.open		= panicinfo_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.write            = panicinfo_proc_write,
	.release	= single_release,
};
static ssize_t kmsg_ctrl_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
unsigned int symbol=0;
		//char panic_num=0;
		unsigned int panic_num=0;
		//char *buffer_head=NULL;

		volatile unsigned int info=__raw_readl(PANIC_INFO_ADDR);
		symbol=(info>>16)& 0xffff;

		if(symbol != PANIC_SYMBOL)
		{
			printk( "There is no valid panic information in memory\n");

		}
		else
		{
			panic_num=info & 0xffff;
				printk( "There are %d valid panic information in memory\n",panic_num);
			if(panic_num==0){
				__raw_writel(0,PANIC_INFO_ADDR);
				BUG();
			}
		
		//buffer_head=PANIC_MEM_POOL_ADDR_VA+((info & 0xffff-1) %2)*PANIC_MEM_POOL_STEP;
			}

return 0;
}

static int ksmg_write_data_to_file(char * mem,char *file,unsigned int size)
{
	//dma_addr_t phy_cpmem, vir_cpmem;
	struct file *fp;
        mm_segment_t fs;
	int ret = 0;
	
	/* File Open */
        fs = get_fs();
        set_fs(KERNEL_DS);
#if 0
	switch(nvm) {
	case CP_NVM_STATIC: /* 128KB */
		fp_nvm = filp_open(FILE_NVM_STATIC, O_RDWR, 0);	
		ret = vfs_write(fp_nvm, vir_cpmem + 0x1F80000, 0x20000, &fp_nvm->f_pos);
		break;
	case CP_NVM_DYNAMIC: /* 256KB */
		fp_nvm = filp_open(FILE_NVM_DYNAMIC, O_RDWR, 0);	
		ret = vfs_write(fp_nvm, vir_cpmem + 0x1FA0000, 0x40000, &fp_nvm->f_pos);
		break;
	case CP_NVM_CAL: /* 128KB */
		fp_nvm = filp_open(FILE_NVM_CAL, O_RDWR, 0);	
		ret = vfs_write(fp_nvm, vir_cpmem + 0x1FE0000, 0x20000, &fp_nvm->f_pos);
		break;
	default :
		dev_info(c2c_con.c2c_dev, "Wrong NVM Type!!!\n");
	}
	#else
		fp = filp_open(file, O_RDWR|O_CREAT, 0);	
	if(IS_ERR(fp)){
			printk("Sorry. Can't creat panic dump file\n");
			goto ERR;
		}

		ret = vfs_write(fp, mem, size, &fp->f_pos);
	#endif
	filp_close(fp, NULL);
	ERR:
	set_fs(fs);

//
	return ret;
}
#if 1
static int parse_logger_data_to_file(char * mem,char *file,unsigned int size);
#else
#define parse_logger_data_to_file ksmg_write_data_to_file
#endif
static ssize_t kmsg_ctrl_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
		unsigned int symbol=0;
		//char panic_num=0;
		unsigned int panic_num=0;
		char *buffer_head=NULL, *buffer_logger=NULL;
		int ops_num;

		volatile unsigned int info=__raw_readl(PANIC_INFO_ADDR);
		symbol=(info>>16)& 0xffff;

		if(symbol != PANIC_SYMBOL)
		{
				printk( "There is no valid panic information in memory\n");
				return count;

		}
		else
		{
			panic_num=info & 0xffff;
				printk( "There are %d valid panic information in memory\n",panic_num);
			if(panic_num==0){
				__raw_writel(0,PANIC_INFO_ADDR);
				BUG();
			}
		
			buffer_head=PANIC_MEM_POOL_ADDR_VA+((panic_num-1) %2)*PANIC_MEM_POOL_STEP;
			buffer_logger=PANIC_MEM_POOL_LOGGER_ADDR_VA+((panic_num-1) %2)*PANIC_MEM_POOL_SIZE;
		}



		sscanf(buf, "%d", &ops_num);	
		switch (ops_num) 
		{	
			case 1: //kmsg
				ksmg_write_data_to_file(buffer_head,"/data/kmsg_last.txt",PANIC_MEM_POOL_STEP);
				printk("kmsg wriiten OK !!\n");
				break;
			case 2: //logger main
				parse_logger_data_to_file(buffer_logger,"/data/logger_main_last.txt",PANIC_MEM_POOL_LOGGER_STEP);
				printk("logger main wriiten OK : 0x %x !!\n",buffer_logger);
				break;
			case 3: //logger event
				parse_logger_data_to_file(buffer_logger+256*1024,"/data/logger_event_last.txt",PANIC_MEM_POOL_LOGGER_STEP);
				printk("logger event wriiten OK !!\n");
				break;
			case 4: //logger radio
				parse_logger_data_to_file(buffer_logger+256*1024*2,"/data/logger_radio_last.txt",PANIC_MEM_POOL_LOGGER_STEP);
				printk("logger radio wriiten OK !!\n");
				break;
			case 5: //logger system
				parse_logger_data_to_file(buffer_logger+256*1024*3,"/data/logger_system_last.txt",PANIC_MEM_POOL_LOGGER_STEP);
				printk("logger system  wriiten OK !!\n");
				break;
			case 6: //all wriiten
				printk("starting to written all log msg to /data/  \n");
				ksmg_write_data_to_file(buffer_head,"/data/kmsg_last.txt",PANIC_MEM_POOL_STEP);
				printk("kmsg wriiten OK !!\n");
				parse_logger_data_to_file(buffer_logger,"/data/logger_main_last.txt",PANIC_MEM_POOL_LOGGER_STEP);
				printk("logger main wriiten OK !!\n");
				parse_logger_data_to_file(buffer_logger+PANIC_MEM_POOL_LOGGER_STEP,"/data/logger_event_last.txt",PANIC_MEM_POOL_LOGGER_STEP);
				printk("logger event wriiten OK !!\n");
				parse_logger_data_to_file(buffer_logger+PANIC_MEM_POOL_LOGGER_STEP*2,"/data/logger_radio_last.txt",PANIC_MEM_POOL_LOGGER_STEP);
				printk("logger radio wriiten OK !!\n");
				parse_logger_data_to_file(buffer_logger+PANIC_MEM_POOL_LOGGER_STEP*3,"/data/logger_system_last.txt",PANIC_MEM_POOL_LOGGER_STEP);
				printk("logger system  wriiten OK !!\n");
				break;
			default:
					printk("ehco 1 for kmsg, and 2 3 4 5 for logger main event radio system !!\n");
					break;

		}

		
		
	


	return count;
}
struct platform_device exynos_device_kmsg = {
	.name		= "samsung-kmsg",
	.id		= -1,

};
static DEVICE_ATTR(kmsg_ctrl, 0644, kmsg_ctrl_show, kmsg_ctrl_store);
int panic_file_create(void)
{
int err;
#if 0
		PanicFile = create_proc_entry(PANIC_FILE_NAME, S_IRUGO,NULL);   
		if (PanicFile==NULL)
			{
			remove_proc_entry(PANIC_FILE_NAME, NULL);
			printk(KERN_INFO "[mjdbg]creat the proc file fail.\n");
			//return -ENOMEM;
			}
		else
			{
			PanicFile->read_proc = exynos4_panic_read;
			}
#else
		proc_create(PANIC_FILE_NAME, 0, NULL, &panic_dump_fops);



struct platform_device *pdev=&exynos_device_kmsg;

platform_add_devices(&pdev, 1);

//struct device	kmsg_dev;
/* Create sysfs file for C2C debug */
	err = device_create_file(&pdev->dev, &dev_attr_kmsg_ctrl);
	if (err) {
		//dev_err(&pdev->dev, "Failed to create sysfs for C2C\n");
		//goto release_sscm_irq1;
		printk("panic_file create failed !!\n");
		while(1){printk("panic_file create failed !!\n");}
		return -1;
	}
	#if 0
	printk("panic_file create OK !!\n");
	printk("panic_file create OK !!\n");
	printk("panic_file create OK !!\n");
		printk("panic_file create OK !!\n");
	printk("panic_file create OK !!\n");
	printk("panic_file create OK !!\n");
		printk("panic_file create OK !!\n");
	printk("panic_file create OK !!\n");
	printk("panic_file create OK !!\n");
		printk("panic_file create OK !!\n");
	printk("panic_file create OK !!\n");
	#endif
	printk("panic_file create OK !!\n");
	

	
return 0;

#endif


}
#if 1
struct logger_entry {
	__u16		len;	/* length of the payload */
	__u16		__pad;	/* no matter what, we get 2 bytes of padding */
	__s32		pid;	/* generating process's pid */
	__s32		tid;	/* generating process's tid */
	__s32		sec;	/* seconds since Epoch */
	__s32		nsec;	/* nanoseconds */
	char		msg[0];	/* the entry's payload */
};


static int parse_logger_data_to_file(char * mem,char *file,unsigned int size)
{
	//dma_addr_t phy_cpmem, vir_cpmem;
	struct file *fp;
        mm_segment_t fs;
	int ret = 0;
	struct logger_entry *entry=NULL;
	volatile unsigned char * ptr=mem;

	/* File Open */
        fs = get_fs();
        set_fs(KERNEL_DS);

	fp = filp_open(file, O_RDWR|O_CREAT, 0);	
	if(IS_ERR(fp)){
			printk("Sorry. Can't creat panic dump file\n");
			goto ERR;
	}

	entry= (struct logger_entry *)ptr;
	if(entry->len==0)
		printk("len is 0!!!\n");
	while(1){
		if((entry->len==0)|| ((ptr+ sizeof(struct logger_entry)+entry->len)>(mem+PANIC_MEM_POOL_LOGGER_STEP)))
			break;
		ret = vfs_write(fp,ptr+ sizeof(struct logger_entry), entry->len, &fp->f_pos);
		ptr+=(sizeof(struct logger_entry)+entry->len);
		entry= (struct logger_entry *)ptr;
	}

	filp_close(fp, NULL);
	ERR:
	set_fs(fs);
//	cma_free(phy_cpmem);
//
	return ret;
}

#endif


