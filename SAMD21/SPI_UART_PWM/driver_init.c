/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

#include <hpl_adc_base.h>

struct spi_m_sync_descriptor SPI_0;
struct timer_descriptor      TIMER_0;

struct adc_sync_descriptor ADC_0;

struct usart_sync_descriptor USART_0;

struct pwm_descriptor PWM_0;

void ADC_0_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(PA02, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PA02, PINMUX_PA02B_ADC_AIN0);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PA03, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PA03, PINMUX_PA03B_ADC_AIN1);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PB08, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PB08, PINMUX_PB08B_ADC_AIN2);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PB09, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PB09, PINMUX_PB09B_ADC_AIN3);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PA04, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PA04, PINMUX_PA04B_ADC_AIN4);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PA05, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PA05, PINMUX_PA05B_ADC_AIN5);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PA06, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PA06, PINMUX_PA06B_ADC_AIN6);
}

void ADC_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, ADC);
	_gclk_enable_channel(ADC_GCLK_ID, CONF_GCLK_ADC_SRC);
}

void ADC_0_init(void)
{
	ADC_0_CLOCK_init();
	ADC_0_PORT_init();
	adc_sync_init(&ADC_0, ADC, (void *)NULL);
}

void EXTERNAL_IRQ_0_init(void)
{
	_gclk_enable_channel(EIC_GCLK_ID, CONF_GCLK_EIC_SRC);

	// Set pin direction to input
	gpio_set_pin_direction(PA20, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA20,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA20, PINMUX_PA20A_EIC_EXTINT4);

	// Set pin direction to input
	gpio_set_pin_direction(PA21, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA21,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA21, PINMUX_PA21A_EIC_EXTINT5);

	// Set pin direction to input
	gpio_set_pin_direction(PA07, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA07,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA07, PINMUX_PA07A_EIC_EXTINT7);

	ext_irq_init();
}

void SPI_0_PORT_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(PA17, GPIO_DIRECTION_OUT);

	gpio_set_pin_pull_mode(PA17,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA17, PINMUX_PA17C_SERCOM1_PAD1);

	gpio_set_pin_level(PA16,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PA16, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PA16, PINMUX_PA16C_SERCOM1_PAD0);

	gpio_set_pin_level(PA19,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PA19, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PA19, PINMUX_PA19C_SERCOM1_PAD3);
}

void SPI_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM1);
	_gclk_enable_channel(SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC);
}

void SPI_0_init(void)
{
	SPI_0_CLOCK_init();
	spi_m_sync_init(&SPI_0, SERCOM1);
	SPI_0_PORT_init();
}

void USART_0_PORT_init(void)
{

	gpio_set_pin_function(PA10, PINMUX_PA10D_SERCOM2_PAD2);

	gpio_set_pin_function(PA11, PINMUX_PA11D_SERCOM2_PAD3);
}

void USART_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM2);
	_gclk_enable_channel(SERCOM2_GCLK_ID_CORE, CONF_GCLK_SERCOM2_CORE_SRC);
}

void USART_0_init(void)
{
	USART_0_CLOCK_init();
	usart_sync_init(&USART_0, SERCOM2, (void *)NULL);
	USART_0_PORT_init();
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC4);
	_gclk_enable_channel(TC4_GCLK_ID, CONF_GCLK_TC4_SRC);

	timer_init(&TIMER_0, TC4, _tc_get_timer());
}

void PWM_0_PORT_init(void)
{

	gpio_set_pin_function(PA08, PINMUX_PA08E_TCC0_WO0);

	gpio_set_pin_function(PA09, PINMUX_PA09E_TCC0_WO1);

	gpio_set_pin_function(PA18, PINMUX_PA18F_TCC0_WO2);

	gpio_set_pin_function(PA14, PINMUX_PA14F_TCC0_WO4);

	gpio_set_pin_function(PA15, PINMUX_PA15F_TCC0_WO5);

	gpio_set_pin_function(PA16, PINMUX_PA16F_TCC0_WO6);
}

void PWM_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TCC0);
	_gclk_enable_channel(TCC0_GCLK_ID, CONF_GCLK_TCC0_SRC);
}

void PWM_0_init(void)
{
	PWM_0_CLOCK_init();
	PWM_0_PORT_init();
	pwm_init(&PWM_0, TCC0, _tcc_get_pwm());
	hri_tcc_set_WEXCTRL_DTIEN0_bit(TCC0);
	hri_tcc_set_WEXCTRL_DTIEN1_bit(TCC0);
	hri_tcc_set_WEXCTRL_DTIEN2_bit(TCC0);
	hri_tcc_set_WEXCTRL_DTHS_bf(TCC0,4);
	hri_tcc_set_WEXCTRL_DTLS_bf(TCC0,4);
	//hri_tcc_set_DRVCTRL_INVEN4_bit(TCC0);
	//hri_tcc_set_DRVCTRL_INVEN5_bit(TCC0);
	//hri_tcc_set_DRVCTRL_INVEN6_bit(TCC0);
}

void system_init(void)
{
	init_mcu();

	// GPIO on PB10

	gpio_set_pin_level(LED0,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(LED0, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(LED0, GPIO_PIN_FUNCTION_OFF);

	ADC_0_init();
	EXTERNAL_IRQ_0_init();

	SPI_0_init();

	USART_0_init();

	TIMER_0_init();

	PWM_0_init();
}
