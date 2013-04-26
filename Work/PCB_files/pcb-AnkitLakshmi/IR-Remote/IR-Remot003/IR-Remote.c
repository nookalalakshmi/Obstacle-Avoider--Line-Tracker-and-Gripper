/*  
IR Remote control on ATMEGA32 cpu in "AVR 40 Pin Robot controller 
using- Programmers Notepad [WinAVR]
20-2-2009
Himanshu Mazumdar

This Experiment reads input from PA0(IR TSOC#3). 
Timer2 interrupt is set 72.463usec (64 count) because 8Mhz is not 
actual 8MHz.

IR Spec-
14 bit bi-phase code
1 = (0,1)
0 = (1,0)
Bit sequence-
1,1,t,s4,s3,s2,s1,s0,c5,c4,c3,c2,c1,c0
t=>toggles every frame
S4-0 => 5 bit type code
C5-0 => 4 bit command code
Bit length 1.8 mSec (0.9+0.9);
frame length =  25.2 mSec
frame repeats every 114 mSec 

Start bit is tested for 131 mSec
data bit is sampled after 1.35 mSec of mid transision

Algorithm-
bool r = GetFrameStart();
1. test 0 for 3.5 mSec
2. wait for 1 for max 131 mSec
3. if 1 then it is first transition of frame else return as no IR pressed
4. Call bool r = GetFrameData(); r=true for success;

Algo for bool r = GetFrameData() :-

1. set cn = 0 
2. wait 1.35 uSec and check data bit
3. shift data reg and save data bit to lsb of reg
4. incriment cn
5. if cn>=14 goto 9.
6. bool r = GetNextTransition();if r=false then goto 8.
7. goto 2.
8. format error, exit
9. good data in reg

*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
/*----------------------------------------------------------------
-----------------GLOBAL VARIABLE----------------------------------
-----------------------------------------------------------------*/

//static volatile uint8_t led; 					// use volatile when variable is accessed from interrupts
//static volatile int oneSec=0;
static volatile int irDt=0;
static volatile int c3p5=0;
static volatile int c131=0;


/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/
//#define TMC8_CK8	(_BV(CS22))	// 8 BIT TIMER2 AT 256 PRESCALAR
#define TMC8_CK8	(_BV(CS21))	// 8 BIT TIMER2 AT 8 PRESCALAR
												// GIVES 8*64 = 512 CYCLES
												// AT 8MHZ FREQUENCY  = 0.125 microSECONDS/cycle
												
#define TIMER_2_CNT     191  // 64 micro sec, use AVRcalc to calculate these values
								// MAX VALUE = 255 and up counting from 191
								// TIMER OVERFLOW ON 255-191 = 64 COUNTS



/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

SIGNAL(SIG_OVERFLOW2)            	// signal handler for tcnt2 overflow interrupt
{//every 72.463usec here
	c3p5++;
	c131++;
	
    TCNT2 = TIMER_2_CNT;         	// reset counter to get this interrupt again
	
}
/*
	count++;
		if(bit_is_clear(PINC,0))
		{
		sbi(PORTC,0);
		}
		else
		{
		cbi(PORTC,0);
		}
	oneSec++;
	if(oneSec>=2000)  //13800: 64uSec x 15625 = 1,000,000 uSec
	{
		oneSec=0;
		if(bit_is_clear(PINC,1))
		{
			sbi(PORTC,1);
		}
		else
		{
			cbi(PORTC,1);
		}

	}
*/

//---------------------------------------------
char GetFrameStart(void)
{
	c3p5=0;
	c131=0;
	char b=0;
	for(;;)
	{
		c131++;
		if(!bit_is_clear(PINA,0))
		{
			c3p5=0;
		}
		c3p5++;
		if(c3p5>48)//3.478mSec
		{
			b=1;
			break;
		}
		if(c131>1808)//131.01mSec
		{
			b=2;
			break;
		}
	}
	if(b==2)
		return b;
	b=0;	
	c131=0;
	for(;;)
	{
		c131++;
		if(!bit_is_clear(PINA,0))
		{
			b=0;
			break;
		}
		if(c131>1808)//131.01mSec
		{
			b=2;
			break;
		}
	}
	return b;
}
//---------------------------------------------
int GetFrameData(void)
{
static int data;
int i =0;
c3p5=0;
c131=0;
char c;
data=0;
for(;;)
{
	for(;;)
	{
		if(c3p5>=18)//was 18 after 1.304 mSec
		{
		c = bit_is_clear(PINA,0);
		data=data << 1;
		char d = !c;
		d = d & 1;
		data = data + c; 
		i++;
		c3p5=0;
		break;
		}
	}
	for(;;)
	{
		if(c!=bit_is_clear(PINA,0))
		{
			break;
			c3p5=0;
		}
		
	}
	if(i==14)
	{
		break;
	}
}
	return data;	
}
/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
    int data;
	DDRA=0x00;				//set port A as input port all bits.
	DDRC=0xFF;				//Set Port C as output port all bits.
	TCCR2 = TMC8_CK8;               	
    TCNT2  = TIMER_2_CNT;        	// reset TCNT1
     TIMSK  = _BV(TOIE2);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts
	
	for(;;)
	{
		char r = GetFrameStart();
		if(r==0)
		{
		 //sbi(PORTC,0);
		 
		 data = GetFrameData();
		 data = data & 0x3f;
		 
			PORTC=(char)data;
		}
		else
		{
			PORTC=0x00;
		 //cbi(PORTC,0);
		}

	}
	
return 0;

}
/*
cbi(PORTC,1);
	count = 0;
	for(;;)
	{
		if(bit_is_clear(PINA,0))
		break;
		int c=b & 0x04000;
		if(c==0)
		{
		cbi(PORTC,1);
		}
		else
		{
		sbi(PORTC,1);
		}	
	}
	for(;;)
	{
	b++;
		if(!bit_is_clear(PINA,0))
		break;
		int c=b & 0x04000;
		if(c==0)
		{
		cbi(PORTC,2);
		}
		else
		{
		sbi(PORTC,2);
		}
	}

	sbi(PORTC,1);	int b = 0;
		if(oneSec == 0)
		{
			if(b == 0)
			{
				if(bit_is_clear(PINC,2))
				{
				sbi(PORTC,2);
				}
				else
				{
				cbi(PORTC,2);
				}
				b = 1;
			}
		}
		else
		{
			b=0;
		}void ir_decode()
{

#asm
L00184:   
PUSH    R16              ;Push register on stack
L00185:   
PUSH    R19              ;Push register on stack
L00186:   
PUSH    R20              ;Push register on stack
L00187:   
PUSH    R21              ;Push register on stack
L00188:   
PUSH    R2               ;Push register on stack
L00189:   
PUSH    R3               ;Push register on stack
L0018A:   
PUSH    R24              ;Push register on stack
L0018B:   
PUSH    R25              ;Push register on stack
L0018C:   
IN      R24,0x3F         ;In from I/O location
L0018D:   
PUSH    R24              ;Push register on stack
L0018E:   
IN      R24,0x25         ;In from I/O location
L0018F:   
PUSH    R24              ;Push register on stack
L00190:   
ORI     R24,0x01         ;No Pre Scalling in TCCR2
L00191:   
OUT     0x25,R24         ;Out to I/O location
L00192:   
IN      R24,0x39         ;In from I/O location
L00193:   
PUSH    R24              ;Push register on stack
L00194:   
ORI     R24,0x40         ;Timer2 OVFL Enable bit High
L00195:   
OUT     0x39,R24         ;Out to I/O location
L00196:   
LDI     R24,0xC1         ;Load immediate
L00197:   
OUT     0x24,R24         ;C! count in TimerCounter2
L00198:   
CLR     R21              ;Clear Register
L00199:   
CLR     R20              ;Clear Register
L0019A:   
CLR     R19              ;Clear Register
L0019B:   
CPI     R20,0x08         ;Compare with immediate
L0019C:   
BRCS    PC+0x02          ;Branch if carry set
L0019D:   
RJMP    PC+0x0048        ;Relative jump

L0019E:   
CPI     R19,0x37         ;Compare with immediate
L0019F:   
BRGE    PC+0x05          ;Branch if greater or equal, signed
L001A0:   
	SBIS    0x19,0           ;Skip if bit in I/O register set
L001A1:   
RJMP    PC-0x0007        ;Relative jump

L001A2:   
RJMP    PC-0x0007        ;Relative jump

L001A3:   
RJMP    PC+0x0042        ;Relative jump

L001A4:   
CPI     R20,0x08         ;Compare with immediate
L001A5:   
BRGE    PC-0x02          ;Branch if greater or equal, signed
L001A6:   
	SBIC    0x19,0           ;Skip if bit in I/O register cleared
L001A7:   
RJMP    PC-0x0003        ;Relative jump

L001A8:   
CLR     R19              ;Clear Register
L001A9:   
CPI     R19,0x22         ;Compare with immediate
L001AA:   
BRGE    PC+0x3B          ;Branch if greater or equal, signed
L001AB:   
	SBIS    0x19,0           ;Skip if bit in I/O register set
L001AC:   
RJMP    PC-0x0003        ;Relative jump

L001AD:   
MOV     R25,R19          ;Copy register
L001AE:   
CLR     R19              ;Clear Register
L001AF:   
CLR     R17              ;Clear Register
L001B0:   
CLR     R18              ;Clear Register
L001B1:   
CPI     R25,0x11         ;Compare with immediate
L001B2:   
BRCS    PC+0x03          ;Branch if carry set
L001B3:   
LSR     R25              ;Logical shift right
L001B4:   
LDI     R17,0x01         ;Load immediate
L001B5:   
MOV     R2,R25           ;Copy register
L001B6:   
LSR     R2               ;Logical shift right
L001B7:   
MOV     R3,R2            ;Copy register
L001B8:   
ADD     R2,R25           ;Add without carry
L001B9:   
LSL     R25              ;Logical Shift Left
L001BA:   
ADD     R3,R25           ;Add without carry
L001BB:   
CPI     R17,0x01         ;Compare with immediate
L001BC:   
BREQ    PC+0x05          ;Branch if equal
L001BD:   
CP      R19,R2           ;Compare
L001BE:   
BRGE    PC+0x27          ;Branch if greater or equal, signed
L001BF:   
	SBIC    0x19,0           ;Skip if bit in I/O register cleared
L001C0:   
RJMP    PC-0x0003        ;Relative jump

L001C1:   
CLR     R19              ;Clear Register
L001C2:   
LDI     R16,0x0C         ;Load immediate
L001C3:   
CP      R19,R2           ;Compare
L001C4:   
BRCS    PC-0x01          ;Branch if carry set
L001C5:   
	SBIC    0x19,0           ;Skip if bit in I/O register cleared
L001C6:   
RJMP    PC+0x000A        ;Relative jump

L001C7:   
CLC                      ;Clear Carry
L001C8:   
ROL     R17              ;Rotate Left Through Carry
L001C9:   
ROL     R18              ;Rotate Left Through Carry
L001CA:   
CP      R19,R3           ;Compare
L001CB:   
BRGE    PC+0x1A          ;Branch if greater or equal, signed
L001CC:   
	SBIS    0x19,0           ;Skip if bit in I/O register set
L001CD:   
RJMP    PC-0x0003        ;Relative jump

L001CE:   
CLR     R19              ;Clear Register
L001CF:   
RJMP    PC+0x0009        ;Relative jump

L001D0:   
SEC                      ;Set Carry
L001D1:   
ROL     R17              ;Rotate Left Through Carry
L001D2:   
ROL     R18              ;Rotate Left Through Carry
L001D3:   
CP      R19,R3           ;Compare
L001D4:   
BRGE    PC+0x11          ;Branch if greater or equal, signed
L001D5:   
	SBIC    0x19,0           ;Skip if bit in I/O register cleared
L001D6:   
RJMP    PC-0x0003        ;Relative jump

L001D7:   
CLR     R19              ;Clear Register
L001D8:   
DEC     R16              ;Decrement
L001D9:   
BRNE    PC-0x16          ;Branch if not equal
L001DA:   
MOV     R25,R17          ;Copy register
L001DB:   
ROL     R25              ;Rotate Left Through Carry
L001DC:   
ROL     R18              ;Rotate Left Through Carry
L001DD:   
ROL     R25              ;Rotate Left Through Carry
L001DE:   
ROL     R18              ;Rotate Left Through Carry
L001DF:   
BST     R18,5            ;Bit store from register to T
L001E0:   
BLD     R17,7            ;Bit load from T to register
L001E1:   
BST     R18,6            ;Bit store from register to T
L001E2:   
BLD     R17,6            ;Bit load from T to register
L001E3:   
ANDI    R18,0x1F         ;Logical AND with immediate
L001E4:   
RJMP    PC+0x0003        ;Relative jump

L001E5:   
SER     R17              ;Set Register
L001E6:   
SER     R18              ;Set Register
L001E7:   
POP     R24              ;Pop register from stack
L001E8:   
OUT     0x39,R24         ;Out to I/O location
L001E9:   
POP     R24              ;Pop register from stack
L001EA:   
OUT     0x25,R24         ;Out to I/O location
L001EB:   
POP     R24              ;Pop register from stack
L001EC:   
OUT     0x3F,R24         ;Out to I/O location
L001ED:   
POP     R25              ;Pop register from stack
L001EE:   
POP     R24              ;Pop register from stack
L001EF:   
POP     R3               ;Pop register from stack
L001F0:   
POP     R2               ;Pop register from stack
L001F1:   
POP     R21              ;Pop register from stack
L001F2:   
POP     R20              ;Pop register from stack
L001F3:   
POP     R19              ;Pop register from stack
L001F4:   
POP     R16              ;Pop register from stack
L001F5:   
RET                      ;Subroutine return
#endasm
}
*/