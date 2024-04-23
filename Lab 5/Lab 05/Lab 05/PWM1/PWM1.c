#include "PWM1.h"
void initPWM0FastB(uint8_t inverted, uint16_t precaler){
	//Pin de salida del servo 2 (OC0B)
	DDRD |=(1<<DDD5);
	
	
	//	TCCR0A = 0;
	TCCR0B = 0;
	
	if (inverted)
	{
		//Se deja el OC0A como invertido
		TCCR0A |= (1<<COM0B1)|(1<<COM0B0);
		}else{
		//Se deja el OC0A como no invertido
		TCCR0A |= (1<<COM0B1);
	}
	
	//Configura modo PWM FAST TOP = 0xFF
	TCCR0A |= (1<<WGM01)|(1<<WGM00);
	
	//Prescaler de 1024
	TCCR0B |= (1<<CS02)|(1<<CS00);
	
}

void updateDCB(uint8_t duty){
	OCR0B = duty;
}