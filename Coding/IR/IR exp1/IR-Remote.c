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
#define TIMER_2_CNT     79  // 45m sec, use AVRcalc to calculate these values
                                
								// DECIMAL VALUE = 79
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-79 = 176 COUNTS

#define TMC8_CK8	(_BV(CS02))	// 8 BIT TIMER2 AT 256 PRESCALAR
												// GIVES 256*176 = 45056 CYCLES=45.056msec
												// AT 1MHZ FREQUENCY  = 1 microSECONDS/cycle

char volatile d[12]={'0'};
/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

SIGNAL(SIG_OVERFLOW0)            	// signal handler for tcnt1 overflow interrupt
{
	char sold=bit_is_clear(PIND,2);
	char s;
	sbi(PORTB,2);
	
	int i=0,j=0;
	for(i=0;i<1125;i++)
	{
		s=bit_is_clear(PIND,2);
		if(sold!=s)
		{		
			return;
		}
	}
	sold=bit_is_clear(PIND,2);
	for(i=0;i<600;i++)
	{
		s=bit_is_clear(PIND,2);
	}
	if(s!=sold)
	{
		return;
	}
	for(j=0;j<12;j++)
	{
		for(i=0;i<900;i++)
		{
		}
		d[j]=bit_is_clear(PIND,2);
		
		
	}
	if(d[6]=='1')
		sbi(PORTC,0);
	else
		cbi(PORTC,0);
		
	if(d[7]=='1')
		sbi(PORTC,1);
	else
		cbi(PORTC,1);
	

		
	if(d[8]=='1')
		sbi(PORTC,2);
	else
		cbi(PORTC,2);
	

		
	if(d[9]=='1')
		sbi(PORTC,3);
	else
		cbi(PORTC,3);
	

		
	if(d[10]=='1')
		sbi(PORTC,4);
	else
		cbi(PORTC,4);
	

		
	if(d[11]=='1')
		sbi(PORTC,5);
	else
		cbi(PORTC,5);
	
	TCNT0  = TIMER_2_CNT;        	// reset TCNT2

	return;
}

/*----------------------------------------------------------------
-----------------FUNCTIONS-------------------------------------
-----------------------------------------------------------------*/




/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
	DDRB=0x02;
	DDRD=0x00;
	
	DDRC=0x3F;				//Set Port C 0-5 pins as output port all bits.
	
	TCCR0 = TMC8_CK8;               	
    
    TCNT0  = TIMER_2_CNT;        	// reset TCNT1
    
    TIMSK  = _BV(TOIE0);         	// enable TCNT1 overflow 
	
    
    sei();                       	// enable interrupts
	
	for(;;)
	{
		cbi(PORTB,2);
	}
	return(0);

}
