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
char m3p5=0;
int m131=0;
char u800=0;
int d_old=0;
int d_new=0;
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
void detect_start(void)
{
	while(m131<513)
	{
		TCNT0=0;
		while((PIND & 0x04));
		m3p5=TCNT0;
		if(TCNT0>220)
		{
			m131++;
		}
		if(m3p5>50)
		{
			flag=0;
			break;
		}
		else
		{
			flag=1;
		}
	}
	if(flag==0)
	{
		TCNT0=0;
		while(bit_is_clear(PIND,2));
		u800=TCNT0;
		if(u800>=13 && u800<15)
		{
			TCNT0=0;
			while(!bit_is_clear(PIND,2));
			u800=TCNT0;
			if(u800>=13 && u800<15)
			{
				d_old=bit_is_clear(PIND,2);
				TCNT0=0;
				while(TCNT0<14)
				{
					d_new=bit_is_clear(PIND,2);
					if(d_old==d_new)
					{
						flag=0;
						d_old=d_new;
						continue;
					}
					else
					{
						flag=1;
						break;
					}
				}
				
			}
			
		}
		else
		{
			flag=1;
		}
	}
}
void detect_control(void)
{
	
	
	TCNT0=0;
	
	while(TCNT0<21);	//to watch control bit
	if(bit_is_clear(PIND,2))
	{
		sbi(PORTD,6);
	}
	else
	{
		cbi(PORTD,6);
	}
	
	
	return;
	/*if(bit_is_clear(PIND,2))
	{
		while(bit_is_clear(PIND,2));
		u800=TCNT0;
		if(u800>=13 && u800<15)
		{
			TCNT0=0;
			d_old=bit_is_clear(PIND,2);
			while(TCNT0<13)
			{	
				d_new=bit_is_clear(PIND,2);
				if(d_old==d_new)
				{
					d_old=d_new;
					sbi(PORTD,6);
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		else
		{
			flag=1;
		}
	}
	else 
	{
		while(!bit_is_clear(PIND,2));
		u800=TCNT0;
		if(u800>=13 && u800<15)
		{
				TCNT0=0;
				while(bit_is_clear(PIND,2));
				u800=TCNT0;
				if(u800>=13 && u800<15)
				{
					TCNT0=0;
					d_old=bit_is_clear(PIND,2);
					while(TCNT0<13)
					{	
						d_new=bit_is_clear(PIND,2);
						if(d_old==d_new)
						{
							d_old=d_new;
							cbi(PORTD,6);
						}
						else
						{
							flag=1;
							break;
						}
					}
				}
				else
				{
					flag=1;
				}
			
		}
		else
		{
			flag=1;
		}
		
			
	}
	*/

}
void detect_address(void)
{
	int pulsecount=0;
	while(pulsecount<5)
	{
		TCNT0=0;
		if(bit_is_clear(PIND,2))
		{
			while(bit_is_clear(PIND,2));
			u800=TCNT0;
			if(u800>=13 && u800<15)
			{
				TCNT0=0;
				d_old=bit_is_clear(PIND,2);
				while(TCNT0<13)
				{	
					d_new=bit_is_clear(PIND,2);
					if(d_old==d_new)
					{
						d_old=d_new;
						cbi(PORTC,pulsecount+1);
						pulsecount++;
					}
					else
					{
						pulsecount++;
						flag=1;
						break;
						
					}
				}
			}
			else
			{
				flag=1;
			}
		}
		else
		{
			while(!bit_is_clear(PIND,2));
			u800=TCNT0;
			if(u800>=13 && u800<15)
			{
				TCNT0=0;
				d_old=bit_is_clear(PIND,2);
				while(TCNT0<13)
				{	
					d_new=bit_is_clear(PIND,2);
					if(d_old==d_new)
					{
						d_old=d_new;
						sbi(PORTC,pulsecount+1);
						pulsecount++;
					}
					else
					{
						pulsecount++;
						flag=1;
						break;
						
					}
				}
			}
			else
			{
				flag=1;
			}
		}
	}
}
void detect_data(void)
{
	PORTC=0x00;
	int pulsecount=0;
	while(pulsecount<6)
	{
		TCNT0=0;
		if(bit_is_clear(PIND,2))
		{
			while(bit_is_clear(PIND,2));
			u800=TCNT0;
			if(u800>=13 && u800<15)
			{
				TCNT0=0;
				d_old=bit_is_clear(PIND,2);
				while(TCNT0<13)
				{	
					d_new=bit_is_clear(PIND,2);
					if(d_old==d_new)
					{
						d_old=d_new;
						cbi(PORTC,pulsecount);
						pulsecount++;
					}
					else
					{
						pulsecount++;
						flag=1;
						break;
						
					}
				}
			}
			else
			{
				flag=1;
			}
		}
		else
		{
			while(!bit_is_clear(PIND,2));
			u800=TCNT0;
			if(u800>=13 && u800<15)
			{
				TCNT0=0;
				d_old=bit_is_clear(PIND,2);
				while(TCNT0<13)
				{	
					d_new=bit_is_clear(PIND,2);
					if(d_old==d_new)
					{
						d_old=d_new;
						sbi(PORTC,pulsecount);
						pulsecount++;
					}
					else
					{
						pulsecount++;
						flag=1;
						break;
						
					}
				}
			}
			else
			{
				flag=1;
			}
		}
	}
}

void callIR(void)
{
	
	detect_start();
	
	
	if(flag==0)
	{
		detect_control();
		
		if(flag==0)
		{
			detect_address();
			if(PORTC==0x00)
			{
				detect_data();
			}
			
		}
		
	}
	if(flag==1)
	{
		sbi(PORTD,7);
		
	}
}


/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
	DDRB=0x04;
	DDRC=0x3f;
	DDRD=0xf0;
	
	TCCR0=TMC8_CK8;
	//TCCR2=TMC8_CK1024;
	//TCNT2=TIMER_2_CNT;
	//TIMSK=_BV(TOIE2);
	sei();
	
	for(;;)
	{
		if(bit_is_clear(PIND,2))
		{
			callIR();
		}
		else
		{
			sbi(PORTD,7);
		}
	}
	

}
