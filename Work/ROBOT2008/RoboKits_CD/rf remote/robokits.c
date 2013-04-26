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
	DDRD=0X00;
	DDRA=0XFF;
	DDRC=0XFF;
	
	for(;1;)
	{
		if(bit_is_set(PIND,4))
		{
			sbi(PORTC,0);
			cbi(PORTC,1);
			sbi(PORTC,2);
			cbi(PORTC,3);
			sbi(PORTA,4);
		}
		else if(bit_is_set(PIND,5))
		{
			cbi(PORTC,0);
			sbi(PORTC,1);
			cbi(PORTC,2);
			sbi(PORTC,3);
			sbi(PORTA,5);
		}
		else if(bit_is_set(PIND,6))
		{
			sbi(PORTC,0);
			cbi(PORTC,1);
			cbi(PORTC,2);
			sbi(PORTC,3);
			sbi(PORTA,6);
		}
		else if(bit_is_set(PIND,7))
		{
			cbi(PORTC,0);
			sbi(PORTC,1);
			sbi(PORTC,2);
			cbi(PORTC,3);
			sbi(PORTA,7);
		}		
		else
		{
			cbi(PORTC,0);
			cbi(PORTC,1);
			cbi(PORTC,2);
			cbi(PORTC,3);
			cbi(PORTA,4);
			cbi(PORTA,5);
			cbi(PORTA,6);
			cbi(PORTA,7);			
		}
		_delay_ms(10);
	}
	return(0);
}

