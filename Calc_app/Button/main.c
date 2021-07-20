//Peter Boshra 
#include "MODES.h"
extern uint8_t switch_Button;

int main(void)
{	
	UART_init();
	pwm_ocr1a_init();
	pwm_ocr1b_init();
	KeyPad_init();
	LCD_init();
	switch_Button=1;
	MCUCR = 0b10;//Rising Falling Edge
	GICR  = 1<<6;
	SREG  = 1<<7;
    while (1) 

    {			
			if(switch_Button == ModeA)		{MODE1();}
 	 	    if(switch_Button == ModeB)		{MODE2();}
 	 	    if(switch_Button == ModeC)		{MODE3();}
	}
}

ISR(INT0_vect)
 {	
	 
	switch_Button++;
	if (switch_Button > ModeC )
		{
			switch_Button = ModeA ; //if C come A
		}		
 }