#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "systick.h"
#include "leds.h"
#include "LCD.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "interrupt.h"

char buffer2 [5];

void counting(uint32_t y, uint32_t x){
			 snprintf(buffer,10,"%02d",x);
			 strcat(buffer, ":");	
			 snprintf(buffer2,10,"%02d",y);
			 strcat(buffer,buffer2);
			 LCD_Clear();
	    LCD_OutString(buffer);
		 
for(int i =0;i<=500;i++){
	
	
  SysTick_Wait10ms(1);
if(((GPIO_PORTF_DATA_R&01)==0)&(GPIO_PORTE_DATA_R&0x10)){
   // SysTick_Wait1s(2); 
		isPlay=true;
		while(strcmp (buffer,"00:00")&isPlay){
						LCD_Clear(); 
						 LEDS_ON();
			demo:
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
					}

}   
if((x==0)&(y==0)){
LCD_OutString("FOOD IS READY");
						//GPIO_PORTE_DATA_R|=0X20;
			LEDS_BLINK_3times ();
			LEDS_OFF ();
}
     
				
					
else{
	SysTick_Wait10ms(1);
	goto demo;
}
}