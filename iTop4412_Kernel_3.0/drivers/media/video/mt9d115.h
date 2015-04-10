/* linux/drivers/media/video/mt9d115.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __MT9D115_H__
#define __MT9D115_H__

struct mt9d115_reg {
	unsigned short addr;
	unsigned short val;
};

struct mt9d115_regset_type {
	unsigned char *regset;
	int len;
};

/*
 * Macro
 */
#define REGSET_LENGTH(x)	(sizeof(x)/sizeof(mt9d115_reg))

/*
 * Host S/W Register interface (0x70000000-0x70002000)
 */
/* Initialization section */
#define REG_TC_IPRM_InClockLSBs			0x01B8
#define REG_TC_IPRM_InClockMSBs			0x01BA
#define REG_TC_IPRM_PllFreqDiv4			0x01BC
#define REG_TC_IPRM_AddHeader			0x01BE
#define REG_TC_IPRM_ValidVActiveLow		0x01C0
#define REG_TC_IPRM_SenI2CAdr			0x01C2
#define REG_TC_IPRM_MI2CDrSclMan		0x01C4
#define REG_TC_IPRM_UseNPviClocks		0x01C6
#define REG_TC_IPRM_UseNMipiClocks		0x01C8
#define REG_TC_IPRM_bBlockInternalPllCalc	0x01CA

#define REG_TC_IPRM_OpClk4KHz_0			0x01CC
#define REG_TC_IPRM_MinOutRate4KHz_0		0x01CE
#define REG_TC_IPRM_MaxOutRate4KHz_0		0x01D0

#define REG_TC_IPRM_OpClk4KHz_1			0x01D2
#define REG_TC_IPRM_MinOutRate4KHz_1		0x01D4
#define REG_TC_IPRM_MaxOutRate4KHz_1		0x01D6

#define REG_TC_IPRM_OpClk4KHz_2			0x01D8
#define REG_TC_IPRM_MinOutRate4KHz_2		0x01DA
#define REG_TC_IPRM_MaxOutRate4KHz_2		0x01DC

#define REG_TC_IPRM_UseRegsAPI			0x01DE
#define REG_TC_IPRM_InitParamsUpdated		0x01E0
#define REG_TC_IPRM_ErrorInfo			0x01E2

/* Preview control section */
#define REG_0TC_PCFG_usWidth			0x0242
#define REG_0TC_PCFG_usHeight			0x0244
#define REG_0TC_PCFG_Format			0x0246
#define REG_0TC_PCFG_usMaxOut4KHzRate		0x0248
#define REG_0TC_PCFG_usMinOut4KHzRate		0x024A
#define REG_0TC_PCFG_PVIMask			0x024C
#define REG_0TC_PCFG_uClockInd			0x024E
#define REG_0TC_PCFG_usFrTimeType		0x0250
#define REG_0TC_PCFG_FrRateQualityType		0x0252
#define REG_0TC_PCFG_usMaxFrTimeMsecMult10	0x0254
#define REG_0TC_PCFG_usMinFrTimeMsecMult10	0x0256
#define REG_0TC_PCFG_sSaturation		0x0258
#define REG_0TC_PCFG_sSharpBlur			0x025A
#define REG_0TC_PCFG_sGlamour			0x025C
#define REG_0TC_PCFG_sColorTemp			0x025E
#define REG_0TC_PCFG_uDeviceGammaIndex		0x0260
#define REG_0TC_PCFG_uPrevMirror		0x0262
#define REG_0TC_PCFG_uCaptureMirror		0x0264
#define REG_0TC_PCFG_uRotation			0x0266

#define REG_1TC_PCFG_usWidth			0x0268
#define REG_1TC_PCFG_usHeight			0x026A
#define REG_1TC_PCFG_Format			0x026C
#define REG_1TC_PCFG_usMaxOut4KHzRate		0x026E
#define REG_1TC_PCFG_usMinOut4KHzRate		0x0270
#define REG_1TC_PCFG_PVIMask			0x0272
#define REG_1TC_PCFG_uClockInd			0x0274
#define REG_1TC_PCFG_usFrTimeType		0x0276
#define REG_1TC_PCFG_FrRateQualityType		0x0278
#define REG_1TC_PCFG_usMaxFrTimeMsecMult10	0x027A
#define REG_1TC_PCFG_usMinFrTimeMsecMult10	0x027C
#define REG_1TC_PCFG_sSaturation		0x027E
#define REG_1TC_PCFG_sSharpBlur			0x0280
#define REG_1TC_PCFG_sGlamour			0x0282
#define REG_1TC_PCFG_sColorTemp			0x0284
#define REG_1TC_PCFG_uDeviceGammaIndex		0x0286
#define REG_1TC_PCFG_uPrevMirror		0x0288
#define REG_1TC_PCFG_uCaptureMirror		0x028A
#define REG_1TC_PCFG_uRotation			0x028C

#define REG_2TC_PCFG_usWidth			0x028E
#define REG_2TC_PCFG_usHeight			0x0290
#define REG_2TC_PCFG_Format			0x0292
#define REG_2TC_PCFG_usMaxOut4KHzRate		0x0294
#define REG_2TC_PCFG_usMinOut4KHzRate		0x0296
#define REG_2TC_PCFG_PVIMask			0x0298
#define REG_2TC_PCFG_uClockInd			0x029A
#define REG_2TC_PCFG_usFrTimeType		0x029C
#define REG_2TC_PCFG_FrRateQualityType		0x029E
#define REG_2TC_PCFG_usMaxFrTimeMsecMult10	0x02A0
#define REG_2TC_PCFG_usMinFrTimeMsecMult10	0x02A2
#define REG_2TC_PCFG_sSaturation		0x02A4
#define REG_2TC_PCFG_sSharpBlur			0x02A6
#define REG_2TC_PCFG_sGlamour			0x02A8
#define REG_2TC_PCFG_sColorTemp			0x02AA
#define REG_2TC_PCFG_uDeviceGammaIndex		0x02AC
#define REG_2TC_PCFG_uPrevMirror		0x02AE
#define REG_2TC_PCFG_uCaptureMirror		0x02B0
#define REG_2TC_PCFG_uRotation			0x02B2

#define REG_3TC_PCFG_usWidth			0x02B4
#define REG_3TC_PCFG_usHeight			0x02B6
#define REG_3TC_PCFG_Format			0x02B8
#define REG_3TC_PCFG_usMaxOut4KHzRate		0x02BA
#define REG_3TC_PCFG_usMinOut4KHzRate		0x02BC
#define REG_3TC_PCFG_PVIMask			0x02BE
#define REG_3TC_PCFG_uClockInd			0x02C0
#define REG_3TC_PCFG_usFrTimeType		0x02C2
#define REG_3TC_PCFG_FrRateQualityType		0x02C4
#define REG_3TC_PCFG_usMaxFrTimeMsecMult10	0x02C6
#define REG_3TC_PCFG_usMinFrTimeMsecMult10	0x02C8
#define REG_3TC_PCFG_sSaturation		0x02CA
#define REG_3TC_PCFG_sSharpBlur			0x02CC
#define REG_3TC_PCFG_sGlamour			0x02CE
#define REG_3TC_PCFG_sColorTemp			0x02D0
#define REG_3TC_PCFG_uDeviceGammaIndex		0x02D2
#define REG_3TC_PCFG_uPrevMirror		0x02D4
#define REG_3TC_PCFG_uCaptureMirror		0x02D6
#define REG_3TC_PCFG_uRotation			0x02D8

#define REG_4TC_PCFG_usWidth			0x02DA
#define REG_4TC_PCFG_usHeight			0x02DC
#define REG_4TC_PCFG_Format			0x02DE
#define REG_4TC_PCFG_usMaxOut4KHzRate		0x02E0
#define REG_4TC_PCFG_usMinOut4KHzRate		0x02E2
#define REG_4TC_PCFG_PVIMask			0x02E4
#define REG_4TC_PCFG_uClockInd			0x02E6
#define REG_4TC_PCFG_usFrTimeType		0x02E8
#define REG_4TC_PCFG_FrRateQualityType		0x02EA
#define REG_4TC_PCFG_usMaxFrTimeMsecMult10	0x02EC
#define REG_4TC_PCFG_usMinFrTimeMsecMult10	0x02EE
#define REG_4TC_PCFG_sSaturation		0x02F0
#define REG_4TC_PCFG_sSharpBlur			0x02F2
#define REG_4TC_PCFG_sGlamour			0x02F4
#define REG_4TC_PCFG_sColorTemp			0x02F6
#define REG_4TC_PCFG_uDeviceGammaIndex		0x02F8
#define REG_4TC_PCFG_uPrevMirror		0x02FA
#define REG_4TC_PCFG_uCaptureMirror		0x02FC
#define REG_4TC_PCFG_uRotation			0x02FEa

#define REG_AC_TC_PCFG_usWidth			0x11C8
#define REG_AC_TC_PCFG_usHeight			0x11CA
#define REG_AC_TC_PCFG_Format			0x11CC
#define REG_AC_TC_PCFG_usMaxOut4KHzRate		0x11CE
#define REG_AC_TC_PCFG_usMinOut4KHzRate		0x11D0
#define REG_AC_TC_PCFG_PVIMask			0x11D2
#define REG_AC_TC_PCFG_uClockInd		0x11D4
#define REG_AC_TC_PCFG_usFrTimeType		0x11D6
#define REG_AC_TC_PCFG_FrRateQualityType	0x11D8
#define REG_AC_TC_PCFG_usMaxFrTimeMsecMult10	0x11DA
#define REG_AC_TC_PCFG_usMinFrTimeMsecMult10	0x11DC
#define REG_AC_TC_PCFG_sSaturation		0x11DE
#define REG_AC_TC_PCFG_sSharpBlur		0x11E0
#define REG_AC_TC_PCFG_sGlamour			0x11E2
#define REG_AC_TC_PCFG_sColorTemp		0x11E4
#define REG_AC_TC_PCFG_uDeviceGammaIndex	0x11E6
#define REG_AC_TC_PCFG_uPrevMirror		0x11E8
#define REG_AC_TC_PCFG_uCaptureMirror		0x11EA
#define REG_AC_TC_PCFG_uRotation		0x11EC

/* Capture control section */
#define REG_0TC_CCFG_uCaptureMode		0x030C
#define REG_0TC_CCFG_usWidth			0x030E
#define REG_0TC_CCFG_usHeight			0x0310
#define REG_0TC_CCFG_Format			0x3012
#define REG_0TC_CCFG_usMaxOut4KHzRate		0x0314
#define REG_0TC_CCFG_usMinOut4KHzRate		0x0316
#define REG_0TC_CCFG_PVIMask			0x0318
#define REG_0TC_CCFG_uClockInd			0x031A
#define REG_0TC_CCFG_usFrTimeType		0x031C
#define REG_0TC_CCFG_FrRateQualityType		0x031E
#define REG_0TC_CCFG_usMaxFrTimeMsecMult10	0x0320
#define REG_0TC_CCFG_usMinFrTimeMsecMult10	0x0322
#define REG_0TC_CCFG_sSaturation		0x0324
#define REG_0TC_CCFG_sSharpBlur			0x0326
#define REG_0TC_CCFG_sGlamour			0x0328
#define REG_0TC_CCFG_sColorTemp			0x032A
#define REG_0TC_CCFG_uDeviceGammaIndex		0x032C

#define REG_1TC_CCFG_uCaptureMode		0x032E
#define REG_1TC_CCFG_usWidth			0x0330
#define REG_1TC_CCFG_usHeight			0x0332
#define REG_1TC_CCFG_Format			0x0334
#define REG_1TC_CCFG_usMaxOut4KHzRate		0x0336
#define REG_1TC_CCFG_usMinOut4KHzRate		0x0338
#define REG_1TC_CCFG_PVIMask			0x033A
#define REG_1TC_CCFG_uClockInd			0x033C
#define REG_1TC_CCFG_usFrTimeType		0x033E
#define REG_1TC_CCFG_FrRateQualityType		0x0340
#define REG_1TC_CCFG_usMaxFrTimeMsecMult10	0x0342
#define REG_1TC_CCFG_usMinFrTimeMsecMult10	0x0344
#define REG_1TC_CCFG_sSaturation		0x0346
#define REG_1TC_CCFG_sSharpBlur			0x0348
#define REG_1TC_CCFG_sGlamour			0x034A
#define REG_1TC_CCFG_sColorTemp			0x034C
#define REG_1TC_CCFG_uDeviceGammaIndex		0x034E

#define REG_2TC_CCFG_uCaptureMode		0x0350
#define REG_2TC_CCFG_usWidth			0x0352
#define REG_2TC_CCFG_usHeight			0x0354
#define REG_2TC_CCFG_Format			0x0356
#define REG_2TC_CCFG_usMaxOut4KHzRate		0x0358
#define REG_2TC_CCFG_usMinOut4KHzRate		0x035A
#define REG_2TC_CCFG_PVIMask			0x035C
#define REG_2TC_CCFG_uClockInd			0x035E
#define REG_2TC_CCFG_usFrTimeType		0x0360
#define REG_2TC_CCFG_FrRateQualityType		0x0362
#define REG_2TC_CCFG_usMaxFrTimeMsecMult10	0x0364
#define REG_2TC_CCFG_usMinFrTimeMsecMult10	0x0366
#define REG_2TC_CCFG_sSaturation		0x0368
#define REG_2TC_CCFG_sSharpBlur			0x036A
#define REG_2TC_CCFG_sGlamour			0x036C
#define REG_2TC_CCFG_sColorTemp			0x036E
#define REG_2TC_CCFG_uDeviceGammaIndex		0x0370

#define REG_3TC_CCFG_uCaptureMode		0x0372
#define REG_3TC_CCFG_usWidth			0x0374
#define REG_3TC_CCFG_usHeight			0x0376
#define REG_3TC_CCFG_Format			0x0378
#define REG_3TC_CCFG_usMaxOut4KHzRate		0x037A
#define REG_3TC_CCFG_usMinOut4KHzRate		0x037C
#define REG_3TC_CCFG_PVIMask			0x037E
#define REG_3TC_CCFG_uClockInd			0x0380
#define REG_3TC_CCFG_usFrTimeType		0x0382
#define REG_3TC_CCFG_FrRateQualityType		0x0384
#define REG_3TC_CCFG_usMaxFrTimeMsecMult10	0x0386
#define REG_3TC_CCFG_usMinFrTimeMsecMult10	0x0388
#define REG_3TC_CCFG_sSaturation		0x038A
#define REG_3TC_CCFG_sSharpBlur			0x038C
#define REG_3TC_CCFG_sGlamour			0x038E
#define REG_3TC_CCFG_sColorTemp			0x0390
#define REG_3TC_CCFG_uDeviceGammaIndex		0x0392

#define REG_4TC_CCFG_uCaptureMode		0x0394
#define REG_4TC_CCFG_usWidth			0x0396
#define REG_4TC_CCFG_usHeight			0x0398
#define REG_4TC_CCFG_Format			0x039A
#define REG_4TC_CCFG_usMaxOut4KHzRate		0x039C
#define REG_4TC_CCFG_usMinOut4KHzRate		0x039E
#define REG_4TC_CCFG_PVIMask			0x03A0
#define REG_4TC_CCFG_uClockInd			0x03A2
#define REG_4TC_CCFG_usFrTimeType		0x03A4
#define REG_4TC_CCFG_FrRateQualityType		0x03A6
#define REG_4TC_CCFG_usMaxFrTimeMsecMult10	0x03A8
#define REG_4TC_CCFG_usMinFrTimeMsecMult10	0x03AA
#define REG_4TC_CCFG_sSaturation		0x03AC
#define REG_4TC_CCFG_sSharpBlur			0x03AE
#define REG_4TC_CCFG_sGlamour			0x03B0
#define REG_4TC_CCFG_sColorTemp			0x03B2
#define REG_4TC_CCFG_uDeviceGammaIndex		0x03B4

#define REG_AC_TC_CCFG_uCaptureMode		0x1214
#define REG_AC_TC_CCFG_usWidth			0x1216
#define REG_AC_TC_CCFG_usHeight			0x1218
#define REG_AC_TC_CCFG_Format			0x121A
#define REG_AC_TC_CCFG_usMaxOut4KHzRate		0x121C
#define REG_AC_TC_CCFG_usMinOut4KHzRate		0x121E
#define REG_AC_TC_CCFG_PVIMask			0x1220
#define REG_AC_TC_CCFG_uClockInd		0x1222
#define REG_AC_TC_CCFG_usFrTimeType		0x1224
#define REG_AC_TC_CCFG_FrRateQualityType	0x1226
#define REG_AC_TC_CCFG_usMaxFrTimeMsecMult10	0x1228
#define REG_AC_TC_CCFG_usMinFrTimeMsecMult10	0x122A
#define REG_AC_TC_CCFG_sSaturation		0x122C
#define REG_AC_TC_CCFG_sSharpBlur		0x122E
#define REG_AC_TC_CCFG_sGlamour			0x1230
#define REG_AC_TC_CCFG_sColorTemp		0x1232
#define REG_AC_TC_CCFG_uDeviceGammaIndex	0x1234

/* Configuration value section */
/* Frame rate */
/* for REG_[NUM]TC_PCFG_usFrTimeType */
#define TC_FR_TIME_DYNAMIC			0
#define TC_FR_TIME_FIXED_NOT_ACCURATE		1
#define TC_FR_TIME_FIXED_ACCURATE		2
/* for REG_[NUM]TC_PCFG_FrRateQualityType */
#define TC_FRVSQ_BEST_FRRATE			1	/* Binning enabled */
#define TC_FRVSQ_BEST_QUALITY			2	/* Binning disabled */

/* General purpose section */
#define REG_TC_GP_SpecialEffects		0x01EE
#define REG_TC_GP_EnablePreview			0x01F0
#define REG_TC_GP_EnablePreviewChanged		0x01F2
#define REG_TC_GP_EnableCapture			0x01F4
#define REG_TC_GP_EnableCaptureChanged		0x01F6
#define REG_TC_GP_NewConfigSync			0x01F8
#define REG_TC_GP_PrevReqInputWidth		0x01FA
#define REG_TC_GP_PrevReqInputHeight		0x01FC
#define REG_TC_GP_PrevInputWidthOfs		0x01FE
#define REG_TC_GP_PrevInputHeightOfs		0x0200
#define REG_TC_GP_CapReqInputWidth		0x0202
#define REG_TC_GP_CapReqInputHeight		0x0204
#define REG_TC_GP_CapInputWidthOfs		0x0206
#define REG_TC_GP_CapInputHeightOfs		0x0208
#define REG_TC_GP_PrevZoomReqInputWidth		0x020A
#define REG_TC_GP_PrevZoomReqInputHeight	0x020C
#define REG_TC_GP_PrevZoomReqInputWidthOfs	0x020E
#define REG_TC_GP_PrevZoomReqInputHeightOfs	0x0210
#define REG_TC_GP_CapZoomReqInputWidth		0x0212
#define REG_TC_GP_CapZoomReqInputHeight		0x0214
#define REG_TC_GP_CapZoomReqInputWidthOfs	0x0216
#define REG_TC_GP_CapZoomReqInputHeightOfs	0x0218
#define REG_TC_GP_InputsChangeRequest		0x021A
#define REG_TC_GP_ActivePrevConfig		0x021C
#define REG_TC_GP_PrevConfigChanged		0x021E
#define REG_TC_GP_PrevOpenAfterChange		0x0220
#define REG_TC_GP_ErrorPrevConfig		0x0222
#define REG_TC_GP_ActiveCapConfig		0x0224
#define REG_TC_GP_CapConfigChanged		0x0226
#define REG_TC_GP_ErrorCapConfig		0x0228
#define REG_TC_GP_PrevConfigBypassChanged	0x022A
#define REG_TC_GP_CapConfigBypassChanged	0x022C
#define REG_TC_GP_SleepMode			0x022E
#define REG_TC_GP_SleepModeChanged		0x0230
#define REG_TC_GP_SRA_AddLow			0x0232
#define REG_TC_GP_SRA_AddHigh			0x0234
#define REG_TC_GP_SRA_AccessType		0x0236
#define REG_TC_GP_SRA_Changed			0x0238
#define REG_TC_GP_PrevMinFrTimeMsecMult10	0x023A
#define REG_TC_GP_PrevOutKHzRate		0x023C
#define REG_TC_GP_CapMinFrTimeMsecMult10	0x023E
#define REG_TC_GP_CapOutKHzRate			0x0240

/* Image property control section */
#define REG_TC_UserBrightness			0x01E4
#define REG_TC_UserContrast			0x01E6
#define REG_TC_UserSaturation			0x01E8
#define REG_TC_UserSharpBlur			0x01EA
#define REG_TC_UserGlamour			0x01EC

/* Flash control section */
#define REG_TC_FLS_Mode				0x03B6
#define REG_TC_FLS_Threshold			0x03B8
#define REG_TC_FLS_Polarity			0x03BA
#define REG_TC_FLS_XenonMode			0x03BC
#define REG_TC_FLS_XenonPreFlashCnt		0x03BE

/* Extended image property control section */
#define REG_SF_USER_LeiLow			0x03C0
#define REG_SF_USER_LeiHigh			0x03C2
#define REG_SF_USER_LeiChanged			0x03C4
#define REG_SF_USER_Exposure			0x03C6
#define REG_SF_USER_ExposureChanged		0x03CA
#define REG_SF_USER_TotalGain			0x03CC
#define REG_SF_USER_TotalGainChanged		0x03CE
#define REG_SF_USER_Rgain			0x03D0
#define REG_SF_USER_RgainChanged		0x03D2
#define REG_SF_USER_Ggain			0x03D4
#define REG_SF_USER_GgainChanged		0x03D6
#define REG_SF_USER_Bgain			0x03D8
#define REG_SF_USER_BgainChanged		0x03DA
#define REG_SF_USER_FlickerQuant		0x03DC
#define REG_SF_USER_FlickerQuantChanged		0x03DE
#define REG_SF_USER_GASRAlphaVal		0x03E0
#define REG_SF_USER_GASRAlphaChanged		0x03E2
#define REG_SF_USER_GASGAlphaVal		0x03E4
#define REG_SF_USER_GASGAlphaChanged		0x03E6
#define REG_SF_USER_GASBAlphaVal		0x03E8
#define REG_SF_USER_GASBAlphaChanged		0x03EA
#define REG_SF_USER_DbgIdx			0x03EC
#define REG_SF_USER_DbgVal			0x03EE
#define REG_SF_USER_DbgChanged			0x03F0
#define REG_SF_USER_aGain			0x03F2
#define REG_SF_USER_aGainChanged		0x03F4
#define REG_SF_USER_dGain			0x03F6
#define REG_SF_USER_dGainChanged		0x03F8

/* Output interface control section */
#define REG_TC_OIF_EnMipiLanes			0x03FA
#define REG_TC_OIF_EnPackets			0x03FC
#define REG_TC_OIF_CfgChanged			0x03FE

/* Debug control section */
#define REG_TC_DBG_AutoAlgEnBits		0x0400
#define REG_TC_DBG_IspBypass			0x0402
#define REG_TC_DBG_ReInitCmd			0x0404

/* Version information section */
#define REG_FWdate				0x012C
#define REG_FWapiVer				0x012E
#define REG_FWrevision				0x0130
#define REG_FWpid				0x0132
#define REG_FWprjName				0x0134
#define REG_FWcompDate				0x0140
#define REG_FWSFC_VER				0x014C
#define REG_FWTC_VER				0x014E
#define REG_FWrealImageLine			0x0150
#define REG_FWsenId				0x0152
#define REG_FWusDevIdQaVersion			0x0154
#define REG_FWusFwCompilationBits		0x0156
#define REG_ulSVNrevision			0x0158
#define REG_SVNpathRomAddress			0x015C
#define REG_TRAP_N_PATCH_START_ADD		0x1B00

#define	setot_usForceClocksSettings		0x0AEA
#define	setot_usConfigClocksSettings		0x0AEC

/*
 * User defined commands
 */
/* S/W defined features for tune */
#define REG_DELAY	0xFF	/* in ms */
#define REG_CMD		0xFFFF	/* Followed by command */

/* Following order should not be changed */
enum image_size_mt9d115 {
	/* This SoC supports upto SXGA (1280*1024) */
#if 0
	QQVGA,	/* 160*120*/
	QCIF,	/* 176*144 */
	QVGA,	/* 320*240 */
	CIF,	/* 352*288 */
#endif
	VGA,	/* 640*480 */
	SVGA,	/* 800*600 */
	UXGA,	/*1600*1200*/
#if 0	
	HD720P,	/* 1280*720 */
	SXGA,	/* 1280*1024 */
#endif
};

/*
 * Following values describe controls of camera
 * in user aspect and must be match with index of mt9d115_regset[]
 * These values indicates each controls and should be used
 * to control each control
 */
enum mt9d115_control {
	MT9D115_INIT,
	MT9D115_EV,
	MT9D115_AWB,
	MT9D115_MWB,
	MT9D115_EFFECT,
	MT9D115_CONTRAST,
	MT9D115_SATURATION,
	MT9D115_SHARPNESS,
};

#define MT9D115_REGSET(x)	{	\
	.regset = x,			\
	.len = sizeof(x)/sizeof(mt9d115_reg),}

/*
 * User tuned register setting values
 */
unsigned short mt9d115_init_reg[][2] = {
	{0x001A, 0x0051}, 	// RESET_AND_MISC_CONTROL
	{REG_DELAY,1},				// Allow PLL to lock
	{0x001A, 0x0050}, 	// RESET_AND_MISC_CONTROL
	
	//pll settings
	{0x0014, 0x2545}, 	// PLL_CONTROL
	{0x0010, 0x0110}, 	// PLL_DIVIDERS
	{0x0012, 0x1FF7}, 	// PLL_P_DIVIDERS
	{0x0014, 0x2547}, 	// PLL_CONTROL
	{0x0014, 0x2447}, 	// PLL_CONTROL
	{REG_DELAY,20},
	{0x0014, 0x2047}, 	// PLL_CONTROL
	{0x0014, 0x2046}, 	// PLL_CONTROL
	{0x001A, 0x0050}, 	// RESET_AND_MISC_CONTROL
	{0x0018, 0x4028}, 	// STANDBY_CONTROL
	{REG_DELAY,20},
	//timing settings

	{0x321C, 0x0003}, 	// OFIFO_CONTROL_STATUS
	{0x098C, 0x2703}, 	// MCU_ADDRESS
	{0x0990, 0x0280}, 	// MCU_DATA_0
	{0x098C, 0x2705}, 	// MCU_ADDRESS
	{0x0990, 0x01E0}, 	// MCU_DATA_0
	{0x098C, 0x2707}, 	// MCU_ADDRESS
	{0x0990, 0x0640}, 	// MCU_DATA_0
	{0x098C, 0x2709}, 	// MCU_ADDRESS
	{0x0990, 0x04B0}, 	// MCU_DATA_0
	{0x098C, 0x270D}, 	// MCU_ADDRESS
	{0x0990, 0x0000}, 	// MCU_DATA_0
	{0x098C, 0x270F}, 	// MCU_ADDRESS
	{0x0990, 0x0000}, 	// MCU_DATA_0
	{0x098C, 0x2711}, 	// MCU_ADDRESS
	{0x0990, 0x04BD}, 	// MCU_DATA_0
	{0x098C, 0x2713}, 	// MCU_ADDRESS
	{0x0990, 0x064D}, 	// MCU_DATA_0
	{0x098C, 0x2715}, 	// MCU_ADDRESS
	{0x0990, 0x0111}, 	// MCU_DATA_0
	{0x098C, 0x2717}, 	// MCU_ADDRESS
	{0x0990, 0x046C}, 	// MCU_DATA_0
	{0x098C, 0x2719}, 	// MCU_ADDRESS
	{0x0990, 0x005A}, 	// MCU_DATA_0
	{0x098C, 0x271B}, 	// MCU_ADDRESS
	{0x0990, 0x01BE}, 	// MCU_DATA_0
	{0x098C, 0x271D}, 	// MCU_ADDRESS
	{0x0990, 0x0131}, 	// MCU_DATA_0
	{0x098C, 0x271F}, 	// MCU_ADDRESS
	{0x0990, 0x02D5}, 	// MCU_DATA_0
	{0x098C, 0x2721}, 	// MCU_ADDRESS
	{0x0990, 0x0546}, 	// MCU_DATA_0
	{0x098C, 0x2723}, 	// MCU_ADDRESS
	{0x0990, 0x0004}, 	// MCU_DATA_0
	{0x098C, 0x2725}, 	// MCU_ADDRESS
	{0x0990, 0x0004}, 	// MCU_DATA_0
	{0x098C, 0x2727}, 	// MCU_ADDRESS
	{0x0990, 0x04BB}, 	// MCU_DATA_0
	{0x098C, 0x2729}, 	// MCU_ADDRESS
	{0x0990, 0x064B}, 	// MCU_DATA_0
	{0x098C, 0x272B}, 	// MCU_ADDRESS
	{0x0990, 0x0111}, 	// MCU_DATA_0
	{0x098C, 0x272D}, 	// MCU_ADDRESS
	{0x0990, 0x0024}, 	// MCU_DATA_0
	{0x098C, 0x272F}, 	// MCU_ADDRESS
	{0x0990, 0x003A}, 	// MCU_DATA_0
	{0x098C, 0x2731}, 	// MCU_ADDRESS
	{0x0990, 0x00F6}, 	// MCU_DATA_0
	{0x098C, 0x2733}, 	// MCU_ADDRESS
	{0x0990, 0x008B}, 	// MCU_DATA_0
	{0x098C, 0x2735}, 	// MCU_ADDRESS
	{0x0990, 0x08D5}, 	// MCU_DATA_0
	{0x098C, 0x2737}, 	// MCU_ADDRESS
	{0x0990, 0x07BC}, 	// MCU_DATA_0
	{0x098C, 0x2739}, 	// MCU_ADDRESS
	{0x0990, 0x0000}, 	// MCU_DATA_0
	{0x098C, 0x273B}, 	// MCU_ADDRESS
	{0x0990, 0x031F}, 	// MCU_DATA_0
	{0x098C, 0x273D}, 	// MCU_ADDRESS
	{0x0990, 0x0000}, 	// MCU_DATA_0
	{0x098C, 0x273F}, 	// MCU_ADDRESS
	{0x0990, 0x0257}, 	// MCU_DATA_0
	{0x098C, 0x2747}, 	// MCU_ADDRESS
	{0x0990, 0x0000}, 	// MCU_DATA_0
	{0x098C, 0x2749}, 	// MCU_ADDRESS
	{0x0990, 0x063F}, 	// MCU_DATA_0
	{0x098C, 0x274B}, 	// MCU_ADDRESS
	{0x0990, 0x0000}, 	// MCU_DATA_0
	{0x098C, 0x274D}, 	// MCU_ADDRESS
	{0x0990, 0x04AF}, 	// MCU_DATA_0
	{0x098C, 0x222D}, 	// MCU_ADDRESS
	{0x0990, 0x0094}, 	// MCU_DATA_0
	{0x098C, 0xA408}, 	// MCU_ADDRESS
	{0x0990, 0x0024}, 	// MCU_DATA_0
	{0x098C, 0xA409}, 	// MCU_ADDRESS
	{0x0990, 0x0026}, 	// MCU_DATA_0
	{0x098C, 0xA40A}, 	// MCU_ADDRESS
	{0x0990, 0x002B}, 	// MCU_DATA_0
	{0x098C, 0xA40B}, 	// MCU_ADDRESS
	{0x0990, 0x002D}, 	// MCU_DATA_0
	{0x098C, 0x2411}, 	// MCU_ADDRESS
	{0x0990, 0x0094}, 	// MCU_DATA_0
	{0x098C, 0x2413}, 	// MCU_ADDRESS
	{0x0990, 0x00B2}, 	// MCU_DATA_0
	{0x098C, 0x2415}, 	// MCU_ADDRESS
	{0x0990, 0x0065}, 	// MCU_DATA_0
	{0x098C, 0x2417}, 	// MCU_ADDRESS
	{0x0990, 0x0079}, 	// MCU_DATA_0
	{0x098C, 0xA404}, 	// MCU_ADDRESS
	{0x0990, 0x0010}, 	// MCU_DATA_0
	{0x098C, 0xA40D}, 	// MCU_ADDRESS
	{0x0990, 0x0002}, 	// MCU_DATA_0
	{0x098C, 0xA40E}, 	// MCU_ADDRESS
	{0x0990, 0x0003}, 	// MCU_DATA_0
	{0x098C, 0xA410}, 	// MCU_ADDRESS
	{0x0990, 0x000A}, 	// MCU_DATA_0
	{0x098C, 0xA103}, 	// MCU_ADDRESS
	{0x0990, 0x0006}, 	// MCU_DATA_0
	{REG_DELAY,20},
	{0x098C, 0xA103}, 	// MCU_ADDRESS
	{0x0990, 0x0005}, 	// MCU_DATA_0
	{REG_DELAY,50},

	//


	//[CbYCrY]
	//{0x098C, 0x2755}, 	// MCU_ADDRESS [MODE_OUTPUT_FORMAT_A]
	//{0x0990, 0x0000}, 	// MCU_DATA_0
	//[CrYCbY]
	//{0x098C, 0x2755}, 	// MCU_ADDRESS [MODE_OUTPUT_FORMAT_A]
	//{0x0990, 0x0001}, 	// MCU_DATA_0
	//[YCbYCr]
	//{0x098C, 0x2755}, 	// MCU_ADDRESS [MODE_OUTPUT_FORMAT_A]
	//{0x0990, 0x0002}, 	// MCU_DATA_0
	//[YCrYCb]
	//{0x098C, 0x2755}, 	// MCU_ADDRESS [MODE_OUTPUT_FORMAT_A]
	//{0x0990, 0x0003}, 	// MCU_DATA_0

#if 1


	//LSC
	//patch
	{0x098C, 0x0415}, 	// MCU_ADDRESS
	{0x0990, 0xF601},
	{0x0992, 0x42C1},
	{0x0994, 0x0326},
	{0x0996, 0x11F6},
	{0x0998, 0x0143},
	{0x099A, 0xC104},
	{0x099C, 0x260A},
	{0x099E, 0xCC04},
	{0x098C, 0x0425},	// MCU_ADDRESS
	{0x0990, 0x33BD},
	{0x0992, 0xA362},
	{0x0994, 0xBD04},
	{0x0996, 0x3339},
	{0x0998, 0xC6FF},
	{0x099A, 0xF701},
	{0x099C, 0x6439},
	{0x099E, 0xFE01},
	{0x098C, 0x0435 },	// MCU_ADDRESS
	{0x0990, 0x6918},
	{0x0992, 0xCE03},
	{0x0994, 0x25CC},
	{0x0996, 0x0013},
	{0x0998, 0xBDC2},
	{0x099A, 0xB8CC},
	{0x099C, 0x0489},
	{0x099E, 0xFD03},
	{0x098C, 0x0445 },	// MCU_ADDRESS
	{0x0990, 0x27CC},
	{0x0992, 0x0325},
	{0x0994, 0xFD01},
	{0x0996, 0x69FE},
	{0x0998, 0x02BD},
	{0x099A, 0x18CE},
	{0x099C, 0x0339},
	{0x099E, 0xCC00},
	{0x098C, 0x0455 },	// MCU_ADDRESS
	{0x0990, 0x11BD},
	{0x0992, 0xC2B8},
	{0x0994, 0xCC04},
	{0x0996, 0xC8FD},
	{0x0998, 0x0347},
	{0x099A, 0xCC03},
	{0x099C, 0x39FD},
	{0x099E, 0x02BD},
	{0x098C, 0x0465 },	// MCU_ADDRESS
	{0x0990, 0xDE00},
	{0x0992, 0x18CE},
	{0x0994, 0x00C2},
	{0x0996, 0xCC00},
	{0x0998, 0x37BD},
	{0x099A, 0xC2B8},
	{0x099C, 0xCC04},
	{0x099E, 0xEFDD},
	{0x098C, 0x0475 },	// MCU_ADDRESS
	{0x0990, 0xE6CC},
	{0x0992, 0x00C2},
	{0x0994, 0xDD00},
	{0x0996, 0xC601},
	{0x0998, 0xF701},
	{0x099A, 0x64C6},
	{0x099C, 0x03F7},
	{0x099E, 0x0165},
	{0x098C, 0x0485 },	// MCU_ADDRESS
	{0x0990, 0x7F01},
	{0x0992, 0x6639},
	{0x0994, 0x3C3C},
	{0x0996, 0x3C34},
	{0x0998, 0xCC32},
	{0x099A, 0x3EBD},
	{0x099C, 0xA558},
	{0x099E, 0x30ED},
	{0x098C, 0x0495 },	// MCU_ADDRESS
	{0x0990, 0x04BD},
	{0x0992, 0xB2D7},
	{0x0994, 0x30E7},
	{0x0996, 0x06CC},
	{0x0998, 0x323E},
	{0x099A, 0xED00},
	{0x099C, 0xEC04},
	{0x099E, 0xBDA5},
	{0x098C, 0x04A5 },	// MCU_ADDRESS
	{0x0990, 0x44CC},
	{0x0992, 0x3244},
	{0x0994, 0xBDA5},
	{0x0996, 0x585F},
	{0x0998, 0x30ED},
	{0x099A, 0x02CC},
	{0x099C, 0x3244},
	{0x099E, 0xED00},
	{0x098C, 0x04B5 },	// MCU_ADDRESS
	{0x0990, 0xF601},
	{0x0992, 0xD54F},
	{0x0994, 0xEA03},
	{0x0996, 0xAA02},
	{0x0998, 0xBDA5},
	{0x099A, 0x4430},
	{0x099C, 0xE606},
	{0x099E, 0x3838},
	{0x098C, 0x04C5 },	// MCU_ADDRESS
	{0x0990, 0x3831},
	{0x0992, 0x39BD},
	{0x0994, 0xD661},
	{0x0996, 0xF602},
	{0x0998, 0xF4C1},
	{0x099A, 0x0126},
	{0x099C, 0x0BFE},
	{0x099E, 0x02BD},
	{0x098C, 0x04D5 },	// MCU_ADDRESS
	{0x0990, 0xEE10},
	{0x0992, 0xFC02},
	{0x0994, 0xF5AD},
	{0x0996, 0x0039},
	{0x0998, 0xF602},
	{0x099A, 0xF4C1},
	{0x099C, 0x0226},
	{0x099E, 0x0AFE},
	{0x098C, 0x04E5 },	// MCU_ADDRESS
	{0x0990, 0x02BD},
	{0x0992, 0xEE10},
	{0x0994, 0xFC02},
	{0x0996, 0xF7AD},
	{0x0998, 0x0039},
	{0x099A, 0x3CBD},
	{0x099C, 0xB059},
	{0x099E, 0xCC00},
	{0x098C, 0x04F5 },	// MCU_ADDRESS
	{0x0990, 0x28BD},
	{0x0992, 0xA558},
	{0x0994, 0x8300},
	{0x0996, 0x0027},
	{0x0998, 0x0BCC},
	{0x099A, 0x0026},
	{0x099C, 0x30ED},
	{0x099E, 0x00C6},
	{0x098C, 0x0505 },	// MCU_ADDRESS
	{0x0990, 0x03BD},
	{0x0992, 0xA544},
	{0x0994, 0x3839},
	{0x098C, 0x2006 },	// MCU_ADDRESS [MON_ARG1]
	{0x0990, 0x0415 	},// MCU_DATA_0
	{0x098C, 0xA005 },	// MCU_ADDRESS [MON_CMD]
	{0x0990, 0x0001 },	// MCU_DATA_0
	{REG_DELAY,20},
	
	//ccms &awb
	{0x098C, 0xA117}, 	// MCU_ADDRESS [SEQ_PREVIEW_0_AE]
	{0x0990, 0x0002 },	// MCU_DATA_0
	{0x098C, 0xA11D },	// MCU_ADDRESS [SEQ_PREVIEW_1_AE]
	{0x0990, 0x0002 },	// MCU_DATA_0
	{0x098C, 0xA129 },	// MCU_ADDRESS [SEQ_PREVIEW_3_AE]
	{0x0990, 0x0002}, 	// MCU_DATA_0
	{0x098C, 0xA24F}, 	// MCU_ADDRESS [AE_BASETARGET]
	{0x0990, 0x0032}, 	// MCU_DATA_0
	{0x098C, 0xA20C}, 	// MCU_ADDRESS [AE_MAX_INDEX]
	{0x0990, 0x0010}, 	// MCU_DATA_0
	{0x098C, 0xA216}, 	// MCU_ADDRESS
	{0x0990, 0x0091}, 	// MCU_DATA_0
	{0x098C, 0xA20E}, 	// MCU_ADDRESS [AE_MAX_VIRTGAIN]
	{0x0990, 0x0091}, 	// MCU_DATA_0
	{0x098C, 0x2212}, 	// MCU_ADDRESS [AE_MAX_DGAIN_AE1]
	{0x0990, 0x00A4}, 	// MCU_DATA_0
	{0x3210, 0x01B8}, 	// COLOR_PIPELINE_CONTROL
	{0x098C, 0xAB36}, 	// MCU_ADDRESS [RESERVED_HG_36]
	{0x0990, 0x0014}, 	// MCU_DATA_0
	{0x098C, 0x2B66}, 	// MCU_ADDRESS [HG_CLUSTER_DC_BM]
	{0x0990, 0x2AF8}, 	// MCU_DATA_0
	{0x098C, 0xAB20}, 	// MCU_ADDRESS [HG_LL_SAT1]
	{0x0990, 0x0080 },	// MCU_DATA_0
	{0x098C, 0xAB24 },	// MCU_ADDRESS [HG_LL_SAT2]
	{0x0990, 0x0000}, 	// MCU_DATA_0
	{0x098C, 0xAB21}, 	// MCU_ADDRESS [HG_LL_INTERPTHRESH1]
	{0x0990, 0x000A}, 	// MCU_DATA_0
	{0x098C, 0xAB25}, 	// MCU_ADDRESS [HG_LL_INTERPTHRESH2]
	{0x0990, 0x002A },	// MCU_DATA_0
	{0x098C, 0xAB22}, 	// MCU_ADDRESS [HG_LL_APCORR1]
	{0x0990, 0x0007}, 	// MCU_DATA_0
	{0x098C, 0xAB26}, 	// MCU_ADDRESS [HG_LL_APCORR2]
	{0x0990, 0x0001 },	// MCU_DATA_0
	{0x098C, 0xAB23}, 	// MCU_ADDRESS [HG_LL_APTHRESH1]
	{0x0990, 0x0004}, 	// MCU_DATA_0
	{0x098C, 0xAB27}, 	// MCU_ADDRESS [HG_LL_APTHRESH2]
	{0x0990, 0x0009}, 	// MCU_DATA_0
	{0x098C, 0x2B28}, 	// MCU_ADDRESS [HG_LL_BRIGHTNESSSTART]
	{0x0990, 0x0BB8}, 	// MCU_DATA_0
	{0x098C, 0x2B2A}, 	// MCU_ADDRESS [HG_LL_BRIGHTNESSSTOP]
	{0x0990, 0x2968}, 	// MCU_DATA_0
	{0x098C, 0xAB2C}, 	// MCU_ADDRESS [HG_NR_START_R]
	{0x0990, 0x00FF },	// MCU_DATA_0
	{0x098C, 0xAB30}, 	// MCU_ADDRESS [HG_NR_STOP_R]
	{0x0990, 0x00FF },	// MCU_DATA_0
	{0x098C, 0xAB2D}, 	// MCU_ADDRESS [HG_NR_START_G]
	{0x0990, 0x00FF },	// MCU_DATA_0
	{0x098C, 0xAB31}, 	// MCU_ADDRESS [HG_NR_STOP_G]
	{0x0990, 0x00FF}, 	// MCU_DATA_0
	{0x098C, 0xAB2E}, 	// MCU_ADDRESS [HG_NR_START_B]
	{0x0990, 0x00FF}, 	// MCU_DATA_0
	{0x098C, 0xAB32}, 	// MCU_ADDRESS [HG_NR_STOP_B]
	{0x0990, 0x00FF },	// MCU_DATA_0
	{0x098C, 0xAB2F}, 	// MCU_ADDRESS [HG_NR_START_OL]
	{0x0990, 0x000A}, 	// MCU_DATA_0
	{0x098C, 0xAB33}, 	// MCU_ADDRESS [HG_NR_STOP_OL]
	{0x0990, 0x0006}, 	// MCU_DATA_0
	{0x098C, 0xAB34}, 	// MCU_ADDRESS [HG_NR_GAINSTART]
	{0x0990, 0x0020}, 	// MCU_DATA_0
	{0x098C, 0xAB35}, 	// MCU_ADDRESS [HG_NR_GAINSTOP]
	{0x0990, 0x0091}, 	// MCU_DATA_0
	{0x098C, 0xA765}, 	// MCU_ADDRESS [MODE_COMMONMODESETTINGS_FILTER_MODE]
	{0x0990, 0x0006}, 	// MCU_DATA_0
	{0x098C, 0xAB37}, 	// MCU_ADDRESS [HG_GAMMA_MORPH_CTRL]
	{0x0990, 0x0003}, 	// MCU_DATA_0
	{0x098C, 0x2B38}, 	// MCU_ADDRESS [HG_GAMMASTARTMORPH]
	{0x0990, 0x2968}, 	// MCU_DATA_0
	{0x098C, 0x2B3A}, 	// MCU_ADDRESS [HG_GAMMASTOPMORPH]
	{0x0990, 0x2D50}, 	// MCU_DATA_0
	{0x098C, 0x2B62}, 	// MCU_ADDRESS [HG_FTB_START_BM]
	{0x0990, 0xFFFE}, 	// MCU_DATA_0
	{0x098C, 0x2B64}, 	// MCU_ADDRESS [HG_FTB_STOP_BM]
	{0x0990, 0xFFFF}, 	// MCU_DATA_0
	{0x098C, 0xAB4F}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_0]
	{0x0990, 0x0000}, 	// MCU_DATA_0
	{0x098C, 0xAB50 },	// MCU_ADDRESS [HG_GAMMA_TABLE_B_1]
	{0x0990, 0x0013}, 	// MCU_DATA_0
	{0x098C, 0xAB51}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_2]
	{0x0990, 0x0027}, 	// MCU_DATA_0
	{0x098C, 0xAB52}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_3]
	{0x0990, 0x0043}, 	// MCU_DATA_0
	{0x098C, 0xAB53}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_4]
	{0x0990, 0x0068}, 	// MCU_DATA_0
	{0x098C, 0xAB54}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_5]
	{0x0990, 0x0081}, 	// MCU_DATA_0
	{0x098C, 0xAB55}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_6]
	{0x0990, 0x0093}, 	// MCU_DATA_0
	{0x098C, 0xAB56}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_7]
	{0x0990, 0x00A3}, 	// MCU_DATA_0
	{0x098C, 0xAB57}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_8]
	{0x0990, 0x00B0}, 	// MCU_DATA_0
	{0x098C, 0xAB58}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_9]
	{0x0990, 0x00BC}, 	// MCU_DATA_0
	{0x098C, 0xAB59}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_10]
	{0x0990, 0x00C7}, 	// MCU_DATA_0
	{0x098C, 0xAB5A}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_11]
	{0x0990, 0x00D1}, 	// MCU_DATA_0
	{0x098C, 0xAB5B}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_12]
	{0x0990, 0x00DA}, 	// MCU_DATA_0
	{0x098C, 0xAB5C}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_13]
	{0x0990, 0x00E2}, 	// MCU_DATA_0
	{0x098C, 0xAB5D}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_14]
	{0x0990, 0x00E9}, 	// MCU_DATA_0
	{0x098C, 0xAB5E}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_15]
	{0x0990, 0x00EF}, 	// MCU_DATA_0
	{0x098C, 0xAB5F}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_16]
	{0x0990, 0x00F4}, 	// MCU_DATA_0
	{0x098C, 0xAB60}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_17]
	{0x0990, 0x00FA}, 	// MCU_DATA_0
	{0x098C, 0xAB61}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_18]
	{0x0990, 0x00FF}, 	// MCU_DATA_0
	{0x098C, 0x2306}, 	// MCU_ADDRESS [AWB_CCM_L_0]
	{0x0990, 0x01D6}, 	// MCU_DATA_0
	{0x098C, 0x2308}, 	// MCU_ADDRESS [AWB_CCM_L_1]
	{0x0990, 0xFF89}, 	// MCU_DATA_0
	{0x098C, 0x230A}, 	// MCU_ADDRESS [AWB_CCM_L_2]
	{0x0990, 0xFFA1}, 	// MCU_DATA_0
	{0x098C, 0x230C}, 	// MCU_ADDRESS [AWB_CCM_L_3]
	{0x0990, 0xFF73}, 	// MCU_DATA_0
	{0x098C, 0x230E}, 	// MCU_ADDRESS [AWB_CCM_L_4]
	{0x0990, 0x019C}, 	// MCU_DATA_0
	{0x098C, 0x2310}, 	// MCU_ADDRESS [AWB_CCM_L_5]
	{0x0990, 0xFFF1}, 	// MCU_DATA_0
	{0x098C, 0x2312}, 	// MCU_ADDRESS [AWB_CCM_L_6]
	{0x0990, 0xFFB0}, 	// MCU_DATA_0
	{0x098C, 0x2314}, 	// MCU_ADDRESS [AWB_CCM_L_7]
	{0x0990, 0xFF2D}, 	// MCU_DATA_0
	{0x098C, 0x2316}, 	// MCU_ADDRESS [AWB_CCM_L_8]
	{0x0990, 0x0223}, 	// MCU_DATA_0
	{0x098C, 0x2318}, 	// MCU_ADDRESS [AWB_CCM_L_9]
	{0x0990, 0x001C}, 	// MCU_DATA_0
	{0x098C, 0x231A}, 	// MCU_ADDRESS [AWB_CCM_L_10]
	{0x0990, 0x0048}, 	// MCU_DATA_0
	{0x098C, 0x2318}, 	// MCU_ADDRESS [AWB_CCM_L_9]
	{0x0990, 0x001C}, 	// MCU_DATA_0
	{0x098C, 0x231A}, 	// MCU_ADDRESS [AWB_CCM_L_10]
	{0x0990, 0x0038}, 	// MCU_DATA_0
	{0x098C, 0x2318}, 	// MCU_ADDRESS [AWB_CCM_L_9]
	{0x0990, 0x001E}, 	// MCU_DATA_0
	{0x098C, 0x231A}, 	// MCU_ADDRESS [AWB_CCM_L_10]
	{0x0990, 0x0038}, 	// MCU_DATA_0
	{0x098C, 0x2318}, 	// MCU_ADDRESS [AWB_CCM_L_9]
	{0x0990, 0x0022}, 	// MCU_DATA_0
	{0x098C, 0x231A}, 	// MCU_ADDRESS [AWB_CCM_L_10]
	{0x0990, 0x0038}, 	// MCU_DATA_0
	{0x098C, 0x2318}, 	// MCU_ADDRESS [AWB_CCM_L_9]
	{0x0990, 0x002C}, 	// MCU_DATA_0
	{0x098C, 0x231A}, 	// MCU_ADDRESS [AWB_CCM_L_10]
	{0x0990, 0x0038}, 	// MCU_DATA_0
	{0x098C, 0x2318}, 	// MCU_ADDRESS [AWB_CCM_L_9]
	{0x0990, 0x0024}, 	// MCU_DATA_0
	{0x098C, 0x231A}, 	// MCU_ADDRESS [AWB_CCM_L_10]
	{0x0990, 0x0038}, 	// MCU_DATA_0
	{0x098C, 0x231C}, 	// MCU_ADDRESS [AWB_CCM_RL_0]
	{0x0990, 0xFFCD}, 	// MCU_DATA_0
	{0x098C, 0x231E}, 	// MCU_ADDRESS [AWB_CCM_RL_1]
	{0x0990, 0x0023}, 	// MCU_DATA_0
	{0x098C, 0x2320}, 	// MCU_ADDRESS [AWB_CCM_RL_2]
	{0x0990, 0x0010}, 	// MCU_DATA_0
	{0x098C, 0x2322}, 	// MCU_ADDRESS [AWB_CCM_RL_3]
	{0x0990, 0x0026}, 	// MCU_DATA_0
	{0x098C, 0x2324}, 	// MCU_ADDRESS [AWB_CCM_RL_4]
	{0x0990, 0xFFE9}, 	// MCU_DATA_0
	{0x098C, 0x2326}, 	// MCU_ADDRESS [AWB_CCM_RL_5]
	{0x0990, 0xFFF1}, 	// MCU_DATA_0
	{0x098C, 0x2328}, 	// MCU_ADDRESS [AWB_CCM_RL_6]
	{0x0990, 0x003A}, 	// MCU_DATA_0
	{0x098C, 0x232A}, 	// MCU_ADDRESS [AWB_CCM_RL_7]
	{0x0990, 0x005D}, 	// MCU_DATA_0
	{0x098C, 0x232C}, 	// MCU_ADDRESS [AWB_CCM_RL_8]
	{0x0990, 0xFF69}, 	// MCU_DATA_0
	{0x098C, 0x232E}, 	// MCU_ADDRESS [AWB_CCM_RL_9]
	{0x0990, 0x000C}, 	// MCU_DATA_0
	{0x098C, 0x2330}, 	// MCU_ADDRESS [AWB_CCM_RL_10]
	{0x0990, 0xFFE4}, 	// MCU_DATA_0
	{0x098C, 0x232E}, 	// MCU_ADDRESS [AWB_CCM_RL_9]
	{0x0990, 0x000C}, 	// MCU_DATA_0
	{0x098C, 0x2330}, 	// MCU_ADDRESS [AWB_CCM_RL_10]
	{0x0990, 0xFFF4}, 	// MCU_DATA_0
	{0x098C, 0x232E}, 	// MCU_ADDRESS [AWB_CCM_RL_9]
	{0x0990, 0x000A}, 	// MCU_DATA_0
	{0x098C, 0x2330}, 	// MCU_ADDRESS [AWB_CCM_RL_10]
	{0x0990, 0xFFF4}, 	// MCU_DATA_0
	{0x098C, 0x232E}, 	// MCU_ADDRESS [AWB_CCM_RL_9]
	{0x0990, 0x0006}, 	// MCU_DATA_0
	{0x098C, 0x2330}, 	// MCU_ADDRESS [AWB_CCM_RL_10]
	{0x0990, 0xFFF4}, 	// MCU_DATA_0
	{0x098C, 0x232E}, 	// MCU_ADDRESS [AWB_CCM_RL_9]
	{0x0990, 0xFFFC}, 	// MCU_DATA_0
	{0x098C, 0x2330}, 	// MCU_ADDRESS [AWB_CCM_RL_10]
	{0x0990, 0xFFF4}, 	// MCU_DATA_0
	{0x098C, 0x232E}, 	// MCU_ADDRESS [AWB_CCM_RL_9]
	{0x0990, 0x0004}, 	// MCU_DATA_0
	{0x098C, 0x2330}, 	// MCU_ADDRESS [AWB_CCM_RL_10]
	{0x0990, 0xFFF4}, 	// MCU_DATA_0
	
	{0x0018, 0x0028}, 	// STANDBY_CONTROL
	{REG_DELAY,20},
	{0x098C, 0xA103}, 	// MCU_ADDRESS [SEQ_CMD]
	{0x0990, 0x0006}, 	// MCU_DATA_0
	#endif
	{REG_DELAY,100},

		
	// Color Bar …Ë÷√
	
	//{0x098C, 0xA766},		   // MCU_ADDRESS [MODE_COMMONMODESETTINGS_TEST_MODE]
	
	//{0x0990, 0x0003}, // MCU_DATA_0
	
	//{0x098C, 0xA103}, 		// MCU_ADDRESS [SEQ_CMD]
	
	//{0x0990, 0x0006}, // MCU_DATA_0
	//color bar setting end
	

	
};

#define MT9D115_INIT_REGS	\
	(sizeof(mt9d115_init_reg) / sizeof(mt9d115_init_reg[0]))

unsigned short mt9d115_sleep_reg[][2] = {
};

#define MT9D115_SLEEP_REGS	\
	(sizeof(mt9d115_sleep_reg) / sizeof(mt9d115_sleep_reg[0]))

unsigned short mt9d115_wakeup_reg[][2] = {
};

#define MT9D115_WAKEUP_REGS	\
	(sizeof(mt9d115_wakeup_reg) / sizeof(mt9d115_wakeup_reg[0]))

/* Clock configuration: should be expanded to various clock input */
static const struct mt9d115_reg mt9d115_mclk_24mhz[] = {
};

/*
 * Image resolution configuration
 * This SoC supports 5 presets for each preview and capture resolutions
 */
/* Preview configuration preset #0 */
unsigned short mt9d115_preview_vga[][2] = {
	{0x098C, 0xA115}, 	// MCU_ADDRESS [SEQ_CAP_MODE]
	{0x0990, 0x0000}, 	// MCU_DATA_0
	{0x098C, 0xA103}, 	// MCU_ADDRESS [SEQ_CMD]
	{0x0990, 0x0001}, 	// MCU_DATA_0
	{REG_DELAY,100},

	
};

#define MT9D115_VGA_REGS	\
	(sizeof(mt9d115_preview_vga) / sizeof(mt9d115_preview_vga[0]))

//1600*1200
unsigned short mt9d115_capture_uxga[][2] = {

{0x098C, 0x2747}, 	// MCU_ADDRESS [MODE_CROP_X0_B]
{0x0990, 0x0000}, 	// MCU_DATA_0
{0x098C, 0x2749}, 	// MCU_ADDRESS [MODE_CROP_X1_B]
{0x0990, 0x063F}, 	// MCU_DATA_0
{0x098C, 0x274B}, 	// MCU_ADDRESS [MODE_CROP_Y0_B]
{0x0990, 0x0000}, 	// MCU_DATA_0
{0x098C, 0x274D}, 	// MCU_ADDRESS [MODE_CROP_Y1_B]
{0x0990, 0x04AF}, 	// MCU_DATA_0
{0x098C, 0x2707}, 	// MCU_ADDRESS [MODE_OUTPUT_WIDTH_B]
{0x0990, 0x0640}, 	// MCU_DATA_0
{0x098C, 0x2709}, 	// MCU_ADDRESS 
{0x0990, 0x04B0}, 	// MCU_DATA_0

{0x098C, 0xA115}, 	// MCU_ADDRESS [SEQ_CAP_MODE]
{0x0990, 0x0002}, 	// MCU_DATA_0
{0x098C, 0xA103}, 	// MCU_ADDRESS [SEQ_CMD]
{0x0990, 0x0002}, 	// MCU_DATA_0
{REG_DELAY,100},



};

#define MT9D115_UXGA_REGS	\
	(sizeof(mt9d115_capture_uxga) / sizeof(mt9d115_capture_uxga[0]))

/* Preview configuration preset #1 */
/* Preview configuration preset #2 */
/* Preview configuration preset #3 */
/* Preview configuration preset #4 */

/* Capture configuration preset #0 */
/* Capture configuration preset #1 */
/* Capture configuration preset #2 */
/* Capture configuration preset #3 */
/* Capture configuration preset #4 */

/*
 * EV bias
 */

static const struct mt9d115_reg mt9d115_ev_m6[] = {
};

static const struct mt9d115_reg mt9d115_ev_m5[] = {
};

static const struct mt9d115_reg mt9d115_ev_m4[] = {
};

static const struct mt9d115_reg mt9d115_ev_m3[] = {
};

static const struct mt9d115_reg mt9d115_ev_m2[] = {
};

static const struct mt9d115_reg mt9d115_ev_m1[] = {
};

static const struct mt9d115_reg mt9d115_ev_default[] = {
};

static const struct mt9d115_reg mt9d115_ev_p1[] = {
};

static const struct mt9d115_reg mt9d115_ev_p2[] = {
};

static const struct mt9d115_reg mt9d115_ev_p3[] = {
};

static const struct mt9d115_reg mt9d115_ev_p4[] = {
};

static const struct mt9d115_reg mt9d115_ev_p5[] = {
};

static const struct mt9d115_reg mt9d115_ev_p6[] = {
};



#endif
