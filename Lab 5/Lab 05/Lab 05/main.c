//******************************************************************************
//Universidad del Valle de Guatemala
//IE2023: Programación de Microcontroladores
//Autor: Gabriel Sanchez
//Proyecto: Laboratorio 05
//Hardware: ATMEGA328P
//Creado: 14/04/2024
//Última modificación: 15/04/2024
//******************************************************************************

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "PWM0/PWM0.h"
#include "PWM1/PWM1.h"
#include "PWMLED/PWMLED.h"
void setup(void);

//Seccion de variables
unsigned char pot_value = 0; //Contador binario de 8 bits sin signo
uint8_t dutyCycle1 = 0;
uint8_t dutyCycle2 = 0;
uint8_t dutyCycle3 = 0;

extern uint16_t CPD;
extern uint16_t CDT;

//Encendido del PWM con timer 
void setup_timer1_pwm() {
	// Configurar el Timer1 para modo PWM de 8 bits (Ajuste en fase, no invertido)
	TCCR1A |= (1 << COM1A1) | (1 << WGM10);
	TCCR1B |= (1 << WGM12) | (1 << CS11); // Preescalador de 8
	
	// Configurar el pin OC1A (pin 3 en el Arduino Nano) como salida
	DDRD |= (1 << PD3);
}
//Le decimos al timer 0 que trabaje con las bases de duty cicle
void set_pwm_duty_cycle(uint8_t duty_cycle) {
	// Establecer el ciclo de trabajo (duty cycle) del PWM
	OCR1A = duty_cycle;
}

//Seccion de encendido del ADC
void ADC_init(void) {
	ADMUX |= (1 << REFS0);
	//Se enciende el ISR del ADC
	ADCSRA |= (1<<ADIE);

	//Se deja encendido el ADC
	//Prescaler definido
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	DIDR0 |= (1<<ADC5D); 
}

// Función para leer el valor del ADC
uint16_t ADC_read(uint8_t adc_channel) {
	// Limpiar los bits de selección de canal anterior
	ADMUX &= 0xF0;
	// Seleccionar el canal de ADC
	ADMUX |= adc_channel;
	// Iniciar la conversión
	ADCSRA |= (1 << ADSC);
	// Esperar hasta que la conversión esté completa
	while (ADCSRA & (1 << ADSC));
	// Devolver el valor del ADC
	return ADC;
}

// Función para leer el valor del ADC
uint16_t ADC_read2(uint8_t adc_channel2) {
	// Limpiar los bits de selección de canal anterior
	ADMUX &= 0xF0;
	// Seleccionar el canal de ADC
	ADMUX |= adc_channel2;
	// Iniciar la conversión
	ADCSRA |= (1 << ADSC);
	// Esperar hasta que la conversión esté completa
	while (ADCSRA & (1 << ADSC));
	// Devolver el valor del ADC
	return ADC;
}

// Función para leer el valor del ADC
uint16_t ADC_read3(uint8_t adc_channel3) {
	// Limpiar los bits de selección de canal anterior
	ADMUX &= 0xF0;
	// Seleccionar el canal de ADC
	ADMUX |= adc_channel3;
	// Iniciar la conversión
	ADCSRA |= (1 << ADSC);
	// Esperar hasta que la conversión esté completa
	while (ADCSRA & (1 << ADSC));
	// Devolver el valor del ADC
	return ADC;
}

int main(void)
{
	initPWM0FastA(0,1024);
	initPWM0FastB(0,1024);
	setup();
	ADC_init();
    // Llamar a la función de configuración del Timer1 para PWM
    setup_timer1_pwm();
	updateDCA(0);
	updateDCB(0);
	PWM_a_patita();
    while (1) 
    {	 
		 // Configurar el ciclo de trabajo del PWM (0 a 255)	
		uint16_t dutyCycle1 = ADC_read(6);	
		_delay_ms(10);
		uint16_t dutyCycle2 = ADC_read2(7);
		uint16_t dutyCycle3 = ADC_read3(5);
		uint16_t VRL = valorADC(5);
		
		updateDCA(dutyCycle1);
		updateDCB(dutyCycle2);
		set_pwm_duty_cycle(dutyCycle3);
		_delay_ms(25);
		// Encender la salida del PWM si el ciclo de trabajo es menor que el valor del ADC
		 if (CDT < VRL) {
		  PORTD |=(1 << DDD3) ; }
		  else {PORTD &= ~(1 << DDD3);}
				   
    }
}

void setup(void){
 DDRC |= (1 << DDC3);
}