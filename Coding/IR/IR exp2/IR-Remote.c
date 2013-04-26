/*  
O/I-Test on ATMEGA8 cpu in "AVR 28 Pin DEV" Kit 
using- Programmers Notepad [WinAVR]
25-1-2009
Ankit and Lakshmi

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

static volatile uint8_t led; 					// use volatile when variable is accessed from interrupts

static volatile int count=0;
int ledout=0;
static volatile int  a=0;
static volatile int  b=0;
static volatile int  flag=0;
/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/
#define TIMER_2_CNT     79  // 45m sec, use AVRcalc to calculate these values
                                
								// DECIMAL VALUE = 79
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-79 = 176 COUNTS

#define TMC8_CK8	(_BV(CS02))	// 8 BIT TIMER2 AT 256 PRESCALAR
												// GIVES 256*176 = 45056 CYCLES=45.056msec
												// AT 1MHZ FREQUENCY  = 1 microSECONDS/cycle


/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
void getstartbit(void);
void getdatabit(void);


/*----------------------------------------------------------------
-----------------FUNCTIONS-------------------------------------
-----------------------------------------------------------------*/

void getstartbit(void)
{
	int i;
	if(bit_is_clear(PIND,2))
	{
		for(i=0;i<900;i++)
		{
			
		}
		if(bit_is_clear(PIND,2))
		{
			a=1;
			
		}
		else
		{
			a=0;
			
		}
	}
}

void getdatabit(void)
{
	int i;
	for(i=0;i<900;i++)
	{
	
	}
	if(bit_is_clear(PIND,2))
	{
		b=1;
		sbi(PORTB,2);
		
	}
	else
	{
		b=0;
		
	}
}


SIGNAL(SIG_INTERRUPT0)
{
 
	int i;

	for(i=0;i<1750;i++)
	{
		
	}
	
		getstartbit();	
			
			if(a==1)
			{
				for(i=0;i<5400;i++)
				{
		
				}
				for(i=5;i>=0;i--)
				{
					getdatabit();
					if(b==1)
					{
						sbi(PORTC,i);
						cbi(PORTB,2);
						b=0;
					}
					else
					{
						cbi(PORTC,i);
					}
				}
				a=0;
		
			}	
	
		
 
}


/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
	
	
	DDRB=0x04;
	
	
	DDRC=0x3F;				//Set Port C 0-5 pins as output port all bits.
	
	/*TCCR0 = TMC8_CK8;               	
    
    TCNT0  = TIMER_2_CNT;        	// reset TCNT1
    
    TIMSK  = _BV(TOIE0);         	// enable TCNT1 overflow*/ 
	
    GIMSK=_BV(INT0);
	MCUCR = _BV(ISC01);          	// falling egde: int0
    
	
    sei();                       	// enable interrupts
	
	for(;;)
	{
		
	}
	return(0);

}
