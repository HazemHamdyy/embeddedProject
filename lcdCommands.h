#include <stdio.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"


#define  CLEAR_DISPLAY            ((unsigned char) 0X01 )
#define  HOME_POSITION            ((unsigned char) 0X02 )
#define  SHIFT_CURSOR_LEFT        ((unsigned char) 0X04 )
#define  SHIFT_CURSOR_RIGHT       ((unsigned char) 0X06 )
#define  SHIFT_DISPLAY_LEFT       ((unsigned char) 0X07 )
#define  SHIFT_DISPLAY_RIGHT      ((unsigned char) 0X05 )
#define  DISPLAY_OFF_CURSOR_OFF   ((unsigned char) 0X08 )
#define  DISPLAY_OFF_CURSOR_ON    ((unsigned char) 0X0A )
#define  DISPLAY_ON_CURSOR_OFF    ((unsigned char) 0X0C )
#define  DISPLAY_ON_CURSOR_ON     ((unsigned char) 0X0E )
#define  DISPLAY_ON_CURSOR_BLINK  ((unsigned char) 0X0F )
#define  FUNC_SET_4BIT_1LINE      ((unsigned char) 0X020)
#define  FUNC_SET_4BIT_2LINE      ((unsigned char) 0X028)
#define  FUNC_SET_8BIT_1LINE      ((unsigned char) 0X030)
#define  FUNC_SET_8BIT_2LINE      ((unsigned char) 0X038)
#define  CURSOR_START_1ST_LINE    ((unsigned char) 0X80 )
#define  CURSOR_START_2ND_LINE    ((unsigned char) 0XC0 )


void LCD_Init              (void);
void LCD_command           (unsigned int);
void LCD_setRowCol(unsigned int row, unsigned int col);
