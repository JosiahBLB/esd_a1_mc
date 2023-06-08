/*
 * GccApplication1.c
 *
 * Created: 6/04/2023 12:51:59 pm
 * Author : Josiah Brough
 */ 


#include "instructions.h"


int main(void)
{	
    setup();
    while (1) 
    {
		if (execute_instruction) // flag to see if instruction should be executed
		{
			executeInstruction();
		}
    }
}

void setup(void)
{
	cli(); // Clear interrupts
	
	// I/O
	DDRC = 0xFF;
	DDRA = 0x00;
	DDRE = 0x03;
	PORTE = 0x00;
	
	// USART
	UCSR1B = 0b10011000;//enable receiver and it's interrupt
	UCSR1C = 0b00000110;//1 stop bit, 8 bit character size, no parity bits
	UBRR1L = 12;//Baud rate set to 38400
	
	// ADC
	ADMUX = 0x01100000;
	ADCSRA = 0b11000111; // Enable ADC, start conversion, free running mode, slowest speed

	// 16-bit timer
	TCCR1A = 0b10101010; // A, B and C fast PWM, ICR1 as top
	TCCR1B = 0b00011010; // ICR1 as top, div 8 pre-scaling
	ICR1 = 49; // 20kHz
	
	// Initialize variables
	instruction = DEFAULT;
	execute_instruction = FALSE;
	p_buffer = &buffer;
		
	sei(); // Set interrupts
}

ISR(USART1_RX_vect)
{
	readUsart();
}