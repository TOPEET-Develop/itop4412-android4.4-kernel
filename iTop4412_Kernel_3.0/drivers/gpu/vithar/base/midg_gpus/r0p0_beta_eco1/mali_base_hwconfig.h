/*
 * Copyright:
 * ----------------------------------------------------------------------------
 * This confidential and proprietary software may be used only as authorized
 * by a licensing agreement from ARM Limited.
 *      (C) COPYRIGHT 2011 ARM Limited, ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorized copies and
 * copies may only be made to the extent permitted by a licensing agreement
 * from ARM Limited.
 * ----------------------------------------------------------------------------
 */

#ifndef _BASE_HWCONFIG_H_
#define _BASE_HWCONFIG_H_

/** Clarifications requested to First Vertex Index.
 *  Note this reference needs to be replaced with a proper issue raised against the HW Beta.
 */
#define BASE_HW_ISSUE_999   1

/** Tiler triggers a fault if the scissor rectangle is empty. */
#define BASE_HW_ISSUE_5699  1

/** Soft-stopped jobs should cause the job slot to stall until the software has cleared the IRQ. */
#define BASE_HW_ISSUE_5713  1

/** Framebuffer output smaller than 6 pixels causes hang. */
#define BASE_HW_ISSUE_5753  1

/* Transaction Elimination doesn't work correctly. */
#define BASE_HW_ISSUE_5907  1

/* Multisample write mask must be set to all 1s. */
#define BASE_HW_ISSUE_5936  1

/* Job can get stuck on hardware after a page fault */
#define BASE_HW_ISSUE_6035  1

/* Hierarchical tiling doesn't work properly. */
#define BASE_HW_ISSUE_6097  1

/* Depth texture read of D24S8 hangs the FPGA */
#define BASE_HW_ISSUE_6156 1

/* Readback with negative stride doesn't work properly. */
#define BASE_HW_ISSUE_6325  1

/* Using 8xMSAA surfaces produces incorrect output */
#define BASE_HW_ISSUE_6352  1



#endif /* _BASE_HWCONFIG_H_ */
