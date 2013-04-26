//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR WRITING AND READING EEPROM
//			WRITTEN FOR ROBOGRID

/*-------------------------------------------------------------------          
 Description:
 Writes eeprom with 0 to 255 at address 0x00 to 0xff and reads from
 the same and writes it to uart of avr. 

 Note:
 Change F_CPU if any other clock frequency is used.
 
 Connect PC-MCU serial link form avr board to pc serial port.
 
 Open Hyperterminal or other compatible program for receiving 
 input from serial port.
 
 Set baudrate accordingly.
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include <avr/io.h>
#include <inttypes.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI

#include "uart.h" 

/* define CPU frequency in Mhz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

/* 4800 baud */
#define UART_BAUD_RATE      4800      



int main(void)
{
    char buffer[7];
    
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
	
    /*
     *  Initialize UART library, pass baudrate and AVR cpu clock
     *  with the macro 
     *  UART_BAUD_SELECT() (normal speed mode )
     *  or 
     *  UART_BAUD_SELECT_DOUBLE_SPEED() ( double speed mode)
     */
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
    
    /*
     * now enable interrupt, since UART library is interrupt controlled
     */
    sei();
    
    /*
     * Transmit string from program memory to UART
     */
    uart_puts_P("\r\n\nSample code made by Robokits India for ROBOGRID. ");
	uart_puts_P("\r\n\nVisit Us at www.robokits.org. ");
	uart_puts_P("\r\n\nSample code for eeprom writing and reading.");
	
	uint8_t num;
	uint8_t *ead;

	num=0;
	ead = 0;

	do
	{                   
		eeprom_write_byte(ead++, num);  
		num++; 		
	} while (num != 255);
		
	uart_puts_P("\r\n EEPROM written. Now read content from EEPROM\n\r");  		
		
	num = 0;
		
	for (ead = 0; num != 255; ead++)
	{
		num = eeprom_read_byte(ead);     
		itoa(num, buffer, 10);   // convert interger into string (decimal format)    
		uart_puts(buffer);        // and transmit string to UART
		uart_puts_P("  ");  	  
	}
	return(0);
}


