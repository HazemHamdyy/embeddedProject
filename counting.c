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
#include "counting.h"
#include "stateEnum.h"

char buffer2 [5];

int* calcTime(int duration){
int arrOfTime [2];
	arrOfTime[0]=duration/60;
	arrOfTime[1]=duration%60;
	
	return arrOfTime;
}
	
void counting(int min, int sec){
	state=idle_case;
	for(int i =0;i<=500;i++){
SysTick_Wait10ms(10);
		if(GPIO_PORTE_DATA_R&0x10){
   	if((!(GPIO_PORTF_DATA_R&1))){
  	LCD_Clear();
    isPlay=true;       
while(!(min==-1)&isPlay){
          while(!(sec==-1)&isPlay){
						 LEDS_ON();
						 snprintf(buffer,10,"%02d",min);  //to convert minutes and seconds into strings
						strcat(buffer, ":");			
								snprintf(buffer2,10,"%02d",sec);
								strcat(buffer,buffer2);
								LCD_OutString(buffer);
						   SysTick_Wait10ms(100); //display for 1 second 
								LCD_Clear(); 
						sec--;	
				}
					if(min==0){
					break;
					}
					sec=59;
					min--;
}
					isPlay=false;
			if(sec==-1)	{
				LCD_OutString("FOOD IS READY");
				 SysTick_Wait10ms(100);
				 LEDS_BLINK_3times ();
			   GPIO_PORTE_DATA_R|=0X20;
			}
					break;}else{
						snprintf(buffer,10,"%02d",min);  //to convert minutes and seconds into strings
								strcat(buffer, ":");			
								snprintf(buffer2,10,"%02d",sec);
								strcat(buffer,buffer2);
								LCD_OutString(buffer);
						LCD_OutString("  PRESS SW2");
						SysTick_Wait10ms(25); 
						LCD_Clear();
		}
		}else{
				LCD_Clear();
	      LCD_OutString("CLOSE THE DOOR");
				SysTick_Wait10ms(200); 
				LCD_Clear();
						
	}}   

}