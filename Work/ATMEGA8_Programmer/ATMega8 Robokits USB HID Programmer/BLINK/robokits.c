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

	while(1)						//INFINITE LOOP
	{
						//ALL LED'S OFF
		cbi(PORTB,0);						//ALL LED'S ON
		cbi(PORTD,6);
		cbi(PORTD,7);

		_delay_ms(250);					//DELAY IN MILLISECONDS 
										//PARAMETER PASSED SHOULD NOT EXCEED 262.14MS / F_CPU IN MHZ
										//F_CPU IS DEFINED IN MAKEFILE
										//SO FOR 16MHZ SPEED THE MAXIMUM PARAMETER SHOULD BE 16MS
										//FOR 1MHZ IT CAN BE UPTO 262MS (250 IS USED FOR THIS EXAMPLE)
										//SEE AVR LIBC USER MANUAL FOR MORE DETAIL.
		_delay_ms(250);					//DELAY IN MILLISECONDS 									
		_delay_ms(250);					//DELAY IN MILLISECONDS 		
		_delay_ms(250);					//DELAY IN MILLISECONDS 
		sbi(PORTB,0);						//ALL LED'S ON
		sbi((PORTD,6)&&(PORTD,7));
		_delay_ms(250);					//DELAY IN MILLISECONDS 
		_delay_ms(250);					//DELAY IN MILLISECONDS 
		_delay_ms(250);					//DELAY IN MILLISECONDS 
		_delay_ms(250);					//DELAY IN MILLISECONDS 
	}
	return(0);
}

