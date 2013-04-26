
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

/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/

void path_follower(void)
{
	
	if((bit_is_clear(PINC,2)))
	{
		sbi(PORTD,0);
		cbi(PORTD,1);	//move left
		//robotmove('L');
		sbi(PORTD,7);
		cbi(PORTB,0);
	}
	if((bit_is_clear(PINB,1)))
	{
		sbi(PORTD,1);
		cbi(PORTD,0);	//move right
		//robotmove('R');
		sbi(PORTB,0);
		cbi(PORTD,7);
	}
	if((bit_is_clear(PINC,3)) || (bit_is_clear(PINC,4)) || (bit_is_clear(PINC,5)))
	{
		sbi(PORTD,0);
		sbi(PORTD,1);	//move forward
		//robotmove('F');
		sbi(PORTD,7);
		sbi(PORTB,0);
	}
	if((!bit_is_clear(PINC,2)) && (!bit_is_clear(PINC,3)) && (!bit_is_clear(PINC,4)) && (!bit_is_clear(PINC,5)) && (!bit_is_clear(PINB,1)))
	{
		cbi(PORTD,0);
		cbi(PORTD,1);	//stop
		//robotmove('S');
		cbi(PORTD,7);
		cbi(PORTB,0);
	}
	/*if((bit_is_clear(PINC,1)))
	{
		cbi(PORTD,0);
		cbi(PORTD,1);	//stop
		cbi(PORTD,7);
		cbi(PORTB,0);
		_delay_ms(1000);
		
		sbi(PORTD,0);
		cbi(PORTD,1);	//move left
		//robotmove('L');
		sbi(PORTD,7);
		cbi(PORTB,0);
	}
	if((bit_is_clear(PINB,2)))
	{
		cbi(PORTD,0);
		cbi(PORTD,1);	//stop
		cbi(PORTD,7);
		cbi(PORTB,0);
		_delay_ms(1000);
		
		sbi(PORTD,1);
		cbi(PORTD,0);	//move right
		//robotmove('R');
		sbi(PORTB,0);
		cbi(PORTD,7);
	}*/
	
}
/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/
int main(void)
{
	DDRD=0x8F;						//SET DATA DIRECTION REGISTER
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
	DDRB = 0x01;

	for(;;)
	{
		path_follower();
	}
	return(0);
}