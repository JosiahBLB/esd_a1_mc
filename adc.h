#ifndef ADC_H_
#define ADC_H_

// libraries
#include <avr/io.h>

// macros
#define converisonRunning (ADCSRA & (1 << ADSC))
#define startConversion (ADCSRA |= (1 << ADSC))

// function prototypes
void setupAdc(void);
char getAdcValue(char input_device);

#endif /* ADC_H_ */
