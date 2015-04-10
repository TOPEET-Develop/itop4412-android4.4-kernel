
wmt_core.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <opfunc_stp_rst>:
       0:	e1a0c00d 	mov	ip, sp
       4:	e92dd800 	push	{fp, ip, lr, pc}
       8:	e24cb004 	sub	fp, ip, #4
       c:	e3a00000 	mov	r0, #0
      10:	e89da800 	ldm	sp, {fp, sp, pc}

00000014 <wmt_core_patch_check>:
      14:	e1a0c00d 	mov	ip, sp
      18:	e92dd800 	push	{fp, ip, lr, pc}
      1c:	e24cb004 	sub	fp, ip, #4
      20:	e24dd008 	sub	sp, sp, #8
      24:	e0213000 	eor	r3, r1, r0
      28:	e1a0c000 	mov	ip, r0
      2c:	e31300f0 	tst	r3, #240	; 0xf0
      30:	03a00001 	moveq	r0, #1
      34:	0a000006 	beq	54 <wmt_core_patch_check+0x40>
      38:	e1a03001 	mov	r3, r1
      3c:	e59f0018 	ldr	r0, [pc, #24]	; 5c <wmt_core_patch_check+0x48>
      40:	e59f1018 	ldr	r1, [pc, #24]	; 60 <wmt_core_patch_check+0x4c>
      44:	e30023a3 	movw	r2, #931	; 0x3a3
      48:	e58dc000 	str	ip, [sp]
      4c:	ebfffffe 	bl	0 <osal_err_print>
      50:	e3a00000 	mov	r0, #0
      54:	e24bd00c 	sub	sp, fp, #12
      58:	e89da800 	ldm	sp, {fp, sp, pc}
	...

00000064 <wmt_core_opid_handler>:
      64:	e1a0c00d 	mov	ip, sp
      68:	e92dd800 	push	{fp, ip, lr, pc}
      6c:	e24cb004 	sub	fp, ip, #4
      70:	e5903000 	ldr	r3, [r0]
      74:	e59f102c 	ldr	r1, [pc, #44]	; a8 <wmt_core_opid_handler+0x44>
      78:	e0812103 	add	r2, r1, r3, lsl #2
      7c:	e5922018 	ldr	r2, [r2, #24]
      80:	e3520000 	cmp	r2, #0
      84:	0a000001 	beq	90 <wmt_core_opid_handler+0x2c>
      88:	e12fff32 	blx	r2
      8c:	e89da800 	ldm	sp, {fp, sp, pc}
      90:	e2811064 	add	r1, r1, #100	; 0x64
      94:	e3002209 	movw	r2, #521	; 0x209
      98:	e59f000c 	ldr	r0, [pc, #12]	; ac <wmt_core_opid_handler+0x48>
      9c:	ebfffffe 	bl	0 <osal_err_print>
      a0:	e3e00001 	mvn	r0, #1
      a4:	e89da800 	ldm	sp, {fp, sp, pc}
      a8:	00000000 	andeq	r0, r0, r0
      ac:	00000048 	andeq	r0, r0, r8, asr #32

000000b0 <wmt_core_opid>:
      b0:	e1a0c00d 	mov	ip, sp
      b4:	e92dd800 	push	{fp, ip, lr, pc}
      b8:	e24cb004 	sub	fp, ip, #4
      bc:	e2503000 	subs	r3, r0, #0
      c0:	0a00000a 	beq	f0 <wmt_core_opid+0x40>
      c4:	e5933000 	ldr	r3, [r3]
      c8:	e3530012 	cmp	r3, #18
      cc:	8a000001 	bhi	d8 <wmt_core_opid+0x28>
      d0:	ebfffffe 	bl	64 <wmt_core_opid_handler>
      d4:	e89da800 	ldm	sp, {fp, sp, pc}
      d8:	e59f0028 	ldr	r0, [pc, #40]	; 108 <wmt_core_opid+0x58>
      dc:	e3002219 	movw	r2, #537	; 0x219
      e0:	e59f1024 	ldr	r1, [pc, #36]	; 10c <wmt_core_opid+0x5c>
      e4:	ebfffffe 	bl	0 <osal_err_print>
      e8:	e3e00001 	mvn	r0, #1
      ec:	e89da800 	ldm	sp, {fp, sp, pc}
      f0:	e59f0018 	ldr	r0, [pc, #24]	; 110 <wmt_core_opid+0x60>
      f4:	e3002213 	movw	r2, #531	; 0x213
      f8:	e59f100c 	ldr	r1, [pc, #12]	; 10c <wmt_core_opid+0x5c>
      fc:	ebfffffe 	bl	0 <osal_err_print>
     100:	e3e00000 	mvn	r0, #0
     104:	e89da800 	ldm	sp, {fp, sp, pc}
     108:	0000008c 	andeq	r0, r0, ip, lsl #1
     10c:	0000007c 	andeq	r0, r0, ip, ror r0
     110:	0000006c 	andeq	r0, r0, ip, rrx

00000114 <wmt_core_deinit>:
     114:	e1a0c00d 	mov	ip, sp
     118:	e92dd800 	push	{fp, ip, lr, pc}
     11c:	e24cb004 	sub	fp, ip, #4
     120:	e3000000 	movw	r0, #0
     124:	e3a01000 	mov	r1, #0
     128:	e3a02054 	mov	r2, #84	; 0x54
     12c:	e3400000 	movt	r0, #0
     130:	ebfffffe 	bl	0 <osal_memset>
     134:	e3a00000 	mov	r0, #0
     138:	e89da800 	ldm	sp, {fp, sp, pc}

0000013c <wmt_core_init>:
     13c:	e1a0c00d 	mov	ip, sp
     140:	e92dd800 	push	{fp, ip, lr, pc}
     144:	e24cb004 	sub	fp, ip, #4
     148:	e3a02054 	mov	r2, #84	; 0x54
     14c:	e59f0020 	ldr	r0, [pc, #32]	; 174 <wmt_core_init+0x38>
     150:	e3a01000 	mov	r1, #0
     154:	ebfffffe 	bl	0 <osal_memset>
     158:	e59f3018 	ldr	r3, [pc, #24]	; 178 <wmt_core_init+0x3c>
     15c:	e3a00000 	mov	r0, #0
     160:	e2832024 	add	r2, r3, #36	; 0x24
     164:	e5a30004 	str	r0, [r3, #4]!
     168:	e1530002 	cmp	r3, r2
     16c:	1afffffc 	bne	164 <wmt_core_init+0x28>
     170:	e89da800 	ldm	sp, {fp, sp, pc}
     174:	00000000 	andeq	r0, r0, r0
     178:	fffffffc 			; <UNDEFINED> instruction: 0xfffffffc

0000017c <wmt_core_dump_data>:
     17c:	e1a0c00d 	mov	ip, sp
     180:	e92dd8f0 	push	{r4, r5, r6, r7, fp, ip, lr, pc}
     184:	e24cb004 	sub	fp, ip, #4
     188:	e59f40a4 	ldr	r4, [pc, #164]	; 234 <wmt_core_dump_data+0xb8>
     18c:	e1a06000 	mov	r6, r0
     190:	e1a05002 	mov	r5, r2
     194:	e5943000 	ldr	r3, [r4]
     198:	e3530001 	cmp	r3, #1
     19c:	9a000005 	bls	1b8 <wmt_core_dump_data+0x3c>
     1a0:	e1a02001 	mov	r2, r1
     1a4:	e1a03005 	mov	r3, r5
     1a8:	e59f0088 	ldr	r0, [pc, #136]	; 238 <wmt_core_dump_data+0xbc>
     1ac:	e59f1088 	ldr	r1, [pc, #136]	; 23c <wmt_core_dump_data+0xc0>
     1b0:	ebfffffe 	bl	0 <osal_info_print>
     1b4:	e5943000 	ldr	r3, [r4]
     1b8:	e3550000 	cmp	r5, #0
     1bc:	0a000016 	beq	21c <wmt_core_dump_data+0xa0>
     1c0:	e3a02000 	mov	r2, #0
     1c4:	e1a07002 	mov	r7, r2
     1c8:	ea000000 	b	1d0 <wmt_core_dump_data+0x54>
     1cc:	e5943000 	ldr	r3, [r4]
     1d0:	e312000f 	tst	r2, #15
     1d4:	1a000005 	bne	1f0 <wmt_core_dump_data+0x74>
     1d8:	e3530001 	cmp	r3, #1
     1dc:	e59f1058 	ldr	r1, [pc, #88]	; 23c <wmt_core_dump_data+0xc0>
     1e0:	e59f0058 	ldr	r0, [pc, #88]	; 240 <wmt_core_dump_data+0xc4>
     1e4:	9a000008 	bls	20c <wmt_core_dump_data+0x90>
     1e8:	ebfffffe 	bl	0 <osal_info_print>
     1ec:	e5943000 	ldr	r3, [r4]
     1f0:	e3530001 	cmp	r3, #1
     1f4:	e59f1040 	ldr	r1, [pc, #64]	; 23c <wmt_core_dump_data+0xc0>
     1f8:	e59f0044 	ldr	r0, [pc, #68]	; 244 <wmt_core_dump_data+0xc8>
     1fc:	9a000002 	bls	20c <wmt_core_dump_data+0x90>
     200:	e7d62007 	ldrb	r2, [r6, r7]
     204:	ebfffffe 	bl	0 <osal_info_print>
     208:	e5943000 	ldr	r3, [r4]
     20c:	e2877001 	add	r7, r7, #1
     210:	e1570005 	cmp	r7, r5
     214:	e1a02007 	mov	r2, r7
     218:	1affffeb 	bne	1cc <wmt_core_dump_data+0x50>
     21c:	e3530001 	cmp	r3, #1
     220:	989da8f0 	ldmls	sp, {r4, r5, r6, r7, fp, sp, pc}
     224:	e59f1010 	ldr	r1, [pc, #16]	; 23c <wmt_core_dump_data+0xc0>
     228:	e59f0018 	ldr	r0, [pc, #24]	; 248 <wmt_core_dump_data+0xcc>
     22c:	ebfffffe 	bl	0 <osal_info_print>
     230:	e89da8f0 	ldm	sp, {r4, r5, r6, r7, fp, sp, pc}
     234:	00000000 	andeq	r0, r0, r0
     238:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
     23c:	0000008c 	andeq	r0, r0, ip, lsl #1
     240:	000000c8 	andeq	r0, r0, r8, asr #1
     244:	000000d8 	ldrdeq	r0, [r0], -r8
     248:	000000f0 	strdeq	r0, [r0], -r0	; <UNPREDICTABLE>

0000024c <opfunc_gpio_ctrl>:
     24c:	e1a0c00d 	mov	ip, sp
     250:	e92dd8f0 	push	{r4, r5, r6, r7, fp, ip, lr, pc}
     254:	e24cb004 	sub	fp, ip, #4
     258:	e24dd008 	sub	sp, sp, #8
     25c:	e59f409c 	ldr	r4, [pc, #156]	; 300 <opfunc_gpio_ctrl+0xb4>
     260:	e5943010 	ldr	r3, [r4, #16]
     264:	e3530002 	cmp	r3, #2
     268:	1a000018 	bne	2d0 <opfunc_gpio_ctrl+0x84>
     26c:	e5943050 	ldr	r3, [r4, #80]	; 0x50
     270:	e593300c 	ldr	r3, [r3, #12]
     274:	e3530000 	cmp	r3, #0
     278:	0a00001a 	beq	2e8 <opfunc_gpio_ctrl+0x9c>
     27c:	e59f2080 	ldr	r2, [pc, #128]	; 304 <opfunc_gpio_ctrl+0xb8>
     280:	e5907010 	ldr	r7, [r0, #16]
     284:	e5906008 	ldr	r6, [r0, #8]
     288:	e5922000 	ldr	r2, [r2]
     28c:	e590500c 	ldr	r5, [r0, #12]
     290:	e3520001 	cmp	r2, #1
     294:	9a000007 	bls	2b8 <opfunc_gpio_ctrl+0x6c>
     298:	e1a03005 	mov	r3, r5
     29c:	e59f0064 	ldr	r0, [pc, #100]	; 308 <opfunc_gpio_ctrl+0xbc>
     2a0:	e1a02006 	mov	r2, r6
     2a4:	e59f1060 	ldr	r1, [pc, #96]	; 30c <opfunc_gpio_ctrl+0xc0>
     2a8:	e58d7000 	str	r7, [sp]
     2ac:	ebfffffe 	bl	0 <osal_info_print>
     2b0:	e5943050 	ldr	r3, [r4, #80]	; 0x50
     2b4:	e593300c 	ldr	r3, [r3, #12]
     2b8:	e1a00006 	mov	r0, r6
     2bc:	e1a01005 	mov	r1, r5
     2c0:	e1a02007 	mov	r2, r7
     2c4:	e12fff33 	blx	r3
     2c8:	e24bd01c 	sub	sp, fp, #28
     2cc:	e89da8f0 	ldm	sp, {r4, r5, r6, r7, fp, sp, pc}
     2d0:	e59f0038 	ldr	r0, [pc, #56]	; 310 <opfunc_gpio_ctrl+0xc4>
     2d4:	e3a02e7f 	mov	r2, #2032	; 0x7f0
     2d8:	e59f102c 	ldr	r1, [pc, #44]	; 30c <opfunc_gpio_ctrl+0xc0>
     2dc:	ebfffffe 	bl	0 <osal_err_print>
     2e0:	e3e00000 	mvn	r0, #0
     2e4:	eafffff7 	b	2c8 <opfunc_gpio_ctrl+0x7c>
     2e8:	e59f0024 	ldr	r0, [pc, #36]	; 314 <opfunc_gpio_ctrl+0xc8>
     2ec:	e30027f5 	movw	r2, #2037	; 0x7f5
     2f0:	e59f1014 	ldr	r1, [pc, #20]	; 30c <opfunc_gpio_ctrl+0xc0>
     2f4:	ebfffffe 	bl	0 <osal_err_print>
     2f8:	e3e00000 	mvn	r0, #0
     2fc:	eafffff1 	b	2c8 <opfunc_gpio_ctrl+0x7c>
	...
     308:	0000016c 	andeq	r0, r0, ip, ror #2
     30c:	000000a0 	andeq	r0, r0, r0, lsr #1
     310:	00000104 	andeq	r0, r0, r4, lsl #2
     314:	00000130 	andeq	r0, r0, r0, lsr r1

00000318 <opfunc_hif_conf>:
     318:	e1a0c00d 	mov	ip, sp
     31c:	e92dd830 	push	{r4, r5, fp, ip, lr, pc}
     320:	e24cb004 	sub	fp, ip, #4
     324:	e5903004 	ldr	r3, [r0, #4]
     328:	e1a04000 	mov	r4, r0
     32c:	e3130001 	tst	r3, #1
     330:	0a000021 	beq	3bc <opfunc_hif_conf+0xa4>
     334:	e59f3098 	ldr	r3, [pc, #152]	; 3d4 <opfunc_hif_conf+0xbc>
     338:	e5932024 	ldr	r2, [r3, #36]	; 0x24
     33c:	e3120001 	tst	r2, #1
     340:	1a00000e 	bne	380 <opfunc_hif_conf+0x68>
     344:	e3822001 	orr	r2, r2, #1
     348:	e5832024 	str	r2, [r3, #36]	; 0x24
     34c:	e59f3084 	ldr	r3, [pc, #132]	; 3d8 <opfunc_hif_conf+0xc0>
     350:	e5933000 	ldr	r3, [r3]
     354:	e3530001 	cmp	r3, #1
     358:	9a000002 	bls	368 <opfunc_hif_conf+0x50>
     35c:	e59f0078 	ldr	r0, [pc, #120]	; 3dc <opfunc_hif_conf+0xc4>
     360:	e59f1078 	ldr	r1, [pc, #120]	; 3e0 <opfunc_hif_conf+0xc8>
     364:	ebfffffe 	bl	0 <osal_info_print>
     368:	e2841008 	add	r1, r4, #8
     36c:	e3a02028 	mov	r2, #40	; 0x28
     370:	e59f006c 	ldr	r0, [pc, #108]	; 3e4 <opfunc_hif_conf+0xcc>
     374:	ebfffffe 	bl	0 <osal_memcpy>
     378:	e3a00000 	mov	r0, #0
     37c:	e89da830 	ldm	sp, {r4, r5, fp, sp, pc}
     380:	e59f2050 	ldr	r2, [pc, #80]	; 3d8 <opfunc_hif_conf+0xc0>
     384:	e5922000 	ldr	r2, [r2]
     388:	e3520001 	cmp	r2, #1
     38c:	9afffff5 	bls	368 <opfunc_hif_conf+0x50>
     390:	e5932028 	ldr	r2, [r3, #40]	; 0x28
     394:	e59f1044 	ldr	r1, [pc, #68]	; 3e0 <opfunc_hif_conf+0xc8>
     398:	e5903008 	ldr	r3, [r0, #8]
     39c:	e59f0044 	ldr	r0, [pc, #68]	; 3e8 <opfunc_hif_conf+0xd0>
     3a0:	ebfffffe 	bl	0 <osal_info_print>
     3a4:	e2841008 	add	r1, r4, #8
     3a8:	e3a02028 	mov	r2, #40	; 0x28
     3ac:	e59f0030 	ldr	r0, [pc, #48]	; 3e4 <opfunc_hif_conf+0xcc>
     3b0:	ebfffffe 	bl	0 <osal_memcpy>
     3b4:	e3a00000 	mov	r0, #0
     3b8:	e89da830 	ldm	sp, {r4, r5, fp, sp, pc}
     3bc:	e59f0028 	ldr	r0, [pc, #40]	; 3ec <opfunc_hif_conf+0xd4>
     3c0:	e30023e7 	movw	r2, #999	; 0x3e7
     3c4:	e59f1014 	ldr	r1, [pc, #20]	; 3e0 <opfunc_hif_conf+0xc8>
     3c8:	ebfffffe 	bl	0 <osal_err_print>
     3cc:	e3e00000 	mvn	r0, #0
     3d0:	e89da830 	ldm	sp, {r4, r5, fp, sp, pc}
	...
     3dc:	00000208 	andeq	r0, r0, r8, lsl #4
     3e0:	000000b4 	strheq	r0, [r0], -r4
     3e4:	00000028 	andeq	r0, r0, r8, lsr #32
     3e8:	000001c4 	andeq	r0, r0, r4, asr #3
     3ec:	0000019c 	muleq	r0, ip, r1

000003f0 <wmt_core_ctrl>:
     3f0:	e1a0c00d 	mov	ip, sp
     3f4:	e92dddf0 	push	{r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}
     3f8:	e24cb004 	sub	fp, ip, #4
     3fc:	e24dd058 	sub	sp, sp, #88	; 0x58
     400:	e2517000 	subs	r7, r1, #0
     404:	e1a08000 	mov	r8, r0
     408:	01a06007 	moveq	r6, r7
     40c:	e24b0068 	sub	r0, fp, #104	; 0x68
     410:	15976000 	ldrne	r6, [r7]
     414:	e3520000 	cmp	r2, #0
     418:	01a05002 	moveq	r5, r2
     41c:	e1a0a002 	mov	sl, r2
     420:	15925000 	ldrne	r5, [r2]
     424:	e50b8068 	str	r8, [fp, #-104]	; 0xffffff98
     428:	e50b6064 	str	r6, [fp, #-100]	; 0xffffff9c
     42c:	e50b5060 	str	r5, [fp, #-96]	; 0xffffffa0
     430:	ebfffffe 	bl	0 <wmt_ctrl>
     434:	e2504000 	subs	r4, r0, #0
     438:	1a000008 	bne	460 <wmt_core_ctrl+0x70>
     43c:	e3570000 	cmp	r7, #0
     440:	151b3064 	ldrne	r3, [fp, #-100]	; 0xffffff9c
     444:	15873000 	strne	r3, [r7]
     448:	e35a0000 	cmp	sl, #0
     44c:	151b3060 	ldrne	r3, [fp, #-96]	; 0xffffffa0
     450:	158a3000 	strne	r3, [sl]
     454:	e1a00004 	mov	r0, r4
     458:	e24bd024 	sub	sp, fp, #36	; 0x24
     45c:	e89dadf0 	ldm	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
     460:	e1a03008 	mov	r3, r8
     464:	e59f102c 	ldr	r1, [pc, #44]	; 498 <wmt_core_ctrl+0xa8>
     468:	e300222f 	movw	r2, #559	; 0x22f
     46c:	e59f0028 	ldr	r0, [pc, #40]	; 49c <wmt_core_ctrl+0xac>
     470:	e58d6000 	str	r6, [sp]
     474:	e58d5004 	str	r5, [sp, #4]
     478:	e58d4008 	str	r4, [sp, #8]
     47c:	ebfffffe 	bl	0 <osal_err_print>
     480:	e59f1018 	ldr	r1, [pc, #24]	; 4a0 <wmt_core_ctrl+0xb0>
     484:	e3a02e23 	mov	r2, #560	; 0x230
     488:	e59f3014 	ldr	r3, [pc, #20]	; 4a4 <wmt_core_ctrl+0xb4>
     48c:	e59f0014 	ldr	r0, [pc, #20]	; 4a8 <wmt_core_ctrl+0xb8>
     490:	ebfffffe 	bl	0 <osal_err_print>
     494:	eaffffee 	b	454 <wmt_core_ctrl+0x64>
     498:	000000c4 	andeq	r0, r0, r4, asr #1
     49c:	0000022c 	andeq	r0, r0, ip, lsr #4
     4a0:	0000027c 	andeq	r0, r0, ip, ror r2
     4a4:	000002ac 	andeq	r0, r0, ip, lsr #5
     4a8:	0000026c 	andeq	r0, r0, ip, ror #4

000004ac <opfunc_hw_rst>:
     4ac:	e1a0c00d 	mov	ip, sp
     4b0:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
     4b4:	e24cb004 	sub	fp, ip, #4
     4b8:	e24dd02c 	sub	sp, sp, #44	; 0x2c
     4bc:	e59f5328 	ldr	r5, [pc, #808]	; 7ec <opfunc_hw_rst+0x340>
     4c0:	e5953000 	ldr	r3, [r5]
     4c4:	e3530001 	cmp	r3, #1
     4c8:	959f4320 	ldrls	r4, [pc, #800]	; 7f0 <opfunc_hw_rst+0x344>
     4cc:	9a000013 	bls	520 <opfunc_hw_rst+0x74>
     4d0:	e59f4318 	ldr	r4, [pc, #792]	; 7f0 <opfunc_hw_rst+0x344>
     4d4:	e59f0318 	ldr	r0, [pc, #792]	; 7f4 <opfunc_hw_rst+0x348>
     4d8:	e59f1318 	ldr	r1, [pc, #792]	; 7f8 <opfunc_hw_rst+0x34c>
     4dc:	e594c00c 	ldr	ip, [r4, #12]
     4e0:	e9944040 	ldmib	r4, {r6, lr}
     4e4:	e5947020 	ldr	r7, [r4, #32]
     4e8:	e5948010 	ldr	r8, [r4, #16]
     4ec:	e594a018 	ldr	sl, [r4, #24]
     4f0:	e594901c 	ldr	r9, [r4, #28]
     4f4:	e5943000 	ldr	r3, [r4]
     4f8:	e88d4040 	stm	sp, {r6, lr}
     4fc:	e58dc008 	str	ip, [sp, #8]
     500:	e58d700c 	str	r7, [sp, #12]
     504:	e58d8010 	str	r8, [sp, #16]
     508:	e58da014 	str	sl, [sp, #20]
     50c:	e58d9018 	str	r9, [sp, #24]
     510:	e594c014 	ldr	ip, [r4, #20]
     514:	e59f22e0 	ldr	r2, [pc, #736]	; 7fc <opfunc_hw_rst+0x350>
     518:	e58dc01c 	str	ip, [sp, #28]
     51c:	ebfffffe 	bl	0 <osal_info_print>
     520:	e594200c 	ldr	r2, [r4, #12]
     524:	e3a03000 	mov	r3, #0
     528:	e5843000 	str	r3, [r4]
     52c:	e3520002 	cmp	r2, #2
     530:	e5843004 	str	r3, [r4, #4]
     534:	e5843008 	str	r3, [r4, #8]
     538:	124b6030 	subne	r6, fp, #48	; 0x30
     53c:	e5843020 	str	r3, [r4, #32]
     540:	124b7034 	subne	r7, fp, #52	; 0x34
     544:	e5843014 	str	r3, [r4, #20]
     548:	0a000058 	beq	6b0 <opfunc_hw_rst+0x204>
     54c:	e5943028 	ldr	r3, [r4, #40]	; 0x28
     550:	e3530001 	cmp	r3, #1
     554:	0a000033 	beq	628 <opfunc_hw_rst+0x17c>
     558:	e3a03000 	mov	r3, #0
     55c:	e3a00002 	mov	r0, #2
     560:	e5843010 	str	r3, [r4, #16]
     564:	e1a01006 	mov	r1, r6
     568:	e1a02007 	mov	r2, r7
     56c:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     570:	e2503000 	subs	r3, r0, #0
     574:	1a000026 	bne	614 <opfunc_hw_rst+0x168>
     578:	e5953000 	ldr	r3, [r5]
     57c:	e3530001 	cmp	r3, #1
     580:	9a000002 	bls	590 <opfunc_hw_rst+0xe4>
     584:	e59f0274 	ldr	r0, [pc, #628]	; 800 <opfunc_hw_rst+0x354>
     588:	e59f1274 	ldr	r1, [pc, #628]	; 804 <opfunc_hw_rst+0x358>
     58c:	ebfffffe 	bl	0 <osal_info_print>
     590:	e1a01006 	mov	r1, r6
     594:	e1a02007 	mov	r2, r7
     598:	e3a00003 	mov	r0, #3
     59c:	e3a03000 	mov	r3, #0
     5a0:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
     5a4:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
     5a8:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     5ac:	e2506000 	subs	r6, r0, #0
     5b0:	1a00007d 	bne	7ac <opfunc_hw_rst+0x300>
     5b4:	e5953000 	ldr	r3, [r5]
     5b8:	e3530001 	cmp	r3, #1
     5bc:	9a000011 	bls	608 <opfunc_hw_rst+0x15c>
     5c0:	e5949014 	ldr	r9, [r4, #20]
     5c4:	e8944028 	ldm	r4, {r3, r5, lr}
     5c8:	e594c00c 	ldr	ip, [r4, #12]
     5cc:	e5947020 	ldr	r7, [r4, #32]
     5d0:	e5948010 	ldr	r8, [r4, #16]
     5d4:	e594a018 	ldr	sl, [r4, #24]
     5d8:	e594401c 	ldr	r4, [r4, #28]
     5dc:	e59f0210 	ldr	r0, [pc, #528]	; 7f4 <opfunc_hw_rst+0x348>
     5e0:	e59f1210 	ldr	r1, [pc, #528]	; 7f8 <opfunc_hw_rst+0x34c>
     5e4:	e59f221c 	ldr	r2, [pc, #540]	; 808 <opfunc_hw_rst+0x35c>
     5e8:	e88d4020 	stm	sp, {r5, lr}
     5ec:	e58dc008 	str	ip, [sp, #8]
     5f0:	e58d700c 	str	r7, [sp, #12]
     5f4:	e58d8010 	str	r8, [sp, #16]
     5f8:	e58da014 	str	sl, [sp, #20]
     5fc:	e58d4018 	str	r4, [sp, #24]
     600:	e58d901c 	str	r9, [sp, #28]
     604:	ebfffffe 	bl	0 <osal_info_print>
     608:	e1a00006 	mov	r0, r6
     60c:	e24bd028 	sub	sp, fp, #40	; 0x28
     610:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
     614:	e59f11e8 	ldr	r1, [pc, #488]	; 804 <opfunc_hw_rst+0x358>
     618:	e3002754 	movw	r2, #1876	; 0x754
     61c:	e59f01e8 	ldr	r0, [pc, #488]	; 80c <opfunc_hw_rst+0x360>
     620:	ebfffffe 	bl	0 <osal_err_print>
     624:	eaffffd9 	b	590 <opfunc_hw_rst+0xe4>
     628:	e3a0000b 	mov	r0, #11
     62c:	e1a01006 	mov	r1, r6
     630:	e1a02007 	mov	r2, r7
     634:	e3a03000 	mov	r3, #0
     638:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
     63c:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
     640:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     644:	e2503000 	subs	r3, r0, #0
     648:	1a000031 	bne	714 <opfunc_hw_rst+0x268>
     64c:	e5953000 	ldr	r3, [r5]
     650:	e3530001 	cmp	r3, #1
     654:	9a000002 	bls	664 <opfunc_hw_rst+0x1b8>
     658:	e59f01b0 	ldr	r0, [pc, #432]	; 810 <opfunc_hw_rst+0x364>
     65c:	e59f11a0 	ldr	r1, [pc, #416]	; 804 <opfunc_hw_rst+0x358>
     660:	ebfffffe 	bl	0 <osal_info_print>
     664:	e3a0000a 	mov	r0, #10
     668:	e1a01006 	mov	r1, r6
     66c:	e1a02007 	mov	r2, r7
     670:	e3a03002 	mov	r3, #2
     674:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
     678:	e3a03000 	mov	r3, #0
     67c:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
     680:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     684:	e2503000 	subs	r3, r0, #0
     688:	1a00003d 	bne	784 <opfunc_hw_rst+0x2d8>
     68c:	e5953000 	ldr	r3, [r5]
     690:	e3530001 	cmp	r3, #1
     694:	9a000002 	bls	6a4 <opfunc_hw_rst+0x1f8>
     698:	e59f0174 	ldr	r0, [pc, #372]	; 814 <opfunc_hw_rst+0x368>
     69c:	e59f1160 	ldr	r1, [pc, #352]	; 804 <opfunc_hw_rst+0x358>
     6a0:	ebfffffe 	bl	0 <osal_info_print>
     6a4:	e3a03000 	mov	r3, #0
     6a8:	e584301c 	str	r3, [r4, #28]
     6ac:	eaffffa9 	b	558 <opfunc_hw_rst+0xac>
     6b0:	e24b6030 	sub	r6, fp, #48	; 0x30
     6b4:	e24b7034 	sub	r7, fp, #52	; 0x34
     6b8:	e3a0000b 	mov	r0, #11
     6bc:	e1a01006 	mov	r1, r6
     6c0:	e1a02007 	mov	r2, r7
     6c4:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
     6c8:	e3a03001 	mov	r3, #1
     6cc:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
     6d0:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     6d4:	e2503000 	subs	r3, r0, #0
     6d8:	1a000024 	bne	770 <opfunc_hw_rst+0x2c4>
     6dc:	e5953000 	ldr	r3, [r5]
     6e0:	e3530001 	cmp	r3, #1
     6e4:	9a000002 	bls	6f4 <opfunc_hw_rst+0x248>
     6e8:	e59f0128 	ldr	r0, [pc, #296]	; 818 <opfunc_hw_rst+0x36c>
     6ec:	e59f1110 	ldr	r1, [pc, #272]	; 804 <opfunc_hw_rst+0x358>
     6f0:	ebfffffe 	bl	0 <osal_info_print>
     6f4:	e5943028 	ldr	r3, [r4, #40]	; 0x28
     6f8:	e3a02000 	mov	r2, #0
     6fc:	e584200c 	str	r2, [r4, #12]
     700:	e1530002 	cmp	r3, r2
     704:	0a000007 	beq	728 <opfunc_hw_rst+0x27c>
     708:	e3a03000 	mov	r3, #0
     70c:	e584300c 	str	r3, [r4, #12]
     710:	eaffff8d 	b	54c <opfunc_hw_rst+0xa0>
     714:	e59f10e8 	ldr	r1, [pc, #232]	; 804 <opfunc_hw_rst+0x358>
     718:	e300272f 	movw	r2, #1839	; 0x72f
     71c:	e59f00f8 	ldr	r0, [pc, #248]	; 81c <opfunc_hw_rst+0x370>
     720:	ebfffffe 	bl	0 <osal_err_print>
     724:	eaffffce 	b	664 <opfunc_hw_rst+0x1b8>
     728:	e3a0000a 	mov	r0, #10
     72c:	e1a01006 	mov	r1, r6
     730:	e1a02007 	mov	r2, r7
     734:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
     738:	e3a03001 	mov	r3, #1
     73c:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
     740:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     744:	e2503000 	subs	r3, r0, #0
     748:	1a00001d 	bne	7c4 <opfunc_hw_rst+0x318>
     74c:	e5953000 	ldr	r3, [r5]
     750:	e3530001 	cmp	r3, #1
     754:	9a000002 	bls	764 <opfunc_hw_rst+0x2b8>
     758:	e59f00c0 	ldr	r0, [pc, #192]	; 820 <opfunc_hw_rst+0x374>
     75c:	e59f10a0 	ldr	r1, [pc, #160]	; 804 <opfunc_hw_rst+0x358>
     760:	ebfffffe 	bl	0 <osal_info_print>
     764:	e3a03000 	mov	r3, #0
     768:	e5843018 	str	r3, [r4, #24]
     76c:	eaffffe5 	b	708 <opfunc_hw_rst+0x25c>
     770:	e59f108c 	ldr	r1, [pc, #140]	; 804 <opfunc_hw_rst+0x358>
     774:	e3a02e71 	mov	r2, #1808	; 0x710
     778:	e59f00a4 	ldr	r0, [pc, #164]	; 824 <opfunc_hw_rst+0x378>
     77c:	ebfffffe 	bl	0 <osal_err_print>
     780:	eaffffdb 	b	6f4 <opfunc_hw_rst+0x248>
     784:	e59f1078 	ldr	r1, [pc, #120]	; 804 <opfunc_hw_rst+0x358>
     788:	e300273b 	movw	r2, #1851	; 0x73b
     78c:	e59f0094 	ldr	r0, [pc, #148]	; 828 <opfunc_hw_rst+0x37c>
     790:	ebfffffe 	bl	0 <osal_err_print>
     794:	e59f1090 	ldr	r1, [pc, #144]	; 82c <opfunc_hw_rst+0x380>
     798:	e300273c 	movw	r2, #1852	; 0x73c
     79c:	e59f308c 	ldr	r3, [pc, #140]	; 830 <opfunc_hw_rst+0x384>
     7a0:	e59f008c 	ldr	r0, [pc, #140]	; 834 <opfunc_hw_rst+0x388>
     7a4:	ebfffffe 	bl	0 <osal_err_print>
     7a8:	eaffffbd 	b	6a4 <opfunc_hw_rst+0x1f8>
     7ac:	e300275d 	movw	r2, #1885	; 0x75d
     7b0:	e59f104c 	ldr	r1, [pc, #76]	; 804 <opfunc_hw_rst+0x358>
     7b4:	e59f007c 	ldr	r0, [pc, #124]	; 838 <opfunc_hw_rst+0x38c>
     7b8:	e3e06000 	mvn	r6, #0
     7bc:	ebfffffe 	bl	0 <osal_err_print>
     7c0:	eaffff90 	b	608 <opfunc_hw_rst+0x15c>
     7c4:	e59f1038 	ldr	r1, [pc, #56]	; 804 <opfunc_hw_rst+0x358>
     7c8:	e300271e 	movw	r2, #1822	; 0x71e
     7cc:	e59f0068 	ldr	r0, [pc, #104]	; 83c <opfunc_hw_rst+0x390>
     7d0:	ebfffffe 	bl	0 <osal_err_print>
     7d4:	e59f1050 	ldr	r1, [pc, #80]	; 82c <opfunc_hw_rst+0x380>
     7d8:	e300271f 	movw	r2, #1823	; 0x71f
     7dc:	e59f304c 	ldr	r3, [pc, #76]	; 830 <opfunc_hw_rst+0x384>
     7e0:	e59f004c 	ldr	r0, [pc, #76]	; 834 <opfunc_hw_rst+0x388>
     7e4:	ebfffffe 	bl	0 <osal_err_print>
     7e8:	eaffffdd 	b	764 <opfunc_hw_rst+0x2b8>
	...
     7f4:	000002b0 			; <UNDEFINED> instruction: 0x000002b0
     7f8:	000000d4 	ldrdeq	r0, [r0], -r4
     7fc:	00000304 	andeq	r0, r0, r4, lsl #6
     800:	000004b0 			; <UNDEFINED> instruction: 0x000004b0
     804:	000000f0 	strdeq	r0, [r0], -r0	; <UNPREDICTABLE>
     808:	000004ec 	andeq	r0, r0, ip, ror #9
     80c:	00000488 	andeq	r0, r0, r8, lsl #9
     810:	00000400 	andeq	r0, r0, r0, lsl #8
     814:	00000460 	andeq	r0, r0, r0, ror #8
     818:	00000344 	andeq	r0, r0, r4, asr #6
     81c:	000003c8 	andeq	r0, r0, r8, asr #7
     820:	000003a0 	andeq	r0, r0, r0, lsr #7
     824:	00000310 	andeq	r0, r0, r0, lsl r3
     828:	00000430 	andeq	r0, r0, r0, lsr r4
     82c:	0000027c 	andeq	r0, r0, ip, ror r2
     830:	000002ac 	andeq	r0, r0, ip, lsr #5
     834:	0000026c 	andeq	r0, r0, ip, ror #4
     838:	000004c8 	andeq	r0, r0, r8, asr #9
     83c:	00000370 	andeq	r0, r0, r0, ror r3

00000840 <wmt_core_rx_flush>:
     840:	e1a0c00d 	mov	ip, sp
     844:	e92dd810 	push	{r4, fp, ip, lr, pc}
     848:	e24cb004 	sub	fp, ip, #4
     84c:	e24dd04c 	sub	sp, sp, #76	; 0x4c
     850:	e50b0054 	str	r0, [fp, #-84]	; 0xffffffac
     854:	e24b0058 	sub	r0, fp, #88	; 0x58
     858:	e3a03012 	mov	r3, #18
     85c:	e50b3058 	str	r3, [fp, #-88]	; 0xffffffa8
     860:	ebfffffe 	bl	0 <wmt_ctrl>
     864:	e2504000 	subs	r4, r0, #0
     868:	0a000009 	beq	894 <wmt_core_rx_flush+0x54>
     86c:	e59f102c 	ldr	r1, [pc, #44]	; 8a0 <wmt_core_rx_flush+0x60>
     870:	e30021a3 	movw	r2, #419	; 0x1a3
     874:	e1a03004 	mov	r3, r4
     878:	e59f0024 	ldr	r0, [pc, #36]	; 8a4 <wmt_core_rx_flush+0x64>
     87c:	ebfffffe 	bl	0 <osal_err_print>
     880:	e59f0020 	ldr	r0, [pc, #32]	; 8a8 <wmt_core_rx_flush+0x68>
     884:	e59f1020 	ldr	r1, [pc, #32]	; 8ac <wmt_core_rx_flush+0x6c>
     888:	e3a02f69 	mov	r2, #420	; 0x1a4
     88c:	e59f301c 	ldr	r3, [pc, #28]	; 8b0 <wmt_core_rx_flush+0x70>
     890:	ebfffffe 	bl	0 <osal_err_print>
     894:	e1a00004 	mov	r0, r4
     898:	e24bd010 	sub	sp, fp, #16
     89c:	e89da810 	ldm	sp, {r4, fp, sp, pc}
     8a0:	00000100 	andeq	r0, r0, r0, lsl #2
     8a4:	000004f8 	strdeq	r0, [r0], -r8
     8a8:	0000026c 	andeq	r0, r0, ip, ror #4
     8ac:	0000027c 	andeq	r0, r0, ip, ror r2
     8b0:	000002ac 	andeq	r0, r0, ip, lsr #5

000008b4 <wmt_core_rx>:
     8b4:	e1a0c00d 	mov	ip, sp
     8b8:	e92dd810 	push	{r4, fp, ip, lr, pc}
     8bc:	e24cb004 	sub	fp, ip, #4
     8c0:	e24dd04c 	sub	sp, sp, #76	; 0x4c
     8c4:	e50b0054 	str	r0, [fp, #-84]	; 0xffffffac
     8c8:	e24b0058 	sub	r0, fp, #88	; 0x58
     8cc:	e3a03011 	mov	r3, #17
     8d0:	e50b1050 	str	r1, [fp, #-80]	; 0xffffffb0
     8d4:	e50b204c 	str	r2, [fp, #-76]	; 0xffffffb4
     8d8:	e50b3058 	str	r3, [fp, #-88]	; 0xffffffa8
     8dc:	ebfffffe 	bl	0 <wmt_ctrl>
     8e0:	e2504000 	subs	r4, r0, #0
     8e4:	0a00000a 	beq	914 <wmt_core_rx+0x60>
     8e8:	e59f1030 	ldr	r1, [pc, #48]	; 920 <wmt_core_rx+0x6c>
     8ec:	e3002192 	movw	r2, #402	; 0x192
     8f0:	e1a03004 	mov	r3, r4
     8f4:	e59f0028 	ldr	r0, [pc, #40]	; 924 <wmt_core_rx+0x70>
     8f8:	ebfffffe 	bl	0 <osal_err_print>
     8fc:	ebfffffe 	bl	0 <mtk_wcn_stp_dbg_dump_package>
     900:	e59f0020 	ldr	r0, [pc, #32]	; 928 <wmt_core_rx+0x74>
     904:	e59f1020 	ldr	r1, [pc, #32]	; 92c <wmt_core_rx+0x78>
     908:	e3a02f65 	mov	r2, #404	; 0x194
     90c:	e59f301c 	ldr	r3, [pc, #28]	; 930 <wmt_core_rx+0x7c>
     910:	ebfffffe 	bl	0 <osal_err_print>
     914:	e1a00004 	mov	r0, r4
     918:	e24bd010 	sub	sp, fp, #16
     91c:	e89da810 	ldm	sp, {r4, fp, sp, pc}
     920:	00000114 	andeq	r0, r0, r4, lsl r1
     924:	00000538 	andeq	r0, r0, r8, lsr r5
     928:	0000026c 	andeq	r0, r0, ip, ror #4
     92c:	0000027c 	andeq	r0, r0, ip, ror r2
     930:	000002ac 	andeq	r0, r0, ip, lsr #5

00000934 <opfunc_sdio_ctrl>:
     934:	e1a0c00d 	mov	ip, sp
     938:	e92dd810 	push	{r4, fp, ip, lr, pc}
     93c:	e24cb004 	sub	fp, ip, #4
     940:	e24dd00c 	sub	sp, sp, #12
     944:	e59f409c 	ldr	r4, [pc, #156]	; 9e8 <opfunc_sdio_ctrl+0xb4>
     948:	e24b201c 	sub	r2, fp, #28
     94c:	e24b1018 	sub	r1, fp, #24
     950:	e5943028 	ldr	r3, [r4, #40]	; 0x28
     954:	e3530001 	cmp	r3, #1
     958:	03a03002 	moveq	r3, #2
     95c:	13a03001 	movne	r3, #1
     960:	e50b3018 	str	r3, [fp, #-24]	; 0xffffffe8
     964:	e5903008 	ldr	r3, [r0, #8]
     968:	e3a0000a 	mov	r0, #10
     96c:	e50b301c 	str	r3, [fp, #-28]	; 0xffffffe4
     970:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     974:	e2502000 	subs	r2, r0, #0
     978:	0a000009 	beq	9a4 <opfunc_sdio_ctrl+0x70>
     97c:	e59f3068 	ldr	r3, [pc, #104]	; 9ec <opfunc_sdio_ctrl+0xb8>
     980:	e5933000 	ldr	r3, [r3]
     984:	e3530000 	cmp	r3, #0
     988:	1a000012 	bne	9d8 <opfunc_sdio_ctrl+0xa4>
     98c:	e51b3018 	ldr	r3, [fp, #-24]	; 0xffffffe8
     990:	e3a02000 	mov	r2, #0
     994:	e7842103 	str	r2, [r4, r3, lsl #2]
     998:	e3a00000 	mov	r0, #0
     99c:	e24bd010 	sub	sp, fp, #16
     9a0:	e89da810 	ldm	sp, {r4, fp, sp, pc}
     9a4:	e59f3040 	ldr	r3, [pc, #64]	; 9ec <opfunc_sdio_ctrl+0xb8>
     9a8:	e5933000 	ldr	r3, [r3]
     9ac:	e3530001 	cmp	r3, #1
     9b0:	9a000002 	bls	9c0 <opfunc_sdio_ctrl+0x8c>
     9b4:	e59f0034 	ldr	r0, [pc, #52]	; 9f0 <opfunc_sdio_ctrl+0xbc>
     9b8:	e59f1034 	ldr	r1, [pc, #52]	; 9f4 <opfunc_sdio_ctrl+0xc0>
     9bc:	ebfffffe 	bl	0 <osal_info_print>
     9c0:	e51b3018 	ldr	r3, [fp, #-24]	; 0xffffffe8
     9c4:	e51b201c 	ldr	r2, [fp, #-28]	; 0xffffffe4
     9c8:	e2522000 	subs	r2, r2, #0
     9cc:	13a02001 	movne	r2, #1
     9d0:	e7842103 	str	r2, [r4, r3, lsl #2]
     9d4:	eaffffef 	b	998 <opfunc_sdio_ctrl+0x64>
     9d8:	e59f1014 	ldr	r1, [pc, #20]	; 9f4 <opfunc_sdio_ctrl+0xc0>
     9dc:	e59f0014 	ldr	r0, [pc, #20]	; 9f8 <opfunc_sdio_ctrl+0xc4>
     9e0:	ebfffffe 	bl	0 <osal_warn_print>
     9e4:	eaffffe8 	b	98c <opfunc_sdio_ctrl+0x58>
	...
     9f0:	00000598 	muleq	r0, r8, r5
     9f4:	00000120 	andeq	r0, r0, r0, lsr #2
     9f8:	00000570 	andeq	r0, r0, r0, ror r5

000009fc <opfunc_exit>:
     9fc:	e1a0c00d 	mov	ip, sp
     a00:	e92dd800 	push	{fp, ip, lr, pc}
     a04:	e24cb004 	sub	fp, ip, #4
     a08:	e59f301c 	ldr	r3, [pc, #28]	; a2c <opfunc_exit+0x30>
     a0c:	e5933000 	ldr	r3, [r3]
     a10:	e3530000 	cmp	r3, #0
     a14:	0a000002 	beq	a24 <opfunc_exit+0x28>
     a18:	e59f0010 	ldr	r0, [pc, #16]	; a30 <opfunc_exit+0x34>
     a1c:	e59f1010 	ldr	r1, [pc, #16]	; a34 <opfunc_exit+0x38>
     a20:	ebfffffe 	bl	0 <osal_warn_print>
     a24:	e3a00000 	mov	r0, #0
     a28:	e89da800 	ldm	sp, {fp, sp, pc}
     a2c:	00000000 	andeq	r0, r0, r0
     a30:	000005c0 	andeq	r0, r0, r0, asr #11
     a34:	00000134 	andeq	r0, r0, r4, lsr r1

00000a38 <wmt_core_stp_deinit>:
     a38:	e1a0c00d 	mov	ip, sp
     a3c:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
     a40:	e24cb004 	sub	fp, ip, #4
     a44:	e24dd00c 	sub	sp, sp, #12
     a48:	e59f81f0 	ldr	r8, [pc, #496]	; c40 <wmt_core_stp_deinit+0x208>
     a4c:	e5983000 	ldr	r3, [r8]
     a50:	e3530002 	cmp	r3, #2
     a54:	8a000034 	bhi	b2c <wmt_core_stp_deinit+0xf4>
     a58:	e59f51e4 	ldr	r5, [pc, #484]	; c44 <wmt_core_stp_deinit+0x20c>
     a5c:	e5953050 	ldr	r3, [r5, #80]	; 0x50
     a60:	e3530000 	cmp	r3, #0
     a64:	0a000037 	beq	b48 <wmt_core_stp_deinit+0x110>
     a68:	e5933008 	ldr	r3, [r3, #8]
     a6c:	e3530000 	cmp	r3, #0
     a70:	0a000056 	beq	bd0 <wmt_core_stp_deinit+0x198>
     a74:	e2850028 	add	r0, r5, #40	; 0x28
     a78:	e12fff33 	blx	r3
     a7c:	e3a03000 	mov	r3, #0
     a80:	e5853050 	str	r3, [r5, #80]	; 0x50
     a84:	e24b7030 	sub	r7, fp, #48	; 0x30
     a88:	e24b6034 	sub	r6, fp, #52	; 0x34
     a8c:	e1a01007 	mov	r1, r7
     a90:	e1a02006 	mov	r2, r6
     a94:	e3a00005 	mov	r0, #5
     a98:	e3a04000 	mov	r4, #0
     a9c:	e3a03001 	mov	r3, #1
     aa0:	e50b4034 	str	r4, [fp, #-52]	; 0xffffffcc
     aa4:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
     aa8:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     aac:	e1a01007 	mov	r1, r7
     ab0:	e1a02006 	mov	r2, r6
     ab4:	e50b4030 	str	r4, [fp, #-48]	; 0xffffffd0
     ab8:	e50b4034 	str	r4, [fp, #-52]	; 0xffffffcc
     abc:	e1a09000 	mov	r9, r0
     ac0:	e3a00005 	mov	r0, #5
     ac4:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     ac8:	e1a01007 	mov	r1, r7
     acc:	e1a02006 	mov	r2, r6
     ad0:	e50b4030 	str	r4, [fp, #-48]	; 0xffffffd0
     ad4:	e50b4034 	str	r4, [fp, #-52]	; 0xffffffcc
     ad8:	e1a0a000 	mov	sl, r0
     adc:	e3a00003 	mov	r0, #3
     ae0:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     ae4:	e5953028 	ldr	r3, [r5, #40]	; 0x28
     ae8:	e3530001 	cmp	r3, #1
     aec:	108aa009 	addne	sl, sl, r9
     af0:	108aa000 	addne	sl, sl, r0
     af4:	0a00001a 	beq	b64 <wmt_core_stp_deinit+0x12c>
     af8:	e35a0000 	cmp	sl, #0
     afc:	0a000002 	beq	b0c <wmt_core_stp_deinit+0xd4>
     b00:	e5983000 	ldr	r3, [r8]
     b04:	e3530000 	cmp	r3, #0
     b08:	1a000002 	bne	b18 <wmt_core_stp_deinit+0xe0>
     b0c:	e1a0000a 	mov	r0, sl
     b10:	e24bd028 	sub	sp, fp, #40	; 0x28
     b14:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
     b18:	e1a0200a 	mov	r2, sl
     b1c:	e59f1124 	ldr	r1, [pc, #292]	; c48 <wmt_core_stp_deinit+0x210>
     b20:	e59f0124 	ldr	r0, [pc, #292]	; c4c <wmt_core_stp_deinit+0x214>
     b24:	ebfffffe 	bl	0 <osal_warn_print>
     b28:	eafffff7 	b	b0c <wmt_core_stp_deinit+0xd4>
     b2c:	e59f5110 	ldr	r5, [pc, #272]	; c44 <wmt_core_stp_deinit+0x20c>
     b30:	e59f0118 	ldr	r0, [pc, #280]	; c50 <wmt_core_stp_deinit+0x218>
     b34:	e59f110c 	ldr	r1, [pc, #268]	; c48 <wmt_core_stp_deinit+0x210>
     b38:	ebfffffe 	bl	0 <osal_dbg_print>
     b3c:	e5953050 	ldr	r3, [r5, #80]	; 0x50
     b40:	e3530000 	cmp	r3, #0
     b44:	1affffc7 	bne	a68 <wmt_core_stp_deinit+0x30>
     b48:	e5983000 	ldr	r3, [r8]
     b4c:	e3530000 	cmp	r3, #0
     b50:	0affffcb 	beq	a84 <wmt_core_stp_deinit+0x4c>
     b54:	e59f10ec 	ldr	r1, [pc, #236]	; c48 <wmt_core_stp_deinit+0x210>
     b58:	e59f00f4 	ldr	r0, [pc, #244]	; c54 <wmt_core_stp_deinit+0x21c>
     b5c:	ebfffffe 	bl	0 <osal_warn_print>
     b60:	eaffffc7 	b	a84 <wmt_core_stp_deinit+0x4c>
     b64:	e1a02006 	mov	r2, r6
     b68:	e3a0000b 	mov	r0, #11
     b6c:	e1a01007 	mov	r1, r7
     b70:	e50b4034 	str	r4, [fp, #-52]	; 0xffffffcc
     b74:	e50b4030 	str	r4, [fp, #-48]	; 0xffffffd0
     b78:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     b7c:	e2502000 	subs	r2, r0, #0
     b80:	0a00001e 	beq	c00 <wmt_core_stp_deinit+0x1c8>
     b84:	e5983000 	ldr	r3, [r8]
     b88:	e3530000 	cmp	r3, #0
     b8c:	1a000027 	bne	c30 <wmt_core_stp_deinit+0x1f8>
     b90:	e1a01007 	mov	r1, r7
     b94:	e1a02006 	mov	r2, r6
     b98:	e3a0000a 	mov	r0, #10
     b9c:	e3a03002 	mov	r3, #2
     ba0:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
     ba4:	e3a03000 	mov	r3, #0
     ba8:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
     bac:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     bb0:	e250a000 	subs	sl, r0, #0
     bb4:	0a00000a 	beq	be4 <wmt_core_stp_deinit+0x1ac>
     bb8:	e5983000 	ldr	r3, [r8]
     bbc:	e3530000 	cmp	r3, #0
     bc0:	1a000015 	bne	c1c <wmt_core_stp_deinit+0x1e4>
     bc4:	e3a03000 	mov	r3, #0
     bc8:	e585301c 	str	r3, [r5, #28]
     bcc:	eaffffc9 	b	af8 <wmt_core_stp_deinit+0xc0>
     bd0:	e3a02fd6 	mov	r2, #856	; 0x358
     bd4:	e59f106c 	ldr	r1, [pc, #108]	; c48 <wmt_core_stp_deinit+0x210>
     bd8:	e59f0078 	ldr	r0, [pc, #120]	; c58 <wmt_core_stp_deinit+0x220>
     bdc:	ebfffffe 	bl	0 <osal_err_print>
     be0:	eaffffa7 	b	a84 <wmt_core_stp_deinit+0x4c>
     be4:	e5983000 	ldr	r3, [r8]
     be8:	e3530001 	cmp	r3, #1
     bec:	9afffff4 	bls	bc4 <wmt_core_stp_deinit+0x18c>
     bf0:	e59f1050 	ldr	r1, [pc, #80]	; c48 <wmt_core_stp_deinit+0x210>
     bf4:	e59f0060 	ldr	r0, [pc, #96]	; c5c <wmt_core_stp_deinit+0x224>
     bf8:	ebfffffe 	bl	0 <osal_info_print>
     bfc:	eafffff0 	b	bc4 <wmt_core_stp_deinit+0x18c>
     c00:	e5983000 	ldr	r3, [r8]
     c04:	e3530001 	cmp	r3, #1
     c08:	9affffe0 	bls	b90 <wmt_core_stp_deinit+0x158>
     c0c:	e59f1034 	ldr	r1, [pc, #52]	; c48 <wmt_core_stp_deinit+0x210>
     c10:	e59f0048 	ldr	r0, [pc, #72]	; c60 <wmt_core_stp_deinit+0x228>
     c14:	ebfffffe 	bl	0 <osal_info_print>
     c18:	eaffffdc 	b	b90 <wmt_core_stp_deinit+0x158>
     c1c:	e59f1024 	ldr	r1, [pc, #36]	; c48 <wmt_core_stp_deinit+0x210>
     c20:	e1a0200a 	mov	r2, sl
     c24:	e59f0038 	ldr	r0, [pc, #56]	; c64 <wmt_core_stp_deinit+0x22c>
     c28:	ebfffffe 	bl	0 <osal_warn_print>
     c2c:	eaffffe4 	b	bc4 <wmt_core_stp_deinit+0x18c>
     c30:	e59f1010 	ldr	r1, [pc, #16]	; c48 <wmt_core_stp_deinit+0x210>
     c34:	e59f002c 	ldr	r0, [pc, #44]	; c68 <wmt_core_stp_deinit+0x230>
     c38:	ebfffffe 	bl	0 <osal_warn_print>
     c3c:	eaffffd3 	b	b90 <wmt_core_stp_deinit+0x158>
	...
     c48:	00000140 	andeq	r0, r0, r0, asr #2
     c4c:	00000708 	andeq	r0, r0, r8, lsl #14
     c50:	000005e0 	andeq	r0, r0, r0, ror #11
     c54:	000005f8 	strdeq	r0, [r0], -r8
     c58:	00000624 	andeq	r0, r0, r4, lsr #12
     c5c:	000006e4 	andeq	r0, r0, r4, ror #13
     c60:	0000068c 	andeq	r0, r0, ip, lsl #13
     c64:	000006b8 			; <UNDEFINED> instruction: 0x000006b8
     c68:	0000065c 	andeq	r0, r0, ip, asr r6

00000c6c <opfunc_pwr_off>:
     c6c:	e1a0c00d 	mov	ip, sp
     c70:	e92dd870 	push	{r4, r5, r6, fp, ip, lr, pc}
     c74:	e24cb004 	sub	fp, ip, #4
     c78:	e24dd00c 	sub	sp, sp, #12
     c7c:	e59f50f4 	ldr	r5, [pc, #244]	; d78 <opfunc_pwr_off+0x10c>
     c80:	e5952010 	ldr	r2, [r5, #16]
     c84:	e3520000 	cmp	r2, #0
     c88:	0a00002c 	beq	d40 <opfunc_pwr_off+0xd4>
     c8c:	e3520002 	cmp	r2, #2
     c90:	0a00001b 	beq	d04 <opfunc_pwr_off+0x98>
     c94:	e59f60e0 	ldr	r6, [pc, #224]	; d7c <opfunc_pwr_off+0x110>
     c98:	e3a03000 	mov	r3, #0
     c9c:	e24b1020 	sub	r1, fp, #32
     ca0:	e1a00003 	mov	r0, r3
     ca4:	e24b2024 	sub	r2, fp, #36	; 0x24
     ca8:	e3a0c001 	mov	ip, #1
     cac:	e50b3020 	str	r3, [fp, #-32]	; 0xffffffe0
     cb0:	e585c010 	str	ip, [r5, #16]
     cb4:	e50b3024 	str	r3, [fp, #-36]	; 0xffffffdc
     cb8:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     cbc:	e2504000 	subs	r4, r0, #0
     cc0:	1a000007 	bne	ce4 <opfunc_pwr_off+0x78>
     cc4:	e5963000 	ldr	r3, [r6]
     cc8:	e3530000 	cmp	r3, #0
     ccc:	1a000017 	bne	d30 <opfunc_pwr_off+0xc4>
     cd0:	e3a03000 	mov	r3, #0
     cd4:	e5853010 	str	r3, [r5, #16]
     cd8:	e1a00004 	mov	r0, r4
     cdc:	e24bd018 	sub	sp, fp, #24
     ce0:	e89da870 	ldm	sp, {r4, r5, r6, fp, sp, pc}
     ce4:	e5963000 	ldr	r3, [r6]
     ce8:	e3530000 	cmp	r3, #0
     cec:	0afffff7 	beq	cd0 <opfunc_pwr_off+0x64>
     cf0:	e59f1088 	ldr	r1, [pc, #136]	; d80 <opfunc_pwr_off+0x114>
     cf4:	e1a02004 	mov	r2, r4
     cf8:	e59f0084 	ldr	r0, [pc, #132]	; d84 <opfunc_pwr_off+0x118>
     cfc:	ebfffffe 	bl	0 <osal_warn_print>
     d00:	eafffff2 	b	cd0 <opfunc_pwr_off+0x64>
     d04:	ebffff4b 	bl	a38 <wmt_core_stp_deinit>
     d08:	e2502000 	subs	r2, r0, #0
     d0c:	0affffe0 	beq	c94 <opfunc_pwr_off+0x28>
     d10:	e59f6064 	ldr	r6, [pc, #100]	; d7c <opfunc_pwr_off+0x110>
     d14:	e5963000 	ldr	r3, [r6]
     d18:	e3530000 	cmp	r3, #0
     d1c:	0affffdd 	beq	c98 <opfunc_pwr_off+0x2c>
     d20:	e59f1058 	ldr	r1, [pc, #88]	; d80 <opfunc_pwr_off+0x114>
     d24:	e59f005c 	ldr	r0, [pc, #92]	; d88 <opfunc_pwr_off+0x11c>
     d28:	ebfffffe 	bl	0 <osal_warn_print>
     d2c:	eaffffd9 	b	c98 <opfunc_pwr_off+0x2c>
     d30:	e59f1048 	ldr	r1, [pc, #72]	; d80 <opfunc_pwr_off+0x114>
     d34:	e59f0050 	ldr	r0, [pc, #80]	; d8c <opfunc_pwr_off+0x120>
     d38:	ebfffffe 	bl	0 <osal_warn_print>
     d3c:	eaffffe3 	b	cd0 <opfunc_pwr_off+0x64>
     d40:	e59f3034 	ldr	r3, [pc, #52]	; d7c <opfunc_pwr_off+0x110>
     d44:	e5933000 	ldr	r3, [r3]
     d48:	e3530000 	cmp	r3, #0
     d4c:	0a000002 	beq	d5c <opfunc_pwr_off+0xf0>
     d50:	e59f0038 	ldr	r0, [pc, #56]	; d90 <opfunc_pwr_off+0x124>
     d54:	e59f1024 	ldr	r1, [pc, #36]	; d80 <opfunc_pwr_off+0x114>
     d58:	ebfffffe 	bl	0 <osal_warn_print>
     d5c:	e3002449 	movw	r2, #1097	; 0x449
     d60:	e59f102c 	ldr	r1, [pc, #44]	; d94 <opfunc_pwr_off+0x128>
     d64:	e59f302c 	ldr	r3, [pc, #44]	; d98 <opfunc_pwr_off+0x12c>
     d68:	e3e04000 	mvn	r4, #0
     d6c:	e59f0028 	ldr	r0, [pc, #40]	; d9c <opfunc_pwr_off+0x130>
     d70:	ebfffffe 	bl	0 <osal_err_print>
     d74:	eaffffd7 	b	cd8 <opfunc_pwr_off+0x6c>
	...
     d80:	00000154 	andeq	r0, r0, r4, asr r1
     d84:	00000788 	andeq	r0, r0, r8, lsl #15
     d88:	0000075c 	andeq	r0, r0, ip, asr r7
     d8c:	000007ac 	andeq	r0, r0, ip, lsr #15
     d90:	00000728 	andeq	r0, r0, r8, lsr #14
     d94:	0000027c 	andeq	r0, r0, ip, ror r2
     d98:	000002ac 	andeq	r0, r0, ip, lsr #5
     d9c:	0000026c 	andeq	r0, r0, ip, ror #4

00000da0 <opfunc_func_off>:
     da0:	e1a0c00d 	mov	ip, sp
     da4:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
     da8:	e24cb004 	sub	fp, ip, #4
     dac:	e24dd02c 	sub	sp, sp, #44	; 0x2c
     db0:	e5904008 	ldr	r4, [r0, #8]
     db4:	e1a07000 	mov	r7, r0
     db8:	e3540008 	cmp	r4, #8
     dbc:	8a000093 	bhi	1010 <opfunc_func_off+0x270>
     dc0:	e59f52d4 	ldr	r5, [pc, #724]	; 109c <opfunc_func_off+0x2fc>
     dc4:	e795c104 	ldr	ip, [r5, r4, lsl #2]
     dc8:	e35c0002 	cmp	ip, #2
     dcc:	8a00009b 	bhi	1040 <opfunc_func_off+0x2a0>
     dd0:	0a00000d 	beq	e0c <opfunc_func_off+0x6c>
     dd4:	e59f32c4 	ldr	r3, [pc, #708]	; 10a0 <opfunc_func_off+0x300>
     dd8:	e5936000 	ldr	r6, [r3]
     ddc:	e3560000 	cmp	r6, #0
     de0:	1a000002 	bne	df0 <opfunc_func_off+0x50>
     de4:	e1a00006 	mov	r0, r6
     de8:	e24bd028 	sub	sp, fp, #40	; 0x28
     dec:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
     df0:	e1a02004 	mov	r2, r4
     df4:	e1a0300c 	mov	r3, ip
     df8:	e59f12a4 	ldr	r1, [pc, #676]	; 10a4 <opfunc_func_off+0x304>
     dfc:	e3a06000 	mov	r6, #0
     e00:	e59f02a0 	ldr	r0, [pc, #672]	; 10a8 <opfunc_func_off+0x308>
     e04:	ebfffffe 	bl	0 <osal_warn_print>
     e08:	eafffff5 	b	de4 <opfunc_func_off+0x44>
     e0c:	e3540003 	cmp	r4, #3
     e10:	8a00004f 	bhi	f54 <opfunc_func_off+0x1b4>
     e14:	e59f3290 	ldr	r3, [pc, #656]	; 10ac <opfunc_func_off+0x30c>
     e18:	e7933104 	ldr	r3, [r3, r4, lsl #2]
     e1c:	e3530000 	cmp	r3, #0
     e20:	0a000051 	beq	f6c <opfunc_func_off+0x1cc>
     e24:	e5936004 	ldr	r6, [r3, #4]
     e28:	e3560000 	cmp	r6, #0
     e2c:	0a00004e 	beq	f6c <opfunc_func_off+0x1cc>
     e30:	e5958050 	ldr	r8, [r5, #80]	; 0x50
     e34:	ebfffffe 	bl	0 <wmt_conf_get_cfg>
     e38:	e1a01000 	mov	r1, r0
     e3c:	e1a00008 	mov	r0, r8
     e40:	e12fff36 	blx	r6
     e44:	e3540003 	cmp	r4, #3
     e48:	e1a06000 	mov	r6, r0
     e4c:	0a000060 	beq	fd4 <opfunc_func_off+0x234>
     e50:	e3560000 	cmp	r6, #0
     e54:	e3a03000 	mov	r3, #0
     e58:	e7853104 	str	r3, [r5, r4, lsl #2]
     e5c:	1a000055 	bne	fb8 <opfunc_func_off+0x218>
     e60:	e59f8238 	ldr	r8, [pc, #568]	; 10a0 <opfunc_func_off+0x300>
     e64:	e5953000 	ldr	r3, [r5]
     e68:	e59f222c 	ldr	r2, [pc, #556]	; 109c <opfunc_func_off+0x2fc>
     e6c:	e3530000 	cmp	r3, #0
     e70:	1a000021 	bne	efc <opfunc_func_off+0x15c>
     e74:	e5923008 	ldr	r3, [r2, #8]
     e78:	e3530000 	cmp	r3, #0
     e7c:	1a00001e 	bne	efc <opfunc_func_off+0x15c>
     e80:	e5923004 	ldr	r3, [r2, #4]
     e84:	e3530000 	cmp	r3, #0
     e88:	1a00001b 	bne	efc <opfunc_func_off+0x15c>
     e8c:	e592300c 	ldr	r3, [r2, #12]
     e90:	e3530000 	cmp	r3, #0
     e94:	1a000018 	bne	efc <opfunc_func_off+0x15c>
     e98:	e5923020 	ldr	r3, [r2, #32]
     e9c:	e3530000 	cmp	r3, #0
     ea0:	1a000015 	bne	efc <opfunc_func_off+0x15c>
     ea4:	e5983000 	ldr	r3, [r8]
     ea8:	e3530001 	cmp	r3, #1
     eac:	9a000003 	bls	ec0 <opfunc_func_off+0x120>
     eb0:	e59f01f8 	ldr	r0, [pc, #504]	; 10b0 <opfunc_func_off+0x310>
     eb4:	e1a02004 	mov	r2, r4
     eb8:	e59f11e4 	ldr	r1, [pc, #484]	; 10a4 <opfunc_func_off+0x304>
     ebc:	ebfffffe 	bl	0 <osal_info_print>
     ec0:	e1a00007 	mov	r0, r7
     ec4:	ebffff68 	bl	c6c <opfunc_pwr_off>
     ec8:	e2506000 	subs	r6, r0, #0
     ecc:	0a00000a 	beq	efc <opfunc_func_off+0x15c>
     ed0:	e59f11cc 	ldr	r1, [pc, #460]	; 10a4 <opfunc_func_off+0x304>
     ed4:	e300254e 	movw	r2, #1358	; 0x54e
     ed8:	e1a03006 	mov	r3, r6
     edc:	e59f01d0 	ldr	r0, [pc, #464]	; 10b4 <opfunc_func_off+0x314>
     ee0:	e58d4000 	str	r4, [sp]
     ee4:	ebfffffe 	bl	0 <osal_err_print>
     ee8:	e59f01c8 	ldr	r0, [pc, #456]	; 10b8 <opfunc_func_off+0x318>
     eec:	e300254f 	movw	r2, #1359	; 0x54f
     ef0:	e59f11c4 	ldr	r1, [pc, #452]	; 10bc <opfunc_func_off+0x31c>
     ef4:	e59f31c4 	ldr	r3, [pc, #452]	; 10c0 <opfunc_func_off+0x320>
     ef8:	ebfffffe 	bl	0 <osal_err_print>
     efc:	e5983000 	ldr	r3, [r8]
     f00:	e3530001 	cmp	r3, #1
     f04:	9affffb6 	bls	de4 <opfunc_func_off+0x44>
     f08:	e5959014 	ldr	r9, [r5, #20]
     f0c:	e8954018 	ldm	r5, {r3, r4, lr}
     f10:	e595c00c 	ldr	ip, [r5, #12]
     f14:	e5957020 	ldr	r7, [r5, #32]
     f18:	e5958010 	ldr	r8, [r5, #16]
     f1c:	e595a018 	ldr	sl, [r5, #24]
     f20:	e595501c 	ldr	r5, [r5, #28]
     f24:	e59f1198 	ldr	r1, [pc, #408]	; 10c4 <opfunc_func_off+0x324>
     f28:	e59f2198 	ldr	r2, [pc, #408]	; 10c8 <opfunc_func_off+0x328>
     f2c:	e59f0198 	ldr	r0, [pc, #408]	; 10cc <opfunc_func_off+0x32c>
     f30:	e88d4010 	stm	sp, {r4, lr}
     f34:	e58dc008 	str	ip, [sp, #8]
     f38:	e58d700c 	str	r7, [sp, #12]
     f3c:	e58d8010 	str	r8, [sp, #16]
     f40:	e58da014 	str	sl, [sp, #20]
     f44:	e58d5018 	str	r5, [sp, #24]
     f48:	e58d901c 	str	r9, [sp, #28]
     f4c:	ebfffffe 	bl	0 <osal_info_print>
     f50:	eaffffa3 	b	de4 <opfunc_func_off+0x44>
     f54:	e3540008 	cmp	r4, #8
     f58:	e3a06000 	mov	r6, #0
     f5c:	03a03000 	moveq	r3, #0
     f60:	05853020 	streq	r3, [r5, #32]
     f64:	e7856104 	str	r6, [r5, r4, lsl #2]
     f68:	eaffffbc 	b	e60 <opfunc_func_off+0xc0>
     f6c:	e59f812c 	ldr	r8, [pc, #300]	; 10a0 <opfunc_func_off+0x300>
     f70:	e5983000 	ldr	r3, [r8]
     f74:	e3530000 	cmp	r3, #0
     f78:	1a000010 	bne	fc0 <opfunc_func_off+0x220>
     f7c:	e3e06002 	mvn	r6, #2
     f80:	e3a03000 	mov	r3, #0
     f84:	e7853104 	str	r3, [r5, r4, lsl #2]
     f88:	e1a03004 	mov	r3, r4
     f8c:	e59f1110 	ldr	r1, [pc, #272]	; 10a4 <opfunc_func_off+0x304>
     f90:	e300253d 	movw	r2, #1341	; 0x53d
     f94:	e59f0134 	ldr	r0, [pc, #308]	; 10d0 <opfunc_func_off+0x330>
     f98:	e58d6000 	str	r6, [sp]
     f9c:	ebfffffe 	bl	0 <osal_err_print>
     fa0:	e300253e 	movw	r2, #1342	; 0x53e
     fa4:	e59f1110 	ldr	r1, [pc, #272]	; 10bc <opfunc_func_off+0x31c>
     fa8:	e59f3110 	ldr	r3, [pc, #272]	; 10c0 <opfunc_func_off+0x320>
     fac:	e59f0104 	ldr	r0, [pc, #260]	; 10b8 <opfunc_func_off+0x318>
     fb0:	ebfffffe 	bl	0 <osal_err_print>
     fb4:	eaffffaa 	b	e64 <opfunc_func_off+0xc4>
     fb8:	e59f80e0 	ldr	r8, [pc, #224]	; 10a0 <opfunc_func_off+0x300>
     fbc:	eafffff1 	b	f88 <opfunc_func_off+0x1e8>
     fc0:	e59f10dc 	ldr	r1, [pc, #220]	; 10a4 <opfunc_func_off+0x304>
     fc4:	e1a02004 	mov	r2, r4
     fc8:	e59f0104 	ldr	r0, [pc, #260]	; 10d4 <opfunc_func_off+0x334>
     fcc:	ebfffffe 	bl	0 <osal_warn_print>
     fd0:	eaffffe9 	b	f7c <opfunc_func_off+0x1dc>
     fd4:	e5953028 	ldr	r3, [r5, #40]	; 0x28
     fd8:	e3530000 	cmp	r3, #0
     fdc:	1affff9b 	bne	e50 <opfunc_func_off+0xb0>
     fe0:	e3a0000a 	mov	r0, #10
     fe4:	e24b1030 	sub	r1, fp, #48	; 0x30
     fe8:	e24b2034 	sub	r2, fp, #52	; 0x34
     fec:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
     ff0:	e3a03001 	mov	r3, #1
     ff4:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
     ff8:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
     ffc:	e2503000 	subs	r3, r0, #0
    1000:	1a00001b 	bne	1074 <opfunc_func_off+0x2d4>
    1004:	e3a03000 	mov	r3, #0
    1008:	e5853018 	str	r3, [r5, #24]
    100c:	eaffff8f 	b	e50 <opfunc_func_off+0xb0>
    1010:	e1a03004 	mov	r3, r4
    1014:	e59f1088 	ldr	r1, [pc, #136]	; 10a4 <opfunc_func_off+0x304>
    1018:	e3002507 	movw	r2, #1287	; 0x507
    101c:	e59f00b4 	ldr	r0, [pc, #180]	; 10d8 <opfunc_func_off+0x338>
    1020:	ebfffffe 	bl	0 <osal_err_print>
    1024:	e59f1090 	ldr	r1, [pc, #144]	; 10bc <opfunc_func_off+0x31c>
    1028:	e3002508 	movw	r2, #1288	; 0x508
    102c:	e59f308c 	ldr	r3, [pc, #140]	; 10c0 <opfunc_func_off+0x320>
    1030:	e59f0080 	ldr	r0, [pc, #128]	; 10b8 <opfunc_func_off+0x318>
    1034:	e3e06000 	mvn	r6, #0
    1038:	ebfffffe 	bl	0 <osal_err_print>
    103c:	eaffff68 	b	de4 <opfunc_func_off+0x44>
    1040:	e1a03004 	mov	r3, r4
    1044:	e59f1058 	ldr	r1, [pc, #88]	; 10a4 <opfunc_func_off+0x304>
    1048:	e3a02e51 	mov	r2, #1296	; 0x510
    104c:	e59f0088 	ldr	r0, [pc, #136]	; 10dc <opfunc_func_off+0x33c>
    1050:	e58dc000 	str	ip, [sp]
    1054:	ebfffffe 	bl	0 <osal_err_print>
    1058:	e3002511 	movw	r2, #1297	; 0x511
    105c:	e59f1058 	ldr	r1, [pc, #88]	; 10bc <opfunc_func_off+0x31c>
    1060:	e59f3058 	ldr	r3, [pc, #88]	; 10c0 <opfunc_func_off+0x320>
    1064:	e3e06001 	mvn	r6, #1
    1068:	e59f0048 	ldr	r0, [pc, #72]	; 10b8 <opfunc_func_off+0x318>
    106c:	ebfffffe 	bl	0 <osal_err_print>
    1070:	eaffff5b 	b	de4 <opfunc_func_off+0x44>
    1074:	e59f1028 	ldr	r1, [pc, #40]	; 10a4 <opfunc_func_off+0x304>
    1078:	e3002526 	movw	r2, #1318	; 0x526
    107c:	e59f005c 	ldr	r0, [pc, #92]	; 10e0 <opfunc_func_off+0x340>
    1080:	ebfffffe 	bl	0 <osal_err_print>
    1084:	e59f1030 	ldr	r1, [pc, #48]	; 10bc <opfunc_func_off+0x31c>
    1088:	e3002527 	movw	r2, #1319	; 0x527
    108c:	e59f302c 	ldr	r3, [pc, #44]	; 10c0 <opfunc_func_off+0x320>
    1090:	e59f0020 	ldr	r0, [pc, #32]	; 10b8 <opfunc_func_off+0x318>
    1094:	ebfffffe 	bl	0 <osal_err_print>
    1098:	eaffffd9 	b	1004 <opfunc_func_off+0x264>
	...
    10a4:	00000164 	andeq	r0, r0, r4, ror #2
    10a8:	00000820 	andeq	r0, r0, r0, lsr #16
    10ac:	00000000 	andeq	r0, r0, r0
    10b0:	000008dc 	ldrdeq	r0, [r0], -ip
    10b4:	00000914 	andeq	r0, r0, r4, lsl r9
    10b8:	0000026c 	andeq	r0, r0, ip, ror #4
    10bc:	0000027c 	andeq	r0, r0, ip, ror r2
    10c0:	000002ac 	andeq	r0, r0, ip, lsr #5
    10c4:	000000d4 	ldrdeq	r0, [r0], -r4
    10c8:	00000950 	andeq	r0, r0, r0, asr r9
    10cc:	000002b0 			; <UNDEFINED> instruction: 0x000002b0
    10d0:	000008b4 			; <UNDEFINED> instruction: 0x000008b4
    10d4:	00000888 	andeq	r0, r0, r8, lsl #17
    10d8:	000007c8 	andeq	r0, r0, r8, asr #15
    10dc:	000007ec 	andeq	r0, r0, ip, ror #15
    10e0:	00000858 	andeq	r0, r0, r8, asr r8

000010e4 <wmt_core_tx>:
    10e4:	e1a0c00d 	mov	ip, sp
    10e8:	e92dd800 	push	{fp, ip, lr, pc}
    10ec:	e24cb004 	sub	fp, ip, #4
    10f0:	ebfffffe 	bl	0 <wmt_ctrl_tx_ex>
    10f4:	e89da800 	ldm	sp, {fp, sp, pc}

000010f8 <wmt_core_init_script>:
    10f8:	e1a0c00d 	mov	ip, sp
    10fc:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
    1100:	e24cb004 	sub	fp, ip, #4
    1104:	e24ddf4f 	sub	sp, sp, #316	; 0x13c
    1108:	e2519000 	subs	r9, r1, #0
    110c:	da000078 	ble	12f4 <wmt_core_init_script+0x1fc>
    1110:	e59f61e4 	ldr	r6, [pc, #484]	; 12fc <wmt_core_init_script+0x204>
    1114:	e1a04000 	mov	r4, r0
    1118:	e3a07000 	mov	r7, #0
    111c:	e24ba030 	sub	sl, fp, #48	; 0x30
    1120:	e24b5e13 	sub	r5, fp, #304	; 0x130
    1124:	ea000025 	b	11c0 <wmt_core_init_script+0xc8>
    1128:	e5941004 	ldr	r1, [r4, #4]
    112c:	e1a0200a 	mov	r2, sl
    1130:	e3a03000 	mov	r3, #0
    1134:	e5940000 	ldr	r0, [r4]
    1138:	ebfffffe 	bl	10e4 <wmt_core_tx>
    113c:	e3a02c01 	mov	r2, #256	; 0x100
    1140:	e250c000 	subs	ip, r0, #0
    1144:	e1a00005 	mov	r0, r5
    1148:	e1a0100c 	mov	r1, ip
    114c:	1a00002d 	bne	1208 <wmt_core_init_script+0x110>
    1150:	e5948004 	ldr	r8, [r4, #4]
    1154:	e51be030 	ldr	lr, [fp, #-48]	; 0xffffffd0
    1158:	e158000e 	cmp	r8, lr
    115c:	1a00002b 	bne	1210 <wmt_core_init_script+0x118>
    1160:	ebfffffe 	bl	0 <osal_memset>
    1164:	e1a00005 	mov	r0, r5
    1168:	e594100c 	ldr	r1, [r4, #12]
    116c:	e1a0200a 	mov	r2, sl
    1170:	ebfffffe 	bl	8b4 <wmt_core_rx>
    1174:	e2508000 	subs	r8, r0, #0
    1178:	e1a00005 	mov	r0, r5
    117c:	1a00002e 	bne	123c <wmt_core_init_script+0x144>
    1180:	e594c00c 	ldr	ip, [r4, #12]
    1184:	e51be030 	ldr	lr, [fp, #-48]	; 0xffffffd0
    1188:	e1a0200c 	mov	r2, ip
    118c:	e15c000e 	cmp	ip, lr
    1190:	1a00002b 	bne	1244 <wmt_core_init_script+0x14c>
    1194:	e5941008 	ldr	r1, [r4, #8]
    1198:	ebfffffe 	bl	0 <osal_memcmp>
    119c:	e3500000 	cmp	r0, #0
    11a0:	1a000031 	bne	126c <wmt_core_init_script+0x174>
    11a4:	e5963000 	ldr	r3, [r6]
    11a8:	e2877001 	add	r7, r7, #1
    11ac:	e3530002 	cmp	r3, #2
    11b0:	8a00000a 	bhi	11e0 <wmt_core_init_script+0xe8>
    11b4:	e1570009 	cmp	r7, r9
    11b8:	e2844014 	add	r4, r4, #20
    11bc:	0a00000e 	beq	11fc <wmt_core_init_script+0x104>
    11c0:	e5963000 	ldr	r3, [r6]
    11c4:	e3530002 	cmp	r3, #2
    11c8:	9affffd6 	bls	1128 <wmt_core_init_script+0x30>
    11cc:	e5942010 	ldr	r2, [r4, #16]
    11d0:	e59f1128 	ldr	r1, [pc, #296]	; 1300 <wmt_core_init_script+0x208>
    11d4:	e59f0128 	ldr	r0, [pc, #296]	; 1304 <wmt_core_init_script+0x20c>
    11d8:	ebfffffe 	bl	0 <osal_dbg_print>
    11dc:	eaffffd1 	b	1128 <wmt_core_init_script+0x30>
    11e0:	e5942010 	ldr	r2, [r4, #16]
    11e4:	e2844014 	add	r4, r4, #20
    11e8:	e59f0118 	ldr	r0, [pc, #280]	; 1308 <wmt_core_init_script+0x210>
    11ec:	e59f110c 	ldr	r1, [pc, #268]	; 1300 <wmt_core_init_script+0x208>
    11f0:	ebfffffe 	bl	0 <osal_dbg_print>
    11f4:	e1570009 	cmp	r7, r9
    11f8:	1afffff0 	bne	11c0 <wmt_core_init_script+0xc8>
    11fc:	e3a00000 	mov	r0, #0
    1200:	e24bd028 	sub	sp, fp, #40	; 0x28
    1204:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
    1208:	e5948004 	ldr	r8, [r4, #4]
    120c:	e51be030 	ldr	lr, [fp, #-48]	; 0xffffffd0
    1210:	e5943010 	ldr	r3, [r4, #16]
    1214:	e30022a7 	movw	r2, #679	; 0x2a7
    1218:	e59f10e0 	ldr	r1, [pc, #224]	; 1300 <wmt_core_init_script+0x208>
    121c:	e59f00e8 	ldr	r0, [pc, #232]	; 130c <wmt_core_init_script+0x214>
    1220:	e88d5000 	stm	sp, {ip, lr}
    1224:	e58d8008 	str	r8, [sp, #8]
    1228:	ebfffffe 	bl	0 <osal_err_print>
    122c:	e1570009 	cmp	r7, r9
    1230:	13e00000 	mvnne	r0, #0
    1234:	0afffff0 	beq	11fc <wmt_core_init_script+0x104>
    1238:	eafffff0 	b	1200 <wmt_core_init_script+0x108>
    123c:	e594c00c 	ldr	ip, [r4, #12]
    1240:	e51be030 	ldr	lr, [fp, #-48]	; 0xffffffd0
    1244:	e5943010 	ldr	r3, [r4, #16]
    1248:	e30022ae 	movw	r2, #686	; 0x2ae
    124c:	e59f10ac 	ldr	r1, [pc, #172]	; 1300 <wmt_core_init_script+0x208>
    1250:	e59f00b8 	ldr	r0, [pc, #184]	; 1310 <wmt_core_init_script+0x218>
    1254:	e58de004 	str	lr, [sp, #4]
    1258:	e58dc008 	str	ip, [sp, #8]
    125c:	e58d8000 	str	r8, [sp]
    1260:	ebfffffe 	bl	0 <osal_err_print>
    1264:	ebfffffe 	bl	0 <mtk_wcn_stp_dbg_dump_package>
    1268:	eaffffef 	b	122c <wmt_core_init_script+0x134>
    126c:	e5943010 	ldr	r3, [r4, #16]
    1270:	e3a02fad 	mov	r2, #692	; 0x2b4
    1274:	e59f1084 	ldr	r1, [pc, #132]	; 1300 <wmt_core_init_script+0x208>
    1278:	e59f0094 	ldr	r0, [pc, #148]	; 1314 <wmt_core_init_script+0x21c>
    127c:	ebfffffe 	bl	0 <osal_err_print>
    1280:	e55be12f 	ldrb	lr, [fp, #-303]	; 0xfffffed1
    1284:	e55b012e 	ldrb	r0, [fp, #-302]	; 0xfffffed2
    1288:	e30022b7 	movw	r2, #695	; 0x2b7
    128c:	e55b112d 	ldrb	r1, [fp, #-301]	; 0xfffffed3
    1290:	e55b312c 	ldrb	r3, [fp, #-300]	; 0xfffffed4
    1294:	e55b5130 	ldrb	r5, [fp, #-304]	; 0xfffffed0
    1298:	e594c008 	ldr	ip, [r4, #8]
    129c:	e58d0008 	str	r0, [sp, #8]
    12a0:	e58d100c 	str	r1, [sp, #12]
    12a4:	e88d4020 	stm	sp, {r5, lr}
    12a8:	e58d3010 	str	r3, [sp, #16]
    12ac:	e594300c 	ldr	r3, [r4, #12]
    12b0:	e59f1048 	ldr	r1, [pc, #72]	; 1300 <wmt_core_init_script+0x208>
    12b4:	e59f005c 	ldr	r0, [pc, #92]	; 1318 <wmt_core_init_script+0x220>
    12b8:	e58d3014 	str	r3, [sp, #20]
    12bc:	e5dce000 	ldrb	lr, [ip]
    12c0:	e51b3030 	ldr	r3, [fp, #-48]	; 0xffffffd0
    12c4:	e58de018 	str	lr, [sp, #24]
    12c8:	e5dce001 	ldrb	lr, [ip, #1]
    12cc:	e58de01c 	str	lr, [sp, #28]
    12d0:	e5dce002 	ldrb	lr, [ip, #2]
    12d4:	e58de020 	str	lr, [sp, #32]
    12d8:	e5dce003 	ldrb	lr, [ip, #3]
    12dc:	e58de024 	str	lr, [sp, #36]	; 0x24
    12e0:	e5dcc004 	ldrb	ip, [ip, #4]
    12e4:	e58dc028 	str	ip, [sp, #40]	; 0x28
    12e8:	ebfffffe 	bl	0 <osal_err_print>
    12ec:	ebfffffe 	bl	0 <mtk_wcn_stp_dbg_dump_package>
    12f0:	eaffffcd 	b	122c <wmt_core_init_script+0x134>
    12f4:	e3a07000 	mov	r7, #0
    12f8:	eaffffcb 	b	122c <wmt_core_init_script+0x134>
    12fc:	00000000 	andeq	r0, r0, r0
    1300:	00000174 	andeq	r0, r0, r4, ror r1
    1304:	0000095c 	andeq	r0, r0, ip, asr r9
    1308:	00000a88 	andeq	r0, r0, r8, lsl #21
    130c:	00000980 	andeq	r0, r0, r0, lsl #19
    1310:	000009bc 			; <UNDEFINED> instruction: 0x000009bc
    1314:	00000a00 	andeq	r0, r0, r0, lsl #20
    1318:	00000a30 	andeq	r0, r0, r0, lsr sl

0000131c <wmt_core_reg_rw_raw>:
    131c:	e1a0c00d 	mov	ip, sp
    1320:	e92dddf0 	push	{r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}
    1324:	e24cb004 	sub	fp, ip, #4
    1328:	e24dd030 	sub	sp, sp, #48	; 0x30
    132c:	e24b6040 	sub	r6, fp, #64	; 0x40
    1330:	e59f41a8 	ldr	r4, [pc, #424]	; 14e0 <wmt_core_reg_rw_raw+0x1c4>
    1334:	e286c004 	add	ip, r6, #4
    1338:	e1a05000 	mov	r5, r0
    133c:	e3550000 	cmp	r5, #0
    1340:	e3a07000 	mov	r7, #0
    1344:	e50b1048 	str	r1, [fp, #-72]	; 0xffffffb8
    1348:	e1a0a002 	mov	sl, r2
    134c:	e48c7004 	str	r7, [ip], #4
    1350:	e24b1048 	sub	r1, fp, #72	; 0x48
    1354:	e48c7004 	str	r7, [ip], #4
    1358:	e3a02004 	mov	r2, #4
    135c:	e58c7000 	str	r7, [ip]
    1360:	e2840018 	add	r0, r4, #24
    1364:	e50b304c 	str	r3, [fp, #-76]	; 0xffffffb4
    1368:	13a03001 	movne	r3, #1
    136c:	03a03002 	moveq	r3, #2
    1370:	e50b7040 	str	r7, [fp, #-64]	; 0xffffffc0
    1374:	e5c43014 	strb	r3, [r4, #20]
    1378:	ebfffffe 	bl	0 <osal_memcpy>
    137c:	e1a0100a 	mov	r1, sl
    1380:	e3a02004 	mov	r2, #4
    1384:	e284001c 	add	r0, r4, #28
    1388:	e24b8028 	sub	r8, fp, #40	; 0x28
    138c:	ebfffffe 	bl	0 <osal_memcpy>
    1390:	e24b104c 	sub	r1, fp, #76	; 0x4c
    1394:	e3a02004 	mov	r2, #4
    1398:	e2840020 	add	r0, r4, #32
    139c:	ebfffffe 	bl	0 <osal_memcpy>
    13a0:	e1a03007 	mov	r3, r7
    13a4:	e2840010 	add	r0, r4, #16
    13a8:	e3a01014 	mov	r1, #20
    13ac:	e1a02008 	mov	r2, r8
    13b0:	ebfffffe 	bl	10e4 <wmt_core_tx>
    13b4:	e2503000 	subs	r3, r0, #0
    13b8:	151bc028 	ldrne	ip, [fp, #-40]	; 0xffffffd8
    13bc:	1a000029 	bne	1468 <wmt_core_reg_rw_raw+0x14c>
    13c0:	e51bc028 	ldr	ip, [fp, #-40]	; 0xffffffd8
    13c4:	e35c0014 	cmp	ip, #20
    13c8:	1a000026 	bne	1468 <wmt_core_reg_rw_raw+0x14c>
    13cc:	e3550000 	cmp	r5, #0
    13d0:	e1a02008 	mov	r2, r8
    13d4:	13a07008 	movne	r7, #8
    13d8:	03a07010 	moveq	r7, #16
    13dc:	e1a00006 	mov	r0, r6
    13e0:	e1a01007 	mov	r1, r7
    13e4:	ebfffffe 	bl	8b4 <wmt_core_rx>
    13e8:	e3500000 	cmp	r0, #0
    13ec:	151bc028 	ldrne	ip, [fp, #-40]	; 0xffffffd8
    13f0:	1a000025 	bne	148c <wmt_core_reg_rw_raw+0x170>
    13f4:	e51bc028 	ldr	ip, [fp, #-40]	; 0xffffffd8
    13f8:	e157000c 	cmp	r7, ip
    13fc:	1a000022 	bne	148c <wmt_core_reg_rw_raw+0x170>
    1400:	e3550000 	cmp	r5, #0
    1404:	0a000001 	beq	1410 <wmt_core_reg_rw_raw+0xf4>
    1408:	e24bd024 	sub	sp, fp, #36	; 0x24
    140c:	e89dadf0 	ldm	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
    1410:	e2841018 	add	r1, r4, #24
    1414:	e3a02004 	mov	r2, #4
    1418:	e24b0030 	sub	r0, fp, #48	; 0x30
    141c:	ebfffffe 	bl	0 <osal_memcpy>
    1420:	e24b002c 	sub	r0, fp, #44	; 0x2c
    1424:	e2861008 	add	r1, r6, #8
    1428:	e3a02004 	mov	r2, #4
    142c:	ebfffffe 	bl	0 <osal_memcpy>
    1430:	e51bc030 	ldr	ip, [fp, #-48]	; 0xffffffd0
    1434:	e51b302c 	ldr	r3, [fp, #-44]	; 0xffffffd4
    1438:	e15c0003 	cmp	ip, r3
    143c:	1a000020 	bne	14c4 <wmt_core_reg_rw_raw+0x1a8>
    1440:	e59f309c 	ldr	r3, [pc, #156]	; 14e4 <wmt_core_reg_rw_raw+0x1c8>
    1444:	e5933000 	ldr	r3, [r3]
    1448:	e3530002 	cmp	r3, #2
    144c:	8a000017 	bhi	14b0 <wmt_core_reg_rw_raw+0x194>
    1450:	e1a0000a 	mov	r0, sl
    1454:	e286100c 	add	r1, r6, #12
    1458:	e3a02004 	mov	r2, #4
    145c:	ebfffffe 	bl	0 <osal_memcpy>
    1460:	e3a00000 	mov	r0, #0
    1464:	eaffffe7 	b	1408 <wmt_core_reg_rw_raw+0xec>
    1468:	e59f0078 	ldr	r0, [pc, #120]	; 14e8 <wmt_core_reg_rw_raw+0x1cc>
    146c:	e3002275 	movw	r2, #629	; 0x275
    1470:	e59f1074 	ldr	r1, [pc, #116]	; 14ec <wmt_core_reg_rw_raw+0x1d0>
    1474:	e58dc000 	str	ip, [sp]
    1478:	e3a0c014 	mov	ip, #20
    147c:	e58dc004 	str	ip, [sp, #4]
    1480:	ebfffffe 	bl	0 <osal_err_print>
    1484:	e3e00001 	mvn	r0, #1
    1488:	eaffffde 	b	1408 <wmt_core_reg_rw_raw+0xec>
    148c:	e1a03000 	mov	r3, r0
    1490:	e59f1054 	ldr	r1, [pc, #84]	; 14ec <wmt_core_reg_rw_raw+0x1d0>
    1494:	e59f0054 	ldr	r0, [pc, #84]	; 14f0 <wmt_core_reg_rw_raw+0x1d4>
    1498:	e300227d 	movw	r2, #637	; 0x27d
    149c:	e58dc000 	str	ip, [sp]
    14a0:	e58d7004 	str	r7, [sp, #4]
    14a4:	ebfffffe 	bl	0 <osal_err_print>
    14a8:	e3e00002 	mvn	r0, #2
    14ac:	eaffffd5 	b	1408 <wmt_core_reg_rw_raw+0xec>
    14b0:	e1a0200c 	mov	r2, ip
    14b4:	e59f1030 	ldr	r1, [pc, #48]	; 14ec <wmt_core_reg_rw_raw+0x1d0>
    14b8:	e59f0034 	ldr	r0, [pc, #52]	; 14f4 <wmt_core_reg_rw_raw+0x1d8>
    14bc:	ebfffffe 	bl	0 <osal_dbg_print>
    14c0:	eaffffe2 	b	1450 <wmt_core_reg_rw_raw+0x134>
    14c4:	e59f002c 	ldr	r0, [pc, #44]	; 14f8 <wmt_core_reg_rw_raw+0x1dc>
    14c8:	e3002289 	movw	r2, #649	; 0x289
    14cc:	e59f1018 	ldr	r1, [pc, #24]	; 14ec <wmt_core_reg_rw_raw+0x1d0>
    14d0:	e58dc000 	str	ip, [sp]
    14d4:	ebfffffe 	bl	0 <osal_err_print>
    14d8:	e3e00003 	mvn	r0, #3
    14dc:	eaffffc9 	b	1408 <wmt_core_reg_rw_raw+0xec>
	...
    14e8:	00000ab4 			; <UNDEFINED> instruction: 0x00000ab4
    14ec:	0000018c 	andeq	r0, r0, ip, lsl #3
    14f0:	00000aec 	andeq	r0, r0, ip, ror #21
    14f4:	00000b58 	andeq	r0, r0, r8, asr fp
    14f8:	00000b20 	andeq	r0, r0, r0, lsr #22

000014fc <wmt_core_stp_init>:
    14fc:	e1a0c00d 	mov	ip, sp
    1500:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
    1504:	e24cb004 	sub	fp, ip, #4
    1508:	e24dd024 	sub	sp, sp, #36	; 0x24
    150c:	e59f45e4 	ldr	r4, [pc, #1508]	; 1af8 <wmt_core_stp_init+0x5fc>
    1510:	e5943000 	ldr	r3, [r4]
    1514:	e3530003 	cmp	r3, #3
    1518:	8a00006c 	bhi	16d0 <wmt_core_stp_init+0x1d4>
    151c:	e59f65d8 	ldr	r6, [pc, #1496]	; 1afc <wmt_core_stp_init+0x600>
    1520:	e5963024 	ldr	r3, [r6, #36]	; 0x24
    1524:	e3130001 	tst	r3, #1
    1528:	0a000140 	beq	1a30 <wmt_core_stp_init+0x534>
    152c:	e5968028 	ldr	r8, [r6, #40]	; 0x28
    1530:	e3580001 	cmp	r8, #1
    1534:	124b5030 	subne	r5, fp, #48	; 0x30
    1538:	124b7034 	subne	r7, fp, #52	; 0x34
    153c:	0a000081 	beq	1748 <wmt_core_stp_init+0x24c>
    1540:	e3a00004 	mov	r0, #4
    1544:	e1a01005 	mov	r1, r5
    1548:	e1a02007 	mov	r2, r7
    154c:	e3a03000 	mov	r3, #0
    1550:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
    1554:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
    1558:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    155c:	e3500000 	cmp	r0, #0
    1560:	1a00013d 	bne	1a5c <wmt_core_stp_init+0x560>
    1564:	e5963028 	ldr	r3, [r6, #40]	; 0x28
    1568:	e3530000 	cmp	r3, #0
    156c:	0a00004e 	beq	16ac <wmt_core_stp_init+0x1b0>
    1570:	e5943000 	ldr	r3, [r4]
    1574:	e3530003 	cmp	r3, #3
    1578:	8a0000f0 	bhi	1940 <wmt_core_stp_init+0x444>
    157c:	e3a00005 	mov	r0, #5
    1580:	e1a01005 	mov	r1, r5
    1584:	e1a02007 	mov	r2, r7
    1588:	e3a03000 	mov	r3, #0
    158c:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
    1590:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
    1594:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    1598:	e5943000 	ldr	r3, [r4]
    159c:	e3530003 	cmp	r3, #3
    15a0:	e1a08000 	mov	r8, r0
    15a4:	8a00004d 	bhi	16e0 <wmt_core_stp_init+0x1e4>
    15a8:	e3a00005 	mov	r0, #5
    15ac:	e1a01005 	mov	r1, r5
    15b0:	e1a02007 	mov	r2, r7
    15b4:	e3a03001 	mov	r3, #1
    15b8:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
    15bc:	e3a03000 	mov	r3, #0
    15c0:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
    15c4:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    15c8:	e5943000 	ldr	r3, [r4]
    15cc:	e3530003 	cmp	r3, #3
    15d0:	e0808008 	add	r8, r0, r8
    15d4:	8a000056 	bhi	1734 <wmt_core_stp_init+0x238>
    15d8:	e5963028 	ldr	r3, [r6, #40]	; 0x28
    15dc:	e3530000 	cmp	r3, #0
    15e0:	0a000043 	beq	16f4 <wmt_core_stp_init+0x1f8>
    15e4:	e3530001 	cmp	r3, #1
    15e8:	0a0000ec 	beq	19a0 <wmt_core_stp_init+0x4a4>
    15ec:	e3a00005 	mov	r0, #5
    15f0:	e1a01005 	mov	r1, r5
    15f4:	e1a02007 	mov	r2, r7
    15f8:	e3a03000 	mov	r3, #0
    15fc:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
    1600:	e3a03001 	mov	r3, #1
    1604:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
    1608:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    160c:	e0908008 	adds	r8, r0, r8
    1610:	1a000118 	bne	1a78 <wmt_core_stp_init+0x57c>
    1614:	e5943000 	ldr	r3, [r4]
    1618:	e59fa4d8 	ldr	sl, [pc, #1240]	; 1af8 <wmt_core_stp_init+0x5fc>
    161c:	e3530003 	cmp	r3, #3
    1620:	8a000069 	bhi	17cc <wmt_core_stp_init+0x2d0>
    1624:	e3a03000 	mov	r3, #0
    1628:	e50b3038 	str	r3, [fp, #-56]	; 0xffffffc8
    162c:	e30f3fff 	movw	r3, #65535	; 0xffff
    1630:	e3a00000 	mov	r0, #0
    1634:	e3a01122 	mov	r1, #-2147483640	; 0x80000008
    1638:	e24b2038 	sub	r2, fp, #56	; 0x38
    163c:	ebfffffe 	bl	131c <wmt_core_reg_rw_raw>
    1640:	e2503000 	subs	r3, r0, #0
    1644:	1a00005a 	bne	17b4 <wmt_core_stp_init+0x2b8>
    1648:	e5943000 	ldr	r3, [r4]
    164c:	e3530001 	cmp	r3, #1
    1650:	9a000003 	bls	1664 <wmt_core_stp_init+0x168>
    1654:	e59f04a4 	ldr	r0, [pc, #1188]	; 1b00 <wmt_core_stp_init+0x604>
    1658:	e59f14a4 	ldr	r1, [pc, #1188]	; 1b04 <wmt_core_stp_init+0x608>
    165c:	e51b2038 	ldr	r2, [fp, #-56]	; 0xffffffc8
    1660:	ebfffffe 	bl	0 <osal_info_print>
    1664:	e51b2038 	ldr	r2, [fp, #-56]	; 0xffffffc8
    1668:	e3063620 	movw	r3, #26144	; 0x6620
    166c:	e1520003 	cmp	r2, r3
    1670:	0a000066 	beq	1810 <wmt_core_stp_init+0x314>
    1674:	e1a03002 	mov	r3, r2
    1678:	e59f0488 	ldr	r0, [pc, #1160]	; 1b08 <wmt_core_stp_init+0x60c>
    167c:	e59f1480 	ldr	r1, [pc, #1152]	; 1b04 <wmt_core_stp_init+0x608>
    1680:	e30023ce 	movw	r2, #974	; 0x3ce
    1684:	ebfffffe 	bl	0 <osal_err_print>
    1688:	e3e03002 	mvn	r3, #2
    168c:	e59f0478 	ldr	r0, [pc, #1144]	; 1b0c <wmt_core_stp_init+0x610>
    1690:	e300232a 	movw	r2, #810	; 0x32a
    1694:	e59f1474 	ldr	r1, [pc, #1140]	; 1b10 <wmt_core_stp_init+0x614>
    1698:	e3e05007 	mvn	r5, #7
    169c:	ebfffffe 	bl	0 <osal_err_print>
    16a0:	e1a00005 	mov	r0, r5
    16a4:	e24bd028 	sub	sp, fp, #40	; 0x28
    16a8:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
    16ac:	e5943000 	ldr	r3, [r4]
    16b0:	e3530001 	cmp	r3, #1
    16b4:	9affffb0 	bls	157c <wmt_core_stp_init+0x80>
    16b8:	e30c2200 	movw	r2, #49664	; 0xc200
    16bc:	e59f144c 	ldr	r1, [pc, #1100]	; 1b10 <wmt_core_stp_init+0x614>
    16c0:	e3402001 	movt	r2, #1
    16c4:	e59f0448 	ldr	r0, [pc, #1096]	; 1b14 <wmt_core_stp_init+0x618>
    16c8:	ebfffffe 	bl	0 <osal_info_print>
    16cc:	eaffffaa 	b	157c <wmt_core_stp_init+0x80>
    16d0:	e59f1438 	ldr	r1, [pc, #1080]	; 1b10 <wmt_core_stp_init+0x614>
    16d4:	e59f043c 	ldr	r0, [pc, #1084]	; 1b18 <wmt_core_stp_init+0x61c>
    16d8:	ebfffffe 	bl	0 <osal_loud_print>
    16dc:	eaffff8e 	b	151c <wmt_core_stp_init+0x20>
    16e0:	e1a02008 	mov	r2, r8
    16e4:	e59f1424 	ldr	r1, [pc, #1060]	; 1b10 <wmt_core_stp_init+0x614>
    16e8:	e59f042c 	ldr	r0, [pc, #1068]	; 1b1c <wmt_core_stp_init+0x620>
    16ec:	ebfffffe 	bl	0 <osal_loud_print>
    16f0:	eaffffac 	b	15a8 <wmt_core_stp_init+0xac>
    16f4:	e3a00005 	mov	r0, #5
    16f8:	e1a01005 	mov	r1, r5
    16fc:	e1a02007 	mov	r2, r7
    1700:	e3a03002 	mov	r3, #2
    1704:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
    1708:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
    170c:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    1710:	e5943000 	ldr	r3, [r4]
    1714:	e3530003 	cmp	r3, #3
    1718:	e0888000 	add	r8, r8, r0
    171c:	9affffb2 	bls	15ec <wmt_core_stp_init+0xf0>
    1720:	e59f13e8 	ldr	r1, [pc, #1000]	; 1b10 <wmt_core_stp_init+0x614>
    1724:	e1a02008 	mov	r2, r8
    1728:	e59f03f0 	ldr	r0, [pc, #1008]	; 1b20 <wmt_core_stp_init+0x624>
    172c:	ebfffffe 	bl	0 <osal_loud_print>
    1730:	eaffffad 	b	15ec <wmt_core_stp_init+0xf0>
    1734:	e1a02008 	mov	r2, r8
    1738:	e59f13d0 	ldr	r1, [pc, #976]	; 1b10 <wmt_core_stp_init+0x614>
    173c:	e59f03e0 	ldr	r0, [pc, #992]	; 1b24 <wmt_core_stp_init+0x628>
    1740:	ebfffffe 	bl	0 <osal_loud_print>
    1744:	eaffffa3 	b	15d8 <wmt_core_stp_init+0xdc>
    1748:	e24b5030 	sub	r5, fp, #48	; 0x30
    174c:	e24b7034 	sub	r7, fp, #52	; 0x34
    1750:	e3a0000a 	mov	r0, #10
    1754:	e1a01005 	mov	r1, r5
    1758:	e1a02007 	mov	r2, r7
    175c:	e50b8034 	str	r8, [fp, #-52]	; 0xffffffcc
    1760:	e3a0a002 	mov	sl, #2
    1764:	e50ba030 	str	sl, [fp, #-48]	; 0xffffffd0
    1768:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    176c:	e2503000 	subs	r3, r0, #0
    1770:	1a0000ce 	bne	1ab0 <wmt_core_stp_init+0x5b4>
    1774:	e3a0000b 	mov	r0, #11
    1778:	e1a01005 	mov	r1, r5
    177c:	e1a02007 	mov	r2, r7
    1780:	e586a01c 	str	sl, [r6, #28]
    1784:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
    1788:	e50b8034 	str	r8, [fp, #-52]	; 0xffffffcc
    178c:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    1790:	e3500000 	cmp	r0, #0
    1794:	1a0000d0 	bne	1adc <wmt_core_stp_init+0x5e0>
    1798:	e5943000 	ldr	r3, [r4]
    179c:	e3530003 	cmp	r3, #3
    17a0:	9affff66 	bls	1540 <wmt_core_stp_init+0x44>
    17a4:	e59f1364 	ldr	r1, [pc, #868]	; 1b10 <wmt_core_stp_init+0x614>
    17a8:	e59f0378 	ldr	r0, [pc, #888]	; 1b28 <wmt_core_stp_init+0x62c>
    17ac:	ebfffffe 	bl	0 <osal_loud_print>
    17b0:	eaffff62 	b	1540 <wmt_core_stp_init+0x44>
    17b4:	e59f0370 	ldr	r0, [pc, #880]	; 1b2c <wmt_core_stp_init+0x630>
    17b8:	e30023b7 	movw	r2, #951	; 0x3b7
    17bc:	e59f1340 	ldr	r1, [pc, #832]	; 1b04 <wmt_core_stp_init+0x608>
    17c0:	ebfffffe 	bl	0 <osal_err_print>
    17c4:	e3e03001 	mvn	r3, #1
    17c8:	eaffffaf 	b	168c <wmt_core_stp_init+0x190>
    17cc:	e59f035c 	ldr	r0, [pc, #860]	; 1b30 <wmt_core_stp_init+0x634>
    17d0:	e59f1338 	ldr	r1, [pc, #824]	; 1b10 <wmt_core_stp_init+0x614>
    17d4:	ebfffffe 	bl	0 <osal_loud_print>
    17d8:	e59a3000 	ldr	r3, [sl]
    17dc:	e3530003 	cmp	r3, #3
    17e0:	9affff8f 	bls	1624 <wmt_core_stp_init+0x128>
    17e4:	e59f032c 	ldr	r0, [pc, #812]	; 1b18 <wmt_core_stp_init+0x61c>
    17e8:	e59f1314 	ldr	r1, [pc, #788]	; 1b04 <wmt_core_stp_init+0x608>
    17ec:	ebfffffe 	bl	0 <osal_loud_print>
    17f0:	e59a3000 	ldr	r3, [sl]
    17f4:	e50b8038 	str	r8, [fp, #-56]	; 0xffffffc8
    17f8:	e3530003 	cmp	r3, #3
    17fc:	9affff8a 	bls	162c <wmt_core_stp_init+0x130>
    1800:	e59f12fc 	ldr	r1, [pc, #764]	; 1b04 <wmt_core_stp_init+0x608>
    1804:	e59f0328 	ldr	r0, [pc, #808]	; 1b34 <wmt_core_stp_init+0x638>
    1808:	ebfffffe 	bl	0 <osal_loud_print>
    180c:	eaffff86 	b	162c <wmt_core_stp_init+0x130>
    1810:	e59f8320 	ldr	r8, [pc, #800]	; 1b38 <wmt_core_stp_init+0x63c>
    1814:	e5989004 	ldr	r9, [r8, #4]
    1818:	e3590000 	cmp	r9, #0
    181c:	0a000070 	beq	19e4 <wmt_core_stp_init+0x4e8>
    1820:	e598e008 	ldr	lr, [r8, #8]
    1824:	e35e0000 	cmp	lr, #0
    1828:	0a000050 	beq	1970 <wmt_core_stp_init+0x474>
    182c:	e598c010 	ldr	ip, [r8, #16]
    1830:	e35c0000 	cmp	ip, #0
    1834:	0598a00c 	ldreq	sl, [r8, #12]
    1838:	0a00004e 	beq	1978 <wmt_core_stp_init+0x47c>
    183c:	e598a00c 	ldr	sl, [r8, #12]
    1840:	e35a0000 	cmp	sl, #0
    1844:	0a00004b 	beq	1978 <wmt_core_stp_init+0x47c>
    1848:	e5943000 	ldr	r3, [r4]
    184c:	e3530002 	cmp	r3, #2
    1850:	9a000007 	bls	1874 <wmt_core_stp_init+0x378>
    1854:	e1a03009 	mov	r3, r9
    1858:	e59f02dc 	ldr	r0, [pc, #732]	; 1b3c <wmt_core_stp_init+0x640>
    185c:	e59f12a0 	ldr	r1, [pc, #672]	; 1b04 <wmt_core_stp_init+0x608>
    1860:	e58dc008 	str	ip, [sp, #8]
    1864:	e58de000 	str	lr, [sp]
    1868:	e58da004 	str	sl, [sp, #4]
    186c:	ebfffffe 	bl	0 <osal_dbg_print>
    1870:	e598c010 	ldr	ip, [r8, #16]
    1874:	e12fff3c 	blx	ip
    1878:	e250c000 	subs	ip, r0, #0
    187c:	1a000033 	bne	1950 <wmt_core_stp_init+0x454>
    1880:	e5943000 	ldr	r3, [r4]
    1884:	e3530001 	cmp	r3, #1
    1888:	95868050 	strls	r8, [r6, #80]	; 0x50
    188c:	9a00000d 	bls	18c8 <wmt_core_stp_init+0x3cc>
    1890:	e59f02a8 	ldr	r0, [pc, #680]	; 1b40 <wmt_core_stp_init+0x644>
    1894:	e59f1268 	ldr	r1, [pc, #616]	; 1b04 <wmt_core_stp_init+0x608>
    1898:	e51b2038 	ldr	r2, [fp, #-56]	; 0xffffffc8
    189c:	ebfffffe 	bl	0 <osal_info_print>
    18a0:	e59f3250 	ldr	r3, [pc, #592]	; 1af8 <wmt_core_stp_init+0x5fc>
    18a4:	e5868050 	str	r8, [r6, #80]	; 0x50
    18a8:	e5933000 	ldr	r3, [r3]
    18ac:	e3530003 	cmp	r3, #3
    18b0:	9a000004 	bls	18c8 <wmt_core_stp_init+0x3cc>
    18b4:	e59f0288 	ldr	r0, [pc, #648]	; 1b44 <wmt_core_stp_init+0x648>
    18b8:	e59f1250 	ldr	r1, [pc, #592]	; 1b10 <wmt_core_stp_init+0x614>
    18bc:	ebfffffe 	bl	0 <osal_loud_print>
    18c0:	e59f3234 	ldr	r3, [pc, #564]	; 1afc <wmt_core_stp_init+0x600>
    18c4:	e5938050 	ldr	r8, [r3, #80]	; 0x50
    18c8:	e5983004 	ldr	r3, [r8, #4]
    18cc:	e3530000 	cmp	r3, #0
    18d0:	0a000047 	beq	19f4 <wmt_core_stp_init+0x4f8>
    18d4:	e59f026c 	ldr	r0, [pc, #620]	; 1b48 <wmt_core_stp_init+0x64c>
    18d8:	e12fff33 	blx	r3
    18dc:	e3500000 	cmp	r0, #0
    18e0:	1a00006b 	bne	1a94 <wmt_core_stp_init+0x598>
    18e4:	e5943000 	ldr	r3, [r4]
    18e8:	e3530003 	cmp	r3, #3
    18ec:	8a00000f 	bhi	1930 <wmt_core_stp_init+0x434>
    18f0:	e1a01005 	mov	r1, r5
    18f4:	e1a02007 	mov	r2, r7
    18f8:	e3a00005 	mov	r0, #5
    18fc:	e3a03001 	mov	r3, #1
    1900:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
    1904:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
    1908:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    190c:	e5943000 	ldr	r3, [r4]
    1910:	e3530003 	cmp	r3, #3
    1914:	e1a05000 	mov	r5, r0
    1918:	9affff60 	bls	16a0 <wmt_core_stp_init+0x1a4>
    191c:	e1a02005 	mov	r2, r5
    1920:	e59f11e8 	ldr	r1, [pc, #488]	; 1b10 <wmt_core_stp_init+0x614>
    1924:	e59f0220 	ldr	r0, [pc, #544]	; 1b4c <wmt_core_stp_init+0x650>
    1928:	ebfffffe 	bl	0 <osal_loud_print>
    192c:	eaffff5b 	b	16a0 <wmt_core_stp_init+0x1a4>
    1930:	e59f11d8 	ldr	r1, [pc, #472]	; 1b10 <wmt_core_stp_init+0x614>
    1934:	e59f0214 	ldr	r0, [pc, #532]	; 1b50 <wmt_core_stp_init+0x654>
    1938:	ebfffffe 	bl	0 <osal_loud_print>
    193c:	eaffffeb 	b	18f0 <wmt_core_stp_init+0x3f4>
    1940:	e59f11c8 	ldr	r1, [pc, #456]	; 1b10 <wmt_core_stp_init+0x614>
    1944:	e59f0208 	ldr	r0, [pc, #520]	; 1b54 <wmt_core_stp_init+0x658>
    1948:	ebfffffe 	bl	0 <osal_loud_print>
    194c:	eaffff0a 	b	157c <wmt_core_stp_init+0x80>
    1950:	e51b3038 	ldr	r3, [fp, #-56]	; 0xffffffc8
    1954:	e30023db 	movw	r2, #987	; 0x3db
    1958:	e59f01f8 	ldr	r0, [pc, #504]	; 1b58 <wmt_core_stp_init+0x65c>
    195c:	e59f11a0 	ldr	r1, [pc, #416]	; 1b04 <wmt_core_stp_init+0x608>
    1960:	e58dc000 	str	ip, [sp]
    1964:	ebfffffe 	bl	0 <osal_err_print>
    1968:	e3e03004 	mvn	r3, #4
    196c:	eaffff46 	b	168c <wmt_core_stp_init+0x190>
    1970:	e598a00c 	ldr	sl, [r8, #12]
    1974:	e598c010 	ldr	ip, [r8, #16]
    1978:	e3063620 	movw	r3, #26144	; 0x6620
    197c:	e59f01d8 	ldr	r0, [pc, #472]	; 1b5c <wmt_core_stp_init+0x660>
    1980:	e30023d3 	movw	r2, #979	; 0x3d3
    1984:	e59f1178 	ldr	r1, [pc, #376]	; 1b04 <wmt_core_stp_init+0x608>
    1988:	e88d4200 	stm	sp, {r9, lr}
    198c:	e58da008 	str	sl, [sp, #8]
    1990:	e58dc00c 	str	ip, [sp, #12]
    1994:	ebfffffe 	bl	0 <osal_err_print>
    1998:	e3e03003 	mvn	r3, #3
    199c:	eaffff3a 	b	168c <wmt_core_stp_init+0x190>
    19a0:	e3a00005 	mov	r0, #5
    19a4:	e1a01005 	mov	r1, r5
    19a8:	e1a02007 	mov	r2, r7
    19ac:	e3a03002 	mov	r3, #2
    19b0:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
    19b4:	e3a03004 	mov	r3, #4
    19b8:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
    19bc:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    19c0:	e5943000 	ldr	r3, [r4]
    19c4:	e3530003 	cmp	r3, #3
    19c8:	e0888000 	add	r8, r8, r0
    19cc:	9affff06 	bls	15ec <wmt_core_stp_init+0xf0>
    19d0:	e1a02008 	mov	r2, r8
    19d4:	e59f1134 	ldr	r1, [pc, #308]	; 1b10 <wmt_core_stp_init+0x614>
    19d8:	e59f0180 	ldr	r0, [pc, #384]	; 1b60 <wmt_core_stp_init+0x664>
    19dc:	ebfffffe 	bl	0 <osal_loud_print>
    19e0:	eaffff01 	b	15ec <wmt_core_stp_init+0xf0>
    19e4:	e598a00c 	ldr	sl, [r8, #12]
    19e8:	e598e008 	ldr	lr, [r8, #8]
    19ec:	e598c010 	ldr	ip, [r8, #16]
    19f0:	eaffffe0 	b	1978 <wmt_core_stp_init+0x47c>
    19f4:	e59f3168 	ldr	r3, [pc, #360]	; 1b64 <wmt_core_stp_init+0x668>
    19f8:	e3a02e33 	mov	r2, #816	; 0x330
    19fc:	e59f0164 	ldr	r0, [pc, #356]	; 1b68 <wmt_core_stp_init+0x66c>
    1a00:	e59f1164 	ldr	r1, [pc, #356]	; 1b6c <wmt_core_stp_init+0x670>
    1a04:	ebfffffe 	bl	0 <osal_err_print>
    1a08:	e5963050 	ldr	r3, [r6, #80]	; 0x50
    1a0c:	e5933004 	ldr	r3, [r3, #4]
    1a10:	e3530000 	cmp	r3, #0
    1a14:	1affffae 	bne	18d4 <wmt_core_stp_init+0x3d8>
    1a18:	e3002335 	movw	r2, #821	; 0x335
    1a1c:	e59f10ec 	ldr	r1, [pc, #236]	; 1b10 <wmt_core_stp_init+0x614>
    1a20:	e59f0148 	ldr	r0, [pc, #328]	; 1b70 <wmt_core_stp_init+0x674>
    1a24:	e3e05008 	mvn	r5, #8
    1a28:	ebfffffe 	bl	0 <osal_err_print>
    1a2c:	eaffff1b 	b	16a0 <wmt_core_stp_init+0x1a4>
    1a30:	e59f10d8 	ldr	r1, [pc, #216]	; 1b10 <wmt_core_stp_init+0x614>
    1a34:	e30022cd 	movw	r2, #717	; 0x2cd
    1a38:	e59f0134 	ldr	r0, [pc, #308]	; 1b74 <wmt_core_stp_init+0x678>
    1a3c:	e3e05000 	mvn	r5, #0
    1a40:	ebfffffe 	bl	0 <osal_err_print>
    1a44:	e59f1120 	ldr	r1, [pc, #288]	; 1b6c <wmt_core_stp_init+0x670>
    1a48:	e30022ce 	movw	r2, #718	; 0x2ce
    1a4c:	e59f3124 	ldr	r3, [pc, #292]	; 1b78 <wmt_core_stp_init+0x67c>
    1a50:	e59f0110 	ldr	r0, [pc, #272]	; 1b68 <wmt_core_stp_init+0x66c>
    1a54:	ebfffffe 	bl	0 <osal_err_print>
    1a58:	eaffff10 	b	16a0 <wmt_core_stp_init+0x1a4>
    1a5c:	e1a03000 	mov	r3, r0
    1a60:	e59f10a8 	ldr	r1, [pc, #168]	; 1b10 <wmt_core_stp_init+0x614>
    1a64:	e59f0110 	ldr	r0, [pc, #272]	; 1b7c <wmt_core_stp_init+0x680>
    1a68:	e30022ef 	movw	r2, #751	; 0x2ef
    1a6c:	ebfffffe 	bl	0 <osal_err_print>
    1a70:	e3e05003 	mvn	r5, #3
    1a74:	eaffff09 	b	16a0 <wmt_core_stp_init+0x1a4>
    1a78:	e1a03008 	mov	r3, r8
    1a7c:	e59f00fc 	ldr	r0, [pc, #252]	; 1b80 <wmt_core_stp_init+0x684>
    1a80:	e59f1088 	ldr	r1, [pc, #136]	; 1b10 <wmt_core_stp_init+0x614>
    1a84:	e3002321 	movw	r2, #801	; 0x321
    1a88:	ebfffffe 	bl	0 <osal_err_print>
    1a8c:	e3e05006 	mvn	r5, #6
    1a90:	eaffff02 	b	16a0 <wmt_core_stp_init+0x1a4>
    1a94:	e1a03000 	mov	r3, r0
    1a98:	e59f1070 	ldr	r1, [pc, #112]	; 1b10 <wmt_core_stp_init+0x614>
    1a9c:	e59f00e0 	ldr	r0, [pc, #224]	; 1b84 <wmt_core_stp_init+0x688>
    1aa0:	e3002339 	movw	r2, #825	; 0x339
    1aa4:	ebfffffe 	bl	0 <osal_err_print>
    1aa8:	e3e05009 	mvn	r5, #9
    1aac:	eafffefb 	b	16a0 <wmt_core_stp_init+0x1a4>
    1ab0:	e59f1058 	ldr	r1, [pc, #88]	; 1b10 <wmt_core_stp_init+0x614>
    1ab4:	e3a02fb6 	mov	r2, #728	; 0x2d8
    1ab8:	e59f00c8 	ldr	r0, [pc, #200]	; 1b88 <wmt_core_stp_init+0x68c>
    1abc:	e3e05001 	mvn	r5, #1
    1ac0:	ebfffffe 	bl	0 <osal_err_print>
    1ac4:	e59f10a0 	ldr	r1, [pc, #160]	; 1b6c <wmt_core_stp_init+0x670>
    1ac8:	e30022d9 	movw	r2, #729	; 0x2d9
    1acc:	e59f30a4 	ldr	r3, [pc, #164]	; 1b78 <wmt_core_stp_init+0x67c>
    1ad0:	e59f0090 	ldr	r0, [pc, #144]	; 1b68 <wmt_core_stp_init+0x66c>
    1ad4:	ebfffffe 	bl	0 <osal_err_print>
    1ad8:	eafffef0 	b	16a0 <wmt_core_stp_init+0x1a4>
    1adc:	e1a03000 	mov	r3, r0
    1ae0:	e59f1028 	ldr	r1, [pc, #40]	; 1b10 <wmt_core_stp_init+0x614>
    1ae4:	e59f00a0 	ldr	r0, [pc, #160]	; 1b8c <wmt_core_stp_init+0x690>
    1ae8:	e30022e3 	movw	r2, #739	; 0x2e3
    1aec:	ebfffffe 	bl	0 <osal_err_print>
    1af0:	e3e05002 	mvn	r5, #2
    1af4:	eafffee9 	b	16a0 <wmt_core_stp_init+0x1a4>
	...
    1b00:	00000e08 	andeq	r0, r0, r8, lsl #28
    1b04:	000001b4 			; <UNDEFINED> instruction: 0x000001b4
    1b08:	00000e34 	andeq	r0, r0, r4, lsr lr
    1b0c:	00000f94 	muleq	r0, r4, pc	; <UNPREDICTABLE>
    1b10:	000001a0 	andeq	r0, r0, r0, lsr #3
    1b14:	00000c6c 	andeq	r0, r0, ip, ror #24
    1b18:	00000b84 	andeq	r0, r0, r4, lsl #23
    1b1c:	00000cc4 	andeq	r0, r0, r4, asr #25
    1b20:	00000d0c 	andeq	r0, r0, ip, lsl #26
    1b24:	00000ce8 	andeq	r0, r0, r8, ror #25
    1b28:	00000c20 	andeq	r0, r0, r0, lsr #24
    1b2c:	00000dd4 	ldrdeq	r0, [r0], -r4
    1b30:	00000d88 	andeq	r0, r0, r8, lsl #27
    1b34:	00000da8 	andeq	r0, r0, r8, lsr #27
    1b38:	00000000 	andeq	r0, r0, r0
    1b3c:	00000edc 	ldrdeq	r0, [r0], -ip
    1b40:	00000f68 	andeq	r0, r0, r8, ror #30
    1b44:	00000fb8 			; <UNDEFINED> instruction: 0x00000fb8
    1b48:	00000028 	andeq	r0, r0, r8, lsr #32
    1b4c:	00001050 	andeq	r1, r0, r0, asr r0
    1b50:	0000102c 	andeq	r1, r0, ip, lsr #32
    1b54:	00000ca8 	andeq	r0, r0, r8, lsr #25
    1b58:	00000f34 	andeq	r0, r0, r4, lsr pc
    1b5c:	00000e6c 	andeq	r0, r0, ip, ror #28
    1b60:	00000d34 	andeq	r0, r0, r4, lsr sp
    1b64:	00000fd4 	ldrdeq	r0, [r0], -r4
    1b68:	0000026c 	andeq	r0, r0, ip, ror #4
    1b6c:	0000027c 	andeq	r0, r0, ip, ror r2
    1b70:	00000624 	andeq	r0, r0, r4, lsr #12
    1b74:	00000b98 	muleq	r0, r8, fp
    1b78:	000002ac 	andeq	r0, r0, ip, lsr #5
    1b7c:	00000c48 	andeq	r0, r0, r8, asr #24
    1b80:	00000d5c 	andeq	r0, r0, ip, asr sp
    1b84:	00000ff4 	strdeq	r0, [r0], -r4
    1b88:	00000bb8 			; <UNDEFINED> instruction: 0x00000bb8
    1b8c:	00000be8 	andeq	r0, r0, r8, ror #23

00001b90 <opfunc_sw_rst>:
    1b90:	e1a0c00d 	mov	ip, sp
    1b94:	e92dd800 	push	{fp, ip, lr, pc}
    1b98:	e24cb004 	sub	fp, ip, #4
    1b9c:	ebfffe56 	bl	14fc <wmt_core_stp_init>
    1ba0:	e89da800 	ldm	sp, {fp, sp, pc}

00001ba4 <opfunc_pwr_on>:
    1ba4:	e1a0c00d 	mov	ip, sp
    1ba8:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
    1bac:	e24cb004 	sub	fp, ip, #4
    1bb0:	e24dd00c 	sub	sp, sp, #12
    1bb4:	e59fa194 	ldr	sl, [pc, #404]	; 1d50 <opfunc_pwr_on+0x1ac>
    1bb8:	e1a09000 	mov	r9, r0
    1bbc:	e59a3010 	ldr	r3, [sl, #16]
    1bc0:	e3530000 	cmp	r3, #0
    1bc4:	1a000056 	bne	1d24 <opfunc_pwr_on+0x180>
    1bc8:	e5903004 	ldr	r3, [r0, #4]
    1bcc:	e3130001 	tst	r3, #1
    1bd0:	1a00004b 	bne	1d04 <opfunc_pwr_on+0x160>
    1bd4:	e3a04002 	mov	r4, #2
    1bd8:	e3a05001 	mov	r5, #1
    1bdc:	e3a07000 	mov	r7, #0
    1be0:	e59f816c 	ldr	r8, [pc, #364]	; 1d54 <opfunc_pwr_on+0x1b0>
    1be4:	ea00000a 	b	1c14 <opfunc_pwr_on+0x70>
    1be8:	e3540000 	cmp	r4, #0
    1bec:	da00002a 	ble	1c9c <opfunc_pwr_on+0xf8>
    1bf0:	e5983000 	ldr	r3, [r8]
    1bf4:	e3530001 	cmp	r3, #1
    1bf8:	9a000003 	bls	1c0c <opfunc_pwr_on+0x68>
    1bfc:	e59f1154 	ldr	r1, [pc, #340]	; 1d58 <opfunc_pwr_on+0x1b4>
    1c00:	e1a02005 	mov	r2, r5
    1c04:	e59f0150 	ldr	r0, [pc, #336]	; 1d5c <opfunc_pwr_on+0x1b8>
    1c08:	ebfffffe 	bl	0 <osal_info_print>
    1c0c:	e2455001 	sub	r5, r5, #1
    1c10:	e2444001 	sub	r4, r4, #1
    1c14:	e3a00001 	mov	r0, #1
    1c18:	e24b1030 	sub	r1, fp, #48	; 0x30
    1c1c:	e24b2034 	sub	r2, fp, #52	; 0x34
    1c20:	e50b7030 	str	r7, [fp, #-48]	; 0xffffffd0
    1c24:	e50b7034 	str	r7, [fp, #-52]	; 0xffffffcc
    1c28:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    1c2c:	e3500000 	cmp	r0, #0
    1c30:	1a00001b 	bne	1ca4 <opfunc_pwr_on+0x100>
    1c34:	e3a03001 	mov	r3, #1
    1c38:	e58a3010 	str	r3, [sl, #16]
    1c3c:	ebfffe2e 	bl	14fc <wmt_core_stp_init>
    1c40:	e2506000 	subs	r6, r0, #0
    1c44:	0a000025 	beq	1ce0 <opfunc_pwr_on+0x13c>
    1c48:	e1a03006 	mov	r3, r6
    1c4c:	e59f1104 	ldr	r1, [pc, #260]	; 1d58 <opfunc_pwr_on+0x1b4>
    1c50:	e3002422 	movw	r2, #1058	; 0x422
    1c54:	e59f0104 	ldr	r0, [pc, #260]	; 1d60 <opfunc_pwr_on+0x1bc>
    1c58:	ebfffffe 	bl	0 <osal_err_print>
    1c5c:	e59f3100 	ldr	r3, [pc, #256]	; 1d64 <opfunc_pwr_on+0x1c0>
    1c60:	e59f1100 	ldr	r1, [pc, #256]	; 1d68 <opfunc_pwr_on+0x1c4>
    1c64:	e3002423 	movw	r2, #1059	; 0x423
    1c68:	e59f00fc 	ldr	r0, [pc, #252]	; 1d6c <opfunc_pwr_on+0x1c8>
    1c6c:	ebfffffe 	bl	0 <osal_err_print>
    1c70:	ebfffb70 	bl	a38 <wmt_core_stp_deinit>
    1c74:	e1a00009 	mov	r0, r9
    1c78:	ebfffbfb 	bl	c6c <opfunc_pwr_off>
    1c7c:	e2503000 	subs	r3, r0, #0
    1c80:	0affffd8 	beq	1be8 <opfunc_pwr_on+0x44>
    1c84:	e59f00e4 	ldr	r0, [pc, #228]	; 1d70 <opfunc_pwr_on+0x1cc>
    1c88:	e3002429 	movw	r2, #1065	; 0x429
    1c8c:	e59f10c4 	ldr	r1, [pc, #196]	; 1d58 <opfunc_pwr_on+0x1b4>
    1c90:	ebfffffe 	bl	0 <osal_err_print>
    1c94:	e3540000 	cmp	r4, #0
    1c98:	caffffd4 	bgt	1bf0 <opfunc_pwr_on+0x4c>
    1c9c:	e3e06001 	mvn	r6, #1
    1ca0:	ea000014 	b	1cf8 <opfunc_pwr_on+0x154>
    1ca4:	e1a03000 	mov	r3, r0
    1ca8:	e59f10a8 	ldr	r1, [pc, #168]	; 1d58 <opfunc_pwr_on+0x1b4>
    1cac:	e59f00c0 	ldr	r0, [pc, #192]	; 1d74 <opfunc_pwr_on+0x1d0>
    1cb0:	e3002416 	movw	r2, #1046	; 0x416
    1cb4:	ebfffffe 	bl	0 <osal_err_print>
    1cb8:	e3540000 	cmp	r4, #0
    1cbc:	1a000016 	bne	1d1c <opfunc_pwr_on+0x178>
    1cc0:	e5983000 	ldr	r3, [r8]
    1cc4:	e3530001 	cmp	r3, #1
    1cc8:	9affffcf 	bls	1c0c <opfunc_pwr_on+0x68>
    1ccc:	e59f1084 	ldr	r1, [pc, #132]	; 1d58 <opfunc_pwr_on+0x1b4>
    1cd0:	e1a02005 	mov	r2, r5
    1cd4:	e59f009c 	ldr	r0, [pc, #156]	; 1d78 <opfunc_pwr_on+0x1d4>
    1cd8:	ebfffffe 	bl	0 <osal_info_print>
    1cdc:	eaffffca 	b	1c0c <opfunc_pwr_on+0x68>
    1ce0:	e59f306c 	ldr	r3, [pc, #108]	; 1d54 <opfunc_pwr_on+0x1b0>
    1ce4:	e5933000 	ldr	r3, [r3]
    1ce8:	e3530002 	cmp	r3, #2
    1cec:	8a000006 	bhi	1d0c <opfunc_pwr_on+0x168>
    1cf0:	e3a03002 	mov	r3, #2
    1cf4:	e58a3010 	str	r3, [sl, #16]
    1cf8:	e1a00006 	mov	r0, r6
    1cfc:	e24bd028 	sub	sp, fp, #40	; 0x28
    1d00:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
    1d04:	ebfff983 	bl	318 <opfunc_hif_conf>
    1d08:	eaffffb1 	b	1bd4 <opfunc_pwr_on+0x30>
    1d0c:	e59f1044 	ldr	r1, [pc, #68]	; 1d58 <opfunc_pwr_on+0x1b4>
    1d10:	e59f0064 	ldr	r0, [pc, #100]	; 1d7c <opfunc_pwr_on+0x1d8>
    1d14:	ebfffffe 	bl	0 <osal_dbg_print>
    1d18:	eafffff4 	b	1cf0 <opfunc_pwr_on+0x14c>
    1d1c:	e3e06000 	mvn	r6, #0
    1d20:	eafffff4 	b	1cf8 <opfunc_pwr_on+0x154>
    1d24:	e59f102c 	ldr	r1, [pc, #44]	; 1d58 <opfunc_pwr_on+0x1b4>
    1d28:	e3002406 	movw	r2, #1030	; 0x406
    1d2c:	e59f004c 	ldr	r0, [pc, #76]	; 1d80 <opfunc_pwr_on+0x1dc>
    1d30:	e3e06000 	mvn	r6, #0
    1d34:	ebfffffe 	bl	0 <osal_err_print>
    1d38:	e59f1028 	ldr	r1, [pc, #40]	; 1d68 <opfunc_pwr_on+0x1c4>
    1d3c:	e3002407 	movw	r2, #1031	; 0x407
    1d40:	e59f301c 	ldr	r3, [pc, #28]	; 1d64 <opfunc_pwr_on+0x1c0>
    1d44:	e59f0020 	ldr	r0, [pc, #32]	; 1d6c <opfunc_pwr_on+0x1c8>
    1d48:	ebfffffe 	bl	0 <osal_err_print>
    1d4c:	eaffffe9 	b	1cf8 <opfunc_pwr_on+0x154>
	...
    1d58:	000001c8 	andeq	r0, r0, r8, asr #3
    1d5c:	00001170 	andeq	r1, r0, r0, ror r1
    1d60:	00001100 	andeq	r1, r0, r0, lsl #2
    1d64:	000002ac 	andeq	r0, r0, ip, lsr #5
    1d68:	0000027c 	andeq	r0, r0, ip, ror r2
    1d6c:	0000026c 	andeq	r0, r0, ip, ror #4
    1d70:	00001130 	andeq	r1, r0, r0, lsr r1
    1d74:	000010b0 	strheq	r1, [r0], -r0
    1d78:	000010e4 	andeq	r1, r0, r4, ror #1
    1d7c:	00001198 	muleq	r0, r8, r1
    1d80:	00001074 	andeq	r1, r0, r4, ror r0

00001d84 <opfunc_func_on>:
    1d84:	e1a0c00d 	mov	ip, sp
    1d88:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
    1d8c:	e24cb004 	sub	fp, ip, #4
    1d90:	e24dd02c 	sub	sp, sp, #44	; 0x2c
    1d94:	e5905008 	ldr	r5, [r0, #8]
    1d98:	e1a07000 	mov	r7, r0
    1d9c:	e3550008 	cmp	r5, #8
    1da0:	8a0000ca 	bhi	20d0 <opfunc_func_on+0x34c>
    1da4:	e59f43e4 	ldr	r4, [pc, #996]	; 2190 <opfunc_func_on+0x40c>
    1da8:	e794c105 	ldr	ip, [r4, r5, lsl #2]
    1dac:	e35c0002 	cmp	ip, #2
    1db0:	8a0000d2 	bhi	2100 <opfunc_func_on+0x37c>
    1db4:	0a00006d 	beq	1f70 <opfunc_func_on+0x1ec>
    1db8:	e5943010 	ldr	r3, [r4, #16]
    1dbc:	e3530002 	cmp	r3, #2
    1dc0:	0a000002 	beq	1dd0 <opfunc_func_on+0x4c>
    1dc4:	ebffff76 	bl	1ba4 <opfunc_pwr_on>
    1dc8:	e250c000 	subs	ip, r0, #0
    1dcc:	1a000098 	bne	2034 <opfunc_func_on+0x2b0>
    1dd0:	e3550003 	cmp	r5, #3
    1dd4:	9a00001c 	bls	1e4c <opfunc_func_on+0xc8>
    1dd8:	e3550008 	cmp	r5, #8
    1ddc:	03a03002 	moveq	r3, #2
    1de0:	05843020 	streq	r3, [r4, #32]
    1de4:	e59f33a8 	ldr	r3, [pc, #936]	; 2194 <opfunc_func_on+0x410>
    1de8:	e5933000 	ldr	r3, [r3]
    1dec:	e3530001 	cmp	r3, #1
    1df0:	9a000062 	bls	1f80 <opfunc_func_on+0x1fc>
    1df4:	e5949014 	ldr	r9, [r4, #20]
    1df8:	e3a06000 	mov	r6, #0
    1dfc:	e8944028 	ldm	r4, {r3, r5, lr}
    1e00:	e594c00c 	ldr	ip, [r4, #12]
    1e04:	e5947020 	ldr	r7, [r4, #32]
    1e08:	e5948010 	ldr	r8, [r4, #16]
    1e0c:	e594a018 	ldr	sl, [r4, #24]
    1e10:	e594401c 	ldr	r4, [r4, #28]
    1e14:	e59f037c 	ldr	r0, [pc, #892]	; 2198 <opfunc_func_on+0x414>
    1e18:	e59f137c 	ldr	r1, [pc, #892]	; 219c <opfunc_func_on+0x418>
    1e1c:	e59f237c 	ldr	r2, [pc, #892]	; 21a0 <opfunc_func_on+0x41c>
    1e20:	e88d4020 	stm	sp, {r5, lr}
    1e24:	e58dc008 	str	ip, [sp, #8]
    1e28:	e58d700c 	str	r7, [sp, #12]
    1e2c:	e58d8010 	str	r8, [sp, #16]
    1e30:	e58da014 	str	sl, [sp, #20]
    1e34:	e58d4018 	str	r4, [sp, #24]
    1e38:	e58d901c 	str	r9, [sp, #28]
    1e3c:	ebfffffe 	bl	0 <osal_info_print>
    1e40:	e1a00006 	mov	r0, r6
    1e44:	e24bd028 	sub	sp, fp, #40	; 0x28
    1e48:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
    1e4c:	e59f6350 	ldr	r6, [pc, #848]	; 21a4 <opfunc_func_on+0x420>
    1e50:	e7963105 	ldr	r3, [r6, r5, lsl #2]
    1e54:	e3530000 	cmp	r3, #0
    1e58:	0a00005d 	beq	1fd4 <opfunc_func_on+0x250>
    1e5c:	e593a000 	ldr	sl, [r3]
    1e60:	e35a0000 	cmp	sl, #0
    1e64:	0a00005a 	beq	1fd4 <opfunc_func_on+0x250>
    1e68:	e3550003 	cmp	r5, #3
    1e6c:	0a000045 	beq	1f88 <opfunc_func_on+0x204>
    1e70:	e5946050 	ldr	r6, [r4, #80]	; 0x50
    1e74:	ebfffffe 	bl	0 <wmt_conf_get_cfg>
    1e78:	e59f8310 	ldr	r8, [pc, #784]	; 2190 <opfunc_func_on+0x40c>
    1e7c:	e1a01000 	mov	r1, r0
    1e80:	e1a00006 	mov	r0, r6
    1e84:	e12fff3a 	blx	sl
    1e88:	e2506000 	subs	r6, r0, #0
    1e8c:	03a03002 	moveq	r3, #2
    1e90:	07883105 	streq	r3, [r8, r5, lsl #2]
    1e94:	0affffd2 	beq	1de4 <opfunc_func_on+0x60>
    1e98:	e3550003 	cmp	r5, #3
    1e9c:	0a00007f 	beq	20a0 <opfunc_func_on+0x31c>
    1ea0:	e3a03000 	mov	r3, #0
    1ea4:	e7843105 	str	r3, [r4, r5, lsl #2]
    1ea8:	e59f12f8 	ldr	r1, [pc, #760]	; 21a8 <opfunc_func_on+0x424>
    1eac:	e30024e3 	movw	r2, #1251	; 0x4e3
    1eb0:	e1a03005 	mov	r3, r5
    1eb4:	e59f02f0 	ldr	r0, [pc, #752]	; 21ac <opfunc_func_on+0x428>
    1eb8:	e58d6000 	str	r6, [sp]
    1ebc:	ebfffffe 	bl	0 <osal_err_print>
    1ec0:	e30024e4 	movw	r2, #1252	; 0x4e4
    1ec4:	e59f32e4 	ldr	r3, [pc, #740]	; 21b0 <opfunc_func_on+0x42c>
    1ec8:	e59f02e4 	ldr	r0, [pc, #740]	; 21b4 <opfunc_func_on+0x430>
    1ecc:	e59f12e4 	ldr	r1, [pc, #740]	; 21b8 <opfunc_func_on+0x434>
    1ed0:	ebfffffe 	bl	0 <osal_err_print>
    1ed4:	e5942000 	ldr	r2, [r4]
    1ed8:	e59f32b0 	ldr	r3, [pc, #688]	; 2190 <opfunc_func_on+0x40c>
    1edc:	e3520000 	cmp	r2, #0
    1ee0:	1affffd6 	bne	1e40 <opfunc_func_on+0xbc>
    1ee4:	e5932008 	ldr	r2, [r3, #8]
    1ee8:	e3520000 	cmp	r2, #0
    1eec:	1affffd3 	bne	1e40 <opfunc_func_on+0xbc>
    1ef0:	e5932004 	ldr	r2, [r3, #4]
    1ef4:	e3520000 	cmp	r2, #0
    1ef8:	1affffd0 	bne	1e40 <opfunc_func_on+0xbc>
    1efc:	e593200c 	ldr	r2, [r3, #12]
    1f00:	e3520000 	cmp	r2, #0
    1f04:	1affffcd 	bne	1e40 <opfunc_func_on+0xbc>
    1f08:	e5933020 	ldr	r3, [r3, #32]
    1f0c:	e3530000 	cmp	r3, #0
    1f10:	1affffca 	bne	1e40 <opfunc_func_on+0xbc>
    1f14:	e59f3278 	ldr	r3, [pc, #632]	; 2194 <opfunc_func_on+0x410>
    1f18:	e5933000 	ldr	r3, [r3]
    1f1c:	e3530001 	cmp	r3, #1
    1f20:	9a000003 	bls	1f34 <opfunc_func_on+0x1b0>
    1f24:	e59f0290 	ldr	r0, [pc, #656]	; 21bc <opfunc_func_on+0x438>
    1f28:	e1a02005 	mov	r2, r5
    1f2c:	e59f1274 	ldr	r1, [pc, #628]	; 21a8 <opfunc_func_on+0x424>
    1f30:	ebfffffe 	bl	0 <osal_info_print>
    1f34:	e1a00007 	mov	r0, r7
    1f38:	ebfffb4b 	bl	c6c <opfunc_pwr_off>
    1f3c:	e2503000 	subs	r3, r0, #0
    1f40:	0affffbe 	beq	1e40 <opfunc_func_on+0xbc>
    1f44:	e59f125c 	ldr	r1, [pc, #604]	; 21a8 <opfunc_func_on+0x424>
    1f48:	e3a02e4f 	mov	r2, #1264	; 0x4f0
    1f4c:	e59f026c 	ldr	r0, [pc, #620]	; 21c0 <opfunc_func_on+0x43c>
    1f50:	e58d5000 	str	r5, [sp]
    1f54:	ebfffffe 	bl	0 <osal_err_print>
    1f58:	e59f1258 	ldr	r1, [pc, #600]	; 21b8 <opfunc_func_on+0x434>
    1f5c:	e30024f1 	movw	r2, #1265	; 0x4f1
    1f60:	e59f3248 	ldr	r3, [pc, #584]	; 21b0 <opfunc_func_on+0x42c>
    1f64:	e59f0248 	ldr	r0, [pc, #584]	; 21b4 <opfunc_func_on+0x430>
    1f68:	ebfffffe 	bl	0 <osal_err_print>
    1f6c:	eaffffb3 	b	1e40 <opfunc_func_on+0xbc>
    1f70:	e59f321c 	ldr	r3, [pc, #540]	; 2194 <opfunc_func_on+0x410>
    1f74:	e5933000 	ldr	r3, [r3]
    1f78:	e3530000 	cmp	r3, #0
    1f7c:	1a00000e 	bne	1fbc <opfunc_func_on+0x238>
    1f80:	e3a06000 	mov	r6, #0
    1f84:	eaffffad 	b	1e40 <opfunc_func_on+0xbc>
    1f88:	e5943028 	ldr	r3, [r4, #40]	; 0x28
    1f8c:	e59f81fc 	ldr	r8, [pc, #508]	; 2190 <opfunc_func_on+0x40c>
    1f90:	e3530000 	cmp	r3, #0
    1f94:	0a000033 	beq	2068 <opfunc_func_on+0x2e4>
    1f98:	e3530001 	cmp	r3, #1
    1f9c:	0a000017 	beq	2000 <opfunc_func_on+0x27c>
    1fa0:	e59f021c 	ldr	r0, [pc, #540]	; 21c4 <opfunc_func_on+0x440>
    1fa4:	e30024bc 	movw	r2, #1212	; 0x4bc
    1fa8:	e59f11f8 	ldr	r1, [pc, #504]	; 21a8 <opfunc_func_on+0x424>
    1fac:	ebfffffe 	bl	0 <osal_err_print>
    1fb0:	e596300c 	ldr	r3, [r6, #12]
    1fb4:	e593a000 	ldr	sl, [r3]
    1fb8:	eaffffac 	b	1e70 <opfunc_func_on+0xec>
    1fbc:	e1a02005 	mov	r2, r5
    1fc0:	e59f11e0 	ldr	r1, [pc, #480]	; 21a8 <opfunc_func_on+0x424>
    1fc4:	e59f01fc 	ldr	r0, [pc, #508]	; 21c8 <opfunc_func_on+0x444>
    1fc8:	e3a06000 	mov	r6, #0
    1fcc:	ebfffffe 	bl	0 <osal_warn_print>
    1fd0:	eaffff9a 	b	1e40 <opfunc_func_on+0xbc>
    1fd4:	e59f31b8 	ldr	r3, [pc, #440]	; 2194 <opfunc_func_on+0x410>
    1fd8:	e5933000 	ldr	r3, [r3]
    1fdc:	e3530000 	cmp	r3, #0
    1fe0:	03e06004 	mvneq	r6, #4
    1fe4:	0affffaf 	beq	1ea8 <opfunc_func_on+0x124>
    1fe8:	e1a02005 	mov	r2, r5
    1fec:	e59f11b4 	ldr	r1, [pc, #436]	; 21a8 <opfunc_func_on+0x424>
    1ff0:	e59f01d4 	ldr	r0, [pc, #468]	; 21cc <opfunc_func_on+0x448>
    1ff4:	e3e06004 	mvn	r6, #4
    1ff8:	ebfffffe 	bl	0 <osal_warn_print>
    1ffc:	eaffffa9 	b	1ea8 <opfunc_func_on+0x124>
    2000:	e598301c 	ldr	r3, [r8, #28]
    2004:	e3530002 	cmp	r3, #2
    2008:	1a000055 	bne	2164 <opfunc_func_on+0x3e0>
    200c:	e59f3180 	ldr	r3, [pc, #384]	; 2194 <opfunc_func_on+0x410>
    2010:	e5933000 	ldr	r3, [r3]
    2014:	e3530002 	cmp	r3, #2
    2018:	9affff94 	bls	1e70 <opfunc_func_on+0xec>
    201c:	e59f01ac 	ldr	r0, [pc, #428]	; 21d0 <opfunc_func_on+0x44c>
    2020:	e59f1180 	ldr	r1, [pc, #384]	; 21a8 <opfunc_func_on+0x424>
    2024:	ebfffffe 	bl	0 <osal_dbg_print>
    2028:	e596300c 	ldr	r3, [r6, #12]
    202c:	e593a000 	ldr	sl, [r3]
    2030:	eaffff8e 	b	1e70 <opfunc_func_on+0xec>
    2034:	e1a03005 	mov	r3, r5
    2038:	e59f1168 	ldr	r1, [pc, #360]	; 21a8 <opfunc_func_on+0x424>
    203c:	e3002492 	movw	r2, #1170	; 0x492
    2040:	e59f018c 	ldr	r0, [pc, #396]	; 21d4 <opfunc_func_on+0x450>
    2044:	e58dc000 	str	ip, [sp]
    2048:	ebfffffe 	bl	0 <osal_err_print>
    204c:	e3002493 	movw	r2, #1171	; 0x493
    2050:	e59f1160 	ldr	r1, [pc, #352]	; 21b8 <opfunc_func_on+0x434>
    2054:	e59f3154 	ldr	r3, [pc, #340]	; 21b0 <opfunc_func_on+0x42c>
    2058:	e3e06002 	mvn	r6, #2
    205c:	e59f0150 	ldr	r0, [pc, #336]	; 21b4 <opfunc_func_on+0x430>
    2060:	ebfffffe 	bl	0 <osal_err_print>
    2064:	eaffff75 	b	1e40 <opfunc_func_on+0xbc>
    2068:	e3a0000a 	mov	r0, #10
    206c:	e24b1030 	sub	r1, fp, #48	; 0x30
    2070:	e24b2034 	sub	r2, fp, #52	; 0x34
    2074:	e3a03001 	mov	r3, #1
    2078:	e50b3034 	str	r3, [fp, #-52]	; 0xffffffcc
    207c:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
    2080:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    2084:	e2503000 	subs	r3, r0, #0
    2088:	1a000029 	bne	2134 <opfunc_func_on+0x3b0>
    208c:	e596300c 	ldr	r3, [r6, #12]
    2090:	e3a02002 	mov	r2, #2
    2094:	e5882018 	str	r2, [r8, #24]
    2098:	e593a000 	ldr	sl, [r3]
    209c:	eaffff73 	b	1e70 <opfunc_func_on+0xec>
    20a0:	e598a028 	ldr	sl, [r8, #40]	; 0x28
    20a4:	e35a0000 	cmp	sl, #0
    20a8:	1affff7c 	bne	1ea0 <opfunc_func_on+0x11c>
    20ac:	e3a0000a 	mov	r0, #10
    20b0:	e24b1030 	sub	r1, fp, #48	; 0x30
    20b4:	e24b2034 	sub	r2, fp, #52	; 0x34
    20b8:	e3a03001 	mov	r3, #1
    20bc:	e50ba034 	str	sl, [fp, #-52]	; 0xffffffcc
    20c0:	e50b3030 	str	r3, [fp, #-48]	; 0xffffffd0
    20c4:	ebfffffe 	bl	3f0 <wmt_core_ctrl>
    20c8:	e588a018 	str	sl, [r8, #24]
    20cc:	eaffff73 	b	1ea0 <opfunc_func_on+0x11c>
    20d0:	e1a03005 	mov	r3, r5
    20d4:	e59f10cc 	ldr	r1, [pc, #204]	; 21a8 <opfunc_func_on+0x424>
    20d8:	e3002478 	movw	r2, #1144	; 0x478
    20dc:	e59f00f4 	ldr	r0, [pc, #244]	; 21d8 <opfunc_func_on+0x454>
    20e0:	ebfffffe 	bl	0 <osal_err_print>
    20e4:	e59f10cc 	ldr	r1, [pc, #204]	; 21b8 <opfunc_func_on+0x434>
    20e8:	e3002479 	movw	r2, #1145	; 0x479
    20ec:	e59f30bc 	ldr	r3, [pc, #188]	; 21b0 <opfunc_func_on+0x42c>
    20f0:	e59f00bc 	ldr	r0, [pc, #188]	; 21b4 <opfunc_func_on+0x430>
    20f4:	e3e06000 	mvn	r6, #0
    20f8:	ebfffffe 	bl	0 <osal_err_print>
    20fc:	eaffff4f 	b	1e40 <opfunc_func_on+0xbc>
    2100:	e1a03005 	mov	r3, r5
    2104:	e59f109c 	ldr	r1, [pc, #156]	; 21a8 <opfunc_func_on+0x424>
    2108:	e3002482 	movw	r2, #1154	; 0x482
    210c:	e59f00c8 	ldr	r0, [pc, #200]	; 21dc <opfunc_func_on+0x458>
    2110:	e58dc000 	str	ip, [sp]
    2114:	ebfffffe 	bl	0 <osal_err_print>
    2118:	e3002483 	movw	r2, #1155	; 0x483
    211c:	e59f1094 	ldr	r1, [pc, #148]	; 21b8 <opfunc_func_on+0x434>
    2120:	e59f3088 	ldr	r3, [pc, #136]	; 21b0 <opfunc_func_on+0x42c>
    2124:	e3e06001 	mvn	r6, #1
    2128:	e59f0084 	ldr	r0, [pc, #132]	; 21b4 <opfunc_func_on+0x430>
    212c:	ebfffffe 	bl	0 <osal_err_print>
    2130:	eaffff42 	b	1e40 <opfunc_func_on+0xbc>
    2134:	e59f106c 	ldr	r1, [pc, #108]	; 21a8 <opfunc_func_on+0x424>
    2138:	e30024a5 	movw	r2, #1189	; 0x4a5
    213c:	e59f009c 	ldr	r0, [pc, #156]	; 21e0 <opfunc_func_on+0x45c>
    2140:	ebfffffe 	bl	0 <osal_err_print>
    2144:	e59f3064 	ldr	r3, [pc, #100]	; 21b0 <opfunc_func_on+0x42c>
    2148:	e59f0064 	ldr	r0, [pc, #100]	; 21b4 <opfunc_func_on+0x430>
    214c:	e30024a6 	movw	r2, #1190	; 0x4a6
    2150:	e59f1060 	ldr	r1, [pc, #96]	; 21b8 <opfunc_func_on+0x434>
    2154:	ebfffffe 	bl	0 <osal_err_print>
    2158:	e596300c 	ldr	r3, [r6, #12]
    215c:	e593a000 	ldr	sl, [r3]
    2160:	eaffff42 	b	1e70 <opfunc_func_on+0xec>
    2164:	e59f103c 	ldr	r1, [pc, #60]	; 21a8 <opfunc_func_on+0x424>
    2168:	e30024b6 	movw	r2, #1206	; 0x4b6
    216c:	e59f0070 	ldr	r0, [pc, #112]	; 21e4 <opfunc_func_on+0x460>
    2170:	e3e06003 	mvn	r6, #3
    2174:	ebfffffe 	bl	0 <osal_err_print>
    2178:	e59f1038 	ldr	r1, [pc, #56]	; 21b8 <opfunc_func_on+0x434>
    217c:	e30024b7 	movw	r2, #1207	; 0x4b7
    2180:	e59f3028 	ldr	r3, [pc, #40]	; 21b0 <opfunc_func_on+0x42c>
    2184:	e59f0028 	ldr	r0, [pc, #40]	; 21b4 <opfunc_func_on+0x430>
    2188:	ebfffffe 	bl	0 <osal_err_print>
    218c:	eaffff2b 	b	1e40 <opfunc_func_on+0xbc>
	...
    2198:	000002b0 			; <UNDEFINED> instruction: 0x000002b0
    219c:	000000d4 	ldrdeq	r0, [r0], -r4
    21a0:	00001330 	andeq	r1, r0, r0, lsr r3
    21a4:	00000000 	andeq	r0, r0, r0
    21a8:	000001d8 	ldrdeq	r0, [r0], -r8
    21ac:	000008b4 			; <UNDEFINED> instruction: 0x000008b4
    21b0:	000002ac 	andeq	r0, r0, ip, lsr #5
    21b4:	0000026c 	andeq	r0, r0, ip, ror #4
    21b8:	0000027c 	andeq	r0, r0, ip, ror r2
    21bc:	000008dc 	ldrdeq	r0, [r0], -ip
    21c0:	00000914 	andeq	r0, r0, r4, lsl r9
    21c4:	000012d4 	ldrdeq	r1, [r0], -r4
    21c8:	0000120c 	andeq	r1, r0, ip, lsl #4
    21cc:	00000888 	andeq	r0, r0, r8, lsl #17
    21d0:	0000125c 	andeq	r1, r0, ip, asr r2
    21d4:	00001230 	andeq	r1, r0, r0, lsr r2
    21d8:	000011b4 			; <UNDEFINED> instruction: 0x000011b4
    21dc:	000011d8 	ldrdeq	r1, [r0], -r8
    21e0:	00000858 	andeq	r0, r0, r8, asr r8
    21e4:	00001284 	andeq	r1, r0, r4, lsl #5

000021e8 <opfunc_reg_rw>:
    21e8:	e1a0c00d 	mov	ip, sp
    21ec:	e92dd800 	push	{fp, ip, lr, pc}
    21f0:	e24cb004 	sub	fp, ip, #4
    21f4:	e59f303c 	ldr	r3, [pc, #60]	; 2238 <opfunc_reg_rw+0x50>
    21f8:	e1a02000 	mov	r2, r0
    21fc:	e5933010 	ldr	r3, [r3, #16]
    2200:	e3530002 	cmp	r3, #2
    2204:	1a000005 	bne	2220 <opfunc_reg_rw+0x38>
    2208:	e5903014 	ldr	r3, [r0, #20]
    220c:	e592100c 	ldr	r1, [r2, #12]
    2210:	e5900008 	ldr	r0, [r0, #8]
    2214:	e5922010 	ldr	r2, [r2, #16]
    2218:	ebfffffe 	bl	131c <wmt_core_reg_rw_raw>
    221c:	e89da800 	ldm	sp, {fp, sp, pc}
    2220:	e59f0014 	ldr	r0, [pc, #20]	; 223c <opfunc_reg_rw+0x54>
    2224:	e3a02e56 	mov	r2, #1376	; 0x560
    2228:	e59f1010 	ldr	r1, [pc, #16]	; 2240 <opfunc_reg_rw+0x58>
    222c:	ebfffffe 	bl	0 <osal_err_print>
    2230:	e3e00000 	mvn	r0, #0
    2234:	e89da800 	ldm	sp, {fp, sp, pc}
    2238:	00000000 	andeq	r0, r0, r0
    223c:	0000133c 	andeq	r1, r0, ip, lsr r3
    2240:	000001e8 	andeq	r0, r0, r8, ror #3

00002244 <opfunc_efuse_rw>:
    2244:	e1a0c00d 	mov	ip, sp
    2248:	e92dd9f0 	push	{r4, r5, r6, r7, r8, fp, ip, lr, pc}
    224c:	e24cb004 	sub	fp, ip, #4
    2250:	e24dd024 	sub	sp, sp, #36	; 0x24
    2254:	e59f213c 	ldr	r2, [pc, #316]	; 2398 <opfunc_efuse_rw+0x154>
    2258:	e24b5038 	sub	r5, fp, #56	; 0x38
    225c:	e2853004 	add	r3, r5, #4
    2260:	e3a04000 	mov	r4, #0
    2264:	e1a08000 	mov	r8, r0
    2268:	e50b4038 	str	r4, [fp, #-56]	; 0xffffffc8
    226c:	e5922010 	ldr	r2, [r2, #16]
    2270:	e4834004 	str	r4, [r3], #4
    2274:	e3520002 	cmp	r2, #2
    2278:	e4834004 	str	r4, [r3], #4
    227c:	e5834000 	str	r4, [r3]
    2280:	1a00003e 	bne	2380 <opfunc_efuse_rw+0x13c>
    2284:	e5903008 	ldr	r3, [r0, #8]
    2288:	e280100c 	add	r1, r0, #12
    228c:	e59f7108 	ldr	r7, [pc, #264]	; 239c <opfunc_efuse_rw+0x158>
    2290:	e24b6028 	sub	r6, fp, #40	; 0x28
    2294:	e3530000 	cmp	r3, #0
    2298:	e287002a 	add	r0, r7, #42	; 0x2a
    229c:	13a03001 	movne	r3, #1
    22a0:	03a03002 	moveq	r3, #2
    22a4:	e5c73028 	strb	r3, [r7, #40]	; 0x28
    22a8:	ebfffffe 	bl	0 <osal_memcpy>
    22ac:	e5981010 	ldr	r1, [r8, #16]
    22b0:	e3a02004 	mov	r2, #4
    22b4:	e287002c 	add	r0, r7, #44	; 0x2c
    22b8:	ebfffffe 	bl	0 <osal_memcpy>
    22bc:	e2870024 	add	r0, r7, #36	; 0x24
    22c0:	e59f10d8 	ldr	r1, [pc, #216]	; 23a0 <opfunc_efuse_rw+0x15c>
    22c4:	e3a0200c 	mov	r2, #12
    22c8:	ebfffffe 	bl	17c <wmt_core_dump_data>
    22cc:	e1a03004 	mov	r3, r4
    22d0:	e2870024 	add	r0, r7, #36	; 0x24
    22d4:	e3a0100c 	mov	r1, #12
    22d8:	e1a02006 	mov	r2, r6
    22dc:	ebfffffe 	bl	10e4 <wmt_core_tx>
    22e0:	e2504000 	subs	r4, r0, #0
    22e4:	151bc028 	ldrne	ip, [fp, #-40]	; 0xffffffd8
    22e8:	1a000002 	bne	22f8 <opfunc_efuse_rw+0xb4>
    22ec:	e51bc028 	ldr	ip, [fp, #-40]	; 0xffffffd8
    22f0:	e35c000c 	cmp	ip, #12
    22f4:	0a00000a 	beq	2324 <opfunc_efuse_rw+0xe0>
    22f8:	e59f10a4 	ldr	r1, [pc, #164]	; 23a4 <opfunc_efuse_rw+0x160>
    22fc:	e30027d8 	movw	r2, #2008	; 0x7d8
    2300:	e1a03004 	mov	r3, r4
    2304:	e59f009c 	ldr	r0, [pc, #156]	; 23a8 <opfunc_efuse_rw+0x164>
    2308:	e58dc000 	str	ip, [sp]
    230c:	e3a0c00c 	mov	ip, #12
    2310:	e58dc004 	str	ip, [sp, #4]
    2314:	ebfffffe 	bl	0 <osal_err_print>
    2318:	e1a00004 	mov	r0, r4
    231c:	e24bd020 	sub	sp, fp, #32
    2320:	e89da9f0 	ldm	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
    2324:	e1a0100c 	mov	r1, ip
    2328:	e1a02006 	mov	r2, r6
    232c:	e1a00005 	mov	r0, r5
    2330:	ebfffffe 	bl	8b4 <wmt_core_rx>
    2334:	e2504000 	subs	r4, r0, #0
    2338:	151bc028 	ldrne	ip, [fp, #-40]	; 0xffffffd8
    233c:	1a000002 	bne	234c <opfunc_efuse_rw+0x108>
    2340:	e51bc028 	ldr	ip, [fp, #-40]	; 0xffffffd8
    2344:	e35c000c 	cmp	ip, #12
    2348:	0a000007 	beq	236c <opfunc_efuse_rw+0x128>
    234c:	e59f0058 	ldr	r0, [pc, #88]	; 23ac <opfunc_efuse_rw+0x168>
    2350:	e3a02e7e 	mov	r2, #2016	; 0x7e0
    2354:	e59f1048 	ldr	r1, [pc, #72]	; 23a4 <opfunc_efuse_rw+0x160>
    2358:	e1a03004 	mov	r3, r4
    235c:	e58dc000 	str	ip, [sp]
    2360:	e3a0c00c 	mov	ip, #12
    2364:	e58dc004 	str	ip, [sp, #4]
    2368:	ebfffffe 	bl	0 <osal_err_print>
    236c:	e1a00005 	mov	r0, r5
    2370:	e59f1038 	ldr	r1, [pc, #56]	; 23b0 <opfunc_efuse_rw+0x16c>
    2374:	e3a02010 	mov	r2, #16
    2378:	ebfffffe 	bl	17c <wmt_core_dump_data>
    237c:	eaffffe5 	b	2318 <opfunc_efuse_rw+0xd4>
    2380:	e30027ca 	movw	r2, #1994	; 0x7ca
    2384:	e59f1018 	ldr	r1, [pc, #24]	; 23a4 <opfunc_efuse_rw+0x160>
    2388:	e59f0024 	ldr	r0, [pc, #36]	; 23b4 <opfunc_efuse_rw+0x170>
    238c:	e3e04000 	mvn	r4, #0
    2390:	ebfffffe 	bl	0 <osal_err_print>
    2394:	eaffffdf 	b	2318 <opfunc_efuse_rw+0xd4>
	...
    23a0:	00001370 	andeq	r1, r0, r0, ror r3
    23a4:	000001f8 	strdeq	r0, [r0], -r8
    23a8:	0000137c 	andeq	r1, r0, ip, ror r3
    23ac:	000013b8 			; <UNDEFINED> instruction: 0x000013b8
    23b0:	000013f0 	strdeq	r1, [r0], -r0
    23b4:	00000104 	andeq	r0, r0, r4, lsl #2

000023b8 <opfunc_therm_ctrl>:
    23b8:	e1a0c00d 	mov	ip, sp
    23bc:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
    23c0:	e24cb004 	sub	fp, ip, #4
    23c4:	e24dd04c 	sub	sp, sp, #76	; 0x4c
    23c8:	e59f525c 	ldr	r5, [pc, #604]	; 262c <opfunc_therm_ctrl+0x274>
    23cc:	e24b8040 	sub	r8, fp, #64	; 0x40
    23d0:	e5904008 	ldr	r4, [r0, #8]
    23d4:	e288c004 	add	ip, r8, #4
    23d8:	e3a0e000 	mov	lr, #0
    23dc:	e24ba030 	sub	sl, fp, #48	; 0x30
    23e0:	e48ce004 	str	lr, [ip], #4
    23e4:	e1a06000 	mov	r6, r0
    23e8:	e5c54034 	strb	r4, [r5, #52]	; 0x34
    23ec:	e1a0300e 	mov	r3, lr
    23f0:	e48ce004 	str	lr, [ip], #4
    23f4:	e2850030 	add	r0, r5, #48	; 0x30
    23f8:	e3a01005 	mov	r1, #5
    23fc:	e1a0200a 	mov	r2, sl
    2400:	e58ce000 	str	lr, [ip]
    2404:	e50be040 	str	lr, [fp, #-64]	; 0xffffffc0
    2408:	ebfffffe 	bl	10e4 <wmt_core_tx>
    240c:	e2504000 	subs	r4, r0, #0
    2410:	151b7030 	ldrne	r7, [fp, #-48]	; 0xffffffd0
    2414:	1a000002 	bne	2424 <opfunc_therm_ctrl+0x6c>
    2418:	e51b7030 	ldr	r7, [fp, #-48]	; 0xffffffd0
    241c:	e3570005 	cmp	r7, #5
    2420:	0a000009 	beq	244c <opfunc_therm_ctrl+0x94>
    2424:	e59f1204 	ldr	r1, [pc, #516]	; 2630 <opfunc_therm_ctrl+0x278>
    2428:	e3002793 	movw	r2, #1939	; 0x793
    242c:	e1a03004 	mov	r3, r4
    2430:	e59f01fc 	ldr	r0, [pc, #508]	; 2634 <opfunc_therm_ctrl+0x27c>
    2434:	e3a0c005 	mov	ip, #5
    2438:	e88d1080 	stm	sp, {r7, ip}
    243c:	ebfffffe 	bl	0 <osal_err_print>
    2440:	e1a00004 	mov	r0, r4
    2444:	e24bd028 	sub	sp, fp, #40	; 0x28
    2448:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
    244c:	e1a0200a 	mov	r2, sl
    2450:	e1a00008 	mov	r0, r8
    2454:	e3a01010 	mov	r1, #16
    2458:	ebfffffe 	bl	8b4 <wmt_core_rx>
    245c:	e2504000 	subs	r4, r0, #0
    2460:	151ba030 	ldrne	sl, [fp, #-48]	; 0xffffffd0
    2464:	1a000003 	bne	2478 <opfunc_therm_ctrl+0xc0>
    2468:	e51ba030 	ldr	sl, [fp, #-48]	; 0xffffffd0
    246c:	e24a3005 	sub	r3, sl, #5
    2470:	e3530001 	cmp	r3, #1
    2474:	9a000008 	bls	249c <opfunc_therm_ctrl+0xe4>
    2478:	e59f11b0 	ldr	r1, [pc, #432]	; 2630 <opfunc_therm_ctrl+0x278>
    247c:	e300279b 	movw	r2, #1947	; 0x79b
    2480:	e1a03004 	mov	r3, r4
    2484:	e59f01ac 	ldr	r0, [pc, #428]	; 2638 <opfunc_therm_ctrl+0x280>
    2488:	e3a0c010 	mov	ip, #16
    248c:	e88d1400 	stm	sp, {sl, ip}
    2490:	ebfffffe 	bl	0 <osal_err_print>
    2494:	ebfffffe 	bl	0 <mtk_wcn_stp_dbg_dump_package>
    2498:	eaffffe8 	b	2440 <opfunc_therm_ctrl+0x88>
    249c:	e35a0005 	cmp	sl, #5
    24a0:	0a00000f 	beq	24e4 <opfunc_therm_ctrl+0x12c>
    24a4:	e1a00008 	mov	r0, r8
    24a8:	e1a02007 	mov	r2, r7
    24ac:	e2851040 	add	r1, r5, #64	; 0x40
    24b0:	ebfffffe 	bl	0 <osal_memcmp>
    24b4:	e3500000 	cmp	r0, #0
    24b8:	1a000019 	bne	2524 <opfunc_therm_ctrl+0x16c>
    24bc:	e59f3178 	ldr	r3, [pc, #376]	; 263c <opfunc_therm_ctrl+0x284>
    24c0:	e5933000 	ldr	r3, [r3]
    24c4:	e3530001 	cmp	r3, #1
    24c8:	9a000002 	bls	24d8 <opfunc_therm_ctrl+0x120>
    24cc:	e59f016c 	ldr	r0, [pc, #364]	; 2640 <opfunc_therm_ctrl+0x288>
    24d0:	e59f1158 	ldr	r1, [pc, #344]	; 2630 <opfunc_therm_ctrl+0x278>
    24d4:	ebfffffe 	bl	0 <osal_info_print>
    24d8:	e55b303b 	ldrb	r3, [fp, #-59]	; 0xffffffc5
    24dc:	e586300c 	str	r3, [r6, #12]
    24e0:	eaffffd6 	b	2440 <opfunc_therm_ctrl+0x88>
    24e4:	e1a00008 	mov	r0, r8
    24e8:	e2851038 	add	r1, r5, #56	; 0x38
    24ec:	e1a0200a 	mov	r2, sl
    24f0:	ebfffffe 	bl	0 <osal_memcmp>
    24f4:	e3500000 	cmp	r0, #0
    24f8:	1a00002c 	bne	25b0 <opfunc_therm_ctrl+0x1f8>
    24fc:	e59f3138 	ldr	r3, [pc, #312]	; 263c <opfunc_therm_ctrl+0x284>
    2500:	e5933000 	ldr	r3, [r3]
    2504:	e3530001 	cmp	r3, #1
    2508:	9a000002 	bls	2518 <opfunc_therm_ctrl+0x160>
    250c:	e59f0130 	ldr	r0, [pc, #304]	; 2644 <opfunc_therm_ctrl+0x28c>
    2510:	e59f1118 	ldr	r1, [pc, #280]	; 2630 <opfunc_therm_ctrl+0x278>
    2514:	ebfffffe 	bl	0 <osal_info_print>
    2518:	e3a03001 	mov	r3, #1
    251c:	e586300c 	str	r3, [r6, #12]
    2520:	eaffffc6 	b	2440 <opfunc_therm_ctrl+0x88>
    2524:	e59f1104 	ldr	r1, [pc, #260]	; 2630 <opfunc_therm_ctrl+0x278>
    2528:	e30027b1 	movw	r2, #1969	; 0x7b1
    252c:	e59f0114 	ldr	r0, [pc, #276]	; 2648 <opfunc_therm_ctrl+0x290>
    2530:	ebfffffe 	bl	0 <osal_err_print>
    2534:	e5d53043 	ldrb	r3, [r5, #67]	; 0x43
    2538:	e55bc03f 	ldrb	ip, [fp, #-63]	; 0xffffffc1
    253c:	e30027b4 	movw	r2, #1972	; 0x7b4
    2540:	e55be040 	ldrb	lr, [fp, #-64]	; 0xffffffc0
    2544:	e58d3028 	str	r3, [sp, #40]	; 0x28
    2548:	e5d51040 	ldrb	r1, [r5, #64]	; 0x40
    254c:	e55b703e 	ldrb	r7, [fp, #-62]	; 0xffffffc2
    2550:	e55b803d 	ldrb	r8, [fp, #-61]	; 0xffffffc3
    2554:	e58d101c 	str	r1, [sp, #28]
    2558:	e5d51041 	ldrb	r1, [r5, #65]	; 0x41
    255c:	e55ba03c 	ldrb	sl, [fp, #-60]	; 0xffffffc4
    2560:	e55b903b 	ldrb	r9, [fp, #-59]	; 0xffffffc5
    2564:	e58d1020 	str	r1, [sp, #32]
    2568:	e5d55042 	ldrb	r5, [r5, #66]	; 0x42
    256c:	e51b3030 	ldr	r3, [fp, #-48]	; 0xffffffd0
    2570:	e59f10b8 	ldr	r1, [pc, #184]	; 2630 <opfunc_therm_ctrl+0x278>
    2574:	e59f00d0 	ldr	r0, [pc, #208]	; 264c <opfunc_therm_ctrl+0x294>
    2578:	e58dc004 	str	ip, [sp, #4]
    257c:	e3a0c006 	mov	ip, #6
    2580:	e58de000 	str	lr, [sp]
    2584:	e58d7008 	str	r7, [sp, #8]
    2588:	e58d800c 	str	r8, [sp, #12]
    258c:	e58da010 	str	sl, [sp, #16]
    2590:	e58d9014 	str	r9, [sp, #20]
    2594:	e58dc018 	str	ip, [sp, #24]
    2598:	e58d5024 	str	r5, [sp, #36]	; 0x24
    259c:	ebfffffe 	bl	0 <osal_err_print>
    25a0:	e3a030ff 	mov	r3, #255	; 0xff
    25a4:	e586300c 	str	r3, [r6, #12]
    25a8:	ebfffffe 	bl	0 <mtk_wcn_stp_dbg_dump_package>
    25ac:	eaffffa3 	b	2440 <opfunc_therm_ctrl+0x88>
    25b0:	e59f1078 	ldr	r1, [pc, #120]	; 2630 <opfunc_therm_ctrl+0x278>
    25b4:	e30027a2 	movw	r2, #1954	; 0x7a2
    25b8:	e59f0090 	ldr	r0, [pc, #144]	; 2650 <opfunc_therm_ctrl+0x298>
    25bc:	ebfffffe 	bl	0 <osal_err_print>
    25c0:	e5d5103c 	ldrb	r1, [r5, #60]	; 0x3c
    25c4:	e55bc040 	ldrb	ip, [fp, #-64]	; 0xffffffc0
    25c8:	e30027a5 	movw	r2, #1957	; 0x7a5
    25cc:	e55b703f 	ldrb	r7, [fp, #-63]	; 0xffffffc1
    25d0:	e58d1028 	str	r1, [sp, #40]	; 0x28
    25d4:	e55b103c 	ldrb	r1, [fp, #-60]	; 0xffffffc4
    25d8:	e55b803e 	ldrb	r8, [fp, #-62]	; 0xffffffc2
    25dc:	e55b903d 	ldrb	r9, [fp, #-61]	; 0xffffffc3
    25e0:	e58d1010 	str	r1, [sp, #16]
    25e4:	e5d51038 	ldrb	r1, [r5, #56]	; 0x38
    25e8:	e51b3030 	ldr	r3, [fp, #-48]	; 0xffffffd0
    25ec:	e59f0060 	ldr	r0, [pc, #96]	; 2654 <opfunc_therm_ctrl+0x29c>
    25f0:	e58d1018 	str	r1, [sp, #24]
    25f4:	e5d51039 	ldrb	r1, [r5, #57]	; 0x39
    25f8:	e58d101c 	str	r1, [sp, #28]
    25fc:	e5d5103a 	ldrb	r1, [r5, #58]	; 0x3a
    2600:	e58d1020 	str	r1, [sp, #32]
    2604:	e5d5e03b 	ldrb	lr, [r5, #59]	; 0x3b
    2608:	e59f1020 	ldr	r1, [pc, #32]	; 2630 <opfunc_therm_ctrl+0x278>
    260c:	e58dc000 	str	ip, [sp]
    2610:	e98d0380 	stmib	sp, {r7, r8, r9}
    2614:	e58da014 	str	sl, [sp, #20]
    2618:	e58de024 	str	lr, [sp, #36]	; 0x24
    261c:	ebfffffe 	bl	0 <osal_err_print>
    2620:	e586400c 	str	r4, [r6, #12]
    2624:	ebfffffe 	bl	0 <mtk_wcn_stp_dbg_dump_package>
    2628:	eaffff84 	b	2440 <opfunc_therm_ctrl+0x88>
    262c:	00000000 	andeq	r0, r0, r0
    2630:	00000208 	andeq	r0, r0, r8, lsl #4
    2634:	000013fc 	strdeq	r1, [r0], -ip
    2638:	0000143c 	andeq	r1, r0, ip, lsr r4
    263c:	00000000 	andeq	r0, r0, r0
    2640:	0000157c 	andeq	r1, r0, ip, ror r5
    2644:	000014bc 			; <UNDEFINED> instruction: 0x000014bc
    2648:	000014f0 	strdeq	r1, [r0], -r0
    264c:	00001524 	andeq	r1, r0, r4, lsr #10
    2650:	00001488 	andeq	r1, r0, r8, lsl #9
    2654:	00000a30 	andeq	r0, r0, r0, lsr sl

00002658 <opfunc_cmd_test>:
    2658:	e1a0c00d 	mov	ip, sp
    265c:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
    2660:	e24cb004 	sub	fp, ip, #4
    2664:	e24ddf4f 	sub	sp, sp, #316	; 0x13c
    2668:	e59fc3f0 	ldr	ip, [pc, #1008]	; 2a60 <opfunc_cmd_test+0x408>
    266c:	e24ba038 	sub	sl, fp, #56	; 0x38
    2670:	e50b0148 	str	r0, [fp, #-328]	; 0xfffffeb8
    2674:	e24b9040 	sub	r9, fp, #64	; 0x40
    2678:	e28c3008 	add	r3, ip, #8
    267c:	e28c8010 	add	r8, ip, #16
    2680:	e89c0003 	ldm	ip, {r0, r1}
    2684:	e28c6018 	add	r6, ip, #24
    2688:	e28c4020 	add	r4, ip, #32
    268c:	e28c2028 	add	r2, ip, #40	; 0x28
    2690:	e28ce034 	add	lr, ip, #52	; 0x34
    2694:	e24b7070 	sub	r7, fp, #112	; 0x70
    2698:	e50b0038 	str	r0, [fp, #-56]	; 0xffffffc8
    269c:	e5ca1004 	strb	r1, [sl, #4]
    26a0:	e8930003 	ldm	r3, {r0, r1}
    26a4:	e24b3064 	sub	r3, fp, #100	; 0x64
    26a8:	e50b3158 	str	r3, [fp, #-344]	; 0xfffffea8
    26ac:	e24b3080 	sub	r3, fp, #128	; 0x80
    26b0:	e50b315c 	str	r3, [fp, #-348]	; 0xfffffea4
    26b4:	e50b0040 	str	r0, [fp, #-64]	; 0xffffffc0
    26b8:	e5c91004 	strb	r1, [r9, #4]
    26bc:	e8980003 	ldm	r8, {r0, r1}
    26c0:	e59f539c 	ldr	r5, [pc, #924]	; 2a64 <opfunc_cmd_test+0x40c>
    26c4:	e50b0048 	str	r0, [fp, #-72]	; 0xffffffb8
    26c8:	e54b1044 	strb	r1, [fp, #-68]	; 0xffffffbc
    26cc:	e8960003 	ldm	r6, {r0, r1}
    26d0:	e50b0050 	str	r0, [fp, #-80]	; 0xffffffb0
    26d4:	e54b104c 	strb	r1, [fp, #-76]	; 0xffffffb4
    26d8:	e8940003 	ldm	r4, {r0, r1}
    26dc:	e51b4158 	ldr	r4, [fp, #-344]	; 0xfffffea8
    26e0:	e50b0058 	str	r0, [fp, #-88]	; 0xffffffa8
    26e4:	e14b15b4 	strh	r1, [fp, #-84]	; 0xffffffac
    26e8:	e8920007 	ldm	r2, {r0, r1, r2}
    26ec:	e8a40003 	stmia	r4!, {r0, r1}
    26f0:	e5c42000 	strb	r2, [r4]
    26f4:	e89e0007 	ldm	lr, {r0, r1, r2}
    26f8:	e59f4368 	ldr	r4, [pc, #872]	; 2a68 <opfunc_cmd_test+0x410>
    26fc:	e1a0e822 	lsr	lr, r2, #16
    2700:	e5c7e00a 	strb	lr, [r7, #10]
    2704:	e1a0e007 	mov	lr, r7
    2708:	e8ae0003 	stmia	lr!, {r0, r1}
    270c:	e1ce20b0 	strh	r2, [lr]
    2710:	e894000f 	ldm	r4, {r0, r1, r2, r3}
    2714:	e51be15c 	ldr	lr, [fp, #-348]	; 0xfffffea4
    2718:	e8ae0007 	stmia	lr!, {r0, r1, r2}
    271c:	e1a0200e 	mov	r2, lr
    2720:	e595e000 	ldr	lr, [r5]
    2724:	e5c23000 	strb	r3, [r2]
    2728:	e51b2148 	ldr	r2, [fp, #-328]	; 0xfffffeb8
    272c:	e35e0001 	cmp	lr, #1
    2730:	e5924008 	ldr	r4, [r2, #8]
    2734:	9a000003 	bls	2748 <opfunc_cmd_test+0xf0>
    2738:	e28c1050 	add	r1, ip, #80	; 0x50
    273c:	e59f0328 	ldr	r0, [pc, #808]	; 2a6c <opfunc_cmd_test+0x414>
    2740:	e1a02004 	mov	r2, r4
    2744:	ebfffffe 	bl	0 <osal_info_print>
    2748:	e3540000 	cmp	r4, #0
    274c:	1a00002c 	bne	2804 <opfunc_cmd_test+0x1ac>
    2750:	e5953000 	ldr	r3, [r5]
    2754:	e3530001 	cmp	r3, #1
    2758:	9a000002 	bls	2768 <opfunc_cmd_test+0x110>
    275c:	e59f030c 	ldr	r0, [pc, #780]	; 2a70 <opfunc_cmd_test+0x418>
    2760:	e59f130c 	ldr	r1, [pc, #780]	; 2a74 <opfunc_cmd_test+0x41c>
    2764:	ebfffffe 	bl	0 <osal_info_print>
    2768:	e24b80c0 	sub	r8, fp, #192	; 0xc0
    276c:	e1a0100a 	mov	r1, sl
    2770:	e3a02005 	mov	r2, #5
    2774:	e1a00008 	mov	r0, r8
    2778:	ebfffffe 	bl	0 <osal_memcpy>
    277c:	e1a01009 	mov	r1, r9
    2780:	e3a02005 	mov	r2, #5
    2784:	e24b0c01 	sub	r0, fp, #256	; 0x100
    2788:	e1a09002 	mov	r9, r2
    278c:	e3a06000 	mov	r6, #0
    2790:	e1a07009 	mov	r7, r9
    2794:	ebfffffe 	bl	0 <osal_memcpy>
    2798:	e50b6150 	str	r6, [fp, #-336]	; 0xfffffeb0
    279c:	e50b614c 	str	r6, [fp, #-332]	; 0xfffffeb4
    27a0:	e24ba030 	sub	sl, fp, #48	; 0x30
    27a4:	e1a00008 	mov	r0, r8
    27a8:	e1a01007 	mov	r1, r7
    27ac:	e1a0200a 	mov	r2, sl
    27b0:	e3a03000 	mov	r3, #0
    27b4:	ebfffffe 	bl	10e4 <wmt_core_tx>
    27b8:	e2508000 	subs	r8, r0, #0
    27bc:	151bc030 	ldrne	ip, [fp, #-48]	; 0xffffffd0
    27c0:	1a000051 	bne	290c <opfunc_cmd_test+0x2b4>
    27c4:	e51bc030 	ldr	ip, [fp, #-48]	; 0xffffffd0
    27c8:	e15c0007 	cmp	ip, r7
    27cc:	1a00004e 	bne	290c <opfunc_cmd_test+0x2b4>
    27d0:	e3540001 	cmp	r4, #1
    27d4:	9a000015 	bls	2830 <opfunc_cmd_test+0x1d8>
    27d8:	e24b7d05 	sub	r7, fp, #320	; 0x140
    27dc:	e1a0200a 	mov	r2, sl
    27e0:	e1a00007 	mov	r0, r7
    27e4:	e1a01009 	mov	r1, r9
    27e8:	ebfffffe 	bl	8b4 <wmt_core_rx>
    27ec:	e3540002 	cmp	r4, #2
    27f0:	e1a08000 	mov	r8, r0
    27f4:	0a000021 	beq	2880 <opfunc_cmd_test+0x228>
    27f8:	e1a00008 	mov	r0, r8
    27fc:	e24bd028 	sub	sp, fp, #40	; 0x28
    2800:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
    2804:	e3540001 	cmp	r4, #1
    2808:	0a00000f 	beq	284c <opfunc_cmd_test+0x1f4>
    280c:	e3540002 	cmp	r4, #2
    2810:	0a000046 	beq	2930 <opfunc_cmd_test+0x2d8>
    2814:	e3a06000 	mov	r6, #0
    2818:	e24b80c0 	sub	r8, fp, #192	; 0xc0
    281c:	e50b6150 	str	r6, [fp, #-336]	; 0xfffffeb0
    2820:	e1a09006 	mov	r9, r6
    2824:	e1a07006 	mov	r7, r6
    2828:	e50b614c 	str	r6, [fp, #-332]	; 0xfffffeb4
    282c:	eaffffdb 	b	27a0 <opfunc_cmd_test+0x148>
    2830:	e5953000 	ldr	r3, [r5]
    2834:	e3530001 	cmp	r3, #1
    2838:	9affffee 	bls	27f8 <opfunc_cmd_test+0x1a0>
    283c:	e59f1230 	ldr	r1, [pc, #560]	; 2a74 <opfunc_cmd_test+0x41c>
    2840:	e59f0230 	ldr	r0, [pc, #560]	; 2a78 <opfunc_cmd_test+0x420>
    2844:	ebfffffe 	bl	0 <osal_info_print>
    2848:	eaffffea 	b	27f8 <opfunc_cmd_test+0x1a0>
    284c:	e5953000 	ldr	r3, [r5]
    2850:	e3530001 	cmp	r3, #1
    2854:	9a000002 	bls	2864 <opfunc_cmd_test+0x20c>
    2858:	e59f021c 	ldr	r0, [pc, #540]	; 2a7c <opfunc_cmd_test+0x424>
    285c:	e59f1210 	ldr	r1, [pc, #528]	; 2a74 <opfunc_cmd_test+0x41c>
    2860:	ebfffffe 	bl	0 <osal_info_print>
    2864:	e24b80c0 	sub	r8, fp, #192	; 0xc0
    2868:	e24b1048 	sub	r1, fp, #72	; 0x48
    286c:	e3a02005 	mov	r2, #5
    2870:	e1a00008 	mov	r0, r8
    2874:	ebfffffe 	bl	0 <osal_memcpy>
    2878:	e24b1050 	sub	r1, fp, #80	; 0x50
    287c:	eaffffbf 	b	2780 <opfunc_cmd_test+0x128>
    2880:	e5953000 	ldr	r3, [r5]
    2884:	e3530001 	cmp	r3, #1
    2888:	9a00000a 	bls	28b8 <opfunc_cmd_test+0x260>
    288c:	e59f01ec 	ldr	r0, [pc, #492]	; 2a80 <opfunc_cmd_test+0x428>
    2890:	e59f11dc 	ldr	r1, [pc, #476]	; 2a74 <opfunc_cmd_test+0x41c>
    2894:	ebfffffe 	bl	0 <osal_info_print>
    2898:	e59f31c4 	ldr	r3, [pc, #452]	; 2a64 <opfunc_cmd_test+0x40c>
    289c:	e5933000 	ldr	r3, [r3]
    28a0:	e3530001 	cmp	r3, #1
    28a4:	9a000003 	bls	28b8 <opfunc_cmd_test+0x260>
    28a8:	e51b214c 	ldr	r2, [fp, #-332]	; 0xfffffeb4
    28ac:	e59f01d0 	ldr	r0, [pc, #464]	; 2a84 <opfunc_cmd_test+0x42c>
    28b0:	e59f11bc 	ldr	r1, [pc, #444]	; 2a74 <opfunc_cmd_test+0x41c>
    28b4:	ebfffffe 	bl	0 <osal_info_print>
    28b8:	e3590005 	cmp	r9, #5
    28bc:	9a000045 	bls	29d8 <opfunc_cmd_test+0x380>
    28c0:	e2870005 	add	r0, r7, #5
    28c4:	e59f11bc 	ldr	r1, [pc, #444]	; 2a88 <opfunc_cmd_test+0x430>
    28c8:	e2492005 	sub	r2, r9, #5
    28cc:	ebfffffe 	bl	17c <wmt_core_dump_data>
    28d0:	e51b4150 	ldr	r4, [fp, #-336]	; 0xfffffeb0
    28d4:	e3560000 	cmp	r6, #0
    28d8:	13540000 	cmpne	r4, #0
    28dc:	03a03000 	moveq	r3, #0
    28e0:	13a03001 	movne	r3, #1
    28e4:	1a000040 	bne	29ec <opfunc_cmd_test+0x394>
    28e8:	e51b2148 	ldr	r2, [fp, #-328]	; 0xfffffeb8
    28ec:	e5823014 	str	r3, [r2, #20]
    28f0:	e5953000 	ldr	r3, [r5]
    28f4:	e3530001 	cmp	r3, #1
    28f8:	9affffbe 	bls	27f8 <opfunc_cmd_test+0x1a0>
    28fc:	e59f1170 	ldr	r1, [pc, #368]	; 2a74 <opfunc_cmd_test+0x41c>
    2900:	e59f0178 	ldr	r0, [pc, #376]	; 2a80 <opfunc_cmd_test+0x428>
    2904:	ebfffffe 	bl	0 <osal_info_print>
    2908:	eaffffba 	b	27f8 <opfunc_cmd_test+0x1a0>
    290c:	e1a03008 	mov	r3, r8
    2910:	e59f115c 	ldr	r1, [pc, #348]	; 2a74 <opfunc_cmd_test+0x41c>
    2914:	e30026d3 	movw	r2, #1747	; 0x6d3
    2918:	e59f016c 	ldr	r0, [pc, #364]	; 2a8c <opfunc_cmd_test+0x434>
    291c:	e58dc000 	str	ip, [sp]
    2920:	e3e08000 	mvn	r8, #0
    2924:	e58d7004 	str	r7, [sp, #4]
    2928:	ebfffffe 	bl	0 <osal_err_print>
    292c:	eaffffb1 	b	27f8 <opfunc_cmd_test+0x1a0>
    2930:	e51b3148 	ldr	r3, [fp, #-328]	; 0xfffffeb8
    2934:	e51be148 	ldr	lr, [fp, #-328]	; 0xfffffeb8
    2938:	e51b2148 	ldr	r2, [fp, #-328]	; 0xfffffeb8
    293c:	e593300c 	ldr	r3, [r3, #12]
    2940:	e353000f 	cmp	r3, #15
    2944:	e50b314c 	str	r3, [fp, #-332]	; 0xfffffeb4
    2948:	e59ee010 	ldr	lr, [lr, #16]
    294c:	e50be150 	str	lr, [fp, #-336]	; 0xfffffeb0
    2950:	e5926014 	ldr	r6, [r2, #20]
    2954:	8a00003b 	bhi	2a48 <opfunc_cmd_test+0x3f0>
    2958:	e5953000 	ldr	r3, [r5]
    295c:	e3530001 	cmp	r3, #1
    2960:	9a000003 	bls	2974 <opfunc_cmd_test+0x31c>
    2964:	e59f0124 	ldr	r0, [pc, #292]	; 2a90 <opfunc_cmd_test+0x438>
    2968:	e51b214c 	ldr	r2, [fp, #-332]	; 0xfffffeb4
    296c:	e59f1100 	ldr	r1, [pc, #256]	; 2a74 <opfunc_cmd_test+0x41c>
    2970:	ebfffffe 	bl	0 <osal_info_print>
    2974:	e24b80c0 	sub	r8, fp, #192	; 0xc0
    2978:	e24b1058 	sub	r1, fp, #88	; 0x58
    297c:	e1a00008 	mov	r0, r8
    2980:	e3a02006 	mov	r2, #6
    2984:	ebfffffe 	bl	0 <osal_memcpy>
    2988:	e51b314c 	ldr	r3, [fp, #-332]	; 0xfffffeb4
    298c:	e3530004 	cmp	r3, #4
    2990:	e54b30bb 	strb	r3, [fp, #-187]	; 0xffffff45
    2994:	9a000024 	bls	2a2c <opfunc_cmd_test+0x3d4>
    2998:	e51be14c 	ldr	lr, [fp, #-332]	; 0xfffffeb4
    299c:	e35e0005 	cmp	lr, #5
    29a0:	0a00001a 	beq	2a10 <opfunc_cmd_test+0x3b8>
    29a4:	e51b214c 	ldr	r2, [fp, #-332]	; 0xfffffeb4
    29a8:	e2423006 	sub	r3, r2, #6
    29ac:	e3530009 	cmp	r3, #9
    29b0:	83a09000 	movhi	r9, #0
    29b4:	83a07006 	movhi	r7, #6
    29b8:	8affff78 	bhi	27a0 <opfunc_cmd_test+0x148>
    29bc:	e3a0200d 	mov	r2, #13
    29c0:	e24b1080 	sub	r1, fp, #128	; 0x80
    29c4:	e24b0c01 	sub	r0, fp, #256	; 0x100
    29c8:	e1a09002 	mov	r9, r2
    29cc:	e3a07006 	mov	r7, #6
    29d0:	ebfffffe 	bl	0 <osal_memcpy>
    29d4:	eaffff71 	b	27a0 <opfunc_cmd_test+0x148>
    29d8:	e30026e5 	movw	r2, #1765	; 0x6e5
    29dc:	e59f1090 	ldr	r1, [pc, #144]	; 2a74 <opfunc_cmd_test+0x41c>
    29e0:	e59f00ac 	ldr	r0, [pc, #172]	; 2a94 <opfunc_cmd_test+0x43c>
    29e4:	ebfffffe 	bl	0 <osal_err_print>
    29e8:	eaffffb8 	b	28d0 <opfunc_cmd_test+0x278>
    29ec:	e51be148 	ldr	lr, [fp, #-328]	; 0xfffffeb8
    29f0:	e2492005 	sub	r2, r9, #5
    29f4:	e1520006 	cmp	r2, r6
    29f8:	21a02006 	movcs	r2, r6
    29fc:	e1a00004 	mov	r0, r4
    2a00:	e2871005 	add	r1, r7, #5
    2a04:	e58e2014 	str	r2, [lr, #20]
    2a08:	ebfffffe 	bl	0 <osal_memcpy>
    2a0c:	eaffffb7 	b	28f0 <opfunc_cmd_test+0x298>
    2a10:	e1a01007 	mov	r1, r7
    2a14:	e3a0200b 	mov	r2, #11
    2a18:	e24b0c01 	sub	r0, fp, #256	; 0x100
    2a1c:	e1a09002 	mov	r9, r2
    2a20:	e3a07006 	mov	r7, #6
    2a24:	ebfffffe 	bl	0 <osal_memcpy>
    2a28:	eaffff5c 	b	27a0 <opfunc_cmd_test+0x148>
    2a2c:	e3a02009 	mov	r2, #9
    2a30:	e24b1064 	sub	r1, fp, #100	; 0x64
    2a34:	e24b0c01 	sub	r0, fp, #256	; 0x100
    2a38:	e1a09002 	mov	r9, r2
    2a3c:	e3a07006 	mov	r7, #6
    2a40:	ebfffffe 	bl	0 <osal_memcpy>
    2a44:	eaffff55 	b	27a0 <opfunc_cmd_test+0x148>
    2a48:	e30026c8 	movw	r2, #1736	; 0x6c8
    2a4c:	e59f1020 	ldr	r1, [pc, #32]	; 2a74 <opfunc_cmd_test+0x41c>
    2a50:	e59f0040 	ldr	r0, [pc, #64]	; 2a98 <opfunc_cmd_test+0x440>
    2a54:	e3a08000 	mov	r8, #0
    2a58:	ebfffffe 	bl	0 <osal_err_print>
    2a5c:	eaffff65 	b	27f8 <opfunc_cmd_test+0x1a0>
    2a60:	0000021c 	andeq	r0, r0, ip, lsl r2
    2a64:	00000000 	andeq	r0, r0, r0
    2a68:	0000025c 	andeq	r0, r0, ip, asr r2
    2a6c:	000015b0 			; <UNDEFINED> instruction: 0x000015b0
    2a70:	000015d4 	ldrdeq	r1, [r0], -r4
    2a74:	0000026c 	andeq	r0, r0, ip, ror #4
    2a78:	000016b0 			; <UNDEFINED> instruction: 0x000016b0
    2a7c:	000015f8 	strdeq	r1, [r0], -r8
    2a80:	000016e4 	andeq	r1, r0, r4, ror #13
    2a84:	00001730 	andeq	r1, r0, r0, lsr r7
    2a88:	00001758 	andeq	r1, r0, r8, asr r7
    2a8c:	0000167c 	andeq	r1, r0, ip, ror r6
    2a90:	00001620 	andeq	r1, r0, r0, lsr #12
    2a94:	00001768 	andeq	r1, r0, r8, ror #14
    2a98:	00001658 	andeq	r1, r0, r8, asr r6

00002a9c <opfunc_lpbk>:
    2a9c:	e1a0c00d 	mov	ip, sp
    2aa0:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
    2aa4:	e24cb004 	sub	fp, ip, #4
    2aa8:	e24dd044 	sub	sp, sp, #68	; 0x44
    2aac:	e59f320c 	ldr	r3, [pc, #524]	; 2cc0 <opfunc_lpbk+0x224>
    2ab0:	e1a09000 	mov	r9, r0
    2ab4:	e24b7040 	sub	r7, fp, #64	; 0x40
    2ab8:	e59fe204 	ldr	lr, [pc, #516]	; 2cc4 <opfunc_lpbk+0x228>
    2abc:	e283c008 	add	ip, r3, #8
    2ac0:	e3a02000 	mov	r2, #0
    2ac4:	e8930003 	ldm	r3, {r0, r1}
    2ac8:	e59ee000 	ldr	lr, [lr]
    2acc:	e50b2038 	str	r2, [fp, #-56]	; 0xffffffc8
    2ad0:	e50b0040 	str	r0, [fp, #-64]	; 0xffffffc0
    2ad4:	e35e0003 	cmp	lr, #3
    2ad8:	e5c71004 	strb	r1, [r7, #4]
    2adc:	e89c0003 	ldm	ip, {r0, r1}
    2ae0:	e50b2034 	str	r2, [fp, #-52]	; 0xffffffcc
    2ae4:	e599a008 	ldr	sl, [r9, #8]
    2ae8:	e50b0048 	str	r0, [fp, #-72]	; 0xffffffb8
    2aec:	e54b1044 	strb	r1, [fp, #-68]	; 0xffffffbc
    2af0:	e599200c 	ldr	r2, [r9, #12]
    2af4:	e50b2050 	str	r2, [fp, #-80]	; 0xffffffb0
    2af8:	8a00003c 	bhi	2bf0 <opfunc_lpbk+0x154>
    2afc:	e59f41c4 	ldr	r4, [pc, #452]	; 2cc8 <opfunc_lpbk+0x22c>
    2b00:	e5948020 	ldr	r8, [r4, #32]
    2b04:	e3580002 	cmp	r8, #2
    2b08:	1a00003c 	bne	2c00 <opfunc_lpbk+0x164>
    2b0c:	e28a5005 	add	r5, sl, #5
    2b10:	e3550b01 	cmp	r5, #1024	; 0x400
    2b14:	8a000039 	bhi	2c00 <opfunc_lpbk+0x164>
    2b18:	e24b602c 	sub	r6, fp, #44	; 0x2c
    2b1c:	e3a01000 	mov	r1, #0
    2b20:	e3a02b01 	mov	r2, #1024	; 0x400
    2b24:	e2840054 	add	r0, r4, #84	; 0x54
    2b28:	ebfffffe 	bl	0 <osal_memset>
    2b2c:	e28a3001 	add	r3, sl, #1
    2b30:	e1a02008 	mov	r2, r8
    2b34:	e16630b2 	strh	r3, [r6, #-2]!
    2b38:	e2870002 	add	r0, r7, #2
    2b3c:	e1a01006 	mov	r1, r6
    2b40:	ebfffffe 	bl	0 <osal_memcpy>
    2b44:	e24b3048 	sub	r3, fp, #72	; 0x48
    2b48:	e2830002 	add	r0, r3, #2
    2b4c:	e1a01006 	mov	r1, r6
    2b50:	e1a02008 	mov	r2, r8
    2b54:	ebfffffe 	bl	0 <osal_memcpy>
    2b58:	e1a01007 	mov	r1, r7
    2b5c:	e3a02005 	mov	r2, #5
    2b60:	e2840054 	add	r0, r4, #84	; 0x54
    2b64:	ebfffffe 	bl	0 <osal_memcpy>
    2b68:	e51b1050 	ldr	r1, [fp, #-80]	; 0xffffffb0
    2b6c:	e1a0200a 	mov	r2, sl
    2b70:	e2840059 	add	r0, r4, #89	; 0x59
    2b74:	ebfffffe 	bl	0 <osal_memcpy>
    2b78:	e2840054 	add	r0, r4, #84	; 0x54
    2b7c:	e1a01005 	mov	r1, r5
    2b80:	e24b2034 	sub	r2, fp, #52	; 0x34
    2b84:	e3a03000 	mov	r3, #0
    2b88:	ebfffffe 	bl	10e4 <wmt_core_tx>
    2b8c:	e3500000 	cmp	r0, #0
    2b90:	1a000010 	bne	2bd8 <opfunc_lpbk+0x13c>
    2b94:	e2840054 	add	r0, r4, #84	; 0x54
    2b98:	e1a01005 	mov	r1, r5
    2b9c:	e24b2038 	sub	r2, fp, #56	; 0x38
    2ba0:	ebfffffe 	bl	8b4 <wmt_core_rx>
    2ba4:	e3500000 	cmp	r0, #0
    2ba8:	1a00001f 	bne	2c2c <opfunc_lpbk+0x190>
    2bac:	e51b3038 	ldr	r3, [fp, #-56]	; 0xffffffc8
    2bb0:	e1550003 	cmp	r5, r3
    2bb4:	0a000022 	beq	2c44 <opfunc_lpbk+0x1a8>
    2bb8:	e59f010c 	ldr	r0, [pc, #268]	; 2ccc <opfunc_lpbk+0x230>
    2bbc:	e300265f 	movw	r2, #1631	; 0x65f
    2bc0:	e59f1108 	ldr	r1, [pc, #264]	; 2cd0 <opfunc_lpbk+0x234>
    2bc4:	e58d5000 	str	r5, [sp]
    2bc8:	ebfffffe 	bl	0 <osal_err_print>
    2bcc:	e3a00001 	mov	r0, #1
    2bd0:	e24bd028 	sub	sp, fp, #40	; 0x28
    2bd4:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
    2bd8:	e59f00f4 	ldr	r0, [pc, #244]	; 2cd4 <opfunc_lpbk+0x238>
    2bdc:	e3002654 	movw	r2, #1620	; 0x654
    2be0:	e59f10e8 	ldr	r1, [pc, #232]	; 2cd0 <opfunc_lpbk+0x234>
    2be4:	ebfffffe 	bl	0 <osal_err_print>
    2be8:	e3a00001 	mov	r0, #1
    2bec:	eafffff7 	b	2bd0 <opfunc_lpbk+0x134>
    2bf0:	e2831010 	add	r1, r3, #16
    2bf4:	e59f00dc 	ldr	r0, [pc, #220]	; 2cd8 <opfunc_lpbk+0x23c>
    2bf8:	ebfffffe 	bl	0 <osal_loud_print>
    2bfc:	eaffffbe 	b	2afc <opfunc_lpbk+0x60>
    2c00:	e59f10c8 	ldr	r1, [pc, #200]	; 2cd0 <opfunc_lpbk+0x234>
    2c04:	e300263b 	movw	r2, #1595	; 0x63b
    2c08:	e59f00cc 	ldr	r0, [pc, #204]	; 2cdc <opfunc_lpbk+0x240>
    2c0c:	ebfffffe 	bl	0 <osal_err_print>
    2c10:	e59f00c8 	ldr	r0, [pc, #200]	; 2ce0 <opfunc_lpbk+0x244>
    2c14:	e59f10c8 	ldr	r1, [pc, #200]	; 2ce4 <opfunc_lpbk+0x248>
    2c18:	e300263c 	movw	r2, #1596	; 0x63c
    2c1c:	e59f30c4 	ldr	r3, [pc, #196]	; 2ce8 <opfunc_lpbk+0x24c>
    2c20:	ebfffffe 	bl	0 <osal_err_print>
    2c24:	e3e00001 	mvn	r0, #1
    2c28:	eaffffe8 	b	2bd0 <opfunc_lpbk+0x134>
    2c2c:	e59f00b8 	ldr	r0, [pc, #184]	; 2cec <opfunc_lpbk+0x250>
    2c30:	e300265a 	movw	r2, #1626	; 0x65a
    2c34:	e59f1094 	ldr	r1, [pc, #148]	; 2cd0 <opfunc_lpbk+0x234>
    2c38:	ebfffffe 	bl	0 <osal_err_print>
    2c3c:	e3a00001 	mov	r0, #1
    2c40:	eaffffe2 	b	2bd0 <opfunc_lpbk+0x134>
    2c44:	e24b0048 	sub	r0, fp, #72	; 0x48
    2c48:	e2841054 	add	r1, r4, #84	; 0x54
    2c4c:	e3a02005 	mov	r2, #5
    2c50:	ebfffffe 	bl	0 <osal_memcmp>
    2c54:	e2505000 	subs	r5, r0, #0
    2c58:	0a00000f 	beq	2c9c <opfunc_lpbk+0x200>
    2c5c:	e5d4c058 	ldrb	ip, [r4, #88]	; 0x58
    2c60:	e3002666 	movw	r2, #1638	; 0x666
    2c64:	e5d46054 	ldrb	r6, [r4, #84]	; 0x54
    2c68:	e5d45055 	ldrb	r5, [r4, #85]	; 0x55
    2c6c:	e5d4e056 	ldrb	lr, [r4, #86]	; 0x56
    2c70:	e5d44057 	ldrb	r4, [r4, #87]	; 0x57
    2c74:	e51b3038 	ldr	r3, [fp, #-56]	; 0xffffffc8
    2c78:	e59f0070 	ldr	r0, [pc, #112]	; 2cf0 <opfunc_lpbk+0x254>
    2c7c:	e59f104c 	ldr	r1, [pc, #76]	; 2cd0 <opfunc_lpbk+0x234>
    2c80:	e58d6000 	str	r6, [sp]
    2c84:	e98d4020 	stmib	sp, {r5, lr}
    2c88:	e58d400c 	str	r4, [sp, #12]
    2c8c:	e58dc010 	str	ip, [sp, #16]
    2c90:	ebfffffe 	bl	0 <osal_err_print>
    2c94:	e3a00001 	mov	r0, #1
    2c98:	eaffffcc 	b	2bd0 <opfunc_lpbk+0x134>
    2c9c:	e51b3038 	ldr	r3, [fp, #-56]	; 0xffffffc8
    2ca0:	e2841059 	add	r1, r4, #89	; 0x59
    2ca4:	e599000c 	ldr	r0, [r9, #12]
    2ca8:	e1a0200a 	mov	r2, sl
    2cac:	e2433005 	sub	r3, r3, #5
    2cb0:	e5893008 	str	r3, [r9, #8]
    2cb4:	ebfffffe 	bl	0 <osal_memcpy>
    2cb8:	e1a00005 	mov	r0, r5
    2cbc:	eaffffc3 	b	2bd0 <opfunc_lpbk+0x134>
    2cc0:	0000027c 	andeq	r0, r0, ip, ror r2
	...
    2ccc:	00001830 	andeq	r1, r0, r0, lsr r8
    2cd0:	0000028c 	andeq	r0, r0, ip, lsl #5
    2cd4:	000017c8 	andeq	r1, r0, r8, asr #15
    2cd8:	00000b84 	andeq	r0, r0, r4, lsl #23
    2cdc:	00001798 	muleq	r0, r8, r7
    2ce0:	0000026c 	andeq	r0, r0, ip, ror #4
    2ce4:	0000027c 	andeq	r0, r0, ip, ror r2
    2ce8:	000002ac 	andeq	r0, r0, ip, lsr #5
    2cec:	000017fc 	strdeq	r1, [r0], -ip
    2cf0:	00001868 	andeq	r1, r0, r8, ror #16

00002cf4 <opfunc_dsns>:
    2cf4:	e1a0c00d 	mov	ip, sp
    2cf8:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
    2cfc:	e24cb004 	sub	fp, ip, #4
    2d00:	e24dd04c 	sub	sp, sp, #76	; 0x4c
    2d04:	e59f4188 	ldr	r4, [pc, #392]	; 2e94 <opfunc_dsns+0x1a0>
    2d08:	e1a05000 	mov	r5, r0
    2d0c:	e5902008 	ldr	r2, [r0, #8]
    2d10:	e24b6040 	sub	r6, fp, #64	; 0x40
    2d14:	e286c004 	add	ip, r6, #4
    2d18:	e3a0e000 	mov	lr, #0
    2d1c:	e24b7030 	sub	r7, fp, #48	; 0x30
    2d20:	e1a0300e 	mov	r3, lr
    2d24:	e5c4204c 	strb	r2, [r4, #76]	; 0x4c
    2d28:	e2840048 	add	r0, r4, #72	; 0x48
    2d2c:	e595500c 	ldr	r5, [r5, #12]
    2d30:	e3a01006 	mov	r1, #6
    2d34:	e48ce004 	str	lr, [ip], #4
    2d38:	e1a02007 	mov	r2, r7
    2d3c:	e48ce004 	str	lr, [ip], #4
    2d40:	e5c4504d 	strb	r5, [r4, #77]	; 0x4d
    2d44:	e58ce000 	str	lr, [ip]
    2d48:	e50be040 	str	lr, [fp, #-64]	; 0xffffffc0
    2d4c:	ebfffffe 	bl	10e4 <wmt_core_tx>
    2d50:	e2505000 	subs	r5, r0, #0
    2d54:	151bc030 	ldrne	ip, [fp, #-48]	; 0xffffffd0
    2d58:	1a000002 	bne	2d68 <opfunc_dsns+0x74>
    2d5c:	e51bc030 	ldr	ip, [fp, #-48]	; 0xffffffd0
    2d60:	e35c0006 	cmp	ip, #6
    2d64:	0a00000a 	beq	2d94 <opfunc_dsns+0xa0>
    2d68:	e59f1128 	ldr	r1, [pc, #296]	; 2e98 <opfunc_dsns+0x1a4>
    2d6c:	e300260c 	movw	r2, #1548	; 0x60c
    2d70:	e1a03005 	mov	r3, r5
    2d74:	e59f0120 	ldr	r0, [pc, #288]	; 2e9c <opfunc_dsns+0x1a8>
    2d78:	e58dc000 	str	ip, [sp]
    2d7c:	e3a0c006 	mov	ip, #6
    2d80:	e58dc004 	str	ip, [sp, #4]
    2d84:	ebfffffe 	bl	0 <osal_err_print>
    2d88:	e1a00005 	mov	r0, r5
    2d8c:	e24bd028 	sub	sp, fp, #40	; 0x28
    2d90:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
    2d94:	e1a02007 	mov	r2, r7
    2d98:	e1a00006 	mov	r0, r6
    2d9c:	e3a01005 	mov	r1, #5
    2da0:	ebfffffe 	bl	8b4 <wmt_core_rx>
    2da4:	e2505000 	subs	r5, r0, #0
    2da8:	151b7030 	ldrne	r7, [fp, #-48]	; 0xffffffd0
    2dac:	1a000002 	bne	2dbc <opfunc_dsns+0xc8>
    2db0:	e51b7030 	ldr	r7, [fp, #-48]	; 0xffffffd0
    2db4:	e3570005 	cmp	r7, #5
    2db8:	0a000008 	beq	2de0 <opfunc_dsns+0xec>
    2dbc:	e59f10d4 	ldr	r1, [pc, #212]	; 2e98 <opfunc_dsns+0x1a4>
    2dc0:	e3002614 	movw	r2, #1556	; 0x614
    2dc4:	e1a03005 	mov	r3, r5
    2dc8:	e59f00d0 	ldr	r0, [pc, #208]	; 2ea0 <opfunc_dsns+0x1ac>
    2dcc:	e3a0c005 	mov	ip, #5
    2dd0:	e88d1080 	stm	sp, {r7, ip}
    2dd4:	ebfffffe 	bl	0 <osal_err_print>
    2dd8:	ebfffffe 	bl	0 <mtk_wcn_stp_dbg_dump_package>
    2ddc:	eaffffe9 	b	2d88 <opfunc_dsns+0x94>
    2de0:	e1a00006 	mov	r0, r6
    2de4:	e2841050 	add	r1, r4, #80	; 0x50
    2de8:	e1a02007 	mov	r2, r7
    2dec:	ebfffffe 	bl	0 <osal_memcmp>
    2df0:	e3500000 	cmp	r0, #0
    2df4:	1a000007 	bne	2e18 <opfunc_dsns+0x124>
    2df8:	e59f30a4 	ldr	r3, [pc, #164]	; 2ea4 <opfunc_dsns+0x1b0>
    2dfc:	e5933000 	ldr	r3, [r3]
    2e00:	e3530001 	cmp	r3, #1
    2e04:	9affffdf 	bls	2d88 <opfunc_dsns+0x94>
    2e08:	e59f1088 	ldr	r1, [pc, #136]	; 2e98 <opfunc_dsns+0x1a4>
    2e0c:	e59f0094 	ldr	r0, [pc, #148]	; 2ea8 <opfunc_dsns+0x1b4>
    2e10:	ebfffffe 	bl	0 <osal_info_print>
    2e14:	eaffffdb 	b	2d88 <opfunc_dsns+0x94>
    2e18:	e59f1078 	ldr	r1, [pc, #120]	; 2e98 <opfunc_dsns+0x1a4>
    2e1c:	e300261a 	movw	r2, #1562	; 0x61a
    2e20:	e59f0084 	ldr	r0, [pc, #132]	; 2eac <opfunc_dsns+0x1b8>
    2e24:	ebfffffe 	bl	0 <osal_err_print>
    2e28:	e5d41054 	ldrb	r1, [r4, #84]	; 0x54
    2e2c:	e55be040 	ldrb	lr, [fp, #-64]	; 0xffffffc0
    2e30:	e300261d 	movw	r2, #1565	; 0x61d
    2e34:	e55bc03f 	ldrb	ip, [fp, #-63]	; 0xffffffc1
    2e38:	e58d1028 	str	r1, [sp, #40]	; 0x28
    2e3c:	e5d41051 	ldrb	r1, [r4, #81]	; 0x51
    2e40:	e5d49050 	ldrb	r9, [r4, #80]	; 0x50
    2e44:	e55b603e 	ldrb	r6, [fp, #-62]	; 0xffffffc2
    2e48:	e58d101c 	str	r1, [sp, #28]
    2e4c:	e5d41052 	ldrb	r1, [r4, #82]	; 0x52
    2e50:	e55b803d 	ldrb	r8, [fp, #-61]	; 0xffffffc3
    2e54:	e55ba03c 	ldrb	sl, [fp, #-60]	; 0xffffffc4
    2e58:	e58d1020 	str	r1, [sp, #32]
    2e5c:	e5d44053 	ldrb	r4, [r4, #83]	; 0x53
    2e60:	e51b3030 	ldr	r3, [fp, #-48]	; 0xffffffd0
    2e64:	e59f102c 	ldr	r1, [pc, #44]	; 2e98 <opfunc_dsns+0x1a4>
    2e68:	e59f0040 	ldr	r0, [pc, #64]	; 2eb0 <opfunc_dsns+0x1bc>
    2e6c:	e58de000 	str	lr, [sp]
    2e70:	e58dc004 	str	ip, [sp, #4]
    2e74:	e58d6008 	str	r6, [sp, #8]
    2e78:	e58d800c 	str	r8, [sp, #12]
    2e7c:	e58da010 	str	sl, [sp, #16]
    2e80:	e58d7014 	str	r7, [sp, #20]
    2e84:	e58d9018 	str	r9, [sp, #24]
    2e88:	e58d4024 	str	r4, [sp, #36]	; 0x24
    2e8c:	ebfffffe 	bl	0 <osal_err_print>
    2e90:	eaffffbc 	b	2d88 <opfunc_dsns+0x94>
    2e94:	00000000 	andeq	r0, r0, r0
    2e98:	00000298 	muleq	r0, r8, r2
    2e9c:	000018bc 			; <UNDEFINED> instruction: 0x000018bc
    2ea0:	000018f4 	strdeq	r1, [r0], -r4
    2ea4:	00000000 	andeq	r0, r0, r0
    2ea8:	0000195c 	andeq	r1, r0, ip, asr r9
    2eac:	0000192c 	andeq	r1, r0, ip, lsr #18
    2eb0:	00000a30 	andeq	r0, r0, r0, lsr sl

00002eb4 <opfunc_pwr_sv>:
    2eb4:	e1a0c00d 	mov	ip, sp
    2eb8:	e92ddff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
    2ebc:	e24cb004 	sub	fp, ip, #4
    2ec0:	e24dd054 	sub	sp, sp, #84	; 0x54
    2ec4:	e5902008 	ldr	r2, [r0, #8]
    2ec8:	e3a01000 	mov	r1, #0
    2ecc:	e24b7040 	sub	r7, fp, #64	; 0x40
    2ed0:	e1a04000 	mov	r4, r0
    2ed4:	e2873004 	add	r3, r7, #4
    2ed8:	e1520001 	cmp	r2, r1
    2edc:	e50b1040 	str	r1, [fp, #-64]	; 0xffffffc0
    2ee0:	e4831004 	str	r1, [r3], #4
    2ee4:	e4831004 	str	r1, [r3], #4
    2ee8:	e5831000 	str	r1, [r3]
    2eec:	1a000019 	bne	2f58 <opfunc_pwr_sv+0xa4>
    2ef0:	e59f64c0 	ldr	r6, [pc, #1216]	; 33b8 <opfunc_pwr_sv+0x504>
    2ef4:	e5963000 	ldr	r3, [r6]
    2ef8:	e3530002 	cmp	r3, #2
    2efc:	8a000040 	bhi	3004 <opfunc_pwr_sv+0x150>
    2f00:	e24b8030 	sub	r8, fp, #48	; 0x30
    2f04:	e59f04b0 	ldr	r0, [pc, #1200]	; 33bc <opfunc_pwr_sv+0x508>
    2f08:	e3a01005 	mov	r1, #5
    2f0c:	e1a02008 	mov	r2, r8
    2f10:	e3a03000 	mov	r3, #0
    2f14:	ebfffffe 	bl	10e4 <wmt_core_tx>
    2f18:	e2505000 	subs	r5, r0, #0
    2f1c:	151bc030 	ldrne	ip, [fp, #-48]	; 0xffffffd0
    2f20:	1a000002 	bne	2f30 <opfunc_pwr_sv+0x7c>
    2f24:	e51bc030 	ldr	ip, [fp, #-48]	; 0xffffffd0
    2f28:	e35c0005 	cmp	ip, #5
    2f2c:	0a00005e 	beq	30ac <opfunc_pwr_sv+0x1f8>
    2f30:	e59f0488 	ldr	r0, [pc, #1160]	; 33c0 <opfunc_pwr_sv+0x50c>
    2f34:	e3002584 	movw	r2, #1412	; 0x584
    2f38:	e59f1484 	ldr	r1, [pc, #1156]	; 33c4 <opfunc_pwr_sv+0x510>
    2f3c:	e1a03005 	mov	r3, r5
    2f40:	e58dc000 	str	ip, [sp]
    2f44:	e3a0c005 	mov	ip, #5
    2f48:	e58dc004 	str	ip, [sp, #4]
    2f4c:	ebfffffe 	bl	0 <osal_err_print>
    2f50:	e5942008 	ldr	r2, [r4, #8]
    2f54:	ea00001c 	b	2fcc <opfunc_pwr_sv+0x118>
    2f58:	e3520002 	cmp	r2, #2
    2f5c:	1a00003c 	bne	3054 <opfunc_pwr_sv+0x1a0>
    2f60:	e59f6450 	ldr	r6, [pc, #1104]	; 33b8 <opfunc_pwr_sv+0x504>
    2f64:	e5963000 	ldr	r3, [r6]
    2f68:	e3530002 	cmp	r3, #2
    2f6c:	8a000034 	bhi	3044 <opfunc_pwr_sv+0x190>
    2f70:	e3a01001 	mov	r1, #1
    2f74:	e24b8030 	sub	r8, fp, #48	; 0x30
    2f78:	e59f0448 	ldr	r0, [pc, #1096]	; 33c8 <opfunc_pwr_sv+0x514>
    2f7c:	e1a02008 	mov	r2, r8
    2f80:	e1a03001 	mov	r3, r1
    2f84:	ebfffffe 	bl	10e4 <wmt_core_tx>
    2f88:	e2505000 	subs	r5, r0, #0
    2f8c:	1a000002 	bne	2f9c <opfunc_pwr_sv+0xe8>
    2f90:	e51b3030 	ldr	r3, [fp, #-48]	; 0xffffffd0
    2f94:	e3530001 	cmp	r3, #1
    2f98:	0a00005a 	beq	3108 <opfunc_pwr_sv+0x254>
    2f9c:	e3a00004 	mov	r0, #4
    2fa0:	ebfffffe 	bl	840 <wmt_core_rx_flush>
    2fa4:	e51bc030 	ldr	ip, [fp, #-48]	; 0xffffffd0
    2fa8:	e30025aa 	movw	r2, #1450	; 0x5aa
    2fac:	e59f0418 	ldr	r0, [pc, #1048]	; 33cc <opfunc_pwr_sv+0x518>
    2fb0:	e59f140c 	ldr	r1, [pc, #1036]	; 33c4 <opfunc_pwr_sv+0x510>
    2fb4:	e1a03005 	mov	r3, r5
    2fb8:	e58dc000 	str	ip, [sp]
    2fbc:	e3a0c001 	mov	ip, #1
    2fc0:	e58dc004 	str	ip, [sp, #4]
    2fc4:	ebfffffe 	bl	0 <osal_err_print>
    2fc8:	e5942008 	ldr	r2, [r4, #8]
    2fcc:	e3520004 	cmp	r2, #4
    2fd0:	8a000008 	bhi	2ff8 <opfunc_pwr_sv+0x144>
    2fd4:	e59f33dc 	ldr	r3, [pc, #988]	; 33b8 <opfunc_pwr_sv+0x504>
    2fd8:	e594600c 	ldr	r6, [r4, #12]
    2fdc:	e5933000 	ldr	r3, [r3]
    2fe0:	e3530002 	cmp	r3, #2
    2fe4:	8a00000a 	bhi	3014 <opfunc_pwr_sv+0x160>
    2fe8:	e3560000 	cmp	r6, #0
    2fec:	0a00000e 	beq	302c <opfunc_pwr_sv+0x178>
    2ff0:	e5940008 	ldr	r0, [r4, #8]
    2ff4:	e12fff36 	blx	r6
    2ff8:	e1a00005 	mov	r0, r5
    2ffc:	e24bd028 	sub	sp, fp, #40	; 0x28
    3000:	e89daff0 	ldm	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
    3004:	e59f13b8 	ldr	r1, [pc, #952]	; 33c4 <opfunc_pwr_sv+0x510>
    3008:	e59f03c0 	ldr	r0, [pc, #960]	; 33d0 <opfunc_pwr_sv+0x51c>
    300c:	ebfffffe 	bl	0 <osal_dbg_print>
    3010:	eaffffba 	b	2f00 <opfunc_pwr_sv+0x4c>
    3014:	e59f03b8 	ldr	r0, [pc, #952]	; 33d4 <opfunc_pwr_sv+0x520>
    3018:	e1a03006 	mov	r3, r6
    301c:	e59f13a0 	ldr	r1, [pc, #928]	; 33c4 <opfunc_pwr_sv+0x510>
    3020:	ebfffffe 	bl	0 <osal_dbg_print>
    3024:	e3560000 	cmp	r6, #0
    3028:	1afffff0 	bne	2ff0 <opfunc_pwr_sv+0x13c>
    302c:	e1a03006 	mov	r3, r6
    3030:	e59f138c 	ldr	r1, [pc, #908]	; 33c4 <opfunc_pwr_sv+0x510>
    3034:	e30025f6 	movw	r2, #1526	; 0x5f6
    3038:	e59f0398 	ldr	r0, [pc, #920]	; 33d8 <opfunc_pwr_sv+0x524>
    303c:	ebfffffe 	bl	0 <osal_err_print>
    3040:	eaffffec 	b	2ff8 <opfunc_pwr_sv+0x144>
    3044:	e59f1378 	ldr	r1, [pc, #888]	; 33c4 <opfunc_pwr_sv+0x510>
    3048:	e59f038c 	ldr	r0, [pc, #908]	; 33dc <opfunc_pwr_sv+0x528>
    304c:	ebfffffe 	bl	0 <osal_dbg_print>
    3050:	eaffffc6 	b	2f70 <opfunc_pwr_sv+0xbc>
    3054:	e3520001 	cmp	r2, #1
    3058:	13e05000 	mvnne	r5, #0
    305c:	1affffda 	bne	2fcc <opfunc_pwr_sv+0x118>
    3060:	e59f6350 	ldr	r6, [pc, #848]	; 33b8 <opfunc_pwr_sv+0x504>
    3064:	e5963000 	ldr	r3, [r6]
    3068:	e3530002 	cmp	r3, #2
    306c:	8a000051 	bhi	31b8 <opfunc_pwr_sv+0x304>
    3070:	e24b8030 	sub	r8, fp, #48	; 0x30
    3074:	e59f0364 	ldr	r0, [pc, #868]	; 33e0 <opfunc_pwr_sv+0x52c>
    3078:	e3a01005 	mov	r1, #5
    307c:	e1a02008 	mov	r2, r8
    3080:	e3a03000 	mov	r3, #0
    3084:	ebfffffe 	bl	10e4 <wmt_core_tx>
    3088:	e2505000 	subs	r5, r0, #0
    308c:	151bc030 	ldrne	ip, [fp, #-48]	; 0xffffffd0
    3090:	1a000002 	bne	30a0 <opfunc_pwr_sv+0x1ec>
    3094:	e51bc030 	ldr	ip, [fp, #-48]	; 0xffffffd0
    3098:	e35c0005 	cmp	ip, #5
    309c:	0a00007a 	beq	328c <opfunc_pwr_sv+0x3d8>
    30a0:	e59f033c 	ldr	r0, [pc, #828]	; 33e4 <opfunc_pwr_sv+0x530>
    30a4:	e30025cf 	movw	r2, #1487	; 0x5cf
    30a8:	eaffffa2 	b	2f38 <opfunc_pwr_sv+0x84>
    30ac:	e1a02008 	mov	r2, r8
    30b0:	e1a00007 	mov	r0, r7
    30b4:	e3a01006 	mov	r1, #6
    30b8:	ebfffffe 	bl	8b4 <wmt_core_rx>
    30bc:	e2505000 	subs	r5, r0, #0
    30c0:	1a000002 	bne	30d0 <opfunc_pwr_sv+0x21c>
    30c4:	e51b8030 	ldr	r8, [fp, #-48]	; 0xffffffd0
    30c8:	e3580006 	cmp	r8, #6
    30cc:	0a00001d 	beq	3148 <opfunc_pwr_sv+0x294>
    30d0:	e3a00004 	mov	r0, #4
    30d4:	ebfffffe 	bl	840 <wmt_core_rx_flush>
    30d8:	e51bc030 	ldr	ip, [fp, #-48]	; 0xffffffd0
    30dc:	e59f12e0 	ldr	r1, [pc, #736]	; 33c4 <opfunc_pwr_sv+0x510>
    30e0:	e300258d 	movw	r2, #1421	; 0x58d
    30e4:	e59f02fc 	ldr	r0, [pc, #764]	; 33e8 <opfunc_pwr_sv+0x534>
    30e8:	e1a03005 	mov	r3, r5
    30ec:	e58dc000 	str	ip, [sp]
    30f0:	e3a0c006 	mov	ip, #6
    30f4:	e58dc004 	str	ip, [sp, #4]
    30f8:	ebfffffe 	bl	0 <osal_err_print>
    30fc:	ebfffffe 	bl	0 <mtk_wcn_stp_dbg_dump_package>
    3100:	e5942008 	ldr	r2, [r4, #8]
    3104:	eaffffb0 	b	2fcc <opfunc_pwr_sv+0x118>
    3108:	e1a02008 	mov	r2, r8
    310c:	e1a00007 	mov	r0, r7
    3110:	e3a01006 	mov	r1, #6
    3114:	ebfffffe 	bl	8b4 <wmt_core_rx>
    3118:	e2505000 	subs	r5, r0, #0
    311c:	151b8030 	ldrne	r8, [fp, #-48]	; 0xffffffd0
    3120:	1a000002 	bne	3130 <opfunc_pwr_sv+0x27c>
    3124:	e51b8030 	ldr	r8, [fp, #-48]	; 0xffffffd0
    3128:	e3580006 	cmp	r8, #6
    312c:	0a000013 	beq	3180 <opfunc_pwr_sv+0x2cc>
    3130:	e59f128c 	ldr	r1, [pc, #652]	; 33c4 <opfunc_pwr_sv+0x510>
    3134:	e30025b2 	movw	r2, #1458	; 0x5b2
    3138:	e1a03005 	mov	r3, r5
    313c:	e59f02a8 	ldr	r0, [pc, #680]	; 33ec <opfunc_pwr_sv+0x538>
    3140:	e58d8000 	str	r8, [sp]
    3144:	eaffffe9 	b	30f0 <opfunc_pwr_sv+0x23c>
    3148:	e1a00007 	mov	r0, r7
    314c:	e59f129c 	ldr	r1, [pc, #668]	; 33f0 <opfunc_pwr_sv+0x53c>
    3150:	e1a02008 	mov	r2, r8
    3154:	ebfffffe 	bl	0 <osal_memcmp>
    3158:	e3500000 	cmp	r0, #0
    315c:	1a000027 	bne	3200 <opfunc_pwr_sv+0x34c>
    3160:	e5963000 	ldr	r3, [r6]
    3164:	e3530001 	cmp	r3, #1
    3168:	9a000022 	bls	31f8 <opfunc_pwr_sv+0x344>
    316c:	e59f0280 	ldr	r0, [pc, #640]	; 33f4 <opfunc_pwr_sv+0x540>
    3170:	e59f124c 	ldr	r1, [pc, #588]	; 33c4 <opfunc_pwr_sv+0x510>
    3174:	ebfffffe 	bl	0 <osal_info_print>
    3178:	e5942008 	ldr	r2, [r4, #8]
    317c:	eaffff92 	b	2fcc <opfunc_pwr_sv+0x118>
    3180:	e1a00007 	mov	r0, r7
    3184:	e59f126c 	ldr	r1, [pc, #620]	; 33f8 <opfunc_pwr_sv+0x544>
    3188:	e1a02008 	mov	r2, r8
    318c:	ebfffffe 	bl	0 <osal_memcmp>
    3190:	e3500000 	cmp	r0, #0
    3194:	1a00004e 	bne	32d4 <opfunc_pwr_sv+0x420>
    3198:	e5963000 	ldr	r3, [r6]
    319c:	e3530001 	cmp	r3, #1
    31a0:	9a000014 	bls	31f8 <opfunc_pwr_sv+0x344>
    31a4:	e59f0250 	ldr	r0, [pc, #592]	; 33fc <opfunc_pwr_sv+0x548>
    31a8:	e59f1214 	ldr	r1, [pc, #532]	; 33c4 <opfunc_pwr_sv+0x510>
    31ac:	ebfffffe 	bl	0 <osal_info_print>
    31b0:	e5942008 	ldr	r2, [r4, #8]
    31b4:	eaffff84 	b	2fcc <opfunc_pwr_sv+0x118>
    31b8:	e59f1204 	ldr	r1, [pc, #516]	; 33c4 <opfunc_pwr_sv+0x510>
    31bc:	e59f023c 	ldr	r0, [pc, #572]	; 3400 <opfunc_pwr_sv+0x54c>
    31c0:	ebfffffe 	bl	0 <osal_dbg_print>
    31c4:	eaffffa9 	b	3070 <opfunc_pwr_sv+0x1bc>
    31c8:	e1a00007 	mov	r0, r7
    31cc:	e59f1230 	ldr	r1, [pc, #560]	; 3404 <opfunc_pwr_sv+0x550>
    31d0:	e1a02008 	mov	r2, r8
    31d4:	ebfffffe 	bl	0 <osal_memcmp>
    31d8:	e3500000 	cmp	r0, #0
    31dc:	1a000059 	bne	3348 <opfunc_pwr_sv+0x494>
    31e0:	e5963000 	ldr	r3, [r6]
    31e4:	e3530001 	cmp	r3, #1
    31e8:	9a000002 	bls	31f8 <opfunc_pwr_sv+0x344>
    31ec:	e59f0214 	ldr	r0, [pc, #532]	; 3408 <opfunc_pwr_sv+0x554>
    31f0:	e59f11cc 	ldr	r1, [pc, #460]	; 33c4 <opfunc_pwr_sv+0x510>
    31f4:	ebfffffe 	bl	0 <osal_info_print>
    31f8:	e5942008 	ldr	r2, [r4, #8]
    31fc:	eaffff72 	b	2fcc <opfunc_pwr_sv+0x118>
    3200:	e59f11bc 	ldr	r1, [pc, #444]	; 33c4 <opfunc_pwr_sv+0x510>
    3204:	e3002594 	movw	r2, #1428	; 0x594
    3208:	e59f01fc 	ldr	r0, [pc, #508]	; 340c <opfunc_pwr_sv+0x558>
    320c:	ebfffffe 	bl	0 <osal_err_print>
    3210:	e3a00004 	mov	r0, #4
    3214:	ebfffffe 	bl	840 <wmt_core_rx_flush>
    3218:	e55b103c 	ldrb	r1, [fp, #-60]	; 0xffffffc4
    321c:	e55be03b 	ldrb	lr, [fp, #-59]	; 0xffffffc5
    3220:	e3002599 	movw	r2, #1433	; 0x599
    3224:	e55b6040 	ldrb	r6, [fp, #-64]	; 0xffffffc0
    3228:	e3a0c002 	mov	ip, #2
    322c:	e55b703f 	ldrb	r7, [fp, #-63]	; 0xffffffc1
    3230:	e55ba03e 	ldrb	sl, [fp, #-62]	; 0xffffffc2
    3234:	e55b903d 	ldrb	r9, [fp, #-61]	; 0xffffffc3
    3238:	e58d1010 	str	r1, [sp, #16]
    323c:	e51b3030 	ldr	r3, [fp, #-48]	; 0xffffffd0
    3240:	e59f117c 	ldr	r1, [pc, #380]	; 33c4 <opfunc_pwr_sv+0x510>
    3244:	e59f01c4 	ldr	r0, [pc, #452]	; 3410 <opfunc_pwr_sv+0x55c>
    3248:	e58de014 	str	lr, [sp, #20]
    324c:	e3a0e003 	mov	lr, #3
    3250:	e58d6000 	str	r6, [sp]
    3254:	e58de020 	str	lr, [sp, #32]
    3258:	e3a0e001 	mov	lr, #1
    325c:	e98d0480 	stmib	sp, {r7, sl}
    3260:	e58d900c 	str	r9, [sp, #12]
    3264:	e58d8018 	str	r8, [sp, #24]
    3268:	e58dc024 	str	ip, [sp, #36]	; 0x24
    326c:	e58de030 	str	lr, [sp, #48]	; 0x30
    3270:	e58dc01c 	str	ip, [sp, #28]
    3274:	e58d5028 	str	r5, [sp, #40]	; 0x28
    3278:	e58d502c 	str	r5, [sp, #44]	; 0x2c
    327c:	ebfffffe 	bl	0 <osal_err_print>
    3280:	ebfffffe 	bl	0 <mtk_wcn_stp_dbg_dump_package>
    3284:	e5942008 	ldr	r2, [r4, #8]
    3288:	eaffff4f 	b	2fcc <opfunc_pwr_sv+0x118>
    328c:	e1a02008 	mov	r2, r8
    3290:	e1a00007 	mov	r0, r7
    3294:	e3a01006 	mov	r1, #6
    3298:	ebfffffe 	bl	8b4 <wmt_core_rx>
    329c:	e2505000 	subs	r5, r0, #0
    32a0:	1a000002 	bne	32b0 <opfunc_pwr_sv+0x3fc>
    32a4:	e51b8030 	ldr	r8, [fp, #-48]	; 0xffffffd0
    32a8:	e3580006 	cmp	r8, #6
    32ac:	0affffc5 	beq	31c8 <opfunc_pwr_sv+0x314>
    32b0:	e3a00004 	mov	r0, #4
    32b4:	ebfffffe 	bl	840 <wmt_core_rx_flush>
    32b8:	e51bc030 	ldr	ip, [fp, #-48]	; 0xffffffd0
    32bc:	e59f1100 	ldr	r1, [pc, #256]	; 33c4 <opfunc_pwr_sv+0x510>
    32c0:	e30025d8 	movw	r2, #1496	; 0x5d8
    32c4:	e1a03005 	mov	r3, r5
    32c8:	e59f0144 	ldr	r0, [pc, #324]	; 3414 <opfunc_pwr_sv+0x560>
    32cc:	e58dc000 	str	ip, [sp]
    32d0:	eaffff86 	b	30f0 <opfunc_pwr_sv+0x23c>
    32d4:	e59f10e8 	ldr	r1, [pc, #232]	; 33c4 <opfunc_pwr_sv+0x510>
    32d8:	e30025b9 	movw	r2, #1465	; 0x5b9
    32dc:	e59f0134 	ldr	r0, [pc, #308]	; 3418 <opfunc_pwr_sv+0x564>
    32e0:	ebfffffe 	bl	0 <osal_err_print>
    32e4:	e3a00004 	mov	r0, #4
    32e8:	ebfffffe 	bl	840 <wmt_core_rx_flush>
    32ec:	e55b603d 	ldrb	r6, [fp, #-61]	; 0xffffffc3
    32f0:	e55b103c 	ldrb	r1, [fp, #-60]	; 0xffffffc4
    32f4:	e3a0c002 	mov	ip, #2
    32f8:	e55b7040 	ldrb	r7, [fp, #-64]	; 0xffffffc0
    32fc:	e30025be 	movw	r2, #1470	; 0x5be
    3300:	e55ba03f 	ldrb	sl, [fp, #-63]	; 0xffffffc1
    3304:	e55b903e 	ldrb	r9, [fp, #-62]	; 0xffffffc2
    3308:	e55be03b 	ldrb	lr, [fp, #-59]	; 0xffffffc5
    330c:	e58d600c 	str	r6, [sp, #12]
    3310:	e3a06003 	mov	r6, #3
    3314:	e58d1010 	str	r1, [sp, #16]
    3318:	e51b3030 	ldr	r3, [fp, #-48]	; 0xffffffd0
    331c:	e59f10a0 	ldr	r1, [pc, #160]	; 33c4 <opfunc_pwr_sv+0x510>
    3320:	e59f00e8 	ldr	r0, [pc, #232]	; 3410 <opfunc_pwr_sv+0x55c>
    3324:	e88d0480 	stm	sp, {r7, sl}
    3328:	e58d9008 	str	r9, [sp, #8]
    332c:	e58de014 	str	lr, [sp, #20]
    3330:	e58d8018 	str	r8, [sp, #24]
    3334:	e58dc024 	str	ip, [sp, #36]	; 0x24
    3338:	e58d6030 	str	r6, [sp, #48]	; 0x30
    333c:	e58dc01c 	str	ip, [sp, #28]
    3340:	e58d6020 	str	r6, [sp, #32]
    3344:	eaffffca 	b	3274 <opfunc_pwr_sv+0x3c0>
    3348:	e59f1074 	ldr	r1, [pc, #116]	; 33c4 <opfunc_pwr_sv+0x510>
    334c:	e30025df 	movw	r2, #1503	; 0x5df
    3350:	e59f00c4 	ldr	r0, [pc, #196]	; 341c <opfunc_pwr_sv+0x568>
    3354:	ebfffffe 	bl	0 <osal_err_print>
    3358:	e3a00004 	mov	r0, #4
    335c:	ebfffffe 	bl	840 <wmt_core_rx_flush>
    3360:	e55b303c 	ldrb	r3, [fp, #-60]	; 0xffffffc4
    3364:	e55be03b 	ldrb	lr, [fp, #-59]	; 0xffffffc5
    3368:	e3a0c002 	mov	ip, #2
    336c:	e55b6040 	ldrb	r6, [fp, #-64]	; 0xffffffc0
    3370:	e30025e4 	movw	r2, #1508	; 0x5e4
    3374:	e55b703f 	ldrb	r7, [fp, #-63]	; 0xffffffc1
    3378:	e55ba03e 	ldrb	sl, [fp, #-62]	; 0xffffffc2
    337c:	e55b903d 	ldrb	r9, [fp, #-61]	; 0xffffffc3
    3380:	e58d3010 	str	r3, [sp, #16]
    3384:	e58de014 	str	lr, [sp, #20]
    3388:	e3a0e003 	mov	lr, #3
    338c:	e59f1030 	ldr	r1, [pc, #48]	; 33c4 <opfunc_pwr_sv+0x510>
    3390:	e51b3030 	ldr	r3, [fp, #-48]	; 0xffffffd0
    3394:	e59f0074 	ldr	r0, [pc, #116]	; 3410 <opfunc_pwr_sv+0x55c>
    3398:	e88d04c0 	stm	sp, {r6, r7, sl}
    339c:	e58d900c 	str	r9, [sp, #12]
    33a0:	e58d8018 	str	r8, [sp, #24]
    33a4:	e58de020 	str	lr, [sp, #32]
    33a8:	e58dc030 	str	ip, [sp, #48]	; 0x30
    33ac:	e58dc01c 	str	ip, [sp, #28]
    33b0:	e58dc024 	str	ip, [sp, #36]	; 0x24
    33b4:	eaffffae 	b	3274 <opfunc_pwr_sv+0x3c0>
    33b8:	00000000 	andeq	r0, r0, r0
    33bc:	000002b4 			; <UNDEFINED> instruction: 0x000002b4
    33c0:	000019b0 			; <UNDEFINED> instruction: 0x000019b0
    33c4:	000002a4 	andeq	r0, r0, r4, lsr #5
    33c8:	000002c4 	andeq	r0, r0, r4, asr #5
    33cc:	00001b28 	andeq	r1, r0, r8, lsr #22
    33d0:	00001988 	andeq	r1, r0, r8, lsl #19
    33d4:	00001d34 	andeq	r1, r0, r4, lsr sp
    33d8:	00001d54 	andeq	r1, r0, r4, asr sp
    33dc:	00001b00 	andeq	r1, r0, r0, lsl #22
    33e0:	000002d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
    33e4:	00001c3c 	andeq	r1, r0, ip, lsr ip
    33e8:	000019f4 	strdeq	r1, [r0], -r4
    33ec:	00001b6c 	andeq	r1, r0, ip, ror #22
    33f0:	000002bc 			; <UNDEFINED> instruction: 0x000002bc
    33f4:	00001ad8 	ldrdeq	r1, [r0], -r8
    33f8:	000002c8 	andeq	r0, r0, r8, asr #5
    33fc:	00001be8 	andeq	r1, r0, r8, ror #23
    3400:	00001c10 	andeq	r1, r0, r0, lsl ip
    3404:	000002d8 	ldrdeq	r0, [r0], -r8
    3408:	00001d08 	andeq	r1, r0, r8, lsl #26
    340c:	00001a34 	andeq	r1, r0, r4, lsr sl
    3410:	00001a6c 	andeq	r1, r0, ip, ror #20
    3414:	00001c84 	andeq	r1, r0, r4, lsl #25
    3418:	00001bac 	andeq	r1, r0, ip, lsr #23
    341c:	00001cc8 	andeq	r1, r0, r8, asr #25

00003420 <wmt_core_func_ctrl_cmd>:
    3420:	e1a0c00d 	mov	ip, sp
    3424:	e92dd8f0 	push	{r4, r5, r6, r7, fp, ip, lr, pc}
    3428:	e24cb004 	sub	fp, ip, #4
    342c:	e24dd058 	sub	sp, sp, #88	; 0x58
    3430:	e24b7048 	sub	r7, fp, #72	; 0x48
    3434:	e1a05000 	mov	r5, r0
    3438:	e1a06001 	mov	r6, r1
    343c:	e3a02024 	mov	r2, #36	; 0x24
    3440:	e3a01000 	mov	r1, #0
    3444:	e1a00007 	mov	r0, r7
    3448:	e24b406c 	sub	r4, fp, #108	; 0x6c
    344c:	ebfffffe 	bl	0 <osal_memset>
    3450:	e3a01000 	mov	r1, #0
    3454:	e3a02024 	mov	r2, #36	; 0x24
    3458:	e1a00004 	mov	r0, r4
    345c:	e3560001 	cmp	r6, #1
    3460:	13a06000 	movne	r6, #0
    3464:	03a06001 	moveq	r6, #1
    3468:	ebfffffe 	bl	0 <osal_memset>
    346c:	e3a0c006 	mov	ip, #6
    3470:	e1a0100c 	mov	r1, ip
    3474:	e3a03000 	mov	r3, #0
    3478:	e1a00007 	mov	r0, r7
    347c:	e24b2024 	sub	r2, fp, #36	; 0x24
    3480:	e3a0e002 	mov	lr, #2
    3484:	e54bc047 	strb	ip, [fp, #-71]	; 0xffffffb9
    3488:	e54b5044 	strb	r5, [fp, #-68]	; 0xffffffbc
    348c:	e3a0c001 	mov	ip, #1
    3490:	e54b6043 	strb	r6, [fp, #-67]	; 0xffffffbd
    3494:	e14be4b6 	strh	lr, [fp, #-70]	; 0xffffffba
    3498:	e54bc048 	strb	ip, [fp, #-72]	; 0xffffffb8
    349c:	ebfffffe 	bl	10e4 <wmt_core_tx>
    34a0:	e2503000 	subs	r3, r0, #0
    34a4:	0a00000b 	beq	34d8 <wmt_core_func_ctrl_cmd+0xb8>
    34a8:	e59f10e8 	ldr	r1, [pc, #232]	; 3598 <wmt_core_func_ctrl_cmd+0x178>
    34ac:	e30021ce 	movw	r2, #462	; 0x1ce
    34b0:	e59f00e4 	ldr	r0, [pc, #228]	; 359c <wmt_core_func_ctrl_cmd+0x17c>
    34b4:	ebfffffe 	bl	0 <osal_err_print>
    34b8:	e59f00e0 	ldr	r0, [pc, #224]	; 35a0 <wmt_core_func_ctrl_cmd+0x180>
    34bc:	e3a02f7e 	mov	r2, #504	; 0x1f8
    34c0:	e59f10d0 	ldr	r1, [pc, #208]	; 3598 <wmt_core_func_ctrl_cmd+0x178>
    34c4:	e55b3044 	ldrb	r3, [fp, #-68]	; 0xffffffbc
    34c8:	ebfffffe 	bl	0 <osal_err_print>
    34cc:	e3e00001 	mvn	r0, #1
    34d0:	e24bd01c 	sub	sp, fp, #28
    34d4:	e89da8f0 	ldm	sp, {r4, r5, r6, r7, fp, sp, pc}
    34d8:	e1a00004 	mov	r0, r4
    34dc:	e3a01005 	mov	r1, #5
    34e0:	e24b2020 	sub	r2, fp, #32
    34e4:	ebfffffe 	bl	8b4 <wmt_core_rx>
    34e8:	e2503000 	subs	r3, r0, #0
    34ec:	1a000011 	bne	3538 <wmt_core_func_ctrl_cmd+0x118>
    34f0:	e55b306c 	ldrb	r3, [fp, #-108]	; 0xffffff94
    34f4:	e3530002 	cmp	r3, #2
    34f8:	0a000004 	beq	3510 <wmt_core_func_ctrl_cmd+0xf0>
    34fc:	e59f1094 	ldr	r1, [pc, #148]	; 3598 <wmt_core_func_ctrl_cmd+0x178>
    3500:	e30021da 	movw	r2, #474	; 0x1da
    3504:	e59f0098 	ldr	r0, [pc, #152]	; 35a4 <wmt_core_func_ctrl_cmd+0x184>
    3508:	ebfffffe 	bl	0 <osal_err_print>
    350c:	eaffffe9 	b	34b8 <wmt_core_func_ctrl_cmd+0x98>
    3510:	e55b3047 	ldrb	r3, [fp, #-71]	; 0xffffffb9
    3514:	e55bc06b 	ldrb	ip, [fp, #-107]	; 0xffffff95
    3518:	e153000c 	cmp	r3, ip
    351c:	0a00000a 	beq	354c <wmt_core_func_ctrl_cmd+0x12c>
    3520:	e59f1070 	ldr	r1, [pc, #112]	; 3598 <wmt_core_func_ctrl_cmd+0x178>
    3524:	e3a02e1e 	mov	r2, #480	; 0x1e0
    3528:	e59f0078 	ldr	r0, [pc, #120]	; 35a8 <wmt_core_func_ctrl_cmd+0x188>
    352c:	e58dc000 	str	ip, [sp]
    3530:	ebfffffe 	bl	0 <osal_err_print>
    3534:	eaffffdf 	b	34b8 <wmt_core_func_ctrl_cmd+0x98>
    3538:	e59f1058 	ldr	r1, [pc, #88]	; 3598 <wmt_core_func_ctrl_cmd+0x178>
    353c:	e3a02f75 	mov	r2, #468	; 0x1d4
    3540:	e59f0064 	ldr	r0, [pc, #100]	; 35ac <wmt_core_func_ctrl_cmd+0x18c>
    3544:	ebfffffe 	bl	0 <osal_err_print>
    3548:	eaffffda 	b	34b8 <wmt_core_func_ctrl_cmd+0x98>
    354c:	e15bc6ba 	ldrh	ip, [fp, #-106]	; 0xffffff96
    3550:	e35c0001 	cmp	ip, #1
    3554:	0a000006 	beq	3574 <wmt_core_func_ctrl_cmd+0x154>
    3558:	e59f1038 	ldr	r1, [pc, #56]	; 3598 <wmt_core_func_ctrl_cmd+0x178>
    355c:	e30021e6 	movw	r2, #486	; 0x1e6
    3560:	e3a03005 	mov	r3, #5
    3564:	e59f0044 	ldr	r0, [pc, #68]	; 35b0 <wmt_core_func_ctrl_cmd+0x190>
    3568:	e58dc000 	str	ip, [sp]
    356c:	ebfffffe 	bl	0 <osal_err_print>
    3570:	eaffffd0 	b	34b8 <wmt_core_func_ctrl_cmd+0x98>
    3574:	e55b0068 	ldrb	r0, [fp, #-104]	; 0xffffff98
    3578:	e3500000 	cmp	r0, #0
    357c:	0affffd3 	beq	34d0 <wmt_core_func_ctrl_cmd+0xb0>
    3580:	e1a03000 	mov	r3, r0
    3584:	e59f100c 	ldr	r1, [pc, #12]	; 3598 <wmt_core_func_ctrl_cmd+0x178>
    3588:	e3a02f7b 	mov	r2, #492	; 0x1ec
    358c:	e59f0020 	ldr	r0, [pc, #32]	; 35b4 <wmt_core_func_ctrl_cmd+0x194>
    3590:	ebfffffe 	bl	0 <osal_err_print>
    3594:	eaffffc7 	b	34b8 <wmt_core_func_ctrl_cmd+0x98>
    3598:	000002e0 	andeq	r0, r0, r0, ror #5
    359c:	00001db4 			; <UNDEFINED> instruction: 0x00001db4
    35a0:	00001f00 	andeq	r1, r0, r0, lsl #30
    35a4:	00001e0c 	andeq	r1, r0, ip, lsl #28
    35a8:	00001e48 	andeq	r1, r0, r8, asr #28
    35ac:	00001de0 	andeq	r1, r0, r0, ror #27
    35b0:	00001e90 	muleq	r0, r0, lr
    35b4:	00001edc 	ldrdeq	r1, [r0], -ip

Disassembly of section .data:

00000000 <gpWmtFuncOps>:
	...

00000010 <WMT_SET_REG_CMD>:
  10:	00100801 	andseq	r0, r0, r1, lsl #16
  14:	01000100 	mrseq	r0, (UNDEF: 16)
	...
  20:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff

00000024 <WMT_EFUSE_CMD>:
  24:	00080d01 	andeq	r0, r8, r1, lsl #26
  28:	aaaa0101 	bge	fea80434 <wmt_core_func_ctrl_cmd+0xfea7d014>
  2c:	bbbbbbbb 	bllt	feeeef20 <wmt_core_func_ctrl_cmd+0xfeeebb00>

00000030 <WMT_THERM_CMD>:
  30:	00011101 	andeq	r1, r1, r1, lsl #2
  34:	00000000 	andeq	r0, r0, r0

00000038 <WMT_THERM_CTRL_EVT>:
  38:	00011102 	andeq	r1, r1, r2, lsl #2
  3c:	00000000 	andeq	r0, r0, r0

00000040 <WMT_THERM_READ_EVT>:
  40:	00021102 	andeq	r1, r2, r2, lsl #2
  44:	00000000 	andeq	r0, r0, r0

00000048 <WMT_DSNS_CMD>:
  48:	00020e01 	andeq	r0, r2, r1, lsl #28
  4c:	00000001 	andeq	r0, r0, r1

00000050 <WMT_DSNS_EVT>:
  50:	00010e02 	andeq	r0, r1, r2, lsl #28
  54:	00000000 	andeq	r0, r0, r0

Disassembly of section .bss:

00000000 <gMtkWmtCtx>:
	...

00000054 <gLpbkBuf>:
	...

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	25011101 	strcs	r1, [r1, #-257]	; 0xfffffeff
   4:	030b130e 	movweq	r1, #45838	; 0xb30e
   8:	110e1b0e 	tstne	lr, lr, lsl #22
   c:	10011201 	andne	r1, r1, r1, lsl #4
  10:	02000006 	andeq	r0, r0, #6
  14:	0e030016 	mcreq	0, 0, r0, cr3, cr6, {0}
  18:	0b3b0b3a 	bleq	ec2d08 <wmt_core_func_ctrl_cmd+0xebf8e8>
  1c:	00001349 	andeq	r1, r0, r9, asr #6
  20:	0b002403 	bleq	9034 <wmt_core_func_ctrl_cmd+0x5c14>
  24:	030b3e0b 	movweq	r3, #48651	; 0xbe0b
  28:	0400000e 	streq	r0, [r0], #-14
  2c:	0b0b000f 	bleq	2c0070 <wmt_core_func_ctrl_cmd+0x2bcc50>
  30:	00001349 	andeq	r1, r0, r9, asr #6
  34:	0b002405 	bleq	9050 <wmt_core_func_ctrl_cmd+0x5c30>
  38:	030b3e0b 	movweq	r3, #48651	; 0xbe0b
  3c:	06000008 	streq	r0, [r0], -r8
  40:	13490101 	movtne	r0, #37121	; 0x9101
  44:	00001301 	andeq	r1, r0, r1, lsl #6
  48:	49002107 	stmdbmi	r0, {r0, r1, r2, r8, sp}
  4c:	000b2f13 	andeq	r2, fp, r3, lsl pc
  50:	00240800 	eoreq	r0, r4, r0, lsl #16
  54:	0b3e0b0b 	bleq	f82c88 <wmt_core_func_ctrl_cmd+0xf7f868>
  58:	26090000 	strcs	r0, [r9], -r0
  5c:	00134900 	andseq	r4, r3, r0, lsl #18
  60:	01130a00 	tsteq	r3, r0, lsl #20
  64:	0b0b0e03 	bleq	2c3878 <wmt_core_func_ctrl_cmd+0x2c0458>
  68:	0b3b0b3a 	bleq	ec2d58 <wmt_core_func_ctrl_cmd+0xebf938>
  6c:	00001301 	andeq	r1, r0, r1, lsl #6
  70:	03000d0b 	movweq	r0, #3339	; 0xd0b
  74:	3b0b3a0e 	blcc	2ce8b4 <wmt_core_func_ctrl_cmd+0x2cb494>
  78:	3813490b 	ldmdacc	r3, {r0, r1, r3, r8, fp, lr}
  7c:	0c00000a 	stceq	0, cr0, [r0], {10}
  80:	0e030104 	adfeqs	f0, f3, f4
  84:	0b3a0b0b 	bleq	e82cb8 <wmt_core_func_ctrl_cmd+0xe7f898>
  88:	13010b3b 	movwne	r0, #6971	; 0x1b3b
  8c:	280d0000 	stmdacs	sp, {}	; <UNPREDICTABLE>
  90:	1c0e0300 	stcne	3, cr0, [lr], {-0}
  94:	0e00000d 	cdpeq	0, 0, cr0, cr0, cr13, {0}
  98:	0b0b0104 	bleq	2c04b0 <wmt_core_func_ctrl_cmd+0x2bd090>
  9c:	0b3b0b3a 	bleq	ec2d8c <wmt_core_func_ctrl_cmd+0xebf96c>
  a0:	00001301 	andeq	r1, r0, r1, lsl #6
  a4:	2701150f 	strcs	r1, [r1, -pc, lsl #10]
  a8:	0113490c 	tsteq	r3, ip, lsl #18
  ac:	10000013 	andne	r0, r0, r3, lsl r0
  b0:	13490005 	movtne	r0, #36869	; 0x9005
  b4:	0d110000 	ldceq	0, cr0, [r1, #-0]
  b8:	3a0e0300 	bcc	380cc0 <wmt_core_func_ctrl_cmd+0x37d8a0>
  bc:	49053b0b 	stmdbmi	r5, {r0, r1, r3, r8, r9, fp, ip, sp}
  c0:	000a3813 	andeq	r3, sl, r3, lsl r8
  c4:	00161200 	andseq	r1, r6, r0, lsl #4
  c8:	0b3a0e03 	bleq	e838dc <wmt_core_func_ctrl_cmd+0xe804bc>
  cc:	1349053b 	movtne	r0, #38203	; 0x953b
  d0:	04130000 	ldreq	r0, [r3], #-0
  d4:	0b0e0301 	bleq	380ce0 <wmt_core_func_ctrl_cmd+0x37d8c0>
  d8:	3b0b3a0b 	blcc	2ce90c <wmt_core_func_ctrl_cmd+0x2cb4ec>
  dc:	00130105 	andseq	r0, r3, r5, lsl #2
  e0:	00151400 	andseq	r1, r5, r0, lsl #8
  e4:	13490c27 	movtne	r0, #39975	; 0x9c27
  e8:	13150000 	tstne	r5, #0
  ec:	0b0e0301 	bleq	380cf8 <wmt_core_func_ctrl_cmd+0x37d8d8>
  f0:	3b0b3a0b 	blcc	2ce924 <wmt_core_func_ctrl_cmd+0x2cb504>
  f4:	00130105 	andseq	r0, r3, r5, lsl #2
  f8:	01041600 	tsteq	r4, r0, lsl #12
  fc:	0b3a0b0b 	bleq	e82d30 <wmt_core_func_ctrl_cmd+0xe7f910>
 100:	1301053b 	movwne	r0, #5435	; 0x153b
 104:	0d170000 	ldceq	0, cr0, [r7, #-0]
 108:	3a080300 	bcc	200d10 <wmt_core_func_ctrl_cmd+0x1fd8f0>
 10c:	49053b0b 	stmdbmi	r5, {r0, r1, r3, r8, r9, fp, ip, sp}
 110:	000a3813 	andeq	r3, sl, r3, lsl r8
 114:	012e1800 	teqeq	lr, r0, lsl #16
 118:	0b3a0e03 	bleq	e8392c <wmt_core_func_ctrl_cmd+0xe8050c>
 11c:	0c27053b 	cfstr32eq	mvfx0, [r7], #-236	; 0xffffff14
 120:	13010b20 	movwne	r0, #6944	; 0x1b20
 124:	05190000 	ldreq	r0, [r9, #-0]
 128:	3a0e0300 	bcc	380d30 <wmt_core_func_ctrl_cmd+0x37d910>
 12c:	49053b0b 	stmdbmi	r5, {r0, r1, r3, r8, r9, fp, ip, sp}
 130:	1a000013 	bne	184 <.debug_abbrev+0x184>
 134:	0e030034 	mcreq	0, 0, r0, cr3, cr4, {1}
 138:	0c341349 	ldceq	3, cr1, [r4], #-292	; 0xfffffedc
 13c:	00000e1c 	andeq	r0, r0, ip, lsl lr
 140:	03012e1b 	movweq	r2, #7707	; 0x1e1b
 144:	3b0b3a0e 	blcc	2ce984 <wmt_core_func_ctrl_cmd+0x2cb564>
 148:	490c2705 	stmdbmi	ip, {r0, r2, r8, r9, sl, sp}
 14c:	010b2013 	tsteq	fp, r3, lsl r0
 150:	1c000013 	stcne	0, cr0, [r0], {19}
 154:	0e030034 	mcreq	0, 0, r0, cr3, cr4, {1}
 158:	053b0b3a 	ldreq	r0, [fp, #-2874]!	; 0xfffff4c6
 15c:	00001349 	andeq	r1, r0, r9, asr #6
 160:	03012e1d 	movweq	r2, #7709	; 0x1e1d
 164:	3b0b3a0e 	blcc	2ce9a4 <wmt_core_func_ctrl_cmd+0x2cb584>
 168:	490c2705 	stmdbmi	ip, {r0, r2, r8, r9, sl, sp}
 16c:	12011113 	andne	r1, r1, #-1073741820	; 0xc0000004
 170:	01064001 	tsteq	r6, r1
 174:	1e000013 	mcrne	0, 0, r0, cr0, cr3, {0}
 178:	0e030005 	cdpeq	0, 0, cr0, cr3, cr5, {0}
 17c:	053b0b3a 	ldreq	r0, [fp, #-2874]!	; 0xfffff4c6
 180:	06021349 	streq	r1, [r2], -r9, asr #6
 184:	2e1f0000 	cdpcs	0, 1, cr0, cr15, cr0, {0}
 188:	030c3f01 	movweq	r3, #52993	; 0xcf01
 18c:	3b0b3a0e 	blcc	2ce9cc <wmt_core_func_ctrl_cmd+0x2cb5ac>
 190:	490c2705 	stmdbmi	ip, {r0, r2, r8, r9, sl, sp}
 194:	12011113 	andne	r1, r1, #-1073741820	; 0xc0000004
 198:	01064001 	tsteq	r6, r1
 19c:	20000013 	andcs	r0, r0, r3, lsl r0
 1a0:	0e030034 	mcreq	0, 0, r0, cr3, cr4, {1}
 1a4:	0c341349 	ldceq	3, cr1, [r4], #-292	; 0xfffffedc
 1a8:	00000a02 	andeq	r0, r0, r2, lsl #20
 1ac:	03003421 	movweq	r3, #1057	; 0x421
 1b0:	3b0b3a0e 	blcc	2ce9f0 <wmt_core_func_ctrl_cmd+0x2cb5d0>
 1b4:	02134905 	andseq	r4, r3, #81920	; 0x14000
 1b8:	22000006 	andcs	r0, r0, #6
 1bc:	08030034 	stmdaeq	r3, {r2, r4, r5}
 1c0:	053b0b3a 	ldreq	r0, [fp, #-2874]!	; 0xfffff4c6
 1c4:	06021349 	streq	r1, [r2], -r9, asr #6
 1c8:	2e230000 	cdpcs	0, 2, cr0, cr3, cr0, {0}
 1cc:	030c3f00 	movweq	r3, #52992	; 0xcf00
 1d0:	3b0b3a0e 	blcc	2cea10 <wmt_core_func_ctrl_cmd+0x2cb5f0>
 1d4:	490c2705 	stmdbmi	ip, {r0, r2, r8, r9, sl, sp}
 1d8:	12011113 	andne	r1, r1, #-1073741820	; 0xc0000004
 1dc:	00064001 	andeq	r4, r6, r1
 1e0:	00342400 	eorseq	r2, r4, r0, lsl #8
 1e4:	0b3a0803 	bleq	e821f8 <wmt_core_func_ctrl_cmd+0xe7edd8>
 1e8:	1349053b 	movtne	r0, #38203	; 0x953b
 1ec:	2e250000 	cdpcs	0, 2, cr0, cr5, cr0, {0}
 1f0:	030c3f01 	movweq	r3, #52993	; 0xcf01
 1f4:	3b0b3a0e 	blcc	2cea34 <wmt_core_func_ctrl_cmd+0x2cb614>
 1f8:	110c2705 	tstne	ip, r5, lsl #14
 1fc:	40011201 	andmi	r1, r1, r1, lsl #4
 200:	00130106 	andseq	r0, r3, r6, lsl #2
 204:	00052600 	andeq	r2, r5, r0, lsl #12
 208:	0b3a0803 	bleq	e8221c <wmt_core_func_ctrl_cmd+0xe7edfc>
 20c:	1349053b 	movtne	r0, #38203	; 0x953b
 210:	00000602 	andeq	r0, r0, r2, lsl #12
 214:	03003427 	movweq	r3, #1063	; 0x427
 218:	3b0b3a08 	blcc	2cea40 <wmt_core_func_ctrl_cmd+0x2cb620>
 21c:	02134905 	andseq	r4, r3, #81920	; 0x14000
 220:	2800000a 	stmdacs	r0, {r1, r3}
 224:	0e030034 	mcreq	0, 0, r0, cr3, cr4, {1}
 228:	053b0b3a 	ldreq	r0, [fp, #-2874]!	; 0xfffff4c6
 22c:	0a021349 	beq	84f58 <wmt_core_func_ctrl_cmd+0x81b38>
 230:	1d290000 	stcne	0, cr0, [r9, #-0]
 234:	11133101 	tstne	r3, r1, lsl #2
 238:	58011201 	stmdapl	r1, {r0, r9, ip}
 23c:	0105590b 	tsteq	r5, fp, lsl #18
 240:	2a000013 	bcs	294 <.debug_abbrev+0x294>
 244:	13310005 	teqne	r1, #5
 248:	0b2b0000 	bleq	ac0250 <wmt_core_func_ctrl_cmd+0xabce30>
 24c:	12011101 	andne	r1, r1, #1073741824	; 0x40000000
 250:	2c000001 	stccs	0, cr0, [r0], {1}
 254:	13310034 	teqne	r1, #52	; 0x34
 258:	00000a02 	andeq	r0, r0, r2, lsl #20
 25c:	31011d2d 	tstcc	r1, sp, lsr #26
 260:	12011113 	andne	r1, r1, #-1073741820	; 0xc0000004
 264:	590b5801 	stmdbpl	fp, {r0, fp, ip, lr}
 268:	2e000005 	cdpcs	0, 0, cr0, cr0, cr5, {0}
 26c:	0e03000a 	cdpeq	0, 0, cr0, cr3, cr10, {0}
 270:	053b0b3a 	ldreq	r0, [fp, #-2874]!	; 0xfffff4c6
 274:	00000111 	andeq	r0, r0, r1, lsl r1
 278:	55010b2f 	strpl	r0, [r1, #-2863]	; 0xfffff4d1
 27c:	30000006 	andcc	r0, r0, r6
 280:	1331011d 	teqne	r1, #1073741831	; 0x40000007
 284:	06550152 			; <UNDEFINED> instruction: 0x06550152
 288:	05590b58 	ldrbeq	r0, [r9, #-2904]	; 0xfffff4a8
 28c:	34310000 	ldrtcc	r0, [r1], #-0
 290:	02133100 	andseq	r3, r3, #0, 2
 294:	32000006 	andcc	r0, r0, #6
 298:	0e03000a 	cdpeq	0, 0, cr0, cr3, cr10, {0}
 29c:	053b0b3a 	ldreq	r0, [fp, #-2874]!	; 0xfffff4c6
 2a0:	34330000 	ldrtcc	r0, [r3], #-0
 2a4:	3a0e0300 	bcc	380eac <wmt_core_func_ctrl_cmd+0x37da8c>
 2a8:	490b3b0b 	stmdbmi	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
 2ac:	000a0213 	andeq	r0, sl, r3, lsl r2
 2b0:	00213400 	eoreq	r3, r1, r0, lsl #8
 2b4:	052f1349 	streq	r1, [pc, #-841]!	; ffffff73 <wmt_core_func_ctrl_cmd+0xffffcb53>
 2b8:	34350000 	ldrtcc	r0, [r5], #-0
 2bc:	3a0e0300 	bcc	380ec4 <wmt_core_func_ctrl_cmd+0x37daa4>
 2c0:	490b3b0b 	stmdbmi	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
 2c4:	36000013 			; <UNDEFINED> instruction: 0x36000013
 2c8:	0e030034 	mcreq	0, 0, r0, cr3, cr4, {1}
 2cc:	0b3b0b3a 	bleq	ec2fbc <wmt_core_func_ctrl_cmd+0xebfb9c>
 2d0:	0c3f1349 	ldceq	3, cr1, [pc], #-292	; 1b4 <.debug_abbrev+0x1b4>
 2d4:	00000c3c 	andeq	r0, r0, ip, lsr ip
 2d8:	03003437 	movweq	r3, #1079	; 0x437
 2dc:	3b0b3a0e 	blcc	2ceb1c <wmt_core_func_ctrl_cmd+0x2cb6fc>
 2e0:	3f13490b 	svccc	0x0013490b
 2e4:	000a020c 	andeq	r0, sl, ip, lsl #4
	...

Disassembly of section .debug_info:

00000000 <.debug_info>:
       0:	00001f1f 	andeq	r1, r0, pc, lsl pc
       4:	00000002 	andeq	r0, r0, r2
       8:	01040000 	mrseq	r0, (UNDEF: 4)
       c:	000009b5 			; <UNDEFINED> instruction: 0x000009b5
      10:	000d0a01 	andeq	r0, sp, r1, lsl #20
      14:	00127200 	andseq	r7, r2, r0, lsl #4
      18:	00000000 	andeq	r0, r0, r0
      1c:	0035b800 	eorseq	fp, r5, r0, lsl #16
      20:	00000000 	andeq	r0, r0, r0
      24:	0b8a0200 	bleq	fe280808 <wmt_core_func_ctrl_cmd+0xfe27d3e8>
      28:	32020000 	andcc	r0, r2, #0
      2c:	00000030 	andeq	r0, r0, r0, lsr r0
      30:	39080103 	stmdbcc	r8, {r0, r1, r8}
      34:	03000005 	movweq	r0, #5
      38:	03e30601 	mvneq	r0, #1048576	; 0x100000
      3c:	8e020000 	cdphi	0, 0, cr0, cr2, cr0, {0}
      40:	0200000f 	andeq	r0, r0, #15
      44:	00004936 	andeq	r4, r0, r6, lsr r9
      48:	08010300 	stmdaeq	r1, {r8, r9}
      4c:	00000453 	andeq	r0, r0, r3, asr r4
      50:	00041c02 	andeq	r1, r4, r2, lsl #24
      54:	5b370200 	blpl	dc085c <wmt_core_func_ctrl_cmd+0xdbd43c>
      58:	04000000 	streq	r0, [r0], #-0
      5c:	00004904 	andeq	r4, r0, r4, lsl #18
      60:	12f60200 	rscsne	r0, r6, #0, 4
      64:	38020000 	stmdacc	r2, {}	; <UNPREDICTABLE>
      68:	00000049 	andeq	r0, r0, r9, asr #32
      6c:	15050203 	strne	r0, [r5, #-515]	; 0xfffffdfd
      70:	02000010 	andeq	r0, r0, #16
      74:	000007a4 	andeq	r0, r0, r4, lsr #15
      78:	007e3d02 	rsbseq	r3, lr, r2, lsl #26
      7c:	02030000 	andeq	r0, r3, #0
      80:	00130c07 	andseq	r0, r3, r7, lsl #24
      84:	05040300 	streq	r0, [r4, #-768]	; 0xfffffd00
      88:	000002dc 	ldrdeq	r0, [r0], -ip
      8c:	00057d02 	andeq	r7, r5, r2, lsl #26
      90:	97430200 	strbls	r0, [r3, -r0, lsl #4]
      94:	05000000 	streq	r0, [r0, #-0]
      98:	6e690504 	cdpvs	5, 6, cr0, cr9, cr4, {0}
      9c:	fa020074 	blx	801d8 <wmt_core_func_ctrl_cmd+0x7cdb8>
      a0:	02000008 	andeq	r0, r0, #8
      a4:	0000a945 	andeq	sl, r0, r5, asr #18
      a8:	07040300 	streq	r0, [r4, -r0, lsl #6]
      ac:	00000b17 	andeq	r0, r0, r7, lsl fp
      b0:	0010b602 	andseq	fp, r0, r2, lsl #12
      b4:	bb460200 	bllt	11808bc <wmt_core_func_ctrl_cmd+0x117d49c>
      b8:	04000000 	streq	r0, [r0], #-0
      bc:	0000a904 	andeq	sl, r0, r4, lsl #18
      c0:	07040300 	streq	r0, [r4, -r0, lsl #6]
      c4:	00000855 	andeq	r0, r0, r5, asr r8
      c8:	0007df02 	andeq	sp, r7, r2, lsl #30
      cc:	974b0200 	strbls	r0, [fp, -r0, lsl #4]
      d0:	06000000 	streq	r0, [r0], -r0
      d4:	00000030 	andeq	r0, r0, r0, lsr r0
      d8:	000000e3 	andeq	r0, r0, r3, ror #1
      dc:	0000e307 	andeq	lr, r0, r7, lsl #6
      e0:	08000f00 	stmdaeq	r0, {r8, r9, sl, fp}
      e4:	04040704 	streq	r0, [r4], #-1796	; 0xfffff8fc
      e8:	0000003e 	andeq	r0, r0, lr, lsr r0
      ec:	00f20404 	rscseq	r0, r2, r4, lsl #8
      f0:	3e090000 	cdpcc	0, 0, cr0, cr9, cr0, {0}
      f4:	0a000000 	beq	fc <.debug_info+0xfc>
      f8:	0000121d 	andeq	r1, r0, sp, lsl r2
      fc:	2ef20388 	cdpcs	3, 15, cr0, cr2, cr8, {4}
     100:	0b000001 	bleq	10c <.debug_info+0x10c>
     104:	000002d7 	ldrdeq	r0, [r0], -r7
     108:	009ef303 	addseq	pc, lr, r3, lsl #6
     10c:	23020000 	movwcs	r0, #8192	; 0x2000
     110:	0c270b00 	stceq	11, cr0, [r7], #-0
     114:	f4030000 	vst4.8	{d0-d3}, [r3], r0
     118:	0000009e 	muleq	r0, lr, r0
     11c:	0b042302 	bleq	108d2c <wmt_core_func_ctrl_cmd+0x10590c>
     120:	00000f9d 	muleq	r0, sp, pc	; <UNPREDICTABLE>
     124:	012ef503 	msreq	CPSR_fsx, r3, lsl #10
     128:	23020000 	movwcs	r0, #8192	; 0x2000
     12c:	9e060008 	cdpls	0, 0, cr0, cr6, cr8, {0}
     130:	3e000000 	cdpcc	0, 0, cr0, cr0, cr0, {0}
     134:	07000001 	streq	r0, [r0, -r1]
     138:	000000e3 	andeq	r0, r0, r3, ror #1
     13c:	0e02001f 	mcreq	0, 0, r0, cr2, cr15, {0}
     140:	03000004 	movweq	r0, #4
     144:	000149f6 	strdeq	r4, [r1], -r6
     148:	f7040400 			; <UNDEFINED> instruction: 0xf7040400
     14c:	06000000 	streq	r0, [r0], -r0
     150:	0000003e 	andeq	r0, r0, lr, lsr r0
     154:	0000015f 	andeq	r0, r0, pc, asr r1
     158:	0000e307 	andeq	lr, r0, r7, lsl #6
     15c:	0a000f00 	beq	3d64 <wmt_core_func_ctrl_cmd+0x944>
     160:	00000c78 	andeq	r0, r0, r8, ror ip
     164:	887d0444 	ldmdahi	sp!, {r2, r6, sl}^
     168:	0b000001 	bleq	174 <.debug_info+0x174>
     16c:	0000097d 	andeq	r0, r0, sp, ror r9
     170:	009e7e04 	addseq	r7, lr, r4, lsl #28
     174:	23020000 	movwcs	r0, #8192	; 0x2000
     178:	13990b00 	orrsne	r0, r9, #0, 22
     17c:	7f040000 	svcvc	0x00040000
     180:	00000188 	andeq	r0, r0, r8, lsl #3
     184:	00042302 	andeq	r2, r4, r2, lsl #6
     188:	00009e06 	andeq	r9, r0, r6, lsl #28
     18c:	00019800 	andeq	r9, r1, r0, lsl #16
     190:	00e30700 	rsceq	r0, r3, r0, lsl #14
     194:	000f0000 	andeq	r0, pc, r0
     198:	00026b02 	andeq	r6, r2, r2, lsl #22
     19c:	5f800400 	svcpl	0x00800400
     1a0:	0c000001 	stceq	0, cr0, [r0], {1}
     1a4:	000008a2 	andeq	r0, r0, r2, lsr #17
     1a8:	46820404 	strmi	r0, [r2], r4, lsl #8
     1ac:	0d000002 	stceq	0, cr0, [r0, #-8]
     1b0:	000011e3 	andeq	r1, r0, r3, ror #3
     1b4:	03940d00 	orrseq	r0, r4, #0, 26
     1b8:	0d010000 	stceq	0, cr0, [r1, #-0]
     1bc:	000008b3 			; <UNDEFINED> instruction: 0x000008b3
     1c0:	02a90d02 	adceq	r0, r9, #2, 26	; 0x80
     1c4:	0d030000 	stceq	0, cr0, [r3, #-0]
     1c8:	00000e72 	andeq	r0, r0, r2, ror lr
     1cc:	0f100d04 	svceq	0x00100d04
     1d0:	0d050000 	stceq	0, cr0, [r5, #-0]
     1d4:	00000e32 	andeq	r0, r0, r2, lsr lr
     1d8:	0e460d06 	cdpeq	13, 4, cr0, cr6, cr6, {0}
     1dc:	0d070000 	stceq	0, cr0, [r7, #-0]
     1e0:	00000ac6 	andeq	r0, r0, r6, asr #21
     1e4:	06ee0d08 	strbteq	r0, [lr], r8, lsl #26
     1e8:	0d090000 	stceq	0, cr0, [r9, #-0]
     1ec:	0000122a 	andeq	r1, r0, sl, lsr #4
     1f0:	03350d0a 	teqeq	r5, #640	; 0x280
     1f4:	0d0b0000 	stceq	0, cr0, [fp, #-0]
     1f8:	00000074 	andeq	r0, r0, r4, ror r0
     1fc:	10ed0d0c 	rscne	r0, sp, ip, lsl #26
     200:	0d0d0000 	stceq	0, cr0, [sp, #-0]
     204:	000001f3 	strdeq	r0, [r0], -r3
     208:	0b8f0d0e 	bleq	fe3c3440 <wmt_core_func_ctrl_cmd+0xfe3c0020>
     20c:	0d0f0000 	stceq	0, cr0, [pc, #-0]	; 214 <.debug_info+0x214>
     210:	00000151 	andeq	r0, r0, r1, asr r1
     214:	14110d10 	ldrne	r0, [r1], #-3344	; 0xfffff2f0
     218:	0d110000 	ldceq	0, cr0, [r1, #-0]
     21c:	000013f1 	strdeq	r1, [r0], -r1	; <UNPREDICTABLE>
     220:	0b240d12 	bleq	903450 <wmt_core_func_ctrl_cmd+0x900030>
     224:	0d130000 	ldceq	0, cr0, [r3, #-0]
     228:	000005fc 	strdeq	r0, [r0], -ip
     22c:	019d0d14 	orrseq	r0, sp, r4, lsl sp
     230:	0d150000 	ldceq	0, cr0, [r5, #-0]
     234:	00000301 	andeq	r0, r0, r1, lsl #6
     238:	07c70d17 	bfieq	r0, r7, (invalid: 26:7)
     23c:	0d180000 	ldceq	0, cr0, [r8, #-0]
     240:	0000134c 	andeq	r1, r0, ip, asr #6
     244:	da020019 	ble	8006c <wmt_core_func_ctrl_cmd+0x7cc4c>
     248:	0400000b 	streq	r0, [r0], #-11
     24c:	0001a39d 	muleq	r1, sp, r3
     250:	0b450c00 	bleq	1143008 <wmt_core_func_ctrl_cmd+0x113fbe8>
     254:	05040000 	streq	r0, [r4, #-0]
     258:	00029a95 	muleq	r2, r5, sl
     25c:	102a0d00 	eorne	r0, sl, r0, lsl #26
     260:	0d000000 	stceq	0, cr0, [r0, #-0]
     264:	00001359 	andeq	r1, r0, r9, asr r3
     268:	073b0d01 	ldreq	r0, [fp, -r1, lsl #26]!
     26c:	0d020000 	stceq	0, cr0, [r2, #-0]
     270:	00000e21 	andeq	r0, r0, r1, lsr #28
     274:	0a060d03 	beq	183414 <wmt_core_func_ctrl_cmd+0x17fff4>
     278:	0d040000 	stceq	0, cr0, [r4, #-0]
     27c:	000012cf 	andeq	r1, r0, pc, asr #5
     280:	05450d05 	strbeq	r0, [r5, #-3333]	; 0xfffff2fb
     284:	0d060000 	stceq	0, cr0, [r6, #-0]
     288:	00000557 	andeq	r0, r0, r7, asr r5
     28c:	08d10d07 	ldmeq	r1, {r0, r1, r2, r8, sl, fp}^
     290:	0d080000 	stceq	0, cr0, [r8, #-0]
     294:	000001e3 	andeq	r0, r0, r3, ror #3
     298:	8e020009 	cdphi	0, 0, cr0, cr2, cr9, {0}
     29c:	05000002 	streq	r0, [r0, #-2]
     2a0:	000251a0 	andeq	r5, r2, r0, lsr #3
     2a4:	05040e00 	streq	r0, [r4, #-3584]	; 0xfffff200
     2a8:	0002c6e1 	andeq	ip, r2, r1, ror #13
     2ac:	036e0d00 	cmneq	lr, #0, 26
     2b0:	0d000000 	stceq	0, cr0, [r0, #-0]
     2b4:	0000111f 	andeq	r1, r0, pc, lsl r1
     2b8:	11330d01 	teqne	r3, r1, lsl #26
     2bc:	0d020000 	stceq	0, cr0, [r2, #-0]
     2c0:	00000fe5 	andeq	r0, r0, r5, ror #31
     2c4:	040e0003 	streq	r0, [lr], #-3
     2c8:	02e1e805 	rsceq	lr, r1, #327680	; 0x50000
     2cc:	230d0000 	movwcs	r0, #53248	; 0xd000
     2d0:	0000000a 	andeq	r0, r0, sl
     2d4:	0000000d 	andeq	r0, r0, sp
     2d8:	510d0100 	mrspl	r0, (UNDEF: 29)
     2dc:	0200000d 	andeq	r0, r0, #13
     2e0:	0b6a0c00 	bleq	1a83008 <wmt_core_func_ctrl_cmd+0x1a7fbe8>
     2e4:	06040000 	streq	r0, [r4], -r0
     2e8:	00036692 	muleq	r3, r2, r6
     2ec:	06110d00 	ldreq	r0, [r1], -r0, lsl #26
     2f0:	0d000000 	stceq	0, cr0, [r0, #-0]
     2f4:	00000bf2 	strdeq	r0, [r0], -r2
     2f8:	12df0d01 	sbcsne	r0, pc, #1, 26	; 0x40
     2fc:	0d020000 	stceq	0, cr0, [r2, #-0]
     300:	00001194 	muleq	r0, r4, r1
     304:	0f220d03 	svceq	0x00220d03
     308:	0d040000 	stceq	0, cr0, [r4, #-0]
     30c:	00000384 	andeq	r0, r0, r4, lsl #7
     310:	0d630d05 	stcleq	13, cr0, [r3, #-20]!	; 0xffffffec
     314:	0d060000 	stceq	0, cr0, [r6, #-0]
     318:	00000eba 			; <UNDEFINED> instruction: 0x00000eba
     31c:	06230d07 	strteq	r0, [r3], -r7, lsl #26
     320:	0d080000 	stceq	0, cr0, [r8, #-0]
     324:	00000719 	andeq	r0, r0, r9, lsl r7
     328:	0aa00d09 	beq	fe80342c <wmt_core_func_ctrl_cmd+0xfe80000c>
     32c:	0d0a0000 	stceq	0, cr0, [sl, #-0]
     330:	00000fc8 	andeq	r0, r0, r8, asr #31
     334:	11730d0b 	cmnne	r3, fp, lsl #26
     338:	0d0c0000 	stceq	0, cr0, [ip, #-0]
     33c:	00000843 	andeq	r0, r0, r3, asr #16
     340:	04e90d0d 	strbteq	r0, [r9], #3341	; 0xd0d
     344:	0d0e0000 	stceq	0, cr0, [lr, #-0]
     348:	00000727 	andeq	r0, r0, r7, lsr #14
     34c:	00b60d0f 	adcseq	r0, r6, pc, lsl #26
     350:	0d100000 	ldceq	0, cr0, [r0, #-0]
     354:	0000092a 	andeq	r0, r0, sl, lsr #18
     358:	10930d11 	addsne	r0, r3, r1, lsl sp
     35c:	0d120000 	ldceq	0, cr0, [r2, #-0]
     360:	00000895 	muleq	r0, r5, r8
     364:	91020013 	tstls	r2, r3, lsl r0
     368:	0600000e 	streq	r0, [r0], -lr
     36c:	00013eb4 			; <UNDEFINED> instruction: 0x00013eb4
     370:	009e0900 	addseq	r0, lr, r0, lsl #18
     374:	04040000 	streq	r0, [r4], #-0
     378:	0000009e 	muleq	r0, lr, r0
     37c:	0003180a 	andeq	r1, r3, sl, lsl #16
     380:	c8062800 	stmdagt	r6, {fp, sp}
     384:	000003c1 	andeq	r0, r0, r1, asr #7
     388:	0013c90b 	andseq	ip, r3, fp, lsl #18
     38c:	9ec90600 	cdpls	6, 12, cr0, cr9, cr0, {0}
     390:	02000000 	andeq	r0, r0, #0
     394:	ce0b0023 	cdpgt	0, 0, cr0, cr11, cr3, {1}
     398:	06000001 	streq	r0, [r0], -r1
     39c:	00009eca 	andeq	r9, r0, sl, asr #29
     3a0:	04230200 	strteq	r0, [r3], #-512	; 0xfffffe00
     3a4:	0001750b 	andeq	r7, r1, fp, lsl #10
     3a8:	c1cb0600 	bicgt	r0, fp, r0, lsl #12
     3ac:	02000003 	andeq	r0, r0, #3
     3b0:	160b0823 	strne	r0, [fp], -r3, lsr #16
     3b4:	0600000a 	streq	r0, [r0], -sl
     3b8:	0003c1cc 	andeq	ip, r3, ip, asr #3
     3bc:	18230200 	stmdane	r3!, {r9}
     3c0:	009e0600 	addseq	r0, lr, r0, lsl #12
     3c4:	03d10000 	bicseq	r0, r1, #0
     3c8:	e3070000 	movw	r0, #28672	; 0x7000
     3cc:	03000000 	movweq	r0, #0
     3d0:	0c020200 	sfmeq	f0, 4, [r2], {-0}
     3d4:	cd060000 	stcgt	0, cr0, [r6, #-0]
     3d8:	0000037c 	andeq	r0, r0, ip, ror r3
     3dc:	000bbb02 	andeq	fp, fp, r2, lsl #22
     3e0:	e7cd0600 	strb	r0, [sp, r0, lsl #12]
     3e4:	04000003 	streq	r0, [r0], #-3
     3e8:	00037c04 	andeq	r7, r3, r4, lsl #24
     3ec:	10670c00 	rsbne	r0, r7, r0, lsl #24
     3f0:	07040000 	streq	r0, [r4, -r0]
     3f4:	00040ca6 	andeq	r0, r4, r6, lsr #25
     3f8:	00fc0d00 	rscseq	r0, ip, r0, lsl #26
     3fc:	0d000000 	stceq	0, cr0, [r0, #-0]
     400:	00000631 	andeq	r0, r0, r1, lsr r6
     404:	0a350d01 	beq	d4340c <wmt_core_func_ctrl_cmd+0xd3ffec>
     408:	00020000 	andeq	r0, r2, r0
     40c:	000e9a02 	andeq	r9, lr, r2, lsl #20
     410:	17eb0700 	strbne	r0, [fp, r0, lsl #14]!
     414:	04000004 	streq	r0, [r0], #-4
     418:	00041d04 	andeq	r1, r4, r4, lsl #26
     41c:	8c010f00 	stchi	15, cr0, [r1], {-0}
     420:	2d000000 	stccs	0, cr0, [r0, #-0]
     424:	10000004 	andne	r0, r0, r4
     428:	00000366 	andeq	r0, r0, r6, ror #6
     42c:	12480a00 	subne	r0, r8, #0, 20
     430:	072c0000 	streq	r0, [ip, -r0]!
     434:	00060bed 	andeq	r0, r6, sp, ror #23
     438:	05070b00 	streq	r0, [r7, #-2816]	; 0xfffff500
     43c:	ee070000 	cdp	0, 0, cr0, cr7, cr0, {0}
     440:	00000061 	andeq	r0, r0, r1, rrx
     444:	0b002302 	bleq	9054 <wmt_core_func_ctrl_cmd+0x5c34>
     448:	000003a7 	andeq	r0, r0, r7, lsr #7
     44c:	0061f007 	rsbeq	pc, r1, r7
     450:	23020000 	movwcs	r0, #8192	; 0x2000
     454:	001b0b01 	andseq	r0, fp, r1, lsl #22
     458:	f1070000 			; <UNDEFINED> instruction: 0xf1070000
     45c:	00000061 	andeq	r0, r0, r1, rrx
     460:	0b022302 	bleq	89070 <wmt_core_func_ctrl_cmd+0x85c50>
     464:	00000c0f 	andeq	r0, r0, pc, lsl #24
     468:	0061f207 	rsbeq	pc, r1, r7, lsl #4
     46c:	23020000 	movwcs	r0, #8192	; 0x2000
     470:	0e590b03 	vnmlseq.f64	d16, d9, d3
     474:	f4070000 	vst4.8	{d0-d3}, [r7], r0
     478:	00000061 	andeq	r0, r0, r1, rrx
     47c:	0b042302 	bleq	10908c <wmt_core_func_ctrl_cmd+0x105c6c>
     480:	00000089 	andeq	r0, r0, r9, lsl #1
     484:	0061f507 	rsbeq	pc, r1, r7, lsl #10
     488:	23020000 	movwcs	r0, #8192	; 0x2000
     48c:	0ce00b05 	fstmiaxeq	r0!, {d16-d17}	;@ Deprecated
     490:	f6070000 			; <UNDEFINED> instruction: 0xf6070000
     494:	00000061 	andeq	r0, r0, r1, rrx
     498:	0b062302 	bleq	1890a8 <wmt_core_func_ctrl_cmd+0x185c88>
     49c:	00000cf9 	strdeq	r0, [r0], -r9
     4a0:	0061f707 	rsbeq	pc, r1, r7, lsl #14
     4a4:	23020000 	movwcs	r0, #8192	; 0x2000
     4a8:	04a30b07 	strteq	r0, [r3], #2823	; 0xb07
     4ac:	f8070000 			; <UNDEFINED> instruction: 0xf8070000
     4b0:	00000061 	andeq	r0, r0, r1, rrx
     4b4:	0b082302 	bleq	2090c4 <wmt_core_func_ctrl_cmd+0x205ca4>
     4b8:	000004d3 	ldrdeq	r0, [r0], -r3
     4bc:	0061f907 	rsbeq	pc, r1, r7, lsl #18
     4c0:	23020000 	movwcs	r0, #8192	; 0x2000
     4c4:	02bc0b09 	adcseq	r0, ip, #9216	; 0x2400
     4c8:	fb070000 	blx	1c04d2 <wmt_core_func_ctrl_cmd+0x1bd0b2>
     4cc:	00000061 	andeq	r0, r0, r1, rrx
     4d0:	0b0a2302 	bleq	2890e0 <wmt_core_func_ctrl_cmd+0x285cc0>
     4d4:	0000141d 	andeq	r1, r0, sp, lsl r4
     4d8:	0061fc07 	rsbeq	pc, r1, r7, lsl #24
     4dc:	23020000 	movwcs	r0, #8192	; 0x2000
     4e0:	01b30b0b 			; <UNDEFINED> instruction: 0x01b30b0b
     4e4:	fd070000 	stc2	0, cr0, [r7, #-0]
     4e8:	00000061 	andeq	r0, r0, r1, rrx
     4ec:	0b0c2302 	bleq	3090fc <wmt_core_func_ctrl_cmd+0x305cdc>
     4f0:	0000063e 	andeq	r0, r0, lr, lsr r6
     4f4:	0061fe07 	rsbeq	pc, r1, r7, lsl #28
     4f8:	23020000 	movwcs	r0, #8192	; 0x2000
     4fc:	0ea80b0d 	vfmaeq.f64	d0, d8, d13
     500:	ff070000 			; <UNDEFINED> instruction: 0xff070000
     504:	00000061 	andeq	r0, r0, r1, rrx
     508:	110e2302 	tstne	lr, r2, lsl #6
     50c:	00000eca 	andeq	r0, r0, sl, asr #29
     510:	61010007 	tstvs	r1, r7
     514:	02000000 	andeq	r0, r0, #0
     518:	b9110f23 	ldmdblt	r1, {r0, r1, r5, r8, r9, sl, fp}
     51c:	07000003 	streq	r0, [r0, -r3]
     520:	00610102 	rsbeq	r0, r1, r2, lsl #2
     524:	23020000 	movwcs	r0, #8192	; 0x2000
     528:	0c3c1110 	ldfeqs	f1, [ip], #-64	; 0xffffffc0
     52c:	03070000 	movweq	r0, #28672	; 0x7000
     530:	00006101 	andeq	r6, r0, r1, lsl #2
     534:	11230200 	teqne	r3, r0, lsl #4
     538:	00120611 	andseq	r0, r2, r1, lsl r6
     53c:	01040700 	tsteq	r4, r0, lsl #14
     540:	00000061 	andeq	r0, r0, r1, rrx
     544:	11122302 	tstne	r2, r2, lsl #6
     548:	00000cc1 	andeq	r0, r0, r1, asr #25
     54c:	61010507 	tstvs	r1, r7, lsl #10
     550:	02000000 	andeq	r0, r0, #0
     554:	5d111323 	ldcpl	3, cr1, [r1, #-140]	; 0xffffff74
     558:	07000007 	streq	r0, [r0, -r7]
     55c:	00730106 	rsbseq	r0, r3, r6, lsl #2
     560:	23020000 	movwcs	r0, #8192	; 0x2000
     564:	07741114 			; <UNDEFINED> instruction: 0x07741114
     568:	07070000 	streq	r0, [r7, -r0]
     56c:	00007301 	andeq	r7, r0, r1, lsl #6
     570:	16230200 	strtne	r0, [r3], -r0, lsl #4
     574:	00011911 	andeq	r1, r1, r1, lsl r9
     578:	01080700 	tsteq	r8, r0, lsl #14
     57c:	00000061 	andeq	r0, r0, r1, rrx
     580:	11182302 	tstne	r8, r2, lsl #6
     584:	00000ddb 	ldrdeq	r0, [r0], -fp
     588:	9e010a07 	vmlals.f32	s0, s2, s14
     58c:	02000000 	andeq	r0, r0, #0
     590:	59111c23 	ldmdbpl	r1, {r0, r1, r5, sl, fp, ip}
     594:	07000011 	smladeq	r0, r1, r0, r0
     598:	009e010b 	addseq	r0, lr, fp, lsl #2
     59c:	23020000 	movwcs	r0, #8192	; 0x2000
     5a0:	01411120 	cmpeq	r1, r0, lsr #2
     5a4:	0d070000 	stceq	0, cr0, [r7, #-0]
     5a8:	00006101 	andeq	r6, r0, r1, lsl #2
     5ac:	24230200 	strtcs	r0, [r3], #-512	; 0xfffffe00
     5b0:	0003fb11 	andeq	pc, r3, r1, lsl fp	; <UNPREDICTABLE>
     5b4:	010e0700 	tsteq	lr, r0, lsl #14
     5b8:	00000061 	andeq	r0, r0, r1, rrx
     5bc:	11252302 	teqne	r5, r2, lsl #6
     5c0:	00000bca 	andeq	r0, r0, sl, asr #23
     5c4:	61011007 	tstvs	r1, r7
     5c8:	02000000 	andeq	r0, r0, #0
     5cc:	dd112623 	ldcle	6, cr2, [r1, #-140]	; 0xffffff74
     5d0:	07000000 	streq	r0, [r0, -r0]
     5d4:	00610111 	rsbeq	r0, r1, r1, lsl r1
     5d8:	23020000 	movwcs	r0, #8192	; 0x2000
     5dc:	13db1127 	bicsne	r1, fp, #-1073741815	; 0xc0000009
     5e0:	12070000 	andne	r0, r7, #0
     5e4:	00006101 	andeq	r6, r0, r1, lsl #2
     5e8:	28230200 	stmdacs	r3!, {r9}
     5ec:	00110a11 	andseq	r0, r1, r1, lsl sl
     5f0:	01130700 	tsteq	r3, r0, lsl #14
     5f4:	00000061 	andeq	r0, r0, r1, rrx
     5f8:	11292302 	teqne	r9, r2, lsl #6
     5fc:	00000591 	muleq	r0, r1, r5
     600:	61011407 	tstvs	r1, r7, lsl #8
     604:	02000000 	andeq	r0, r0, #0
     608:	12002a23 	andne	r2, r0, #143360	; 0x23000
     60c:	00000d95 	muleq	r0, r5, sp
     610:	17011507 	strne	r1, [r1, -r7, lsl #10]
     614:	04000006 	streq	r0, [r0], #-6
     618:	00042d04 	andeq	r2, r4, r4, lsl #26
     61c:	11f71300 	mvnsne	r1, r0, lsl #6
     620:	07040000 	streq	r0, [r4, -r0]
     624:	06430117 			; <UNDEFINED> instruction: 0x06430117
     628:	630d0000 	movwvs	r0, #53248	; 0xd000
     62c:	00000001 	andeq	r0, r0, r1
     630:	000d710d 	andeq	r7, sp, sp, lsl #2
     634:	980d0100 	stmdals	sp, {r8}
     638:	0200000c 	andeq	r0, r0, #12
     63c:	0006930d 	andeq	r9, r6, sp, lsl #6
     640:	12000300 	andne	r0, r0, #0, 6
     644:	00000440 	andeq	r0, r0, r0, asr #8
     648:	1d012007 	stcne	0, cr2, [r1, #-28]	; 0xffffffe4
     64c:	13000006 	movwne	r0, #6
     650:	00000064 	andeq	r0, r0, r4, rrx
     654:	01230704 	teqeq	r3, r4, lsl #14
     658:	0000067b 	andeq	r0, r0, fp, ror r6
     65c:	0013b80d 	andseq	fp, r3, sp, lsl #16
     660:	5f0d0000 	svcpl	0x000d0000
     664:	0100000a 	tsteq	r0, sl
     668:	000a880d 	andeq	r8, sl, sp, lsl #16
     66c:	320d0200 	andcc	r0, sp, #0, 4
     670:	03000008 	movweq	r0, #8
     674:	000e120d 	andeq	r1, lr, sp, lsl #4
     678:	12000400 	andne	r0, r0, #0, 8
     67c:	00001256 	andeq	r1, r0, r6, asr r2
     680:	4f012907 	svcmi	0x00012907
     684:	13000006 	movwne	r0, #6
     688:	0000020e 	andeq	r0, r0, lr, lsl #4
     68c:	012d0704 	teqeq	sp, r4, lsl #14
     690:	000006bf 			; <UNDEFINED> instruction: 0x000006bf
     694:	000f760d 	andeq	r7, pc, sp, lsl #12
     698:	260d0000 	strcs	r0, [sp], -r0
     69c:	01000003 	tsteq	r0, r3
     6a0:	0006ab0d 	andeq	sl, r6, sp, lsl #22
     6a4:	b80d0200 	stmdalt	sp, {r9}
     6a8:	03000006 	movweq	r0, #6
     6ac:	0006c50d 	andeq	ip, r6, sp, lsl #10
     6b0:	d20d0400 	andle	r0, sp, #0, 8
     6b4:	05000006 	streq	r0, [r0, #-6]
     6b8:	0007ec0d 	andeq	lr, r7, sp, lsl #24
     6bc:	12000600 	andne	r0, r0, #0, 12
     6c0:	00000878 	andeq	r0, r0, r8, ror r8
     6c4:	87013507 	strhi	r3, [r1, -r7, lsl #10]
     6c8:	12000006 	andne	r0, r0, #6
     6cc:	000002a1 	andeq	r0, r0, r1, lsr #5
     6d0:	d7013707 	strle	r3, [r1, -r7, lsl #14]
     6d4:	04000006 	streq	r0, [r0], #-6
     6d8:	0006dd04 	andeq	sp, r6, r4, lsl #26
     6dc:	8c010f00 	stchi	15, cr0, [r1], {-0}
     6e0:	ed000000 	stc	0, cr0, [r0, #-0]
     6e4:	10000006 	andne	r0, r0, r6
     6e8:	000003dc 	ldrdeq	r0, [r0], -ip
     6ec:	05b61200 	ldreq	r1, [r6, #512]!	; 0x200
     6f0:	38070000 	stmdacc	r7, {}	; <UNPREDICTABLE>
     6f4:	0006d701 	andeq	sp, r6, r1, lsl #14
     6f8:	10be1200 	adcsne	r1, lr, r0, lsl #4
     6fc:	39070000 	stmdbcc	r7, {}	; <UNPREDICTABLE>
     700:	00070501 	andeq	r0, r7, r1, lsl #10
     704:	0b040400 	bleq	10170c <wmt_core_func_ctrl_cmd+0xfe2ec>
     708:	0f000007 	svceq	0x00000007
     70c:	00008c01 	andeq	r8, r0, r1, lsl #24
     710:	00072500 	andeq	r2, r7, r0, lsl #10
     714:	067b1000 	ldrbteq	r1, [fp], -r0
     718:	bf100000 	svclt	0x00100000
     71c:	10000006 	andne	r0, r0, r6
     720:	0000009e 	muleq	r0, lr, r0
     724:	09cd1200 	stmibeq	sp, {r9, ip}^
     728:	3a070000 	bcc	1c0730 <wmt_core_func_ctrl_cmd+0x1bd310>
     72c:	00073101 	andeq	r3, r7, r1, lsl #2
     730:	37040400 	strcc	r0, [r4, -r0, lsl #8]
     734:	14000007 	strne	r0, [r0], #-7
     738:	00008c01 	andeq	r8, r0, r1, lsl #24
     73c:	046b1500 	strbteq	r1, [fp], #-1280	; 0xfffffb00
     740:	07140000 	ldreq	r0, [r4, -r0]
     744:	0796013c 			; <UNDEFINED> instruction: 0x0796013c
     748:	68110000 	ldmdavs	r1, {}	; <UNPREDICTABLE>
     74c:	07000013 	smladeq	r0, r3, r0, r0
     750:	009e013d 	addseq	r0, lr, sp, lsr r1
     754:	23020000 	movwcs	r0, #8192	; 0x2000
     758:	00131100 	andseq	r1, r3, r0, lsl #2
     75c:	3e070000 	cdpcc	0, 0, cr0, cr7, cr0, {0}
     760:	0006cb01 	andeq	ip, r6, r1, lsl #22
     764:	04230200 	strteq	r0, [r3], #-512	; 0xfffffe00
     768:	000db311 	andeq	fp, sp, r1, lsl r3
     76c:	013f0700 	teqeq	pc, r0, lsl #14
     770:	000006ed 	andeq	r0, r0, sp, ror #13
     774:	11082302 	tstne	r8, r2, lsl #6
     778:	000003ef 	andeq	r0, r0, pc, ror #7
     77c:	f9014007 			; <UNDEFINED> instruction: 0xf9014007
     780:	02000006 	andeq	r0, r0, #6
     784:	86110c23 	ldrhi	r0, [r1], -r3, lsr #24
     788:	07000006 	streq	r0, [r0, -r6]
     78c:	07250141 	streq	r0, [r5, -r1, asr #2]!
     790:	23020000 	movwcs	r0, #8192	; 0x2000
     794:	6d120010 	ldcvs	0, cr0, [r2, #-64]	; 0xffffffc0
     798:	0700000c 	streq	r0, [r0, -ip]
     79c:	073d0142 	ldreq	r0, [sp, -r2, asr #2]!
     7a0:	01120000 	tsteq	r2, r0
     7a4:	07000008 	streq	r0, [r0, -r8]
     7a8:	07ae0142 	streq	r0, [lr, r2, asr #2]!
     7ac:	04040000 	streq	r0, [r4], #-0
     7b0:	0000073d 	andeq	r0, r0, sp, lsr r7
     7b4:	00110015 	andseq	r0, r1, r5, lsl r0
     7b8:	45075400 	strmi	r5, [r7, #-1024]	; 0xfffffc00
     7bc:	0007fe01 	andeq	pc, r7, r1, lsl #28
     7c0:	04351100 	ldrteq	r1, [r5], #-256	; 0xffffff00
     7c4:	46070000 	strmi	r0, [r7], -r0
     7c8:	0007fe01 	andeq	pc, r7, r1, lsl #28
     7cc:	00230200 	eoreq	r0, r3, r0, lsl #4
     7d0:	000f5c11 	andeq	r5, pc, r1, lsl ip	; <UNPREDICTABLE>
     7d4:	01470700 	cmpeq	r7, r0, lsl #14
     7d8:	0000009e 	muleq	r0, lr, r0
     7dc:	11242302 	teqne	r4, r2, lsl #6
     7e0:	00001436 	andeq	r1, r0, r6, lsr r4
     7e4:	d1014807 	tstle	r1, r7, lsl #16
     7e8:	02000003 	andeq	r0, r0, #3
     7ec:	cc112823 	ldcgt	8, cr2, [r1], {35}	; 0x23
     7f0:	07000011 	smladeq	r0, r1, r0, r0
     7f4:	07a2014e 	streq	r0, [r2, lr, asr #2]!
     7f8:	23020000 	movwcs	r0, #8192	; 0x2000
     7fc:	43060050 	movwmi	r0, #24656	; 0x6050
     800:	0e000006 	cdpeq	0, 0, cr0, cr0, cr6, {0}
     804:	07000008 	streq	r0, [r0, -r8]
     808:	000000e3 	andeq	r0, r0, r3, ror #1
     80c:	56120008 	ldrpl	r0, [r2], -r8
     810:	07000003 	streq	r0, [r0, -r3]
     814:	07b4014f 	ldreq	r0, [r4, pc, asr #2]!
     818:	84120000 	ldrhi	r0, [r2], #-0
     81c:	0700000f 	streq	r0, [r0, -pc]
     820:	0826014f 	stmdaeq	r6!, {r0, r1, r2, r3, r6, r8}
     824:	04040000 	streq	r0, [r4], #-0
     828:	000007b4 			; <UNDEFINED> instruction: 0x000007b4
     82c:	00095f15 	andeq	r5, r9, r5, lsl pc
     830:	53072400 	movwpl	r2, #29696	; 0x7400
     834:	00087601 	andeq	r7, r8, r1, lsl #12
     838:	09591100 	ldmdbeq	r9, {r8, ip}^
     83c:	54070000 	strpl	r0, [r7], #-0
     840:	00003e01 	andeq	r3, r0, r1, lsl #28
     844:	00230200 	eoreq	r0, r3, r0, lsl #4
     848:	000cd811 	andeq	sp, ip, r1, lsl r8
     84c:	01550700 	cmpeq	r5, r0, lsl #14
     850:	0000003e 	andeq	r0, r0, lr, lsr r0
     854:	11012302 	tstne	r1, r2, lsl #6
     858:	0000129a 	muleq	r0, sl, r2
     85c:	73015607 	movwvc	r5, #5639	; 0x1607
     860:	02000000 	andeq	r0, r0, #0
     864:	d7110223 	ldrle	r0, [r1, -r3, lsr #4]
     868:	07000010 	smladeq	r0, r0, r0, r0
     86c:	08760157 	ldmdaeq	r6!, {r0, r1, r2, r4, r6, r8}^
     870:	23020000 	movwcs	r0, #8192	; 0x2000
     874:	3e060004 	cdpcc	0, 0, cr0, cr6, cr4, {0}
     878:	86000000 	strhi	r0, [r0], -r0
     87c:	07000008 	streq	r0, [r0, -r8]
     880:	000000e3 	andeq	r0, r0, r3, ror #1
     884:	da12001f 	ble	480084 <wmt_core_func_ctrl_cmd+0x47cc64>
     888:	07000009 	streq	r0, [r0, -r9]
     88c:	082c0158 	stmdaeq	ip!, {r3, r4, r6, r8}
     890:	bd130000 	ldclt	0, cr0, [r3, #-0]
     894:	0400000d 	streq	r0, [r0], #-13
     898:	b8015b07 	stmdalt	r1, {r0, r1, r2, r8, r9, fp, ip, lr}
     89c:	0d000008 	stceq	0, cr0, [r0, #-32]	; 0xffffffe0
     8a0:	00000867 	andeq	r0, r0, r7, ror #16
     8a4:	123b0d00 	eorsne	r0, fp, #0, 26
     8a8:	0d010000 	stceq	0, cr0, [r1, #-0]
     8ac:	00000f67 	andeq	r0, r0, r7, ror #30
     8b0:	09840d02 	stmibeq	r4, {r1, r8, sl, fp}
     8b4:	00030000 	andeq	r0, r3, r0
     8b8:	0004fa13 	andeq	pc, r4, r3, lsl sl	; <UNPREDICTABLE>
     8bc:	62070400 	andvs	r0, r7, #0, 8
     8c0:	00090201 	andeq	r0, r9, r1, lsl #4
     8c4:	09910d00 	ldmibeq	r1, {r8, sl, fp}
     8c8:	0d000000 	stceq	0, cr0, [r0, #-0]
     8cc:	00000fd8 	ldrdeq	r0, [r0], -r8
     8d0:	078b0d01 	streq	r0, [fp, r1, lsl #26]
     8d4:	0d020000 	stceq	0, cr0, [r2, #-0]
     8d8:	0000103f 	andeq	r1, r0, pc, lsr r0
     8dc:	100a0d03 	andne	r0, sl, r3, lsl #26
     8e0:	0d040000 	stceq	0, cr0, [r4, #-0]
     8e4:	00000a6f 	andeq	r0, r0, pc, ror #20
     8e8:	11830d05 	orrne	r0, r3, r5, lsl #26
     8ec:	0d060000 	stceq	0, cr0, [r6, #-0]
     8f0:	00000797 	muleq	r0, r7, r7
     8f4:	00a00d07 	adceq	r0, r0, r7, lsl #26
     8f8:	0d080000 	stceq	0, cr0, [r8, #-0]
     8fc:	00000b3a 	andeq	r0, r0, sl, lsr fp
     900:	04160009 	ldreq	r0, [r6], #-9
     904:	24016f07 	strcs	r6, [r1], #-3847	; 0xfffff0f9
     908:	0d000009 	stceq	0, cr0, [r0, #-36]	; 0xffffffdc
     90c:	0000035e 	andeq	r0, r0, lr, asr r3
     910:	00530d00 	subseq	r0, r3, r0, lsl #26
     914:	0d010000 	stceq	0, cr0, [r1, #-0]
     918:	00000527 	andeq	r0, r0, r7, lsr #10
     91c:	12b30d02 	adcsne	r0, r3, #2, 26	; 0x80
     920:	00030000 	andeq	r0, r3, r0
     924:	00049715 	andeq	r9, r4, r5, lsl r7
     928:	76071400 	strvc	r1, [r7], -r0, lsl #8
     92c:	00097d01 	andeq	r7, r9, r1, lsl #26
     930:	6d631700 	stclvs	7, cr1, [r3, #-0]
     934:	77070064 	strvc	r0, [r7, -r4, rrx]
     938:	00097d01 	andeq	r7, r9, r1, lsl #26
     93c:	00230200 	eoreq	r0, r3, r0, lsl #4
     940:	00044d11 	andeq	r4, r4, r1, lsl sp
     944:	01780700 	cmneq	r8, r0, lsl #14
     948:	0000009e 	muleq	r0, lr, r0
     94c:	17042302 	strne	r2, [r4, -r2, lsl #6]
     950:	00747665 	rsbseq	r7, r4, r5, ror #12
     954:	7d017907 	stcvc	9, cr7, [r1, #-28]	; 0xffffffe4
     958:	02000009 	andeq	r0, r0, #9
     95c:	a4110823 	ldrge	r0, [r1], #-2083	; 0xfffff7dd
     960:	0700000d 	streq	r0, [r0, -sp]
     964:	009e017a 	addseq	r0, lr, sl, ror r1
     968:	23020000 	movwcs	r0, #8192	; 0x2000
     96c:	7473170c 	ldrbtvc	r1, [r3], #-1804	; 0xfffff8f4
     970:	7b070072 	blvc	1c0b40 <wmt_core_func_ctrl_cmd+0x1bd720>
     974:	00097d01 	andeq	r7, r9, r1, lsl #26
     978:	10230200 	eorne	r0, r3, r0, lsl #4
     97c:	61040400 	tstvs	r4, r0, lsl #8
     980:	0e000000 	cdpeq	0, 0, cr0, cr0, cr0, {0}
     984:	b07b0804 	rsbslt	r0, fp, r4, lsl #16
     988:	0d000009 	stceq	0, cr0, [r0, #-36]	; 0xffffffdc
     98c:	000005d7 	ldrdeq	r0, [r0], -r7
     990:	00ab0d00 	adceq	r0, fp, r0, lsl #26
     994:	0d010000 	stceq	0, cr0, [r1, #-0]
     998:	00000a81 	andeq	r0, r0, r1, lsl #21
     99c:	06a60d02 	strteq	r0, [r6], r2, lsl #26
     9a0:	0d030000 	stceq	0, cr0, [r3, #-0]
     9a4:	00000b7b 	andeq	r0, r0, fp, ror fp
     9a8:	13a50d04 			; <UNDEFINED> instruction: 0x13a50d04
     9ac:	00050000 	andeq	r0, r5, r0
     9b0:	00006106 	andeq	r6, r0, r6, lsl #2
     9b4:	0009c000 	andeq	ip, r9, r0
     9b8:	00e30700 	rsceq	r0, r3, r0, lsl #14
     9bc:	00ff0000 	rscseq	r0, pc, r0
     9c0:	000aeb02 	andeq	lr, sl, r2, lsl #22
     9c4:	cb8f0900 	blgt	fe3c2dcc <wmt_core_func_ctrl_cmd+0xfe3bf9ac>
     9c8:	04000009 	streq	r0, [r0], #-9
     9cc:	0009d104 	andeq	sp, r9, r4, lsl #2
     9d0:	8c010f00 	stchi	15, cr0, [r1], {-0}
     9d4:	e6000000 	str	r0, [r0], -r0
     9d8:	10000009 	andne	r0, r0, r9
     9dc:	000007a2 	andeq	r0, r0, r2, lsr #15
     9e0:	00060b10 	andeq	r0, r6, r0, lsl fp
     9e4:	41020000 	mrsmi	r0, (UNDEF: 2)
     9e8:	09000014 	stmdbeq	r0, {r2, r4}
     9ec:	0009cb90 	muleq	r9, r0, fp
     9f0:	0d370a00 	vldmdbeq	r7!, {s0-s-1}
     9f4:	09080000 	stmdbeq	r8, {}	; <UNPREDICTABLE>
     9f8:	000a1a92 	muleq	sl, r2, sl
     9fc:	0bea0b00 	bleq	ffa82c08 <wmt_core_func_ctrl_cmd+0xffa7f7e8>
     a00:	93090000 	movwls	r0, #36864	; 0x9000
     a04:	000009c0 	andeq	r0, r0, r0, asr #19
     a08:	0b002302 	bleq	9618 <wmt_core_func_ctrl_cmd+0x61f8>
     a0c:	00000daa 	andeq	r0, r0, sl, lsr #27
     a10:	09e69409 	stmibeq	r6!, {r0, r3, sl, ip, pc}^
     a14:	23020000 	movwcs	r0, #8192	; 0x2000
     a18:	ca020004 	bgt	80018 <wmt_core_func_ctrl_cmd+0x7cbf8>
     a1c:	09000010 	stmdbeq	r0, {r4}
     a20:	0009f195 	muleq	r9, r5, r1
     a24:	11a50200 			; <UNDEFINED> instruction: 0x11a50200
     a28:	95090000 	strls	r0, [r9, #-0]
     a2c:	00000a30 	andeq	r0, r0, r0, lsr sl
     a30:	09f10404 	ldmibeq	r1!, {r2, sl}^
     a34:	04040000 	streq	r0, [r4], #-0
     a38:	00000a3c 	andeq	r0, r0, ip, lsr sl
     a3c:	008c010f 	addeq	r0, ip, pc, lsl #2
     a40:	0a4c0000 	beq	1300a48 <wmt_core_func_ctrl_cmd+0x12fd628>
     a44:	8c100000 	ldchi	0, cr0, [r0], {-0}
     a48:	00000000 	andeq	r0, r0, r0
     a4c:	00024318 	andeq	r4, r2, r8, lsl r3
     a50:	03870100 	orreq	r0, r7, #0, 2
     a54:	0a750101 	beq	1d40e60 <wmt_core_func_ctrl_cmd+0x1d3da40>
     a58:	f4190000 			; <UNDEFINED> instruction: 0xf4190000
     a5c:	01000005 	tsteq	r0, r5
     a60:	0a750388 	beq	1d41888 <wmt_core_func_ctrl_cmd+0x1d3e468>
     a64:	c61a0000 	ldrgt	r0, [sl], -r0
     a68:	8b000004 	blhi	a80 <.debug_info+0xa80>
     a6c:	0100000a 	tsteq	r0, sl
     a70:	00000243 	andeq	r0, r0, r3, asr #4
     a74:	25040400 	strcs	r0, [r4, #-1024]	; 0xfffffc00
     a78:	06000000 	streq	r0, [r0], -r0
     a7c:	00000030 	andeq	r0, r0, r0, lsr r0
     a80:	00000a8b 	andeq	r0, r0, fp, lsl #21
     a84:	0000e307 	andeq	lr, r0, r7, lsl #6
     a88:	09001800 	stmdbeq	r0, {fp, ip}
     a8c:	00000a7b 	andeq	r0, r0, fp, ror sl
     a90:	0005a01b 	andeq	sl, r5, fp, lsl r0
     a94:	013d0100 	teqeq	sp, r0, lsl #2
     a98:	0000c801 	andeq	ip, r0, r1, lsl #16
     a9c:	0aaf0100 	beq	febc0ea4 <wmt_core_func_ctrl_cmd+0xfebbda84>
     aa0:	d1190000 	tstle	r9, r0
     aa4:	01000005 	tsteq	r0, r5
     aa8:	07a2013e 			; <UNDEFINED> instruction: 0x07a2013e
     aac:	1b000000 	blne	ab4 <.debug_info+0xab4>
     ab0:	00000906 	andeq	r0, r0, r6, lsl #18
     ab4:	0103aa01 	tsteq	r3, r1, lsl #20
     ab8:	0000008c 	andeq	r0, r0, ip, lsl #1
     abc:	000af401 	andeq	pc, sl, r1, lsl #8
     ac0:	0c611c00 	stcleq	12, cr1, [r1], #-0
     ac4:	ac010000 	stcge	0, cr0, [r1], {-0}
     ac8:	00009e03 	andeq	r9, r0, r3, lsl #28
     acc:	05d11c00 	ldrbeq	r1, [r1, #3072]	; 0xc00
     ad0:	ad010000 	stcge	0, cr0, [r1, #-0]
     ad4:	0007a203 	andeq	sl, r7, r3, lsl #4
     ad8:	08e21c00 	stmiaeq	r2!, {sl, fp, ip}^
     adc:	ae010000 	cdpge	0, 0, cr0, cr1, cr0, {0}
     ae0:	00008c03 	andeq	r8, r0, r3, lsl #24
     ae4:	04c61a00 	strbeq	r1, [r6], #2560	; 0xa00
     ae8:	0b040000 	bleq	100af0 <wmt_core_func_ctrl_cmd+0xfd6d0>
     aec:	06010000 	streq	r0, [r1], -r0
     af0:	00000009 	andeq	r0, r0, r9
     af4:	00003006 	andeq	r3, r0, r6
     af8:	000b0400 	andeq	r0, fp, r0, lsl #8
     afc:	00e30700 	rsceq	r0, r3, r0, lsl #14
     b00:	00110000 	andseq	r0, r1, r0
     b04:	000af409 	andeq	pc, sl, r9, lsl #8
     b08:	025c1d00 	subseq	r1, ip, #0, 26
     b0c:	7f010000 	svcvc	0x00010000
     b10:	008c0107 	addeq	r0, ip, r7, lsl #2
     b14:	00000000 	andeq	r0, r0, r0
     b18:	00140000 	andseq	r0, r4, r0
     b1c:	00000000 	andeq	r0, r0, r0
     b20:	0b370000 	bleq	dc0b28 <wmt_core_func_ctrl_cmd+0xdbd708>
     b24:	101e0000 	andsne	r0, lr, r0
     b28:	0100000b 	tsteq	r0, fp
     b2c:	0366077f 	cmneq	r6, #33292288	; 0x1fc0000
     b30:	002c0000 	eoreq	r0, ip, r0
     b34:	1f000000 	svcne	0x00000000
     b38:	00027901 	andeq	r7, r2, r1, lsl #18
     b3c:	039c0100 	orrseq	r0, ip, #0, 2
     b40:	0000c801 	andeq	ip, r0, r1, lsl #16
     b44:	00001400 	andeq	r1, r0, r0, lsl #8
     b48:	00006400 	andeq	r6, r0, r0, lsl #8
     b4c:	00003f00 	andeq	r3, r0, r0, lsl #30
     b50:	000b8600 	andeq	r8, fp, r0, lsl #12
     b54:	00321e00 	eorseq	r1, r2, r0, lsl #28
     b58:	9d010000 	stcls	0, cr0, [r1, #-0]
     b5c:	00009e03 	andeq	r9, r0, r3, lsl #28
     b60:	00006b00 	andeq	r6, r0, r0, lsl #22
     b64:	09691e00 	stmdbeq	r9!, {r9, sl, fp, ip}^
     b68:	9e010000 	cdpls	0, 0, cr0, cr1, cr0, {0}
     b6c:	00009e03 	andeq	r9, r0, r3, lsl #28
     b70:	00009400 	andeq	r9, r0, r0, lsl #8
     b74:	04c62000 	strbeq	r2, [r6], #0
     b78:	0b960000 	bleq	fe580b80 <wmt_core_func_ctrl_cmd+0xfe57d760>
     b7c:	05010000 	streq	r0, [r1, #-0]
     b80:	00000003 	andeq	r0, r0, r3
     b84:	30060000 	andcc	r0, r6, r0
     b88:	96000000 	strls	r0, [r0], -r0
     b8c:	0700000b 	streq	r0, [r0, -fp]
     b90:	000000e3 	andeq	r0, r0, r3, ror #1
     b94:	86090014 			; <UNDEFINED> instruction: 0x86090014
     b98:	1f00000b 	svcne	0x0000000b
     b9c:	00003d01 	andeq	r3, r0, r1, lsl #26
     ba0:	01fd0100 	mvnseq	r0, r0, lsl #2
     ba4:	00008c01 	andeq	r8, r0, r1, lsl #24
     ba8:	00006400 	andeq	r6, r0, r0, lsl #8
     bac:	0000b000 	andeq	fp, r0, r0
     bb0:	0000b200 	andeq	fp, r0, r0, lsl #4
     bb4:	000bfa00 	andeq	pc, fp, r0, lsl #20
     bb8:	0b101e00 	bleq	407808 <wmt_core_func_ctrl_cmd+0x4043e8>
     bbc:	fd010000 	stc2	0, cr0, [r1, #-0]
     bc0:	00036601 	andeq	r6, r3, r1, lsl #12
     bc4:	0000de00 	andeq	sp, r0, r0, lsl #28
     bc8:	02d72100 	sbcseq	r2, r7, #0, 2
     bcc:	ff010000 			; <UNDEFINED> instruction: 0xff010000
     bd0:	00009e01 	andeq	r9, r0, r1, lsl #28
     bd4:	0000fc00 	andeq	pc, r0, r0, lsl #24
     bd8:	65722200 	ldrbvs	r2, [r2, #-512]!	; 0xfffffe00
     bdc:	00010074 	andeq	r0, r1, r4, ror r0
     be0:	00008c02 	andeq	r8, r0, r2, lsl #24
     be4:	00011a00 	andeq	r1, r1, r0, lsl #20
     be8:	04c62000 	strbeq	r2, [r6], #0
     bec:	0c0a0000 	stceq	0, cr0, [sl], {-0}
     bf0:	05010000 	streq	r0, [r1, #-0]
     bf4:	00006403 	andeq	r6, r0, r3, lsl #8
     bf8:	30060000 	andcc	r0, r6, r0
     bfc:	0a000000 	beq	c04 <.debug_info+0xc04>
     c00:	0700000c 	streq	r0, [r0, -ip]
     c04:	000000e3 	andeq	r0, r0, r3, ror #1
     c08:	fa090015 	blx	240c64 <wmt_core_func_ctrl_cmd+0x23d844>
     c0c:	1f00000b 	svcne	0x0000000b
     c10:	0011d501 	andseq	sp, r1, r1, lsl #10
     c14:	020e0100 	andeq	r0, lr, #0, 2
     c18:	00008c01 	andeq	r8, r0, r1, lsl #24
     c1c:	0000b000 	andeq	fp, r0, r0
     c20:	00011400 	andeq	r1, r1, r0, lsl #8
     c24:	00012d00 	andeq	r2, r1, r0, lsl #26
     c28:	000c4e00 	andeq	r4, ip, r0, lsl #28
     c2c:	0b101e00 	bleq	407808 <wmt_core_func_ctrl_cmd+0x4043e8>
     c30:	0e010000 	cdpeq	0, 0, cr0, cr1, cr0, {0}
     c34:	00036602 	andeq	r6, r3, r2, lsl #12
     c38:	00015900 	andeq	r5, r1, r0, lsl #18
     c3c:	04c62000 	strbeq	r2, [r6], #0
     c40:	0c5e0000 	mraeq	r0, lr, acc0
     c44:	05010000 	streq	r0, [r1, #-0]
     c48:	00007c03 	andeq	r7, r0, r3, lsl #24
     c4c:	30060000 	andcc	r0, r6, r0
     c50:	5e000000 	cdppl	0, 0, cr0, cr0, cr0, {0}
     c54:	0700000c 	streq	r0, [r0, -ip]
     c58:	000000e3 	andeq	r0, r0, r3, ror #1
     c5c:	4e09000d 	cdpmi	0, 0, cr0, cr9, cr13, {0}
     c60:	2300000c 	movwcs	r0, #12
     c64:	0010a601 	andseq	sl, r0, r1, lsl #12
     c68:	015f0100 	cmpeq	pc, r0, lsl #2
     c6c:	00008c01 	andeq	r8, r0, r1, lsl #24
     c70:	00011400 	andeq	r1, r1, r0, lsl #8
     c74:	00013c00 	andeq	r3, r1, r0, lsl #24
     c78:	00019800 	andeq	r9, r1, r0, lsl #16
     c7c:	4b011f00 	blmi	47c08 <wmt_core_func_ctrl_cmd+0x447e8>
     c80:	01000009 	tsteq	r0, r9
     c84:	8c01014f 	stfhis	f0, [r1], {79}	; 0x4f
     c88:	3c000000 	stccc	0, cr0, [r0], {-0}
     c8c:	7c000001 	stcvc	0, cr0, [r0], {1}
     c90:	c4000001 	strgt	r0, [r0], #-1
     c94:	a6000001 	strge	r0, [r0], -r1
     c98:	2400000c 	strcs	r0, [r0], #-12
     c9c:	51010069 	tstpl	r1, r9, rrx
     ca0:	00008c01 	andeq	r8, r0, r1, lsl #24
     ca4:	01250000 	teqeq	r5, r0
     ca8:	0000132d 	andeq	r1, r0, sp, lsr #6
     cac:	01023e01 	tsteq	r2, r1, lsl #28
     cb0:	0000017c 	andeq	r0, r0, ip, ror r1
     cb4:	0000024c 	andeq	r0, r0, ip, asr #4
     cb8:	000001f0 	strdeq	r0, [r0], -r0	; <UNPREDICTABLE>
     cbc:	00000d19 	andeq	r0, r0, r9, lsl sp
     cc0:	0013eb1e 	andseq	lr, r3, lr, lsl fp
     cc4:	023f0100 	eorseq	r0, pc, #0, 2
     cc8:	00000050 	andeq	r0, r0, r0, asr r0
     ccc:	0000021c 	andeq	r0, r0, ip, lsl r2
     cd0:	00136d1e 	andseq	r6, r3, lr, lsl sp
     cd4:	02400100 	subeq	r0, r0, #0, 2
     cd8:	00000050 	andeq	r0, r0, r0, asr r0
     cdc:	0000023a 	andeq	r0, r0, sl, lsr r2
     ce0:	6e656c26 	cdpvs	12, 6, cr6, cr5, cr6, {1}
     ce4:	02410100 	subeq	r0, r1, #0, 2
     ce8:	0000009e 	muleq	r0, lr, r0
     cec:	00000279 	andeq	r0, r0, r9, ror r2
     cf0:	72747024 	rsbsvc	r7, r4, #36	; 0x24
     cf4:	02440100 	subeq	r0, r4, #0, 2
     cf8:	00000050 	andeq	r0, r0, r0, asr r0
     cfc:	01006b27 	tsteq	r0, r7, lsr #22
     d00:	008c0245 	addeq	r0, ip, r5, asr #4
     d04:	57010000 	strpl	r0, [r1, -r0]
     d08:	0004c620 	andeq	ip, r4, r0, lsr #12
     d0c:	000d2900 	andeq	r2, sp, r0, lsl #18
     d10:	03050100 	movweq	r0, #20736	; 0x5100
     d14:	0000008c 	andeq	r0, r0, ip, lsl #1
     d18:	00300600 	eorseq	r0, r0, r0, lsl #12
     d1c:	0d290000 	stceq	0, cr0, [r9, #-0]
     d20:	e3070000 	movw	r0, #28672	; 0x7000
     d24:	12000000 	andne	r0, r0, #0
     d28:	0d190900 	ldceq	9, cr0, [r9, #-0]
     d2c:	781d0000 	ldmdavc	sp, {}	; <UNPREDICTABLE>
     d30:	01000004 	tsteq	r0, r4
     d34:	8c0107e8 	stchi	7, cr0, [r1], {232}	; 0xe8
     d38:	4c000000 	stcmi	0, cr0, [r0], {-0}
     d3c:	18000002 	stmdane	r0, {r1}
     d40:	97000003 	strls	r0, [r0, -r3]
     d44:	ab000002 	blge	d54 <.debug_info+0xd54>
     d48:	1e00000d 	cdpne	0, 0, cr0, cr0, cr13, {0}
     d4c:	00000b10 	andeq	r0, r0, r0, lsl fp
     d50:	6607e801 	strvs	lr, [r7], -r1, lsl #16
     d54:	c3000003 	movwgt	r0, #3
     d58:	21000002 	tstcs	r0, r2
     d5c:	0000145f 	andeq	r1, r0, pc, asr r4
     d60:	8c07ea01 	stchi	10, cr14, [r7], {1}
     d64:	f7000000 			; <UNDEFINED> instruction: 0xf7000000
     d68:	22000002 	andcs	r0, r0, #2
     d6c:	01006469 	tsteq	r0, r9, ror #8
     d70:	067b07eb 	ldrbteq	r0, [fp], -fp, ror #15
     d74:	03200000 	teqeq	r0, #0
     d78:	de210000 	cdple	0, 2, cr0, cr1, cr0, {0}
     d7c:	01000001 	tsteq	r0, r1
     d80:	06bf07ec 	ldrteq	r0, [pc], ip, ror #15
     d84:	03330000 	teqeq	r3, #0
     d88:	85210000 	strhi	r0, [r1, #-0]!
     d8c:	0100000b 	tsteq	r0, fp
     d90:	009e07ed 	addseq	r0, lr, sp, ror #15
     d94:	03460000 	movteq	r0, #24576	; 0x6000
     d98:	c6200000 	strtgt	r0, [r0], -r0
     d9c:	bb000004 	bllt	db4 <.debug_info+0xdb4>
     da0:	0100000d 	tsteq	r0, sp
     da4:	00a00305 	adceq	r0, r0, r5, lsl #6
     da8:	06000000 	streq	r0, [r0], -r0
     dac:	00000030 	andeq	r0, r0, r0, lsr r0
     db0:	00000dbb 			; <UNDEFINED> instruction: 0x00000dbb
     db4:	0000e307 	andeq	lr, r0, r7, lsl #6
     db8:	09001000 	stmdbeq	r0, {ip}
     dbc:	00000dab 	andeq	r0, r0, fp, lsr #27
     dc0:	00065f1d 	andeq	r5, r6, sp, lsl pc
     dc4:	03e40100 	mvneq	r0, #0, 2
     dc8:	00008c01 	andeq	r8, r0, r1, lsl #24
     dcc:	00031800 	andeq	r1, r3, r0, lsl #16
     dd0:	0003f000 	andeq	pc, r3, r0
     dd4:	00035900 	andeq	r5, r3, r0, lsl #18
     dd8:	000dfe00 	andeq	pc, sp, r0, lsl #28
     ddc:	0b101e00 	bleq	407808 <wmt_core_func_ctrl_cmd+0x4043e8>
     de0:	e4010000 	str	r0, [r1], #-0
     de4:	00036603 	andeq	r6, r3, r3, lsl #12
     de8:	00038500 	andeq	r8, r3, r0, lsl #10
     dec:	04c62000 	strbeq	r2, [r6], #0
     df0:	0dfe0000 	ldcleq	0, cr0, [lr]
     df4:	05010000 	streq	r0, [r1, #-0]
     df8:	0000b403 	andeq	fp, r0, r3, lsl #8
     dfc:	d3090000 	movwle	r0, #36864	; 0x9000
     e00:	1f000000 	svcne	0x00000000
     e04:	00131f01 	andseq	r1, r3, r1, lsl #30
     e08:	02210100 	eoreq	r0, r1, #0, 2
     e0c:	00008c01 	andeq	r8, r0, r1, lsl #24
     e10:	0003f000 	andeq	pc, r3, r0
     e14:	0004ac00 	andeq	sl, r4, r0, lsl #24
     e18:	0003a300 	andeq	sl, r3, r0, lsl #6
     e1c:	000e9c00 	andeq	r9, lr, r0, lsl #24
     e20:	04e31e00 	strbteq	r1, [r3], #3584	; 0xe00
     e24:	21010000 	mrscs	r0, (UNDEF: 1)
     e28:	00024602 	andeq	r4, r2, r2, lsl #12
     e2c:	0003cf00 	andeq	ip, r3, r0, lsl #30
     e30:	13d11e00 	bicsne	r1, r1, #0, 28
     e34:	21010000 	mrscs	r0, (UNDEF: 1)
     e38:	0000b002 	andeq	fp, r0, r2
     e3c:	0003ed00 	andeq	lr, r3, r0, lsl #26
     e40:	13d61e00 	bicsne	r1, r6, #0, 28
     e44:	21010000 	mrscs	r0, (UNDEF: 1)
     e48:	0000b002 	andeq	fp, r0, r2
     e4c:	00040b00 	andeq	r0, r4, r0, lsl #22
     e50:	145f2800 	ldrbne	r2, [pc], #-2048	; 8 <.debug_info+0x8>
     e54:	23010000 	movwcs	r0, #4096	; 0x1000
     e58:	00008c02 	andeq	r8, r0, r2, lsl #24
     e5c:	28540100 	ldmdacs	r4, {r8}^
     e60:	0000023a 	andeq	r0, r0, sl, lsr r2
     e64:	98022401 	stmdals	r2, {r0, sl, sp}
     e68:	03000001 	movweq	r0, #1
     e6c:	287f9491 	ldmdacs	pc!, {r0, r4, r7, sl, ip, pc}^	; <UNPREDICTABLE>
     e70:	00000204 	andeq	r0, r0, r4, lsl #4
     e74:	9e022501 	cfsh32ls	mvfx2, mvfx2, #1
     e78:	01000000 	mrseq	r0, (UNDEF: 0)
     e7c:	02092856 	andeq	r2, r9, #5636096	; 0x560000
     e80:	26010000 	strcs	r0, [r1], -r0
     e84:	00009e02 	andeq	r9, r0, r2, lsl #28
     e88:	20550100 	subscs	r0, r5, r0, lsl #2
     e8c:	000004c6 	andeq	r0, r0, r6, asr #9
     e90:	00000e9c 	muleq	r0, ip, lr
     e94:	c4030501 	strgt	r0, [r3], #-1281	; 0xfffffaff
     e98:	00000000 	andeq	r0, r0, r0
     e9c:	000c4e09 	andeq	r4, ip, r9, lsl #28
     ea0:	04891d00 	streq	r1, [r9], #3328	; 0xd00
     ea4:	f8010000 			; <UNDEFINED> instruction: 0xf8010000
     ea8:	008c0106 	addeq	r0, ip, r6, lsl #2
     eac:	04ac0000 	strteq	r0, [ip], #0
     eb0:	08400000 	stmdaeq	r0, {}^	; <UNPREDICTABLE>
     eb4:	04290000 	strteq	r0, [r9], #-0
     eb8:	0f690000 	svceq	0x00690000
     ebc:	101e0000 	andsne	r0, lr, r0
     ec0:	0100000b 	tsteq	r0, fp
     ec4:	036606f8 	cmneq	r6, #248, 12	; 0xf800000
     ec8:	04550000 	ldrbeq	r0, [r5], #-0
     ecc:	5f210000 	svcpl	0x00210000
     ed0:	01000014 	tsteq	r0, r4, lsl r0
     ed4:	008c06fb 	strdeq	r0, [ip], fp
     ed8:	04890000 	streq	r0, [r9], #0
     edc:	10210000 	eorne	r0, r1, r0
     ee0:	01000005 	tsteq	r0, r5
     ee4:	009e06fc 			; <UNDEFINED> instruction: 0x009e06fc
     ee8:	05150000 	ldreq	r0, [r5, #-0]
     eec:	18210000 	stmdane	r1!, {}	; <UNPREDICTABLE>
     ef0:	01000005 	tsteq	r0, r5
     ef4:	009e06fd 			; <UNDEFINED> instruction: 0x009e06fd
     ef8:	05350000 	ldreq	r0, [r5, #-0]!
     efc:	c6200000 	strtgt	r0, [r0], -r0
     f00:	69000004 	stmdbvs	r0, {r2}
     f04:	0100000f 	tsteq	r0, pc
     f08:	00f00305 	rscseq	r0, r0, r5, lsl #6
     f0c:	4c290000 	stcmi	0, cr0, [r9], #-0
     f10:	bc00000a 	stclt	0, cr0, [r0], {10}
     f14:	20000004 	andcs	r0, r0, r4
     f18:	01000005 	tsteq	r0, r5
     f1c:	0f3d06ff 	svceq	0x003d06ff
     f20:	5a2a0000 	bpl	a80f28 <wmt_core_func_ctrl_cmd+0xa7db08>
     f24:	2b00000a 	blcs	f54 <.debug_info+0xf54>
     f28:	000004bc 			; <UNDEFINED> instruction: 0x000004bc
     f2c:	00000520 	andeq	r0, r0, r0, lsr #10
     f30:	000a662c 	andeq	r6, sl, ip, lsr #12
     f34:	d4030500 	strle	r0, [r3], #-1280	; 0xfffffb00
     f38:	00000000 	andeq	r0, r0, r0
     f3c:	0a4c2d00 	beq	130c344 <wmt_core_func_ctrl_cmd+0x1308f24>
     f40:	05b40000 	ldreq	r0, [r4, #0]!
     f44:	06080000 	streq	r0, [r8], -r0
     f48:	61010000 	mrsvs	r0, (UNDEF: 1)
     f4c:	0a5a2a07 	beq	168b770 <wmt_core_func_ctrl_cmd+0x1688350>
     f50:	b42b0000 	strtlt	r0, [fp], #-0
     f54:	08000005 	stmdaeq	r0, {r0, r2}
     f58:	2c000006 	stccs	0, cr0, [r0], {6}
     f5c:	00000a66 	andeq	r0, r0, r6, ror #20
     f60:	00d40305 	sbcseq	r0, r4, r5, lsl #6
     f64:	00000000 	andeq	r0, r0, r0
     f68:	0c4e0900 	mcrreq	9, 0, r0, lr, cr0
     f6c:	011f0000 	tsteq	pc, r0
     f70:	000009e2 	andeq	r0, r0, r2, ror #19
     f74:	01019901 	tsteq	r1, r1, lsl #18
     f78:	0000008c 	andeq	r0, r0, ip, lsl #1
     f7c:	00000840 	andeq	r0, r0, r0, asr #16
     f80:	000008b4 			; <UNDEFINED> instruction: 0x000008b4
     f84:	00000555 	andeq	r0, r0, r5, asr r5
     f88:	00000fcb 	andeq	r0, r0, fp, asr #31
     f8c:	0001d91e 	andeq	sp, r1, lr, lsl r9
     f90:	01990100 	orrseq	r0, r9, r0, lsl #2
     f94:	0000009e 	muleq	r0, lr, r0
     f98:	00000581 	andeq	r0, r0, r1, lsl #11
     f9c:	00145f28 	andseq	r5, r4, r8, lsr #30
     fa0:	019b0100 	orrseq	r0, fp, r0, lsl #2
     fa4:	0000008c 	andeq	r0, r0, ip, lsl #1
     fa8:	3a285401 	bcc	a1500c <wmt_core_func_ctrl_cmd+0xa11bec>
     fac:	01000002 	tsteq	r0, r2
     fb0:	0198019c 			; <UNDEFINED> instruction: 0x0198019c
     fb4:	91030000 	mrsls	r0, (UNDEF: 3)
     fb8:	c6207fa4 	strtgt	r7, [r0], -r4, lsr #31
     fbc:	cb000004 	blgt	fd4 <.debug_info+0xfd4>
     fc0:	0100000f 	tsteq	r0, pc
     fc4:	01000305 	tsteq	r0, r5, lsl #6
     fc8:	09000000 	stmdbeq	r0, {}	; <UNPREDICTABLE>
     fcc:	00000af4 	strdeq	r0, [r0], -r4
     fd0:	0889011f 	stmeq	r9, {r0, r1, r2, r3, r4, r8}
     fd4:	86010000 	strhi	r0, [r1], -r0
     fd8:	008c0101 	addeq	r0, ip, r1, lsl #2
     fdc:	08b40000 	ldmeq	r4!, {}	; <UNPREDICTABLE>
     fe0:	09340000 	ldmdbeq	r4!, {}	; <UNPREDICTABLE>
     fe4:	05940000 	ldreq	r0, [r4]
     fe8:	104d0000 	subne	r0, sp, r0
     fec:	591e0000 	ldmdbpl	lr, {}	; <UNPREDICTABLE>
     ff0:	01000010 	tsteq	r0, r0, lsl r0
     ff4:	00500186 	subseq	r0, r0, r6, lsl #3
     ff8:	05c00000 	strbeq	r0, [r0]
     ffc:	331e0000 	tstcc	lr, #0
    1000:	01000002 	tsteq	r0, r2
    1004:	009e0186 	addseq	r0, lr, r6, lsl #3
    1008:	05d30000 	ldrbeq	r0, [r3]
    100c:	941e0000 	ldrls	r0, [lr], #-0
    1010:	0100000f 	tsteq	r0, pc
    1014:	03760186 	cmneq	r6, #-2147483615	; 0x80000021
    1018:	05e60000 	strbeq	r0, [r6, #0]!
    101c:	5f280000 	svcpl	0x00280000
    1020:	01000014 	tsteq	r0, r4, lsl r0
    1024:	008c0188 	addeq	r0, ip, r8, lsl #3
    1028:	54010000 	strpl	r0, [r1], #-0
    102c:	00023a28 	andeq	r3, r2, r8, lsr #20
    1030:	01890100 	orreq	r0, r9, r0, lsl #2
    1034:	00000198 	muleq	r0, r8, r1
    1038:	7fa49103 	svcvc	0x00a49103
    103c:	0004c620 	andeq	ip, r4, r0, lsr #12
    1040:	00105d00 	andseq	r5, r0, r0, lsl #26
    1044:	03050100 	movweq	r0, #20736	; 0x5100
    1048:	00000114 	andeq	r0, r0, r4, lsl r1
    104c:	00300600 	eorseq	r0, r0, r0, lsl #12
    1050:	105d0000 	subsne	r0, sp, r0
    1054:	e3070000 	movw	r0, #28672	; 0x7000
    1058:	0b000000 	bleq	1060 <.debug_info+0x1060>
    105c:	104d0900 	subne	r0, sp, r0, lsl #18
    1060:	c01d0000 	andsgt	r0, sp, r0
    1064:	01000005 	tsteq	r0, r5
    1068:	8c010805 	stchi	8, cr0, [r1], {5}
    106c:	34000000 	strcc	r0, [r0], #-0
    1070:	fc000009 	stc2	0, cr0, [r0], {9}
    1074:	f9000009 			; <UNDEFINED> instruction: 0xf9000009
    1078:	cb000005 	blgt	1094 <.debug_info+0x1094>
    107c:	1e000010 	mcrne	0, 0, r0, cr0, cr0, {0}
    1080:	00000b10 	andeq	r0, r0, r0, lsl fp
    1084:	66080501 	strvs	r0, [r8], -r1, lsl #10
    1088:	25000003 	strcs	r0, [r0, #-3]
    108c:	21000006 	tstcs	r0, r6
    1090:	00000510 	andeq	r0, r0, r0, lsl r5
    1094:	9e080701 	cdpls	7, 0, cr0, cr8, cr1, {0}
    1098:	38000000 	stmdacc	r0, {}	; <UNPREDICTABLE>
    109c:	28000006 	stmdacs	r0, {r1, r2}
    10a0:	00000518 	andeq	r0, r0, r8, lsl r5
    10a4:	9e080801 	cdpls	8, 0, cr0, cr8, cr1, {0}
    10a8:	02000000 	andeq	r0, r0, #0
    10ac:	5f1c647b 	svcpl	0x001c647b
    10b0:	01000014 	tsteq	r0, r4, lsl r0
    10b4:	009e0809 	addseq	r0, lr, r9, lsl #16
    10b8:	c6200000 	strtgt	r0, [r0], -r0
    10bc:	cb000004 	blgt	10d4 <.debug_info+0x10d4>
    10c0:	01000010 	tsteq	r0, r0, lsl r0
    10c4:	01200305 	teqeq	r0, r5, lsl #6
    10c8:	09000000 	stmdbeq	r0, {}	; <UNPREDICTABLE>
    10cc:	00000dab 	andeq	r0, r0, fp, lsr #27
    10d0:	00104d1d 	andseq	r4, r0, sp, lsl sp
    10d4:	056c0100 	strbeq	r0, [ip, #-256]!	; 0xffffff00
    10d8:	00008c01 	andeq	r8, r0, r1, lsl #24
    10dc:	0009fc00 	andeq	pc, r9, r0, lsl #24
    10e0:	000a3800 	andeq	r3, sl, r0, lsl #16
    10e4:	00066e00 	andeq	r6, r6, r0, lsl #28
    10e8:	00110e00 	andseq	r0, r1, r0, lsl #28
    10ec:	0b101e00 	bleq	407808 <wmt_core_func_ctrl_cmd+0x4043e8>
    10f0:	6d010000 	stcvs	0, cr0, [r1, #-0]
    10f4:	00036605 	andeq	r6, r3, r5, lsl #12
    10f8:	00069a00 	andeq	r9, r6, r0, lsl #20
    10fc:	04c62000 	strbeq	r2, [r6], #0
    1100:	110e0000 	mrsne	r0, (UNDEF: 14)
    1104:	05010000 	streq	r0, [r1, #-0]
    1108:	00013403 	andeq	r3, r1, r3, lsl #8
    110c:	4d090000 	stcmi	0, cr0, [r9, #-0]
    1110:	1d000010 	stcne	0, cr0, [r0, #-64]	; 0xffffffc0
    1114:	00000569 	andeq	r0, r0, r9, ror #10
    1118:	01034601 	tsteq	r3, r1, lsl #12
    111c:	0000008c 	andeq	r0, r0, ip, lsl #1
    1120:	00000a38 	andeq	r0, r0, r8, lsr sl
    1124:	00000c6c 	andeq	r0, r0, ip, ror #24
    1128:	000006b8 			; <UNDEFINED> instruction: 0x000006b8
    112c:	0000117d 	andeq	r1, r0, sp, ror r1
    1130:	00145f21 	andseq	r5, r4, r1, lsr #30
    1134:	03480100 	movteq	r0, #33024	; 0x8100
    1138:	0000008c 	andeq	r0, r0, ip, lsl #1
    113c:	000006e4 	andeq	r0, r0, r4, ror #13
    1140:	00051021 	andeq	r1, r5, r1, lsr #32
    1144:	03490100 	movteq	r0, #37120	; 0x9100
    1148:	0000009e 	muleq	r0, lr, r0
    114c:	0000074f 	andeq	r0, r0, pc, asr #14
    1150:	00051821 	andeq	r1, r5, r1, lsr #16
    1154:	034a0100 	movteq	r0, #41216	; 0xa100
    1158:	0000009e 	muleq	r0, lr, r0
    115c:	0000077b 	andeq	r0, r0, fp, ror r7
    1160:	0004c620 	andeq	ip, r4, r0, lsr #12
    1164:	00118d00 	andseq	r8, r1, r0, lsl #26
    1168:	03050100 	movweq	r0, #20736	; 0x5100
    116c:	00000140 	andeq	r0, r0, r0, asr #2
    1170:	000eee2e 	andeq	lr, lr, lr, lsr #28
    1174:	035b0100 	cmpeq	fp, #0, 2
    1178:	00000a84 	andeq	r0, r0, r4, lsl #21
    117c:	00300600 	eorseq	r0, r0, r0, lsl #12
    1180:	118d0000 	orrne	r0, sp, r0
    1184:	e3070000 	movw	r0, #28672	; 0x7000
    1188:	13000000 	movwne	r0, #0
    118c:	117d0900 	cmnne	sp, r0, lsl #18
    1190:	b11d0000 	tstlt	sp, r0
    1194:	0100000f 	tsteq	r0, pc
    1198:	8c010440 	cfstrshi	mvf0, [r1], {64}	; 0x40
    119c:	6c000000 	stcvs	0, cr0, [r0], {-0}
    11a0:	a000000c 	andge	r0, r0, ip
    11a4:	a700000d 	strge	r0, [r0, -sp]
    11a8:	00000007 	andeq	r0, r0, r7
    11ac:	1e000012 	mcrne	0, 0, r0, cr0, cr2, {0}
    11b0:	00000b10 	andeq	r0, r0, r0, lsl fp
    11b4:	66044001 	strvs	r4, [r4], -r1
    11b8:	d3000003 	movwle	r0, #3
    11bc:	21000007 	tstcs	r0, r7
    11c0:	0000145f 	andeq	r1, r0, pc, asr r4
    11c4:	8c044301 	stchi	3, cr4, [r4], {1}
    11c8:	07000000 	streq	r0, [r0, -r0]
    11cc:	21000008 	tstcs	r0, r8
    11d0:	00000510 	andeq	r0, r0, r0, lsl r5
    11d4:	9e044401 	cdpls	4, 0, cr4, cr4, cr1, {0}
    11d8:	46000000 	strmi	r0, [r0], -r0
    11dc:	21000008 	tstcs	r0, r8
    11e0:	00000518 	andeq	r0, r0, r8, lsl r5
    11e4:	9e044501 	cfsh32ls	mvfx4, mvfx4, #1
    11e8:	66000000 	strvs	r0, [r0], -r0
    11ec:	20000008 	andcs	r0, r0, r8
    11f0:	000004c6 	andeq	r0, r0, r6, asr #9
    11f4:	00001210 	andeq	r1, r0, r0, lsl r2
    11f8:	54030501 	strpl	r0, [r3], #-1281	; 0xfffffaff
    11fc:	00000001 	andeq	r0, r0, r1
    1200:	00003006 	andeq	r3, r0, r6
    1204:	00121000 	andseq	r1, r2, r0
    1208:	00e30700 	rsceq	r0, r3, r0, lsl #14
    120c:	000e0000 	andeq	r0, lr, r0
    1210:	00120009 	andseq	r0, r2, r9
    1214:	0c881d00 	stceq	13, cr1, [r8], {0}
    1218:	fc010000 	stc2	0, cr0, [r1], {-0}
    121c:	008c0104 	addeq	r0, ip, r4, lsl #2
    1220:	0da00000 	stceq	0, cr0, [r0]
    1224:	10e40000 	rscne	r0, r4, r0
    1228:	08860000 	stmeq	r6, {}	; <UNPREDICTABLE>
    122c:	12d40000 	sbcsne	r0, r4, #0
    1230:	101e0000 	andsne	r0, lr, r0
    1234:	0100000b 	tsteq	r0, fp
    1238:	036604fc 	cmneq	r6, #252, 8	; 0xfc000000
    123c:	08b20000 	ldmeq	r2!, {}	; <UNPREDICTABLE>
    1240:	5f210000 	svcpl	0x00210000
    1244:	01000014 	tsteq	r0, r4, lsl r0
    1248:	008c04ff 	strdeq	r0, [ip], pc	; <UNPREDICTABLE>
    124c:	08e60000 	stmiaeq	r6!, {}^	; <UNPREDICTABLE>
    1250:	c0210000 	eorgt	r0, r1, r0
    1254:	0100000f 	tsteq	r0, pc
    1258:	009e0500 	addseq	r0, lr, r0, lsl #10
    125c:	093b0000 	ldmdbeq	fp!, {}	; <UNPREDICTABLE>
    1260:	10210000 	eorne	r0, r1, r0
    1264:	01000005 	tsteq	r0, r5
    1268:	009e0501 	addseq	r0, lr, r1, lsl #10
    126c:	09590000 	ldmdbeq	r9, {}^	; <UNPREDICTABLE>
    1270:	18210000 	stmdane	r1!, {}	; <UNPREDICTABLE>
    1274:	01000005 	tsteq	r0, r5
    1278:	009e0502 	addseq	r0, lr, r2, lsl #10
    127c:	099d0000 	ldmibeq	sp, {}	; <UNPREDICTABLE>
    1280:	c6200000 	strtgt	r0, [r0], -r0
    1284:	d4000004 	strle	r0, [r0], #-4
    1288:	01000012 	tsteq	r0, r2, lsl r0
    128c:	01640305 	cmneq	r4, r5, lsl #6
    1290:	4c290000 	stcmi	0, cr0, [r9], #-0
    1294:	fc00000a 	stc2	0, cr0, [r0], {10}
    1298:	5400000e 	strpl	r0, [r0], #-14
    129c:	0100000f 	tsteq	r0, pc
    12a0:	12c10553 	sbcne	r0, r1, #348127232	; 0x14c00000
    12a4:	5a2a0000 	bpl	a812ac <wmt_core_func_ctrl_cmd+0xa7de8c>
    12a8:	2b00000a 	blcs	12d8 <.debug_info+0x12d8>
    12ac:	00000efc 	strdeq	r0, [r0], -ip
    12b0:	00000f54 	andeq	r0, r0, r4, asr pc
    12b4:	000a662c 	andeq	r6, sl, ip, lsr #12
    12b8:	d4030500 	strle	r0, [r3], #-1280	; 0xfffffb00
    12bc:	00000000 	andeq	r0, r0, r0
    12c0:	00002f00 	andeq	r2, r0, r0, lsl #30
    12c4:	5f1c0000 	svcpl	0x001c0000
    12c8:	01000014 	tsteq	r0, r4, lsl r0
    12cc:	009e0521 	addseq	r0, lr, r1, lsr #10
    12d0:	00000000 	andeq	r0, r0, r0
    12d4:	0000d309 	andeq	sp, r0, r9, lsl #6
    12d8:	c1011f00 	tstgt	r1, r0, lsl #30
    12dc:	01000009 	tsteq	r0, r9
    12e0:	8c01016a 	stfhis	f0, [r1], {106}	; 0x6a
    12e4:	e4000000 	str	r0, [r0], #-0
    12e8:	f8000010 			; <UNDEFINED> instruction: 0xf8000010
    12ec:	e1000010 	tst	r0, r0, lsl r0
    12f0:	44000009 	strmi	r0, [r0], #-9
    12f4:	1e000013 	mcrne	0, 0, r0, cr0, cr3, {0}
    12f8:	000013eb 	andeq	r1, r0, fp, ror #7
    12fc:	ec016b01 	stc	11, cr6, [r1], {1}
    1300:	0d000000 	stceq	0, cr0, [r0, #-0]
    1304:	1e00000a 	cdpne	0, 0, cr0, cr0, cr10, {0}
    1308:	00000c68 	andeq	r0, r0, r8, ror #24
    130c:	71016c01 	tstvc	r1, r1, lsl #24
    1310:	20000003 	andcs	r0, r0, r3
    1314:	1e00000a 	cdpne	0, 0, cr0, cr0, cr10, {0}
    1318:	00001340 	andeq	r1, r0, r0, asr #6
    131c:	76016d01 	strvc	r6, [r1], -r1, lsl #26
    1320:	33000003 	movwcc	r0, #3
    1324:	1e00000a 	cdpne	0, 0, cr0, cr0, cr10, {0}
    1328:	00001380 	andeq	r1, r0, r0, lsl #7
    132c:	44016e01 	strmi	r6, [r1], #-3585	; 0xfffff1ff
    1330:	46000013 			; <UNDEFINED> instruction: 0x46000013
    1334:	1c00000a 	stcne	0, cr0, [r0], {10}
    1338:	0000145f 	andeq	r1, r0, pc, asr r4
    133c:	8c017101 	stfhis	f7, [r1], {1}
    1340:	00000000 	andeq	r0, r0, r0
    1344:	0000c809 	andeq	ip, r0, r9, lsl #16
    1348:	34011f00 	strcc	r1, [r1], #-3840	; 0xfffff100
    134c:	0100000f 	tsteq	r0, pc
    1350:	8c010297 	sfmhi	f0, 4, [r1], {151}	; 0x97
    1354:	f8000000 			; <UNDEFINED> instruction: 0xf8000000
    1358:	1c000010 	stcne	0, cr0, [r0], {16}
    135c:	59000013 	stmdbpl	r0, {r0, r1, r4}
    1360:	d600000a 	strle	r0, [r0], -sl
    1364:	1e000013 	mcrne	0, 0, r0, cr0, cr3, {0}
    1368:	00000520 	andeq	r0, r0, r0, lsr #10
    136c:	d6029801 	strle	r9, [r2], -r1, lsl #16
    1370:	85000013 	strhi	r0, [r0, #-19]	; 0xffffffed
    1374:	1e00000a 	cdpne	0, 0, cr0, cr0, cr10, {0}
    1378:	00000b0a 	andeq	r0, r0, sl, lsl #22
    137c:	8c029901 	stchi	9, cr9, [r2], {1}
    1380:	b9000000 	stmdblt	r0, {}	; <UNPREDICTABLE>
    1384:	2800000a 	stmdacs	r0, {r1, r3}
    1388:	00000dd4 	ldrdeq	r0, [r0], -r4
    138c:	b0029c01 	andlt	r9, r2, r1, lsl #24
    1390:	03000009 	movweq	r0, #9
    1394:	217dcc91 			; <UNDEFINED> instruction: 0x217dcc91
    1398:	000012f0 	strdeq	r1, [r0], -r0
    139c:	9e029d01 	cdpls	13, 0, cr9, cr2, cr1, {0}
    13a0:	d7000000 	strle	r0, [r0, -r0]
    13a4:	2200000a 	andcs	r0, r0, #10
    13a8:	9e010069 	cdpls	0, 0, cr0, cr1, cr9, {3}
    13ac:	00008c02 	andeq	r8, r0, r2, lsl #24
    13b0:	000aeb00 	andeq	lr, sl, r0, lsl #22
    13b4:	145f2100 	ldrbne	r2, [pc], #-256	; 8 <.debug_info+0x8>
    13b8:	9f010000 	svcls	0x00010000
    13bc:	00008c02 	andeq	r8, r0, r2, lsl #24
    13c0:	000b0900 	andeq	r0, fp, r0, lsl #18
    13c4:	04c62000 	strbeq	r2, [r6], #0
    13c8:	13dc0000 	bicsne	r0, ip, #0
    13cc:	05010000 	streq	r0, [r1, #-0]
    13d0:	00017403 	andeq	r7, r1, r3, lsl #8
    13d4:	04040000 	streq	r0, [r4], #-0
    13d8:	00000924 	andeq	r0, r0, r4, lsr #18
    13dc:	000b8609 	andeq	r8, fp, r9, lsl #12
    13e0:	f0011f00 			; <UNDEFINED> instruction: 0xf0011f00
    13e4:	0100000d 	tsteq	r0, sp
    13e8:	8c010261 	sfmhi	f0, 4, [r1], {97}	; 0x61
    13ec:	1c000000 	stcne	0, cr0, [r0], {-0}
    13f0:	fc000013 	stc2	0, cr0, [r0], {19}
    13f4:	48000014 	stmdami	r0, {r2, r4}
    13f8:	b500000b 	strlt	r0, [r0, #-11]
    13fc:	1e000014 	mcrne	0, 0, r0, cr0, cr4, {0}
    1400:	00000ade 	ldrdeq	r0, [r0], -lr
    1404:	9e026201 	cdpls	2, 0, cr6, cr2, cr1, {0}
    1408:	74000000 	strvc	r0, [r0], #-0
    140c:	1e00000b 	cdpne	0, 0, cr0, cr0, cr11, {0}
    1410:	00000bb4 			; <UNDEFINED> instruction: 0x00000bb4
    1414:	9e026301 	cdpls	3, 0, cr6, cr2, cr1, {0}
    1418:	92000000 	andls	r0, r0, #0
    141c:	1e00000b 	cdpne	0, 0, cr0, cr0, cr11, {0}
    1420:	000003de 	ldrdeq	r0, [r0], -lr
    1424:	b0026401 	andlt	r6, r2, r1, lsl #8
    1428:	b2000000 	andlt	r0, r0, #0
    142c:	1e00000b 	cdpne	0, 0, cr0, cr0, cr11, {0}
    1430:	00000ac1 	andeq	r0, r0, r1, asr #21
    1434:	9e026501 	cfsh32ls	mvfx6, mvfx2, #1
    1438:	d0000000 	andle	r0, r0, r0
    143c:	2100000b 	tstcs	r0, fp
    1440:	0000145f 	andeq	r1, r0, pc, asr r4
    1444:	8c026801 	stchi	8, cr6, [r2], {1}
    1448:	f0000000 			; <UNDEFINED> instruction: 0xf0000000
    144c:	2800000b 	stmdacs	r0, {r0, r1, r3}
    1450:	000012f0 	strdeq	r1, [r0], -r0
    1454:	9e026901 	cdpls	9, 0, cr6, cr2, cr1, {0}
    1458:	02000000 	andeq	r0, r0, #0
    145c:	ab21587b 	blge	8561f4 <wmt_core_func_ctrl_cmd+0x852dd4>
    1460:	01000007 	tsteq	r0, r7
    1464:	009e026a 	addseq	r0, lr, sl, ror #4
    1468:	0c2f0000 	stceq	0, cr0, [pc], #-0	; 8 <.debug_info+0x8>
    146c:	d4280000 	strtle	r0, [r8], #-0
    1470:	0100000d 	tsteq	r0, sp
    1474:	014f026b 	cmpeq	pc, fp, ror #4
    1478:	91030000 	mrsls	r0, (UNDEF: 3)
    147c:	c6207fbc 			; <UNDEFINED> instruction: 0xc6207fbc
    1480:	b5000004 	strlt	r0, [r0, #-4]
    1484:	01000014 	tsteq	r0, r4, lsl r0
    1488:	018c0305 	orreq	r0, ip, r5, lsl #6
    148c:	182f0000 	stmdane	pc!, {}	; <UNPREDICTABLE>
    1490:	21000000 	mrscs	r0, (UNDEF: 0)
    1494:	000009a0 	andeq	r0, r0, r0, lsr #19
    1498:	9e028201 	cdpls	2, 0, cr8, cr2, cr1, {0}
    149c:	4d000000 	stcmi	0, cr0, [r0, #-0]
    14a0:	2100000c 	tstcs	r0, ip
    14a4:	00000fa7 	andeq	r0, r0, r7, lsr #31
    14a8:	9e028301 	cdpls	3, 0, cr8, cr2, cr1, {0}
    14ac:	79000000 	stmdbvc	r0, {}	; <UNPREDICTABLE>
    14b0:	0000000c 	andeq	r0, r0, ip
    14b4:	117d0900 	cmnne	sp, r0, lsl #18
    14b8:	471d0000 	ldrmi	r0, [sp, -r0]
    14bc:	01000011 	tsteq	r0, r1, lsl r0
    14c0:	8c0102c3 	sfmhi	f0, 4, [r1], {195}	; 0xc3
    14c4:	fc000000 	stc2	0, cr0, [r0], {-0}
    14c8:	90000014 	andls	r0, r0, r4, lsl r0
    14cc:	a500001b 	strge	r0, [r0, #-27]	; 0xffffffe5
    14d0:	7700000c 	strvc	r0, [r0, -ip]
    14d4:	21000015 	tstcs	r0, r5, lsl r0
    14d8:	0000145f 	andeq	r1, r0, pc, asr r4
    14dc:	8c02c501 	cfstr32hi	mvfx12, [r2], {1}
    14e0:	d1000000 	mrsle	r0, (UNDEF: 0)
    14e4:	2100000c 	tstcs	r0, ip
    14e8:	00000510 	andeq	r0, r0, r0, lsl r5
    14ec:	9e02c601 	cfmadd32ls	mvax0, mvfx12, mvfx2, mvfx1
    14f0:	2e000000 	cdpcs	0, 0, cr0, cr0, cr0, {0}
    14f4:	2100000e 	tstcs	r0, lr
    14f8:	00000518 	andeq	r0, r0, r8, lsl r5
    14fc:	9e02c701 	cdpls	7, 0, cr12, cr2, cr1, {0}
    1500:	66000000 	strvs	r0, [r0], -r0
    1504:	1c00000e 	stcne	0, cr0, [r0], {14}
    1508:	00000901 	andeq	r0, r0, r1, lsl #18
    150c:	1a02c801 	bne	b3518 <wmt_core_func_ctrl_cmd+0xb00f8>
    1510:	20000008 	andcs	r0, r0, r8
    1514:	000004c6 	andeq	r0, r0, r6, asr #9
    1518:	00001577 	andeq	r1, r0, r7, ror r5
    151c:	a0030501 	andge	r0, r3, r1, lsl #10
    1520:	30000001 	andcc	r0, r0, r1
    1524:	00000aaf 	andeq	r0, r0, pc, lsr #21
    1528:	00001624 	andeq	r1, r0, r4, lsr #12
    152c:	00000030 	andeq	r0, r0, r0, lsr r0
    1530:	2f032801 	svccs	0x00032801
    1534:	00000060 	andeq	r0, r0, r0, rrx
    1538:	000ac131 	andeq	ip, sl, r1, lsr r1
    153c:	000e9e00 	andeq	r9, lr, r0, lsl #28
    1540:	0acd3100 	beq	ff34d948 <wmt_core_func_ctrl_cmd+0xff34a528>
    1544:	0eee0000 	cdpeq	0, 14, cr0, cr14, cr0, {0}
    1548:	d9310000 	ldmdble	r1!, {}	; <UNPREDICTABLE>
    154c:	2d00000a 	stccs	0, cr0, [r0, #-40]	; 0xffffffd8
    1550:	2c00000f 	stccs	0, cr0, [r0], {15}
    1554:	00000ae5 	andeq	r0, r0, r5, ror #21
    1558:	01b40305 			; <UNDEFINED> instruction: 0x01b40305
    155c:	90300000 	eorsls	r0, r0, r0
    1560:	1400000a 	strne	r0, [r0], #-10
    1564:	90000018 	andls	r0, r0, r8, lsl r0
    1568:	01000000 	mrseq	r0, (UNDEF: 0)
    156c:	a22a03d1 	eorge	r0, sl, #1140850691	; 0x44000003
    1570:	0000000a 	andeq	r0, r0, sl
    1574:	09000000 	stmdbeq	r0, {}	; <UNPREDICTABLE>
    1578:	00000af4 	strdeq	r0, [r0], -r4
    157c:	0014031d 	andseq	r0, r4, sp, lsl r3
    1580:	07660100 	strbeq	r0, [r6, -r0, lsl #2]!
    1584:	00008c01 	andeq	r8, r0, r1, lsl #24
    1588:	001b9000 	andseq	r9, fp, r0
    158c:	001ba400 	andseq	sl, fp, r0, lsl #8
    1590:	000f7700 	andeq	r7, pc, r0, lsl #14
    1594:	0015aa00 	andseq	sl, r5, r0, lsl #20
    1598:	0b101e00 	bleq	407808 <wmt_core_func_ctrl_cmd+0x4043e8>
    159c:	66010000 	strvs	r0, [r1], -r0
    15a0:	00036607 	andeq	r6, r3, r7, lsl #12
    15a4:	000fa300 	andeq	sl, pc, r0, lsl #6
    15a8:	c31d0000 	tstgt	sp, #0
    15ac:	01000008 	tsteq	r0, r8
    15b0:	8c0103fc 	stchi	3, cr0, [r1], {252}	; 0xfc
    15b4:	a4000000 	strge	r0, [r0], #-0
    15b8:	8400001b 	strhi	r0, [r0], #-27	; 0xffffffe5
    15bc:	b600001d 			; <UNDEFINED> instruction: 0xb600001d
    15c0:	2c00000f 	stccs	0, cr0, [r0], {15}
    15c4:	1e000016 	mcrne	0, 0, r0, cr0, cr6, {0}
    15c8:	00000b10 	andeq	r0, r0, r0, lsl fp
    15cc:	6603fc01 	strvs	pc, [r3], -r1, lsl #24
    15d0:	e2000003 	and	r0, r0, #3
    15d4:	2100000f 	tstcs	r0, pc
    15d8:	0000145f 	andeq	r1, r0, pc, asr r4
    15dc:	8c03ff01 	stchi	15, cr15, [r3], {1}
    15e0:	16000000 	strne	r0, [r0], -r0
    15e4:	21000010 	tstcs	r0, r0, lsl r0
    15e8:	00000510 	andeq	r0, r0, r0, lsl r5
    15ec:	9e040001 	cdpls	0, 0, cr0, cr4, cr1, {0}
    15f0:	97000000 	strls	r0, [r0, -r0]
    15f4:	21000010 	tstcs	r0, r0, lsl r0
    15f8:	00000518 	andeq	r0, r0, r8, lsl r5
    15fc:	9e040101 	adflss	f0, f4, f1
    1600:	b7000000 	strlt	r0, [r0, -r0]
    1604:	1c000010 	stcne	0, cr0, [r0], {16}
    1608:	00001039 	andeq	r1, r0, r9, lsr r0
    160c:	8c040201 	sfmhi	f0, 4, [r4], {1}
    1610:	20000000 	andcs	r0, r0, r0
    1614:	000004c6 	andeq	r0, r0, r6, asr #9
    1618:	0000162c 	andeq	r1, r0, ip, lsr #12
    161c:	c8030501 	stmdagt	r3, {r0, r8, sl}
    1620:	32000001 	andcc	r0, r0, #1
    1624:	00000136 	andeq	r0, r0, r6, lsr r1
    1628:	00041901 	andeq	r1, r4, r1, lsl #18
    162c:	000c4e09 	andeq	r4, ip, r9, lsl #28
    1630:	0f011d00 	svceq	0x00011d00
    1634:	69010000 	stmdbvs	r1, {}	; <UNPREDICTABLE>
    1638:	008c0104 	addeq	r0, ip, r4, lsl #2
    163c:	1d840000 	stcne	0, cr0, [r4]
    1640:	21e80000 	mvncs	r0, r0
    1644:	10d70000 	sbcsne	r0, r7, r0
    1648:	16e60000 	strbtne	r0, [r6], r0
    164c:	101e0000 	andsne	r0, lr, r0
    1650:	0100000b 	tsteq	r0, fp
    1654:	0366046a 	cmneq	r6, #1778384896	; 0x6a000000
    1658:	11030000 	mrsne	r0, (UNDEF: 3)
    165c:	5f210000 	svcpl	0x00210000
    1660:	01000014 	tsteq	r0, r4, lsl r0
    1664:	008c046d 	addeq	r0, ip, sp, ror #8
    1668:	11370000 	teqne	r7, r0
    166c:	46210000 	strtmi	r0, [r1], -r0
    1670:	0100000d 	tsteq	r0, sp
    1674:	008c046e 	addeq	r0, ip, lr, ror #8
    1678:	12260000 	eorne	r0, r6, #0
    167c:	c0210000 	eorgt	r0, r1, r0
    1680:	0100000f 	tsteq	r0, pc
    1684:	009e046f 	addseq	r0, lr, pc, ror #8
    1688:	12440000 	subne	r0, r4, #0
    168c:	10210000 	eorne	r0, r1, r0
    1690:	01000005 	tsteq	r0, r5
    1694:	009e0470 	addseq	r0, lr, r0, ror r4
    1698:	12620000 	rsbne	r0, r2, #0
    169c:	18210000 	stmdane	r1!, {}	; <UNPREDICTABLE>
    16a0:	01000005 	tsteq	r0, r5
    16a4:	009e0471 	addseq	r0, lr, r1, ror r4
    16a8:	12a60000 	adcne	r0, r6, #0
    16ac:	c6200000 	strtgt	r0, [r0], -r0
    16b0:	e6000004 	str	r0, [r0], -r4
    16b4:	01000016 	tsteq	r0, r6, lsl r0
    16b8:	01d80305 	bicseq	r0, r8, r5, lsl #6
    16bc:	4c300000 	ldcmi	0, cr0, [r0], #-0
    16c0:	e400000a 	str	r0, [r0], #-10
    16c4:	b000001d 	andlt	r0, r0, sp, lsl r0
    16c8:	01000000 	mrseq	r0, (UNDEF: 0)
    16cc:	5a2a04f7 	bpl	a82ab0 <wmt_core_func_ctrl_cmd+0xa7f690>
    16d0:	2f00000a 	svccs	0x0000000a
    16d4:	000000c8 	andeq	r0, r0, r8, asr #1
    16d8:	000a662c 	andeq	r6, sl, ip, lsr #12
    16dc:	d4030500 	strle	r0, [r3], #-1280	; 0xfffffb00
    16e0:	00000000 	andeq	r0, r0, r0
    16e4:	00090000 	andeq	r0, r9, r0
    16e8:	1d000012 	stcne	0, cr0, [r0, #-72]	; 0xffffffb8
    16ec:	00000651 	andeq	r0, r0, r1, asr r6
    16f0:	01055901 	tsteq	r5, r1, lsl #18
    16f4:	0000008c 	andeq	r0, r0, ip, lsl #1
    16f8:	000021e8 	andeq	r2, r0, r8, ror #3
    16fc:	00002244 	andeq	r2, r0, r4, asr #4
    1700:	000012ea 	andeq	r1, r0, sl, ror #5
    1704:	00001737 	andeq	r1, r0, r7, lsr r7
    1708:	000b101e 	andeq	r1, fp, lr, lsl r0
    170c:	055a0100 	ldrbeq	r0, [sl, #-256]	; 0xffffff00
    1710:	00000366 	andeq	r0, r0, r6, ror #6
    1714:	00001316 	andeq	r1, r0, r6, lsl r3
    1718:	0008e228 	andeq	lr, r8, r8, lsr #4
    171c:	055d0100 	ldrbeq	r0, [sp, #-256]	; 0xffffff00
    1720:	0000008c 	andeq	r0, r0, ip, lsl #1
    1724:	c6205001 	strtgt	r5, [r0], -r1
    1728:	37000004 	strcc	r0, [r0, -r4]
    172c:	01000017 	tsteq	r0, r7, lsl r0
    1730:	01e80305 	mvneq	r0, r5, lsl #6
    1734:	09000000 	stmdbeq	r0, {}	; <UNPREDICTABLE>
    1738:	00000c4e 	andeq	r0, r0, lr, asr #24
    173c:	0013891d 	andseq	r8, r3, sp, lsl r9
    1740:	07c10100 	strbeq	r0, [r1, r0, lsl #2]
    1744:	00008c01 	andeq	r8, r0, r1, lsl #24
    1748:	00224400 	eoreq	r4, r2, r0, lsl #8
    174c:	0023b800 	eoreq	fp, r3, r0, lsl #16
    1750:	00133f00 	andseq	r3, r3, r0, lsl #30
    1754:	0017b500 	andseq	fp, r7, r0, lsl #10
    1758:	0b101e00 	bleq	407808 <wmt_core_func_ctrl_cmd+0x4043e8>
    175c:	c1010000 	mrsgt	r0, (UNDEF: 1)
    1760:	00036607 	andeq	r6, r3, r7, lsl #12
    1764:	00136b00 	andseq	r6, r3, r0, lsl #22
    1768:	145f2100 	ldrbne	r2, [pc], #-256	; 8 <.debug_info+0x8>
    176c:	c4010000 	strgt	r0, [r1], #-0
    1770:	00008c07 	andeq	r8, r0, r7, lsl #24
    1774:	00138900 	andseq	r8, r3, r0, lsl #18
    1778:	12f02100 	rscsne	r2, r0, #0, 2
    177c:	c5010000 	strgt	r0, [r1, #-0]
    1780:	00009e07 	andeq	r9, r0, r7, lsl #28
    1784:	0013a700 	andseq	sl, r3, r0, lsl #14
    1788:	07ab1c00 	streq	r1, [fp, r0, lsl #24]!
    178c:	c6010000 	strgt	r0, [r1], -r0
    1790:	00009e07 	andeq	r9, r0, r7, lsl #28
    1794:	0dd42800 	ldcleq	8, cr2, [r4]
    1798:	c7010000 	strgt	r0, [r1, -r0]
    179c:	00014f07 	andeq	r4, r1, r7, lsl #30
    17a0:	44910200 	ldrmi	r0, [r1], #512	; 0x200
    17a4:	0004c620 	andeq	ip, r4, r0, lsr #12
    17a8:	0017b500 	andseq	fp, r7, r0, lsl #10
    17ac:	03050100 	movweq	r0, #20736	; 0x5100
    17b0:	000001f8 	strdeq	r0, [r0], -r8
    17b4:	00d30900 	sbcseq	r0, r3, r0, lsl #18
    17b8:	201d0000 	andscs	r0, sp, r0
    17bc:	01000008 	tsteq	r0, r8
    17c0:	8c010785 	stchi	7, cr0, [r1], {133}	; 0x85
    17c4:	b8000000 	stmdalt	r0, {}	; <UNPREDICTABLE>
    17c8:	58000023 	stmdapl	r0, {r0, r1, r5}
    17cc:	bb000026 	bllt	a0 <.debug_info+0xa0>
    17d0:	31000013 	tstcc	r0, r3, lsl r0
    17d4:	1e000018 	mcrne	0, 0, r0, cr0, cr8, {0}
    17d8:	00000b10 	andeq	r0, r0, r0, lsl fp
    17dc:	66078501 	strvs	r8, [r7], -r1, lsl #10
    17e0:	e7000003 	str	r0, [r0, -r3]
    17e4:	28000013 	stmdacs	r0, {r0, r1, r4}
    17e8:	0000145f 	andeq	r1, r0, pc, asr r4
    17ec:	8c078801 	stchi	8, cr8, [r7], {1}
    17f0:	01000000 	mrseq	r0, (UNDEF: 0)
    17f4:	12f02854 	rscsne	r2, r0, #84, 16	; 0x540000
    17f8:	89010000 	stmdbhi	r1, {}	; <UNPREDICTABLE>
    17fc:	00009e07 	andeq	r9, r0, r7, lsl #28
    1800:	507b0200 	rsbspl	r0, fp, r0, lsl #4
    1804:	0007ab1c 	andeq	sl, r7, ip, lsl fp
    1808:	078a0100 	streq	r0, [sl, r0, lsl #2]
    180c:	0000009e 	muleq	r0, lr, r0
    1810:	000dd428 	andeq	sp, sp, r8, lsr #8
    1814:	078b0100 	streq	r0, [fp, r0, lsl #2]
    1818:	0000014f 	andeq	r0, r0, pc, asr #2
    181c:	7fbc9103 	svcvc	0x00bc9103
    1820:	0004c620 	andeq	ip, r4, r0, lsr #12
    1824:	00183100 	andseq	r3, r8, r0, lsl #2
    1828:	03050100 	movweq	r0, #20736	; 0x5100
    182c:	00000208 	andeq	r0, r0, r8, lsl #4
    1830:	0af40900 	beq	ffd03c38 <wmt_core_func_ctrl_cmd+0xffd00818>
    1834:	fa1d0000 	blx	740008 <wmt_core_func_ctrl_cmd+0x73cbe8>
    1838:	0100000a 	tsteq	r0, sl
    183c:	8c010673 	stchi	6, cr0, [r1], {115}	; 0x73
    1840:	58000000 	stmdapl	r0, {}	; <UNPREDICTABLE>
    1844:	9c000026 	stcls	0, cr0, [r0], {38}	; 0x26
    1848:	0500002a 	streq	r0, [r0, #-42]	; 0xffffffd6
    184c:	a3000014 	movwge	r0, #20
    1850:	1e000019 	mcrne	0, 0, r0, cr0, cr9, {0}
    1854:	00000b10 	andeq	r0, r0, r0, lsl fp
    1858:	66067301 	strvs	r7, [r6], -r1, lsl #6
    185c:	31000003 	tstcc	r0, r3
    1860:	21000014 	tstcs	r0, r4, lsl r0
    1864:	0000145f 	andeq	r1, r0, pc, asr r4
    1868:	8c067601 	stchi	6, cr7, [r6], {1}
    186c:	44000000 	strmi	r0, [r0], #-0
    1870:	21000014 	tstcs	r0, r4, lsl r0
    1874:	0000015d 	andeq	r0, r0, sp, asr r1
    1878:	9e067701 	cdpls	7, 0, cr7, cr6, cr1, {0}
    187c:	83000000 	movwhi	r0, #0
    1880:	28000014 	stmdacs	r0, {r2, r4}
    1884:	00000dcc 	andeq	r0, r0, ip, asr #27
    1888:	9e067801 	cdpls	8, 0, cr7, cr6, cr1, {0}
    188c:	03000000 	movweq	r0, #0
    1890:	287db47b 	ldmdacs	sp!, {r0, r1, r3, r4, r5, r6, sl, ip, sp, pc}^
    1894:	00000c5a 	andeq	r0, r0, sl, asr ip
    1898:	a3067a01 	movwge	r7, #27137	; 0x6a01
    189c:	03000019 	movweq	r0, #25
    18a0:	287ebc91 	ldmdacs	lr!, {r0, r4, r7, sl, fp, ip, sp, pc}^
    18a4:	0000069f 	muleq	r0, pc, r6	; <UNPREDICTABLE>
    18a8:	a3067b01 	movwge	r7, #27393	; 0x6b01
    18ac:	03000019 	movweq	r0, #25
    18b0:	287dfc91 	ldmdacs	sp!, {r0, r4, r7, sl, fp, ip, sp, lr, pc}^
    18b4:	00000461 	andeq	r0, r0, r1, ror #8
    18b8:	a3067c01 	movwge	r7, #27649	; 0x6c01
    18bc:	03000019 	movweq	r0, #25
    18c0:	217dbc91 			; <UNDEFINED> instruction: 0x217dbc91
    18c4:	000012f0 	strdeq	r1, [r0], -r0
    18c8:	9e067d01 	cdpls	13, 0, cr7, cr6, cr1, {0}
    18cc:	ac000000 	stcge	0, cr0, [r0], {-0}
    18d0:	21000014 	tstcs	r0, r4, lsl r0
    18d4:	00000cb8 			; <UNDEFINED> instruction: 0x00000cb8
    18d8:	9e067e01 	cdpls	14, 0, cr7, cr6, cr1, {0}
    18dc:	e4000000 	str	r0, [r0], #-0
    18e0:	21000014 	tstcs	r0, r4, lsl r0
    18e4:	000002e5 	andeq	r0, r0, r5, ror #5
    18e8:	9e067f01 	cdpls	15, 0, cr7, cr6, cr1, {0}
    18ec:	39000000 	stmdbcc	r0, {}	; <UNPREDICTABLE>
    18f0:	28000015 	stmdacs	r0, {r0, r2, r4}
    18f4:	00000ae6 	andeq	r0, r0, r6, ror #21
    18f8:	e6068101 	str	r8, [r6], -r1, lsl #2
    18fc:	03000000 	movweq	r0, #0
    1900:	217db07b 	cmncs	sp, fp, ror r0
    1904:	000009aa 	andeq	r0, r0, sl, lsr #19
    1908:	9e068201 	cdpls	2, 0, cr8, cr6, cr1, {0}
    190c:	83000000 	movwhi	r0, #0
    1910:	28000015 	stmdacs	r0, {r0, r2, r4}
    1914:	000000ed 	andeq	r0, r0, sp, ror #1
    1918:	b3068501 	movwlt	r8, #25857	; 0x6501
    191c:	02000019 	andeq	r0, r0, #25
    1920:	b2284491 	eorlt	r4, r8, #-1862270976	; 0x91000000
    1924:	0100000a 	tsteq	r0, sl
    1928:	19b30686 	ldmibne	r3!, {r1, r2, r7, r9, sl}
    192c:	91030000 	mrsls	r0, (UNDEF: 3)
    1930:	dc287fbc 	stcle	15, cr7, [r8], #-752	; 0xfffffd10
    1934:	0100000e 	tsteq	r0, lr
    1938:	19b30687 	ldmibne	r3!, {r0, r1, r2, r7, r9, sl}
    193c:	91030000 	mrsls	r0, (UNDEF: 3)
    1940:	18287fb4 	stmdane	r8!, {r2, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr}
    1944:	01000009 	tsteq	r0, r9
    1948:	19b30688 	ldmibne	r3!, {r3, r7, r9, sl}
    194c:	91030000 	mrsls	r0, (UNDEF: 3)
    1950:	a8287fac 	stmdage	r8!, {r2, r3, r5, r7, r8, r9, sl, fp, ip, sp, lr}
    1954:	0100000c 	tsteq	r0, ip
    1958:	19c3068a 	stmibne	r3, {r1, r3, r7, r9, sl}^
    195c:	91030000 	mrsls	r0, (UNDEF: 3)
    1960:	4b287fa4 	blmi	a1fe98 <wmt_core_func_ctrl_cmd+0xa1ca78>
    1964:	01000007 	tsteq	r0, r7
    1968:	19d3068e 	ldmibne	r3, {r1, r2, r3, r7, r9, sl}^
    196c:	91030000 	mrsls	r0, (UNDEF: 3)
    1970:	23287f98 	teqcs	r8, #152, 30	; 0x260
    1974:	01000004 	tsteq	r0, r4
    1978:	19e30692 	stmibne	r3!, {r1, r4, r7, r9, sl}^
    197c:	91030000 	mrsls	r0, (UNDEF: 3)
    1980:	8b287f8c 	blhi	a1fe38 <wmt_core_func_ctrl_cmd+0xa1ca18>
    1984:	01000001 	tsteq	r0, r1
    1988:	19f30696 	ldmibne	r3!, {r1, r2, r4, r7, r9, sl}^
    198c:	91030000 	mrsls	r0, (UNDEF: 3)
    1990:	c6207efc 			; <UNDEFINED> instruction: 0xc6207efc
    1994:	03000004 	movweq	r0, #4
    1998:	0100001a 	tsteq	r0, sl, lsl r0
    199c:	026c0305 	rsbeq	r0, ip, #335544320	; 0x14000000
    19a0:	06000000 	streq	r0, [r0], -r0
    19a4:	0000003e 	andeq	r0, r0, lr, lsr r0
    19a8:	000019b3 			; <UNDEFINED> instruction: 0x000019b3
    19ac:	0000e307 	andeq	lr, r0, r7, lsl #6
    19b0:	06003f00 	streq	r3, [r0], -r0, lsl #30
    19b4:	0000003e 	andeq	r0, r0, lr, lsr r0
    19b8:	000019c3 	andeq	r1, r0, r3, asr #19
    19bc:	0000e307 	andeq	lr, r0, r7, lsl #6
    19c0:	06000400 	streq	r0, [r0], -r0, lsl #8
    19c4:	0000003e 	andeq	r0, r0, lr, lsr r0
    19c8:	000019d3 	ldrdeq	r1, [r0], -r3
    19cc:	0000e307 	andeq	lr, r0, r7, lsl #6
    19d0:	06000500 	streq	r0, [r0], -r0, lsl #10
    19d4:	0000003e 	andeq	r0, r0, lr, lsr r0
    19d8:	000019e3 	andeq	r1, r0, r3, ror #19
    19dc:	0000e307 	andeq	lr, r0, r7, lsl #6
    19e0:	06000800 	streq	r0, [r0], -r0, lsl #16
    19e4:	0000003e 	andeq	r0, r0, lr, lsr r0
    19e8:	000019f3 	strdeq	r1, [r0], -r3
    19ec:	0000e307 	andeq	lr, r0, r7, lsl #6
    19f0:	06000a00 	streq	r0, [r0], -r0, lsl #20
    19f4:	0000003e 	andeq	r0, r0, lr, lsr r0
    19f8:	00001a03 	andeq	r1, r0, r3, lsl #20
    19fc:	0000e307 	andeq	lr, r0, r7, lsl #6
    1a00:	09000c00 	stmdbeq	r0, {sl, fp}
    1a04:	000000d3 	ldrdeq	r0, [r0], -r3
    1a08:	000a411d 	andeq	r4, sl, sp, lsl r1
    1a0c:	06260100 	strteq	r0, [r6], -r0, lsl #2
    1a10:	00008c01 	andeq	r8, r0, r1, lsl #24
    1a14:	002a9c00 	eoreq	r9, sl, r0, lsl #24
    1a18:	002cf400 	eoreq	pc, ip, r0, lsl #8
    1a1c:	0015b700 	andseq	fp, r5, r0, lsl #14
    1a20:	001aca00 	andseq	ip, sl, r0, lsl #20
    1a24:	0b101e00 	bleq	407808 <wmt_core_func_ctrl_cmd+0x4043e8>
    1a28:	26010000 	strcs	r0, [r1], -r0
    1a2c:	00036606 	andeq	r6, r3, r6, lsl #12
    1a30:	0015e300 	andseq	lr, r5, r0, lsl #6
    1a34:	145f1c00 	ldrbne	r1, [pc], #-3072	; 8 <.debug_info+0x8>
    1a38:	29010000 	stmdbcs	r1, {}	; <UNPREDICTABLE>
    1a3c:	00008c06 	andeq	r8, r0, r6, lsl #24
    1a40:	03d02800 	bicseq	r2, r0, #0, 16
    1a44:	2a010000 	bcs	41a4c <wmt_core_func_ctrl_cmd+0x3e62c>
    1a48:	00009e06 	andeq	r9, r0, r6, lsl #28
    1a4c:	4c7b0200 	lfmmi	f0, 2, [fp], #-0
    1a50:	0012c428 	andseq	ip, r2, r8, lsr #8
    1a54:	062b0100 	strteq	r0, [fp], -r0, lsl #2
    1a58:	0000009e 	muleq	r0, lr, r0
    1a5c:	28487b02 	stmdacs	r8, {r1, r8, r9, fp, ip, sp, lr}^
    1a60:	00000180 	andeq	r0, r0, r0, lsl #3
    1a64:	9e062c01 	cdpls	12, 0, cr2, cr6, cr1, {0}
    1a68:	01000000 	mrseq	r0, (UNDEF: 0)
    1a6c:	05ec1c5a 	strbeq	r1, [ip, #3162]!	; 0xc5a
    1a70:	2d010000 	stccs	0, cr0, [r1, #-0]
    1a74:	00037606 	andeq	r7, r3, r6, lsl #12
    1a78:	0c312100 	ldfeqs	f2, [r1], #-0
    1a7c:	2e010000 	cdpcs	0, 0, cr0, cr1, cr0, {0}
    1a80:	00007306 	andeq	r7, r0, r6, lsl #6
    1a84:	00160100 	andseq	r0, r6, r0, lsl #2
    1a88:	080e2800 	stmdaeq	lr, {fp, sp}
    1a8c:	30010000 	andcc	r0, r1, r0
    1a90:	0019b306 	andseq	fp, r9, r6, lsl #6
    1a94:	bc910300 	ldclt	3, cr0, [r1], {0}
    1a98:	0221287f 	eoreq	r2, r1, #8323072	; 0x7f0000
    1a9c:	31010000 	mrscc	r0, (UNDEF: 1)
    1aa0:	0019b306 	andseq	fp, r9, r6, lsl #6
    1aa4:	b4910300 	ldrlt	r0, [r1], #768	; 0x300
    1aa8:	053e217f 	ldreq	r2, [lr, #-383]!	; 0xfffffe81
    1aac:	34010000 	strcc	r0, [r1], #-0
    1ab0:	0000c806 	andeq	ip, r0, r6, lsl #16
    1ab4:	00162100 	andseq	r2, r6, r0, lsl #2
    1ab8:	04c62000 	strbeq	r2, [r6], #0
    1abc:	1aca0000 	bne	ff281ac4 <wmt_core_func_ctrl_cmd+0xff27e6a4>
    1ac0:	05010000 	streq	r0, [r1, #-0]
    1ac4:	00028c03 	andeq	r8, r2, r3, lsl #24
    1ac8:	4d090000 	stcmi	0, cr0, [r9, #-0]
    1acc:	1d000010 	stcne	0, cr0, [r0, #-64]	; 0xffffffc0
    1ad0:	00000971 	andeq	r0, r0, r1, ror r9
    1ad4:	0105fd01 	tsteq	r5, r1, lsl #26
    1ad8:	0000008c 	andeq	r0, r0, ip, lsl #1
    1adc:	00002cf4 	strdeq	r2, [r0], -r4
    1ae0:	00002eb4 			; <UNDEFINED> instruction: 0x00002eb4
    1ae4:	0000166b 	andeq	r1, r0, fp, ror #12
    1ae8:	00001b46 	andeq	r1, r0, r6, asr #22
    1aec:	000b101e 	andeq	r1, fp, lr, lsl r0
    1af0:	05fd0100 	ldrbeq	r0, [sp, #256]!	; 0x100
    1af4:	00000366 	andeq	r0, r0, r6, ror #6
    1af8:	00001697 	muleq	r0, r7, r6
    1afc:	00145f28 	andseq	r5, r4, r8, lsr #30
    1b00:	06000100 	streq	r0, [r0], -r0, lsl #2
    1b04:	0000008c 	andeq	r0, r0, ip, lsl #1
    1b08:	f0285501 			; <UNDEFINED> instruction: 0xf0285501
    1b0c:	01000012 	tsteq	r0, r2, lsl r0
    1b10:	009e0601 	addseq	r0, lr, r1, lsl #12
    1b14:	7b020000 	blvc	81b1c <wmt_core_func_ctrl_cmd+0x7e6fc>
    1b18:	07ab1c50 	sbfxeq	r1, r0, #24, #12
    1b1c:	02010000 	andeq	r0, r1, #0
    1b20:	00009e06 	andeq	r9, r0, r6, lsl #28
    1b24:	0dd42800 	ldcleq	8, cr2, [r4]
    1b28:	03010000 	movweq	r0, #4096	; 0x1000
    1b2c:	00014f06 	andeq	r4, r1, r6, lsl #30
    1b30:	bc910300 	ldclt	3, cr0, [r1], {0}
    1b34:	04c6207f 	strbeq	r2, [r6], #127	; 0x7f
    1b38:	1b460000 	blne	1181b40 <wmt_core_func_ctrl_cmd+0x117e720>
    1b3c:	05010000 	streq	r0, [r1, #-0]
    1b40:	00029803 	andeq	r9, r2, r3, lsl #16
    1b44:	4d090000 	stcmi	0, cr0, [r9, #-0]
    1b48:	1d000010 	stcne	0, cr0, [r0, #-64]	; 0xffffffc0
    1b4c:	00000e04 	andeq	r0, r0, r4, lsl #28
    1b50:	01057501 	tsteq	r5, r1, lsl #10
    1b54:	0000008c 	andeq	r0, r0, ip, lsl #1
    1b58:	00002eb4 			; <UNDEFINED> instruction: 0x00002eb4
    1b5c:	00003420 	andeq	r3, r0, r0, lsr #8
    1b60:	000016b5 			; <UNDEFINED> instruction: 0x000016b5
    1b64:	00001bed 	andeq	r1, r0, sp, ror #23
    1b68:	000b101e 	andeq	r1, fp, lr, lsl r0
    1b6c:	05750100 	ldrbeq	r0, [r5, #-256]!	; 0xffffff00
    1b70:	00000366 	andeq	r0, r0, r6, ror #6
    1b74:	000016e1 	andeq	r1, r0, r1, ror #13
    1b78:	74657222 	strbtvc	r7, [r5], #-546	; 0xfffffdde
    1b7c:	05770100 	ldrbeq	r0, [r7, #-256]!	; 0xffffff00
    1b80:	0000008c 	andeq	r0, r0, ip, lsl #1
    1b84:	000016ff 	strdeq	r1, [r0], -pc	; <UNPREDICTABLE>
    1b88:	0007b221 	andeq	fp, r7, r1, lsr #4
    1b8c:	05780100 	ldrbeq	r0, [r8, #-256]!	; 0xffffff00
    1b90:	0000009e 	muleq	r0, lr, r0
    1b94:	00001733 	andeq	r1, r0, r3, lsr r7
    1b98:	000a981c 	andeq	r9, sl, ip, lsl r8
    1b9c:	05790100 	ldrbeq	r0, [r9, #-256]!	; 0xffffff00
    1ba0:	0000009e 	muleq	r0, lr, r0
    1ba4:	0000d528 	andeq	sp, r0, r8, lsr #10
    1ba8:	057a0100 	ldrbeq	r0, [sl, #-256]!	; 0xffffff00
    1bac:	0000014f 	andeq	r0, r0, pc, asr #2
    1bb0:	7fbc9103 	svcvc	0x00bc9103
    1bb4:	0011b412 	andseq	fp, r1, r2, lsl r4
    1bb8:	057c0100 	ldrbeq	r0, [ip, #-256]!	; 0xffffff00
    1bbc:	00000a36 	andeq	r0, r0, r6, lsr sl
    1bc0:	000c5321 	andeq	r5, ip, r1, lsr #6
    1bc4:	057d0100 	ldrbeq	r0, [sp, #-256]!	; 0xffffff00
    1bc8:	00001bb4 			; <UNDEFINED> instruction: 0x00001bb4
    1bcc:	000017e9 	andeq	r1, r0, r9, ror #15
    1bd0:	0004c620 	andeq	ip, r4, r0, lsr #12
    1bd4:	001bed00 	andseq	lr, fp, r0, lsl #26
    1bd8:	03050100 	movweq	r0, #20736	; 0x5100
    1bdc:	000002a4 	andeq	r0, r0, r4, lsr #5
    1be0:	0013742e 	andseq	r7, r3, lr, lsr #8
    1be4:	05ed0100 	strbeq	r0, [sp, #256]!	; 0x100
    1be8:	00002fcc 	andeq	r2, r0, ip, asr #31
    1bec:	0c4e0900 	mcrreq	9, 0, r0, lr, cr0
    1bf0:	011f0000 	tsteq	pc, r0
    1bf4:	0000066f 	andeq	r0, r0, pc, ror #12
    1bf8:	0101a901 	tsteq	r1, r1, lsl #18
    1bfc:	0000008c 	andeq	r0, r0, ip, lsl #1
    1c00:	00003420 	andeq	r3, r0, r0, lsr #8
    1c04:	000035b8 			; <UNDEFINED> instruction: 0x000035b8
    1c08:	00001807 	andeq	r1, r0, r7, lsl #16
    1c0c:	00001cb3 			; <UNDEFINED> instruction: 0x00001cb3
    1c10:	0001d91e 	andeq	sp, r1, lr, lsl r9
    1c14:	01aa0100 			; <UNDEFINED> instruction: 0x01aa0100
    1c18:	0000029a 	muleq	r0, sl, r2
    1c1c:	00001833 	andeq	r1, r0, r3, lsr r8
    1c20:	00111a1e 	andseq	r1, r1, lr, lsl sl
    1c24:	01ab0100 			; <UNDEFINED> instruction: 0x01ab0100
    1c28:	000000c8 	andeq	r0, r0, r8, asr #1
    1c2c:	00001851 	andeq	r1, r0, r1, asr r8
    1c30:	00145f21 	andseq	r5, r4, r1, lsr #30
    1c34:	01ae0100 			; <UNDEFINED> instruction: 0x01ae0100
    1c38:	0000008c 	andeq	r0, r0, ip, lsl #1
    1c3c:	0000186f 	andeq	r1, r0, pc, ror #16
    1c40:	0006df1c 	andeq	sp, r6, ip, lsl pc
    1c44:	01af0100 			; <UNDEFINED> instruction: 0x01af0100
    1c48:	0000009e 	muleq	r0, lr, r0
    1c4c:	000b591c 	andeq	r5, fp, ip, lsl r9
    1c50:	01b00100 	lslseq	r0, r0, #2
    1c54:	0000009e 	muleq	r0, lr, r0
    1c58:	0012c428 	andseq	ip, r2, r8, lsr #8
    1c5c:	01b10100 			; <UNDEFINED> instruction: 0x01b10100
    1c60:	0000009e 	muleq	r0, lr, r0
    1c64:	285c9102 	ldmdacs	ip, {r1, r8, ip, pc}^
    1c68:	000003d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
    1c6c:	9e01b201 	cdpls	2, 0, cr11, cr1, cr1, {0}
    1c70:	02000000 	andeq	r0, r0, #0
    1c74:	88285891 	stmdahi	r8!, {r0, r4, r7, fp, ip, lr}
    1c78:	01000010 	tsteq	r0, r0, lsl r0
    1c7c:	088601b3 	stmeq	r6, {r0, r1, r4, r5, r7, r8}
    1c80:	91030000 	mrsls	r0, (UNDEF: 3)
    1c84:	e0287fb4 			; <UNDEFINED> instruction: 0xe0287fb4
    1c88:	01000010 	tsteq	r0, r0, lsl r0
    1c8c:	088601b4 	stmeq	r6, {r2, r4, r5, r7, r8}
    1c90:	91030000 	mrsls	r0, (UNDEF: 3)
    1c94:	3e1c7f90 	mrccc	15, 0, r7, cr12, cr0, {4}
    1c98:	01000005 	tsteq	r0, r5
    1c9c:	00c801b5 	strheq	r0, [r8], #21
    1ca0:	c6200000 	strtgt	r0, [r0], -r0
    1ca4:	c3000004 	movwgt	r0, #4
    1ca8:	0100001c 	tsteq	r0, ip, lsl r0
    1cac:	02e00305 	rsceq	r0, r0, #335544320	; 0x14000000
    1cb0:	06000000 	streq	r0, [r0], -r0
    1cb4:	00000030 	andeq	r0, r0, r0, lsr r0
    1cb8:	00001cc3 	andeq	r1, r0, r3, asr #25
    1cbc:	0000e307 	andeq	lr, r0, r7, lsl #6
    1cc0:	09001600 	stmdbeq	r0, {r9, sl, ip}
    1cc4:	00001cb3 			; <UNDEFINED> instruction: 0x00001cb3
    1cc8:	00101f33 	andseq	r1, r0, r3, lsr pc
    1ccc:	0ede0100 	cdpeq	1, 13, cr0, cr14, cr0, {0}
    1cd0:	05000008 	streq	r0, [r0, #-8]
    1cd4:	00000003 	andeq	r0, r0, r3
    1cd8:	003e0600 	eorseq	r0, lr, r0, lsl #12
    1cdc:	1cea0000 	stclne	0, cr0, [sl]
    1ce0:	e3340000 	teq	r4, #0
    1ce4:	ff000000 			; <UNDEFINED> instruction: 0xff000000
    1ce8:	5e330003 	cdppl	0, 3, cr0, cr3, cr3, {0}
    1cec:	01000010 	tsteq	r0, r0, lsl r0
    1cf0:	001cd9df 			; <UNDEFINED> instruction: 0x001cd9df
    1cf4:	54030500 	strpl	r0, [r3], #-1280	; 0xfffffb00
    1cf8:	06000000 	streq	r0, [r0], -r0
    1cfc:	00000061 	andeq	r0, r0, r1, rrx
    1d00:	00001d0b 	andeq	r1, r0, fp, lsl #26
    1d04:	0000e307 	andeq	lr, r0, r7, lsl #6
    1d08:	33000400 	movwcc	r0, #1024	; 0x400
    1d0c:	0000093d 	andeq	r0, r0, sp, lsr r9
    1d10:	1d1ce101 	ldfned	f6, [ip, #-4]
    1d14:	03050000 	movweq	r0, #20480	; 0x5000
    1d18:	000002b4 			; <UNDEFINED> instruction: 0x000002b4
    1d1c:	001cfb09 	andseq	pc, ip, r9, lsl #22
    1d20:	00610600 	rsbeq	r0, r1, r0, lsl #12
    1d24:	1d310000 	ldcne	0, cr0, [r1, #-0]
    1d28:	e3070000 	movw	r0, #28672	; 0x7000
    1d2c:	05000000 	streq	r0, [r0, #-0]
    1d30:	03483300 	movteq	r3, #33536	; 0x8300
    1d34:	e2010000 	and	r0, r1, #0
    1d38:	00001d42 	andeq	r1, r0, r2, asr #26
    1d3c:	02bc0305 	adcseq	r0, ip, #335544320	; 0x14000000
    1d40:	21090000 	mrscs	r0, (UNDEF: 9)
    1d44:	3300001d 	movwcc	r0, #29
    1d48:	000008e7 	andeq	r0, r0, r7, ror #17
    1d4c:	1d58e401 	cfldrdne	mvd14, [r8, #-4]
    1d50:	03050000 	movweq	r0, #20480	; 0x5000
    1d54:	000002d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
    1d58:	001cfb09 	andseq	pc, ip, r9, lsl #22
    1d5c:	02ee3300 	rsceq	r3, lr, #0, 6
    1d60:	e5010000 	str	r0, [r1, #-0]
    1d64:	00001d6e 	andeq	r1, r0, lr, ror #26
    1d68:	02d80305 	sbcseq	r0, r8, #335544320	; 0x14000000
    1d6c:	21090000 	mrscs	r0, (UNDEF: 9)
    1d70:	0600001d 			; <UNDEFINED> instruction: 0x0600001d
    1d74:	00000061 	andeq	r0, r0, r1, rrx
    1d78:	00001d83 	andeq	r1, r0, r3, lsl #27
    1d7c:	0000e307 	andeq	lr, r0, r7, lsl #6
    1d80:	33000000 	movwcc	r0, #0
    1d84:	00000ba5 	andeq	r0, r0, r5, lsr #23
    1d88:	1d94e701 	ldcne	7, cr14, [r4, #4]
    1d8c:	03050000 	movweq	r0, #20480	; 0x5000
    1d90:	000002c4 	andeq	r0, r0, r4, asr #5
    1d94:	001d7309 	andseq	r7, sp, r9, lsl #6
    1d98:	05dd3300 	ldrbeq	r3, [sp, #768]	; 0x300
    1d9c:	e8010000 	stmda	r1, {}	; <UNPREDICTABLE>
    1da0:	00001daa 	andeq	r1, r0, sl, lsr #27
    1da4:	02c80305 	sbceq	r0, r8, #335544320	; 0x14000000
    1da8:	21090000 	mrscs	r0, (UNDEF: 9)
    1dac:	3300001d 	movwcc	r0, #29
    1db0:	00001264 	andeq	r1, r0, r4, ror #4
    1db4:	1cfbea01 	vldmiane	fp!, {s29}
    1db8:	03050000 	movweq	r0, #20480	; 0x5000
    1dbc:	00000030 	andeq	r0, r0, r0, lsr r0
    1dc0:	000ff733 	andeq	pc, pc, r3, lsr r7	; <UNPREDICTABLE>
    1dc4:	fbed0100 	blx	ffb421ce <wmt_core_func_ctrl_cmd+0xffb3edae>
    1dc8:	0500001c 	streq	r0, [r0, #-28]	; 0xffffffe4
    1dcc:	00003803 	andeq	r3, r0, r3, lsl #16
    1dd0:	0f493300 	svceq	0x00493300
    1dd4:	ee010000 	cdp	0, 0, cr0, cr1, cr0, {0}
    1dd8:	00001d21 	andeq	r1, r0, r1, lsr #26
    1ddc:	00400305 	subeq	r0, r0, r5, lsl #6
    1de0:	61060000 	mrsvs	r0, (UNDEF: 6)
    1de4:	f2000000 	vhadd.s8	d0, d0, d0
    1de8:	0700001d 	smladeq	r0, sp, r0, r0
    1dec:	000000e3 	andeq	r0, r0, r3, ror #1
    1df0:	8333000b 	teqhi	r3, #11
    1df4:	01000005 	tsteq	r0, r5
    1df8:	001de2f0 			; <UNDEFINED> instruction: 0x001de2f0
    1dfc:	24030500 	strcs	r0, [r3], #-1280	; 0xfffffb00
    1e00:	35000000 	strcc	r0, [r0, #-0]
    1e04:	00001451 	andeq	r1, r0, r1, asr r4
    1e08:	1de2f701 	stclne	7, cr15, [r2, #4]!
    1e0c:	c8330000 	ldmdagt	r3!, {}	; <UNPREDICTABLE>
    1e10:	01000000 	mrseq	r0, (UNDEF: 0)
    1e14:	001d21fe 			; <UNDEFINED> instruction: 0x001d21fe
    1e18:	48030500 	stmdami	r3, {r8, sl}
    1e1c:	28000000 	stmdacs	r0, {}	; <UNPREDICTABLE>
    1e20:	00000e84 	andeq	r0, r0, r4, lsl #29
    1e24:	fb010101 	blx	42232 <wmt_core_func_ctrl_cmd+0x3ee12>
    1e28:	0500001c 	streq	r0, [r0, #-28]	; 0xffffffe4
    1e2c:	00005003 	andeq	r5, r0, r3
    1e30:	00610600 	rsbeq	r0, r1, r0, lsl #12
    1e34:	1e410000 	cdpne	0, 4, cr0, cr1, cr0, {0}
    1e38:	e3070000 	movw	r0, #28672	; 0x7000
    1e3c:	13000000 	movwne	r0, #0
    1e40:	07092800 	streq	r2, [r9, -r0, lsl #16]
    1e44:	04010000 	streq	r0, [r1], #-0
    1e48:	001e3101 	andseq	r3, lr, r1, lsl #2
    1e4c:	10030500 	andne	r0, r3, r0, lsl #10
    1e50:	06000000 	streq	r0, [r0], -r0
    1e54:	00000061 	andeq	r0, r0, r1, rrx
    1e58:	00001e63 	andeq	r1, r0, r3, ror #28
    1e5c:	0000e307 	andeq	lr, r0, r7, lsl #6
    1e60:	1c000700 	stcne	7, cr0, [r0], {-0}
    1e64:	000004b3 			; <UNDEFINED> instruction: 0x000004b3
    1e68:	53010d01 	movwpl	r0, #7425	; 0x1d01
    1e6c:	0600001e 			; <UNDEFINED> instruction: 0x0600001e
    1e70:	00000061 	andeq	r0, r0, r1, rrx
    1e74:	00001e7f 	andeq	r1, r0, pc, ror lr
    1e78:	0000e307 	andeq	lr, r0, r7, lsl #6
    1e7c:	1c000f00 	stcne	15, cr0, [r0], {-0}
    1e80:	00000d82 	andeq	r0, r0, r2, lsl #27
    1e84:	6f011501 	svcvs	0x00011501
    1e88:	0600001e 			; <UNDEFINED> instruction: 0x0600001e
    1e8c:	0000040c 	andeq	r0, r0, ip, lsl #8
    1e90:	00001e9b 	muleq	r0, fp, lr
    1e94:	0000e307 	andeq	lr, r0, r7, lsl #6
    1e98:	28001200 	stmdacs	r0, {r9, ip}
    1e9c:	000012fc 	strdeq	r1, [r0], -ip
    1ea0:	ad012201 	sfmge	f2, 4, [r1, #-4]
    1ea4:	0500001e 	streq	r0, [r0, #-30]	; 0xffffffe2
    1ea8:	00001803 	andeq	r1, r0, r3, lsl #16
    1eac:	1e8b0900 	cdpne	9, 8, cr0, cr11, cr0, {0}
    1eb0:	bc360000 	ldclt	0, cr0, [r6], #-0
    1eb4:	05000007 	streq	r0, [r0, #-7]
    1eb8:	00009e82 	andeq	r9, r0, r2, lsl #29
    1ebc:	36010100 	strcc	r0, [r1], -r0, lsl #2
    1ec0:	000009f4 	strdeq	r0, [r0], -r4
    1ec4:	07967501 	ldreq	r7, [r6, r1, lsl #10]
    1ec8:	01010000 	mrseq	r0, (UNDEF: 1)
    1ecc:	00010936 	andeq	r0, r1, r6, lsr r9
    1ed0:	1a7d0100 	bne	1f422d8 <wmt_core_func_ctrl_cmd+0x1f3eeb8>
    1ed4:	0100000a 	tsteq	r0, sl
    1ed8:	12a33601 	adcne	r3, r3, #1048576	; 0x100000
    1edc:	81010000 	mrshi	r0, (UNDEF: 1)
    1ee0:	00000a1a 	andeq	r0, r0, sl, lsl sl
    1ee4:	77360101 	ldrvc	r0, [r6, -r1, lsl #2]!
    1ee8:	01000010 	tsteq	r0, r0, lsl r0
    1eec:	000a1a85 	andeq	r1, sl, r5, lsl #21
    1ef0:	36010100 	strcc	r0, [r1], -r0, lsl #2
    1ef4:	00000a4d 	andeq	r0, r0, sp, asr #20
    1ef8:	0a1a8901 	beq	6a4304 <wmt_core_func_ctrl_cmd+0x6a0ee4>
    1efc:	01010000 	mrseq	r0, (UNDEF: 1)
    1f00:	000a2506 	andeq	r2, sl, r6, lsl #10
    1f04:	001f1000 	andseq	r1, pc, r0
    1f08:	00e30700 	rsceq	r0, r3, r0, lsl #14
    1f0c:	00030000 	andeq	r0, r3, r0
    1f10:	0011bf37 	andseq	fp, r1, r7, lsr pc
    1f14:	008c0100 	addeq	r0, ip, r0, lsl #2
    1f18:	0100001f 	tsteq	r0, pc, lsl r0
    1f1c:	00000305 	andeq	r0, r0, r5, lsl #6
    1f20:	Address 0x00001f20 is out of bounds.


Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	00000b76 	andeq	r0, r0, r6, ror fp
   4:	012b0002 	teqeq	fp, r2
   8:	01020000 	mrseq	r0, (UNDEF: 2)
   c:	000d0efb 	strdeq	r0, [sp], -fp
  10:	01010101 	tsteq	r1, r1, lsl #2
  14:	01000000 	mrseq	r0, (UNDEF: 0)
  18:	64010000 	strvs	r0, [r1], #-0
  1c:	65766972 	ldrbvs	r6, [r6, #-2418]!	; 0xfffff68e
  20:	6d2f7372 	stcvs	3, cr7, [pc, #-456]!	; fffffe60 <wmt_core_func_ctrl_cmd+0xffffca40>
  24:	775f6b74 			; <UNDEFINED> instruction: 0x775f6b74
  28:	635f6e63 	cmpvs	pc, #1584	; 0x630
  2c:	6f626d6f 	svcvs	0x00626d6f
  30:	6d6f632f 	stclvs	3, cr6, [pc, #-188]!	; ffffff7c <wmt_core_func_ctrl_cmd+0xffffcb5c>
  34:	2f6e6f6d 	svccs	0x006e6f6d
  38:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  3c:	69726400 	ldmdbvs	r2!, {sl, sp, lr}^
  40:	73726576 	cmnvc	r2, #494927872	; 0x1d800000
  44:	6b746d2f 	blvs	1d1b508 <wmt_core_func_ctrl_cmd+0x1d180e8>
  48:	6e63775f 	mcrvs	7, 3, r7, cr3, cr15, {2}
  4c:	6d6f635f 	stclvs	3, cr6, [pc, #-380]!	; fffffed8 <wmt_core_func_ctrl_cmd+0xffffcab8>
  50:	632f6f62 	teqvs	pc, #392	; 0x188
  54:	6f6d6d6f 	svcvs	0x006d6d6f
  58:	696c2f6e 	stmdbvs	ip!, {r1, r2, r3, r5, r6, r8, r9, sl, fp, sp}^
  5c:	2f78756e 	svccs	0x0078756e
  60:	6c636e69 	stclvs	14, cr6, [r3], #-420	; 0xfffffe5c
  64:	00656475 	rsbeq	r6, r5, r5, ror r4
  68:	76697264 	strbtvc	r7, [r9], -r4, ror #4
  6c:	2f737265 	svccs	0x00737265
  70:	5f6b746d 	svcpl	0x006b746d
  74:	5f6e6377 	svcpl	0x006e6377
  78:	626d6f63 	rsbvs	r6, sp, #396	; 0x18c
  7c:	6f632f6f 	svcvs	0x00632f6f
  80:	6e6f6d6d 	cdpvs	13, 6, cr6, cr15, cr13, {3}
  84:	636e692f 	cmnvs	lr, #770048	; 0xbc000
  88:	6564756c 	strbvs	r7, [r4, #-1388]!	; 0xfffffa94
  8c:	69726400 	ldmdbvs	r2!, {sl, sp, lr}^
  90:	73726576 	cmnvc	r2, #494927872	; 0x1d800000
  94:	6b746d2f 	blvs	1d1b558 <wmt_core_func_ctrl_cmd+0x1d18138>
  98:	6e63775f 	mcrvs	7, 3, r7, cr3, cr15, {2}
  9c:	6d6f635f 	stclvs	3, cr6, [pc, #-380]!	; ffffff28 <wmt_core_func_ctrl_cmd+0xffffcb08>
  a0:	632f6f62 	teqvs	pc, #392	; 0x188
  a4:	6f6d6d6f 	svcvs	0x006d6d6f
  a8:	6f632f6e 	svcvs	0x00632f6e
  ac:	692f6572 	stmdbvs	pc!, {r1, r4, r5, r6, r8, sl, sp, lr}	; <UNPREDICTABLE>
  b0:	756c636e 	strbvc	r6, [ip, #-878]!	; 0xfffffc92
  b4:	00006564 	andeq	r6, r0, r4, ror #10
  b8:	5f746d77 	svcpl	0x00746d77
  bc:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  c0:	0100632e 	tsteq	r0, lr, lsr #6
  c4:	736f0000 	cmnvc	pc, #0
  c8:	745f6c61 	ldrbvc	r6, [pc], #-3169	; d0 <.debug_line+0xd0>
  cc:	64657079 	strbtvs	r7, [r5], #-121	; 0xffffff87
  d0:	682e6665 	stmdavs	lr!, {r0, r2, r5, r6, r9, sl, sp, lr}
  d4:	00000200 	andeq	r0, r0, r0, lsl #4
  d8:	6c61736f 	stclvs	3, cr7, [r1], #-444	; 0xfffffe44
  dc:	0300682e 	movweq	r6, #2094	; 0x82e
  e0:	6d770000 	ldclvs	0, cr0, [r7, #-0]
  e4:	74635f74 	strbtvc	r5, [r3], #-3956	; 0xfffff08c
  e8:	682e6c72 	stmdavs	lr!, {r1, r4, r5, r6, sl, fp, sp, lr}
  ec:	00000400 	andeq	r0, r0, r0, lsl #8
  f0:	5f746d77 	svcpl	0x00746d77
  f4:	2e707865 	cdpcs	8, 7, cr7, cr0, cr5, {3}
  f8:	00030068 	andeq	r0, r3, r8, rrx
  fc:	726f6300 	rsbvc	r6, pc, #0, 6
 100:	78655f65 	stmdavc	r5!, {r0, r2, r5, r6, r8, r9, sl, fp, ip, lr}^
 104:	00682e70 	rsbeq	r2, r8, r0, ror lr
 108:	77000003 	strvc	r0, [r0, -r3]
 10c:	635f746d 	cmpvs	pc, #1828716544	; 0x6d000000
 110:	2e65726f 	cdpcs	2, 6, cr7, cr5, cr15, {3}
 114:	00040068 	andeq	r0, r4, r8, rrx
 118:	70747300 	rsbsvc	r7, r4, r0, lsl #6
 11c:	746d775f 	strbtvc	r7, [sp], #-1887	; 0xfffff8a1
 120:	0400682e 	streq	r6, [r0], #-2094	; 0xfffff7d2
 124:	6d770000 	ldclvs	0, cr0, [r7, #-0]
 128:	75665f74 	strbvc	r5, [r6, #-3956]!	; 0xfffff08c
 12c:	682e636e 	stmdavs	lr!, {r1, r2, r3, r5, r6, r8, r9, sp, lr}
 130:	00000400 	andeq	r0, r0, r0, lsl #8
 134:	02050000 	andeq	r0, r5, #0
 138:	00000000 	andeq	r0, r0, r0
 13c:	010eff03 	tsteq	lr, r3, lsl #30
 140:	789d0369 	ldmvc	sp, {r0, r3, r5, r6, r8, r9}
 144:	2f2d834a 	svccs	0x002d834a
 148:	bb302933 	bllt	c0a61c <wmt_core_func_ctrl_cmd+0xc071fc>
 14c:	7cd70331 	ldclvc	3, cr0, [r7], {49}	; 0x31
 150:	9f306a82 	svcls	0x00306a82
 154:	3083312f 	addcc	r3, r3, pc, lsr #2
 158:	6c506969 	mrrcvs	9, 6, r6, r0, cr9
 15c:	2e7a032f 	cdpcs	3, 7, cr0, cr10, cr15, {1}
 160:	4a790383 	bmi	1e40f74 <wmt_core_func_ctrl_cmd+0x1e3db54>
 164:	7ecb0384 	cdpvc	3, 12, cr0, cr11, cr4, {4}
 168:	03a1689e 			; <UNDEFINED> instruction: 0x03a1689e
 16c:	a4694a6b 	strbtge	r4, [r9], #-2667	; 0xfffff595
 170:	032e7603 	teqeq	lr, #3145728	; 0x300000
 174:	02002e0a 	andeq	r2, r0, #10, 28	; 0xa0
 178:	502c0104 	eorpl	r0, ip, r4, lsl #2
 17c:	6601e603 	strvs	lr, [r1], -r3, lsl #12
 180:	004d2b69 	subeq	r2, sp, r9, ror #22
 184:	06010402 	streq	r0, [r1], -r2, lsl #8
 188:	04020066 	streq	r0, [r2], #-102	; 0xffffff9a
 18c:	bbbb0601 	bllt	feec1998 <wmt_core_func_ctrl_cmd+0xfeebe578>
 190:	01040200 	mrseq	r0, R12_usr
 194:	02004a06 	andeq	r4, r0, #24576	; 0x6000
 198:	002e0204 	eoreq	r0, lr, r4, lsl #4
 19c:	4a010402 	bmi	411ac <wmt_core_func_ctrl_cmd+0x3dd8c>
 1a0:	02040200 	andeq	r0, r4, #0, 4
 1a4:	004b062e 	subeq	r0, fp, lr, lsr #12
 1a8:	06010402 	streq	r0, [r1], -r2, lsl #8
 1ac:	02004a2e 	andeq	r4, r0, #188416	; 0x2e000
 1b0:	062e0104 	strteq	r0, [lr], -r4, lsl #2
 1b4:	04020064 	streq	r0, [r2], #-100	; 0xffffff9c
 1b8:	2e2e0601 	cfmadda32cs	mvax0, mvax0, mvfx14, mvfx1
 1bc:	01040200 	mrseq	r0, R12_usr
 1c0:	0033062e 	eorseq	r0, r3, lr, lsr #12
 1c4:	06010402 	streq	r0, [r1], -r2, lsl #8
 1c8:	9d03064a 	stcls	6, cr0, [r3, #-296]	; 0xfffffed8
 1cc:	883c080b 	ldmdahi	ip!, {r0, r1, r3, fp}
 1d0:	82090387 	andhi	r0, r9, #469762050	; 0x1c000002
 1d4:	2b322c2c 	blcs	c8b28c <wmt_core_func_ctrl_cmd+0xc87e6c>
 1d8:	04020031 	streq	r0, [r2], #-49	; 0xffffffcf
 1dc:	064a0601 	strbeq	r0, [sl], -r1, lsl #12
 1e0:	6e0385f4 	mcrvs	5, 0, r8, cr3, cr4, {7}
 1e4:	834e834a 	movthi	r8, #58186	; 0xe34a
 1e8:	f277ef03 	vmin.f<illegal width 64>	d30, d7, d3
 1ec:	4f2f2d67 	svcmi	0x002f2d67
 1f0:	02004b88 	andeq	r4, r0, #136, 22	; 0x22000
 1f4:	82060104 	andhi	r0, r6, #4, 2
 1f8:	30856906 	addcc	r6, r5, r6, lsl #18
 1fc:	002e7203 	eoreq	r7, lr, r3, lsl #4
 200:	06010402 	streq	r0, [r1], -r2, lsl #8
 204:	09030682 	stmdbeq	r3, {r1, r7, r9, sl}
 208:	0330859e 	teqeq	r0, #662700032	; 0x27800000
 20c:	03832e6d 	orreq	r2, r3, #1744	; 0x6d0
 210:	20087cba 			; <UNDEFINED> instruction: 0x20087cba
 214:	02002b85 	andeq	r2, r0, #136192	; 0x21400
 218:	35310204 	ldrcc	r0, [r1, #-516]!	; 0xfffffdfc
 21c:	01040200 	mrseq	r0, R12_usr
 220:	2f2e7903 	svccs	0x002e7903
 224:	02040200 	andeq	r0, r4, #0, 4
 228:	2a062e06 	bcs	18ba48 <wmt_core_func_ctrl_cmd+0x188628>
 22c:	01040200 	mrseq	r0, R12_usr
 230:	2f2f3032 	svccs	0x002f3032
 234:	2f502f30 	svccs	0x00502f30
 238:	034e2f4c 	movteq	r2, #61260	; 0xef4c
 23c:	03f36674 	mvnseq	r6, #116, 12	; 0x7400000
 240:	580809c9 	stmdapl	r8, {r0, r3, r6, r7, r8, fp}
 244:	82799203 	rsbshi	r9, r9, #805306368	; 0x30000000
 248:	04040200 	streq	r0, [r4], #-512	; 0xfffffe00
 24c:	03069e06 	movweq	r9, #28166	; 0x6e06
 250:	28020780 	stmdacs	r2, {r7, r8, r9, sl}
 254:	2e760301 	cdpcs	3, 7, cr0, cr6, cr1, {0}
 258:	034a0a03 	movteq	r0, #43523	; 0xaa03
 25c:	4c2f2e77 	stcmi	14, cr2, [pc], #-476	; 88 <.debug_line+0x88>
 260:	1f03314d 	svcne	0x0003314d
 264:	6625032e 	strtvs	r0, [r5], -lr, lsr #6
 268:	67312b31 			; <UNDEFINED> instruction: 0x67312b31
 26c:	0402004d 	streq	r0, [r2], #-77	; 0xffffffb3
 270:	06660601 	strbteq	r0, [r6], -r1, lsl #12
 274:	2f67656b 	svccs	0x0067656b
 278:	4a78af03 	bmi	1e2be8c <wmt_core_func_ctrl_cmd+0x1e28a6c>
 27c:	04040200 	streq	r0, [r4], #-512	; 0xfffffe00
 280:	03066606 	movweq	r6, #26118	; 0x6606
 284:	240207d9 	strcs	r0, [r2], #-2009	; 0xfffff827
 288:	66700301 	ldrbtvs	r0, [r0], -r1, lsl #6
 28c:	649e5903 	ldrvs	r5, [lr], #2307	; 0x903
 290:	2f302d2f 	svccs	0x00302d2f
 294:	04020050 	streq	r0, [r2], #-80	; 0xffffffb0
 298:	06660601 	strbteq	r0, [r6], -r1, lsl #12
 29c:	4b4b646b 	blmi	12d9450 <wmt_core_func_ctrl_cmd+0x12d6030>
 2a0:	0200512f 	andeq	r5, r0, #-1073741813	; 0xc000000b
 2a4:	66060104 	strvs	r0, [r6], -r4, lsl #2
 2a8:	4b036806 	blmi	da2c8 <wmt_core_func_ctrl_cmd+0xd6ea8>
 2ac:	4c2d9d66 	stcmi	13, cr9, [sp], #-408	; 0xfffffe68
 2b0:	02004f2f 	andeq	r4, r0, #47, 30	; 0xbc
 2b4:	66060104 	strvs	r0, [r6], -r4, lsl #2
 2b8:	4c2c6b06 	stcmi	11, cr6, [ip], #-24	; 0xffffffe8
 2bc:	6e4a0e03 	cdpvs	14, 4, cr0, cr10, cr3, {0}
 2c0:	659e6d03 	ldrvs	r6, [lr, #3331]	; 0xd03
 2c4:	502f4c2d 	eorpl	r4, pc, sp, lsr #24
 2c8:	01040200 	mrseq	r0, R12_usr
 2cc:	68066606 	stmdavs	r6, {r1, r2, r9, sl, sp, lr}
 2d0:	03666b03 	cmneq	r6, #3072	; 0xc00
 2d4:	03839e2b 	orreq	r9, r3, #688	; 0x2b0
 2d8:	2d67ba21 	vstmdbcs	r7!, {s23-s55}
 2dc:	2e40032f 	cdpcs	3, 4, cr0, cr0, cr15, {1}
 2e0:	74fb0383 	ldrbtvc	r0, [fp], #899	; 0x383
 2e4:	86013602 	strhi	r3, [r1], -r2, lsl #12
 2e8:	2f4d2b30 	svccs	0x004d2b30
 2ec:	03a19f4c 			; <UNDEFINED> instruction: 0x03a19f4c
 2f0:	3286f260 	addcc	pc, r6, #96, 4
 2f4:	2b2f3029 	blcs	bcc3a0 <wmt_core_func_ctrl_cmd+0xbc8f80>
 2f8:	9f4c2f33 	svcls	0x004c2f33
 2fc:	ef03a12f 	svc	0x0003a12f
 300:	3086f20c 	addcc	pc, r6, ip, lsl #4
 304:	04020048 	streq	r0, [r2], #-72	; 0xffffffb8
 308:	002e0602 	eoreq	r0, lr, r2, lsl #12
 30c:	66030402 	strvs	r0, [r3], -r2, lsl #8
 310:	2d2f2f06 	stccs	15, cr2, [pc, #-24]!	; 300 <.debug_line+0x300>
 314:	844b2f2f 	strbhi	r2, [fp], #-3887	; 0xfffff0d1
 318:	03660903 	cmneq	r6, #49152	; 0xc000
 31c:	0200667a 	andeq	r6, r0, #127926272	; 0x7a00000
 320:	82060104 	andhi	r0, r6, #4, 2
 324:	02006706 	andeq	r6, r0, #1572864	; 0x180000
 328:	7a030104 	bvc	c0740 <wmt_core_func_ctrl_cmd+0xbd320>
 32c:	7ae103ba 	bvc	ff84121c <wmt_core_func_ctrl_cmd+0xff83ddfc>
 330:	00682008 	rsbeq	r2, r8, r8
 334:	06010402 	streq	r0, [r1], -r2, lsl #8
 338:	03680682 	cmneq	r8, #136314880	; 0x8200000
 33c:	879e7bd4 			; <UNDEFINED> instruction: 0x879e7bd4
 340:	4c678684 	stclmi	6, cr8, [r7], #-528	; 0xfffffdf0
 344:	9d4a0a03 	vstrls	s1, [sl, #-12]
 348:	49493083 	stmdbmi	r9, {r0, r1, r7, ip, sp}^
 34c:	49494c30 	stmdbmi	r9, {r4, r5, sl, fp, lr}^
 350:	30454d30 	subcc	r4, r5, r0, lsr sp
 354:	2e190331 	mrccs	3, 0, r0, cr9, cr1, {1}
 358:	02006a4b 	andeq	r6, r0, #307200	; 0x4b000
 35c:	03620104 	cmneq	r2, #4, 2
 360:	02009e4e 	andeq	r9, r0, #1248	; 0x4e0
 364:	682c0104 	stmdavs	ip!, {r2, r8}
 368:	04020067 	streq	r0, [r2], #-103	; 0xffffff99
 36c:	06660601 	strbteq	r0, [r6], -r1, lsl #12
 370:	65821a03 	strvs	r1, [r2, #2563]	; 0xa03
 374:	4b2f302d 	blmi	bcc430 <wmt_core_func_ctrl_cmd+0xbc9010>
 378:	64660903 	strbtvs	r0, [r6], #-2307	; 0xfffff6fd
 37c:	4b2f4b4b 	blmi	bd30b0 <wmt_core_func_ctrl_cmd+0xbcfc90>
 380:	665c036c 	ldrbvs	r0, [ip], -ip, ror #6
 384:	009e2203 	addseq	r2, lr, r3, lsl #4
 388:	06010402 	streq	r0, [r1], -r2, lsl #8
 38c:	75030666 	strvc	r0, [r3, #-1638]	; 0xfffff99a
 390:	04020082 	streq	r0, [r2], #-130	; 0xffffff7e
 394:	00660601 	rsbeq	r0, r6, r1, lsl #12
 398:	06010402 	streq	r0, [r1], -r2, lsl #8
 39c:	04020089 	streq	r0, [r2], #-137	; 0xffffff77
 3a0:	9e750301 	cdpls	3, 7, cr0, cr5, cr1, {0}
 3a4:	0801d603 	stmdaeq	r1, {r0, r1, r9, sl, ip, lr, pc}
 3a8:	038988c8 	orreq	r8, r9, #200, 16	; 0xc80000
 3ac:	6130660a 	teqvs	r0, sl, lsl #12
 3b0:	2f322b31 	svccs	0x00322b31
 3b4:	4d6a4e2f 	stclmi	14, cr4, [sl, #-188]!	; 0xffffff44
 3b8:	00667603 	rsbeq	r7, r6, r3, lsl #12
 3bc:	06010402 	streq	r0, [r1], -r2, lsl #8
 3c0:	73030666 	movwvc	r0, #13926	; 0x3666
 3c4:	004b2f9e 	umaaleq	r2, fp, lr, pc	; <UNPREDICTABLE>
 3c8:	06010402 	streq	r0, [r1], -r2, lsl #8
 3cc:	04020082 	streq	r0, [r2], #-130	; 0xffffff7e
 3d0:	0e030601 	cfmadd32eq	mvax0, mvfx0, mvfx3, mvfx1
 3d4:	82690382 	rsbhi	r0, r9, #134217730	; 0x8000002
 3d8:	01040200 	mrseq	r0, R12_usr
 3dc:	67068206 	strvs	r8, [r6, -r6, lsl #4]
 3e0:	034b2d67 	movteq	r2, #48487	; 0xbd67
 3e4:	580801b3 	stmdapl	r8, {r0, r1, r4, r5, r7, r8}
 3e8:	2e790389 	cdpcs	3, 7, cr0, cr9, cr9, {4}
 3ec:	512e0903 	teqpl	lr, r3, lsl #18
 3f0:	3f032f8a 	svccc	0x00032f8a
 3f4:	04020082 	streq	r0, [r2], #-130	; 0xffffff7e
 3f8:	66410301 	strbvs	r0, [r1], -r1, lsl #6
 3fc:	0402006a 	streq	r0, [r2], #-106	; 0xffffff96
 400:	4b6b2a01 	blmi	1acac0c <wmt_core_func_ctrl_cmd+0x1ac77ec>
 404:	01040200 	mrseq	r0, R12_usr
 408:	68068206 	stmdavs	r6, {r1, r2, r9, pc}
 40c:	03302ca0 	teqeq	r0, #160, 24	; 0xa000
 410:	4b2d2e1c 	blmi	b4bc88 <wmt_core_func_ctrl_cmd+0xb48868>
 414:	834a0903 	movthi	r0, #43267	; 0xa903
 418:	67676767 	strbvs	r6, [r7, -r7, ror #14]!
 41c:	01040200 	mrseq	r0, R12_usr
 420:	84066606 	strhi	r6, [r6], #-1542	; 0xfffff9fa
 424:	03bb4b4b 			; <UNDEFINED> instruction: 0x03bb4b4b
 428:	009e7cbc 			; <UNDEFINED> instruction: 0x009e7cbc
 42c:	06040402 	streq	r0, [r4], -r2, lsl #8
 430:	a9030666 	stmdbge	r3, {r1, r2, r5, r6, r9, sl}
 434:	01260203 	teqeq	r6, r3, lsl #4
 438:	2e7a0335 	mrccs	3, 3, r0, cr10, cr5, {1}
 43c:	4a750350 	bmi	1d41184 <wmt_core_func_ctrl_cmd+0x1d3dd64>
 440:	68820b03 	stmvs	r2, {r0, r1, r8, r9, fp}
 444:	040200bb 	streq	r0, [r2], #-187	; 0xffffff45
 448:	f2720301 	vcgt.s<illegal width 64>	d16, d2, d1
 44c:	01040200 	mrseq	r0, R12_usr
 450:	6a9e7003 	bvs	fe79c464 <wmt_core_func_ctrl_cmd+0xfe799044>
 454:	2f4c2d65 	svccs	0x004c2d65
 458:	665c0350 			; <UNDEFINED> instruction: 0x665c0350
 45c:	2f2d839f 	svccs	0x002d839f
 460:	2d67bd33 	stclcs	13, cr11, [r7, #-204]!	; 0xffffff34
 464:	2e14034b 	cdpcs	3, 1, cr0, cr4, cr11, {2}
 468:	78c90383 	stmiavc	r9, {r0, r1, r7, r8, r9}^
 46c:	03013002 	movweq	r3, #4098	; 0x1002
 470:	03306612 	teqeq	r0, #18874368	; 0x1200000
 474:	002e0297 	mlaeq	lr, r7, r2, r0
 478:	88010402 	stmdahi	r1, {r1, sl}
 47c:	03068206 	movweq	r8, #25094	; 0x6206
 480:	7a034a0a 	bvc	d2cb0 <wmt_core_func_ctrl_cmd+0xcf890>
 484:	3329a44a 	teqcc	r9, #1241513984	; 0x4a000000
 488:	04020045 	streq	r0, [r2], #-69	; 0xffffffbb
 48c:	062e0601 	strteq	r0, [lr], -r1, lsl #12
 490:	34832f87 	strcc	r2, [r3], #3975	; 0xf87
 494:	002e7a03 	eoreq	r7, lr, r3, lsl #20
 498:	06010402 	streq	r0, [r1], -r2, lsl #8
 49c:	0050062e 	subseq	r0, r0, lr, lsr #12
 4a0:	03010402 	movweq	r0, #5122	; 0x1402
 4a4:	03502e7a 	cmpeq	r0, #1952	; 0x7a0
 4a8:	65038209 	strvs	r8, [r3, #-521]	; 0xfffffdf7
 4ac:	2e1b032e 	cdpcs	3, 1, cr0, cr11, cr14, {1}
 4b0:	01040200 	mrseq	r0, R12_usr
 4b4:	064a6503 	strbeq	r6, [sl], -r3, lsl #10
 4b8:	0402002e 	streq	r0, [r2], #-46	; 0xffffffd2
 4bc:	2f062e01 	svccs	0x00062e01
 4c0:	01040200 	mrseq	r0, R12_usr
 4c4:	02006606 	andeq	r6, r0, #6291456	; 0x600000
 4c8:	03060104 	movweq	r0, #24836	; 0x6104
 4cc:	65039e1a 	strvs	r9, [r3, #-3610]	; 0xfffff1e6
 4d0:	0402002e 	streq	r0, [r2], #-46	; 0xffffffd2
 4d4:	2e1b0301 	cdpcs	3, 1, cr0, cr11, cr1, {0}
 4d8:	01040200 	mrseq	r0, R12_usr
 4dc:	00666503 	rsbeq	r6, r6, r3, lsl #10
 4e0:	03010402 	movweq	r0, #5122	; 0x1402
 4e4:	032f4a1e 	teqeq	pc, #122880	; 0x1e000
 4e8:	034b4a66 	movteq	r4, #47718	; 0xba66
 4ec:	0200d618 	andeq	sp, r0, #24, 12	; 0x1800000
 4f0:	2e060204 	cdpcs	2, 0, cr0, cr6, cr4, {0}
 4f4:	6e03062e 	cfmadd32vs	mvax1, mvfx0, mvfx3, mvfx14
 4f8:	2ff34b4a 	svccs	0x00f34b4a
 4fc:	36029f32 			; <UNDEFINED> instruction: 0x36029f32
 500:	68032f15 	stmdavs	r3, {r0, r2, r4, r8, r9, sl, fp, sp}
 504:	0846032e 	stmdaeq	r6, {r1, r2, r3, r5, r8, r9}^
 508:	0200863c 	andeq	r8, r0, #60, 12	; 0x3c00000
 50c:	2c300304 	ldccs	3, cr0, [r0], #-16
 510:	02040200 	andeq	r0, r4, #0, 4
 514:	4e2a4830 	mcrmi	8, 1, r4, cr10, cr0, {1}
 518:	2b312b31 	blcs	c4b1e4 <wmt_core_func_ctrl_cmd+0xc47dc4>
 51c:	2e790331 	mrccs	3, 3, r0, cr9, cr1, {1}
 520:	02040200 	andeq	r0, r4, #0, 4
 524:	02004834 	andeq	r4, r0, #52, 16	; 0x340000
 528:	2f300304 	svccs	0x00300304
 52c:	2f2a6a2f 	svccs	0x002a6a2f
 530:	02009f85 	andeq	r9, r0, #532	; 0x214
 534:	66060104 	strvs	r0, [r6], -r4, lsl #2
 538:	02040200 	andeq	r0, r4, #0, 4
 53c:	002f6c06 	eoreq	r6, pc, r6, lsl #24
 540:	2d020402 	cfstrscs	mvf0, [r2, #-8]
 544:	0200674b 	andeq	r6, r0, #19660800	; 0x12c0000
 548:	66060104 	strvs	r0, [r6], -r4, lsl #2
 54c:	13036b06 	movwne	r6, #15110	; 0x3b06
 550:	4a70034a 	bmi	1c01280 <wmt_core_func_ctrl_cmd+0x1bfde60>
 554:	84878583 	strhi	r8, [r7], #1411	; 0x583
 558:	4a620386 	bmi	1881378 <wmt_core_func_ctrl_cmd+0x187df58>
 55c:	00d751d7 	ldrsbeq	r5, [r7], #23
 560:	03010402 	movweq	r0, #5122	; 0x1402
 564:	9f9a4a0f 	svcls	0x009a4a0f
 568:	20083a03 	andcs	r3, r8, r3, lsl #20
 56c:	03898488 	orreq	r8, r9, #136, 8	; 0x88000000
 570:	67659e1a 			; <UNDEFINED> instruction: 0x67659e1a
 574:	4a14032f 	bmi	501238 <wmt_core_func_ctrl_cmd+0x4fde18>
 578:	67656d6a 	strbvs	r6, [r5, -sl, ror #26]!
 57c:	302f492f 	eorcc	r4, pc, pc, lsr #18
 580:	492f8365 	stmdbmi	pc!, {r0, r2, r5, r6, r8, r9, pc}	; <UNPREDICTABLE>
 584:	506b312f 	rsbpl	r3, fp, pc, lsr #2
 588:	4e2f8365 	cdpmi	3, 2, cr8, cr15, cr5, {3}
 58c:	82018f03 	andhi	r8, r1, #3, 30
 590:	004e9f4c 	subeq	r9, lr, ip, asr #30
 594:	06010402 	streq	r0, [r1], -r2, lsl #8
 598:	03850666 	orreq	r0, r5, #106954752	; 0x6600000
 59c:	039f8211 	orrseq	r8, pc, #268435457	; 0x10000001
 5a0:	672e7edb 			; <UNDEFINED> instruction: 0x672e7edb
 5a4:	2e1a032d 	cdpcs	3, 1, cr0, cr10, cr13, {1}
 5a8:	667fbf03 	ldrbtvs	fp, [pc], -r3, lsl #30
 5ac:	01040200 	mrseq	r0, R12_usr
 5b0:	02006606 	andeq	r6, r0, #6291456	; 0x600000
 5b4:	03060104 	movweq	r0, #24836	; 0x6104
 5b8:	0200ba47 	andeq	fp, r0, #290816	; 0x47000
 5bc:	c4030104 	strgt	r0, [r3], #-260	; 0xfffffefc
 5c0:	65a68200 	strvs	r8, [r6, #512]!	; 0x200
 5c4:	2f492f67 	svccs	0x00492f67
 5c8:	01040200 	mrseq	r0, R12_usr
 5cc:	02002e06 	andeq	r2, r0, #6, 28	; 0x60
 5d0:	03060104 	movweq	r0, #24836	; 0x6104
 5d4:	45039e7a 	strmi	r9, [r3, #-3706]	; 0xfffff186
 5d8:	4c2d9d9e 	stcmi	13, cr9, [sp], #-632	; 0xfffffd88
 5dc:	4a0a032f 	bmi	2812a0 <wmt_core_func_ctrl_cmd+0x27de80>
 5e0:	2f2f3062 	svccs	0x002f3062
 5e4:	0200502f 	andeq	r5, r0, #47	; 0x2f
 5e8:	66060104 	strvs	r0, [r6], -r4, lsl #2
 5ec:	01cf0306 	biceq	r0, pc, r6, lsl #6
 5f0:	02008382 	andeq	r8, r0, #134217730	; 0x8000002
 5f4:	ec030104 	stfs	f0, [r3], {4}
 5f8:	8c034a7e 	stchi	10, cr4, [r3], {126}	; 0x7e
 5fc:	02006601 	andeq	r6, r0, #1048576	; 0x100000
 600:	66060104 	strvs	r0, [r6], -r4, lsl #2
 604:	2f2d6a06 	svccs	0x002d6a06
 608:	01040200 	mrseq	r0, R12_usr
 60c:	03064a06 	movweq	r4, #27142	; 0x6a06
 610:	8403820c 	strhi	r8, [r3], #-524	; 0xfffffdf4
 614:	00672e7b 	rsbeq	r2, r7, fp, ror lr
 618:	2d010402 	cfstrscs	mvf0, [r1, #-8]
 61c:	0402004c 	streq	r0, [r2], #-76	; 0xffffffb4
 620:	00692c02 	rsbeq	r2, r9, r2, lsl #24
 624:	2b030402 	blcs	c1634 <wmt_core_func_ctrl_cmd+0xbe214>
 628:	4a059203 	bmi	164e3c <wmt_core_func_ctrl_cmd+0x161a1c>
 62c:	01040200 	mrseq	r0, R12_usr
 630:	f5066606 			; <UNDEFINED> instruction: 0xf5066606
 634:	2d4b4f2f 	stclcs	15, cr4, [fp, #-188]	; 0xffffff44
 638:	01040200 	mrseq	r0, R12_usr
 63c:	9f062e06 	svcls	0x00062e06
 640:	01040200 	mrseq	r0, R12_usr
 644:	7ece032d 	cdpvc	3, 12, cr0, cr14, cr13, {1}
 648:	0402002e 	streq	r0, [r2], #-46	; 0xffffffd2
 64c:	064a0601 	strbeq	r0, [sl], -r1, lsl #12
 650:	4e5068a1 	cdpmi	8, 5, cr6, cr0, cr1, {5}
 654:	2f67656a 	svccs	0x0067656a
 658:	02002f49 	andeq	r2, r0, #292	; 0x124
 65c:	2e060104 	adfcss	f0, f6, f4
 660:	01040200 	mrseq	r0, R12_usr
 664:	02009906 	andeq	r9, r0, #98304	; 0x18000
 668:	4a030104 	bmi	c0a80 <wmt_core_func_ctrl_cmd+0xbd660>
 66c:	01d50382 	bicseq	r0, r5, r2, lsl #7
 670:	0200bb82 	andeq	fp, r0, #133120	; 0x20800
 674:	e8030104 	stmda	r3, {r2, r8}
 678:	8e034a7a 	mcrhi	10, 0, r4, cr3, cr10, {3}
 67c:	03f44a05 	mvnseq	r4, #20480	; 0x5000
 680:	654a7ec7 	strbvs	r7, [sl, #-3783]	; 0xfffff139
 684:	2f492f83 	svccs	0x00492f83
 688:	01040200 	mrseq	r0, R12_usr
 68c:	03062e06 	movweq	r2, #28166	; 0x6e06
 690:	009e7ca8 	addseq	r7, lr, r8, lsr #25
 694:	03010402 	movweq	r0, #5122	; 0x1402
 698:	9f8203ec 	svcls	0x008203ec
 69c:	2f2d6786 	svccs	0x002d6786
 6a0:	2e7f9703 	cdpcs	7, 7, cr9, cr15, cr3, {0}
 6a4:	9f2f2c68 	svcls	0x002f2c68
 6a8:	9f2e2003 	svcls	0x002e2003
 6ac:	9f4a3103 	svcls	0x004a3103
 6b0:	9f4a1703 	svcls	0x004a1703
 6b4:	4a7f9e03 	bmi	1fe7ec8 <wmt_core_func_ctrl_cmd+0x1fe4aa8>
 6b8:	a02f2b69 	eorge	r2, pc, r9, ror #22
 6bc:	8103a136 	tsthi	r3, r6, lsr r1
 6c0:	01500209 	cmpeq	r0, r9, lsl #4
 6c4:	2f661503 	svccs	0x00661503
 6c8:	2e798003 	cdpcs	0, 7, cr8, cr9, cr3, {0}
 6cc:	2e790389 	cdpcs	3, 7, cr0, cr9, cr9, {4}
 6d0:	4f676e35 	svcmi	0x00676e35
 6d4:	492e1b03 	stmdbmi	lr!, {r0, r1, r8, r9, fp, ip}
 6d8:	0402004b 	streq	r0, [r2], #-75	; 0xffffffb5
 6dc:	06660601 	strbteq	r0, [r6], -r1, lsl #12
 6e0:	51826003 	orrpl	r6, r2, r3
 6e4:	2f2f2f64 	svccs	0x002f2f64
 6e8:	4b2f4d52 	blmi	bd3c38 <wmt_core_func_ctrl_cmd+0xbd0818>
 6ec:	4b2fa19f 	blmi	be8d70 <wmt_core_func_ctrl_cmd+0xbe5950>
 6f0:	034f854b 	movteq	r8, #62795	; 0xf54b
 6f4:	4b9f4a65 	blmi	fe7d3090 <wmt_core_func_ctrl_cmd+0xfe7cfc70>
 6f8:	01040200 	mrseq	r0, R12_usr
 6fc:	03066606 	movweq	r6, #26118	; 0x6606
 700:	03839e1c 	orreq	r9, r3, #28, 28	; 0x1c0
 704:	4f034a09 	svcmi	0x00034a09
 708:	04020066 	streq	r0, [r2], #-102	; 0xffffff9a
 70c:	4a270301 	bmi	9c1318 <wmt_core_func_ctrl_cmd+0x9bdef8>
 710:	03826703 	orreq	r6, r2, #786432	; 0xc0000
 714:	2b694a6a 	blcs	1a530c4 <wmt_core_func_ctrl_cmd+0x1a4fca4>
 718:	e4039f30 	str	r9, [r3], #-3888	; 0xfffff0d0
 71c:	89ac0800 	stmibhi	ip!, {fp}
 720:	032e7903 	teqeq	lr, #49152	; 0xc000
 724:	09032e0a 	stmdbeq	r3, {r1, r3, r9, sl, fp, sp}
 728:	0a03494a 	beq	d2c58 <wmt_core_func_ctrl_cmd+0xcf838>
 72c:	3067344a 	rsbcc	r3, r7, sl, asr #8
 730:	034a0903 	movteq	r0, #43267	; 0xa903
 734:	2f4a00c2 	svccs	0x004a00c2
 738:	4a7dae03 	bmi	1f6bf4c <wmt_core_func_ctrl_cmd+0x1f68b2c>
 73c:	04040200 	streq	r0, [r4], #-512	; 0xfffffe00
 740:	03068206 	movweq	r8, #25094	; 0x6206
 744:	002e02ee 	eoreq	r0, lr, lr, ror #5
 748:	03040402 	movweq	r0, #17410	; 0x4402
 74c:	032e7d92 	teqeq	lr, #9344	; 0x2480
 750:	220202ef 	andcs	r0, r2, #-268435442	; 0xf000000e
 754:	7fa10301 	svcvc	0x00a10301
 758:	04020066 	streq	r0, [r2], #-102	; 0xffffff9a
 75c:	06820601 	streq	r0, [r2], r1, lsl #12
 760:	4a22036a 	bmi	881510 <wmt_core_func_ctrl_cmd+0x87e0f0>
 764:	2e0f03bb 	mcrcs	3, 0, r0, cr15, cr11, {5}
 768:	304a7103 	subcc	r7, sl, r3, lsl #2
 76c:	034a0903 	movteq	r0, #43267	; 0xa903
 770:	a1bb4a16 			; <UNDEFINED> instruction: 0xa1bb4a16
 774:	67676783 	strbvs	r6, [r7, -r3, lsl #15]!
 778:	04020067 	streq	r0, [r2], #-103	; 0xffffff99
 77c:	06820601 	streq	r0, [r2], r1, lsl #12
 780:	9f4b4b84 	svcls	0x004b4b84
 784:	ba7f9803 	blt	1fe6798 <wmt_core_func_ctrl_cmd+0x1fe3378>
 788:	8200f003 	andhi	pc, r0, #3
 78c:	4a7fa703 	bmi	1fea3a0 <wmt_core_func_ctrl_cmd+0x1fe6f80>
 790:	03820d03 	orreq	r0, r2, #3, 26	; 0xc0
 794:	02004a0f 	andeq	r4, r0, #61440	; 0xf000
 798:	4d030104 	stfmis	f0, [r3, #-16]
 79c:	020067d6 	andeq	r6, r0, #56098816	; 0x3580000
 7a0:	032d0104 	teqeq	sp, #4, 2
 7a4:	674a00cd 	strbvs	r0, [sl, -sp, asr #1]
 7a8:	0402002d 	streq	r0, [r2], #-45	; 0xffffffd3
 7ac:	062e0601 	strteq	r0, [lr], -r1, lsl #12
 7b0:	04020067 	streq	r0, [r2], #-103	; 0xffffff99
 7b4:	58032d01 	stmdapl	r3, {r0, r8, sl, fp, sp}
 7b8:	0200674a 	andeq	r6, r0, #19398656	; 0x1280000
 7bc:	82060104 	andhi	r0, r6, #4, 2
 7c0:	ba630306 	blt	18c13e0 <wmt_core_func_ctrl_cmd+0x18bdfc0>
 7c4:	4d2b69bb 	stcmi	9, cr6, [fp, #-748]!	; 0xfffffd14
 7c8:	642e0d03 	strtvs	r0, [lr], #-3331	; 0xfffff2fd
 7cc:	2f302d2f 	svccs	0x00302d2f
 7d0:	04020050 	streq	r0, [r2], #-80	; 0xffffffb0
 7d4:	9e1a0301 	cdpls	3, 1, cr0, cr10, cr1, {0}
 7d8:	2d2f646a 	cfstrscs	mvf6, [pc, #-424]!	; 638 <.debug_line+0x638>
 7dc:	ad033030 	stcge	0, cr3, [r3, #-192]	; 0xffffff40
 7e0:	83a04a7f 	movhi	r4, #520192	; 0x7f000
 7e4:	bd342f2d 	ldclt	15, cr2, [r4, #-180]!	; 0xffffff4c
 7e8:	034b2d67 	movteq	r2, #48487	; 0xbd67
 7ec:	03832e21 	orreq	r2, r3, #528	; 0x210
 7f0:	2c68f210 	sfmcs	f7, 3, [r8], #-64	; 0xffffffc0
 7f4:	a4039f2f 	strge	r9, [r3], #-3887	; 0xfffff0d1
 7f8:	012e0201 	teqeq	lr, r1, lsl #4
 7fc:	6a312b69 	bvs	c4b5a8 <wmt_core_func_ctrl_cmd+0xc48188>
 800:	2e7703a4 	cdpcs	3, 7, cr0, cr7, cr4, {5}
 804:	04e10383 	strbteq	r0, [r1], #899	; 0x383
 808:	612c899e 			; <UNDEFINED> instruction: 0x612c899e
 80c:	302c3033 	eorcc	r3, ip, r3, lsr r0
 810:	2f334c2c 	svccs	0x00334c2c
 814:	03040200 	movweq	r0, #16896	; 0x4200
 818:	0200362d 	andeq	r3, r0, #47185920	; 0x2d00000
 81c:	78030204 	stmdavc	r3, {r2, r9}
 820:	02002f2e 	andeq	r2, r0, #46, 30	; 0xb8
 824:	002d0204 	eoreq	r0, sp, r4, lsl #4
 828:	06030402 	streq	r0, [r3], -r2, lsl #8
 82c:	2f2f064a 	svccs	0x002f064a
 830:	009f8684 	addseq	r8, pc, r4, lsl #13
 834:	06010402 	streq	r0, [r1], -r2, lsl #8
 838:	03670666 	cmneq	r7, #106954752	; 0x6600000
 83c:	7803f20e 	stmdavc	r3, {r1, r2, r3, r9, ip, sp, lr, pc}
 840:	02008366 	andeq	r8, r0, #-1744830463	; 0x98000001
 844:	66060104 	strvs	r0, [r6], -r4, lsl #2
 848:	84f46706 	ldrbthi	r6, [r4], #1798	; 0x706
 84c:	672e6603 	strvs	r6, [lr, -r3, lsl #12]!
 850:	bb032f2d 	bllt	cc50c <wmt_core_func_ctrl_cmd+0xc90ec>
 854:	8920087f 	stmdbhi	r0!, {r0, r1, r2, r3, r4, r5, r6, fp}
 858:	502c302c 	eorpl	r3, ip, ip, lsr #32
 85c:	292e7a03 	stmdbcs	lr!, {r0, r1, r9, fp, ip, sp, lr}
 860:	7a033235 	bvc	cd13c <wmt_core_func_ctrl_cmd+0xc9d1c>
 864:	7a03342e 	bvc	cd924 <wmt_core_func_ctrl_cmd+0xca504>
 868:	002f5066 	eoreq	r5, pc, r6, rrx
 86c:	06010402 	streq	r0, [r1], -r2, lsl #8
 870:	03670666 	cmneq	r7, #106954752	; 0x6600000
 874:	5a03d62c 	bpl	f612c <wmt_core_func_ctrl_cmd+0xf2d0c>
 878:	02008366 	andeq	r8, r0, #-1744830463	; 0x98000001
 87c:	66060104 	strvs	r0, [r6], -r4, lsl #2
 880:	2fd78306 	svccs	0x00d78306
 884:	4a110330 	bmi	44154c <wmt_core_func_ctrl_cmd+0x43e12c>
 888:	040200c2 	streq	r0, [r2], #-194	; 0xffffff3e
 88c:	06820601 	streq	r0, [r2], r1, lsl #12
 890:	66680367 	strbtvs	r0, [r8], -r7, ror #6
 894:	040200c2 	streq	r0, [r2], #-194	; 0xffffff3e
 898:	06820601 	streq	r0, [r2], r1, lsl #12
 89c:	02836d67 	addeq	r6, r3, #6592	; 0x19c0
 8a0:	034b1536 	movteq	r1, #46390	; 0xb536
 8a4:	02834a6c 	addeq	r4, r3, #108, 20	; 0x6c000
 8a8:	032f1530 	teqeq	pc, #48, 10	; 0xc000000
 8ac:	90087dcd 	andls	r7, r8, sp, asr #27
 8b0:	03821103 	orreq	r1, r2, #-1073741824	; 0xc0000000
 8b4:	12034a6f 	andne	r4, r3, #454656	; 0x6f000
 8b8:	312c4b2e 	teqcc	ip, lr, lsr #22
 8bc:	03323233 	teqeq	r2, #805306371	; 0x30000003
 8c0:	034b4a70 	movteq	r4, #47728	; 0xba70
 8c4:	03522e0b 	cmpeq	r2, #11, 28	; 0xb0
 8c8:	034b4a6d 	movteq	r4, #47725	; 0xba6d
 8cc:	69032e17 	stmdbvs	r3, {r0, r1, r2, r4, r9, sl, fp, sp}
 8d0:	326b4b2e 	rsbcc	r4, fp, #47104	; 0xb800
 8d4:	326a4e2a 	rsbcc	r4, sl, #672	; 0x2a0
 8d8:	2987a22a 	stmibcs	r7, {r1, r3, r5, r9, sp, pc}
 8dc:	302c3031 	eorcc	r3, ip, r1, lsr r0
 8e0:	01040200 	mrseq	r0, R12_usr
 8e4:	83062e06 	movwhi	r2, #28166	; 0x6e06
 8e8:	0402004c 	streq	r0, [r2], #-76	; 0xffffffb4
 8ec:	06660601 	strbteq	r0, [r6], -r1, lsl #12
 8f0:	48359f69 	ldmdami	r5!, {r0, r3, r5, r6, r8, r9, sl, fp, ip, pc}
 8f4:	032e5803 	teqeq	lr, #196608	; 0x30000
 8f8:	03312e27 	teqeq	r1, #624	; 0x270
 8fc:	77032e55 	smlsdvc	r3, r5, lr, r2
 900:	00d9032e 	sbcseq	r0, r9, lr, lsr #6
 904:	0200bb2e 	andeq	fp, r0, #47104	; 0xb800
 908:	66060104 	strvs	r0, [r6], -r4, lsl #2
 90c:	a14f6b06 	cmpge	pc, r6, lsl #22
 910:	1703312b 	strne	r3, [r3, -fp, lsr #2]
 914:	7fb0032e 	svcvc	0x00b0032e
 918:	55035166 	strpl	r5, [r3, #-358]	; 0xfffffe9a
 91c:	2d2c494a 	stccs	9, cr4, [ip, #-296]!	; 0xfffffed8
 920:	032e7a03 	teqeq	lr, #12288	; 0x3000
 924:	004a00e0 	subeq	r0, sl, r0, ror #1
 928:	06010402 	streq	r0, [r1], -r2, lsl #8
 92c:	50030666 	andpl	r0, r3, r6, ror #12
 930:	04020082 	streq	r0, [r2], #-130	; 0xffffff7e
 934:	06660601 	strbteq	r0, [r6], -r1, lsl #12
 938:	34039f69 	strcc	r9, [r3], #-3945	; 0xfffff097
 93c:	0402004a 	streq	r0, [r2], #-74	; 0xffffffb6
 940:	06660601 	strbteq	r0, [r6], -r1, lsl #12
 944:	04020067 	streq	r0, [r2], #-103	; 0xffffff99
 948:	06820601 	streq	r0, [r2], r1, lsl #12
 94c:	c1874b83 	orrgt	r4, r7, r3, lsl #23
 950:	0402004c 	streq	r0, [r2], #-76	; 0xffffffb4
 954:	06660601 	strbteq	r0, [r6], -r1, lsl #12
 958:	9f826203 	svcls	0x00826203
 95c:	5a034b2d 	bpl	d3618 <wmt_core_func_ctrl_cmd+0xd01f8>
 960:	2c2f2f2e 	stccs	15, cr2, [pc], #-184	; 8b0 <.debug_line+0x8b0>
 964:	4b2f2b31 	blmi	bcb630 <wmt_core_func_ctrl_cmd+0xbc8210>
 968:	02002f2f 	andeq	r2, r0, #47, 30	; 0xbc
 96c:	66060104 	strvs	r0, [r6], -r4, lsl #2
 970:	46a48406 	strtmi	r8, [r4], r6, lsl #8
 974:	03693132 	cmneq	r9, #-2147483636	; 0x8000000c
 978:	03667fbf 	cmneq	r6, #764	; 0x2fc
 97c:	0d032e34 	stceq	14, cr2, [r3, #-208]	; 0xffffff30
 980:	0365302e 	cmneq	r5, #46	; 0x2e
 984:	0f032e72 	svceq	0x00032e72
 988:	4a23032e 	bmi	8c1648 <wmt_core_func_ctrl_cmd+0x8be228>
 98c:	2f4983a3 	svccs	0x004983a3
 990:	654a5403 	strbvs	r5, [sl, #-1027]	; 0xfffffbfd
 994:	032e7503 	teqeq	lr, #12582912	; 0xc00000
 998:	65472e0c 	strbvs	r2, [r7, #-3596]	; 0xfffff1f4
 99c:	032e7803 	teqeq	lr, #196608	; 0x30000
 9a0:	0c032e09 	stceq	14, cr2, [r3], {9}
 9a4:	2f2d674a 	svccs	0x002d674a
 9a8:	087ede03 	ldmdaeq	lr!, {r0, r1, r9, sl, fp, ip, lr, pc}^
 9ac:	820903e4 	andhi	r0, r9, #228, 6	; 0x90000003
 9b0:	032e7703 	teqeq	lr, #786432	; 0xc0000
 9b4:	03352e09 	teqeq	r5, #9, 28	; 0x90
 9b8:	79032e7a 	stmdbvc	r3, {r1, r3, r4, r5, r6, r9, sl, fp, sp}
 9bc:	0335342e 	teqeq	r5, #771751936	; 0x2e000000
 9c0:	35332e74 	ldrcc	r2, [r3, #-3700]!	; 0xfffff18c
 9c4:	2f2e7903 	svccs	0x002e7903
 9c8:	032e7903 	teqeq	lr, #49152	; 0xc000
 9cc:	4f2a2e0b 	svcmi	0x002a2e0b
 9d0:	0083304b 	addeq	r3, r3, fp, asr #32
 9d4:	2d010402 	cfstrscs	mvf0, [r1, #-8]
 9d8:	2c4a0b03 	mcrrcs	11, 0, r0, sl, cr3
 9dc:	302c3084 	eorcc	r3, ip, r4, lsl #1
 9e0:	8983a167 	stmibhi	r3, {r0, r1, r2, r5, r6, r8, sp, pc}
 9e4:	4f834f9f 	svcmi	0x00834f9f
 9e8:	9e6f0367 	cdpls	3, 6, cr0, cr15, cr7, {3}
 9ec:	032e2303 	teqeq	lr, #201326592	; 0xc000000
 9f0:	7a034a63 	bvc	d3384 <wmt_core_func_ctrl_cmd+0xcff64>
 9f4:	02003582 	andeq	r3, r0, #545259520	; 0x20800000
 9f8:	62030104 	andvs	r0, r3, #4, 2
 9fc:	9f83862e 	svcls	0x0083862e
 a00:	034a1d03 	movteq	r1, #44291	; 0xad03
 a04:	0d038274 	sfmeq	f0, 1, [r3, #-464]	; 0xfffffe30
 a08:	03bb352e 			; <UNDEFINED> instruction: 0x03bb352e
 a0c:	03ac086b 			; <UNDEFINED> instruction: 0x03ac086b
 a10:	2f302e19 	svccs	0x00302e19
 a14:	032f4b65 	teqeq	pc, #103424	; 0x19400
 a18:	c8087f93 	stmdagt	r8, {r0, r1, r4, r7, r8, r9, sl, fp, ip, sp, lr}
 a1c:	2e790389 	cdpcs	3, 7, cr0, cr9, cr9, {4}
 a20:	456d2c35 	strbmi	r2, [sp, #-3125]!	; 0xfffff3cb
 a24:	03322a33 	teqeq	r2, #208896	; 0x33000
 a28:	03352e79 	teqeq	r5, #1936	; 0x790
 a2c:	2b312e79 	blcs	c4c418 <wmt_core_func_ctrl_cmd+0xc48ff8>
 a30:	02002f51 	andeq	r2, r0, #324	; 0x144
 a34:	66060104 	strvs	r0, [r6], -r4, lsl #2
 a38:	17036706 	strne	r6, [r3, -r6, lsl #14]
 a3c:	666f03f2 			; <UNDEFINED> instruction: 0x666f03f2
 a40:	04020083 	streq	r0, [r2], #-131	; 0xffffff7d
 a44:	06660601 	strbteq	r0, [r6], -r1, lsl #12
 a48:	312fd767 	teqcc	pc, r7, ror #14
 a4c:	040200c0 	streq	r0, [r2], #-192	; 0xffffff40
 a50:	06820601 	streq	r0, [r2], r1, lsl #12
 a54:	db03837d 	blle	e1850 <wmt_core_func_ctrl_cmd+0xde430>
 a58:	0146027e 	hvceq	24622	; 0x602e
 a5c:	29820903 	stmibcs	r2, {r0, r1, r8, fp}
 a60:	29333246 	ldmdbcs	r3!, {r1, r2, r6, r9, ip, sp}
 a64:	bb842f87 	bllt	fe10c888 <wmt_core_func_ctrl_cmd+0xfe109468>
 a68:	01040200 	mrseq	r0, R12_usr
 a6c:	67066606 	strvs	r6, [r6, -r6, lsl #12]
 a70:	4a00cb03 	bmi	33684 <wmt_core_func_ctrl_cmd+0x30264>
 a74:	2e5203d7 	mrccs	3, 2, r0, cr2, cr7, {6}
 a78:	00bc834c 	adcseq	r8, ip, ip, asr #6
 a7c:	06010402 	streq	r0, [r1], -r2, lsl #8
 a80:	4b68064a 	blmi	1a023b0 <wmt_core_func_ctrl_cmd+0x19fef90>
 a84:	0800c503 	stmdaeq	r0, {r0, r1, r8, sl, lr, pc}
 a88:	2f2d4c3c 	svccs	0x002d4c3c
 a8c:	00524b67 	subseq	r4, r2, r7, ror #22
 a90:	03010402 	movweq	r0, #5122	; 0x1402
 a94:	00667f85 	rsbeq	r7, r6, r5, lsl #31
 a98:	03010402 	movweq	r0, #5122	; 0x1402
 a9c:	838200f1 	orrhi	r0, r2, #241	; 0xf1
 aa0:	0402004e 	streq	r0, [r2], #-78	; 0xffffffb2
 aa4:	7fae0301 	svcvc	0x00ae0301
 aa8:	822203ba 	eorhi	r0, r2, #-402653182	; 0xe8000002
 aac:	2e7fb103 	expcse	f3, f3
 ab0:	2e00cf03 	cdpcs	15, 0, cr12, cr0, cr3, {0}
 ab4:	00bb8630 	adcseq	r8, fp, r0, lsr r6
 ab8:	06010402 	streq	r0, [r1], -r2, lsl #8
 abc:	03680666 	cmneq	r8, #106954752	; 0x6600000
 ac0:	83667fba 	cmnhi	r6, #744	; 0x2e8
 ac4:	01040200 	mrseq	r0, R12_usr
 ac8:	68064a06 	stmdavs	r6, {r1, r2, r9, fp, lr}
 acc:	ba25034b 	blt	941800 <wmt_core_func_ctrl_cmd+0x93e3e0>
 ad0:	83294b67 	teqhi	r9, #105472	; 0x19c00
 ad4:	01040200 	mrseq	r0, R12_usr
 ad8:	68066606 	stmdavs	r6, {r1, r2, r9, sl, sp, lr}
 adc:	03ba6003 			; <UNDEFINED> instruction: 0x03ba6003
 ae0:	0200ba0d 	andeq	fp, r0, #53248	; 0xd000
 ae4:	66060104 	strvs	r0, [r6], -r4, lsl #2
 ae8:	9e180306 	cdpls	3, 1, cr0, cr8, cr6, {0}
 aec:	00ba0d03 	adcseq	r0, sl, r3, lsl #26
 af0:	06010402 	streq	r0, [r1], -r2, lsl #8
 af4:	04020066 	streq	r0, [r2], #-102	; 0xffffff9a
 af8:	03a20601 			; <UNDEFINED> instruction: 0x03a20601
 afc:	0d038215 	sfmeq	f0, 1, [r3, #-84]	; 0xffffffac
 b00:	040200ba 	streq	r0, [r2], #-186	; 0xffffff46
 b04:	06660601 	strbteq	r0, [r6], -r1, lsl #12
 b08:	9e7faa03 	vaddls.f32	s21, s30, s6
 b0c:	cb034b83 	blgt	d3920 <wmt_core_func_ctrl_cmd+0xd0500>
 b10:	012e0200 	teqeq	lr, r0, lsl #4
 b14:	666f036a 	strbtvs	r0, [pc], -sl, ror #6
 b18:	04020083 	streq	r0, [r2], #-131	; 0xffffff7d
 b1c:	064a0601 	strbeq	r0, [sl], -r1, lsl #12
 b20:	61034b68 	tstvs	r3, r8, ror #22
 b24:	034b83d6 	movteq	r8, #46038	; 0xb3d6
 b28:	012e0224 	teqeq	lr, r4, lsr #4
 b2c:	cc034b83 	stcgt	11, cr4, [r3], {131}	; 0x83
 b30:	01600277 	smceq	39	; 0x27
 b34:	03820c03 	orreq	r0, r2, #768	; 0x300
 b38:	0c032e74 	stceq	14, cr2, [r3], {116}	; 0x74
 b3c:	2f2d674a 	svccs	0x002d674a
 b40:	6678036e 	ldrbtvs	r0, [r8], -lr, ror #6
 b44:	2e0f0331 	mcrcs	3, 0, r0, cr15, cr1, {1}
 b48:	03827703 	orreq	r7, r2, #786432	; 0xc0000
 b4c:	2a312e7a 	bcs	c4c53c <wmt_core_func_ctrl_cmd+0xc4911c>
 b50:	79032f34 	stmdbvc	r3, {r2, r4, r5, r8, r9, sl, fp, sp}
 b54:	2e10032e 	cdpcs	3, 1, cr0, cr0, cr14, {1}
 b58:	2a034b2f 	bcs	d381c <wmt_core_func_ctrl_cmd+0xd03fc>
 b5c:	03309f82 	teqeq	r0, #520	; 0x208
 b60:	50834a57 	addpl	r4, r3, r7, asr sl
 b64:	83318367 	teqhi	r1, #-1677721599	; 0x9c000001
 b68:	2e7303a0 	cdpcs	3, 7, cr0, cr3, cr0, {5}
 b6c:	2e0f0383 	cdpcs	3, 0, cr0, cr15, cr3, {4}
 b70:	6732bc67 	ldrvs	fp, [r2, -r7, ror #24]!
 b74:	0012029f 	mulseq	r2, pc, r2	; <UNPREDICTABLE>
 b78:	Address 0x00000b78 is out of bounds.


Disassembly of section .rodata:

00000000 <__FUNCTION__.3297>:
   0:	5f746d77 	svcpl	0x00746d77
   4:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
   8:	7461705f 	strbtvc	r7, [r1], #-95	; 0xffffffa1
   c:	635f6863 	cmpvs	pc, #6488064	; 0x630000
  10:	6b636568 	blvs	18d95b8 <wmt_core_func_ctrl_cmd+0x18d6198>
  14:	00000000 	andeq	r0, r0, r0

00000018 <wmt_core_opfunc>:
	...

00000064 <__FUNCTION__.2917>:
  64:	5f746d77 	svcpl	0x00746d77
  68:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  6c:	69706f5f 	ldmdbvs	r0!, {r0, r1, r2, r3, r4, r6, r8, r9, sl, fp, sp, lr}^
  70:	61685f64 	cmnvs	r8, r4, ror #30
  74:	656c646e 	strbvs	r6, [ip, #-1134]!	; 0xfffffb92
  78:	00000072 	andeq	r0, r0, r2, ror r0

0000007c <__FUNCTION__.2930>:
  7c:	5f746d77 	svcpl	0x00746d77
  80:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  84:	69706f5f 	ldmdbvs	r0!, {r0, r1, r2, r3, r4, r6, r8, r9, sl, fp, sp, lr}^
  88:	00000064 	andeq	r0, r0, r4, rrx

0000008c <__FUNCTION__.2982>:
  8c:	5f746d77 	svcpl	0x00746d77
  90:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  94:	6d75645f 	cfldrdvs	mvd6, [r5, #-380]!	; 0xfffffe84
  98:	61645f70 	smcvs	17904	; 0x45f0
  9c:	00006174 	andeq	r6, r0, r4, ror r1

000000a0 <__FUNCTION__.4275>:
  a0:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
  a4:	675f636e 	ldrbvs	r6, [pc, -lr, ror #6]
  a8:	5f6f6970 	svcpl	0x006f6970
  ac:	6c727463 	cfldrdvs	mvd7, [r2], #-396	; 0xfffffe74
  b0:	00000000 	andeq	r0, r0, r0

000000b4 <__FUNCTION__.3354>:
  b4:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
  b8:	685f636e 	ldmdavs	pc, {r1, r2, r3, r5, r6, r8, r9, sp, lr}^	; <UNPREDICTABLE>
  bc:	635f6669 	cmpvs	pc, #110100480	; 0x6900000
  c0:	00666e6f 	rsbeq	r6, r6, pc, ror #28

000000c4 <__FUNCTION__.2951>:
  c4:	5f746d77 	svcpl	0x00746d77
  c8:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  cc:	7274635f 	rsbsvc	r6, r4, #2080374785	; 0x7c000001
  d0:	0000006c 	andeq	r0, r0, ip, rrx

000000d4 <__FUNCTION__.3276>:
  d4:	5f746d77 	svcpl	0x00746d77
  d8:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  dc:	6d75645f 	cfldrdvs	mvd6, [r5, #-380]!	; 0xfffffe84
  e0:	75665f70 	strbvc	r5, [r6, #-3952]!	; 0xfffff090
  e4:	735f636e 	cmpvc	pc, #-1207959551	; 0xb8000001
  e8:	65746174 	ldrbvs	r6, [r4, #-372]!	; 0xfffffe8c
  ec:	00000000 	andeq	r0, r0, r0

000000f0 <__FUNCTION__.4083>:
  f0:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
  f4:	685f636e 	ldmdavs	pc, {r1, r2, r3, r5, r6, r8, r9, sp, lr}^	; <UNPREDICTABLE>
  f8:	73725f77 	cmnvc	r2, #476	; 0x1dc
  fc:	00000074 	andeq	r0, r0, r4, ror r0

00000100 <__FUNCTION__.2839>:
 100:	5f746d77 	svcpl	0x00746d77
 104:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
 108:	5f78725f 	svcpl	0x0078725f
 10c:	73756c66 	cmnvc	r5, #26112	; 0x6600
 110:	00000068 	andeq	r0, r0, r8, rrx

00000114 <__FUNCTION__.2823>:
 114:	5f746d77 	svcpl	0x00746d77
 118:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
 11c:	0078725f 	rsbseq	r7, r8, pc, asr r2

00000120 <__FUNCTION__.4298>:
 120:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 124:	735f636e 	cmpvc	pc, #-1207959551	; 0xb8000001
 128:	5f6f6964 	svcpl	0x006f6964
 12c:	6c727463 	cfldrdvs	mvd7, [r2], #-396	; 0xfffffe74
 130:	00000000 	andeq	r0, r0, r0

00000134 <__FUNCTION__.3692>:
 134:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 138:	655f636e 	ldrbvs	r6, [pc, #-878]	; fffffdd2 <wmt_core_func_ctrl_cmd+0xffffc9b2>
 13c:	00746978 	rsbseq	r6, r4, r8, ror r9

00000140 <__FUNCTION__.3229>:
 140:	5f746d77 	svcpl	0x00746d77
 144:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
 148:	7074735f 	rsbsvc	r7, r4, pc, asr r3
 14c:	6965645f 	stmdbvs	r5!, {r0, r1, r2, r3, r4, r6, sl, sp, lr}^
 150:	0074696e 	rsbseq	r6, r4, lr, ror #18

00000154 <__FUNCTION__.3439>:
 154:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 158:	705f636e 	subsvc	r6, pc, lr, ror #6
 15c:	6f5f7277 	svcvs	0x005f7277
 160:	00006666 	andeq	r6, r0, r6, ror #12

00000164 <__FUNCTION__.3592>:
 164:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 168:	665f636e 	ldrbvs	r6, [pc], -lr, ror #6
 16c:	5f636e75 	svcpl	0x00636e75
 170:	0066666f 	rsbeq	r6, r6, pc, ror #12

00000174 <__FUNCTION__.3056>:
 174:	5f746d77 	svcpl	0x00746d77
 178:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
 17c:	696e695f 	stmdbvs	lr!, {r0, r1, r2, r3, r4, r6, r8, fp, sp, lr}^
 180:	63735f74 	cmnvs	r3, #116, 30	; 0x1d0
 184:	74706972 	ldrbtvc	r6, [r0], #-2418	; 0xfffff68e
 188:	00000000 	andeq	r0, r0, r0

0000018c <__FUNCTION__.3012>:
 18c:	5f746d77 	svcpl	0x00746d77
 190:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
 194:	6765725f 			; <UNDEFINED> instruction: 0x6765725f
 198:	5f77725f 	svcpl	0x0077725f
 19c:	00776172 	rsbseq	r6, r7, r2, ror r1

000001a0 <__FUNCTION__.3129>:
 1a0:	5f746d77 	svcpl	0x00746d77
 1a4:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
 1a8:	7074735f 	rsbsvc	r7, r4, pc, asr r3
 1ac:	696e695f 	stmdbvs	lr!, {r0, r1, r2, r3, r4, r6, r8, fp, sp, lr}^
 1b0:	00000074 	andeq	r0, r0, r4, ror r0

000001b4 <__FUNCTION__.3311>:
 1b4:	5f746d77 	svcpl	0x00746d77
 1b8:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
 1bc:	5f77685f 	svcpl	0x0077685f
 1c0:	63656863 	cmnvs	r5, #6488064	; 0x630000
 1c4:	0000006b 	andeq	r0, r0, fp, rrx

000001c8 <__FUNCTION__.3386>:
 1c8:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 1cc:	705f636e 	subsvc	r6, pc, lr, ror #6
 1d0:	6f5f7277 	svcvs	0x005f7277
 1d4:	0000006e 	andeq	r0, r0, lr, rrx

000001d8 <__FUNCTION__.3472>:
 1d8:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 1dc:	665f636e 	ldrbvs	r6, [pc], -lr, ror #6
 1e0:	5f636e75 	svcpl	0x00636e75
 1e4:	00006e6f 	andeq	r6, r0, pc, ror #28

000001e8 <__FUNCTION__.3676>:
 1e8:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 1ec:	725f636e 	subsvc	r6, pc, #-1207959551	; 0xb8000001
 1f0:	725f6765 	subsvc	r6, pc, #26476544	; 0x1940000
 1f4:	00000077 	andeq	r0, r0, r7, ror r0

000001f8 <__FUNCTION__.4239>:
 1f8:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 1fc:	655f636e 	ldrbvs	r6, [pc, #-878]	; fffffe96 <wmt_core_func_ctrl_cmd+0xffffca76>
 200:	65737566 	ldrbvs	r7, [r3, #-1382]!	; 0xfffffa9a
 204:	0077725f 	rsbseq	r7, r7, pc, asr r2

00000208 <__FUNCTION__.4159>:
 208:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 20c:	745f636e 	ldrbvc	r6, [pc], #-878	; 214 <__FUNCTION__.4159+0xc>
 210:	6d726568 	cfldr64vs	mvdx6, [r2, #-416]!	; 0xfffffe60
 214:	7274635f 	rsbsvc	r6, r4, #2080374785	; 0x7c000001
 218:	0000006c 	andeq	r0, r0, ip, rrx

0000021c <C.89.3997>:
 21c:	00010201 	andeq	r0, r1, r1, lsl #4
 220:	00000008 	andeq	r0, r0, r8

00000224 <C.90.3998>:
 224:	00000202 	andeq	r0, r0, r2, lsl #4
 228:	00000000 	andeq	r0, r0, r0

0000022c <C.91.3999>:
 22c:	00010201 	andeq	r0, r1, r1, lsl #4
 230:	00000009 	andeq	r0, r0, r9

00000234 <C.92.4000>:
 234:	00000202 	andeq	r0, r0, r2, lsl #4
 238:	00000000 	andeq	r0, r0, r0

0000023c <C.93.4001>:
 23c:	00021001 	andeq	r1, r2, r1
 240:	0000aa08 	andeq	sl, r0, r8, lsl #20

00000244 <C.94.4002>:
 244:	00051002 	andeq	r1, r5, r2
 248:	aaaaaa00 	bge	feaaaa50 <wmt_core_func_ctrl_cmd+0xfeaa7630>
 24c:	000000aa 	andeq	r0, r0, sl, lsr #1

00000250 <C.95.4003>:
 250:	00071002 	andeq	r1, r7, r2
 254:	aaaaaa00 	bge	feaaaa5c <wmt_core_func_ctrl_cmd+0xfeaa763c>
 258:	00bbbbaa 	adcseq	fp, fp, sl, lsr #23

0000025c <C.96.4004>:
 25c:	000b1002 	andeq	r1, fp, r2
 260:	aaaaaa00 	bge	feaaaa68 <wmt_core_func_ctrl_cmd+0xfeaa7648>
 264:	bbbbbbaa 	bllt	feeef114 <wmt_core_func_ctrl_cmd+0xfeeebcf4>
 268:	000000bb 	strheq	r0, [r0], -fp

0000026c <__FUNCTION__.3996>:
 26c:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 270:	635f636e 	cmpvs	pc, #-1207959551	; 0xb8000001
 274:	745f646d 	ldrbvc	r6, [pc], #-1133	; 27c <C.81.3922>
 278:	00747365 	rsbseq	r7, r4, r5, ror #6

0000027c <C.81.3922>:
 27c:	00000201 	andeq	r0, r0, r1, lsl #4
 280:	00000007 	andeq	r0, r0, r7

00000284 <C.82.3923>:
 284:	00000202 	andeq	r0, r0, r2, lsl #4
 288:	00000000 	andeq	r0, r0, r0

0000028c <__FUNCTION__.3920>:
 28c:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 290:	6c5f636e 	mrrcvs	3, 6, r6, pc, cr14	; <UNPREDICTABLE>
 294:	006b6270 	rsbeq	r6, fp, r0, ror r2

00000298 <__FUNCTION__.3858>:
 298:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 29c:	645f636e 	ldrbvs	r6, [pc], #-878	; 2a4 <__FUNCTION__.3707>
 2a0:	00736e73 	rsbseq	r6, r3, r3, ror lr

000002a4 <__FUNCTION__.3707>:
 2a4:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
 2a8:	705f636e 	subsvc	r6, pc, lr, ror #6
 2ac:	735f7277 	cmpvc	pc, #1879048199	; 0x70000007
 2b0:	00000076 	andeq	r0, r0, r6, ror r0

000002b4 <WMT_SLEEP_CMD>:
 2b4:	00010301 	andeq	r0, r1, r1, lsl #6
 2b8:	00000001 	andeq	r0, r0, r1

000002bc <WMT_SLEEP_EVT>:
 2bc:	00020302 	andeq	r0, r2, r2, lsl #6
 2c0:	00000100 	andeq	r0, r0, r0, lsl #2

000002c4 <WMT_WAKEUP_CMD>:
 2c4:	000000ff 	strdeq	r0, [r0], -pc	; <UNPREDICTABLE>

000002c8 <WMT_WAKEUP_EVT>:
 2c8:	00020302 	andeq	r0, r2, r2, lsl #6
 2cc:	00000300 	andeq	r0, r0, r0, lsl #6

000002d0 <WMT_HOST_AWAKE_CMD>:
 2d0:	00010301 	andeq	r0, r1, r1, lsl #6
 2d4:	00000002 	andeq	r0, r0, r2

000002d8 <WMT_HOST_AWAKE_EVT>:
 2d8:	00020302 	andeq	r0, r2, r2, lsl #6
 2dc:	00000200 	andeq	r0, r0, r0, lsl #4

000002e0 <__FUNCTION__.2860>:
 2e0:	5f746d77 	svcpl	0x00746d77
 2e4:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
 2e8:	6e75665f 	mrcvs	6, 3, r6, cr5, cr15, {2}
 2ec:	74635f63 	strbtvc	r5, [r3], #-3939	; 0xfffff09d
 2f0:	635f6c72 	cmpvs	pc, #29184	; 0x7200
 2f4:	0000646d 	andeq	r6, r0, sp, ror #8

Disassembly of section .rodata.str1.4:

00000000 <.rodata.str1.4>:
       0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
       4:	5b5d432d 	blpl	1750cc0 <wmt_core_func_ctrl_cmd+0x174d8a0>
       8:	73255d45 	teqvc	r5, #4416	; 0x1140
       c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
      10:	6968633a 	stmdbvs	r8!, {r1, r3, r4, r5, r8, r9, sp, lr}^
      14:	65762070 	ldrbvs	r2, [r6, #-112]!	; 0xffffff90
      18:	6f697372 	svcvs	0x00697372
      1c:	7830286e 	ldmdavc	r0!, {r1, r2, r3, r5, r6, fp, sp}
      20:	20297825 	eorcs	r7, r9, r5, lsr #16
      24:	73656f64 	cmnvc	r5, #100, 30	; 0x190
      28:	746f6e20 	strbtvc	r6, [pc], #-3616	; 30 <.rodata.str1.4+0x30>
      2c:	74616d20 	strbtvc	r6, [r1], #-3360	; 0xfffff2e0
      30:	70206863 	eorvc	r6, r0, r3, ror #16
      34:	68637461 	stmdavs	r3!, {r0, r5, r6, sl, ip, sp, lr}^
      38:	72657620 	rsbvc	r7, r5, #32, 12	; 0x2000000
      3c:	6e6f6973 	mcrvs	9, 3, r6, cr15, cr3, {3}
      40:	25783028 	ldrbcs	r3, [r8, #-40]!	; 0xffffffd8
      44:	000a2978 	andeq	r2, sl, r8, ror r9
      48:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
      4c:	5b5d432d 	blpl	1750d08 <wmt_core_func_ctrl_cmd+0x174d8e8>
      50:	73255d45 	teqvc	r5, #4416	; 0x1140
      54:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
      58:	6c756e3a 	ldclvs	14, cr6, [r5], #-232	; 0xffffff18
      5c:	6168206c 	cmnvs	r8, ip, rrx
      60:	656c646e 	strbvs	r6, [ip, #-1134]!	; 0xfffffb92
      64:	25282072 	strcs	r2, [r8, #-114]!	; 0xffffff8e
      68:	000a2964 	andeq	r2, sl, r4, ror #18
      6c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
      70:	5b5d432d 	blpl	1750d2c <wmt_core_func_ctrl_cmd+0x174d90c>
      74:	73255d45 	teqvc	r5, #4416	; 0x1140
      78:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
      7c:	6c756e3a 	ldclvs	14, cr6, [r5], #-232	; 0xffffff18
      80:	5770206c 	ldrbpl	r2, [r0, -ip, rrx]!
      84:	504f746d 	subpl	r7, pc, sp, ror #8
      88:	0000000a 	andeq	r0, r0, sl
      8c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
      90:	5b5d432d 	blpl	1750d4c <wmt_core_func_ctrl_cmd+0x174d92c>
      94:	73255d45 	teqvc	r5, #4416	; 0x1140
      98:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
      9c:	766e693a 			; <UNDEFINED> instruction: 0x766e693a
      a0:	64696c61 	strbtvs	r6, [r9], #-3169	; 0xfffff39f
      a4:	49504f20 	ldmdbmi	r0, {r5, r8, r9, sl, fp, lr}^
      a8:	64252844 	strtvs	r2, [r5], #-2116	; 0xfffff7bc
      ac:	00000a29 	andeq	r0, r0, r9, lsr #20
      b0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
      b4:	5b5d432d 	blpl	1750d70 <wmt_core_func_ctrl_cmd+0x174d950>
      b8:	73255d49 	teqvc	r5, #4672	; 0x1240
      bc:	2073253a 	rsbscs	r2, r3, sl, lsr r5
      c0:	3d6e656c 	cfstr64cc	mvdx6, [lr, #-432]!	; 0xfffffe50
      c4:	000a6425 	andeq	r6, sl, r5, lsr #8
      c8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
      cc:	5b5d432d 	blpl	1750d88 <wmt_core_func_ctrl_cmd+0x174d968>
      d0:	73255d49 	teqvc	r5, #4672	; 0x1240
      d4:	00000a3a 	andeq	r0, r0, sl, lsr sl
      d8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
      dc:	5b5d432d 	blpl	1750d98 <wmt_core_func_ctrl_cmd+0x174d978>
      e0:	73255d49 	teqvc	r5, #4672	; 0x1240
      e4:	2578303a 	ldrbcs	r3, [r8, #-58]!	; 0xffffffc6
      e8:	20783230 	rsbscs	r3, r8, r0, lsr r2
      ec:	00000000 	andeq	r0, r0, r0
      f0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
      f4:	5b5d432d 	blpl	1750db0 <wmt_core_func_ctrl_cmd+0x174d990>
      f8:	73255d49 	teqvc	r5, #4672	; 0x1240
      fc:	652d2d3a 	strvs	r2, [sp, #-3386]!	; 0xfffff2c6
     100:	000a646e 	andeq	r6, sl, lr, ror #8
     104:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     108:	5b5d432d 	blpl	1750dc4 <wmt_core_func_ctrl_cmd+0x174d9a4>
     10c:	73255d45 	teqvc	r5, #4416	; 0x1140
     110:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     114:	6961663a 	stmdbvs	r1!, {r1, r3, r4, r5, r9, sl, sp, lr}^
     118:	63203a6c 	teqvs	r0, #108, 20	; 0x6c000
     11c:	20706968 	rsbscs	r6, r0, r8, ror #18
     120:	70207369 	eorvc	r7, r0, r9, ror #6
     124:	7265776f 	rsbvc	r7, r5, #29097984	; 0x1bc0000
     128:	6f206465 	svcvs	0x00206465
     12c:	000a6666 	andeq	r6, sl, r6, ror #12
     130:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     134:	5b5d432d 	blpl	1750df0 <wmt_core_func_ctrl_cmd+0x174d9d0>
     138:	73255d45 	teqvc	r5, #4416	; 0x1140
     13c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     140:	744d673a 	strbvc	r6, [sp], #-1850	; 0xfffff8c6
     144:	746d576b 	strbtvc	r5, [sp], #-1899	; 0xfffff895
     148:	2e787443 	cdpcs	4, 7, cr7, cr8, cr3, {2}
     14c:	63695f70 	cmnvs	r9, #112, 30	; 0x1c0
     150:	73706f5f 	cmnvc	r0, #380	; 0x17c
     154:	63693e2d 	cmnvs	r9, #720	; 0x2d0
     158:	6e69705f 	mcrvs	0, 3, r7, cr9, cr15, {2}
     15c:	7274635f 	rsbsvc	r6, r4, #2080374785	; 0x7c000001
     160:	554e286c 	strbpl	r2, [lr, #-2156]	; 0xfffff794
     164:	0a294c4c 	beq	a5329c <wmt_core_func_ctrl_cmd+0xa4fe7c>
     168:	00000000 	andeq	r0, r0, r0
     16c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     170:	5b5d432d 	blpl	1750e2c <wmt_core_func_ctrl_cmd+0x174da0c>
     174:	73255d49 	teqvc	r5, #4672	; 0x1240
     178:	2063693a 	rsbcs	r6, r3, sl, lsr r9
     17c:	206e6970 	rsbcs	r6, lr, r0, ror r9
     180:	253a6469 	ldrcs	r6, [sl, #-1129]!	; 0xfffffb97
     184:	73202c64 	teqvc	r0, #100, 24	; 0x6400
     188:	3a746174 	bcc	1d18760 <wmt_core_func_ctrl_cmd+0x1d15340>
     18c:	202c6425 	eorcs	r6, ip, r5, lsr #8
     190:	67616c66 	strbvs	r6, [r1, -r6, ror #24]!
     194:	2578303a 	ldrbcs	r3, [r8, #-58]!	; 0xffffffc6
     198:	00000a78 	andeq	r0, r0, r8, ror sl
     19c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     1a0:	5b5d432d 	blpl	1750e5c <wmt_core_func_ctrl_cmd+0x174da3c>
     1a4:	73255d45 	teqvc	r5, #4416	; 0x1140
     1a8:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     1ac:	206f6e3a 	rsbcs	r6, pc, sl, lsr lr	; <UNPREDICTABLE>
     1b0:	5f464948 	svcpl	0x00464948
     1b4:	20544942 	subscs	r4, r4, r2, asr #18
     1b8:	57206e69 	strpl	r6, [r0, -r9, ror #28]!
     1bc:	4f5f544d 	svcmi	0x005f544d
     1c0:	000a2150 	andeq	r2, sl, r0, asr r1
     1c4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     1c8:	5b5d432d 	blpl	1750e84 <wmt_core_func_ctrl_cmd+0x174da64>
     1cc:	73255d49 	teqvc	r5, #4672	; 0x1240
     1d0:	544d573a 	strbpl	r5, [sp], #-1850	; 0xfffff8c6
     1d4:	46494820 	strbmi	r4, [r9], -r0, lsr #16
     1d8:	726c6120 	rsbvc	r6, ip, #32, 2
     1dc:	79646165 	stmdbvc	r4!, {r0, r2, r5, r6, r8, sp, lr}^
     1e0:	69786520 	ldmdbvs	r8!, {r5, r8, sl, sp, lr}^
     1e4:	202e7473 	eorcs	r7, lr, r3, ror r4
     1e8:	7265766f 	rsbvc	r7, r5, #116391936	; 0x6f00000
     1ec:	74697277 	strbtvc	r7, [r9], #-631	; 0xfffffd89
     1f0:	6f202165 	svcvs	0x00202165
     1f4:	2820646c 	stmdacs	r0!, {r2, r3, r5, r6, sl, sp, lr}
     1f8:	2c296425 	cfstrscs	mvf6, [r9], #-148	; 0xffffff6c
     1fc:	77656e20 	strbvc	r6, [r5, -r0, lsr #28]!
     200:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     204:	00000a29 	andeq	r0, r0, r9, lsr #20
     208:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     20c:	5b5d432d 	blpl	1750ec8 <wmt_core_func_ctrl_cmd+0x174daa8>
     210:	73255d49 	teqvc	r5, #4672	; 0x1240
     214:	544d573a 	strbpl	r5, [sp], #-1850	; 0xfffff8c6
     218:	46494820 	strbmi	r4, [r9], -r0, lsr #16
     21c:	666e6920 	strbtvs	r6, [lr], -r0, lsr #18
     220:	6461206f 	strbtvs	r2, [r1], #-111	; 0xffffff91
     224:	0a646564 	beq	19197bc <wmt_core_func_ctrl_cmd+0x191639c>
     228:	00000000 	andeq	r0, r0, r0
     22c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     230:	5b5d432d 	blpl	1750eec <wmt_core_func_ctrl_cmd+0x174dacc>
     234:	73255d45 	teqvc	r5, #4416	; 0x1140
     238:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     23c:	6961663a 	stmdbvs	r1!, {r1, r3, r4, r5, r9, sl, sp, lr}^
     240:	3a64656c 	bcc	19197f8 <wmt_core_func_ctrl_cmd+0x19163d8>
     244:	28646920 	stmdacs	r4!, {r5, r8, fp, sp, lr}^
     248:	2c296425 	cfstrscs	mvf6, [r9], #-148	; 0xffffff6c
     24c:	70797420 	rsbsvc	r7, r9, r0, lsr #8
     250:	64252865 	strtvs	r2, [r5], #-2149	; 0xfffff79b
     254:	76202c29 	strtvc	r2, [r0], -r9, lsr #24
     258:	65756c61 	ldrbvs	r6, [r5, #-3169]!	; 0xfffff39f
     25c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     260:	65526920 	ldrbvs	r6, [r2, #-2336]	; 0xfffff6e0
     264:	25283a74 	strcs	r3, [r8, #-2676]!	; 0xfffff58c
     268:	000a2964 	andeq	r2, sl, r4, ror #18
     26c:	202c7325 	eorcs	r7, ip, r5, lsr #6
     270:	202c6425 	eorcs	r6, ip, r5, lsr #8
     274:	29732528 	ldmdbcs	r3!, {r3, r5, r8, sl, sp}^
     278:	0000000a 	andeq	r0, r0, sl
     27c:	76697264 	strbtvc	r7, [r9], -r4, ror #4
     280:	2f737265 	svccs	0x00737265
     284:	5f6b746d 	svcpl	0x006b746d
     288:	5f6e6377 	svcpl	0x006e6377
     28c:	626d6f63 	rsbvs	r6, sp, #396	; 0x18c
     290:	6f632f6f 	svcvs	0x00632f6f
     294:	6e6f6d6d 	cdpvs	13, 6, cr6, cr15, cr13, {3}
     298:	726f632f 	rsbvc	r6, pc, #-1140850688	; 0xbc000000
     29c:	6d772f65 	ldclvs	15, cr2, [r7, #-404]!	; 0xfffffe6c
     2a0:	6f635f74 	svcvs	0x00635f74
     2a4:	632e6572 	teqvs	lr, #478150656	; 0x1c800000
     2a8:	00000000 	andeq	r0, r0, r0
     2ac:	00000030 	andeq	r0, r0, r0, lsr r0
     2b0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     2b4:	5b5d432d 	blpl	1750f70 <wmt_core_func_ctrl_cmd+0x174db50>
     2b8:	73255d49 	teqvc	r5, #4672	; 0x1240
     2bc:	73255b3a 	teqvc	r5, #59392	; 0xe800
     2c0:	6174735d 	cmnvs	r4, sp, asr r3
     2c4:	28737574 	ldmdacs	r3!, {r2, r4, r5, r6, r8, sl, ip, sp, lr}^
     2c8:	64253a62 	strtvs	r3, [r5], #-2658	; 0xfffff59e
     2cc:	253a6620 	ldrcs	r6, [sl, #-1568]!	; 0xfffff9e0
     2d0:	3a672064 	bcc	19c8468 <wmt_core_func_ctrl_cmd+0x19c5048>
     2d4:	77206425 	strvc	r6, [r0, -r5, lsr #8]!
     2d8:	2064253a 	rsbcs	r2, r4, sl, lsr r5
     2dc:	6b62706c 	blvs	189c494 <wmt_core_func_ctrl_cmd+0x1899074>
     2e0:	2064253a 	rsbcs	r2, r4, sl, lsr r5
     2e4:	3a746d77 	bcc	1d1b8c8 <wmt_core_func_ctrl_cmd+0x1d184a8>
     2e8:	73206425 	teqvc	r0, #620756992	; 0x25000000
     2ec:	253a3164 	ldrcs	r3, [sl, #-356]!	; 0xfffffe9c
     2f0:	64732064 	ldrbtvs	r2, [r3], #-100	; 0xffffff9c
     2f4:	64253a32 	strtvs	r3, [r5], #-2610	; 0xfffff5ce
     2f8:	70747320 	rsbsvc	r7, r4, r0, lsr #6
     2fc:	2964253a 	stmdbcs	r4!, {r1, r3, r4, r5, r8, sl, sp}^
     300:	0000000a 	andeq	r0, r0, sl
     304:	48204542 	stmdami	r0!, {r1, r6, r8, sl, lr}
     308:	53522057 	cmppl	r2, #87	; 0x57
     30c:	00000054 	andeq	r0, r0, r4, asr r0
     310:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     314:	5b5d432d 	blpl	1750fd0 <wmt_core_func_ctrl_cmd+0x174dbb0>
     318:	73255d45 	teqvc	r5, #4416	; 0x1140
     31c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     320:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     324:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     328:	44532066 	ldrbmi	r2, [r3], #-102	; 0xffffff9a
     32c:	575f4f49 	ldrbpl	r4, [pc, -r9, asr #30]
     330:	20494649 	subcs	r4, r9, r9, asr #12
     334:	636e7566 	cmnvs	lr, #427819008	; 0x19800000
     338:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
     33c:	2528206c 	strcs	r2, [r8, #-108]!	; 0xffffff94
     340:	000a2964 	andeq	r2, sl, r4, ror #18
     344:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     348:	5b5d432d 	blpl	1751004 <wmt_core_func_ctrl_cmd+0x174dbe4>
     34c:	73255d49 	teqvc	r5, #4672	; 0x1240
     350:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     354:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     358:	44532066 	ldrbmi	r2, [r3], #-102	; 0xffffff9a
     35c:	57204f49 	strpl	r4, [r0, -r9, asr #30]!
     360:	20494649 	subcs	r4, r9, r9, asr #12
     364:	636e7566 	cmnvs	lr, #427819008	; 0x19800000
     368:	0a6b6f20 	beq	1adbff0 <wmt_core_func_ctrl_cmd+0x1ad8bd0>
     36c:	00000000 	andeq	r0, r0, r0
     370:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     374:	5b5d432d 	blpl	1751030 <wmt_core_func_ctrl_cmd+0x174dc10>
     378:	73255d45 	teqvc	r5, #4416	; 0x1140
     37c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     380:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     384:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     388:	4c532066 	mrrcmi	0, 6, r2, r3, cr6
     38c:	535f544f 	cmppl	pc, #1325400064	; 0x4f000000
     390:	314f4944 	cmpcc	pc, r4, asr #18
     394:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
     398:	2528206c 	strcs	r2, [r8, #-108]!	; 0xffffff94
     39c:	000a2964 	andeq	r2, sl, r4, ror #18
     3a0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     3a4:	5b5d432d 	blpl	1751060 <wmt_core_func_ctrl_cmd+0x174dc40>
     3a8:	73255d49 	teqvc	r5, #4672	; 0x1240
     3ac:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     3b0:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     3b4:	4c532066 	mrrcmi	0, 6, r2, r3, cr6
     3b8:	535f544f 	cmppl	pc, #1325400064	; 0x4f000000
     3bc:	314f4944 	cmpcc	pc, r4, asr #18
     3c0:	0a6b6f20 	beq	1adc048 <wmt_core_func_ctrl_cmd+0x1ad8c28>
     3c4:	00000000 	andeq	r0, r0, r0
     3c8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     3cc:	5b5d432d 	blpl	1751088 <wmt_core_func_ctrl_cmd+0x174dc68>
     3d0:	73255d45 	teqvc	r5, #4416	; 0x1140
     3d4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     3d8:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     3dc:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     3e0:	44532066 	ldrbmi	r2, [r3], #-102	; 0xffffff9a
     3e4:	465f4f49 	ldrbmi	r4, [pc], -r9, asr #30
     3e8:	5f434e55 	svcpl	0x00434e55
     3ec:	20505453 	subscs	r5, r0, r3, asr r4
     3f0:	636e7566 	cmnvs	lr, #427819008	; 0x19800000
     3f4:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
     3f8:	2528206c 	strcs	r2, [r8, #-108]!	; 0xffffff94
     3fc:	000a2964 	andeq	r2, sl, r4, ror #18
     400:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     404:	5b5d432d 	blpl	17510c0 <wmt_core_func_ctrl_cmd+0x174dca0>
     408:	73255d49 	teqvc	r5, #4672	; 0x1240
     40c:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     410:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     414:	44532066 	ldrbmi	r2, [r3], #-102	; 0xffffff9a
     418:	465f4f49 	ldrbmi	r4, [pc], -r9, asr #30
     41c:	5f434e55 	svcpl	0x00434e55
     420:	20505453 	subscs	r5, r0, r3, asr r4
     424:	636e7566 	cmnvs	lr, #427819008	; 0x19800000
     428:	0a6b6f20 	beq	1adc0b0 <wmt_core_func_ctrl_cmd+0x1ad8c90>
     42c:	00000000 	andeq	r0, r0, r0
     430:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     434:	5b5d432d 	blpl	17510f0 <wmt_core_func_ctrl_cmd+0x174dcd0>
     438:	73255d45 	teqvc	r5, #4416	; 0x1140
     43c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     440:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     444:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     448:	4c532066 	mrrcmi	0, 6, r2, r3, cr6
     44c:	535f544f 	cmppl	pc, #1325400064	; 0x4f000000
     450:	324f4944 	subcc	r4, pc, #68, 18	; 0x110000
     454:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
     458:	2528206c 	strcs	r2, [r8, #-108]!	; 0xffffff94
     45c:	000a2964 	andeq	r2, sl, r4, ror #18
     460:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     464:	5b5d432d 	blpl	1751120 <wmt_core_func_ctrl_cmd+0x174dd00>
     468:	73255d49 	teqvc	r5, #4672	; 0x1240
     46c:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     470:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     474:	4c532066 	mrrcmi	0, 6, r2, r3, cr6
     478:	535f544f 	cmppl	pc, #1325400064	; 0x4f000000
     47c:	324f4944 	subcc	r4, pc, #68, 18	; 0x110000
     480:	0a6b6f20 	beq	1adc108 <wmt_core_func_ctrl_cmd+0x1ad8ce8>
     484:	00000000 	andeq	r0, r0, r0
     488:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     48c:	5b5d432d 	blpl	1751148 <wmt_core_func_ctrl_cmd+0x174dd28>
     490:	73255d45 	teqvc	r5, #4416	; 0x1140
     494:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     498:	2057483a 	subscs	r4, r7, sl, lsr r8
     49c:	20545352 	subscs	r5, r4, r2, asr r3
     4a0:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
     4a4:	65526920 	ldrbvs	r6, [r2, #-2336]	; 0xfffff6e0
     4a8:	64252874 	strtvs	r2, [r5], #-2164	; 0xfffff78c
     4ac:	00000a29 	andeq	r0, r0, r9, lsr #20
     4b0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     4b4:	5b5d432d 	blpl	1751170 <wmt_core_func_ctrl_cmd+0x174dd50>
     4b8:	73255d49 	teqvc	r5, #4672	; 0x1240
     4bc:	2057483a 	subscs	r4, r7, sl, lsr r8
     4c0:	20545352 	subscs	r5, r4, r2, asr r3
     4c4:	000a6b6f 	andeq	r6, sl, pc, ror #22
     4c8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     4cc:	5b5d432d 	blpl	1751188 <wmt_core_func_ctrl_cmd+0x174dd68>
     4d0:	73255d45 	teqvc	r5, #4416	; 0x1140
     4d4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     4d8:	5054533a 	subspl	r5, r4, sl, lsr r3
     4dc:	4f4c435f 	svcmi	0x004c435f
     4e0:	66204553 			; <UNDEFINED> instruction: 0x66204553
     4e4:	656c6961 	strbvs	r6, [ip, #-2401]!	; 0xfffff69f
     4e8:	00000a64 	andeq	r0, r0, r4, ror #20
     4ec:	48204641 	stmdami	r0!, {r0, r6, r9, sl, lr}
     4f0:	53522057 	cmppl	r2, #87	; 0x57
     4f4:	00000054 	andeq	r0, r0, r4, asr r0
     4f8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     4fc:	5b5d432d 	blpl	17511b8 <wmt_core_func_ctrl_cmd+0x174dd98>
     500:	73255d45 	teqvc	r5, #4416	; 0x1140
     504:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     508:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
     50c:	7274635f 	rsbsvc	r6, r4, #2080374785	; 0x7c000001
     510:	6166206c 	cmnvs	r6, ip, rrx
     514:	64656c69 	strbtvs	r6, [r5], #-3177	; 0xfffff397
     518:	4d57203a 	ldclmi	0, cr2, [r7, #-232]	; 0xffffff18
     51c:	54435f54 	strbpl	r5, [r3], #-3924	; 0xfffff0ac
     520:	525f4c52 	subspl	r4, pc, #20992	; 0x5200
     524:	4c465f58 	mcrrmi	15, 5, r5, r6, cr8
     528:	2c485355 	mcrrcs	3, 5, r5, r8, cr5
     52c:	65526920 	ldrbvs	r6, [r2, #-2336]	; 0xfffff6e0
     530:	64253a74 	strtvs	r3, [r5], #-2676	; 0xfffff58c
     534:	0000000a 	andeq	r0, r0, sl
     538:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     53c:	5b5d432d 	blpl	17511f8 <wmt_core_func_ctrl_cmd+0x174ddd8>
     540:	73255d45 	teqvc	r5, #4416	; 0x1140
     544:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     548:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
     54c:	7274635f 	rsbsvc	r6, r4, #2080374785	; 0x7c000001
     550:	6166206c 	cmnvs	r6, ip, rrx
     554:	64656c69 	strbtvs	r6, [r5], #-3177	; 0xfffff397
     558:	4d57203a 	ldclmi	0, cr2, [r7, #-232]	; 0xffffff18
     55c:	54435f54 	strbpl	r5, [r3], #-3924	; 0xfffff0ac
     560:	525f4c52 	subspl	r4, pc, #20992	; 0x5200
     564:	69202c58 	stmdbvs	r0!, {r3, r4, r6, sl, fp, sp}
     568:	3a746552 	bcc	1d19ab8 <wmt_core_func_ctrl_cmd+0x1d16698>
     56c:	000a6425 	andeq	r6, sl, r5, lsr #8
     570:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     574:	5b5d432d 	blpl	1751230 <wmt_core_func_ctrl_cmd+0x174de10>
     578:	73255d57 	teqvc	r5, #5568	; 0x15c0
     57c:	4944533a 	stmdbmi	r4, {r1, r3, r4, r5, r8, r9, ip, lr}^
     580:	7768204f 	strbvc	r2, [r8, -pc, asr #32]!
     584:	72746320 	rsbsvc	r6, r4, #32, 6	; 0x80000000
     588:	6166206c 	cmnvs	r6, ip, rrx
     58c:	72206c69 	eorvc	r6, r0, #26880	; 0x6900
     590:	25287465 	strcs	r7, [r8, #-1125]!	; 0xfffffb9b
     594:	000a2964 	andeq	r2, sl, r4, ror #18
     598:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     59c:	5b5d432d 	blpl	1751258 <wmt_core_func_ctrl_cmd+0x174de38>
     5a0:	73255d49 	teqvc	r5, #4672	; 0x1240
     5a4:	4944533a 	stmdbmi	r4, {r1, r3, r4, r5, r8, r9, ip, lr}^
     5a8:	7768204f 	strbvc	r2, [r8, -pc, asr #32]!
     5ac:	72746320 	rsbsvc	r6, r4, #32, 6	; 0x80000000
     5b0:	7573206c 	ldrbvc	r2, [r3, #-108]!	; 0xffffff94
     5b4:	65656363 	strbvs	r6, [r5, #-867]!	; 0xfffffc9d
     5b8:	0a202064 	beq	808750 <wmt_core_func_ctrl_cmd+0x805330>
     5bc:	00000000 	andeq	r0, r0, r0
     5c0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     5c4:	5b5d432d 	blpl	1751280 <wmt_core_func_ctrl_cmd+0x174de60>
     5c8:	73255d57 	teqvc	r5, #5568	; 0x15c0
     5cc:	504d453a 	subpl	r4, sp, sl, lsr r5
     5d0:	46205954 			; <UNDEFINED> instruction: 0x46205954
     5d4:	54434e55 	strbpl	r4, [r3], #-3669	; 0xfffff1ab
     5d8:	0a4e4f49 	beq	1394304 <wmt_core_func_ctrl_cmd+0x1390ee4>
     5dc:	00000000 	andeq	r0, r0, r0
     5e0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     5e4:	5b5d432d 	blpl	17512a0 <wmt_core_func_ctrl_cmd+0x174de80>
     5e8:	73255d44 	teqvc	r5, #68, 26	; 0x1100
     5ec:	7473203a 	ldrbtvc	r2, [r3], #-58	; 0xffffffc6
     5f0:	0a747261 	beq	1d1cf7c <wmt_core_func_ctrl_cmd+0x1d19b5c>
     5f4:	00000000 	andeq	r0, r0, r0
     5f8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     5fc:	5b5d432d 	blpl	17512b8 <wmt_core_func_ctrl_cmd+0x174de98>
     600:	73255d57 	teqvc	r5, #5568	; 0x15c0
     604:	744d673a 	strbvc	r6, [sp], #-1850	; 0xfffff8c6
     608:	746d576b 	strbtvc	r5, [sp], #-1899	; 0xfffff895
     60c:	2e787443 	cdpcs	4, 7, cr7, cr8, cr3, {2}
     610:	63695f70 	cmnvs	r9, #112, 30	; 0x1c0
     614:	73706f5f 	cmnvc	r0, #380	; 0x17c
     618:	20736920 	rsbscs	r6, r3, r0, lsr #18
     61c:	4c4c554e 	cfstr64mi	mvdx5, [ip], {78}	; 0x4e
     620:	0000000a 	andeq	r0, r0, sl
     624:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     628:	5b5d432d 	blpl	17512e4 <wmt_core_func_ctrl_cmd+0x174dec4>
     62c:	73255d45 	teqvc	r5, #4416	; 0x1140
     630:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     634:	744d673a 	strbvc	r6, [sp], #-1850	; 0xfffff8c6
     638:	746d576b 	strbtvc	r5, [sp], #-1899	; 0xfffff895
     63c:	2e787443 	cdpcs	4, 7, cr7, cr8, cr3, {2}
     640:	63695f70 	cmnvs	r9, #112, 30	; 0x1c0
     644:	73706f5f 	cmnvc	r0, #380	; 0x17c
     648:	77733e2d 	ldrbvc	r3, [r3, -sp, lsr #28]!
     64c:	696e695f 	stmdbvs	lr!, {r0, r1, r2, r3, r4, r6, r8, fp, sp, lr}^
     650:	73692074 	cmnvc	r9, #116	; 0x74
     654:	4c554e20 	mrrcmi	14, 2, r4, r5, cr0
     658:	00000a4c 	andeq	r0, r0, ip, asr #20
     65c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     660:	5b5d432d 	blpl	175131c <wmt_core_func_ctrl_cmd+0x174defc>
     664:	73255d57 	teqvc	r5, #5568	; 0x15c0
     668:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     66c:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     670:	44532066 	ldrbmi	r2, [r3], #-102	; 0xffffff9a
     674:	465f4f49 	ldrbmi	r4, [pc], -r9, asr #30
     678:	5f434e55 	svcpl	0x00434e55
     67c:	20505453 	subscs	r5, r0, r3, asr r4
     680:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
     684:	64252820 	strtvs	r2, [r5], #-2080	; 0xfffff7e0
     688:	00000a29 	andeq	r0, r0, r9, lsr #20
     68c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     690:	5b5d432d 	blpl	175134c <wmt_core_func_ctrl_cmd+0x174df2c>
     694:	73255d49 	teqvc	r5, #4672	; 0x1240
     698:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     69c:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     6a0:	44532066 	ldrbmi	r2, [r3], #-102	; 0xffffff9a
     6a4:	465f4f49 	ldrbmi	r4, [pc], -r9, asr #30
     6a8:	5f434e55 	svcpl	0x00434e55
     6ac:	20505453 	subscs	r5, r0, r3, asr r4
     6b0:	0a206b6f 	beq	81b474 <wmt_core_func_ctrl_cmd+0x818054>
     6b4:	00000000 	andeq	r0, r0, r0
     6b8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     6bc:	5b5d432d 	blpl	1751378 <wmt_core_func_ctrl_cmd+0x174df58>
     6c0:	73255d57 	teqvc	r5, #5568	; 0x15c0
     6c4:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     6c8:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     6cc:	44532066 	ldrbmi	r2, [r3], #-102	; 0xffffff9a
     6d0:	20324f49 	eorscs	r4, r2, r9, asr #30
     6d4:	66205748 	strtvs	r5, [r0], -r8, asr #14
     6d8:	206c6961 	rsbcs	r6, ip, r1, ror #18
     6dc:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     6e0:	0000000a 	andeq	r0, r0, sl
     6e4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     6e8:	5b5d432d 	blpl	17513a4 <wmt_core_func_ctrl_cmd+0x174df84>
     6ec:	73255d49 	teqvc	r5, #4672	; 0x1240
     6f0:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     6f4:	666f206e 	strbtvs	r2, [pc], -lr, rrx
     6f8:	44532066 	ldrbmi	r2, [r3], #-102	; 0xffffff9a
     6fc:	20324f49 	eorscs	r4, r2, r9, asr #30
     700:	6f205748 	svcvs	0x00205748
     704:	000a206b 	andeq	r2, sl, fp, rrx
     708:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     70c:	5b5d432d 	blpl	17513c8 <wmt_core_func_ctrl_cmd+0x174dfa8>
     710:	73255d57 	teqvc	r5, #5568	; 0x15c0
     714:	646e653a 	strbtvs	r6, [lr], #-1338	; 0xfffffac6
     718:	74697720 	strbtvc	r7, [r9], #-1824	; 0xfffff8e0
     71c:	61662068 	cmnvs	r6, r8, rrx
     720:	253a6c69 	ldrcs	r6, [sl, #-3177]!	; 0xfffff397
     724:	00000a64 	andeq	r0, r0, r4, ror #20
     728:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     72c:	5b5d432d 	blpl	17513e8 <wmt_core_func_ctrl_cmd+0x174dfc8>
     730:	73255d57 	teqvc	r5, #5568	; 0x15c0
     734:	544d573a 	strbpl	r5, [sp], #-1850	; 0xfffff8c6
     738:	726c6120 	rsbvc	r6, ip, #32, 2
     73c:	79646165 	stmdbvc	r4!, {r0, r2, r5, r6, r8, sp, lr}^
     740:	66666f20 	strbtvs	r6, [r6], -r0, lsr #30
     744:	4d57202c 	ldclmi	0, cr2, [r7, #-176]	; 0xffffff50
     748:	52442054 	subpl	r2, r4, #84	; 0x54
     74c:	54535f56 	ldrbpl	r5, [r3], #-3926	; 0xfffff0aa
     750:	305b5f53 	subscc	r5, fp, r3, asr pc
     754:	5d782578 	cfldr64pl	mvdx2, [r8, #-480]!	; 0xfffffe20
     758:	0000000a 	andeq	r0, r0, sl
     75c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     760:	5b5d432d 	blpl	175141c <wmt_core_func_ctrl_cmd+0x174dffc>
     764:	73255d57 	teqvc	r5, #5568	; 0x15c0
     768:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
     76c:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
     770:	74735f65 	ldrbtvc	r5, [r3], #-3941	; 0xfffff09b
     774:	65645f70 	strbvs	r5, [r4, #-3952]!	; 0xfffff090
     778:	74696e69 	strbtvc	r6, [r9], #-3689	; 0xfffff197
     77c:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
     780:	2528206c 	strcs	r2, [r8, #-108]!	; 0xffffff94
     784:	000a2964 	andeq	r2, sl, r4, ror #18
     788:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     78c:	5b5d432d 	blpl	1751448 <wmt_core_func_ctrl_cmd+0x174e028>
     790:	73255d57 	teqvc	r5, #5568	; 0x15c0
     794:	5f57483a 	svcpl	0x0057483a
     798:	5f525750 	svcpl	0x00525750
     79c:	2046464f 	subcs	r4, r6, pc, asr #12
     7a0:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
     7a4:	64252820 	strtvs	r2, [r5], #-2080	; 0xfffff7e0
     7a8:	00000a29 	andeq	r0, r0, r9, lsr #20
     7ac:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     7b0:	5b5d432d 	blpl	175146c <wmt_core_func_ctrl_cmd+0x174e04c>
     7b4:	73255d57 	teqvc	r5, #5568	; 0x15c0
     7b8:	5f57483a 	svcpl	0x0057483a
     7bc:	5f525750 	svcpl	0x00525750
     7c0:	2046464f 	subcs	r4, r6, pc, asr #12
     7c4:	000a6b6f 	andeq	r6, sl, pc, ror #22
     7c8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     7cc:	5b5d432d 	blpl	1751488 <wmt_core_func_ctrl_cmd+0x174e068>
     7d0:	73255d45 	teqvc	r5, #4416	; 0x1140
     7d4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     7d8:	6e62613a 	mcrvs	1, 3, r6, cr2, cr10, {1}
     7dc:	616d726f 	cmnvs	sp, pc, ror #4
     7e0:	7546206c 	strbvc	r2, [r6, #-108]	; 0xffffff94
     7e4:	6425286e 	strtvs	r2, [r5], #-2158	; 0xfffff792
     7e8:	00000a29 	andeq	r0, r0, r9, lsr #20
     7ec:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     7f0:	5b5d432d 	blpl	17514ac <wmt_core_func_ctrl_cmd+0x174e08c>
     7f4:	73255d45 	teqvc	r5, #4416	; 0x1140
     7f8:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     7fc:	6e75463a 	mrcvs	6, 3, r4, cr5, cr10, {1}
     800:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     804:	56524420 	ldrbpl	r4, [r2], -r0, lsr #8
     808:	5354535f 	cmppl	r4, #2080374785	; 0x7c000001
     80c:	78305b5f 	ldmdavc	r0!, {r0, r1, r2, r3, r4, r6, r8, r9, fp, ip, lr}
     810:	205d7825 	subscs	r7, sp, r5, lsr #16
     814:	6f6e6261 	svcvs	0x006e6261
     818:	6c616d72 	stclvs	13, cr6, [r1], #-456	; 0xfffffe38
     81c:	0000000a 	andeq	r0, r0, sl
     820:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     824:	5b5d432d 	blpl	17514e0 <wmt_core_func_ctrl_cmd+0x174e0c0>
     828:	73255d57 	teqvc	r5, #5568	; 0x15c0
     82c:	6e75463a 	mrcvs	6, 3, r4, cr5, cr10, {1}
     830:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     834:	56524420 	ldrbpl	r4, [r2], -r0, lsr #8
     838:	5354535f 	cmppl	r4, #2080374785	; 0x7c000001
     83c:	78305b5f 	ldmdavc	r0!, {r0, r1, r2, r3, r4, r6, r8, r9, fp, ip, lr}
     840:	205d7825 	subscs	r7, sp, r5, lsr #16
     844:	65726c61 	ldrbvs	r6, [r2, #-3169]!	; 0xfffff39f
     848:	20796461 	rsbscs	r6, r9, r1, ror #8
     84c:	2d6e6f6e 	stclcs	15, cr6, [lr, #-440]!	; 0xfffffe48
     850:	5f4e5546 	svcpl	0x004e5546
     854:	000a4e4f 	andeq	r4, sl, pc, asr #28
     858:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     85c:	5b5d432d 	blpl	1751518 <wmt_core_func_ctrl_cmd+0x174e0f8>
     860:	73255d45 	teqvc	r5, #4416	; 0x1140
     864:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     868:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     86c:	6e6f206e 	cdpvs	0, 6, cr2, cr15, cr14, {3}
     870:	4f4c5320 	svcmi	0x004c5320
     874:	44535f54 	ldrbmi	r5, [r3], #-3924	; 0xfffff0ac
     878:	20314f49 	eorscs	r4, r1, r9, asr #30
     87c:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
     880:	64252820 	strtvs	r2, [r5], #-2080	; 0xfffff7e0
     884:	00000a29 	andeq	r0, r0, r9, lsr #20
     888:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     88c:	5b5d432d 	blpl	1751548 <wmt_core_func_ctrl_cmd+0x174e128>
     890:	73255d57 	teqvc	r5, #5568	; 0x15c0
     894:	73706f3a 	cmnvc	r0, #58, 30	; 0xe8
     898:	726f6620 	rsbvc	r6, pc, #32, 12	; 0x2000000
     89c:	70797420 	rsbsvc	r7, r9, r0, lsr #8
     8a0:	64252865 	strtvs	r2, [r5], #-2149	; 0xfffff79b
     8a4:	6f6e2029 	svcvs	0x006e2029
     8a8:	6f662074 	svcvs	0x00662074
     8ac:	0a646e75 	beq	191c288 <wmt_core_func_ctrl_cmd+0x1918e68>
     8b0:	00000000 	andeq	r0, r0, r0
     8b4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     8b8:	5b5d432d 	blpl	1751574 <wmt_core_func_ctrl_cmd+0x174e154>
     8bc:	73255d45 	teqvc	r5, #4416	; 0x1140
     8c0:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     8c4:	7079743a 	rsbsvc	r7, r9, sl, lsr r4
     8c8:	78302865 	ldmdavc	r0!, {r0, r2, r5, r6, fp, sp}
     8cc:	20297825 	eorcs	r7, r9, r5, lsr #16
     8d0:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
     8d4:	25286465 	strcs	r6, [r8, #-1125]!	; 0xfffffb9b
     8d8:	000a2964 	andeq	r2, sl, r4, ror #18
     8dc:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     8e0:	5b5d432d 	blpl	175159c <wmt_core_func_ctrl_cmd+0x174e17c>
     8e4:	73255d49 	teqvc	r5, #4672	; 0x1240
     8e8:	6e75463a 	mrcvs	6, 3, r4, cr5, cr10, {1}
     8ec:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     8f0:	4f505b20 	svcmi	0x00505b20
     8f4:	5f524557 	svcpl	0x00524557
     8f8:	5d46464f 	stclpl	6, cr4, [r6, #-316]	; 0xfffffec4
     8fc:	646e6120 	strbtvs	r6, [lr], #-288	; 0xfffffee0
     900:	776f7020 	strbvc	r7, [pc, -r0, lsr #32]!
     904:	64207265 	strtvs	r7, [r0], #-613	; 0xfffffd9b
     908:	206e776f 	rsbcs	r7, lr, pc, ror #14
     90c:	70696863 	rsbvc	r6, r9, r3, ror #16
     910:	0000000a 	andeq	r0, r0, sl
     914:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     918:	5b5d432d 	blpl	17515d4 <wmt_core_func_ctrl_cmd+0x174e1b4>
     91c:	73255d45 	teqvc	r5, #4416	; 0x1140
     920:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     924:	7277703a 	rsbsvc	r7, r7, #58	; 0x3a
     928:	66666f5f 	uqsaxvs	r6, r6, pc	; <UNPREDICTABLE>
     92c:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
     930:	6425286c 	strtvs	r2, [r5], #-2156	; 0xfffff794
     934:	68772029 	ldmdavs	r7!, {r0, r3, r5, sp}^
     938:	74206e65 	strtvc	r6, [r0], #-3685	; 0xfffff19b
     93c:	206e7275 	rsbcs	r7, lr, r5, ror r2
     940:	2066666f 	rsbcs	r6, r6, pc, ror #12
     944:	636e7566 	cmnvs	lr, #427819008	; 0x19800000
     948:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     94c:	0000000a 	andeq	r0, r0, sl
     950:	46204641 	strtmi	r4, [r0], -r1, asr #12
     954:	20434e55 	subcs	r4, r3, r5, asr lr
     958:	0046464f 	subeq	r4, r6, pc, asr #12
     95c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     960:	5b5d432d 	blpl	175161c <wmt_core_func_ctrl_cmd+0x174e1fc>
     964:	73255d44 	teqvc	r5, #68, 26	; 0x1100
     968:	65706f3a 	ldrbvs	r6, [r0, #-3898]!	; 0xfffff0c6
     96c:	69746172 	ldmdbvs	r4!, {r1, r4, r5, r6, r8, sp, lr}^
     970:	25206e6f 	strcs	r6, [r0, #-3695]!	; 0xfffff191
     974:	74732073 	ldrbtvc	r2, [r3], #-115	; 0xffffff8d
     978:	20747261 	rsbscs	r7, r4, r1, ror #4
     97c:	0000000a 	andeq	r0, r0, sl
     980:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     984:	5b5d432d 	blpl	1751640 <wmt_core_func_ctrl_cmd+0x174e220>
     988:	73255d45 	teqvc	r5, #4416	; 0x1140
     98c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     990:	6972773a 	ldmdbvs	r2!, {r1, r3, r4, r5, r8, r9, sl, ip, sp, lr}^
     994:	28206574 	stmdacs	r0!, {r2, r4, r5, r6, r8, sl, sp, lr}
     998:	20297325 	eorcs	r7, r9, r5, lsr #6
     99c:	74655269 	strbtvc	r5, [r5], #-617	; 0xfffffd97
     9a0:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     9a4:	646d6320 	strbtvs	r6, [sp], #-800	; 0xfffffce0
     9a8:	6e656c20 	cdpvs	12, 6, cr6, cr5, cr0, {1}
     9ac:	72726520 	rsbsvc	r6, r2, #32, 10	; 0x8000000
     9b0:	2c642528 	cfstr64cs	mvdx2, [r4], #-160	; 0xffffff60
     9b4:	29642520 	stmdbcs	r4!, {r5, r8, sl, sp}^
     9b8:	00000a20 	andeq	r0, r0, r0, lsr #20
     9bc:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     9c0:	5b5d432d 	blpl	175167c <wmt_core_func_ctrl_cmd+0x174e25c>
     9c4:	73255d45 	teqvc	r5, #4416	; 0x1140
     9c8:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     9cc:	6165723a 	cmnvs	r5, sl, lsr r2
     9d0:	25282064 	strcs	r2, [r8, #-100]!	; 0xffffff9c
     9d4:	69202973 	stmdbvs	r0!, {r0, r1, r4, r5, r6, r8, fp, sp}
     9d8:	28746552 	ldmdacs	r4!, {r1, r4, r6, r8, sl, sp, lr}^
     9dc:	20296425 	eorcs	r6, r9, r5, lsr #8
     9e0:	20747665 	rsbscs	r7, r4, r5, ror #12
     9e4:	206e656c 	rsbcs	r6, lr, ip, ror #10
     9e8:	28727265 	ldmdacs	r2!, {r0, r2, r5, r6, r9, ip, sp, lr}^
     9ec:	253a7872 	ldrcs	r7, [sl, #-2162]!	; 0xfffff78e
     9f0:	65202c64 	strvs	r2, [r0, #-3172]!	; 0xfffff39c
     9f4:	253a7078 	ldrcs	r7, [sl, #-120]!	; 0xffffff88
     9f8:	0a202964 	beq	80af90 <wmt_core_func_ctrl_cmd+0x807b70>
     9fc:	00000000 	andeq	r0, r0, r0
     a00:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     a04:	5b5d432d 	blpl	17516c0 <wmt_core_func_ctrl_cmd+0x174e2a0>
     a08:	73255d45 	teqvc	r5, #4416	; 0x1140
     a0c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     a10:	6d6f633a 	stclvs	3, cr6, [pc, #-232]!	; 930 <.rodata.str1.4+0x930>
     a14:	65726170 	ldrbvs	r6, [r2, #-368]!	; 0xfffffe90
     a18:	73252820 	teqvc	r5, #32, 16	; 0x200000
     a1c:	65722029 	ldrbvs	r2, [r2, #-41]!	; 0xffffffd7
     a20:	746c7573 	strbtvc	r7, [ip], #-1395	; 0xfffffa8d
     a24:	72726520 	rsbsvc	r6, r2, #32, 10	; 0x8000000
     a28:	0a20726f 	beq	81d3ec <wmt_core_func_ctrl_cmd+0x819fcc>
     a2c:	00000000 	andeq	r0, r0, r0
     a30:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     a34:	5b5d432d 	blpl	17516f0 <wmt_core_func_ctrl_cmd+0x174e2d0>
     a38:	73255d45 	teqvc	r5, #4416	; 0x1140
     a3c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     a40:	2878723a 	ldmdacs	r8!, {r1, r3, r4, r5, r9, ip, sp, lr}^
     a44:	3a296425 	bcc	a59ae0 <wmt_core_func_ctrl_cmd+0xa566c0>
     a48:	3230255b 	eorscc	r2, r0, #381681664	; 0x16c00000
     a4c:	30252c58 	eorcc	r2, r5, r8, asr ip
     a50:	252c5832 	strcs	r5, [ip, #-2098]!	; 0xfffff7ce
     a54:	2c583230 	lfmcs	f3, 2, [r8], {48}	; 0x30
     a58:	58323025 	ldmdapl	r2!, {r0, r2, r5, ip, sp}
     a5c:	3230252c 	eorscc	r2, r0, #44, 10	; 0xb000000
     a60:	65205d58 	strvs	r5, [r0, #-3416]!	; 0xfffff2a8
     a64:	25287078 	strcs	r7, [r8, #-120]!	; 0xffffff88
     a68:	5b3a2964 	blpl	e8b000 <wmt_core_func_ctrl_cmd+0xe87be0>
     a6c:	58323025 	ldmdapl	r2!, {r0, r2, r5, ip, sp}
     a70:	3230252c 	eorscc	r2, r0, #44, 10	; 0xb000000
     a74:	30252c58 	eorcc	r2, r5, r8, asr ip
     a78:	252c5832 	strcs	r5, [ip, #-2098]!	; 0xfffff7ce
     a7c:	2c583230 	lfmcs	f3, 2, [r8], {48}	; 0x30
     a80:	58323025 	ldmdapl	r2!, {r0, r2, r5, ip, sp}
     a84:	00000a5d 	andeq	r0, r0, sp, asr sl
     a88:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     a8c:	5b5d432d 	blpl	1751748 <wmt_core_func_ctrl_cmd+0x174e328>
     a90:	73255d44 	teqvc	r5, #68, 26	; 0x1100
     a94:	696e693a 	stmdbvs	lr!, {r1, r3, r4, r5, r8, fp, sp, lr}^
     a98:	63735f74 	cmnvs	r3, #116, 30	; 0x1d0
     a9c:	74706972 	ldrbtvc	r6, [r0], #-2418	; 0xfffff68e
     aa0:	65706f20 	ldrbvs	r6, [r0, #-3872]!	; 0xfffff0e0
     aa4:	69746172 	ldmdbvs	r4!, {r1, r4, r5, r6, r8, sp, lr}^
     aa8:	25206e6f 	strcs	r6, [r0, #-3695]!	; 0xfffff191
     aac:	6b6f2073 	blvs	1bc8c80 <wmt_core_func_ctrl_cmd+0x1bc5860>
     ab0:	00000a20 	andeq	r0, r0, r0, lsr #20
     ab4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     ab8:	5b5d432d 	blpl	1751774 <wmt_core_func_ctrl_cmd+0x174e354>
     abc:	73255d45 	teqvc	r5, #4416	; 0x1140
     ac0:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     ac4:	2078543a 	rsbscs	r5, r8, sl, lsr r4
     ac8:	5f474552 	svcpl	0x00474552
     acc:	20444d43 	subcs	r4, r4, r3, asr #26
     ad0:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
     ad4:	64252821 	strtvs	r2, [r5], #-2081	; 0xfffff7df
     ad8:	656c2029 	strbvs	r2, [ip, #-41]!	; 0xffffffd7
     adc:	2528206e 	strcs	r2, [r8, #-110]!	; 0xffffff92
     ae0:	25202c64 	strcs	r2, [r0, #-3172]!	; 0xfffff39c
     ae4:	0a202964 	beq	80b07c <wmt_core_func_ctrl_cmd+0x807c5c>
     ae8:	00000000 	andeq	r0, r0, r0
     aec:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     af0:	5b5d432d 	blpl	17517ac <wmt_core_func_ctrl_cmd+0x174e38c>
     af4:	73255d45 	teqvc	r5, #4416	; 0x1140
     af8:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     afc:	2078523a 	rsbscs	r5, r8, sl, lsr r2
     b00:	5f474552 	svcpl	0x00474552
     b04:	20545645 	subscs	r5, r4, r5, asr #12
     b08:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
     b0c:	64252821 	strtvs	r2, [r5], #-2081	; 0xfffff7df
     b10:	656c2029 	strbvs	r2, [ip, #-41]!	; 0xffffffd7
     b14:	6425286e 	strtvs	r2, [r5], #-2158	; 0xfffff792
     b18:	6425202c 	strtvs	r2, [r5], #-44	; 0xffffffd4
     b1c:	00000a29 	andeq	r0, r0, r9, lsr #20
     b20:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     b24:	5b5d432d 	blpl	17517e0 <wmt_core_func_ctrl_cmd+0x174e3c0>
     b28:	73255d45 	teqvc	r5, #4416	; 0x1140
     b2c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     b30:	6568433a 	strbvs	r4, [r8, #-826]!	; 0xfffffcc6
     b34:	72206b63 	eorvc	r6, r0, #101376	; 0x18c00
     b38:	20646165 	rsbcs	r6, r4, r5, ror #2
     b3c:	72646461 	rsbvc	r6, r4, #1627389952	; 0x61000000
     b40:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
     b44:	3028206c 	eorcc	r2, r8, ip, rrx
     b48:	38302578 	ldmdacc	r0!, {r3, r4, r5, r6, r8, sl, sp}
     b4c:	30202c78 	eorcc	r2, r0, r8, ror ip
     b50:	38302578 	ldmdacc	r0!, {r3, r4, r5, r6, r8, sl, sp}
     b54:	000a2978 	andeq	r2, sl, r8, ror r9
     b58:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     b5c:	5b5d432d 	blpl	1751818 <wmt_core_func_ctrl_cmd+0x174e3f8>
     b60:	73255d44 	teqvc	r5, #68, 26	; 0x1100
     b64:	6568433a 	strbvs	r4, [r8, #-826]!	; 0xfffffcc6
     b68:	72206b63 	eorvc	r6, r0, #101376	; 0x18c00
     b6c:	20646165 	rsbcs	r6, r4, r5, ror #2
     b70:	72646461 	rsbvc	r6, r4, #1627389952	; 0x61000000
     b74:	25783028 	ldrbcs	r3, [r8, #-40]!	; 0xffffffd8
     b78:	29783830 	ldmdbcs	r8!, {r4, r5, fp, ip, sp}^
     b7c:	0a6b6f20 	beq	1adc804 <wmt_core_func_ctrl_cmd+0x1ad93e4>
     b80:	00000000 	andeq	r0, r0, r0
     b84:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     b88:	5b5d432d 	blpl	1751844 <wmt_core_func_ctrl_cmd+0x174e424>
     b8c:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
     b90:	6174733a 	cmnvs	r4, sl, lsr r3
     b94:	000a7472 	andeq	r7, sl, r2, ror r4
     b98:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     b9c:	5b5d432d 	blpl	1751858 <wmt_core_func_ctrl_cmd+0x174e438>
     ba0:	73255d45 	teqvc	r5, #4416	; 0x1140
     ba4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     ba8:	206f6e3a 	rsbcs	r6, pc, sl, lsr lr	; <UNPREDICTABLE>
     bac:	20666968 	rsbcs	r6, r6, r8, ror #18
     bb0:	6f666e69 	svcvs	0x00666e69
     bb4:	00000a21 	andeq	r0, r0, r1, lsr #20
     bb8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     bbc:	5b5d432d 	blpl	1751878 <wmt_core_func_ctrl_cmd+0x174e458>
     bc0:	73255d45 	teqvc	r5, #4416	; 0x1140
     bc4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     bc8:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     bcc:	6e6f206e 	cdpvs	0, 6, cr2, cr15, cr14, {3}
     bd0:	4f4c5320 	svcmi	0x004c5320
     bd4:	44535f54 	ldrbmi	r5, [r3], #-3924	; 0xfffff0ac
     bd8:	20324f49 	eorscs	r4, r2, r9, asr #30
     bdc:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
     be0:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     be4:	0000000a 	andeq	r0, r0, sl
     be8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     bec:	5b5d432d 	blpl	17518a8 <wmt_core_func_ctrl_cmd+0x174e488>
     bf0:	73255d45 	teqvc	r5, #4416	; 0x1140
     bf4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     bf8:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     bfc:	6e6f206e 	cdpvs	0, 6, cr2, cr15, cr14, {3}
     c00:	49445320 	stmdbmi	r4, {r5, r8, r9, ip, lr}^
     c04:	55465f4f 	strbpl	r5, [r6, #-3919]	; 0xfffff0b1
     c08:	535f434e 	cmppl	pc, #939524097	; 0x38000001
     c0c:	66205054 			; <UNDEFINED> instruction: 0x66205054
     c10:	20636e75 	rsbcs	r6, r3, r5, ror lr
     c14:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
     c18:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     c1c:	0000000a 	andeq	r0, r0, sl
     c20:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     c24:	5b5d432d 	blpl	17518e0 <wmt_core_func_ctrl_cmd+0x174e4c0>
     c28:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
     c2c:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
     c30:	6e6f206e 	cdpvs	0, 6, cr2, cr15, cr14, {3}
     c34:	49445320 	stmdbmi	r4, {r5, r8, r9, ip, lr}^
     c38:	55465f4f 	strbpl	r5, [r6, #-3919]	; 0xfffff0b1
     c3c:	535f434e 	cmppl	pc, #939524097	; 0x38000001
     c40:	6f205054 	svcvs	0x00205054
     c44:	00000a6b 	andeq	r0, r0, fp, ror #20
     c48:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     c4c:	5b5d432d 	blpl	1751908 <wmt_core_func_ctrl_cmd+0x174e4e8>
     c50:	73255d45 	teqvc	r5, #4416	; 0x1140
     c54:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     c58:	65706f3a 	ldrbvs	r6, [r0, #-3898]!	; 0xfffff0c6
     c5c:	7473206e 	ldrbtvc	r2, [r3], #-110	; 0xffffff92
     c60:	61662070 	smcvs	25088	; 0x6200
     c64:	25286c69 	strcs	r6, [r8, #-3177]!	; 0xfffff397
     c68:	000a2964 	andeq	r2, sl, r4, ror #18
     c6c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     c70:	5b5d432d 	blpl	175192c <wmt_core_func_ctrl_cmd+0x174e50c>
     c74:	73255d49 	teqvc	r5, #4672	; 0x1240
     c78:	65706f3a 	ldrbvs	r6, [r0, #-3898]!	; 0xfffff0c6
     c7c:	7473206e 	ldrbtvc	r2, [r3], #-110	; 0xffffff92
     c80:	6b6f2070 	blvs	1bc8e48 <wmt_core_func_ctrl_cmd+0x1bc5a28>
     c84:	7865202c 	stmdavc	r5!, {r2, r3, r5, sp}^
     c88:	74636570 	strbtvc	r6, [r3], #-1392	; 0xfffffa90
     c8c:	736f6820 	cmnvc	pc, #32, 16	; 0x200000
     c90:	61622074 	smcvs	8708	; 0x2204
     c94:	61726475 	cmnvs	r2, r5, ror r4
     c98:	74206574 	strtvc	r6, [r0], #-1396	; 0xfffffa8c
     c9c:	6562206f 	strbvs	r2, [r2, #-111]!	; 0xffffff91
     ca0:	64252820 	strtvs	r2, [r5], #-2080	; 0xfffff7e0
     ca4:	000a2029 	andeq	r2, sl, r9, lsr #32
     ca8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     cac:	5b5d432d 	blpl	1751968 <wmt_core_func_ctrl_cmd+0x174e548>
     cb0:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
     cb4:	65706f3a 	ldrbvs	r6, [r0, #-3898]!	; 0xfffff0c6
     cb8:	7473206e 	ldrbtvc	r2, [r3], #-110	; 0xffffff92
     cbc:	6b6f2070 	blvs	1bc8e84 <wmt_core_func_ctrl_cmd+0x1bc5a64>
     cc0:	0000000a 	andeq	r0, r0, sl
     cc4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     cc8:	5b5d432d 	blpl	1751984 <wmt_core_func_ctrl_cmd+0x174e564>
     ccc:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
     cd0:	7074733a 	rsbsvc	r7, r4, sl, lsr r3
     cd4:	6e6f6320 	cdpvs	3, 6, cr6, cr15, cr0, {1}
     cd8:	6e652066 	cdpvs	0, 6, cr2, cr5, cr6, {3}
     cdc:	202c3028 	eorcs	r3, ip, r8, lsr #32
     ce0:	0a296425 	beq	a59d7c <wmt_core_func_ctrl_cmd+0xa5695c>
     ce4:	00000000 	andeq	r0, r0, r0
     ce8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     cec:	5b5d432d 	blpl	17519a8 <wmt_core_func_ctrl_cmd+0x174e588>
     cf0:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
     cf4:	7074733a 	rsbsvc	r7, r4, sl, lsr r3
     cf8:	6e6f6320 	cdpvs	3, 6, cr6, cr15, cr0, {1}
     cfc:	64722066 	ldrbtvs	r2, [r2], #-102	; 0xffffff9a
     d00:	2c302879 	ldccs	8, cr2, [r0], #-484	; 0xfffffe1c
     d04:	29642520 	stmdbcs	r4!, {r5, r8, sl, sp}^
     d08:	0000000a 	andeq	r0, r0, sl
     d0c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     d10:	5b5d432d 	blpl	17519cc <wmt_core_func_ctrl_cmd+0x174e5ac>
     d14:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
     d18:	7074733a 	rsbsvc	r7, r4, sl, lsr r3
     d1c:	6e6f6320 	cdpvs	3, 6, cr6, cr15, cr0, {1}
     d20:	6f6d2066 	svcvs	0x006d2066
     d24:	6d286564 	cfstr32vs	mvfx6, [r8, #-400]!	; 0xfffffe70
     d28:	2c646e61 	stclcs	14, cr6, [r4], #-388	; 0xfffffe7c
     d2c:	29642520 	stmdbcs	r4!, {r5, r8, sl, sp}^
     d30:	0000000a 	andeq	r0, r0, sl
     d34:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     d38:	5b5d432d 	blpl	17519f4 <wmt_core_func_ctrl_cmd+0x174e5d4>
     d3c:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
     d40:	7074733a 	rsbsvc	r7, r4, sl, lsr r3
     d44:	6e6f6320 	cdpvs	3, 6, cr6, cr15, cr0, {1}
     d48:	6f6d2066 	svcvs	0x006d2066
     d4c:	73286564 	teqvc	r8, #100, 10	; 0x19000000
     d50:	2c6f6964 	stclcs	9, cr6, [pc], #-400	; bc8 <.rodata.str1.4+0xbc8>
     d54:	29642520 	stmdbcs	r4!, {r5, r8, sl, sp}^
     d58:	0000000a 	andeq	r0, r0, sl
     d5c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     d60:	5b5d432d 	blpl	1751a1c <wmt_core_func_ctrl_cmd+0x174e5fc>
     d64:	73255d45 	teqvc	r5, #4416	; 0x1140
     d68:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     d6c:	7074733a 	rsbsvc	r7, r4, sl, lsr r3
     d70:	6e6f6320 	cdpvs	3, 6, cr6, cr15, cr0, {1}
     d74:	6e652066 	cdpvs	0, 6, cr2, cr5, cr6, {3}
     d78:	20293128 	eorcs	r3, r9, r8, lsr #2
     d7c:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
     d80:	0a64253a 	beq	190a270 <wmt_core_func_ctrl_cmd+0x1906e50>
     d84:	00000000 	andeq	r0, r0, r0
     d88:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     d8c:	5b5d432d 	blpl	1751a48 <wmt_core_func_ctrl_cmd+0x174e628>
     d90:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
     d94:	7074733a 	rsbsvc	r7, r4, sl, lsr r3
     d98:	6e6f6320 	cdpvs	3, 6, cr6, cr15, cr0, {1}
     d9c:	6e652066 	cdpvs	0, 6, cr2, cr5, cr6, {3}
     da0:	20293128 	eorcs	r3, r9, r8, lsr #2
     da4:	000a6b6f 	andeq	r6, sl, pc, ror #22
     da8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     dac:	5b5d432d 	blpl	1751a68 <wmt_core_func_ctrl_cmd+0x174e648>
     db0:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
     db4:	6665623a 			; <UNDEFINED> instruction: 0x6665623a
     db8:	2065726f 	rsbcs	r7, r5, pc, ror #4
     dbc:	64616572 	strbtvs	r6, [r1], #-1394	; 0xfffffa8e
     dc0:	63776820 	cmnvs	r7, #32, 16	; 0x200000
     dc4:	2065646f 	rsbcs	r6, r5, pc, ror #8
     dc8:	69686328 	stmdbvs	r8!, {r3, r5, r8, r9, sp, lr}^
     dcc:	64692070 	strbtvs	r2, [r9], #-112	; 0xffffff90
     dd0:	00000a29 	andeq	r0, r0, r9, lsr #20
     dd4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     dd8:	5b5d432d 	blpl	1751a94 <wmt_core_func_ctrl_cmd+0x174e674>
     ddc:	73255d45 	teqvc	r5, #4416	; 0x1140
     de0:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     de4:	7465673a 	strbtvc	r6, [r5], #-1850	; 0xfffff8c6
     de8:	63776820 	cmnvs	r7, #32, 16	; 0x200000
     dec:	2065646f 	rsbcs	r6, r5, pc, ror #8
     df0:	69686328 	stmdbvs	r8!, {r3, r5, r8, r9, sp, lr}^
     df4:	64692070 	strbtvs	r2, [r9], #-112	; 0xffffff90
     df8:	61662029 	cmnvs	r6, r9, lsr #32
     dfc:	28206c69 	stmdacs	r0!, {r0, r3, r5, r6, sl, fp, sp, lr}
     e00:	0a296425 	beq	a59e9c <wmt_core_func_ctrl_cmd+0xa56a7c>
     e04:	00000000 	andeq	r0, r0, r0
     e08:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     e0c:	5b5d432d 	blpl	1751ac8 <wmt_core_func_ctrl_cmd+0x174e6a8>
     e10:	73255d49 	teqvc	r5, #4672	; 0x1240
     e14:	7465673a 	strbtvc	r6, [r5], #-1850	; 0xfffff8c6
     e18:	63776820 	cmnvs	r7, #32, 16	; 0x200000
     e1c:	2065646f 	rsbcs	r6, r5, pc, ror #8
     e20:	69686328 	stmdbvs	r8!, {r3, r5, r8, r9, sp, lr}^
     e24:	64692070 	strbtvs	r2, [r9], #-112	; 0xffffff90
     e28:	30282029 	eorcc	r2, r8, r9, lsr #32
     e2c:	29782578 	ldmdbcs	r8!, {r3, r4, r5, r6, r8, sl, sp}^
     e30:	0000000a 	andeq	r0, r0, sl
     e34:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     e38:	5b5d432d 	blpl	1751af4 <wmt_core_func_ctrl_cmd+0x174e6d4>
     e3c:	73255d45 	teqvc	r5, #4416	; 0x1140
     e40:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     e44:	736e753a 	cmnvc	lr, #243269632	; 0xe800000
     e48:	6f707075 	svcvs	0x00707075
     e4c:	64657472 	strbtvs	r7, [r5], #-1138	; 0xfffffb8e
     e50:	69686320 	stmdbvs	r8!, {r5, r8, r9, sp, lr}^
     e54:	64692070 	strbtvs	r2, [r9], #-112	; 0xffffff90
     e58:	77682820 	strbvc	r2, [r8, -r0, lsr #16]!
     e5c:	646f635f 	strbtvs	r6, [pc], #-863	; e64 <.rodata.str1.4+0xe64>
     e60:	203a2965 	eorscs	r2, sl, r5, ror #18
     e64:	78257830 	stmdavc	r5!, {r4, r5, fp, ip, sp, lr}
     e68:	0000000a 	andeq	r0, r0, sl
     e6c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     e70:	5b5d432d 	blpl	1751b2c <wmt_core_func_ctrl_cmd+0x174e70c>
     e74:	73255d45 	teqvc	r5, #4416	; 0x1140
     e78:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     e7c:	6968633a 	stmdbvs	r8!, {r1, r3, r4, r5, r8, r9, sp, lr}^
     e80:	64692070 	strbtvs	r2, [r9], #-112	; 0xffffff90
     e84:	25783028 	ldrbcs	r3, [r8, #-40]!	; 0xffffffd8
     e88:	77202978 			; <UNDEFINED> instruction: 0x77202978
     e8c:	20687469 	rsbcs	r7, r8, r9, ror #8
     e90:	6c6c756e 	cfstr64vs	mvdx7, [ip], #-440	; 0xfffffe48
     e94:	65706f20 	ldrbvs	r6, [r0, #-3872]!	; 0xfffff0e0
     e98:	69746172 	ldmdbvs	r4!, {r1, r4, r5, r6, r8, sp, lr}^
     e9c:	66206e6f 	strtvs	r6, [r0], -pc, ror #28
     ea0:	69203a70 	stmdbvs	r0!, {r4, r5, r6, r9, fp, ip, sp}
     ea4:	2874696e 	ldmdacs	r4!, {r1, r2, r3, r5, r6, r8, fp, sp, lr}^
     ea8:	70257830 	eorvc	r7, r5, r0, lsr r8
     eac:	64202c29 	strtvs	r2, [r0], #-3113	; 0xfffff3d7
     eb0:	696e6965 	stmdbvs	lr!, {r0, r2, r5, r6, r8, fp, sp, lr}^
     eb4:	78302874 	ldmdavc	r0!, {r2, r4, r5, r6, fp, sp}
     eb8:	2c297025 	stccs	0, cr7, [r9], #-148	; 0xffffff6c
     ebc:	6e697020 	cdpvs	0, 6, cr7, cr9, cr0, {1}
     ec0:	7274635f 	rsbsvc	r6, r4, #2080374785	; 0x7c000001
     ec4:	7830286c 	ldmdavc	r0!, {r2, r3, r5, r6, fp, sp}
     ec8:	2c297025 	stccs	0, cr7, [r9], #-148	; 0xffffff6c
     ecc:	72657620 	rsbvc	r7, r5, #32, 12	; 0x2000000
     ed0:	6b68635f 	blvs	1a19c54 <wmt_core_func_ctrl_cmd+0x1a16834>
     ed4:	25783028 	ldrbcs	r3, [r8, #-40]!	; 0xffffffd8
     ed8:	000a2970 	andeq	r2, sl, r0, ror r9
     edc:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     ee0:	5b5d432d 	blpl	1751b9c <wmt_core_func_ctrl_cmd+0x174e77c>
     ee4:	73255d44 	teqvc	r5, #68, 26	; 0x1100
     ee8:	6968633a 	stmdbvs	r8!, {r1, r3, r4, r5, r8, r9, sp, lr}^
     eec:	64692070 	strbtvs	r2, [r9], #-112	; 0xffffff90
     ef0:	25783028 	ldrbcs	r3, [r8, #-40]!	; 0xffffffd8
     ef4:	66202978 			; <UNDEFINED> instruction: 0x66202978
     ef8:	69203a70 	stmdbvs	r0!, {r4, r5, r6, r9, fp, ip, sp}
     efc:	2874696e 	ldmdacs	r4!, {r1, r2, r3, r5, r6, r8, fp, sp, lr}^
     f00:	70257830 	eorvc	r7, r5, r0, lsr r8
     f04:	64202c29 	strtvs	r2, [r0], #-3113	; 0xfffff3d7
     f08:	696e6965 	stmdbvs	lr!, {r0, r2, r5, r6, r8, fp, sp, lr}^
     f0c:	78302874 	ldmdavc	r0!, {r2, r4, r5, r6, fp, sp}
     f10:	2c297025 	stccs	0, cr7, [r9], #-148	; 0xffffff6c
     f14:	6e697020 	cdpvs	0, 6, cr7, cr9, cr0, {1}
     f18:	7274635f 	rsbsvc	r6, r4, #2080374785	; 0x7c000001
     f1c:	7830286c 	ldmdavc	r0!, {r2, r3, r5, r6, fp, sp}
     f20:	2c297025 	stccs	0, cr7, [r9], #-148	; 0xffffff6c
     f24:	72657620 	rsbvc	r7, r5, #32, 12	; 0x2000000
     f28:	6b68635f 	blvs	1a19cac <wmt_core_func_ctrl_cmd+0x1a1688c>
     f2c:	25783028 	ldrbcs	r3, [r8, #-40]!	; 0xffffffd8
     f30:	000a2970 	andeq	r2, sl, r0, ror r9
     f34:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     f38:	5b5d432d 	blpl	1751bf4 <wmt_core_func_ctrl_cmd+0x174e7d4>
     f3c:	73255d45 	teqvc	r5, #4416	; 0x1140
     f40:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     f44:	6968633a 	stmdbvs	r8!, {r1, r3, r4, r5, r8, r9, sp, lr}^
     f48:	64692070 	strbtvs	r2, [r9], #-112	; 0xffffff90
     f4c:	25783028 	ldrbcs	r3, [r8, #-40]!	; 0xffffffd8
     f50:	76202978 			; <UNDEFINED> instruction: 0x76202978
     f54:	635f7265 	cmpvs	pc, #1342177286	; 0x50000006
     f58:	6b636568 	blvs	18da500 <wmt_core_func_ctrl_cmd+0x18d70e0>
     f5c:	72726520 	rsbsvc	r6, r2, #32, 10	; 0x8000000
     f60:	253a726f 	ldrcs	r7, [sl, #-623]!	; 0xfffffd91
     f64:	00000a64 	andeq	r0, r0, r4, ror #20
     f68:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     f6c:	5b5d432d 	blpl	1751c28 <wmt_core_func_ctrl_cmd+0x174e808>
     f70:	73255d49 	teqvc	r5, #4672	; 0x1240
     f74:	6968633a 	stmdbvs	r8!, {r1, r3, r4, r5, r8, r9, sp, lr}^
     f78:	64692070 	strbtvs	r2, [r9], #-112	; 0xffffff90
     f7c:	25783028 	ldrbcs	r3, [r8, #-40]!	; 0xffffffd8
     f80:	76202978 			; <UNDEFINED> instruction: 0x76202978
     f84:	635f7265 	cmpvs	pc, #1342177286	; 0x50000006
     f88:	6b636568 	blvs	18da530 <wmt_core_func_ctrl_cmd+0x18d7110>
     f8c:	0a6b6f20 	beq	1adcc14 <wmt_core_func_ctrl_cmd+0x1ad97f4>
     f90:	00000000 	andeq	r0, r0, r0
     f94:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     f98:	5b5d432d 	blpl	1751c54 <wmt_core_func_ctrl_cmd+0x174e834>
     f9c:	73255d45 	teqvc	r5, #4416	; 0x1140
     fa0:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
     fa4:	5f77683a 	svcpl	0x0077683a
     fa8:	63656863 	cmnvs	r5, #6488064	; 0x630000
     fac:	6166206b 	cmnvs	r6, fp, rrx
     fb0:	25286c69 	strcs	r6, [r8, #-3177]!	; 0xfffff397
     fb4:	000a2964 	andeq	r2, sl, r4, ror #18
     fb8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     fbc:	5b5d432d 	blpl	1751c78 <wmt_core_func_ctrl_cmd+0x174e858>
     fc0:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
     fc4:	5f77683a 	svcpl	0x0077683a
     fc8:	63656863 	cmnvs	r5, #6488064	; 0x630000
     fcc:	6b6f206b 	blvs	1bc9180 <wmt_core_func_ctrl_cmd+0x1bc5d60>
     fd0:	0000000a 	andeq	r0, r0, sl
     fd4:	4c4c554e 	cfstr64mi	mvdx5, [ip], {78}	; 0x4e
     fd8:	203d2120 	eorscs	r2, sp, r0, lsr #2
     fdc:	78746370 	ldmdavc	r4!, {r4, r5, r6, r8, r9, sp, lr}^
     fe0:	5f703e2d 	svcpl	0x00703e2d
     fe4:	6f5f6369 	svcvs	0x005f6369
     fe8:	3e2d7370 	mcrcc	3, 1, r7, cr13, cr0, {3}
     fec:	695f7773 	ldmdbvs	pc, {r0, r1, r4, r5, r6, r8, r9, sl, ip, sp, lr}^	; <UNPREDICTABLE>
     ff0:	0074696e 	rsbseq	r6, r4, lr, ror #18
     ff4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
     ff8:	5b5d432d 	blpl	1751cb4 <wmt_core_func_ctrl_cmd+0x174e894>
     ffc:	73255d45 	teqvc	r5, #4416	; 0x1140
    1000:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1004:	744d673a 	strbvc	r6, [sp], #-1850	; 0xfffff8c6
    1008:	746d576b 	strbtvc	r5, [sp], #-1899	; 0xfffff895
    100c:	2e787443 	cdpcs	4, 7, cr7, cr8, cr3, {2}
    1010:	63695f70 	cmnvs	r9, #112, 30	; 0x1c0
    1014:	73706f5f 	cmnvc	r0, #380	; 0x17c
    1018:	77733e2d 	ldrbvc	r3, [r3, -sp, lsr #28]!
    101c:	696e695f 	stmdbvs	lr!, {r0, r1, r2, r3, r4, r6, r8, fp, sp, lr}^
    1020:	61662074 	smcvs	25092	; 0x6204
    1024:	253a6c69 	ldrcs	r6, [sl, #-3177]!	; 0xfffff397
    1028:	00000a64 	andeq	r0, r0, r4, ror #20
    102c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1030:	5b5d432d 	blpl	1751cec <wmt_core_func_ctrl_cmd+0x174e8cc>
    1034:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
    1038:	695f703a 	ldmdbvs	pc, {r1, r3, r4, r5, ip, sp, lr}^	; <UNPREDICTABLE>
    103c:	706f5f63 	rsbvc	r5, pc, r3, ror #30
    1040:	733e2d73 	teqvc	lr, #7360	; 0x1cc0
    1044:	6e695f77 	mcrvs	15, 3, r5, cr9, cr7, {3}
    1048:	6f207469 	svcvs	0x00207469
    104c:	00000a6b 	andeq	r0, r0, fp, ror #20
    1050:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1054:	5b5d432d 	blpl	1751d10 <wmt_core_func_ctrl_cmd+0x174e8f0>
    1058:	73255d4c 	teqvc	r5, #76, 26	; 0x1300
    105c:	7074733a 	rsbsvc	r7, r4, sl, lsr r3
    1060:	6e6f6320 	cdpvs	3, 6, cr6, cr15, cr0, {1}
    1064:	64722066 	ldrbtvs	r2, [r2], #-102	; 0xffffff9a
    1068:	2c312879 	ldccs	8, cr2, [r1], #-484	; 0xfffffe1c
    106c:	29642520 	stmdbcs	r4!, {r5, r8, sl, sp}^
    1070:	0000000a 	andeq	r0, r0, sl
    1074:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1078:	5b5d432d 	blpl	1751d34 <wmt_core_func_ctrl_cmd+0x174e914>
    107c:	73255d45 	teqvc	r5, #4416	; 0x1140
    1080:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1084:	726c613a 	rsbvc	r6, ip, #-2147483634	; 0x8000000e
    1088:	79646165 	stmdbvc	r4!, {r0, r2, r5, r6, r8, sp, lr}^
    108c:	776f7020 	strbvc	r7, [pc, -r0, lsr #32]!
    1090:	64657265 	strbtvs	r7, [r5], #-613	; 0xfffffd9b
    1094:	2c6e6f20 	stclcs	15, cr6, [lr], #-128	; 0xffffff80
    1098:	544d5720 	strbpl	r5, [sp], #-1824	; 0xfffff8e0
    109c:	56524420 	ldrbpl	r4, [r2], -r0, lsr #8
    10a0:	5354535f 	cmppl	r4, #2080374785	; 0x7c000001
    10a4:	78305b5f 	ldmdavc	r0!, {r0, r1, r2, r3, r4, r6, r8, r9, fp, ip, lr}
    10a8:	0a5d7825 	beq	175f144 <wmt_core_func_ctrl_cmd+0x175bd24>
    10ac:	00000000 	andeq	r0, r0, r0
    10b0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    10b4:	5b5d432d 	blpl	1751d70 <wmt_core_func_ctrl_cmd+0x174e950>
    10b8:	73255d45 	teqvc	r5, #4416	; 0x1140
    10bc:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    10c0:	544d573a 	strbpl	r5, [sp], #-1850	; 0xfffff8c6
    10c4:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
    10c8:	57485f4c 	strbpl	r5, [r8, -ip, asr #30]
    10cc:	5257505f 	subspl	r5, r7, #95	; 0x5f
    10d0:	204e4f5f 	subcs	r4, lr, pc, asr pc
    10d4:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
    10d8:	65526920 	ldrbvs	r6, [r2, #-2336]	; 0xfffff6e0
    10dc:	64252874 	strtvs	r2, [r5], #-2164	; 0xfffff78c
    10e0:	00000a29 	andeq	r0, r0, r9, lsr #20
    10e4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    10e8:	5b5d432d 	blpl	1751da4 <wmt_core_func_ctrl_cmd+0x174e984>
    10ec:	73255d49 	teqvc	r5, #4672	; 0x1240
    10f0:	7465723a 	strbtvc	r7, [r5], #-570	; 0xfffffdc6
    10f4:	28207972 	stmdacs	r0!, {r1, r4, r5, r6, r8, fp, ip, sp, lr}
    10f8:	0a296425 	beq	a5a194 <wmt_core_func_ctrl_cmd+0xa56d74>
    10fc:	00000000 	andeq	r0, r0, r0
    1100:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1104:	5b5d432d 	blpl	1751dc0 <wmt_core_func_ctrl_cmd+0x174e9a0>
    1108:	73255d45 	teqvc	r5, #4416	; 0x1140
    110c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1110:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1114:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1118:	74735f65 	ldrbtvc	r5, [r3], #-3941	; 0xfffff09b
    111c:	6e695f70 	mcrvs	15, 3, r5, cr9, cr0, {3}
    1120:	66207469 	strtvs	r7, [r0], -r9, ror #8
    1124:	206c6961 	rsbcs	r6, ip, r1, ror #18
    1128:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    112c:	0000000a 	andeq	r0, r0, sl
    1130:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1134:	5b5d432d 	blpl	1751df0 <wmt_core_func_ctrl_cmd+0x174e9d0>
    1138:	73255d45 	teqvc	r5, #4416	; 0x1140
    113c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1140:	66706f3a 	uhasxvs	r6, r0, sl
    1144:	5f636e75 	svcpl	0x00636e75
    1148:	5f727770 	svcpl	0x00727770
    114c:	2066666f 	rsbcs	r6, r6, pc, ror #12
    1150:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
    1154:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1158:	72756420 	rsbsvc	r6, r5, #32, 8	; 0x20000000
    115c:	20676e69 	rsbcs	r6, r7, r9, ror #28
    1160:	5f727770 	svcpl	0x00727770
    1164:	72206e6f 	eorvc	r6, r0, #1776	; 0x6f0
    1168:	79727465 	ldmdbvc	r2!, {r0, r2, r5, r6, sl, ip, sp, lr}^
    116c:	0000000a 	andeq	r0, r0, sl
    1170:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1174:	5b5d432d 	blpl	1751e30 <wmt_core_func_ctrl_cmd+0x174ea10>
    1178:	73255d49 	teqvc	r5, #4672	; 0x1240
    117c:	206f643a 	rsbcs	r6, pc, sl, lsr r4	; <UNPREDICTABLE>
    1180:	72746572 	rsbsvc	r6, r4, #478150656	; 0x1c800000
    1184:	63202c79 	teqvs	r0, #30976	; 0x7900
    1188:	746e756f 	strbtvc	r7, [lr], #-1391	; 0xfffffa91
    118c:	66656c20 	strbtvs	r6, [r5], -r0, lsr #24
    1190:	64252874 	strtvs	r2, [r5], #-2164	; 0xfffff78c
    1194:	00000a29 	andeq	r0, r0, r9, lsr #20
    1198:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    119c:	5b5d432d 	blpl	1751e58 <wmt_core_func_ctrl_cmd+0x174ea38>
    11a0:	73255d44 	teqvc	r5, #68, 26	; 0x1100
    11a4:	544d573a 	strbpl	r5, [sp], #-1850	; 0xfffff8c6
    11a8:	55465b20 	strbpl	r5, [r6, #-2848]	; 0xfffff4e0
    11ac:	4f5f434e 	svcmi	0x005f434e
    11b0:	000a5d4e 	andeq	r5, sl, lr, asr #26
    11b4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    11b8:	5b5d432d 	blpl	1751e74 <wmt_core_func_ctrl_cmd+0x174ea54>
    11bc:	73255d45 	teqvc	r5, #4416	; 0x1140
    11c0:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    11c4:	6e62613a 	mcrvs	1, 3, r6, cr2, cr10, {1}
    11c8:	616d726f 	cmnvs	sp, pc, ror #4
    11cc:	7566206c 	strbvc	r2, [r6, #-108]!	; 0xffffff94
    11d0:	2528636e 	strcs	r6, [r8, #-878]!	; 0xfffffc92
    11d4:	000a2964 	andeq	r2, sl, r4, ror #18
    11d8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    11dc:	5b5d432d 	blpl	1751e98 <wmt_core_func_ctrl_cmd+0x174ea78>
    11e0:	73255d45 	teqvc	r5, #4416	; 0x1140
    11e4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    11e8:	6e75663a 	mrcvs	6, 3, r6, cr5, cr10, {1}
    11ec:	64252863 	strtvs	r2, [r5], #-2147	; 0xfffff79d
    11f0:	74732029 	ldrbtvc	r2, [r3], #-41	; 0xffffffd7
    11f4:	73757461 	cmnvc	r5, #1627389952	; 0x61000000
    11f8:	2578305b 	ldrbcs	r3, [r8, #-91]!	; 0xffffffa5
    11fc:	61205d78 	teqvs	r0, r8, ror sp
    1200:	726f6e62 	rsbvc	r6, pc, #1568	; 0x620
    1204:	0a6c616d 	beq	1b197c0 <wmt_core_func_ctrl_cmd+0x1b163a0>
    1208:	00000000 	andeq	r0, r0, r0
    120c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1210:	5b5d432d 	blpl	1751ecc <wmt_core_func_ctrl_cmd+0x174eaac>
    1214:	73255d57 	teqvc	r5, #5568	; 0x15c0
    1218:	6e75663a 	mrcvs	6, 3, r6, cr5, cr10, {1}
    121c:	64252863 	strtvs	r2, [r5], #-2147	; 0xfffff79d
    1220:	6c612029 	stclvs	0, cr2, [r1], #-164	; 0xffffff5c
    1224:	64616572 	strbtvs	r6, [r1], #-1394	; 0xfffffa8e
    1228:	6e6f2079 	mcrvs	0, 3, r2, cr15, cr9, {3}
    122c:	0000000a 	andeq	r0, r0, sl
    1230:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1234:	5b5d432d 	blpl	1751ef0 <wmt_core_func_ctrl_cmd+0x174ead0>
    1238:	73255d45 	teqvc	r5, #4416	; 0x1140
    123c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1240:	6e75663a 	mrcvs	6, 3, r6, cr5, cr10, {1}
    1244:	64252863 	strtvs	r2, [r5], #-2147	; 0xfffff79d
    1248:	77702029 	ldrbvc	r2, [r0, -r9, lsr #32]!
    124c:	6e6f5f72 	mcrvs	15, 3, r5, cr15, cr2, {3}
    1250:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
    1254:	6425286c 	strtvs	r2, [r5], #-2156	; 0xfffff794
    1258:	00000a29 	andeq	r0, r0, r9, lsr #20
    125c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1260:	5b5d432d 	blpl	1751f1c <wmt_core_func_ctrl_cmd+0x174eafc>
    1264:	73255d44 	teqvc	r5, #68, 26	; 0x1100
    1268:	4f4c533a 	svcmi	0x004c533a
    126c:	44535f54 	ldrbmi	r5, [r3], #-3924	; 0xfffff0ac
    1270:	20324f49 	eorscs	r4, r2, r9, asr #30
    1274:	64616572 	strbtvs	r6, [r1], #-1394	; 0xfffffa8e
    1278:	6f662079 	svcvs	0x00662079
    127c:	49572072 	ldmdbmi	r7, {r1, r4, r5, r6, sp}^
    1280:	000a4946 	andeq	r4, sl, r6, asr #18
    1284:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1288:	5b5d432d 	blpl	1751f44 <wmt_core_func_ctrl_cmd+0x174eb24>
    128c:	73255d45 	teqvc	r5, #4416	; 0x1140
    1290:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1294:	7275743a 	rsbsvc	r7, r5, #973078528	; 0x3a000000
    1298:	6e6f206e 	cdpvs	0, 6, cr2, cr15, cr14, {3}
    129c:	2d695720 	stclcs	7, cr5, [r9, #-128]!	; 0xffffff80
    12a0:	69206946 	stmdbvs	r0!, {r1, r2, r6, r8, fp, sp, lr}
    12a4:	6f63206e 	svcvs	0x0063206e
    12a8:	53206d6d 	teqpl	r0, #6976	; 0x1b40
    12ac:	324f4944 	subcc	r4, pc, #68, 18	; 0x110000
    12b0:	74756220 	ldrbtvc	r6, [r5], #-544	; 0xfffffde0
    12b4:	49445320 	stmdbmi	r4, {r5, r8, r9, ip, lr}^
    12b8:	6e69204f 	cdpvs	0, 6, cr2, cr9, cr15, {2}
    12bc:	4e554620 	cdpmi	6, 5, cr4, cr5, cr0, {1}
    12c0:	464f5f43 	strbmi	r5, [pc], -r3, asr #30
    12c4:	74732046 	ldrbtvc	r2, [r3], #-70	; 0xffffffba
    12c8:	28657461 	stmdacs	r5!, {r0, r5, r6, sl, ip, sp, lr}^
    12cc:	78257830 	stmdavc	r5!, {r4, r5, fp, ip, sp, lr}
    12d0:	00000a29 	andeq	r0, r0, r9, lsr #20
    12d4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    12d8:	5b5d432d 	blpl	1751f94 <wmt_core_func_ctrl_cmd+0x174eb74>
    12dc:	73255d45 	teqvc	r5, #4416	; 0x1140
    12e0:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    12e4:	746f6e3a 	strbtvc	r6, [pc], #-3642	; 12ec <.rodata.str1.4+0x12ec>
    12e8:	70757320 	rsbsvc	r7, r5, r0, lsr #6
    12ec:	74726f70 	ldrbtvc	r6, [r2], #-3952	; 0xfffff090
    12f0:	67206465 	strvs	r6, [r0, -r5, ror #8]!
    12f4:	576b744d 	strbpl	r7, [fp, -sp, asr #8]!
    12f8:	7443746d 	strbvc	r7, [r3], #-1133	; 0xfffffb93
    12fc:	6d772e78 	ldclvs	14, cr2, [r7, #-480]!	; 0xfffffe20
    1300:	66694874 			; <UNDEFINED> instruction: 0x66694874
    1304:	666e6f43 	strbtvs	r6, [lr], -r3, asr #30
    1308:	6669682e 	strbtvs	r6, [r9], -lr, lsr #16
    130c:	65707954 	ldrbvs	r7, [r0, #-2388]!	; 0xfffff6ac
    1310:	7830203a 	ldmdavc	r0!, {r1, r3, r4, r5, sp}
    1314:	202c7825 	eorcs	r7, ip, r5, lsr #16
    1318:	70736e75 	rsbsvc	r6, r3, r5, ror lr
    131c:	66696365 	strbtvs	r6, [r9], -r5, ror #6
    1320:	20646569 	rsbcs	r6, r4, r9, ror #10
    1324:	69666977 	stmdbvs	r6!, {r0, r1, r2, r4, r5, r6, r8, fp, sp, lr}^
    1328:	6669685f 			; <UNDEFINED> instruction: 0x6669685f
    132c:	0000000a 	andeq	r0, r0, sl
    1330:	46204641 	strtmi	r4, [r0], -r1, asr #12
    1334:	20434e55 	subcs	r4, r3, r5, asr lr
    1338:	00004e4f 	andeq	r4, r0, pc, asr #28
    133c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1340:	5b5d432d 	blpl	1751ffc <wmt_core_func_ctrl_cmd+0x174ebdc>
    1344:	73255d45 	teqvc	r5, #4416	; 0x1140
    1348:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    134c:	6765723a 			; <UNDEFINED> instruction: 0x6765723a
    1350:	2077725f 	rsbscs	r7, r7, pc, asr r2
    1354:	6e656877 	mcrvs	8, 3, r6, cr5, cr7, {3}
    1358:	544d5720 	strbpl	r5, [sp], #-1824	; 0xfffff8e0
    135c:	20736920 	rsbscs	r6, r3, r0, lsr #18
    1360:	65776f70 	ldrbvs	r6, [r7, #-3952]!	; 0xfffff090
    1364:	20646572 	rsbcs	r6, r4, r2, ror r5
    1368:	0a66666f 	beq	199ad2c <wmt_core_func_ctrl_cmd+0x199790c>
    136c:	00000000 	andeq	r0, r0, r0
    1370:	73756665 	cmnvc	r5, #105906176	; 0x6500000
    1374:	6d635f65 	stclvs	15, cr5, [r3, #-404]!	; 0xfffffe6c
    1378:	00000064 	andeq	r0, r0, r4, rrx
    137c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1380:	5b5d432d 	blpl	175203c <wmt_core_func_ctrl_cmd+0x174ec1c>
    1384:	73255d45 	teqvc	r5, #4416	; 0x1140
    1388:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    138c:	5546453a 	strbpl	r4, [r6, #-1338]	; 0xfffffac6
    1390:	435f4553 	cmpmi	pc, #348127232	; 0x14c00000
    1394:	6920444d 	stmdbvs	r0!, {r0, r2, r3, r6, sl, lr}
    1398:	28746552 	ldmdacs	r4!, {r1, r4, r6, r8, sl, sp, lr}^
    139c:	20296425 	eorcs	r6, r9, r5, lsr #8
    13a0:	20646d63 	rsbcs	r6, r4, r3, ror #26
    13a4:	206e656c 	rsbcs	r6, lr, ip, ror #10
    13a8:	28727265 	ldmdacs	r2!, {r0, r2, r5, r6, r9, ip, sp, lr}^
    13ac:	202c6425 	eorcs	r6, ip, r5, lsr #8
    13b0:	20296425 	eorcs	r6, r9, r5, lsr #8
    13b4:	0000000a 	andeq	r0, r0, sl
    13b8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    13bc:	5b5d432d 	blpl	1752078 <wmt_core_func_ctrl_cmd+0x174ec58>
    13c0:	73255d45 	teqvc	r5, #4416	; 0x1140
    13c4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    13c8:	6165723a 	cmnvs	r5, sl, lsr r2
    13cc:	46452064 	strbmi	r2, [r5], -r4, rrx
    13d0:	5f455355 	svcpl	0x00455355
    13d4:	20545645 	subscs	r5, r4, r5, asr #12
    13d8:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
    13dc:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    13e0:	6e656c20 	cdpvs	12, 6, cr6, cr5, cr0, {1}
    13e4:	2c642528 	cfstr64cs	mvdx2, [r4], #-160	; 0xffffff60
    13e8:	29642520 	stmdbcs	r4!, {r5, r8, sl, sp}^
    13ec:	0000000a 	andeq	r0, r0, sl
    13f0:	73756665 	cmnvc	r5, #105906176	; 0x6500000
    13f4:	76655f65 	strbtvc	r5, [r5], -r5, ror #30
    13f8:	00000074 	andeq	r0, r0, r4, ror r0
    13fc:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1400:	5b5d432d 	blpl	17520bc <wmt_core_func_ctrl_cmd+0x174ec9c>
    1404:	73255d45 	teqvc	r5, #4416	; 0x1140
    1408:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    140c:	4548543a 	strbmi	r5, [r8, #-1082]	; 0xfffffbc6
    1410:	435f4d52 	cmpmi	pc, #5248	; 0x1480
    1414:	5f4c5254 	svcpl	0x004c5254
    1418:	20444d43 	subcs	r4, r4, r3, asr #26
    141c:	74655269 	strbtvc	r5, [r5], #-617	; 0xfffffd97
    1420:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1424:	646d6320 	strbtvs	r6, [sp], #-800	; 0xfffffce0
    1428:	6e656c20 	cdpvs	12, 6, cr6, cr5, cr0, {1}
    142c:	72726520 	rsbsvc	r6, r2, #32, 10	; 0x8000000
    1430:	2c642528 	cfstr64cs	mvdx2, [r4], #-160	; 0xffffff60
    1434:	29642520 	stmdbcs	r4!, {r5, r8, sl, sp}^
    1438:	00000a20 	andeq	r0, r0, r0, lsr #20
    143c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1440:	5b5d432d 	blpl	17520fc <wmt_core_func_ctrl_cmd+0x174ecdc>
    1444:	73255d45 	teqvc	r5, #4416	; 0x1140
    1448:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    144c:	6165723a 	cmnvs	r5, sl, lsr r2
    1450:	48542064 	ldmdami	r4, {r2, r5, r6, sp}^
    1454:	5f4d5245 	svcpl	0x004d5245
    1458:	4c525443 	cfldrdmi	mvd5, [r2], {67}	; 0x43
    145c:	5456455f 	ldrbpl	r4, [r6], #-1375	; 0xfffffaa1
    1460:	4548542f 	strbmi	r5, [r8, #-1071]	; 0xfffffbd1
    1464:	525f4d52 	subspl	r4, pc, #5248	; 0x1480
    1468:	5f444145 	svcpl	0x00444145
    146c:	4e455645 	cdpmi	6, 4, cr5, cr5, cr5, {2}
    1470:	61662054 	qdsubvs	r2, r4, r6
    1474:	25286c69 	strcs	r6, [r8, #-3177]!	; 0xfffff397
    1478:	6c202964 	stcvs	9, cr2, [r0], #-400	; 0xfffffe70
    147c:	25286e65 	strcs	r6, [r8, #-3685]!	; 0xfffff19b
    1480:	25202c64 	strcs	r2, [r0, #-3172]!	; 0xfffff39c
    1484:	000a2964 	andeq	r2, sl, r4, ror #18
    1488:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    148c:	5b5d432d 	blpl	1752148 <wmt_core_func_ctrl_cmd+0x174ed28>
    1490:	73255d45 	teqvc	r5, #4416	; 0x1140
    1494:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1498:	6d6f633a 	stclvs	3, cr6, [pc, #-232]!	; 13b8 <.rodata.str1.4+0x13b8>
    149c:	65726170 	ldrbvs	r6, [r2, #-368]!	; 0xfffffe90
    14a0:	544d5720 	strbpl	r5, [sp], #-1824	; 0xfffff8e0
    14a4:	4548545f 	strbmi	r5, [r8, #-1119]	; 0xfffffba1
    14a8:	435f4d52 	cmpmi	pc, #5248	; 0x1480
    14ac:	5f4c5254 	svcpl	0x004c5254
    14b0:	20545645 	subscs	r5, r4, r5, asr #12
    14b4:	6f727265 	svcvs	0x00727265
    14b8:	00000a72 	andeq	r0, r0, r2, ror sl
    14bc:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    14c0:	5b5d432d 	blpl	175217c <wmt_core_func_ctrl_cmd+0x174ed5c>
    14c4:	73255d49 	teqvc	r5, #4672	; 0x1240
    14c8:	6e65533a 	mcrvs	3, 3, r5, cr5, cr10, {1}
    14cc:	4d572064 	ldclmi	0, cr2, [r7, #-400]	; 0xfffffe70
    14d0:	48545f54 	ldmdami	r4, {r2, r4, r6, r8, r9, sl, fp, ip, lr}^
    14d4:	5f4d5245 	svcpl	0x004d5245
    14d8:	4c525443 	cfldrdmi	mvd5, [r2], {67}	; 0x43
    14dc:	444d435f 	strbmi	r4, [sp], #-863	; 0xfffffca1
    14e0:	6d6f6320 	stclvs	3, cr6, [pc, #-128]!	; 1468 <.rodata.str1.4+0x1468>
    14e4:	646e616d 	strbtvs	r6, [lr], #-365	; 0xfffffe93
    14e8:	214b4f20 	cmpcs	fp, r0, lsr #30
    14ec:	0000000a 	andeq	r0, r0, sl
    14f0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    14f4:	5b5d432d 	blpl	17521b0 <wmt_core_func_ctrl_cmd+0x174ed90>
    14f8:	73255d45 	teqvc	r5, #4416	; 0x1140
    14fc:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1500:	6d6f633a 	stclvs	3, cr6, [pc, #-232]!	; 1420 <.rodata.str1.4+0x1420>
    1504:	65726170 	ldrbvs	r6, [r2, #-368]!	; 0xfffffe90
    1508:	544d5720 	strbpl	r5, [sp], #-1824	; 0xfffff8e0
    150c:	4548545f 	strbmi	r5, [r8, #-1119]	; 0xfffffba1
    1510:	525f4d52 	subspl	r4, pc, #5248	; 0x1480
    1514:	5f444145 	svcpl	0x00444145
    1518:	20545645 	subscs	r5, r4, r5, asr #12
    151c:	6f727265 	svcvs	0x00727265
    1520:	00000a72 	andeq	r0, r0, r2, ror sl
    1524:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1528:	5b5d432d 	blpl	17521e4 <wmt_core_func_ctrl_cmd+0x174edc4>
    152c:	73255d45 	teqvc	r5, #4416	; 0x1140
    1530:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1534:	2878723a 	ldmdacs	r8!, {r1, r3, r4, r5, r9, ip, sp, lr}^
    1538:	3a296425 	bcc	a5a5d4 <wmt_core_func_ctrl_cmd+0xa571b4>
    153c:	3230255b 	eorscc	r2, r0, #381681664	; 0x16c00000
    1540:	30252c58 	eorcc	r2, r5, r8, asr ip
    1544:	252c5832 	strcs	r5, [ip, #-2098]!	; 0xfffff7ce
    1548:	2c583230 	lfmcs	f3, 2, [r8], {48}	; 0x30
    154c:	58323025 	ldmdapl	r2!, {r0, r2, r5, ip, sp}
    1550:	3230252c 	eorscc	r2, r0, #44, 10	; 0xb000000
    1554:	30252c58 	eorcc	r2, r5, r8, asr ip
    1558:	205d5832 	subscs	r5, sp, r2, lsr r8
    155c:	28707865 	ldmdacs	r0!, {r0, r2, r5, r6, fp, ip, sp, lr}^
    1560:	3a296425 	bcc	a5a5fc <wmt_core_func_ctrl_cmd+0xa571dc>
    1564:	3230255b 	eorscc	r2, r0, #381681664	; 0x16c00000
    1568:	30252c58 	eorcc	r2, r5, r8, asr ip
    156c:	252c5832 	strcs	r5, [ip, #-2098]!	; 0xfffff7ce
    1570:	2c583230 	lfmcs	f3, 2, [r8], {48}	; 0x30
    1574:	58323025 	ldmdapl	r2!, {r0, r2, r5, ip, sp}
    1578:	00000a5d 	andeq	r0, r0, sp, asr sl
    157c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1580:	5b5d432d 	blpl	175223c <wmt_core_func_ctrl_cmd+0x174ee1c>
    1584:	73255d49 	teqvc	r5, #4672	; 0x1240
    1588:	6e65533a 	mcrvs	3, 3, r5, cr5, cr10, {1}
    158c:	4d572064 	ldclmi	0, cr2, [r7, #-400]	; 0xfffffe70
    1590:	48545f54 	ldmdami	r4, {r2, r4, r6, r8, r9, sl, fp, ip, lr}^
    1594:	5f4d5245 	svcpl	0x004d5245
    1598:	44414552 	strbmi	r4, [r1], #-1362	; 0xfffffaae
    159c:	444d435f 	strbmi	r4, [sp], #-863	; 0xfffffca1
    15a0:	6d6f6320 	stclvs	3, cr6, [pc, #-128]!	; 1528 <.rodata.str1.4+0x1528>
    15a4:	646e616d 	strbtvs	r6, [lr], #-365	; 0xfffffe93
    15a8:	214b4f20 	cmpcs	fp, r0, lsr #30
    15ac:	0000000a 	andeq	r0, r0, sl
    15b0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    15b4:	5b5d432d 	blpl	1752270 <wmt_core_func_ctrl_cmd+0x174ee50>
    15b8:	73255d49 	teqvc	r5, #4672	; 0x1240
    15bc:	6e65533a 	mcrvs	3, 3, r5, cr5, cr10, {1}
    15c0:	65542064 	ldrbvs	r2, [r4, #-100]	; 0xffffff9c
    15c4:	63207473 	teqvs	r0, #1929379840	; 0x73000000
    15c8:	616d6d6f 	cmnvs	sp, pc, ror #26
    15cc:	2520646e 	strcs	r6, [r0, #-1134]!	; 0xfffffb92
    15d0:	000a2164 	andeq	r2, sl, r4, ror #2
    15d4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    15d8:	5b5d432d 	blpl	1752294 <wmt_core_func_ctrl_cmd+0x174ee74>
    15dc:	73255d49 	teqvc	r5, #4672	; 0x1240
    15e0:	6e65533a 	mcrvs	3, 3, r5, cr5, cr10, {1}
    15e4:	73412064 	movtvc	r2, #4196	; 0x1064
    15e8:	74726573 	ldrbtvc	r6, [r2], #-1395	; 0xfffffa8d
    15ec:	6d6f6320 	stclvs	3, cr6, [pc, #-128]!	; 1574 <.rodata.str1.4+0x1574>
    15f0:	646e616d 	strbtvs	r6, [lr], #-365	; 0xfffffe93
    15f4:	000a2120 	andeq	r2, sl, r0, lsr #2
    15f8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    15fc:	5b5d432d 	blpl	17522b8 <wmt_core_func_ctrl_cmd+0x174ee98>
    1600:	73255d49 	teqvc	r5, #4672	; 0x1240
    1604:	6e65533a 	mcrvs	3, 3, r5, cr5, cr10, {1}
    1608:	78452064 	stmdavc	r5, {r2, r5, r6, sp}^
    160c:	74706563 	ldrbtvc	r6, [r0], #-1379	; 0xfffffa9d
    1610:	206e6f69 	rsbcs	r6, lr, r9, ror #30
    1614:	6d6d6f63 	stclvs	15, cr6, [sp, #-396]!	; 0xfffffe74
    1618:	20646e61 	rsbcs	r6, r4, r1, ror #28
    161c:	00000a21 	andeq	r0, r0, r1, lsr #20
    1620:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1624:	5b5d432d 	blpl	17522e0 <wmt_core_func_ctrl_cmd+0x174eec0>
    1628:	73255d49 	teqvc	r5, #4672	; 0x1240
    162c:	6e65533a 	mcrvs	3, 3, r5, cr5, cr10, {1}
    1630:	6f432064 	svcvs	0x00432064
    1634:	73697865 	cmnvc	r9, #6619136	; 0x650000
    1638:	636e6574 	cmnvs	lr, #116, 10	; 0x1d000000
    163c:	65442065 	strbvs	r2, [r4, #-101]	; 0xffffff9b
    1640:	20677562 	rsbcs	r7, r7, r2, ror #10
    1644:	6d6d6f63 	stclvs	15, cr6, [sp, #-396]!	; 0xfffffe74
    1648:	20646e61 	rsbcs	r6, r4, r1, ror #28
    164c:	2578305b 	ldrbcs	r3, [r8, #-91]!	; 0xffffffa5
    1650:	0a215d78 	beq	858c38 <wmt_core_func_ctrl_cmd+0x855818>
    1654:	00000000 	andeq	r0, r0, r0
    1658:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    165c:	5b5d432d 	blpl	1752318 <wmt_core_func_ctrl_cmd+0x174eef8>
    1660:	73255d45 	teqvc	r5, #4416	; 0x1140
    1664:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1668:	646d633a 	strbtvs	r6, [sp], #-826	; 0xfffffcc6
    166c:	61506f4e 	cmpvs	r0, lr, asr #30
    1670:	20736920 	rsbscs	r6, r3, r0, lsr #18
    1674:	6e6f7277 	mcrvs	2, 3, r7, cr15, cr7, {3}
    1678:	00000a67 	andeq	r0, r0, r7, ror #20
    167c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1680:	5b5d432d 	blpl	175233c <wmt_core_func_ctrl_cmd+0x174ef1c>
    1684:	73255d45 	teqvc	r5, #4416	; 0x1140
    1688:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    168c:	2078743a 	rsbscs	r7, r8, sl, lsr r4
    1690:	6c696166 	stfvse	f6, [r9], #-408	; 0xfffffe68
    1694:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1698:	646d6320 	strbtvs	r6, [sp], #-800	; 0xfffffce0
    169c:	6e656c20 	cdpvs	12, 6, cr6, cr5, cr0, {1}
    16a0:	72726520 	rsbsvc	r6, r2, #32, 10	; 0x8000000
    16a4:	2c642528 	cfstr64cs	mvdx2, [r4], #-160	; 0xffffff60
    16a8:	29642520 	stmdbcs	r4!, {r5, r8, sl, sp}^
    16ac:	00000a20 	andeq	r0, r0, r0, lsr #20
    16b0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    16b4:	5b5d432d 	blpl	1752370 <wmt_core_func_ctrl_cmd+0x174ef50>
    16b8:	73255d49 	teqvc	r5, #4672	; 0x1240
    16bc:	746f6e3a 	strbtvc	r6, [pc], #-3642	; 16c4 <.rodata.str1.4+0x16c4>
    16c0:	206f7420 	rsbcs	r7, pc, r0, lsr #8
    16c4:	65207872 	strvs	r7, [r0, #-2162]!	; 0xfffff78e
    16c8:	746e6576 	strbtvc	r6, [lr], #-1398	; 0xfffffa8a
    16cc:	726f6620 	rsbvc	r6, pc, #32, 12	; 0x2000000
    16d0:	73736120 	cmnvc	r3, #32, 2
    16d4:	20747265 	rsbscs	r7, r4, r5, ror #4
    16d8:	6d6d6f63 	stclvs	15, cr6, [sp, #-396]!	; 0xfffffe74
    16dc:	0a646e61 	beq	191d068 <wmt_core_func_ctrl_cmd+0x1919c48>
    16e0:	00000000 	andeq	r0, r0, r0
    16e4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    16e8:	5b5d432d 	blpl	17523a4 <wmt_core_func_ctrl_cmd+0x174ef84>
    16ec:	73255d49 	teqvc	r5, #4672	; 0x1240
    16f0:	3d3d233a 	ldccc	3, cr2, [sp, #-232]!	; 0xffffff18
    16f4:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    16f8:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    16fc:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    1700:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    1704:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    1708:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    170c:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    1710:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    1714:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    1718:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    171c:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    1720:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    1724:	3d3d3d3d 	ldccc	13, cr3, [sp, #-244]!	; 0xffffff0c
    1728:	233d3d3d 	teqcs	sp, #3904	; 0xf40
    172c:	0000000a 	andeq	r0, r0, sl
    1730:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1734:	5b5d432d 	blpl	17523f0 <wmt_core_func_ctrl_cmd+0x174efd0>
    1738:	73255d49 	teqvc	r5, #4672	; 0x1240
    173c:	656f633a 	strbvs	r6, [pc, #-826]!	; 140a <.rodata.str1.4+0x140a>
    1740:	64207478 	strtvs	r7, [r0], #-1144	; 0xfffffb88
    1744:	67756265 	ldrbvs	r6, [r5, -r5, ror #4]!
    1748:	676e6967 	strbvs	r6, [lr, -r7, ror #18]!
    174c:	20646920 	rsbcs	r6, r4, r0, lsr #18
    1750:	6425203d 	strtvs	r2, [r5], #-61	; 0xffffffc3
    1754:	00000000 	andeq	r0, r0, r0
    1758:	78656f63 	stmdavc	r5!, {r0, r1, r5, r6, r8, r9, sl, fp, sp, lr}^
    175c:	62656420 	rsbvs	r6, r5, #32, 8	; 0x20000000
    1760:	69676775 	stmdbvs	r7!, {r0, r2, r4, r5, r6, r8, r9, sl, sp, lr}^
    1764:	0020676e 	eoreq	r6, r0, lr, ror #14
    1768:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    176c:	5b5d432d 	blpl	1752428 <wmt_core_func_ctrl_cmd+0x174f008>
    1770:	73255d45 	teqvc	r5, #4416	; 0x1140
    1774:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1778:	7272653a 	rsbsvc	r6, r2, #243269632	; 0xe800000
    177c:	6320726f 	teqvs	r0, #-268435450	; 0xf0000006
    1780:	2078656f 	rsbscs	r6, r8, pc, ror #10
    1784:	75626564 	strbvc	r6, [r2, #-1380]!	; 0xfffffa9c
    1788:	6e696767 	cdpvs	7, 6, cr6, cr9, cr7, {3}
    178c:	76652067 	strbtvc	r2, [r5], -r7, rrx
    1790:	0a746e65 	beq	1d1d12c <wmt_core_func_ctrl_cmd+0x1d19d0c>
    1794:	00000000 	andeq	r0, r0, r0
    1798:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    179c:	5b5d432d 	blpl	1752458 <wmt_core_func_ctrl_cmd+0x174f038>
    17a0:	73255d45 	teqvc	r5, #4416	; 0x1140
    17a4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    17a8:	6e62613a 	mcrvs	1, 3, r6, cr2, cr10, {1}
    17ac:	616d726f 	cmnvs	sp, pc, ror #4
    17b0:	504c206c 	subpl	r2, ip, ip, rrx
    17b4:	69204b42 	stmdbvs	r0!, {r1, r6, r8, r9, fp, lr}
    17b8:	6d77206e 	ldclvs	0, cr2, [r7, #-440]!	; 0xfffffe48
    17bc:	6f645f74 	svcvs	0x00645f74
    17c0:	62706c5f 	rsbsvs	r6, r0, #24320	; 0x5f00
    17c4:	00000a6b 	andeq	r0, r0, fp, ror #20
    17c8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    17cc:	5b5d432d 	blpl	1752488 <wmt_core_func_ctrl_cmd+0x174f068>
    17d0:	73255d45 	teqvc	r5, #4416	; 0x1140
    17d4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    17d8:	66706f3a 	uhasxvs	r6, r0, sl
    17dc:	5f636e75 	svcpl	0x00636e75
    17e0:	6b62706c 	blvs	189d998 <wmt_core_func_ctrl_cmd+0x189a578>
    17e4:	746d7720 	strbtvc	r7, [sp], #-1824	; 0xfffff8e0
    17e8:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    17ec:	78745f65 	ldmdavc	r4!, {r0, r2, r5, r6, r8, r9, sl, fp, ip, lr}^
    17f0:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
    17f4:	2064656c 	rsbcs	r6, r4, ip, ror #10
    17f8:	0000000a 	andeq	r0, r0, sl
    17fc:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1800:	5b5d432d 	blpl	17524bc <wmt_core_func_ctrl_cmd+0x174f09c>
    1804:	73255d45 	teqvc	r5, #4416	; 0x1140
    1808:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    180c:	66706f3a 	uhasxvs	r6, r0, sl
    1810:	5f636e75 	svcpl	0x00636e75
    1814:	6b62706c 	blvs	189d9cc <wmt_core_func_ctrl_cmd+0x189a5ac>
    1818:	746d7720 	strbtvc	r7, [sp], #-1824	; 0xfffff8e0
    181c:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1820:	78725f65 	ldmdavc	r2!, {r0, r2, r5, r6, r8, r9, sl, fp, ip, lr}^
    1824:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
    1828:	2064656c 	rsbcs	r6, r4, ip, ror #10
    182c:	0000000a 	andeq	r0, r0, sl
    1830:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1834:	5b5d432d 	blpl	17524f0 <wmt_core_func_ctrl_cmd+0x174f0d0>
    1838:	73255d45 	teqvc	r5, #4416	; 0x1140
    183c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1840:	62706c3a 	rsbsvs	r6, r0, #14848	; 0x3a00
    1844:	7665206b 	strbtvc	r2, [r5], -fp, rrx
    1848:	20746e65 	rsbscs	r6, r4, r5, ror #28
    184c:	64616572 	strbtvs	r6, [r1], #-1394	; 0xfffffa8e
    1850:	7a697320 	bvc	1a5e4d8 <wmt_core_func_ctrl_cmd+0x1a5b0b8>
    1854:	72772065 	rsbsvc	r2, r7, #101	; 0x65
    1858:	28676e6f 	stmdacs	r7!, {r0, r1, r2, r3, r5, r6, r9, sl, fp, sp, lr}^
    185c:	202c6425 	eorcs	r6, ip, r5, lsr #8
    1860:	20296425 	eorcs	r6, r9, r5, lsr #8
    1864:	0000000a 	andeq	r0, r0, sl
    1868:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    186c:	5b5d432d 	blpl	1752528 <wmt_core_func_ctrl_cmd+0x174f108>
    1870:	73255d45 	teqvc	r5, #4416	; 0x1140
    1874:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1878:	544d573a 	strbpl	r5, [sp], #-1850	; 0xfffff8c6
    187c:	5345545f 	movtpl	r5, #21599	; 0x545f
    1880:	504c5f54 	subpl	r5, ip, r4, asr pc
    1884:	455f4b42 	ldrbmi	r4, [pc, #-2882]	; d4a <.rodata.str1.4+0xd4a>
    1888:	65205456 	strvs	r5, [r0, #-1110]!	; 0xfffffbaa
    188c:	726f7272 	rsbvc	r7, pc, #536870919	; 0x20000007
    1890:	65722021 	ldrbvs	r2, [r2, #-33]!	; 0xffffffdf
    1894:	6c206461 	cfstrsvs	mvf6, [r0], #-388	; 0xfffffe7c
    1898:	25206e65 	strcs	r6, [r0, #-3685]!	; 0xfffff19b
    189c:	255b2064 	ldrbcs	r2, [fp, #-100]	; 0xffffff9c
    18a0:	2c783230 	lfmcs	f3, 2, [r8], #-192	; 0xffffff40
    18a4:	78323025 	ldmdavc	r2!, {r0, r2, r5, ip, sp}
    18a8:	3230252c 	eorscc	r2, r0, #44, 10	; 0xb000000
    18ac:	30252c78 	eorcc	r2, r5, r8, ror ip
    18b0:	252c7832 	strcs	r7, [ip, #-2098]!	; 0xfffff7ce
    18b4:	5d783230 	lfmpl	f3, 2, [r8, #-192]!	; 0xffffff40
    18b8:	00000a20 	andeq	r0, r0, r0, lsr #20
    18bc:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    18c0:	5b5d432d 	blpl	175257c <wmt_core_func_ctrl_cmd+0x174f15c>
    18c4:	73255d45 	teqvc	r5, #4416	; 0x1140
    18c8:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    18cc:	4e53443a 	mrcmi	4, 2, r4, cr3, cr10, {1}
    18d0:	4d435f53 	stclmi	15, cr5, [r3, #-332]	; 0xfffffeb4
    18d4:	52692044 	rsbpl	r2, r9, #68	; 0x44
    18d8:	25287465 	strcs	r7, [r8, #-1125]!	; 0xfffffb9b
    18dc:	74202964 	strtvc	r2, [r0], #-2404	; 0xfffff69c
    18e0:	656c2078 	strbvs	r2, [ip, #-120]!	; 0xffffff88
    18e4:	7265206e 	rsbvc	r2, r5, #110	; 0x6e
    18e8:	64252872 	strtvs	r2, [r5], #-2162	; 0xfffff78e
    18ec:	6425202c 	strtvs	r2, [r5], #-44	; 0xffffffd4
    18f0:	000a2029 	andeq	r2, sl, r9, lsr #32
    18f4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    18f8:	5b5d432d 	blpl	17525b4 <wmt_core_func_ctrl_cmd+0x174f194>
    18fc:	73255d45 	teqvc	r5, #4416	; 0x1140
    1900:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1904:	6165723a 	cmnvs	r5, sl, lsr r2
    1908:	53442064 	movtpl	r2, #16484	; 0x4064
    190c:	455f534e 	ldrbmi	r5, [pc, #-846]	; 15c6 <.rodata.str1.4+0x15c6>
    1910:	66205456 			; <UNDEFINED> instruction: 0x66205456
    1914:	286c6961 	stmdacs	ip!, {r0, r5, r6, r8, fp, sp, lr}^
    1918:	20296425 	eorcs	r6, r9, r5, lsr #8
    191c:	286e656c 	stmdacs	lr!, {r2, r3, r5, r6, r8, sl, sp, lr}^
    1920:	202c6425 	eorcs	r6, ip, r5, lsr #8
    1924:	0a296425 	beq	a5a9c0 <wmt_core_func_ctrl_cmd+0xa575a0>
    1928:	00000000 	andeq	r0, r0, r0
    192c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1930:	5b5d432d 	blpl	17525ec <wmt_core_func_ctrl_cmd+0x174f1cc>
    1934:	73255d45 	teqvc	r5, #4416	; 0x1140
    1938:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    193c:	6d6f633a 	stclvs	3, cr6, [pc, #-232]!	; 185c <.rodata.str1.4+0x185c>
    1940:	65726170 	ldrbvs	r6, [r2, #-368]!	; 0xfffffe90
    1944:	544d5720 	strbpl	r5, [sp], #-1824	; 0xfffff8e0
    1948:	4e53445f 	mrcmi	4, 2, r4, cr3, cr15, {2}
    194c:	56455f53 			; <UNDEFINED> instruction: 0x56455f53
    1950:	72652054 	rsbvc	r2, r5, #84	; 0x54
    1954:	0a726f72 	beq	1c9d724 <wmt_core_func_ctrl_cmd+0x1c9a304>
    1958:	00000000 	andeq	r0, r0, r0
    195c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1960:	5b5d432d 	blpl	175261c <wmt_core_func_ctrl_cmd+0x174f1fc>
    1964:	73255d49 	teqvc	r5, #4672	; 0x1240
    1968:	6e65533a 	mcrvs	3, 3, r5, cr5, cr10, {1}
    196c:	4d572064 	ldclmi	0, cr2, [r7, #-400]	; 0xfffffe70
    1970:	53445f54 	movtpl	r5, #20308	; 0x4f54
    1974:	435f534e 	cmpmi	pc, #939524097	; 0x38000001
    1978:	6320444d 	teqvs	r0, #1291845632	; 0x4d000000
    197c:	616d6d6f 	cmnvs	sp, pc, ror #26
    1980:	4f20646e 	svcmi	0x0020646e
    1984:	000a214b 	andeq	r2, sl, fp, asr #2
    1988:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    198c:	5b5d432d 	blpl	1752648 <wmt_core_func_ctrl_cmd+0x174f228>
    1990:	73255d44 	teqvc	r5, #68, 26	; 0x1100
    1994:	2a2a2a3a 	bcs	a8c284 <wmt_core_func_ctrl_cmd+0xa88e64>
    1998:	6553202a 	ldrbvs	r2, [r3, #-42]	; 0xffffffd6
    199c:	7320646e 	teqvc	r0, #1845493760	; 0x6e000000
    19a0:	7065656c 	rsbvc	r6, r5, ip, ror #10
    19a4:	6d6f6320 	stclvs	3, cr6, [pc, #-128]!	; 192c <.rodata.str1.4+0x192c>
    19a8:	646e616d 	strbtvs	r6, [lr], #-365	; 0xfffffe93
    19ac:	0000000a 	andeq	r0, r0, sl
    19b0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    19b4:	5b5d432d 	blpl	1752670 <wmt_core_func_ctrl_cmd+0x174f250>
    19b8:	73255d45 	teqvc	r5, #4416	; 0x1140
    19bc:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    19c0:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    19c4:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    19c8:	53203a65 	teqpl	r0, #413696	; 0x65000
    19cc:	5045454c 	subpl	r4, r5, ip, asr #10
    19d0:	444d435f 	strbmi	r4, [sp], #-863	; 0xfffffca1
    19d4:	74657220 	strbtvc	r7, [r5], #-544	; 0xfffffde0
    19d8:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    19dc:	646d6320 	strbtvs	r6, [sp], #-800	; 0xfffffce0
    19e0:	6e656c20 	cdpvs	12, 6, cr6, cr5, cr0, {1}
    19e4:	72726520 	rsbsvc	r6, r2, #32, 10	; 0x8000000
    19e8:	2c642528 	cfstr64cs	mvdx2, [r4], #-160	; 0xffffff60
    19ec:	29642520 	stmdbcs	r4!, {r5, r8, sl, sp}^
    19f0:	00000020 	andeq	r0, r0, r0, lsr #32
    19f4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    19f8:	5b5d432d 	blpl	17526b4 <wmt_core_func_ctrl_cmd+0x174f294>
    19fc:	73255d45 	teqvc	r5, #4416	; 0x1140
    1a00:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1a04:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1a08:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1a0c:	72203a65 	eorvc	r3, r0, #413696	; 0x65000
    1a10:	20646165 	rsbcs	r6, r4, r5, ror #2
    1a14:	45454c53 	strbmi	r4, [r5, #-3155]	; 0xfffff3ad
    1a18:	56455f50 			; <UNDEFINED> instruction: 0x56455f50
    1a1c:	61662054 	qdsubvs	r2, r4, r6
    1a20:	25286c69 	strcs	r6, [r8, #-3177]!	; 0xfffff397
    1a24:	6c202964 	stcvs	9, cr2, [r0], #-400	; 0xfffffe70
    1a28:	25286e65 	strcs	r6, [r8, #-3685]!	; 0xfffff19b
    1a2c:	25202c64 	strcs	r2, [r0, #-3172]!	; 0xfffff39c
    1a30:	00002964 	andeq	r2, r0, r4, ror #18
    1a34:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1a38:	5b5d432d 	blpl	17526f4 <wmt_core_func_ctrl_cmd+0x174f2d4>
    1a3c:	73255d45 	teqvc	r5, #4416	; 0x1140
    1a40:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1a44:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1a48:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1a4c:	63203a65 	teqvs	r0, #413696	; 0x65000
    1a50:	61706d6f 	cmnvs	r0, pc, ror #26
    1a54:	57206572 			; <UNDEFINED> instruction: 0x57206572
    1a58:	535f544d 	cmppl	pc, #1291845632	; 0x4d000000
    1a5c:	5045454c 	subpl	r4, r5, ip, asr #10
    1a60:	5456455f 	ldrbpl	r4, [r6], #-1375	; 0xfffffaa1
    1a64:	72726520 	rsbsvc	r6, r2, #32, 10	; 0x8000000
    1a68:	000a726f 	andeq	r7, sl, pc, ror #4
    1a6c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1a70:	5b5d432d 	blpl	175272c <wmt_core_func_ctrl_cmd+0x174f30c>
    1a74:	73255d45 	teqvc	r5, #4416	; 0x1140
    1a78:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1a7c:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1a80:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1a84:	72203a65 	eorvc	r3, r0, #413696	; 0x65000
    1a88:	64252878 	strtvs	r2, [r5], #-2168	; 0xfffff788
    1a8c:	255b3a29 	ldrbcs	r3, [fp, #-2601]	; 0xfffff5d7
    1a90:	2c583230 	lfmcs	f3, 2, [r8], {48}	; 0x30
    1a94:	58323025 	ldmdapl	r2!, {r0, r2, r5, ip, sp}
    1a98:	3230252c 	eorscc	r2, r0, #44, 10	; 0xb000000
    1a9c:	30252c58 	eorcc	r2, r5, r8, asr ip
    1aa0:	252c5832 	strcs	r5, [ip, #-2098]!	; 0xfffff7ce
    1aa4:	2c583230 	lfmcs	f3, 2, [r8], {48}	; 0x30
    1aa8:	58323025 	ldmdapl	r2!, {r0, r2, r5, ip, sp}
    1aac:	7865205d 	stmdavc	r5!, {r0, r2, r3, r4, r6, sp}^
    1ab0:	64252870 	strtvs	r2, [r5], #-2160	; 0xfffff790
    1ab4:	255b3a29 	ldrbcs	r3, [fp, #-2601]	; 0xfffff5d7
    1ab8:	2c583230 	lfmcs	f3, 2, [r8], {48}	; 0x30
    1abc:	58323025 	ldmdapl	r2!, {r0, r2, r5, ip, sp}
    1ac0:	3230252c 	eorscc	r2, r0, #44, 10	; 0xb000000
    1ac4:	30252c58 	eorcc	r2, r5, r8, asr ip
    1ac8:	252c5832 	strcs	r5, [ip, #-2098]!	; 0xfffff7ce
    1acc:	2c583230 	lfmcs	f3, 2, [r8], {48}	; 0x30
    1ad0:	58323025 	ldmdapl	r2!, {r0, r2, r5, ip, sp}
    1ad4:	00000a5d 	andeq	r0, r0, sp, asr sl
    1ad8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1adc:	5b5d432d 	blpl	1752798 <wmt_core_func_ctrl_cmd+0x174f378>
    1ae0:	73255d49 	teqvc	r5, #4672	; 0x1240
    1ae4:	6e65533a 	mcrvs	3, 3, r5, cr5, cr10, {1}
    1ae8:	6c732064 	ldclvs	0, cr2, [r3], #-400	; 0xfffffe70
    1aec:	20706565 	rsbscs	r6, r0, r5, ror #10
    1af0:	6d6d6f63 	stclvs	15, cr6, [sp, #-396]!	; 0xfffffe74
    1af4:	20646e61 	rsbcs	r6, r4, r1, ror #28
    1af8:	0a214b4f 	beq	85483c <wmt_core_func_ctrl_cmd+0x85141c>
    1afc:	00000000 	andeq	r0, r0, r0
    1b00:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1b04:	5b5d432d 	blpl	17527c0 <wmt_core_func_ctrl_cmd+0x174f3a0>
    1b08:	73255d44 	teqvc	r5, #68, 26	; 0x1100
    1b0c:	2a2a2a3a 	bcs	a8c3fc <wmt_core_func_ctrl_cmd+0xa88fdc>
    1b10:	6553202a 	ldrbvs	r2, [r3, #-42]	; 0xffffffd6
    1b14:	7720646e 	strvc	r6, [r0, -lr, ror #8]!
    1b18:	75656b61 	strbvc	r6, [r5, #-2913]!	; 0xfffff49f
    1b1c:	6f632070 	svcvs	0x00632070
    1b20:	6e616d6d 	cdpvs	13, 6, cr6, cr1, cr13, {3}
    1b24:	00000a64 	andeq	r0, r0, r4, ror #20
    1b28:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1b2c:	5b5d432d 	blpl	17527e8 <wmt_core_func_ctrl_cmd+0x174f3c8>
    1b30:	73255d45 	teqvc	r5, #4416	; 0x1140
    1b34:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1b38:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1b3c:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1b40:	57203a65 	strpl	r3, [r0, -r5, ror #20]!
    1b44:	55454b41 	strbpl	r4, [r5, #-2881]	; 0xfffff4bf
    1b48:	4d435f50 	stclmi	15, cr5, [r3, #-320]	; 0xfffffec0
    1b4c:	65722044 	ldrbvs	r2, [r2, #-68]!	; 0xffffffbc
    1b50:	64252874 	strtvs	r2, [r5], #-2164	; 0xfffff78c
    1b54:	6d632029 	stclvs	0, cr2, [r3, #-164]!	; 0xffffff5c
    1b58:	656c2064 	strbvs	r2, [ip, #-100]!	; 0xffffff9c
    1b5c:	7265206e 	rsbvc	r2, r5, #110	; 0x6e
    1b60:	64252872 	strtvs	r2, [r5], #-2162	; 0xfffff78e
    1b64:	6425202c 	strtvs	r2, [r5], #-44	; 0xffffffd4
    1b68:	00002029 	andeq	r2, r0, r9, lsr #32
    1b6c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1b70:	5b5d432d 	blpl	175282c <wmt_core_func_ctrl_cmd+0x174f40c>
    1b74:	73255d45 	teqvc	r5, #4416	; 0x1140
    1b78:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1b7c:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1b80:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1b84:	72203a65 	eorvc	r3, r0, #413696	; 0x65000
    1b88:	20646165 	rsbcs	r6, r4, r5, ror #2
    1b8c:	454b4157 	strbmi	r4, [fp, #-343]	; 0xfffffea9
    1b90:	455f5055 	ldrbmi	r5, [pc, #-85]	; 1b43 <.rodata.str1.4+0x1b43>
    1b94:	66205456 			; <UNDEFINED> instruction: 0x66205456
    1b98:	286c6961 	stmdacs	ip!, {r0, r5, r6, r8, fp, sp, lr}^
    1b9c:	20296425 	eorcs	r6, r9, r5, lsr #8
    1ba0:	286e656c 	stmdacs	lr!, {r2, r3, r5, r6, r8, sl, sp, lr}^
    1ba4:	202c6425 	eorcs	r6, ip, r5, lsr #8
    1ba8:	00296425 	eoreq	r6, r9, r5, lsr #8
    1bac:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1bb0:	5b5d432d 	blpl	175286c <wmt_core_func_ctrl_cmd+0x174f44c>
    1bb4:	73255d45 	teqvc	r5, #4416	; 0x1140
    1bb8:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1bbc:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1bc0:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1bc4:	63203a65 	teqvs	r0, #413696	; 0x65000
    1bc8:	61706d6f 	cmnvs	r0, pc, ror #26
    1bcc:	57206572 			; <UNDEFINED> instruction: 0x57206572
    1bd0:	575f544d 	ldrbpl	r5, [pc, -sp, asr #8]
    1bd4:	55454b41 	strbpl	r4, [r5, #-2881]	; 0xfffff4bf
    1bd8:	56455f50 			; <UNDEFINED> instruction: 0x56455f50
    1bdc:	72652054 	rsbvc	r2, r5, #84	; 0x54
    1be0:	0a726f72 	beq	1c9d9b0 <wmt_core_func_ctrl_cmd+0x1c9a590>
    1be4:	00000000 	andeq	r0, r0, r0
    1be8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1bec:	5b5d432d 	blpl	17528a8 <wmt_core_func_ctrl_cmd+0x174f488>
    1bf0:	73255d49 	teqvc	r5, #4672	; 0x1240
    1bf4:	6e65533a 	mcrvs	3, 3, r5, cr5, cr10, {1}
    1bf8:	61772064 	cmnvs	r7, r4, rrx
    1bfc:	7075656b 	rsbsvc	r6, r5, fp, ror #10
    1c00:	6d6f6320 	stclvs	3, cr6, [pc, #-128]!	; 1b88 <.rodata.str1.4+0x1b88>
    1c04:	646e616d 	strbtvs	r6, [lr], #-365	; 0xfffffe93
    1c08:	214b4f20 	cmpcs	fp, r0, lsr #30
    1c0c:	0000000a 	andeq	r0, r0, sl
    1c10:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1c14:	5b5d432d 	blpl	17528d0 <wmt_core_func_ctrl_cmd+0x174f4b0>
    1c18:	73255d44 	teqvc	r5, #68, 26	; 0x1100
    1c1c:	2a2a2a3a 	bcs	a8c50c <wmt_core_func_ctrl_cmd+0xa890ec>
    1c20:	6553202a 	ldrbvs	r2, [r3, #-42]	; 0xffffffd6
    1c24:	6820646e 	stmdavs	r0!, {r1, r2, r3, r5, r6, sl, sp, lr}
    1c28:	2074736f 	rsbscs	r7, r4, pc, ror #6
    1c2c:	6b617761 	blvs	185f9b8 <wmt_core_func_ctrl_cmd+0x185c598>
    1c30:	6f632065 	svcvs	0x00632065
    1c34:	6e616d6d 	cdpvs	13, 6, cr6, cr1, cr13, {3}
    1c38:	00000a64 	andeq	r0, r0, r4, ror #20
    1c3c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1c40:	5b5d432d 	blpl	17528fc <wmt_core_func_ctrl_cmd+0x174f4dc>
    1c44:	73255d45 	teqvc	r5, #4416	; 0x1140
    1c48:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1c4c:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1c50:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1c54:	48203a65 	stmdami	r0!, {r0, r2, r5, r6, r9, fp, ip, sp}
    1c58:	5f54534f 	svcpl	0x0054534f
    1c5c:	4b415741 	blmi	1057968 <wmt_core_func_ctrl_cmd+0x1054548>
    1c60:	4d435f45 	stclmi	15, cr5, [r3, #-276]	; 0xfffffeec
    1c64:	65722044 	ldrbvs	r2, [r2, #-68]!	; 0xffffffbc
    1c68:	64252874 	strtvs	r2, [r5], #-2164	; 0xfffff78c
    1c6c:	6d632029 	stclvs	0, cr2, [r3, #-164]!	; 0xffffff5c
    1c70:	656c2064 	strbvs	r2, [ip, #-100]!	; 0xffffff9c
    1c74:	7265206e 	rsbvc	r2, r5, #110	; 0x6e
    1c78:	64252872 	strtvs	r2, [r5], #-2162	; 0xfffff78e
    1c7c:	6425202c 	strtvs	r2, [r5], #-44	; 0xffffffd4
    1c80:	00002029 	andeq	r2, r0, r9, lsr #32
    1c84:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1c88:	5b5d432d 	blpl	1752944 <wmt_core_func_ctrl_cmd+0x174f524>
    1c8c:	73255d45 	teqvc	r5, #4416	; 0x1140
    1c90:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1c94:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1c98:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1c9c:	72203a65 	eorvc	r3, r0, #413696	; 0x65000
    1ca0:	20646165 	rsbcs	r6, r4, r5, ror #2
    1ca4:	54534f48 	ldrbpl	r4, [r3], #-3912	; 0xfffff0b8
    1ca8:	4157415f 	cmpmi	r7, pc, asr r1
    1cac:	455f454b 	ldrbmi	r4, [pc, #-1355]	; 1769 <.rodata.str1.4+0x1769>
    1cb0:	66205456 			; <UNDEFINED> instruction: 0x66205456
    1cb4:	286c6961 	stmdacs	ip!, {r0, r5, r6, r8, fp, sp, lr}^
    1cb8:	20296425 	eorcs	r6, r9, r5, lsr #8
    1cbc:	286e656c 	stmdacs	lr!, {r2, r3, r5, r6, r8, sl, sp, lr}^
    1cc0:	202c6425 	eorcs	r6, ip, r5, lsr #8
    1cc4:	00296425 	eoreq	r6, r9, r5, lsr #8
    1cc8:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1ccc:	5b5d432d 	blpl	1752988 <wmt_core_func_ctrl_cmd+0x174f568>
    1cd0:	73255d45 	teqvc	r5, #4416	; 0x1140
    1cd4:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1cd8:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1cdc:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1ce0:	63203a65 	teqvs	r0, #413696	; 0x65000
    1ce4:	61706d6f 	cmnvs	r0, pc, ror #26
    1ce8:	57206572 			; <UNDEFINED> instruction: 0x57206572
    1cec:	485f544d 	ldmdami	pc, {r0, r2, r3, r6, sl, ip, lr}^	; <UNPREDICTABLE>
    1cf0:	5f54534f 	svcpl	0x0054534f
    1cf4:	4b415741 	blmi	1057a00 <wmt_core_func_ctrl_cmd+0x10545e0>
    1cf8:	56455f45 	strbpl	r5, [r5], -r5, asr #30
    1cfc:	72652054 	rsbvc	r2, r5, #84	; 0x54
    1d00:	0a726f72 	beq	1c9dad0 <wmt_core_func_ctrl_cmd+0x1c9a6b0>
    1d04:	00000000 	andeq	r0, r0, r0
    1d08:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1d0c:	5b5d432d 	blpl	17529c8 <wmt_core_func_ctrl_cmd+0x174f5a8>
    1d10:	73255d49 	teqvc	r5, #4672	; 0x1240
    1d14:	6e65533a 	mcrvs	3, 3, r5, cr5, cr10, {1}
    1d18:	6f682064 	svcvs	0x00682064
    1d1c:	61207473 	teqvs	r0, r3, ror r4
    1d20:	656b6177 	strbvs	r6, [fp, #-375]!	; 0xfffffe89
    1d24:	6d6f6320 	stclvs	3, cr6, [pc, #-128]!	; 1cac <.rodata.str1.4+0x1cac>
    1d28:	646e616d 	strbtvs	r6, [lr], #-365	; 0xfffffe93
    1d2c:	214b4f20 	cmpcs	fp, r0, lsr #30
    1d30:	0000000a 	andeq	r0, r0, sl
    1d34:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1d38:	5b5d432d 	blpl	17529f4 <wmt_core_func_ctrl_cmd+0x174f5d4>
    1d3c:	73255d44 	teqvc	r5, #68, 26	; 0x1100
    1d40:	206f443a 	rsbcs	r4, pc, sl, lsr r4	; <UNPREDICTABLE>
    1d44:	2d505453 	cfldrdcs	mvd5, [r0, #-332]	; 0xfffffeb4
    1d48:	20214243 	eorcs	r4, r1, r3, asr #4
    1d4c:	25206425 	strcs	r6, [r0, #-1061]!	; 0xfffffbdb
    1d50:	00000a70 	andeq	r0, r0, r0, ror sl
    1d54:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1d58:	5b5d432d 	blpl	1752a14 <wmt_core_func_ctrl_cmd+0x174f5f4>
    1d5c:	73255d45 	teqvc	r5, #4416	; 0x1140
    1d60:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1d64:	7461663a 	strbtvc	r6, [r1], #-1594	; 0xfffff9c6
    1d68:	65206c61 	strvs	r6, [r0, #-3169]!	; 0xfffff39f
    1d6c:	726f7272 	rsbvc	r7, pc, #536870919	; 0x20000007
    1d70:	21212120 	teqcs	r1, r0, lsr #2
    1d74:	7370202c 	cmnvc	r0, #44	; 0x2c
    1d78:	62635f6d 	rsbvs	r5, r3, #436	; 0x1b4
    1d7c:	25203d20 	strcs	r3, [r0, #-3360]!	; 0xfffff2e0
    1d80:	67202c70 			; <UNDEFINED> instruction: 0x67202c70
    1d84:	202c646f 	eorcs	r6, ip, pc, ror #8
    1d88:	656d6f73 	strbvs	r6, [sp, #-3955]!	; 0xfffff08d
    1d8c:	20656e6f 	rsbcs	r6, r5, pc, ror #28
    1d90:	7473756d 	ldrbtvc	r7, [r3], #-1389	; 0xfffffa93
    1d94:	76616820 	strbtvc	r6, [r1], -r0, lsr #16
    1d98:	6f632065 	svcvs	0x00632065
    1d9c:	70757272 	rsbsvc	r7, r5, r2, ror r2
    1da0:	20646574 	rsbcs	r6, r4, r4, ror r5
    1da4:	2072756f 	rsbscs	r7, r2, pc, ror #10
    1da8:	6f6d656d 	svcvs	0x006d656d
    1dac:	0a2e7972 	beq	ba037c <wmt_core_func_ctrl_cmd+0xb9cf5c>
    1db0:	00000000 	andeq	r0, r0, r0
    1db4:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1db8:	5b5d432d 	blpl	1752a74 <wmt_core_func_ctrl_cmd+0x174f654>
    1dbc:	73255d45 	teqvc	r5, #4416	; 0x1140
    1dc0:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1dc4:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1dc8:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1dcc:	78745f65 	ldmdavc	r4!, {r0, r2, r5, r6, r8, r9, sl, fp, ip, lr}^
    1dd0:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
    1dd4:	2864656c 	stmdacs	r4!, {r2, r3, r5, r6, r8, sl, sp, lr}^
    1dd8:	20296425 	eorcs	r6, r9, r5, lsr #8
    1ddc:	0000000a 	andeq	r0, r0, sl
    1de0:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1de4:	5b5d432d 	blpl	1752aa0 <wmt_core_func_ctrl_cmd+0x174f680>
    1de8:	73255d45 	teqvc	r5, #4416	; 0x1140
    1dec:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1df0:	746d773a 	strbtvc	r7, [sp], #-1850	; 0xfffff8c6
    1df4:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1df8:	78725f65 	ldmdavc	r2!, {r0, r2, r5, r6, r8, r9, sl, fp, ip, lr}^
    1dfc:	69616620 	stmdbvs	r1!, {r5, r9, sl, sp, lr}^
    1e00:	2864656c 	stmdacs	r4!, {r2, r3, r5, r6, r8, sl, sp, lr}^
    1e04:	0a296425 	beq	a5aea0 <wmt_core_func_ctrl_cmd+0xa57a80>
    1e08:	00000000 	andeq	r0, r0, r0
    1e0c:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1e10:	5b5d432d 	blpl	1752acc <wmt_core_func_ctrl_cmd+0x174f6ac>
    1e14:	73255d45 	teqvc	r5, #4416	; 0x1140
    1e18:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1e1c:	544b503a 	strbpl	r5, [fp], #-58	; 0xffffffc6
    1e20:	5059545f 	subspl	r5, r9, pc, asr r4
    1e24:	56455f45 	strbpl	r5, [r5], -r5, asr #30
    1e28:	20544e45 	subscs	r4, r4, r5, asr #28
    1e2c:	72203d21 	eorvc	r3, r0, #2112	; 0x840
    1e30:	50746d57 	rsbspl	r6, r4, r7, asr sp
    1e34:	7645746b 	strbvc	r7, [r5], -fp, ror #8
    1e38:	2e746e65 	cdpcs	14, 7, cr6, cr4, cr5, {3}
    1e3c:	70795465 	rsbsvc	r5, r9, r5, ror #8
    1e40:	64252865 	strtvs	r2, [r5], #-2149	; 0xfffff79b
    1e44:	00000a29 	andeq	r0, r0, r9, lsr #20
    1e48:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1e4c:	5b5d432d 	blpl	1752b08 <wmt_core_func_ctrl_cmd+0x174f6e8>
    1e50:	73255d45 	teqvc	r5, #4416	; 0x1140
    1e54:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1e58:	6d57723a 	lfmvs	f7, 2, [r7, #-232]	; 0xffffff18
    1e5c:	746b5074 	strbtvc	r5, [fp], #-116	; 0xffffff8c
    1e60:	2e646d43 	cdpcs	13, 6, cr6, cr4, cr3, {2}
    1e64:	43704f65 	cmnmi	r0, #404	; 0x194
    1e68:	2865646f 	stmdacs	r5!, {r0, r1, r2, r3, r5, r6, sl, sp, lr}^
    1e6c:	78257830 	stmdavc	r5!, {r4, r5, fp, ip, sp, lr}
    1e70:	3d212029 	stccc	0, cr2, [r1, #-164]!	; 0xffffff5c
    1e74:	6d577220 	lfmvs	f7, 2, [r7, #-128]	; 0xffffff80
    1e78:	746b5074 	strbtvc	r5, [fp], #-116	; 0xffffff8c
    1e7c:	6e657645 	cdpvs	6, 6, cr7, cr5, cr5, {2}
    1e80:	54652e74 	strbtpl	r2, [r5], #-3700	; 0xfffff18c
    1e84:	28657079 	stmdacs	r5!, {r0, r3, r4, r5, r6, ip, sp, lr}^
    1e88:	78257830 	stmdavc	r5!, {r4, r5, fp, ip, sp, lr}
    1e8c:	00000a29 	andeq	r0, r0, r9, lsr #20
    1e90:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1e94:	5b5d432d 	blpl	1752b50 <wmt_core_func_ctrl_cmd+0x174f730>
    1e98:	73255d45 	teqvc	r5, #4416	; 0x1140
    1e9c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1ea0:	5734753a 			; <UNDEFINED> instruction: 0x5734753a
    1ea4:	7645746d 	strbvc	r7, [r5], -sp, ror #8
    1ea8:	50746e65 	rsbspl	r6, r4, r5, ror #28
    1eac:	654c7564 	strbvs	r7, [ip, #-1380]	; 0xfffffa9c
    1eb0:	7830286e 	ldmdavc	r0!, {r1, r2, r3, r5, r6, fp, sp}
    1eb4:	20297825 	eorcs	r7, r9, r5, lsr #16
    1eb8:	72203d21 	eorvc	r3, r0, #2112	; 0x840
    1ebc:	50746d57 	rsbspl	r6, r4, r7, asr sp
    1ec0:	7645746b 	strbvc	r7, [r5], -fp, ror #8
    1ec4:	2e746e65 	cdpcs	14, 7, cr6, cr4, cr5, {3}
    1ec8:	64533275 	ldrbvs	r3, [r3], #-629	; 0xfffffd8b
    1ecc:	6e654c75 	mcrvs	12, 3, r4, cr5, cr5, {3}
    1ed0:	25783028 	ldrbcs	r3, [r8, #-40]!	; 0xffffffd8
    1ed4:	342b2978 	strtcc	r2, [fp], #-2424	; 0xfffff688
    1ed8:	0000000a 	andeq	r0, r0, sl
    1edc:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1ee0:	5b5d432d 	blpl	1752b9c <wmt_core_func_ctrl_cmd+0x174f77c>
    1ee4:	73255d45 	teqvc	r5, #4416	; 0x1140
    1ee8:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1eec:	2120303a 	teqcs	r0, sl, lsr r0
    1ef0:	7473203d 	ldrbtvc	r2, [r3], #-61	; 0xffffffc3
    1ef4:	73757461 	cmnvc	r5, #1627389952	; 0x61000000
    1ef8:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1efc:	0000000a 	andeq	r0, r0, sl
    1f00:	544d575b 	strbpl	r5, [sp], #-1883	; 0xfffff8a5
    1f04:	5b5d432d 	blpl	1752bc0 <wmt_core_func_ctrl_cmd+0x174f7a0>
    1f08:	73255d45 	teqvc	r5, #4416	; 0x1140
    1f0c:	29642528 	stmdbcs	r4!, {r3, r5, r8, sl, sp}^
    1f10:	4941463a 	stmdbmi	r1, {r1, r3, r4, r5, r9, sl, lr}^
    1f14:	7830284c 	ldmdavc	r0!, {r2, r3, r6, fp, sp}
    1f18:	0a297825 	beq	a5ffb4 <wmt_core_func_ctrl_cmd+0xa5cb94>
    1f1c:	00000000 	andeq	r0, r0, r0

Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	andeq	r0, r0, ip
   4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
   8:	7c010001 	stcvc	0, cr0, [r1], {1}
   c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  10:	00000020 	andeq	r0, r0, r0, lsr #32
	...
  1c:	00000014 	andeq	r0, r0, r4, lsl r0
  20:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
  24:	11020e11 	tstne	r2, r1, lsl lr
  28:	0b11030d 	bleq	440c64 <wmt_core_func_ctrl_cmd+0x43d844>
  2c:	0b0c4404 	bleq	311044 <wmt_core_func_ctrl_cmd+0x30dc24>
  30:	00000004 	andeq	r0, r0, r4
  34:	00000020 	andeq	r0, r0, r0, lsr #32
  38:	00000000 	andeq	r0, r0, r0
  3c:	00000014 	andeq	r0, r0, r4, lsl r0
  40:	00000050 	andeq	r0, r0, r0, asr r0
  44:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
  48:	11020e11 	tstne	r2, r1, lsl lr
  4c:	0b11030d 	bleq	440c88 <wmt_core_func_ctrl_cmd+0x43d868>
  50:	0b0c4404 	bleq	311068 <wmt_core_func_ctrl_cmd+0x30dc48>
  54:	00000004 	andeq	r0, r0, r4
  58:	00000020 	andeq	r0, r0, r0, lsr #32
  5c:	00000000 	andeq	r0, r0, r0
  60:	00000064 	andeq	r0, r0, r4, rrx
  64:	0000004c 	andeq	r0, r0, ip, asr #32
  68:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
  6c:	11020e11 	tstne	r2, r1, lsl lr
  70:	0b11030d 	bleq	440cac <wmt_core_func_ctrl_cmd+0x43d88c>
  74:	0b0c4404 	bleq	31108c <wmt_core_func_ctrl_cmd+0x30dc6c>
  78:	00000004 	andeq	r0, r0, r4
  7c:	00000020 	andeq	r0, r0, r0, lsr #32
  80:	00000000 	andeq	r0, r0, r0
  84:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  88:	00000064 	andeq	r0, r0, r4, rrx
  8c:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
  90:	11020e11 	tstne	r2, r1, lsl lr
  94:	0b11030d 	bleq	440cd0 <wmt_core_func_ctrl_cmd+0x43d8b0>
  98:	0b0c4404 	bleq	3110b0 <wmt_core_func_ctrl_cmd+0x30dc90>
  9c:	00000004 	andeq	r0, r0, r4
  a0:	00000020 	andeq	r0, r0, r0, lsr #32
  a4:	00000000 	andeq	r0, r0, r0
  a8:	00000114 	andeq	r0, r0, r4, lsl r1
  ac:	00000028 	andeq	r0, r0, r8, lsr #32
  b0:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
  b4:	11020e11 	tstne	r2, r1, lsl lr
  b8:	0b11030d 	bleq	440cf4 <wmt_core_func_ctrl_cmd+0x43d8d4>
  bc:	0b0c4404 	bleq	3110d4 <wmt_core_func_ctrl_cmd+0x30dcb4>
  c0:	00000004 	andeq	r0, r0, r4
  c4:	00000020 	andeq	r0, r0, r0, lsr #32
  c8:	00000000 	andeq	r0, r0, r0
  cc:	0000013c 	andeq	r0, r0, ip, lsr r1
  d0:	00000040 	andeq	r0, r0, r0, asr #32
  d4:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
  d8:	11020e11 	tstne	r2, r1, lsl lr
  dc:	0b11030d 	bleq	440d18 <wmt_core_func_ctrl_cmd+0x43d8f8>
  e0:	0b0c4404 	bleq	3110f8 <wmt_core_func_ctrl_cmd+0x30dcd8>
  e4:	00000004 	andeq	r0, r0, r4
  e8:	0000002c 	andeq	r0, r0, ip, lsr #32
  ec:	00000000 	andeq	r0, r0, r0
  f0:	0000017c 	andeq	r0, r0, ip, ror r1
  f4:	000000d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
  f8:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
  fc:	11020e11 	tstne	r2, r1, lsl lr
 100:	0b11030d 	bleq	440d3c <wmt_core_func_ctrl_cmd+0x43d91c>
 104:	05071104 	streq	r1, [r7, #-260]	; 0xfffffefc
 108:	11060611 	tstne	r6, r1, lsl r6
 10c:	04110705 	ldreq	r0, [r1], #-1797	; 0xfffff8fb
 110:	0b0c4408 	bleq	311138 <wmt_core_func_ctrl_cmd+0x30dd18>
 114:	00000004 	andeq	r0, r0, r4
 118:	0000002c 	andeq	r0, r0, ip, lsr #32
 11c:	00000000 	andeq	r0, r0, r0
 120:	0000024c 	andeq	r0, r0, ip, asr #4
 124:	000000cc 	andeq	r0, r0, ip, asr #1
 128:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 12c:	11020e11 	tstne	r2, r1, lsl lr
 130:	0b11030d 	bleq	440d6c <wmt_core_func_ctrl_cmd+0x43d94c>
 134:	05071104 	streq	r1, [r7, #-260]	; 0xfffffefc
 138:	11060611 	tstne	r6, r1, lsl r6
 13c:	04110705 	ldreq	r0, [r1], #-1797	; 0xfffff8fb
 140:	0b0c4408 	bleq	311168 <wmt_core_func_ctrl_cmd+0x30dd48>
 144:	00000004 	andeq	r0, r0, r4
 148:	00000024 	andeq	r0, r0, r4, lsr #32
 14c:	00000000 	andeq	r0, r0, r0
 150:	00000318 	andeq	r0, r0, r8, lsl r3
 154:	000000d8 	ldrdeq	r0, [r0], -r8
 158:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 15c:	11020e11 	tstne	r2, r1, lsl lr
 160:	0b11030d 	bleq	440d9c <wmt_core_func_ctrl_cmd+0x43d97c>
 164:	05051104 	streq	r1, [r5, #-260]	; 0xfffffefc
 168:	44060411 	strmi	r0, [r6], #-1041	; 0xfffffbef
 16c:	00040b0c 	andeq	r0, r4, ip, lsl #22
 170:	00000030 	andeq	r0, r0, r0, lsr r0
 174:	00000000 	andeq	r0, r0, r0
 178:	000003f0 	strdeq	r0, [r0], -r0	; <UNPREDICTABLE>
 17c:	000000bc 	strheq	r0, [r0], -ip
 180:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 184:	11020e11 	tstne	r2, r1, lsl lr
 188:	0b11030d 	bleq	440dc4 <wmt_core_func_ctrl_cmd+0x43d9a4>
 18c:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 190:	11060811 	tstne	r6, r1, lsl r8
 194:	06110707 	ldreq	r0, [r1], -r7, lsl #14
 198:	09051108 	stmdbeq	r5, {r3, r8, ip}
 19c:	440a0411 	strmi	r0, [sl], #-1041	; 0xfffffbef
 1a0:	00040b0c 	andeq	r0, r4, ip, lsl #22
 1a4:	00000034 	andeq	r0, r0, r4, lsr r0
 1a8:	00000000 	andeq	r0, r0, r0
 1ac:	000004ac 	andeq	r0, r0, ip, lsr #9
 1b0:	00000394 	muleq	r0, r4, r3
 1b4:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 1b8:	11020e11 	tstne	r2, r1, lsl lr
 1bc:	0b11030d 	bleq	440df8 <wmt_core_func_ctrl_cmd+0x43d9d8>
 1c0:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 1c4:	11060911 	tstne	r6, r1, lsl r9
 1c8:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 1cc:	09061108 	stmdbeq	r6, {r3, r8, ip}
 1d0:	110a0511 	tstne	sl, r1, lsl r5
 1d4:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 1d8:	0000040b 	andeq	r0, r0, fp, lsl #8
 1dc:	00000020 	andeq	r0, r0, r0, lsr #32
 1e0:	00000000 	andeq	r0, r0, r0
 1e4:	00000840 	andeq	r0, r0, r0, asr #16
 1e8:	00000074 	andeq	r0, r0, r4, ror r0
 1ec:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 1f0:	11020e11 	tstne	r2, r1, lsl lr
 1f4:	0b11030d 	bleq	440e30 <wmt_core_func_ctrl_cmd+0x43da10>
 1f8:	05041104 	streq	r1, [r4, #-260]	; 0xfffffefc
 1fc:	040b0c44 	streq	r0, [fp], #-3140	; 0xfffff3bc
 200:	00000020 	andeq	r0, r0, r0, lsr #32
 204:	00000000 	andeq	r0, r0, r0
 208:	000008b4 			; <UNDEFINED> instruction: 0x000008b4
 20c:	00000080 	andeq	r0, r0, r0, lsl #1
 210:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 214:	11020e11 	tstne	r2, r1, lsl lr
 218:	0b11030d 	bleq	440e54 <wmt_core_func_ctrl_cmd+0x43da34>
 21c:	05041104 	streq	r1, [r4, #-260]	; 0xfffffefc
 220:	040b0c44 	streq	r0, [fp], #-3140	; 0xfffff3bc
 224:	00000020 	andeq	r0, r0, r0, lsr #32
 228:	00000000 	andeq	r0, r0, r0
 22c:	00000934 	andeq	r0, r0, r4, lsr r9
 230:	000000c8 	andeq	r0, r0, r8, asr #1
 234:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 238:	11020e11 	tstne	r2, r1, lsl lr
 23c:	0b11030d 	bleq	440e78 <wmt_core_func_ctrl_cmd+0x43da58>
 240:	05041104 	streq	r1, [r4, #-260]	; 0xfffffefc
 244:	040b0c44 	streq	r0, [fp], #-3140	; 0xfffff3bc
 248:	00000020 	andeq	r0, r0, r0, lsr #32
 24c:	00000000 	andeq	r0, r0, r0
 250:	000009fc 	strdeq	r0, [r0], -ip
 254:	0000003c 	andeq	r0, r0, ip, lsr r0
 258:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 25c:	11020e11 	tstne	r2, r1, lsl lr
 260:	0b11030d 	bleq	440e9c <wmt_core_func_ctrl_cmd+0x43da7c>
 264:	0b0c4404 	bleq	31127c <wmt_core_func_ctrl_cmd+0x30de5c>
 268:	00000004 	andeq	r0, r0, r4
 26c:	00000034 	andeq	r0, r0, r4, lsr r0
 270:	00000000 	andeq	r0, r0, r0
 274:	00000a38 	andeq	r0, r0, r8, lsr sl
 278:	00000234 	andeq	r0, r0, r4, lsr r2
 27c:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 280:	11020e11 	tstne	r2, r1, lsl lr
 284:	0b11030d 	bleq	440ec0 <wmt_core_func_ctrl_cmd+0x43daa0>
 288:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 28c:	11060911 	tstne	r6, r1, lsl r9
 290:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 294:	09061108 	stmdbeq	r6, {r3, r8, ip}
 298:	110a0511 	tstne	sl, r1, lsl r5
 29c:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 2a0:	0000040b 	andeq	r0, r0, fp, lsl #8
 2a4:	00000028 	andeq	r0, r0, r8, lsr #32
 2a8:	00000000 	andeq	r0, r0, r0
 2ac:	00000c6c 	andeq	r0, r0, ip, ror #24
 2b0:	00000134 	andeq	r0, r0, r4, lsr r1
 2b4:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 2b8:	11020e11 	tstne	r2, r1, lsl lr
 2bc:	0b11030d 	bleq	440ef8 <wmt_core_func_ctrl_cmd+0x43dad8>
 2c0:	05061104 	streq	r1, [r6, #-260]	; 0xfffffefc
 2c4:	11060511 	tstne	r6, r1, lsl r5
 2c8:	0c440704 	mcrreq	7, 0, r0, r4, cr4
 2cc:	0000040b 	andeq	r0, r0, fp, lsl #8
 2d0:	00000034 	andeq	r0, r0, r4, lsr r0
 2d4:	00000000 	andeq	r0, r0, r0
 2d8:	00000da0 	andeq	r0, r0, r0, lsr #27
 2dc:	00000344 	andeq	r0, r0, r4, asr #6
 2e0:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 2e4:	11020e11 	tstne	r2, r1, lsl lr
 2e8:	0b11030d 	bleq	440f24 <wmt_core_func_ctrl_cmd+0x43db04>
 2ec:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 2f0:	11060911 	tstne	r6, r1, lsl r9
 2f4:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 2f8:	09061108 	stmdbeq	r6, {r3, r8, ip}
 2fc:	110a0511 	tstne	sl, r1, lsl r5
 300:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 304:	0000040b 	andeq	r0, r0, fp, lsl #8
 308:	00000020 	andeq	r0, r0, r0, lsr #32
 30c:	00000000 	andeq	r0, r0, r0
 310:	000010e4 	andeq	r1, r0, r4, ror #1
 314:	00000014 	andeq	r0, r0, r4, lsl r0
 318:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 31c:	11020e11 	tstne	r2, r1, lsl lr
 320:	0b11030d 	bleq	440f5c <wmt_core_func_ctrl_cmd+0x43db3c>
 324:	0b0c4404 	bleq	31133c <wmt_core_func_ctrl_cmd+0x30df1c>
 328:	00000004 	andeq	r0, r0, r4
 32c:	00000034 	andeq	r0, r0, r4, lsr r0
 330:	00000000 	andeq	r0, r0, r0
 334:	000010f8 	strdeq	r1, [r0], -r8
 338:	00000224 	andeq	r0, r0, r4, lsr #4
 33c:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 340:	11020e11 	tstne	r2, r1, lsl lr
 344:	0b11030d 	bleq	440f80 <wmt_core_func_ctrl_cmd+0x43db60>
 348:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 34c:	11060911 	tstne	r6, r1, lsl r9
 350:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 354:	09061108 	stmdbeq	r6, {r3, r8, ip}
 358:	110a0511 	tstne	sl, r1, lsl r5
 35c:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 360:	0000040b 	andeq	r0, r0, fp, lsl #8
 364:	00000030 	andeq	r0, r0, r0, lsr r0
 368:	00000000 	andeq	r0, r0, r0
 36c:	0000131c 	andeq	r1, r0, ip, lsl r3
 370:	000001e0 	andeq	r0, r0, r0, ror #3
 374:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 378:	11020e11 	tstne	r2, r1, lsl lr
 37c:	0b11030d 	bleq	440fb8 <wmt_core_func_ctrl_cmd+0x43db98>
 380:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 384:	11060811 	tstne	r6, r1, lsl r8
 388:	06110707 	ldreq	r0, [r1], -r7, lsl #14
 38c:	09051108 	stmdbeq	r5, {r3, r8, ip}
 390:	440a0411 	strmi	r0, [sl], #-1041	; 0xfffffbef
 394:	00040b0c 	andeq	r0, r4, ip, lsl #22
 398:	00000034 	andeq	r0, r0, r4, lsr r0
 39c:	00000000 	andeq	r0, r0, r0
 3a0:	000014fc 	strdeq	r1, [r0], -ip
 3a4:	00000694 	muleq	r0, r4, r6
 3a8:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 3ac:	11020e11 	tstne	r2, r1, lsl lr
 3b0:	0b11030d 	bleq	440fec <wmt_core_func_ctrl_cmd+0x43dbcc>
 3b4:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 3b8:	11060911 	tstne	r6, r1, lsl r9
 3bc:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 3c0:	09061108 	stmdbeq	r6, {r3, r8, ip}
 3c4:	110a0511 	tstne	sl, r1, lsl r5
 3c8:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 3cc:	0000040b 	andeq	r0, r0, fp, lsl #8
 3d0:	00000020 	andeq	r0, r0, r0, lsr #32
 3d4:	00000000 	andeq	r0, r0, r0
 3d8:	00001b90 	muleq	r0, r0, fp
 3dc:	00000014 	andeq	r0, r0, r4, lsl r0
 3e0:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 3e4:	11020e11 	tstne	r2, r1, lsl lr
 3e8:	0b11030d 	bleq	441024 <wmt_core_func_ctrl_cmd+0x43dc04>
 3ec:	0b0c4404 	bleq	311404 <wmt_core_func_ctrl_cmd+0x30dfe4>
 3f0:	00000004 	andeq	r0, r0, r4
 3f4:	00000034 	andeq	r0, r0, r4, lsr r0
 3f8:	00000000 	andeq	r0, r0, r0
 3fc:	00001ba4 	andeq	r1, r0, r4, lsr #23
 400:	000001e0 	andeq	r0, r0, r0, ror #3
 404:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 408:	11020e11 	tstne	r2, r1, lsl lr
 40c:	0b11030d 	bleq	441048 <wmt_core_func_ctrl_cmd+0x43dc28>
 410:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 414:	11060911 	tstne	r6, r1, lsl r9
 418:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 41c:	09061108 	stmdbeq	r6, {r3, r8, ip}
 420:	110a0511 	tstne	sl, r1, lsl r5
 424:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 428:	0000040b 	andeq	r0, r0, fp, lsl #8
 42c:	00000034 	andeq	r0, r0, r4, lsr r0
 430:	00000000 	andeq	r0, r0, r0
 434:	00001d84 	andeq	r1, r0, r4, lsl #27
 438:	00000464 	andeq	r0, r0, r4, ror #8
 43c:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 440:	11020e11 	tstne	r2, r1, lsl lr
 444:	0b11030d 	bleq	441080 <wmt_core_func_ctrl_cmd+0x43dc60>
 448:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 44c:	11060911 	tstne	r6, r1, lsl r9
 450:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 454:	09061108 	stmdbeq	r6, {r3, r8, ip}
 458:	110a0511 	tstne	sl, r1, lsl r5
 45c:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 460:	0000040b 	andeq	r0, r0, fp, lsl #8
 464:	00000020 	andeq	r0, r0, r0, lsr #32
 468:	00000000 	andeq	r0, r0, r0
 46c:	000021e8 	andeq	r2, r0, r8, ror #3
 470:	0000005c 	andeq	r0, r0, ip, asr r0
 474:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 478:	11020e11 	tstne	r2, r1, lsl lr
 47c:	0b11030d 	bleq	4410b8 <wmt_core_func_ctrl_cmd+0x43dc98>
 480:	0b0c4404 	bleq	311498 <wmt_core_func_ctrl_cmd+0x30e078>
 484:	00000004 	andeq	r0, r0, r4
 488:	0000002c 	andeq	r0, r0, ip, lsr #32
 48c:	00000000 	andeq	r0, r0, r0
 490:	00002244 	andeq	r2, r0, r4, asr #4
 494:	00000174 	andeq	r0, r0, r4, ror r1
 498:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 49c:	11020e11 	tstne	r2, r1, lsl lr
 4a0:	0b11030d 	bleq	4410dc <wmt_core_func_ctrl_cmd+0x43dcbc>
 4a4:	05081104 	streq	r1, [r8, #-260]	; 0xfffffefc
 4a8:	11060711 	tstne	r6, r1, lsl r7
 4ac:	05110706 	ldreq	r0, [r1, #-1798]	; 0xfffff8fa
 4b0:	09041108 	stmdbeq	r4, {r3, r8, ip}
 4b4:	040b0c44 	streq	r0, [fp], #-3140	; 0xfffff3bc
 4b8:	00000034 	andeq	r0, r0, r4, lsr r0
 4bc:	00000000 	andeq	r0, r0, r0
 4c0:	000023b8 			; <UNDEFINED> instruction: 0x000023b8
 4c4:	000002a0 	andeq	r0, r0, r0, lsr #5
 4c8:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 4cc:	11020e11 	tstne	r2, r1, lsl lr
 4d0:	0b11030d 	bleq	44110c <wmt_core_func_ctrl_cmd+0x43dcec>
 4d4:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 4d8:	11060911 	tstne	r6, r1, lsl r9
 4dc:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 4e0:	09061108 	stmdbeq	r6, {r3, r8, ip}
 4e4:	110a0511 	tstne	sl, r1, lsl r5
 4e8:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 4ec:	0000040b 	andeq	r0, r0, fp, lsl #8
 4f0:	00000034 	andeq	r0, r0, r4, lsr r0
 4f4:	00000000 	andeq	r0, r0, r0
 4f8:	00002658 	andeq	r2, r0, r8, asr r6
 4fc:	00000444 	andeq	r0, r0, r4, asr #8
 500:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 504:	11020e11 	tstne	r2, r1, lsl lr
 508:	0b11030d 	bleq	441144 <wmt_core_func_ctrl_cmd+0x43dd24>
 50c:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 510:	11060911 	tstne	r6, r1, lsl r9
 514:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 518:	09061108 	stmdbeq	r6, {r3, r8, ip}
 51c:	110a0511 	tstne	sl, r1, lsl r5
 520:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 524:	0000040b 	andeq	r0, r0, fp, lsl #8
 528:	00000034 	andeq	r0, r0, r4, lsr r0
 52c:	00000000 	andeq	r0, r0, r0
 530:	00002a9c 	muleq	r0, ip, sl
 534:	00000258 	andeq	r0, r0, r8, asr r2
 538:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 53c:	11020e11 	tstne	r2, r1, lsl lr
 540:	0b11030d 	bleq	44117c <wmt_core_func_ctrl_cmd+0x43dd5c>
 544:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 548:	11060911 	tstne	r6, r1, lsl r9
 54c:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 550:	09061108 	stmdbeq	r6, {r3, r8, ip}
 554:	110a0511 	tstne	sl, r1, lsl r5
 558:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 55c:	0000040b 	andeq	r0, r0, fp, lsl #8
 560:	00000034 	andeq	r0, r0, r4, lsr r0
 564:	00000000 	andeq	r0, r0, r0
 568:	00002cf4 	strdeq	r2, [r0], -r4
 56c:	000001c0 	andeq	r0, r0, r0, asr #3
 570:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 574:	11020e11 	tstne	r2, r1, lsl lr
 578:	0b11030d 	bleq	4411b4 <wmt_core_func_ctrl_cmd+0x43dd94>
 57c:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 580:	11060911 	tstne	r6, r1, lsl r9
 584:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 588:	09061108 	stmdbeq	r6, {r3, r8, ip}
 58c:	110a0511 	tstne	sl, r1, lsl r5
 590:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 594:	0000040b 	andeq	r0, r0, fp, lsl #8
 598:	00000034 	andeq	r0, r0, r4, lsr r0
 59c:	00000000 	andeq	r0, r0, r0
 5a0:	00002eb4 			; <UNDEFINED> instruction: 0x00002eb4
 5a4:	0000056c 	andeq	r0, r0, ip, ror #10
 5a8:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 5ac:	11020e11 	tstne	r2, r1, lsl lr
 5b0:	0b11030d 	bleq	4411ec <wmt_core_func_ctrl_cmd+0x43ddcc>
 5b4:	050a1104 	streq	r1, [sl, #-260]	; 0xfffffefc
 5b8:	11060911 	tstne	r6, r1, lsl r9
 5bc:	07110708 	ldreq	r0, [r1, -r8, lsl #14]
 5c0:	09061108 	stmdbeq	r6, {r3, r8, ip}
 5c4:	110a0511 	tstne	sl, r1, lsl r5
 5c8:	0c440b04 	mcrreq	11, 0, r0, r4, cr4
 5cc:	0000040b 	andeq	r0, r0, fp, lsl #8
 5d0:	0000002c 	andeq	r0, r0, ip, lsr #32
 5d4:	00000000 	andeq	r0, r0, r0
 5d8:	00003420 	andeq	r3, r0, r0, lsr #8
 5dc:	00000198 	muleq	r0, r8, r1
 5e0:	440c0d44 	strmi	r0, [ip], #-3396	; 0xfffff2bc
 5e4:	11020e11 	tstne	r2, r1, lsl lr
 5e8:	0b11030d 	bleq	441224 <wmt_core_func_ctrl_cmd+0x43de04>
 5ec:	05071104 	streq	r1, [r7, #-260]	; 0xfffffefc
 5f0:	11060611 	tstne	r6, r1, lsl r6
 5f4:	04110705 	ldreq	r0, [r1], #-1797	; 0xfffff8fb
 5f8:	0b0c4408 	bleq	311620 <wmt_core_func_ctrl_cmd+0x30e200>
 5fc:	00000004 	andeq	r0, r0, r4

Disassembly of section .debug_loc:

00000000 <.debug_loc>:
       0:	00000000 	andeq	r0, r0, r0
       4:	00000004 	andeq	r0, r0, r4
       8:	007d0002 	rsbseq	r0, sp, r2
       c:	00000004 	andeq	r0, r0, r4
      10:	0000000c 	andeq	r0, r0, ip
      14:	007c0002 	rsbseq	r0, ip, r2
      18:	0000000c 	andeq	r0, r0, ip
      1c:	00000014 	andeq	r0, r0, r4, lsl r0
      20:	047b0002 	ldrbteq	r0, [fp], #-2
	...
      30:	00000010 	andeq	r0, r0, r0, lsl r0
      34:	00500001 	subseq	r0, r0, r1
      38:	00000000 	andeq	r0, r0, r0
      3c:	14000000 	strne	r0, [r0], #-0
      40:	18000000 	stmdane	r0, {}	; <UNPREDICTABLE>
      44:	02000000 	andeq	r0, r0, #0
      48:	18007d00 	stmdane	r0, {r8, sl, fp, ip, sp, lr}
      4c:	20000000 	andcs	r0, r0, r0
      50:	02000000 	andeq	r0, r0, #0
      54:	20007c00 	andcs	r7, r0, r0, lsl #24
      58:	64000000 	strvs	r0, [r0], #-0
      5c:	02000000 	andeq	r0, r0, #0
      60:	00047b00 	andeq	r7, r4, r0, lsl #22
      64:	00000000 	andeq	r0, r0, r0
      68:	14000000 	strne	r0, [r0], #-0
      6c:	34000000 	strcc	r0, [r0], #-0
      70:	01000000 	mrseq	r0, (UNDEF: 0)
      74:	00345000 	eorseq	r5, r4, r0
      78:	00500000 	subseq	r0, r0, r0
      7c:	00010000 	andeq	r0, r1, r0
      80:	0000545c 	andeq	r5, r0, ip, asr r4
      84:	00006400 	andeq	r6, r0, r0, lsl #8
      88:	5c000100 	stfpls	f0, [r0], {-0}
	...
      94:	00000014 	andeq	r0, r0, r4, lsl r0
      98:	00000044 	andeq	r0, r0, r4, asr #32
      9c:	54510001 	ldrbpl	r0, [r1], #-1
      a0:	64000000 	strvs	r0, [r0], #-0
      a4:	01000000 	mrseq	r0, (UNDEF: 0)
      a8:	00005100 	andeq	r5, r0, r0, lsl #2
      ac:	00000000 	andeq	r0, r0, r0
      b0:	00640000 	rsbeq	r0, r4, r0
      b4:	00680000 	rsbeq	r0, r8, r0
      b8:	00020000 	andeq	r0, r2, r0
      bc:	0068007d 	rsbeq	r0, r8, sp, ror r0
      c0:	00700000 	rsbseq	r0, r0, r0
      c4:	00020000 	andeq	r0, r2, r0
      c8:	0070007c 	rsbseq	r0, r0, ip, ror r0
      cc:	00b00000 	adcseq	r0, r0, r0
      d0:	00020000 	andeq	r0, r2, r0
      d4:	0000047b 	andeq	r0, r0, fp, ror r4
      d8:	00000000 	andeq	r0, r0, r0
      dc:	00640000 	rsbeq	r0, r4, r0
      e0:	008c0000 	addeq	r0, ip, r0
      e4:	00010000 	andeq	r0, r1, r0
      e8:	00009050 	andeq	r9, r0, r0, asr r0
      ec:	00009c00 	andeq	r9, r0, r0, lsl #24
      f0:	50000100 	andpl	r0, r0, r0, lsl #2
	...
      fc:	00000074 	andeq	r0, r0, r4, ror r0
     100:	0000008c 	andeq	r0, r0, ip, lsl #1
     104:	90530001 	subsls	r0, r3, r1
     108:	a0000000 	andge	r0, r0, r0
     10c:	01000000 	mrseq	r0, (UNDEF: 0)
     110:	00005300 	andeq	r5, r0, r0, lsl #6
     114:	00000000 	andeq	r0, r0, r0
     118:	00a40000 	adceq	r0, r4, r0
     11c:	00a40000 	adceq	r0, r4, r0
     120:	00010000 	andeq	r0, r1, r0
     124:	00000050 	andeq	r0, r0, r0, asr r0
     128:	00000000 	andeq	r0, r0, r0
     12c:	0000b000 	andeq	fp, r0, r0
     130:	0000b400 	andeq	fp, r0, r0, lsl #8
     134:	7d000200 	sfmvc	f0, 4, [r0, #-0]
     138:	0000b400 	andeq	fp, r0, r0, lsl #8
     13c:	0000bc00 	andeq	fp, r0, r0, lsl #24
     140:	7c000200 	sfmvc	f0, 4, [r0], {-0}
     144:	0000bc00 	andeq	fp, r0, r0, lsl #24
     148:	00011400 	andeq	r1, r1, r0, lsl #8
     14c:	7b000200 	blvc	954 <.debug_loc+0x954>
     150:	00000004 	andeq	r0, r0, r4
     154:	00000000 	andeq	r0, r0, r0
     158:	0000b000 	andeq	fp, r0, r0
     15c:	0000c400 	andeq	ip, r0, r0, lsl #8
     160:	50000100 	andpl	r0, r0, r0, lsl #2
     164:	000000c4 	andeq	r0, r0, r4, asr #1
     168:	000000c8 	andeq	r0, r0, r8, asr #1
     16c:	c8530001 	ldmdagt	r3, {r0}^
     170:	d4000000 	strle	r0, [r0], #-0
     174:	01000000 	mrseq	r0, (UNDEF: 0)
     178:	00d85000 	sbcseq	r5, r8, r0
     17c:	00dc0000 	sbcseq	r0, ip, r0
     180:	00010000 	andeq	r0, r1, r0
     184:	0000f050 	andeq	pc, r0, r0, asr r0	; <UNPREDICTABLE>
     188:	00010000 	andeq	r0, r1, r0
     18c:	53000100 	movwpl	r0, #256	; 0x100
	...
     198:	00000114 	andeq	r0, r0, r4, lsl r1
     19c:	00000118 	andeq	r0, r0, r8, lsl r1
     1a0:	007d0002 	rsbseq	r0, sp, r2
     1a4:	00000118 	andeq	r0, r0, r8, lsl r1
     1a8:	00000120 	andeq	r0, r0, r0, lsr #2
     1ac:	007c0002 	rsbseq	r0, ip, r2
     1b0:	00000120 	andeq	r0, r0, r0, lsr #2
     1b4:	0000013c 	andeq	r0, r0, ip, lsr r1
     1b8:	047b0002 	ldrbteq	r0, [fp], #-2
	...
     1c4:	0000013c 	andeq	r0, r0, ip, lsr r1
     1c8:	00000140 	andeq	r0, r0, r0, asr #2
     1cc:	007d0002 	rsbseq	r0, sp, r2
     1d0:	00000140 	andeq	r0, r0, r0, asr #2
     1d4:	00000148 	andeq	r0, r0, r8, asr #2
     1d8:	007c0002 	rsbseq	r0, ip, r2
     1dc:	00000148 	andeq	r0, r0, r8, asr #2
     1e0:	0000017c 	andeq	r0, r0, ip, ror r1
     1e4:	047b0002 	ldrbteq	r0, [fp], #-2
	...
     1f0:	0000017c 	andeq	r0, r0, ip, ror r1
     1f4:	00000180 	andeq	r0, r0, r0, lsl #3
     1f8:	007d0002 	rsbseq	r0, sp, r2
     1fc:	00000180 	andeq	r0, r0, r0, lsl #3
     200:	00000188 	andeq	r0, r0, r8, lsl #3
     204:	007c0002 	rsbseq	r0, ip, r2
     208:	00000188 	andeq	r0, r0, r8, lsl #3
     20c:	0000024c 	andeq	r0, r0, ip, asr #4
     210:	047b0002 	ldrbteq	r0, [fp], #-2
	...
     21c:	0000017c 	andeq	r0, r0, ip, ror r1
     220:	000001a0 	andeq	r0, r0, r0, lsr #3
     224:	a0500001 	subsge	r0, r0, r1
     228:	4c000001 	stcmi	0, cr0, [r0], {1}
     22c:	01000002 	tsteq	r0, r2
     230:	00005600 	andeq	r5, r0, r0, lsl #12
     234:	00000000 	andeq	r0, r0, r0
     238:	017c0000 	cmneq	ip, r0
     23c:	01b00000 	movseq	r0, r0
     240:	00010000 	andeq	r0, r1, r0
     244:	0001b851 	andeq	fp, r1, r1, asr r8
     248:	0001cc00 	andeq	ip, r1, r0, lsl #24
     24c:	51000100 	mrspl	r0, (UNDEF: 16)
     250:	000001d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
     254:	000001e0 	andeq	r0, r0, r0, ror #3
     258:	f0510001 			; <UNDEFINED> instruction: 0xf0510001
     25c:	f8000001 			; <UNDEFINED> instruction: 0xf8000001
     260:	01000001 	tsteq	r0, r1
     264:	021c5100 	andseq	r5, ip, #0, 2
     268:	02280000 	eoreq	r0, r8, #0
     26c:	00010000 	andeq	r0, r1, r0
     270:	00000051 	andeq	r0, r0, r1, asr r0
     274:	00000000 	andeq	r0, r0, r0
     278:	00017c00 	andeq	r7, r1, r0, lsl #24
     27c:	0001a000 	andeq	sl, r1, r0
     280:	52000100 	andpl	r0, r0, #0, 2
     284:	000001a0 	andeq	r0, r0, r0, lsr #3
     288:	0000024c 	andeq	r0, r0, ip, asr #4
     28c:	00550001 	subseq	r0, r5, r1
     290:	00000000 	andeq	r0, r0, r0
     294:	4c000000 	stcmi	0, cr0, [r0], {-0}
     298:	50000002 	andpl	r0, r0, r2
     29c:	02000002 	andeq	r0, r0, #2
     2a0:	50007d00 	andpl	r7, r0, r0, lsl #26
     2a4:	58000002 	stmdapl	r0, {r1}
     2a8:	02000002 	andeq	r0, r0, #2
     2ac:	58007c00 	stmdapl	r0, {sl, fp, ip, sp, lr}
     2b0:	18000002 	stmdane	r0, {r1}
     2b4:	02000003 	andeq	r0, r0, #3
     2b8:	00047b00 	andeq	r7, r4, r0, lsl #22
     2bc:	00000000 	andeq	r0, r0, r0
     2c0:	4c000000 	stcmi	0, cr0, [r0], {-0}
     2c4:	a0000002 	andge	r0, r0, r2
     2c8:	01000002 	tsteq	r0, r2
     2cc:	02b85000 	adcseq	r5, r8, #0
     2d0:	02bc0000 	adcseq	r0, ip, #0
     2d4:	00010000 	andeq	r0, r1, r0
     2d8:	0002d050 	andeq	sp, r2, r0, asr r0
     2dc:	0002d400 	andeq	sp, r2, r0, lsl #8
     2e0:	50000100 	andpl	r0, r0, r0, lsl #2
     2e4:	000002e8 	andeq	r0, r0, r8, ror #5
     2e8:	000002ec 	andeq	r0, r0, ip, ror #5
     2ec:	00500001 	subseq	r0, r0, r1
     2f0:	00000000 	andeq	r0, r0, r0
     2f4:	c8000000 	stmdagt	r0, {}	; <UNPREDICTABLE>
     2f8:	c8000002 	stmdagt	r0, {r1}
     2fc:	01000002 	tsteq	r0, r2
     300:	02e45000 	rsceq	r5, r4, #0
     304:	02e80000 	rsceq	r0, r8, #0
     308:	00010000 	andeq	r0, r1, r0
     30c:	0002fc50 	andeq	pc, r2, r0, asr ip	; <UNPREDICTABLE>
     310:	00031800 	andeq	r1, r3, r0, lsl #16
     314:	50000100 	andpl	r0, r0, r0, lsl #2
	...
     320:	00000288 	andeq	r0, r0, r8, lsl #5
     324:	000002d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
     328:	00560001 	subseq	r0, r6, r1
     32c:	00000000 	andeq	r0, r0, r0
     330:	90000000 	andls	r0, r0, r0
     334:	d0000002 	andle	r0, r0, r2
     338:	01000002 	tsteq	r0, r2
     33c:	00005500 	andeq	r5, r0, r0, lsl #10
     340:	00000000 	andeq	r0, r0, r0
     344:	02840000 	addeq	r0, r4, #0
     348:	02d00000 	sbcseq	r0, r0, #0
     34c:	00010000 	andeq	r0, r1, r0
     350:	00000057 	andeq	r0, r0, r7, asr r0
     354:	00000000 	andeq	r0, r0, r0
     358:	00031800 	andeq	r1, r3, r0, lsl #16
     35c:	00031c00 	andeq	r1, r3, r0, lsl #24
     360:	7d000200 	sfmvc	f0, 4, [r0, #-0]
     364:	00031c00 	andeq	r1, r3, r0, lsl #24
     368:	00032400 	andeq	r2, r3, r0, lsl #8
     36c:	7c000200 	sfmvc	f0, 4, [r0], {-0}
     370:	00032400 	andeq	r2, r3, r0, lsl #8
     374:	0003f000 	andeq	pc, r3, r0
     378:	7b000200 	blvc	b80 <.debug_loc+0xb80>
     37c:	00000004 	andeq	r0, r0, r4
     380:	00000000 	andeq	r0, r0, r0
     384:	00031800 	andeq	r1, r3, r0, lsl #16
     388:	00033400 	andeq	r3, r3, r0, lsl #8
     38c:	50000100 	andpl	r0, r0, r0, lsl #2
     390:	00000334 	andeq	r0, r0, r4, lsr r3
     394:	000003f0 	strdeq	r0, [r0], -r0	; <UNPREDICTABLE>
     398:	00540001 	subseq	r0, r4, r1
     39c:	00000000 	andeq	r0, r0, r0
     3a0:	f0000000 			; <UNDEFINED> instruction: 0xf0000000
     3a4:	f4000003 	vst4.8	{d0-d3}, [r0], r3
     3a8:	02000003 	andeq	r0, r0, #3
     3ac:	f4007d00 			; <UNDEFINED> instruction: 0xf4007d00
     3b0:	fc000003 	stc2	0, cr0, [r0], {3}
     3b4:	02000003 	andeq	r0, r0, #3
     3b8:	fc007c00 	stc2	12, cr7, [r0], {-0}
     3bc:	ac000003 	stcge	0, cr0, [r0], {3}
     3c0:	02000004 	andeq	r0, r0, #4
     3c4:	00047b00 	andeq	r7, r4, r0, lsl #22
     3c8:	00000000 	andeq	r0, r0, r0
     3cc:	f0000000 			; <UNDEFINED> instruction: 0xf0000000
     3d0:	10000003 	andne	r0, r0, r3
     3d4:	01000004 	tsteq	r0, r4
     3d8:	04105000 	ldreq	r5, [r0], #-0
     3dc:	04ac0000 	strteq	r0, [ip], #0
     3e0:	00010000 	andeq	r0, r1, r0
     3e4:	00000058 	andeq	r0, r0, r8, asr r0
     3e8:	00000000 	andeq	r0, r0, r0
     3ec:	0003f000 	andeq	pc, r3, r0
     3f0:	00043400 	andeq	r3, r4, r0, lsl #8
     3f4:	51000100 	mrspl	r0, (UNDEF: 16)
     3f8:	00000434 	andeq	r0, r0, r4, lsr r4
     3fc:	000004ac 	andeq	r0, r0, ip, lsr #9
     400:	00570001 	subseq	r0, r7, r1
     404:	00000000 	andeq	r0, r0, r0
     408:	f0000000 			; <UNDEFINED> instruction: 0xf0000000
     40c:	34000003 	strcc	r0, [r0], #-3
     410:	01000004 	tsteq	r0, r4
     414:	04345200 	ldrteq	r5, [r4], #-512	; 0xfffffe00
     418:	04ac0000 	strteq	r0, [ip], #0
     41c:	00010000 	andeq	r0, r1, r0
     420:	0000005a 	andeq	r0, r0, sl, asr r0
     424:	00000000 	andeq	r0, r0, r0
     428:	0004ac00 	andeq	sl, r4, r0, lsl #24
     42c:	0004b000 	andeq	fp, r4, r0
     430:	7d000200 	sfmvc	f0, 4, [r0, #-0]
     434:	0004b000 	andeq	fp, r4, r0
     438:	0004b800 	andeq	fp, r4, r0, lsl #16
     43c:	7c000200 	sfmvc	f0, 4, [r0], {-0}
     440:	0004b800 	andeq	fp, r4, r0, lsl #16
     444:	00084000 	andeq	r4, r8, r0
     448:	7b000200 	blvc	c50 <.debug_loc+0xc50>
     44c:	00000004 	andeq	r0, r0, r4
     450:	00000000 	andeq	r0, r0, r0
     454:	0004ac00 	andeq	sl, r4, r0, lsl #24
     458:	0004d800 	andeq	sp, r4, r0, lsl #16
     45c:	50000100 	andpl	r0, r0, r0, lsl #2
     460:	00000520 	andeq	r0, r0, r0, lsr #10
     464:	00000560 	andeq	r0, r0, r0, ror #10
     468:	28500001 	ldmdacs	r0, {r0}^
     46c:	2c000006 	stccs	0, cr0, [r0], {6}
     470:	01000006 	tsteq	r0, r6
     474:	06b05000 	ldrteq	r5, [r0], r0
     478:	06bc0000 	ldrteq	r0, [ip], r0
     47c:	00010000 	andeq	r0, r1, r0
     480:	00000050 	andeq	r0, r0, r0, asr r0
     484:	00000000 	andeq	r0, r0, r0
     488:	00057400 	andeq	r7, r5, r0, lsl #8
     48c:	00057c00 	andeq	r7, r5, r0, lsl #24
     490:	53000100 	movwpl	r0, #256	; 0x100
     494:	000005b0 			; <UNDEFINED> instruction: 0x000005b0
     498:	00000614 	andeq	r0, r0, r4, lsl r6
     49c:	14560001 	ldrbne	r0, [r6], #-1
     4a0:	24000006 	strcs	r0, [r0], #-6
     4a4:	01000006 	tsteq	r0, r6
     4a8:	06485300 	strbeq	r5, [r8], -r0, lsl #6
     4ac:	06500000 	ldrbeq	r0, [r0], -r0
     4b0:	00010000 	andeq	r0, r1, r0
     4b4:	00068853 	andeq	r8, r6, r3, asr r8
     4b8:	00069000 	andeq	r9, r6, r0
     4bc:	53000100 	movwpl	r0, #256	; 0x100
     4c0:	000006d8 	ldrdeq	r0, [r0], -r8
     4c4:	000006e0 	andeq	r0, r0, r0, ror #13
     4c8:	14530001 	ldrbne	r0, [r3], #-1
     4cc:	24000007 	strcs	r0, [r0], #-7
     4d0:	01000007 	tsteq	r0, r7
     4d4:	07485300 	strbeq	r5, [r8, -r0, lsl #6]
     4d8:	07500000 	ldrbeq	r0, [r0, -r0]
     4dc:	00010000 	andeq	r0, r1, r0
     4e0:	00077053 	andeq	r7, r7, r3, asr r0
     4e4:	00078000 	andeq	r8, r7, r0
     4e8:	53000100 	movwpl	r0, #256	; 0x100
     4ec:	00000784 	andeq	r0, r0, r4, lsl #15
     4f0:	00000794 	muleq	r0, r4, r7
     4f4:	ac530001 	mrrcge	0, 0, r0, r3, cr1
     4f8:	c4000007 	strgt	r0, [r0], #-7
     4fc:	01000007 	tsteq	r0, r7
     500:	07c45600 	strbeq	r5, [r4, r0, lsl #12]
     504:	07d40000 	ldrbeq	r0, [r4, r0]
     508:	00010000 	andeq	r0, r1, r0
     50c:	00000053 	andeq	r0, r0, r3, asr r0
     510:	00000000 	andeq	r0, r0, r0
     514:	00054c00 	andeq	r4, r5, r0, lsl #24
     518:	0006b000 	andeq	fp, r6, r0
     51c:	7b000200 	blvc	d24 <.debug_loc+0xd24>
     520:	0006d050 	andeq	sp, r6, r0, asr r0
     524:	00084000 	andeq	r4, r8, r0
     528:	7b000200 	blvc	d30 <.debug_loc+0xd30>
     52c:	00000050 	andeq	r0, r0, r0, asr r0
     530:	00000000 	andeq	r0, r0, r0
     534:	00054c00 	andeq	r4, r5, r0, lsl #24
     538:	0006b000 	andeq	fp, r6, r0
     53c:	7b000200 	blvc	d44 <.debug_loc+0xd44>
     540:	0006c84c 	andeq	ip, r6, ip, asr #16
     544:	00084000 	andeq	r4, r8, r0
     548:	7b000200 	blvc	d50 <.debug_loc+0xd50>
     54c:	0000004c 	andeq	r0, r0, ip, asr #32
     550:	00000000 	andeq	r0, r0, r0
     554:	00084000 	andeq	r4, r8, r0
     558:	00084400 	andeq	r4, r8, r0, lsl #8
     55c:	7d000200 	sfmvc	f0, 4, [r0, #-0]
     560:	00084400 	andeq	r4, r8, r0, lsl #8
     564:	00084c00 	andeq	r4, r8, r0, lsl #24
     568:	7c000200 	sfmvc	f0, 4, [r0], {-0}
     56c:	00084c00 	andeq	r4, r8, r0, lsl #24
     570:	0008b400 	andeq	fp, r8, r0, lsl #8
     574:	7b000200 	blvc	d7c <.debug_loc+0xd7c>
     578:	00000004 	andeq	r0, r0, r4
     57c:	00000000 	andeq	r0, r0, r0
     580:	00084000 	andeq	r4, r8, r0
     584:	00085800 	andeq	r5, r8, r0, lsl #16
     588:	50000100 	andpl	r0, r0, r0, lsl #2
	...
     594:	000008b4 			; <UNDEFINED> instruction: 0x000008b4
     598:	000008b8 			; <UNDEFINED> instruction: 0x000008b8
     59c:	007d0002 	rsbseq	r0, sp, r2
     5a0:	000008b8 			; <UNDEFINED> instruction: 0x000008b8
     5a4:	000008c0 	andeq	r0, r0, r0, asr #17
     5a8:	007c0002 	rsbseq	r0, ip, r2
     5ac:	000008c0 	andeq	r0, r0, r0, asr #17
     5b0:	00000934 	andeq	r0, r0, r4, lsr r9
     5b4:	047b0002 	ldrbteq	r0, [fp], #-2
	...
     5c0:	000008b4 			; <UNDEFINED> instruction: 0x000008b4
     5c4:	000008cc 	andeq	r0, r0, ip, asr #17
     5c8:	00500001 	subseq	r0, r0, r1
     5cc:	00000000 	andeq	r0, r0, r0
     5d0:	b4000000 	strlt	r0, [r0], #-0
     5d4:	e0000008 	and	r0, r0, r8
     5d8:	01000008 	tsteq	r0, r8
     5dc:	00005100 	andeq	r5, r0, r0, lsl #2
     5e0:	00000000 	andeq	r0, r0, r0
     5e4:	08b40000 	ldmeq	r4!, {}	; <UNPREDICTABLE>
     5e8:	08e00000 	stmiaeq	r0!, {}^	; <UNPREDICTABLE>
     5ec:	00010000 	andeq	r0, r1, r0
     5f0:	00000052 	andeq	r0, r0, r2, asr r0
     5f4:	00000000 	andeq	r0, r0, r0
     5f8:	00093400 	andeq	r3, r9, r0, lsl #8
     5fc:	00093800 	andeq	r3, r9, r0, lsl #16
     600:	7d000200 	sfmvc	f0, 4, [r0, #-0]
     604:	00093800 	andeq	r3, r9, r0, lsl #16
     608:	00094000 	andeq	r4, r9, r0
     60c:	7c000200 	sfmvc	f0, 4, [r0], {-0}
     610:	00094000 	andeq	r4, r9, r0
     614:	0009fc00 	andeq	pc, r9, r0, lsl #24
     618:	7b000200 	blvc	e20 <.debug_loc+0xe20>
     61c:	00000004 	andeq	r0, r0, r4
     620:	00000000 	andeq	r0, r0, r0
     624:	00093400 	andeq	r3, r9, r0, lsl #8
     628:	00096c00 	andeq	r6, r9, r0, lsl #24
     62c:	50000100 	andpl	r0, r0, r0, lsl #2
	...
     638:	0000095c 	andeq	r0, r0, ip, asr r9
     63c:	00000968 	andeq	r0, r0, r8, ror #18
     640:	68530001 	ldmdavs	r3, {r0}^
     644:	98000009 	stmdals	r0, {r0, r3}
     648:	02000009 	andeq	r0, r0, #9
     64c:	98687b00 	stmdals	r8!, {r8, r9, fp, ip, sp, lr}^
     650:	a4000009 	strge	r0, [r0], #-9
     654:	01000009 	tsteq	r0, r9
     658:	09a45300 	stmibeq	r4!, {r8, r9, ip, lr}
     65c:	09fc0000 	ldmibeq	ip!, {}^	; <UNPREDICTABLE>
     660:	00020000 	andeq	r0, r2, r0
     664:	0000687b 	andeq	r6, r0, fp, ror r8
     668:	00000000 	andeq	r0, r0, r0
     66c:	09fc0000 	ldmibeq	ip!, {}^	; <UNPREDICTABLE>
     670:	0a000000 	beq	678 <.debug_loc+0x678>
     674:	00020000 	andeq	r0, r2, r0
     678:	0a00007d 	beq	874 <.debug_loc+0x874>
     67c:	0a080000 	beq	200684 <wmt_core_func_ctrl_cmd+0x1fd264>
     680:	00020000 	andeq	r0, r2, r0
     684:	0a08007c 	beq	20087c <wmt_core_func_ctrl_cmd+0x1fd45c>
     688:	0a380000 	beq	e00690 <wmt_core_func_ctrl_cmd+0xdfd270>
     68c:	00020000 	andeq	r0, r2, r0
     690:	0000047b 	andeq	r0, r0, fp, ror r4
     694:	00000000 	andeq	r0, r0, r0
     698:	09fc0000 	ldmibeq	ip!, {}^	; <UNPREDICTABLE>
     69c:	0a1c0000 	beq	7006a4 <wmt_core_func_ctrl_cmd+0x6fd284>
     6a0:	00010000 	andeq	r0, r1, r0
     6a4:	000a2450 	andeq	r2, sl, r0, asr r4
     6a8:	000a2800 	andeq	r2, sl, r0, lsl #16
     6ac:	50000100 	andpl	r0, r0, r0, lsl #2
	...
     6b8:	00000a38 	andeq	r0, r0, r8, lsr sl
     6bc:	00000a3c 	andeq	r0, r0, ip, lsr sl
     6c0:	007d0002 	rsbseq	r0, sp, r2
     6c4:	00000a3c 	andeq	r0, r0, ip, lsr sl
     6c8:	00000a44 	andeq	r0, r0, r4, asr #20
     6cc:	007c0002 	rsbseq	r0, ip, r2
     6d0:	00000a44 	andeq	r0, r0, r4, asr #20
     6d4:	00000c6c 	andeq	r0, r0, ip, ror #24
     6d8:	047b0002 	ldrbteq	r0, [fp], #-2
	...
     6e4:	00000ac0 	andeq	r0, r0, r0, asr #21
     6e8:	00000af0 	strdeq	r0, [r0], -r0	; <UNPREDICTABLE>
     6ec:	f0590001 			; <UNDEFINED> instruction: 0xf0590001
     6f0:	2c00000a 	stccs	0, cr0, [r0], {10}
     6f4:	0100000b 	tsteq	r0, fp
     6f8:	0b645a00 	bleq	1916f00 <wmt_core_func_ctrl_cmd+0x1913ae0>
     6fc:	0b800000 	bleq	fe000704 <wmt_core_func_ctrl_cmd+0xfdffd2e4>
     700:	00010000 	andeq	r0, r1, r0
     704:	000b805a 	andeq	r8, fp, sl, asr r0
     708:	000b9800 	andeq	r9, fp, r0, lsl #16
     70c:	52000100 	andpl	r0, r0, #0, 2
     710:	00000bb4 			; <UNDEFINED> instruction: 0x00000bb4
     714:	00000bd0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
     718:	e45a0001 	ldrb	r0, [sl], #-1
     71c:	0000000b 	andeq	r0, r0, fp
     720:	0100000c 	tsteq	r0, ip
     724:	0c005a00 	stceq	10, cr5, [r0], {-0}
     728:	0c180000 	ldceq	0, cr0, [r8], {-0}
     72c:	00010000 	andeq	r0, r1, r0
     730:	000c1c52 	andeq	r1, ip, r2, asr ip
     734:	000c3000 	andeq	r3, ip, r0
     738:	5a000100 	bpl	b40 <.debug_loc+0xb40>
     73c:	00000c30 	andeq	r0, r0, r0, lsr ip
     740:	00000c3c 	andeq	r0, r0, ip, lsr ip
     744:	00520001 	subseq	r0, r2, r1
     748:	00000000 	andeq	r0, r0, r0
     74c:	a8000000 	stmdage	r0, {}	; <UNPREDICTABLE>
     750:	2c00000a 	stccs	0, cr0, [r0], {10}
     754:	0200000b 	andeq	r0, r0, #11
     758:	64507b00 	ldrbvs	r7, [r0], #-2816	; 0xfffff500
     75c:	d000000b 	andle	r0, r0, fp
     760:	0200000b 	andeq	r0, r0, #11
     764:	e4507b00 	ldrb	r7, [r0], #-2816	; 0xfffff500
     768:	6c00000b 	stcvs	0, cr0, [r0], {11}
     76c:	0200000c 	andeq	r0, r0, #12
     770:	00507b00 	subseq	r7, r0, r0, lsl #22
     774:	00000000 	andeq	r0, r0, r0
     778:	a4000000 	strge	r0, [r0], #-0
     77c:	2c00000a 	stccs	0, cr0, [r0], {10}
     780:	0200000b 	andeq	r0, r0, #11
     784:	644c7b00 	strbvs	r7, [ip], #-2816	; 0xfffff500
     788:	d000000b 	andle	r0, r0, fp
     78c:	0200000b 	andeq	r0, r0, #11
     790:	e44c7b00 	strb	r7, [ip], #-2816	; 0xfffff500
     794:	6c00000b 	stcvs	0, cr0, [r0], {11}
     798:	0200000c 	andeq	r0, r0, #12
     79c:	004c7b00 	subeq	r7, ip, r0, lsl #22
     7a0:	00000000 	andeq	r0, r0, r0
     7a4:	6c000000 	stcvs	0, cr0, [r0], {-0}
     7a8:	7000000c 	andvc	r0, r0, ip
     7ac:	0200000c 	andeq	r0, r0, #12
     7b0:	70007d00 	andvc	r7, r0, r0, lsl #26
     7b4:	7800000c 	stmdavc	r0, {r2, r3}
     7b8:	0200000c 	andeq	r0, r0, #12
     7bc:	78007c00 	stmdavc	r0, {sl, fp, ip, sp, lr}
     7c0:	a000000c 	andge	r0, r0, ip
     7c4:	0200000d 	andeq	r0, r0, #13
     7c8:	00047b00 	andeq	r7, r4, r0, lsl #22
     7cc:	00000000 	andeq	r0, r0, r0
     7d0:	6c000000 	stcvs	0, cr0, [r0], {-0}
     7d4:	a400000c 	strge	r0, [r0], #-12
     7d8:	0100000c 	tsteq	r0, ip
     7dc:	0d045000 	stceq	0, cr5, [r4, #-0]
     7e0:	0d080000 	stceq	0, cr0, [r8, #-0]
     7e4:	00010000 	andeq	r0, r1, r0
     7e8:	000d4050 	andeq	r4, sp, r0, asr r0
     7ec:	000d5400 	andeq	r5, sp, r0, lsl #8
     7f0:	50000100 	andpl	r0, r0, r0, lsl #2
     7f4:	00000d5c 	andeq	r0, r0, ip, asr sp
     7f8:	00000d70 	andeq	r0, r0, r0, ror sp
     7fc:	00500001 	subseq	r0, r0, r1
     800:	00000000 	andeq	r0, r0, r0
     804:	94000000 	strls	r0, [r0], #-0
     808:	a800000c 	stmdage	r0, {r2, r3}
     80c:	0100000c 	tsteq	r0, ip
     810:	0cc05200 	sfmeq	f5, 2, [r0], {0}
     814:	0d040000 	stceq	0, cr0, [r4, #-0]
     818:	00010000 	andeq	r0, r1, r0
     81c:	000d0c54 	andeq	r0, sp, r4, asr ip
     820:	000d2c00 	andeq	r2, sp, r0, lsl #24
     824:	52000100 	andpl	r0, r0, #0, 2
     828:	00000d30 	andeq	r0, r0, r0, lsr sp
     82c:	00000d40 	andeq	r0, r0, r0, asr #26
     830:	6c540001 	mrrcvs	0, 0, r0, r4, cr1
     834:	a000000d 	andge	r0, r0, sp
     838:	0100000d 	tsteq	r0, sp
     83c:	00005400 	andeq	r5, r0, r0, lsl #8
     840:	00000000 	andeq	r0, r0, r0
     844:	0cb00000 	ldceq	0, cr0, [r0]
     848:	0d040000 	stceq	0, cr0, [r4, #-0]
     84c:	00020000 	andeq	r0, r2, r0
     850:	0d30607b 	ldceq	0, cr6, [r0, #-492]!	; 0xfffffe14
     854:	0d400000 	stcleq	0, cr0, [r0, #-0]
     858:	00020000 	andeq	r0, r2, r0
     85c:	0000607b 	andeq	r6, r0, fp, ror r0
     860:	00000000 	andeq	r0, r0, r0
     864:	0cb80000 	ldceq	0, cr0, [r8]
     868:	0d040000 	stceq	0, cr0, [r4, #-0]
     86c:	00020000 	andeq	r0, r2, r0
     870:	0d305c7b 	ldceq	12, cr5, [r0, #-492]!	; 0xfffffe14
     874:	0d400000 	stcleq	0, cr0, [r0, #-0]
     878:	00020000 	andeq	r0, r2, r0
     87c:	00005c7b 	andeq	r5, r0, fp, ror ip
     880:	00000000 	andeq	r0, r0, r0
     884:	0da00000 	stceq	0, cr0, [r0]
     888:	0da40000 	stceq	0, cr0, [r4]
     88c:	00020000 	andeq	r0, r2, r0
     890:	0da4007d 	stceq	0, cr0, [r4, #500]!	; 0x1f4
     894:	0dac0000 	stceq	0, cr0, [ip]
     898:	00020000 	andeq	r0, r2, r0
     89c:	0dac007c 	stceq	0, cr0, [ip, #496]!	; 0x1f0
     8a0:	10e40000 	rscne	r0, r4, r0
     8a4:	00020000 	andeq	r0, r2, r0
     8a8:	0000047b 	andeq	r0, r0, fp, ror r4
     8ac:	00000000 	andeq	r0, r0, r0
     8b0:	0da00000 	stceq	0, cr0, [r0]
     8b4:	0dc00000 	stcleq	0, cr0, [r0]
     8b8:	00010000 	andeq	r0, r1, r0
     8bc:	000dc050 	andeq	ip, sp, r0, asr r0
     8c0:	000f1800 	andeq	r1, pc, r0, lsl #16
     8c4:	57000100 	strpl	r0, [r0, -r0, lsl #2]
     8c8:	00000f18 	andeq	r0, r0, r8, lsl pc
     8cc:	00000f30 	andeq	r0, r0, r0, lsr pc
     8d0:	54500001 	ldrbpl	r0, [r0], #-1
     8d4:	e400000f 	str	r0, [r0], #-15
     8d8:	01000010 	tsteq	r0, r0, lsl r0
     8dc:	00005700 	andeq	r5, r0, r0, lsl #14
     8e0:	00000000 	andeq	r0, r0, r0
     8e4:	0de40000 	stcleq	0, cr0, [r4]
     8e8:	0df00000 	ldcleq	0, cr0, [r0]
     8ec:	00010000 	andeq	r0, r1, r0
     8f0:	000e0056 	andeq	r0, lr, r6, asr r0
     8f4:	000e0c00 	andeq	r0, lr, r0, lsl #24
     8f8:	56000100 	strpl	r0, [r0], -r0, lsl #2
     8fc:	00000e4c 	andeq	r0, r0, ip, asr #28
     900:	00000f54 	andeq	r0, r0, r4, asr pc
     904:	80560001 	subshi	r0, r6, r1
     908:	c000000f 	andgt	r0, r0, pc
     90c:	0100000f 	tsteq	r0, pc
     910:	0fd45600 	svceq	0x00d45600
     914:	10100000 	andsne	r0, r0, r0
     918:	00010000 	andeq	r0, r1, r0
     91c:	00103856 	andseq	r3, r0, r6, asr r8
     920:	00104000 	andseq	r4, r0, r0
     924:	56000100 	strpl	r0, [r0], -r0, lsl #2
     928:	00001068 	andeq	r1, r0, r8, rrx
     92c:	000010e4 	andeq	r1, r0, r4, ror #1
     930:	00560001 	subseq	r0, r6, r1
     934:	00000000 	andeq	r0, r0, r0
     938:	b4000000 	strlt	r0, [r0], #-0
     93c:	0c00000d 	stceq	0, cr0, [r0], {13}
     940:	0100000f 	tsteq	r0, pc
     944:	0f545400 	svceq	0x00545400
     948:	10e40000 	rscne	r0, r4, r0
     94c:	00010000 	andeq	r0, r1, r0
     950:	00000054 	andeq	r0, r0, r4, asr r0
     954:	00000000 	andeq	r0, r0, r0
     958:	000de400 	andeq	lr, sp, r0, lsl #8
     95c:	000df000 	andeq	pc, sp, r0
     960:	7b000200 	blvc	1168 <.debug_loc+0x1168>
     964:	000e5050 	andeq	r5, lr, r0, asr r0
     968:	000f5400 	andeq	r5, pc, r0, lsl #8
     96c:	7b000200 	blvc	1174 <.debug_loc+0x1174>
     970:	000f8850 	andeq	r8, pc, r0, asr r8	; <UNPREDICTABLE>
     974:	000fc000 	andeq	ip, pc, r0
     978:	7b000200 	blvc	1180 <.debug_loc+0x1180>
     97c:	000ff850 	andeq	pc, pc, r0, asr r8	; <UNPREDICTABLE>
     980:	00101000 	andseq	r1, r0, r0
     984:	7b000200 	blvc	118c <.debug_loc+0x118c>
     988:	00107450 	andseq	r7, r0, r0, asr r4
     98c:	0010e400 	andseq	lr, r0, r0, lsl #8
     990:	7b000200 	blvc	1198 <.debug_loc+0x1198>
     994:	00000050 	andeq	r0, r0, r0, asr r0
     998:	00000000 	andeq	r0, r0, r0
     99c:	000de400 	andeq	lr, sp, r0, lsl #8
     9a0:	000df000 	andeq	pc, sp, r0
     9a4:	7b000200 	blvc	11ac <.debug_loc+0x11ac>
     9a8:	000e504c 	andeq	r5, lr, ip, asr #32
     9ac:	000f5400 	andeq	r5, pc, r0, lsl #8
     9b0:	7b000200 	blvc	11b8 <.debug_loc+0x11b8>
     9b4:	000f884c 	andeq	r8, pc, ip, asr #16
     9b8:	000fc000 	andeq	ip, pc, r0
     9bc:	7b000200 	blvc	11c4 <.debug_loc+0x11c4>
     9c0:	000ff04c 	andeq	pc, pc, ip, asr #32
     9c4:	00101000 	andseq	r1, r0, r0
     9c8:	7b000200 	blvc	11d0 <.debug_loc+0x11d0>
     9cc:	0010744c 	andseq	r7, r0, ip, asr #8
     9d0:	0010e400 	andseq	lr, r0, r0, lsl #8
     9d4:	7b000200 	blvc	11dc <.debug_loc+0x11dc>
     9d8:	0000004c 	andeq	r0, r0, ip, asr #32
     9dc:	00000000 	andeq	r0, r0, r0
     9e0:	0010e400 	andseq	lr, r0, r0, lsl #8
     9e4:	0010e800 	andseq	lr, r0, r0, lsl #16
     9e8:	7d000200 	sfmvc	f0, 4, [r0, #-0]
     9ec:	0010e800 	andseq	lr, r0, r0, lsl #16
     9f0:	0010f000 	andseq	pc, r0, r0
     9f4:	7c000200 	sfmvc	f0, 4, [r0], {-0}
     9f8:	0010f000 	andseq	pc, r0, r0
     9fc:	0010f800 	andseq	pc, r0, r0, lsl #16
     a00:	7b000200 	blvc	1208 <.debug_loc+0x1208>
     a04:	00000004 	andeq	r0, r0, r4
     a08:	00000000 	andeq	r0, r0, r0
     a0c:	0010e400 	andseq	lr, r0, r0, lsl #8
     a10:	0010f400 	andseq	pc, r0, r0, lsl #8
     a14:	50000100 	andpl	r0, r0, r0, lsl #2
	...
     a20:	000010e4 	andeq	r1, r0, r4, ror #1
     a24:	000010f4 	strdeq	r1, [r0], -r4
     a28:	00510001 	subseq	r0, r1, r1
     a2c:	00000000 	andeq	r0, r0, r0
     a30:	e4000000 	str	r0, [r0], #-0
     a34:	f4000010 	vst4.8	{d0-d3}, [r0 :64], r0
     a38:	01000010 	tsteq	r0, r0, lsl r0
     a3c:	00005200 	andeq	r5, r0, r0, lsl #4
     a40:	00000000 	andeq	r0, r0, r0
     a44:	10e40000 	rscne	r0, r4, r0
     a48:	10f40000 	rscsne	r0, r4, r0
     a4c:	00010000 	andeq	r0, r1, r0
     a50:	00000053 	andeq	r0, r0, r3, asr r0
     a54:	00000000 	andeq	r0, r0, r0
     a58:	0010f800 	andseq	pc, r0, r0, lsl #16
     a5c:	0010fc00 	andseq	pc, r0, r0, lsl #24
     a60:	7d000200 	sfmvc	f0, 4, [r0, #-0]
     a64:	0010fc00 	andseq	pc, r0, r0, lsl #24
     a68:	00110400 	andseq	r0, r1, r0, lsl #8
     a6c:	7c000200 	sfmvc	f0, 4, [r0], {-0}
     a70:	00110400 	andseq	r0, r1, r0, lsl #8
     a74:	00131c00 	andseq	r1, r3, r0, lsl #24
     a78:	7b000200 	blvc	1280 <.debug_loc+0x1280>
     a7c:	00000004 	andeq	r0, r0, r4
     a80:	00000000 	andeq	r0, r0, r0
     a84:	0010f800 	andseq	pc, r0, r0, lsl #16
     a88:	00113800 	andseq	r3, r1, r0, lsl #16
     a8c:	50000100 	andpl	r0, r0, r0, lsl #2
     a90:	000011c0 	andeq	r1, r0, r0, asr #3
     a94:	000011d8 	ldrdeq	r1, [r0], -r8
     a98:	2c500001 	mrrccs	0, 0, r0, r0, cr1	; <UNPREDICTABLE>
     a9c:	34000012 	strcc	r0, [r0], #-18	; 0xffffffee
     aa0:	01000012 	tsteq	r0, r2, lsl r0
     aa4:	12f45000 	rscsne	r5, r4, #0
     aa8:	131c0000 	tstne	ip, #0
     aac:	00010000 	andeq	r0, r1, r0
     ab0:	00000050 	andeq	r0, r0, r0, asr r0
     ab4:	00000000 	andeq	r0, r0, r0
     ab8:	0010f800 	andseq	pc, r0, r0, lsl #16
     abc:	00111000 	andseq	r1, r1, r0
     ac0:	51000100 	mrspl	r0, (UNDEF: 16)
     ac4:	00001110 	andeq	r1, r0, r0, lsl r1
     ac8:	0000131c 	andeq	r1, r0, ip, lsl r3
     acc:	00590001 	subseq	r0, r9, r1
     ad0:	00000000 	andeq	r0, r0, r0
     ad4:	28000000 	stmdacs	r0, {}	; <UNPREDICTABLE>
     ad8:	f4000011 	vst4.8	{d0-d3}, [r0 :64], r1
     adc:	02000012 	andeq	r0, r0, #18
     ae0:	00507b00 	subseq	r7, r0, r0, lsl #22
     ae4:	00000000 	andeq	r0, r0, r0
     ae8:	1c000000 	stcne	0, cr0, [r0], {-0}
     aec:	f4000011 	vst4.8	{d0-d3}, [r0 :64], r1
     af0:	01000012 	tsteq	r0, r2, lsl r0
     af4:	12f85700 	rscsne	r5, r8, #0, 14
     af8:	131c0000 	tstne	ip, #0
     afc:	00010000 	andeq	r0, r1, r0
     b00:	00000057 	andeq	r0, r0, r7, asr r0
     b04:	00000000 	andeq	r0, r0, r0
     b08:	00112800 	andseq	r2, r1, r0, lsl #16
     b0c:	00114400 	andseq	r4, r1, r0, lsl #8
     b10:	58000100 	stmdapl	r0, {r8}
     b14:	00001144 	andeq	r1, r0, r4, asr #2
     b18:	00001164 	andeq	r1, r0, r4, ror #2
     b1c:	785c0001 	ldmdavc	ip, {r0}^
     b20:	08000011 	stmdaeq	r0, {r0, r4}
     b24:	01000012 	tsteq	r0, r2, lsl r0
     b28:	12085800 	andne	r5, r8, #0, 16
     b2c:	122c0000 	eorne	r0, ip, #0
     b30:	00010000 	andeq	r0, r1, r0
     b34:	00122c5c 	andseq	r2, r2, ip, asr ip
     b38:	0012f400 	andseq	pc, r2, r0, lsl #8
     b3c:	58000100 	stmdapl	r0, {r8}
	...
     b48:	0000131c 	andeq	r1, r0, ip, lsl r3
     b4c:	00001320 	andeq	r1, r0, r0, lsr #6
     b50:	007d0002 	rsbseq	r0, sp, r2
     b54:	00001320 	andeq	r1, r0, r0, lsr #6
     b58:	00001328 	andeq	r1, r0, r8, lsr #6
     b5c:	007c0002 	rsbseq	r0, ip, r2
     b60:	00001328 	andeq	r1, r0, r8, lsr #6
     b64:	000014fc 	strdeq	r1, [r0], -ip
     b68:	047b0002 	ldrbteq	r0, [fp], #-2
	...
     b74:	0000131c 	andeq	r1, r0, ip, lsl r3
     b78:	00001364 	andeq	r1, r0, r4, ror #6
     b7c:	64500001 	ldrbvs	r0, [r0], #-1
     b80:	fc000013 	stc2	0, cr0, [r0], {19}
     b84:	01000014 	tsteq	r0, r4, lsl r0
     b88:	00005500 	andeq	r5, r0, r0, lsl #10
     b8c:	00000000 	andeq	r0, r0, r0
     b90:	131c0000 	tstne	ip, #0
     b94:	13540000 	cmpne	r4, #0
     b98:	00010000 	andeq	r0, r1, r0
     b9c:	00135451 	andseq	r5, r3, r1, asr r4
     ba0:	0014fc00 	andseq	pc, r4, r0, lsl #24
     ba4:	7b000300 	blvc	17ac <.debug_loc+0x17ac>
     ba8:	00007fb8 			; <UNDEFINED> instruction: 0x00007fb8
     bac:	00000000 	andeq	r0, r0, r0
     bb0:	131c0000 	tstne	ip, #0
     bb4:	135c0000 	cmpne	ip, #0
     bb8:	00010000 	andeq	r0, r1, r0
     bbc:	00135c52 	andseq	r5, r3, r2, asr ip
     bc0:	0014fc00 	andseq	pc, r4, r0, lsl #24
     bc4:	5a000100 	bpl	fcc <.debug_loc+0xfcc>
	...
     bd0:	0000131c 	andeq	r1, r0, ip, lsl r3
     bd4:	0000136c 	andeq	r1, r0, ip, ror #6
     bd8:	6c530001 	mrrcvs	0, 0, r0, r3, cr1
     bdc:	fc000013 	stc2	0, cr0, [r0], {19}
     be0:	03000014 	movweq	r0, #20
     be4:	7fb47b00 	svcvc	0x00b47b00
	...
     bf0:	000013b8 			; <UNDEFINED> instruction: 0x000013b8
     bf4:	000013e8 	andeq	r1, r0, r8, ror #7
     bf8:	ec530001 	mrrc	0, 0, r0, r3, cr1
     bfc:	08000013 	stmdaeq	r0, {r0, r1, r4}
     c00:	01000014 	tsteq	r0, r4, lsl r0
     c04:	14105000 	ldrne	r5, [r0], #-0
     c08:	141c0000 	ldrne	r0, [ip], #-0
     c0c:	00010000 	andeq	r0, r1, r0
     c10:	00146850 	andseq	r6, r4, r0, asr r8
     c14:	00148400 	andseq	r8, r4, r0, lsl #8
     c18:	53000100 	movwpl	r0, #256	; 0x100
     c1c:	0000148c 	andeq	r1, r0, ip, lsl #9
     c20:	00001498 	muleq	r0, r8, r4
     c24:	00500001 	subseq	r0, r0, r1
     c28:	00000000 	andeq	r0, r0, r0
     c2c:	d8000000 	stmdale	r0, {}	; <UNPREDICTABLE>
     c30:	68000013 	stmdavs	r0, {r0, r1, r4}
     c34:	01000014 	tsteq	r0, r4, lsl r0
     c38:	148c5700 	strne	r5, [ip], #1792	; 0x700
     c3c:	14fc0000 	ldrbtne	r0, [ip], #0
     c40:	00010000 	andeq	r0, r1, r0
     c44:	00000057 	andeq	r0, r0, r7, asr r0
     c48:	00000000 	andeq	r0, r0, r0
     c4c:	00140800 	andseq	r0, r4, r0, lsl #16
     c50:	00141000 	andseq	r1, r4, r0
     c54:	7b000200 	blvc	145c <.debug_loc+0x145c>
     c58:	00143854 	andseq	r3, r4, r4, asr r8
     c5c:	00146800 	andseq	r6, r4, r0, lsl #16
     c60:	7b000200 	blvc	1468 <.debug_loc+0x1468>
     c64:	0014b054 	andseq	fp, r4, r4, asr r0
     c68:	0014fc00 	andseq	pc, r4, r0, lsl #24
     c6c:	7b000200 	blvc	1474 <.debug_loc+0x1474>
     c70:	00000054 	andeq	r0, r0, r4, asr r0
     c74:	00000000 	andeq	r0, r0, r0
     c78:	00140800 	andseq	r0, r4, r0, lsl #16
     c7c:	00141000 	andseq	r1, r4, r0
     c80:	7b000200 	blvc	1488 <.debug_loc+0x1488>
     c84:	00143450 	andseq	r3, r4, r0, asr r4
     c88:	00146800 	andseq	r6, r4, r0, lsl #16
     c8c:	7b000200 	blvc	1494 <.debug_loc+0x1494>
     c90:	0014b050 	andseq	fp, r4, r0, asr r0
     c94:	0014fc00 	andseq	pc, r4, r0, lsl #24
     c98:	7b000200 	blvc	14a0 <.debug_loc+0x14a0>
     c9c:	00000050 	andeq	r0, r0, r0, asr r0
     ca0:	00000000 	andeq	r0, r0, r0
     ca4:	0014fc00 	andseq	pc, r4, r0, lsl #24
     ca8:	00150000 	andseq	r0, r5, r0
     cac:	7d000200 	sfmvc	f0, 4, [r0, #-0]
     cb0:	00150000 	andseq	r0, r5, r0
     cb4:	00150800 	andseq	r0, r5, r0, lsl #16
     cb8:	7c000200 	sfmvc	f0, 4, [r0], {-0}
     cbc:	00150800 	andseq	r0, r5, r0, lsl #16
     cc0:	001b9000 	andseq	r9, fp, r0
     cc4:	7b000200 	blvc	14cc <.debug_loc+0x14cc>
     cc8:	00000004 	andeq	r0, r0, r4
     ccc:	00000000 	andeq	r0, r0, r0
     cd0:	00154000 	andseq	r4, r5, r0
     cd4:	00154400 	andseq	r4, r5, r0, lsl #8
     cd8:	50000100 	andpl	r0, r0, r0, lsl #2
     cdc:	00001560 	andeq	r1, r0, r0, ror #10
     ce0:	00001580 	andeq	r1, r0, r0, lsl #11
     ce4:	a4500001 	ldrbge	r0, [r0], #-1
     ce8:	8c000015 	stchi	0, cr0, [r0], {21}
     cec:	01000016 	tsteq	r0, r6, lsl r0
     cf0:	168c5800 	strne	r5, [ip], r0, lsl #16
     cf4:	169c0000 	ldrne	r0, [ip], r0
     cf8:	00010000 	andeq	r0, r1, r0
     cfc:	00169c53 	andseq	r9, r6, r3, asr ip
     d00:	0016ac00 	andseq	sl, r6, r0, lsl #24
     d04:	55000100 	strpl	r0, [r0, #-256]	; 0xffffff00
     d08:	000016ac 	andeq	r1, r0, ip, lsr #13
     d0c:	000016c8 	andeq	r1, r0, r8, asr #13
     d10:	e0500001 	subs	r0, r0, r1
     d14:	48000016 	stmdami	r0, {r1, r2, r4}
     d18:	01000017 	tsteq	r0, r7, lsl r0
     d1c:	17705800 	ldrbne	r5, [r0, -r0, lsl #16]!
     d20:	17900000 	ldrne	r0, [r0, r0]
     d24:	00010000 	andeq	r0, r1, r0
     d28:	00179453 	andseq	r9, r7, r3, asr r4
     d2c:	0017ac00 	andseq	sl, r7, r0, lsl #24
     d30:	50000100 	andpl	r0, r0, r0, lsl #2
     d34:	000017b4 			; <UNDEFINED> instruction: 0x000017b4
     d38:	000017c8 	andeq	r1, r0, r8, asr #15
     d3c:	c8580001 	ldmdagt	r8, {r0}^
     d40:	cc000017 	stcgt	0, cr0, [r0], {23}
     d44:	01000017 	tsteq	r0, r7, lsl r0
     d48:	17cc5300 	strbne	r5, [ip, r0, lsl #6]
     d4c:	18140000 	ldmdane	r4, {}	; <UNPREDICTABLE>
     d50:	00010000 	andeq	r0, r1, r0
     d54:	0018e058 	andseq	lr, r8, r8, asr r0
     d58:	0018fc00 	andseq	pc, r8, r0, lsl #24
     d5c:	50000100 	andpl	r0, r0, r0, lsl #2
     d60:	00001918 	andeq	r1, r0, r8, lsl r9
     d64:	00001930 	andeq	r1, r0, r0, lsr r9
     d68:	30550001 	subscc	r0, r5, r1
     d6c:	38000019 	stmdacc	r0, {r0, r3, r4}
     d70:	01000019 	tsteq	r0, r9, lsl r0
     d74:	19405000 	stmdbne	r0, {ip, lr}^
     d78:	19480000 	stmdbne	r8, {}^	; <UNPREDICTABLE>
     d7c:	00010000 	andeq	r0, r1, r0
     d80:	00196c50 	andseq	r6, r9, r0, asr ip
     d84:	00197000 	andseq	r7, r9, r0
     d88:	53000100 	movwpl	r0, #256	; 0x100
     d8c:	0000199c 	muleq	r0, ip, r9
     d90:	000019a0 	andeq	r1, r0, r0, lsr #19
     d94:	a0530001 	subsge	r0, r3, r1
     d98:	e4000019 	str	r0, [r0], #-25	; 0xffffffe7
     d9c:	01000019 	tsteq	r0, r9, lsl r0
     da0:	1a285800 	bne	a16da8 <wmt_core_func_ctrl_cmd+0xa13988>
     da4:	1a300000 	bne	c00dac <wmt_core_func_ctrl_cmd+0xbfd98c>
     da8:	00010000 	andeq	r0, r1, r0
     dac:	001a4055 	andseq	r4, sl, r5, asr r0
     db0:	001a5c00 	andseq	r5, sl, r0, lsl #24
     db4:	55000100 	strpl	r0, [r0, #-256]	; 0xffffff00
     db8:	00001a5c 	andeq	r1, r0, ip, asr sl
     dbc:	00001a68 	andeq	r1, r0, r8, ror #20
     dc0:	74500001 	ldrbvc	r0, [r0], #-1
     dc4:	7800001a 	stmdavc	r0, {r1, r3, r4}
     dc8:	0100001a 	tsteq	r0, sl, lsl r0
     dcc:	1a785500 	bne	1e161d4 <wmt_core_func_ctrl_cmd+0x1e12db4>
     dd0:	1a900000 	bne	fe400dd8 <wmt_core_func_ctrl_cmd+0xfe3fd9b8>
     dd4:	00010000 	andeq	r0, r1, r0
     dd8:	001a9058 	andseq	r9, sl, r8, asr r0
     ddc:	001a9400 	andseq	r9, sl, r0, lsl #8
     de0:	55000100 	strpl	r0, [r0, #-256]	; 0xffffff00
     de4:	00001a94 	muleq	r0, r4, sl
     de8:	00001aa0 	andeq	r1, r0, r0, lsr #21
     dec:	ac500001 	mrrcge	0, 0, r0, r0, cr1	; <UNPREDICTABLE>
     df0:	b000001a 	andlt	r0, r0, sl, lsl r0
     df4:	0100001a 	tsteq	r0, sl, lsl r0
     df8:	1ab05500 	bne	fec16200 <wmt_core_func_ctrl_cmd+0xfec12de0>
     dfc:	1ac00000 	bne	ff000e04 <wmt_core_func_ctrl_cmd+0xfeffd9e4>
     e00:	00010000 	andeq	r0, r1, r0
     e04:	001ac053 	andseq	ip, sl, r3, asr r0
     e08:	001adc00 	andseq	sp, sl, r0, lsl #24
     e0c:	55000100 	strpl	r0, [r0, #-256]	; 0xffffff00
     e10:	00001adc 	ldrdeq	r1, [r0], -ip
     e14:	00001ae8 	andeq	r1, r0, r8, ror #21
     e18:	f4500001 			; <UNDEFINED> instruction: 0xf4500001
     e1c:	9000001a 	andls	r0, r0, sl, lsl r0
     e20:	0100001b 	tsteq	r0, fp, lsl r0
     e24:	00005500 	andeq	r5, r0, r0, lsl #10
     e28:	00000000 	andeq	r0, r0, r0
     e2c:	15400000 	strbne	r0, [r0, #-0]
     e30:	16d00000 	ldrbne	r0, [r0], r0
     e34:	00020000 	andeq	r0, r2, r0
     e38:	16e0507b 	uxtabne	r5, r0, fp
     e3c:	17480000 	strbne	r0, [r8, -r0]
     e40:	00020000 	andeq	r0, r2, r0
     e44:	1768507b 			; <UNDEFINED> instruction: 0x1768507b
     e48:	1a300000 	bne	c00e50 <wmt_core_func_ctrl_cmd+0xbfda30>
     e4c:	00020000 	andeq	r0, r2, r0
     e50:	1a5c507b 	bne	1715044 <wmt_core_func_ctrl_cmd+0x1711c24>
     e54:	1b900000 	blne	fe400e5c <wmt_core_func_ctrl_cmd+0xfe3fda3c>
     e58:	00020000 	andeq	r0, r2, r0
     e5c:	0000507b 	andeq	r5, r0, fp, ror r0
     e60:	00000000 	andeq	r0, r0, r0
     e64:	15400000 	strbne	r0, [r0, #-0]
     e68:	16d00000 	ldrbne	r0, [r0], r0
     e6c:	00020000 	andeq	r0, r2, r0
     e70:	16e04c7b 	uxtabne	r4, r0, fp, ror #24
     e74:	17480000 	strbne	r0, [r8, -r0]
     e78:	00020000 	andeq	r0, r2, r0
     e7c:	17604c7b 			; <UNDEFINED> instruction: 0x17604c7b
     e80:	1a300000 	bne	c00e88 <wmt_core_func_ctrl_cmd+0xbfda68>
     e84:	00020000 	andeq	r0, r2, r0
     e88:	1a5c4c7b 	bne	171407c <wmt_core_func_ctrl_cmd+0x1710c5c>
     e8c:	1b900000 	blne	fe400e94 <wmt_core_func_ctrl_cmd+0xfe3fda74>
     e90:	00020000 	andeq	r0, r2, r0
     e94:	00004c7b 	andeq	r4, r0, fp, ror ip
     e98:	00000000 	andeq	r0, r0, r0
     e9c:	162c0000 	strtne	r0, [ip], -r0
     ea0:	16ac0000 	strtne	r0, [ip], r0
     ea4:	00020000 	andeq	r0, r2, r0
     ea8:	17b4487b 			; <UNDEFINED> instruction: 0x17b4487b
     eac:	17cc0000 	strbne	r0, [ip, r0]
     eb0:	00020000 	andeq	r0, r2, r0
     eb4:	17f8487b 			; <UNDEFINED> instruction: 0x17f8487b
     eb8:	19400000 	stmdbne	r0, {}^	; <UNPREDICTABLE>
     ebc:	00020000 	andeq	r0, r2, r0
     ec0:	1950487b 	ldmdbne	r0, {r0, r1, r3, r4, r5, r6, fp, lr}^
     ec4:	19a00000 	stmibne	r0!, {}	; <UNPREDICTABLE>
     ec8:	00020000 	andeq	r0, r2, r0
     ecc:	19e4487b 	stmibne	r4!, {r0, r1, r3, r4, r5, r6, fp, lr}^
     ed0:	1a300000 	bne	c00ed8 <wmt_core_func_ctrl_cmd+0xbfdab8>
     ed4:	00020000 	andeq	r0, r2, r0
     ed8:	1a94487b 	bne	fe5130cc <wmt_core_func_ctrl_cmd+0xfe50fcac>
     edc:	1ab00000 	bne	fec00ee4 <wmt_core_func_ctrl_cmd+0xfebfdac4>
     ee0:	00020000 	andeq	r0, r2, r0
     ee4:	0000487b 	andeq	r4, r0, fp, ror r8
     ee8:	00000000 	andeq	r0, r0, r0
     eec:	168c0000 	strne	r0, [ip], r0
     ef0:	16ac0000 	strtne	r0, [ip], r0
     ef4:	00010000 	andeq	r0, r1, r0
     ef8:	00181458 	andseq	r1, r8, r8, asr r4
     efc:	00194000 	andseq	r4, r9, r0
     f00:	58000100 	stmdapl	r0, {r8}
     f04:	00001950 	andeq	r1, r0, r0, asr r9
     f08:	000019a0 	andeq	r1, r0, r0, lsr #19
     f0c:	e4580001 	ldrb	r0, [r8], #-1
     f10:	30000019 	andcc	r0, r0, r9, lsl r0
     f14:	0100001a 	tsteq	r0, sl, lsl r0
     f18:	1a945800 	bne	fe516f20 <wmt_core_func_ctrl_cmd+0xfe513b00>
     f1c:	1ab00000 	bne	fec00f24 <wmt_core_func_ctrl_cmd+0xfebfdb04>
     f20:	00010000 	andeq	r0, r1, r0
     f24:	00000058 	andeq	r0, r0, r8, asr r0
     f28:	00000000 	andeq	r0, r0, r0
     f2c:	00164400 	andseq	r4, r6, r0, lsl #8
     f30:	00164c00 	andseq	r4, r6, r0, lsl #24
     f34:	53000100 	movwpl	r0, #256	; 0x100
     f38:	000017b4 			; <UNDEFINED> instruction: 0x000017b4
     f3c:	000017c4 	andeq	r1, r0, r4, asr #15
     f40:	7c530001 	mrrcvc	0, 0, r0, r3, cr1
     f44:	a0000018 	andge	r0, r0, r8, lsl r0
     f48:	01000018 	tsteq	r0, r8, lsl r0
     f4c:	18c85c00 	stmiane	r8, {sl, fp, ip, lr}^
     f50:	18dc0000 	ldmne	ip, {}^	; <UNPREDICTABLE>
     f54:	00010000 	andeq	r0, r1, r0
     f58:	0019505c 	andseq	r5, r9, ip, asr r0
     f5c:	00196800 	andseq	r6, r9, r0, lsl #16
     f60:	5c000100 	stfpls	f0, [r0], {-0}
     f64:	000019f4 	strdeq	r1, [r0], -r4
     f68:	00001a08 	andeq	r1, r0, r8, lsl #20
     f6c:	005c0001 	subseq	r0, ip, r1
     f70:	00000000 	andeq	r0, r0, r0
     f74:	90000000 	andls	r0, r0, r0
     f78:	9400001b 	strls	r0, [r0], #-27	; 0xffffffe5
     f7c:	0200001b 	andeq	r0, r0, #27
     f80:	94007d00 	strls	r7, [r0], #-3328	; 0xfffff300
     f84:	9c00001b 	stcls	0, cr0, [r0], {27}
     f88:	0200001b 	andeq	r0, r0, #27
     f8c:	9c007c00 	stcls	12, cr7, [r0], {-0}
     f90:	a400001b 	strge	r0, [r0], #-27	; 0xffffffe5
     f94:	0200001b 	andeq	r0, r0, #27
     f98:	00047b00 	andeq	r7, r4, r0, lsl #22
     f9c:	00000000 	andeq	r0, r0, r0
     fa0:	90000000 	andls	r0, r0, r0
     fa4:	a000001b 	andge	r0, r0, fp, lsl r0
     fa8:	0100001b 	tsteq	r0, fp, lsl r0
     fac:	00005000 	andeq	r5, r0, r0
     fb0:	00000000 	andeq	r0, r0, r0
     fb4:	1ba40000 	blne	fe900fbc <wmt_core_func_ctrl_cmd+0xfe8fdb9c>
     fb8:	1ba80000 	blne	fea00fc0 <wmt_core_func_ctrl_cmd+0xfe9fdba0>
     fbc:	00020000 	andeq	r0, r2, r0
     fc0:	1ba8007d 	blne	fea011bc <wmt_core_func_ctrl_cmd+0xfe9fdd9c>
     fc4:	1bb00000 	blne	fec00fcc <wmt_core_func_ctrl_cmd+0xfebfdbac>
     fc8:	00020000 	andeq	r0, r2, r0
     fcc:	1bb0007c 	blne	fec011c4 <wmt_core_func_ctrl_cmd+0xfebfdda4>
     fd0:	1d840000 	stcne	0, cr0, [r4]
     fd4:	00020000 	andeq	r0, r2, r0
     fd8:	0000047b 	andeq	r0, r0, fp, ror r4
     fdc:	00000000 	andeq	r0, r0, r0
     fe0:	1ba40000 	blne	fe900fe8 <wmt_core_func_ctrl_cmd+0xfe8fdbc8>
     fe4:	1bc80000 	blne	ff200fec <wmt_core_func_ctrl_cmd+0xff1fdbcc>
     fe8:	00010000 	andeq	r0, r1, r0
     fec:	001bc850 	andseq	ip, fp, r0, asr r8
     ff0:	001d0400 	andseq	r0, sp, r0, lsl #8
     ff4:	59000100 	stmdbpl	r0, {r8}
     ff8:	00001d04 	andeq	r1, r0, r4, lsl #26
     ffc:	00001d08 	andeq	r1, r0, r8, lsl #26
    1000:	08500001 	ldmdaeq	r0, {r0}^
    1004:	8400001d 	strhi	r0, [r0], #-29	; 0xffffffe3
    1008:	0100001d 	tsteq	r0, sp, lsl r0
    100c:	00005900 	andeq	r5, r0, r0, lsl #18
    1010:	00000000 	andeq	r0, r0, r0
    1014:	1be80000 	blne	ffa0101c <wmt_core_func_ctrl_cmd+0xff9fdbfc>
    1018:	1bf40000 	blne	ffd01020 <wmt_core_func_ctrl_cmd+0xffcfdc00>
    101c:	00010000 	andeq	r0, r1, r0
    1020:	001c3053 	andseq	r3, ip, r3, asr r0
    1024:	001c4000 	andseq	r4, ip, r0
    1028:	50000100 	andpl	r0, r0, r0, lsl #2
    102c:	00001c44 	andeq	r1, r0, r4, asr #24
    1030:	00001c80 	andeq	r1, r0, r0, lsl #25
    1034:	80560001 	subshi	r0, r6, r1
    1038:	9400001c 	strls	r0, [r0], #-28	; 0xffffffe4
    103c:	0100001c 	tsteq	r0, ip, lsl r0
    1040:	1c9c5300 	ldcne	3, cr5, [ip], {0}
    1044:	1ca00000 	stcne	0, cr0, [r0]
    1048:	00010000 	andeq	r0, r1, r0
    104c:	001ca053 	andseq	sl, ip, r3, asr r0
    1050:	001ca400 	andseq	sl, ip, r0, lsl #8
    1054:	56000100 	strpl	r0, [r0], -r0, lsl #2
    1058:	00001ca4 	andeq	r1, r0, r4, lsr #25
    105c:	00001cb0 			; <UNDEFINED> instruction: 0x00001cb0
    1060:	e0500001 	subs	r0, r0, r1
    1064:	0400001c 	streq	r0, [r0], #-28	; 0xffffffe4
    1068:	0100001d 	tsteq	r0, sp, lsl r0
    106c:	1d0c5600 	stcne	6, cr5, [ip, #-0]
    1070:	1d1c0000 	ldcne	0, cr0, [ip, #-0]
    1074:	00010000 	andeq	r0, r1, r0
    1078:	001d2056 	andseq	r2, sp, r6, asr r0
    107c:	001d2400 	andseq	r2, sp, r0, lsl #8
    1080:	56000100 	strpl	r0, [r0], -r0, lsl #2
    1084:	00001d34 	andeq	r1, r0, r4, lsr sp
    1088:	00001d84 	andeq	r1, r0, r4, lsl #27
    108c:	00560001 	subseq	r0, r6, r1
    1090:	00000000 	andeq	r0, r0, r0
    1094:	e8000000 	stmda	r0, {}	; <UNPREDICTABLE>
    1098:	0400001b 	streq	r0, [r0], #-27	; 0xffffffe5
    109c:	0200001d 	andeq	r0, r0, #29
    10a0:	0c507b00 	mrrceq	11, 0, r7, r0, cr0
    10a4:	2400001d 	strcs	r0, [r0], #-29	; 0xffffffe3
    10a8:	0200001d 	andeq	r0, r0, #29
    10ac:	00507b00 	subseq	r7, r0, r0, lsl #22
    10b0:	00000000 	andeq	r0, r0, r0
    10b4:	e8000000 	stmda	r0, {}	; <UNPREDICTABLE>
    10b8:	0400001b 	streq	r0, [r0], #-27	; 0xffffffe5
    10bc:	0200001d 	andeq	r0, r0, #29
    10c0:	0c4c7b00 	mcrreq	11, 0, r7, ip, cr0
    10c4:	2400001d 	strcs	r0, [r0], #-29	; 0xffffffe3
    10c8:	0200001d 	andeq	r0, r0, #29
    10cc:	004c7b00 	subeq	r7, ip, r0, lsl #22
    10d0:	00000000 	andeq	r0, r0, r0
    10d4:	84000000 	strhi	r0, [r0], #-0
    10d8:	8800001d 	stmdahi	r0, {r0, r2, r3, r4}
    10dc:	0200001d 	andeq	r0, r0, #29
    10e0:	88007d00 	stmdahi	r0, {r8, sl, fp, ip, sp, lr}
    10e4:	9000001d 	andls	r0, r0, sp, lsl r0
    10e8:	0200001d 	andeq	r0, r0, #29
    10ec:	90007c00 	andls	r7, r0, r0, lsl #24
    10f0:	e800001d 	stmda	r0, {r0, r2, r3, r4}
    10f4:	02000021 	andeq	r0, r0, #33	; 0x21
    10f8:	00047b00 	andeq	r7, r4, r0, lsl #22
    10fc:	00000000 	andeq	r0, r0, r0
    1100:	84000000 	strhi	r0, [r0], #-0
    1104:	a400001d 	strge	r0, [r0], #-29	; 0xffffffe3
    1108:	0100001d 	tsteq	r0, sp, lsl r0
    110c:	1da45000 	stcne	0, cr5, [r4]
    1110:	1e080000 	cdpne	0, 0, cr0, cr8, cr0, {0}
    1114:	00010000 	andeq	r0, r1, r0
    1118:	001e0857 	andseq	r0, lr, r7, asr r8
    111c:	001e1800 	andseq	r1, lr, r0, lsl #16
    1120:	50000100 	andpl	r0, r0, r0, lsl #2
    1124:	00001e40 	andeq	r1, r0, r0, asr #28
    1128:	000021e8 	andeq	r2, r0, r8, ror #3
    112c:	00570001 	subseq	r0, r7, r1
    1130:	00000000 	andeq	r0, r0, r0
    1134:	cc000000 	stcgt	0, cr0, [r0], {-0}
    1138:	fc00001d 	stc2	0, cr0, [r0], {29}
    113c:	0100001d 	tsteq	r0, sp, lsl r0
    1140:	1dfc5c00 	ldclne	12, cr5, [ip]
    1144:	1e4c0000 	cdpne	0, 4, cr0, cr12, cr0, {0}
    1148:	00010000 	andeq	r0, r1, r0
    114c:	001e4c56 	andseq	r4, lr, r6, asr ip
    1150:	001e7800 	andseq	r7, lr, r0, lsl #16
    1154:	5c000100 	stfpls	f0, [r0], {-0}
    1158:	00001e8c 	andeq	r1, r0, ip, lsl #29
    115c:	00001f70 	andeq	r1, r0, r0, ror pc
    1160:	80560001 	subshi	r0, r6, r1
    1164:	8400001f 	strhi	r0, [r0], #-31	; 0xffffffe1
    1168:	0100001f 	tsteq	r0, pc, lsl r0
    116c:	1f845c00 	svcne	0x00845c00
    1170:	1f880000 	svcne	0x00880000
    1174:	00010000 	andeq	r0, r1, r0
    1178:	001f8856 	andseq	r8, pc, r6, asr r8	; <UNPREDICTABLE>
    117c:	001fb000 	andseq	fp, pc, r0
    1180:	5c000100 	stfpls	f0, [r0], {-0}
    1184:	00001fcc 	andeq	r1, r0, ip, asr #31
    1188:	00001fd4 	ldrdeq	r1, [r0], -r4
    118c:	d4560001 	ldrble	r0, [r6], #-1
    1190:	e400001f 	str	r0, [r0], #-31	; 0xffffffe1
    1194:	0100001f 	tsteq	r0, pc, lsl r0
    1198:	1fe45c00 	svcne	0x00e45c00
    119c:	20000000 	andcs	r0, r0, r0
    11a0:	00010000 	andeq	r0, r1, r0
    11a4:	00200056 	eoreq	r0, r0, r6, asr r0
    11a8:	00202800 	eoreq	r2, r0, r0, lsl #16
    11ac:	5c000100 	stfpls	f0, [r0], {-0}
    11b0:	00002034 	andeq	r2, r0, r4, lsr r0
    11b4:	0000204c 	andeq	r2, r0, ip, asr #32
    11b8:	5c5c0001 	mrrcpl	0, 0, r0, ip, cr1
    11bc:	68000020 	stmdavs	r0, {r5}
    11c0:	01000020 	tsteq	r0, r0, lsr #32
    11c4:	20685600 	rsbcs	r5, r8, r0, lsl #12
    11c8:	20840000 	addcs	r0, r4, r0
    11cc:	00010000 	andeq	r0, r1, r0
    11d0:	0020885c 	eoreq	r8, r0, ip, asr r8
    11d4:	00209000 	eoreq	r9, r0, r0
    11d8:	53000100 	movwpl	r0, #256	; 0x100
    11dc:	000020a0 	andeq	r2, r0, r0, lsr #1
    11e0:	000020d0 	ldrdeq	r2, [r0], -r0
    11e4:	f8560001 			; <UNDEFINED> instruction: 0xf8560001
    11e8:	00000020 	andeq	r0, r0, r0, lsr #32
    11ec:	01000021 	tsteq	r0, r1, lsr #32
    11f0:	21285600 	teqcs	r8, r0, lsl #12
    11f4:	21340000 	teqcs	r4, r0
    11f8:	00010000 	andeq	r0, r1, r0
    11fc:	00213456 	eoreq	r3, r1, r6, asr r4
    1200:	00214400 	eoreq	r4, r1, r0, lsl #8
    1204:	53000100 	movwpl	r0, #256	; 0x100
    1208:	00002164 	andeq	r2, r0, r4, ror #2
    120c:	00002174 	andeq	r2, r0, r4, ror r1
    1210:	745c0001 	ldrbvc	r0, [ip], #-1
    1214:	e8000021 	stmda	r0, {r0, r5}
    1218:	01000021 	tsteq	r0, r1, lsr #32
    121c:	00005600 	andeq	r5, r0, r0, lsl #12
    1220:	00000000 	andeq	r0, r0, r0
    1224:	1e400000 	cdpne	0, 4, cr0, cr0, cr0, {0}
    1228:	1e4c0000 	cdpne	0, 4, cr0, cr12, cr0, {0}
    122c:	00010000 	andeq	r0, r1, r0
    1230:	001f4053 	andseq	r4, pc, r3, asr r0	; <UNPREDICTABLE>
    1234:	001f5800 	andseq	r5, pc, r0, lsl #16
    1238:	53000100 	movwpl	r0, #256	; 0x100
	...
    1244:	00001d98 	muleq	r0, r8, sp
    1248:	00001dfc 	strdeq	r1, [r0], -ip
    124c:	40550001 	subsmi	r0, r5, r1
    1250:	e800001e 	stmda	r0, {r1, r2, r3, r4}
    1254:	01000021 	tsteq	r0, r1, lsr #32
    1258:	00005500 	andeq	r5, r0, r0, lsl #10
    125c:	00000000 	andeq	r0, r0, r0
    1260:	1de40000 	stclne	0, cr0, [r4]
    1264:	1e4c0000 	cdpne	0, 4, cr0, cr12, cr0, {0}
    1268:	00020000 	andeq	r0, r2, r0
    126c:	1e70507b 	mrcne	0, 3, r5, cr0, cr11, {3}
    1270:	1f700000 	svcne	0x00700000
    1274:	00020000 	andeq	r0, r2, r0
    1278:	1f80507b 	svcne	0x0080507b
    127c:	1f880000 	svcne	0x00880000
    1280:	00020000 	andeq	r0, r2, r0
    1284:	2080507b 	addcs	r5, r0, fp, ror r0
    1288:	20d00000 	sbcscs	r0, r0, r0
    128c:	00020000 	andeq	r0, r2, r0
    1290:	2134507b 	teqcs	r4, fp, ror r0
    1294:	21640000 	cmncs	r4, r0
    1298:	00020000 	andeq	r0, r2, r0
    129c:	0000507b 	andeq	r5, r0, fp, ror r0
    12a0:	00000000 	andeq	r0, r0, r0
    12a4:	1de40000 	stclne	0, cr0, [r4]
    12a8:	1e4c0000 	cdpne	0, 4, cr0, cr12, cr0, {0}
    12ac:	00020000 	andeq	r0, r2, r0
    12b0:	1e704c7b 	mrcne	12, 3, r4, cr0, cr11, {3}
    12b4:	1f700000 	svcne	0x00700000
    12b8:	00020000 	andeq	r0, r2, r0
    12bc:	1f804c7b 	svcne	0x00804c7b
    12c0:	1f880000 	svcne	0x00880000
    12c4:	00020000 	andeq	r0, r2, r0
    12c8:	207c4c7b 	rsbscs	r4, ip, fp, ror ip
    12cc:	20d00000 	sbcscs	r0, r0, r0
    12d0:	00020000 	andeq	r0, r2, r0
    12d4:	21344c7b 	teqcs	r4, fp, ror ip
    12d8:	21640000 	cmncs	r4, r0
    12dc:	00020000 	andeq	r0, r2, r0
    12e0:	00004c7b 	andeq	r4, r0, fp, ror ip
    12e4:	00000000 	andeq	r0, r0, r0
    12e8:	21e80000 	mvncs	r0, r0
    12ec:	21ec0000 	mvncs	r0, r0
    12f0:	00020000 	andeq	r0, r2, r0
    12f4:	21ec007d 	mvncs	r0, sp, ror r0
    12f8:	21f40000 	mvnscs	r0, r0
    12fc:	00020000 	andeq	r0, r2, r0
    1300:	21f4007c 	mvnscs	r0, ip, ror r0
    1304:	22440000 	subcs	r0, r4, #0
    1308:	00020000 	andeq	r0, r2, r0
    130c:	0000047b 	andeq	r0, r0, fp, ror r4
    1310:	00000000 	andeq	r0, r0, r0
    1314:	21e80000 	mvncs	r0, r0
    1318:	22080000 	andcs	r0, r8, #0
    131c:	00010000 	andeq	r0, r1, r0
    1320:	00220850 	eoreq	r0, r2, r0, asr r8
    1324:	00221800 	eoreq	r1, r2, r0, lsl #16
    1328:	52000100 	andpl	r0, r0, #0, 2
    132c:	00002220 	andeq	r2, r0, r0, lsr #4
    1330:	00002228 	andeq	r2, r0, r8, lsr #4
    1334:	00520001 	subseq	r0, r2, r1
    1338:	00000000 	andeq	r0, r0, r0
    133c:	44000000 	strmi	r0, [r0], #-0
    1340:	48000022 	stmdami	r0, {r1, r5}
    1344:	02000022 	andeq	r0, r0, #34	; 0x22
    1348:	48007d00 	stmdami	r0, {r8, sl, fp, ip, sp, lr}
    134c:	50000022 	andpl	r0, r0, r2, lsr #32
    1350:	02000022 	andeq	r0, r0, #34	; 0x22
    1354:	50007c00 	andpl	r7, r0, r0, lsl #24
    1358:	b8000022 	stmdalt	r0, {r1, r5}
    135c:	02000023 	andeq	r0, r0, #35	; 0x23
    1360:	00047b00 	andeq	r7, r4, r0, lsl #22
    1364:	00000000 	andeq	r0, r0, r0
    1368:	44000000 	strmi	r0, [r0], #-0
    136c:	84000022 	strhi	r0, [r0], #-34	; 0xffffffde
    1370:	01000022 	tsteq	r0, r2, lsr #32
    1374:	22845000 	addcs	r5, r4, #0
    1378:	23b80000 			; <UNDEFINED> instruction: 0x23b80000
    137c:	00010000 	andeq	r0, r1, r0
    1380:	00000058 	andeq	r0, r0, r8, asr r0
    1384:	00000000 	andeq	r0, r0, r0
    1388:	0022e400 	eoreq	lr, r2, r0, lsl #8
    138c:	00238000 	eoreq	r8, r3, r0
    1390:	54000100 	strpl	r0, [r0], #-256	; 0xffffff00
    1394:	00002390 	muleq	r0, r0, r3
    1398:	000023b8 			; <UNDEFINED> instruction: 0x000023b8
    139c:	00540001 	subseq	r0, r4, r1
    13a0:	00000000 	andeq	r0, r0, r0
    13a4:	e8000000 	stmda	r0, {}	; <UNPREDICTABLE>
    13a8:	80000022 	andhi	r0, r0, r2, lsr #32
    13ac:	02000023 	andeq	r0, r0, #35	; 0x23
    13b0:	00587b00 	subseq	r7, r8, r0, lsl #22
    13b4:	00000000 	andeq	r0, r0, r0
    13b8:	b8000000 	stmdalt	r0, {}	; <UNPREDICTABLE>
    13bc:	bc000023 	stclt	0, cr0, [r0], {35}	; 0x23
    13c0:	02000023 	andeq	r0, r0, #35	; 0x23
    13c4:	bc007d00 	stclt	13, cr7, [r0], {-0}
    13c8:	c4000023 	strgt	r0, [r0], #-35	; 0xffffffdd
    13cc:	02000023 	andeq	r0, r0, #35	; 0x23
    13d0:	c4007c00 	strgt	r7, [r0], #-3072	; 0xfffff400
    13d4:	58000023 	stmdapl	r0, {r0, r1, r5}
    13d8:	02000026 	andeq	r0, r0, #38	; 0x26
    13dc:	00047b00 	andeq	r7, r4, r0, lsl #22
    13e0:	00000000 	andeq	r0, r0, r0
    13e4:	b8000000 	stmdalt	r0, {}	; <UNPREDICTABLE>
    13e8:	f8000023 			; <UNDEFINED> instruction: 0xf8000023
    13ec:	01000023 	tsteq	r0, r3, lsr #32
    13f0:	23f85000 	mvnscs	r5, #0
    13f4:	26580000 	ldrbcs	r0, [r8], -r0
    13f8:	00010000 	andeq	r0, r1, r0
    13fc:	00000056 	andeq	r0, r0, r6, asr r0
    1400:	00000000 	andeq	r0, r0, r0
    1404:	00265800 	eoreq	r5, r6, r0, lsl #16
    1408:	00265c00 	eoreq	r5, r6, r0, lsl #24
    140c:	7d000200 	sfmvc	f0, 4, [r0, #-0]
    1410:	00265c00 	eoreq	r5, r6, r0, lsl #24
    1414:	00266400 	eoreq	r6, r6, r0, lsl #8
    1418:	7c000200 	sfmvc	f0, 4, [r0], {-0}
    141c:	00266400 	eoreq	r6, r6, r0, lsl #8
    1420:	002a9c00 	eoreq	r9, sl, r0, lsl #24
    1424:	7b000200 	blvc	1c2c <opfunc_pwr_on+0x88>
    1428:	00000004 	andeq	r0, r0, r4
    142c:	00000000 	andeq	r0, r0, r0
    1430:	00265800 	eoreq	r5, r6, r0, lsl #16
    1434:	00268400 	eoreq	r8, r6, r0, lsl #8
    1438:	50000100 	andpl	r0, r0, r0, lsl #2
	...
    1444:	000027bc 			; <UNDEFINED> instruction: 0x000027bc
    1448:	00002804 	andeq	r2, r0, r4, lsl #16
    144c:	30580001 	subscc	r0, r8, r1
    1450:	4c000028 	stcmi	0, cr0, [r0], {40}	; 0x28
    1454:	01000028 	tsteq	r0, r8, lsr #32
    1458:	28805800 	stmcs	r0, {fp, ip, lr}
    145c:	29300000 	ldmdbcs	r0!, {}	; <UNPREDICTABLE>
    1460:	00010000 	andeq	r0, r1, r0
    1464:	0029d858 	eoreq	sp, r9, r8, asr r8
    1468:	002a1000 	eoreq	r1, sl, r0
    146c:	58000100 	stmdapl	r0, {r8}
    1470:	00002a58 	andeq	r2, r0, r8, asr sl
    1474:	00002a9c 	muleq	r0, ip, sl
    1478:	00580001 	subseq	r0, r8, r1
    147c:	00000000 	andeq	r0, r0, r0
    1480:	34000000 	strcc	r0, [r0], #-0
    1484:	d4000027 	strle	r0, [r0], #-39	; 0xffffffd9
    1488:	01000028 	tsteq	r0, r8, lsr #32
    148c:	290c5400 	stmdbcs	ip, {sl, ip, lr}
    1490:	29ec0000 	stmibcs	ip!, {}^	; <UNPREDICTABLE>
    1494:	00010000 	andeq	r0, r1, r0
    1498:	002a1054 	eoreq	r1, sl, r4, asr r0
    149c:	002a9c00 	eoreq	r9, sl, r0, lsl #24
    14a0:	54000100 	strpl	r0, [r0], #-256	; 0xffffff00
	...
    14ac:	000027c0 	andeq	r2, r0, r0, asr #15
    14b0:	00002804 	andeq	r2, r0, r4, lsl #16
    14b4:	507b0002 	rsbspl	r0, fp, r2
    14b8:	00002830 	andeq	r2, r0, r0, lsr r8
    14bc:	0000284c 	andeq	r2, r0, ip, asr #16
    14c0:	507b0002 	rsbspl	r0, fp, r2
    14c4:	00002880 	andeq	r2, r0, r0, lsl #17
    14c8:	00002930 	andeq	r2, r0, r0, lsr r9
    14cc:	507b0002 	rsbspl	r0, fp, r2
    14d0:	000029d8 	ldrdeq	r2, [r0], -r8
    14d4:	00002a10 	andeq	r2, r0, r0, lsl sl
    14d8:	507b0002 	rsbspl	r0, fp, r2
	...
    14e4:	00002794 	muleq	r0, r4, r7
    14e8:	000027dc 	ldrdeq	r2, [r0], -ip
    14ec:	f8570001 			; <UNDEFINED> instruction: 0xf8570001
    14f0:	04000027 	streq	r0, [r0], #-39	; 0xffffffd9
    14f4:	01000028 	tsteq	r0, r8, lsr #32
    14f8:	28285700 	stmdacs	r8!, {r8, r9, sl, ip, lr}
    14fc:	284c0000 	stmdacs	ip, {}^	; <UNPREDICTABLE>
    1500:	00010000 	andeq	r0, r1, r0
    1504:	00290c57 	eoreq	r0, r9, r7, asr ip
    1508:	00293000 	eoreq	r3, r9, r0
    150c:	57000100 	strpl	r0, [r0, -r0, lsl #2]
    1510:	000029b8 			; <UNDEFINED> instruction: 0x000029b8
    1514:	000029d8 	ldrdeq	r2, [r0], -r8
    1518:	24570001 	ldrbcs	r0, [r7], #-1
    151c:	2c00002a 	stccs	0, cr0, [r0], {42}	; 0x2a
    1520:	0100002a 	tsteq	r0, sl, lsr #32
    1524:	2a405700 	bcs	101712c <wmt_core_func_ctrl_cmd+0x1013d0c>
    1528:	2a480000 	bcs	1201530 <wmt_core_func_ctrl_cmd+0x11fe110>
    152c:	00010000 	andeq	r0, r1, r0
    1530:	00000057 	andeq	r0, r0, r7, asr r0
    1534:	00000000 	andeq	r0, r0, r0
    1538:	00278c00 	eoreq	r8, r7, r0, lsl #24
    153c:	00280400 	eoreq	r0, r8, r0, lsl #8
    1540:	59000100 	stmdbpl	r0, {r8}
    1544:	00002824 	andeq	r2, r0, r4, lsr #16
    1548:	0000284c 	andeq	r2, r0, ip, asr #16
    154c:	80590001 	subshi	r0, r9, r1
    1550:	30000028 	andcc	r0, r0, r8, lsr #32
    1554:	01000029 	tsteq	r0, r9, lsr #32
    1558:	29b45900 	ldmibcs	r4!, {r8, fp, ip, lr}
    155c:	2a100000 	bcs	401564 <wmt_core_func_ctrl_cmd+0x3fe144>
    1560:	00010000 	andeq	r0, r1, r0
    1564:	002a2059 	eoreq	r2, sl, r9, asr r0
    1568:	002a2c00 	eoreq	r2, sl, r0, lsl #24
    156c:	59000100 	stmdbpl	r0, {r8}
    1570:	00002a3c 	andeq	r2, r0, ip, lsr sl
    1574:	00002a48 	andeq	r2, r0, r8, asr #20
    1578:	00590001 	subseq	r0, r9, r1
    157c:	00000000 	andeq	r0, r0, r0
    1580:	90000000 	andls	r0, r0, r0
    1584:	04000027 	streq	r0, [r0], #-39	; 0xffffffd9
    1588:	01000028 	tsteq	r0, r8, lsr #32
    158c:	28185600 	ldmdacs	r8, {r9, sl, ip, lr}
    1590:	284c0000 	stmdacs	ip, {}^	; <UNPREDICTABLE>
    1594:	00010000 	andeq	r0, r1, r0
    1598:	00288056 	eoreq	r8, r8, r6, asr r0
    159c:	00293000 	eoreq	r3, r9, r0
    15a0:	56000100 	strpl	r0, [r0], -r0, lsl #2
    15a4:	00002954 	andeq	r2, r0, r4, asr r9
    15a8:	00002a9c 	muleq	r0, ip, sl
    15ac:	00560001 	subseq	r0, r6, r1
    15b0:	00000000 	andeq	r0, r0, r0
    15b4:	9c000000 	stcls	0, cr0, [r0], {-0}
    15b8:	a000002a 	andge	r0, r0, sl, lsr #32
    15bc:	0200002a 	andeq	r0, r0, #42	; 0x2a
    15c0:	a0007d00 	andge	r7, r0, r0, lsl #26
    15c4:	a800002a 	stmdage	r0, {r1, r3, r5}
    15c8:	0200002a 	andeq	r0, r0, #42	; 0x2a
    15cc:	a8007c00 	stmdage	r0, {sl, fp, ip, sp, lr}
    15d0:	f400002a 	vst4.8	{d0-d3}, [r0 :128], sl
    15d4:	0200002c 	andeq	r0, r0, #44	; 0x2c
    15d8:	00047b00 	andeq	r7, r4, r0, lsl #22
    15dc:	00000000 	andeq	r0, r0, r0
    15e0:	9c000000 	stcls	0, cr0, [r0], {-0}
    15e4:	c800002a 	stmdagt	r0, {r1, r3, r5}
    15e8:	0100002a 	tsteq	r0, sl, lsr #32
    15ec:	2ac85000 	bcs	ff2155f4 <wmt_core_func_ctrl_cmd+0xff2121d4>
    15f0:	2cf40000 	ldclcs	0, cr0, [r4]
    15f4:	00010000 	andeq	r0, r1, r0
    15f8:	00000059 	andeq	r0, r0, r9, asr r0
    15fc:	00000000 	andeq	r0, r0, r0
    1600:	002b3800 	eoreq	r3, fp, r0, lsl #16
    1604:	002bf000 	eoreq	pc, fp, r0
    1608:	76000200 	strvc	r0, [r0], -r0, lsl #4
    160c:	002c2c7e 	eoreq	r2, ip, lr, ror ip
    1610:	002cf400 	eoreq	pc, ip, r0, lsl #8
    1614:	76000200 	strvc	r0, [r0], -r0, lsl #4
    1618:	0000007e 	andeq	r0, r0, lr, ror r0
    161c:	00000000 	andeq	r0, r0, r0
    1620:	002bd000 	eoreq	sp, fp, r0
    1624:	002bd000 	eoreq	sp, fp, r0
    1628:	50000100 	andpl	r0, r0, r0, lsl #2
    162c:	00002bec 	andeq	r2, r0, ip, ror #23
    1630:	00002bf0 	strdeq	r2, [r0], -r0
    1634:	28500001 	ldmdacs	r0, {r0}^
    1638:	2c00002c 	stccs	0, cr0, [r0], {44}	; 0x2c
    163c:	0100002c 	tsteq	r0, ip, lsr #32
    1640:	2c405000 	marcs	acc0, r5, r0
    1644:	2c440000 	marcs	acc0, r0, r4
    1648:	00010000 	andeq	r0, r1, r0
    164c:	002c9850 	eoreq	r9, ip, r0, asr r8
    1650:	002c9c00 	eoreq	r9, ip, r0, lsl #24
    1654:	50000100 	andpl	r0, r0, r0, lsl #2
    1658:	00002cbc 			; <UNDEFINED> instruction: 0x00002cbc
    165c:	00002cf4 	strdeq	r2, [r0], -r4
    1660:	00500001 	subseq	r0, r0, r1
    1664:	00000000 	andeq	r0, r0, r0
    1668:	f4000000 	vst4.8	{d0-d3}, [r0], r0
    166c:	f800002c 			; <UNDEFINED> instruction: 0xf800002c
    1670:	0200002c 	andeq	r0, r0, #44	; 0x2c
    1674:	f8007d00 			; <UNDEFINED> instruction: 0xf8007d00
    1678:	0000002c 	andeq	r0, r0, ip, lsr #32
    167c:	0200002d 	andeq	r0, r0, #45	; 0x2d
    1680:	00007c00 	andeq	r7, r0, r0, lsl #24
    1684:	b400002d 	strlt	r0, [r0], #-45	; 0xffffffd3
    1688:	0200002e 	andeq	r0, r0, #46	; 0x2e
    168c:	00047b00 	andeq	r7, r4, r0, lsl #22
    1690:	00000000 	andeq	r0, r0, r0
    1694:	f4000000 	vst4.8	{d0-d3}, [r0], r0
    1698:	2c00002c 	stccs	0, cr0, [r0], {44}	; 0x2c
    169c:	0100002d 	tsteq	r0, sp, lsr #32
    16a0:	2d2c5000 	stccs	0, cr5, [ip, #-0]
    16a4:	2d300000 	ldccs	0, cr0, [r0, #-0]
    16a8:	00010000 	andeq	r0, r1, r0
    16ac:	00000055 	andeq	r0, r0, r5, asr r0
    16b0:	00000000 	andeq	r0, r0, r0
    16b4:	002eb400 	eoreq	fp, lr, r0, lsl #8
    16b8:	002eb800 	eoreq	fp, lr, r0, lsl #16
    16bc:	7d000200 	sfmvc	f0, 4, [r0, #-0]
    16c0:	002eb800 	eoreq	fp, lr, r0, lsl #16
    16c4:	002ec000 	eoreq	ip, lr, r0
    16c8:	7c000200 	sfmvc	f0, 4, [r0], {-0}
    16cc:	002ec000 	eoreq	ip, lr, r0
    16d0:	00342000 	eorseq	r2, r4, r0
    16d4:	7b000200 	blvc	1edc <opfunc_func_on+0x158>
    16d8:	00000004 	andeq	r0, r0, r4
    16dc:	00000000 	andeq	r0, r0, r0
    16e0:	002eb400 	eoreq	fp, lr, r0, lsl #8
    16e4:	002ef000 	eoreq	pc, lr, r0
    16e8:	50000100 	andpl	r0, r0, r0, lsl #2
    16ec:	00002ef0 	strdeq	r2, [r0], -r0
    16f0:	00003420 	andeq	r3, r0, r0, lsr #8
    16f4:	00540001 	subseq	r0, r4, r1
    16f8:	00000000 	andeq	r0, r0, r0
    16fc:	1c000000 	stcne	0, cr0, [r0], {-0}
    1700:	5800002f 	stmdapl	r0, {r0, r1, r2, r3, r5}
    1704:	0100002f 	tsteq	r0, pc, lsr #32
    1708:	2f8c5500 	svccs	0x008c5500
    170c:	30040000 	andcc	r0, r4, r0
    1710:	00010000 	andeq	r0, r1, r0
    1714:	00301455 	eorseq	r1, r0, r5, asr r4
    1718:	00304400 	eorseq	r4, r0, r0, lsl #8
    171c:	55000100 	strpl	r0, [r0, #-256]	; 0xffffff00
    1720:	0000305c 	andeq	r3, r0, ip, asr r0
    1724:	00003420 	andeq	r3, r0, r0, lsr #8
    1728:	00550001 	subseq	r0, r5, r1
    172c:	00000000 	andeq	r0, r0, r0
    1730:	20000000 	andcs	r0, r0, r0
    1734:	5800002f 	stmdapl	r0, {r0, r1, r2, r3, r5}
    1738:	0200002f 	andeq	r0, r0, #47	; 0x2f
    173c:	94507b00 	ldrbls	r7, [r0], #-2816	; 0xfffff500
    1740:	9c00002f 	stcls	0, cr0, [r0], {47}	; 0x2f
    1744:	0200002f 	andeq	r0, r0, #47	; 0x2f
    1748:	9c507b00 	mrrcls	11, 0, r7, r0, cr0
    174c:	a400002f 	strge	r0, [r0], #-47	; 0xffffffd1
    1750:	0100002f 	tsteq	r0, pc, lsr #32
    1754:	2fa45300 	svccs	0x00a45300
    1758:	30040000 	andcc	r0, r4, r0
    175c:	00020000 	andeq	r0, r2, r0
    1760:	3014507b 	andscc	r5, r4, fp, ror r0
    1764:	30440000 	subcc	r0, r4, r0
    1768:	00020000 	andeq	r0, r2, r0
    176c:	3090507b 	addscc	r5, r0, fp, ror r0
    1770:	31080000 	mrscc	r0, (UNDEF: 8)
    1774:	00020000 	andeq	r0, r2, r0
    1778:	3108507b 	tstcc	r8, fp, ror r0
    177c:	31180000 	tstcc	r8, r0
    1780:	00010000 	andeq	r0, r1, r0
    1784:	00311853 	eorseq	r1, r1, r3, asr r8
    1788:	00314800 	eorseq	r4, r1, r0, lsl #16
    178c:	7b000200 	blvc	1f94 <opfunc_func_on+0x210>
    1790:	00314850 	eorseq	r4, r1, r0, asr r8
    1794:	00318000 	eorseq	r8, r1, r0
    1798:	58000100 	stmdapl	r0, {r8}
    179c:	00003180 	andeq	r3, r0, r0, lsl #3
    17a0:	000031b8 			; <UNDEFINED> instruction: 0x000031b8
    17a4:	507b0002 	rsbspl	r0, fp, r2
    17a8:	000031c8 	andeq	r3, r0, r8, asr #3
    17ac:	000031f8 	strdeq	r3, [r0], -r8
    17b0:	f8580001 			; <UNDEFINED> instruction: 0xf8580001
    17b4:	00000031 	andeq	r0, r0, r1, lsr r0
    17b8:	02000032 	andeq	r0, r0, #50	; 0x32
    17bc:	00507b00 	subseq	r7, r0, r0, lsl #22
    17c0:	74000032 	strvc	r0, [r0], #-50	; 0xffffffce
    17c4:	01000032 	tsteq	r0, r2, lsr r0
    17c8:	32745800 	rsbscc	r5, r4, #0, 16
    17cc:	33480000 	movtcc	r0, #32768	; 0x8000
    17d0:	00020000 	andeq	r0, r2, r0
    17d4:	3348507b 	movtcc	r5, #32891	; 0x807b
    17d8:	34200000 	strtcc	r0, [r0], #-0
    17dc:	00010000 	andeq	r0, r1, r0
    17e0:	00000058 	andeq	r0, r0, r8, asr r0
    17e4:	00000000 	andeq	r0, r0, r0
    17e8:	002fdc00 	eoreq	sp, pc, r0, lsl #24
    17ec:	00300400 	eorseq	r0, r0, r0, lsl #8
    17f0:	56000100 	strpl	r0, [r0], -r0, lsl #2
    17f4:	00003014 	andeq	r3, r0, r4, lsl r0
    17f8:	00003044 	andeq	r3, r0, r4, asr #32
    17fc:	00560001 	subseq	r0, r6, r1
    1800:	00000000 	andeq	r0, r0, r0
    1804:	20000000 	andcs	r0, r0, r0
    1808:	24000034 	strcs	r0, [r0], #-52	; 0xffffffcc
    180c:	02000034 	andeq	r0, r0, #52	; 0x34
    1810:	24007d00 	strcs	r7, [r0], #-3328	; 0xfffff300
    1814:	2c000034 	stccs	0, cr0, [r0], {52}	; 0x34
    1818:	02000034 	andeq	r0, r0, #52	; 0x34
    181c:	2c007c00 	stccs	12, cr7, [r0], {-0}
    1820:	b8000034 	stmdalt	r0, {r2, r4, r5}
    1824:	02000035 	andeq	r0, r0, #53	; 0x35
    1828:	00047b00 	andeq	r7, r4, r0, lsl #22
    182c:	00000000 	andeq	r0, r0, r0
    1830:	20000000 	andcs	r0, r0, r0
    1834:	48000034 	stmdami	r0, {r2, r4, r5}
    1838:	01000034 	tsteq	r0, r4, lsr r0
    183c:	34485000 	strbcc	r5, [r8], #-0
    1840:	35b80000 	ldrcc	r0, [r8, #0]!
    1844:	00010000 	andeq	r0, r1, r0
    1848:	00000055 	andeq	r0, r0, r5, asr r0
    184c:	00000000 	andeq	r0, r0, r0
    1850:	00342000 	eorseq	r2, r4, r0
    1854:	00344400 	eorseq	r4, r4, r0, lsl #8
    1858:	51000100 	mrspl	r0, (UNDEF: 16)
    185c:	00003444 	andeq	r3, r0, r4, asr #8
    1860:	00003468 	andeq	r3, r0, r8, ror #8
    1864:	00560001 	subseq	r0, r6, r1
    1868:	00000000 	andeq	r0, r0, r0
    186c:	a4000000 	strge	r0, [r0], #-0
    1870:	b8000034 	stmdalt	r0, {r2, r4, r5}
    1874:	01000034 	tsteq	r0, r4, lsr r0
    1878:	34d85300 	ldrbcc	r5, [r8], #768	; 0x300
    187c:	34e80000 	strbtcc	r0, [r8], #0
    1880:	00010000 	andeq	r0, r1, r0
    1884:	0034ec53 	eorseq	lr, r4, r3, asr ip
    1888:	0034f400 	eorseq	pc, r4, r0, lsl #8
    188c:	53000100 	movwpl	r0, #256	; 0x100
    1890:	00003538 	andeq	r3, r0, r8, lsr r5
    1894:	00003548 	andeq	r3, r0, r8, asr #10
    1898:	00530001 	subseq	r0, r3, r1
    189c:	00000000 	andeq	r0, r0, r0
    18a0:	Address 0x000018a0 is out of bounds.


Disassembly of section .debug_pubnames:

00000000 <.debug_pubnames>:
   0:	00000135 	andeq	r0, r0, r5, lsr r1
   4:	00000002 	andeq	r0, r0, r2
   8:	1f230000 	svcne	0x00230000
   c:	0b370000 	bleq	dc0014 <wmt_core_func_ctrl_cmd+0xdbcbf4>
  10:	6d770000 	ldclvs	0, cr0, [r7, #-0]
  14:	6f635f74 	svcvs	0x00635f74
  18:	705f6572 	subsvc	r6, pc, r2, ror r5	; <UNPREDICTABLE>
  1c:	68637461 	stmdavs	r3!, {r0, r5, r6, sl, ip, sp, lr}^
  20:	6568635f 	strbvs	r6, [r8, #-863]!	; 0xfffffca1
  24:	9b006b63 	blls	1adb8 <wmt_core_func_ctrl_cmd+0x17998>
  28:	7700000b 	strvc	r0, [r0, -fp]
  2c:	635f746d 	cmpvs	pc, #1828716544	; 0x6d000000
  30:	5f65726f 	svcpl	0x0065726f
  34:	6469706f 	strbtvs	r7, [r9], #-111	; 0xffffff91
  38:	6e61685f 	mcrvs	8, 3, r6, cr1, cr15, {2}
  3c:	72656c64 	rsbvc	r6, r5, #100, 24	; 0x6400
  40:	000c0f00 	andeq	r0, ip, r0, lsl #30
  44:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
  48:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
  4c:	706f5f65 	rsbvc	r5, pc, r5, ror #30
  50:	63006469 	movwvs	r6, #1129	; 0x469
  54:	7700000c 	strvc	r0, [r0, -ip]
  58:	635f746d 	cmpvs	pc, #1828716544	; 0x6d000000
  5c:	5f65726f 	svcpl	0x0065726f
  60:	6e696564 	cdpvs	5, 6, cr6, cr9, cr4, {3}
  64:	7d007469 	cfstrsvc	mvf7, [r0, #-420]	; 0xfffffe5c
  68:	7700000c 	strvc	r0, [r0, -ip]
  6c:	635f746d 	cmpvs	pc, #1828716544	; 0x6d000000
  70:	5f65726f 	svcpl	0x0065726f
  74:	74696e69 	strbtvc	r6, [r9], #-3689	; 0xfffff197
  78:	000ca600 	andeq	sl, ip, r0, lsl #12
  7c:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
  80:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
  84:	75645f65 	strbvc	r5, [r4, #-3941]!	; 0xfffff09b
  88:	645f706d 	ldrbvs	r7, [pc], #-109	; 90 <.debug_pubnames+0x90>
  8c:	00617461 	rsbeq	r7, r1, r1, ror #8
  90:	00000e03 	andeq	r0, r0, r3, lsl #28
  94:	5f746d77 	svcpl	0x00746d77
  98:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  9c:	7274635f 	rsbsvc	r6, r4, #2080374785	; 0x7c000001
  a0:	0f6e006c 	svceq	0x006e006c
  a4:	6d770000 	ldclvs	0, cr0, [r7, #-0]
  a8:	6f635f74 	svcvs	0x00635f74
  ac:	725f6572 	subsvc	r6, pc, #478150656	; 0x1c800000
  b0:	6c665f78 	stclvs	15, cr5, [r6], #-480	; 0xfffffe20
  b4:	00687375 	rsbeq	r7, r8, r5, ror r3
  b8:	00000fd0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
  bc:	5f746d77 	svcpl	0x00746d77
  c0:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  c4:	0078725f 	rsbseq	r7, r8, pc, asr r2
  c8:	000012d9 	ldrdeq	r1, [r0], -r9
  cc:	5f746d77 	svcpl	0x00746d77
  d0:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  d4:	0078745f 	rsbseq	r7, r8, pc, asr r4
  d8:	00001349 	andeq	r1, r0, r9, asr #6
  dc:	5f746d77 	svcpl	0x00746d77
  e0:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
  e4:	696e695f 	stmdbvs	lr!, {r0, r1, r2, r3, r4, r6, r8, fp, sp, lr}^
  e8:	63735f74 	cmnvs	r3, #116, 30	; 0x1d0
  ec:	74706972 	ldrbtvc	r6, [r0], #-2418	; 0xfffff68e
  f0:	0013e100 	andseq	lr, r3, r0, lsl #2
  f4:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
  f8:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
  fc:	65725f65 	ldrbvs	r5, [r2, #-3941]!	; 0xfffff09b
 100:	77725f67 	ldrbvc	r5, [r2, -r7, ror #30]!
 104:	7761725f 			; <UNDEFINED> instruction: 0x7761725f
 108:	001bf200 	andseq	pc, fp, r0, lsl #4
 10c:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
 110:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
 114:	75665f65 	strbvc	r5, [r6, #-3941]!	; 0xfffff09b
 118:	635f636e 	cmpvs	pc, #-1207959551	; 0xb8000001
 11c:	5f6c7274 	svcpl	0x006c7274
 120:	00646d63 	rsbeq	r6, r4, r3, ror #26
 124:	00001f10 	andeq	r1, r0, r0, lsl pc
 128:	6d577067 	ldclvs	0, cr7, [r7, #-412]	; 0xfffffe64
 12c:	6e754674 	mrcvs	6, 3, r4, cr5, cr4, {3}
 130:	73704f63 	cmnvc	r0, #396	; 0x18c
 134:	00000000 	andeq	r0, r0, r0
	...

Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	0000001c 	andeq	r0, r0, ip, lsl r0
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
	...
  14:	000035b8 			; <UNDEFINED> instruction: 0x000035b8
	...

Disassembly of section .debug_ranges:

00000000 <.debug_ranges>:
   0:	00000fe0 	andeq	r0, r0, r0, ror #31
   4:	00001010 	andeq	r1, r0, r0, lsl r0
   8:	00001074 	andeq	r1, r0, r4, ror r0
   c:	000010e4 	andeq	r1, r0, r4, ror #1
	...
  18:	00001410 	andeq	r1, r0, r0, lsl r4
  1c:	00001468 	andeq	r1, r0, r8, ror #8
  20:	000014b0 			; <UNDEFINED> instruction: 0x000014b0
  24:	000014fc 	strdeq	r1, [r0], -ip
	...
  30:	00001624 	andeq	r1, r0, r4, lsr #12
  34:	0000168c 	andeq	r1, r0, ip, lsl #13
  38:	000019e4 	andeq	r1, r0, r4, ror #19
  3c:	000019f4 	strdeq	r1, [r0], -r4
  40:	00001950 	andeq	r1, r0, r0, asr r9
  44:	000019a0 	andeq	r1, r0, r0, lsr #19
  48:	000017d8 	ldrdeq	r1, [r0], -r8
  4c:	000018ac 	andeq	r1, r0, ip, lsr #17
  50:	000017b4 			; <UNDEFINED> instruction: 0x000017b4
  54:	000017cc 	andeq	r1, r0, ip, asr #15
	...
  60:	00001624 	andeq	r1, r0, r4, lsr #12
  64:	0000168c 	andeq	r1, r0, ip, lsl #13
  68:	000019e4 	andeq	r1, r0, r4, ror #19
  6c:	000019f4 	strdeq	r1, [r0], -r4
  70:	00001950 	andeq	r1, r0, r0, asr r9
  74:	000019a0 	andeq	r1, r0, r0, lsr #19
  78:	000017d8 	ldrdeq	r1, [r0], -r8
  7c:	000018ac 	andeq	r1, r0, ip, lsr #17
  80:	000017b4 			; <UNDEFINED> instruction: 0x000017b4
  84:	000017cc 	andeq	r1, r0, ip, asr #15
	...
  90:	00001814 	andeq	r1, r0, r4, lsl r8
  94:	00001848 	andeq	r1, r0, r8, asr #16
  98:	000019e4 	andeq	r1, r0, r4, ror #19
  9c:	000019f4 	strdeq	r1, [r0], -r4
  a0:	00001970 	andeq	r1, r0, r0, ror r9
  a4:	00001978 	andeq	r1, r0, r8, ror r9
	...
  b0:	00001de4 	andeq	r1, r0, r4, ror #27
  b4:	00001e40 	andeq	r1, r0, r0, asr #28
  b8:	00001f80 	andeq	r1, r0, r0, lsl #31
  bc:	00001f88 	andeq	r1, r0, r8, lsl #31
	...
  c8:	00001de4 	andeq	r1, r0, r4, ror #27
  cc:	00001e40 	andeq	r1, r0, r0, asr #28
  d0:	00001f80 	andeq	r1, r0, r0, lsl #31
  d4:	00001f88 	andeq	r1, r0, r8, lsl #31
	...

Disassembly of section .debug_str:

00000000 <.debug_str>:
       0:	5f544d57 	svcpl	0x00544d57
       4:	4f494453 	svcmi	0x00494453
       8:	4e55465f 	mrcmi	6, 2, r4, cr5, cr15, {2}
       c:	49575f43 	ldmdbmi	r7, {r0, r1, r6, r8, r9, sl, fp, ip, lr}^
      10:	73004946 	movwvc	r4, #2374	; 0x946
      14:	6e695f77 	mcrvs	15, 3, r5, cr9, cr7, {3}
      18:	63007469 	movwvs	r7, #1129	; 0x469
      1c:	5f78656f 	svcpl	0x0078656f
      20:	5f746d77 	svcpl	0x00746d77
      24:	69666977 	stmdbvs	r6!, {r0, r1, r2, r4, r5, r6, r8, fp, sp, lr}^
      28:	6d69745f 	cfstrdvs	mvd7, [r9, #-380]!	; 0xfffffe84
      2c:	74635f65 	strbtvc	r5, [r3], #-3941	; 0xfffff09b
      30:	3475006c 	ldrbtcc	r0, [r5], #-108	; 0xffffff94
      34:	63746150 	cmnvs	r4, #80, 2
      38:	72655668 	rsbvc	r5, r5, #104, 12	; 0x6800000
      3c:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
      40:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
      44:	706f5f65 	rsbvc	r5, pc, r5, ror #30
      48:	685f6469 	ldmdavs	pc, {r0, r3, r5, r6, sl, sp, lr}^	; <UNPREDICTABLE>
      4c:	6c646e61 	stclvs	14, cr6, [r4], #-388	; 0xfffffe7c
      50:	57007265 	strpl	r7, [r0, -r5, ror #4]
      54:	535f544d 	cmppl	pc, #1291845632	; 0x4d000000
      58:	435f5054 	cmpmi	pc, #84	; 0x54
      5c:	5f464e4f 	svcpl	0x00464e4f
      60:	00594452 	subseq	r4, r9, r2, asr r4
      64:	544d575f 	strbpl	r5, [sp], #-1887	; 0xfffff8a1
      68:	5f43495f 	svcpl	0x0043495f
      6c:	5f4e4950 	svcpl	0x004e4950
      70:	005f4449 	subseq	r4, pc, r9, asr #8
      74:	5f544d57 	svcpl	0x00544d57
      78:	4c525443 	cfldrdmi	mvd5, [r2], {67}	; 0x43
      7c:	4957485f 	ldmdbmi	r7, {r0, r1, r2, r3, r4, r6, fp, lr}^
      80:	52455644 	subpl	r5, r5, #68, 12	; 0x4400000
      84:	5445535f 	strbpl	r5, [r5], #-863	; 0xfffffca1
      88:	656f6300 	strbvs	r6, [pc, #-768]!	; fffffd90 <wmt_core_func_ctrl_cmd+0xffffc970>
      8c:	74625f78 	strbtvc	r5, [r2], #-3960	; 0xfffff088
      90:	7373725f 	cmnvc	r3, #-268435451	; 0xf0000005
      94:	696d5f69 	stmdbvs	sp!, {r0, r3, r5, r6, r8, r9, sl, fp, ip, lr}^
      98:	696c5f64 	stmdbvs	ip!, {r2, r5, r6, r8, r9, sl, fp, ip, lr}^
      9c:	0074696d 	rsbseq	r6, r4, sp, ror #18
      a0:	4f43504f 	svcmi	0x0043504f
      a4:	495f4544 	ldmdbmi	pc, {r2, r6, r8, sl, lr}^	; <UNPREDICTABLE>
      a8:	4800544e 	stmdami	r0, {r1, r2, r3, r6, sl, ip, lr}
      ac:	5f54534f 	svcpl	0x0054534f
      b0:	4b415741 	blmi	1055dbc <wmt_core_func_ctrl_cmd+0x105299c>
      b4:	4d570045 	ldclmi	0, cr0, [r7, #-276]	; 0xfffffeec
      b8:	504f5f54 	subpl	r5, pc, r4, asr pc	; <UNPREDICTABLE>
      bc:	455f4449 	ldrbmi	r4, [pc, #-1097]	; fffffc7b <wmt_core_func_ctrl_cmd+0xffffc85b>
      c0:	45535546 	ldrbmi	r5, [r3, #-1350]	; 0xfffffaba
      c4:	0057525f 	subseq	r5, r7, pc, asr r2
      c8:	5f544d57 	svcpl	0x00544d57
      cc:	534e5344 	movtpl	r5, #58180	; 0xe344
      d0:	444d435f 	strbmi	r4, [sp], #-863	; 0xfffffca1
      d4:	74766500 	ldrbtvc	r6, [r6], #-1280	; 0xfffffb00
      d8:	6675625f 			; <UNDEFINED> instruction: 0x6675625f
      dc:	72777000 	rsbsvc	r7, r7, #0
      e0:	5f6e6f5f 	svcpl	0x006e6f5f
      e4:	5f6f646c 	svcpl	0x006f646c
      e8:	746f6c73 	strbtvc	r6, [pc], #-3187	; f0 <.debug_str+0xf0>
      ec:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
      f0:	5353415f 	cmppl	r3, #-1073741801	; 0xc0000017
      f4:	5f545245 	svcpl	0x00545245
      f8:	00444d43 	subeq	r4, r4, r3, asr #26
      fc:	5f544d57 	svcpl	0x00544d57
     100:	5f464948 	svcpl	0x00464948
     104:	54524155 	ldrbpl	r4, [r2], #-341	; 0xfffffeab
     108:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
     10c:	6e75665f 	mrcvs	6, 3, r6, cr5, cr15, {2}
     110:	74625f63 	strbtvc	r5, [r2], #-3939	; 0xfffff09d
     114:	73706f5f 	cmnvc	r0, #380	; 0x17c
     118:	656f6300 	strbvs	r6, [pc, #-768]!	; fffffe20 <wmt_core_func_ctrl_cmd+0xffffca00>
     11c:	78655f78 	stmdavc	r5!, {r3, r4, r5, r6, r8, r9, sl, fp, ip, lr}^
     120:	74705f74 	ldrbtvc	r5, [r0], #-3956	; 0xfffff08c
     124:	69775f61 	ldmdbvs	r7!, {r0, r5, r6, r8, r9, sl, fp, ip, lr}^
     128:	625f6966 	subsvs	r6, pc, #1671168	; 0x198000
     12c:	6f635f74 	svcvs	0x00635f74
     130:	72745f6e 	rsbsvc	r5, r4, #440	; 0x1b8
     134:	77700078 			; <UNDEFINED> instruction: 0x77700078
     138:	6e6f5f72 	mcrvs	15, 3, r5, cr15, cr2, {3}
     13c:	7974725f 	ldmdbvc	r4!, {r0, r1, r2, r3, r4, r6, r9, ip, sp, lr}^
     140:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
     144:	7370675f 	cmnvc	r0, #24903680	; 0x17c0000
     148:	616e6c5f 	cmnvs	lr, pc, asr ip
     14c:	6e69705f 	mcrvs	0, 3, r7, cr9, cr15, {2}
     150:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     154:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
     158:	58545f4c 	ldmdapl	r4, {r2, r3, r6, r8, r9, sl, fp, ip, lr}^
     15c:	646d6300 	strbtvs	r6, [sp], #-768	; 0xfffffd00
     160:	44006f4e 	strmi	r6, [r0], #-3918	; 0xfffff0b2
     164:	535f5652 	cmppl	pc, #85983232	; 0x5200000
     168:	505f5354 	subspl	r5, pc, r4, asr r3	; <UNPREDICTABLE>
     16c:	5245574f 	subpl	r5, r5, #20709376	; 0x13c0000
     170:	46464f5f 			; <UNDEFINED> instruction: 0x46464f5f
     174:	34756100 	ldrbtcc	r6, [r5], #-256	; 0xffffff00
     178:	43666948 	cmnmi	r6, #72, 18	; 0x120000
     17c:	00666e6f 	rsbeq	r6, r6, pc, ror #28
     180:	5f667562 	svcpl	0x00667562
     184:	676e656c 	strbvs	r6, [lr, -ip, ror #10]!
     188:	57006874 	smlsdxpl	r0, r4, r8, r6
     18c:	435f544d 	cmpmi	pc, #1291845632	; 0x4d000000
     190:	4458454f 	ldrbmi	r4, [r8], #-1359	; 0xfffffab1
     194:	335f4742 	cmpcc	pc, #17301504	; 0x1080000
     198:	5456455f 	ldrbpl	r4, [r6], #-1375	; 0xfffffaa1
     19c:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     1a0:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
     1a4:	41505f4c 	cmpmi	r0, ip, asr #30
     1a8:	5f484354 	svcpl	0x00484354
     1ac:	52414553 	subpl	r4, r1, #348127232	; 0x14c00000
     1b0:	63004843 	movwvs	r4, #2115	; 0x843
     1b4:	5f78656f 	svcpl	0x0078656f
     1b8:	69666977 	stmdbvs	r6!, {r0, r1, r2, r4, r5, r6, r8, fp, sp, lr}^
     1bc:	7373725f 	cmnvc	r3, #-268435451	; 0xf0000005
     1c0:	6f6c5f69 	svcvs	0x006c5f69
     1c4:	5f726577 	svcpl	0x00726577
     1c8:	696d696c 	stmdbvs	sp!, {r2, r3, r5, r6, r8, fp, sp, lr}^
     1cc:	61750074 	cmnvs	r5, r4, ror r0
     1d0:	63467472 	movtvs	r7, #25714	; 0x6472
     1d4:	6c727443 	cfldrdvs	mvd7, [r2], #-268	; 0xfffffef4
     1d8:	70797400 	rsbsvc	r7, r9, r0, lsl #8
     1dc:	74730065 	ldrbtvc	r0, [r3], #-101	; 0xffffff9b
     1e0:	57007461 	strpl	r7, [r0, -r1, ror #8]
     1e4:	5244544d 	subpl	r5, r4, #1291845632	; 0x4d000000
     1e8:	59545f56 	ldmdbpl	r4, {r1, r2, r4, r6, r8, r9, sl, fp, ip, lr}^
     1ec:	4d5f4550 	cfldr64mi	mvdx4, [pc, #-320]	; b4 <.debug_str+0xb4>
     1f0:	57005841 	strpl	r5, [r0, -r1, asr #16]
     1f4:	435f544d 	cmpmi	pc, #1291845632	; 0x4d000000
     1f8:	5f4c5254 	svcpl	0x004c5254
     1fc:	5f505453 	svcpl	0x00505453
     200:	00545352 	subseq	r5, r4, r2, asr r3
     204:	316c6176 	smccc	50710	; 0xc616
     208:	6c617600 	stclvs	6, cr7, [r1], #-0
     20c:	575f0032 	smmlarpl	pc, r2, r0, r0	; <UNPREDICTABLE>
     210:	495f544d 	ldmdbmi	pc, {r0, r2, r3, r6, sl, ip, lr}^	; <UNPREDICTABLE>
     214:	49505f43 	ldmdbmi	r0, {r0, r1, r6, r8, r9, sl, fp, ip, lr}^
     218:	54535f4e 	ldrbpl	r5, [r3], #-3918	; 0xfffff0b2
     21c:	5f455441 	svcpl	0x00455441
     220:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     224:	5345545f 	movtpl	r5, #21599	; 0x545f
     228:	504c5f54 	subpl	r5, ip, r4, asr pc
     22c:	455f4b42 	ldrbmi	r4, [pc, #-2882]	; fffff6f2 <wmt_core_func_ctrl_cmd+0xffffc2d2>
     230:	62005456 	andvs	r5, r0, #1442840576	; 0x56000000
     234:	654c6675 	strbvs	r6, [ip, #-1653]	; 0xfffff98b
     238:	7463006e 	strbtvc	r0, [r3], #-110	; 0xffffff92
     23c:	61446c72 	hvcvs	18114	; 0x46c2
     240:	77006174 	smlsdxvc	r0, r4, r1, r6
     244:	635f746d 	cmpvs	pc, #1828716544	; 0x6d000000
     248:	5f65726f 	svcpl	0x0065726f
     24c:	706d7564 	rsbvc	r7, sp, r4, ror #10
     250:	6e75665f 	mrcvs	6, 3, r6, cr5, cr15, {2}
     254:	74735f63 	ldrbtvc	r5, [r3], #-3939	; 0xfffff09d
     258:	00657461 	rsbeq	r7, r5, r1, ror #8
     25c:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
     260:	735f636e 	cmpvc	pc, #-1207959551	; 0xb8000001
     264:	725f7074 	subsvc	r7, pc, #116	; 0x74
     268:	57007473 	smlsdxpl	r0, r3, r4, r7
     26c:	435f544d 	cmpmi	pc, #1291845632	; 0x4d000000
     270:	5f4c5254 	svcpl	0x004c5254
     274:	41544144 	cmpmi	r4, r4, asr #2
     278:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
     27c:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
     280:	61705f65 	cmnvs	r0, r5, ror #30
     284:	5f686374 	svcpl	0x00686374
     288:	63656863 	cmnvs	r5, #6488064	; 0x630000
     28c:	4e45006b 	cdpmi	0, 4, cr0, cr5, cr11, {3}
     290:	575f4d55 			; <UNDEFINED> instruction: 0x575f4d55
     294:	5244544d 	subpl	r5, r4, #1291845632	; 0x4d000000
     298:	59545f56 	ldmdbpl	r4, {r1, r2, r4, r6, r8, r9, sl, fp, ip, lr}^
     29c:	545f4550 	ldrbpl	r4, [pc], #-1360	; 2a4 <.debug_str+0x2a4>
     2a0:	5f575300 	svcpl	0x00575300
     2a4:	54494e49 	strbpl	r4, [r9], #-3657	; 0xfffff1b7
     2a8:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     2ac:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
     2b0:	54535f4c 	ldrbpl	r5, [r3], #-3916	; 0xfffff0b4
     2b4:	4c435f50 	mcrrmi	15, 5, r5, r3, cr0
     2b8:	0045534f 	subeq	r5, r5, pc, asr #6
     2bc:	78656f63 	stmdavc	r5!, {r0, r1, r5, r6, r8, r9, sl, fp, sp, lr}^
     2c0:	6669775f 			; <UNDEFINED> instruction: 0x6669775f
     2c4:	73725f69 	cmnvc	r2, #420	; 0x1a4
     2c8:	755f6973 	ldrbvc	r6, [pc, #-2419]	; fffff95d <wmt_core_func_ctrl_cmd+0xffffc53d>
     2cc:	72657070 	rsbvc	r7, r5, #112	; 0x70
     2d0:	6d696c5f 	stclvs	12, cr6, [r9, #-380]!	; 0xfffffe84
     2d4:	6f007469 	svcvs	0x00007469
     2d8:	00644970 	rsbeq	r4, r4, r0, ror r9
     2dc:	676e6f6c 	strbvs	r6, [lr, -ip, ror #30]!
     2e0:	746e6920 	strbtvc	r6, [lr], #-2336	; 0xfffff6e0
     2e4:	74737400 	ldrbtvc	r7, [r3], #-1024	; 0xfffffc00
     2e8:	53747645 	cmnpl	r4, #72351744	; 0x4500000
     2ec:	4d57007a 	ldclmi	0, cr0, [r7, #-488]	; 0xfffffe18
     2f0:	4f485f54 	svcmi	0x00485f54
     2f4:	415f5453 	cmpmi	pc, r3, asr r4	; <UNPREDICTABLE>
     2f8:	454b4157 	strbmi	r4, [fp, #-343]	; 0xfffffea9
     2fc:	5456455f 	ldrbpl	r4, [r6], #-1375	; 0xfffffaa1
     300:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     304:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
     308:	45475f4c 	strbmi	r5, [r7, #-3916]	; 0xfffff0b4
     30c:	41505f54 	cmpmi	r0, r4, asr pc
     310:	5f484354 	svcpl	0x00484354
     314:	004d554e 	subeq	r5, sp, lr, asr #10
     318:	544d575f 	strbpl	r5, [sp], #-1887	; 0xfffff8a1
     31c:	4649485f 			; <UNDEFINED> instruction: 0x4649485f
     320:	4e4f435f 	mcrmi	3, 2, r4, cr15, cr15, {2}
     324:	4d570046 	ldclmi	0, cr0, [r7, #-280]	; 0xfffffee8
     328:	43495f54 	movtmi	r5, #40788	; 0x9f54
     32c:	4e49505f 	mcrmi	0, 2, r5, cr9, cr15, {2}
     330:	5349445f 	movtpl	r4, #37983	; 0x945f
     334:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     338:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
     33c:	44535f4c 	ldrbmi	r5, [r3], #-3916	; 0xfffff0b4
     340:	465f4f49 	ldrbmi	r4, [pc], -r9, asr #30
     344:	00434e55 	subeq	r4, r3, r5, asr lr
     348:	5f544d57 	svcpl	0x00544d57
     34c:	45454c53 	strbmi	r4, [r5, #-3155]	; 0xfffff3ad
     350:	56455f50 			; <UNDEFINED> instruction: 0x56455f50
     354:	4d570054 	ldclmi	0, cr0, [r7, #-336]	; 0xfffffeb0
     358:	54435f54 	strbpl	r5, [r3], #-3924	; 0xfffff0ac
     35c:	4d570058 	ldclmi	0, cr0, [r7, #-352]	; 0xfffffea0
     360:	54535f54 	ldrbpl	r5, [r3], #-3924	; 0xfffff0ac
     364:	4f435f50 	svcmi	0x00435f50
     368:	455f464e 	ldrbmi	r4, [pc, #-1614]	; fffffd22 <wmt_core_func_ctrl_cmd+0xffffc902>
     36c:	4d57004e 	ldclmi	0, cr0, [r7, #-312]	; 0xfffffec8
     370:	44535f54 	ldrbmi	r5, [r3], #-3924	; 0xfffff0ac
     374:	535f4f49 	cmppl	pc, #292	; 0x124
     378:	5f544f4c 	svcpl	0x00544f4c
     37c:	41564e49 	cmpmi	r6, r9, asr #28
     380:	0044494c 	subeq	r4, r4, ip, asr #18
     384:	5f544d57 	svcpl	0x00544d57
     388:	4449504f 	strbmi	r5, [r9], #-79	; 0xffffffb1
     38c:	4745525f 	smlsldmi	r5, r5, pc, r2	; <UNPREDICTABLE>
     390:	0057525f 	subseq	r5, r7, pc, asr r2
     394:	5f544d57 	svcpl	0x00544d57
     398:	4c525443 	cfldrdmi	mvd5, [r2], {67}	; 0x43
     39c:	5f57485f 	svcpl	0x0057485f
     3a0:	5f525750 	svcpl	0x00525750
     3a4:	63004e4f 	movwvs	r4, #3663	; 0xe4f
     3a8:	5f78656f 	svcpl	0x0078656f
     3ac:	5f746d77 	svcpl	0x00746d77
     3b0:	5f746e61 	svcpl	0x00746e61
     3b4:	65646f6d 	strbvs	r6, [r4, #-3949]!	; 0xfffff093
     3b8:	656f6300 	strbvs	r6, [pc, #-768]!	; c0 <.debug_str+0xc0>
     3bc:	78655f78 	stmdavc	r5!, {r3, r4, r5, r6, r8, r9, sl, fp, ip, lr}^
     3c0:	74705f74 	ldrbtvc	r5, [r0], #-3956	; 0xfffff08c
     3c4:	69685f61 	stmdbvs	r8!, {r0, r5, r6, r8, r9, sl, fp, ip, lr}^
     3c8:	5f78745f 	svcpl	0x0078745f
     3cc:	00676174 	rsbeq	r6, r7, r4, ror r1
     3d0:	72573475 	subsvc	r3, r7, #1962934272	; 0x75000000
     3d4:	65747469 	ldrbvs	r7, [r4, #-1129]!	; 0xfffffb97
     3d8:	7a69536e 	bvc	1a55198 <wmt_core_func_ctrl_cmd+0x1a51d78>
     3dc:	56700065 	ldrbtpl	r0, [r0], -r5, rrx
     3e0:	73006c61 	movwvc	r6, #3169	; 0xc61
     3e4:	656e6769 	strbvs	r6, [lr, #-1897]!	; 0xfffff897
     3e8:	68632064 	stmdavs	r3!, {r2, r5, r6, sp}^
     3ec:	69007261 	stmdbvs	r0, {r0, r5, r6, r9, ip, sp, lr}
     3f0:	69705f63 	ldmdbvs	r0!, {r0, r1, r5, r6, r8, r9, sl, fp, ip, lr}^
     3f4:	74635f6e 	strbtvc	r5, [r3], #-3950	; 0xfffff092
     3f8:	77006c72 	smlsdxvc	r0, r2, ip, r6
     3fc:	675f746d 	ldrbvs	r7, [pc, -sp, ror #8]
     400:	6c5f7370 	mrrcvs	3, 7, r7, pc, cr0	; <UNPREDICTABLE>
     404:	655f616e 	ldrbvs	r6, [pc, #-366]	; 29e <.debug_str+0x29e>
     408:	6c62616e 	stfvse	f6, [r2], #-440	; 0xfffffe48
     40c:	5f500065 	svcpl	0x00500065
     410:	4c41534f 	mcrrmi	3, 4, r5, r1, cr15
     414:	5f504f5f 	svcpl	0x00504f5f
     418:	00544144 	subseq	r4, r4, r4, asr #2
     41c:	4e495550 	mcrmi	5, 2, r5, cr9, cr0, {2}
     420:	57003854 	smlsdpl	r0, r4, r8, r3
     424:	435f544d 	cmpmi	pc, #1291845632	; 0x4d000000
     428:	4458454f 	ldrbmi	r4, [r8], #-1359	; 0xfffffab1
     42c:	325f4742 	subscc	r4, pc, #17301504	; 0x1080000
     430:	5456455f 	ldrbpl	r4, [r6], #-1375	; 0xfffffaa1
     434:	72446500 	subvc	r6, r4, #0, 10
     438:	61745376 	cmnvs	r4, r6, ror r3
     43c:	00737574 	rsbseq	r7, r3, r4, ror r5
     440:	4d554e45 	ldclmi	14, cr4, [r5, #-276]	; 0xfffffeec
     444:	5652445f 			; <UNDEFINED> instruction: 0x5652445f
     448:	5354535f 	cmppl	r4, #2080374785	; 0x7c000001
     44c:	646d6300 	strbtvs	r6, [sp], #-768	; 0xfffffd00
     450:	75007a53 	strvc	r7, [r0, #-2643]	; 0xfffff5ad
     454:	6769736e 	strbvs	r7, [r9, -lr, ror #6]!
     458:	2064656e 	rsbcs	r6, r4, lr, ror #10
     45c:	72616863 	rsbvc	r6, r1, #6488064	; 0x630000
     460:	74737400 	ldrbtvc	r7, [r3], #-1024	; 0xfffffc00
     464:	54747645 	ldrbtpl	r7, [r4], #-1605	; 0xfffff9bb
     468:	5f00706d 	svcpl	0x0000706d
     46c:	5f544d57 	svcpl	0x00544d57
     470:	4f5f4349 	svcmi	0x005f4349
     474:	005f5350 	subseq	r5, pc, r0, asr r3	; <UNPREDICTABLE>
     478:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
     47c:	675f636e 	ldrbvs	r6, [pc, -lr, ror #6]
     480:	5f6f6970 	svcpl	0x006f6970
     484:	6c727463 	cfldrdvs	mvd7, [r2], #-396	; 0xfffffe74
     488:	66706f00 	ldrbtvs	r6, [r0], -r0, lsl #30
     48c:	5f636e75 	svcpl	0x00636e75
     490:	725f7768 	subsvc	r7, pc, #104, 14	; 0x1a00000
     494:	69007473 	stmdbvs	r0, {r0, r1, r4, r5, r6, sl, ip, sp, lr}
     498:	5f74696e 	svcpl	0x0074696e
     49c:	69726373 	ldmdbvs	r2!, {r0, r1, r4, r5, r6, r8, r9, sp, lr}^
     4a0:	63007470 	movwvs	r7, #1136	; 0x470
     4a4:	5f78656f 	svcpl	0x0078656f
     4a8:	705f7462 	subsvc	r7, pc, r2, ror #8
     4ac:	6d5f7277 	lfmvs	f7, 2, [pc, #-476]	; 2d8 <.debug_str+0x2d8>
     4b0:	57006469 	strpl	r6, [r0, -r9, ror #8]
     4b4:	535f544d 	cmppl	pc, #1291845632	; 0x4d000000
     4b8:	525f5445 	subspl	r5, pc, #1157627904	; 0x45000000
     4bc:	575f4745 	ldrbpl	r4, [pc, -r5, asr #14]
     4c0:	56455f52 			; <UNDEFINED> instruction: 0x56455f52
     4c4:	5f5f0054 	svcpl	0x005f0054
     4c8:	434e5546 	movtmi	r5, #58694	; 0xe546
     4cc:	4e4f4954 	mcrmi	9, 2, r4, cr15, cr4, {2}
     4d0:	63005f5f 	movwvs	r5, #3935	; 0xf5f
     4d4:	5f78656f 	svcpl	0x0078656f
     4d8:	705f7462 	subsvc	r7, pc, r2, ror #8
     4dc:	6c5f7277 	lfmvs	f7, 2, [pc], {119}	; 0x77
     4e0:	6300776f 	movwvs	r7, #1903	; 0x76f
     4e4:	64497274 	strbvs	r7, [r9], #-628	; 0xfffffd8c
     4e8:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     4ec:	49504f5f 	ldmdbmi	r0, {r0, r1, r2, r3, r4, r6, r8, r9, sl, fp, lr}^
     4f0:	54535f44 	ldrbpl	r5, [r3], #-3908	; 0xfffff0bc
     4f4:	53525f50 	cmppl	r2, #80, 30	; 0x140
     4f8:	455f0054 	ldrbmi	r0, [pc, #-84]	; 4ac <.debug_str+0x4ac>
     4fc:	5f4d554e 	svcpl	0x004d554e
     500:	4f43504f 	svcmi	0x0043504f
     504:	63004544 	movwvs	r4, #1348	; 0x544
     508:	78456766 	stmdavc	r5, {r1, r2, r5, r6, r8, r9, sl, sp, lr}^
     50c:	00747369 	rsbseq	r7, r4, r9, ror #6
     510:	6c727463 	cfldrdvs	mvd7, [r2], #-396	; 0xfffffe74
     514:	00316150 	eorseq	r6, r1, r0, asr r1
     518:	6c727463 	cfldrdvs	mvd7, [r2], #-396	; 0xfffffe74
     51c:	00326150 	eorseq	r6, r2, r0, asr r1
     520:	69726373 	ldmdbvs	r2!, {r0, r1, r4, r5, r6, r8, r9, sp, lr}^
     524:	57007470 	smlsdxpl	r0, r0, r4, r7
     528:	535f544d 	cmppl	pc, #1291845632	; 0x4d000000
     52c:	435f5054 	cmpmi	pc, #84	; 0x54
     530:	5f464e4f 	svcpl	0x00464e4f
     534:	45444f4d 	strbmi	r4, [r4, #-3917]	; 0xfffff0b3
     538:	61686300 	cmnvs	r8, r0, lsl #6
     53c:	67660072 			; <UNDEFINED> instruction: 0x67660072
     540:	6c696146 	stfvse	f6, [r9], #-280	; 0xfffffee8
     544:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     548:	5f565244 	svcpl	0x00565244
     54c:	45505954 	ldrbmi	r5, [r0, #-2388]	; 0xfffff6ac
     550:	4944535f 	stmdbmi	r4, {r0, r1, r2, r3, r4, r6, r8, r9, ip, lr}^
     554:	5700314f 	strpl	r3, [r0, -pc, asr #2]
     558:	5244544d 	subpl	r5, r4, #1291845632	; 0x4d000000
     55c:	59545f56 	ldmdbpl	r4, {r1, r2, r4, r6, r8, r9, sl, fp, ip, lr}^
     560:	535f4550 	cmppl	pc, #80, 10	; 0x14000000
     564:	324f4944 	subcc	r4, pc, #68, 18	; 0x110000
     568:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
     56c:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
     570:	74735f65 	ldrbtvc	r5, [r3], #-3941	; 0xfffff09b
     574:	65645f70 	strbvs	r5, [r4, #-3952]!	; 0xfffff090
     578:	74696e69 	strbtvc	r6, [r9], #-3689	; 0xfffff197
     57c:	544e4900 	strbpl	r4, [lr], #-2304	; 0xfffff700
     580:	57003233 	smladxpl	r0, r3, r2, r3
     584:	455f544d 	ldrbmi	r5, [pc, #-1101]	; 13f <.debug_str+0x13f>
     588:	45535546 	ldrbmi	r5, [r3, #-1350]	; 0xfffffaba
     58c:	444d435f 	strbmi	r4, [sp], #-863	; 0xfffffca1
     590:	72777000 	rsbsvc	r7, r7, #0
     594:	5f6e6f5f 	svcpl	0x006e6f5f
     598:	735f6e6f 	cmpvc	pc, #1776	; 0x6f0
     59c:	00746f6c 	rsbseq	r6, r4, ip, ror #30
     5a0:	5f746d77 	svcpl	0x00746d77
     5a4:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
     5a8:	5f63695f 	svcpl	0x0063695f
     5ac:	5f73706f 	svcpl	0x0073706f
     5b0:	63656863 	cmnvs	r5, #6488064	; 0x630000
     5b4:	5753006b 	ldrbpl	r0, [r3, -fp, rrx]
     5b8:	4945445f 	stmdbmi	r5, {r0, r1, r2, r3, r4, r6, sl, lr}^
     5bc:	0054494e 	subseq	r4, r4, lr, asr #18
     5c0:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
     5c4:	735f636e 	cmpvc	pc, #-1207959551	; 0xb8000001
     5c8:	5f6f6964 	svcpl	0x006f6964
     5cc:	6c727463 	cfldrdvs	mvd7, [r2], #-396	; 0xfffffe74
     5d0:	6f5f7000 	svcvs	0x005f7000
     5d4:	53007370 	movwpl	r7, #880	; 0x370
     5d8:	5045454c 	subpl	r4, r5, ip, asr #10
     5dc:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     5e0:	4b41575f 	blmi	1056364 <wmt_core_func_ctrl_cmd+0x1052f44>
     5e4:	5f505545 	svcpl	0x00505545
     5e8:	00545645 	subseq	r5, r4, r5, asr #12
     5ec:	66756270 			; <UNDEFINED> instruction: 0x66756270
     5f0:	00726566 	rsbseq	r6, r2, r6, ror #10
     5f4:	756f5370 	strbvc	r5, [pc, #-880]!	; 28c <.debug_str+0x28c>
     5f8:	00656372 	rsbeq	r6, r5, r2, ror r3
     5fc:	5f544d57 	svcpl	0x00544d57
     600:	4c525443 	cfldrdmi	mvd5, [r2], {67}	; 0x43
     604:	5350475f 	cmppl	r0, #24903680	; 0x17c0000
     608:	414e4c5f 	cmpmi	lr, pc, asr ip
     60c:	5445535f 	strbpl	r5, [r5], #-863	; 0xfffffca1
     610:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     614:	49504f5f 	ldmdbmi	r0, {r0, r1, r2, r3, r4, r6, r8, r9, sl, fp, lr}^
     618:	49485f44 	stmdbmi	r8, {r2, r6, r8, r9, sl, fp, ip, lr}^
     61c:	4f435f46 	svcmi	0x00435f46
     620:	5700464e 	strpl	r4, [r0, -lr, asr #12]
     624:	4f5f544d 	svcmi	0x005f544d
     628:	5f444950 	svcpl	0x00444950
     62c:	534e5344 	movtpl	r5, #58180	; 0xe344
     630:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     634:	4649485f 			; <UNDEFINED> instruction: 0x4649485f
     638:	4944535f 	stmdbmi	r4, {r0, r1, r2, r3, r4, r6, r8, r9, ip, lr}^
     63c:	6f63004f 	svcvs	0x0063004f
     640:	775f7865 	ldrbvc	r7, [pc, -r5, ror #16]
     644:	5f696669 	svcpl	0x00696669
     648:	5f727770 	svcpl	0x00727770
     64c:	68676968 	stmdavs	r7!, {r3, r5, r6, r8, fp, sp, lr}^
     650:	66706f00 	ldrbtvs	r6, [r0], -r0, lsl #30
     654:	5f636e75 	svcpl	0x00636e75
     658:	5f676572 	svcpl	0x00676572
     65c:	6f007772 	svcvs	0x00007772
     660:	6e756670 	mrcvs	6, 3, r6, cr5, cr0, {3}
     664:	69685f63 	stmdbvs	r8!, {r0, r1, r5, r6, r8, r9, sl, fp, ip, lr}^
     668:	6f635f66 	svcvs	0x00635f66
     66c:	7700666e 	strvc	r6, [r0, -lr, ror #12]
     670:	635f746d 	cmpvs	pc, #1828716544	; 0x6d000000
     674:	5f65726f 	svcpl	0x0065726f
     678:	636e7566 	cmnvs	lr, #427819008	; 0x19800000
     67c:	7274635f 	rsbsvc	r6, r4, #2080374785	; 0x7c000001
     680:	6d635f6c 	stclvs	15, cr5, [r3, #-432]!	; 0xfffffe50
     684:	63690064 	cmnvs	r9, #100	; 0x64
     688:	7265765f 	rsbvc	r7, r5, #99614720	; 0x5f00000
     68c:	6568635f 	strbvs	r6, [r8, #-863]!	; 0xfffffca1
     690:	44006b63 	strmi	r6, [r0], #-2915	; 0xfffff49d
     694:	535f5652 	cmppl	pc, #85983232	; 0x5200000
     698:	4d5f5354 	ldclmi	3, cr5, [pc, #-336]	; 550 <.debug_str+0x550>
     69c:	74005841 	strvc	r5, [r0], #-2113	; 0xfffff7bf
     6a0:	76457473 			; <UNDEFINED> instruction: 0x76457473
     6a4:	49450074 	stmdbmi	r5, {r2, r4, r5, r6}^
     6a8:	57005152 	smlsdpl	r0, r2, r1, r5
     6ac:	495f544d 	ldmdbmi	pc, {r0, r2, r3, r6, sl, ip, lr}^	; <UNPREDICTABLE>
     6b0:	49415f43 	stmdbmi	r1, {r0, r1, r6, r8, r9, sl, fp, ip, lr}^
     6b4:	00305f46 	eorseq	r5, r0, r6, asr #30
     6b8:	5f544d57 	svcpl	0x00544d57
     6bc:	415f4349 	cmpmi	pc, r9, asr #6
     6c0:	315f4649 	cmpcc	pc, r9, asr #12
     6c4:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     6c8:	5f43495f 	svcpl	0x0043495f
     6cc:	5f464941 	svcpl	0x00464941
     6d0:	4d570032 	ldclmi	0, cr0, [r7, #-200]	; 0xffffff38
     6d4:	43495f54 	movtmi	r5, #40788	; 0x9f54
     6d8:	4649415f 			; <UNDEFINED> instruction: 0x4649415f
     6dc:	7500335f 	strvc	r3, [r0, #-863]	; 0xfffffca1
     6e0:	746d5734 	strbtvc	r5, [sp], #-1844	; 0xfffff8cc
     6e4:	50646d43 	rsbpl	r6, r4, r3, asr #26
     6e8:	654c7564 	strbvs	r7, [ip, #-1380]	; 0xfffffa9c
     6ec:	4d57006e 	ldclmi	0, cr0, [r7, #-440]	; 0xfffffe48
     6f0:	54435f54 	strbpl	r5, [r3], #-3924	; 0xfffff0ac
     6f4:	485f4c52 	ldmdami	pc, {r1, r4, r6, sl, fp, lr}^	; <UNPREDICTABLE>
     6f8:	5f54534f 	svcpl	0x0054534f
     6fc:	44554142 	ldrbmi	r4, [r5], #-322	; 0xfffffebe
     700:	45544152 	ldrbmi	r4, [r4, #-338]	; 0xfffffeae
     704:	5445535f 	strbpl	r5, [r5], #-863	; 0xfffffca1
     708:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     70c:	5445535f 	strbpl	r5, [r5], #-863	; 0xfffffca1
     710:	4745525f 	smlsldmi	r5, r5, pc, r2	; <UNPREDICTABLE>
     714:	444d435f 	strbmi	r4, [sp], #-863	; 0xfffffca1
     718:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     71c:	49504f5f 	ldmdbmi	r0, {r0, r1, r2, r3, r4, r6, r8, r9, sl, fp, lr}^
     720:	504c5f44 	subpl	r5, ip, r4, asr #30
     724:	57004b42 	strpl	r4, [r0, -r2, asr #22]
     728:	4f5f544d 	svcmi	0x005f544d
     72c:	5f444950 	svcpl	0x00444950
     730:	52454854 	subpl	r4, r5, #84, 16	; 0x540000
     734:	54435f4d 	strbpl	r5, [r3], #-3917	; 0xfffff0b3
     738:	57004c52 	smlsdpl	r0, r2, ip, r4
     73c:	5244544d 	subpl	r5, r4, #1291845632	; 0x4d000000
     740:	59545f56 	ldmdbpl	r4, {r1, r2, r4, r6, r8, r9, sl, fp, ip, lr}^
     744:	475f4550 			; <UNDEFINED> instruction: 0x475f4550
     748:	57005350 	smlsdpl	r0, r0, r3, r5
     74c:	435f544d 	cmpmi	pc, #1291845632	; 0x4d000000
     750:	4458454f 	ldrbmi	r4, [r8], #-1359	; 0xfffffab1
     754:	315f4742 	cmpcc	pc, r2, asr #14
     758:	5456455f 	ldrbpl	r4, [r6], #-1375	; 0xfffffaa1
     75c:	656f6300 	strbvs	r6, [pc, #-768]!	; 464 <.debug_str+0x464>
     760:	78655f78 	stmdavc	r5!, {r3, r4, r5, r6, r8, r9, sl, fp, ip, lr}^
     764:	74705f74 	ldrbtvc	r5, [r0], #-3956	; 0xfffff08c
     768:	61735f61 	cmnvs	r3, r1, ror #30
     76c:	656c706d 	strbvs	r7, [ip, #-109]!	; 0xffffff93
     770:	0031745f 	eorseq	r7, r1, pc, asr r4
     774:	78656f63 	stmdavc	r5!, {r0, r1, r5, r6, r8, r9, sl, fp, sp, lr}^
     778:	7478655f 	ldrbtvc	r6, [r8], #-1375	; 0xfffffaa1
     77c:	6174705f 	cmnvs	r4, pc, asr r0
     780:	6d61735f 	stclvs	3, cr7, [r1, #-380]!	; 0xfffffe84
     784:	5f656c70 	svcpl	0x00656c70
     788:	4f003274 	svcmi	0x00003274
     78c:	444f4350 	strbmi	r4, [pc], #-848	; 794 <.debug_str+0x794>
     790:	45545f45 	ldrbmi	r5, [r4, #-3909]	; 0xfffff0bb
     794:	4f005453 	svcmi	0x00005453
     798:	444f4350 	strbmi	r4, [pc], #-848	; 7a0 <.debug_str+0x7a0>
     79c:	45525f45 	ldrbmi	r5, [r2, #-3909]	; 0xfffff0bb
     7a0:	00544553 	subseq	r4, r4, r3, asr r5
     7a4:	544e4955 	strbpl	r4, [lr], #-2389	; 0xfffff6ab
     7a8:	65003631 	strvs	r3, [r0, #-1585]	; 0xfffff9cf
     7ac:	654c7476 	strbvs	r7, [ip, #-1142]	; 0xfffffb8a
     7b0:	3475006e 	ldrbtcc	r0, [r5], #-110	; 0xffffff92
     7b4:	7365725f 	cmnvc	r5, #-268435451	; 0xf0000005
     7b8:	00746c75 	rsbseq	r6, r4, r5, ror ip
     7bc:	746d5767 	strbtvc	r5, [sp], #-1895	; 0xfffff899
     7c0:	4c676244 	sfmmi	f6, 2, [r7], #-272	; 0xfffffef0
     7c4:	57006c76 	smlsdxpl	r0, r6, ip, r6
     7c8:	435f544d 	cmpmi	pc, #1291845632	; 0x4d000000
     7cc:	5f4c5254 	svcpl	0x004c5254
     7d0:	5f544547 	svcpl	0x00544547
     7d4:	43544150 	cmpmi	r4, #80, 2
     7d8:	4e495f48 	cdpmi	15, 4, cr5, cr9, cr8, {2}
     7dc:	4d004f46 	stcmi	15, cr4, [r0, #-280]	; 0xfffffee8
     7e0:	575f4b54 			; <UNDEFINED> instruction: 0x575f4b54
     7e4:	425f4e43 	subsmi	r4, pc, #1072	; 0x430
     7e8:	004c4f4f 	subeq	r4, ip, pc, asr #30
     7ec:	5f544d57 	svcpl	0x00544d57
     7f0:	505f4349 	subspl	r4, pc, r9, asr #6
     7f4:	535f4e49 	cmppl	pc, #1168	; 0x490
     7f8:	45544154 	ldrbmi	r4, [r4, #-340]	; 0xfffffeac
     7fc:	58414d5f 	stmdapl	r1, {r0, r1, r2, r3, r4, r6, r8, sl, fp, lr}^
     800:	575f5000 	ldrbpl	r5, [pc, -r0]
     804:	495f544d 	ldmdbmi	pc, {r0, r2, r3, r6, sl, ip, lr}^	; <UNPREDICTABLE>
     808:	504f5f43 	subpl	r5, pc, r3, asr #30
     80c:	4d570053 	ldclmi	0, cr0, [r7, #-332]	; 0xfffffeb4
     810:	45545f54 	ldrbmi	r5, [r4, #-3924]	; 0xfffff0ac
     814:	4c5f5453 	cfldrdmi	mvd5, [pc], {83}	; 0x53
     818:	5f4b4250 	svcpl	0x004b4250
     81c:	00444d43 	subeq	r4, r4, r3, asr #26
     820:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
     824:	745f636e 	ldrbvc	r6, [pc], #-878	; 82c <.debug_str+0x82c>
     828:	6d726568 	cfldr64vs	mvdx6, [r2, #-416]!	; 0xfffffe60
     82c:	7274635f 	rsbsvc	r6, r4, #2080374785	; 0x7c000001
     830:	4d57006c 	ldclmi	0, cr0, [r7, #-432]	; 0xfffffe50
     834:	43495f54 	movtmi	r5, #40788	; 0x9f54
     838:	4e49505f 	mcrmi	0, 2, r5, cr9, cr15, {2}
     83c:	5953475f 	ldmdbpl	r3, {r0, r1, r2, r3, r4, r6, r8, r9, sl, lr}^
     840:	5700434e 	strpl	r4, [r0, -lr, asr #6]
     844:	4f5f544d 	svcmi	0x005f544d
     848:	5f444950 	svcpl	0x00444950
     84c:	44554142 	ldrbmi	r4, [r5], #-322	; 0xfffffebe
     850:	5453525f 	ldrbpl	r5, [r3], #-607	; 0xfffffda1
     854:	6e6f6c00 	cdpvs	12, 6, cr6, cr15, cr0, {0}
     858:	6e752067 	cdpvs	0, 7, cr2, cr5, cr7, {3}
     85c:	6e676973 	mcrvs	9, 3, r6, cr7, cr3, {3}
     860:	69206465 	stmdbvs	r0!, {r0, r2, r5, r6, sl, sp, lr}
     864:	5000746e 	andpl	r7, r0, lr, ror #8
     868:	545f544b 	ldrbpl	r5, [pc], #-1099	; 870 <.debug_str+0x870>
     86c:	5f455059 	svcpl	0x00455059
     870:	41564e49 	cmpmi	r6, r9, asr #28
     874:	0044494c 	subeq	r4, r4, ip, asr #18
     878:	5f544d57 	svcpl	0x00544d57
     87c:	505f4349 	subspl	r4, pc, r9, asr #6
     880:	535f4e49 	cmppl	pc, #1168	; 0x490
     884:	45544154 	ldrbmi	r4, [r4, #-340]	; 0xfffffeac
     888:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
     88c:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
     890:	78725f65 	ldmdavc	r2!, {r0, r2, r5, r6, r8, r9, sl, fp, ip, lr}^
     894:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     898:	49504f5f 	ldmdbmi	r0, {r0, r1, r2, r3, r4, r6, r8, r9, sl, fp, lr}^
     89c:	414d5f44 	cmpmi	sp, r4, asr #30
     8a0:	455f0058 	ldrbmi	r0, [pc, #-88]	; 850 <.debug_str+0x850>
     8a4:	5f4d554e 	svcpl	0x004d554e
     8a8:	5f544d57 	svcpl	0x00544d57
     8ac:	4c525443 	cfldrdmi	mvd5, [r2], {67}	; 0x43
     8b0:	5700545f 	smlsdpl	r0, pc, r4, r5	; <UNPREDICTABLE>
     8b4:	435f544d 	cmpmi	pc, #1291845632	; 0x4d000000
     8b8:	5f4c5254 	svcpl	0x004c5254
     8bc:	525f5748 	subspl	r5, pc, #72, 14	; 0x1200000
     8c0:	6f005453 	svcvs	0x00005453
     8c4:	6e756670 	mrcvs	6, 3, r6, cr5, cr0, {3}
     8c8:	77705f63 	ldrbvc	r5, [r0, -r3, ror #30]!
     8cc:	6e6f5f72 	mcrvs	15, 3, r5, cr15, cr2, {3}
     8d0:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     8d4:	5f565244 	svcpl	0x00565244
     8d8:	45505954 	ldrbmi	r5, [r0, #-2388]	; 0xfffff6ac
     8dc:	42504c5f 	subsmi	r4, r0, #24320	; 0x5f00
     8e0:	7269004b 	rsbvc	r0, r9, #75	; 0x4b
     8e4:	57007465 	strpl	r7, [r0, -r5, ror #8]
     8e8:	485f544d 	ldmdami	pc, {r0, r2, r3, r6, sl, ip, lr}^	; <UNPREDICTABLE>
     8ec:	5f54534f 	svcpl	0x0054534f
     8f0:	4b415741 	blmi	10565fc <wmt_core_func_ctrl_cmd+0x10531dc>
     8f4:	4d435f45 	stclmi	15, cr5, [r3, #-276]	; 0xfffffeec
     8f8:	49550044 	ldmdbmi	r5, {r2, r6}^
     8fc:	3233544e 	eorscc	r5, r3, #1308622848	; 0x4e000000
     900:	74637000 	strbtvc	r7, [r3], #-0
     904:	6d770078 	ldclvs	0, cr0, [r7, #-480]!	; 0xfffffe20
     908:	6f635f74 	svcvs	0x00635f74
     90c:	685f6572 	ldmdavs	pc, {r1, r4, r5, r6, r8, sl, sp, lr}^	; <UNPREDICTABLE>
     910:	68635f77 	stmdavs	r3!, {r0, r1, r2, r4, r5, r6, r8, r9, sl, fp, ip, lr}^
     914:	006b6365 	rsbeq	r6, fp, r5, ror #6
     918:	5f544d57 	svcpl	0x00544d57
     91c:	45435845 	strbmi	r5, [r3, #-2117]	; 0xfffff7bb
     920:	4f495450 	svcmi	0x00495450
     924:	56455f4e 	strbpl	r5, [r5], -lr, asr #30
     928:	4d570054 	ldclmi	0, cr0, [r7, #-336]	; 0xfffffeb0
     92c:	504f5f54 	subpl	r5, pc, r4, asr pc	; <UNPREDICTABLE>
     930:	475f4449 	ldrbmi	r4, [pc, -r9, asr #8]
     934:	5f4f4950 	svcpl	0x004f4950
     938:	4c525443 	cfldrdmi	mvd5, [r2], {67}	; 0x43
     93c:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     940:	454c535f 	strbmi	r5, [ip, #-863]	; 0xfffffca1
     944:	435f5045 	cmpmi	pc, #69	; 0x45
     948:	7700444d 	strvc	r4, [r0, -sp, asr #8]
     94c:	635f746d 	cmpvs	pc, #1828716544	; 0x6d000000
     950:	5f65726f 	svcpl	0x0065726f
     954:	74696e69 	strbtvc	r6, [r9], #-3689	; 0xfffff197
     958:	79546500 	ldmdbvc	r4, {r8, sl, sp, lr}^
     95c:	5f006570 	svcpl	0x00006570
     960:	5f544d57 	svcpl	0x00544d57
     964:	5f544b50 	svcpl	0x00544b50
     968:	48347500 	ldmdami	r4!, {r8, sl, ip, sp, lr}
     96c:	72655677 	rsbvc	r5, r5, #124780544	; 0x7700000
     970:	66706f00 	ldrbtvs	r6, [r0], -r0, lsl #30
     974:	5f636e75 	svcpl	0x00636e75
     978:	736e7364 	cmnvc	lr, #100, 6	; 0x90000001
     97c:	72746300 	rsbsvc	r6, r4, #0, 6
     980:	0064496c 	rsbeq	r4, r4, ip, ror #18
     984:	5f544b50 	svcpl	0x00544b50
     988:	45505954 	ldrbmi	r5, [r0, #-2388]	; 0xfffff6ac
     98c:	58414d5f 	stmdapl	r1, {r0, r1, r2, r3, r4, r6, r8, sl, fp, lr}^
     990:	43504f00 	cmpmi	r0, #0, 30
     994:	5f45444f 	svcpl	0x0045444f
     998:	41564e49 	cmpmi	r6, r9, asr #28
     99c:	0044494c 	subeq	r4, r4, ip, asr #18
     9a0:	76457872 			; <UNDEFINED> instruction: 0x76457872
     9a4:	64644174 	strbtvs	r4, [r4], #-372	; 0xfffffe8c
     9a8:	65720072 	ldrbvs	r0, [r2, #-114]!	; 0xffffff8e
     9ac:	66754273 			; <UNDEFINED> instruction: 0x66754273
     9b0:	6d6f6f52 	stclvs	15, cr6, [pc, #-328]!	; 870 <.debug_str+0x870>
     9b4:	554e4700 	strbpl	r4, [lr, #-1792]	; 0xfffff900
     9b8:	34204320 	strtcc	r4, [r0], #-800	; 0xfffffce0
     9bc:	332e342e 	teqcc	lr, #771751936	; 0x2e000000
     9c0:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
     9c4:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
     9c8:	78745f65 	ldmdavc	r4!, {r0, r2, r5, r6, r8, r9, sl, fp, ip, lr}^
     9cc:	5f434900 	svcpl	0x00434900
     9d0:	5f524556 	svcpl	0x00524556
     9d4:	43454843 	movtmi	r4, #22595	; 0x5843
     9d8:	4d57004b 	ldclmi	0, cr0, [r7, #-300]	; 0xfffffed4
     9dc:	4b505f54 	blmi	1418734 <wmt_core_func_ctrl_cmd+0x1415314>
     9e0:	6d770054 	ldclvs	0, cr0, [r7, #-336]!	; 0xfffffeb0
     9e4:	6f635f74 	svcvs	0x00635f74
     9e8:	725f6572 	subsvc	r6, pc, #478150656	; 0x1c800000
     9ec:	6c665f78 	stclvs	15, cr5, [r6], #-480	; 0xfffffe20
     9f0:	00687375 	rsbeq	r7, r8, r5, ror r3
     9f4:	5f746d77 	svcpl	0x00746d77
     9f8:	6f5f6369 	svcvs	0x005f6369
     9fc:	6d5f7370 	ldclvs	3, cr7, [pc, #-448]	; 844 <.debug_str+0x844>
     a00:	32363674 	eorscc	r3, r6, #116, 12	; 0x7400000
     a04:	4d570030 	ldclmi	0, cr0, [r7, #-192]	; 0xffffff40
     a08:	56524454 			; <UNDEFINED> instruction: 0x56524454
     a0c:	5059545f 	subspl	r5, r9, pc, asr r4
     a10:	4d575f45 	ldclmi	15, cr5, [r7, #-276]	; 0xfffffeec
     a14:	75610054 	strbvc	r0, [r1, #-84]!	; 0xffffffac
     a18:	72745334 	rsbsvc	r5, r4, #52, 6	; 0xd0000000
     a1c:	6f437061 	svcvs	0x00437061
     a20:	5700666e 	strpl	r6, [r0, -lr, ror #12]
     a24:	535f544d 	cmppl	pc, #1291845632	; 0x4d000000
     a28:	5f4f4944 	svcpl	0x004f4944
     a2c:	434e5546 	movtmi	r5, #58694	; 0xe546
     a30:	5054535f 	subspl	r5, r4, pc, asr r3
     a34:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     a38:	4649485f 			; <UNDEFINED> instruction: 0x4649485f
     a3c:	58414d5f 	stmdapl	r1, {r0, r1, r2, r3, r4, r6, r8, sl, fp, lr}^
     a40:	66706f00 	ldrbtvs	r6, [r0], -r0, lsl #30
     a44:	5f636e75 	svcpl	0x00636e75
     a48:	6b62706c 	blvs	189cc00 <wmt_core_func_ctrl_cmd+0x18997e0>
     a4c:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
     a50:	6e75665f 	mrcvs	6, 3, r6, cr5, cr15, {2}
     a54:	69775f63 	ldmdbvs	r7!, {r0, r1, r5, r6, r8, r9, sl, fp, ip, lr}^
     a58:	6f5f6966 	svcvs	0x005f6966
     a5c:	57007370 	smlsdxpl	r0, r0, r3, r7
     a60:	495f544d 	ldmdbmi	pc, {r0, r2, r3, r6, sl, ip, lr}^	; <UNPREDICTABLE>
     a64:	49505f43 	ldmdbmi	r0, {r0, r1, r6, r8, r9, sl, fp, ip, lr}^
     a68:	45455f4e 	strbmi	r5, [r5, #-3918]	; 0xfffff0b2
     a6c:	4f004944 	svcmi	0x00004944
     a70:	444f4350 	strbmi	r4, [pc], #-848	; a78 <.debug_str+0xa78>
     a74:	54535f45 	ldrbpl	r5, [r3], #-3909	; 0xfffff0bb
     a78:	5f504152 	svcpl	0x00504152
     a7c:	464e4f43 	strbmi	r4, [lr], -r3, asr #30
     a80:	4b415700 	blmi	1056688 <wmt_core_func_ctrl_cmd+0x1053268>
     a84:	00505545 	subseq	r5, r0, r5, asr #10
     a88:	5f544d57 	svcpl	0x00544d57
     a8c:	505f4349 	subspl	r4, pc, r9, asr #6
     a90:	455f4e49 	ldrbmi	r4, [pc, #-3657]	; fffffc4f <wmt_core_func_ctrl_cmd+0xffffc82f>
     a94:	004f4445 	subeq	r4, pc, r5, asr #8
     a98:	5f747665 	svcpl	0x00747665
     a9c:	006e656c 	rsbeq	r6, lr, ip, ror #10
     aa0:	5f544d57 	svcpl	0x00544d57
     aa4:	4449504f 	strbmi	r5, [r9], #-79	; 0xffffffb1
     aa8:	444d435f 	strbmi	r4, [sp], #-863	; 0xfffffca1
     aac:	5345545f 	movtpl	r5, #21599	; 0x545f
     ab0:	4d570054 	ldclmi	0, cr0, [r7, #-336]	; 0xfffffeb0
     ab4:	53415f54 	movtpl	r5, #8020	; 0x1f54
     ab8:	54524553 	ldrbpl	r4, [r2], #-1363	; 0xfffffaad
     abc:	5456455f 	ldrbpl	r4, [r6], #-1375	; 0xfffffaa1
     ac0:	73616d00 	cmnvc	r1, #0, 26
     ac4:	4d57006b 	ldclmi	0, cr0, [r7, #-428]	; 0xfffffe54
     ac8:	54435f54 	strbpl	r5, [r3], #-3924	; 0xfffff0ac
     acc:	475f4c52 			; <UNDEFINED> instruction: 0x475f4c52
     ad0:	505f5445 	subspl	r5, pc, r5, asr #8
     ad4:	48435441 	stmdami	r3, {r0, r6, sl, ip, lr}^
     ad8:	4d414e5f 	stclmi	14, cr4, [r1, #-380]	; 0xfffffe84
     adc:	73690045 	cmnvc	r9, #69	; 0x45
     ae0:	74697257 	strbtvc	r7, [r9], #-599	; 0xfffffda9
     ae4:	52700065 	rsbspl	r0, r0, #101	; 0x65
     ae8:	53007365 	movwpl	r7, #869	; 0x365
     aec:	59534255 	ldmdbpl	r3, {r0, r2, r4, r6, r9, lr}^
     af0:	55465f53 	strbpl	r5, [r6, #-3923]	; 0xfffff0ad
     af4:	4f5f434e 	svcmi	0x005f434e
     af8:	706f004e 	rsbvc	r0, pc, lr, asr #32
     afc:	636e7566 	cmnvs	lr, #427819008	; 0x19800000
     b00:	646d635f 	strbtvs	r6, [sp], #-863	; 0xfffffca1
     b04:	7365745f 	cmnvc	r5, #1593835520	; 0x5f000000
     b08:	6f630074 	svcvs	0x00630074
     b0c:	00746e75 	rsbseq	r6, r4, r5, ror lr
     b10:	746d5770 	strbtvc	r5, [sp], #-1904	; 0xfffff890
     b14:	7500704f 	strvc	r7, [r0, #-79]	; 0xffffffb1
     b18:	6769736e 	strbvs	r7, [r9, -lr, ror #6]!
     b1c:	2064656e 	rsbcs	r6, r4, lr, ror #10
     b20:	00746e69 	rsbseq	r6, r4, r9, ror #28
     b24:	5f544d57 	svcpl	0x00544d57
     b28:	4c525443 	cfldrdmi	mvd5, [r2], {67}	; 0x43
     b2c:	5350475f 	cmppl	r0, #24903680	; 0x17c0000
     b30:	4e59535f 	mrcmi	3, 2, r5, cr9, cr15, {2}
     b34:	45535f43 	ldrbmi	r5, [r3, #-3907]	; 0xfffff0bd
     b38:	504f0054 	subpl	r0, pc, r4, asr r0	; <UNPREDICTABLE>
     b3c:	45444f43 	strbmi	r4, [r4, #-3907]	; 0xfffff0bd
     b40:	58414d5f 	stmdapl	r1, {r0, r1, r2, r3, r4, r6, r8, sl, fp, lr}^
     b44:	4e455f00 	cdpmi	15, 4, cr5, cr5, cr0, {0}
     b48:	575f4d55 			; <UNDEFINED> instruction: 0x575f4d55
     b4c:	5244544d 	subpl	r5, r4, #1291845632	; 0x4d000000
     b50:	59545f56 	ldmdbpl	r4, {r1, r2, r4, r6, r8, r9, sl, fp, ip, lr}^
     b54:	545f4550 	ldrbpl	r4, [pc], #-1360	; b5c <.debug_str+0xb5c>
     b58:	57347500 	ldrpl	r7, [r4, -r0, lsl #10]!
     b5c:	7645746d 	strbvc	r7, [r5], -sp, ror #8
     b60:	50746e65 	rsbspl	r6, r4, r5, ror #28
     b64:	654c7564 	strbvs	r7, [ip, #-1380]	; 0xfffffa9c
     b68:	455f006e 	ldrbmi	r0, [pc, #-110]	; b02 <.debug_str+0xb02>
     b6c:	5f4d554e 	svcpl	0x004d554e
     b70:	5f544d57 	svcpl	0x00544d57
     b74:	4449504f 	strbmi	r5, [r9], #-79	; 0xffffffb1
     b78:	5200545f 	andpl	r5, r0, #1593835520	; 0x5f000000
     b7c:	5f4c4c4f 	svcpl	0x004c4c4f
     b80:	4b434142 	blmi	10d1090 <wmt_core_func_ctrl_cmd+0x10cdc70>
     b84:	616c6600 	cmnvs	ip, r0, lsl #12
     b88:	48430067 	stmdami	r3, {r0, r1, r2, r5, r6}^
     b8c:	57005241 	strpl	r5, [r0, -r1, asr #4]
     b90:	435f544d 	cmpmi	pc, #1291845632	; 0x4d000000
     b94:	5f4c5254 	svcpl	0x004c5254
     b98:	5f544547 	svcpl	0x00544547
     b9c:	5f544d57 	svcpl	0x00544d57
     ba0:	464e4f43 	strbmi	r4, [lr], -r3, asr #30
     ba4:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     ba8:	4b41575f 	blmi	105692c <wmt_core_func_ctrl_cmd+0x105350c>
     bac:	5f505545 	svcpl	0x00505545
     bb0:	00444d43 	subeq	r4, r4, r3, asr #26
     bb4:	7366666f 	cmnvc	r6, #116391936	; 0x6f00000
     bb8:	50007465 	andpl	r7, r0, r5, ror #8
     bbc:	544d575f 	strbpl	r5, [sp], #-1887	; 0xfffff8a1
     bc0:	4649485f 			; <UNDEFINED> instruction: 0x4649485f
     bc4:	4e4f435f 	mcrmi	3, 2, r4, cr15, cr15, {2}
     bc8:	77700046 	ldrbvc	r0, [r0, -r6, asr #32]!
     bcc:	6e6f5f72 	mcrvs	15, 3, r5, cr15, cr2, {3}
     bd0:	6374725f 	cmnvs	r4, #-268435451	; 0xf0000005
     bd4:	6f6c735f 	svcvs	0x006c735f
     bd8:	4e450074 	mcrmi	0, 2, r0, cr5, cr4, {3}
     bdc:	575f4d55 			; <UNDEFINED> instruction: 0x575f4d55
     be0:	435f544d 	cmpmi	pc, #1291845632	; 0x4d000000
     be4:	5f4c5254 	svcpl	0x004c5254
     be8:	75660054 	strbvc	r0, [r6, #-84]!	; 0xffffffac
     bec:	6f5f636e 	svcvs	0x005f636e
     bf0:	4d57006e 	ldclmi	0, cr0, [r7, #-440]	; 0xfffffe48
     bf4:	504f5f54 	subpl	r5, pc, r4, asr pc	; <UNPREDICTABLE>
     bf8:	505f4449 	subspl	r4, pc, r9, asr #8
     bfc:	4f5f5257 	svcmi	0x005f5257
     c00:	4d57004e 	ldclmi	0, cr0, [r7, #-312]	; 0xfffffec8
     c04:	49485f54 	stmdbmi	r8, {r2, r4, r6, r8, r9, sl, fp, ip, lr}^
     c08:	4f435f46 	svcmi	0x00435f46
     c0c:	6300464e 	movwvs	r4, #1614	; 0x64e
     c10:	5f78656f 	svcpl	0x0078656f
     c14:	5f746d77 	svcpl	0x00746d77
     c18:	5f747865 	svcpl	0x00747865
     c1c:	5f617470 	svcpl	0x00617470
     c20:	5f766564 	svcpl	0x00766564
     c24:	75006e6f 	strvc	r6, [r0, #-3695]	; 0xfffff191
     c28:	666e4934 			; <UNDEFINED> instruction: 0x666e4934
     c2c:	7469426f 	strbtvc	r4, [r9], #-623	; 0xfffffd91
     c30:	6e656c00 	cdpvs	12, 6, cr6, cr5, cr0, {0}
     c34:	5f6e695f 	svcpl	0x006e695f
     c38:	00646d63 	rsbeq	r6, r4, r3, ror #26
     c3c:	78656f63 	stmdavc	r5!, {r0, r1, r5, r6, r8, r9, sl, fp, sp, lr}^
     c40:	7478655f 	ldrbtvc	r6, [r8], #-1375	; 0xfffffaa1
     c44:	6174705f 	cmnvs	r4, pc, asr r0
     c48:	5f69685f 	svcpl	0x0069685f
     c4c:	745f7872 	ldrbvc	r7, [pc], #-2162	; c54 <.debug_str+0xc54>
     c50:	70006761 	andvc	r6, r0, r1, ror #14
     c54:	635f6d73 	cmpvs	pc, #7360	; 0x1cc0
     c58:	73740062 	cmnvc	r4, #98	; 0x62
     c5c:	646d4374 	strbtvs	r4, [sp], #-884	; 0xfffffc8c
     c60:	69686300 	stmdbvs	r8!, {r8, r9, sp, lr}^
     c64:	00646970 	rsbeq	r6, r4, r0, ror r9
     c68:	657a6973 	ldrbvs	r6, [sl, #-2419]!	; 0xfffff68d
     c6c:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     c70:	5f43495f 	svcpl	0x0043495f
     c74:	0053504f 	subseq	r5, r3, pc, asr #32
     c78:	544d575f 	strbpl	r5, [sp], #-1887	; 0xfffff8a1
     c7c:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
     c80:	41445f4c 	cmpmi	r4, ip, asr #30
     c84:	005f4154 	subseq	r4, pc, r4, asr r1	; <UNPREDICTABLE>
     c88:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
     c8c:	665f636e 	ldrbvs	r6, [pc], -lr, ror #6
     c90:	5f636e75 	svcpl	0x00636e75
     c94:	0066666f 	rsbeq	r6, r6, pc, ror #12
     c98:	5f565244 	svcpl	0x00565244
     c9c:	5f535453 	svcpl	0x00535453
     ca0:	434e5546 	movtmi	r5, #58694	; 0xe546
     ca4:	004e4f5f 	subeq	r4, lr, pc, asr pc
     ca8:	5f544d57 	svcpl	0x00544d57
     cac:	58454f43 	stmdapl	r5, {r0, r1, r6, r8, r9, sl, fp, lr}^
     cb0:	5f474244 	svcpl	0x00474244
     cb4:	00444d43 	subeq	r4, r4, r3, asr #26
     cb8:	43747374 	cmnmi	r4, #116, 6	; 0xd0000001
     cbc:	7a53646d 	bvc	14d9e78 <wmt_core_func_ctrl_cmd+0x14d6a58>
     cc0:	656f6300 	strbvs	r6, [pc, #-768]!	; 9c8 <.debug_str+0x9c8>
     cc4:	78655f78 	stmdavc	r5!, {r3, r4, r5, r6, r8, r9, sl, fp, ip, lr}^
     cc8:	74705f74 	ldrbtvc	r5, [r0], #-3956	; 0xfffff08c
     ccc:	6f6c5f61 	svcvs	0x006c5f61
     cd0:	5f78725f 	svcpl	0x0078725f
     cd4:	00676174 	rsbeq	r6, r7, r4, ror r1
     cd8:	43704f65 	cmnmi	r0, #404	; 0x194
     cdc:	0065646f 	rsbeq	r6, r5, pc, ror #8
     ce0:	78656f63 	stmdavc	r5!, {r0, r1, r5, r6, r8, r9, sl, fp, sp, lr}^
     ce4:	5f74625f 	svcpl	0x0074625f
     ce8:	69737372 	ldmdbvs	r3!, {r1, r4, r5, r6, r8, r9, ip, sp, lr}^
     cec:	776f6c5f 			; <UNDEFINED> instruction: 0x776f6c5f
     cf0:	6c5f7265 	lfmvs	f7, 2, [pc], {101}	; 0x65
     cf4:	74696d69 	strbtvc	r6, [r9], #-3433	; 0xfffff297
     cf8:	656f6300 	strbvs	r6, [pc, #-768]!	; a00 <.debug_str+0xa00>
     cfc:	74625f78 	strbtvc	r5, [r2], #-3960	; 0xfffff088
     d00:	7277705f 	rsbsvc	r7, r7, #95	; 0x5f
     d04:	6769685f 			; <UNDEFINED> instruction: 0x6769685f
     d08:	72640068 	rsbvc	r0, r4, #104	; 0x68
     d0c:	72657669 	rsbvc	r7, r5, #110100480	; 0x6900000
     d10:	746d2f73 	strbtvc	r2, [sp], #-3955	; 0xfffff08d
     d14:	63775f6b 	cmnvs	r7, #428	; 0x1ac
     d18:	6f635f6e 	svcvs	0x00635f6e
     d1c:	2f6f626d 	svccs	0x006f626d
     d20:	6d6d6f63 	stclvs	15, cr6, [sp, #-396]!	; 0xfffffe74
     d24:	632f6e6f 	teqvs	pc, #1776	; 0x6f0
     d28:	2f65726f 	svccs	0x0065726f
     d2c:	5f746d77 	svcpl	0x00746d77
     d30:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
     d34:	5f00632e 	svcpl	0x0000632e
     d38:	5f544d57 	svcpl	0x00544d57
     d3c:	434e5546 	movtmi	r5, #58694	; 0xe546
     d40:	53504f5f 	cmppl	r0, #380	; 0x17c
     d44:	5069005f 	rsbpl	r0, r9, pc, asr r0
     d48:	664f7277 			; <UNDEFINED> instruction: 0x664f7277
     d4c:	74655266 	strbtvc	r5, [r5], #-614	; 0xfffffd9a
     d50:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     d54:	4944535f 	stmdbmi	r4, {r0, r1, r2, r3, r4, r6, r8, r9, ip, lr}^
     d58:	55465f4f 	strbpl	r5, [r6, #-3919]	; 0xfffff0b1
     d5c:	4d5f434e 	ldclmi	3, cr4, [pc, #-312]	; c2c <.debug_str+0xc2c>
     d60:	57005841 	strpl	r5, [r0, -r1, asr #16]
     d64:	4f5f544d 	svcmi	0x005f544d
     d68:	5f444950 	svcpl	0x00444950
     d6c:	54495845 	strbpl	r5, [r9], #-2117	; 0xfffff7bb
     d70:	56524400 	ldrbpl	r4, [r2], -r0, lsl #8
     d74:	5354535f 	cmppl	r4, #2080374785	; 0x7c000001
     d78:	574f505f 	smlsldpl	r5, pc, pc, r0	; <UNPREDICTABLE>
     d7c:	4f5f5245 	svcmi	0x005f5245
     d80:	4d57004e 	ldclmi	0, cr0, [r7, #-312]	; 0xfffffec8
     d84:	45535f54 	ldrbmi	r5, [r3, #-3924]	; 0xfffff0ac
     d88:	45525f54 	ldrbmi	r5, [r2, #-3924]	; 0xfffff0ac
     d8c:	44525f47 	ldrbmi	r5, [r2], #-3911	; 0xfffff0b9
     d90:	5456455f 	ldrbpl	r4, [r6], #-1375	; 0xfffffaa1
     d94:	575f5000 	ldrbpl	r5, [pc, -r0]
     d98:	475f544d 	ldrbmi	r5, [pc, -sp, asr #8]
     d9c:	435f4e45 	cmpmi	pc, #1104	; 0x450
     da0:	00464e4f 	subeq	r4, r6, pc, asr #28
     da4:	53747665 	cmnpl	r4, #105906176	; 0x6500000
     da8:	7566007a 	strbvc	r0, [r6, #-122]!	; 0xffffff86
     dac:	6f5f636e 	svcvs	0x005f636e
     db0:	73006666 	movwvc	r6, #1638	; 0x666
     db4:	65645f77 	strbvs	r5, [r4, #-3959]!	; 0xfffff089
     db8:	74696e69 	strbtvc	r6, [r9], #-3689	; 0xfffff197
     dbc:	4e455f00 	cdpmi	15, 4, cr5, cr5, cr0, {0}
     dc0:	505f4d55 	subspl	r4, pc, r5, asr sp	; <UNPREDICTABLE>
     dc4:	545f544b 	ldrbpl	r5, [pc], #-1099	; dcc <.debug_str+0xdcc>
     dc8:	00455059 	subeq	r5, r5, r9, asr r0
     dcc:	4e646d63 	cdpmi	13, 6, cr6, cr4, cr3, {3}
     dd0:	0061506f 	rsbeq	r5, r1, pc, rrx
     dd4:	42747665 	rsbsmi	r7, r4, #105906176	; 0x6500000
     dd8:	63006675 	movwvs	r6, #1653	; 0x675
     ddc:	5f78656f 	svcpl	0x0078656f
     de0:	6373696d 	cmnvs	r3, #1785856	; 0x1b4000
     de4:	7478655f 	ldrbtvc	r6, [r8], #-1375	; 0xfffffaa1
     de8:	6174705f 	cmnvs	r4, pc, asr r0
     dec:	006e6f5f 	rsbeq	r6, lr, pc, asr pc
     df0:	5f746d77 	svcpl	0x00746d77
     df4:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
     df8:	6765725f 			; <UNDEFINED> instruction: 0x6765725f
     dfc:	5f77725f 	svcpl	0x0077725f
     e00:	00776172 	rsbseq	r6, r7, r2, ror r1
     e04:	7566706f 	strbvc	r7, [r6, #-111]!	; 0xffffff91
     e08:	705f636e 	subsvc	r6, pc, lr, ror #6
     e0c:	735f7277 	cmpvc	pc, #1879048199	; 0x70000007
     e10:	4d570076 	ldclmi	0, cr0, [r7, #-472]	; 0xfffffe28
     e14:	43495f54 	movtmi	r5, #40788	; 0x9f54
     e18:	4e49505f 	mcrmi	0, 2, r5, cr9, cr15, {2}
     e1c:	58414d5f 	stmdapl	r1, {r0, r1, r2, r3, r4, r6, r8, sl, fp, lr}^
     e20:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     e24:	5f565244 	svcpl	0x00565244
     e28:	45505954 	ldrbmi	r5, [r0, #-2388]	; 0xfffff6ac
     e2c:	4649575f 			; <UNDEFINED> instruction: 0x4649575f
     e30:	4d570049 	ldclmi	0, cr0, [r7, #-292]	; 0xfffffedc
     e34:	54435f54 	strbpl	r5, [r3], #-3924	; 0xfffff0ac
     e38:	465f4c52 			; <UNDEFINED> instruction: 0x465f4c52
     e3c:	5f454552 	svcpl	0x00454552
     e40:	43544150 	cmpmi	r4, #80, 2
     e44:	4d570048 	ldclmi	0, cr0, [r7, #-288]	; 0xfffffee0
     e48:	54435f54 	strbpl	r5, [r3], #-3924	; 0xfffff0ac
     e4c:	475f4c52 			; <UNDEFINED> instruction: 0x475f4c52
     e50:	505f5445 	subspl	r5, pc, r5, asr #8
     e54:	48435441 	stmdami	r3, {r0, r6, sl, ip, lr}^
     e58:	656f6300 	strbvs	r6, [pc, #-768]!	; b60 <.debug_str+0xb60>
     e5c:	74625f78 	strbtvc	r5, [r2], #-3960	; 0xfffff088
     e60:	7373725f 	cmnvc	r3, #-268435451	; 0xf0000005
     e64:	70755f69 	rsbsvc	r5, r5, r9, ror #30
     e68:	5f726570 	svcpl	0x00726570
     e6c:	696d696c 	stmdbvs	sp!, {r2, r3, r5, r6, r8, fp, sp, lr}^
     e70:	4d570074 	ldclmi	0, cr0, [r7, #-464]	; 0xfffffe30
     e74:	54435f54 	strbpl	r5, [r3], #-3924	; 0xfffff0ac
     e78:	535f4c52 	cmppl	pc, #20992	; 0x5200
     e7c:	4f5f5054 	svcmi	0x005f5054
     e80:	004e4550 	subeq	r4, lr, r0, asr r5
     e84:	5f544d57 	svcpl	0x00544d57
     e88:	534e5344 	movtpl	r5, #58180	; 0xe344
     e8c:	5456455f 	ldrbpl	r4, [r6], #-1375	; 0xfffffaa1
     e90:	575f5000 	ldrbpl	r5, [pc, -r0]
     e94:	4f5f544d 	svcmi	0x005f544d
     e98:	4d570050 	ldclmi	0, cr0, [r7, #-320]	; 0xfffffec0
     e9c:	504f5f54 	subpl	r5, pc, r4, asr pc	; <UNPREDICTABLE>
     ea0:	465f4449 	ldrbmi	r4, [pc], -r9, asr #8
     ea4:	00434e55 	subeq	r4, r3, r5, asr lr
     ea8:	78656f63 	stmdavc	r5!, {r0, r1, r5, r6, r8, r9, sl, fp, sp, lr}^
     eac:	6669775f 			; <UNDEFINED> instruction: 0x6669775f
     eb0:	77705f69 	ldrbvc	r5, [r0, -r9, ror #30]!
     eb4:	696d5f72 	stmdbvs	sp!, {r1, r4, r5, r6, r8, r9, sl, fp, ip, lr}^
     eb8:	4d570064 	ldclmi	0, cr0, [r7, #-400]	; 0xfffffe70
     ebc:	504f5f54 	subpl	r5, pc, r4, asr pc	; <UNPREDICTABLE>
     ec0:	505f4449 	subspl	r4, pc, r9, asr #8
     ec4:	535f5257 	cmppl	pc, #1879048197	; 0x70000005
     ec8:	6f630056 	svcvs	0x00630056
     ecc:	775f7865 	ldrbvc	r7, [pc, -r5, ror #16]
     ed0:	5f696669 	svcpl	0x00696669
     ed4:	5f727770 	svcpl	0x00727770
     ed8:	00776f6c 	rsbseq	r6, r7, ip, ror #30
     edc:	5f544d57 	svcpl	0x00544d57
     ee0:	45435845 	strbmi	r5, [r3, #-2117]	; 0xfffff7bb
     ee4:	4f495450 	svcmi	0x00495450
     ee8:	4d435f4e 	stclmi	15, cr5, [r3, #-312]	; 0xfffffec8
     eec:	65640044 	strbvs	r0, [r4, #-68]!	; 0xffffffbc
     ef0:	74696e69 	strbtvc	r6, [r9], #-3689	; 0xfffff197
     ef4:	5f63695f 	svcpl	0x0063695f
     ef8:	5f73706f 	svcpl	0x0073706f
     efc:	656e6f64 	strbvs	r6, [lr, #-3940]!	; 0xfffff09c
     f00:	66706f00 	ldrbtvs	r6, [r0], -r0, lsl #30
     f04:	5f636e75 	svcpl	0x00636e75
     f08:	636e7566 	cmnvs	lr, #427819008	; 0x19800000
     f0c:	006e6f5f 	rsbeq	r6, lr, pc, asr pc
     f10:	5f544d57 	svcpl	0x00544d57
     f14:	4c525443 	cfldrdmi	mvd5, [r2], {67}	; 0x43
     f18:	5054535f 	subspl	r5, r4, pc, asr r3
     f1c:	4e4f435f 	mcrmi	3, 2, r4, cr15, cr15, {2}
     f20:	4d570046 	ldclmi	0, cr0, [r7, #-280]	; 0xfffffee8
     f24:	504f5f54 	subpl	r5, pc, r4, asr pc	; <UNPREDICTABLE>
     f28:	465f4449 	ldrbmi	r4, [pc], -r9, asr #8
     f2c:	5f434e55 	svcpl	0x00434e55
     f30:	0046464f 	subeq	r4, r6, pc, asr #12
     f34:	5f746d77 	svcpl	0x00746d77
     f38:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
     f3c:	696e695f 	stmdbvs	lr!, {r0, r1, r2, r3, r4, r6, r8, fp, sp, lr}^
     f40:	63735f74 	cmnvs	r3, #116, 30	; 0x1d0
     f44:	74706972 	ldrbtvc	r6, [r0], #-2418	; 0xfffff68e
     f48:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     f4c:	4548545f 	strbmi	r5, [r8, #-1119]	; 0xfffffba1
     f50:	525f4d52 	subspl	r4, pc, #5248	; 0x1480
     f54:	5f444145 	svcpl	0x00444145
     f58:	00545645 	subseq	r5, r4, r5, asr #12
     f5c:	49746d77 	ldmdbmi	r4!, {r0, r1, r2, r4, r5, r6, r8, sl, fp, sp, lr}^
     f60:	426f666e 	rsbmi	r6, pc, #115343360	; 0x6e00000
     f64:	50007469 	andpl	r7, r0, r9, ror #8
     f68:	545f544b 	ldrbpl	r5, [pc], #-1099	; f70 <.debug_str+0xf70>
     f6c:	5f455059 	svcpl	0x00455059
     f70:	4e455645 	cdpmi	6, 4, cr5, cr5, cr5, {2}
     f74:	4d570054 	ldclmi	0, cr0, [r7, #-336]	; 0xfffffeb0
     f78:	43495f54 	movtmi	r5, #40788	; 0x9f54
     f7c:	4e49505f 	mcrmi	0, 2, r5, cr9, cr15, {2}
     f80:	004e455f 	subeq	r4, lr, pc, asr r5
     f84:	4d575f50 	ldclmi	15, cr5, [r7, #-320]	; 0xfffffec0
     f88:	54435f54 	strbpl	r5, [r3], #-3924	; 0xfffff0ac
     f8c:	49550058 	ldmdbmi	r5, {r3, r4, r6}^
     f90:	0038544e 	eorseq	r5, r8, lr, asr #8
     f94:	64616572 	strbtvs	r6, [r1], #-1394	; 0xfffffa8e
     f98:	657a6953 	ldrbvs	r6, [sl, #-2387]!	; 0xfffff6ad
     f9c:	34756100 	ldrbtcc	r6, [r5], #-256	; 0xffffff00
     fa0:	6144704f 	cmpvs	r4, pc, asr #32
     fa4:	74006174 	strvc	r6, [r0], #-372	; 0xfffffe8c
     fa8:	646d4378 	strbtvs	r4, [sp], #-888	; 0xfffffc88
     fac:	72646441 	rsbvc	r6, r4, #1090519040	; 0x41000000
     fb0:	66706f00 	ldrbtvs	r6, [r0], -r0, lsl #30
     fb4:	5f636e75 	svcpl	0x00636e75
     fb8:	5f727770 	svcpl	0x00727770
     fbc:	0066666f 	rsbeq	r6, r6, pc, ror #12
     fc0:	54767264 	ldrbtpl	r7, [r6], #-612	; 0xfffffd9c
     fc4:	00657079 	rsbeq	r7, r5, r9, ror r0
     fc8:	5f544d57 	svcpl	0x00544d57
     fcc:	4449504f 	strbmi	r5, [r9], #-79	; 0xffffffb1
     fd0:	5f57485f 	svcpl	0x0057485f
     fd4:	00545352 	subseq	r5, r4, r2, asr r3
     fd8:	4f43504f 	svcmi	0x0043504f
     fdc:	505f4544 	subspl	r4, pc, r4, asr #10
     fe0:	48435441 	stmdami	r3, {r0, r6, sl, ip, lr}^
     fe4:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
     fe8:	4944535f 	stmdbmi	r4, {r0, r1, r2, r3, r4, r6, r8, r9, ip, lr}^
     fec:	4c535f4f 	mrrcmi	15, 4, r5, r3, cr15
     ff0:	4d5f544f 	cfldrdmi	mvd5, [pc, #-316]	; ebc <.debug_str+0xebc>
     ff4:	57005841 	strpl	r5, [r0, -r1, asr #16]
     ff8:	545f544d 	ldrbpl	r5, [pc], #-1101	; 1000 <.debug_str+0x1000>
     ffc:	4d524548 	cfldr64mi	mvdx4, [r2, #-288]	; 0xfffffee0
    1000:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
    1004:	56455f4c 	strbpl	r5, [r5], -ip, asr #30
    1008:	504f0054 	subpl	r0, pc, r4, asr r0	; <UNPREDICTABLE>
    100c:	45444f43 	strbmi	r4, [r4, #-3907]	; 0xfffff0bd
    1010:	4649485f 			; <UNDEFINED> instruction: 0x4649485f
    1014:	6f687300 	svcvs	0x00687300
    1018:	69207472 	stmdbvs	r0!, {r1, r4, r5, r6, sl, ip, sp, lr}
    101c:	6700746e 	strvs	r7, [r0, -lr, ror #8]
    1020:	576b744d 	strbpl	r7, [fp, -sp, asr #8]!
    1024:	7443746d 	strbvc	r7, [r3], #-1133	; 0xfffffb93
    1028:	4d570078 	ldclmi	0, cr0, [r7, #-480]	; 0xfffffe20
    102c:	56524454 			; <UNDEFINED> instruction: 0x56524454
    1030:	5059545f 	subspl	r5, r9, pc, asr r4
    1034:	54425f45 	strbpl	r5, [r2], #-3909	; 0xfffff0bb
    1038:	74657200 	strbtvc	r7, [r5], #-512	; 0xfffffe00
    103c:	4f007972 	svcmi	0x00007972
    1040:	444f4350 	strbmi	r4, [pc], #-848	; 1048 <.debug_str+0x1048>
    1044:	41575f45 	cmpmi	r7, r5, asr #30
    1048:	5055454b 	subspl	r4, r5, fp, asr #10
    104c:	66706f00 	ldrbtvs	r6, [r0], -r0, lsl #30
    1050:	5f636e75 	svcpl	0x00636e75
    1054:	74697865 	strbtvc	r7, [r9], #-2149	; 0xfffff79b
    1058:	75427000 	strbvc	r7, [r2, #-0]
    105c:	4c670066 	stclmi	0, cr0, [r7], #-408	; 0xfffffe68
    1060:	426b6270 	rsbmi	r6, fp, #112, 4
    1064:	5f006675 	svcpl	0x00006675
    1068:	4d554e45 	ldclmi	14, cr4, [r5, #-276]	; 0xfffffeec
    106c:	544d575f 	strbpl	r5, [sp], #-1887	; 0xfffff8a1
    1070:	4649485f 			; <UNDEFINED> instruction: 0x4649485f
    1074:	7700545f 	smlsdvc	r0, pc, r4, r5	; <UNPREDICTABLE>
    1078:	665f746d 	ldrbvs	r7, [pc], -sp, ror #8
    107c:	5f636e75 	svcpl	0x00636e75
    1080:	5f737067 	svcpl	0x00737067
    1084:	0073706f 	rsbseq	r7, r3, pc, rrx
    1088:	746d5772 	strbtvc	r5, [sp], #-1906	; 0xfffff88e
    108c:	43746b50 	cmnmi	r4, #80, 22	; 0x14000
    1090:	5700646d 	strpl	r6, [r0, -sp, ror #8]
    1094:	4f5f544d 	svcmi	0x005f544d
    1098:	5f444950 	svcpl	0x00444950
    109c:	4f494453 	svcmi	0x00494453
    10a0:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
    10a4:	6d77004c 	ldclvs	0, cr0, [r7, #-304]!	; 0xfffffed0
    10a8:	6f635f74 	svcvs	0x00635f74
    10ac:	645f6572 	ldrbvs	r6, [pc], #-1394	; 10b4 <.debug_str+0x10b4>
    10b0:	696e6965 	stmdbvs	lr!, {r0, r2, r5, r6, r8, fp, sp, lr}^
    10b4:	55500074 	ldrbpl	r0, [r0, #-116]	; 0xffffff8c
    10b8:	33544e49 	cmpcc	r4, #1168	; 0x490
    10bc:	43490032 	movtmi	r0, #36914	; 0x9032
    10c0:	4e49505f 	mcrmi	0, 2, r5, cr9, cr15, {2}
    10c4:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
    10c8:	4d57004c 	ldclmi	0, cr0, [r7, #-304]	; 0xfffffed0
    10cc:	55465f54 	strbpl	r5, [r6, #-3924]	; 0xfffff0ac
    10d0:	4f5f434e 	svcmi	0x005f434e
    10d4:	61005350 	tstvs	r0, r0, asr r3
    10d8:	61506375 	cmpvs	r0, r5, ror r3
    10dc:	006d6172 	rsbeq	r6, sp, r2, ror r1
    10e0:	746d5772 	strbtvc	r5, [sp], #-1906	; 0xfffff88e
    10e4:	45746b50 	ldrbmi	r6, [r4, #-2896]!	; 0xfffff4b0
    10e8:	746e6576 	strbtvc	r6, [lr], #-1398	; 0xfffffa8a
    10ec:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
    10f0:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
    10f4:	57485f4c 	strbpl	r5, [r8, -ip, asr #30]
    10f8:	5f524556 	svcpl	0x00524556
    10fc:	00544547 	subseq	r4, r4, r7, asr #10
    1100:	544d575f 	strbpl	r5, [sp], #-1887	; 0xfffff8a1
    1104:	5854435f 	ldmdapl	r4, {r0, r1, r2, r3, r4, r6, r8, r9, lr}^
    1108:	7770005f 			; <UNDEFINED> instruction: 0x7770005f
    110c:	6e6f5f72 	mcrvs	15, 3, r5, cr15, cr2, {3}
    1110:	66666f5f 	uqsaxvs	r6, r6, pc	; <UNPREDICTABLE>
    1114:	6f6c735f 	svcvs	0x006c735f
    1118:	67660074 			; <UNDEFINED> instruction: 0x67660074
    111c:	57006e45 	strpl	r6, [r0, -r5, asr #28]
    1120:	535f544d 	cmppl	pc, #1291845632	; 0x4d000000
    1124:	5f4f4944 	svcpl	0x004f4944
    1128:	544f4c53 	strbpl	r4, [pc], #-3155	; 1130 <.debug_str+0x1130>
    112c:	4944535f 	stmdbmi	r4, {r0, r1, r2, r3, r4, r6, r8, r9, ip, lr}^
    1130:	5700314f 	strpl	r3, [r0, -pc, asr #2]
    1134:	535f544d 	cmppl	pc, #1291845632	; 0x4d000000
    1138:	5f4f4944 	svcpl	0x004f4944
    113c:	544f4c53 	strbpl	r4, [pc], #-3155	; 1144 <.debug_str+0x1144>
    1140:	4944535f 	stmdbmi	r4, {r0, r1, r2, r3, r4, r6, r8, r9, ip, lr}^
    1144:	7700324f 	strvc	r3, [r0, -pc, asr #4]
    1148:	635f746d 	cmpvs	pc, #1828716544	; 0x6d000000
    114c:	5f65726f 	svcpl	0x0065726f
    1150:	5f707473 	svcpl	0x00707473
    1154:	74696e69 	strbtvc	r6, [r9], #-3689	; 0xfffff197
    1158:	656f6300 	strbvs	r6, [pc, #-768]!	; e60 <.debug_str+0xe60>
    115c:	696d5f78 	stmdbvs	sp!, {r3, r4, r5, r6, r8, r9, sl, fp, ip, lr}^
    1160:	655f6373 	ldrbvs	r6, [pc, #-883]	; df5 <.debug_str+0xdf5>
    1164:	665f7478 			; <UNDEFINED> instruction: 0x665f7478
    1168:	75746165 	ldrbvc	r6, [r4, #-357]!	; 0xfffffe9b
    116c:	735f6572 	cmpvc	pc, #478150656	; 0x1c800000
    1170:	57007465 	strpl	r7, [r0, -r5, ror #8]
    1174:	4f5f544d 	svcmi	0x005f544d
    1178:	5f444950 	svcpl	0x00444950
    117c:	525f5753 	subspl	r5, pc, #21757952	; 0x14c0000
    1180:	4f005453 	svcmi	0x00005453
    1184:	444f4350 	strbmi	r4, [pc], #-848	; 118c <.debug_str+0x118c>
    1188:	55465f45 	strbpl	r5, [r6, #-3909]	; 0xfffff0bb
    118c:	435f434e 	cmpmi	pc, #939524097	; 0x38000001
    1190:	004c5254 	subeq	r5, ip, r4, asr r2
    1194:	5f544d57 	svcpl	0x00544d57
    1198:	4449504f 	strbmi	r5, [r9], #-79	; 0xffffffb1
    119c:	4e55465f 	mrcmi	6, 2, r4, cr5, cr15, {2}
    11a0:	4e4f5f43 	cdpmi	15, 4, cr5, cr15, cr3, {2}
    11a4:	575f5000 	ldrbpl	r5, [pc, -r0]
    11a8:	465f544d 	ldrbmi	r5, [pc], -sp, asr #8
    11ac:	5f434e55 	svcpl	0x00434e55
    11b0:	0053504f 	subseq	r5, r3, pc, asr #32
    11b4:	5f505453 	svcpl	0x00505453
    11b8:	5f4d5350 	svcpl	0x004d5350
    11bc:	67004243 	strvs	r4, [r0, -r3, asr #4]
    11c0:	746d5770 	strbtvc	r5, [sp], #-1904	; 0xfffff890
    11c4:	636e7546 	cmnvs	lr, #293601280	; 0x11800000
    11c8:	0073704f 	rsbseq	r7, r3, pc, asr #32
    11cc:	63695f70 	cmnvs	r9, #112, 30	; 0x1c0
    11d0:	73706f5f 	cmnvc	r0, #380	; 0x17c
    11d4:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
    11d8:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    11dc:	706f5f65 	rsbvc	r5, pc, r5, ror #30
    11e0:	57006469 	strpl	r6, [r0, -r9, ror #8]
    11e4:	435f544d 	cmpmi	pc, #1291845632	; 0x4d000000
    11e8:	5f4c5254 	svcpl	0x004c5254
    11ec:	505f5748 	subspl	r5, pc, r8, asr #14
    11f0:	4f5f5257 	svcmi	0x005f5257
    11f4:	5f004646 	svcpl	0x00004646
    11f8:	4d554e45 	ldclmi	14, cr4, [r5, #-276]	; 0xfffffeec
    11fc:	5652445f 			; <UNDEFINED> instruction: 0x5652445f
    1200:	5354535f 	cmppl	r4, #2080374785	; 0x7c000001
    1204:	6f63005f 	svcvs	0x0063005f
    1208:	655f7865 	ldrbvs	r7, [pc, #-2149]	; 9ab <.debug_str+0x9ab>
    120c:	705f7478 	subsvc	r7, pc, r8, ror r4	; <UNPREDICTABLE>
    1210:	6c5f6174 	ldfvse	f6, [pc], {116}	; 0x74
    1214:	78745f6f 	ldmdavc	r4!, {r0, r1, r2, r3, r5, r6, r8, r9, sl, fp, ip, lr}^
    1218:	6761745f 			; <UNDEFINED> instruction: 0x6761745f
    121c:	534f5f00 	movtpl	r5, #65280	; 0xff00
    1220:	4f5f4c41 	svcmi	0x005f4c41
    1224:	41445f50 	cmpmi	r4, r0, asr pc
    1228:	4d570054 	ldclmi	0, cr0, [r7, #-336]	; 0xfffffeb0
    122c:	54435f54 	strbpl	r5, [r3], #-3924	; 0xfffff0ac
    1230:	535f4c52 	cmppl	pc, #20992	; 0x5200
    1234:	5f4f4944 	svcpl	0x004f4944
    1238:	50005748 	andpl	r5, r0, r8, asr #14
    123c:	545f544b 	ldrbpl	r5, [pc], #-1099	; 1244 <.debug_str+0x1244>
    1240:	5f455059 	svcpl	0x00455059
    1244:	00444d43 	subeq	r4, r4, r3, asr #26
    1248:	544d575f 	strbpl	r5, [sp], #-1887	; 0xfffff8a1
    124c:	4e45475f 	mcrmi	7, 2, r4, cr5, cr15, {2}
    1250:	4e4f435f 	mcrmi	3, 2, r4, cr15, cr15, {2}
    1254:	4d570046 	ldclmi	0, cr0, [r7, #-280]	; 0xfffffee8
    1258:	43495f54 	movtmi	r5, #40788	; 0x9f54
    125c:	4e49505f 	mcrmi	0, 2, r5, cr9, cr15, {2}
    1260:	0044495f 	subeq	r4, r4, pc, asr r9
    1264:	5f544d57 	svcpl	0x00544d57
    1268:	52454854 	subpl	r4, r5, #84, 16	; 0x540000
    126c:	4d435f4d 	stclmi	15, cr5, [r3, #-308]	; 0xfffffecc
    1270:	682f0044 	stmdavs	pc!, {r2, r6}	; <UNPREDICTABLE>
    1274:	2f656d6f 	svccs	0x00656d6f
    1278:	6f736165 	svcvs	0x00736165
    127c:	72502f6e 	subsvc	r2, r0, #440	; 0x1b8
    1280:	63656a6f 	cmnvs	r5, #454656	; 0x6f000
    1284:	61722f74 	cmnvs	r2, r4, ror pc
    1288:	5f736f6d 	svcpl	0x00736f6d
    128c:	72756f73 	rsbsvc	r6, r5, #460	; 0x1cc
    1290:	6b2f6563 	blvs	bda824 <wmt_core_func_ctrl_cmd+0xbd7404>
    1294:	656e7265 	strbvs	r7, [lr, #-613]!	; 0xfffffd9b
    1298:	3275006c 	rsbscc	r0, r5, #108	; 0x6c
    129c:	4c756453 	cfldrdmi	mvd6, [r5], #-332	; 0xfffffeb4
    12a0:	77006e65 	strvc	r6, [r0, -r5, ror #28]
    12a4:	665f746d 	ldrbvs	r7, [pc], -sp, ror #8
    12a8:	5f636e75 	svcpl	0x00636e75
    12ac:	6f5f6d66 	svcvs	0x005f6d66
    12b0:	57007370 	smlsdxpl	r0, r0, r3, r7
    12b4:	535f544d 	cmppl	pc, #1291845632	; 0x4d000000
    12b8:	435f5054 	cmpmi	pc, #84	; 0x54
    12bc:	5f464e4f 	svcpl	0x00464e4f
    12c0:	0058414d 	subseq	r4, r8, sp, asr #2
    12c4:	65523475 	ldrbvs	r3, [r2, #-1141]	; 0xfffffb8b
    12c8:	69536461 	ldmdbvs	r3, {r0, r5, r6, sl, sp, lr}^
    12cc:	5700657a 	smlsdxpl	r0, sl, r5, r6
    12d0:	5244544d 	subpl	r5, r4, #1291845632	; 0x4d000000
    12d4:	59545f56 	ldmdbpl	r4, {r1, r2, r4, r6, r8, r9, sl, fp, ip, lr}^
    12d8:	535f4550 	cmppl	pc, #80, 10	; 0x14000000
    12dc:	57005054 	smlsdpl	r0, r4, r0, r5
    12e0:	4f5f544d 	svcmi	0x005f544d
    12e4:	5f444950 	svcpl	0x00444950
    12e8:	5f525750 	svcpl	0x00525750
    12ec:	0046464f 	subeq	r4, r6, pc, asr #12
    12f0:	65523475 	ldrbvs	r3, [r2, #-1141]	; 0xfffffb8b
    12f4:	43550073 	cmpmi	r5, #115	; 0x73
    12f8:	00524148 	subseq	r4, r2, r8, asr #2
    12fc:	5f746d77 	svcpl	0x00746d77
    1300:	65726f63 	ldrbvs	r6, [r2, #-3939]!	; 0xfffff09d
    1304:	66706f5f 	uhsaxvs	r6, r0, pc	; <UNPREDICTABLE>
    1308:	00636e75 	rsbeq	r6, r3, r5, ror lr
    130c:	726f6873 	rsbvc	r6, pc, #7536640	; 0x730000
    1310:	6e752074 	mrcvs	0, 3, r2, cr5, cr4, {3}
    1314:	6e676973 	mcrvs	9, 3, r6, cr7, cr3, {3}
    1318:	69206465 	stmdbvs	r0!, {r0, r2, r5, r6, sl, sp, lr}
    131c:	7700746e 	strvc	r7, [r0, -lr, ror #8]
    1320:	635f746d 	cmpvs	pc, #1828716544	; 0x6d000000
    1324:	5f65726f 	svcpl	0x0065726f
    1328:	6c727463 	cfldrdvs	mvd7, [r2], #-396	; 0xfffffe74
    132c:	746d7700 	strbtvc	r7, [sp], #-1792	; 0xfffff900
    1330:	726f635f 	rsbvc	r6, pc, #2080374785	; 0x7c000001
    1334:	75645f65 	strbvc	r5, [r4, #-3941]!	; 0xfffff09b
    1338:	645f706d 	ldrbvs	r7, [pc], #-109	; 1340 <.debug_str+0x1340>
    133c:	00617461 	rsbeq	r7, r1, r1, ror #8
    1340:	74697277 	strbtvc	r7, [r9], #-631	; 0xfffffd89
    1344:	536e6574 	cmnpl	lr, #116, 10	; 0x1d000000
    1348:	00657a69 	rsbeq	r7, r5, r9, ror #20
    134c:	5f544d57 	svcpl	0x00544d57
    1350:	4c525443 	cfldrdmi	mvd5, [r2], {67}	; 0x43
    1354:	58414d5f 	stmdapl	r1, {r0, r1, r2, r3, r4, r6, r8, sl, fp, lr}^
    1358:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
    135c:	5f565244 	svcpl	0x00565244
    1360:	45505954 	ldrbmi	r5, [r0, #-2388]	; 0xfffff6ac
    1364:	004d465f 	subeq	r4, sp, pc, asr r6
    1368:	64496369 	strbvs	r6, [r9], #-873	; 0xfffffc97
    136c:	69547000 	ldmdbvs	r4, {ip, sp, lr}^
    1370:	00656c74 	rsbeq	r6, r5, r4, ror ip
    1374:	5f727770 	svcpl	0x00727770
    1378:	645f7673 	ldrbvs	r7, [pc], #-1651	; 1380 <.debug_str+0x1380>
    137c:	00656e6f 	rsbeq	r6, r5, pc, ror #28
    1380:	77615262 	strbvc	r5, [r1, -r2, ror #4]!
    1384:	67616c46 	strbvs	r6, [r1, -r6, asr #24]!
    1388:	66706f00 	ldrbtvs	r6, [r0], -r0, lsl #30
    138c:	5f636e75 	svcpl	0x00636e75
    1390:	73756665 	cmnvc	r5, #105906176	; 0x6500000
    1394:	77725f65 	ldrbvc	r5, [r2, -r5, ror #30]!
    1398:	34756100 	ldrbtcc	r6, [r5], #-256	; 0xffffff00
    139c:	6c727443 	cfldrdvs	mvd7, [r2], #-268	; 0xfffffef4
    13a0:	61746144 	cmnvs	r4, r4, asr #2
    13a4:	50545300 	subspl	r5, r4, r0, lsl #6
    13a8:	4d53505f 	ldclmi	0, cr5, [r3, #-380]	; 0xfffffe84
    13ac:	58414d5f 	stmdapl	r1, {r0, r1, r2, r3, r4, r6, r8, sl, fp, lr}^
    13b0:	5443415f 	strbpl	r4, [r3], #-351	; 0xfffffea1
    13b4:	004e4f49 	subeq	r4, lr, r9, asr #30
    13b8:	5f544d57 	svcpl	0x00544d57
    13bc:	505f4349 	subspl	r4, pc, r9, asr #6
    13c0:	415f4e49 	cmpmi	pc, r9, asr #28
    13c4:	4f494455 	svcmi	0x00494455
    13c8:	66696800 	strbtvs	r6, [r9], -r0, lsl #16
    13cc:	65707954 	ldrbvs	r7, [r0, #-2388]!	; 0xfffff6ac
    13d0:	61507000 	cmpvs	r0, r0
    13d4:	50700031 	rsbspl	r0, r0, r1, lsr r0
    13d8:	70003261 	andvc	r3, r0, r1, ror #4
    13dc:	6f5f7277 	svcvs	0x005f7277
    13e0:	73725f6e 	cmnvc	r2, #440	; 0x1b8
    13e4:	6c735f74 	ldclvs	15, cr5, [r3], #-464	; 0xfffffe30
    13e8:	7000746f 	andvc	r7, r0, pc, ror #8
    13ec:	61746144 	cmnvs	r4, r4, asr #2
    13f0:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
    13f4:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
    13f8:	58525f4c 	ldmdapl	r2, {r2, r3, r6, r8, r9, sl, fp, ip, lr}^
    13fc:	554c465f 	strbpl	r4, [ip, #-1631]	; 0xfffff9a1
    1400:	6f004853 	svcvs	0x00004853
    1404:	6e756670 	mrcvs	6, 3, r6, cr5, cr0, {3}
    1408:	77735f63 	ldrbvc	r5, [r3, -r3, ror #30]!
    140c:	7473725f 	ldrbtvc	r7, [r3], #-607	; 0xfffffda1
    1410:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
    1414:	5254435f 	subspl	r4, r4, #2080374785	; 0x7c000001
    1418:	58525f4c 	ldmdapl	r2, {r2, r3, r6, r8, r9, sl, fp, ip, lr}^
    141c:	656f6300 	strbvs	r6, [pc, #-768]!	; 1124 <.debug_str+0x1124>
    1420:	69775f78 	ldmdbvs	r7!, {r3, r4, r5, r6, r8, r9, sl, fp, ip, lr}^
    1424:	725f6966 	subsvc	r6, pc, #1671168	; 0x198000
    1428:	5f697373 	svcpl	0x00697373
    142c:	5f64696d 	svcpl	0x0064696d
    1430:	696d696c 	stmdbvs	sp!, {r2, r3, r5, r6, r8, fp, sp, lr}^
    1434:	6d770074 	ldclvs	0, cr0, [r7, #-464]!	; 0xfffffe30
    1438:	66694874 			; <UNDEFINED> instruction: 0x66694874
    143c:	666e6f43 	strbtvs	r6, [lr], -r3, asr #30
    1440:	42555300 	subsmi	r5, r5, #0, 6
    1444:	5f535953 	svcpl	0x00535953
    1448:	434e5546 	movtmi	r5, #58694	; 0xe546
    144c:	46464f5f 			; <UNDEFINED> instruction: 0x46464f5f
    1450:	544d5700 	strbpl	r5, [sp], #-1792	; 0xfffff900
    1454:	5546455f 	strbpl	r4, [r6, #-1375]	; 0xfffffaa1
    1458:	455f4553 	ldrbmi	r4, [pc, #-1363]	; f0d <.debug_str+0xf0d>
    145c:	69005456 	stmdbvs	r0, {r1, r2, r4, r6, sl, ip, lr}
    1460:	00746552 	rsbseq	r6, r4, r2, asr r5

Disassembly of section .comment:

00000000 <.comment>:
   0:	43434700 	movtmi	r4, #14080	; 0x3700
   4:	4728203a 			; <UNDEFINED> instruction: 0x4728203a
   8:	2029554e 	eorcs	r5, r9, lr, asr #10
   c:	2e342e34 	mrccs	14, 1, r2, cr4, cr4, {1}
  10:	Address 0x00000010 is out of bounds.


Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002c41 	andeq	r2, r0, r1, asr #24
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000022 	andeq	r0, r0, r2, lsr #32
  10:	412d3705 	teqmi	sp, r5, lsl #14
  14:	070a0600 	streq	r0, [sl, -r0, lsl #12]
  18:	09010841 	stmdbeq	r1, {r0, r6, fp}
  1c:	14041202 	strne	r1, [r4], #-514	; 0xfffffdfe
  20:	17011501 	strne	r1, [r1, -r1, lsl #10]
  24:	19011803 	stmdbne	r1, {r0, r1, fp, ip}
  28:	1e021a01 	vmlane.f32	s2, s4, s2
  2c:	Address 0x0000002c is out of bounds.

