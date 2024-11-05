#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

// libraries
#include "adc.h"
#include "usart.h"
#include <avr/io.h>

// instructions
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

// for setting ADMUX
#define LIGHTSENSOR 0b01100000 // ADC 0
#define POT2 0b01100001        // ADC 1
#define POT1 0b01100010        // ADC 2
#define TEMPSENSOR 0b01100011  // ADC 3

// enabling/disabling DDRBn
#define MOTOR 5
#define LAMP 6
#define HEATER 7
#define enableBitPortB(bit) (DDRB |= (1 << bit))
#define disableBitPortB(bit) (DDRB &= ~(1 << bit))

// function prototypes
void setup16BitTimer(void);
void setupIo(void);
void exeInst(void);
void updatePeripheralState(char portBn);

#endif /* ADC_H_ */
