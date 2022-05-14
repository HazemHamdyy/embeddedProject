#include "LCD.h"
#include <stdint.h>
#include "systick.h"
#include "Keypad.h"

	int main(void){
  unsigned char key;
  LCD_Init(); 	
	keypad_Init();
  LCD_Clear();
  LCD_OutString("Test LCD");
  SysTick_Wait10ms(10);

while(1){
    LCD_Clear();
		key=keypad_getkey();
switch(key){
case 'A':
					LCD_OutString("Popcorn");
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
	
	
	
	
	
	
	





