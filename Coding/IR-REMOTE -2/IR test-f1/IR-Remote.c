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
static volatile int silence=0;
static volatile int startdetector=0;
static volatile int bitdetector=0; 
char flag=2;

/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/


#define TIMER_0_CNT     254  // 64 micro sec, use AVRcalc to calculate these values
								// MAX VALUE = 255 and up counting from 191
								// TIMER OVERFLOW ON 255-254 = 1 COUNTS

#define TMC08_CK64	(_BV(CS01)+_BV(CS00))	// 8 BIT TIMER0 AT 64 PRESCALAR
												// GIVES 64*1 = 64 CYCLES
												// AT 8MHZ FREQUENCY  = 0.125 microSECONDS/cycle
												
#define TIMER_2_CNT     254  // 64 micro sec, use AVRcalc to calculate these values
								// MAX VALUE = 255 and up counting from 191
								// TIMER OVERFLOW ON 255-254 = 1 COUNTS

#define TMC28_CK8	(_BV(CS21))	// 8 BIT TIMER0 AT8 PRESCALAR
												// GIVES 8*1 = 8 CYCLES
												// AT 8MHZ FREQUENCY  = 0.125 microSECONDS/cycle


SIGNAL(SIG_OVERFLOW2)            	
{
	
	bitdetector=bitdetector+1;
    TCNT2 = TIMER_2_CNT;         	
	
}

//---------------------------------------------
void detect_silence(void)
{
	TCNT0  = 0;
	silence=0;
	startdetector=0;
	
	
	for(;;)
	{
		
		if(bit_is_clear(PIND,2))
		{
			silence=TCNT0;
			
		}
		else
		{
			silence=0;
		}
		startdetector=TCNT0;
		if(silence>=6)
		{
			flag=0;
			break;
		}
		if(startdetector>246)
		{
			flag=1;
			break;
		}
	}
	if(flag==1 || flag==2)
		return;
	//while(bit_is_clear(PIND,2));
	startdetector=0;
	for(;;)
	{
		TCNT0  = 0;
		if(!bit_is_clear(PIND,2))
		{
			flag=0;
			break;
		}
		startdetector=TCNT0;
		if(startdetector>246)
		{
			flag=1;
			break;
		}
	}
	
}
void detect_start(void)
{
	int i=0;
	
	TCNT2  = TIMER_2_CNT;
	bitdetector=0;
		while(bitdetector>165);
	
		if(!bit_is_clear(PIND,2))
		{
			flag=0;
		}
		else
		{
			flag=1;
		}
		if(flag==1)
			return;
		
		for(i=0;i<9;i++)
		{
			TCNT2  = TIMER_2_CNT;
			bitdetector=0;
			while(bitdetector>=225);
		}
		bitdetector=0;
		if(bit_is_clear(PIND,2))
		{
			cbi(PORTB,2);
		}
		else
		{
			sbi(PORTB,2);
		}
}

/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
   	
	DDRD=0x00;
	DDRC=0xFF;				//Set Port C as output port all bits.
	DDRB=0x04;
	TCCR0 = TMC08_CK64;               	
    TCNT0  = TIMER_0_CNT;        	// reset TCNT0
	TCCR2 =TMC28_CK8;
    TCNT2  = TIMER_2_CNT;
	TIMSK=(_BV(TOIE2));
    sei();                       	// enable interrupts
	
	for(;;)
	{
		detect_silence();
	
		if(flag==0)
		{
			detect_start();
			
		}
		else
		{
			

		}

	}
	
return 0;

}
