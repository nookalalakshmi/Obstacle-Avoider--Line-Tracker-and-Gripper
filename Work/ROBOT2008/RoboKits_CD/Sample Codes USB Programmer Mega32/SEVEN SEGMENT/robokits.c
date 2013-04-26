//			MADE BY ROBOKITS INDIA
//			VISIT US AT WWW.ROBOKITS.ORG
//			PROGRAM FOR SEVEN SEGMENT DISPLAY (Common Cathod Type)
//			WRITTEN FOR ROBOGRID

/*-------------------------------------------------------------------          
 Description:
 This example writes 0 to 9 numbers constantly to a common cathode type
 Seven Segment display at 1Hz.

 Note:
 
 Remove all led selection jumpers.
  
 Connect display as per the connection list shown below.
 
 Change the statements within switch for display on a common anode 
 7 segment.
 
  _delay_ms() function parameter passed should not exeed
 262.14ms / F_CPU in mhz.
 
 so for 16MHz the maximum paramer should be 16ms.
 
 For 1MHz it can be upto 262ms (250 is used for this example).
  
 Must be changed to get accurate delay at higher MHz.
 ---------------------------------------------------------------------*/

/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include<avr/io.h>
#include<util/delay.h>

/*----------------------------------------------------------------
-------------CONNECTION BETWEEN 7 segment AND ATMEGA32-----------
-----------------------------------------------------------------*/
#define DATA_PORT 	 PORTA
#define Pin_a     		0
#define Pin_b     		1
#define Pin_c     		2
#define Pin_d     		3
#define Pin_e     		4
#define Pin_f     		5
#define Pin_g     		6
#define Pin_Dec         7
#define DATA_MASK     0XFF


/*----------------------------------------------------------------
-----------------FUNCTION DECLARATION-----------------------------
-----------------------------------------------------------------*/
void Display(int a);

/*----------------------------------------------------------------
-----------------MAIN PROGRAM-------------------------------------
-----------------------------------------------------------------*/
int main(void)
{
	DDRA = 0xff;
	unsigned int i;
	i=0;
	do
	{
		Display(i);
		i++;
		if(i>9) 
			i=0;		
		_delay_ms(255);
		_delay_ms(255);
		_delay_ms(255);
		_delay_ms(255);	  
	}while(1);
} 
  
/*----------------------------------------------------------------
-----------------FUNCTIONS TO DISPLAY VALUES----------------------
-----------------------------------------------------------------*/  
void Display(int a)
{
	switch(a)
	{
		case 0:  
			DATA_PORT&=~(_BV(Pin_g));
			DATA_PORT|=(_BV(Pin_a)|_BV(Pin_b)|_BV(Pin_c)|_BV(Pin_d)|_BV(Pin_e)|_BV(Pin_f));
			break;			
		case 1:			
			DATA_PORT&=~(_BV(Pin_a)|_BV(Pin_d)|_BV(Pin_e)|_BV(Pin_f)|_BV(Pin_g));
			DATA_PORT|=(_BV(Pin_b)|_BV(Pin_c));
			break;
		case 2:  
			DATA_PORT&=~(_BV(Pin_c)|_BV(Pin_f));
			DATA_PORT|=(_BV(Pin_b)|_BV(Pin_d)|_BV(Pin_e)|_BV(Pin_a)|_BV(Pin_g));
			break;
		case 3:  
			DATA_PORT&=~(_BV(Pin_e)|_BV(Pin_f));
			DATA_PORT|=(_BV(Pin_c)|_BV(Pin_d)|_BV(Pin_a)|_BV(Pin_b)|_BV(Pin_g));
			break;
		case 4:  
			DATA_PORT&=~(_BV(Pin_a)|_BV(Pin_d)|_BV(Pin_e));
			DATA_PORT|=(_BV(Pin_c)|_BV(Pin_b)|_BV(Pin_f)|_BV(Pin_g));
			break;
		case 5:  
			DATA_PORT&=~(_BV(Pin_b)|_BV(Pin_e));
			DATA_PORT|=(_BV(Pin_a)|_BV(Pin_c)|_BV(Pin_d)|_BV(Pin_f)|_BV(Pin_g));
			break;
		case 6:  
			DATA_PORT&=~(_BV(Pin_a)|_BV(Pin_b));
			DATA_PORT|=(_BV(Pin_a)|_BV(Pin_c)|_BV(Pin_d)|_BV(Pin_f)|_BV(Pin_g)|_BV(Pin_e));
			break;
		case 7:  
			DATA_PORT&=~(_BV(Pin_d)|_BV(Pin_e)|_BV(Pin_f)|_BV(Pin_g));
			DATA_PORT|=(_BV(Pin_a)|_BV(Pin_c)|_BV(Pin_b));
			break;
		case 8:  
			DATA_PORT|=(_BV(Pin_a)|_BV(Pin_d)|_BV(Pin_e)|_BV(Pin_c)|_BV(Pin_b)|_BV(Pin_f)|_BV(Pin_g));
			break;
		case 9:  
			DATA_PORT&=~(_BV(Pin_d)|_BV(Pin_e));
			DATA_PORT|=(_BV(Pin_a)|_BV(Pin_c)|_BV(Pin_b)|_BV(Pin_f)|_BV(Pin_g));
			break;
					
	}
}
