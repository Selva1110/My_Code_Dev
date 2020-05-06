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
 * @brief UART demo example
 *
 * Send a periodic message via UART
 *
 * History <br>
 *
 * Version 0.1.0 Initial <br>
 *
 */

#include "xmc_gpio.h"
#include "xmc_uart.h"

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 1000

const uint8_t message[] = "Hello world!!\n";


XMC_GPIO_CONFIG_t led1_config;
XMC_GPIO_CONFIG_t rx_pin_config;
XMC_GPIO_CONFIG_t tx_pin_config;
XMC_UART_CH_CONFIG_t uart_config;

void SysTick_Handler(void)
{
  uint32_t index;
  static uint32_t ticks = 0;

  ticks++;
  if (ticks == TICKS_WAIT)
  {
	XMC_GPIO_ToggleOutput(XMC_GPIO_PORT0,6);

	for (index = 0; index < sizeof(message) - 1; index++)
	{
	  XMC_UART_CH_Transmit(XMC_UART0_CH1, message[index]);
	}
	ticks = 0;
  }
}


int main(void)
{
  /* Configure LED1 */
  led1_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  XMC_GPIO_Init(XMC_GPIO_PORT0,6, &led1_config);

  /* UART configuration */
  uart_config.data_bits = 8U;
  uart_config.stop_bits = 1U;
  uart_config.baudrate = 115200;

  /* Configure RX pin */
  rx_pin_config.mode = XMC_GPIO_MODE_INPUT_INVERTED_TRISTATE;
  XMC_GPIO_Init(XMC_GPIO_PORT1,3, &rx_pin_config);

  XMC_UART_CH_SetInputSource(XMC_UART0_CH1,XMC_UART_CH_INPUT_RXD,USIC0_C1_DX0_P1_3);


  /* Configure UART channel */
  XMC_UART_CH_Init(XMC_UART0_CH1, &uart_config);
  /* Start UART channel */
  XMC_UART_CH_Start(XMC_UART0_CH1);

  /* Configure TX pin */
  tx_pin_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
  XMC_GPIO_Init(XMC_GPIO_PORT1,2, &tx_pin_config);

  /* Send a message via UART periodically */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while(1)
  {
	/* Infinite loop */
  }
}
