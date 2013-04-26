
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
 
 The ports used in CPU-1 to drive the motor
 PORTB:-0,1,6,7.
 The ports set in various conditions
 Forward:-PORTB-0,7
 Left:-PORTB-1,7
 Right:-PORTB-0,6
 Reverse:-PORTB-1,6
 Stop:-none
 
The ports used to get input to CPU-1 from CPU-2
PORTC-1,2

Depending upon the values taken from PORTC 1,2 the actions are decided.
PORTC- (1,2):- the values accordingly where 0 indicates its out of black track and 1 indicates on black track
PORTC- (0,0):- Stop 
PORTC- (1,1):- Forward
PORTC- (1,0):- Left
PORTC- (0,1):- Right

Speed can be programmed according to requirement 
The speed can vary from 180 to 255.
Below 180 it would be very slow to avoid ground friction.
255 is maximum speed and speed limit.
So the bound from 180-255 are the different speeding grades used.
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
#define TIMER_0_CNT     0xC0  // 500 us sec, Timer set at 500 micro sec.
                                // ((TCNT0=0xC0))
								// DECIMAL VALUE = 192
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-192 = 63 COUNTS
#define TMC8_CK64	(_BV(CS01)+_BV(CS00))	// 8 BIT TIMER0 AT 64 PRESCALAR
											// GIVES 64*63 = 4000 CYCLES		//8mhz  500 micro sec delay
											// AT 8MHZ FREQUENCY 1 cycle is of 0.125 micro sec.
/*----------------------------------------------------------------
-----------------Constants-------------------------------------
-----------------------------------------------------------------*/


static volatile int detectline=0;
char timercount=0;
int stopcount=0;
int flag=0;
int backflag=0;
int startcount=0;
char pathfound=0;

/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

void path_follower_motor(int detectline);//Function to set speed and direction of move
void speed(char direction,int value);	//Sets the speed

SIGNAL(SIG_OVERFLOW0)            	// signal handler for tcnt0 overflow interrupt
{
	
	//Every 500 micro sec
	if(startcount==0)
	{
		_delay_ms(5000);	//During first time entering this mode delay is used
		startcount++;
	}
	TCNT0  = TIMER_0_CNT;
	
	if(flag==0)
	{	//PORTB=0x00;
		if((!bit_is_clear(PINC,1) && !bit_is_clear(PINC,2)))
			detectline=1;	//forward
		else if((bit_is_clear(PINC,1) && !bit_is_clear(PINC,2)))
			detectline=2;	//right
		else if((!bit_is_clear(PINC,1) && bit_is_clear(PINC,2)))
			detectline=3;	//left
		else if((bit_is_clear(PINC,1) && bit_is_clear(PINC,2)))
			detectline=4;	//stop;
				
		path_follower_motor(detectline);		
		
	}
	if(flag==1 && backflag==0 && pathfound==1)
	{
		stopcount=0;
		while(bit_is_clear(PINC,1) && bit_is_clear(PINC,2)) 
		{
			sbi(PORTB,2);
			PORTB=0x42;		//Reverse
			flag=0;
		}
		PORTB=0x00;
		cbi(PORTB,2);
		if(!bit_is_clear(PINC,1) && !bit_is_clear(PINC,2))
		{
			backflag=1;
		}
	}
	
}

void speed(char direction,int value)
{
	//This function will take value as speed and direction and will implement accordingly
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
	
	return;
}



void path_follower_motor(int detectline)
{
	//Set the direction and speed according to the line detected
	char direction;
	switch(detectline)
	{
		case 1:	//forward
				direction=0x81;
				pathfound=1;
				speed(direction,230);
				return;
		case 2:	//right
				direction=0x41;
				pathfound=1;
				speed(direction,220);
				return;
		case 3:	//left
				direction=0x82;
				pathfound=1;
				speed(direction,220);
				return;
		case 4:	//stop
				direction=0x00;
				flag=1;
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
	DDRC=0x00;						//SET 1 for OUTPUT PORT
	DDRB = 0xC7;					//SET 0 FOR INPUT PORT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	sbi(PORTC,4);	
	TCCR0 = TMC8_CK64;       		// use CLK/64 prescale value
    TCNT0  = TIMER_0_CNT;        			// reset TCNT0
    TIMSK  = _BV(TOIE0);         	// enable TCNT0 overflow 
    
    sei();                       	// enable interrupts 
 	
	for(;;)
	{
		
		
	}
	return(0);
}