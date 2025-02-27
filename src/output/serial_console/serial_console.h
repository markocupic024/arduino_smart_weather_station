#ifndef SERIAL_CONSOLE_H
#define SERIAL_CONSOLE_H

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <WString.h>
#include "../../control/control_types.h"
#include "serial_console_config.h"

/* Flag to proceed with displaying data */
#define SERIAL_CONSOLE_PROCEED_WITH_DISPLAY      (bool)(true)
/* Flag to prevent displaying data */
#define SERIAL_CONSOLE_DONT_PROCEED_WITH_DISPLAY (bool)(false)

/* Size of the buffer for converting float to string */
#define SERIAL_CONSOLE_DTOSTRF_BUFFER_SIZE   (uint8_t)(20u)
/* Size for the null terminator in strings */
#define SERIAL_CONSOLE_NULL_TERMINATOR_SIZE  (uint8_t)(1u)
/* Minimal size of float string for serial console */
#define SERIAL_CONSOLE_MIN_FLOAT_STRING_LEN  (signed char)(1)
/* Len of formated hex address */
#define SERIAL_CONSOLE_HEX_ADDR_STRING_LEN   (uint8_t)(3u)

// Predefined buffer sizes for string storage in serial console output
#define SERIAL_CONSOLE_STRING_RESERVED_MINI          (uint16_t)(10u)  /* Suitable for short strings like status codes or flags */
#define SERIAL_CONSOLE_STRING_RESERVED_SMALL         (uint16_t)(20u)  /* Suitable for short messages or small numerical values */
#define SERIAL_CONSOLE_STRING_RESERVED_MEDIUM        (uint16_t)(40u)  /* Suitable for longer messages or formatted data */
#define SERIAL_CONSOLE_STRING_RESERVED_LARGE         (uint16_t)(60u)  /* Suitable for longer messages or formatted data */
#define SERIAL_CONSOLE_STRING_RESERVED_GIANT         (uint16_t)(100u) /* Suitable for multi-field messages or debugging output */
#define SERIAL_CONSOLE_STRING_RESERVED_ENORMOUS      (uint16_t)(200u) /* Very large messages or extensive debugging output, not recommended for RAM saving */

/**
 * @brief Initializes the serial console communication.
 *
 * This function begins serial communication at the specified baud rate
 * and does not block the program execution if the serial port is not available.
 *
 * @return control_error_code_te
 * - ERROR_CODE_NO_ERROR: Serial communication initialized successfully.
 * - ERROR_CODE_SERIAL_INIT_FAILED: Failed to initialize the serial communication.
 */
control_error_code_te serial_console_init();

/**
 * @brief Displays data on the serial console based on input type.
 *
 * This function handles data routing and invokes specific display functions
 * based on the type of input provided (e.g., sensor data, RTC time, or I2C scan results).
 *
 * @param data Pointer to data structure containing the input type and associated readings.
 * @return control_error_code_te
 * - ERROR_CODE_NO_ERROR: Data displayed successfully.
 * - ERROR_CODE_INVALID_INPUT_TYPE: Invalid input type specified.
 */
control_error_code_te serial_console_displayData(const control_data_ts *data);

#endif