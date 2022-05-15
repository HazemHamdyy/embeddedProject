#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Keypad.h"
#include "LcdCommand.h"
#include "LCD.h"
#include "systick.h"
#include "string.h"
#include "counting.h"

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
uint32_t n;
unsigned char button;
unsigned char sw3;
char arr[5] = {'0', '0', ':', '0', '0'};
char temp[5] = {'0', '0', ':', '0', '0'};
uint32_t sec;
uint32_t min;

void reset(void){
	LCD_Clear();
	for(int i = 0; i<5; i++){
		LCD_OutChar((int)arr[i]);
	}
}

int duration() {
	int min, sec;
	min = (temp[1] - '0') + (10 * (temp[0] - '0'));
	sec = (temp[4] - '0') + (10 * (temp[3] - '0'));
	return ((min * 60) + sec);
	//counting(sec, min);
}


/*void print(char arr[]){
	LCD_command(0x02);
	LCD_OutChar((int)arr[0]);
 	for(int i = 1; i<5; i++){
		if (i == 2){
			LCD_setRowCol(0, 2);
			LCD_OutChar(':');
				}
		else {
			LCD_OutChar((int)arr[i]);
				}
	}
}

void shift(char arr[], int i){
		if (i == 0){
			for(int j = 0; j<4; j++){
				temp[3-j] = arr[j];
			}
		}
			
		else if(i == 1){
			temp[3] = arr[1];
			temp[2] = arr[0];
			temp[1] = '0';
			temp[0] = '0';
			//print(temp);
		}
		
		else if (i == 2){
			temp[3] = arr[2];
			temp[2] = arr[1];
			temp[1] = arr[0];
			temp[0] = '0';
			//print(temp);
		}
		
		else if (i == 3){
			for(int j = 0; j<4; j++){
				temp[3-j] = arr[3-j];
			}
			//print(temp);
		}
}*/
void show_user_value(uint32_t n){
	switch(n){
		case 0:
			//LCD_setRowCol(0, 2);
			//LCD_OutChar(':');
			temp[2] = ':';
			LCD_setRowCol(0, 4);
			LCD_OutChar((int)arr[0]);
			temp[4] = arr[0];
			temp[3] = '0';
			temp[1] = '0';
			temp[0] = '0';
		break;
			/*for(int j = 0; j<5; j++){
				if (j == 2){
					LCD_setRowCol(0, 2);
					LCD_OutChar(':');
					temp[4-j] = arr[j];
				}
				else {
				LCD_setRowCol(0,(4-j));
				LCD_OutChar((int)arr[j]);
					temp[4-j] = arr[j];
				} 
			}*/
			break;
			
		case 1:
			//LCD_setRowCol(0, 2);
			//LCD_OutChar(':');
			temp[2] = ':';
			LCD_setRowCol(0, 4);
			LCD_OutChar((int)arr[1]);
			temp[4] = arr[1];
			LCD_setRowCol(0, 3);
			LCD_OutChar((int)arr[0]);
			temp[3] = arr[0];
			temp[1] = '0';
			temp[0] = '0';
		break;
		
		case 2:
			//LCD_setRowCol(0, 2);
			//LCD_OutChar(':');
			temp[2] = ':';
			LCD_setRowCol(0, 4);
			LCD_OutChar((int)arr[2]);
			temp[4] = arr[2];
			LCD_setRowCol(0, 3);
			LCD_OutChar((int)arr[1]);
			temp[3] = arr[1];
			LCD_setRowCol(0, 1);
			LCD_OutChar((int)arr[0]);
			temp[1] = arr[0];
			temp[0] = '0';
			break;
		
		case 3:
			//LCD_setRowCol(0, 2);
			//LCD_OutChar(':');
			temp[2] = ':';
			LCD_setRowCol(0, 4);
			LCD_OutChar((int)arr[3]);
			temp[4] = arr[3];
			LCD_setRowCol(0, 3);
			LCD_OutChar((int)arr[2]);
			temp[3] = arr[2];
			LCD_setRowCol(0, 1);
			LCD_OutChar((int)arr[1]);
			temp[1] = arr[1];
			LCD_command(0x02);
			LCD_OutChar((int)arr[0]);
			temp[0] = arr[0];
			//print(arr);
			/*for(int i = 3; i>=0; i--){
				reset();
				LCD_OutChar((int)arr[i]);
	}*/
			break;
	}
	
}

uint32_t get_input(void){
	uint32_t j = i;
	arr[j] = key;
	i++;
	return j;
}

void read_write(){
	char buffer [5];
	int m;
	reset();
	while(n < 3){
		dee:
		if((GPIO_PORTF_DATA_R&01) == 0){
			break;
		}
	key=keypad_getkey();
		if((key < '0') && (key > '9')){
				LCD_OutString("Invalid Num");
			goto dee;
		}
			if (key !=0){
				//button = sw_input();
				/*if ( (GPIO_PORTF_DATA_R&01) == 0) {
					  m = duration();
						snprintf (buffer, 10, "%d", m);
						LCD_OutString(buffer);
					//if (((int)temp[0]) > 3 || ((int)temp[3]) > 5){
						LCD_OutString("Invalid Num");
						read_write();
					}*/
					/*else {
						m = duration();
						snprintf (buffer, 10, "%d", m);
						LCD_OutString(buffer);
					}*/
				//*/
				//else /*(button != sw2_pressed)*/
				
					n = get_input();
					//shift(arr, n);
					//print(temp);
					show_user_value(n);
					//SysTick_Wait10ms(100);
					//goto dee;
				
			}
			else
			{
				goto dee;
			}
			
}
	}