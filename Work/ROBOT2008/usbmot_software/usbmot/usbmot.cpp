/**
\file usbmot.cpp
\author Andreas Gölzer
\date 2008-10-24

USB Motor Control Firmware for the usbmot device
Copyright (C) 2008  Andreas Goelzer
 
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

This program uses the avr-usb library, http://www.obdev.at/avrusb/, 
to perform the usb communication.

see http://andreas.goelzer.de/usbmot for updates.
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
extern "C" {
#include "usbdrv.h"
}
#include "usbmotiface.h"


#define isbitset(port,bit) (port & (1 << bit)) >> bit
#define setbit(port,bit,value) port = (port & ~(1 << bit)) | (value << bit);
/*inline void setbit(volatile uint8_t& port, uint8_t bit, uint8_t value){
	port = (port & ~(1 << bit)) | (value << bit);
}*/

static uint8_t port;
static uint8_t getset;

static const uint8_t dropmotorres = 4;
static uchar    replyBuf[8];

/// Handle the usb communication
/** This function gets called by the auvr-usb api during usbpoll(),
see the api doc for return values and stuff */
usbMsgLen_t usbFunctionSetup(uchar setupData[8]){
	usbRequest_t *rq = (usbRequest_t *)setupData;
	usbMsgPtr = replyBuf;
	getset = rq->bRequest & 1;
	port = rq->wIndex.bytes[0];
	if(getset == usbmot::get) switch(port){
		case 0: case 1:
			replyBuf[0] = isbitset(PORTC,port);
		return 1;
		case 3:
			return MotorData::serialize(replyBuf,OCR1A << dropmotorres, isbitset(PORTB,4), isbitset(PORTB,5));
		case 4:
			return MotorData::serialize(replyBuf,OCR1B << dropmotorres, isbitset(PORTB,0), isbitset(PORTB,3));
		default:
			replyBuf[0] = 'u';
			replyBuf[1] = 'p';
			return 2;
	} else if(getset == usbmot::set) return USB_NO_MSG;
	else {
		replyBuf[0] = 'u';
		replyBuf[1] = 'c';
		return 2;
	}
	return 0;
}

uchar usbFunctionWrite(uchar *data, uchar len){
	switch(port){
	case 0: case 1:{
		setbit(PORTC,port,data[0]);
		break;
		}
	case 3: case 4: {
		MotorData mot(data);
		if(port == 3){
			OCR1A = mot.enabled >> dropmotorres;
			setbit(PORTB,4,mot.forward);
			setbit(PORTB,5,mot.backward);
		} else {
			OCR1B = mot.enabled >> dropmotorres;
			setbit(PORTB,0,mot.forward);
			setbit(PORTB,3,mot.backward);
		}
		break;
		}
	default: {
		replyBuf[0] = 'u';
		replyBuf[1] = 'p';
		return 2;
		}
	}
	return 1;
}

int main(){
	//force re-enumeration of the device
	usbDeviceDisconnect();
	//we have to wait some time here, so initializing non-usb stuff here
	DDRC = 0x3;

	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11); //clear on compare match, set at bottom , fast pwm, ICR1 is TOP 
	TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS10); 

	ICR1 = 4096; //2^11, ~4 kHz at 8 MHz Clock (< 5 kHz, L293D)

	OCR1B = 4096;
	OCR1A = 2000;
	DDRB=63;
	setbit(PORTB,0,1);
	setbit(PORTB,4,1);
	setbit(PORTB,5,1);

	//continue re-emumerations and start usb, enable ints
	_delay_ms(200);
	usbDeviceConnect();
	usbInit();
	sei();
	while(true){
		usbPoll();
		//_delay_ms(200);
	}
}
