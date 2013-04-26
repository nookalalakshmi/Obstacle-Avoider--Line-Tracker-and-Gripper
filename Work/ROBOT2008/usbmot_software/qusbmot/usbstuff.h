#ifndef USBSTUFF_H
#define USBSTUFF_H USBSTUFF_H
/*
qusbmot is the host software to control the usbmot motor controller. 
Copyright (C) 2008 Andreas Goelzer, http://andreas.goelzer.de/usbmot

This file is part of qusbmot.

qusbmot is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

qusbmot is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with qusbmot.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <usb.h>
#include <QObject>
#include <QTextStream>
#include <iostream>
#include <iomanip>
#include "usbmotiface.h"
//obdevs shared vid/pid pair, see USBID-License.txt
const int obdev_shared_vid = 0x16C0;
const int obdev_shared_pid = 0x05DC;

const int usb_language = 0x0409; //US English, seems to be standard for querying at least in windows



class usb : public QObject{
	Q_OBJECT
	QTextStream cout;
	void reportError(const char* desc){
		cout << desc <<  usb_strerror() << endl;
	}
	
	QString GetString(usb_dev_handle *dev, int index, int langid = usb_language);
	usb_dev_handle* OpenDevice(int vendor, const char *vendorName, int product, const char *productName);
	
	public:
	usb_dev_handle* handle;
	unsigned char buffer[8];
	int nBytes;
	usb(QObject *parent = 0) : QObject(parent), cout(stdout), handle(NULL){ init(); }	

	void init(){
		usb_init();
		if(!(handle = OpenDevice(obdev_shared_vid, "andreas.goelzer.de", obdev_shared_pid, "usbmot"))){
        		reportError("Could not find USB device usbmot");
		}
	}
	~usb(){ close(); }
	void close(){
		if(handle) usb_close(handle);
	}
	void printhexbyte(unsigned char datum){
		//std::cout.setwidth(2);
		std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)datum << " ";	
	}
	void ctrlmsg(int cmd, int port, unsigned char* data, int length){
#ifdef DEBUG
		std::cout << "sending " << length << " Bytes to device pt. " << port << " cmd " << cmd<< ":";
		for(int j = 0; j < length; ++j) printhexbyte(data[j]);
		std::cout << std::endl;
#endif
		int reqType = 0;
		if(cmd == usbmot::set) reqType = USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT;
		else reqType = USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN;
		nBytes = usb_control_msg(handle, reqType, cmd, 0, port, (char*)data, length, 5000);
#ifdef DEBUG
		std::cout << "read back " << nBytes << " Bytes: ";
		for(int j = 0; j < nBytes; ++j) printhexbyte(data[j]);
		std::cout << std::endl;
#endif
		if(nBytes < 0){
			cout << "USB error nbytes < 0:" << usb_strerror() << endl;
			emit connectionProblem(nBytes);
		}
	}
	void sendData(int port, unsigned char* data, int length){
		ctrlmsg(usbmot::set,port,data,length);
	}
	void readData(int port, unsigned char* data, int length){
		ctrlmsg(usbmot::get,port,data,length);
	}
	signals:
	void connectionProblem(int errorcode);
};


#endif
