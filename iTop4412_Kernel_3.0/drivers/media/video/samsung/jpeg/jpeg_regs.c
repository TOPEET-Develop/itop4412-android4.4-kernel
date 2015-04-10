/* linux/drivers/media/video/samsung/jpeg/jpeg_regs.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Register interface file for jpeg driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
#include <linux/io.h>
#include <plat/regs_jpeg.h>
#include <linux/delay.h>


#include "jpeg_regs.h"
#include "jpeg_conf.h"

unsigned int g_frame_width = 0;
unsigned int g_frame_height = 0;

void jpeg_sw_reset(void __iomem *base)
{
	unsigned int tmp;
	tmp = readl(base + S5P_JPEG_CNTL_REG);

	tmp &= ~(S5P_JPEG_SW_RESET_REG_ENABLE);
	writel(tmp, base + S5P_JPEG_CNTL_REG);
	mdelay(15);
	tmp |= (S5P_JPEG_SW_RESET_REG_ENABLE);
	writel(tmp, base + S5P_JPEG_CNTL_REG);

}

void jpeg_set_clk_power_on(void __iomem *base)
{
	//There is no this register @exynos4212
	
}

void jpeg_set_mode(void __iomem *base, int mode)
{

}

void jpeg_set_dec_out_fmt(void __iomem *base,
					enum jpeg_frame_format out_fmt)
{
	/* set jpeg deocde ouput format register */


}

void jpeg_set_enc_in_fmt(void __iomem *base,
					enum jpeg_frame_format in_fmt)
{
	if (in_fmt == YUV_422) {
		writel(readl(base + S5P_JPEG_IMAGE_FMT_REG) |
			(3<<0 | 4<<12), //YUV422, 3PLANE
			base + S5P_JPEG_IMAGE_FMT_REG);
		
	} else {
		printk("Only support the YUV_422 format\n");
	}

}

void jpeg_set_enc_out_fmt(void __iomem *base,
					enum jpeg_stream_format out_fmt)
{
	if (out_fmt == JPEG_422) {
		writel(readl(base + S5P_JPEG_IMAGE_FMT_REG) |
			(2<<24), //YCBCR 422
			base + S5P_JPEG_IMAGE_FMT_REG);
	} else {
		printk("Only support the YCBCR_422 format\n");
	}
}

void jpeg_set_enc_dri(void __iomem *base, unsigned int value)
{
	
}


void JPEG_SET_Table(void __iomem *base)
{
   u32 i;

   //QUAN_TABLE
   for (i=0; i<16; i++)
	   writel(ITU_Q_tbl[0][i],(base + S5P_JPEG_QUAN_TBL_ENTRY_REG+i*4));
   for (i=0; i<16; i++)
    	writel(ITU_Q_tbl[1][i],((base + S5P_JPEG_QUAN_TBL_ENTRY_REG+0x40)+i*4));
   for (i=0; i<16; i++)
	   writel(ITU_Q_tbl[2][i],((base + S5P_JPEG_QUAN_TBL_ENTRY_REG+0x80)+i*4));
   for (i=0; i<16; i++)
	   writel(ITU_Q_tbl[3][i],((base + S5P_JPEG_QUAN_TBL_ENTRY_REG+0xc0)+i*4));

   for (i=0; i<4; i++)
   		writel(ITU_H_tbl_len_DC_luminance[i],((base + S5P_JPEG_HUFF_TBL_ENTRY_REG)+i*4));
   for (i=0; i<3; i++)
   		writel(ITU_H_tbl_val_DC_luminance[i],((base + S5P_JPEG_HUFF_TBL_ENTRY_REG + 0x10)+i*4));
   for (i=0; i<4; i++)
   		writel(ITU_H_tbl_len_DC_chrominance[i],((base + S5P_JPEG_HUFF_TBL_ENTRY_REG + 0x20)+i*4));
   for (i=0; i<3; i++)
		writel(ITU_H_tbl_val_DC_chrominance[i],((base + S5P_JPEG_HUFF_TBL_ENTRY_REG + 0x30)+i*4));
   
   for (i=0; i<4; i++)
   		writel(ITU_H_tbl_len_AC_luminance[i],((base + S5P_JPEG_HUFF_TBL_ENTRY_REG + 0x40)+i*4));
   for (i=0; i<41; i++)
    	writel(ITU_H_tbl_val_AC_luminance[i],((base + S5P_JPEG_HUFF_TBL_ENTRY_REG + 0x50)+i*4));
   for (i=0; i<4; i++)
   		writel(ITU_H_tbl_len_AC_chrominance[i],((base + S5P_JPEG_HUFF_TBL_ENTRY_REG + 0x100)+i*4));
   for (i=0; i<41; i++)
   		writel(ITU_H_tbl_val_AC_chrominance[i],((base + S5P_JPEG_HUFF_TBL_ENTRY_REG + 0x110)+i*4));

}


void jpeg_set_enc_qtbl(void __iomem *base,
				enum  jpeg_img_quality_level level)
{
	/* set quantization table index for jpeg encode */
	unsigned int val;
	int i;

	JPEG_SET_Table(base);


	val = 0xc20;
	writel(val,base + S5P_JPEG_TB_SEL_REG);


	
}


void jpeg_huf_tbl_enable(void __iomem *base)
{
	unsigned int val;
	val = readl(base + S5P_JPEG_CNTL_REG);
	val &= ~(1<<19);
	val |= (1<<19); //gen huff table
	writel(val,base + S5P_JPEG_CNTL_REG);

}

void jpeg_set_enc_htbl(void __iomem *base)
{
	int i;

	/* set huffman table index for jpeg encode */

}

void jpeg_set_enc_coef(void __iomem *base)
{
	unsigned int val;
	val = 0x1fffffff;
	writel(val,base + S5P_JPEG_BITSTREAM_SIZE_REG);
	val = 0x0046f06f;
	writel(val,base + S5P_JPEG_PADDING_REG);

	val = 0x1a2;
	writel(val,base + S5P_JPEG_HUFF_CNT_REG);

}

void jpeg_set_frame_addr(void __iomem *base, unsigned int fra_addr)
{
	/* set the address of compressed input data */
	//printk("@@@ must know the plane num...\n");
	writel(fra_addr, base + S5P_JPEG_IMAGE_BA_PLANE_1_REG);
	//writel(fra_addr + g_frame_width *g_frame_height , base + S5P_JPEG_IMAGE_BA_PLANE_2_REG);
	//writel(fra_addr + g_frame_width *g_frame_height + g_frame_width *g_frame_height/2, base + S5P_JPEG_IMAGE_BA_PLANE_3_REG);
	
}

void jpeg_set_stream_addr(void __iomem *base, unsigned int str_addr)
{
	/* set the address of compressed input data */
	writel(str_addr, base + S5P_JPEG_OP_MEM_BA_REG);
}

void jpeg_get_frame_size(void __iomem *base,
			unsigned int *width, unsigned int *height)
{
	*width = readl(base + S5P_JPEG_IMAGE_SIZE_REG) & (0xffff);
	*height = (readl(base + S5P_JPEG_IMAGE_SIZE_REG) >>16) & (0xffff);
}

void jpeg_set_frame_size(void __iomem *base,
			unsigned int width, unsigned int height)
{
	/* Horizontal/Vertical resolution */
	writel(width |(height<<16) , base + S5P_JPEG_IMAGE_SIZE_REG);
	g_frame_width = width;
	g_frame_height = height;
}

enum jpeg_stream_format jpeg_get_stream_fmt(void __iomem *base)
{
	enum jpeg_stream_format		out_fmt;
	unsigned long			jpeg_mode;


	out_fmt = JPEG_422;

	return out_fmt;

}

unsigned int jpeg_get_stream_size(void __iomem *base)
{
	unsigned int size;

	size = readl(base + S5P_JPEG_BITSTREAM_SIZE_REG);

	return size;
}

void jpeg_start_decode(void __iomem *base)
{

}

int jpeg_debug(void __iomem *base)
{
	u32 cfg ;
#if 0	
	printk("----------------------jpeg----------------\n");
	cfg = readl(base + S5P_JPEG_CNTL_REG);
	printk(" S5P_JPEG_CNTL_REG =0x%x\n",cfg);

	cfg = readl(base + S5P_JPEG_INT_EN_REG);
	printk(" S5P_JPEG_INT_EN_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_OP_MEM_BA_REG);
	printk(" S5P_JPEG_OP_MEM_BA_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_IMAGE_SIZE_REG);
	printk(" S5P_JPEG_IMAGE_SIZE_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_IMAGE_BA_PLANE_1_REG);
	printk(" S5P_JPEG_IMAGE_BA_PLANE_1_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_IMAGE_SO_PLANE_1_REG);
	printk(" S5P_JPEG_IMAGE_SO_PLANE_1_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_IMAGE_PO_PLANE_1_REG);
	printk(" S5P_JPEG_IMAGE_PO_PLANE_1_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_IMAGE_BA_PLANE_2_REG);
	printk(" S5P_JPEG_IMAGE_BA_PLANE_2_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_IMAGE_SO_PLANE_2_REG);
	printk(" S5P_JPEG_IMAGE_SO_PLANE_2_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_IMAGE_PO_PLANE_2_REG);
	printk(" S5P_JPEG_IMAGE_PO_PLANE_2_REG =0x%x\n",cfg);




	cfg = readl(base + S5P_JPEG_IMAGE_BA_PLANE_3_REG);
	printk(" S5P_JPEG_IMAGE_BA_PLANE_3_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_IMAGE_SO_PLANE_3_REG);
	printk(" S5P_JPEG_IMAGE_SO_PLANE_3_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_IMAGE_PO_PLANE_3_REG);
	printk(" S5P_JPEG_IMAGE_PO_PLANE_3_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_TB_SEL_REG);
	printk(" S5P_JPEG_TB_SEL_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_IMAGE_FMT_REG);
	printk(" S5P_JPEG_IMAGE_FMT_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_BITSTREAM_SIZE_REG);
	printk(" S5P_JPEG_BITSTREAM_SIZE_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_PADDING_REG);
	printk(" S5P_JPEG_PADDING_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_HUFF_CNT_REG);
	printk(" S5P_JPEG_HUFF_CNT_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_FIFO_STATUS_REG);
	printk(" S5P_JPEG_FIFO_STATUS_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_DEC_IMAGE_SIZE_REG);
	printk(" S5P_JPEG_DEC_IMAGE_SIZE_REG =0x%x\n",cfg);
	cfg = readl(base + S5P_JPEG_DEC_IMAGE_FMT_REG);
	printk(" S5P_JPEG_DEC_IMAGE_FMT_REG =0x%x\n",cfg);

#endif
}	

void jpeg_start_encode(void __iomem *base)
{
	/* set jpeg interrupt */
	writel(readl(base + S5P_JPEG_INT_EN_REG) |0x1f,
			base + S5P_JPEG_INT_EN_REG);
	jpeg_debug(base);
	mdelay(1);
	/* start encoding */
	writel(	readl(base + S5P_JPEG_CNTL_REG)&(~0x3) | 0x2
			,
			base + S5P_JPEG_CNTL_REG);
}

unsigned int jpeg_get_int_status(void __iomem *base)
{
	unsigned int	int_status;
	unsigned int	status;

	int_status = readl(base + S5P_JPEG_INT_STATUS_REG);

	//do {
	//	status = readl(base + S5P_JPEG_OPR_REG);
	//} while (status);

	return int_status;
}

void jpeg_clear_int(void __iomem *base)
{
	//writel(S5P_JPEG_COM_INT_RELEASE, base + S5P_JPEG_COM_REG);
}

