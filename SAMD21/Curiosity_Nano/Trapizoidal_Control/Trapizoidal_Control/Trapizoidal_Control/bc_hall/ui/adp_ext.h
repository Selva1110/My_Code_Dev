#ifndef ADP_EXT_H_INCLUDED
#define ADP_EXT_H_INCLUDED

#include "adp.h"
#include "adp_interface.h"
#include <compiler.h>
#include <utils_assert.h>
#include <utils.h>

COMPILER_PACK_SET(1);
struct adp_ext_msg_response_data {
	/* ID of stream */
	uint16_t stream_id;
	/* Number of bytes in packet.
	 * If the target has requested data from an unknown stream, or if stream
	 * has no data to send, this field should be set to 0 and the appropriate
	 * status flag should be set.
	 */
	uint8_t bytes_sent;
	/* The data */
	uint8_t *data;
};
COMPILER_PACK_RESET();

bool adp_ext_add_button_to_dashboard(struct adp_msg_conf_dashboard_element_button *const config, const char *label,
                                     uint8_t *toggle);
bool adp_ext_request_data(struct adp_ext_msg_response_data *response);

/** Number of input streams configured */
uint8_t num_input_streams;

#endif
