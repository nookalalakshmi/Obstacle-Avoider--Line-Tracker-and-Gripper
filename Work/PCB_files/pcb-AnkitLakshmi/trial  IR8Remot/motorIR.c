//			Two Motors and a Proximity IR sensor

/*-------------------------------------------------------------------          
 Operation-
 1. IR-Remote ecoder	
 2. Test IR-Remote using 4-LEDs

 Description:
 CPU => ATMEGA8-L @8MHz Internal

 
    
  PC0-INPUT- TSOC IR-Sensor Pin-3
  
  PD0-OUTPUT-LED-1 Red    	#2
  PD1-OUTPUT-LED-2 Green	#3
  PD2-OUTPUT-LED-3 Red		#4
  PD3-OUTPUT-LED-4 Green	#5
  
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/
//#define TMC8_CK8	(_BV(CS22))	// 8 BIT TIMER2 AT 256 PRESCALAR
#define TMC8_CK8	(_BV(CS21))	// 8 BIT TIMER2 AT 8 PRESCALAR
												// GIVES 8*64 = 512 CYCLES
												// AT 8MHZ FREQUENCY  = 0.125 microSECONDS/cycle
												
#define TIMER_2_CNT   191// 64 micro sec, use AVRcalc to calculate these values
								// MAX VALUE = 255 and up counting from 191
								// TIMER OVERFLOW ON 255-191 = 64 COUNTSd

static volatile uint8_t led;     // use volatile when variable is accessed from interrupts

/*----------------------------------------------------------------
-----------------FUNCTION-----------------------------------------
-----------------------------------------------------------------*/
SIGNAL(SIG_OVERFLOW2)     // signal handler for tcnt2 overflow interrupt
{//every 70.721usec here
     sbi(PORTD,1);
    TCNT2 = TIMER_2_CNT; // reset counter to get this interrupt again
}




/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{    

	DDRD=0X0F;				//SET DATA DIRECTION REGISTER
	
	TCCR2 = TMC8_CK8;               	
    TCNT2  = TIMER_2_CNT;  	// reset TCNT1
     TIMSK  = _BV(TOIE2);         	// enable TCNT2 overflow 
    
    sei();                       	// enable interrupts
	   

    for (;;)			 	//
	{	
	
		if(bit_is_clear(PIND,0))
		{
			sbi(PORTD,0);			//LED ON
			_delay_ms(250);
		}
		else
		{
			cbi(PORTD,0);			//LED OFF
			_delay_ms(250);
		}
//			   if(cmd==0)			     sbi(PORTD,0);				 else				 cbi(PORTD,0);
	}		
}
