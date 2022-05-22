#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "LCD.h"
#include "systick.h"
#include "Keypad.h"
#include "tm4c123gh6pm.h"
#include "stdbool.h"
#include "interrupt.h"
#include "case B-C.h"
#include "leds.h"
#include "switch3.h"
#include "caseD.h"
#include "lcdCommand.h"
#include "counting.h"

 int globalTime;
 enum state {
 case_A,case_B,case_C,case_D,idle_case,counting_state
 }state;
 
int main(void){
		state=idle_case;
	
 	switch3_buzzer_init();
  unsigned char key ;
	
  LCD_Init(); 	
	keypad_Init();
  LCD_Clear();
  LCD_OutString("Test LCD");
  SysTick_Wait10ms(50);
	EdgeCounter_Init();
	
		
while(1){
	LCD_Clear();
switch(state){
case case_A:
					LCD_OutString("Popcorn");
          SysTick_Wait10ms(200);
          globalTime=60;
					state=counting_state;
					break;
case case_B:
       LCD_Clear();
			 LCD_OutString("Beef weight?");
       OutCmd(0xC0); ////Set LCD Cursor to second line
        SysTick_Wait10ms(50);
        beefAndChicken(30);
      	break;
case case_C:
					LCD_OutString("Chicken weight?");
          OutCmd(0xC0); ////Set LCD Cursor to second line
           SysTick_Wait10ms(50);
           beefAndChicken(12);
           break;
	

case case_D:
					LCD_OutString("Cooking time?");
					SysTick_Wait10ms(200);
					read_write();
					globalTime = duration();
          state=counting_state;
					break;
case idle_case:
       LCD_OutString("CHOOSE YOUR MEAL");
       if(keypad_getkey()){
	     state=keypad_getkey()-'A';
       }else{
       state=idle_case;
       }
       break;
case counting_state:
	     counting(calcTime(globalTime)[0],calcTime(globalTime)[1]);
	     break;
}
       SysTick_Wait10ms(100);
	 } 
}
