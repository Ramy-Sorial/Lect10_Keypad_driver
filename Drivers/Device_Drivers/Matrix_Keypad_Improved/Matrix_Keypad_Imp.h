/*
 * Matrix_Keypad.h
 *
 *  Created on: Jan 31, 2024
 *      Author: ramys
 */

#ifndef DEVICE_DRIVERS_MATRIX_KEYPAD_H_
#define DEVICE_DRIVERS_MATRIX_KEYPAD_H_

#include <stdint.h>

typedef struct
{
    /// @brief defines the number of rows
    uint8_t Rows;

    /// @brief defines the number of columns
    uint8_t Columns;

    /// @brief Holds the status of all keys
    /// 32-bits means the max number of keys is 32
    uint32_t KeysStatus;

    /// @struct HW_Interface_t
    /// @brief
    /// Structure containing the function pointers to be used by
    /// the driver
    struct HW_Interface_t
    {
        /// @brief Reads the GPIO input pin status (Columns)
        uint16_t (*Keypad_GetInputs)();
        /// @brief Writes the GPIO output Status (Rows)
        void (*Keypad_SetOutputs)(uint16_t Status);
        /// @brief Used to generate a Delay
        void (*Keypad_Delay)(uint32_t delay_ms);
    } HW_Interface;

} Matrix_Keypad_t;

#ifdef __cplusplus
extern "C"
{
#endif

    /// @brief Configres the hardware to use keypad
    /// @param keypad
    void Keypad_Init(Matrix_Keypad_t *keypad);

    /// @brief Function periodically called by the user to refresh the status of the keys
    /// @param keypad
    void Keypad_Refresh(Matrix_Keypad_t *keypad);

#ifdef __cplusplus
}
#endif
#endif /* DEVICE_DRIVERS_MATRIX_KEYPAD_H_ */
