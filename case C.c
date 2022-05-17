#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "Keypad.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Caseb&c.h"




void chicken (void)
{ int weight,i,j;
	char key; 
	if(((GPIO_PORTE_DATA_R&0x10)==0x10) && (GPIO_PORTF_DATA_R &0x11)==0x01) //SW2 should always be pressed and sw3 should be open 
	{	LCD_OutString("Chicken weight?");
          OutCmd(0xC0); ////Set LCD Cursor to second line
           SysTick_Wait10ms(10);
int k =0;
		int time;

 weight=keypad_getkey();

if (weight!=0){

	LCD_OutChar(weight);
	SysTick_Wait10ms(10);
	bool invalid = CheckInValidNum(weight);
    // time=CookingTime(weight);
		
    while (invalid) // invalid true
    {
        printf("ERR \n");
				 SysTick_Wait10ms(50);
       /* while (getchar() != '\n')
        {
            continue;
        }
			*/

       weight=keypad_getkey();
       invalid = CheckInValidNum(weight);
    }
    if (!invalid)
    {
        double timeps;
       timeps =CookingTimeChicken(weight);
        int minutes = timeps / 60;
        int seconds = timeps - (minutes * 60); // calculate remaining seconds
        int i = minutes;
        unsigned char buffer1[5];
        unsigned char buffer2[5];
        do
        {
            for (int j = seconds; j >= 0; j--)
            {
                snprintf(buffer1, 10, "%02d", i); // to convert minutes and seconds into strings
                strcat(buffer1, ":");
                snprintf(buffer2, 10, "%02d", j);
                strcat(buffer1, buffer2);
                printf("%s", buffer1);
                // LCD_Clear();
                // CD_OutString(buffer1);
                // SysTick_Wait10ms(100); //display for 1 second
                // LCD_Clear();
                printf("\n");
            }

            seconds = 59;
            i--;
        } while (i >= 0);
    }
			

		 }

}

}
	