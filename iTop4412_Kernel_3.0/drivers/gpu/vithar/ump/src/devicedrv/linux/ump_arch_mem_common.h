/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _UMP_MEM_COMMON_H_
#define _UMP_MEM_COMMON_H_

/* 15 bits for the UMP ID (allowing 32768 IDs) */
#define UMP_LINUX_ID_BITS 15
#define UMP_LINUX_ID_MASK ((1ULL << UMP_LINUX_ID_BITS) - 1ULL)

/* 64-bit (really 52 bits) encoding: 15 bits for the ID, 37 bits for the offset */
#define UMP_LINUX_OFFSET_BITS_64 37
#define UMP_LINUX_OFFSET_MASK_64 ((1ULL << UMP_LINUX_OFFSET_BITS_64)-1)
/* 32-bit encoding: 15 bits for the ID, 17 bits for the offset */
#define UMP_LINUX_OFFSET_BITS_32 17
#define UMP_LINUX_OFFSET_MASK_32 ((1ULL << UMP_LINUX_OFFSET_BITS_32)-1)

#if __SIZEOF_LONG__ == 8
#define UMP_LINUX_OFFSET_BITS UMP_LINUX_OFFSET_BITS_64
#define UMP_LINUX_OFFSET_MASK UMP_LINUX_OFFSET_MASK_64
#else
#define UMP_LINUX_OFFSET_BITS UMP_LINUX_OFFSET_BITS_32
#define UMP_LINUX_OFFSET_MASK UMP_LINUX_OFFSET_MASK_32
#endif


#endif /* _UMP_MEM_COMMON_H_ */
