/*
 * Matrix_Keypad.c
 *
 *  Created on: Jan 31, 2024
 *      Author: ramys
 */

#include "Matrix_Keypad_Imp.h"

void Keypad_Refresh(Matrix_Keypad_t *keypad) {
	// temporary variable to store the new status of keys
	uint32_t TempKeys = 0;
	uint16_t OutputStat = 1 << (keypad->Rows - 1);

	uint16_t x = 0;
	do {

		TempKeys <<= keypad->Columns;
		// send the output status to the hardware
		keypad->HW_Interface.Keypad_SetOutputs(OutputStat);
		keypad->HW_Interface.Keypad_Delay(1);
		// read the input status from the hardware

		TempKeys |= keypad->HW_Interface.Keypad_GetInputs();
		OutputStat >>= 1;
		x++;
	} while (x < keypad->Rows);

	keypad->KeysStatus = TempKeys;
}

void Keypad_Init(Matrix_Keypad_t *keypad) {

	// turn off all the outputs
	keypad->HW_Interface.Keypad_SetOutputs(0);
}

uint8_t Keypad_Get_Key(Matrix_Keypad_t *keypad, uint8_t key) {
	return (keypad->KeysStatus & (1 << key)) ? 1 : 0;
}
