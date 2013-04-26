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
#define TIMER_2_CNT      118 // 114m sec, use AVRcalc to calculate these values
                                
								// DECIMAL VALUE = 143
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-118 = 137 COUNTS
#define TIMER_1_CNT		
#define TMC16_CK64 	(_BV(CS11)+_BV(CS10))

#define TMC8_CK8	(_BV(CS01)+_BV(CS00))	
#define	TMC8_CK1024	(_BV(CS22)+_BV(CS20))	// 8 BIT TIMER2 AT 1024 PRESCALAR
												// GIVES 1024*137 = 140000 CYCLES=114.000msec
												// AT 1MHZ FREQUENCY  = 1 microSECONDS/cycle


/*----------------------------------------------------------------
-----------------MOTOR FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
void motormove(char motor, char state)
{
	int n1=0,n2=0;
	if(motor=='1')
	{
		n1=7;
		n2=6;
	}
	if(motor=='2')
	{
		n1=0;
		n2=1;
	}
	switch (state)
	{
	 case 'F':
			sbi(PORTB,n1);
			cbi(PORTB,n2);
			break;

	case 'B':
			sbi(PORTB,n2);
			cbi(PORTB,n1);
			break;

	
	case 'S':
			cbi(PORTB,n2);
			cbi(PORTB,n1);
			break;

	case 's':
			cbi(PORTB,n1);
			cbi(PORTB,n2);
			break;
	}	
}
//***************************************
void robotmove(char mode)
{

	switch(mode)
	{
		case 'F':
		 motormove('1','F');
		 motormove('2','F');
		break;
		
		case 'B':
		 motormove('1','B');
		 motormove('2','B');
		break;
		
		case 'R':
		 motormove('1','B');
		 motormove('2','s');
		break;
		
		case 'L':
		 motormove('1','s');
		 motormove('2','B');
		break;
		
		case 'r':
		 motormove('1','B');
		 motormove('2','F');
		break;
		
		case 'l':
		 motormove('1','F');
		 motormove('2','B');
		break;
		
		case 's':
		 motormove('1','s');
		 motormove('2','s');
		break;
		
		case 'S':
		 motormove('1','S');
		 motormove('2','S');
		break;
	}
}

/*----------------------------------------------------------------
-----------------REMOTE MOTOR INTERFACE FUNCTION------------------
-----------------------------------------------------------------*/
void call_motor(void)
{
	unsigned int code=0;
	code=PORTC;
	switch(PORTC)
	{
		case 0x26:
			sbi(PORTD,1);
			robotmove('F');
		break;
		
		case 0x24:
			cbi(PORTD,1);
			robotmove('B');
		break;
		
		case 22:
			
		break;
		
		case 20:
			
		break;
		
		case 56:
			
		break;
	}
	
}





/*----------------------------------------------------------------
-----------------REMOTE FUNCTIONS-------------------------------------
-----------------------------------------------------------------*/	
void detect_start(void)
{
	
	TCNT1=0;
	
	while(TCNT1<2047)
	{
		TCNT0=0;
		while(PIND & 0x04);
		count=TCNT0;
		if(count<55)
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
		TCNT1=0;
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
void detect_control(void)
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
void detect_data(void)
{
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
	
	detect_start();
	if(flag!=1)
	{
		detect_control();
		TCNT0=0;
		PORTC=0x00;
		while(TCNT0<114);
		detect_data();
		call_motor();
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
	DDRB=0xC7;
	DDRC=0x3F;
	DDRD=0x02;
	
	
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
