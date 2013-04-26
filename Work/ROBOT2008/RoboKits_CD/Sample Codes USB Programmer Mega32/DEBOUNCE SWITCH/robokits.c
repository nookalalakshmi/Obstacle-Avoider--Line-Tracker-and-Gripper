//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR DEBOUNCE
//			WRITTEN FOR ROBOGRID

/*-------------------------------------------------------------------          
 Description:
 This example shows how to debounce a switch input.
 The switch used is labled sw1 on the board.
 Press it continuously and check status of led2.

 Note:
 In certain application debouncing input is required for changing the
 counts at lower speed than the controller frequency.
 
 Even if you want only one increment the counts will be incremented
 several times.
 
 Here wait_debounce function will debounce sw1.
 
 Press sw1 constantly. Led1 will toggle after every 65535 counts.

 Change i variable as per requirement. 
 
 The timing will differ if the operating frequency is changed. 
---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include <avr/io.h>
#include <compat/deprecated.h>		//HEADER FILE FOR FUNCTIONS LIKE SBI AND CBI

/*----------------------------------------------------------------
-----------------FUNCTION PROTOTYPES------------------------------
-----------------------------------------------------------------*/

void wait_debounce(void);

/*----------------------------------------------------------------
-----------------FUNCTIONS----------------------------------------
-----------------------------------------------------------------*/
void wait_debounce(void)
{
    unsigned char temp1, temp2;
    unsigned int i,j;
    
    do {
        temp1 = PIND;                  		// read input
        for(i=0;i<65535;i++)
			for(j=0;j<50;j++);
        temp2 = PIND;                  		// read input
        temp1 = (temp1 & temp2);       		// debounce input
    } while ( temp1 & _BV(PIND1) );
}

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/

int main(void)
{
	
	DDRA=0xF0;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PA.4, PA.5, PA.6 AND PA.7 ARE OUTPUT
									//ALL OTHERS ARE INPUT
									
	DDRB=0XFB;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PB.2 IS  INPUT
									//ALL OTHERS ARE OUTPUT
	
	DDRD=0XF1;						//SET DATA DIRECTION REGISTER
									//SET 1 for OUTPUT PORT
									//SET 0 FOR INPUT PORT
									//PD.1, PD.2 AND PD.3 ARE INPUT
									//ALL OTHERS ARE OUTPUT

	sbi(PORTA,4);					//LED1 ON (INDICATION FOR READY TO USE)
	
	
	sbi(PORTB,2);					//ENABLE PULL UP FOR SWITCH INT2
	sbi(PORTD,1);					//ENABLE PULL UP FOR SW1
	sbi(PORTD,2);					//ENABLE PULL UP FOR SWITCH INT0
	sbi(PORTD,3);					//ENABLE PULL UP FOR SWITCH INT1
    

    for (;;)								/* loop forever */ 
	{                           
		sbi(PORTA,5);
        wait_debounce();				/* wait until push button sw1 is pressed */
		cbi(PORTA,5);
		wait_debounce();				/* wait until push button sw1 is pressed */
    }
}
