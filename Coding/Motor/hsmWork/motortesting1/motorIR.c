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
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI

/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/

static volatile uint8_t led;     // use volatile when variable is accessed from interrupts
//static char volatile navflag='S';

/*----------------------------------------------------------------
-----------------FUNCTION-----------------------------------------
-----------------------------------------------------------------*/


//SIGNAL(SIG_INTERRUPT0)     
/* signal handler for external interrupt int0 */
//{           
          //  navflag='O';
          //  robotmove('S');
			//sbi(PORTB,2);			//LED ON
            
        
//}

void motormove(char motor,char state)
{
	
	int n1,n2;
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

void robotmove(char mode)
{
	_delay_ms(1000);
	cbi(PORTB,2);
	
	switch (mode)
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
		
		case 'S':
		 motormove('1','s');
		 motormove('2','s');
		break;
	}
	
}



/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{    
	DDRB=0XC7;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PB.2 IS  INPUT
									//ALL OTHERS ARE OUTPUT
	
	DDRD=0XF1;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PD.1, PD.2 AND PD.3 ARE INPUT
									//ALL OTHERS ARE OUTPUT

	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1
    /*GICR = _BV(INT0);           	// enable external int0
    MCUCR = _BV(ISC01);          	// falling egde: int0
    sei();                       	// enable interrupts */
		
		sbi(PORTB,2);
        //robotmove('S');
			//motormove('1','s');
		//	motormove('2','s');
			
		//cbi(PORTB,2);			//LED ON
		
		_delay_ms(2000);
		cbi(PORTB,2);			//LED OFF
        //robotmove('F');
		motormove('1','F');
		 motormove('2','F');
		_delay_ms(5000);
		//sbi(PORTB,2);
	/*	_delay_ms(2000);
		robotmove('B');
		_delay_ms(2000);
		robotmove('S');
		_delay_ms(2000);
		robotmove('L');
		_delay_ms(2000);
		robotmove('R');
		_delay_ms(2000);
		robotmove('S');*/
		
	/*	cbi(PORTB,7);
	sbi(PORTB,6);
		cbi(PORTB,0);
		sbi(PORTB,1);*/
		
		
	//sbi(PORTB,2);
    for (;;) 					 	//BLINK LED2
	{	
   /* switch(navflag)
    {
        case 'O':
            robotmove('B');
            _delay_ms(2000);
            _delay_ms(2000);
            robotmove('L');
            _delay_ms(5000);
            robotmove('F');
            navflag='F';
        break;
        
        case 'F':
        
        break;
    }*/
	
		
	}                  				// loop forever   
}
