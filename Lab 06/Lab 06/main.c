//******************************************************************************
//Universidad del Valle de Guatemala
//IE2023: Programación de Microcontroladores
//Autor: Gabriel Sanchez
//Proyecto: Laboratorio 06
//Hardware: ATMEGA328P
//Creado: 22/04/2024
//Última modificación: 28/04/2024
//******************************************************************************
#include <avr/io.h>
#include <util/delay.h>

//Definicion de valores de reloj
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE F_CPU/16/BAUD - 1

// Encendemos el UART 
void UART_init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Definimos funcion para transmitir datos con UART
void UART_transmit(unsigned char data) {
//Verificamos espacio y que queden datos
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

// Definimos funcion para recibir datos con UART
unsigned char UART_receive(void) {
//Verificamos espacio y si aun quedan datos por recibir
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

//Creamos funcion para emitir cadenas de texto
void parrafouart(const char* text) {
	for (int i = 0; text[i] != '\0'; i++) {
		UART_transmit(text[i]);
	}
}

//Creamos una secuencia para nuestro menu
void print_menu() {
	parrafouart("Menu:\n");
	parrafouart("T - Leer potenciómetro\n");
	parrafouart("R - Recibir\n");
}

//Seccion de definicion y configuracion del ADC para el potenciometro
void ADC_init() {
	ADMUX |= (1 << REFS0);
	//Prescaler a 128
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_read(uint8_t channel) {
	//definimos con que canal vamos a trabajar
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	// Iniciamos a convertir
	ADCSRA |= (1 << ADSC);
	// Esperamos a que ya no hallan datos para convertir :y
	while (ADCSRA & (1 << ADSC));
	// Lectura de ADC 
	return ADC;
}

int main(void) {
	UART_init(UBRR_VALUE);
	ADC_init();
	DDRB = 0xFF; // Configurar Puerto B como salida

	while(1) {
		char mode;

		print_menu();

		mode = UART_receive();

		if (mode == 'T') {
			// Leer el valor del potenciómetro en ADC6
			uint16_t pot_value = ADC_read(6);
			//Vamos a mostrar cada digito por separado, de centenas para abajo 
			//Seccion centenas
			UART_transmit((pot_value / 100) + '0');
			// Seccion decenas
			UART_transmit(((pot_value / 10) % 10) + '0');
			// Seccion unidades
			UART_transmit((pot_value % 10) + '0');
			// Hacemos un salto de linea por estetica 
			UART_transmit('\n');
			} else if (mode == 'R') {
			//Definimos la seccion de enviar ASCII a los LEDS
			char received_char = UART_receive();
			PORTB = received_char;
		}
	}
	return 0;
}
