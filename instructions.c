#include "instructions.h"

void setup16BitTimer(void) {
    TCCR1A = 0b10101010; // A, B and C fast PWM, ICR1 as top
    TCCR1B = 0b00011010; // ICR1 as top, div 8 pre-scaling
    ICR1 = 49;           // 20kHz
    OCR1C = 49;          // heater on
}

void setupIo(void) {
    DDRC = 0xFF;  // LEDs
    DDRA = 0x00;  // switches
    DDRE = 0x03;  // multiplexer
    PORTE = 0x00; // set multiplexer to switches
}

void exeInst(void) {
    switch (p_serialCom->instruction) {
        // read instructions
        case TX_CHECK:
            sendUsart(TX_CHECK);
            break;
        case READ_PINA:
            sendUsart(PINA);
            break;
        case READ_POT1:
            sendUsart(getAdcValue(POT1));
            break;
        case READ_POT2:
            sendUsart(getAdcValue(POT2));
            break;
        case READ_TEMP:
            sendUsart(getAdcValue(TEMPSENSOR));
            break;
        case READ_LDR:
            sendUsart(getAdcValue(LIGHTSENSOR));
            break;

        // set instructions
        // return 'instruction' to confirm completion
        case SET_PORTC:
            PORTC = (p_serialCom->data & 0xFF);
            sendUsart(SET_PORTC);
            break;
        case SET_HEATER:
            updatePeripheralState(HEATER);
            sendUsart(SET_HEATER);
            break;
        case SET_LAMP:
            updatePeripheralState(LAMP);
            OCR1B = p_serialCom->data;
            sendUsart(SET_LAMP);
            break;
        case SET_MOTOR:
            updatePeripheralState(MOTOR);
            OCR1A = p_serialCom->data;
            sendUsart(SET_MOTOR);
            break;
        default:
            break;
    }

    // reset values
    p_serialCom->data = 0;
    p_serialCom->instruction = NONE;
    p_serialCom->instruction_ready = FALSE;
}

void updatePeripheralState(char portBn) {
    if (p_serialCom->data > 0)
        enableBitPortB(portBn);
    else
        disableBitPortB(portBn);
}
