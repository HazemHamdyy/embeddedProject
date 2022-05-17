#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "Keypad.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
void SystemInit(){}

int CookingTime(int weight)
	{ double timeps;
    timeps=	0.2*weight*60;
		return timeps;
	}
	
void chicken (void)
{ int weight,i,j;
	char key;
	
	LCD_OutString("Chicken weight?");
	//Set LCD Cursor to second line//
	OutCmd(0xC0);
	
		if(((GPIO_PORTE_DATA_R&0x10)==0x10) && (GPIO_PORTF_DATA_R &0x11)==0x01) //SW2 should always be pressed and sw3 should be open 
	{
		key=keypad_getkey(); //CHECK NUMBER
		
		//weightinput: 
		weight=key;
	  while((weight>=1) && (weight<=9)!=1)                         // if((weight>=1) && (weight<=9)) for check
	{ 
		 LCD_Clear();
	  LCD_OutString("Err");
		SysTick_Wait10ms(200); // display for 2 seconds
		LCD_Clear();
		                                /////////////goto weightinput;
		//waiting time till the oven gets back to its start position
	}
		int time;
	  unsigned char buffer1 [5];
	  unsigned char buffer2 [5];
		int minutes,seconds;
		LCD_Clear();
		LCD_OutUDec(weight); // Print out 0-9
		SysTick_Wait10ms(200);  // display weight for 2 sec
		time= CookingTime(weight);
		//convert seconds to minutes
    minutes= time/60;
    seconds= time -(minutes*60); //calculate remaining seconds
	  i=minutes;
	do{
	    for (j=seconds;j>=0;j--)
		{
      snprintf(buffer1,10,"%02d%",i);  //to convert minutes and seconds into strings
		  strcat(buffer1, ":");
      snprintf(buffer2,10,"%02d%",j);
		  strcat(buffer1,buffer2);
      LCD_Clear();
	    LCD_OutString(buffer1);
		  SysTick_Wait10ms(100); //display for 1 second
			LCD_Clear();	 
		}
     	seconds=60;
		   i--;
		} while(i>=0);
	}
	else {
		 LCD_Clear();
	  LCD_OutString("Please close the door");
		//waiting time till the oven gets back to its start position
	}
		
}
	