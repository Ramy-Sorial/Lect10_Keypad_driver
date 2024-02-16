/*
 * Hardware_Interface.c
 *
 *  Created on: Feb 16, 2024
 *      Author: ramys
 */

#include "Hardware_Interface.h"
#include "stm32f1xx_hal.h"

uint16_t Keypad_HW_GetInputs() {
	return (uint32_t) (Keypad_Input_GPIO->IDR & kp.IP_Mask)
			>> Keypad_Input_Start;
}

void Keypad_HW_SetOutputs(uint16_t Status) {
	//turn off the pins
	Keypad_GPIO_Output->BRR |= kp.OP_Mask;
	//turn on only the needed ones according to the required output
	Keypad_GPIO_Output->ODR |= (Status << Keypad_Output_Start);
}

void Keypad_HW_Delay(uint32_t delay_ms) {
	HAL_Delay(delay_ms);
}

Matrix_Keypad_t kp = {
		.Columns = 4,
		.Rows = 4,
		.HW_Interface = {
						.Keypad_GetInputs = Keypad_HW_GetInputs,
						.Keypad_SetOutputs = Keypad_HW_SetOutputs,
						.Keypad_Delay = Keypad_HW_Delay
		},
};

void Keypad_HW_Init() {
	//enable the clock
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//create an ini struct
	GPIO_InitTypeDef G = {
			.Mode = GPIO_MODE_OUTPUT_PP,
			.Speed = GPIO_SPEED_FREQ_LOW,
			.Pin = 1 << Keypad_Output_Start
	};

	//initialize the outputs
	for (int x = 0; x < kp.Rows - 1; x++) {
		G.Pin <<= 1;
		G.Pin |= (1 << Keypad_Output_Start);
	}
	HAL_GPIO_Init(Keypad_Input_GPIO, &G);
	kp.OP_Mask = G.Pin;

	//initialize the inputs
	G.Mode = GPIO_MODE_INPUT;
	G.Pull = GPIO_PULLDOWN;
	G.Pin = 1 << Keypad_Input_Start;
	for (int x = 0; x < kp.Columns - 1; x++) {
		G.Pin <<= 1;
		G.Pin |= (1 << Keypad_Input_Start);
	}
	HAL_GPIO_Init(Keypad_Input_GPIO, &G);
	kp.IP_Mask = G.Pin;

	//Initialize the driver
	Keypad_Init(&kp);
}
