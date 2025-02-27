#ifndef CONTROL_TYPES_H
#define CONTROL_TYPES_H

#include <Arduino.h>
#include "../input/input_types.h"
#include "control_error_codes.h"

/* Represents an unused or invalid ID */
#define CONTROL_ID_UNUSED     (uint8_t)(0xFF)

/**
 * Defines a type alias for control I/O components.
 *
 * This type represents different input and output components used in the system. 
 * It is defined as an 8-bit unsigned integer (uint8_t) to ensure efficient memory usage 
 * and compatibility with embedded systems.
 *
 * Typical values for this type are defined in the @ref control_io_te enumeration.
 */
typedef uint8_t control_io_t;

/**
 * Enum listing all available inputs and outputs.
 *
 * This enumeration defines the possible inputs and outputs
 * within the data routing system.
 */
typedef enum
{   
    INPUT_SENSORS,          /**< Input for sensors. */

#ifdef RTC_COMPONENT
    INPUT_RTC,              /**< Input for the Real-Time Clock (RTC). */
#endif

    INPUT_I2C_SCAN,         /**< Input for I2C address scanning. */
    INPUT_ERROR,            /**< Input for error. */

#ifdef LCD_DISPLAY_COMPONENT
    OUTPUT_DISPLAY,         /**< Output component for a display device. */
#endif

#ifdef SERIAL_CONSOLE_COMPONENT
    OUTPUT_SERIAL_CONSOLE,  /**< Output component for the serial console. */
#endif

    IO_UNUSED = 0xFF
} control_io_te;

/**
 * Structure representing a specific device.
 * 
 * This structure defines a device which consists of an I/O component
 * and a unique device identifier - for example, a specific sensor etc..
 * Members:
 *  - io_component: Input/output component.
 *  - device_id: Specific ID of input/output component.
 */
typedef struct
{
    control_io_t io_component;
    uint8_t device_id;
} control_device_ts;

/**
 * Structure representing a generic error in the system.
 * 
 * This structure encapsulates all relevant details of an error, including
 * the error code and specific details about the affected component.
 * 
 * Members:
 *  - error_code: The error code identifying the specific type of error.
 *  - component: Contains detailed information about the affected input/output component.
 */
typedef struct
{
    control_error_code_te error_code; /**< The specific error code. */
    control_device_ts component;      /**< Detailed information about the error source and the ID of the component */
} control_error_ts;

/**
 * Union for handling various input types dynamically.
 *
 * This union is designed to accommodate different types of input data that
 * may be returned from `control_fetchDataFromInput` or an error. The specific input
 * type (e.g., sensor reading, RTC reading) is determined dynamically at runtime,
 * allowing the function to flexibly handle multiple input sources.
 *
 * Fields:
 *  - sensor_reading:     Contains data specific to sensor readings, such as value,
 *                        measurement type, and sensor ID.
 *  - rtc_reading:        Contains data specific to RTC readings, such as date and time.
 *  - i2c_scan_reading:    Contains data specific to I2C scan readings,
 *                        such as addresses bit fields or I2C device status.
 *  - error_msg           Contains data specific to the error message, such as error source,
 *                        input/output flag and specific error code.
 */
typedef union
{
    sensor_reading_ts sensor_reading;       /**< Data structure for sensor readings. */
    rtc_reading_ts rtc_reading;             /**< Data structure for RTC readings. */
    i2c_scan_reading_ts i2c_scan_reading;   /**< Data structure for I2C scan readings. */
    control_error_ts error_msg;             /**< Data structure for error message. */
} input_return_tu;

/**
 * Structure representing data returned from an input.
 *
 * This structure encapsulates the data recieved from an input,
 * including the actual return data, the type of input, and its unique identifier.
 * It is used to standardize and simplify the handling of data from various inputs
 * (e.g., sensors, RTC).
 *
 * Members:
 *  - input_return: A union (`input_return_tu`) holding the actual data returned from
 *                  the input. The specific type (e.g., sensor data, RTC data)
 *                  is determined dynamically based on the `input_type`.
 *  - input     :   Structure with input type and ID.
 */
typedef struct
{
    input_return_tu input_return;    /**< Union holding the returned input data. */
    control_device_ts input;         /**< Structure with input type and ID. */
} control_data_ts;

/**
 * Structure for managing the dual output of data fetching operations.
 *
 * This structure is designed to encapsulate two outputs resulting from
 * a data fetch operation. One part (`data`) contains the fetched data
 * that can be forwarded to an output component, while the other part
 * (`error_code`) contains an error message to be handled by the Error Handler.
 *
 * Members:
 *  - data:       Contains the fetched data, encapsulated in the `control_data_ts`
 *                structure, to be forwarded to an output component (e.g., display, console).
 *  - error_code: Represents the error message of type `control_error_code_te`
 *                that can be passed to the Error Handler for further processing.
 */
typedef struct
{
    control_data_ts data;             /**< The fetched data for output forwarding. */
    control_error_code_te error_code;  /**< The error code for the Error Handler. */
} control_input_data_ts;

#endif