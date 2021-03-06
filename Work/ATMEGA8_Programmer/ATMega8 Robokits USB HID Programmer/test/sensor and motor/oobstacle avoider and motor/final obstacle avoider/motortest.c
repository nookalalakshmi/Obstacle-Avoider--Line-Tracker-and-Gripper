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

//************** CONSTANTS ********************
//#define cnt0            0x00
/*#define TIMER_0_CNT     0x37  		// 204 ms sec, use AVRcalc to calculate these values
									// TIMER OVERFLOW ON 255-55 = 200 COUNTS
#define TIMER_0_CNT1   	0xB1
#define CNT             0xfc
#define TMC8_CK1024	(_BV(CS02)+_BV(CS00))	// 8 BIT TIMER0 AT 1024 PRESCALAR
												// GIVES 1024*200 = 204800 CYCLES
												// AT 1MHZ FREQUENCY DELAY OF 204 mSECONDS*/

//#define TIMER_1_CNT		0xB3B3						//20 seconds
												//TIMER OVERFLOW AT 65535-46003=19532
#define TIMER_1_CNT			0xD9D9
#define TMC16_CK1024 (_BV(CS12)+_BV(CS10))		//16 BIT TIMER1 at 1024 PRESCALAR
												//GIVES 1024*19532= 20000768 cycles
												//AT 1MHZ FREQUENCY DELAY OF 20 seconds
//************** FUNCTIONS ********************
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
		
		case 'R':
		 motormove('1','B');
		 motormove('2','s');
		break;
		
		case 'L':
		 motormove('1','s');
		 motormove('2','B');
		break;
		
		case 'r':
		 motormove('1','B');
		 motormove('2','F');
		break;
		
		case 'l':
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
void obstacleL(void)
{
	sbi(PORTB,2);
	robotmove('B');
	_delay_ms(300);
	robotmove('r');
	_delay_ms(500);

}
void obstacle(void)
{
            robotmove('S');
			_delay_ms(100);
			sbi(PORTB,2);			//LED ON
			robotmove('B');
			_delay_ms(500);
			if(bit_is_clear(PINC,0))
			{
				obstacleL();
			}
			navflag='O';
}


//************** INTERRUPT0 ********************
SIGNAL(SIG_INTERRUPT0)     
{//signal handler for external interrupt int0           
            obstacle();
			

}

//************** TIMER0 INTERRUPT ********************
SIGNAL(SIG_OVERFLOW1)            	// signal handler for tcnt1 overflow interrupt
{//re-enter every 204 mSec here
	//TCNT0 = TIMER_0_CNT; //reload this counter
	robotmove('S');
	_delay_ms(200);
	robotmove('B');
	_delay_ms(1000);
	robotmove('L');
	_delay_ms(300);
	robotmove('F');
	TCNT1 = TIMER_1_CNT;	
}
//************** MAIN PROGRAM ********************
int main(void)
{
	//char tbl[8]={'s','F','S','B','s','L','S','R'};
//	int m=0;
	
	DDRB=0xC7;						//SET DATA DIRECTION REGISTER
	DDRD=0xF1;						//SET DATA DIRECTION REGISTER
	
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	//sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1
    GICR = _BV(INT0);           	// enable external int0
    MCUCR = _BV(ISC01);          	// falling egde: int0*/
    sei();                       	// enable interrupts 
									
    TCCR1B = TMC16_CK1024;       		// use CLK/1024 prescale value
    //TCNT0  = 0x00;        			// reset TCNT0
    TIMSK  = _BV(TOIE1);        	// enable TCNT0 overflow 
 
	navflag = 'S';
	_delay_ms(1000);				//DELAY IN MILLISECONDS 
	robotmove('F');
	TCNT1=TIMER_1_CNT;
	while(1)						//INFINITE LOOP
	{
		if(navflag=='O')
		{
			if (bit_is_clear(PIND,2))	//IF Sensor1 senses obstacle
			{
				robotmove('l');
				cli();                       	// disable interrupts 
				_delay_ms(500);
				sei();                       	// enable interrupts 
				        			
				//count = 0;
				//navflag='S';
				TCNT1 = TIMER_1_CNT;			// reset TCNT0
			}
			else if(bit_is_clear(PINC,0))
			{
				obstacleL();
				cbi(PORTB,2);
			}
			else 
			{
				//if(move=='F')
				
					cbi(PORTB,2);
					robotmove('F');
			}
		}
		
//		m++;
//		m=m & 7;
			
	}
	return(0);
}