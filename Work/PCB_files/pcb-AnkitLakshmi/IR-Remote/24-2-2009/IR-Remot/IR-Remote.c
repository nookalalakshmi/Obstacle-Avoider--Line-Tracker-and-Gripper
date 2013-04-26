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
static volatile int c3p5=0;
static volatile int	dt;	 
static volatile char pwmc=0;
static volatile char mode=0; 
static volatile char state=0;
static volatile char d_old;
static volatile char cmd;	 
static volatile char m1=0;
static volatile char m2=0;
static volatile char s11=0;
static volatile char s12=0;
static volatile char s21=0;
static volatile char s22=0;
/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/
//#define TMC8_CK8	(_BV(CS22))	// 8 BIT TIMER2 AT 256 PRESCALAR
#define TMC8_CK8	(_BV(CS21))	// 8 BIT TIMER2 AT 8 PRESCALAR
												// GIVES 8*64 = 512 CYCLES
												// AT 8MHZ FREQUENCY  = 0.125 microSECONDS/cycle
												
#define TIMER_2_CNT     191  // 64 micro sec, use AVRcalc to calculate these values
								// MAX VALUE = 255 and up counting from 191
								// TIMER OVERFLOW ON 255-191 = 64 COUNTSd
/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
SIGNAL(SIG_OVERFLOW2)     // signal handler for tcnt2 overflow interrupt
{//every 70.721usec here
	char d;
	c3p5++;
	pwmc++;
    TCNT2 = TIMER_2_CNT; // reset counter to get this interrupt again
	//---------------------------------------------
	if(pwmc==0)
	{
		sbi(PORTC,7);
		sbi(PORTC,6);
		sbi(PORTC,5);
		sbi(PORTC,4);
	}
	if(pwmc==m1)
	{
	 if(s11==1) cbi(PORTC,7);
	 if(s12==1) cbi(PORTC,6);
	}
	if(pwmc==m2)
	{
	 if(s21==1) cbi(PORTC,5);
	 if(s22==1) cbi(PORTC,4);
	}
	if(mode==0)//Idle
	{
		return;
	}
	
	if(mode==1)//Get start frame first mid-bit
	{
		if(state==0)//detect sylence for 3.5mSec
		{//
			c3p5=0;
			state=1;
			d_old=bit_is_clear(PINA,0);
			return;
		}
		if(state==1)
		{
			d=bit_is_clear(PINA,0);
			if(d_old==d)
			{
				if(c3p5>49)
				{//sylence for 3.5 mSec
					state=2;//now detect first transition
				}
			}
			else
			{
				state=0;
			}
			
			return;
		}
		if(state==2)
		{
			d=bit_is_clear(PINA,0);
			if(d_old!=d)
			{//first transition detected
				state=1;
				c3p5=0;
				dt=0;//reset frame data
				mode=2;//go to frame read
				//PORTC = 0x01;
			}
			return;
		}
	}
	//---------------------------------------------
	if(mode==2)
	{
		if(state==0)
		{//detect mid-bit transition
			d=bit_is_clear(PINA,0);
			if(d_old!=d)
			{//data changed
				d_old=d;
				state=1; 
				c3p5=0;
				return;
			}
			if(c3p5>49)//3.5mSec
			{//no data in 2 bit period; end of frame
			 state=1;
			 mode=0;
			 cmd = dt>>1;
			 cmd=255-cmd;
			 cmd=cmd & 0x3f;
			 
				//PORTC = 0x02;
			}
			return;
		}		
		if(state==1)
		{
			if(c3p5>16)
			{//skip bit boundary
				state=0;
				d=bit_is_clear(PINA,0);
				d_old=d;
				dt=dt<<1;
				dt=dt+d;
				//PORTC = dt;
				return;
			}
		}
		return;
	}
	//---------------------------------------------
}
//---------------------------------------------

/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
	DDRA=0x00;				//set port A as input port all bits.
	DDRC=0xFF;				//Set Port C as output port all bits.
	TCCR2 = TMC8_CK8;               	
    TCNT2  = TIMER_2_CNT;        	// reset TCNT1
     TIMSK  = _BV(TOIE2);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts
	state=0;
	mode=1;
	PORTC = 0xff;
	for(;;)
	{
		if(mode==0)
		{
			if(state==1)
			{
				//PORTC = cmd;
				mode=1;
				state=0;
			}
			else
			{
				if(c3p5>5000)
				{
					//PORTC = 0x55;
					c3p5=0;
					mode=1;
					state=0;
				}
			}
		}
		switch(cmd)
		{
		case 17://Left
			//sbi(PORTC,7);
			//cbi(PORTC,6);
			//cbi(PORTC,5);
			//sbi(PORTC,4);
			s11=1;
			s12=0;
			s21=0;
			s22=1;
		break;
		
		case 16://Right
			//cbi(PORTC,7);
			//sbi(PORTC,6);
			//sbi(PORTC,5);
			//cbi(PORTC,4);
			s11=0;
			s12=1;
			s21=1;
			s22=0;
		break;
		
		case 32://Front
			//sbi(PORTC,7);
			//cbi(PORTC,6);
			//sbi(PORTC,5);
			//cbi(PORTC,4);
			s11=1;
			s12=0;
			s21=1;
			s22=0;
		break;
		
		case 33://Back
			//cbi(PORTC,7);
			//sbi(PORTC,6);
			//cbi(PORTC,5);
			//sbi(PORTC,4);
			s11=0;
			s12=1;
			s21=0;
			s22=1;
		break;
		
		case 59://stop
			//cbi(PORTC,7);
			//cbi(PORTC,6);
			//cbi(PORTC,5);
			//cbi(PORTC,4);
			s11=0;
			s12=0;
			s21=0;
			s22=0;
		break;
		
		case 0://Lowest Speed
		break;
		
		case 1://Low Speed
		 m1=5;
		 m2=5;
		break;
		
		case 2://Normal Speed
		 m1=90;
		 m2=90;
		break;
		
		case 3://High Speed
		 m1=180;
		 m2=180;
		break;
		
		case 4://Highest Speed
		 m1=250;
		 m2=250;
		break;
		}
		cmd = 255;
	}
	
return 0;

}
//********************************************
