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

Grabber:
Motor PORTC2 and PORTC3;0-0 stop;1-0 Forward; 0-1 Reverse
Limit Switch PORTA2; 0 at limit

Wheel Speed:
LEDs(both LEDs are in serise) PB7 0  for LED on
Sensor1 PB6
Sensor2 PB5

Indicator LED:
Green LED at PORTD-6

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
static volatile int c131=0;
static volatile int	irDt;	 
static volatile char irMode=0; 
static volatile char irState=0;
static volatile char d_old;

static volatile char cmd;	 
static volatile char cmd_old;	 
static volatile char pwmc=0;
static volatile char count=0;
/
static volatile char m1=0;
static volatile char m2=0;
static volatile char m3=0;
static volatile char s11=0;
static volatile char s12=0;
static volatile char s21=0;
static volatile char s22=0;
static volatile char s31=0;
static volatile char s32=0;

static volatile char lrwo;
static volatile char lrwc;

static volatile char lwo;
static volatile char lwc;
static volatile char rwo;
static volatile char rwc;


/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/
//#define TMC8_CK8	(_BV(CS22))	// 8 BIT TIMER2 AT 256 PRESCALAR
#define TMC8_CK8	(_BV(CS21))	// 8 BIT TIMER2 AT 8 PRESCALAR
												// GIVES 8*64 = 512 CYCLES
												// AT 8MHZ FREQUENCY  = 0.125 microSECONDS/cycle
												
#define TIMER_2_CNT     191  //191; 64 micro sec, use AVRcalc to calculate these values
								// MAX VALUE = 255 and up counting from 191
								// TIMER OVERFLOW ON 255-191 = 64 COUNTSd
/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
void MotorControlUpdate(void);
void MotorMOve(char lc, char rc);
//Timer2 OVERFLOW Interupt----------------------
SIGNAL(SIG_OVERFLOW2)     // signal handler for tcnt2 overflow interrupt
{//every 70.721usec here
	char d;
	char lw;
	char rw;
	char lrw;
	c3p5++;
	pwmc++;
    TCNT2 = TIMER_2_CNT; // reset counter to get this interrupt again
	//Motor PWM Output------------------------------
	if(pwmc==0)
	{//every 18.1 mSec
		c131++;
		count++;
		sbi(PORTC,7);
		sbi(PORTC,6);
		sbi(PORTC,5);
		sbi(PORTC,4);
		sbi(PORTC,3);
		sbi(PORTC,2);
		cbi(PORTB,7); //IR LED ON
		//max wheel RPM is 100 ie 600mSec/revolution or 150mSec/segment
	}
	//Motor Wheel Reader----------------------------
	if(pwmc==3)
	{//every 18.1 mSec
	lw = bit_is_clear(PINB, 5);//Lssx 	xxxx
	rw = bit_is_clear(PINB, 6);
	lrw = lw;
    lrw = lrw << 1;
    lrw = lrw + rw;
	
	sbi(PORTB, 7); //IR LED OFF
		if(lw!=lwo)
		{
			lwc++;
			lwo=lw;
		}
		if(rw!=rwo)
		{
		  rwc++;
			rwo=rw;
		}
		
		if(lrw==lrwo)
		{
		  lrwc++;
			if(lrwc>200) //No rotation > 3.62 Sec
			{
				lrwc=200;
			}
		}
		else
		{//Yes Wheel rotating
			lrwc=0;
			lrwo=lrw;
		}
	}
	//Motor Motion Control-1--------------------------
	if(pwmc==4)
	{//every 18.1 mSec
	}
	//Motor Motion Control-2--------------------------
	if(pwmc==5)
	{//every 18.1 mSec
	  MotorControlUpdate();
	}
	//Motor PWM Output------------------------------
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
	if(pwmc==m3)
	{
	 if(s31==1) cbi(PORTC,3);
	 if(s32==1) cbi(PORTC,2);
		if(bit_is_clear(PINA,2))
		{
		count++;
		if(count<10)
			{
			m3=255;
			s31=0;
			s32=0;
			}
			else
			{
			count=10;
			}
		}
		else
		{
		count=0;
		}
	}
	//IR-Remote Decoder ----------------------------
	if(irMode==0)//Idle
	{
		return;
	}
	//IR-Remote Decoder ----------------------------
	if(irMode==1)//Get start frame first mid-bit
	{
		if(irState==0)//detect sylence for 3.5mSec
		{//
			c3p5=0;
			irState=1;
			d_old=bit_is_clear(PINA,0);
			return;
		}
		if(irState==1)
		{
			d=bit_is_clear(PINA,0);
			if(d_old==d)
			{
				if(c3p5>49)
				{//sylence for 3.5 mSec
					irState=2;//now detect first transition
					c131=0;
				}
			}
			else
			{
				irState=0;
			}
			return;
		}
		if(irState==2)
		{
			d=bit_is_clear(PINA,0);
			if(d_old!=d)
			{//first transition detected
				irState=1;
				c3p5=0;
				irDt=0;//reset frame data
				irMode=2;//go to frame read
			}
			else
			{
				if(c131>8)//144 mSec
				{//70.721*256*8=144
					cmd=64;
				}
			}
			return;
		}
	}
	//IR-Remote Decoder ----------------------------
	if(irMode==2)
	{
		if(irState==0)
		{//detect mid-bit transition
			d=bit_is_clear(PINA,0);
			if(d_old!=d)
			{//data changed
				d_old=d;
				irState=1; 
				c3p5=0;
				return;
			}
			if(c3p5>49)//3.5mSec
			{//no data in 2 bit period; end of frame
			 irState=1;
			 irMode=0;
			 irDt = irDt>>1;
			 irDt=255-irDt;
			 cmd=irDt & 0x3f;
			 		//sbi(PORTD, 6);
			}
			return;
		}		
		if(irState==1)
		{
			if(c3p5>16)
			{//skip bit boundary
				irState=0;
				d=bit_is_clear(PINA,0);
				d_old=d;
				irDt=irDt<<1;
				irDt=irDt+d;
				return;
			}
		}
		return;
	}
	//---------------------------------------------
}
//Motor Direction & Speed Set----------------------
void MotorControlUpdate(void)     // 
{
		switch(cmd)
		{
		case 16://Left
			s11=1;
			s12=0;
			s21=0;
			s22=1;
			count=0;
		break;
		
		case 17://Right
			s11=0;
			s12=1;
			s21=1;
			s22=0;
			count=0;
			
		break;
		
		case 32://Front
			s11=1;
			s12=0;
			s21=1;
			s22=0;
			s31=1;
			s32=0;
			cmd_old=cmd;
		break;
		
		case 33://Back
			s11=0;
			s12=1;
			s21=0;
			s22=1;
			s31=0;
			s32=1;
			cmd_old=cmd;
		break;
		
		case 41://stop home remot
		case 59://stop robokit remot
			s11=0;
			s12=0;
			s21=0;
			s22=0;
			s31=0;
			s32=0;
			cmd_old=cmd;
		break;
		
		case 0://Stop walking motors
			s11=0;
			s12=0;
			s21=0;
			s22=0;
			s31=0;
			s32=0;
		 m1=255;
		 m2=255;
		 m3=180;
		 lrwc=0;
		cmd_old=cmd;
		break;
		
		case 1://Highest Speed
		 m1=45;
		 m2=45;
		 m3=255;
		break;
		
		case 2://High Speed
		 m1=120;
		 m2=120;
		 m3=255;
		break;
		
		case 3://Normal Speed
		 m1=180;
		 m2=180;
		 m3=255;
		break;
		
		case 4://Low Speed
		 m1=210;
		 m2=210;
		 m3=255;
		break;
		
		case 5://
		sbi(PORTD, 6);
		cmd=64;
		break;
		
		case 6://
		cbi(PORTD, 6);
		break;
		
		case 64://no command
		//cbi(PORTD, 6);
			s11=0;
			s12=0;
			s21=0;
			s22=0;
			s31=0;
			s32=0;
			cmd=cmd_old;
		MotorControlUpdate();
	
			
		break;
		}
}
//Move Robot-----------------------------------
void MotorMOve(char lc, char rc)
{

}
//-----------------MAIN-------------------------------------
int main(void)
{
	DDRA=0x00;				//set port A as input port all bits.
	DDRB=0x80;				//set port B as input 0-6 output 7.
	DDRC=0xFF;				//Set Port C as output port all bits.
	DDRD=0xF0;				//(Not Used) Set Port D as PD7-4 as output bits.
	
	TCCR2 = TMC8_CK8;               	
    TCNT2  = TIMER_2_CNT;        	// reset TCNT1
     TIMSK  = _BV(TOIE2);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts
	irState=0;
	irMode=1;
	PORTC = 0xff;
//==================================	
	for(;;)
	{
	//Robot Wheels Not Moving-----------------------
		if(lrwc==200)
		{//Robot stuck for 3.62 Sec
		if(m3==255)
			if((s11 != s12) | (s21 != s22))
			{//Both Wheels Stuck
			switch(cmd_old)
			{
			case 32:
			 cmd_old=33;
			 break;
			case 33:
			 cmd_old=32;
			 break;
			 }
		sbi(PORTD, 6);
			}

			 lrwc=0;
		}
	//IR-Remote--------------------------------------
		if(irMode==0)
		{
			if(irState==1)
			{
				irMode=1;
				irState=0;
			}
			else
			{
				if(c3p5>5000)
				{
					c3p5=0;
					irMode=1;
					irState=0;
				}
			}
		}
	//---------------------------------------------
	}
//==================================	
return 0;

}
//********************************************
