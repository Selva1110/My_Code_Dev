#include "adp_ext.h"
#include <compiler.h>
#include <utils.h>
#include <string.h>

static uint16_t adp_add_dashboard_element_common_send_byte(uint8_t *add_buf, uint16_t index,
                                                           struct adp_msg_conf_dashboard_element_common *const config)
{
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->dashboard_id, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->element_id, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->z_index, 1);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->x, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->y, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->width, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->height, 2);
	index = adp_add_send_byte(add_buf, index, (uint8_t *)&config->element_type, 1);

	return index;
}

/**
 * \brief Add a button to dashboard
 *
 * \param[in] config    Pointer to dashboard button struct
 * \param[in] label		Pointer to char array containing button label
 * \param[in] config		Pointer to integer specifying button toggle
 *
 * \return Status from PC
 * \retval true   Message received and accepted
 * \retval false  Message received but not accepted
 */
bool adp_ext_add_button_to_dashboard(struct adp_msg_conf_dashboard_element_button *const config, const char *label,
                                     uint8_t *toggle)
{
	uint8_t  ack;
	uint16_t label_len;

	/* Add 0-termination to label string length */
	label_len = strlen(label) + 1;

	/* Make sure label isn't too big */
	ASSERT(ADP_ELEMENT_TYPE_BUTTON_LEN + label_len <= ADP_MAX_PACKET_DATA_SIZE);

	uint16_t data_length;
	uint16_t index                         = 0;
	uint8_t  rx_buf[ADP_MAX_PACKET_LENGTH] = {
        0,
    };

	struct adp_msg_format msg_format;

	msg_format.protocol_token  = ADP_TOKEN;
	msg_format.protocol_msg_id = MSG_CONF_DASHBOARD_ELEMENT;
	msg_format.data_length     = ADP_ELEMENT_TYPE_BUTTON_LEN + label_len + 1;
	index                      = adp_add_dashboard_element_common_send_byte(
        (uint8_t *)&msg_format.data, index, (struct adp_msg_conf_dashboard_element_common *)config);
	index       = adp_add_send_byte((uint8_t *)&msg_format.data, index, (uint8_t *)&config->font_size, 1);
	index       = adp_add_send_byte((uint8_t *)&msg_format.data, index, (uint8_t *)label, label_len);
	index       = adp_add_send_byte((uint8_t *)&msg_format.data, index, (uint8_t *)toggle, 1);
	data_length = ADP_LENGTH_PACKET_HEADER + index;

	/* Send the protocol packet data */
	adp_interface_transceive_procotol((uint8_t *)&msg_format, data_length, rx_buf);

	return true;
}

/**
 * \brief Send MSG_REQ_DATA_READY and wait for response
 *
 * \param[out] response Struct containing response
 *
 * \return None
 */
bool adp_ext_request_data(struct adp_ext_msg_response_data *response)
{
	uint8_t rx_buf[4] = {
	    0,
	};

	/* Send the protocol packet data */
	adp_interface_read_response(rx_buf, 3);

	if (rx_buf[1] == MSG_RES_DATA) {
		uint16_t res_data_len = (uint16_t)((rx_buf[3] << 8) + rx_buf[2] + 1);
		uint8_t  res_data_buf[res_data_len];

		memset(res_data_buf, 0, sizeof(res_data_buf));

		adp_interface_read_response(res_data_buf, res_data_len);

		memset(response, 0, sizeof(response));

		response->stream_id  = (uint16_t)((res_data_buf[0] << 8) + res_data_buf[1]);
		response->bytes_sent = (uint16_t)((res_data_buf[2] << 8) + res_data_buf[3]);

		uint8_t data_buf[response->bytes_sent];
		for (int i = 0, j = 4; i < response->bytes_sent; i++, j++) {
			data_buf[i] = res_data_buf[j];
		}

		response->data = data_buf;

		return true;
	}

	return false;
}
