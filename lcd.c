/*
  ground = pin 1    Vss
  power  = pin 2    Vdd    
  ground = pin 3    Vlc   
  PA6    = pin 4    RS    
  ground = pin 5    R/W   
  PA7    = pin 6    E     
  PB0    = pin 7    DB0   
  PB1    = pin 8    DB1
  PB2    = pin 9    DB2
  PB3    = pin 10   DB3
  PB4    = pin 11   DB4
  PB5    = pin 12   DB5
  PB6    = pin 13   DB6
  PB7    = pin 14   DB7

*/
#include <stdint.h>
#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "systick.h"

#define E  0x80 // on PA7
#define RS 0x40 // on PA6
#define LCDDATA (*((volatile uint32_t *)0x400053FC))   // PORTB
#define LCDCMD (*((volatile uint32_t *)0x40004300))    // PA7-PA6
//#define Freq 80            // assuming a 80 MHz bus clock
//#define T6us 6*Freq        // 6us
//#define T40us 40*Freq      // 40us
//#define T160us 160*Freq    // 160us
//#define T1600us 1600*Freq  // 1.60ms
//#define T5ms 5000*Freq     // 5ms
//#define T15ms 15000*Freq   // 15ms
void OutCmd(unsigned char command){
  LCDDATA = command;
  LCDCMD = 0;           // E=0, R/W=0, RS=0
	SysTick_Wait1microsec(6);
  //SysTick_Wait(T6us);   // wait 6us
  LCDCMD = E;           // E=1, R/W=0, RS=0
	SysTick_Wait1microsec(6);
  //SysTick_Wait(T6us);   // wait 6us
  LCDCMD = 0;           // E=0, R/W=0, RS=0
	SysTick_Wait1microsec(40);
  //SysTick_Wait(T40us);  // wait 40us
}

// Initialize LCD
// Inputs: none
// Outputs: none
void LCD_Init(void){ volatile long delay;
  SYSCTL_RCGC2_R |= 0x00000003;  // 1) activate clock for Ports A and B
  delay = SYSCTL_RCGC2_R;        // 2) no need to unlock
  GPIO_PORTB_AMSEL_R &= ~0xFF;   // 3) disable analog function on PB7-0
  GPIO_PORTA_AMSEL_R &= ~0xC0;   //    disable analog function on PA7-6              
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) configure PB7-0 as GPIO   
  GPIO_PORTA_PCTL_R &= ~0xFF000000; //    configure PA7-6 as GPIO
  GPIO_PORTB_DIR_R = 0xFF;       // 5) set direction register
  GPIO_PORTA_DIR_R |= 0xC0;
  GPIO_PORTB_AFSEL_R = 0x00;     // 6) regular port function
  GPIO_PORTA_AFSEL_R &= ~0xC0;
  GPIO_PORTB_DEN_R = 0xFF;       // 7) enable digital port
  GPIO_PORTA_DEN_R |= 0xC0;
  GPIO_PORTB_DR8R_R = 0xFF;      // enable 8 mA drive
  GPIO_PORTA_DR8R_R |= 0xC0;
  SysTick_Init();       
  LCDCMD = 0;           // E=0, R/W=0, RS=0
	SysTick_Wait1microsec(15000);
  //SysTick_Wait(T15ms);  // Wait >15 ms after power is applied
  OutCmd(0x30);         // command 0x30 = Wake up
	SysTick_Wait1microsec(5000);
  //SysTick_Wait(T5ms);   // must wait 5ms, busy flag not available
  OutCmd(0x30);         // command 0x30 = Wake up #2
	SysTick_Wait1microsec(160);
  //SysTick_Wait(T160us); // must wait 160us, busy flag not available
  OutCmd(0x30);         // command 0x30 = Wake up #3
	SysTick_Wait1microsec(160);
  //SysTick_Wait(T160us); // must wait 160us, busy flag not available
  OutCmd(0x38);         // Function set: 8-bit/2-line
  OutCmd(0x10);         // Set cursor
  OutCmd(0x0C);         // Display ON; Cursor ON
  OutCmd(0x06);         // Entry mode set
}
// Output a character to the LCD
// Inputs: letter is ASCII character, 0 to 0x7F
// Outputs: none
void LCD_OutChar(unsigned char letter){
  LCDDATA = letter;
  LCDCMD = RS;          // E=0, R/W=0, RS=1
	SysTick_Wait1microsec(6);
  //SysTick_Wait(T6us);   // wait 6us
  LCDCMD = E+RS;        // E=1, R/W=0, RS=1
	SysTick_Wait1microsec(6);
  //SysTick_Wait(T6us);   // wait 6us
  LCDCMD = RS;          // E=0, R/W=0, RS=1
	SysTick_Wait1microsec(40);
  //SysTick_Wait(T40us);  // wait 40us
}

