#include "PWM0.h"

void initPWM0FastA(uint8_t inverted, uint16_t precaler){
		//Pin de salida del servo 1 (OC0A)
		DDRD |=(1<<DDD6);
		
		
		TCCR0A = 0;
//		TCCR0B = 0;

	if (inverted)
	{
		//Se deja el OC0A como invertido
		TCCR0A |= (1<<COM0A1)|(1<<COM0A0);
		}else{
		//Se deja el OC0A como no invertido
		TCCR0A |= (1<<COM0A1);
	}

				
		//Configura modo PWM FAST TOP = 0xFF
		TCCR0A |= (1<<WGM01)|(1<<WGM00);
		
		if (precaler==1024)
		{
		//Prescaler de 1024
		TCCR0B |= (1<<CS02)|(1<<CS00);	
		}
}



void updateDCA(uint8_t duty){
	OCR0A = duty;	
}
/*
void updateDCB(uint8_t duty){
	OCR0B = duty;
}
*/
