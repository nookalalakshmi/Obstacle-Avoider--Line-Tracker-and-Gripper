//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR BLINKING LED'S ON TIMER1
//			WRITTEN FOR PRODUCT ID 19

/*-------------------------------------------------------------------          
 Description:
 This example shows how to generate delays with timers so that cpu is
 free for processing other things. Here cpu is used for blinking led2.

 Note:
 Led2 is blinking with normal delay routine and led3 on timer1 interrupt.
 
 Both leds work at almost 1hz rate.
 
 Since _delay_ms() function will be affected by the interrupt generation 
 and gives more delay. So, after sometime the led timing will be mismached.
 
 Even the timer delay is not perfectly mached to 1s. Use smaller presclar
 for better operation.
 
  _delay_ms() function parameter passed should not exeed
 262.14ms / F_CPU in mhz.
 
 so for 16MHz the maximum paramer should be 16ms.
 
 For 1MHz it can be upto 262ms (250 is used for this example).
  
 Must be changed to get accurate delay at higher MHz.
 
 The timing will differ if the operating frequency is changed.
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY

/*----------------------------------------------------------------
-----------------CONSTANTS----------------------------------------
-----------------------------------------------------------------*/

#define TIMER_1_CNT     0x85ED  // 250 msec in 1 MHZ and 31.25 milisec in 8MHZ, use AVRcalc to calculate these values
                                // ((TCNT1H=0xfc, TCNT1L=0x2e)
								// DECIMAL VALUE = 34285
								// MAX VALUE = 65535
								// TIMER OVERFLOW ON 65535-34285 = 31250 COUNTS
#define CNT             0xfffc
#define TMC16_CK8	(_BV(CS11))	// 16 BIT TIMER1 AT 8 PRESCALAR
												// GIVES 8*31250 = 250000 CYCLES
												// AT 1MHZ FREQUENCY DELAY OF 1.000448 SECONDS

/*----------------------------------------------------------------
-----------------GLOBAL VARIABLE----------------------------------
-----------------------------------------------------------------*/

static volatile uint8_t led; 					// use volatile when variable is accessed from interrupts


/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

SIGNAL(SIG_OVERFLOW1)            	// signal handler for tcnt1 overflow interrupt
{
	
	if (bit_is_clear(PINB, 5))		//BLINK LED3 ON TIMER INTERRUPT
		sbi(PORTB,5);				//LED3 ON
	else					
		cbi(PORTB,5);				//LED3 OFF	
	   
	TCNT1 = TIMER_1_CNT;// reset counter to get this interrupt again
}

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
    
	DDRB=0x20;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTB.0 IS OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	
	DDRD=0x00;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTD.7 AND PORTD.6 ARE OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	
//	sbi(PORTB,0);					//LED1 ON (INDICATION FOR READY TO USE)

    TCCR1A = 0x00;               	// disable PWM and Compare Output Mode
    TCCR1B = TMC16_CK8;       	// use CLK/1024 prescale value
    TCNT1  = CNT;        	// reset TCNT1
    
    TIMSK  = _BV(TOIE1);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts 
    
    for (;;) 						// loop forever
	{                      
			
		
    }
}
