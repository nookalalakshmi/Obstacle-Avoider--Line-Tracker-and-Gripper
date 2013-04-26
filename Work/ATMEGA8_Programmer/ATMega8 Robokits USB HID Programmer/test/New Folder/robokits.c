

#include <avr/io.h>
#include <avr/interrupt.h>
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY


static volatile uint8_t led; 					// use volatile when variable is accessed from interrupts
int volatile pw=100,count=0;

/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/


void spi_masterinit(void)
{
	DDRB=0x28;
	SPCR=0x51;

}
void master_transmit(char cdata)
{
	SPDR=cdata;
	while(!(SPSR &&(1<<SPIF)));
}
	     	

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
   
	
	cbi(PORTC,6);

	cbi(PORTB,5);
	
	_delay_ms(20);
	
	spi_masterinit();
	while(1)
	{		
			master_transmit(0xAC);
			master_transmit(0x53);
			master_transmit(0x00);
			master_transmit(0x11);
			master_transmit(0x32);
			master_transmit(0x32);
			master_transmit(0x32);
			master_transmit(0x32);
			master_transmit(0x32);
	}
	
}
