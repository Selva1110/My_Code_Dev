/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <hal_init.h>
#include <hpl_pmc.h>
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hpl_pwm_base.h>

#include <hpl_tc.h>

#include <hpl_tc.h>

struct timer_descriptor TIMER_0;
struct timer_descriptor TIMER_1;

struct adc_sync_descriptor ADC_0;

struct adc_sync_descriptor ADC_1;

struct pwm_descriptor PWM_0;

struct usart_sync_descriptor USART_0;

void ADC_0_PORT_init(void)
{

	gpio_set_pin_function(PD30, GPIO_PIN_FUNCTION_OFF);

	gpio_set_pin_function(PB3, GPIO_PIN_FUNCTION_OFF);

	gpio_set_pin_function(PB2, GPIO_PIN_FUNCTION_OFF);

	gpio_set_pin_function(PA19, GPIO_PIN_FUNCTION_OFF);
}

void ADC_0_CLOCK_init(void)
{

	_pmc_enable_periph_clock(ID_AFEC0);
}

void ADC_0_init(void)
{
	ADC_0_CLOCK_init();
	ADC_0_PORT_init();
	adc_sync_init(&ADC_0, AFEC0, (void *)NULL);
}

void ADC_1_PORT_init(void)
{

	gpio_set_pin_function(PC13, GPIO_PIN_FUNCTION_OFF);

	gpio_set_pin_function(PC12, GPIO_PIN_FUNCTION_OFF);

	gpio_set_pin_function(PC30, GPIO_PIN_FUNCTION_OFF);

	gpio_set_pin_function(PC31, GPIO_PIN_FUNCTION_OFF);
}

void ADC_1_CLOCK_init(void)
{

	_pmc_enable_periph_clock(ID_AFEC1);
}

void ADC_1_init(void)
{
	ADC_1_CLOCK_init();
	ADC_1_PORT_init();
	adc_sync_init(&ADC_1, AFEC1, (void *)NULL);
}

void EXTERNAL_IRQ_0_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(PC9, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PC9,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PC9, GPIO_PIN_FUNCTION_OFF);

	// Set pin direction to input
	gpio_set_pin_direction(PC19, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PC19,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PC19, GPIO_PIN_FUNCTION_OFF);
}

void EXTERNAL_IRQ_1_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(PA2, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA2,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA2, GPIO_PIN_FUNCTION_OFF);
}

void PWM_0_PORT_init(void)
{

	gpio_set_pin_function(PD20, MUX_PD20A_PWM0_PWMH0);

	gpio_set_pin_function(PD21, MUX_PD21A_PWM0_PWMH1);

	gpio_set_pin_function(PA13, MUX_PA13B_PWM0_PWMH2);

	gpio_set_pin_function(PA17, MUX_PA17C_PWM0_PWMH3);

	gpio_set_pin_function(PD10, MUX_PD10B_PWM0_PWML0);

	gpio_set_pin_function(PD25, MUX_PD25A_PWM0_PWML1);

	gpio_set_pin_function(PA30, MUX_PA30A_PWM0_PWML2);

	gpio_set_pin_function(PD27, MUX_PD27A_PWM0_PWML3);
}

void PWM_0_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_PWM0);
}

void PWM_0_init(void)
{
	PWM_0_CLOCK_init();
	PWM_0_PORT_init();
	pwm_init(&PWM_0, PWM0, _pwm_get_pwm());
}

void TIMER_0_PORT_init(void)
{

	gpio_set_pin_function(PA4, MUX_PA4B_TC0_TCLK0);

	gpio_set_pin_function(PA28, MUX_PA28B_TC0_TCLK1);

	gpio_set_pin_function(PA0, MUX_PA0B_TC0_TIOA0);
}
/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
	_pmc_enable_periph_clock(ID_TC0_CHANNEL0);
	TIMER_0_PORT_init();
	timer_init(&TIMER_0, TC0, _tc_get_timer());
}

void TIMER_1_PORT_init(void)
{

	gpio_set_pin_function(PC25, MUX_PC25B_TC1_TCLK3);

	gpio_set_pin_function(PC28, MUX_PC28B_TC1_TCLK4);
}
/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_1_init(void)
{
	_pmc_enable_periph_clock(ID_TC1_CHANNEL0);
	TIMER_1_PORT_init();
	timer_init(&TIMER_1, TC1, _tc_get_timer());
}

void USART_0_PORT_init(void)
{

	gpio_set_pin_function(PD18, MUX_PD18C_UART4_URXD4);

	gpio_set_pin_function(PD19, MUX_PD19C_UART4_UTXD4);
}

void USART_0_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_UART4);
}

void USART_0_init(void)
{
	USART_0_CLOCK_init();
	usart_sync_init(&USART_0, UART4, _uart_get_usart_sync());
	USART_0_PORT_init();
}

void system_init(void)
{
	init_mcu();

	_pmc_enable_periph_clock(ID_PIOA);

	_pmc_enable_periph_clock(ID_PIOC);

	/* Disable Watchdog */
	hri_wdt_set_MR_WDDIS_bit(WDT);

	ADC_0_init();

	ADC_1_init();
	EXTERNAL_IRQ_0_init();
	EXTERNAL_IRQ_1_init();

	PWM_0_init();
	TIMER_0_init();
	TIMER_1_init();

	USART_0_init();

	ext_irq_init();
}
