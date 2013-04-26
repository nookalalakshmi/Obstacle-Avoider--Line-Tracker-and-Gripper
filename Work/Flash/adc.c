#include "adc.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "pid.h"
#include "pwm.h"
#include "curve.h"

#define CPLD_PORT		PORTD
#define CPLD_PORT_DDR	DDRD
#define CPLD_WHB 		7
#define CPLD_D3 		6
#define CPLD_D2 		5
#define CPLD_D1 		4
#define CPLD_D0			3

void cpld_init() {
	CPLD_PORT_DDR |= (_BV(CPLD_WHB) | _BV(CPLD_D3) | _BV(CPLD_D2) | _BV(CPLD_D1) | _BV(CPLD_D0));
	CPLD_PORT &= ~_BV(CPLD_WHB);
}

void cpld_setduty(unsigned char duty) {
	// High part
	CPLD_PORT = ((duty & 0xF0) >> 1);	 // mask off low part
	CPLD_PORT |= _BV(CPLD_WHB);
	//portread |= (mask | _BV(CPLD_WHB));	// set 1's
	//CPLD_PORT &= ~(mask | 0x83); // set 0's

	// Low part
	CPLD_PORT = (duty & 0x0F) << 3;
	CPLD_PORT &= ~_BV(CPLD_WHB);
	//CPLD_PORT |= mask;
	//CPLD_PORT &= ~(mask | 0x83);
}

ISR(ADC_vect) {
	unsigned char out;
	adcResult = ADCH;
	out = (unsigned char)pid_Controller((int16_t)curveY, (int16_t)adcResult, &pidData);
	pwm_setduty(out);
	cpld_setduty(out);
}

// Initializes ADC (1/500) / 4 = 2khz
void adc_init() {
	ADCSR &= ~_BV(ADEN); // disable adc before setup

	//ADMUX &= ~(_BV(REFS0) | _BV(REFS1) | _BV(ADLAR)); // set to external AREF, right adjusted res
	
	ADMUX |= (_BV(ADLAR) | _BV(REFS0) | _BV(REFS1)); // left adjust result, 2.56vref

	ADCSR |= _BV(ADIE); 	// enable adc interrupt

	// prescaler 8
	//ADCSR &= ~_BV(ADPS2);
	//ADCSR |= _BV(ADPS1) | _BV(ADPS0);

	// prescaler 16
	//ADCSR |= _BV(ADPS2);
	//ADCSR &= ~(_BV(ADPS1) | _BV(ADPS0));

	// prescaler 32
	ADCSR |= (_BV(ADPS2) | _BV(ADPS0));
	ADCSR &= ~_BV(ADPS1);
	
	// prescaler 128
	//ADCSR |= (_BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0));

	ADCSR |= (_BV(ADEN) | _BV(ADFR)); // enable adc, free running mode

	sei(); //enable interrupt

	ADCSR |= _BV(ADSC); // start the first conversion

	cpld_init();
}
