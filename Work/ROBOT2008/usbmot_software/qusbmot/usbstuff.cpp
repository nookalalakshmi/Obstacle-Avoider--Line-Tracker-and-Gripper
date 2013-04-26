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
#include "usbstuff.h"

QString usb::GetString(usb_dev_handle *dev, int index, int langid){
	QString s;
	s.resize(255);
	int rval = usb_control_msg(dev, USB_ENDPOINT_IN, USB_REQ_GET_DESCRIPTOR, (USB_DT_STRING << 8) + index, langid, (char*)s.data(), s.size()*2, 1000);
	if(rval < 0){
		reportError("Warning: cannot query manufacturer for device");
		return "Error";
	}
	s.resize(rval / 2);
#ifdef DEBUG
	cout << s << endl;
#endif
	return s.right(s.size() - 1);
}

usb_dev_handle* usb::OpenDevice(int vendor, const char *vendorName, int product, const char *productName) {
	struct usb_bus* bus;
	struct usb_device* dev;
	usb_dev_handle* handle = NULL;
	usb_find_busses();
	usb_find_devices();
	for(bus=usb_get_busses(); bus; bus=bus->next){
		for(dev=bus->devices; dev; dev=dev->next){
			if(dev->descriptor.idVendor == vendor && dev->descriptor.idProduct == product){
				handle = usb_open(dev);
				if(!handle){
					reportError("Warning: cannot open USB device:");
					continue;
				}
				//if(vendorName == NULL && productName == NULL) return handle;
				if(GetString(handle, dev->descriptor.iManufacturer) == vendorName && GetString(handle, dev->descriptor.iProduct) == productName) return handle;
				usb_close(handle);
			}
		}
	}
	return NULL;
}
