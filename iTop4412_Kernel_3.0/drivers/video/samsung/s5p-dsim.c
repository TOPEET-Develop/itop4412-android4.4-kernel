/* linux/drivers/video/samsung/s5p-dsim.c
 *
 * Samsung MIPI-DSIM driver.
 *
 * InKi Dae, <inki.dae@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Modified by Samsung Electronics (UK) on May 2010
 *
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/clk.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/fb.h>
#include <linux/ctype.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/memory.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/regulator/consumer.h>
#include <linux/gpio.h>
#include <linux/pm_runtime.h>

#ifdef CONFIG_HAS_WAKELOCK
#include <linux/wakelock.h>
#include <linux/earlysuspend.h>
#include <linux/suspend.h>
#endif

#include <plat/clock.h>
#include <plat/regs-dsim.h>
#include <plat/gpio-cfg.h>

#include <mach/map.h>
#include <mach/dsim.h>
#include <mach/mipi_ddi.h>

#include "s5p-dsim.h"
#include "s5p_dsim_lowlevel.h"
#include "s3cfb.h"

/* Indicates the state of the device */
struct dsim_global {
	struct device *dev;
	struct clk *clock;
	/* VMIPI_1.1V */
	struct regulator *r_mipi_1_1v;
	/* VMIPI_1.8V */
	struct regulator *r_mipi_1_8v;

	struct s5p_platform_dsim *pd;
	struct dsim_config *dsim_info;
	struct dsim_lcd_config *dsim_lcd_info;
	/* lcd panel data. */
	struct s3cfb_lcd *lcd_panel_info;
	/* platform and machine specific data for lcd panel driver. */
	struct mipi_ddi_platform_data *mipi_ddi_pd;
	/* lcd panel driver based on MIPI-DSI. */
	struct mipi_lcd_driver *mipi_drv;

	unsigned int irq;
	unsigned int te_irq;
	unsigned int reg_base;

	unsigned char state;
	unsigned int data_lane;
	enum dsim_byte_clk_src e_clk_src;
	unsigned long hs_clk;
	unsigned long byte_clk;
	unsigned long escape_clk;
	unsigned char freq_band;

	char header_fifo_index[DSIM_HEADER_FIFO_SZ];
	#ifdef CONFIG_HAS_WAKELOCK
	struct early_suspend	early_suspend;
	struct wake_lock	idle_lock;
	#endif
};

struct mipi_lcd_info {
	struct list_head	list;
	struct mipi_lcd_driver	*mipi_drv;
};

static LIST_HEAD(lcd_info_list);
static DEFINE_MUTEX(mipi_lock);

static struct dsim_global dsim;

struct s5p_platform_dsim *to_dsim_plat(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);

	return (struct s5p_platform_dsim *)pdev->dev.platform_data;
}

unsigned char s5p_dsim_wr_data(unsigned int dsim_base,
	unsigned int data_id, unsigned int data0, unsigned int data1)
{
	unsigned char check_rx_ack = 0;

	if (dsim.state == DSIM_STATE_ULPS) {
		dev_err(dsim.dev, "state is ULPS.\n");
		return DSIM_FALSE;
	}
	switch (data_id) {
	/* short packet types of packet types for command. */
	case GEN_SHORT_WR_NO_PARA:
	case GEN_SHORT_WR_1_PARA:
	case GEN_SHORT_WR_2_PARA:
	case DCS_WR_NO_PARA:
	case DCS_WR_1_PARA:
	case SET_MAX_RTN_PKT_SIZE:
		s5p_dsim_wr_tx_header(dsim_base, (unsigned char) data_id,
			(unsigned char) data0, (unsigned char) data1);
		if (check_rx_ack)
			/* process response func  should be implemented */
			return DSIM_TRUE;
		else
			return DSIM_TRUE;

	/* general command */
	case CMD_OFF:
	case CMD_ON:
	case SHUT_DOWN:
	case TURN_ON:
		s5p_dsim_wr_tx_header(dsim_base, (unsigned char) data_id,
			(unsigned char) data0, (unsigned char) data1);
		if (check_rx_ack)
			/* process response func should be implemented. */
			return DSIM_TRUE;
		else
			return DSIM_TRUE;

	/* packet types for video data */
	case VSYNC_START:
	case VSYNC_END:
	case HSYNC_START:
	case HSYNC_END:
	case EOT_PKT:
		return DSIM_TRUE;

	/* short and response packet types for command */
	case GEN_RD_1_PARA:
	case GEN_RD_2_PARA:
	case GEN_RD_NO_PARA:
	case DCS_RD_NO_PARA:
		s5p_dsim_clear_interrupt(dsim_base, 0xffffffff);
		s5p_dsim_wr_tx_header(dsim_base, (unsigned char) data_id,
			(unsigned char) data0, (unsigned char) data1);
		/* process response func should be implemented. */
		return DSIM_FALSE;

	/* long packet type and null packet */
	case NULL_PKT:
	case BLANKING_PKT:
		return DSIM_TRUE;
	case GEN_LONG_WR:
	case DCS_LONG_WR:
		{
			u32 uCnt = 0;
			u32* pWordPtr = (u32 *)data0;
			do {
				s5p_dsim_wr_tx_data(dsim_base, pWordPtr[uCnt]);
			} while (((data1-1) / 4) > uCnt++);
		}

		/* put data into header fifo */
		s5p_dsim_wr_tx_header(dsim_base, (unsigned char)data_id,
			(unsigned char)(((unsigned short)data1) & 0xff),
			(unsigned char)((((unsigned short)data1) & 0xff00) >> 8));

		if (check_rx_ack)
			/* process response func should be implemented. */
			return DSIM_TRUE;
		else
			return DSIM_TRUE;

	/* packet typo for video data */
	case RGB565_PACKED:
	case RGB666_PACKED:
	case RGB666_LOOSLY:
	case RGB888_PACKED:
		if (check_rx_ack)
			/* process response func should be implemented. */
			return DSIM_TRUE;
		else
			return DSIM_TRUE;
	default:
		dev_warn(dsim.dev, "data id %x is not supported current DSI spec.\n", data_id);
		return DSIM_FALSE;
	}

	return DSIM_TRUE;
}

static void s5p_dsim_init_header_fifo(void)
{
	unsigned int cnt;

	for (cnt = 0; cnt < DSIM_HEADER_FIFO_SZ; cnt++)
		dsim.header_fifo_index[cnt] = -1;
	return;
}

unsigned char s5p_dsim_pll_on(unsigned int dsim_base, unsigned char enable)
{
	if (enable) {
		int sw_timeout = 1000;
		s5p_dsim_clear_interrupt(dsim_base, DSIM_PLL_STABLE);
		s5p_dsim_enable_pll(dsim_base, 1);
		while (1) {
			sw_timeout--;
			if (s5p_dsim_is_pll_stable(dsim_base))
				return DSIM_TRUE;
			if (sw_timeout == 0)
				return DSIM_FALSE;
		}
	} else
		s5p_dsim_enable_pll(dsim_base, 0);

	return DSIM_TRUE;
}

static unsigned long s5p_dsim_change_pll(unsigned int dsim_base, unsigned char pre_divider,
	unsigned short main_divider, unsigned char scaler)
{
	unsigned long dfin_pll, dfvco, dpll_out;
	unsigned char freq_band;
	unsigned char temp0, temp1;

	dfin_pll = (MIPI_FIN / pre_divider);

	if (dfin_pll < 6 * 1000 * 1000 || dfin_pll > 12 * 1000 * 1000) {
		dev_warn(dsim.dev, "warning!!\n");
		dev_warn(dsim.dev, "fin_pll range is 6MHz ~ 12MHz\n");
		dev_warn(dsim.dev, "fin_pll of mipi dphy pll is %luMHz\n",
				(dfin_pll / 1000000));

		s5p_dsim_enable_afc(dsim_base, 0, 0);
	} else {
		if (dfin_pll < 7 * 1000000)
			s5p_dsim_enable_afc(dsim_base, 1, 0x1);
		else if (dfin_pll < 8 * 1000000)
			s5p_dsim_enable_afc(dsim_base, 1, 0x0);
		else if (dfin_pll < 9 * 1000000)
			s5p_dsim_enable_afc(dsim_base, 1, 0x3);
		else if (dfin_pll < 10 * 1000000)
			s5p_dsim_enable_afc(dsim_base, 1, 0x2);
		else if (dfin_pll < 11 * 1000000)
			s5p_dsim_enable_afc(dsim_base, 1, 0x5);
		else
			s5p_dsim_enable_afc(dsim_base, 1, 0x4);
	}

	dfvco = dfin_pll * main_divider;
	dev_dbg(dsim.dev, "dfvco = %lu, dfin_pll = %lu, main_divider = %d\n",
		dfvco, dfin_pll, main_divider);
	if (dfvco < 500000000 || dfvco > 1000000000) {
		dev_warn(dsim.dev, "Caution!!\n");
		dev_warn(dsim.dev, "fvco range is 500MHz ~ 1000MHz\n");
		dev_warn(dsim.dev, "fvco of mipi dphy pll is %luMHz\n",
				(dfvco / 1000000));
	}

	dpll_out = dfvco / (1 << scaler);
	dev_dbg(dsim.dev, "dpll_out = %lu, dfvco = %lu, scaler = %d\n",
		dpll_out, dfvco, scaler);
	if (dpll_out < 100 * 1000000)
		freq_band = 0x0;
	else if (dpll_out < 120 * 1000000)
		freq_band = 0x1;
	else if (dpll_out < 170 * 1000000)
		freq_band = 0x2;
	else if (dpll_out < 220 * 1000000)
		freq_band = 0x3;
	else if (dpll_out < 270 * 1000000)
		freq_band = 0x4;
	else if (dpll_out < 320 * 1000000)
		freq_band = 0x5;
	else if (dpll_out < 390 * 1000000)
		freq_band = 0x6;
	else if (dpll_out < 450 * 1000000)
		freq_band = 0x7;
	else if (dpll_out < 510 * 1000000)
		freq_band = 0x8;
	else if (dpll_out < 560 * 1000000)
		freq_band = 0x9;
	else if (dpll_out < 640 * 1000000)
		freq_band = 0xa;
	else if (dpll_out < 690 * 1000000)
		freq_band = 0xb;
	else if (dpll_out < 770 * 1000000)
		freq_band = 0xc;
	else if (dpll_out < 870 * 1000000)
		freq_band = 0xd;
	else if (dpll_out < 950 * 1000000)
		freq_band = 0xe;
	else
		freq_band = 0xf;

	dev_dbg(dsim.dev, "freq_band = %d\n", freq_band);

	s5p_dsim_pll_freq(dsim_base, pre_divider, main_divider, scaler);
	temp0 = 0;
	s5p_dsim_hs_zero_ctrl(dsim_base, temp0);
	temp1 = 0;
	s5p_dsim_prep_ctrl(dsim_base, temp1);

	/* Freq Band */
	s5p_dsim_pll_freq_band(dsim_base, freq_band);

	/* Stable time */
	s5p_dsim_pll_stable_time(dsim_base, dsim.dsim_info->pll_stable_time);

	/* Enable PLL */
	dev_dbg(dsim.dev, "FOUT of mipi dphy pll is %luMHz\n",
			(dpll_out / 1000000));

	return dpll_out;
}

static void s5p_dsim_set_clock(unsigned int dsim_base,
	unsigned char byte_clk_sel, unsigned char enable)
{
	unsigned int esc_div;
	unsigned long esc_clk_error_rate;

	if (enable) {
		dsim.e_clk_src = byte_clk_sel;

		/* Escape mode clock and byte clock source */
		s5p_dsim_set_byte_clock_src(dsim_base, byte_clk_sel);

		/* DPHY, DSIM Link : D-PHY clock out */
		if (byte_clk_sel == DSIM_PLL_OUT_DIV8) {
			dsim.hs_clk = s5p_dsim_change_pll(dsim_base,
					dsim.dsim_info->p, dsim.dsim_info->m,
					dsim.dsim_info->s);
			dsim.byte_clk = dsim.hs_clk / 8;
			s5p_dsim_enable_pll_bypass(dsim_base, 0);
			s5p_dsim_pll_on(dsim_base, 1);
		/* DPHY : D-PHY clock out, DSIM link : external clock out */
		} else if (byte_clk_sel == DSIM_EXT_CLK_DIV8)
			dev_warn(dsim.dev, "this project is not supported "
				"external clock source for MIPI DSIM\n");
		else if (byte_clk_sel == DSIM_EXT_CLK_BYPASS)
			dev_warn(dsim.dev, "this project is not supported "
				"external clock source for MIPI DSIM\n");

		/* escape clock divider */
		esc_div = dsim.byte_clk / (dsim.dsim_info->esc_clk);
		dev_dbg(dsim.dev, "esc_div = %d, byte_clk = %lu, "
				"esc_clk = %lu\n",
			esc_div, dsim.byte_clk, dsim.dsim_info->esc_clk);
		if ((dsim.byte_clk / esc_div) >= 20000000 ||
			(dsim.byte_clk / esc_div) > dsim.dsim_info->esc_clk)
			esc_div += 1;

		dsim.escape_clk = dsim.byte_clk / esc_div;
		dev_dbg(dsim.dev, "escape_clk = %lu, byte_clk = %lu, "
				"esc_div = %d\n",
			dsim.escape_clk, dsim.byte_clk, esc_div);

		/*
		 * enable escclk on lane
		 */
		s5p_dsim_enable_byte_clock(dsim_base, DSIM_TRUE);

		/* enable byte clk and escape clock */
		s5p_dsim_set_esc_clk_prs(dsim_base, 1, esc_div);
		/* escape clock on lane */
		s5p_dsim_enable_esc_clk_on_lane(dsim_base, (DSIM_LANE_CLOCK | dsim.data_lane), 1);

		dev_dbg(dsim.dev, "byte clock is %luMHz\n",
				(dsim.byte_clk / 1000000));
		dev_dbg(dsim.dev, "escape clock that user's need is %lu\n",
				(dsim.dsim_info->esc_clk / 1000000));
		dev_dbg(dsim.dev, "escape clock divider is %x\n", esc_div);
		dev_dbg(dsim.dev, "escape clock is %luMHz\n",
				((dsim.byte_clk / esc_div) / 1000000));

		if ((dsim.byte_clk / esc_div) > dsim.escape_clk) {
			esc_clk_error_rate =
				dsim.escape_clk / (dsim.byte_clk / esc_div);
			dev_warn(dsim.dev, "error rate is %lu over.\n",
					(esc_clk_error_rate / 100));
		} else if ((dsim.byte_clk / esc_div) < (dsim.escape_clk)) {
			esc_clk_error_rate =
				(dsim.byte_clk / esc_div) / dsim.escape_clk;
			dev_warn(dsim.dev, "error rate is %lu under.\n",
					(esc_clk_error_rate / 100));
		}
	} else {
		s5p_dsim_enable_esc_clk_on_lane(dsim_base,
				(DSIM_LANE_CLOCK | dsim.data_lane), 0);
		s5p_dsim_set_esc_clk_prs(dsim_base, 0, 0);

		s5p_dsim_enable_byte_clock(dsim_base, DSIM_FALSE);

		if (byte_clk_sel == DSIM_PLL_OUT_DIV8)
			s5p_dsim_pll_on(dsim_base, 0);
	}
}

static int s5p_dsim_late_resume_init_dsim(unsigned int dsim_base)
{
	if (dsim.pd->init_d_phy)
		dsim.pd->init_d_phy(dsim.reg_base);

	if (dsim.pd->cfg_gpio)
		dsim.pd->cfg_gpio();

	dsim.state = DSIM_STATE_RESET;

	switch (dsim.dsim_info->e_no_data_lane) {
	case DSIM_DATA_LANE_1:
		dsim.data_lane = DSIM_LANE_DATA0;
		break;
	case DSIM_DATA_LANE_2:
		dsim.data_lane = DSIM_LANE_DATA0 | DSIM_LANE_DATA1;
		break;
	case DSIM_DATA_LANE_3:
		dsim.data_lane = DSIM_LANE_DATA0 | DSIM_LANE_DATA1 |
			DSIM_LANE_DATA2;
		break;
	case DSIM_DATA_LANE_4:
		dsim.data_lane = DSIM_LANE_DATA0 | DSIM_LANE_DATA1 |
			DSIM_LANE_DATA2 | DSIM_LANE_DATA3;
		break;
	default:
		dev_info(dsim.dev, "data lane is invalid.\n");
		return -1;
	};

	s5p_dsim_init_header_fifo();
	s5p_dsim_sw_reset(dsim_base);
	s5p_dsim_dp_dn_swap(dsim_base, dsim.dsim_info->e_lane_swap);

	/* enable only frame done interrupt */
	/* s5p_dsim_clear_interrupt(dsim_base, AllDsimIntr); */
	s5p_dsim_set_interrupt_mask(dsim.reg_base, AllDsimIntr, 1);

	return 0;
}

static int s5p_dsim_init_dsim(unsigned int dsim_base)
{
	if (dsim.pd->init_d_phy)
		dsim.pd->init_d_phy(dsim.reg_base);

	if (dsim.pd->cfg_gpio)
		dsim.pd->cfg_gpio();

	dsim.state = DSIM_STATE_RESET;

	switch (dsim.dsim_info->e_no_data_lane) {
	case DSIM_DATA_LANE_1:
		dsim.data_lane = DSIM_LANE_DATA0;
		break;
	case DSIM_DATA_LANE_2:
		dsim.data_lane = DSIM_LANE_DATA0 | DSIM_LANE_DATA1;
		break;
	case DSIM_DATA_LANE_3:
		dsim.data_lane = DSIM_LANE_DATA0 | DSIM_LANE_DATA1 |
			DSIM_LANE_DATA2;
		break;
	case DSIM_DATA_LANE_4:
		dsim.data_lane = DSIM_LANE_DATA0 | DSIM_LANE_DATA1 |
			DSIM_LANE_DATA2 | DSIM_LANE_DATA3;
		break;
	default:
		dev_info(dsim.dev, "data lane is invalid.\n");
		return -1;
	};

	s5p_dsim_init_header_fifo();
	/* s5p_dsim_sw_reset(dsim_base); */
	s5p_dsim_dp_dn_swap(dsim_base, dsim.dsim_info->e_lane_swap);

	/* enable only frame done interrupt */
	/* s5p_dsim_clear_interrupt(dsim_base, AllDsimIntr); */
	s5p_dsim_set_interrupt_mask(dsim.reg_base, AllDsimIntr, 1);

	return 0;
}

static void s5p_dsim_set_display_mode(unsigned int dsim_base,
	struct dsim_lcd_config *main_lcd, struct dsim_lcd_config *sub_lcd)
{
	struct s3cfb_lcd *main_lcd_panel_info = NULL, *sub_lcd_panel_info = NULL;
	struct s3cfb_lcd_timing *main_timing = NULL;

	if (main_lcd != NULL) {
		if (main_lcd->lcd_panel_info != NULL) {
			main_lcd_panel_info =
				(struct s3cfb_lcd *) main_lcd->lcd_panel_info;

			s5p_dsim_set_main_disp_resol(dsim_base,
				main_lcd_panel_info->height,
				main_lcd_panel_info->width);
		} else
			dev_warn(dsim.dev, "lcd panel info of main lcd is NULL.\n");
	} else {
		dev_err(dsim.dev, "main lcd is NULL.\n");
		return;
	}

	/* in case of VIDEO MODE (RGB INTERFACE) */
	if (dsim.dsim_lcd_info->e_interface == (u32) DSIM_VIDEO) {

		main_timing = &main_lcd_panel_info->timing;
		if (main_timing == NULL) {
			dev_err(dsim.dev, "main_timing is NULL.\n");
			return;
		}

		/* if (dsim.dsim_info->auto_vertical_cnt == DSIM_FALSE) */
		{
			s5p_dsim_set_main_disp_vporch(dsim_base,
				main_timing->cmd_allow_len,
				main_timing->v_fp, (u16) main_timing->v_bp);
			s5p_dsim_set_main_disp_hporch(dsim_base,
				main_timing->h_fp, (u16) main_timing->h_bp);
			s5p_dsim_set_main_disp_sync_area(dsim_base,
				main_timing->v_sw, (u16) main_timing->h_sw);
		}
	/* in case of COMMAND MODE (CPU or I80 INTERFACE) */
	} else {
		if (sub_lcd != NULL) {
			if (sub_lcd->lcd_panel_info != NULL) {
				sub_lcd_panel_info =
					(struct s3cfb_lcd *)
						sub_lcd->lcd_panel_info;

				s5p_dsim_set_sub_disp_resol(dsim_base,
					sub_lcd_panel_info->height,
					sub_lcd_panel_info->width);
			} else
				dev_warn(dsim.dev, "lcd panel info of sub lcd is NULL.\n");
		}
	}

	s5p_dsim_display_config(dsim_base, dsim.dsim_lcd_info, NULL);
}

static int s5p_dsim_init_link(unsigned int dsim_base)
{
	unsigned int time_out = 100;

	switch (dsim.state) {
	case DSIM_STATE_RESET:
		s5p_dsim_sw_reset(dsim_base);
	case DSIM_STATE_INIT:
		s5p_dsim_init_fifo_pointer(dsim_base, 0x0);
		mdelay(10);
		s5p_dsim_init_fifo_pointer(dsim_base, 0x1f);

		/* dsi configuration */
		s5p_dsim_init_config(dsim_base, dsim.dsim_lcd_info,
				NULL, dsim.dsim_info);
		s5p_dsim_enable_lane(dsim_base, DSIM_LANE_CLOCK, 1);
		s5p_dsim_enable_lane(dsim_base, dsim.data_lane, 1);

		/* set clock configuration */
		s5p_dsim_set_clock(dsim_base, dsim.dsim_info->e_byte_clk, 1);

		/* check clock and data lane state is stop state */
		while (!(s5p_dsim_is_lane_state(dsim_base, DSIM_LANE_CLOCK)
				== DSIM_LANE_STATE_STOP) &&
			!(s5p_dsim_is_lane_state(dsim_base, dsim.data_lane)
				== DSIM_LANE_STATE_STOP)) {
			time_out--;
			if (time_out == 0) {
				dev_info(dsim.dev, "DSI Master state is not "
						"stop state!!!\n");
				dev_info(dsim.dev, "Please check "
						"initialization process\n");

				return DSIM_FALSE;
			}
		}

		dsim.state = DSIM_STATE_STOP;

		/* BTA sequence counters */
		s5p_dsim_set_stop_state_counter(dsim_base,
				dsim.dsim_info->stop_holding_cnt);
		s5p_dsim_set_bta_timeout(dsim_base,
				dsim.dsim_info->bta_timeout);
		s5p_dsim_set_lpdr_timeout(dsim_base,
				dsim.dsim_info->rx_timeout);

		/* default LPDT by both cpu and lcd controller */
		s5p_dsim_set_data_mode(dsim_base, DSIM_TRANSFER_BOTH,
				DSIM_STATE_STOP);

		return DSIM_TRUE;
	default:
		dev_info(dsim.dev, "DSI Master is already init.\n");

		return DSIM_FALSE;
	}
}

unsigned char s5p_dsim_set_hs_enable(unsigned int dsim_base)
{
	u8 ret =  DSIM_FALSE;

	if (dsim.state == DSIM_STATE_STOP) {
		if (dsim.e_clk_src != DSIM_EXT_CLK_BYPASS) {
			dsim.state = DSIM_STATE_HSCLKEN;
			s5p_dsim_set_data_mode(dsim_base, DSIM_TRANSFER_BOTH,
				DSIM_STATE_HSCLKEN);
			s5p_dsim_enable_hs_clock(dsim_base, 1);

			ret = DSIM_TRUE;
		} else
			dev_warn(dsim.dev, "clock source is external bypass.\n");
	} else
		dev_warn(dsim.dev, "DSIM is not stop state.\n");

	return ret;
}

#if 0
static unsigned char s5p_dsim_set_stopstate(unsigned int dsim_base)
{
	u8 ret =  DSIM_FALSE;

	if (dsim.state == DSIM_STATE_HSCLKEN) {
		if (dsim.e_clk_src != DSIM_EXT_CLK_BYPASS) {
			dsim.state = DSIM_STATE_STOP;
			s5p_dsim_enable_hs_clock(dsim_base, 0);
			ret = DSIM_TRUE;
		} else
			dev_warn(dsim.dev, "clock source is external bypass.\n");
	} else if (dsim.state == DSIM_STATE_ULPS) {
		/* will be update for exiting ulps */
		ret = DSIM_TRUE;
	} else if (dsim.state == DSIM_STATE_STOP) {
		dev_warn(dsim.dev, "DSIM is already stop state.\n");
		ret = DSIM_TRUE;
	} else
		dev_warn(dsim.dev, "DSIM is not stop state.\n");

	return ret;
}
#endif
static unsigned char s5p_dsim_set_data_transfer_mode(unsigned int dsim_base,
	unsigned char data_path, unsigned char hs_enable)
{
	u8 ret = DSIM_FALSE;

	if (hs_enable) {
		if (dsim.state == DSIM_STATE_HSCLKEN) {
			s5p_dsim_set_data_mode(dsim_base, data_path, DSIM_STATE_HSCLKEN);
			ret = DSIM_TRUE;
		} else {
			dev_err(dsim.dev, "HS Clock lane is not enabled.\n");
			ret = DSIM_FALSE;
		}
	} else {
		if (dsim.state == DSIM_STATE_INIT || dsim.state == DSIM_STATE_ULPS) {
			dev_err(dsim.dev, "DSI Master is not STOP or HSDT state.\n");
			ret = DSIM_FALSE;
		} else {
			s5p_dsim_set_data_mode(dsim_base, data_path, DSIM_STATE_STOP);
			ret = DSIM_TRUE;
		}
	}

	return ret;
}

#if 0
static irqreturn_t s5p_dsim_interrupt_handler(int irq, void *dev_id)
{
	u32 intsrc = 0;

	disable_irq(irq);

	intsrc = readl(dsim.reg_base + S5P_DSIM_INTSRC);

	s5p_dsim_set_interrupt_mask(dsim.reg_base, 0xffffffff, 1);
	s5p_dsim_clear_interrupt(dsim.reg_base, 0x1000000);
	s5p_dsim_set_interrupt_mask(dsim.reg_base, 0x1000000, 0);

	enable_irq(irq);

	return IRQ_HANDLED;
}
#endif

int s5p_dsim_register_lcd_driver(struct mipi_lcd_driver *lcd_drv)
{
	struct mipi_lcd_info	*lcd_info = NULL;

	lcd_info = kmalloc(sizeof(struct mipi_lcd_info), GFP_KERNEL);
	if (lcd_info == NULL)
		return -ENOMEM;

	lcd_info->mipi_drv = kmalloc(sizeof(struct mipi_lcd_driver), GFP_KERNEL);
	if (lcd_info->mipi_drv == NULL)
		return -ENOMEM;


	memcpy(lcd_info->mipi_drv, lcd_drv, sizeof(struct mipi_lcd_driver));

	mutex_lock(&mipi_lock);
	list_add_tail(&lcd_info->list, &lcd_info_list);
	mutex_unlock(&mipi_lock);

	return 0;
}

struct mipi_lcd_driver *scan_mipi_driver(const char *name)
{
	struct mipi_lcd_info *lcd_info;
	struct mipi_lcd_driver *mipi_drv = NULL;

	mutex_lock(&mipi_lock);

	dev_dbg(dsim.dev, "find lcd panel driver(%s).\n",
		name);

	list_for_each_entry(lcd_info, &lcd_info_list, list) {
		mipi_drv = lcd_info->mipi_drv;

		if ((strcmp(mipi_drv->name, name)) == 0) {
			mutex_unlock(&mipi_lock);
			dev_dbg(dsim.dev, "found!!!(%s).\n", mipi_drv->name);
			return mipi_drv;
		}
	}

	dev_warn(dsim.dev, "failed to find lcd panel driver(%s).\n",
		name);

	mutex_unlock(&mipi_lock);

	return NULL;
}

#ifdef CONFIG_HAS_EARLYSUSPEND
void s5p_dsim_early_suspend(struct early_suspend *h)
{
	pr_err("[DSIM][%s] \n", __func__);

	dsim.mipi_ddi_pd->resume_complete = 0;

	if (dsim.mipi_drv->suspend)
		dsim.mipi_drv->suspend();

	clk_disable(dsim.clock);

	if (dsim.pd->mipi_power)
		dsim.pd->mipi_power(0);

	msleep(100);

#ifdef CONFIG_EXYNOS_DEV_PD
	/* disable the power domain */
	pm_runtime_put(dsim.dev);
#endif
}

irqreturn_t s5p_dsim_intr(struct platform_device *pdev)
{
	u32 intr;
	u32 dsim_clkcon;
	disable_irq(IRQ_MIPIDSI0);
	intr = readl(dsim.reg_base + S5P_DSIM_INTSRC) & ~(readl(dsim.reg_base + S5P_DSIM_INTMSK));

	/* frame done */
	if (intr & (FrameDone)) {
		writel(FrameDone, dsim.reg_base + S5P_DSIM_INTSRC);
		dsim_clkcon = readl(dsim.reg_base + S5P_DSIM_CLKCTRL) & ~(1 << 31);
		writel(dsim_clkcon, dsim.reg_base + S5P_DSIM_CLKCTRL);
	} else if (intr & ErrDsimIntr) { /* all of error interttup of dsim */
		writel((1 << 16), dsim.reg_base + S5P_DSIM_SWRST);
	} else if (intr & SwRstRelease) {
		writel(SwRstRelease, dsim.reg_base + S5P_DSIM_INTSRC);
		dsim_clkcon = readl(dsim.reg_base + S5P_DSIM_CLKCTRL) | (1 << 31);
		writel(dsim_clkcon, dsim.reg_base + S5P_DSIM_CLKCTRL);
	} else if (intr & (SFRFifoEmpty | PllStable)) {
		writel((SFRFifoEmpty | PllStable), dsim.reg_base + S5P_DSIM_INTSRC);
	} else {
		/* others */
	}
	enable_irq(IRQ_MIPIDSI0);
	return IRQ_HANDLED;
}

void s5p_dsim_late_resume(struct early_suspend *h)
{
	pr_err("[DSIM][%s] \n", __func__);

#ifdef CONFIG_EXYNOS_DEV_PD
	/* enable the power domain */
	pm_runtime_get_sync(dsim.dev);
#endif
	/* MIPI SIGNAL ON */
	if (dsim.pd->mipi_power)
		dsim.pd->mipi_power(1);

	/* reset lcd */
	dsim.mipi_ddi_pd->lcd_reset();

	mdelay(10);

	clk_enable(dsim.clock);

	mdelay(5);

	s5p_dsim_late_resume_init_dsim(dsim.reg_base);
	s5p_dsim_init_link(dsim.reg_base);

	s5p_dsim_set_hs_enable(dsim.reg_base);
	s5p_dsim_set_data_transfer_mode(dsim.reg_base, DSIM_TRANSFER_BYCPU, 1);

	s5p_dsim_set_display_mode(dsim.reg_base, dsim.dsim_lcd_info, NULL);

	s5p_dsim_set_data_transfer_mode(dsim.reg_base, DSIM_TRANSFER_BYLCDC, 1);

	s5p_dsim_set_interrupt_mask(dsim.reg_base, AllDsimIntr, 0);

	dsim.mipi_ddi_pd->resume_complete = 1;

	mdelay(10);

	/* initialize lcd panel */
	if (dsim.mipi_drv->init)
		dsim.mipi_drv->init();
	else
		dev_warn(dsim.dev, "init func is null.\n");
}

#else
#ifdef CONFIG_PM
int s5p_dsim_suspend(struct platform_device *pdev, pm_message_t state)
{
	dsim.mipi_ddi_pd->resume_complete = 0;

	if (dsim.mipi_drv->suspend)
		dsim.mipi_drv->suspend(&pdev->dev, state);

	clk_disable(dsim.clock);

	if (dsim.pd->mipi_power)
		dsim.pd->mipi_power(0);

	return 0;
}

int s5p_dsim_resume(struct platform_device *pdev)
{
	if (dsim.pd->mipi_power)
		dsim.pd->mipi_power(1);

	/* reset lcd */
	dsim.mipi_ddi_pd->lcd_reset();

	mdelay(10);

	clk_enable(dsim.clock);

	if (dsim.mipi_drv->resume)
		dsim.mipi_drv->resume(&pdev->dev);

	s5p_dsim_init_dsim(dsim.reg_base);
	s5p_dsim_init_link(dsim.reg_base);

	s5p_dsim_set_hs_enable(dsim.reg_base);
	s5p_dsim_set_data_transfer_mode(dsim.reg_base, DSIM_TRANSFER_BYCPU, 1);

	msleep(120);

	/* initialize lcd panel */
	if (dsim.mipi_drv->init)
		dsim.mipi_drv->init(&pdev->dev);
	else
		dev_warn(&pdev->dev, "init func is null.\n");

	s5p_dsim_set_display_mode(dsim.reg_base, dsim.dsim_lcd_info, NULL);

	s5p_dsim_set_data_transfer_mode(dsim.reg_base, DSIM_TRANSFER_BYLCDC, 1);

	dsim.mipi_ddi_pd->resume_complete = 1;
	return 0;
}
#else
#define s5p_dsim_suspend NULL
#define s5p_dsim_resume NULL
#endif
#endif

static int s5p_dsim_probe(struct platform_device *pdev)
{
	struct resource *res;
	int ret = -1;

	dsim.pd = to_dsim_plat(&pdev->dev);
	dsim.dev = &pdev->dev;
#ifdef CONFIG_EXYNOS_DEV_PD
	/* to use the runtime PM helper functions */
	pm_runtime_enable(&pdev->dev);
	/* enable the power domain */
	pm_runtime_get_sync(&pdev->dev);
#endif
	/* set dsim config data, dsim lcd config data and lcd panel data. */
	dsim.dsim_info = dsim.pd->dsim_info;
	dsim.dsim_lcd_info = dsim.pd->dsim_lcd_info;
	dsim.lcd_panel_info =
		(struct s3cfb_lcd *)dsim.dsim_lcd_info->lcd_panel_info;
	dsim.mipi_ddi_pd =
		(struct mipi_ddi_platform_data *)dsim.dsim_lcd_info->mipi_ddi_pd;
	dsim.mipi_ddi_pd->te_irq = dsim.pd->te_irq;

	dsim.mipi_ddi_pd->resume_complete = 0;

	/* reset lcd */
	dsim.mipi_ddi_pd->lcd_reset();

	/* clock */
	dsim.clock = clk_get(&pdev->dev, dsim.pd->clk_name);
	if (IS_ERR(dsim.clock)) {
		dev_err(&pdev->dev, "failed to get dsim clock source\n");
		return -EINVAL;
	}

	clk_enable(dsim.clock);

	/* io memory */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "failed to get io memory region\n");
		ret = -EINVAL;
		goto err_clk_disable;
	}

	/* request mem region */
	res = request_mem_region(res->start,
				 res->end - res->start + 1, pdev->name);
	if (!res) {
		dev_err(&pdev->dev, "failed to request io memory region\n");
		ret = -EINVAL;
		goto err_clk_disable;
	}

	/* ioremap for register block */
	dsim.reg_base = (unsigned int) ioremap(res->start,
			res->end - res->start + 1);
	if (!dsim.reg_base) {
		dev_err(&pdev->dev, "failed to remap io region\n");
		ret = -EINVAL;
		goto err_clk_disable;
	}

	/* find lcd panel driver registered to mipi-dsi driver. */
	dsim.mipi_drv = scan_mipi_driver(dsim.pd->lcd_panel_name);
	if (dsim.mipi_drv == NULL) {
		dev_err(&pdev->dev, "mipi_drv is NULL.\n");
		goto mipi_drv_err;
	}

	/* set lcd panel driver link */
	dsim.mipi_drv->set_link((void *) dsim.mipi_ddi_pd, dsim.reg_base,
		s5p_dsim_wr_data, NULL);

	dsim.mipi_drv->probe(&pdev->dev);
	s5p_dsim_init_dsim(dsim.reg_base);
	s5p_dsim_init_link(dsim.reg_base);

	s5p_dsim_set_hs_enable(dsim.reg_base);
	s5p_dsim_set_data_transfer_mode(dsim.reg_base, DSIM_TRANSFER_BYCPU, 1);

	/* initialize lcd panel */
	if (dsim.mipi_drv->init) {
		dsim.mipi_drv->init();
	} else {
		dev_warn(&pdev->dev, "init func is null.\n");
	}

	if (dsim.mipi_drv->display_on)
		dsim.mipi_drv->display_on(&pdev->dev);
	else
		dev_warn(&pdev->dev, "display_on func is null.\n");

	s5p_dsim_set_display_mode(dsim.reg_base, dsim.dsim_lcd_info, NULL);
	s5p_dsim_set_data_transfer_mode(dsim.reg_base, DSIM_TRANSFER_BYLCDC, 1);
	msleep(400);
	dev_info(&pdev->dev, "mipi-dsi driver has been probed.\n");

#ifdef CONFIG_HAS_WAKELOCK
#ifdef CONFIG_HAS_EARLYSUSPEND
	dsim.early_suspend.suspend = s5p_dsim_early_suspend;
	dsim.early_suspend.resume = s5p_dsim_late_resume;
	dsim.early_suspend.level = EARLY_SUSPEND_LEVEL_DISABLE_FB;
	register_early_suspend(&dsim.early_suspend);
#endif
#endif

	return 0;

mipi_drv_err:
	dsim.pd->mipi_power(0);
	iounmap((void __iomem *) dsim.reg_base);
err_clk_disable:
	clk_disable(dsim.clock);

	return ret;
}

static int s5p_dsim_remove(struct platform_device *pdev)
{
#ifdef CONFIG_EXYNOS_DEV_PD
	/* disable the power domain */
	pm_runtime_put(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
#endif
	return 0;
}

#ifdef CONFIG_EXYNOS_DEV_PD
static int s5p_dsim_runtime_suspend(struct device *dev)
{
	return 0;
}

static int s5p_dsim_runtime_resume(struct device *dev)
{
	return 0;
}

static const struct dev_pm_ops s5p_dsim_pm_ops = {
	.runtime_suspend = s5p_dsim_runtime_suspend,
	.runtime_resume = s5p_dsim_runtime_resume,
};
#endif

static struct platform_driver s5p_dsim_driver = {
	.probe = s5p_dsim_probe,
	.remove = s5p_dsim_remove,
#ifndef CONFIG_HAS_EARLYSUSPEND
	.suspend = s5p_dsim_suspend,
	.resume = s5p_dsim_resume,
#endif
	.driver = {
		   .name = "s5p-dsim",
		   .owner = THIS_MODULE,
#ifdef CONFIG_EXYNOS_DEV_PD
		   .pm	= &s5p_dsim_pm_ops,
#endif
		   },

};

static int s5p_dsim_register(void)
{
	platform_driver_register(&s5p_dsim_driver);
	return 0;
}

static void s5p_dsim_unregister(void)
{
	platform_driver_unregister(&s5p_dsim_driver);
}

module_init(s5p_dsim_register);
module_exit(s5p_dsim_unregister);

MODULE_AUTHOR("InKi Dae <inki.dae@samsung.com>");
MODULE_DESCRIPTION("Samusung MIPI-DSIM driver");
MODULE_LICENSE("GPL");
