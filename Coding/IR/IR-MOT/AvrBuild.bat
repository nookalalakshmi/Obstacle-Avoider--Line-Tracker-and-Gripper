@ECHO OFF
"E:\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "G:\_Feb2009\IR-MOT\labels.tmp" -fI -W+ie -o "G:\_Feb2009\IR-MOT\IRMOT.hex" -d "G:\_Feb2009\IR-MOT\IRMOT.obj" -e "G:\_Feb2009\IR-MOT\IRMOT.eep" -m "G:\_Feb2009\IR-MOT\IRMOT.map" "G:\_Feb2009\IR-MOT\IRMOT.asm"
