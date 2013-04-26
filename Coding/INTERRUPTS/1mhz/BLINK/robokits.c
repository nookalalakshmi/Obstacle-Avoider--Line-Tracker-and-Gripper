//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR BLINKING LED'S
//			WRITTEN FOR PRODUCT ID 19

/*-------------------------------------------------------------------          
 Description:
 Blinks all three leds at 1hz rate.

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
-----------------MAIN PROGRAM-------------------------------------/
-----------------------------------------------------------------*/
int main(void)
{
	DDRB=0x00;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTB.0 IS OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUTO USE
	
	DDRD=0xc0;						//SET DATA DIRECTION REGISTER
								
									//CHANGE ACCORDING T	//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTD.7 AND PORTD.6 ARE OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE	

	while(1)						//INFINITE LOOP
	{
		
		sbi(PORTD,6);
		cbi(PORTD,6);
		//sbi(PORTD,6);
		//cbi(PORTD,6);
	}
	return(0);
}

