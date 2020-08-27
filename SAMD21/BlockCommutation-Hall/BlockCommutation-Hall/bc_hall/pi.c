#include "pi.h"

uint32_t pi_integratorbuf;

uint16_t pi_lib_calculate(int32_t error, uint16_t kp_gain, uint16_t ki_gain)
{

	int32_t y_kplus;
	int32_t yn_kplus;
	int32_t y_kp;
	int32_t y_ki;

	/* Calculation Proportional term   y_kp = Prop Gain * Error	*/
	y_kp = ((error * (int32_t)kp_gain * 64));

	/* Calculation Integral term   y_ki = Integral Gain * Error	*/
	y_ki = ((error * (int32_t)ki_gain));

	/* Integral term summation	*/
	y_kplus = ((int32_t)pi_integratorbuf + y_ki);

	/*	Load buffer with the accumulated error	*/
	pi_integratorbuf = y_kplus;

	y_kplus = y_kplus / 32768;

	/* Integral term Anti Windup Saturation Limit Check	*/
	if (y_kplus >= 2350) {
		y_kplus          = 2350;
		pi_integratorbuf = (uint32_t)y_kplus * 32768;
	} else if (y_kplus < 10) {
		y_kplus          = 10;
		pi_integratorbuf = (uint32_t)y_kplus * 32768;
	} else {
		/*Do nothing */
	}

	/*	Summation of Prop term and Integral term	*/
	yn_kplus = (y_kp + pi_integratorbuf) / 32768;

	/*	Saturation Limit Check on final output	*/
	if (yn_kplus >= 2350) {
		yn_kplus = 2350;
	} else if (yn_kplus < 10) {
		yn_kplus = 10;
	} else {
		/*Do nothing */
	}
	/*	PI Controller output assignment	*/
	return ((uint16_t)yn_kplus);
}
