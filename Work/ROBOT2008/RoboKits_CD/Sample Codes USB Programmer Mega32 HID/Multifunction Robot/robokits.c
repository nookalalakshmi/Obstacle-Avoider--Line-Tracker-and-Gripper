/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include <util/delay.h>				//HEADER FILE FOR DELAY
#include <setjmp.h>


#define led1on 	sbi(PORTA,4)
#define led1off cbi(PORTA,4)
#define led2on 	sbi(PORTA,5)
#define led2off	cbi(PORTA,5)
#define led3on 	sbi(PORTA,6)
#define led3off	cbi(PORTA,6)
#define led4on 	sbi(PORTA,7)
#define led4off cbi(PORTA,7)

#define leftsensoroff 	bit_is_set(PIND,7)
#define leftsensoron 	bit_is_clear(PIND,7)
#define rightsensoroff 	bit_is_set(PIND,6)
#define rightsensoron   bit_is_clear(PIND,6)

#define int2	bit_is_clear(PINB,2)
#define sw1		bit_is_clear(PIND,1)
#define int0	bit_is_clear(PIND,2)
#define int1	bit_is_clear(PIND,3)

void forward(void);
void backward(void);
void left(void);
void right(void);
void breaks(void);
void stop(void);
void init(void);

void leftmotor(char speed, char direction);
void rightmotor(char speed, char direction);


/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
	char mode;
	
	init();
	
	led1on;	
	mode=0; 
	
	for(;mode<1;)
	{
		if(leftsensoron)
			led2on;
		else
			led2off;
		
		if(rightsensoron)
			led3on;
		else
			led3off;
		
		if(int2)
			mode=1;			//Obstacle Avoider mode
		
		if(sw1)
			mode=2;			//Right Wall Hugger
			
		if(int0)
			mode=3;			//Line Follower
	}
	
	if(mode==1)
	{
		for(;1;)
		{
			if(leftsensoron && rightsensoron)
			{
				backward();
				_delay_ms(500);
				left();
				_delay_ms(1000);
			}
			else if(leftsensoron)
			{
				right();
				_delay_ms(200);
			}
			else if(rightsensoron)
			{
				left();
				_delay_ms(200);
			}
			else
			{
				forward();
			}
			
			if(leftsensoron)
				led2on;
			else
				led2off;
			
			if(rightsensoron)
				led3on;
			else
				led3off;
		}
	}
	else if(mode==2)
	{
		for(;1;)
		{
			if(rightsensoron)
			{
				rightmotor(255,0);
				leftmotor(0,0);
				_delay_ms(50);
			}
			else
			{
				rightmotor(50,0);
				leftmotor(255,0);
			}
			
			if(leftsensoron)
				led2on;
			else
				led2off;
			
			if(rightsensoron)
				led3on;
			else
				led3off;
		}
	}
	else if(mode==3)
	{
		for(;1;)
		{
			if(leftsensoroff)
				leftmotor(0,0);
			else
				leftmotor(255,0);
			
			if(rightsensoroff)
				rightmotor(0,0);
			else
				rightmotor(255,0);
		}
	}
}

void forward(void)
{
	OCR1A=255;
	OCR1B=255;
	sbi(PORTC,0);
	cbi(PORTC,1);
	sbi(PORTC,2);
	cbi(PORTC,3);	
}

void backward(void)
{
	OCR1A=255;
	OCR1B=255;
	cbi(PORTC,0);
	sbi(PORTC,1);
	cbi(PORTC,2);
	sbi(PORTC,3);
}

void left(void)
{
	OCR1A=255;
	OCR1B=255;
	cbi(PORTC,0);
	sbi(PORTC,1);
	sbi(PORTC,2);
	cbi(PORTC,3);
}

void right(void)
{
	OCR1A=255;
	OCR1B=255;
	sbi(PORTC,0);
	cbi(PORTC,1);
	cbi(PORTC,2);
	sbi(PORTC,3);
}

void breaks(void)
{
	OCR1A=0;
	OCR1B=0;
	sbi(PORTC,0);
	sbi(PORTC,1);
	sbi(PORTC,2);
	sbi(PORTC,3);
}

void stop(void)
{
	OCR1A=0;
	OCR1B=0;
	cbi(PORTC,0);
	cbi(PORTC,1);
	cbi(PORTC,2);
	cbi(PORTC,3);
}

void leftmotor(char speed, char direction)
{
	if(direction)
	{
		cbi(PORTC,0);
		sbi(PORTC,1);
	}
	else
	{
		sbi(PORTC,0);
		cbi(PORTC,1);	
	}
	
	OCR1A=speed;
}

void rightmotor(char speed, char direction)
{
	if(direction)
	{
		cbi(PORTC,2);
		sbi(PORTC,3);
	}
	else
	{
		sbi(PORTC,2);
		cbi(PORTC,3);	
	}
	
	OCR1B=speed;	
}

void init(void)
{
	sbi(DDRC,0);			//MOTOR1 +
	sbi(DDRC,1);			//MOTOR1 -
	sbi(DDRC,2);			//MOTOR2 +
	sbi(DDRC,3);			//MOTOR2 -
	
	cbi(DDRD,6);			//LEFT SENSOR
	cbi(DDRD,7);			//RIGHT SENSOR
	
	sbi(DDRA,4);			//LED1
	sbi(DDRA,5);			//LED2
	sbi(DDRA,6);			//LED3
	sbi(DDRA,7);			//LED4
	
	cbi(DDRB,2);			//INT2 switch
	sbi(PORTB,2);
	cbi(DDRD,1);			//SW1 switch
	sbi(PORTD,1);
	cbi(DDRD,2);			//INT0 switch
	sbi(PORTD,2);
	cbi(DDRD,3);			//INT1 switch
	sbi(PORTD,3);	
	
	sbi(DDRD,4);			//PWM Pin for right motor
	sbi(DDRD,5);			//PWM Pin for left motor
	
    sbi(TCCR1A,WGM10);		//PWM timer1 config
	sbi(TCCR1A,COM1A1);
	sbi(TCCR1A,COM1B1);
	sbi(TCCR1B,CS11);
	sbi(TCCR1B,WGM12);
}
