#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "LCD.h"
#include "Keypad.h"
#include "systick.h"
#include "counting.h"
#include "stateEnum.h"
#include "tm4c123gh6pm.h"


char getWieght(void){
	char key;
int wght =0;
	int i=0;
	while((GPIO_PORTF_DATA_R&1)&&(i<4)){
		key = keypad_getkey();
		if(key){
			if(key>='0'&&key<='9'){
		wght=wght*10;
		wght+=(keypad_getkey()-'0');
			 OutCmd(0xC0);
		LCD_OutUDec(wght);
		SysTick_Wait10ms(50);
		i++;
}}
	
	

}
	wght+='0';
return wght;}


void beefAndChicken(int secPerKilo){
	int l=0;
	int time;
	unsigned char weight=0;
	
de:
	weight=getWieght();
   //weight=keypad_getkey();
if (weight!=0){
	  //LCD_OutChar(weight);
	  SysTick_Wait10ms(100);
	  int we=weight-'0';
		if((we>=1) && (we<=9)){
    time=secPerKilo*we;
			 LCD_Clear();
		 }else{
		   LCD_Clear();
			 LCD_OutString("Err");
			 SysTick_Wait10ms(100);
			 LCD_Clear();
			 if(secPerKilo==30){
			 LCD_OutString("Beef weight?");
			 }else if(secPerKilo==12){
			 LCD_OutString("Chicken weight?");
			 }
			  OutCmd(0xC0);
			  goto de;
		  }
	        globalTime= time;
		      state=counting_state;
 	}

else
{
	
	while(l<100){
		SysTick_Wait10ms(5);
	  l++;
	  goto de;
	}
	state = idle_case;
}

}
	