#ifndef PI_H_
#define PI_H_

#include "compiler.h"
#include "utils.h"

typedef struct picontrol_type_t {
	/* kp Gain */
	int32_t kp;
	/* ki Gain */
	int32_t ki;
	/* Old error value */
	int32_t error;
	/*old output value */
	int32_t outputvalue;
	/* Max Limit of output */
	int32_t maxlimit;
	/* Min Limit of output value */
	int32_t minlimit;

} picontrol_type;

extern uint32_t pi_integratorbuf;
uint16_t        pi_lib_calculate(int32_t error, uint16_t kp_gain, uint16_t ki_gain);

#endif /* PI_H_ */
