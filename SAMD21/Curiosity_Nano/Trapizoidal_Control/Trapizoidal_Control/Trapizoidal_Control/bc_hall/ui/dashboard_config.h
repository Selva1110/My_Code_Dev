#ifndef DASHBOARD_CONFIG_H
#define DASHBOARD_CONFIG_H

#include "adp.h"
#include "adp_ext.h"
#include "pi.h"

/* Stream IDs */
#define STREAM_ID_MOTOR_RUN_STATE 0x29
#define STREAM_ID_MOTOR_REF_SPEED_RPM 0x01
#define STREAM_ID_MOTOR_ACTUAL_SPEED_RPM 0x02
#define STREAM_ID_KP_IN 0x03
#define STREAM_ID_KI_IN 0x04
#define STREAM_ID_RAMPUP_TIME_IN 0x05
#define STREAM_ID_DIRECTION_IN 0x06
#define STREAM_ID_POSITION 0x07
#define STREAM_ID_IDCUR 0x08
#define STREAM_ID_MOTOR_REF_SPEED_RPM_IN 0x10
#define STREAM_ID_IQCUR_KP_IN 0x11
#define STREAM_ID_IQCUR_KI_IN 0x12
#define STREAM_ID_IDCUR_KP_IN 0x13
#define STREAM_ID_IDCUR_KI_IN 0x14
#define STREAM_ID_ACCRAMP_IN 0x15
#define STREAM_ID_DECRAMP_IN 0x16
#define STREAM_ID_CRITERRFLAG_IN 0x17
#define STREAM_ID_MOTOR_START_STOP_IN 0x30

/* Dashboard IDs */
#define DASHBOARD_ID_MAIN 0

/* Element IDs */
#define ELEMENT_ID_LBL_DASHBOARD_HEADER 0
#define ELEMENT_ID_BTN_START_STOP 1
#define ELEMENT_ID_LBL_SPEED_REF 2
#define ELEMENT_ID_LBL_SPEED_REF_RPM_CONST 3
#define ELEMENT_ID_LBL_KP 4
#define ELEMENT_ID_LBL_KI 5
#define ELEMENT_ID_LBL_RAMP_UP_TIME 6
#define ELEMENT_ID_LBL_RAMP_UP_TIME_MS_CONST 7
#define ELEMENT_ID_INP_SPEED_REF 8
#define ELEMENT_ID_INP_KP 9
#define ELEMENT_ID_INP_KI 10
#define ELEMENT_ID_INP_RAMP_UP_TIME 11
#define ELEMENT_ID_SPEED_GRAPH 12
#define ELEMENT_ID_RBG_DIRECTION 13
#define ELEMENT_ID_LBL_DIRECTION 14
#define ELEMENT_ID_LBL_REF_SPEED_VAL 15
#define ELEMENT_ID_LBL_ACTUAL_SPEED_VAL 16
#define ELEMENT_ID_SEG_REF_SPEED 17
#define ELEMENT_ID_SEG_ACTUAL_SPEED 18
#define ELEMENT_ID_POSITION_GRAPH 19

#define ELEMENT_ID_LBL_KP_IQCUR 20
#define ELEMENT_ID_LBL_KI_IQCUR 21
#define ELEMENT_ID_LBL_ACC_RAMP 22
#define ELEMENT_ID_LBL_DEC_RAMP 23

#define ELEMENT_ID_INP_KP_IQCUR 24
#define ELEMENT_ID_INP_KI_IQCUR 25
#define ELEMENT_ID_INP_ACC_RAMP 26
#define ELEMENT_ID_INP_DEC_RAMP 27

#define ELEMENT_ID_LBL_CRITERRFLAGS 28
#define ELEMENT_ID_LBL_CRITERRFLAGS_VALUE 29

#define ELEMENT_ID_LBL_VERSION 30

typedef union fl_t {
	float   axisvalue;
	uint8_t axes[4];
} fl_axes_t;

void configure_dashboard(void);

#define BC_HALL_SAMD21_MAJOR_VERSION 1
#define BC_HALL_SAMD21_MINOR_VERSION 0
#define BC_HALL_SAMD21_PATCH_VERSION 0

#define BC_HALL_SAMD21_VERSION_ADP '1', '.', '0', '.', '0'

/* ADP specific variables */
extern uint8_t  dashboardconfigured;
extern uint8_t  start_toggle;
extern uint8_t  state_run;
extern uint16_t set_speed;
extern uint8_t  direction;

extern uint16_t kp_ref;
extern uint16_t ki_ref;
extern uint16_t ramp_speedperms;

extern picontrol_type speedpi;

#endif
