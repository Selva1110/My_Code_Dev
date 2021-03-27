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
#include <hpl_tcc.h>
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
 * Example of using EXTERNAL_IRQ_0
 */
void EXTERNAL_IRQ_0_example(void)
{

	ext_irq_register(PIN_PA20, button_on_PA20_pressed);
	ext_irq_register(PIN_PA21, button_on_PA21_pressed);
	ext_irq_register(PIN_PA07, button_on_PA07_pressed);
}

/**
 * Example of using SPI_0 to write "Hello World" using the IO abstraction.
 */
static uint8_t example_SPI_0[12] = "Hello World!";

void SPI_0_example(void)
{
	
	//MOSI--> PA16
	//SCK --> PA19
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_0, &io);

	spi_m_sync_enable(&SPI_0);
	io_write(io, example_SPI_0, 12);
}

/**
 * Example of using USART_0 to write "Hello World" using the IO abstraction.
 */
void USART_0_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);

	io_write(io, (uint8_t *)"Welcome to Motor_Controller_V3", 30);
}

static struct timer_task TIMER_0_task1;

/**
 * Example of using TIMER_0.
 */
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
	gpio_toggle_pin_level(LED0);
}


void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 500;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_start(&TIMER_0);
}

/**
 * Example of using PWM_0.
 */
void PWM_0_example(void)
{
	struct tcc_pwm_cfg *cfgpwm = _get_tcc_pwm_cfg(TCC0);
 	switch(cfgpwm->sel_ch)
 	{
 		break;
 	}
	hri_tcc_write_PER_reg(TCC0,400);
	hri_tcc_write_CC_reg(TCC0, 0, 200);
	hri_tcc_write_CC_reg(TCC0, 1, 200);
	hri_tcc_write_CC_reg(TCC0, 2, 200);	
	pwm_enable(&PWM_0);
}
