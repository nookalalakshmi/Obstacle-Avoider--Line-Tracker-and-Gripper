//			Two Motors and a Proximity IR sensor

/*-------------------------------------------------------------------          
 Operation-
 This example shows how to drive two mtors and control the direction
 based on Proximity Sensor output.
 At powerup robot moves forward by moving motor M1 Anti-Clockwise and 
 motor M2 Clockwise. 
 If IR Proxmity sensor detects obstrical then robot
 moves backward for 2 second (motor M1 Clockwise and motor M2 
 Anti-Clockwise) then turns clockwise (motor M1 Clockwise and motor 
 M2 Clockwise) till no obstriction in IR Sensor and then moves forward 
 again.

 1. Robot move forward => motor M1 Anti-Clockwise and motor M2 Clockwise
 2. Robot move backward => motor M2 Anti-Clockwise and motor M1 Clockwise
 3. Robot turn right => motor M1 Anti-Clockwise and motor M2 Anti-Clockwise
 4. Robot turn left => motor M1 Clockwise and motor M2 Clockwise
	

 Description:
 CPU => ATMEGA8-L @8MHz Internal

 Motors- 

  M1 Connected to PB6 and PB7 such that-
  PB6	PB7		M1
  0		0		Stop
  1		0		Move Clockwsi
  0		1		Move Anti-Clockwsi
  1		1		Stop

  M2 Connected to PB6 and PB7 such that-
  PB0	PB1		M2
  0		0		Stop
  1		0		Move Clockwsi
  0		1		Move Anti-Clockwsi
  1		1		Stop

  LED indicator-
  PB2	State
  0		Off
  1		On

  Proximity IR Sensor Input
  PD2(INT0)	State
  0			Obstruction
  1			Clear Path
---------------------------------------------------------------------*/

//************** HEADER FILES ********************
#include<avr/io.h>					//HEADER FILE FOR AVR INPUT OUTPUT
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY
#include <avr/interrupt.h>

//************** GLOBAL VARIABLES ********************
char navflag;
int count = 0;
int fwdrestrict=0;
char pathfound=0;
int flag=0;
char sendsig=0;

//**************Timer CONSTANTS ********************
#define TIMER_0_CNT     0xC0  // 500 micro sec, Timer set at 500 microsec.
                                // ((TCNT0=0xC0))
								// DECIMAL VALUE = 192
								// MAX VALUE = 255
								// TIMER OVERFLOW ON 255-192 = 63 COUNTS
#define TMC8_CK64	(_BV(CS01)+_BV(CS00))	// 8 BIT TIMER0 AT 64 PRESCALAR
											// GIVES 64*63 =  4000 CYCLES	
											// AT 8MHZ FREQUENCY 1 cycle is of 0.125 micro sec.
//************** FUNCTIONS ********************
//***************************************
void speed(char direction,int value)
{
	//This function will take value as speed and direction and will implement accordingly
	int i=0;
	while(TCNT0< 254)
	{
		for(i=0;i<255-value;i++)
		{
			PORTB=0x00;
		}
		for(i=0;i<value;i++)
		{
			PORTB=direction;
		}
	}
	
	return;
}



void direction_motor(int detectline)
{
	//Set the direction and speed according to the line detected
	char direction;
	switch(detectline)
	{
		case 1:	//forward
				direction=0x81;
				pathfound=1;
				speed(direction,200);
				return;
		case 2:	//right
				direction=0x41;
				pathfound=1;
				speed(direction,220);
				return;
		case 3:	//left
				direction=0x82;
				pathfound=1;
				speed(direction,220);
				return;
		case 4:	//stop
				direction=0x00;
				flag=1;
				speed(direction,255);
				return;
		case 5: //left from center
				direction=0x02;
				speed(direction,220);
				return;
		
		case 6:	//right from center
				direction=0x40;
				speed(direction,220);
				return;
		
		case 7:	//reverse
				direction=0x42;
				speed(direction,220);
				return;
	}
}





//************** MAIN PROGRAM ********************
int main(void)
{
	
	DDRB=0xC7;						//SET DATA DIRECTION REGISTER
	DDRD=0xF1;						//SET DATA DIRECTION REGISTER
	
	DDRC=0x20;
	
	
    char i=0;
     
	TCCR0 = TMC8_CK64;       		// use CLK/1024 prescale value
    //TIMSK  = _BV(TOIE0);        	// enable TCNT0 overflow 
	//sei();                       	// enable interrupts
	navflag = 'S';
	cbi(PORTC,5);
	TCNT0=TIMER_0_CNT;
	while(1)						//INFINITE LOOP
	{
		fwdrestrict++;
		PORTB=0x81;	//Forward
		for(i=0;i<5;i++)
		{
				
				_delay_ms(2);
				sbi(PORTC,5);
				_delay_ms(2);
				
				if(bit_is_clear(PIND,2))
				{
					sbi(PORTB,2);
					fwdrestrict=0;
				
					while(bit_is_clear(PIND,2))
					{
						PORTB=0x82;		//Left
					}
					
					PORTB=0x81;		//Forward
					_delay_ms(10);
					
				}
				else
				{
					cbi(PORTB,2);
				}
				
				if(bit_is_clear(PINC,0))
				{
					fwdrestrict=0;
					sbi(PORTB,2);
					
					while(bit_is_clear(PINC,0))
					{
						PORTB=0x41;		//right
					}
					
					PORTB=0x81;		//forward
					_delay_ms(10);
					
				}
				else
				{
					cbi(PORTB,2);
				}
				_delay_ms(2);
				cbi(PORTC,5);
				_delay_ms(2);
				
				if(bit_is_clear(PIND,2))
				{
					sbi(PORTB,2);
					fwdrestrict=0;
					while(bit_is_clear(PIND,2))
					{
						PORTB=0x82;		//Left
					}
					
					PORTB=0x81;		//Forward
					_delay_ms(10);
					
				}
				else
				{
					cbi(PORTB,2);
				}
				if(bit_is_clear(PINC,0))
				{
					sbi(PORTB,2);
					fwdrestrict=0;
					while(bit_is_clear(PINC,0))
					{
						PORTB=0x41;		//right
					}
					PORTB=0x81;		//forward
					_delay_ms(10);
					
				}
				else
				{
					cbi(PORTB,2);
				}
				
		}
		_delay_ms(100);
		if(fwdrestrict==1000)
		{
			PORTB=0x42;
			_delay_ms(2000);
			PORTB=0x02;
			_delay_ms(2000);
			PORTB=0x81;
			fwdrestrict=0;
		}
		
	}
	return(0);
}