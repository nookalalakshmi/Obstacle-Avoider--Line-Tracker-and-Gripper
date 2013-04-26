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
//#define cnt0            0x00
#define TIMER_0_CNT     0xE5  // 26.624 ms sec, use AVRcalc to calculate these values
                                // ((TCNT0=0x63))
								// DECIMAL VALUE = 229
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-229 = 26 COUNTS
#define TIMER_0_CNT1   0xDF		// 32.768 ms sec, use AVRcalc to calculate these values
                                // ((TCNT0=0x63))
								// DECIMAL VALUE = 223
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-223 = 32 COUNTS
#define CNT             0xfc
#define TMC8_CK1024	(_BV(CS02)+_BV(CS00))	// 8 BIT TIMER0 AT 1024 PRESCALAR
												// GIVES 1024*32 = 32768 CYCLES
												// AT 1MHZ FREQUENCY DELAY OF 32.768 mSECONDS

/*----------------------------------------------------------------
-----------------GLOBAL VARIABLE----------------------------------
-----------------------------------------------------------------*/

static volatile uint8_t led; 					// use volatile when variable is accessed from interrupts
int volatile pw=100,count=0;

/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

SIGNAL(SIG_OVERFLOW0)            	// signal handler for tcnt1 overflow interrupt
{if(count==0)
	if(!bit_is_clear(PIND,6))
	{	TCNT0 = TIMER_0_CNT;
			//BLINK LED3 ON TIMER INTERRUPT
		cbi(PORTD,6);
	}
	else
	{
		sbi(PORTD,6);
	}
else if(count==1)
{
	if(!bit_is_clear(PIND,6))
	{	//TCNT0 = TIMER_0_CNT1;
		TCNT0=0x00;
			//BLINK LED3 ON TIMER INTERRUPT
		cbi(PORTD,6);
	}
	else
	{
				sbi(PORTD,6);
	}
}
/*else if(count==2)
{
	if(!bit_is_clear(PIND,6))
	{	TCNT0 = TIMER_0_CNT1;
			//BLINK LED3 ON TIMER INTERRUPT
		cbi(PORTD,6);
	}
	else
	{
		TCNT0=0x64-TIMER_0_CNT1;
		sbi(PORTD,6);
	}
}*/

}
SIGNAL(SIG_INTERRUPT0)     
/* s  tignal handler for external interrupt int0 */
{

	count++;
	if(count==2)
	{
		count=0;
	}
	//_delay_ms(100);


}
	     	

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
    
	DDRB=0x01;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTB.0 IS OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	
	DDRD=0xC0;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTD.7 AND PORTD.6 ARE OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	
	sbi(PORTB,0);					//LED1 ON (INDICATION FOR READY TO USE)

    //TCCR1A = 0x00;               	// disable PWM and Compare Output Mode
    TCCR0 = TMC8_CK1024;       	// use CLK/1024 prescale value
    TCNT0  = CNT;        	// reset TCNT1
    
    TIMSK  = _BV(TOIE0);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts 
    
    for (;;) 						// loop forever
	{      
		//_delay_ms(100);
		GIMSK = _BV(INT0);
		MCUCR = _BV(ISC01);
		
	}
}
