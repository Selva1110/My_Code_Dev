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

	while (1) {
	}
}

/**
 * Example of using ADC_1 to generate waveform.
 */
void ADC_1_example(void)
{

	while (1) {
	}
}

static void button_on_PC9_pressed(void)
{
}
static void button_on_PC19_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_0
 */
void EXTERNAL_IRQ_0_example(void)
{
	ext_irq_register(PIO_PC9_IDX, button_on_PC9_pressed);
	ext_irq_register(PIO_PC19_IDX, button_on_PC19_pressed);
}

static void button_on_PA2_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_1
 */
void EXTERNAL_IRQ_1_example(void)
{
	ext_irq_register(PIO_PA2_IDX, button_on_PA2_pressed);
}

static void period_cb_PWM_0(const struct pwm_descriptor *const descr)
{
	/* period interrupt */
}
/**
 * Example of using PWM_0.
 */
void PWM_0_example(void)
{
	pwm_register_callback(&PWM_0, PWM_PERIOD_CB, period_cb_PWM_0);
	pwm_enable(&PWM_0);
}

/**
 * Example of using TIMER_0.
 */
static struct timer_task TIMER_0_task1, TIMER_0_task2;

static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}

/**
 * Example of using TIMER_1.
 */
static struct timer_task TIMER_1_task1, TIMER_1_task2;

static void TIMER_1_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_1_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_1_example(void)
{
	TIMER_1_task1.interval = 100;
	TIMER_1_task1.cb       = TIMER_1_task1_cb;
	TIMER_1_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_1_task2.interval = 200;
	TIMER_1_task2.cb       = TIMER_1_task2_cb;
	TIMER_1_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_1, &TIMER_1_task1);
	timer_add_task(&TIMER_1, &TIMER_1_task2);
	timer_start(&TIMER_1);
}

/**
 * Example of using USART_0 to write "Hello World" using the IO abstraction.
 */
void USART_0_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);

	io_write(io, (uint8_t *)"Hello World!", 12);
}
