/*
 * usart.c
 *
 * Created: 6/04/2023 2:24:19 pm
 *  Author: Josiah Brough
 */ 

#include "usart.h"


void readUsart(void)
{
	*p_buffer = UDR1; // Save byte
	switch (rxState)
	{
		case IDLE: 
		if (*p_buffer == START_BYTE) // Wait for a start byte
		{
			rxState = READ;
			p_buffer++;
		}
		break;
			
		case READ: // [start][instr][msb][lsb][stop][\0]
		if ((p_buffer == &buffer[4]) || (*p_buffer == STOP_BYTE)) // If at end of the array or byte is the stop byte
		{
			if (buffer[2] == STOP_BYTE) // Instruction only
			{
				instruction = buffer[1];
			}
			else if (buffer[3] == STOP_BYTE) // Instruction and one byte
			{
				instruction = buffer[1];
				setValue = buffer[2];
			}
			else if (buffer[4] == STOP_BYTE) // Instruction and two bytes
			{
				instruction = buffer[1];
				setValue = (buffer[2] << 8) + buffer[3];
			}
			execute_instruction = TRUE; // Set flag to true
				
			// Reset
			memset(buffer, 0, 6*sizeof(uint8_t)); // Clear the buffer
			p_buffer = &buffer[0]; // reset the point to the 0th index
			rxState = IDLE;
		}
		else
		{
			p_buffer++;
		}
		break;
	}
}

void sendUsart(char byte_to_send)
{
	while(txBufferFull); // Wait for tx buffer to be empty
	UDR1 = byte_to_send; // Write data to txBuffer
}

void sendAdcUsart(char input_device)
{
	ADMUX = input_device; // Set ADC input device
	startConversion;
	while(converisonRunning); // wait for conversion to complete
	char adc_val = ADCH; // Save converted ADC value
	sendUsart(adc_val);
}