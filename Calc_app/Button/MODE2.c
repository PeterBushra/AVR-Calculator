#include "MODES.h"


void MODE2(void)
{
	ADC1_init();
	LCD_write_cmd_char( 0x0c, 0); //turn off Cursor
	CLRBIT(DDRD,PD5);//Turn off led
	CLRBIT(DDRD,PD4);//Turn off Buzzer

	SETBIT(DDRD,3);
	uint16_t temp = ADC1_read();
	LCD_write_cmd_char(0x80,0);
	LCD_write_txt((uint8_t*)"Mode 2");
	LCD_write_cmd_char(0xc0,0);
	LCD_write_number(ADC1_read());
	if (temp <= 300)
	{
		SETBIT(PORTD,3); // Relay on
	}
	else
	{
		CLRBIT(PORTD,3); // Relay Off
	}
}

