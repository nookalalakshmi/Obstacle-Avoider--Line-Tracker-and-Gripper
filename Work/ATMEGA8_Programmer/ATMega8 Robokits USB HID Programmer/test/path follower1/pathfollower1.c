
//			MADE BY ANKIT-LAKSHMI
//			PROGRAM FOR PATH FOLLOWER

/*-------------------------------------------------------------------          
 Description:
 The robot will follow a 'black' path near which it is placed. In 
 situations where it goes out of track, the indicator LEDs will tell 
 the direction to move to get back its path.
 
 Note:
  _delay_ms() function parameter passed should not exeed
 262.14ms / F_CPU in mhz.
 so for 16MHz the maximum paramer should be 16ms.
 
 For 1MHz it can be upto 262ms (250 is used for this example).
  
 Must be changed to get accurate delay at higher MHz.
 
 The timing will differ if the operating frequency is changed.
---------------------------------------------------------------------*/

/*--------------------------------------------------------------------
-----------------HEADER FILES AND CONSTANTS---------------------------
----------------------------------------------------------------------*/

#include<avr/io.h>					//HEADER FILE FOR AVR INPUT OUTPUT
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY

#define TIMER_1_CNT     0xfc2e						// 1 sec, use AVRcalc to calculate these values
													// ((TCNT1H=0xfc, TCNT1L=0x2e)
													// DECIMAL VALUE = 64558
													// MAX VALUE = 65535
													// TIMER OVERFLOW ON 65535-64558 = 977 COUNTS

#define TMC16_CK1024	(_BV(CS10) + _BV(CS12))		// 16 BIT TIMER1 AT 1024 PRESCALAR
													// GIVES 1024*977 = 1000448 CYCLES
													// AT 1MHZ FREQUENCY DELAY OF 1.000448 SECONDS

int history[4][7];
int hist_write=0;
int hist_read=0;
int reading[7]={0,0,0,0,0,0,0};
int sensor_led=0;
/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
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
		
		case 'S':
		 motormove('1','s');
		 motormove('2','s');
		break;
	}
}

void path_follower(void)
{
	
	if((bit_is_clear(PINC,1)) || (bit_is_clear(PINC,2)))
	{
		/*sbi(PORTD,2);
		cbi(PORTD,3);	//move left */
		
		do
		{
			robotmove('L');
		}while(PORTC!=0x3C);
	}
	
	if((bit_is_clear(PINC,4)) || (bit_is_clear(PINC,5)))
	{
		/*sbi(PORTD,3);
		cbi(PORTD,2);	//move right */
		
		do
		{
			robotmove('R');
		}while(PORTC!=0x3C);
	}
	
	if((bit_is_clear(PINC,1)) && (bit_is_clear(PINC,2)) && (bit_is_clear(PINC,3)) && (bit_is_clear(PINC,4)) && (bit_is_clear(PINC,5)))
	{
		/*sbi(PORTD,2);
		sbi(PORTD,2);	//move forward */
		
		do
		{
			robotmove('F');
		}while(PORTC!=0x3C);
	}
	
	if((!bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)) && (!bit_is_clear(PINC,3)) && (!bit_is_clear(PINC,4)) && (!bit_is_clear(PINC,5)))
	{
		/*cbi(PORTD,2);
		cbi(PORTD,3);	//stop */
		
		robotmove('S');
	}
	
}

//Store history of path sensor by storing last 4 states of the sensor LEDs
SIGNAL(SIG_OVERFLOW1)
{
	if(hist_write==4)
	{
		hist_write=0;
	}
	for(i=0;i<7;i++)
	{
		history[hist_write][i]=;
	}
	TCNT0=;
	hist_write++;
	return;
}

//Read history of the robot path
int* read_history()
{
	if(hist_read==4)
	{
		hist_read=0;
	}
	reading = history[hist_read];
	hist_read++;
	return reading;
}

//Navigate robot according to the history
void navigate_robot(void)
{
	reading = read_history();
	return;
}


/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/
int main(void)
{
	DDRD=0x0F;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTB.0 IS OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	DDRC=0x00;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTD.7 AND PORTD.6 ARE OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
									
//Initialization of history
	for(i=0;i<4;i++)
	{
		for(j=0;j<7;j++)
		{
			history[i][j]=0;
		}
	}
	TCCR1A =TIM16_CK1024;
	TCCR1B = 0x00;
	TIMSK = _BV(TOIE1);
	TCNT0 =TIMER_1_CNT;
	
	sei();
	
	for(;;)
	{
		path_follower();
	}
	return(0);
}