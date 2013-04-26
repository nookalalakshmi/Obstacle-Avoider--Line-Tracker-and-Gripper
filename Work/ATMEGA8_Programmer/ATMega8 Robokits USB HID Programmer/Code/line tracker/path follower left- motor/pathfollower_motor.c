
//			MADE BY ANKIT-LAKSHMI
//			PROGRAM FOR PATH FOLLOWER

/*-------------------------------------------------------------------          
 Description:
 The robot will follow a 'black' path near which it is placed. In 
 situations where it goes out of track, the indicator LEDs will tell 
 the direction to move to get back its path.
 
 Note:
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

#include<avr/io.h>					//HEADER FILE FOR AVR INPUT OUTPUT
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY
#include <avr/interrupt.h>
int mode=0;
/*----------------------------------------------------------------
-----------------Timer variables-------------------------------------
-----------------------------------------------------------------*/
#define TIMER_0_CNT     0xB1  // 5 ms sec, use AVRcalc to calculate these values
                                // ((TCNT0=0x63))
								// DECIMAL VALUE = 130
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-177 = 78 COUNTS
#define TMC8_CK8	(_BV(CS01)+_BV(CS00))	// 8 BIT TIMER0 AT 8 PRESCALAR
												// GIVES 64*78 = 5000 CYCLES
												// AT 1MHZ FREQUENCY DELAY OF 90.112 mSECONDS
/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

void path_follower_motor(void);

SIGNAL(SIG_OVERFLOW0)            	// signal handler for tcnt1 overflow interrupt
{
	cbi(PORTB,7);
	cbi(PORTB,6);
	cbi(PORTB,1);
	cbi(PORTB,0);
	path_follower_motor();
	TCNT0  = TIMER_0_CNT;
}


void func(int m,int s1,int s2)
{
	
	mode=m;
	char i=0;
	
	
	switch(mode)
	{
		case 1://full speed
		
				for(i=0;i<255;i++)
				{
					sbi(PORTB,s1);
					sbi(PORTB,s2);
				}
		
		
		
		case 2:
		
				for(i=0;i<200;i++)
				{
					sbi(PORTB,s1);
					sbi(PORTB,s2);
				}
				cbi(PORTB,s1);
				cbi(PORTB,s2);
		
		
		
		case 3:
		
				for(i=0;i<145;i++)
				{
					sbi(PORTB,s1);
					sbi(PORTB,s2);
				}
				cbi(PORTB,s1);
				cbi(PORTB,s2);
		
		
		case 4:
		
				for(i=0;i<105;i++)
				{
					sbi(PORTB,s1);
					sbi(PORTB,s2);
				}
				cbi(PORTB,s1);
				cbi(PORTB,s2);
		
		
		
	}
}
void path_follower_motor(void)
{

	
	if((bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)))
	{
		do
		{
			func(1,6,0);
			
		}while((!bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)));
	
	}
	if((bit_is_clear(PINC,2)) && (!bit_is_clear(PINC,1)))
	{
		do
		{
			func(1,7,1);
			
		}while((!bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)));

	}
	if((!bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)))
	{
		
        do
		{
			func(2,7,0);
			
		}while((!bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)));

	}
	if((bit_is_clear(PINC,1)) && (bit_is_clear(PINC,2)))
	{
		cbi(PORTB,7);
		cbi(PORTB,6);
		cbi(PORTB,1);
		cbi(PORTB,0);
	}
	
}
/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/
int main(void)
{
	DDRD=0x0F;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTB.0 IS OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	DDRC=0x00;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTD.7 AND PORTD.6 ARE OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	DDRB = 0xC7;
	
	TCCR0 = TMC8_CK8;       		// use CLK/1024 prescale value
    TCNT0  = TIMER_0_CNT;        			// reset TCNT1
    
    TIMSK  = _BV(TOIE0);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts 
 

	for(;;)
	{

	}
	return(0);
}