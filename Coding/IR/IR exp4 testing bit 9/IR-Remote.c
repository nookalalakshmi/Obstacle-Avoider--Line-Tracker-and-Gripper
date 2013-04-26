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

#define TMC8_CK8	(_BV(CS01)+_BV(CS00))	// 8 BIT TIMER2 AT 256 PRESCALAR
												// GIVES 256*176 = 45056 CYCLES=45.056msec
												// AT 1MHZ FREQUENCY  = 1 microSECONDS/cycle


/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
void getstartbit(void);
unsigned char getdatabit(void);


/*----------------------------------------------------------------
-----------------FUNCTIONS-------------------------------------
-----------------------------------------------------------------*/



void getstartbit(void)
{
	unsigned char count;
	TCNT0 = 0;
	while(bit_is_clear(PIND,2));
	while(!bit_is_clear(PIND,2));
	count=TCNT0;
	if(count>25)
	{
		a=1;
		
	}
	else
	{
	a=0;
	}
	
	
}




SIGNAL(SIG_INTERRUPT0)
{
 unsigned char count;
unsigned int IR_input=0;

TCNT0 = 0;
while((PIND & 0x04));
count = TCNT0;

if(count < 55) //to verify silence (3.5 ms long)
{
	 
	_delay_ms(40);
	return;
}

getstartbit();
if(a==1)
{
	
	TCNT0=0;
	
	while(TCNT0<43);	//not to consider control bit
	TCNT0=0;
	while(TCNT0<155);	//not to consider address bits
	TCNT0=0;
	//while(TCNT0<141);	//not consideing first 5.5 command bits
	PORTC=0x00;
	
	if(bit_is_clear(PIND,2))
	{
		sbi(PORTB,2);
		PORTC |= 0x20;
	}
	else
	{
		cbi(PORTB,2);
		cbi(PORTC,5);
	}
	
	return;
	
}
else
{
	cbi(PORTB,2);
}


	
}



/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
	
	
	DDRB=0x04;
	DDRD=0x00;
	
	DDRC=0x3F;				//Set Port C 0-5 pins as output port all bits.
	
	TCCR0 = TMC8_CK8;               	
    
	
    TIMSK  = 0x00;         	// enable TCNT1 overflow
	
    GIMSK=_BV(INT0);
	MCUCR = _BV(ISC01);          	// falling egde: int0

	
    sei();                       	// enable interrupts
	
	for(;;)
	{
		a=0;
		b=0;
		flag=0;
		
		
		
	}
	return(0);

}
