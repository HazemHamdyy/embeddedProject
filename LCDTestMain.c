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
#include "caseD.h"
#include "lcdCommand.h"


int y ;
int a;
int b;
int m;
 int time;
 enum {
	Idle_case,
	Case_A,
	Case_B,
	Case_C,
	Case_D,
	Counting,
	Err} State_type;
 int previous_state;
 int state= Idle_case;
	
	int main (void)
	{ 	switch3_buzzer_init();
  unsigned char key ;
	unsigned char weight=0; 
		LCD_Init(); 	
	keypad_Init();
  LCD_Clear();
  LCD_OutString("Test LCD");
  SysTick_Wait10ms(10);
	EdgeCounter_Init();
	
	while (1) {
switch (state) {
	case Idle_case :
			LCD_Clear();
		key=keypad_getkey();
		LCD_OutString("CHOOSE YOUR MEAL");
   if(key=='A'){state=Case_A;}
	 else if(key=='B'){state=Case_B;}
	 else if(key=='C'){state=Case_C;}
	 else if(key=='D'){state=Case_D;}
	 else {
		 LCD_OutString("Invalid digit");
		 state=Idle_case;
	 }
	 break;
 

	case Case_A:
		previous_state=Case_A;
					LCD_OutString("Popcorn");
          SysTick_Wait10ms(50);
          

					counting(0,60);

			
					break;
case Case_B:
previous_state=Case_B;

       LCD_Clear();
			LCD_OutString("Beef weight?");
          OutCmd(0xC0); ////Set LCD Cursor to second line
           SysTick_Wait10ms(10);
int l=0;
  

	
de:
 weight=keypad_getkey();
if (weight!=0){

	LCD_OutChar(weight);
	SysTick_Wait10ms(20);
	 int we=weight-'0';
		 if((we>=1) && (we<=9)){
     time=CookingTime_case_B(we);
			  a=  calcTime(time)[0];
			 b= calcTime(time)[1];
			 //x=time/60; //minutes
			 //y=time -(x*60); //seconds
			/* snprintf(buffer,10,"%02d",x);
			 strcat(buffer, ":");	
			 snprintf(buffer2,10,"%02d",y);
			 strcat(buffer,buffer2);*/
			 LCD_Clear();
	    //LCD_OutString(buffer);
			 
			
		 }else{
		     state=Err;
			 break;
		 }
	
	
					counting(a,b);
 	}

else
{
	
	while(l<100){
		SysTick_Wait10ms(1);
		
	
	l++;
	goto de;
		
	
	}

}
	break;


case Case_C:
	previous_state=Case_C;
									LCD_OutString("Chicken weight?");
          OutCmd(0xC0); ////Set LCD Cursor to second line
           SysTick_Wait10ms(10);
  

	//char buffer2[5];
	 //weight=keypad_getkey();
int k =0;
deh:

 weight=keypad_getkey();

if (weight!=0){

	LCD_OutChar(weight);
	SysTick_Wait10ms(10);
	 int we=weight-'0';
		 if((we>=1) && (we<=9)){
     time=CookingTime_case_C(we);
			 if(time>1800){
				 LCD_Clear();
				 LCD_OutString("TIME OVER 30");
				 goto deh;
			 }
			 x=  calcTime(time)[0];
			 y= calcTime(time)[1];
			 //x=time/60; //minutes
			 //y=time -(x*60); //seconds
			 snprintf(buffer,10,"%02d",x);
			 strcat(buffer, ":");	
		/*	 snprintf(buffer2,10,"%02d",y);
			 strcat(buffer,buffer2);*/
			 LCD_Clear();
	    LCD_OutString(buffer);
			 
			
		 }else{
		    state=Err;
			 break;
		 }

		 counting(x,y);

}
else
{
	
	while(k<100){
		SysTick_Wait10ms(1);
		
	
	k++;
	goto deh;
		
	
	}
	
	break;
}
break;
	

case Case_D:
	previous_state=Case_D;
					LCD_OutString("Cooking time?");

					SysTick_Wait10ms(50);
					read_write();
					int m = duration();
          //calcTime(m);
					counting(calcTime(m)[0],calcTime(m)[1]);
					break;
	case Err:
		 LCD_Clear();
			 LCD_OutString("Err");
			 SysTick_Wait10ms(50);
	if(previous_state==Case_B)
	{state=Case_B;}
		else if(previous_state==Case_C)
		{state=Case_C;}
			 break;


}
SysTick_Wait10ms(20);
  //SysTick_Wait10ms(20);
	 
	 } 

}
