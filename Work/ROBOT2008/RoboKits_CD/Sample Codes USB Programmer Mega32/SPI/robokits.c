//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR SPI
//			WRITTEN FOR ROBOGRID

/*-------------------------------------------------------------------          
 Description:
 This example shows how to use SPI bus of AVR for communication.

 Note:
 When using with other AVr micro change connections of SS,MOSI,SCK pins
 and definations of pins.
 
   _delay_ms() function parameter passed should not exeed
 262.14ms / F_CPU in mhz.
 
 so for 16MHz the maximum paramer should be 16ms.
 
 For 1MHz it can be upto 262ms (100 is used for this example).
  
 Must be changed to get accurate delay at higher MHz.
 
 The timing will differ if the operating frequency is changed.
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------CONNECTIONS WITH MEGA16---------------------------
------------------------------------------------------------------
 
 AVR ATMEGA16          74HC595
 SS   (5)      ->      LatchClock (12)
 MOSI (6)      ->      SerialIn   (14)
 SCK  (8)      ->      ShiftClock (11)
 GND  (11)	   ->      GND        
                       Reset      (10) -> VCC
                       OE         (13) -> GND
                       Q1         (1)  -> 1K Resistor -> LED -> GND
   
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include <inttypes.h>
#include <avr/io.h>
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY

/*----------------------------------------------------------------
-----------------DEFINATION OF SPI PINS---------------------------
-----------------------------------------------------------------*/

#define SPI_CHIP_SELECT PB4             // SS pin is used here, but any pin can be used
#define SPI_MOSI        PB5             // SPI MOSI pin 
#define SPI_SCK         PB7             // SPI SCK pin
#define LED_PWR			PA4
#define LED_DDR			DDRA
#define SPI_DDR         DDRB            // port used by SPI

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{ 	
    uint8_t led = 2;
    
    SPI_DDR  = _BV(SPI_CHIP_SELECT) + _BV(SPI_MOSI) + _BV(SPI_SCK); /* SPI port initialization (/SS, MOSI, SCK output, MISO input) */
	LED_DDR  = _BV(LED_PWR);    
	sbi(PORTA,4);					//LED1 ON (INDICATION FOR READY TO USE)	
    SPCR = _BV(SPE) +_BV(MSTR) + _BV(CPOL) + _BV(CPHA);    			/* SPI interrupt disabled, SPI port enabled, master mode, MSB first, SPI mode 3, SPI Clock = XTAL/4 */
     
    for(;;)
    {
        PORTB &= ~_BV(SPI_CHIP_SELECT);     	// enable SPI device
        SPDR = led;                         	// send data to SPI device (turn LED on/off)
        while (!(SPSR & _BV(SPIF)));        	// wait until write complets
        PORTB |= _BV(SPI_CHIP_SELECT);      	// disable SPI device

        led ^= 2;                           	// toggle LED
                
        _delay_ms(100);                       	// delay 0.1 seconds
   }
}
