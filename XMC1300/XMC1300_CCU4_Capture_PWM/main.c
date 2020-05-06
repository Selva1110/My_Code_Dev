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
 * @brief XMC1000 Bootkit CCU4 demo example
 *
 * Capture PWM Pulse duty cycle
 * This example uses CCU40 capture mode to measure the frequency and duty cycle of an external incoming PWM pulse signal
 * CCU40, CCU41 clock is set to peripheral clock, prescaler is 0, 64MHz
 * Configure P0.0 as PWM input mode, capture mode CCU40
 * CCU41 configured as PWM Output with duty cycle (33.3?)
 * To measure frequency and the duty cycle, we use CCU40 interrupt request
 * => Frequency and the duty cycle of the external signal are computed in the CCU4_PeriodMatch_IRQHandle() rountine.
 * */

#include <XMC1300.h>		//SFR declarations of the selected device
#include <xmc_ccu4.h>		//SFR declarations of the selected device
#include <xmc_gpio.h>		//SFR declarations of the selected device

/*********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/
#define INPUT_SLICE_PTR         CCU40_CC40
#define INPUT_MODULE_PTR        CCU40
#define INPUT_MODULE_NUMBER     (0U)
#define INPUT_SLICE_NUMBER      (0U)
//#define GPIO_OUTPUT_P0_1   	P0_1
#define INPUT_CCU_OUTPUT  	    P0_0

#define CAPTURE_SLICE_PTR       CCU40_CC41
#define CAPTURE_MODULE_PTR      CCU40
#define CAPTURE_MODULE_NUMBER   (0U)
#define CAPTURE_SLICE_NUMBER    (1U)
//#define INPUT_CCU_OUTPUT  	    P0_0

#define INPUT_PWMPERIOD		  	(1280U) //PWM period calculated based on PCLK = 64MHz: FREQ=50KHz

/*********************************************************************************************************************
 * GLOBAL DATA
 *********************************************************************************************************************/
XMC_SCU_CLOCK_CONFIG_t clock_config =
{
  .pclk_src = XMC_SCU_CLOCK_PCLKSRC_DOUBLE_MCLK, /*PCLK = 2*MCLK*/
  .rtc_src = XMC_SCU_CLOCK_RTCCLKSRC_DCO2,
  .fdiv = 0,  /**< Fractional divider */
  .idiv = 1,  /**MCLK = 32MHz */
};

XMC_CCU4_SLICE_COMPARE_CONFIG_t pwm_input_config =
{
  .timer_mode 		   = (uint32_t) XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
  .monoshot   		   = (uint32_t) false,
  .shadow_xfer_clear   = (uint32_t) 0,
  .dither_timer_period = (uint32_t) 0,
  .dither_duty_cycle   = (uint32_t) 0,
  .prescaler_mode	   = (uint32_t) XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
  .mcm_enable		   = (uint32_t) 0,
  .prescaler_initval   = (uint32_t) 0, /* range: 0 to 15; 2^prescaler */
  .float_limit		   = (uint32_t) 0,
  .dither_limit		   = (uint32_t) 0,
  .passive_level 	   = (uint32_t) XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .timer_concatenation = (uint32_t) 0
};

XMC_CCU4_SLICE_CAPTURE_CONFIG_t capture_config =
{
   .fifo_enable			= false,
   .timer_clear_mode 	= XMC_CCU4_SLICE_TIMER_CLEAR_MODE_ALWAYS,
   .same_event 			= false,
   .ignore_full_flag 	= true,
   .prescaler_mode 		= XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
   .prescaler_initval 	= (uint32_t) 0,
   .float_limit	 		= (uint32_t) 0,
   .timer_concatenation = (uint32_t) 0
};

XMC_CCU4_SLICE_EVENT_CONFIG_t capture_event0_config =  //DUTYCYCLE capture
{
  .mapped_input = XMC_CCU4_SLICE_INPUT_C,		//CAPTURE on P0.1
  .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
  .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
  .duration = XMC_CCU4_SLICE_EVENT_FILTER_7_CYCLES
};

XMC_CCU4_SLICE_EVENT_CONFIG_t capture_event1_config =	//PERIOD capture
{
  .mapped_input = XMC_CCU4_SLICE_INPUT_C,		//CAPTURE on P0.1
  .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_FALLING_EDGE,
  .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
  .duration = XMC_CCU4_SLICE_EVENT_FILTER_7_CYCLES
};


XMC_GPIO_CONFIG_t ccu_output_config =
{
   .mode                = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
//   .mode				= XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
   .input_hysteresis    = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
   .output_level        = XMC_GPIO_OUTPUT_LEVEL_LOW,
};

volatile bool updatecycle=0;
volatile uint8_t count=0;
volatile uint16_t capvalue0,capvalue1,capvalue2,capvalue3;
volatile float captureduty, capturefrequency;


/*********************************************************************************************************************
 * MAIN APPLICATION
 *********************************************************************************************************************/
/* Interrupt handler - at period match to toggle pin P0.1*/
//void CCU40_0_IRQHandler(void)
//{
//	XMC_CCU4_SLICE_ClearEvent(INPUT_SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
//	//XMC_GPIO_ToggleOutput(GPIO_OUTPUT_P0_1);
//}

//void CCU40_1_IRQHandler(void)
//{
//	XMC_CCU4_SLICE_ClearEvent(INPUT_SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_EVENT0);
//	capvalue0=XMC_CCU4_SLICE_GetCaptureRegisterValue(CAPTURE_SLICE_PTR,0U);
//	capvalue1=XMC_CCU4_SLICE_GetCaptureRegisterValue(CAPTURE_SLICE_PTR,1U);
//}

void CCU40_2_IRQHandler(void)
{
	XMC_CCU4_SLICE_ClearEvent(CAPTURE_SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_EVENT1);
	capvalue2=XMC_CCU4_SLICE_GetCaptureRegisterValue(CAPTURE_SLICE_PTR,1U);
	capvalue3=XMC_CCU4_SLICE_GetCaptureRegisterValue(CAPTURE_SLICE_PTR,3U);

	capturefrequency =  (float)(capvalue2 + capvalue3);
	captureduty =  (float)(capvalue2/capturefrequency);
}


int main(void)
{
	/* Ensure clock frequency is set at 64MHz (2*MCLK) */
	XMC_SCU_CLOCK_Init(&clock_config);

	/* Ensure fCCU reaches CCU40 */
	XMC_CCU4_SetModuleClock(INPUT_MODULE_PTR, XMC_CCU4_CLOCK_SCU);
	XMC_CCU4_Init(INPUT_MODULE_PTR, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

	/* Get the slice out of idle mode */
	XMC_CCU4_EnableClock(INPUT_MODULE_PTR, INPUT_SLICE_NUMBER);
	XMC_CCU4_EnableClock(CAPTURE_MODULE_PTR, CAPTURE_SLICE_NUMBER);

	/* Start the prescaler and restore clocks to slices */
	XMC_CCU4_StartPrescaler(INPUT_MODULE_PTR);

	/* Initialize the Slice */
	XMC_CCU4_SLICE_CompareInit(INPUT_SLICE_PTR, &pwm_input_config);
	XMC_CCU4_SLICE_CaptureInit(CAPTURE_SLICE_PTR, &capture_config);

	XMC_CCU4_SLICE_Capture0Config(CAPTURE_SLICE_PTR, XMC_CCU4_SLICE_EVENT_0);
	XMC_CCU4_SLICE_Capture1Config(CAPTURE_SLICE_PTR, XMC_CCU4_SLICE_EVENT_1);

	XMC_CCU4_SLICE_ConfigureEvent(CAPTURE_SLICE_PTR, XMC_CCU4_SLICE_EVENT_0, &capture_event0_config);
	XMC_CCU4_SLICE_ConfigureEvent(CAPTURE_SLICE_PTR, XMC_CCU4_SLICE_EVENT_1, &capture_event1_config);

	/* Enable period match events */
//	XMC_CCU4_SLICE_EnableEvent(INPUT_SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
//	XMC_CCU4_SLICE_EnableEvent(CAPTURE_SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_EVENT0);
	XMC_CCU4_SLICE_EnableEvent(CAPTURE_SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_EVENT1);

	/* Connect period match event to SR0 */
//	XMC_CCU4_SLICE_SetInterruptNode(INPUT_SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU4_SLICE_SR_ID_0);
//	XMC_CCU4_SLICE_SetInterruptNode(CAPTURE_SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_EVENT0, XMC_CCU4_SLICE_SR_ID_1);
	XMC_CCU4_SLICE_SetInterruptNode(CAPTURE_SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_EVENT1, XMC_CCU4_SLICE_SR_ID_2);

	/* Configure NVIC */
	/* Set priority */
//	NVIC_SetPriority(CCU40_0_IRQn, 3U);
//	NVIC_SetPriority(CCU40_1_IRQn, 3U);
	NVIC_SetPriority(CCU40_2_IRQn, 3U);

	/* Enable IRQ */
//	NVIC_EnableIRQ(CCU40_0_IRQn);
//	NVIC_EnableIRQ(CCU40_1_IRQn);
	NVIC_EnableIRQ(CCU40_2_IRQn);

	/* Program duty cycle and frequency */
	XMC_CCU4_SLICE_SetTimerCompareMatch(INPUT_SLICE_PTR, INPUT_PWMPERIOD/3);
	XMC_CCU4_SLICE_SetTimerPeriodMatch(INPUT_SLICE_PTR, INPUT_PWMPERIOD);

	/* Enable shadow transfer */
	XMC_CCU4_EnableShadowTransfer(INPUT_MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_0|XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_0));
	XMC_CCU4_EnableShadowTransfer(CAPTURE_MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_1|XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_1));

	/*Enable CCU4 output*/
	XMC_GPIO_Init(INPUT_CCU_OUTPUT, &ccu_output_config);

	/* Start timer */
	XMC_CCU4_SLICE_StartTimer(INPUT_SLICE_PTR);
	XMC_CCU4_SLICE_StartTimer(CAPTURE_SLICE_PTR);


	while(1)
	{

	}
	return 0;
}
