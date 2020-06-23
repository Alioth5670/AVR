#ifndef _LCD_1602_H
#define _LCD_1602_H

#include "iom128v.h"
#include "macros.h"

#define uchar unsigned char
#define uint unsigned int

#define RS_ON  PORTA |= BIT(6);//RS÷√1
#define RS_OFF PORTA &= ~BIT(6);//RS÷√0

#define RW_ON  PORTA |= BIT(7);//RW÷√1
#define RW_OFF PORTA &= ~BIT(7);//RW÷√0

#define E_ON   PORTG |= BIT(2);//E÷√1
#define E_OFF  PORTG &= ~BIT(2);//E÷√0

void delay_us(uint n);
void delay_ms(uint i);
void Port_init(void);
void LCD_init(void);
void LCD_en_write(void);
void LCD_clear(void);
void Write_Instruction(uchar command);
void Write_Data(uchar Wdata);
void LCD_SET_XY(uchar X,uchar Y);
void LCD_write_str(uchar X,uchar Y,uchar *s);
void LCD_write_char(uchar X,uchar Y,uchar Wdata);

#endif

