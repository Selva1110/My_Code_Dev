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

void delay_driver_init(void)
{
	delay_init(SysTick);
}

void system_init(void)
{
	init_mcu();

	_pmc_enable_periph_clock(ID_PIOA);

	_pmc_enable_periph_clock(ID_PIOC);

	/* Disable Watchdog */
	hri_wdt_set_MR_WDDIS_bit(WDT);

	/* GPIO on PA11 */

	// Set pin direction to input
	gpio_set_pin_direction(SW0, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(SW0,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(SW0, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PC8 */

	gpio_set_pin_level(LED0,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(LED0, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(LED0, GPIO_PIN_FUNCTION_OFF);

	delay_driver_init();
}
