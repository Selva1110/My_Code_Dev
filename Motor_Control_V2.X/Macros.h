/* 
 * File:   Macros.h
 * Author: I18387
 *
 * Created on October 4, 2018, 10:00 PM
 */

#ifndef MACROS_H
#define	MACROS_H
#define BC1_P3                  PORTEbits.RE5
#define P1_P40                  PORTFbits.RF12
#define P2_P41                  PORTBbits.RB12
#define P3_P42                  PORTBbits.RB13
#define P4_P43                  PORTBbits.RB14
#define P5_P44                  PORTBbits.RB15
#define SD_P24                  PORTBbits.RB11
#define H1_P61                  PORTBbits.RB8   // Set the RA0 value as 1
#define H2_P60                  PORTBbits.RB9   // Set the RA0 value as 1
#define H3_P59                  PORTBbits.RB10  // Set the RA0 value as 1
#define PWMUH_DC                PDC4   //
#define PWMUL_DC                SDC4   //
#define PWMVH_DC                PDC5   //
#define PWMVL_DC                SDC5   //
#define PWMWH_DC                PDC6   //
#define PWMWL_DC                SDC6   //
#define PWM_CLK_PRE_VAL         16
#define PWM_CLK_PRE             0x0002
#define MIN_DUTY                0x0000                          // Instruction cycle frequency (Hz)
#define FCY_MHZ                 (uint16_t)120                   // Instruction cycle frequency (MHz)
#define FCY_HZ                  (uint16_t)(FCY_MHZ*1000000)     /* Specify PWM Frequency in Hertz */
#define PWM_HZ                  (uint16_t)20000     
#define PWM_FCY                 1500
#endif	/* MACROS_H */

