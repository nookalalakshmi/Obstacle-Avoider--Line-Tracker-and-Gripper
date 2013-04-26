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
Bit length 1.8 mSec (0.9+0.9);//1.6mSec
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

Remember TSOC output is inverted ie normally 1
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
{//every 70.721usec here
	c3p5++;
	c131++;
			if(bit_is_clear(PINC,1))
			{
				//sbi(PORTC,1);
			}
			else
			{
				//cbi(PORTC,1);
			}
	
    TCNT2 = TIMER_2_CNT;         	// reset counter to get this interrupt again
	
}
//---------------------------------------------
char GetFrameStart(void)
{
	c3p5=0;
	c131=0;
	char b=0;
	for(;;)
	{
		if(bit_is_clear(PINA,0))
		{
			c3p5=0;
		}
		if(c3p5>49)//3.465mSec
		{
			b=1;
			break;
		}
		if(c131>1852)//131.00mSec
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
		if(bit_is_clear(PINA,0))
		{
			b=0;
			break;
		}
		if(c131>1852)//131.0mSec
		{
			b=2;
			break;
		}
	}
	return b;
}
//---------------------------------------------
/*
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
		char d = c;
		d = d & 1;
		data = data + d; 
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
	if(i==13)
	{
		break;
	}
}
	return data;	
}
*/
//---------------------------------------------
int Test2(void)
{
		int c;
		char d;
		char a;
		char e;
		static int data=0;
		char f;
		
		d=0;
		c=0;
		a=0;
		e=0;
		c3p5=0;
		data=0;
		f=0;
	for(;;)
	{
		if(c!=c3p5)
		{
		d=bit_is_clear(PINA,0);
		c=c3p5;
		}
		
		if(c3p5==15)
		{sbi(PORTC,0);
		}
		if(c3p5>16)
		{
			if(c3p5>49)
			{
			break;                                                                       
			}
			if(a!=d)
			{
			c3p5=0;
			c=0;
			a=d;
			e=d & 0x01;
			data = data + data;
			data = data + e;
			cbi(PORTC,0);
			f++;
			}
		}
		else
		{
			if(a!=d)
			{
			c3p5=0;
			a=d;
			}
		}
		/*
		if(e==0)
			sbi(PORTC,0);
		else
			cbi(PORTC,0);
		*/
	}	
	//PORTC = (char)data;
	//data = f;
	return data;
}
/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
    int data;
	char d2;
	DDRA=0x00;				//set port A as input port all bits.
	DDRC=0xFF;				//Set Port C as output port all bits.
	TCCR2 = TMC8_CK8;               	
    TCNT2  = TIMER_2_CNT;        	// reset TCNT1
     TIMSK  = _BV(TOIE2);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts
	
	for(;;)
	{
		//sbi(PORTC,3);
		char r = GetFrameStart();
		if(r==0)
		{
		//cbi(PORTC,3);
		  data = Test2();
		  d2 = data & 0x3f;
		  //PORTC = _BV(d2);
		  /*
		  switch(data)
		  {
		  case 32:
		    sbi(PORTC,7);
			cbi(PORTC,6);
		   break;
		  case 33:
		    sbi(PORTC,6);
			cbi(PORTC,7);
		   break;
		  case 16:
		    sbi(PORTC,5);
			cbi(PORTC,4);
		   break;
		  case 17:
		    sbi(PORTC,4);
			cbi(PORTC,5);
		   break;
		  }
		  */
		}	
	}
	
return 0;

}
//********************************************
