/*
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 01 Aug, 2015
 * @version 0.1.0
 *
 * @brief XMC1000 Bootkit CCU8 demo example
 *
 * Example is for CCU8 module, it starts 1 slice of CCU8 for 1 sets of complementary outputs on
 * Port 0 [1:0] with dead time. The frequency of the PWM is 1Hz. The duty cycle on channel 1 is
 * 33.33%
 * */

#include <xmc_ccu8.h>
#include <xmc_scu.h>
#include <xmc_gpio.h>

/* CCU8 Macros */
#define CCU80_MODULE_PTR      	CCU80
#define CCU80_MODULE_NUMBER   	(0U)

#define CCU80_SLICE0_PTR       	CCU80_CC80
#define CCU80_SLICE0_NUMBER    	(0U)
#define CCU80_SLICE0_OUTPUT00	P0_0
#define CCU80_SLICE0_OUTPUT01	P0_1

/* XMC System Clock Unit (SCU) Configuration: */
/* PWM period is calculated based on PCLK which is equivalent to 64 MHz. */
XMC_SCU_CLOCK_CONFIG_t clock_config =
{
  .pclk_src = XMC_SCU_CLOCK_PCLKSRC_DOUBLE_MCLK,
  .rtc_src = XMC_SCU_CLOCK_RTCCLKSRC_DCO2,
  .fdiv = 0,
  .idiv = 1,
};

/* XMC CCU8 configuration structure */

XMC_CCU8_SLICE_COMPARE_CONFIG_t  CCU80_SLICE_config     =
{
   .timer_mode            = (uint32_t)XMC_CCU8_SLICE_TIMER_COUNT_MODE_EA,
   .monoshot              = (uint32_t)XMC_CCU8_SLICE_TIMER_REPEAT_MODE_REPEAT,
   .shadow_xfer_clear     = 0U,
   .dither_timer_period   = 0U,
   .dither_duty_cycle     = 0U,
   .prescaler_mode        = (uint32_t)XMC_CCU8_SLICE_PRESCALER_MODE_NORMAL,
   .mcm_ch1_enable        = 0U,
   .mcm_ch2_enable        = 0U,
   .slice_status          = (uint32_t)XMC_CCU8_SLICE_STATUS_CHANNEL_1,
   .passive_level_out0    = (uint32_t)XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
   .passive_level_out1    = (uint32_t)XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
   .passive_level_out2    = (uint32_t)XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
   .passive_level_out3    = (uint32_t)XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
   .asymmetric_pwm        = 0U,
   .invert_out0           = 0U,
   .invert_out1           = 1U,
   .invert_out2           = 0U,
   .invert_out3           = 1U,
   .prescaler_initval     = 10U,
   .float_limit           = 0U,
   .dither_limit          = 0U,
   .timer_concatenation   = 0U,
};

XMC_CCU8_SLICE_DEAD_TIME_CONFIG_t  SLICE_dt_config =
    {
      .enable_dead_time_channel1         = 1U,
      .channel1_st_path                  = 1U,
      .channel1_inv_st_path              = 1U,
      .div                               = (uint32_t)XMC_CCU8_SLICE_DTC_DIV_8,
      .channel1_st_rising_edge_counter   = 60U,	//7.5us @ PCLK 64MHz
      .channel1_st_falling_edge_counter  = 30U, //3.75us @ PCLK 64MHz
    };

/* Configuration for standard pads: Port0;[0:1] */
XMC_GPIO_CONFIG_t CCU80_SLICE_OUTPUT_config =
{
   .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5,
   .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
   .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};


/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code.
 */

int main(void)
{
	/* Ensure clock frequency is set at 64MHz (2*MCLK) */
	XMC_SCU_CLOCK_Init(&clock_config);

	/* Enable clock, enable prescaler block and configure global control */
	XMC_CCU8_Init(CCU80_MODULE_PTR, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

	/* Start the prescaler and restore clocks to slices */
	XMC_CCU8_StartPrescaler(CCU80_MODULE_PTR);

	/* Ensure fCCU reaches CCU80 */
	XMC_CCU8_SetModuleClock(CCU80_MODULE_PTR, XMC_CCU8_CLOCK_SCU);

    /* Configure CCU8x_CC8y slice as timer */
	XMC_CCU8_SLICE_CompareInit(CCU80_SLICE0_PTR, &CCU80_SLICE_config);

    /* Set period match value (1Hz) of the timer  */
    XMC_CCU8_SLICE_SetTimerPeriodMatch(CCU80_SLICE0_PTR, 62499U);

    /* Set timer compare match value for channel (duty cycle 33.33 and 66.66%) of period */
    XMC_CCU8_SLICE_SetTimerCompareMatch(CCU80_SLICE0_PTR, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, 41666U);

    /* Transfer value from shadow timer registers to actual timer registers */
    XMC_CCU8_EnableShadowTransfer(CCU80_MODULE_PTR, (uint32_t) \
    		(XMC_CCU8_SHADOW_TRANSFER_SLICE_0|XMC_CCU8_SHADOW_TRANSFER_PRESCALER_SLICE_0));

    /* Deadtime initialisation*/
    XMC_CCU8_SLICE_DeadTimeInit(CCU80_SLICE0_PTR, &SLICE_dt_config);

	/*Initializes the GPIO*/
	XMC_GPIO_Init(CCU80_SLICE0_OUTPUT00, &CCU80_SLICE_OUTPUT_config);
	XMC_GPIO_Init(CCU80_SLICE0_OUTPUT01, &CCU80_SLICE_OUTPUT_config);

	/* Get the slice out of idle mode */
	XMC_CCU8_EnableClock(CCU80_MODULE_PTR, CCU80_SLICE0_NUMBER);

	/* Start the PWM */
	XMC_CCU8_SLICE_StartTimer(CCU80_SLICE0_PTR);


  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {

  }
}
