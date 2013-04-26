//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR DRIVING STEPPER
//			WRITTEN FOR PRODUCT ID 19

/*-------------------------------------------------------------------          
 Description:
 This example runs two stepper motors if used with motor driver from 
 robokits india.

 Note: 
 First stepper is connected with portd.0,d.1,d.2,d.3 pins. 
 
 Second stepper is connected with portc.0,c.1,c.2,c.3 pins.
 
 Press sw1 to drive both motors forward.
 
 Press sw2 to drive both motors reverse.
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
	
	DDRD=0xCF;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PORTD.7 AND PORTD.6 ARE CONFIGURED OUTPUT FOR LED
									//PORTD.0, D.1, D.2, D.3 ARE OUTPUTS FOR STEPPER1
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	
	DDRC=0x0F;						//PORTC.0, C.1, C.2, C.3 ARE OUTPUTS FOR STEPPER2
	
	sbi(PORTB,0);					//LED1 ON (INDICATION FOR READY TO USE)
	
	sbi(PORTD,2);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,3);					//ENABLE PULL UP FOR SW2
	
	while(1)
	{
		mainloop:
		if (bit_is_clear(PIND, 2))			//IF SW1 IS PRESSED STEPPER1&2 FORWARD
		{
			while(1)
			{
				PORTD=0x01;						//COIL1 +
				PORTC=0x01;						//COIL1 +
				_delay_ms(2);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 262.14MS / F_CPU IN MHZ
				PORTD=0x02;						//COIL2 +
				PORTC=0x02;						//COIL2 +
				_delay_ms(2);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 262.14MS / F_CPU IN MHZ
				PORTD=0x04;						//COIL1 -
				PORTC=0x04;						//COIL1 -
				_delay_ms(2);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 262.14MS / F_CPU IN MHZ
				PORTD=0x08;						//COIL2 -
				PORTC=0x08;						//COIL2 -				
				_delay_ms(2);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 262.14MS / F_CPU IN MHZ
				if (bit_is_set(PIND, 2))		//CHECK WHETHER THE SWITCH IS STILL PRESSED
				{
					PORTD=0x00;					//CLEAR PORTD
					PORTC=0x00;					//CLEAR PORTC
					goto mainloop;				//IF NOT GOTO MAINLOOP
				}
			}
		}
		else if (bit_is_clear(PIND, 3))		//IF SW2 IS PRESSED STEPPER1&2 BACKWARD
		{
			while(1)
			{
				PORTD=0x08;						//COIL1 +
				PORTC=0x08;						//COIL1 +
				_delay_ms(2);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 262.14MS / F_CPU IN MHZ
				PORTD=0x04;						//COIL2 -
				PORTC=0x04;						//COIL2 -				
				_delay_ms(2);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 262.14MS / F_CPU IN MHZ
				PORTD=0x02;						//COIL1 -
				PORTC=0x02;						//COIL1 -
				_delay_ms(2);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 262.14MS / F_CPU IN MHZ
				PORTD=0x01;						//COIL2 +
				PORTC=0x01;						//COIL2 +
				_delay_ms(2);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 262.14MS / F_CPU IN MHZ
				if (bit_is_set(PIND, 3))
				{
					PORTD=0x00;					//CLEAR PORTD			
					PORTC=0x00;					//CLEAR PORTC
					goto mainloop;				//IF NOT GOTO MAINLOOP
				}
			}		
		}
		else
		{
			PORTC=0x00;
			PORTD=0X00;
		}
	}
	return(0);
}