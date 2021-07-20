#ifndef CALC_FUNCS_H_
#define CALC_FUNCS_H_

#include "Drivers/stdMacros.h"
#include "Drivers/LCD.h"
#include "Drivers/KeyPad.h"

typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef signed long long sint64;

#define IsOp(x) ((x=='*')||(x=='+')||(x=='-')||(x=='/')||(x=='='))
#define Nums ((1||2||3||4||5||6||7||8||9||0))
#define Operands (('+'||'-'||'*'||'/'))
void ResetData();
void GetData();
void Calculation();
void DisplayResult();
void Errors(uint8_t*);
void Analysis();
sint32 contcatnate(uint8_t pow);
void delete_node(uint8_t node);


enum Points {Reset,Start,Analyze,calculate,Display,Error};
enum States {false,true};

extern uint8_t Flag;


#endif /* CALC_FUNCS_H_ */
