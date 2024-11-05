#ifndef USART_H_
#define USART_H_

// libraries
#include <avr/interrupt.h>
#include <avr/io.h>

// macros
#define txBufferFull !(UCSR1A & (1 << UDRE1))
#define START_BYTE 0x53
#define INST_IDX 1
#define MSB_IDX 2
#define LSB_IDX 3
#define STOP_BYTE 0xAA
#define isReadInstruction(inst) (inst < 0x0A)
#define NONE 0xFF
#define BUFFER_LEN 5

// types
enum UsartState_t { IDLE, READ };
enum InstReady_t { FALSE, TRUE };
struct serialCom_t {
    char buffer[BUFFER_LEN];
    char* p_buffer;
    enum UsartState_t state;
    enum InstReady_t instruction_ready;
    char instruction;
    int data;
};

// function prototypes
void readUsart(void);
void saveBuffer(void);
void sendUsart(char byte_to_send);
void setupUsart(void);
ISR(USART1_RX_vect);

// variable declarations
volatile struct serialCom_t* p_serialCom;

#endif /* USART_H_ */
