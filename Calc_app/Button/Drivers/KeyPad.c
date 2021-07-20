
#include "KeyPad.h"
const uint8_t keypad_matrix[]={7,4,1,'C',8,5,2,'0',9,6,3,'=','/','*','-','+'};
uint8_t i;

void KeyPad_init(void)
{
	KEYPAD_INIT_PORT;	
}

uint8_t KeyPad_read(void)
{
	OUTPUT_PORT = 0b11101111;
	for(i=0; i<4;i++){
		if(READBIT(INPUT_PORT,i) == 0) return keypad_matrix[i];
	}
	_delay_ms(10);
	
	OUTPUT_PORT = 0b11011111;
	for(i=0; i<4;i++){
		if(READBIT(INPUT_PORT,i) == 0) return keypad_matrix[i+4];
	}
	_delay_ms(10);
	
	OUTPUT_PORT = 0b10111111;
	for(i=0; i<4;i++){
		if(READBIT(INPUT_PORT,i) == 0) return keypad_matrix[i+8];
	}
	_delay_ms(10);
	
	OUTPUT_PORT = 0b01111111;
	for(i=0; i<4;i++){
		if(READBIT(INPUT_PORT,i) == 0) return keypad_matrix[i+12];
	}
	_delay_ms(10);
	
	return 0;	//0xff	
}