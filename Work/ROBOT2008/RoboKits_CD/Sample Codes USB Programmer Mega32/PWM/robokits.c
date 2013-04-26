//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR PWM
//			WRITTEN FOR ROBOGRID

 
 /*-------------------------------------------------------------------          
 Description:
 This example shows how to generate average DC voltages between VCC 
 and GND using Pulse Width Modulation (PWM).

 Note:
 Connect motors to board.
 
 Put PWM1 and PWM2 jumpers towards avr.
 
 Change OC1A  and OC1B pin pullup if used with any other AVR micro.
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY

#define XTAL		  1000000L    // Crystal frequency in Hz
#define OC1A_PIN PD5              // OC1A pin
#define OC1B_PIN PD6              // OC1B pin
#define OC1_DDR DDRD             // OC1 DDR


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
	
	DDRC=0xFF;

	sbi(PORTA,4);					//LED1 ON (INDICATION FOR READY TO USE)
		
	sbi(PORTB,2);					//ENABLE PULL UP FOR SWITCH INT2
	sbi(PORTD,1);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1
	

	
	sbi(PORTC,0);					//MOTOR1 forward
	sbi(PORTC,3);					//MOTOR2 reverse
	
	
    uint8_t i = 0;

    OC1_DDR |= _BV(OC1A_PIN) + _BV(OC1B_PIN);    			// set OC1A and OC1B pin as output, required for output toggling 

    TCCR1A =  _BV(WGM10) | _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0);    	// enable 8 bit PWM, select inverted PWM
		
    // timer1 running on 1/8 MCU clock with clear timer/counter1 on Compare Match
    // PWM frequency will be MCU clock / 8 / 512, e.g. with 1Mhz Crystal 244 Hz.
    TCCR1B = _BV(CS11) | _BV(WGM12);
 
    for (;;)
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
