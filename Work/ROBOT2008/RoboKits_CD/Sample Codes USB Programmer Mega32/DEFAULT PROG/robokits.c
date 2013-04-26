//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			DEFAULT PROGRAM SHOWING SOME OF THE CAPABILITIES OF THIS BOAD
//			WRITTEN FOR ROBOGRID

/*-------------------------------------------------------------------          
 Description:
 This example shows features of this board.

 This program is fed while shipping this product with JTAG Fuse disabled.

 Note:
 
 Parameters are as per board and defined in lcd.h file.

 Default values are as below.
 
 #define XTAL 1000000
 
 #define LCD_CONTROLLER_KS0073 0  
 
 #define LCD_PORT         PORTB       port for the LCD lines   
 #define LCD_DATA0_PORT   LCD_PORT      port for 4bit data bit 0 
 #define LCD_DATA1_PORT   LCD_PORT      port for 4bit data bit 1 
 #define LCD_DATA2_PORT   LCD_PORT      port for 4bit data bit 2 
 #define LCD_DATA3_PORT   LCD_PORT      port for 4bit data bit 3 
 #define LCD_DATA0_PIN    4             pin for 4bit data bit 0  
 #define LCD_DATA1_PIN    5             pin for 4bit data bit 1  
 #define LCD_DATA2_PIN    6             pin for 4bit data bit 2  
 #define LCD_DATA3_PIN    7             pin for 4bit data bit 3  
 #define LCD_RS_PORT      LCD_PORT      port for RS line         
 #define LCD_RS_PIN       0             pin  for RS line         
 #define LCD_RW_PORT      LCD_PORT      port for RW line         
 #define LCD_RW_PIN       1             pin  for RW line         
 #define LCD_E_PORT       LCD_PORT      port for Enable line     
 #define LCD_E_PIN        3             pin  for Enable line     
  
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

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY
#include <setjmp.h>

#include "lcd.h"

/*----------------------------------------------------------------
-----------------CONSTANTS----------------------------------------
-----------------------------------------------------------------*/

#define XTAL		  1000000L    // Crystal frequency in Hz
#define OC1A_PIN PD5              // OC1A pin
#define OC1B_PIN PD6              // OC1B pin
#define OC1_DDR DDRD             // OC1 DDR

unsigned char timer2_counter=0;

SIGNAL(SIG_OVERFLOW2)            	// signal handler for tcnt2 overflow interrupt
{
	cli();
	if(timer2_counter==3)
	{
		timer2_counter=0;
		if (bit_is_clear(PINA, 4))		//BLINK LED1 ON TIMER INTERRUPT
			sbi(PORTA,4);				//LED1 ON
		else							//ELSE
			cbi(PORTA,4);				//LED1 OFF	
		if (bit_is_clear(PINA, 5))		//BLINK LED2 ON TIMER INTERRUPT
			sbi(PORTA,5);				//LED2 ON
		else							//ELSE
			cbi(PORTA,5);				//LED2 OFF			
		if (bit_is_clear(PINA, 6))		//BLINK LED3 ON TIMER INTERRUPT
			sbi(PORTA,6);				//LED3 ON
		else							//ELSE
			cbi(PORTA,6);				//LED3 OFF	
		if (bit_is_clear(PINA, 7))		//BLINK LED4 ON TIMER INTERRUPT
			sbi(PORTA,7);				//LED4 ON
		else							//ELSE
			cbi(PORTA,7);				//LED4 OFF			
	}
	else
	{
		timer2_counter++;
	}
	
	if(bit_is_clear(PINB,2))
		TCNT2 = 200;
	else if(bit_is_clear(PIND,1))
		TCNT2 = 150;
	else if(bit_is_clear(PIND,2))
		TCNT2 = 100;
	else if(bit_is_clear(PIND,3))
		TCNT2 = 50;
	else
		TCNT2=0;
	sei();
}												


/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
	int i;
	timer2_counter=0;
	
    OC1_DDR |= _BV(OC1A_PIN) + _BV(OC1B_PIN);    			// set OC1A and OC1B pin as output, required for output toggling 

    TCCR1A =  _BV(WGM10) | _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0);    	// enable 8 bit PWM, select inverted PWM
		
    // timer1 running on 1/8 MCU clock with clear timer/counter1 on Compare Match
    // PWM frequency will be MCU clock / 8 / 512, e.g. with 1Mhz Crystal 244 Hz.
    TCCR1B = _BV(CS11) | _BV(WGM12);	
	
	TCCR2 = _BV(CS22) | _BV(CS21) | _BV(CS20); 
	sbi(TIMSK,TOIE2);
	TCNT2=0;
	sei();
	
	PORTA=0XF0;		
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
	
	DDRC=0xFF;
	
	PORTC=0x55;					//All motors forward	
	
	
    lcd_init(LCD_DISP_ON);				/* initialize display, cursor off */
	lcd_clrscr();						/* clear display and home cursor */        
	lcd_puts("ROBOKITS INDIA\n");		/* put string to display (line 1) with linefeed */		
	lcd_puts("ROBOKITS.CO.IN");		/* cursor is now on second line, write second line */		


	sbi(PORTB,2);					//ENABLE PULL UP FOR SWITCH INT2
	sbi(PORTD,1);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1

	
	for(;1;)
	{
        for (i=0; i<255; i++)								/* Decrease speed of motor */
        {
            OCR1AL = i;
			OCR1BL = i;
            _delay_ms(25);									// delay 25 ms
        }
        
        for( i=255; i>0; i--)								/* Increase speed of motor */
        {
            OCR1AL = i;            
			OCR1BL = i;
            _delay_ms(25);									// delay 25 ms
        }		
	}
}

