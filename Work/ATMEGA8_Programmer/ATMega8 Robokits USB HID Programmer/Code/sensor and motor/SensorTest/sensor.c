//			Two Motors and a Proximity IR sensor

/*-------------------------------------------------------------------          
 Operation-
	This program senses the obstacles and that the obstacle is sensed is signalled by the LED.
 Description:
 CPU => ATMEGA8-L @8MHz Internal

  Proximity IR Sensor Input
  Sensor-1(#4):
  PD2(INT0)	State
  0			Obstruction
  1			Clear Path
  Sensor-2(#23):
  PC0		State
  0			Obstruction
  1			Clear Path
---------------------------------------------------------------------*/

//************** HEADER FILES ********************
#include<avr/io.h>					//HEADER FILE FOR AVR INPUT OUTPUT
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY
#include <avr/interrupt.h>

//************** GLOBAL VARIABLES ********************
#define TIMER_0_CNT     0x82  // 1ms sec, use AVRcalc to calculate these values
                                // ((TCNT0=0x63))
								// DECIMAL VALUE = 130
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-130 = 125 COUNTS
#define TMC8_CK8	(_BV(CS01)+_BV(CS00))	// 8 BIT TIMER0 AT 64 PRESCALAR
											// GIVES 64*125 = 8000 CYCLES		//8mhz 1 msec delay
											// AT 1MHZ FREQUENCY DELAY OF 90.112 mSECONDS

char psensor=0;
char onpsensor=0;
char flag=0;
//************** FUNCTIONS ********************
SIGNAL(SIG_OVERFLOW0)            	// signal handler for tcnt1 overflow interrupt
{
	psensor++;
	onpsensor++;
	while(onpsensor<=20)
	{
		if(psensor==2)
		{
			if(bit_is_clear(PINC,5))
			{
				sbi(PORTC,5);
				
			}
			else
			{
				cbi(PORTC,5);
				
			}
			psensor=0;
		}
		
		
	}
	if(onpsensor==20)
	{
		onpsensor=0;
		_delay_ms(100);
	}
	TCNT0  = TIMER_0_CNT;
	
}

//************** INTERRUPT0 ********************
SIGNAL(SIG_INTERRUPT0)     
{//signal handler for external interrupt int0          
			sbi(PORTB,2);			//LED ON
}


//************** MAIN PROGRAM ********************
int main(void)
{
//SET DATA DIRECTION REGISTER	
//SET 1 for OUTPUT PORT
//SET 0 FOR INPUT PORT
	DDRB=0xC7;						//PB
	DDRC=0x00;						//PC
	DDRD=0xF1;						//PD
	
	TCCR0 = TMC8_CK8;       		// use CLK/1024 prescale value
    TCNT0  = TIMER_0_CNT;        			// reset TCNT1
    
    TIMSK  = _BV(TOIE0);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts 
 

	while(1)						//INFINITE LOOP
	{
		if(onpsensor==0 || onpsensor==1 || onpsensor==2)
		{
		}
		else if(onpsensor==3)
		{
			if(bit_is_clear(PIND,2))
			{
				sbi(PORTB,2);
			}
			else
			{
				cbi(PORTB,2);
			}
		}
		else
		{
			_delay_ms(2);
			if(bit_is_clear(PIND,2))
			{
				sbi(PORTB,2);
			}
			else
			{
				cbi(PORTB,2);
			}
		}
	}
	return(0);
}

