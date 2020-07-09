#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <compiler.h>
#include <utils.h>

// TODO: Verify and Set the Hall sensor pins
#ifndef HALL_SENSOR_PINA
#define HALL_SENSOR_PINA GPIO(GPIO_PORTA, 21)
#endif
#ifndef HALL_SENSOR_PINB
#define HALL_SENSOR_PINB GPIO(GPIO_PORTA, 20)
#endif
#ifndef HALL_SENSOR_PINC
#define HALL_SENSOR_PINC GPIO(GPIO_PORTA, 07)
#endif


void     init_global_variables(void);
void     update_commutation(void);
void     motor_start(void);
void     motor_stop(void);
void     perform_adp_update(void);
void     update_duty_cycle(void);
void     register_hall_events(void);
void     register_one_ms_timer_events(void);
void     motor_pwm_init(void);
void     speed_measurement_init(void);
uint16_t _timer_get_count(const void *const hw);
void     _timer_set_count(const void *const hw, uint16_t data);
void     _timer_stop_a(const void *const hw);
void     _timer_start_a(const void *const hw);
void     adp_receive_data(void);
void     app_one_ms_isr(void);

#endif
