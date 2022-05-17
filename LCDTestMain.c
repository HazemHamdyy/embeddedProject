
#include <stdint.h>
#include "LCD.h"
#include "systick.h"
#include "Keypad.h"
#include "case A.h"

int main(void){
  unsigned char key;
  LCD_Init(); 	
	keypad_Init();
	portF_init();
  LCD_Clear();
  LCD_OutString("Test LCD");
  SysTick_Wait10ms(10);
while(1){
    LCD_Clear();
		key=keypad_getkey();
switch(key){
case 'A':
					LCD_OutString("Popcorn");
          LEDS_ON();
          LCD_Clear();
	        count_1Min(60);
	        LCD_Clear(); 
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
  LEDS_OFF();
}}


