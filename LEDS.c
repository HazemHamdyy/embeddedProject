#include <stdint.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "LCD.h"
#include "systick.h"
#include "interrupt.h"
#include "tm4c123gh6pm.h"
#include "stdbool.h"




void LEDS_ON (void)
{
//GPIO_PORTF_DATA_R &= ~(0X0E);
GPIO_PORTF_DATA_R |=0X0E;
}
void LEDS_OFF (void)
{
 GPIO_PORTF_DATA_R &= 0x11;
//GPIO_PORTF_DATA_R &=~0X0E;

}
void LEDS_BLINK_3times (void)
{
	/*GPIO_PORTF_DATA_R &= ~(0X0E);
	GPIO_PORTF_DATA_R|=0x0E;*/
for (int i=0 ; i<3 ; i++)
	{
		LEDS_OFF();
			GPIO_PORTE_DATA_R|=0x00;
		
				 SysTick_Wait10ms(10);
		GPIO_PORTE_DATA_R|=0x20;
	LEDS_ON();
SysTick_Wait10ms(30);
		
		LEDS_OFF();
			GPIO_PORTE_DATA_R|=0x00;

		//GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
	}
}
