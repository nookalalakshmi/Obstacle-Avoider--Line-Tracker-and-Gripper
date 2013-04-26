/*  
 Since _delay_ms() function will be affected by the interrupt generation 
 and gives more delay. So, after sometime the led timing will be mismached.
 
 Even the timer delay is not perfectly mached to 1s. Use smaller presclar
 for better operation.
 
  _delay_ms() function parameter passed should not exeed
 262.14ms / F_CPU in mhz.
 
 so for 16MHz the maximum paramer should be 16ms.
 
 For 1MHz it can be upto 262ms (250 is used for this example).
  
 Must be changed to get accurate delay at higher MHz.
 
 The timing will differ if the operating frequency is changed.
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
int volatile flag=33,f1=0,c=1,a=0;
int volatile count=0;
int volatile count1=0,count2=0,count3=0,count4;
/*----------------------------------------------------------------
-----------------FUNCTION-----------------------------------------
-----------------------------------------------------------------*/
#define TIMER_1_CNT     0xd48d  // 3 sec, use AVRcalc to calculate these values
                                // ((TCNT1H=0xf4, TCNT1L=0x8d)
								// DECIMAL VALUE = 62605
								// MAX VALUE = 65535
								// TIMER OVERFLOW ON 65535-62605 = 2930 COUNTS
#define TIMER_0_CNT		0x54	//175 ms
								//dec value=84
								//max value=255
								// timer overflow on 255-84=171 counts

#define TIMER_0_CNT2	0x9d	//100ms
								//dec value=157
								//timer overflow on 255-157=98 counts
#define CNT				0xffff
#define TMC16_CK1024	(_BV(CS12)+_BV(CS10))	// 16 BIT TIMER1 AT 1024 PRESCALAR
												// GIVES 1024*2930 = 3000320 CYCLES
												// AT 1MHZ FREQUENCY DELAY OF 3.000320 SECONDS
#define TMC0_CK1024		(_BV(CS02)+_BV(CS00))				//8bit Timer 0 at 1024 prescaler
												//gives 1024*171= 175104 cycles
												//175.104 milliseconds
#define CNT0			0xfc


SIGNAL(SIG_OVERFLOW0)
{
	if(count1!=0)
	{
		if(count1==1)
		{
			TCNT0=TIMER_0_CNT;
			if(bit_is_clear(PIND,6))
				sbi(PORTD,6);
			else
				cbi(PORTD,6);
		}
		else if(count1==2)
		{
			TCNT0=TIMER_0_CNT2;
			if(bit_is_clear(PIND,6))
				sbi(PORTD,6);
			else
				cbi(PORTD,6);

		}
	}
	else if (count2!=0)
	{
		if(count2==1)
		{
			TCNT0=TIMER_0_CNT;
			if(bit_is_clear(PIND,7))
				sbi(PORTD,7);
			else
				cbi(PORTD,7);
		}
		else if(count2==2)
		{
			TCNT0=TIMER_0_CNT2;
			if(bit_is_clear(PIND,7))
				sbi(PORTD,7);
			else
				cbi(PORTD,7);

		}
	}
	else if (count3!=0)
	{
		if(count3==1)
		{
			TCNT0=TIMER_0_CNT;
			if(bit_is_clear(PIND,7) && bit_is_clear(PIND,6))
				{	
					sbi(PORTD,7);
					sbi(PORTD,6);
				}
			else
				{
					cbi(PORTD,7);
					cbi(PORTD,6);
				}
		}
		else if(count3==2)
		{
			TCNT0=TIMER_0_CNT2;
			if(bit_is_clear(PIND,7) && bit_is_clear(PIND,6))
				{
					sbi(PORTD,7);
					sbi(PORTD,6);
				}
			else
				{
					cbi(PORTD,7);
					cbi(PORTD,6);
				}

		}
		
	}
	
}
SIGNAL(SIG_OVERFLOW1)            	// signal handler for tcnt1 overflow interrupt
{
	TCNT1 = TIMER_1_CNT;
	a=0;
	while(a<=2930)
	{
	if(bit_is_clear(PIND,3))
	{
				sbi(PORTD,6);
				sbi(PORTD,7);
				_delay_ms(250);
				cbi(PORTD,6);
				cbi(PORTD,7);
				_delay_ms(250);
				
		
				f1=1;
		
	}
	

	else
	{
				sbi(PORTD,6);
				sbi(PORTD,7);
				_delay_ms(250);
				cbi(PORTD,6);
				cbi(PORTD,7);
				_delay_ms(250);
		f1=0;
		c=0;
	}
	a=a+506;
	}
	
    
}

SIGNAL(SIG_INTERRUPT0)     
/* s  tignal handler for external interrupt int0 */
{

	count++;
	if(count==4)
	{
		count=0;
	}
	_delay_ms(250);
	_delay_ms(250);

}
void flagcal(int f)
{
	
	TIMSK  = _BV(TOIE0);
    TCCR0 = TMC0_CK1024;       	// use CLK/1024 prescale value
    TCNT0  = CNT0;        	// reset TCNT0
	
	
	if(flag==11)
	{
		while(f==1 || f==2)
		{
			sbi(PORTD,7);
				_delay_ms(250);
			cbi(PORTD,7);
		}
	}
	else if(flag==12)
	{
		while(f==1 || f==2)
		{
			sbi(PORTD,6);
				_delay_ms(250);
			cbi(PORTD,6);
		}
	}
	else if(flag==13)
	{
		while(f==1 || f==2)
		{
		}
	}
	TIMSK  = 0x00;
	
}

SIGNAL(SIG_INTERRUPT1)     
/* signal handler for external interrupt int0 */
{
	
	TIMSK  = _BV(TOIE1);
	TCCR1A = 0x00;               	// disable PWM and Compare Output Mode
    TCCR1B = TMC16_CK1024;       	// use CLK/1024 prescale value
    TCNT1  = CNT;        	// reset TCNT1
	
	if(flag==11 || flag==12 || flag==13)
	{
		if(flag==11)
		{
			count1++;
			count2=0;
			count3=0;
			if(count1==3)
			{
				count1=1;
			}
			flagcal(count1);
		}
		else if(flag==12)
		{
			count1=0;
			count2++;
			count3=0;
			if(count2==3)
			{
				count2=1;
			}
			flagcal(count2);
		}
		else if(flag==13)
		{
			count1=0;
			count2=0;
			count3++;
			if(count3==3)
			{
				count3=1;
			}
			flagcal(count3);
		}
		
	}

//	TIMSK  = 0x00;

		

}
	



/*-----------------MAIN PROGRAM-------------------------------------
----------------------------------------------------------------
-----------------------------------------------------------------*/

int main(void)
{    
	DDRB=0x01;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTB.0 IS OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	
	DDRD=0xC0;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//ONLY PORTD.7 AND PORTD.6 ARE OUTPUT
									//CONFIGURE AS PER REQUIREMENT
									//DEFAULT ALL OTHERS ARE INPUT
									//CHANGE ACCORDING TO USE
	
	sbi(PORTB,0);					//LED1 ON (INDICATION FOR READY TO USE)
	
	sbi(PORTD,2);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,3);					//ENABLE PULL UP FOR SW2
    
    GIMSK = _BV(INT1);
    MCUCR = _BV(ISC11);
  // MCUCR=0x00;
	
    
	sei();                       	// enable interrupts 
    
	
    for (;;) 					 	//BLINK LED2
	{	
		sbi(PORTD,6);
		sbi(PORTD,7);
		_delay_ms(250);
		cbi(PORTD,6);
		cbi(PORTD,7);
		_delay_ms(250);
		if(f1==1 && c!=0)
		{
			cbi(PORTD,6);
			cbi(PORTD,7);
			while(bit_is_clear(PIND,3))
			{
				GIMSK = _BV(INT0);
				MCUCR = 0x02;
				

				if(count==1)
				{
					flag=11;
					sbi(PORTD,6);
					cbi(PORTD,7);
					//f1=0;
				}
				
				else if(count==2)
				{
					flag=12;
					sbi(PORTD,7);
					cbi(PORTD,6);
					
				}
				else if(count==3)
				{
					flag=13;
					sbi(PORTD,6);
					sbi(PORTD,7);
					
				}
				
				  else
				{
					flag=10;
					cbi(PORTD,6);
					cbi(PORTD,7);
					
				}

			}				
		}
		TIMSK=0x00;
	GIMSK = _BV(INT1);
	MCUCR = _BV(ISC11);
	
	}
	for(;;)
	{
	}// loop forever   
}

