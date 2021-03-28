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

	io_write(io, (uint8_t *)"Hello World!", 12);
}

void I2C_0_example(void)
{
	struct io_descriptor *I2C_0_io;

	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x12, I2C_M_SEVEN);
	io_write(I2C_0_io, (uint8_t *)"Hello World!", 12);
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
	//struct tcc_pwm_cfg *cfgpwm = _get_tcc_pwm_cfg(TCC0);
 	//switch(cfgpwm->sel_ch)
 	//{
 	//	break;
 	//}
	hri_tcc_write_PER_reg(TCC0,400);
	hri_tcc_write_CC_reg(TCC0, 0, 200);
	hri_tcc_write_CC_reg(TCC0, 1, 200);
	hri_tcc_write_CC_reg(TCC0, 2, 200);	
	pwm_enable(&PWM_0);
}
