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

struct spi_m_sync_descriptor SPI_ADP;
struct timer_descriptor      TIMER_SPEED_MEASURE;
struct timer_descriptor      TIMER_ONE_MS;

struct pwm_descriptor PWM_MOTOR_DRIVER;

void EIC_HALL_SENSOR_init(void)
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

void SPI_ADP_PORT_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(EDBG_SPI_MISO, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(EDBG_SPI_MISO,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(EDBG_SPI_MISO, PINMUX_PB12C_SERCOM4_PAD0);

	gpio_set_pin_level(EDBG_SPI_MOSI,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(EDBG_SPI_MOSI, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(EDBG_SPI_MOSI, PINMUX_PB14C_SERCOM4_PAD2);

	gpio_set_pin_level(EDBG_SPI_SCK,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(EDBG_SPI_SCK, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(EDBG_SPI_SCK, PINMUX_PB15C_SERCOM4_PAD3);
}

void SPI_ADP_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM4);
	_gclk_enable_channel(SERCOM4_GCLK_ID_CORE, CONF_GCLK_SERCOM4_CORE_SRC);
}

void SPI_ADP_init(void)
{
	SPI_ADP_CLOCK_init();
	spi_m_sync_init(&SPI_ADP, SERCOM4);
	SPI_ADP_PORT_init();
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_SPEED_MEASURE_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC3);
	_gclk_enable_channel(TC3_GCLK_ID, CONF_GCLK_TC3_SRC);

	timer_init(&TIMER_SPEED_MEASURE, TC3, _tc_get_timer());
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_ONE_MS_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC4);
	_gclk_enable_channel(TC4_GCLK_ID, CONF_GCLK_TC4_SRC);

	timer_init(&TIMER_ONE_MS, TC4, _tc_get_timer());
}

void PWM_MOTOR_DRIVER_PORT_init(void)
{

	gpio_set_pin_function(PWM_WO_0, PINMUX_PA08E_TCC0_WO0);

	gpio_set_pin_function(PWM_WO_1, PINMUX_PA09E_TCC0_WO1);

	gpio_set_pin_function(HALL_SENSOR_PINB, PINMUX_PA18F_TCC0_WO2);

	gpio_set_pin_function(PWM_WO_4, PINMUX_PA14F_TCC0_WO4);

	gpio_set_pin_function(PWM_WO_5, PINMUX_PA15F_TCC0_WO5);

	gpio_set_pin_function(PWM_WO_6, PINMUX_PA16F_TCC0_WO6);
}

void PWM_MOTOR_DRIVER_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TCC0);
	_gclk_enable_channel(TCC0_GCLK_ID, CONF_GCLK_TCC0_SRC);
}

void PWM_MOTOR_DRIVER_init(void)
{
	PWM_MOTOR_DRIVER_CLOCK_init();
	PWM_MOTOR_DRIVER_PORT_init();
	pwm_init(&PWM_MOTOR_DRIVER, TCC0, _tcc_get_pwm());
}

void system_init(void)
{
	init_mcu();

	// GPIO on PB11

	gpio_set_pin_level(TEST_PIN_0,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(TEST_PIN_0, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(TEST_PIN_0, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB13

	gpio_set_pin_level(EDBG_SPI_SS_PIN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(EDBG_SPI_SS_PIN, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(EDBG_SPI_SS_PIN, GPIO_PIN_FUNCTION_OFF);

	EIC_HALL_SENSOR_init();

	SPI_ADP_init();

	TIMER_SPEED_MEASURE_init();
	TIMER_ONE_MS_init();

	PWM_MOTOR_DRIVER_init();
}
