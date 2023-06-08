/*
 * usart.h
 *
 * Created: 6/04/2023 2:24:37 pm
 *  Author: Josiah Brough
 */ 
#ifndef USART
#define USART

#include <avr/interrupt.h>
#include <string.h>
#include <LabBoard.h>


volatile uint8_t instruction;
volatile int setValue;
volatile char execute_instruction; 

volatile char rxState;
volatile char buffer[6]; // [start][instr][lsb][msb][stop][\0]
volatile char *p_buffer;

#define FALSE 0
#define TRUE 1

#define IDLE 0
#define READ 1

#define START_BYTE 0x53
#define STOP_BYTE 0xAA

#define txBufferFull !(UCSR1A & (1<<UDRE1))
#define converisonRunning (ADCSRA & (1<<ADSC))
#define startConversion (ADCSRA |= (1<<ADSC))

#define DEFAULT 0xFF

void readUsart(void);
void sendUsart(char byte_to_send);
void sendAdcUsart(char input_device);

#endif