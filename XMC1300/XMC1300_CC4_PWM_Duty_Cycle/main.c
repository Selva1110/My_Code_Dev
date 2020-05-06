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
 * How to start a timer (Single PWM)
 * This example generates a PWM signal and an interrupt on every compare match, which alternates
 * the PWM's duty cycle between 33.3% and 66.7%.
 * Frequency set at 1Hz
 *
 * => Measure GPIO to check PWM waveform
 * */

#include <xmc_ccu4.h>		//SFR declarations of the selected device
#include <xmc_gpio.h>		//SFR declarations of the selected device

/*********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/
#define SLICE_PTR         CCU40_CC40
#define MODULE_PTR        CCU40
#define MODULE_NUMBER     (0U)
#define SLICE_NUMBER      (0U)
#define CCU_OUTPUT		  P0_0
#define PWMPERIOD		  (62499U) //PWM period calculated based on PCLK = 64MHz
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

XMC_CCU4_SLICE_COMPARE_CONFIG_t compare_config =
{
  .timer_mode 		   = (uint32_t) XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
  .monoshot   		   = (uint32_t) false,
  .shadow_xfer_clear   = (uint32_t) 0,
  .dither_timer_period = (uint32_t) 0,
  .dither_duty_cycle   = (uint32_t) 0,
  .prescaler_mode	   = (uint32_t) XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
  .mcm_enable		   = (uint32_t) 0,
  .prescaler_initval   = (uint32_t) 10,
  .float_limit		   = (uint32_t) 0,
  .dither_limit		   = (uint32_t) 0,
  .passive_level 	   = (uint32_t) XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .timer_concatenation = (uint32_t) 0
};

XMC_GPIO_CONFIG_t ccu_output_config =
{
   .mode                = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
   .input_hysteresis    = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
   .output_level        = XMC_GPIO_OUTPUT_LEVEL_LOW,
};

volatile bool updatecycle=0;
volatile uint8_t count=0;

uint16_t comparevalue[]=
{
		20833U,		//66.67% duty cycle; based on PCLK of 64MHz
		41666U		//33.33% duty cycle
};

/*********************************************************************************************************************
 * MAIN APPLICATION
 *********************************************************************************************************************/
/* Interrupt handler - at compare match */
void CCU40_0_IRQHandler(void)
{
	XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE_PTR, comparevalue[count]);
	count++;
	if(count==2)
	{
		count=0;
	}

	/* Enable shadow transfer */
	XMC_CCU4_EnableShadowTransfer(MODULE_PTR, XMC_CCU4_SHADOW_TRANSFER_SLICE_0);
}

int main(void)
{
	/* Ensure clock frequency is set at 64MHz (2*MCLK) */
	XMC_SCU_CLOCK_Init(&clock_config);

	/* Ensure fCCU reaches CCU40 */
	XMC_CCU4_SetModuleClock(MODULE_PTR, XMC_CCU4_CLOCK_SCU);
	XMC_CCU4_Init(MODULE_PTR, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

	/* Get the slice out of idle mode */
	XMC_CCU4_EnableClock(MODULE_PTR, SLICE_NUMBER);

	/* Start the prescaler and restore clocks to slices */
	XMC_CCU4_StartPrescaler(MODULE_PTR);

	/* Initialize the Slice */
	XMC_CCU4_SLICE_CompareInit(SLICE_PTR, &compare_config);

	/* Enable compare match events */
	XMC_CCU4_SLICE_EnableEvent(SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP);

    /* Connect compare match event to SR0 */
	XMC_CCU4_SLICE_SetInterruptNode(SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP, XMC_CCU4_SLICE_SR_ID_0);

	/* Configure NVIC */
	/* Set priority */
	NVIC_SetPriority(CCU40_0_IRQn, 3U);

	/* Enable IRQ */
	NVIC_EnableIRQ(CCU40_0_IRQn);

	/* Program duty cycle = 33.33% at 1Hz frequency */
	XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE_PTR, comparevalue[count+1]);
	XMC_CCU4_SLICE_SetTimerPeriodMatch(SLICE_PTR, PWMPERIOD);

	/* Enable shadow transfer */
	XMC_CCU4_EnableShadowTransfer(MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_0|XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_0));

	/*Enable CCU4 output*/
	XMC_GPIO_Init(CCU_OUTPUT, &ccu_output_config);

	/* Start timer */
	XMC_CCU4_SLICE_StartTimer(SLICE_PTR);


	while(1)
	{

	}
	return 0;
}
