#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "LCD.h"
#include "systick.h"
#include "tm4c123gh6pm.h"
#include "stdbool.h"
#include "leds.h"
#include "caseD.h"

int x=0 ;
bool isPlay=false ;
bool isPaused=false ;
char buffer [5];
volatile uint32_t FallingEdges = 0;
void EnableInterrupts(void);  // Enable interrupts

void EdgeCounter_Init(void){                          
  SYSCTL_RCGCGPIO_R |= 0x00000020; // (a) activate clock for port F

  FallingEdges = 0;   
	GPIO_PORTF_LOCK_R = 0x4C4F434B;	// (b) initialize counter
	GPIO_PORTF_CR_R=0x1F;
  GPIO_PORTF_DIR_R = 0x0E;    // (c) make PF4 in (built-in button)
  GPIO_PORTF_DEN_R |= 0x1F;     //     enable digital I/O on PF4   
  GPIO_PORTF_AMSEL_R = 0;       //     disable analog functionality on PF
 	GPIO_PORTF_PUR_R |= 0x10;     //     enable weak pull-up on PF4
 
	GPIO_PORTF_IS_R &= ~0x10;     // (d) PF4 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x10;    //     PF4 is not both edges
  GPIO_PORTF_IEV_R &= ~0x10;    //     PF4 falling edge event
  GPIO_PORTF_ICR_R = 0x10;      // (e) clear flag4
  GPIO_PORTF_IM_R |= 0x10;      // (f) arm interrupt on PF4
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}

void GPIOPortF_Handler(void){
	GPIO_PORTF_ICR_R = 0x10;
if((caseD)&&(!isPlay)){
reset();
} 	
	if(isPlay){
	isPlay=false;
	isPaused=!isPaused;
	
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
	LCD_Clear();
	 LCD_OutString("Pause ");
		LCD_OutString(buffer); 
	 SysTick_Wait10ms(20);
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
		while(1){
				GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
			 SysTick_Wait10ms(2);
			
		if(!(GPIO_PORTF_DATA_R&0x10)){
			
		isPlay=false;
			LEDS_OFF ();
		break;}
		if((!(GPIO_PORTF_DATA_R&1))&&(GPIO_PORTE_DATA_R&0x10)){
		isPaused=false;
			isPlay=true;
			break;
		}}
		}
		}
