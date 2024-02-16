/*
 * Hardware_Interface.c
 *
 *  Created on: Feb 16, 2024
 *      Author: ramys
 */

#include "Hardware_Interface.h"
#include "stm32f1xx_hal.h"

uint16_t Keypad_HW_GetInputs() {
	uint16_t Input = Keypad_Input_GPIO->IDR & kp.IP_Mask;
	return (Input >> keypad->InputStartingPin);
}

void Keypad_HW_SetOutputs(uint16_t Status) {
	//turn off the pins
	keypad->OutputPort->BRR |= keypad->OP_Mask;
	//turn on only the needed ones according to the required output
	keypad->OutputPort->BSRR |= (OutputStat << keypad->OutputStartingPin);

}

void Keypad_HW_Delay(uint32_t delay_ms) {
	HAL_Delay(delay_ms);
}

void Keypad_HW_Init() {
	GPIO_InitTypeDef G = { .Mode = GPIO_MODE_OUTPUT_PP, .Speed =
	GPIO_SPEED_FREQ_LOW, .Pin = Keypad_Output_Start };

	//initialize the outputs
	for (int x = 0; x < kp.Rows - 1; x++) {
		G.Pin <<= 1;
		G.Pin |= Keypad_Output_Start;
	}
	HAL_GPIO_Init(Keypad_Input_GPIO, &G);
	kp.OP_Mask = G.Pin;

	//initialize the inputs
	G.Mode = GPIO_MODE_INPUT;
	G.Pull = GPIO_PULLDOWN;
	G.Pin = Keypad_Input_Start;
	for (int x = 0; x < kp.Columns - 1; x++) {
		G.Pin << 1;
		G.Pin |= Keypad_Input_Start;
	}
	HAL_GPIO_Init(Keypad_Input_GPIO, &G);
	kp.IP_Mask = G.Pin;
}
