#include "spi.h"

void spi_init() {
	// set SCK and MOSI as output (SS/PB0 must be set as output, when SPI is master)
	DDRB |= (_BV(PB0) | _BV(PB1) | _BV(PB2));
	
	// use PD1 as SS
	DDRD |= _BV(PD1);
	
	// enable spi, set as master, scale sck freq with 128
	// SPCR |= (_BV(SPE) | _BV(MSTR) | _BV(SPR1) | _BV(SPR0));

	// enable spi, set as master, scale sck freq with 4
	SPCR |= (_BV(SPE) | _BV(MSTR));
	
	// double SPI speed
	//SPSR |= _BV(SPI2X);
}


uint8_t spi_transmit(uint8_t data) {
	// set SS low
	PORTD &= ~_BV(PD1);
	
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	
	// set SS high
	PORTD |= _BV(PD1);
	
	return SPDR;
}
