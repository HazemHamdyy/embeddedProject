#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "systick.h"
#include "case A.h"

void portF_init(void);

void LEDS_ON (void)
{
GPIO_PORTF_DATA_R &= ~(0X0E);
GPIO_PORTF_DATA_R |=0X0E;
}
void LEDS_OFF (void)
{
GPIO_PORTF_DATA_R &=~0X0E;
}
void LEDS_BLINK_3times (void)
{
	GPIO_PORTF_DATA_R|=0x0E;
for (int i=0 ; i<3 ; i++)
	{
	  void SysTick_Wait1s();
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
	
	}
	
}
