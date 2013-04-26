//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR TAKING INPUT FROM A SWITCH
//			WRITTEN FOR PRODUCT ID 19

/*-------------------------------------------------------------------          
 Description:
 This example shows how to take input from a switch input.

 Note:
 If sw1 is pressed led2 is on.
 
 If sw2 is pressed led3 is on.
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
	
	sbi(PORTB,0);					//LED1 ON (INDICATION FOR READY TO USE)
	
	sbi(PORTD,2);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,3);					//ENABLE PULL UP FOR SW2
	
	while(1)						//START INFINITE LOOP TO SCAN INPUT FROM PORT
	{
		if (bit_is_clear(PIND, 2))	//IF SW1 IS PRESSED
			sbi(PORTD,7);			//LED2 ON
		else						//ELSE
			cbi(PORTD,7);			//LED2 OFF

		if (bit_is_clear(PIND, 3))	//IF SW2 IS PRESSED
			sbi(PORTD,6);			//LED3 ON
		else						//ELSE
			cbi(PORTD,6);			//LED3 OFF
	}
	return(0);
}



