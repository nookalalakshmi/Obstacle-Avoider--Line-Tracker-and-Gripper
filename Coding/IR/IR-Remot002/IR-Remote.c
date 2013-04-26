/*  
O/I-Test on ATMEGA8 cpu in "AVR 28 Pin DEV" Kit 
using- Programmers Notepad [WinAVR]
16-1-2009
Himanshu Mazumdar

This Experiment reads input from PD2(SW1) and PD3(SW2). 
It reads every 500 mSec (250+250).
As input has no pull-up resistor the 0 to 1 transition is slow.
if Sw1 is pressed LED2(PD7) is ON.
if Sw2 is pressed LED3(PD6) is ON.
LED-1 (PB0) is toggled every 250 mSec.
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

/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/
#define TIMER_2_CNT     223  // 1000 micro sec, use AVRcalc to calculate these values
                                // ((TCNT1H=0xfc, TCNT1L=0x2e)
								// DECIMAL VALUE = 191
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-223 = 32 COUNTS

#define TMC8_CK8	(_BV(CS22))	// 8 BIT TIMER2 AT 256 PRESCALAR
												// GIVES 256*32 = 8000 CYCLES
												// AT 8MHZ FREQUENCY  = 0.125 microSECONDS/cycle


/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

SIGNAL(SIG_OVERFLOW2)            	// signal handler for tcnt1 overflow interrupt
{
	count++;
	if(bit_is_clear(PORTC,0))
	{
		sbi(PORTC,0);
	}
	else
	{
		cbi(PORTC,0);
	}
		
	
		

    TCNT2 = TIMER_2_CNT;         	// reset counter to get this interrupt again
	
}

/*----------------------------------------------------------------
-----------------FUNCTIONS-------------------------------------
-----------------------------------------------------------------*/




/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{

	DDRA=0x80;				//Set Port A-6 as output port.
	DDRC=0xFF;				//Set Port C as output port all bits.
	TCCR2 = TMC8_CK8;               	
    
    TCNT2  = TIMER_2_CNT;        	// reset TCNT1
    
    TIMSK  = _BV(TOIE2);         	// enable TCNT1 overflow 
	
    
    sei();                       	// enable interrupts
	
	for(;;)
	{
/*		if(count>0){
		count = 0;
			if(bit_is_clear(PORTC,1))
			{
				sbi(PORTC,1);
			}
			else
			{
				cbi(PORTC,1);
			}
		}*/
		if((count & 0x02) == 0)
		{
			cbi(PORTC,1);
		}
		else
		{
			sbi(PORTC,1);
		}

	}
	return(0);

}
