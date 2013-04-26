//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR Testing Multipurpouse IR Sensors
//			WRITTEN FOR ROBOGRID

/*-------------------------------------------------------------------          
 Description:
 This example shows how to take input from a switch input.
 
 Sensor1 Connected to pin 40(PA0).
 Sensor2 Connected to pin 15(PD1).

 Note:
 Put jumper of IR sensor in pin 1-2(INT) configuration
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include<avr/io.h>					//HEADER FILE FOR AVR INPUT OUTPUT
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI

#include "lcd.h"

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
									
    lcd_init(LCD_DISP_ON);				/* initialize display, cursor off */
	lcd_clrscr();						/* clear display and home cursor */        
	lcd_puts("ROBOKITS NEOBOT\n");		/* put string to display (line 1) with linefeed */		
	lcd_puts("SENSOR TEST");		/* cursor is now on second line, write second line */										

	sbi(PORTB,2);					//ENABLE PULL UP FOR SWITCH INT2
	sbi(PORTD,1);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1
	
	while(1)						//START INFINITE LOOP TO SCAN INPUT FROM PORT
	{
		if (bit_is_clear(PINA,0))	//IF Sensor1 senses obstacle
			sbi(PORTA,5);			//LED2 ON
		else						//ELSE
			cbi(PORTA,5);			//LED2 OFF

		if (bit_is_clear(PIND,1))	//IF Sensor2 senses obstacle
			sbi(PORTA,6);			//LED3 ON
		else						//ELSE
			cbi(PORTA,6);			//LED3 OFF
	}
	return(0);
}



