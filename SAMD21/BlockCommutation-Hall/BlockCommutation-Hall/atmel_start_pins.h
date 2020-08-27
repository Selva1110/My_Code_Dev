/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define PA07 GPIO(GPIO_PORTA, 7)
#define PWM_WO_0 GPIO(GPIO_PORTA, 8)
#define PWM_WO_1 GPIO(GPIO_PORTA, 9)
#define PWM_WO_4 GPIO(GPIO_PORTA, 14)
#define PWM_WO_5 GPIO(GPIO_PORTA, 15)
#define PWM_WO_6 GPIO(GPIO_PORTA, 16)
#define HALL_SENSOR_PINB GPIO(GPIO_PORTA, 18)
#define PA20 GPIO(GPIO_PORTA, 20)
#define PA21 GPIO(GPIO_PORTA, 21)
#define TEST_PIN_0 GPIO(GPIO_PORTB, 11)
#define EDBG_SPI_MISO GPIO(GPIO_PORTB, 12)
#define EDBG_SPI_SS_PIN GPIO(GPIO_PORTB, 13)
#define EDBG_SPI_MOSI GPIO(GPIO_PORTB, 14)
#define EDBG_SPI_SCK GPIO(GPIO_PORTB, 15)

#endif // ATMEL_START_PINS_H_INCLUDED
