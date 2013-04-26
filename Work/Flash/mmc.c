/*! \file mmc.c \brief MultiMedia and SD Flash Card Interface. */
//*****************************************************************************
//
// File Name	: 'mmc.c'
// Title		: MultiMedia and SD Flash Card Interface
// Author		: Pascal Stang - Copyright (C) 2004
// Created		: 2004.09.22
// Revised		: 2006 by Andreas Fugl
// Version		: 0.1
// Target MCU	: Atmel AVR Series
// Editor Tabs	: 4
//
// NOTE: This code is currently below version 1.0, and therefore is considered
// to be lacking in some functionality or documentation, or may not be fully
// tested.  Nonetheless, you can expect most functions to work.
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************

//----- Include Files ---------------------------------------------------------
//#define MMC_DEBUG

#include <avr/io.h>			// include I/O definitions (port names, pin names, etc)
//#include <avr/signal.h>		// include "signal" names (interrupt names)
#include <avr/interrupt.h>	// include interrupt support

#include "global.h"		// include our global settings
#include "spi.h"		// include spi bus support

//#ifdef MMC_DEBUG
#include "rprintf.h"
//#endif

#include "mmc.h"

// include project-specific hardware configuration
#include "mmcconf.h"

#include "timer.h"

#include "logger_settings.h"
#include "logger_hw_defs.h"

// Global variables

// Functions

void mmcInit(void)
{
	// initialize SPI interface
	spiInit();

	// configure pin as output
	sbi(MMC_CS_DDR, MMC_CS_PIN);
	// release chip select
	sbi(MMC_CS_PORT,MMC_CS_PIN);
}

u08 mmcReset(void)
{
	u08 retry = 0;
	
	spiSetClockPhase(SD_CLOCK_PHASE);
	spiSetBitrate(SD_INIT_SPI_DIV);

	// supply at least 74 clocks cycles to the card after power-up
	_mmc80SPIclocks;

	// Go into SPI Idle State mode, by sending the CMD0 software reset command
	retry = 0;
	do {		
		//rprintf("Retry %d\r\n",retry);

		_mmcEnableCS();
		delay_us(255);
		_mmcCMD0;
		delay_us(255);


		if (_mmcCheckResponse(MMC_R1_IDLE_STATE, 0xFE)) {
			_mmcDisableCS();
			break;
		}

		retry++;

		if (retry >= 0xFE) {
			#ifdef MMC_DEBUG
			rprintf("CMD0 timeout\r\n");
			#endif

			_mmcDisableCS();
			return -1;
		}
	} while(1);

	#ifdef MMC_DEBUG
	rprintf("Passed cmd0\r\n");
	#endif

	_mmcDisableCS();

	// poll card continously until card is ready for next command
	retry = 0;
	do {
		#ifdef MMC_DEBUG
		rprintf("Retry %d\r\n",retry);
		#endif
		// send the CMD1 operating conditions command
		_mmcEnableCS();
		delay_us(255);
		_mmcCMD1;
		delay_us(255);

		if (_mmcCheckResponse(MMC_R1_READY, 0xFFE))
			break;

		retry++;
		
		if (retry >= 0xFE) {
			#ifdef MMC_DEBUG
			rprintf("CMD1 timeout\r\n");
			#endif

			_mmcDisableCS();
			return -1;
		}
	} while(1);

	// Provide card with 8 clock cycles to complete the operation
	spiTransferByte(0xFF);
	_mmcDisableCS();
	// Set the block length to 512 bytes
	_mmcEnableCS();

	_mmcBlockLen512

	if (!_mmcCheckResponse(MMC_R1_READY,0xFFE)) {
		#ifdef MMC_DEBUG
		rprintf("Wrong response setting blocklen\r\n");
		#endif	

		_mmcDisableCS();
		return -1;
	}
	
	// Provide card with 8 clock cycles to complete the operation
	spiTransferByte(0xFF);
	_mmcDisableCS();

	// return success
	return 0;
}

u08 mmcSendCommand(u08 cmd, u32 arg)
{
	u08 r1;
	u16 wait = 0;

	// assert chip select
	_mmcEnableCS();
	spiTransferByte(0xFF);
	// issue the command
	r1 = mmcCommand(cmd, arg);
	// release chip select

	while (wait < 1900) {
		wait++;
	}

	_mmcDisableCS();

	return r1;
}

void mmcCommandNoWait(u08 cmd, u32 arg) {
	// send command
	spiTransferByte(cmd | 0x40);
	spiTransferByte(arg>>24);
	spiTransferByte(arg>>16);
	spiTransferByte(arg>>8);
	spiTransferByte(arg);
	spiTransferByte(0x95);	// crc valid only for MMC_GO_IDLE_STATE
	// end command
}

char cardBusy = 1;

u08 mmcRead(u32 sector, u08* buffer)
{
	u08 r1;
	u16 i;
	u16 retries;
	
	//#ifdef MMC_DEBUG
	//rprintf("mmcRead(");
	//rprintfu32(sector);
	//rprintf(")\r\n");
	//#endif
	
	spiSetClockPhase(SD_CLOCK_PHASE);
	spiSetBitrate(SD_TRANSFER_SPI_DIV);

	_mmcEnableCS();

	retries = 0;
	
	// wait for card not busy, at most 250ms
	if (cardBusy) {
		spiTransferByte(0xFF);
		do {
			r1 = spiTransferByte(0xFF);
			retries++;
			if (!r1) {
				delay_us(250);
			}
			else
				break;
		}
		while (!r1 && retries < 0xFFE);
	}

	if (retries == 0xFFE) {
		_mmcDisableCS();
		rprintf("mmcRead - card still busy, sector ");
		rprintfu32(sector);
		rprintfCRLF();
		return -1;
	}

	do {
		r1 = spiTransferByte(0xFF);
	} while (r1 != 0xFF);

	//rprintf("1: r1 = %u\r\n",r1);

	mmcCommandNoWait(MMC_READ_SINGLE_BLOCK, sector<<9);

	// wait for card response
	do {
		r1 = spiTransferByte(0xFF);
	} while (r1 == 0xFF);

	//rprintf("2: r1 = %u\r\n",r1);
	spiTransferByte(0xFF);

	// NOTE TO SELF - Check error tokens
	// wait for block start
	retries = 0;
	do {
		retries++;
		//rprintf("mmcRead() - Timed out waiting for startblock: R1=0x%x\r\n", r1);
		if (retries > 0xFFE) {
			#ifdef MMC_DEBUG
			rprintf("mmcRead() - Timed out waiting for startblock: R1=0x%x, 0x%x retries\r\n", r1, retries);
			#endif
			_mmcDisableCS();
			return -1;
		}	
	} while((r1 = spiTransferByte(0xFF)) != MMC_STARTBLOCK_READ);

	//rprintf("Read startblock after 0x%x retries\r\n", retries);
	// read in data
	for(i=0; i<0x200; i++)
	{
		*buffer++ = spiTransferByte(0xFF);
		//rprintf("%d\r\n",buffer[i]);
	}
	// read 16-bit CRC
	spiTransferByte(0xFF);
	spiTransferByte(0xFF);

	// Provide card with 8 clock cycles to complete the operation
	spiTransferByte(0xFF);

	_mmcDisableCS();

	cardBusy = 1;

	// return success
	return 0;
}



u08 mmcWrite(u32 sector, u08* buffer)
{
	u08 r1;
	u16 i;
	u16 retries;

	spiSetClockPhase(SD_CLOCK_PHASE);
	spiSetBitrate(SD_TRANSFER_SPI_DIV);

	// assert chip select
	_mmcEnableCS();

	retries = 0;

	// wait for card not busy, at most 250ms
	if (cardBusy) {
		spiTransferByte(0xFF);
		do {
			r1 = spiTransferByte(0xFF);
			retries++;
			if (!r1) {
				delay_us(250);
			}
			else
				break;
		}
		while (!r1 && retries < 0xFFE);
	}

	if (retries == 0xFFE) {
		_mmcDisableCS();
		rprintf("mmcWrite - card still busy, sector ");
		rprintfu32(sector);
		rprintfCRLF();
		return -1;
	}

	// issue command
	r1 = mmcCommand(MMC_WRITE_BLOCK, sector<<9);
	#ifdef MMC_DEBUG
	//rprintf("MMC Write Block R1=0x%x\r\n", r1);
	#endif
	// check for valid response
	if(r1 != 0x00) {
		_mmcDisableCS(); // Andreas - was reversed
		rprintf("mmcWrite - invalid response %x\r\n",r1);
		return r1;
	}
	// send dummy
	spiTransferByte(0xFF);
	// send data start token
	spiTransferByte(MMC_STARTBLOCK_WRITE);
	// write data
	for(i=0; i<0x200; i++)
	{
		spiTransferByte(*buffer++);
	}
	// write 16-bit CRC (dummy values)
	spiTransferByte(0xFF);
	spiTransferByte(0xFF);

	// read data response token
	r1 = spiTransferByte(0xFF);
	if( (r1&MMC_DR_MASK) != MMC_DR_ACCEPT) {
		_mmcDisableCS();
		return r1;
	}
	#ifdef MMC_DEBUG
	//rprintf("Data Response Token=0x%x\r\n", r1);
	#endif
	/* old busy code
	// wait until card not busy
	while(!spiTransferByte(0xFF));
	*/

	// Provide card with 8 clock cycles to complete the operation
	spiTransferByte(0xFF);

	cardBusy = 1;

	// release chip select
	_mmcDisableCS();

	// return success
	return 0;
}

u08 mmcCommand(u08 cmd, u32 arg)
{
	u08 r1;
	u08 retry=0;

	//spiSetClockPhase(SD_CLOCK_PHASE);
	// send command
	spiTransferByte(cmd | 0x40);
	spiTransferByte(arg>>24);
	spiTransferByte(arg>>16);
	spiTransferByte(arg>>8);
	spiTransferByte(arg);
	spiTransferByte(0x95);	// crc valid only for MMC_GO_IDLE_STATE
	// end command
	// wait for response
	// if more than 8 retries, card has timed-out
	// return the received 0xFF
	while((r1 = spiTransferByte(0xFF)) == 0xFF)
		if(retry++ > 8) break;
	// return response
	return r1;
}

int _mmcCheckResponse(u08 expected, u16 maxretries) {
	u16 retries = 0;
	u08 res = 0;

	do {
		res = spiTransferByte(0xFF);
		retries++;

		if (retries >= maxretries) {
			// uncomment to see card response
			//rprintf("mmcCheckResponse() - returned response=0x%x\r\n", res);
			return 0;
		}
		//delay_us(100);
	} while (res != expected);

	// we got the expected result
	return -1;
}

void _mmcEnableCS(void) {

	cbi(MMC_CS_PORT,MMC_CS_PIN);

	spiTransferByte(0xFF);

}

void _mmcDisableCS(void) {

	sbi(MMC_CS_PORT,MMC_CS_PIN);

	spiTransferByte(0xFF);
}
