@ECHO OFF
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\_Feb2009\labels.tmp" -fI -W+ie -o "C:\_Feb2009\IRMOT.hex" -d "C:\_Feb2009\IRMOT.obj" -e "C:\_Feb2009\IRMOT.eep" -m "C:\_Feb2009\IRMOT.map" "C:\_Feb2009\IRMOT.asm"
