//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR ADC
//			WRITTEN FOR PRODUCT ID 19 

/*-------------------------------------------------------------------          
 Description:
 This example shows 10bit adc values of channel ADC0 on uart constantly.

 Note:
 Change F_CPU if any other clock frequency is used.
 
 Connect PC-MCU serial link form avr board to pc serial port.
 
 Open Hyperterminal or other compatible program for receiving 
 input from serial port.
 
 Set baudrate accordingly.
 
 Connect variable resistor constant resistor leads to vcc and ground
 and variable pin in ADC. Use the connector near led2. 
 
 You can also connect any other device you like.
 
 Make sure you connect adc device on ADC0.
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include <avr/io.h>
#include <inttypes.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI

#include "uart.h"					//Include coustom library built for UART


/* define CPU frequency in Mhz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 1000000UL 			//Change CPU frequency in makefile or delete from there and change from here
#endif

/* 4800 baud */
#define UART_BAUD_RATE      4800    //Change baud rate here


/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main (void) 
{
	int x = 0;  
	char buffer[5];
	ADCSRA = _BV(ADEN) | _BV(ADPS2);		// Activate ADC with Prescaler 16 --> 1Mhz/16 = 62.5kHz
	
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
    uart_puts_P("\r\n\nSample code made by Robokits India for product id 19. ");
	uart_puts_P("\r\n\nCheapest Robotics Kits in India. ");
	uart_puts_P("\r\n\nVisit Us at www.robokits.org. ");
	uart_puts_P("\r\n\nSample code for ADC.\r\n\n");  
  
	for (;;) 
	{  		
		ADMUX = 0;						// Select pin ADC0 using MUX		
		ADCSRA |= _BV(ADSC);			// Start conversion 		
		while (ADCSRA & _BV(ADSC) ) 	// wait until converstion completed
		{
		
		}
		x = ADCW;  						// get converted value
    
		itoa( x, buffer, 10);   		// convert interger into string (decimal format)    
		uart_puts(buffer);       		// and transmit string to UART
		uart_puts_P("  ");  	  	
	}
	return(0);
}

