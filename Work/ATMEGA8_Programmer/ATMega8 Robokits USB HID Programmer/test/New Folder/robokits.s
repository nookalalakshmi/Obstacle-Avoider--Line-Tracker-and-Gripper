	.file	"robokits.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.global __do_copy_data
	.global __do_clear_bss
	.stabs	"robokits.c",100,0,2,.Ltext0
	.text
.Ltext0:
	.stabs	"gcc2_compiled.",60,0,0,0
	.stabs	"int:t(0,1)=r(0,1);-32768;32767;",128,0,0,0
	.stabs	"char:t(0,2)=r(0,2);0;255;",128,0,0,0
	.stabs	"long int:t(0,3)=r(0,3);-2147483648;2147483647;",128,0,0,0
	.stabs	"unsigned int:t(0,4)=r(0,4);0;65535;",128,0,0,0
	.stabs	"long unsigned int:t(0,5)=r(0,5);0;-1;",128,0,0,0
	.stabs	"long long int:t(0,6)=r(0,6);0;-1;",128,0,0,0
	.stabs	"long long unsigned int:t(0,7)=r(0,7);0;-1;",128,0,0,0
	.stabs	"short int:t(0,8)=r(0,8);-32768;32767;",128,0,0,0
	.stabs	"short unsigned int:t(0,9)=r(0,9);0;65535;",128,0,0,0
	.stabs	"signed char:t(0,10)=r(0,10);-128;127;",128,0,0,0
	.stabs	"unsigned char:t(0,11)=r(0,11);0;255;",128,0,0,0
	.stabs	"float:t(0,12)=r(0,1);4;0;",128,0,0,0
	.stabs	"double:t(0,13)=r(0,1);4;0;",128,0,0,0
	.stabs	"long double:t(0,14)=r(0,1);4;0;",128,0,0,0
	.stabs	"void:t(0,15)=(0,15)",128,0,0,0
	.stabs	"c:/winavr-20080610/lib/gcc/../../avr/include/avr/io.h",130,0,0,0
	.stabs	"c:/winavr-20080610/lib/gcc/../../avr/include/avr/sfr_defs.h",130,0,0,0
	.stabs	"c:/winavr-20080610/lib/gcc/../../avr/include/inttypes.h",130,0,0,0
	.stabs	"c:/winavr-20080610/lib/gcc/../../avr/include/stdint.h",130,0,0,0
	.stabs	"int8_t:t(4,1)=(0,10)",128,0,0,0
	.stabs	"uint8_t:t(4,2)=(0,11)",128,0,0,0
	.stabs	"int16_t:t(4,3)=(0,1)",128,0,0,0
	.stabs	"uint16_t:t(4,4)=(0,4)",128,0,0,0
	.stabs	"int32_t:t(4,5)=(0,3)",128,0,0,0
	.stabs	"uint32_t:t(4,6)=(0,5)",128,0,0,0
	.stabs	"int64_t:t(4,7)=(0,6)",128,0,0,0
	.stabs	"uint64_t:t(4,8)=(0,7)",128,0,0,0
	.stabs	"intptr_t:t(4,9)=(4,3)",128,0,0,0
	.stabs	"uintptr_t:t(4,10)=(4,4)",128,0,0,0
	.stabs	"int_least8_t:t(4,11)=(4,1)",128,0,0,0
	.stabs	"uint_least8_t:t(4,12)=(4,2)",128,0,0,0
	.stabs	"int_least16_t:t(4,13)=(4,3)",128,0,0,0
	.stabs	"uint_least16_t:t(4,14)=(4,4)",128,0,0,0
	.stabs	"int_least32_t:t(4,15)=(4,5)",128,0,0,0
	.stabs	"uint_least32_t:t(4,16)=(4,6)",128,0,0,0
	.stabs	"int_least64_t:t(4,17)=(4,7)",128,0,0,0
	.stabs	"uint_least64_t:t(4,18)=(4,8)",128,0,0,0
	.stabs	"int_fast8_t:t(4,19)=(4,1)",128,0,0,0
	.stabs	"uint_fast8_t:t(4,20)=(4,2)",128,0,0,0
	.stabs	"int_fast16_t:t(4,21)=(4,3)",128,0,0,0
	.stabs	"uint_fast16_t:t(4,22)=(4,4)",128,0,0,0
	.stabs	"int_fast32_t:t(4,23)=(4,5)",128,0,0,0
	.stabs	"uint_fast32_t:t(4,24)=(4,6)",128,0,0,0
	.stabs	"int_fast64_t:t(4,25)=(4,7)",128,0,0,0
	.stabs	"uint_fast64_t:t(4,26)=(4,8)",128,0,0,0
	.stabs	"intmax_t:t(4,27)=(4,7)",128,0,0,0
	.stabs	"uintmax_t:t(4,28)=(4,8)",128,0,0,0
	.stabn	162,0,0,0
	.stabs	"int_farptr_t:t(3,1)=(4,5)",128,0,0,0
	.stabs	"uint_farptr_t:t(3,2)=(4,6)",128,0,0,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"c:/winavr-20080610/lib/gcc/../../avr/include/avr/fuse.h",130,0,0,0
	.stabs	"__fuse_t:t(5,1)=(5,2)=s2low:(0,11),0,8;high:(0,11),8,8;;",128,0,0,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"spi_masterinit:F(0,15)",36,0,0,spi_masterinit
.global	spi_masterinit
	.type	spi_masterinit, @function
spi_masterinit:
	.stabn	68,0,18,.LM0-.LFBB1
.LM0:
.LFBB1:
/* prologue: function */
/* frame size = 0 */
	.stabn	68,0,19,.LM1-.LFBB1
.LM1:
	ldi r24,lo8(40)
	out 55-32,r24
	.stabn	68,0,20,.LM2-.LFBB1
.LM2:
	ldi r24,lo8(81)
	out 45-32,r24
/* epilogue start */
	.stabn	68,0,22,.LM3-.LFBB1
.LM3:
	ret
	.size	spi_masterinit, .-spi_masterinit
.Lscope1:
	.stabs	"master_transmit:F(0,15)",36,0,0,master_transmit
	.stabs	"cdata:P(0,2)",64,0,0,24
.global	master_transmit
	.type	master_transmit, @function
master_transmit:
	.stabn	68,0,24,.LM4-.LFBB2
.LM4:
.LFBB2:
/* prologue: function */
/* frame size = 0 */
	.stabn	68,0,25,.LM5-.LFBB2
.LM5:
	out 47-32,r24
.L4:
	.stabn	68,0,26,.LM6-.LFBB2
.LM6:
	in r24,46-32
	tst r24
	breq .L4
/* epilogue start */
	.stabn	68,0,27,.LM7-.LFBB2
.LM7:
	ret
	.size	master_transmit, .-master_transmit
.Lscope2:
	.stabs	"main:F(0,1)",36,0,0,main
.global	main
	.type	main, @function
main:
	.stabn	68,0,35,.LM8-.LFBB3
.LM8:
.LFBB3:
/* prologue: function */
/* frame size = 0 */
	.stabn	68,0,38,.LM9-.LFBB3
.LM9:
	cbi 53-32,6
	.stabn	68,0,40,.LM10-.LFBB3
.LM10:
	cbi 56-32,5
.LBB32:
.LBB33:
.LBB34:
.LBB35:
	.stabs	"c:/winavr-20080610/lib/gcc/../../avr/include/util/delay_basic.h",132,0,0,.Ltext1
.Ltext1:
	.stabn	68,0,105,.LM11-.LFBB3
.LM11:
	ldi r24,lo8(5000)
	ldi r25,hi8(5000)
/* #APP */
 ;  105 "c:/winavr-20080610/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
.LBE35:
.LBE34:
.LBE33:
.LBE32:
.LBB36:
.LBB37:
	.stabs	"robokits.c",132,0,0,.Ltext2
.Ltext2:
	.stabn	68,0,19,.LM12-.LFBB3
.LM12:
	ldi r24,lo8(40)
	out 55-32,r24
	.stabn	68,0,20,.LM13-.LFBB3
.LM13:
	ldi r24,lo8(81)
	out 45-32,r24
.LBE37:
.LBE36:
.LBB38:
.LBB39:
	.stabn	68,0,25,.LM14-.LFBB3
.LM14:
	ldi r20,lo8(-84)
.LBE39:
.LBE38:
.LBB41:
.LBB42:
	ldi r19,lo8(83)
.LBE42:
.LBE41:
.LBB44:
.LBB45:
	ldi r18,lo8(17)
.LBE45:
.LBE44:
.LBB47:
.LBB48:
	ldi r25,lo8(50)
.L17:
.LBE48:
.LBE47:
.LBB50:
.LBB40:
	out 47-32,r20
.L8:
	.stabn	68,0,26,.LM15-.LFBB3
.LM15:
	in r24,46-32
	tst r24
	breq .L8
.LBE40:
.LBE50:
.LBB51:
.LBB43:
	.stabn	68,0,25,.LM16-.LFBB3
.LM16:
	out 47-32,r19
.L9:
	.stabn	68,0,26,.LM17-.LFBB3
.LM17:
	in r24,46-32
	tst r24
	breq .L9
.LBE43:
.LBE51:
.LBB52:
.LBB53:
	.stabn	68,0,25,.LM18-.LFBB3
.LM18:
	out 47-32,__zero_reg__
.L10:
	.stabn	68,0,26,.LM19-.LFBB3
.LM19:
	in r24,46-32
	tst r24
	breq .L10
.LBE53:
.LBE52:
.LBB54:
.LBB46:
	.stabn	68,0,25,.LM20-.LFBB3
.LM20:
	out 47-32,r18
.L11:
	.stabn	68,0,26,.LM21-.LFBB3
.LM21:
	in r24,46-32
	tst r24
	breq .L11
.LBE46:
.LBE54:
.LBB55:
.LBB49:
	.stabn	68,0,25,.LM22-.LFBB3
.LM22:
	out 47-32,r25
.L12:
	.stabn	68,0,26,.LM23-.LFBB3
.LM23:
	in r24,46-32
	tst r24
	breq .L12
.LBE49:
.LBE55:
.LBB56:
.LBB57:
	.stabn	68,0,25,.LM24-.LFBB3
.LM24:
	out 47-32,r25
.L13:
	.stabn	68,0,26,.LM25-.LFBB3
.LM25:
	in r24,46-32
	tst r24
	breq .L13
.LBE57:
.LBE56:
.LBB58:
.LBB59:
	.stabn	68,0,25,.LM26-.LFBB3
.LM26:
	out 47-32,r25
.L14:
	.stabn	68,0,26,.LM27-.LFBB3
.LM27:
	in r24,46-32
	tst r24
	breq .L14
.LBE59:
.LBE58:
.LBB60:
.LBB61:
	.stabn	68,0,25,.LM28-.LFBB3
.LM28:
	out 47-32,r25
.L15:
	.stabn	68,0,26,.LM29-.LFBB3
.LM29:
	in r24,46-32
	tst r24
	breq .L15
.LBE61:
.LBE60:
.LBB62:
.LBB63:
	.stabn	68,0,25,.LM30-.LFBB3
.LM30:
	out 47-32,r25
.L16:
	.stabn	68,0,26,.LM31-.LFBB3
.LM31:
	in r24,46-32
	tst r24
	breq .L16
	rjmp .L17
.LBE63:
.LBE62:
	.size	main, .-main
.Lscope3:
.global	pw
	.data
	.type	pw, @object
	.size	pw, 2
pw:
	.word	100
.global	count
.global	count
	.section .bss
	.type	count, @object
	.size	count, 2
count:
	.skip 2,0
	.stabs	"pw:G(0,1)",32,0,0,0
	.stabs	"count:G(0,1)",32,0,0,0
	.text
	.stabs	"",100,0,0,.Letext0
.Letext0:
