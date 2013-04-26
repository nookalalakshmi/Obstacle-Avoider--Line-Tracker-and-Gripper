#ifndef _PWM_H_
#define _PWM_H_

#define LED_PORT 		PORTB
#define LED_PORT_DDR	DDRB
#define LED_PIN			1
#define COUNTER_TOP 	0x00FFUL

void pwm_init();
void pwm_setduty(unsigned char duty);

#endif
