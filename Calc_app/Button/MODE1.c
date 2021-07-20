#include "MODES.h"



void MODE1(void)
{

	ADC0_init();
	uint16_t  j=0;
	SETBIT(DDRD,PD5);//led
	SETBIT(DDRD,PD4);//Relay
	LCD_write_cmd_char( 0x0c, 0); //turn off Cursor

	LCD_write_cmd_char(0x80,0);
	LCD_write_txt((uint8_t*)"Mode 1");
	LCD_write_cmd_char(0xc0,0);
	LCD_write_number(ADC0_read());
	j=ADC0_read();

	if((j>=100)&&(j<300))
	{
		duty_ocr1a_init(100);//Led
		duty_ocr1b_init(20);//Buzzer
	}
	else if((j>=300)&&(j<600))
	{
		duty_ocr1a_init(70);//Led
		duty_ocr1b_init(40);//Buzzer
	}
	else if((j>=600)&&(j<900))
	{
		duty_ocr1a_init(30);//Led
		duty_ocr1b_init(60);//Buzzer
	}
	else if(j>=900)
	{
		duty_ocr1a_init(10);//Led
		duty_ocr1b_init(80);//Buzzer
	}
	else
	{
		duty_ocr1a_init(0);//Led
		duty_ocr1b_init(0);//Buzzer
	}

}


