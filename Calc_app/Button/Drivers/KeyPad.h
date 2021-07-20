#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "stdMacros.h"

#define KEYPAD_INIT_PORT DDRC= 0xf0;PORTC= 0x0f
#define INPUT_PORT PINC
#define OUTPUT_PORT PORTC

void KeyPad_init(void);
uint8_t KeyPad_read(void);




#endif /* KEYPAD_H_ */