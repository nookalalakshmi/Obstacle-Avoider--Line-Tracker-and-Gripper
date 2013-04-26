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

#define TIMER_2_CNT     191  // 250	msec at 1 mhz and 31.25 milisec at 8MHZ, use AVRcalc to calculate these values
                                //	
								// DECIMAL VALUE = 34285
								// MAX VALUE = 65535
								// TIMER OVERFLOW ON 65535-34285 = 31250 COUNTS
#define CNT				0xfffc
#define TMC16_CK8	(_BV(CS21))	// 16 BIT TIMER1 AT 1024 PRESCALAR
												// GIVES 8*31250 = 250000 CYCLES
												// AT 8MHZ FREQUENCY DELAY OF 31.25 mSECONDS

/*----------------------------------------------------------------
-----------------GLOBAL VARIABLE----------------------------------
-----------------------------------------------------------------*/

static volatile uint8_t led; 					// use volatile when variable is accessed from interrupts


/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

SIGNAL(SIG_OVERFLOW2)            	// signal handler for tcnt1 overflow interrupt
{
			
		sbi(PORTD,1);				//LED3 ON
	
		
    TCNT2 = TIMER_2_CNT;         	// reset counter to get this interrupt again
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
	
	DDRD=0x0F;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTD.7 AND PORTD.6 ARE OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	
	//sbi(PORTB,0);					//LED1 ON (INDICATION FOR READY TO USE)

                	// disable PWM and Compare Output Mode
    TCCR2 = TMC16_CK8;       	// use CLK/1024 prescale value
    TCNT2  = TIMER_2_CNT;        	// reset TCNT1
    
    TIMSK  = _BV(TOIE2);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts 
    
    for (;;) 						// loop forever
	{   
		if(bit_is_clear(PIND,0))
		{
			sbi(PORTD,0);
			_delay_ms(250);
		}
		else
		{
			cbi(PORTD,0);
			_delay_ms(250);
		}

    }
}
