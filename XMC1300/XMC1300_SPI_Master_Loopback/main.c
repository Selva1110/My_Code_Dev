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
 * @brief SPI demo example
 *
 * Send two periodic messages via SPI with different lengths
 *
 * History <br>
 *
 * Version 0.1.0 Initial <br>
 *
 */

#include "xmc_spi.h"
#include "xmc_gpio.h"

#define LED P0_0

void timing_delay(void);

uint16_t datain;

XMC_GPIO_CONFIG_t rx_pin_config;
XMC_GPIO_CONFIG_t tx_pin_config;
XMC_GPIO_CONFIG_t selo_pin_config;
XMC_GPIO_CONFIG_t clk_pin_config;

/**
 * @brief SPI configuration structure
*/
XMC_SPI_CH_CONFIG_t spi_config =
{
  .baudrate = 10000,
  .bus_mode = XMC_SPI_CH_BUS_MODE_MASTER,
  .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
  .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
};

void USIC0_0_IRQHandler(void)
{
	if((XMC_SPI_CH_GetStatusFlag(XMC_SPI0_CH1) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 1U);
	{
		XMC_SPI_CH_ClearStatusFlag(XMC_SPI0_CH1, XMC_SPI_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);
		timing_delay();
		  XMC_GPIO_ToggleOutput(LED);


		datain = XMC_USIC_CH_RXFIFO_GetData(XMC_SPI0_CH1);
		//Transmit data 0x4D2
		  XMC_USIC_CH_TXFIFO_PutData(XMC_SPI0_CH1, 0x4D2);

	}
}

int main(void)
{
  /* Initialize SPI */
  XMC_SPI_CH_Init(XMC_SPI0_CH1, &spi_config);
  XMC_SPI_CH_SetWordLength(XMC_SPI0_CH1, 16);
  XMC_SPI_CH_SetFrameLength(XMC_SPI0_CH1, 16);
  XMC_SPI_CH_SetBitOrderMsbFirst(XMC_SPI0_CH1);

  XMC_USIC_CH_RXFIFO_Configure(XMC_SPI0_CH1, 32, XMC_USIC_CH_FIFO_SIZE_32WORDS, 0);
  XMC_USIC_CH_TXFIFO_Configure(XMC_SPI0_CH1, 0, XMC_USIC_CH_FIFO_SIZE_32WORDS, 0);
  XMC_SPI_CH_SetInputSource(XMC_SPI0_CH1, XMC_SPI_CH_INPUT_DIN0, USIC0_C1_DX0_P1_2);


  /* Event/interrupt configuration. */
  XMC_SPI_CH_EnableEvent(XMC_SPI0_CH1, XMC_SPI_CH_EVENT_ALTERNATIVE_RECEIVE);

  /* Start operation. */
  XMC_SPI_CH_Start(XMC_SPI0_CH1);

  /* GPIO Input pin configuration */
  rx_pin_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
  XMC_GPIO_Init(XMC_GPIO_PORT1,2, &rx_pin_config);

  /* GPIO Output pin configuration */
  tx_pin_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
  XMC_GPIO_Init(XMC_GPIO_PORT1,2, &tx_pin_config);

  /* GPIO Slave Select line pin configuration */
  selo_pin_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
  XMC_GPIO_Init(XMC_GPIO_PORT1,1, &selo_pin_config);

  /* GPIO Clock pin configuration */
  clk_pin_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2;
  XMC_GPIO_Init(XMC_GPIO_PORT1,4, &clk_pin_config);

  XMC_GPIO_SetMode(LED, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  NVIC_SetPriority(USIC0_0_IRQn, 0U);
  NVIC_EnableIRQ(USIC0_0_IRQn);

  USIC0_CH1->PSR_SSCMode |= 0x8000;
  XMC_USIC_CH_TriggerServiceRequest(XMC_SPI0_CH1, 0);

  while(1)
  {
    /* Infinite loop */
  }
}

void timing_delay(void)
{
	uint32_t d;
	for(d=0; d<100000;d++)
	{;}
}
