
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
-----------------Timer variables-------------------------------------
-----------------------------------------------------------------*/
#define TIMER_0_CNT     0x82  // 1 ms sec, use AVRcalc to calculate these values
                                // ((TCNT0=0x63))
								// DECIMAL VALUE = 130
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-130 = 125 COUNTS
#define TMC8_CK8	(_BV(CS01))	// 8 BIT TIMER0 AT 8 PRESCALAR
												// GIVES 8*125 = 1000 CYCLES
												// AT 1MHZ FREQUENCY DELAY OF 90.112 mSECONDS
/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

void path_follower_motor(void);

SIGNAL(SIG_OVERFLOW0)            	// signal handler for tcnt1 overflow interrupt
{
	TCNT0  = TIMER_0_CNT;	
	path_follower_motor();

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

void path_follower_motor(void)
{
	
	if((bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)))
	{
		do
		{
			sbi(PORTB,6);
			sbi(PORTB,0);
			cbi(PORTB,7);
			cbi(PORTB,1);
			//robotmove('R');
		}while((!bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)));
	
	}
	if((bit_is_clear(PINC,2)) && (!bit_is_clear(PINC,1)))
	{
		do
		{
			sbi(PORTB,7);
			sbi(PORTB,1);
			cbi(PORTB,6);
			cbi(PORTB,0);
			//robotmove('L');
		}while((!bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)));
	
	}
	if((!bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)))
	{
		do
		{
			sbi(PORTB,7);
			sbi(PORTB,0);
			cbi(PORTB,6);
			cbi(PORTB,1);
			//robotmove('F');
		}while((!bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)));
	
	}
	if((bit_is_clear(PINC,1)) && (bit_is_clear(PINC,2)))
	{
			cbi(PORTB,7);
			cbi(PORTB,0);
			cbi(PORTB,6);
			cbi(PORTB,1);
		//robotmove('S');
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
 
	robotmove('S');

	for(;;)
	{
				
	}
	return(0);
}