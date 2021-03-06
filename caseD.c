#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Keypad.h"

#include "LCD.h"
#include "systick.h"
#include "string.h"
#include "counting.h"
#include "LcdCommand.h"
#include "interrupt.h"
#define sw1_pressed 0x01
#define sw2_pressed 0x10
#define sw3_pressed 0x10

bool caseD =false;
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
char arr[5] = {'0', '0', ':', '0', '0'};
char temp[5] = {'0', '0', ':', '0', '0'};
uint32_t sec;
uint32_t min;


void reset(void){
	n = 0;
	i = 0;
	temp[0] = '0';
	temp[1] = '0';
	temp[2] = ':';
	temp[3] = '0';
	temp[4] = '0';
	LCD_Clear();
	for(int i = 0; i<5; i++){
		LCD_OutChar((int)temp[i]);
	}
}

int duration() {
	min = (temp[1] - '0') + (10 * (temp[0] - '0'));
	sec = (temp[4] - '0') + (10 * (temp[3] - '0'));
	return ((min * 60) + sec);
}


void show_user_value(uint32_t n){
	switch(n){
		case 0:
			LCD_setRowCol(0, 4);
			LCD_OutChar((int)arr[0]);
			temp[4] = arr[0];
			temp[3] = '0';
			temp[1] = '0';
			temp[0] = '0';
		break;
			
		case 1:
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
			break;
	}
	
}

uint32_t get_input(void){
	uint32_t j = i;
	arr[j] = key;
	i++;
	return j;
}

bool check(){
	if(((temp[0] - '0') > 2) || ((temp[3] - '0') >5 )){
		LCD_Clear();
		LCD_OutString("Invalid Num");
		SysTick_Wait10ms(250);
		return true;
	}
	else{
		return false;
	}
}

void read_write(){
	caseD=true;
	invalid:
	reset();
	while(n < 3){
		dee:
		if((GPIO_PORTF_DATA_R&01) == 0){
			if((check())){
		goto invalid;
	}
			break;
		}
	key=keypad_getkey();
		if(((key-'0') >= 0) && ((key-'0')<=9)){
			if (key !=0){
					n = get_input();
					show_user_value(n);
				}else
			{
				goto dee;
			}
				
			}
			else
			{
				goto dee;
			}
		
}
	SysTick_Wait10ms(100);
	if((check())){
		goto invalid;
	}
}
