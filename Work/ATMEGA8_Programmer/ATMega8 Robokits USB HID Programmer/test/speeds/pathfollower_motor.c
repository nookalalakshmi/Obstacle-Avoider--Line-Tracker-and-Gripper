
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

/*----------------------------------------------------------------
-----------------Constants-------------------------------------
-----------------------------------------------------------------*/
char count=0;
int mode=0;
/*----------------------------------------------------------------
-----------------Timer variables-------------------------------------
-----------------------------------------------------------------*/


#define TIMER_0_CNT     0x0B  // 250 ms sec, use AVRcalc to calculate these values
                                // ((TCNT0=0x63))
								// DECIMAL VALUE = 11
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-11 = 244 COUNTS
#define TMC8_CK1024	(_BV(CS02)+_BV(CS00))	// 8 BIT TIMER0 AT 1024 PRESCALAR
												// GIVES 1024*244 = 250000 CYCLES
												// AT 1MHZ FREQUENCY DELAY OF 250 mSECONDS
/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
SIGNAL(SIG_OVERFLOW0)            	// signal handler for tcnt1 overflow interrupt
{
	
	count++;
	if(count==40)
	{	
		mode++;
		if(bit_is_clear(PINB,2))
		{
			sbi(PORTB,2);
		}
		else
		{
			cbi(PORTB,2);
		}
		if(mode==5)
		{
			mode=1;
		}
		count=0;
	}
	TCNT0  = TIMER_0_CNT;        			// reset TCNT0
	
}

void motormove(char motor,char state)
{
	
	int n1,n2;
	if(motor=='1')
	{
		n1=7;
		n2=6;
	}
	if(motor=='2')
	{
		n1=0;
		n2=1;
	}
	
	switch (state)
	{
	 case 'F':
			sbi(PORTB,n1);
			cbi(PORTB,n2);
			break;

	case 'B':
			sbi(PORTB,n2);
			cbi(PORTB,n1);
			break;

	
	case 'S':
			cbi(PORTB,n2);
			cbi(PORTB,n1);
			break;

	case 's':
			cbi(PORTB,n1);
			cbi(PORTB,n2);
			break;
	}	
}

void robotmove(char mode)
{

	switch(mode)
	{
		case 'F':
		 motormove('1','F');
		 motormove('2','F');
		break;
		
		case 'B':
		 motormove('1','B');
		 motormove('2','B');
		break;
		
		case 'R':
		 motormove('1','B');
		 motormove('2','F');
		break;
		
		case 'L':
		 motormove('1','F');
		 motormove('2','B');
		break;
		
		case 'S':
		 motormove('1','s');
		 motormove('2','s');
		break;
	}
}


/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/
void func(int m)
{
	mode=m;
	char i=0;
	switch(mode)
	{
		case 1://full speed
		
			while(1)
			{
				robotmove('F');
				if(mode!=1)
					return;
			}
		
		case 2:
		
			while(1)
			{
				for(i=0;i<200;i++)
				{
					robotmove('F');
				}
				for(i=i;i<255;i++)
				{
					robotmove('S');
				}
				if(mode!=2)
					return;
			}
		
		case 3:
		
			while(1)
			{
				for(i=0;i<145;i++)
				{
					robotmove('F');
				}
				for(i=i;i<255;i++)
				{
					robotmove('S');
				}
				if(mode!=3)
					return;
			}
		
		case 4:
		
			while(1)
			{
				for(i=0;i<105;i++)
				{
					robotmove('F');
				}
				for(i=i;i<255;i++)
				{
					robotmove('S');
				}
				if(mode!=4)
					return;
			}

	}
}
int main(void)
{
	mode=1;
	DDRD=0x0F;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTB.0 IS OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	DDRC=0x18;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTD.7 AND PORTD.6 ARE OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	DDRB = 0xC7;
	cbi(PORTC,3);
	cbi(PORTC,4);
	TCCR0 = TMC8_CK1024;       		// use CLK/1024 prescale value
    TCNT0  = TIMER_0_CNT;        			// reset TCNT1
    
    TIMSK  = _BV(TOIE0);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts 

	
	for(;;)
	{
	func(mode);
		
	}
	return(0);
}