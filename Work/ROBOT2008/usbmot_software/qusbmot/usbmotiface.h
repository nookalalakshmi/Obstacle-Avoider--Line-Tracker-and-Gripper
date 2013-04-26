#ifndef USBMOTIFACE_H
#define USBMOTIFACE_H USBMOTIFACE_H
/*
Copyright (C) 2008 Andreas Goelzer, http://andreas.goelzer.de/usbmot

This file defines the interface between qusbmot and the devices
firmware.

qusbmot and the device firmware are free software: you can
redistribute it and/or modify them under the terms of the GNU 
General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option)
any later version.

qusbmot and the firmware are distributed in the hope that they
will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this file.  If not, see <http://www.gnu.org/licenses/>.
*/

class MotorData {
	public:
	uint8_t forward;
	uint8_t backward;
	///enabled=278 means motor will be on 278/65535
	uint16_t enabled;
	///serialize to a char stream
	static uint8_t serialize(unsigned char* targetdata, uint16_t enabled, uint8_t forward, uint8_t backward){
		targetdata[0] = enabled & 0xFF;
		targetdata[1] = enabled >> 8;
		targetdata[2] = forward;
		targetdata[3] = backward;
		return 4;
	}
	///read back what was serialized
	MotorData(unsigned char* sourcedata){
		enabled = sourcedata[0] | (sourcedata[1] << 8);
		forward = sourcedata[2];
		backward = sourcedata[3];
	}
};

namespace usbmot {
	const uint8_t get = 0;
	const uint8_t set = 1;
}




#endif
