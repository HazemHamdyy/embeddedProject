#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Keypad.h"
#include "LcdCommand.h"
#include "LCD.h"
#include "systick.h"
#include "string.h"

#define sw1_pressed 0x01
#define sw2_pressed 0x10
#define sw3_pressed 0x10


void sw1_sw2Init(void){
SYSCTL_RCGCGPIO_R |= 0x20;
while((SYSCTL_PRGPIO_R &0x20)==0);
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_AMSEL_R &= ~0x11;
GPIO_PORTF_CR_R |= 0x11;
GPIO_PORTF_AFSEL_R &= ~0x11;
GPIO_PORTF_PCTL_R &= ~0x000F000F;
GPIO_PORTF_DEN_R |= 0x11;
GPIO_PORTF_DIR_R &= ~0x11;
GPIO_PORTF_PUR_R |= 0x11;
}

void sw3_Init(void){
SYSCTL_RCGCGPIO_R |= 0x10;
while((SYSCTL_PRGPIO_R &0x10)==0);
GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTE_AMSEL_R &= ~0x10;
GPIO_PORTE_CR_R |= 0x10;
GPIO_PORTE_AFSEL_R &= ~0x10;
GPIO_PORTE_PCTL_R &= ~0x000F0000;
GPIO_PORTE_DEN_R |= 0x10;
GPIO_PORTE_DIR_R &= ~0x10;
GPIO_PORTE_PUR_R |= 0x10;
}

unsigned char sw_input(void){
return GPIO_PORTF_DATA_R & 0x11;
}

unsigned char sw3_input(void){
return GPIO_PORTE_DATA_R & 0x10;
}

uint32_t key;
uint32_t i = 0;
unsigned char button;
unsigned char sw3;
char arr[4];
char temp[4] = {0, 0 , 0, 0};
uint32_t sec;
uint32_t min;
char weight;

void show_user_value(char arr[]){
	switch(i){
		case 0:
			for(int j = 0; j<4; j++){
				LCD_setRowCol(0,(3-j));
				LCD_OutChar((int)arr[j]); 
			}
			break;
			
		case 1:
			LCD_setRowCol(0, 3);
			LCD_OutChar((int)arr[1]);
			LCD_setRowCol(0, 2);
			LCD_OutChar((int)arr[0]);
			LCD_setRowCol(0, 1);
			LCD_OutChar(0);
			LCD_setRowCol(0, 0);
			LCD_OutChar(0);
			break;
		
		case 2:
			LCD_setRowCol(0, 3);
			LCD_OutChar((int)arr[2]);
			LCD_setRowCol(0, 2);
			LCD_OutChar((int)arr[1]);
			LCD_setRowCol(0, 1);
			LCD_OutChar((int)arr[0]);
			LCD_setRowCol(0, 0);
			LCD_OutChar(0);
			break;
		
		case 3:
			for(int j = 0; j<4; j++){
				LCD_setRowCol(0,(3-j));
				LCD_OutChar((int)arr[3-j]);
			}
			break;
	}
	
}

void count_down(uint32_t min, uint32_t sec){
	char buffer1 [5];
	char buffer2 [5];
	for (int j = min; j>=0; j--){
		snprintf (buffer2 , 10 , "%d" , j);
			LCD_setRowCol(0, 0);
			LCD_OutString(buffer2);
			SysTick_Wait10ms(100);
		for(int i = sec; i >= 0; i--){
			snprintf (buffer1 , 10 , "%d" , i);
			LCD_setRowCol(0, 2);
			LCD_OutString(buffer1);
			SysTick_Wait10ms(100);
			LCD_Clear();
		}
	}
}

void strat_Operation(){
	min = arr[0] + (10 * arr[1]);
	sec = arr[2] + (10 * arr[3]);
	count_down(min, sec);
}

void reset(void){
	char buffer [5];
	LCD_Clear();
	for(int i = 0; i<4; i++){
		arr[i] = 0;
		snprintf (buffer , 10 , "%d" , arr[i]);
		LCD_OutString(buffer);
	}
}

void Read_Write(void){
	reset();
	dee:
 weight=keypad_getkey();
			if (weight!=0){
				button = sw_input();
				if (button != sw2_pressed){
					for(int i = 3; i >= 0; i--){
						arr[i] = weight;
					}
					strcpy(temp, arr);
				}
				goto dee;
			}
			else
			{
				SysTick_Wait10ms(10);
				goto dee;
			}
	/*while(1){
		//button = sw_input();
		dee:
 weight=keypad_getkey();
			if (weight!=0){
				temp[3] = weight
				SysTick_Wait10ms(10);
			}
			else
			{
				SysTick_Wait10ms(10);
				goto dee;
			}
			i++;
		//sw3 = sw3_input();
			
		if (button == sw1_pressed){
			reset();
			Read_Write();
			break;
		}
		else if((button != sw2_pressed)){
dee:
 weight=keypad_getkey();
			if (weight!=0){
				key = weight;
				SysTick_Wait10ms(10);
			}
			else
			{
				SysTick_Wait10ms(10);
				goto dee;
			}
			if ((arr[0] >= 6) || (arr[2] >= 6)){
				LCD_OutString("Invalid Num");
				SysTick_Wait10ms(200);
				reset();
				Read_Write();
				break;
			}
			//else {
			arr[i] = key;
			show_user_value(arr, i);
			SysTick_Wait10ms(50);
		//}
	}
		else if((button == sw2_pressed) && (sw3 != sw3_pressed)){
			strat_Operation();
		}*/
	}
