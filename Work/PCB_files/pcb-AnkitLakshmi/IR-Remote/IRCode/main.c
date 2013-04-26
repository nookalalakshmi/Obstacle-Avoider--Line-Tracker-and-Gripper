/*
TV-B-Gone
Firmware
for use with ATtiny85
Mitch Altman + Limor Fried
7-Oct-07

Distributed under Creative Commons 2.5 -- Attib & Share Alike
*/

#include <avr/io.h>             // this contains all the IO port definitions
#include <avr/interrupt.h>      // definitions for interrupts
#include <avr/sleep.h>          // definitions for power-down modes
#include <avr/pgmspace.h>       // definitions or keeping constants in program memory
#include "main.h"

#define LED PB0         // visible LED
#define IRLED PB1       // IR LED
#define BUTTON PB2      // push button

//define DEBUG(x) 

/*
This project transmits a bunch of TV POWER codes, one right after the other, 
with a pause in between each.  (To have a visible indication that it is 
transmitting, it also pulses a visible LED once each time a POWER code is 
transmitted.)  That is all TV-B-Gone does.  The tricky part of TV-B-Gone 
was collecting all of the POWER codes, and getting rid of the duplicates and 
near-duplicates (because if there is a duplicate, then one POWER code will 
turn a TV off, and the duplicate will turn it on again (which we certainly 
do not want).  I have compiled the top-40 most popular codes with the 
duplicates eliminated, both for North America (which is the same as Asia, as 
far as POWER codes are concerned -- even though much of Asia USES PAL video) 
and for Europe (which works for Australia, New Zealand, the Middle East, and 
other parts of the world that use PAL video).

Before creating a TV-B-Gone Kit, I originally started this project by hacking 
the MiniPOV kit.  This presents a limitation, based on the size of
the Atmel ATtiny2313 internal flash memory, which is 2KB.  With 2KB we can only 
fit about 7 POWER codes into the firmware's database of POWER codes.  40 codes
requires 8KB of flash memory, which is why we chose the ATtiny85 for the 
TV-B-Gone Kit.

This version of the firmware has the most popular 40 POWER codes for North America.
*/


/*
This project is a good example of how to use the AVR chip timers.
*/


/*
The hardware for this project is very simple:
     ATtiny85 has 8 pins:
       pin 1   connects to programming circuitry
       pin 2   one pin of ceramic resonator
       pin 3   one pin of ceramic resonator
       pin 4   ground
       pin 5   PB0 - visible LED, and also connects to programming circuitry
       pin 6   OC1A - IR emitter, through a PN2222A driver (with 47 ohm base resistor), and also connects to programming circuitry
       pin 7   push-button switch, and also connects to serial port programming circuitry
       pin 8   +3v
    See the schematic for more details.

    This firmware requires using an 8.0MHz ceramic resonator 
       (since the internal oscillator may not be accurate enough).

    IMPORTANT:  to use the ceramic resonator, you must perform the following:
                    make burn-fuse_cr
*/


/*
The C compiler creates code that will transfer all constants into RAM when the microcontroller
resets.  Since this firmware has a table (powerCodes) that is too large to transfer into RAM,
the C compiler needs to be told to keep it in program memory space.  This is accomplished by
the macro PROGMEM (this is used in the definition for powerCodes).  Since the
C compiler assumes that constants are in RAM, rather than in program memory, when accessing
powerCodes, we need to use the pgm_read_word() and pgm_read_byte macros, and we need
to use powerCodes as an address.  This is done with PGM_P, defined below.  
For example, when we start a new powerCode, we first point to it with the following statement:
    PGM_P thecode_p = pgm_read_word(powerCodes+i);
The next read from the powerCode is a byte that indicates the carrier frequency, read as follows:
    uint8_t freq = pgm_read_byte(thecode_p);
Subsequent reads from the powerCode are onTime/offTime pairs, which are words, read as follows:
    ontime = pgm_read_word(thecode_p+(offset_into_table);
    offtime = pgm_read_word(thecode_p+(offset_into_table);
*/

SIGNAL(SIG_INTERRUPT0) {
  PORTB &= ~_BV(LED); // turn on visible LED at PB0 by pulling pin to ground
  TCCR1 = 0;          // turn off Timer1 frequency generator (should be off already)
  WDTCR = _BV(WDE);   // turn on the watchdog timer to reset the chip
}

#define NOP __asm__ __volatile__ ("nop")
// This function delays the specified number of 10 microseconds
#define DELAY_CNT 11
void delay_ten_us(uint16_t us) {
  uint8_t timer;
  while (us != 0) {
    for (timer=0; timer <= DELAY_CNT; timer++) {
      NOP;
      NOP;
    }
    NOP;
    us--;
  }
}


// This function quickly pulses the visible LED (connected to PB0, pin 5)
void quickflashLED( void ) {
  // pulse LED at PB0 on for 30ms
  PORTB &= ~_BV(LED);         // turn on visible LED at PB0 by pulling pin to ground
  delay_ten_us(3000);         // 30 millisec delay
  PORTB |= _BV(LED);          // turn off visible LED at PB0 by pulling pin to +3V
}


// This function quickly pulses the visible LED (connected to PB0, pin 5) 4 times
void quickflashLED4x( void ) {
  quickflashLED();
  delay_ten_us(15000);        // 150 millisec delay
  quickflashLED();
  delay_ten_us(15000);        // 150 millisec delay
  quickflashLED();
  delay_ten_us(15000);        // 150 millisec delay
  quickflashLED();
}


// This function transmits one Code Element of a POWER code to the IR emitter, 
//   given offTime and onTime for the codeElement
//     If offTime = 0 that signifies the last Code Element of the POWER code
//     and the delay_ten_us function will have no delay for offTime 
//     (but we'll delay for 250 milliseconds in the main function)
void xmitCodeElement(uint16_t ontime, uint16_t offtime ) {
  // start Timer1 outputting the carrier frequency to IR emitters on OC1A (PB1, pin 6)
  TCCR1 =_BV(COM1A0) | _BV(CS10) | _BV(CTC1);
  //TCCR1 = 0b10010001  // CTC1 = 1 to reset Timer1 to 0 when it reaches the value in OCR1C (i.e., on Compare Match)
                        // PWM1A = 0 to disable PWM mode
                        // COM1A1:0 = 01 to toggle OC1A on Compare Match
                        // CS13:10 = 0001 to start Timer1 with prescaler set to divide by 1 (i.e., no prescaler divide)

  // keep transmitting carrier for onTime
  delay_ten_us(ontime);

  // turn off output to IR emitters on 0C1A (PB1, pin 6) for offTime
  TCCR1 = 0;      // stop Timer1
  delay_ten_us(offtime);
}

//extern const struct powercode powerCodes[] PROGMEM;
extern const PGM_P *powerCodes[] PROGMEM;

extern uint8_t num_codes;

int main(void) {
  uint8_t i, j;
  uint16_t ontime, offtime;
  //uint16_t x;
 
  MCUSR = 0;                     // clear watchdog flag
  WDTCR = _BV(WDCE) | _BV(WDE);  // enable WDT disable
  WDTCR = 0;                     // disable WDT

  GIMSK = _BV(INT0);     // generate an interrupt on low level of INT0
  TIMSK = 0x00;          // no Timer interrupts enabled
  sei();                 // turn on INT0 interrupts

  DDRB = _BV(LED) | _BV(IRLED);    // set the visible and IR LED pins to outputs
  PORTB = _BV(BUTTON) | _BV(LED);  // button has a pullup, visible LED is off when pin is high
  PORTB &= ~_BV(IRLED);            // IR LED is off when pin is low

  //DEBUG(putstrings("\n\rHi world!"));
  //DEBUG(putstring("Codes: "); putnum_ud(num_codes));

  for (i=0; i<num_codes; i++) {   // for every POWER code in our collection
    quickflashLED(); // visible indication that a code is being output
    PGM_P thecode_p = pgm_read_word(powerCodes+i);     // point to next POWER code
    //DEBUG(putstring("\n\rAddr: "); putnum_uh(thecode_p));

    uint8_t freq = pgm_read_byte(thecode_p);
    // set OCR for Timer1 to output this POWER code's carrier frequency
    OCR1C = freq; 

    //x = (freq+1) * 2;
    //DEBUG(putstring("\n\rOCR1: "); putnum_ud(freq););
    //DEBUG(putstring("\n\rFreq: "); putnum_ud(F_CPU/x););

    // transmit all codeElements for this POWER code (a codeElement is an onTime and an offTime)
    // transmitting onTime means pulsing the IR emitters at the carrier frequency for the length of time specified in onTime
    // transmitting offTime means no output from the IR emitters for the length of time specified in offTime
    j = 0;  // index into codeElements of this POWER code
    do {
      // read the onTime and offTime from the program memory
      ontime = pgm_read_word(thecode_p+(j*4)+1);
      offtime = pgm_read_word(thecode_p+(j*4)+3);
      //DEBUG(putstring("\n\r\tPair = "); putnum_ud(ontime));
      //DEBUG(putstring("\t"); putnum_ud(offtime));

      xmitCodeElement(ontime, offtime);  // transmit this codeElement (ontime and offtime)
      j++;
    } while ( offtime != 0 );  // offTime = 0 signifies last codeElement for a POWER code

    // delay 250 milliseconds before transmitting next POWER code
    delay_ten_us(25000);
  }
  

  // flash the visible LED on PB0  4 times to indicate that we're done
  delay_ten_us(65500); // wait maxtime 
  quickflashLED4x();

  // Shut down everything and put the CPU to sleep
  TCCR1 = 0;                      // turn off frequency generator (should be off already)
  PORTB = _BV(BUTTON) | _BV(LED); // turn on the button pullup, turn off visible LED
  PORTB &= ~_BV(IRLED);           // turn off IR LED
  delay_ten_us(1000);             // wait 10 millisec second

  MCUCR = _BV(SM1) |  _BV(SE);    // power down mode,  SE=1 (bit 5) -- enables Sleep Modes
  sleep_cpu();                    // put CPU inteo Power Down Sleep Mode
}

