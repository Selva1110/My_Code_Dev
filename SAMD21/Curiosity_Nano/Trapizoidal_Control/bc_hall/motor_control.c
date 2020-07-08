#include "motor_control.h"
#include "ui/dashboard_config.h"
#include "block_commutation_cfg.h"
#include "atmel_start.h"

/*********************************************************************************/
/* Variables                                                                     */
/*********************************************************************************/

picontrol_type speedpi;

uint16_t        set_speed;
static uint16_t speed_reference;

static uint8_t  curpattern  = 1;
static uint8_t  nextpattern = 3;
static uint32_t avgtimestorage;
static uint16_t avgcycletime;
static uint16_t actual_speed;
static uint16_t avgctr;
uint8_t         state_run;
uint8_t         direction;

static uint8_t curhall1;
static uint8_t curhall2;
static uint8_t curhall3;

static uint16_t picounter;

static uint16_t timecounter;
uint8_t         dashboardconfigured;
uint8_t         start_toggle;

uint16_t kp_ref;
uint16_t ki_ref;
uint16_t ramp_speedperms;

static struct timer_task task_one_ms_event;

extern struct timer_descriptor TIMER_ONE_MS;
extern uint8_t                 num_input_streams;

/*********************************************************************************/
/* Constants                                                                     */
/*********************************************************************************/

#if (MOTOR_TYPE == M42BL02402)
// LDO M42BL02402
const uint16_t COMMUTATION_ARRAY[16] = {0,
                                        0x2073,
                                        0x1075,
                                        0x1073,
                                        0x4076,
                                        0x2076,
                                        0x4075,
                                        0,
                                        0,
                                        /* to achieve C+ B-, put the following in Pattern register H1H2H3: 001 */
                                        0x4075, // 0x4075, HS //0x0237U, LS
                                        /* to achieve B+ A-, put the following in Pattern register H1H2H3: 010 */
                                        0x2076, // 0x2076, HS //0x0157U, LS
                                        /* to achieve C+ A-, put the following in Pattern register H1H2H3: 011 */
                                        0x4076, // 0x4076, HS //0x0137U, LS
                                        /* to achieve A+ C-, put the following in Pattern register H1H2H3: 100 */
                                        0x1073, // 0x1073, HS //0x0467U, LS
                                        /* to achieve A+ B-, put the following in Pattern register H1H2H3: 101 */
                                        0x1075, // 0x1075, HS //0x0267U, LS
                                        /* to achieve B+ C-, put the following in Pattern register H1H2H3: 110 */
                                        0x2073, // 0x2073, HS //0x0457U, LS
                                        /* Not a valid pattern */
                                        0};
#endif

#if (MOTOR_TYPE == CUSTOM)
// Custom (User define motor)
const uint16_t COMMUTATION_ARRAY[16] = {0,
                                        /* to achieve C+ B-, put the following in Pattern register H1H2H3: 001 */
                                        0x4075, // 0x4075, HS //0x0237U, LS
                                        /* to achieve B+ A-, put the following in Pattern register H1H2H3: 010 */
                                        0x2076, // 0x2076, HS //0x0157U, LS
                                        /* to achieve C+ A-, put the following in Pattern register H1H2H3: 011 */
                                        0x4076, // 0x4076, HS //0x0137U, LS
                                        /* to achieve A+ C-, put the following in Pattern register H1H2H3: 100 */
                                        0x1073, // 0x1073, HS //0x0467U, LS
                                        /* to achieve A+ B-, put the following in Pattern register H1H2H3: 101 */
                                        0x1075, // 0x1075, HS //0x0267U, LS
                                        /* to achieve B+ C-, put the following in Pattern register H1H2H3: 110 */
                                        0x2073, // 0x2073, HS //0x0457U, LS
                                        /* Not a valid pattern */
                                        0,
                                        0,
                                        0x2073,
                                        0x1075,
                                        0x1073,
                                        0x4076,
                                        0x2076,
                                        0x4075,
                                        0};
#endif

static const uint8_t HALL_ARRAY[16] = {0, 3, 6, 2, 5, 1, 4, 0, 0, 5, 3, 1, 6, 4, 2, 0};

/*********************************************************************************/
/* Function Definitions                                                          */
/*********************************************************************************/
uint16_t _timer_get_count(const void *const hw)
{
#ifdef __SAMC21J18A__
	hri_tcc_clear_CTRLB_reg(hw, TC_CTRLBCLR_CMD_NONE);
	hri_tc_wait_for_sync(hw, TC_SYNCBUSY_MASK);
	hri_tcc_set_CTRLB_reg(hw, TC_CTRLBSET_CMD_READSYNC);
	hri_tc_wait_for_sync(hw, TC_SYNCBUSY_MASK);
#else
	hri_tc_wait_for_sync(hw);
#endif
	return hri_tccount16_read_COUNT_reg(hw);
}

void _timer_set_count(const void *const hw, uint16_t data)
{
#ifdef __SAMC21J18A__
	hri_tc_wait_for_sync(hw, TC_SYNCBUSY_MASK);
#else
	hri_tc_wait_for_sync(hw);
#endif
	hri_tccount16_write_COUNT_COUNT_bf(hw, data);
}

void _timer_stop_a(const void *const hw)
{
#ifdef __SAMC21J18A__
	hri_tcc_set_CTRLB_reg(hw, TC_CTRLBSET_CMD_STOP);
	hri_tc_wait_for_sync(hw, TC_SYNCBUSY_MASK);
#else
	if (hri_tc_get_CTRLA_ENABLE_bit(hw) == true) {
		hri_tc_wait_for_sync(hw);

		TC_CRITICAL_SECTION_ENTER();
		((Tc *)hw)->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD(2);
		TC_CRITICAL_SECTION_LEAVE();
	}
#endif
}

void _timer_start_a(const void *const hw)
{
#ifdef __SAMC21J18A__
	hri_tc_wait_for_sync(hw, TC_SYNCBUSY_MASK);
	hri_tcc_clear_CTRLB_reg(hw, TC_CTRLBCLR_CMD_NONE);
	hri_tc_wait_for_sync(hw, TC_SYNCBUSY_MASK);
	hri_tcc_set_CTRLB_reg(hw, TC_CTRLBSET_CMD_RETRIGGER);
	hri_tc_wait_for_sync(hw, TC_SYNCBUSY_MASK);
#else
	hri_tc_wait_for_sync(hw);

	TC_CRITICAL_SECTION_ENTER();
	((Tc *)hw)->COUNT16.CTRLBCLR.reg = TC_CTRLBCLR_CMD_NONE;
	TC_CRITICAL_SECTION_LEAVE();

	hri_tc_wait_for_sync(hw);

	TC_CRITICAL_SECTION_ENTER();
	((Tc *)hw)->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD(1);
	TC_CRITICAL_SECTION_LEAVE();
#endif
}

void speed_measurement_init()
{
#ifdef __SAMC21J18A__
	// Make it in 16 bit mode
	hri_tc_wait_for_sync(TC3, TC_SYNCBUSY_MASK);
	TC3->COUNT16.CTRLA.bit.MODE = 0x00;

	// Count in normal PWM mode
	hri_tc_wait_for_sync(TC3, TC_SYNCBUSY_MASK);
	TC3->COUNT16.WAVE.bit.WAVEGEN = 0x00;

	hri_tc_wait_for_sync(TC3, TC_SYNCBUSY_MASK);

	TC3->COUNT16.CC[0].reg = 0xFFFF;

	hri_tc_wait_for_sync(TC3, TC_SYNCBUSY_MASK);

	timer_start(&TIMER_SPEED_MEASURE);

	hri_tc_wait_for_sync(TC3, TC_SYNCBUSY_MASK);

	// force stop the timer
	TC3->COUNT16.CTRLBSET.bit.CMD = 0x02;

	hri_tc_wait_for_sync(TC3, TC_SYNCBUSY_MASK);
#else
	// Make it in 16 bit mode
	hri_tc_wait_for_sync(TC3);
	TC3->COUNT16.CTRLA.bit.MODE = 0x00;

	// Count in normal PWM mode
	hri_tc_wait_for_sync(TC3);
	TC3->COUNT16.CTRLA.bit.WAVEGEN = 0x00;
	hri_tc_wait_for_sync(TC3);

	TC3->COUNT16.CC[0].reg = 0xFFFF;

	hri_tc_wait_for_sync(TC3);

	timer_start(&TIMER_SPEED_MEASURE);

	hri_tc_wait_for_sync(TC3);

	// force stop the timer
	TC3->COUNT16.CTRLBSET.bit.CMD = 0x02;

	hri_tc_wait_for_sync(TC3);
#endif
}

void motor_pwm_init()
{
	pwm_set_parameters(&PWM_MOTOR_DRIVER, 2400, 240);
	TCC0->PER.reg = 2400U;
	// PWM config specific to motor
	TCC0->WEXCTRL.reg = TCC_WEXCTRL_OTMX(2);
	pwm_enable(&PWM_MOTOR_DRIVER);
}

void register_hall_events(void)
{
	ext_irq_register(HALL_SENSOR_PINA, update_commutation);
	ext_irq_register(HALL_SENSOR_PINB, update_commutation);
	ext_irq_register(HALL_SENSOR_PINC, update_commutation);
}

void register_one_ms_timer_events(void)
{
	task_one_ms_event.interval = 1;
	task_one_ms_event.cb       = app_one_ms_isr;
	task_one_ms_event.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_ONE_MS, &task_one_ms_event);
	timer_start(&TIMER_ONE_MS);
}

void init_global_variables(void)
{
	state_run = 0;

	set_speed           = START_SPEED_DEFAULT;
	speedpi.error       = 0;
	speedpi.kp          = (int32_t)SPEED_KP_DEFAULT;
	speedpi.ki          = (int32_t)SPEED_KI_DEFAULT;
	speedpi.maxlimit    = 2300;
	speedpi.minlimit    = 50;
	speedpi.outputvalue = 0;
	timecounter         = 0;
	direction           = 0;
	picounter           = 0;
	dashboardconfigured = 0;
	start_toggle        = 0;
	kp_ref              = 0;
	ki_ref              = 0;
	ramp_speedperms     = MOTOR_RAMPUP_SPEED_PER_MS;
}

void update_commutation(void)
{
	uint16_t timeelapsed = 0;

	if (state_run == 1U) {
#ifdef __SAMD21E16L__
		/* EIC Hall register mapping for ATSAMD21E16LMOTOR MCU board */
		curhall1 = (uint8_t)((REG_PORT_IN0 & 0x00000008U) >> 1U);
		curhall2 = (uint8_t)((REG_PORT_IN0 & 0x00000004U) >> 1U);
		curhall3 = (uint8_t)((REG_PORT_IN0 & 0x00000080U) >> 7U);
#elif __SAMD21J18A__
		/* EIC Hall register mapping for ATSAMD21MOTOR MCU board */
		curhall1 = (uint8_t)((REG_PORT_IN0 & 0x00000008U) >> 1U);
		curhall2 = (uint8_t)((REG_PORT_IN0 & 0x00040000U) >> 17U);
		curhall3 = (uint8_t)((REG_PORT_IN0 & 0x10000000U) >> 28U);
#elif __SAMC21J18A__
		/* EIC Hall register mapping for ATSAMC21MOTOR MCU board */
		curhall1 = (uint8_t)((REG_PORT_IN1 & 0x00000800U) >> 9U);
		curhall2 = (uint8_t)((REG_PORT_IN1 & 0x00000010U) >> 3U);
		curhall3 = (uint8_t)((REG_PORT_IN0 & 0x10000000U) >> 28U);
#endif

		curpattern = (curhall1 | curhall2 | curhall3);

		if ((curpattern == nextpattern) && ((curpattern != 0U) && (curpattern != 7U))) {
			/* PWM should be applied only at low side switches */
			TCC0->PATT.reg = COMMUTATION_ARRAY[curpattern + (direction)];

			/* wait for Pattern update synchronization */
			while (TCC0->SYNCBUSY.bit.PATT == 1U) {
			}
			nextpattern = HALL_ARRAY[curpattern + (direction)];

			timeelapsed = (uint16_t)_timer_get_count(TC3);
			_timer_stop_a(TC3);
#ifdef __SAMC21J18A__
			hri_tc_wait_for_sync(TC3, TC_SYNCBUSY_MASK);
#else
			hri_tc_wait_for_sync(TC3);
#endif
			_timer_start_a(TC3);
#ifdef __SAMC21J18A__
			hri_tc_wait_for_sync(TC3, TC_SYNCBUSY_MASK);
#else
			hri_tc_wait_for_sync(TC3);
#endif

			if (avgctr == 0U) {
				avgcycletime = (uint16_t)(avgtimestorage / MOTOR_SPEED_CALCFACTOR);
				avgtimestorage -= avgcycletime;
			} else {
				avgctr--;
			}

			avgtimestorage += timeelapsed;

			if (avgcycletime != 0U) {
				actual_speed = (uint16_t)(5120000U / (MOTOR_POLE_PAIRS * (uint32_t)avgcycletime));
				/* 5120000/(PP * Avgcycletime) ; Tecmotor pp = 4;Annaheim pp = 2; */
			}
		}
	}
}

void motor_start(void)
{
	speed_reference  = (uint16_t)START_SPEED_DEFAULT - (uint16_t)100;
	pi_integratorbuf = 0;
	actual_speed     = 0;
	/* speed variables for HALL sensor read */
	avgtimestorage = 0;
	avgcycletime   = 0;
	avgctr         = (uint16_t)MOTOR_SPEED_CALCFACTOR;
	/* Initialize duty cycle */
	TCC0->CC[0].reg = SPEED_DEFAULT_DUTY;

#ifdef __SAMD21E16L__
	/* EIC Hall register mapping for ATSAMD21E16LMOTOR MCU board */
	curhall1 = (uint8_t)((REG_PORT_IN0 & 0x00000008U) >> 1U);
	curhall2 = (uint8_t)((REG_PORT_IN0 & 0x00000004U) >> 1U);
	curhall3 = (uint8_t)((REG_PORT_IN0 & 0x00000080U) >> 7U);
#elif __SAMD21J18A__
	/* EIC Hall register mapping for ATSAMD21MOTOR MCU board */
	curhall1 = (uint8_t)((REG_PORT_IN0 & 0x00000008U) >> 1U);
	curhall2 = (uint8_t)((REG_PORT_IN0 & 0x00040000U) >> 17U);
	curhall3 = (uint8_t)((REG_PORT_IN0 & 0x10000000U) >> 28U);
#elif __SAMC21J18A__
	/* EIC Hall register mapping for ATSAMC21MOTOR MCU board */
	curhall1 = (uint8_t)((REG_PORT_IN1 & 0x00000800U) >> 9U);
	curhall2 = (uint8_t)((REG_PORT_IN1 & 0x00000010U) >> 3U);
	curhall3 = (uint8_t)((REG_PORT_IN0 & 0x10000000U) >> 28U);
#endif

	curpattern = (curhall1 | curhall2 | curhall3);

	if ((curpattern != 0U) && (curpattern != 7U)) {
		/* PWM should be applied only at high side switches */
		TCC0->PATT.reg = COMMUTATION_ARRAY[curpattern + (direction)];
		/* wait for Pattern update synchronization */
		while (TCC0->SYNCBUSY.bit.PATT == 1U) {
		}

		nextpattern = HALL_ARRAY[curpattern + (direction)];
	}
}

void motor_stop()
{
	/*  Stop motor */
	TCC0->CC[0].reg  = 0;
	TCC0->PATT.reg   = 0x0077;
	pi_integratorbuf = 0;
	actual_speed     = 0;
	speed_reference  = 0;
}

void adp_receive_data(void)
{
	uint8_t                          dirref;
	struct adp_ext_msg_response_data response;

	if (adp_ext_request_data(&response) == true) {
		switch (response.stream_id) {
		case STREAM_ID_MOTOR_START_STOP_IN:
			start_toggle ^= 1;
			if (start_toggle == 1) {
				state_run = 1;
				motor_start();
			} else {
				state_run = 0;
				motor_stop();
			}
			break;
		case STREAM_ID_MOTOR_REF_SPEED_RPM_IN:
			set_speed = (uint16_t)((response.data[1] << 8) + response.data[0]);
			break;
		case STREAM_ID_KP_IN:
			kp_ref     = (uint16_t)((response.data[1] << 8) + response.data[0]);
			speedpi.kp = kp_ref;
			break;
		case STREAM_ID_KI_IN:
			ki_ref     = (uint16_t)((response.data[1] << 8) + response.data[0]);
			speedpi.ki = ki_ref;
			break;
		case STREAM_ID_RAMPUP_TIME_IN:
			ramp_speedperms = (uint16_t)((response.data[1] << 8) + response.data[0]);
			break;
		case STREAM_ID_DIRECTION_IN:
			dirref = (uint8_t)(response.data[0]);
			/* direction change is allowed only when
			               motor is in stopped state */
			if (state_run == 0) {
				direction = dirref << 3U;
			}
			break;
		default:
			break;
		}
	}
}

void app_one_ms_isr(void)
{
	uint16_t diff;
	int32_t  error;

	timecounter++;
	picounter++;

	if ((timecounter & 0x03U) == 0U) {
		timecounter = 0;
		if (dashboardconfigured == 1U) {
			for (int i = 0; i < num_input_streams; i++) {
				adp_receive_data();
			}

			if (start_toggle != 0U) {
				uint8_t  recv_pkg = 0;
				uint16_t curpattern_stream;
				curpattern_stream = curpattern & 0xFF;

				adp_transceive_single_stream(STREAM_ID_MOTOR_REF_SPEED_RPM, &speed_reference, 2, &recv_pkg);
				adp_transceive_single_stream(STREAM_ID_MOTOR_ACTUAL_SPEED_RPM, &actual_speed, 2, &recv_pkg);
				adp_transceive_single_stream(STREAM_ID_POSITION, &curpattern_stream, 2, &recv_pkg);
			}
		}
	}

	/* check motor if started */
	if (state_run == 1U) {
		if (picounter == 1U) {
			picounter = 0;
			if (ramp_speedperms == 0U) {
				speed_reference = set_speed;
			} else {
				if (set_speed > (speed_reference + ramp_speedperms)) {
					speed_reference += ramp_speedperms;
				} else if (set_speed < (speed_reference - ramp_speedperms)) {
					speed_reference -= ramp_speedperms;
				} else {
					speed_reference = set_speed;
				}
			}

			if (actual_speed != 0U) {
				/*	Error Calculation   Error = Reference - Actual	*/
				error           = (int32_t)speed_reference - (int32_t)actual_speed;
				diff            = pi_lib_calculate(error, (uint16_t)speedpi.kp, (uint16_t)speedpi.ki);
				TCC0->CC[0].reg = diff;
			}
		}
	} else {
		if (picounter == 1U) {
			picounter = 0;
		}
	}
}
