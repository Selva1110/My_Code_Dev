/**
 * \file
 *
 * \brief SAM Timer/Counter for Control Applications
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 */

#ifndef _HPL_TCC_V101_BASE_H_INCLUDED
#define _HPL_TCC_V101_BASE_H_INCLUDED

#include <hpl_timer.h>
#include <hpl_pwm.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup tcc_group TCC Low Level Driver Helpers
 *
 * \section tcc_helpers_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

/**
 * \name HPL functions
 */
//@{

/**
 * \brief TCC configuration type
 */
struct tcc_cfg {
	void *                 hw; /*!< instance of TCC */
	IRQn_Type              irq;
	hri_tcc_ctrla_reg_t    ctrl_a;
	hri_tcc_ctrlbset_reg_t ctrl_b;
	hri_tcc_dbgctrl_reg_t  dbg_ctrl;
	hri_tcc_evctrl_reg_t   event_ctrl;
	hri_tcc_cc_reg_t       cc0;
	hri_tcc_cc_reg_t       cc1;
	hri_tcc_cc_reg_t       cc2;
	hri_tcc_cc_reg_t       cc3;
	hri_tcc_per_reg_t      per;
};
/**
 * \brief pwm configuration type
 */
struct tcc_pwm_cfg {
	void *    hw; /*!< instance of TCC */
	IRQn_Type irq;
	uint8_t   sel_ch;
	uint32_t  period;
	uint32_t  duty_cycle;
	uint32_t  wave;
};


/**
 * \brief Retrieve timer helper functions
 *
 * \return A pointer to set of timer helper functions
 */
struct _timer_hpl_interface *_tcc_get_timer(void);

/**
 * \brief Retrieve pwm helper functions
 *
 * \return A pointer to set of pwm helper functions
 */
struct _pwm_hpl_interface *_tcc_get_pwm(void);

//@}
/**@}*/

#ifdef __cplusplus
}
#endif
#endif /* _HPL_TCC_V101_BASE_H_INCLUDED */
