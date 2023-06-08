/*
 * instructions.h
 *
 * Created: 6/04/2023 2:20:32 pm
 *  Author: qhs7289
 */ 

#ifndef INSTRUCTION
#define INSTRUCTION

#include <avr/io.h>
#include "usart.h"

#define TX_CHECK 0x00
#define READ_PINA 0x01
#define READ_POT1 0x02
#define READ_POT2 0x03
#define READ_TEMP 0x04
#define READ_LDR 0x05

#define SET_PORTC 0x0A
#define SET_HEATER 0x0B
#define SET_LAMP 0x0C
#define SET_MOTOR 0x0D

#define pot1 0b01100010
#define pot2 0b01100001
#define tempSensor 0b01100011
#define lightSensor 0b01100000

#define motorOff (DDRB &= ~(1<<5))
#define motorOn (DDRB |= (1<<5))
#define lampOff (DDRB &= ~(1<<6))
#define lampOn (DDRB |= (1<<6))
#define heaterOff (DDRB &= ~(1<<7))
#define heaterOn (DDRB |= (1<<7))

ISR(USART1_RX_vect);
void setup(void);

#endif