/*
 * BareMetal.c
 *
 * Created: 4/22/2021 8:02:17 PM
 * Author : Selva
 */ 


#include "same70q21.h"
#define LED0_MASK				8
#define SYS_BOARD_OSCOUNT		(CKGR_MOR_MOSCXTST(0x8U))
#define SYS_BOARD_PLLAR			(CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(0x18U) | \
								CKGR_PLLAR_PLLACOUNT(0x3fU) | CKGR_PLLAR_DIVA(0x1U))
#define SYS_BOARD_MCKR			(PMC_MCKR_MDIV(1) | PMC_MCKR_CSS_PLLA_CLK)
//#define 
#define TC_CMR_WAVSEL(value)	(value << 13) //WAVSEL missed in Tc.h
#define TC_CMR_EEVT(value)		(value<<10)	  //EEVT missing in Tc.h
volatile int a,b;

uint32_t temp;

void TC0_Init(void)
{
	TC0->TcChannel[0].TC_CMR	|= (TC_CMR_TCCLKS(3) | TC_CMR_WAVE | TC_CMR_WAVSEL(2) | TC_CMR_LDRA_RISING | TC_CMR_LDRB_FALLING);
	TC0->TcChannel[0].TC_RA	|= (0x040);
	TC0->TcChannel[0].TC_RC	|= (0x08F0D);
	TC0->TcChannel[0].TC_IER	|= TC_IMR_CPCS;
	NVIC->ICER[(((uint32_t)TC0_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)TC0_IRQn) & 0x1FUL));
	NVIC->ICPR[(((uint32_t)TC0_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)TC0_IRQn) & 0x1FUL));
	NVIC->ISER[(((uint32_t)TC0_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)TC0_IRQn) & 0x1FUL));
}

void TC0_Handler()
{
	temp = TC0->TcChannel[0].TC_SR;
	a++;
	if( (temp &= TC_SR_CPCS) && (a == 16))
	{
		if(PIOC->PIO_ODSR !=1<<LED0_MASK)
		PIOC->PIO_SODR								|= 1<<LED0_MASK;		
		else
		PIOC->PIO_CODR								|= 1<<LED0_MASK;
		a= 0;
	}
}

void PMC_Init(void)
{
	PMC->PMC_PCER0					|= (1<<ID_PIOC)|(1<<ID_TC0_CHANNEL0);
}

void Clock_Init(void)
{
	PMC->CKGR_PLLAR &= ~CKGR_PLLAR_MULA_Msk;	
	PMC->CKGR_PLLAR |= SYS_BOARD_PLLAR;
	while ( !(PMC->PMC_SR & PMC_SR_LOCKA) )
	{
	}
	
	/* Switch to PLLA */
	PMC->PMC_MCKR &= ~PMC_MCKR_PRES_Msk;
	while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) )
	{
	}
	
	PMC->PMC_MCKR |= PMC_MCKR_MDIV_PCK_DIV2;
	while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) )
	{
	}
	temp = PMC->PMC_MCKR;
	temp &= ~PMC_MCKR_CSS_MAIN_CLK_Val;
	temp |=  PMC_MCKR_CSS(2);
	PMC->PMC_MCKR = temp;
	while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) )
	{
	}
}

void Flash_Init()
{
	uint32_t tmp;
	tmp = EFC->EEFC_FMR;
	tmp &= ~EEFC_FMR_FWS_Msk;
	tmp |= EEFC_FMR_FWS(6);
	EFC->EEFC_FMR = tmp;
}

void SystemInit()
{
	Flash_Init();
	Clock_Init();
	PMC_Init();
}

int main(void)
{
    /* Initialize the SAM system */
	SystemInit();
	WDT->WDT_MR |= WDT_MR_WDDIS;
	TC0_Init();
	PIOC->PIO_CODR					|= 1<<LED0_MASK;
	PIOC->PIO_OER					|= 1<<LED0_MASK;
	PIOC->PIO_PER					|= 1<<LED0_MASK;
	TC0->TcChannel[0].TC_CCR		|= TC_CCR_CLKEN | TC_CCR_SWTRG;
    /* Replace with your application code */
    while (1) 
    {
		b++;
    }
}
