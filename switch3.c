#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "interrupt.h"
#include "systick.h"

void EnableInterrupts(void);
//switch3(microwavedoor)--->pE4

void switch3_buzzer_init(void){
		SYSCTL_RCGCGPIO_R |=0x10;
	while((SYSCTL_PRGPIO_R & 0x10)==0);
	GPIO_PORTE_LOCK_R =0X4C4F434B;

	GPIO_PORTE_CR_R|=0X30; 
	GPIO_PORTE_DIR_R|= 0x20; 
	GPIO_PORTE_DEN_R |= 0x30;
  GPIO_PORTE_PUR_R|=0X10; 
	 GPIO_PORTE_AMSEL_R |= 0;       //     disable analog functionality on PF
	
	GPIO_PORTE_IS_R &= ~0x10;     // (d) PF4 is edge-sensitive
  GPIO_PORTE_IBE_R &= ~0x10;    //     PF4 is not both edges
  GPIO_PORTE_IEV_R &= ~0x10;    //     PF4 falling edge event
  GPIO_PORTE_ICR_R = 0x10;      // (e) clear flag4
  GPIO_PORTE_IM_R |= 0x10;      // (f) arm interrupt on PF4 *** No IME bit as mentioned in Book ***
  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00)|0x00000040; // PortE=priority 2
  NVIC_EN0_R |= 0x10;      // (h) enable interrupt 4 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}
		

void GPIOPortE_Handler(void)
{
	if(isPlay ){
	
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
	LCD_Clear();
	 LCD_OutString("Pause ");
	 //snprintf (buffer , 10 , "%d",x);
		LCD_OutString(buffer); 
	 SysTick_Wait10ms(20);
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
}
}
