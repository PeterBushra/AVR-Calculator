#include "Calc_Funcs.h"
#define ModeC 3
uint8_t switch_Button;

void MODE3()
{	
		CLRBIT(PORTD,3);//Turn off Relay
		ResetData();
 		while(Flag == Start		&& switch_Button==ModeC)		{ GetData(); }
 		while(Flag == Analyze	&& switch_Button==ModeC)		{ Analysis(); }
 		while(Flag == calculate && switch_Button==ModeC)		{ Calculation(); }
 		while(Flag == Display	&& switch_Button==ModeC)		{ DisplayResult(); }	
		return ;
}

