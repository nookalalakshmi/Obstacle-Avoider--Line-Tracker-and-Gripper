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

#define TIMER_1_CNT     0xfc2e  // 1 sec, use AVRcalc to calculate these values
                                // ((TCNT1H=0xfc, TCNT1L=0x2e)
								// DECIMAL VALUE = 64558
								// MAX VALUE = 65535
								// TIMER OVERFLOW ON 65535-64558 = 977 COUNTS

#define TMC16_CK1024	(_BV(CS12)+_BV(CS10))	// 16 BIT TIMER1 AT 1024 PRESCALAR
												// GIVES 1024*977 = 1000448 CYCLES
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
	if (bit_is_clear(PINA, 6))		//BLINK LED3 ON TIMER INTERRUPT
		sbi(PORTA,6);				//LED3 ON
	else							//ELSE
		cbi(PORTA,6);				//LED3 OFF	
    TCNT1 = TIMER_1_CNT;         	// reset counter to get this interrupt again
}

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
    
	DDRA=0xF0;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PA.4, PA.5, PA.6 AND PA.7 ARE OUTPUT
									//ALL OTHERS ARE INPUT
									
	DDRB=0XFB;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PB.2 IS  INPUT
									//ALL OTHERS ARE OUTPUT
	
	DDRD=0XF1;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PD.1, PD.2 AND PD.3 ARE INPUT
									//ALL OTHERS ARE OUTPUT

	sbi(PORTA,4);					//LED1 ON (INDICATION FOR READY TO USE)									

	sbi(PORTB,2);					//ENABLE PULL UP FOR SWITCH INT2
	sbi(PORTD,1);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1

    TCCR1A = 0x00;               	// disable PWM and Compare Output Mode
    TCCR1B = TMC16_CK1024;       	// use CLK/1024 prescale value
    TCNT1  = TIMER_1_CNT;        	// reset TCNT1
    
    TIMSK  = _BV(TOIE1);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts 
    
    for (;;) 						// loop forever
	{                      
		if (bit_is_clear(PINA, 5))	//BLINK LED2 WITH NORMAL DELAY
			sbi(PORTA,5);			//LED2 ON
		else						//ELSE
			cbi(PORTA,5);			//LED2 OFF
		_delay_ms(250);				
		_delay_ms(250);	
		_delay_ms(250);	
		_delay_ms(250);	
    }
}
