
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

/*----------------------------------------------------------------
-----------------HEADER FILES & CONSTANTS-------------------------
-----------------------------------------------------------------*/

#include<avr/io.h>					//HEADER FILE FOR AVR INPUT OUTPUT
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY

int count=0;
int flag=0;
#define TMC8_CK1024	((_BV(CS00)) + (_BV(CS02)))	// 16 BIT TIMER1 AT 1024 PRESCALAR
												// GIVES 8*31250 = 250000 CYCLES
												// AT 8MHZ FREQUENCY DELAY OF 31.25 mSECONDS

/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
void pathfinder(void);
void motormove(char ,char );
void robotmove(char );
void path_follower_motor(void);


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
void path_follower_motor(void)
{
	
	if((bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)))
	{
		/*sbi(PORTD,2);
		cbi(PORTD,3);*/	//move left
		do
		{
			robotmove('L');
		}while(PORTC!=0x06);
		robotmove('L');
	}
	if((bit_is_clear(PINC,2)) && (!bit_is_clear(PINC,1)))
	{
		/*sbi(PORTD,3);
		cbi(PORTD,2);*/	//move right
		do
		{
			robotmove('R');
		}while(PORTC!=0x06);
		robotmove('F');
	}
	if((!bit_is_clear(PINC,1)) && (!bit_is_clear(PINC,2)))
	{
		/*sbi(PORTD,2);
		sbi(PORTD,2);	*/ //move forward
		do
		{
			robotmove('F');
		}while(PORTC!=0x06);
		robotmove('F');
	}
	if((bit_is_clear(PINC,1)) && (bit_is_clear(PINC,2)))
	{
		/*cbi(PORTD,2);
		cbi(PORTD,3);	*/ //stop
		robotmove('S');
		pathfinder();
	}
	
}

void pathfinder(void)
{		
		robotmove('L');
		_delay_ms(1000);
		robotmove('S');
		_delay_ms(1000);
	
		count=0;
		while(count<=5)
		{
			TCNT0=0;
			while(TCNT0<=255)
			{
				robotmove('F');
				if((!bit_is_clear(PINC,1)) || (!bit_is_clear(PINC,2)))
				{
					while(!(bit_is_clear(PINC,1) && bit_is_clear(PINC,2)))
					{
						path_follower_motor();
						flag=1;
					}
				}
			}
			count++;
		}
		
		robotmove('R');
		_delay_ms(2000);
		robotmove('S');
		_delay_ms(1000);
		
		count=0;
		while(count<=10)
		{
			TCNT0=0;
			while(TCNT0<=255)
			{
				robotmove('F');
				if((!bit_is_clear(PINC,1)) || (!bit_is_clear(PINC,2)))
				{
					while(!(bit_is_clear(PINC,1) && bit_is_clear(PINC,2)))
					{
						path_follower_motor();
						flag=1;
					}
				}
			}
			count++;
		}
		
		robotmove('L');
		_delay_ms(2000);
		robotmove('S');
		_delay_ms(1000);
	
		count=0;
		while(count<=5)
		{
			TCNT0=0;
			while(TCNT0<=255)
			{
				robotmove('F');
				if((!bit_is_clear(PINC,1)) || (!bit_is_clear(PINC,2)))
				{
					while(!(bit_is_clear(PINC,1) && bit_is_clear(PINC,2)))
					{
						path_follower_motor();
						flag=1;
					}
				}
			}
			count++;
		}
		
		robotmove('R');
		_delay_ms(1000);
		robotmove('S');
		_delay_ms(1000);
		
		count=0;
		while(count<=33)
		{
			TCNT0=0;
			while(TCNT0<=255)
			{
				robotmove('B');
				if((!bit_is_clear(PINC,1)) || (!bit_is_clear(PINC,2)))
				{
					while(!(bit_is_clear(PINC,1) && bit_is_clear(PINC,2)))
					{
						path_follower_motor();
						flag=1;
					}
				}
			}
			count++;
		}
		
		if(flag == 0)
		{ 
			sbi(PORTB,2); //no path found
		}
		else
		{
			cbi(PORTB,2);
		}
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
	DDRB = 0xC2;
	
	TCCR0=TMC8_CK1024;
	TIMSK=0x00;
	
	for(;;)
	{
		pathfinder();
	}
	return(0);
}