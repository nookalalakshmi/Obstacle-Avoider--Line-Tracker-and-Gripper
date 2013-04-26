# Name: Makefile
# Project: AVR-Doper
# Author: Christian Starkjohann
# Creation Date: 2006-06-21
# Tabsize: 4
# Copyright: (c) 2006 by OBJECTIVE DEVELOPMENT Software GmbH
# License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
# This Revision: $Id: Makefile 566 2008-04-26 14:21:47Z cs $

DEVICE = atmega8
F_CPU = 12000000
FUSE_L  = # see below for fuse values for particular devices
FUSE_H  = 
PORT = avrdoper
PROGRAMMER = stk500v2
AVRDUDE = avrdude -c $(PROGRAMMER) -P $(PORT) -p $(DEVICE)

CFLAGS = $(DEFINES) -Iusbdrv -I. -DDEBUG_LEVEL=0 -DF_CPU=$(F_CPU)
OBJECTS = usbdrv/usbdrv.o usbdrv/usbdrvasm.o usbdrv/oddebug.o hvprog.o\
	isp.o serial.o stk500protocol.o timer.o utils.o vreg.o main.o

COMPILE = avr-gcc -Wall -Os $(CFLAGS) -mmcu=$(DEVICE)

################################## ATMega8 ##################################
# ATMega8 FUSE_L (Fuse low byte):
# 0x9f = 1 0 0 1   1 1 1 1
#        ^ ^ \ /   \--+--/
#        | |  |       +------- CKSEL 3..0 (external >8M crystal)
#        | |  +--------------- SUT 1..0 (crystal osc, BOD enabled)
#        | +------------------ BODEN (BrownOut Detector enabled)
#        +-------------------- BODLEVEL (2.7V)
# ATMega8 FUSE_H (Fuse high byte):
# 0xc9 = 1 1 0 0   1 0 0 1 <-- BOOTRST (boot reset vector at 0x0000)
#        ^ ^ ^ ^   ^ ^ ^------ BOOTSZ0
#        | | | |   | +-------- BOOTSZ1
#        | | | |   + --------- EESAVE (don't preserve EEPROM over chip erase)
#        | | | +-------------- CKOPT (full output swing)
#        | | +---------------- SPIEN (allow serial programming)
#        | +------------------ WDTON (WDT not always on)
#        +-------------------- RSTDISBL (reset pin is enabled)
#
############################## ATMega48/88/168 ##############################
# ATMega*8 FUSE_L (Fuse low byte):
# 0xdf = 1 1 0 1   1 1 1 1
#        ^ ^ \ /   \--+--/
#        | |  |       +------- CKSEL 3..0 (external >8M crystal)
#        | |  +--------------- SUT 1..0 (crystal osc, BOD enabled)
#        | +------------------ CKOUT (if 0: Clock output enabled)
#        +-------------------- CKDIV8 (if 0: divide by 8)
# ATMega*8 FUSE_H (Fuse high byte):
# 0xdd = 1 1 0 1   1 1 0 1
#        ^ ^ ^ ^   ^ \-+-/
#        | | | |   |   +------ BODLEVEL 0..2 (101 = 2.7 V)
#        | | | |   + --------- EESAVE (preserve EEPROM over chip erase)
#        | | | +-------------- WDTON (if 0: watchdog always on)
#        | | +---------------- SPIEN (allow serial programming)
#        | +------------------ DWEN (debug wire enable)
#        +-------------------- RSTDISBL (reset pin is enabled)
#


# symbolic targets:
help:
	@echo "This Makefile has no default rule. Use one of the following:"
	@echo "make hex ......... to build stk500protocol.hex for AVR-Doper hardware"
	@echo "make metaboard ... to build stk500protocol.hex for metaboard hardware"
	@echo "make usbasp ...... to build stk500protocol.hex for usbasp hardware"
	@echo "make program ..... to flash fuses and firmware"
	@echo "make fuse ........ to flash the fuses"
	@echo "make flash ....... to flash the firmware"
	@echo "make usbaspload .. to upload firmware to metaboard"
	@echo "make clean ....... to delete objects and hex file"

hex: stk500protocol.hex
program: flash fuse

metaboard:
	$(MAKE) stk500protocol.hex F_CPU=16000000 DEVICE=atmega168 DEFINES=-DMETABOARD_HARDWARE=1

usbasp:	# configure DEVICE and F_CPU appropriately for actual hardware
	$(MAKE) stk500protocol.hex DEFINES=-DUSBASP_HARDWARE=1

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:
	$(AVRDUDE) -U flash:w:stk500protocol.hex:i

usbaspload:
	$(MAKE) flash PROGRAMMER=usbasp DEVICE=atmega168

fuse:
	@[ "$(FUSE_H)" != "" -a "$(FUSE_L)" != "" ] || \
		{ echo "*** Edit Makefile and choose values for FUSE_L and FUSE_H!"; exit 1; }
	$(AVRDUDE) -U hfuse:w:$(FUSE_H):m -U lfuse:w:$(FUSE_L):m

clean:
	rm -f stk500protocol.hex stk500protocol.lst stk500protocol.obj stk500protocol.cof stk500protocol.list stk500protocol.map stk500protocol.eep.hex stk500protocol.elf *.o usbdrv/*.o stk500protocol.s usbdrv/oddebug.s usbdrv/usbdrv.s

# file targets:
stk500protocol.elf:	$(OBJECTS)
	$(COMPILE) -o stk500protocol.elf $(OBJECTS)

stk500protocol.hex:	stk500protocol.elf
	rm -f stk500protocol.hex stk500protocol.eep.hex
	avr-objcopy -j .text -j .data -O ihex stk500protocol.elf stk500protocol.hex
	./checksize stk500protocol.elf 8192 1024
# do the checksize script as our last action to allow successful compilation
# on Windows with WinAVR where the Unix commands will fail.

disasm:	stk500protocol.elf
	avr-objdump -d stk500protocol.elf

cpp:
	$(COMPILE) -E stk500protocol.c
