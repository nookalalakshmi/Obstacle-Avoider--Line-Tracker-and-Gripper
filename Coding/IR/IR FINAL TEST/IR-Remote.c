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
#define TIMER_2_CNT      143 // 114m sec, use AVRcalc to calculate these values
                                
								// DECIMAL VALUE = 143
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-143 = 112 COUNTS
#define TIMER_1_CNT		
#define TMC16_CK64 	(_BV(CS11)+_BV(CS10))

#define TMC8_CK8	(_BV(CS01)+_BV(CS00))	
#define	TMC8_CK1024	(_BV(CS22)+_BV(CS20))	// 8 BIT TIMER2 AT 1024 PRESCALAR
												// GIVES 1024*112 = 114688 CYCLES=114.000msec
												// AT 1MHZ FREQUENCY  = 1 microSECONDS/cycle


/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/



/*----------------------------------------------------------------
-----------------FUNCTIONS-------------------------------------
-----------------------------------------------------------------*/	
void detect(void)
{
	char m3p5=0;
	char m131=0;
	
	
	while(m131<=8)
	{
		TCNT0=0;
		while(PIND & 0x04);
		m3p5=TCNT0;
		if(TCNT0>220)
		{
			m131++;
		}
		if(m3p5<50)
		{
			flag=1;
		}
		else
		{
			flag=0;
		}
		
		if(flag==0)
		{
			break;
		}
	}

	if(flag==1)
	{
		return;
	}
	else
	{
		TCNT0=0;
		if(bit_is_clear(PIND,2))
		{	
			flag=0;
		}
		else
		{
			flag=1;
		}
	
		if(flag==0)
		{
			TCNT0=0;
			while(TCNT0<30);
			if(bit_is_clear(PIND,2))
			{
				flag=0;
			}
			else
			{
				flag=1;
			}
		}
		else
		{
			return;
		}
	}
	
}
void detectc(void)
{
	TCNT0=0;
	while(TCNT0<30);
	if(bit_is_clear(PIND,2))
	{
		sbi(PORTB,2);
		
	}
	else
	{
		cbi(PORTB,2);
	}
}
void detectb(void)
{
	PORTC=0x00;
	TCNT0=0;
	while(TCNT0<30);
	
	if(bit_is_clear(PIND,2))
	{
		PORTC|=0x20;
	}
	else
	{
		PORTC&= 0xdf;
	}
	
	TCNT0=0;
	while(TCNT0<30);
	
	if(bit_is_clear(PIND,2))
	{
		PORTC|=0x10;
	}
	else
	{
		PORTC&= 0xef;
	}
	
	TCNT0=0;
	while(TCNT0<30);
	
	if(bit_is_clear(PIND,2))
	{
		PORTC|=0x08;
	}
	else
	{
		PORTC&= 0xf7;
	}
	
	TCNT0=0;
	while(TCNT0<30);
	
	if(bit_is_clear(PIND,2))
	{
		PORTC|=0x04;
	}
	else
	{
		PORTC&= 0xfb;
	}
	
	TCNT0=0;
	while(TCNT0<30);
	
	if(bit_is_clear(PIND,2))
	{
		PORTC|=0x02;
	}
	else
	{
		PORTC&= 0xfd;
	}
	
	TCNT0=0;
	while(TCNT0<30);
	
	if(bit_is_clear(PIND,2))
	{
		PORTC|=0x01;
	}
	else
	{
		PORTC&= 0xfe;
	}
}

SIGNAL(SIG_OVERFLOW2)
{
	
	detect();
	if(flag!=1)
	{
		detectc();
		TCNT0=0;
		while(TCNT0<142);
		detectb();
		TCNT2=TIMER_2_CNT;
	}
	else
	{
		TCNT2=TIMER_2_CNT;
		return;
	}
	
}


/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
	DDRB=0x04;
	DDRC=0x3F;
	DDRD=0x00;
	
	
	TCCR0 = TMC8_CK8;               	
    TCCR1A=0x00;
	TCCR1B=TMC16_CK64;
	TCCR2=TMC8_CK1024;
    TIMSK  = _BV(TOIE2);         	// disable TCNT2 overflow
	TCNT2=TIMER_2_CNT;
	

	
    sei();                       	// enable interrupts
	
	
	for(;;)
	{
		
	}

}
