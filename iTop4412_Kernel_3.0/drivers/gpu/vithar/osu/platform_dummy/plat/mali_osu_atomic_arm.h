/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_osu_atomic_arm.h
 * arm-specific atomic functions for the OSU module
 */

#ifndef _OSU_ATOMIC_ARM_H_
#define _OSU_ATOMIC_ARM_H_

#include <base/mali_base_debug.h>

static INLINE u32 osu_atomic_get(const osu_atomic *atom)
{
	BDBG_ASSERT_POINTER(atom);
	return atom->osup_internal_struct.val;
}

static INLINE void osu_atomic_set(osu_atomic *atom, u32 val)
{
	u32 tmp;
	volatile u32 *aval;

	BDBG_ASSERT_POINTER(atom);

	aval = &atom->osup_internal_struct.val;

	dmb();
	__asm__ volatile("1:	ldrex	%[tmp], [%[addr]]\n"
			 "	strex	%[tmp], %[val], [%[addr]]\n"
			 "	cmp	%[tmp], #0\n"
			 "	bne	1b"
			 : [tmp] "=&r" (tmp), "+Qo" (*aval)
			 : [val] "r" (val), [addr] "r" (aval)
			 : "cc");
	dmb();
}

static INLINE u32 osu_atomic_add(osu_atomic *atom, u32 val)
{
	u32 res;
	u32 tmp;
	volatile u32 *aval;

	BDBG_ASSERT_POINTER(atom);

	aval = &atom->osup_internal_struct.val;

	dmb();
	__asm__ volatile("1:	ldrex	%[res], [%[addr]]\n"
			 "	add	%[res], %[res], %[val]\n"
			 "	strex	%[tmp], %[res], [%[addr]]\n"
			 "	cmp	%[tmp], #0\n"
			 "	bne	1b"
			 : [tmp] "=&r" (tmp), [res] "=&r" (res), "+Qo" (*aval)
			 : [addr] "r" (aval), [val] "r" (val)
			 : "cc");
	dmb();
	return res;
}

static INLINE u32 osu_atomic_sub(osu_atomic *atom, u32 val)
{
	u32 res;
	u32 tmp;
	volatile u32 *aval;

	BDBG_ASSERT_POINTER(atom);

	aval = &atom->osup_internal_struct.val;

	dmb();
	__asm__ volatile("1:	ldrex	%[res], [%[addr]]\n"
			 "	sub	%[res], %[res], %[val]\n"
			 "	strex	%[tmp], %[res], [%[addr]]\n"
			 "	cmp	%[tmp], #0\n"
			 "	bne	1b"
			 : [tmp] "=&r" (tmp), [res] "=&r" (res), "+Qo" (*aval)
			 : [addr] "r" (aval), [val] "r" (val)
			 : "cc");
	dmb();
	return res;
}

/* Note: the kernel provided VDSO to perform CAS returns zero for
 * success/non-zero for failure. OSU expects the return value to be the value
 * that was in memory  */
static INLINE u32 osu_atomic_compare_and_swap(osu_atomic *atom, u32 old_value,
					      u32 new_value)
{
	u32 res;
	u32 tmp;
	volatile u32 *aval;

	BDBG_ASSERT_POINTER(atom);

	aval = &atom->osup_internal_struct.val;

	dmb();
	__asm__ volatile("1:	ldrex	%[res], [%[addr]]\n"
			 "	mov     %[tmp], #0\n"
			 "	cmp	%[res], %[old_value]\n"
			 "      it	eq\n"
			 "	strexeq	%[tmp], %[new_value], [%[addr]]\n"
			 "	cmp	%[tmp], #0\n"
			 "	bne	1b\n"
			 : [tmp] "=&r" (tmp), [res] "=&r" (res), "+Qo" (*aval)
			 : [addr] "r" (aval), [new_value] "r" (new_value), [old_value] "r" (old_value)
			 : "cc");
	dmb();
	return res;
}

#endif /* _OSU_ATOMIC_ARM_H_ */
