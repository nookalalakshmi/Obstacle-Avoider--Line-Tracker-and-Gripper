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

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include<avr/io.h>					//HEADER FILE FOR AVR INPUT OUTPUT
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY

#include <avr/interrupt.h>

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------/
-----------------------------------------------------------------*/
//***************************************
void motormove(char motor, char state)
{
	int n1=0,n2=0;
	if(motor=='1')
	{
		n1=7;
		n2=6;
	}
	if(motor=='2')
	{
		n1=0;
		n2=1;
	}
	switch (state)
	{
	 case 'F':
			sbi(PORTB,n1);
			cbi(PORTB,n2);
			break;

	case 'B':
			sbi(PORTB,n2);
			cbi(PORTB,n1);
			break;

	
	case 'S':
			cbi(PORTB,n2);
			cbi(PORTB,n1);
			break;

	case 's':
			cbi(PORTB,n1);
			cbi(PORTB,n2);
			break;
	}	
}
//***************************************
void robotmove(char mode)
{

	switch(mode)
	{
		case 'F':
		 motormove('1','F');
		 motormove('2','F');
		break;
		
		case 'B':
		 motormove('1','B');
		 motormove('2','B');
		break;
		
		case 'L':
		 motormove('1','B');
		 motormove('2','F');
		break;
		
		case 'R':
		 motormove('1','F');
		 motormove('2','B');
		break;
		
		case 's':
		 motormove('1','s');
		 motormove('2','s');
		break;
		
		case 'S':
		 motormove('1','S');
		 motormove('2','S');
		break;
	}
}
//***************************************
SIGNAL(SIG_INTERRUPT0)     
/* signal handler for external interrupt int0 */
{           
//            navflag='O';
//            robotmove('S');
			sbi(PORTB,2);			//LED ON
}

			
int main(void)
{
	char tbl[8]={'s','F','S','B','s','L','S','R'};
	int m=0;
	DDRB=0xC7;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTB.0 IS OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	
	DDRD=0xF1;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTD.7 AND PORTD.6 ARE OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE	
									
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1
    GICR = _BV(INT0);           	// enable external int0
    MCUCR = _BV(ISC01);          	// falling egde: int0*/
    sei();                       	// enable interrupts 
									
 
		_delay_ms(1000);					//DELAY IN MILLISECONDS 
										//PARAMETER PASSED SHOULD NOT EXCEED 262.14MS / F_CPU IN MHZ
										//F_CPU IS DEFINED IN MAKEFILE
										//SO FOR 16MHZ SPEED THE MAXIMUM PARAMETER SHOULD BE 16MS
										//FOR 1MHZ IT CAN BE UPTO 262MS (250 IS USED FOR THIS EXAMPLE)
										//SEE AVR LIBC USER MANUAL FOR MORE DETAIL.
	while(1)						//INFINITE LOOP
	{
		
		_delay_ms(1000);	
		robotmove(tbl[m]);
		robotmove(tbl[m]);
		m++;
		m=m & 7;
		cbi(PORTB,2);	
	}
	return(0);
}

