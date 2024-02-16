/*
 * Hardware_Interface.h
 *
 *  Created on: Feb 16, 2024
 *      Author: ramys
 */

#ifndef INC_HARDWARE_INTERFACE_H_
#define INC_HARDWARE_INTERFACE_H_

#define Keypad_Input_GPIO GPIOB
#define Keypad_Input_Start GPIO_PIN_6

#define Keypad_GPIO_Output GPIOB
#define Keypad_Output_Start GPIO_PIN_12

extern Matrix_Keypad_t kp;

/// @brief Reads the GPIO input pin status (Columns)
uint16_t Keypad_HW_GetInputs();

/// @brief Writes the GPIO output Status (Rows)
void Keypad_HW_SetOutputs(uint16_t Status);

/// @brief Used to generate a Delay
void Keypad_HW_Delay(uint32_t delay_ms);

/// @fn void Keypad_HW_Init()
/// @brief
/// Hold the hardware interface initialization
void Keypad_HW_Init();
#endif /* INC_HARDWARE_INTERFACE_H_ */
