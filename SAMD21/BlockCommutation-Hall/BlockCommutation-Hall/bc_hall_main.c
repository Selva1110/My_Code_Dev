#include "atmel_start.h"
#include "atmel_start_pins.h"
#include "adp_main.h"
#include "motor_control.h"

int main(void)
{
	system_init();

	/* Peripheral initializations */
	motor_pwm_init();
	speed_measurement_init();
	register_hall_events();
	register_one_ms_timer_events();

	/* Priority of Interrupts to be scheduled */
	NVIC_SetPriority(EIC_IRQn, 0);

	/* TC4 interrupt priority, task interrupt */
	NVIC_SetPriority(TC4_IRQn, 3);

	spi_m_sync_enable(&SPI_ADP);
	adp_app_init();
	adp_interface_init_spi(&SPI_ADP.io, EDBG_SPI_SS_PIN);

	/* Initialize global variables */
	init_global_variables();

	configure_dashboard();

	while (1) {
	}
}
