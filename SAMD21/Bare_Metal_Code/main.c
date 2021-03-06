/*
 * GccApplication1.c
 *
 * Created: 16-11-2020 21:29:16
 * Author : Selva
 */ 


#include "sam.h"
#include "samd21g17d.h"
#define CONF_TC4_TIMER_TICK 1000
#define CONF_GCLK_TC4_FREQUENCY 48000000
#define CONF_TC4_PRESCALE (1 << TC_CTRLA_PRESCALER_DIV2_Val)
#define CONF_TC4_CC0    (uint32_t)(((float)CONF_TC4_TIMER_TICK / 1000000.f) / (1.f / (CONF_GCLK_TC4_FREQUENCY / CONF_TC4_PRESCALE)))
#define CONF_TCC0_WAVE_PER_VAL 0x3e8
#define CONF_GCLK_TCC0_FREQUENCY 8000000
#define CONF_TCC0_PER_REG	((uint32_t)(((double)CONF_TCC0_WAVE_PER_VAL * CONF_GCLK_TCC0_FREQUENCY) / 1000000 / (1 << TCC_CTRLA_PRESCALER_DIV1_Val) - 1))
#define CONF_TCC0_WAVE_DUTY_VAL 0x1f4
#define CONF_TCC0_CCX_REG ((uint32_t)(((double)(double)CONF_TCC0_PER_REG * CONF_TCC0_WAVE_DUTY_VAL) / 1000))


void TCC0_Init (void)
{
	
	PORT->Group[0].PINCFG[8].bit.PMUXEN &= ~PORT_PINCFG_PMUXEN;
	PORT->Group[0].PMUX[8/2].bit.PMUXE |= 	PORT_PMUX_PMUXO_E;
	
	REG_PM_APBCMASK |= PM_APBCMASK_TCC0;
	REG_GCLK_CLKCTRL |= GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC0_TCC1;
	while(TCC0->SYNCBUSY.bit.STATUS);
	
	REG_TCC0_CTRLA |= TC_CTRLA_SWRST;
	while(TCC0->SYNCBUSY.bit.SWRST);
	
	REG_TCC0_CTRLA |= TCC_CTRLA_PRESCALER_DIV1 | TCC_CTRLA_PRESCSYNC_GCLK;
	REG_TCC0_CTRLBSET |= TCC_CTRLBSET_LUPD;
	
	REG_TCC0_WAVE |= TCC_WAVE_WAVEGEN_NPWM;
	REG_TCC0_PER |= CONF_TCC0_PER_REG;
	
	
	REG_TCC0_CC0 |= CONF_TCC0_CCX_REG;
	REG_TCC0_CTRLBCLR |= TCC_CTRLBSET_LUPD;
	
	REG_TCC0_CTRLA |= TC_CTRLA_ENABLE;
	
		
	
}

void TC4_Init (void)
{
		
	REG_PM_APBCMASK |= PM_APBCMASK_TC4 ;
	REG_GCLK_CLKCTRL |= GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TC4_TC5;
	while(TC4->COUNT16.STATUS.bit.SYNCBUSY);
	
	
	REG_TC4_CTRLA |= TC_CTRLA_SWRST;
	while(TC4->COUNT16.STATUS.bit.SYNCBUSY);
	
	
	REG_TC4_CTRLA |= TC_CTRLA_MODE_COUNT16 | TC_CTRLA_WAVEGEN_MPWM | TC_CTRLA_PRESCSYNC_GCLK | TC_CTRLA_PRESCALER_DIV1024 ;
	REG_TC4_COUNT16_CC0 |= 1000;
	
	//REG_TC4_COUNT32_COUNT = 1000;
	REG_TC4_INTENSET |= TC_INTENSET_OVF;
	
	
	NVIC_EnableIRQ(TC4_IRQn);
	REG_TC4_CTRLA |= TC_CTRLA_ENABLE;
	
	
}

void TC4_Handler()
{
	REG_TC4_CTRLBSET |= TC_CTRLBSET_CMD_RETRIGGER;
	REG_TC4_INTFLAG |= TC_INTFLAG_OVF;
	REG_PORT_OUTTGL1 |= PORT_PB10;
}

int main(void)
{
	/* Replace with your application code */
	int a;
	SystemInit();
	TC4_Init();
	
	REG_PORT_DIR1 |=  PORT_PB10;
	REG_PORT_OUTTGL1 |= PORT_PB10;
    while (1) 
    {
		a++;
    }
}
