#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define converisonRunning (ADCSRA & (1 << ADSC))
#define startConversion (ADCSRA |= (1 << ADSC))

void setupAdc(void);
char getAdcValue(char input_device);

#endif /* ADC_H_ */
