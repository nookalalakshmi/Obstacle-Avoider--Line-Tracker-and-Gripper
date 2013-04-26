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
int odetect=0;
int ldetect=0;
static volatile int detectline=0;
char timercount=0;
int stopcount=0;

int backflag=0;
int startcount=0;

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
	
	DDRC=0x30;
	

	
    char i=0;
     
	                       	// disable interrupts
	navflag = 'S';
	cbi(PORTC,4);
	cbi(PORTC,5);
	
	while(1)						//INFINITE LOOP
	{
		direction_motor(1);
		for(i=0;i<5;i++)
		{
				_delay_ms(2);
				sbi(PORTC,5);
				_delay_ms(2);
				if(bit_is_clear(PIND,2))
				{
					sbi(PORTB,2);
					odetect++;
				}
				else
				{
					cbi(PORTB,2);
				}
				if(odetect>6)
				{
					
					odetect=0;
					direction_motor(4);
					_delay_ms(40000);
					direction_motor(3);
					_delay_ms(10000);
					direction_motor(1);
				}
				
				/*if(bit_is_clear(PINC,0))
				{
					sbi(PORTB,2);
					ldetect++;
				}
				else
				{
					cbi(PORTB,2);
				}
				if(ldetect>6)
				{
					ldetect=0;
					direction_motor(4);
					_delay_ms(40000);
					while(bit_is_clear(PINC,0))
					{
						direction_motor(2);
						
					}
					direction_motor(1);
	
				}*/
				_delay_ms(2);
				cbi(PORTC,5);
				_delay_ms(2);
				
				if(bit_is_clear(PIND,2))
				{
					sbi(PORTB,2);
					odetect++;
				}
				else
				{
					cbi(PORTB,2);
				}
				/*if(bit_is_clear(PINC,0))
				{
					sbi(PORTB,2);
					ldetect++;
				}
				else
				{
					cbi(PORTB,2);
				}*/
				if(odetect>6)
				{
					
					odetect=0;
					direction_motor(4);
					_delay_ms(40000);
					direction_motor(3);
					_delay_ms(10000);
					direction_motor(1);
				}
				
				/*if(ldetect>6)
				{
					ldetect=0;
					direction_motor(4);
					_delay_ms(40000);
					while(bit_is_clear(PINC,0))
					{
						direction_motor(2);
						
					}
					direction_motor(1);
	
				}*/
		}
		odetect=0;
		ldetect=0;
		_delay_ms(100);
		
	}
	return(0);
}