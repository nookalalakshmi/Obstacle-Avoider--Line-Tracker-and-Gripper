
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
#define TIMER_0_CNT     0xC0  // 500 us sec, use AVRcalc to calculate these values
                                // ((TCNT0=0x63))
								// DECIMAL VALUE = 192
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-192 = 63 COUNTS
#define TMC8_CK8	(_BV(CS01)+_BV(CS00))	// 8 BIT TIMER0 AT 64 PRESCALAR
											// GIVES 64*63 = 4000 CYCLES		//8mhz 1 msec delay
											// AT 1MHZ FREQUENCY DELAY OF 90.112 mSECONDS

static volatile int detectline=0;
char timercount=0;
static volatile int stopcount=0;
int flag=0;
int backflag=0;
char turn=0;
char nopathflag=0;
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
	
	if(flag==0)
	{	//PORTB=0x00;
		if((!bit_is_clear(PINC,1) && !bit_is_clear(PINC,2)))
			detectline=1;	//forward
		else if((bit_is_clear(PINC,1) && !bit_is_clear(PINC,2)))
			detectline=2;	//right
		else if((!bit_is_clear(PINC,1) && bit_is_clear(PINC,2)))
			detectline=3;	//left
		else if((bit_is_clear(PINC,1) && bit_is_clear(PINC,2)))
			{
				detectline=4;
				
			}
			
		path_follower_motor(detectline);
		
	}
	if(flag==1 && backflag==0)
	{
		stopcount=0;
		
		while(bit_is_clear(PINC,1) && bit_is_clear(PINC,2)) 
		{
			stopcount++;
			PORTB=0x42;
			if(stopcount>200)
			{
				
				sbi(PORTB,2);
				flag=1;
				PORTB=0x00;
				break;
			}
			else
			{
				cbi(PORTB,2);
				flag=0;
				continue;
			}
		}
		stopcount=0;
		cbi(PORTB,2);
		if(!bit_is_clear(PINC,1) && !bit_is_clear(PINC,2))
		{
			backflag=1;
		}
	}
	if(backflag==1)
	{
		if(nopathflag==0)
		{
			PORTB=0x81;
			_delay_ms(5000);
			PORTB=0x00;
			
			while(turn<20)
			{
				
				TCNT0=0;
				while(TCNT0<255)
				{
					PORTB=0x82;		//left from center
					sbi(PORTB,2);
					/*if(!bit_is_clear(PINC,1))
					{
						backflag=0;
						nopathflag=0;
						flag=0;
						break;
					}
					else
					{
						nopathflag=1;
					}*/
				
				}
				if(flag==0 && nopathflag==0 && backflag==0)
				{
					break;
				}
				turn++;
				
				
			}
			turn=0;
			nopathflag=1;
			/*while(turn==16)
			{
				TCNT0=0;
				while(TCNT0<255 && bit_is_clear(PINC,2))
				{
					PORTB=0x41;
					
				
				}
				turn++;
				PORTB=0x00;
				if(!bit_is_clear(PINC,2))
				{
					backflag=0;
					nopathflag=0;
				}
				else
				{
					nopathflag=1;
				}
			}*/
			turn=0;
		}
		
		
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
	
	return;
}



void path_follower_motor(int detectline)
{
	char direction;
	switch(detectline)
	{
		case 1:	//forward
				direction=0x81;
				speed(direction,200);
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