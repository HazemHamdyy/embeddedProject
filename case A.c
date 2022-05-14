#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "LCD.h"
#include "systick.h"

void   portF_init()
{
	 SYSCTL_RCGCGPIO_R =0X20;
	 while((SYSCTL_PRGPIO_R&0x20)==0){};
	 GPIO_PORTF_LOCK_R=0x4C4F434B;
	 GPIO_PORTF_CR_R =0x1F;
	 GPIO_PORTF_PCTL_R  &=~0x000FFFFF;
	 GPIO_PORTF_AFSEL_R &=~0x1F;
	 GPIO_PORTF_AMSEL_R &=~0x1F;
	 GPIO_PORTF_PUR_R |=0x11;
	 GPIO_PORTF_DEN_R |=0x1F;
	 GPIO_PORTF_DIR_R |=0x0E;
}
void SysTick_Wait1s()
{
  uint32_t i;
  for(i=0; i<1000; i++){
    SysTick_Wait(80000);  // wait 1ms (assumes 80 MHz clock)
  }
}
void count_1Min(uint32_t delay)
{
  uint32_t i;
	char buffer [5];
  for(i=delay; i >0; i--)
	{
		 snprintf (buffer , 10 , "%d" , i);//convert int to string
		 LCD_OutString(buffer);            // print on lcd
     SysTick_Wait1s(); // wait 1s (assumes 80 MHz clock)
		 LCD_Clear();
  }
}



