#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "systick.h"

//	0x01    *  Clear display screen
//  0x02    *  Return to home position
//  0x04    *  Shift cursor to left
//  0x06    *  Shift cursor to right
//  0x05    *  Shift display right
//  0x07    *  Shift display left
//  0x08    *  Display off, Cursor off
//  0x0A    *  Display off, Cursor on
//  0x0C    *  Display on , Cursor off
//  0x0E    *  Display on , Cursor on 
//  0x0F    *  Display on , Cursor blinking
//  0x10    *  Shift cursor position to left
//  0x14    *  Shift cursor position to right
//  0x18    *  Shift entire display to left
//  0x1C    *  Shift entire display to right
//  0x20    *  Function set : 4-bit, 1 lines, 5x7 matrix
//  0x28    *  Function set : 4-bit, 2 lines, 5x7 matrix
//  0x30    *  Function set : 8-bit, 1 lines, 5x7 matrix
//  0x38    *  Function set : 8-bit, 2 lines, 5x7 matrix
//  0x80    *  Force cursor to start from 1st line
//  0xC0    *  Force cursor to start from 2nd line
//  0x90    *  Force cursor to start from 3rd line
//  0xD0    *  Force cursor to start from 4th line

void LCD_command(unsigned int command) { 
	
	GPIO_PORTA_DATA_R = 0;								// Set RS to 0 to enable Command Register and RW to 0 to write to the LCD
	GPIO_PORTB_DATA_R = command;
	GPIO_PORTA_DATA_R = 0x80;
	SysTick_Wait1microsec(5);
	GPIO_PORTA_DATA_R = 0x00;              	// High to Low pulse to push the command to the LCD
	if (command < 4) 
		SysTick_Wait10ms(10);                  	     	// Command 1 and 2 needs up to 1.64ms 
	else             
		SysTick_Wait10ms(40);                 	     	// All others 40 us

}

void LCD_setRowCol(unsigned int row, unsigned int col) {
	
	int command = 0x00;
	
	if(row == 0) {
		command = 0x80;
		while(col <= 0x0F && col) {
			
		 LCD_command(command + col);
		  break;
		}
	}
	
	if(row == 1) {
		command = 0xC0;
		while(col <= 0x0F && col) {
			
		  LCD_command(command + col);
		  break;
		}
	}
}