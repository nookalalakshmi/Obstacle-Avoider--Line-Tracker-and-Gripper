
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
static volatile char speed=200;
static volatile int detectline=0;
static volatile char pathfound=0;
static volatile char flag=0;
static volatile int fwdrestrict=0;
static volatile char direction=0;
static volatile int startcount=0;
static volatile char pathfollower=0;
char timercount=0;
int stopcount=0;
int backflag=0;
static volatile int pathmode=0;
static volatile int obsavoid=0;
static volatile int irobs=0;
static volatile int irdelay=0;
static volatile int leftjam=0;
static volatile int timerontime=0;
static volatile int rightjam=0;
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



SIGNAL(SIG_OVERFLOW2)            	// signal handler for tcnt2 overflow interrupt
{//every 72.463usec here
	
	c3p5++;
	c131++;
	pathmode++;
	remote_decoder();
	TCNT2 = TIMER_2_CNT;         	// reset counter to get this interrupt again
	
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
				direction=0x00;
				pathfollower=0;
				obsavoid=0;
				speed=0;
				return;
			case 1:
				direction=0x00;
				pathfollower=0;
				obsavoid=0;
				speed=255;
				return;
			case 2:
				direction=0x00;
				pathfollower=0;
				obsavoid=0;
				speed=215;
				return;
			case 3:
				direction=0x00;
				pathfollower=0;
				obsavoid=0;
				speed=190;
				return;
			case 4:
				direction=0x00;
				pathfollower=0;
				obsavoid=0;
				speed=160;
				return;
			case 7:
				flag=0;
				backflag=0;
				obsavoid=0;
				pathfollower=1;
				speed=210;
				sbi(PORTC,4);
				return;
			case 8:
				pathfollower=0;
				cbi(PORTC,4);
				obsavoid=0;
				speed=0;
				direction=0x00;
				return;
			case 9:
				pathfollower=0;
				obsavoid=1;
				speed=0;
				direction=0x00;
				return;
			case 32:
				//direction_motor(1);
				pathfollower=0;
				obsavoid=0;
				direction=0x81;
				return;
			case 33:
				//direction_motor(7);
				pathfollower=0;
				obsavoid=0;
				direction=0x42;
				return;
			case 16:
				//direction_motor(2);
				pathfollower=0;
				obsavoid=0;
				direction=0x41;
				return;
			case 17:
				//direction_motor(3);
				pathfollower=0;
				obsavoid=0;
				direction=0x82;
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
		sbi(PORTB,2);
		/*if(obsavoid==0)
		{
			if(speed!=0)
			{
				for(i=0;i<255-speed;i++)
				{
					PORTB=0x00;
				}
				for(i=0;i<speed-10;i++)
				{
					PORTB=direction;
				}
			}
			else
			{
				PORTB=direction;
			}
		}*/
		if(obsavoid==1)	//enter obstacle avoider mode
		{
			cbi(PORTB,2);
			TIMSK=0x00;			//disable timer
			while(1)						//INFINITE LOOP
			{
				fwdrestrict++;
				PORTB=0x81;	//Forward
				for(i=0;i<5;i++)
				{
				
					_delay_ms(10);
					sbi(PORTC,5);		//enable obstacle avoid
					_delay_ms(10);
					
					if(bit_is_clear(PIND,2))
					{
						//sbi(PORTB,2);
						fwdrestrict=0;
						
						while(bit_is_clear(PIND,2))		//front obstacle
						{
							PORTB=0x82;		//Left
							//sbi(PORTB,2);
							leftjam++;
							if(leftjam==1000)
							{
								PORTB=0x42;
								//sbi(PORTB,2);
								_delay_ms(3000);
								PORTB=0x82;
								//sbi(PORTB,2);
							}
						}
						_delay_ms(2000);
						PORTB=0x81;		//Forward
			
						//_delay_ms(10);
						
					}
					else
					{
						cbi(PORTB,2);
					}
					if(bit_is_clear(PINC,0))		//left obstacle
					{		
						//sbi(PORTB,2);
						fwdrestrict=0;
						
						while(bit_is_clear(PINC,0)) //left obstacle
						{
							PORTB=0x41;		//right
							//sbi(PORTB,2);
							rightjam++;
							if(rightjam==1000)
							{
								PORTB=0x42;
								//sbi(PORTB,2);
								_delay_ms(3000);
								PORTB=0x41;
								//sbi(PORTB,2);
							}
						}
						_delay_ms(2000);
						PORTB=0x81;		//Forward
			
						//_delay_ms(10);
						
					}
					else
					{
						cbi(PORTB,2);
					}
					
					
					_delay_ms(10);
					cbi(PORTC,5);
					_delay_ms(10);
					
					
				}
			
				_delay_ms(50);
				if(fwdrestrict==300)
				{
					PORTB=0x42;
					_delay_ms(6000);
					PORTB=0x02;
					_delay_ms(5000);
					PORTB=0x81;
					fwdrestrict=0;
				}
			}	
		}
		
	}
	
return 0;

}
