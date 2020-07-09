#include "dashboard_config.h"
#include "block_commutation_cfg.h"

void configure_dashboard(void)
{
	while (adp_wait_for_handshake() != ADP_HANDSHAKE_ACCEPTED) {
	}

#ifdef __SAMC21J18A__
	adp_configure_info("Motor Control Example for SAM C21",
	                   "This example demonstrates Motor control through the SAMC21");
#else
	adp_configure_info("Motor Control Example for SAMD21",
	                   "This example demonstrates Motor control through the SAMD21");
#endif
	// Add Streams
	struct adp_msg_configure_stream stream;

	// Out Streams
	// Reference Motor Speed out
	stream.stream_id = STREAM_ID_MOTOR_REF_SPEED_RPM;
	stream.type      = ADP_STREAM_UINT_16;
	stream.mode      = ADP_STREAM_OUT;
	stream.state     = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Reference Speed");

	// Actual motor speed out
	stream.stream_id = STREAM_ID_MOTOR_ACTUAL_SPEED_RPM;
	stream.type      = ADP_STREAM_UINT_16;
	stream.mode      = ADP_STREAM_OUT;
	stream.state     = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Actual Speed");

	// Position streams
	stream.stream_id = STREAM_ID_POSITION;
	stream.type      = ADP_STREAM_UINT_16;
	stream.mode      = ADP_STREAM_OUT;
	stream.state     = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Position");

	// In Streams
	// Speed reference IN
	stream.stream_id = STREAM_ID_MOTOR_REF_SPEED_RPM_IN;
	stream.type      = ADP_STREAM_UINT_16;
	stream.mode      = ADP_STREAM_IN;
	stream.state     = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Reference Speed IN");
	num_input_streams++;

	// Start/Stop toggle IN
	stream.stream_id = STREAM_ID_MOTOR_START_STOP_IN;
	stream.type      = ADP_STREAM_UINT_8;
	stream.mode      = ADP_STREAM_IN;
	stream.state     = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Running status");
	num_input_streams++;

	// Kp stream In
	stream.stream_id = STREAM_ID_KP_IN;
	stream.type      = ADP_STREAM_UINT_16;
	stream.mode      = ADP_STREAM_IN;
	stream.state     = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Kp Input");
	num_input_streams++;

	// Ki stream In
	stream.stream_id = STREAM_ID_KI_IN;
	stream.type      = ADP_STREAM_UINT_16;
	stream.mode      = ADP_STREAM_IN;
	stream.state     = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Ki Input");
	num_input_streams++;

	// ramp up time stream In
	stream.stream_id = STREAM_ID_RAMPUP_TIME_IN;
	stream.type      = ADP_STREAM_UINT_16;
	stream.mode      = ADP_STREAM_IN;
	stream.state     = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Ramp up time Input");
	num_input_streams++;

	// Direction stream In
	stream.stream_id = STREAM_ID_DIRECTION_IN;
	stream.type      = ADP_STREAM_UINT_16;
	stream.mode      = ADP_STREAM_IN;
	stream.state     = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Direction Input");
	num_input_streams++;

	// Adding Controls to dashboard
	struct adp_msg_conf_dashboard dashboard
	    = {.dashboard_id = {DASHBOARD_ID_MAIN, 0}, .color = {240, 240, 240}, .height = 0x2E6};

#ifdef __SAMC21J18A__
	adp_add_dashboard(&dashboard, "BLDC Motor Control with SAMC21");
#else
	adp_add_dashboard(&dashboard, "BLDC Motor Control with SAMD21");
#endif

	// Add elements
	// Labels
	uint8_t lbl_dash_header[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_LBL_DASHBOARD_HEADER,
	    0, // ElementID
	    0, // Z-index
	    210,
	    0, // X-coordinate
	    16,
	    0, // Y-coordinate
	    194,
	    1, // Width
	    32,
	    0, // Height
	    ADP_ELEMENT_TYPE_LABEL,
	    24, // Font Size
	    1,  // Attributes - Bold On/Off -- Italic on/off
	    1,  // Horizontal alignment
	    1,  // Vertical alignment
	    0,
	    255,
	    255,
	    255, // background transparency + color
	    255,
	    0,
	    0,
	    0, // foreground transparency + color
	};

#ifdef __SAMC21J18A__
	adp_add_label_to_dashboard(&lbl_dash_header, "Block Commutation-Hall with SAMC21");
#else
	adp_add_label_to_dashboard(&lbl_dash_header, "Block Commutation-Hall with SAMD21");
#endif

	uint8_t lbl_fw_version[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_LBL_VERSION,
	    0, // ElementID
	    0, // Z-index
	    134,
	    2, // X-coordinate
	    23,
	    0, // Y-coordinate
	    56,
	    0, // Width
	    27,
	    0, // Height
	    ADP_ELEMENT_TYPE_LABEL,
	    14, // Font Size
	    1,  // Attributes - Bold On/Off -- Italic on/off
	    1,  // Horizontal alignment
	    1,  // Vertical alignment
	    0,
	    255,
	    255,
	    255, // background transparency + color
	    255,
	    0,
	    0,
	    0, // foreground transparency + color
	};

	adp_add_label_to_dashboard(&lbl_fw_version, "v1.0.2");

	uint8_t lbl_speed_ref_in[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_LBL_SPEED_REF,
	    0, // ElementID
	    0, // Z-Index (GUI stack order)
	    25,
	    0, // X-coordinate
	    108,
	    0, // Y-coordinate
	    110,
	    0, // Width
	    25,
	    0, // Height
	    ADP_ELEMENT_TYPE_LABEL,
	    12, // Font Size
	    1,  // Attributes - Bold On/Off -- Italic on/off
	    0,  // Horizontal alignment
	    0,  // Vertical alignment
	    0,
	    255,
	    255,
	    255, // background transparency + color
	    255,
	    0,
	    0,
	    0, // foreground transparency + color
	};

	adp_add_label_to_dashboard(&lbl_speed_ref_in, "Speed ref (RPM)");

	uint8_t lbl_kp_in[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_LBL_KP,
	    0, // ElementID
	    0, // Z-index
	    25,
	    0, // X-coordinate
	    153,
	    0, // Y-coordinate
	    31,
	    0, // Width
	    25,
	    0, // Height
	    ADP_ELEMENT_TYPE_LABEL,
	    12, // Font Size
	    1,  // Attributes - Bold On/Off -- Italic on/off
	    0,  // Horizontal alignment
	    0,  // Vertical alignment
	    0,
	    255,
	    255,
	    255, // background transparency + color
	    255,
	    0,
	    0,
	    0, // foreground transparency + color
	};

	adp_add_label_to_dashboard(&lbl_kp_in, "Kp");

	uint8_t lbl_ki_in[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_LBL_KI,
	    0, // ElementID
	    0, // Z-index
	    25,
	    0, // X-coordinate
	    198,
	    0, // Y-coordinate
	    31,
	    0, // Width
	    25,
	    0, // Height
	    ADP_ELEMENT_TYPE_LABEL,
	    12, // Font Size
	    1,  // Attributes - Bold On/Off -- Italic on/off
	    0,  // Horizontal alignment
	    0,  // Vertical alignment
	    0,
	    255,
	    255,
	    255, // background transparency + color
	    255,
	    0,
	    0,
	    0, // foreground transparency + color
	};

	adp_add_label_to_dashboard(&lbl_ki_in, "Ki");

	uint8_t lbl_rampup_in[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_LBL_RAMP_UP_TIME,
	    0, // ElementID
	    0, // Z-index
	    26,
	    0, // X-coordinate
	    244,
	    0, // Y-coordinate
	    110,
	    0, // Width
	    25,
	    0, // Height
	    ADP_ELEMENT_TYPE_LABEL,
	    12, // Font Size
	    1,  // Attributes - Bold On/Off -- Italic on/off
	    0,  // Horizontal alignment
	    0,  // Vertical alignment
	    0,
	    255,
	    255,
	    255, // background transparency + color
	    255,
	    0,
	    0,
	    0, // foreground transparency + color
	};

	adp_add_label_to_dashboard(&lbl_rampup_in, "Rampup (RPM/ms)");

	uint8_t lbl_direction[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_LBL_DIRECTION,
	    0, // ElementID
	    0, // Z-Index (GUI stack order)
	    27,
	    0, // X-coordinate
	    38,
	    1, // Y-coordinate
	    75,
	    0, // Width
	    25,
	    0, // Height
	    ADP_ELEMENT_TYPE_LABEL,
	    12, // Font Size
	    1,  // Attributes - Bold On/Off -- Italic on/off
	    0,  // Horizontal alignment
	    0,  // Vertical alignment
	    0,
	    255,
	    255,
	    255, // background transparency + color
	    255,
	    0,
	    0,
	    0, // foreground transparency + color
	};

	adp_add_label_to_dashboard(&lbl_direction, "Direction");

	uint8_t lbl_ref_speed_seg[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_LBL_REF_SPEED_VAL,
	    0, // ElementID
	    0, // Z-Index (GUI stack order)
	    91,
	    1, // X-coordinate
	    175,
	    1, // Y-coordinate
	    104,
	    0, // Width
	    24,
	    0, // Height
	    ADP_ELEMENT_TYPE_LABEL,
	    12, // Font Size
	    3,  // Attributes - Bold On/Off -- Italic on/off
	    0,  // Horizontal alignment
	    0,  // Vertical alignment
	    0,
	    255,
	    255,
	    255, // background transparency + color
	    255,
	    0,
	    0,
	    0, // foreground transparency + color
	};

	adp_add_label_to_dashboard(&lbl_ref_speed_seg, "Reference speed:");

	uint8_t lbl_actual_speed_seg[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_LBL_ACTUAL_SPEED_VAL,
	    0, // ElementID
	    0, // Z-Index (GUI stack order)
	    130,
	    2, // X-coordinate
	    173,
	    1, // Y-coordinate
	    80,
	    0, // Width
	    22,
	    0, // Height
	    ADP_ELEMENT_TYPE_LABEL,
	    12, // Font Size
	    3,  // Attributes - Bold On/Off -- Italic on/off
	    0,  // Horizontal alignment
	    0,  // Vertical alignment
	    0,
	    255,
	    255,
	    255, // background transparency + color
	    255,
	    0,
	    0,
	    0, // foreground transparency + color
	};

	adp_add_label_to_dashboard(&lbl_actual_speed_seg, "Actual speed:");

	// Add start/stop button
	uint8_t btn_start_stop[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_BTN_START_STOP,
	    0, // Element ID
	    0, // Z-index
	    60,
	    0, // X-coordinate
	    103,
	    1, // Y-coordinate
	    145,
	    0, // Width
	    44,
	    0, // Height
	    ADP_ELEMENT_TYPE_BUTTON,
	    20, // Font size
	};

	adp_add_button_to_dashboard(&btn_start_stop, "Start/Stop");

	struct adp_conf_add_stream_to_element element_stream = {.dashboard_id = DASHBOARD_ID_MAIN,
	                                                        .element_id   = ELEMENT_ID_BTN_START_STOP,
	                                                        .stream_id    = STREAM_ID_MOTOR_START_STOP_IN};

	adp_add_stream_to_element(&element_stream);

	// Add text boxes
	uint8_t input_speed_ref[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_INP_SPEED_REF,
	    0, // Element ID
	    0, // Z-index
	    150,
	    0, // X-coordinate
	    104,
	    0, // Y-coordinate
	    80,
	    0, // Width
	    25,
	    0, // Height
	    ADP_ELEMENT_TYPE_TEXT,
	    (uint8_t)MOTOR_MINIMUM_SPEED,
	    (uint8_t)(MOTOR_MINIMUM_SPEED >> 8),
	    0,
	    0, // Min value
	    (uint8_t)MOTOR_MAXIMUM_SPEED,
	    (uint8_t)(MOTOR_MAXIMUM_SPEED >> 8),
	    0,
	    0, // Max Value
	    (uint8_t)START_SPEED_DEFAULT,
	    (uint8_t)(START_SPEED_DEFAULT >> 8),
	    0,
	    0, // Default value
	};

	adp_add_text_to_dashboard(&input_speed_ref);

	struct adp_conf_add_stream_to_element element_stream_1 = {.dashboard_id = DASHBOARD_ID_MAIN,
	                                                          .element_id   = ELEMENT_ID_INP_SPEED_REF,
	                                                          .stream_id    = STREAM_ID_MOTOR_REF_SPEED_RPM_IN};
	adp_add_stream_to_element(&element_stream_1);

	uint8_t input_kp[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_INP_KP,
	    0, // Element ID
	    0, // Z-index
	    150,
	    0, // X-coordinate
	    150,
	    0, // Y-coordinate
	    80,
	    0, // Width
	    25,
	    0, // Height
	    ADP_ELEMENT_TYPE_TEXT,
	    0,
	    0,
	    0,
	    0, // Min value
	    255,
	    255,
	    0,
	    0, // Max Value
	    SPEED_KP_DEFAULT,
	    0,
	    0,
	    0, // Default value
	};

	adp_add_text_to_dashboard(&input_kp);

	struct adp_conf_add_stream_to_element element_stream_2
	    = {.dashboard_id = DASHBOARD_ID_MAIN, .element_id = ELEMENT_ID_INP_KP, .stream_id = STREAM_ID_KP_IN};
	adp_add_stream_to_element(&element_stream_2);

	uint8_t input_ki[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_INP_KI,
	    0, // Element ID
	    0, // Z-index
	    150,
	    0, // X-coordinate
	    195,
	    0, // Y-coordinate
	    80,
	    0, // Width
	    25,
	    0, // Height
	    ADP_ELEMENT_TYPE_TEXT,
	    0,
	    0,
	    0,
	    0, // Min value
	    255,
	    255,
	    0,
	    0, // Max Value
	    SPEED_KI_DEFAULT,
	    0,
	    0,
	    0, // Default value
	};

	adp_add_text_to_dashboard(&input_ki);

	struct adp_conf_add_stream_to_element element_stream_3
	    = {.dashboard_id = DASHBOARD_ID_MAIN, .element_id = ELEMENT_ID_INP_KI, .stream_id = STREAM_ID_KI_IN};
	adp_add_stream_to_element(&element_stream_3);

	uint8_t input_ramp_up_time[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_INP_RAMP_UP_TIME,
	    0, // Element ID
	    0, // Z-index
	    150,
	    0, // X-coordinate
	    240,
	    0, // Y-coordinate
	    80,
	    0, // Width
	    25,
	    0, // Height
	    ADP_ELEMENT_TYPE_TEXT,
	    0,
	    0,
	    0,
	    0, // Min value
	    255,
	    255,
	    0,
	    0, // Max Value
	    MOTOR_RAMPUP_SPEED_PER_MS,
	    0,
	    0,
	    0, // Default value
	};

	adp_add_text_to_dashboard(&input_ramp_up_time);

	struct adp_conf_add_stream_to_element element_stream_4 = {.dashboard_id = DASHBOARD_ID_MAIN,
	                                                          .element_id   = ELEMENT_ID_INP_RAMP_UP_TIME,
	                                                          .stream_id    = STREAM_ID_RAMPUP_TIME_IN};
	adp_add_stream_to_element(&element_stream_4);

	// Add radio group
	uint8_t rbg_direction[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_RBG_DIRECTION,
	    0, // Element ID
	    0, // Z-index
	    150,
	    0, // X-coordinate
	    34,
	    1, // Y-coordinate
	    100,
	    0, // Width
	    25,
	    0, // Height
	    ADP_ELEMENT_TYPE_RADIO,
	    12, // Font size
	    2,  // No of items
	    0,  // Orientation
	    'C',
	    'W',
	    '/',
	    'C',
	    'C',
	    'W',
	    '\0',
	};

	adp_add_radio_to_dashboard(&rbg_direction, "CW/CCW");

	struct adp_conf_add_stream_to_element element_stream_5 = {
	    .dashboard_id = DASHBOARD_ID_MAIN, .element_id = ELEMENT_ID_RBG_DIRECTION, .stream_id = STREAM_ID_DIRECTION_IN};
	adp_add_stream_to_element(&element_stream_5);

	// Add graph

	fl_axes_t time_x_min  = {0.0};
	fl_axes_t time_x_max  = {50.0};
	fl_axes_t speed_y_min = {MOTOR_MINIMUM_SPEED};
	fl_axes_t speed_y_max = {MOTOR_MAXIMUM_SPEED};

	uint8_t graph_speeds[] = {DASHBOARD_ID_MAIN,
	                          0, // DashboardID
	                          ELEMENT_ID_SPEED_GRAPH,
	                          0, // Element ID
	                          0, // Z-index
	                          34,
	                          1, // X-coordinate
	                          79,
	                          0, // Y-coordinate
	                          148,
	                          2, // Width
	                          10,
	                          1, // Height
	                          ADP_ELEMENT_TYPE_GRAPH,
	                          15,
	                          204,
	                          255, // Title color
	                          0,
	                          0,
	                          0, // Background color
	                          0,
	                          0,
	                          0, // Graph background color
	                          2, // Number of plots
	                          time_x_min.axes[0],
	                          time_x_min.axes[1],
	                          time_x_min.axes[2],
	                          time_x_min.axes[3],
	                          time_x_max.axes[0],
	                          time_x_max.axes[1],
	                          time_x_max.axes[2],
	                          time_x_max.axes[3],
	                          speed_y_min.axes[0],
	                          speed_y_min.axes[1],
	                          speed_y_min.axes[2],
	                          speed_y_min.axes[3],
	                          speed_y_max.axes[0],
	                          speed_y_max.axes[1],
	                          speed_y_max.axes[2],
	                          speed_y_max.axes[3],
	                          0x3};

	adp_add_graph_to_dashboard(&graph_speeds, "Speed (RPM)");

	struct adp_conf_add_stream_to_element element_stream_6 = {.dashboard_id = DASHBOARD_ID_MAIN,
	                                                          .element_id   = ELEMENT_ID_SPEED_GRAPH,
	                                                          .stream_id    = STREAM_ID_MOTOR_REF_SPEED_RPM};
	adp_add_stream_to_element(&element_stream_6);

	struct adp_conf_add_stream_to_element element_stream_7 = {.dashboard_id = DASHBOARD_ID_MAIN,
	                                                          .element_id   = ELEMENT_ID_SPEED_GRAPH,
	                                                          .stream_id    = STREAM_ID_MOTOR_ACTUAL_SPEED_RPM};
	adp_add_stream_to_element(&element_stream_7);

	// Add segment displays
	uint8_t seg_ref_speed[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_SEG_REF_SPEED,
	    0, // Element ID
	    0, // Z-Index (GUI stack order)
	    192,
	    1, // X-coordinate
	    174,
	    1, // Y-coordinate
	    74,
	    0, // Width
	    20,
	    0, // Height
	    ADP_ELEMENT_TYPE_SEGMENT,
	    6,  // Segment Count
	    10, // Numeric Base
	    255,
	    255,
	    0,
	    0, // Segment Color
	};

	adp_add_segment_to_dashboard(&seg_ref_speed);

	struct adp_conf_add_stream_to_element element_stream_8 = {.dashboard_id = DASHBOARD_ID_MAIN,
	                                                          .element_id   = ELEMENT_ID_SEG_REF_SPEED,
	                                                          .stream_id    = STREAM_ID_MOTOR_REF_SPEED_RPM};
	adp_add_stream_to_element(&element_stream_8);

	uint8_t seg_actual_speed[] = {
	    DASHBOARD_ID_MAIN,
	    0, // DashboardID
	    ELEMENT_ID_SEG_ACTUAL_SPEED,
	    0, // Element ID
	    0, // Z-Index (GUI stack order)
	    213,
	    2, // X-coordinate
	    172,
	    1, // Y-coordinate
	    74,
	    0, // Width
	    20,
	    0, // Height
	    ADP_ELEMENT_TYPE_SEGMENT,
	    6,  // Segment Count
	    10, // Numeric Base
	    255,
	    0,
	    144,
	    0, // Segment Color
	};

	adp_add_segment_to_dashboard(&seg_actual_speed);

	struct adp_conf_add_stream_to_element element_stream_9 = {.dashboard_id = DASHBOARD_ID_MAIN,
	                                                          .element_id   = ELEMENT_ID_SEG_ACTUAL_SPEED,
	                                                          .stream_id    = STREAM_ID_MOTOR_ACTUAL_SPEED_RPM};
	adp_add_stream_to_element(&element_stream_9);

	fl_axes_t time_x_max_1   = {1.0};
	fl_axes_t position_y_min = {0.0};
	fl_axes_t position_y_max = {7.5};

	uint8_t graph_position[] = {DASHBOARD_ID_MAIN,
	                            0, // DashboardID
	                            ELEMENT_ID_POSITION_GRAPH,
	                            0, // Element ID
	                            0, // Z-Index (GUI stack order)
	                            34,
	                            1, // X-coordinate
	                            210,
	                            1, // Y-coordinate
	                            146,
	                            2, // Width
	                            221,
	                            0,                      // Height
	                            ADP_ELEMENT_TYPE_GRAPH, // Element Type
	                            255,
	                            255,
	                            255, // Title color
	                            0,
	                            0,
	                            0, // Background color
	                            20,
	                            20,
	                            20, // Graph background color
	                            1,  // Number of plots
	                            time_x_min.axes[0],
	                            time_x_min.axes[1],
	                            time_x_min.axes[2],
	                            time_x_min.axes[3],
	                            time_x_max_1.axes[0],
	                            time_x_max_1.axes[1],
	                            time_x_max_1.axes[2],
	                            time_x_max_1.axes[3],
	                            position_y_min.axes[0],
	                            position_y_min.axes[1],
	                            position_y_min.axes[2],
	                            position_y_min.axes[3],
	                            position_y_max.axes[0],
	                            position_y_max.axes[1],
	                            position_y_max.axes[2],
	                            position_y_max.axes[3],
	                            0x3};

	adp_add_graph_to_dashboard(&graph_position, "Position");

	struct adp_conf_add_stream_to_element element_stream_10
	    = {.dashboard_id = DASHBOARD_ID_MAIN, .element_id = ELEMENT_ID_POSITION_GRAPH, .stream_id = STREAM_ID_POSITION};
	adp_add_stream_to_element(&element_stream_10);

	dashboardconfigured = 1;
}
