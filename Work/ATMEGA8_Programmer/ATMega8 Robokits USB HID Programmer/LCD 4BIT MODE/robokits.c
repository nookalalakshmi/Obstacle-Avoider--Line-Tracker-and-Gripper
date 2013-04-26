//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR LCD 4BIT MODE
//			WRITTEN FOR PRODUCT ID 19 

/*-------------------------------------------------------------------          
 Description:
 This example runs lcd in 4bit mode using only 7 I\O pins of AVR.

 Note:
 
 Change following parameters as per requirement in lcd.h file.

 Default values are as below.
 
 #define XTAL 1000000
 
 #define LCD_CONTROLLER_KS0073 0  
 
 #define LCD_PORT         PORTC        port for the LCD lines   
 #define LCD_DATA0_PORT   LCD_PORT     port for 4bit data bit 0 
 #define LCD_DATA1_PORT   LCD_PORT     port for 4bit data bit 1
 #define LCD_DATA2_PORT   LCD_PORT     port for 4bit data bit 2 
 #define LCD_DATA3_PORT   LCD_PORT     port for 4bit data bit 3 
 #define LCD_DATA0_PIN    3            pin for 4bit data bit 0  
 #define LCD_DATA1_PIN    2            pin for 4bit data bit 1  
 #define LCD_DATA2_PIN    1            pin for 4bit data bit 2 
 #define LCD_DATA3_PIN    0            pin for 4bit data bit 3 
 #define LCD_RS_PORT      LCD_PORT     port for RS line         
 #define LCD_RS_PIN       5            pin  for RS line         
 #define LCD_RW_PORT      PORTB        port for RW line         
 #define LCD_RW_PIN       1            pin  for RW line         
 #define LCD_E_PORT       LCD_PORT     port for Enable line     
 #define LCD_E_PIN        4            pin  for Enable line     

 Connect 7 I\O pins as shown before with corresponding lcd pins.
 
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
#include <compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY

#include "lcd.h"

/*----------------------------------------------------------------
-----------------CONSTANTS----------------------------------------
-----------------------------------------------------------------*/

static const PROGMEM unsigned char copyRightChar[] =
{
	0x07, 0x08, 0x13, 0x14, 0x14, 0x13, 0x08, 0x07,
	0x00, 0x10, 0x08, 0x08, 0x08, 0x08, 0x10, 0x00
};


/*----------------------------------------------------------------
-----------------FUNCTION PROTOTYPES------------------------------
-----------------------------------------------------------------*/
void wait_until_key_pressed(void);

/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
void wait_until_key_pressed(void)
{
    unsigned char temp1, temp2;
    unsigned int i;
    
    do {
        temp1 = PIND;                  		// read input
        for(i=0;i<65535;i++);
        temp2 = PIND;                  		// read input
        temp1 = (temp1 & temp2);       		// debounce input
    } while ( temp1 & _BV(PIND2) );
    
    loop_until_bit_is_set(PIND,PIND2);     	/* wait until key is released */
}

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
    char buffer[7];
    int  num=134;
    unsigned char i;
	
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
    
    lcd_init(LCD_DISP_ON);					/* initialize display, cursor off */

    for (;;)								/* loop forever */ 
	{                           
        lcd_clrscr();						/* clear display and home cursor */        
        lcd_puts("ROBOKITS INDIA\n");		/* put string to display (line 1) with linefeed */		
        lcd_puts("    ROBOKITS.ORG");		/* cursor is now on second line, write second line */		
		lcd_gotoxy(0,1);  					/* move cursor to position 0 on line 2 */        
        lcd_puts("WWW.");					/* write single char to display */                
        wait_until_key_pressed();			/* wait until push button PD2 (INT0) is pressed */
		
		
        lcd_command(LCD_DISP_ON_CURSOR);	/* turn on cursor */
        lcd_clrscr();     					/* clear display home cursor */		
        lcd_puts( "CurOn");
		wait_until_key_pressed();			/* wait until push button PD2 (INT0) is pressed */
        
        
		lcd_clrscr();     					/* clear display home cursor */	
		lcd_puts_P( "Line 1 longer than 14 characters\n" );	/* put string from program memory to display */
        lcd_puts_P( "Shift both line1 and line2 left" );		
		for(i=0;i<15;i++)
		{
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);		
			lcd_command(LCD_MOVE_DISP_LEFT);	/* move BOTH lines one position to the left */
		}           
        wait_until_key_pressed();				/* wait until push button PD2 (INT0) is pressed */
        
        
		lcd_command(LCD_DISP_ON);				/* turn off cursor */
        lcd_clrscr();   						/* clear display home cursor */
        itoa( num , buffer, 10);		       	/* convert interger into string */
        lcd_puts(buffer);						/* put converted string to display */
        wait_until_key_pressed();				/* wait until push button PD2 (INT0) is pressed */
		
        
		lcd_clrscr();   						/* clear display home cursor */       
		lcd_puts("Copyright    ");
		lcd_gotoxy(10,0);
		lcd_putc(':');
		/* load two userdefined characters from program memoryinto LCD controller CG RAM location 0 and 1*/
		lcd_command(_BV(LCD_CGRAM)); 	 		/* set CG RAM start address 0 */
		for(i=0; i<16; i++)
		{
			lcd_data(pgm_read_byte_near(&copyRightChar[i]));
		}
		/* move cursor to position 0 on line 2 */
		/* Note: this switched back to DD RAM addresses */
		lcd_gotoxy(0,1);
		lcd_putc(0);							/* display user defined (c), built using two user defined chars */
		lcd_putc(1);     
		wait_until_key_pressed();				/* wait until push button PD2 (INT0) is pressed */
    }
}
