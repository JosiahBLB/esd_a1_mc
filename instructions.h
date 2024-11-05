/*
 * instructions.h
 *
 * Created: 6/04/2023 2:20:32 pm
 *  Author: qhs7289
 */

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "adc.h"
#include "usart.h"
#include <avr/io.h>

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

#define POT1 0b01100010
#define POT2 0b01100001
#define TEMPSENSOR 0b01100011
#define LIGHTSENSOR 0b01100000

#define MOTOR 5
#define LAMP 6
#define HEATER 7

#define enableBitPortB(bit) (DDRB |= (1 << bit))
#define disableBitPortB(bit) (DDRB &= ~(1 << bit))

void setup16BitTimer(void);
void setupIo(void);
void exeInst(void);
void updatePeripheralState(char portBn);

#endif /* ADC_H_ */
