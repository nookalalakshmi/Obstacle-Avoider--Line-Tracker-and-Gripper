//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR TAKING INPUT FROM A SWITCH
//			WRITTEN FOR ROBOGRID

/*-------------------------------------------------------------------          
 Description:
 This example shows how to take input from a switch input.

 Note:
 If INT2 is pressed led1 is on.
 
 If SW1 is pressed led2 is on.
 
 If INT0 is pressed led3 is on.
 
 If INT1 is pressed led4 is on.
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include<avr/io.h>					//HEADER FILE FOR AVR INPUT OUTPUT
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI

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
									
	DDRB=0XFB;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PB.2 IS  INPUT
									//ALL OTHERS ARE OUTPUT
	
	DDRD=0XF1;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PD.1, PD.2 AND PD.3 ARE INPUT
									//ALL OTHERS ARE OUTPUT

	sbi(PORTB,2);					//ENABLE PULL UP FOR SWITCH INT2
	sbi(PORTD,1);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1
	
	while(1)						//START INFINITE LOOP TO SCAN INPUT FROM PORT
	{
		if (bit_is_clear(PINB,2))	//IF INT2 IS PRESSED
			sbi(PORTA,4);			//LED1 ON
		else						//ELSE
			cbi(PORTA,4);			//LED1 OFF

		if (bit_is_clear(PIND,1))	//IF SW1 IS PRESSED
			sbi(PORTA,5);			//LED2 ON
		else						//ELSE
			cbi(PORTA,5);			//LED2 OFF

		if (bit_is_clear(PIND,2))	//IF INT0 IS PRESSED
			sbi(PORTA,6);			//LED3 ON
		else						//ELSE
			cbi(PORTA,6);			//LED3 OFF
			
		if (bit_is_clear(PIND,3))	//IF INT1 IS PRESSED
			sbi(PORTA,7);			//LED4 ON
		else						//ELSE
			cbi(PORTA,7);			//LED4 OFF
	}
	return(0);
}



