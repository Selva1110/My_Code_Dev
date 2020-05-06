/**
 * @file analog_io.h
 * @date 2015-06-20
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
 *
 * @cond
 ***********************************************************************************************************************
 * ANALOG_IO v4.0.4 - The ANALOG_IO APP is used to select port pin as a Analog input/output.
 *
 * Copyright (c) 2015, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-02-16
 *     - Initial version
 *
 * 2015-06-20
 *     - Version check added for XMCLib dependency.
 *
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#ifndef ANALOG_IO_H
#define ANALOG_IO_H

#include <xmc_gpio.h>
#include <DAVE_common.h>
#include "analog_io_conf.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#if (!((XMC_LIB_MAJOR_VERSION == 2U) && \
       (XMC_LIB_MINOR_VERSION >= 0U) && \
       (XMC_LIB_PATCH_VERSION >= 0U)))
#error "ANALOG_IO requires XMC Peripheral Library v2.0.0 or higher"
#endif
/***********************************************************************************************************************
 * LOCAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/

 /**********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup ANALOG_IO_apidoc
 * @{
 */

/**
 * @brief Get ANALOG_IO APP version
 * @return DAVE_APP_VERSION_t APP version information (major, minor and patch number)
 *
 * \par<b>Description: </b><br>
 * The function can be used to check application software compatibility with a
 * specific version of the APP.
 *
 * Example Usage:
 *
 * @code
 * #include <DAVE.h>
 *
 * int main(void)
 * {
 *   DAVE_STATUS_t init_status;
 *   DAVE_APP_VERSION_t version;
 *
 *   // Initialize ANALOG_IO APP:
 *   // ANALOG_IO_Init() is called from within DAVE_Init().
 *   init_status = DAVE_Init();
 *
 *   if(init_status == DAVE_STATUS_SUCCESS)
 *   {
 *     version = ANALOG_IO_GetAppVersion();
 *     if (version.major != 4U) {
 *     // Probably, not the right version.
 *     }
 *   }
 *
 *     // More code here
 *     while(1) {
 *
 *     }
 *     return (1);
 *  }
 * @endcode<BR>
*/


 DAVE_APP_VERSION_t ANALOG_IO_GetAppVersion(void);

 /**
  *@}
  */

#ifdef __cplusplus
}
#endif

/* Include APP extern file */
#include "analog_io_extern.h"


#endif /* ANALOG_IO_H */