This is the Readme file for the usbmot device software. Please 
visit http://andreas.goelzer.de/usbmot for more information.

The usbmot device controls up to two small motors, 600 mA 
current each, 1.2 A peak each, with an atmel atmega 
microcontroller connected to some host device via USB. The speed 
of the motors can be controlled with PWM.

This archive should contain:
- a folder "firmware" containing the software for the USB device,
  including the avr usb driver by obdev
  (http://www.obdev.at/products/avrusb/).
- a folder "qusbmot" containing the host software to control that
  device.

To compile the firmware, change into the firmware folder. Then edit
the makefile and adjust device type and programmer. In order to
remake the hex file, type "make hex", and to transfer it to the
device, type "make flash" (jumper 1-1 needs to be set).

To compile the host software, change into the qusbmot folder. You
will need qt (http://trolltech.com/products) and 
libusb (http://libusb.sourceforge.net/) with their respective tools
and header files in order for the compilation to succeed.
If both are properly installed, typing "make" should compile the 
program, which can then be executed by typing "./qusbmot".
