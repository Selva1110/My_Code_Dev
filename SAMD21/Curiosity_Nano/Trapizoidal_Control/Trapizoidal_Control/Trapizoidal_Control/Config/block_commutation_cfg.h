/* Auto-generated config file block_commutation_cfg.h */
#ifndef BLOCK_COMMUTATION_CFG_H
#define BLOCK_COMMUTATION_CFG_H

// <<< Use Configuration Wizard in Context Menu >>>

#define M42BL02402 1
#define CUSTOM 2

// <y> Motor Type
// <M42BL02402"> LDO M42BL02402
// <CUSTOM"> CUSTOM (USER DEFINED)
// <id> motor_type
#ifndef MOTOR_TYPE
#define MOTOR_TYPE M42BL02402
#endif

// <o> Motor Pole pairs <1-16>
// <id> motor_pole_pairs
#ifndef MOTOR_POLE_PAIRS
#define MOTOR_POLE_PAIRS 4
#endif

// <o> Motor Maximum Speed in RPM <0-40000>
// <id> motor_max_speed
#ifndef MOTOR_MAXIMUM_SPEED
#define MOTOR_MAXIMUM_SPEED 4500
#endif

// <o> Motor Minimum Speed in RPM <0-40000>
// <id> motor_min_speed
#ifndef MOTOR_MINIMUM_SPEED
#define MOTOR_MINIMUM_SPEED 0
#endif

// <o> Motor Ramp up Speed in RPM/ms <0-100>
// <id> motor_rampup_speed
#ifndef MOTOR_RAMPUP_SPEED_PER_MS
#define MOTOR_RAMPUP_SPEED_PER_MS 1
#endif

/* KP Default value */
#define SPEED_KP_DEFAULT (40U)
/* KI Default value */
#define SPEED_KI_DEFAULT (20U)
/* Default reference speed in rpm */
#define START_SPEED_DEFAULT (2000U)
/* Default duty cycle */
#define SPEED_DEFAULT_DUTY (240U)

/* Average Speed calculation factor */
#define MOTOR_SPEED_CALCFACTOR (MOTOR_POLE_PAIRS * 6U)

// <<< end of configuration section >>>

#endif // BLOCK_COMMUTATION_CFG_H
