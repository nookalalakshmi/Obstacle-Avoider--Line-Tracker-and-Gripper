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
SIGNAL(SIG_OVERFLOW0)
{
TCNT0=0;

}


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
	
	
}
unsigned char getdatabit(void)
{
unsigned char pulseCount=0, code = 0;
pulseCount = 0;


	while(pulseCount < 6)
	{
		TCNT0=0;
		if(bit_is_clear(PIND,2))
		{
			while(bit_is_clear(PIND,2));
			count=TCNT0;
			if(count>15)
			{
				
				flag=1;
				break;
			}
			else
			{
				
				TCNT0=0;
				while(TCNT0<15);
				pulseCount++;
				code = code | (1 << (pulseCount-1));
			}
		}
		else
		{
			while(!bit_is_clear(PIND,2));
			count=TCNT0;
			if(count>15)
			{
				
				flag=1;
				break;
			}
			else
			{
				
				TCNT0=0;
				while(TCNT0<15);
				pulseCount++;
				code = code & ~(1 << (pulseCount-1));
			}
		}
	}
	if(flag!=1)
	{
		
		return(code);
	}
	else
	{
		return(0);
	}

}
unsigned int read_IR (void)
{
unsigned char  code = 0;
unsigned int IR_input;
TCNT0=0;
while(TCNT0<71);

	code=getdatabit();

	if(code!=0)
	{
		IR_input = ((unsigned int)code);
		sbi(PORTB,2);
		return(IR_input);
	}
	else
		{ 
		 return(0);
		}
}



SIGNAL(SIG_INTERRUPT0)
{
 unsigned char count;
unsigned int IR_input=0;

TCNT0 = 0;
while((PIND & 0x04));
count = TCNT0;

if(count < 69) //to verify silence (4.4 ms long)
{
	_delay_ms(100); 
	
	return;
}

getstartbit();
if(a==1)
{
	
	TCNT0=0;
	while(TCNT0<43);	//Removal of control bit
	IR_input = read_IR ();
	//cbi(PORTB,2);
	PORTC =IR_input;
	return;
	
}
else
{
	return;
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
    
	
    TIMSK  = _BV(TOIE0);         	// enable TCNT1 overflow
	
    GIMSK=_BV(INT0);
	MCUCR = _BV(ISC01);          	// falling egde: int0
    TCNT0=0;
	
    sei();                       	// enable interrupts
	
	for(;;)
	{
		a=0;
		b=0;
		flag=0;
		cbi(PORTB,2);
		TCNT0=0;
		while(TCNT0<200);
		TCNT0=0;
		sbi(PORTB,2);
		while(TCNT0<200);
		
	}
	return(0);

}
