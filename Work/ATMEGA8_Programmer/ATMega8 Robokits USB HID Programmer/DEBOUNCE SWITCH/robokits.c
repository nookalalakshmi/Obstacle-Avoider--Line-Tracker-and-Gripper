//			MADE BY ROBOKITS INDIA.
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR DEBOUNCE
//			WRITTEN FOR PRODUCT ID 19 

/*-------------------------------------------------------------------          
 Description:
 This example shows how to debounce a switch input.

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
    unsigned int i;
    
    do {
        temp1 = PIND;                  		// read input
        for(i=0;i<65535;i++);
        temp2 = PIND;                  		// read input
        temp1 = (temp1 & temp2);       		// debounce input
    } while ( temp1 & _BV(PIND2) );
}

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
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
    

    for (;;)								/* loop forever */ 
	{                           
		sbi(PORTD,7);
        wait_debounce();				/* wait until push button PD2 (INT0) is pressed */
		cbi(PORTD,7);
		wait_debounce();				/* wait until push button PD2 (INT0) is pressed */
    }
}
