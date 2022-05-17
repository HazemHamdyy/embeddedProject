
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"



void keypad_Init(void){ 
	
 SYSCTL_RCGCGPIO_R |=0x3F;
	while((SYSCTL_PRGPIO_R & 0x3F)==0);
	GPIO_PORTE_LOCK_R =0X4C4F434B;
	GPIO_PORTE_CR_R|=0X0F; 
	GPIO_PORTE_DIR_R|= 0x0F; // set row pins 3-0 as output
	GPIO_PORTE_DEN_R |= 0x0F; //set row pins 3-0 as digital pins
	GPIO_PORTE_ODR_R|= 0x0F; // set row pins 3-0 as open drain 
	
	GPIO_PORTA_LOCK_R =0X4C4F434B;
	GPIO_PORTA_CR_R |=0X3C;
	GPIO_PORTA_DIR_R|= ~0x3C; // set column pin 4-1 as input
	GPIO_PORTA_DEN_R|= 0x3C; //set column pin 4-1 as digital pins
	GPIO_PORTA_PUR_R |= 0x3C;// enable pull-ups for pin 4-1

}
 char keypad_getkey(void)
	 {
		 const unsigned char keymap[4][4]=
    {
    {'1','2','3','A'},
	  {'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'},
    };
		int row ,col;
    
    GPIO_PORTE_DATA_R=0;
		col=GPIO_PORTA_DATA_R & 0x3C;
    if(col==0x3C) return 0;
		while(1)
		{
			row=0;
			GPIO_PORTE_DATA_R=0X0E;
			SysTick_Wait1microsec(2);
			col=GPIO_PORTA_DATA_R & 0x3C;
			if(col !=0X3C) break;
			
			row=1;
		  GPIO_PORTE_DATA_R=0X0D;
			SysTick_Wait1microsec(2);
			col=GPIO_PORTA_DATA_R & 0x3C;
			if(col !=0X3C) break;
			
			row=2;
			GPIO_PORTE_DATA_R=0X0B;
			SysTick_Wait1microsec(2);
			col=GPIO_PORTA_DATA_R & 0x3C;
			if(col !=0X3C) break;
			
			row=3;
			GPIO_PORTE_DATA_R=0X07;
			SysTick_Wait1microsec(2);
			col=GPIO_PORTA_DATA_R & 0x3C;
			if(col !=0X3C) break;
			return 0; //if no key is pressed
		}
		if(col ==0X38) return keymap[row][0];
		if(col ==0X34) return keymap[row][1];
		if(col ==0X2C) return keymap[row][2];
		if(col ==0X1C) return keymap[row][3];
	 return 0;
	 }
