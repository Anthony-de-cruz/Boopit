#include "Board_LED.h"                  // Board Support:LED

#define TIME 1000000

int main(void)
{
		unsigned int i;
	
	  LED_Initialize();                     // LED Init   
	
	while(1)	{    		/* Loop forever */
	
	  LED_On (0U);                                // Switch LED on
    for (i = 0; i < TIME; i++)
			/* empty statement */ ;       /* Wait */
    LED_Off (0U);                               // Switch off
    for (i = 0; i < TIME; i++)
			/* empty statement */ ;       /* Wait */
	}
}
