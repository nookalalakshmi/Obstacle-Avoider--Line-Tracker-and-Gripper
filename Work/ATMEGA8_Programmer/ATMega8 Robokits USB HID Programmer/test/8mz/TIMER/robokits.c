//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR BLINKING LED'S ON TIMER1
//			WRITTEN FOR ROBOGRID

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

#define TIMER_0_CNT     0x82  // 1ms sec, use AVRcalc to calculate these values
                                
								// DECIMAL VALUE = 130
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-130 = 125 COUNTS

#define TMC8_CK64	(_BV(CS01)+_BV(CS00))	// 8 BIT TIMER0 AT 64 PRESCALAR
												// GIVES 64*125 = 8000 CYCLES
												// AT 8MHZ FREQUENCY = 0.125 micro SECONDS/clock cycle

/*----------------------------------------------------------------
-----------------GLOBAL VARIABLE----------------------------------
-----------------------------------------------------------------*/

static volatile uint8_t led; 					// use volatile when variable is accessed from interrupts


/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

SIGNAL(SIG_OVERFLOW1)            	// signal handler for tcnt1 overflow interrupt
{
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);
	sbi(PORTD,6);

    TCNT0 = TIMER_0_CNT;         	// reset counter to get this interrupt again
}

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
    
	DDRD=0xC0;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PA.4, PA.5, PA.6 AND PA.7 ARE OUTPUT
									//ALL OTHERS ARE INPUT
									
	
    TCCR0 = 0x03;               	// disable PWM and Compare Output Mode
    
    TCNT0  = TIMER_0_CNT;        	// reset TCNT1
    
    TIMSK  = _BV(TOIE0);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts 
    
    for (;;) 						// loop forever
	{                      
		cbi(PORTD,6);
    }
}
