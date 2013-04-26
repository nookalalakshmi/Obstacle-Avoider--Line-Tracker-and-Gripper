//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR DRIVING STEPPER
//			WRITTEN FOR ROBOGRID

/*-------------------------------------------------------------------          
 Description:
 This example runs two stepper motors on robogrid.

 Note: 
 
 Jtag should be disabled to use portc normally. 
 Jtag is disabled on the board shipped to you by robokits.
 
 First stepper is connected with portc.4,c.5,c.6,c.7 pins. 
 
 Second stepper is connected with portc.0,c.1,c.2,c.3 pins.
 
 Press INT2 to drive stepper1 forward.
 
 Press sw1 to drive stepper1 reverse.
 
 Press INT0 to drive stepper2 forward.
 
 Press INT1 to drive stepper2 reverse.
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

	sbi(PORTA,4);					//LED1 ON (INDICATION FOR READY TO USE)
	
	
	sbi(PORTB,2);					//ENABLE PULL UP FOR SWITCH INT2
	sbi(PORTD,1);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1

	while(1)
	{
		mainloop:
		if (bit_is_clear(PINB,2))			//IF SW1 IS PRESSED STEPPER1 FORWARD
		{
			while(1)
			{
				PORTC=0x10;						//COIL1 +
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x20;						//COIL2 +
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x40;						//COIL1 -
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x80;						//COIL2 -
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				if (bit_is_set(PINB,2))		//CHECK WHETHER THE SWITCH IS STILL PRESSED
				{
					PORTC=0x00;					//CLEAR PORTC				
					goto mainloop;				//IF NOT GOTO MAINLOOP
				}
			}
		}
		else if (bit_is_clear(PIND,1))		//IF SW2 IS PRESSED STEPPER1 BACKWARD
		{
			while(1)
			{
				PORTC=0x80;						//COIL1 +
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x40;						//COIL2 -
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x20;						//COIL1 -
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x10;						//COIL2 +
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				if (bit_is_set(PIND,1))
				{
					PORTC=0x00;					//CLEAR PORTC			
					goto mainloop;				//IF NOT GOTO MAINLOOP
				}
			}		
		}
		else if (bit_is_clear(PIND,2))		//IF SW3 IS PRESSED STEPPER2 FORWARD
		{
			while(1)
			{
				PORTC=0x01;						//COIL1 +
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x02;						//COIL2 +
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x04;						//COIL1 -
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x08;						//COIL2 -
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				if (bit_is_set(PIND,2))		//CHECK WHETHER THE SWITCH IS STILL PRESSED
				{
					PORTC=0x00;					//CLEAR PORTC				
					goto mainloop;				//IF NOT GOTO MAINLOOP
				}
			}
		}
		else if (bit_is_clear(PIND,3))			//IF SW4 IS PRESSED STEPPER2 BACKWARD
		{
			while(1)
			{
				PORTC=0x08;						//COIL1 +
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x04;						//COIL2 -
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x02;						//COIL1 -
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				PORTC=0x01;						//COIL2 +
				_delay_ms(5);					//DELAY IN MILISECOND ARGUMENT SHOULD NOT BE MORE THAN 255
				if (bit_is_set(PIND,3))
				{
					PORTC=0x00;					//CLEAR PORTC			
					goto mainloop;				//IF NOT GOTO MAINLOOP
				}
			}		
		}
		else
			PORTC=0x00;
	}
	return(0);
}
