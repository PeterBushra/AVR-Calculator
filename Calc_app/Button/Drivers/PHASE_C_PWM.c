#include "PHASE_C_PWM.h"

void pwm_ocr1a_init()
{
	TCCR1A |= 0b10000011;
	TCCR1B |= 0b00001001;
	
} 
void duty_ocr1a_init(uint8_t data)
{
	OCR1A = (data)*(((float)1023)/((float)100));
	
}
void pwm_ocr1b_init()
{
	TCCR1A |= 0b00100011;
	TCCR1B |= 0b00001001;
	
}
void duty_ocr1b_init(uint8_t data)
{
	OCR1B = (data)*(((float)1023)/((float)100));
	
}

