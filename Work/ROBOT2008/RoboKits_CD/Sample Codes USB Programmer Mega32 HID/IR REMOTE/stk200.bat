@echo off


echo "avrdude -c stk200 -P lpt1 -p atmega16 -U flash:w:robokits.hex -U hfuse:w:0xd9:m -U lfuse:w:0xe1:m"
avrdude -c stk200 -P lpt1 -p atmega16 -U flash:w:robokits.hex -U hfuse:w:0xd9:m -U lfuse:w:0xe1:m


pause
