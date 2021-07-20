#ifndef MODES_H_
#define MODES_H_

void MODE1(void);
void MODE2(void);
void MODE3(void);

#include "Drivers/ADC.h"
#include "Drivers/LCD.h"
#include "Drivers/PHASE_C_PWM.h"
#include "Drivers/UART.h"
#include "Drivers/KeyPad.h"

#define ModeA 1
#define ModeB 2
#define ModeC 3



#endif /* MODES_H_ */