/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_ext_irq.h>

#include <hal_spi_m_sync.h>
#include <hal_timer.h>
#include <hpl_tc_base.h>
#include <hal_timer.h>
#include <hpl_tc_base.h>

#include <hal_pwm.h>
#include <hpl_tcc.h>

extern struct spi_m_sync_descriptor SPI_ADP;
extern struct timer_descriptor      TIMER_SPEED_MEASURE;
extern struct timer_descriptor      TIMER_ONE_MS;

extern struct pwm_descriptor PWM_MOTOR_DRIVER;

void SPI_ADP_PORT_init(void);
void SPI_ADP_CLOCK_init(void);
void SPI_ADP_init(void);

void PWM_MOTOR_DRIVER_PORT_init(void);
void PWM_MOTOR_DRIVER_CLOCK_init(void);
void PWM_MOTOR_DRIVER_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
