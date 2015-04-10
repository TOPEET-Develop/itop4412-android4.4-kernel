/* linux/arch/arm/mach-exynos4/idle.S
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS4210 AFTR/LPA idle support
 * Based on S3C2410 sleep code by:
 *	Ben Dooks, (c) 2004 Simtec Electronics
 *
 * Based on PXA/SA1100 sleep code by:
 *	Nicolas Pitre, (c) 2002 Monta Vista Software Inc
 *	Cliff Brake, (c) 2001
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <linux/linkage.h>
#include <asm/assembler.h>
#include <asm/memory.h>
#include <plat/map-base.h>
#include <plat/map-s5p.h>
#include <mach/smc.h>

	.text

	/*
	 * exynos4_enter_lp
	 *
	 * entry:
	 *	r1 = v:p offset
	 */

ENTRY(exynos4_enter_lp)
	stmfd	sp!, { r3 - r12, lr }

	adr	r0, sleep_save_misc

	mrc	p15, 0, r2, c15, c0, 0	@ read power control register
	str	r2, [r0], #4

	mrc	p15, 0, r2, c15, c0, 1	@ read diagnostic register
	str	r2, [r0], #4

	ldr	r3, =resume_with_mmu
	bl	cpu_suspend

	mov	r0, sp

	mrc	p15, 0, r1, c2, c0, 0	@ TTB 0
	mov	r2, r1, lsr #14		@ get TTB0 base
	mov	r1, r2, lsl #14
	bl	exynos4_flush_cache

	adr	r0, sys_pwr_conf_addr
	ldr	r1, [r0]
	ldr	r2, [r1]
	bic	r2, r2, #(1<<16)
	str	r2, [r1]

#ifdef CONFIG_ARM_TRUSTZONE
	ldr	r0, =SMC_CMD_CPU0AFTR
	mov	r1, #0
	mov	r2, #0
	mov	r3, #0
	smc	0
#else
	dsb
	wfi
#endif

	/* Restore original sp */
	mov	r0, sp
	add	r0, r0, #4
	ldr	sp, [r0]

	mov	r0, #0
	b	early_wakeup

resume_with_mmu:
	/* Enable L2 cache */
#ifdef CONFIG_ARM_TRUSTZONE
	ldr	r0, =SMC_CMD_L2X0CTRL
	mov	r1, #1
	mov	r2, #0
	mov	r3, #0
	smc	0
#else
	mov	r0, #1
	ldr	r1, =0xF8600000
	str	r0, [r1, #0x100]
#endif
	adr	r0, sleep_save_misc

#ifdef CONFIG_ARM_TRUSTZONE
	ldr	r1, [r0], #4
	ldr	r2, [r0], #4
	ldr	r0, =SMC_CMD_C15RESUME
	mov	r3, #0
	smc	0
#else
	ldr	r1, [r0], #4
	mcr	p15, 0, r1, c15, c0, 0	@ write power control register

	ldr	r1, [r0], #4
	mcr	p15, 0, r1, c15, c0, 1	@ write diagnostic register
#endif

	mov	r0, #1
early_wakeup:

	ldmfd	sp!, { r3 - r12, pc }

	.ltorg

	/*
	 * sleep magic, to allow the bootloader to check for an valid
	 * image to resume to. Must be the first word before the
	 * s3c_cpu_resume entry.
	 */

	.word	0x2bedf00d

sleep_save_misc:
	.long	0
	.long	0

	.global sys_pwr_conf_addr
sys_pwr_conf_addr:
	.long	0

	/*
	 * exynos4_idle_resume
	 *
	 * resume code entry for IROM to call
	 *
	 * we must put this code here in the data segment as we have no
	 * other way of restoring the stack pointer after sleep, and we
	 * must not write to the code segment (code is read-only)
	 */

ENTRY(exynos4_idle_resume)
	/* SCU enable */
	ldr	r1, =0x10500000
	ldr	r0, [r1]
	orr	r0, r0, #1
	orr	r0, r0, #(1 << 5)
	str	r0, [r1]

	ldr	r1, =0x10000000

	/* Read CHIP ID */
	ldr	r0, [r1]
	mov	r0, r0, lsr #12
	/* Check soc id */
	ldr	r2, =0x43210
	cmp	r0, r2
#ifdef CONFIG_ARM_TRUSTZONE
	ldr	r0, =SMC_CMD_L2X0SETUP1
	ldr	r1, =0x110
	ldrne	r2, =0x110
	ldreq	r2, =0x120
	ldr	r3, =0x30000007
	smc	0

	ldr	r0, =SMC_CMD_L2X0SETUP2
	ldr	r1, =0x3
	ldr	r2, =0x7C470001
	ldr	r3, =0xC200FFFF
	smc	0
#else
	bne	exynos4212_l2_cache

	/* Outer cache TAG,DATA latency */
	ldr	r1, =0x10502000
	mov	r0, #0x110
	str	r0, [r1, #0x108]
	str	r0, [r1, #0x10C]

	/* L2 cache prefetch control register */
	ldr	r0, =0x30000007
	str	r0, [r1, #0xF60]

	b	pwr_ctrl_regster

exynos4212_l2_cache:
	/* Outer cache TAG,DATA latency */
	ldr	r1, =0x10502000
	mov	r0, #0x110
	str	r0, [r1, #0x108]
	mov	r0, #0x120
	str	r0, [r1, #0x10C]

	/* L2 cache prefetch control register */
	ldr	r0, =0x30000007
	str	r0, [r1, #0xF60]

pwr_ctrl_regster:
	/* Power control register setting*/
	mov	r0, #0x3
	str	r0, [r1, #0xF80]

	ldr	r0, [r1, #0x104]
	ldr	r2, =0x7c470001
	ldr	r3, =0xc200ffff

	and	r0, r0, r3
	orr	r0, r0, r2
	str	r0, [r1, #0x104]
#endif

	b	cpu_resume
