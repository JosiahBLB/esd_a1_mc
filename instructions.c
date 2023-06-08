/*
 * instructions.c
 *
 * Created: 6/04/2023 2:20:12 pm
 *  Author: qhs7289
 */ 

#include "instructions.h"


void executeInstruction()
{
	switch (instruction)
	{
	case TX_CHECK:
		sendUsart(TX_CHECK);
		break;
	
	// Sends back PINA
	case READ_PINA:
		sendUsart(PINA);
		break;
	
	// Sends back the ADC values	
	case READ_POT1:
		sendAdcUsart(pot1); 
		break;
		
	case READ_POT2:
		sendAdcUsart(pot2);
		break;
		
	case READ_TEMP:
		sendAdcUsart(tempSensor);
		break;
		
	case READ_LDR:
		sendAdcUsart(lightSensor);
		break;
	
	// Sets Peripherals	and returns instruction
	case SET_PORTC:
		PORTC = setValue;
		sendUsart(SET_PORTC);
		break;
		
	case SET_HEATER:
		if(setValue > 0)
			heaterOn;
		else
			heaterOff;
		OCR1C = 49;
		sendUsart(SET_HEATER);
		break;
		
	case SET_LAMP:
		if(setValue > 0)
			lampOn;
		else
			lampOff;
		OCR1B = setValue;
		sendUsart(SET_LAMP);
		break;
		
	case SET_MOTOR:
		if(setValue > 0)
			motorOn;
		else
			motorOff;
		OCR1A = setValue;
		sendUsart(SET_MOTOR);
		break;
		
	default:
		break;
	}
	instruction = DEFAULT; // Clear instruction on completion
	execute_instruction = FALSE; // reset flag to false
}