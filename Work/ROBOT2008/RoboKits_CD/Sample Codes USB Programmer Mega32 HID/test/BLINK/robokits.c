//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR BLINKING LED'S
//			WRITTEN FOR ROBOGRID


/*-------------------------------------------------------------------          
 Description:
 Blinks all Four leds at 1hz rate.
 LED's are connected to PORTA.4,PORTA.5,PORTA.6 and PORTA.7 though jumpers.
 Place jumpers to use this pins as led pins or remove to disconnect them from ckt.

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
	DDRA=0xF0;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PA.4, PA.5, PA.6 AND PA.7 ARE OUTPUT
									//ALL OTHERS ARE INPUT
	while(1)
	{
		PORTA=0X00;					//ALL LED'S OFF
		_delay_ms(250);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
		_delay_ms(250);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
		_delay_ms(250);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
		_delay_ms(250);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
		sbi(PORTA,4);					//ALL LED'S ON
		_delay_ms(250);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
		_delay_ms(250);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
		_delay_ms(250);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
		_delay_ms(250);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
	}
	return(0);
}

