//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR PWM
//			WRITTEN FOR PRODUCT ID 19

 
 /*-------------------------------------------------------------------          
 Description:
 This example shows how to generate average DC voltages between VCC 
 and GND using Pulse Width Modulation (PWM).

 Note:
 A LED with a series resistor should be connected from OC1A to GND.
 
 Change OC1A pin if used with any other AVR micro.
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY

#define XTAL		  1000000L    // Crystal frequency in Hz
#define OC1B_PIN PB2              // OC1A pin
#define OC1B_DDR DDRB             // OC1A DDR


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
	
    uint8_t i = 0;

    OC1B_DDR |= _BV(OC1B_PIN);    							// set OC1A pin as output, required for output toggling 

    TCCR1A =  _BV(WGM10) | _BV(COM1A1) | _BV(COM1A0);    	// enable 8 bit PWM, select inverted PWM
		
    // timer1 running on 1/8 MCU clock with clear timer/counter1 on Compare Match
    // PWM frequency will be MCU clock / 8 / 512, e.g. with 1Mhz Crystal 244 Hz.
    TCCR1B = _BV(CS11) | _BV(WGM12);
 
    for (;;)
    {   
        for (i=0; i<100; i++)								/* dimm LED on */
        {
            OCR1BL = i;
			//OCR1BH = i+1;
			sbi(PORTD, 6);
            _delay_ms(10);									// delay 10 ms
        }
		cbi(PORTD,6);
        
        for( i=255; i>0; i--)								/* dimm LED off */
        {
            OCR1AL = i; 
			//OCR1AH = i-1;
			sbi(PORTD,7);
            _delay_ms(10);									// delay 10 ms
        }
		cbi(PORTD,7);
    }
}
