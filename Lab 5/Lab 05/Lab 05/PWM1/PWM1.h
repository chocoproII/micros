
#ifndef PWM1_H_
#define PWM1_H_

#include <avr/io.h>
#include <stdint.h>

#define invertido 1
#define no_invertido 0


void initPWM0FastB(uint8_t inverted, uint16_t precaler);

void updateDCB(uint8_t duty);

#endif /* PWM1_H_ */