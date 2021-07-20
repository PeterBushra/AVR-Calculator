#include "UART.h"

void UART_init()
{
	SETBIT(UCSRB,RXEN);
	SETBIT(UCSRB,TXEN);
	SETBIT(UCSRB,RXCIE);
	SETBIT(UCSRB,TXCIE);
	SREG = 1<<7;	
	UBRRL = 77;
}
void UART_trans(uint8_t data)
{
	while(!READBIT(UCSRA,UDRE));
	UDR = data;
}
uint8_t UART_rec()
{
	while(!READBIT(UCSRA,RXC));
	return UDR;
	
}
