//			Two Motors and a Proximity IR sensor

/*-------------------------------------------------------------------          
 Operation-
 1. IR-Remote ecoder	
 2. Test IR-Remote using 4-LEDs

 Description:
 CPU => ATMEGA8-L @8MHz Internal

 
    
  PC0-INPUT- TSOC IR-Sensor Pin-3
  
  PD0-OUTPUT-LED-1 Red    	#2
  PD1-OUTPUT-LED-2 Green	#3
  PD2-OUTPUT-LED-3 Red		#4
  PD3-OUTPUT-LED-4 Green	#5
  
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/
//#define TMC8_CK8	(_BV(CS22))	// 8 BIT TIMER2 AT 256 PRESCALAR
#define TMC8_CK8	(_BV(CS21))	// 8 BIT TIMER2 AT 8 PRESCALAR
												// GIVES 8*64 = 512 CYCLES
												// AT 8MHZ FREQUENCY  = 0.125 microSECONDS/cycle
												
#define TIMER_2_CNT     190  //191: 64 micro sec, use AVRcalc to calculate these values
								// MAX VALUE = 255 and up counting from 191
								// TIMER OVERFLOW ON 255-191 = 64 COUNTSd

static volatile uint8_t led;     // use volatile when variable is accessed from interrupts

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

/*----------------------------------------------------------------
-----------------FUNCTION-----------------------------------------
-----------------------------------------------------------------*/
//Timer2 OVERFLOW Interupt----------------------
SIGNAL(SIG_OVERFLOW2)     // signal handler for tcnt2 overflow interrupt
{//every 70.721usec here
	char d;
//     sbi(PORTD,2);
	c3p5++;
	pwmc++;
    TCNT2 = TIMER_2_CNT; // reset counter to get this interrupt again
	
	if(pwmc==0)
	{
     c131++;	
	 count++;
	}
	if(count==0)
	{
	  
	}
	if(count==128)
	{
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
			d_old=bit_is_clear(PINC,0);
			return;
		}
		if(irState==1)
		{
			d=bit_is_clear(PINC,0);
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
			d=bit_is_clear(PINC,0);
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
					//PORTD=0;
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
			d=bit_is_clear(PINC,0);
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
			//PORTD=cmd;
			
				
			}
			return;
		}		
		if(irState==1)
		{
			if(c3p5>16)
			{//skip bit boundary
				irState=0;
				d=bit_is_clear(PINC,0);
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
/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{    
	irState=0;
	irMode=1;
	DDRD=0X0F;				//SET DATA DIRECTION REGISTER
	TCCR2 = TMC8_CK8;               	
    TCNT2  = TIMER_2_CNT;        	// reset TCNT1
     TIMSK  = _BV(TOIE2);         	// enable TCNT2 overflow 
    
    sei();                       	// enable interrupts

    for (;;)			 	//
	{	
	
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
		PORTD=cmd;
		_delay_ms(10);
	}		
}
