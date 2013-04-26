	.file	"usbmot.cpp"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__tmp_reg__ = 0
__zero_reg__ = 1
	.global __do_copy_data
	.global __do_clear_bss
	.text
.global	main
	.type	main, @function
main:
/* prologue: frame size=0 */
	ldi r28,lo8(__stack - 0)
	ldi r29,hi8(__stack - 0)
	out __SP_H__,r29
	out __SP_L__,r28
/* prologue end (size=4) */
	sbi 42-0x20,4
	ldi r24,lo8(3)
	out 39-0x20,r24
	ldi r24,lo8(-94)
	sts 128,r24
	ldi r24,lo8(25)
	sts 129,r24
	ldi r24,lo8(4096)
	ldi r25,hi8(4096)
	sts (134)+1,r25
	sts 134,r24
	sts (138)+1,r25
	sts 138,r24
	ldi r24,lo8(2000)
	ldi r25,hi8(2000)
	sts (136)+1,r25
	sts 136,r24
	ldi r24,lo8(63)
	out 36-0x20,r24
	in r24,37-0x20
	andi r24,lo8(-2)
	ori r24,lo8(1)
	out 37-0x20,r24
	in r24,37-0x20
	andi r24,lo8(-17)
	ori r24,lo8(16)
	out 37-0x20,r24
	ldi r18,lo8(2000)
	ldi r19,hi8(2000)
.L2:
	ldi r24,lo8(400)
	ldi r25,hi8(400)
/* #APP */
	1: sbiw r24,1
	brne 1b
/* #NOAPP */
	subi r18,lo8(-(-1))
	sbci r19,hi8(-(-1))
	brne .L2
	cbi 42-0x20,4
	call usbInit
/* #APP */
	sei
/* #NOAPP */
.L4:
	call usbPoll
	ldi r18,lo8(2000)
	ldi r19,hi8(2000)
.L5:
	ldi r24,lo8(400)
	ldi r25,hi8(400)
/* #APP */
	1: sbiw r24,1
	brne 1b
/* #NOAPP */
	subi r18,lo8(-(-1))
	sbci r19,hi8(-(-1))
	brne .L5
	in r24,40-0x20
	ldi r25,lo8(3)
	eor r24,r25
	out 40-0x20,r24
	rjmp .L4
/* epilogue: frame size=0 */
/* epilogue: noreturn */
/* epilogue end (size=0) */
/* function int main() size 77 (73) */
	.size	main, .-main
.global	usbFunctionSetup
	.type	usbFunctionSetup, @function
usbFunctionSetup:
/* prologue: frame size=0 */
/* prologue end (size=0) */
	movw r30,r24
	ldd r20,Z+4
	andi r20,lo8(7)
	ldd r24,Z+1
	cpi r24,lo8(2)
	breq .L16
	cpi r24,lo8(3)
	brlo .L29
	cpi r24,lo8(3)
	brne .+2
	rjmp .L17
	cpi r24,lo8(4)
	brne .L28
	in r18,40-0x20
	clr r21
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	mov r0,r20
	rjmp 2f
1:	lsl r24
	rol r25
2:	dec r0
	brpl 1b
	clr r19
	and r24,r18
	and r25,r19
	rjmp 2f
1:	asr r25
	ror r24
2:	dec r20
	brpl 1b
	sts _ZZ16usbFunctionSetupE8replyBuf,r24
	ldi r24,lo8(_ZZ16usbFunctionSetupE8replyBuf)
	ldi r25,hi8(_ZZ16usbFunctionSetupE8replyBuf)
	sts (usbMsgPtr)+1,r25
	sts usbMsgPtr,r24
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	ret
.L29:
	cpi r24,lo8(1)
	breq .L15
.L28:
	ldi r24,lo8(0)
	ldi r25,hi8(0)
	ret
.L16:
	ldd r24,Z+5
	mov r19,r24
	andi r19,lo8(1)
	clr r25
	andi r24,lo8(2)
	andi r25,hi8(2)
	asr r25
	ror r24
	mov r18,r24
	tst r20
	brne .+2
	rjmp .L22
	cpi r20,lo8(1)
	brne .+2
	rjmp .L30
.L15:
	tst r20
	breq .+2
	rjmp .L31
.L24:
	in r24,37-0x20
	clr r25
	andi r24,lo8(16)
	andi r25,hi8(16)
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	mov r18,r24
	in r24,37-0x20
	clr r25
	andi r24,lo8(32)
	andi r25,hi8(32)
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	mov r19,r24
	lds r24,136
	lds r25,(136)+1
.L26:
	sts _ZZ16usbFunctionSetupE8replyBuf+1,r18
	sts _ZZ16usbFunctionSetupE8replyBuf+2,r19
	sts _ZZ16usbFunctionSetupE8replyBuf+3,r24
	mov r24,r25
	clr r25
	sts _ZZ16usbFunctionSetupE8replyBuf+4,r24
	ldi r24,lo8(4)
	ldi r25,hi8(4)
	ret
.L17:
	in r24,40-0x20
	clr r21
	ldi r18,lo8(1)
	ldi r19,hi8(1)
	mov r0,r20
	rjmp 2f
1:	lsl r18
	rol r19
2:	dec r0
	brpl 1b
	com r18
	and r18,r24
	ldi r19,lo8(0)
	ldd r24,Z+2
	ldd r25,Z+3
	or r24,r25
	brne .L32
.L21:
	mov r24,r19
	clr r25
	rjmp 2f
1:	lsl r24
	rol r25
2:	dec r20
	brpl 1b
	or r18,r24
	out 40-0x20,r18
	ldi r24,lo8(0)
	ldi r25,hi8(0)
	ret
.L31:
	cpi r20,lo8(1)
	brne .L26
.L25:
	in r18,37-0x20
	andi r18,lo8(1)
	in r24,37-0x20
	clr r25
	andi r24,lo8(8)
	andi r25,hi8(8)
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	mov r19,r24
	lds r24,138
	lds r25,(138)+1
	rjmp .L26
.L32:
	ldi r19,lo8(1)
	rjmp .L21
.L22:
	ldd r24,Z+2
	ldd r25,Z+3
	swap r25
	swap r24
	andi r24,0x0f
	eor r24,r25
	andi r25,0x0f
	eor r24,r25
	sts (136)+1,r25
	sts 136,r24
	in r24,37-0x20
	swap r19
	andi r19,0xf0
	andi r24,lo8(-17)
	or r19,r24
	out 37-0x20,r19
	in r24,37-0x20
	swap r18
	lsl r18
	andi r18,0xe0
	andi r24,lo8(-33)
	or r18,r24
	out 37-0x20,r18
	rjmp .L24
.L30:
	ldd r24,Z+2
	ldd r25,Z+3
	swap r25
	swap r24
	andi r24,0x0f
	eor r24,r25
	andi r25,0x0f
	eor r24,r25
	sts (138)+1,r25
	sts 138,r24
	in r24,37-0x20
	andi r24,lo8(-2)
	or r24,r19
	out 37-0x20,r24
	in r24,37-0x20
	lsl r18
	lsl r18
	lsl r18
	andi r24,lo8(-9)
	or r18,r24
	out 37-0x20,r18
	rjmp .L25
/* epilogue: frame size=0 */
/* epilogue: noreturn */
/* epilogue end (size=0) */
/* function unsigned char usbFunctionSetup(unsigned char*) size 213 (213) */
	.size	usbFunctionSetup, .-usbFunctionSetup
	.lcomm _ZZ16usbFunctionSetupE8replyBuf,8
/* File "usbmot.cpp": code  290 = 0x0122 ( 286), prologues   4, epilogues   0 */
