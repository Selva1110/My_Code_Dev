#include <atmel_start.h>
#define UART_BAUD_RATE (const uint32_t)9600


static uint8_t print_msg[] = "55";
static uint8_t read_msg[25];



int main(void)
{
	int a;
	/* Initializes MCU, drivers and middle ware */
	atmel_start_init();
	
	speed_measurement_init();
	register_hall_events();
	register_one_ms_timer_events();
	/* Replace with your application code */
	while (1) {
		a++;
	}
}
