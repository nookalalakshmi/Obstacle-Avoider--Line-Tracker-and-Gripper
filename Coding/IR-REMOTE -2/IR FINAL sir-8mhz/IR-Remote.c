
/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
/*----------------------------------------------------------------
-----------------GLOBAL VARIABLE----------------------------------
-----------------------------------------------------------------*/

//static volatile uint8_t led; 					// use volatile when variable is accessed from interrupts
//static volatile int oneSec=0;
static volatile char irDt=0;
static volatile int c3p5=0;
static volatile int c131=0;
static volatile char irMode=0;
static volatile char d=0;
static volatile char d_old=0;
static volatile int cmd=0;
static volatile char speed=220;
static volatile int detectline=0;
static volatile char pathfound=0;
static volatile char flag=0;
static volatile int fwdrestrict=0;

static volatile int startcount=0;
char timercount=0;
int stopcount=0;
int backflag=0;



/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/
//#define TMC8_CK8	(_BV(CS22))	// 8 BIT TIMER2 AT 256 PRESCALAR
#define TMC8_CK8	(_BV(CS21))	// 8 BIT TIMER2 AT 8 PRESCALAR
												// GIVES 8*64 = 512 CYCLES
												// AT 8MHZ FREQUENCY  = 0.125 microSECONDS/cycle
												
#define TIMER_2_CNT     191  // 64 micro sec, use AVRcalc to calculate these values
								// MAX VALUE = 255 and up counting from 191
								// TIMER OVERFLOW ON 255-191 = 64 COUNTS



/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
void command(void);
void remote_decoder(void);
void path_detector(void);
void direction_motor(int detectline);


SIGNAL(SIG_OVERFLOW2)            	// signal handler for tcnt2 overflow interrupt
{//every 72.463usec here
	c3p5++;
	c131++;

    remote_decoder();
	TCNT2 = TIMER_2_CNT;         	// reset counter to get this interrupt again
	
}


void speed_implement(char direction,char value)
{
	//This function will take value as speed and direction and will implement accordingly
	char i=0;
	
	while(TCNT2< 250)
	{
		for(i=0;i<255-value;i++)
		{
			PORTB=0x00;
		}
		for(i=0;i<value;i++)
		{
			PORTB=direction;
			//PORTB=0x04;
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
				PORTB=direction;
				//speed_implement(direction,speed);
				return;
		case 2:	//right
				direction=0x41;
				pathfound=1;
				PORTB=direction;
				//speed_implement(direction,speed);
				return;
		case 3:	//left
				direction=0x82;
				pathfound=1;
				PORTB=direction;
				//speed_implement(direction,speed);
				return;
		case 4:	//stop
				direction=0x00;
				flag=1;
				PORTB=direction;
				//speed_implement(direction,speed);
				return;
		case 5: //left from center
				direction=0x02;
				PORTB=direction;
				//speed_implement(direction,speed);
				return;
		
		case 6:	//right from center
				direction=0x40;
				PORTB=direction;
				//speed_implement(direction,speed);
				return;
		
		case 7:	//reverse
				direction=0x42;
				PORTB=direction;
				//speed_implement(direction,speed);
				return;
	}
}

void remote_decoder(void)
{
	d=bit_is_clear(PIND,6);
	if(irMode==0)
	{
		if(d==1)
		{
			irMode=1;
		}
		if(c131>8)
		{
			cmd=64;
		}
		return;
	}
	if(irMode==1)
	{
		if(d==0)
		{
			irMode=2;
		}
		return;
	}
	if(irMode==2)
	{
		if(d==1)
		{
			irMode=3;
			c3p5=0;
			irDt=0;
		}
		return;
		
	}
	if(irMode==3)
	{
		if(c3p5>16)
		{
			d_old=d;
			irDt=irDt<<1;
			irDt=irDt+d;
			irMode=4;
		}
		return;
	}
	if(irMode==4)
	{
		if(d_old!=d)
		{
			d_old=d;
			irMode=3;
			c3p5=0;
		}
		if(c3p5>49)
		{
			irMode=0;
			irDt=irDt>>1;
			irDt=255-irDt;
			cmd=irDt & 0x3f;
			c131=0;
		}
		return;
	}
}

void command(void)
{
switch (cmd)
		{
			case 0:
				PORTB=0x00;
				return;
			case 1:
				speed=255;
				return;
			case 2:
				speed=150;
				return;
			case 3:
				speed=100;
				return;
			case 4:
				speed=50;
				return;
			case 7:
				//path_detector();
				return;
			case 8:
				return;
			case 32:
				//direction_motor(1);
				PORTB=0x81;
				return;
			case 33:
				//direction_motor(7);
				PORTB=0x42;
				return;
			case 16:
				//direction_motor(2);
				PORTB=0x41;
				return;
			case 17:
				//direction_motor(3);
				PORTB=0x82;
				return;
			case 64:
				return;
		}
}



/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
    char i=0;
	DDRD=0x0F;						//SET DATA DIRECTION REGISTER
	DDRC=0x30;						//SET 1 for OUTPUT PORT
	DDRB = 0xC7;					//SET 0 FOR INPUT PORT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	TCCR2 = TMC8_CK8;               	
    TCNT2  = TIMER_2_CNT;        	// reset TCNT1
     TIMSK  = _BV(TOIE2);         	// enable TCNT1 overflow 
    
    sei();                       	// enable interrupts
	
	for(;;)
	{	
		command();
		if(cmd!=7)
		{
			startcount=0;
			cbi(PORTC,4);
		}
	}
	
return 0;

}
