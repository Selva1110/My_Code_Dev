/**
 * \file
 *
 * \brief ADP service implementation
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include <compiler.h>
#include <hal_gpio.h>
#include <hal_io.h>
#include <adp_interface.h>

static struct io_descriptor *io;
static uint8_t               DGI_SS_PIN = 0xFF;
enum adp_interface_type { ADP_INTERFACE_SPI, ADP_INTERFACE_I2C, ADP_INTERFACE_GPIO };
static enum adp_interface_type dgi_type;
/**
 * * \brief Send SPI start condition
 * *
 * */
static inline void adp_interface_send_start(void)
{
	if (dgi_type == ADP_INTERFACE_SPI) {
		/* Send SPI start condition */
		gpio_set_pin_level(DGI_SS_PIN, false);
	}
}

/**
 * * \brief Send SPI stop condition
 * *
 * */
static inline void adp_interface_send_stop(void)
{
	if (dgi_type == ADP_INTERFACE_SPI) {
		/* Send SPI end condition */
		gpio_set_pin_level(DGI_SS_PIN, true);
	}
}

/**
 * \brief Initialize ADP SPI interface
 *
 */
void adp_interface_init_spi(struct io_descriptor *io_descr, const uint8_t ss_pin)
{
	io         = io_descr;
	dgi_type   = ADP_INTERFACE_SPI;
	DGI_SS_PIN = ss_pin;
}

/**
 * \brief Initialize ADP I2C interface
 *
 */
void adp_interface_init_i2c(struct io_descriptor *io_descr)
{
	io       = io_descr;
	dgi_type = ADP_INTERFACE_I2C;
}

/**
 * * \brief Sends and reads protocol packet data byte on SPI
 * *
 * * \param[in]  tx_buf  Pointer to send the protocol packet data
 * * \param[in]  length  The length of the send protocol packet data
 * * \param[out] rx_buf  Pointer to store the received SPI character
 * */
void adp_interface_transceive_procotol(uint8_t *tx_buf, uint16_t length, uint8_t *rx_buf)
{
	(void)rx_buf;

	adp_interface_send_start();

	io_write(io, tx_buf, length);

	adp_interface_send_stop();
}

/**
 * * \brief Read response on SPI from PC
 * *
 * * return Status
 * * \param[in]  rx_buf  Pointer to receive the data
 * * \param[in]  length  The length of the read data
 * * \param[out] rx_buf  Pointer to store the received SPI character
 * */
bool adp_interface_read_response(uint8_t *rx_buf, uint16_t length)
{
	bool status = false;

	adp_interface_send_start();

	io_read(io, rx_buf, length);

	adp_interface_send_stop();

	return status;
}
