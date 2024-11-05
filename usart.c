#include "usart.h"

void setupUsart(void) {
    cli();               // clear interrupts
    UCSR1B = 0b10011000; // enable receiver and it's interrupt
    UCSR1C = 0b00000110; // 1 stop bit, 8 bit character size, no parity bits
    UBRR1L = 12;         // baud rate set to 38400

    // init globals
    static struct serialCom_t serialCom = {
        .buffer = { 0 }, // zero initiaize array
        .state = IDLE,
        .instruction_ready = FALSE,
        .instruction = NONE,
        .data = 0,
    };
    serialCom.p_buffer = serialCom.buffer;
    p_serialCom = &serialCom;

    sei(); // set interrupts
}

void readUsart(void) {
    // read in the next byte
    *(p_serialCom->p_buffer) = UDR1;

    switch (p_serialCom->state) {
        case IDLE: // wait till start byte
            if (*(p_serialCom->p_buffer) == START_BYTE) {
                p_serialCom->state = READ;
                *(p_serialCom->p_buffer) = 0; // clear start byte
                p_serialCom->p_buffer++;
            }
            break;
        case READ: // save all data to buffer
            p_serialCom->p_buffer++;
            if (p_serialCom->p_buffer ==
                &p_serialCom->buffer[4]) { // end of buffer, reset
                p_serialCom->p_buffer = p_serialCom->buffer;
                p_serialCom->instruction_ready = TRUE;
                p_serialCom->state = IDLE;
            }
            break;
    }
}

void saveBuffer(void) {
    // extract data from buffer
    p_serialCom->instruction = p_serialCom->buffer[INST_IDX];
    p_serialCom->data = (p_serialCom->buffer[MSB_IDX] << 8);
    p_serialCom->data += p_serialCom->buffer[LSB_IDX];
}

void sendUsart(char byte_to_send) {
    while (txBufferFull) // wait for tx buffer to empty
        ;
    UDR1 = byte_to_send; // send byte
}

ISR(USART1_RX_vect) {
    readUsart();
}
