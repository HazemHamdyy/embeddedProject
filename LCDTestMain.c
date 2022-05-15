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


int y ;
 int time;
char buffer2 [5];
int main(void){
	switch3_buzzer_init();
  unsigned char key ;
	unsigned char weight='3';
	
  LCD_Init(); 	
	keypad_Init();
  LCD_Clear();
  LCD_OutString("Test LCD");
  SysTick_Wait10ms(10);
	EdgeCounter_Init();
	
		
while(1){
	
 
		 LCD_Clear();
		key=keypad_getkey();
switch(key){
case 'A':
					LCD_OutString("Popcorn");
          
for(int i =0;i<=500;i++){
SysTick_Wait10ms(1);
		if(GPIO_PORTE_DATA_R&0x10){
		GPIO_PORTF_DATA_R=0x0E;
	
	
	
 	if((!(GPIO_PORTF_DATA_R&1))){
	LCD_Clear();
isPlay=true;
		      
          x=6;

          while(!(x==0)&isPlay){
						 LEDS_ON();
						 snprintf (buffer , 10 , "%d",x);
						 //LCD_OutUDec(x);
						LCD_OutString(buffer); 
						 SysTick_Wait10ms(50);
							LCD_Clear();	
						x--;	
				
				}
					isPlay=false;
				
		

	
			if(x==0)	{
				LCD_OutString("FOOD IS READY");
				
				LEDS_BLINK_3times ();
				
			GPIO_PORTE_DATA_R|=0X20;
			/*LEDS_OFF ();
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;*/
				
				
			
			}
					break;}else{}}}   

			
					break;
case 'B':
	/*
	
					LCD_OutString("Beef weight?  ");
          OutCmd(0xC0); ////Set LCD Cursor to second line
           SysTick_Wait10ms(10);
    	

	//char buffer2[5];
	 //weight=keypad_getkey();
dee:
 weight=keypad_getkey();
if (weight!=0){

	LCD_OutChar(weight);
	SysTick_Wait10ms(10);
	 int we=weight-'0';
		 if((we>=1) && (we<=9)){
     time=CookingTime_case_B(we);
			 x=time/60; //minutes
			 y=time -(x*60); //seconds
			 snprintf(buffer,10,"%02d",x);
			 strcat(buffer, ":");	
			 snprintf(buffer2,10,"%02d",y);
			 strcat(buffer,buffer2);
			 LCD_Clear();
	    LCD_OutString(buffer);
			 
			
		 }else{
		   LCD_Clear();
			 LCD_OutString("Err");
			 SysTick_Wait10ms(50);
			 break;
		 }
			 
		 
for(int i =0;i<=500;i++){
	
	
  SysTick_Wait10ms(10);
	if(GPIO_PORTE_DATA_R&0x10){
		GPIO_PORTF_DATA_R=0x0E;
if((!(GPIO_PORTF_DATA_R&1))){
   // SysTick_Wait1s(2); 
		isPlay=true;
		while(strcmp (buffer,"00:00")&isPlay){
						LCD_Clear(); 
						 LEDS_ON();
						
						for(int z=x;z>=0;z--)//i=x & j=y
	              {for (int j=y;j>=0;j--)
						       { 
										 if(isPlay){
											 	snprintf(buffer,10,"%02d",x);  //to convert minutes and seconds into strings
								strcat(buffer, ":");			
								snprintf(buffer2,10,"%02d",y);
								strcat(buffer,buffer2);
		
								LCD_OutString(buffer);
								 SysTick_Wait10ms(50); //display for 1 second 
								LCD_Clear(); 
									y--;
										 
										 }
							
									 }
									 y=60;
									 x--;
								 }
							LCD_Clear();	
				}
		break;
					}}

}   
if((x==0)&(y==0)){
LCD_OutString("FOOD IS READY");
						//GPIO_PORTE_DATA_R|=0X20;
			LEDS_BLINK_3times ();
			LEDS_OFF ();
}
     
				
					break;
		 
}
else
{
	
	SysTick_Wait10ms(1);
	
	goto dee;
	break;
}
	
	*/


			LCD_OutString("Beef weight?");
          OutCmd(0xC0); ////Set LCD Cursor to second line
           SysTick_Wait10ms(10);
  

	//char buffer2[5];
	 //weight=keypad_getkey();
de:
 weight=keypad_getkey();
if (weight!=0){

	LCD_OutChar(weight);
	SysTick_Wait10ms(20);
	 int we=weight-'0';
		 if((we>=1) && (we<=9)){
     time=CookingTime_case_B(we);
			 x=time/60; //minutes
			 y=time -(x*60); //seconds
			 snprintf(buffer,10,"%02d",x);
			 strcat(buffer, ":");	
			 snprintf(buffer2,10,"%02d",y);
			 strcat(buffer,buffer2);
			 LCD_Clear();
	    LCD_OutString(buffer);
			 
			
		 }else{
		   LCD_Clear();
			 LCD_OutString("Err");
			 SysTick_Wait10ms(50);
			 break;
		 }
			 
		 
for(int i =0;i<=500;i++){
	
	
  SysTick_Wait10ms(10);
	if(GPIO_PORTE_DATA_R&0x10){
		GPIO_PORTF_DATA_R=0x0E;
		for(int m=0;m<500;m++){
			 SysTick_Wait10ms(10);
		if(((GPIO_PORTF_DATA_R&01)==0)){
    SysTick_Wait1s(2); 
		isPlay=true;
		while(strcmp (buffer,"00:00")&isPlay){
						LCD_Clear(); 
						 LEDS_ON();
						
						for(int z=x;z>=0;z--)//i=x & j=y
	              {for (int j=y;j>=0;j--)
						       { 
										 if(isPlay){
											 	snprintf(buffer,10,"%02d",x);  //to convert minutes and seconds into strings
								strcat(buffer, ":");			
								snprintf(buffer2,10,"%02d",y);
								strcat(buffer,buffer2);
		
								LCD_OutString(buffer);
								 SysTick_Wait10ms(50); //display for 1 second 
								LCD_Clear(); 
									y--;
										 
										 }
							
									 }
									 y=60;
									 x--;
								 }
							LCD_Clear();	
								 break;
				}
					break;}}
 	}}    
if((x==0)&(y==0)){
LCD_OutString("FOOD IS READY");
						//GPIO_PORTE_DATA_R|=0X20;
			LEDS_BLINK_3times ();
			LEDS_OFF ();
}
					break;
		 
		 
		 
		 
		 
		 
		 
		 
}
else
{
	
	SysTick_Wait10ms(10);
	
	goto de;
	break;
}











case 'C':
									LCD_OutString("Chicken weight?");
          OutCmd(0xC0); ////Set LCD Cursor to second line
           SysTick_Wait10ms(10);
  

	//char buffer2[5];
	 //weight=keypad_getkey();
deh:
 weight=keypad_getkey();
if (weight!=0){

	LCD_OutChar(weight);
	SysTick_Wait10ms(10);
	 int we=weight-'0';
		 if((we>=1) && (we<=9)){
     time=CookingTime_case_C(we);
			 x=time/60; //minutes
			 y=time -(x*60); //seconds
			 snprintf(buffer,10,"%02d",x);
			 strcat(buffer, ":");	
			 snprintf(buffer2,10,"%02d",y);
			 strcat(buffer,buffer2);
			 LCD_Clear();
	    LCD_OutString(buffer);
			 
			
		 }else{
		   LCD_Clear();
			 LCD_OutString("Err");
			 SysTick_Wait10ms(50);
			 break;
		 }
			 
		 
for(int i =0;i<=500;i++){
	
	
  SysTick_Wait10ms(10);
	if(GPIO_PORTE_DATA_R&0x10){
		GPIO_PORTF_DATA_R=0x0E;
 	if(((GPIO_PORTF_DATA_R&01)==0)){
    SysTick_Wait1s(2); 
		isPlay=true;
		while(strcmp (buffer,"00:00")&isPlay){
						LCD_Clear(); 
						 LEDS_ON();
						
						for(int z=x;z>=0;z--)//i=x & j=y
	              {for (int j=y;j>=0;j--)
						       { 
										 if(isPlay){
											 	snprintf(buffer,10,"%02d",x);  //to convert minutes and seconds into strings
								strcat(buffer, ":");			
								snprintf(buffer2,10,"%02d",y);
								strcat(buffer,buffer2);
		
								LCD_OutString(buffer);
								 SysTick_Wait10ms(50); //display for 1 second 
								LCD_Clear(); 
									y--;
										 
										 }
							
									 }
									 y=60;
									 x--;
								 }
							LCD_Clear();	
								 break;
				}
					break;}}}    
if((x==0)&(y==0)){
LCD_OutString("FOOD IS READY");
						//GPIO_PORTE_DATA_R|=0X20;
			LEDS_BLINK_3times ();
			LEDS_OFF ();
}
					break;
		 
		 
		 
		 
		 
		 
		 
		 
}
else
{
	
	SysTick_Wait10ms(10);
	
	goto deh;
	break;
}
	

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
