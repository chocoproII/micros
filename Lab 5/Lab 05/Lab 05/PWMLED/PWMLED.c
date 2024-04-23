#include "PWMLED.h"

#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t CPD;
uint16_t CDT;

void PWM_a_patita (void){
	
	TCCR1B = 0;
	
	// Configura el preescalador del Timer/Counter1 a 1024
	TCCR1B |= (1 << CS12) | (1 << CS10);
	
	// Habilita la interrupción de desbordamiento del Timer/Counter1
	TIMSK1 |= (1 << TOIE1);
	

}

ISR(TIMER1_OVF_vect) {
	
	CPD++;
	CDT++;
	
	if (CPD > 19){
		CPD = 0;
		CDT = 0;
	}
