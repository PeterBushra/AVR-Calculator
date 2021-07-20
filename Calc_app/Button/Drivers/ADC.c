#include "ADC.h"

void ADC0_init()
{
	ADMUX = 0b01000000;
	ADCSRA|= 0b10000111;
}
uint16_t ADC0_read() // Return 10 bit ,, Adc Resoulation
{
	ADCSRA|= 0b01000000;
	while(READBIT(ADCSRA,ADSC));
	return (ADCL+(ADCH<<8));
}
void ADC1_init()
{
	ADMUX = 0b01000001;
	ADCSRA|= 0b10000111;
}
uint16_t ADC1_read() // Return 10 bit ,, Adc Resoulation
{
	ADCSRA|= 0b01000000;
	while(READBIT(ADCSRA,ADSC));
	return (ADCL+(ADCH<<8));
}
