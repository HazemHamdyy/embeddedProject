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

char buffer2 [5];

void calcTime(int duration){}
	
void counting(int min, int sec){
	for(int i =0;i<=500;i++){
SysTick_Wait10ms(1);
		if(GPIO_PORTE_DATA_R&0x10){
		GPIO_PORTF_DATA_R=0x0E;
	
	
	
 	if((!(GPIO_PORTF_DATA_R&1))){
	LCD_Clear();
isPlay=true;
		      
        
while(!(min==-1)&isPlay){
          while(!(sec==0)&isPlay){
						 LEDS_ON();
						snprintf(buffer,10,"%02d",min);  //to convert minutes and seconds into strings
								strcat(buffer, ":");			
								snprintf(buffer2,10,"%02d",sec);
								strcat(buffer,buffer2);
		
								LCD_OutString(buffer);
								 SysTick_Wait10ms(50); //display for 1 second 
								LCD_Clear(); 
						sec--;	
				
				}
					sec=59;
					min--;
}
					isPlay=false;
				
		

	
			if(sec==0)	{
				LCD_OutString("FOOD IS READY");
				
				LEDS_BLINK_3times ();
				
			GPIO_PORTE_DATA_R|=0X20;
			/*LEDS_OFF ();
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;*/
				
				
			
			}
					break;}else{
						LCD_OutString("PLEASE PRESS SW2");
												SysTick_Wait10ms(5); 
						LCD_Clear();
		
		}}else{
	LCD_OutString("PLEASE CLOSE DOOR");
						SysTick_Wait10ms(50); 
						LCD_Clear();
						
	}}   

}