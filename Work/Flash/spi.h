#ifndef __SPI_H
#define __SPI_H

#include <avr/io.h>

void spi_init();
uint8_t spi_transmit(uint8_t data);

#endif
