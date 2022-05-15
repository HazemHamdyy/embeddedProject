#include "caseD.h"
#include <stdint.h>
#include "LCD.h"
#include "systick.h"
#include "Keypad.h"
#include "case A.h"
#include "tm4c123gh6pm.h"
#include "string.h"
#include "stdio.h"
#include "lcdCommand.h"

int main(void){
  unsigned char key;
  LCD_Init(); 	
	keypad_Init();
	portF_init();
  LCD_Clear();
  LCD_OutString("Test LCD");
  SysTick_Wait10ms(10);
	//LEDS_ON();
	char buffer[5];

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
					SysTick_Wait10ms(50);
					read_write();
					LCD_command(0x02);
						int m = duration();
						snprintf (buffer, 10, "%d", m);
						LCD_Clear();
						SysTick_Wait10ms(50);
						LCD_OutString(buffer);
					
SysTick_Wait10ms(50);
					/*for (int i = 0; i<500 ; i++){
						SysTick_Wait10ms(1);
						 if((GPIO_PORTF_DATA_R&01) == 0) {
						char buffer[5];
						int m = duration();
						snprintf (buffer, 10, "%d", m);
						LCD_OutString(buffer);
					}
					else {
					read_write();
					LCD_OutString("press Sw2");

					}
					}*/
         
					break;
default:
     LCD_OutString("nothing");
     break;
}
  SysTick_Wait10ms(20);

}}


