/*
 * main.c
 *
 *  Created on: 2020 Apr 14 20:13:49
 *  Author: sambasivam
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
XMC_GPIO_CONFIG_t DIGITAL_IO_config  =
{
  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5,
  .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,

};


int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if(status == DAVE_STATUS_FAILURE)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {
    }
  }

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  XMC_GPIO_Init(P0_0,&DIGITAL_IO_config);
  XMC_GPIO_Init(P0_1,&DIGITAL_IO_config);
  XMC_GPIO_Init(P0_2,&DIGITAL_IO_config);
  XMC_GPIO_Init(P0_6,&DIGITAL_IO_config);
  XMC_GPIO_Init(P0_7,&DIGITAL_IO_config);
  XMC_GPIO_Init(P0_8,&DIGITAL_IO_config);
  XMC_GPIO_Init(P0_9,&DIGITAL_IO_config);
  XMC_GPIO_Init(P2_10,&DIGITAL_IO_config);
  XMC_GPIO_Init(P2_11,&DIGITAL_IO_config);
  PWM_CCU8_Init(&PWM_CCU8_0);
  PWM_CCU8_SetFreqAndDutyCycleAsymmetric (&PWM_CCU8_0, 10000,500,4000);
  //PWM_CCU8_SetFreqAndDutyCycleSymmetric(&PWM_CCU8_0, 10000,1000,5000);
  PWM_CCU8_SetFreqAndDutyCycleSymmetric(&PWM_CCU8_1, 10000,2000,5000);
  PWM_CCU8_SetFreqAndDutyCycleSymmetric(&PWM_CCU8_2, 10000,3000,5000);
  PWM_CCU8_SetFreqAndDutyCycleSymmetric(&PWM_CCU8_3, 10000,5000,5000);
  PWM_CCU8_Start(&PWM_CCU8_0);
  PWM_CCU8_Start(&PWM_CCU8_1);
  PWM_CCU8_Start(&PWM_CCU8_2);
  PWM_CCU8_Start(&PWM_CCU8_3);
  while(1U)
  {

  }
}
