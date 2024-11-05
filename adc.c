#include "adc.h"

void setupAdc(void) {
    ADMUX = 0x01100000;  // left adjust and default to input device 0
    ADCSRA = 0b11000111; // enable ADC, start conversion, free running mode,
                         // slowest speed
}

char getAdcValue(char input_device) {
    ADMUX = input_device; // set ADC input device
    startConversion;
    while (converisonRunning)
        ;        // wait for conversion to complete
    return ADCH; // return converted digital value
}
