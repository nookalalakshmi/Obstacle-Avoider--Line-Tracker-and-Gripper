/*  

*/
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

/*----------------------------------------------------------------
-----------------GLOBAL VARIABLES-------------------------------------
-----------------------------------------------------------------*/
//#define TMC8_CK8	(_BV(CS22))	// 8 BIT TIMER2 AT 256 PRESCALAR
#define TMC8_CK8	(_BV(CS01))	// 8 BIT TIMER2 AT 8 PRESCALAR
												// GIVES 8*64 = 512 CYCLES
												// AT 8MHZ FREQUENCY  = 0.125 microSECONDS/cycle
												
#define TIMER_2_CNT     19  // 64 micro sec, use AVRcalc to calculate these values
								// MAX VALUE = 255 and up counting from 191
								// TIMER OVERFLOW ON 255-191 = 64 COUNTSd
/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
SIGNAL(SIG_OVERFLOW0)     // signal handler for tcnt2 overflow interrupt
{//every 70.721usec here
sbi(PORTB,2);
	TCNT0 = TIMER_2_CNT;
}

/*----------------------------------------------------------------
-----------------MAIN-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
	//DDRA=0x00;			//set port A as input port all bits.
	//DDRC=0xFF;			//Set Port C as output port all bits.
	
	DDRC=0x00;			//Set Port C as input port all bits.
	DDRB=0XC7;			//SET DATA DIRECTION REGISTER
	DDRD=0XF1;			//SET DATA DIRECTION REGISTER
	
	
	TIMSK  = _BV(TOIE0);         	// enable TCNT1 overflow 
	TCCR0 = TMC8_CK8;               	
    TCNT0  = TIMER_2_CNT;        	// reset TCNT1
    
   sei();                       	// enable interrupts
	for(;;)
	{
	}
	
	return 0;
}
//********************************************
