

#include <avr/io.h>
#include <avr/interrupt.h>
#include<compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI
#include<util/delay.h>				//HEADER FILE FOR DELAY


static volatile uint8_t led; 					// use volatile when variable is accessed from interrupts
int volatile pw=100,count=0;
char a,b,c='d';
/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/


void spi_slaveinit(void)
{
	DDRB=0x10;
	SPCR=0x40;

}
char slave_recieve(void)
{
	while(!(SPSR & (1<<SPIF)));
		sbi(PORTD,6);
		return SPDR;
		
}
	     	

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
   
	
		
	spi_slaveinit();
	while(1)
	{
		if(bit_is_clear(PINC,6))
		{
		 a= slave_recieve();
		 b= slave_recieve();
		 c= slave_recieve();
		 if(c!='d')
		 {
			 sbi(PORTD,7);
		 }
		}

	}
	
}
