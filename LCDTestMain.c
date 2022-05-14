
#include <stdint.h>
#include "LCD.h"
#include "systick.h"
#include "Keypad.h"
#include "tm4c123gh6pm.h"
#include "stdbool.h"
int x=0 ;
bool isPlay=false ;
bool isPaused=false ;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

// global variable visible in Watch window of debugger
// increments at least once per button press
volatile uint32_t FallingEdges = 0;
void EdgeCounter_Init(void){                          
  SYSCTL_RCGCGPIO_R |= 0x00000020; // (a) activate clock for port F

  FallingEdges = 0;   
	GPIO_PORTF_LOCK_R = 0x4C4F434B;	// (b) initialize counter
	GPIO_PORTF_CR_R=0x1F;
  GPIO_PORTF_DIR_R &= ~0x11;    // (c) make PF4 in (built-in button)
  GPIO_PORTF_AFSEL_R &= ~0x10;  //     disable alt funct on PF4
  GPIO_PORTF_DEN_R |= 0x11;     //     enable digital I/O on PF4   
  GPIO_PORTF_PCTL_R &= ~0x000F0000; // configure PF4 as GPIO
  GPIO_PORTF_AMSEL_R = 0;       //     disable analog functionality on PF
  GPIO_PORTF_PUR_R |= 0x10;     //     enable weak pull-up on PF4
  GPIO_PORTF_IS_R &= ~0x10;     // (d) PF4 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x10;    //     PF4 is not both edges
  GPIO_PORTF_IEV_R &= ~0x10;    //     PF4 falling edge event
  GPIO_PORTF_ICR_R = 0x10;      // (e) clear flag4
  GPIO_PORTF_IM_R |= 0x10;      // (f) arm interrupt on PF4 *** No IME bit as mentioned in Book ***
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}
void GPIOPortF_Handler(void){
	GPIO_PORTF_ICR_R = 0x10; 	// acknowledge flag4
	if(isPlay){
	isPlay=false;
	isPaused=!isPaused;
	LCD_Clear();
	 LCD_OutString("Pause");
	 SysTick_Wait10ms(20);
	//GPIO_PORTF_DATA_R ^= 0x04; 
  
LCD_OutUHex(GPIO_PORTF_DATA_R);
	 SysTick_Wait10ms(20);}
		while(1){
		if((GPIO_PORTF_DATA_R&0x10)==0){
		isPlay=false;
		break;}
		if((GPIO_PORTF_DATA_R&1)==0){
		isPaused=false;
			isPlay=true;
			break;
		}
		
		
	

	
	}
	
	
	
	
}

int main(void){
	
  unsigned char key;
	 
  LCD_Init(); 	
	keypad_Init();
  LCD_Clear();
  LCD_OutString("Test LCD");
  SysTick_Wait10ms(10);
	EdgeCounter_Init();

while(1){
	
    LCD_Clear();
		key=keypad_getkey();
switch(key){
case 'A':
					LCD_OutString("Popcorn");
for(int i =0;i<=500;i++){
SysTick_Wait10ms(1);
 	if((GPIO_PORTF_DATA_R&01)==0){
	LCD_Clear();
isPlay=true;
          x=9;

          while(!(x==0)&isPlay){
						 LCD_OutUDec(x);
						 SysTick_Wait10ms(90);
							LCD_Clear();	
						x--;
						
					/*	if(NVIC_ST_CTRL_R&0x10){
	if(isPlay){
	x--;
		if(x==0){
		isPlay=false;
		}
	}
	}*/
							 
					
					
				}
					break;
}
	
}



         
					break;
case 'B':
					LCD_OutString("Beef");
					break;
case 'C':
					LCD_OutString("Chicken");
					break;
case 'D':
					LCD_OutString("Cooking time?");
					break;
default:
     LCD_OutString("nothing");
     break;
}
  SysTick_Wait10ms(20);

}}


