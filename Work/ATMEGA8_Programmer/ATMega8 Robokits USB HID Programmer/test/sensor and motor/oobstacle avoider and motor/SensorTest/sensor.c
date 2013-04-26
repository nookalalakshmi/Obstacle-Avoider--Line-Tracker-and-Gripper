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

//************** FUNCTIONS ********************


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
	
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
    GICR = _BV(INT0);           	// enable external int0
    MCUCR = _BV(ISC01);          	// falling egde: int0*/
    sei();                       	// enable interrupts 
		
	sbi(PORTB,2);
	_delay_ms(2000);				//DELAY IN MILLISECONDS 
	cbi(PORTB,2);
	while(1)						//INFINITE LOOP
	{
		cli();                       	// desable interrupts 
			if (bit_is_clear(PINC,0) || bit_is_clear(PIND,2))	//IF Sensor1 senses obstacle
			{
				sbi(PORTB,2);
			}
			else
			{
				cbi(PORTB,2);
			}
	}
	return(0);
}

