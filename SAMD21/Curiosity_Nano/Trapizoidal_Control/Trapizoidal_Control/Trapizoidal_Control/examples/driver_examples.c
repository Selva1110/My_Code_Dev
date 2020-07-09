/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using ADC_0 to generate waveform.
 */
void ADC_0_example(void)
{
	uint8_t buffer[2];

	adc_sync_enable_channel(&ADC_0, 0);

	while (1) {
		adc_sync_read_channel(&ADC_0, 0, buffer, 2);
	}
}

static void button_on_PA20_pressed(void)
{
}

static void button_on_PA21_pressed(void)
{
}

static void button_on_PA07_pressed(void)
{
}

/**
 * Example of using EIC_HALL_SENSOR
 */
void EIC_HALL_SENSOR_example(void)
{

	ext_irq_register(PIN_PA20, button_on_PA20_pressed);
	ext_irq_register(PIN_PA21, button_on_PA21_pressed);
	ext_irq_register(PIN_PA07, button_on_PA07_pressed);
}

/**
 * Example of using INTERFACE_INSTANCE to write "Hello World" using the IO abstraction.
 */
static uint8_t example_INTERFACE_INSTANCE[12] = "Hello World!";

void INTERFACE_INSTANCE_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&INTERFACE_INSTANCE, &io);

	spi_m_sync_enable(&INTERFACE_INSTANCE);
	io_write(io, example_INTERFACE_INSTANCE, 12);
}

static struct timer_task TIMER_SPEED_MEASURE_task1, TIMER_SPEED_MEASURE_task2;
/**
 * Example of using TIMER_SPEED_MEASURE.
 */
static void TIMER_SPEED_MEASURE_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_SPEED_MEASURE_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_SPEED_MEASURE_example(void)
{
	TIMER_SPEED_MEASURE_task1.interval = 100;
	TIMER_SPEED_MEASURE_task1.cb       = TIMER_SPEED_MEASURE_task1_cb;
	TIMER_SPEED_MEASURE_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_SPEED_MEASURE_task2.interval = 200;
	TIMER_SPEED_MEASURE_task2.cb       = TIMER_SPEED_MEASURE_task2_cb;
	TIMER_SPEED_MEASURE_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_SPEED_MEASURE, &TIMER_SPEED_MEASURE_task1);
	timer_add_task(&TIMER_SPEED_MEASURE, &TIMER_SPEED_MEASURE_task2);
	timer_start(&TIMER_SPEED_MEASURE);
}

static struct timer_task TIMER_ONE_MS_task1, TIMER_ONE_MS_task2;

/**
 * Example of using TIMER_ONE_MS.
 */
static void TIMER_ONE_MS_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_ONE_MS_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_ONE_MS_example(void)
{
	TIMER_ONE_MS_task1.interval = 100;
	TIMER_ONE_MS_task1.cb       = TIMER_ONE_MS_task1_cb;
	TIMER_ONE_MS_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_ONE_MS_task2.interval = 200;
	TIMER_ONE_MS_task2.cb       = TIMER_ONE_MS_task2_cb;
	TIMER_ONE_MS_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_ONE_MS, &TIMER_ONE_MS_task1);
	timer_add_task(&TIMER_ONE_MS, &TIMER_ONE_MS_task2);
	timer_start(&TIMER_ONE_MS);
}

/**
 * Example of using PWM_MOTOR_DRIVER.
 */
void PWM_MOTOR_DRIVER_example(void)
{
	pwm_set_parameters(&PWM_MOTOR_DRIVER, 10000, 5000);
	pwm_enable(&PWM_MOTOR_DRIVER);
}
