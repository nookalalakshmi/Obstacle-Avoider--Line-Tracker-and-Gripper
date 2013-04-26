

#include<avr/io.h>					
//#include<compat/deprecated.h>		
#include<util/delay.h>				


int main(void)
{
	DDRB=0x00;						
	
	DDRD=0xc0;						
									

	while(1)						//INFINITE LOOP
	{
		
		sbi(PORTD,6);
		cbi(PORTD,6);
	}
	return(0);
}

