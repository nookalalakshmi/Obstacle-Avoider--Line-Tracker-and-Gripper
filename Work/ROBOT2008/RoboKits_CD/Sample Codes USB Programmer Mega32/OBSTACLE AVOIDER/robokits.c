//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR Obstacle Avoider(For NeoBot)
//			WRITTEN FOR ROBOGRID

/*-------------------------------------------------------------------          
 Description:
 This example shows how to use NeoBot as Obstacle Avoider roobt.
 
 Sensor1(Left) Connected to pin 40(PA0).
 Sensor2(Right) Connected to pin 15(PD1).

 Note:
 Put jumper of IR sensor in pin 1-2(INT) configuration
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include<avr/io.h>					//HEADER FILE FOR AVR INPUT OUTPUT
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY
#include <avr/interrupt.h>

#include "lcd.h"

#define OC1A_PIN PD5              // OC1A pin
#define OC1B_PIN PD6              // OC1B pin
#define OC1_DDR DDRD             // OC1 DDR

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{

    OC1_DDR |= _BV(OC1A_PIN) + _BV(OC1B_PIN);    			// set OC1A and OC1B pin as output, required for output toggling 

    TCCR1A =  _BV(WGM10) | _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0);    	// enable 8 bit PWM, select inverted PWM
		
    // timer1 running on 1/8 MCU clock with clear timer/counter1 on Compare Match
    // PWM frequency will be MCU clock / 8 / 512, e.g. with 1Mhz Crystal 244 Hz.
    TCCR1B = _BV(CS11) | _BV(WGM12);
	
    OCR1AL = 0;            			//FUll Speed Left motor
	OCR1BL = 0;						//FUll Speed Right motor
	
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
	
	DDRC=0XFF;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ALL OTHERS ARE OUTPUT
	
	DDRD=0XF1;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PD.1, PD.2 AND PD.3 ARE INPUT
									//ALL OTHERS ARE OUTPUT
									
    lcd_init(LCD_DISP_ON);				/* initialize display, cursor off */
	lcd_clrscr();						/* clear display and home cursor */        
	lcd_puts("ROBOKITS NEOBOT\n");		/* put string to display (line 1) with linefeed */		
	lcd_puts("Obstacle Avoider");		/* cursor is now on second line, write second line */										

	sbi(PORTB,2);					//ENABLE PULL UP FOR SWITCH INT2
	sbi(PORTD,1);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1


	while(1)						//START INFINITE LOOP TO SCAN INPUT FROM PORT
	{
		if(bit_is_clear(PINA,0) && bit_is_clear(PIND,1))	//IF Both Sensors senses obstacle
		{
			sbi(PORTA,4);
			cbi(PORTA,5);
			cbi(PORTA,6);
			PORTC=0X05;							//Go Back
			_delay_ms(255);
			_delay_ms(255);
			PORTC=0x09;							//Turn Left
			_delay_ms(255);
		}
		else if(bit_is_clear(PINA,0))	//IF Sensor1(Left) senses obstacle
		{
			cbi(PORTA,4);
			sbi(PORTA,5);
			cbi(PORTA,6);
			PORTC=0X06;							//Turn Right
			_delay_ms(100);
		}
		else if(bit_is_clear(PIND,1))			//IF Sensor2(Right) senses obstacle
		{
			cbi(PORTA,4);
			cbi(PORTA,5);
			sbi(PORTA,6);
			PORTC=0X09;							//Turn Left
			_delay_ms(100);
		}
		else
		{
			PORTC=0X0A;							//Both motors Forward
			cbi(PORTA,4);
			cbi(PORTA,5);
			cbi(PORTA,6);
		}
	}
	return(0);
}



