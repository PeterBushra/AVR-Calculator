

#ifndef LCD_H_
#define LCD_H_

#include "stdmacros.h"
typedef signed short sint16;
#define init_port_lcd DDRA |= 0b11110000; DDRB |= 0b00001110;
#define RW(x) if(x==0)CLRBIT(PORTB,2);else SETBIT(PORTB,2); // RW=0 To Write  .. 1 To READ
#define RS(x) if(x==0)CLRBIT(PORTB,1);else SETBIT(PORTB,1); // Rs=0 TO Command .. 1 To data
#define EN(x) if(x==0)CLRBIT(PORTB,3);else SETBIT(PORTB,3); //Enable
#define D7(x) if(x==0)CLRBIT(PORTA,7);else SETBIT(PORTA,7);
#define D6(x) if(x==0)CLRBIT(PORTA,6);else SETBIT(PORTA,6);
#define D5(x) if(x==0)CLRBIT(PORTA,5);else SETBIT(PORTA,5);
#define D4(x) if(x==0)CLRBIT(PORTA,4);else SETBIT(PORTA,4);

void LCD_init();
void LCD_write_cmd_char(uint8_t,uint8_t);
void LCD_write_txt(uint8_t*);
void LCD_write_num(uint16_t);
void LCD_write_number(uint16_t num);

#endif