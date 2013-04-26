#include "pwm.h"
#include <avr/io.h>

// Initializes timer1 for pwm output
void pwm_init() {
	LED_PORT_DDR |= _BV(LED_PIN);

	TCCR1A = 0xA2;
	TCCR1B = 0x19;	// Prescaler: (Fastest -> Slowest) (0x19 -> 0x1C)

	ICR1 = COUNTER_TOP; // frequency
	OCR1A = 0; // dutycycle
}

void pwm_setduty(unsigned char duty) {
	OCR1A = (unsigned) duty;
}
