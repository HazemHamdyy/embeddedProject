#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "Keypad.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
void SystemInit(){}
void InitSW()
	{GPIO_PORTE_DIR_R |= 0x00; //SW3 as input 
	  GPIO_PORTE_DEN_R |= 0x10; //SW3 
		
	}
int CookingTime(int weight)
	{ double timeps;
    timeps=	0.5*weight*60;
		return timeps;
	}
/*void TimeConversion(int input_time)
{ int minutes,seconds;
    unsigned char buffer1 [5];
	unsigned char buffer2 [5];
    minutes=input_time/60;
    seconds=input_time -(minutes*60);
	for(int i=minutes;i>=0;i--)
	{for (int j=seconds;j>=0;j--)
		{//////////////
			SysTick_Wait10ms(100);
    snprintf(buffer1,10,"%d%",minutes);     //to convert minutes and seconds into strings
    snprintf(buffer2,10,"%d%",seconds);	
*/
	
void Beef(void)
{ int weight,i,j;
	char key;
	InitSW();
	LCD_OutString("Beef weight?");
	//Set LCD Cursor to second line//
	OutCmd(0xC0);
	
	if(((GPIO_PORTE_DATA_R|0x10)==0) && (GPIO_PORTF_DATA_R &0x11)==0x10) //SW2 should always be pressed
	{
		key=keypad_getkey();
	weightinput: 
		weight=key;
	    if((weight>=1) && (weight<=9))
	{ 	int time;
	  unsigned char buffer1 [5];
	  unsigned char buffer2 [5];
		int minutes,seconds;
		LCD_Clear();
		LCD_OutUDec(weight);
		SysTick_Wait10ms(200);
		time= CookingTime(weight);
		//convert seconds to minutes
    minutes=time/60;
    seconds=time -(minutes*60);
	for(i=minutes;i>=0;i--)
	{for (j=seconds;j>=0;j--)
		{snprintf(buffer1,10,"%d%",minutes);  //to convert minutes and seconds into strings
		strcat(buffer1, ":");			
    snprintf(buffer2,10,"%d%",seconds);
		strcat(buffer1,buffer2);
		LCD_Clear();
	  LCD_OutString(buffer1);
		SysTick_Wait10ms(100);
			LCD_Clear();
		}
		seconds=60;
		}
	}
	    else 
	{ LCD_Clear();
	  LCD_OutString("Err");
		SysTick_Wait10ms(200);
		LCD_Clear();
		goto weightinput;
		//waiting time till the oven gets back to its start position
	}
}
	else {
		 LCD_Clear();
	  LCD_OutString("Please close the door");
		//waiting time till the oven gets back to its start position
	}
		
}
	