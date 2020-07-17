/* Auto-generated config file peripheral_clk_config.h */
#ifndef PERIPHERAL_CLK_CONFIG_H
#define PERIPHERAL_CLK_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> AFEC Clock Settings
// <y> AFEC Clock source
// <CONF_SRC_MCK"> Master Clock (MCK)
// <i> This defines the clock source for the AFEC
// <id> afec_clock_source
#ifndef CONF_AFEC0_SRC
#define CONF_AFEC0_SRC CONF_SRC_MCK
#endif
// </h>

/**
 * \def AFEC FREQUENCY
 * \brief AFEC's Clock frequency
 */
#ifndef CONF_AFEC0_FREQUENCY
#define CONF_AFEC0_FREQUENCY 150000000
#endif

// <h> AFEC Clock Settings
// <y> AFEC Clock source
// <CONF_SRC_MCK"> Master Clock (MCK)
// <i> This defines the clock source for the AFEC
// <id> afec_clock_source
#ifndef CONF_AFEC1_SRC
#define CONF_AFEC1_SRC CONF_SRC_MCK
#endif
// </h>

/**
 * \def AFEC FREQUENCY
 * \brief AFEC's Clock frequency
 */
#ifndef CONF_AFEC1_FREQUENCY
#define CONF_AFEC1_FREQUENCY 150000000
#endif

/**
 * \def CONF_HCLK_FREQUENCY
 * \brief HCLK's Clock frequency
 */
#ifndef CONF_HCLK_FREQUENCY
#define CONF_HCLK_FREQUENCY 300000000
#endif

/**
 * \def CONF_FCLK_FREQUENCY
 * \brief FCLK's Clock frequency
 */
#ifndef CONF_FCLK_FREQUENCY
#define CONF_FCLK_FREQUENCY 300000000
#endif

/**
 * \def CONF_CPU_FREQUENCY
 * \brief CPU's Clock frequency
 */
#ifndef CONF_CPU_FREQUENCY
#define CONF_CPU_FREQUENCY 300000000
#endif

/**
 * \def CONF_SLCK_FREQUENCY
 * \brief Slow Clock frequency
 */
#define CONF_SLCK_FREQUENCY 32000

/**
 * \def CONF_MCK_FREQUENCY
 * \brief Master Clock frequency
 */
#define CONF_MCK_FREQUENCY 150000000

/**
 * \def CONF_PCK6_FREQUENCY
 * \brief Programmable Clock Controller 6 frequency
 */
#define CONF_PCK6_FREQUENCY 12000000

// <h> PWM Clock Settings
// <y> PWM Clock source
// <CONF_SRC_MCK"> Master Clock (MCK)
// <i> This defines the clock source for the PWM
// <id> pwm_clock_source
#ifndef CONF_PWM0_SRC
#define CONF_PWM0_SRC CONF_SRC_MCK
#endif
// </h>

/**
 * \def PWM FREQUENCY
 * \brief PWM's Clock frequency
 */
#ifndef CONF_PWM0_FREQUENCY
#define CONF_PWM0_FREQUENCY 150000000
#endif

// <y> TC Clock Source
// <CONF_SRC_MCK"> Master Clock (MCK)
// <id> tc_clock_source
// <i> Select the clock source for TC.
#ifndef CONF_TC0_SRC
#define CONF_TC0_SRC CONF_SRC_MCK
#endif

/**
 * \def CONF_TC0_FREQUENCY
 * \brief TC0's Clock frequency
 */
#ifndef CONF_TC0_FREQUENCY
#define CONF_TC0_FREQUENCY 150000000
#endif

// <y> TC Clock Source
// <CONF_SRC_MCK"> Master Clock (MCK)
// <id> tc_clock_source
// <i> Select the clock source for TC.
#ifndef CONF_TC1_SRC
#define CONF_TC1_SRC CONF_SRC_MCK
#endif

/**
 * \def CONF_TC1_FREQUENCY
 * \brief TC1's Clock frequency
 */
#ifndef CONF_TC1_FREQUENCY
#define CONF_TC1_FREQUENCY 150000000
#endif

// <h> UART Clock Settings
// <o> UART Clock source
// <0=> Master Clock (MCK)
// <1=> Programmable Clock Controller 4 (PMC_PCK4)
// <i> This defines the clock source for the UART
// <id> uart_clock_source
#ifndef CONF_UART4_CK_SRC
#define CONF_UART4_CK_SRC 0
#endif
// </h>

/**
 * \def UART FREQUENCY
 * \brief UART's Clock frequency
 */
#ifndef CONF_UART4_FREQUENCY
#define CONF_UART4_FREQUENCY 150000000
#endif

// <<< end of configuration section >>>

#endif // PERIPHERAL_CLK_CONFIG_H
