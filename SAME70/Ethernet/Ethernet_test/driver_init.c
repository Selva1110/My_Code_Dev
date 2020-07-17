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

struct mac_async_descriptor ETHERNET_MAC_0;

void ETHERNET_MAC_0_PORT_init(void)
{

	gpio_set_pin_function(PD13, MUX_PD13A_GMAC_GCOL);

	gpio_set_pin_function(PD10, MUX_PD10A_GMAC_GCRS);

	gpio_set_pin_function(PD8, MUX_PD8A_GMAC_GMDC);

	gpio_set_pin_function(PD9, MUX_PD9A_GMAC_GMDIO);

	gpio_set_pin_function(PD5, MUX_PD5A_GMAC_GRX0);

	gpio_set_pin_function(PD6, MUX_PD6A_GMAC_GRX1);

	gpio_set_pin_function(PD11, MUX_PD11A_GMAC_GRX2);

	gpio_set_pin_function(PD12, MUX_PD12A_GMAC_GRX3);

	gpio_set_pin_function(PD14, MUX_PD14A_GMAC_GRXCK);

	gpio_set_pin_function(PD4, MUX_PD4A_GMAC_GRXDV);

	gpio_set_pin_function(PD7, MUX_PD7A_GMAC_GRXER);

	gpio_set_pin_function(PD2, MUX_PD2A_GMAC_GTX0);

	gpio_set_pin_function(PD3, MUX_PD3A_GMAC_GTX1);

	gpio_set_pin_function(PD15, MUX_PD15A_GMAC_GTX2);

	gpio_set_pin_function(PD16, MUX_PD16A_GMAC_GTX3);

	gpio_set_pin_function(PD0, MUX_PD0A_GMAC_GTXCK);

	gpio_set_pin_function(PD1, MUX_PD1A_GMAC_GTXEN);

	gpio_set_pin_function(PD17, MUX_PD17A_GMAC_GTXER);
}

void ETHERNET_MAC_0_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_GMAC);
}

void ETHERNET_MAC_0_init(void)
{
	ETHERNET_MAC_0_CLOCK_init();
	mac_async_init(&ETHERNET_MAC_0, GMAC);
	ETHERNET_MAC_0_PORT_init();
}

void system_init(void)
{
	init_mcu();

	/* Disable Watchdog */
	hri_wdt_set_MR_WDDIS_bit(WDT);

	ETHERNET_MAC_0_init();
}
