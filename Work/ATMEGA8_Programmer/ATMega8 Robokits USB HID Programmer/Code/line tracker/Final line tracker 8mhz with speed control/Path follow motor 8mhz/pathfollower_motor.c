
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
 
 The ports used to drive the motor
 PORTB:-0,1,6,7.
 The ports set in various conditions
 Forward:-PORTB-0,7
 Left:-PORTB-1,7
 Right:-PORTB-0,6
 Stop:-none
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include<avr/io.h>					//HEADER FILE FOR AVR INPUT OUTPUT
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY
#include <avr/interrupt.h>
/*----------------------------------------------------------------
-----------------Timer variables-------------------------------------
-----------------------------------------------------------------*/
#define TIMER_0_CNT     0x82  // 1 ms sec, use AVRcalc to calculate these values
                                // ((TCNT0=0x63))
								// DECIMAL VALUE = 130
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-130 = 125 COUNTS
#define TMC8_CK8	(_BV(CS01)+_BV(CS00))	// 8 BIT TIMER0 AT 64 PRESCALAR
											// GIVES 64*125 = 8000 CYCLES		//8mhz 1 msec delay
											// AT 1MHZ FREQUENCY DELAY OF 90.112 mSECONDS

static volatile int detectline=0;
char timercount=0;
/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

void path_follower_motor(int detectline);
void robotmove(char mode);
void motormove(char motor,char state);
void speed(char direction,int value);

SIGNAL(SIG_OVERFLOW0)            	// signal handler for tcnt1 overflow interrupt
{
	TCNT0  = TIMER_0_CNT;
	timercount++;
	if(timercount==5)
	{
		
		if((!bit_is_clear(PINC,1) && !bit_is_clear(PINC,2)))
			detectline=1;	//forward
		else if((bit_is_clear(PINC,1) && !bit_is_clear(PINC,2)))
			detectline=2;	//right
		else if((!bit_is_clear(PINC,1) && bit_is_clear(PINC,2)))
			detectline=3;	//left
		else if((bit_is_clear(PINC,1) && bit_is_clear(PINC,2)))
			detectline=4;
		timercount=0;
		path_follower_motor(detectline);
	}
}

void speed(char direction,int value)
{
	int i=0;
	while(TCNT0< 254)
	{
		for(i=0;i<255-value;i++)
		{
			PORTB=0x00;
		}
		for(i=0;i<value;i++)
		{
			PORTB=direction;
		}
		
	}
}



void path_follower_motor(int detectline)
{
	char direction;
	switch(detectline)
	{
		case 1:	//forward
				direction=0x81;
				speed(direction,190);
				return;
		case 2:	//right
				direction=0x41;
				speed(direction,220);
				return;
		case 3:	//left
				direction=0x82;
				speed(direction,220);
				return;
		case 4:	//stop
				direction=0x00;
				speed(direction,255);
				return;
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