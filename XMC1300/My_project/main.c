/*
 * main.c
 *
 *  Created on: 2020 Apr 07 14:23:35
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
  while(1U)
  {
	  XMC_GPIO_Init(P0_0,DIGITAL_IO_0.gpio_config);
	  int i=100000;
	  while(i--);
	  XMC_GPIO_SetOutputLevel(P0_0,XMC_GPIO_OUTPUT_LEVEL_LOW);
	  i=100000;
	  while(i--);
	  //DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
	 /*
	  DIGITAL_IO_0.gpio_config->output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
	  DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
	  */
  }
}
