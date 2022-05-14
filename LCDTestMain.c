
#include <stdint.h>
#include "LCD.h"
#include "systick.h"
#include "Keypad.h"
#include "tm4c123gh6pm.h"
#include "case A.h"
#include "LEDS.h"

int main(void){
  unsigned char key;
	LCD_Init();
  portF_init(); 	
	keypad_Init();
  LCD_Clear();
  LCD_OutString("Test LCD");
 SysTick_Wait10ms(10);

while(1){
		  LEDS_ON();

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
  
}
}

