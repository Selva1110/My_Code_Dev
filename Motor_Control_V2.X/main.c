//#define __33EP512MU810
#ifdef __33EP512MU810
#include "p33EP512MU810.h" 
#include "Macros.h"
// Select Internal FRC at POR
_FOSCSEL(FNOSC_FRC & IESO_OFF);
// Enable Clock Switching and Configure POSC in XT mode
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE);
#endif

double temp = 0.0000;
//int test_variable =10;
//int test_variable2 =10;


void Delay_us(unsigned int delay)
{
    int i;
    for (i = 0; i < delay; i++)
{
    __asm__ volatile ("repeat #39");
    __asm__ volatile ("nop");
}
}

void initAdc1(void)
{
#ifdef __33EP512MU810
    /* Set port configuration */
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    ANSELBbits.ANSB5 = 1;// Ensure AN5/RB5 is analog/* Initialize and enable ADC module */
    AD1CON1 = 0x0004;
    AD1CON2 = 0x0000;
    AD1CON3 = 0x000F;
    AD1CON4 = 0x0000;
    AD1CHS0 = 0x0005;
    AD1CHS123 = 0x0000;
    AD1CSSH = 0x0000;
    AD1CSSL = 0x0000;
    AD1CON1bits.ADON = 1;
    //Delay_us(20);
#endif
    
    
}
uint16_t Read_ADC()
{
#ifdef __33EP512MU810
    //Delay_us(100);// Sample for 100 us
    AD1CON1bits.SAMP = 0;// Start the conversion
    while (!AD1CON1bits.DONE);// Wait for the conversion to complete
    AD1CON1bits.DONE = 0;// Clear conversion done status bit
    return ADC1BUF0;
    // Read the ADC conversion result
#endif
    
    
    
}


void PWM123_Init()
{
#ifdef __33EP512MU810   
    //PWM
	/* Set PWM Period on Primary Time Base */
	PTCONbits.PTEN = 0;
	PTPER = PWM_FCY;
	/* Set Phase Shift */
    PHASE3 = 300;
    SPHASE3 = 300;
	PHASE4 = 0;
	SPHASE4 =PWM_FCY/2;
	PHASE5 = (PWM_FCY/3);
	SPHASE5 =(PWM_FCY/3)+(PWM_FCY/2);
	PHASE6 = 2*PWM_FCY/3;
	SPHASE6 =(2*PWM_FCY/3)+(PWM_FCY/2);
	/* Set Duty Cycles */
    PDC3 = 300;
    SDC3 = 150;
	PDC4 = PWM_FCY/2;
	SDC4 = PWM_FCY/2;
	PDC5 = PWM_FCY/2;
	SDC5 = PWM_FCY/2;
	PDC6 = PWM_FCY/2;
	SDC6 = PWM_FCY/2;
	/* Set Dead Time Values */
	DTR3 = DTR4 = DTR5 = DTR6 = 0;
	ALTDTR3 = ALTDTR4 = ALTDTR5 = ALTDTR6 = 0;
	/* Set PWM Mode to Independent */
	IOCON3 = IOCON4 = IOCON5 = IOCON6 = 0xCC00;
	//IOCON1bits.OVRDAT1 = IOCON1bits.OVRDAT0 = 0;
	//IOCON2bits.OVRDAT1 = IOCON2bits.OVRDAT0 = 0;
	//IOCON3bits.OVRDAT1 = IOCON3bits.OVRDAT0 = 0;
	/* Set Primary Time Base, Edge-Aligned Mode and Independent Duty Cycles */
	PWMCON3 = PWMCON4 = PWMCON5 = PWMCON6 = 0x0000;
	/* Configure Faults */
	FCLCON3 = FCLCON4 = FCLCON5 = FCLCON6 = 0x0003;
	SEVTCMP = 1; /* Special Event Trigger value set at 25% of the period value (4999)*/
	PTCONbits.SEVTPS = 1; /* Special Event Trigger output postscaler set to 1:2 selection */
	PTCONbits.SEIEN = 1; /* Special event interrupt is enabled */
	

	
	/* 1:1 Prescaler */
	PTCON2 = PWM_CLK_PRE;
	//    TRIG1 = 1; /* Point at which the ADC module is to be triggered by primary PWM */
	//  TRGCON1bits.TRGDIV = 0; /* Trigger output divider set to trigger ADC on every trigger match event */
	//TRGCON1bits.TRGSTRT = 4; /* First ADC trigger event occurs after four trigger match events */
	//PWMCON1bits.TRGIEN = 1; /* Trigger event generates an interrupt request */
	/* Enable PWM Module */
	PTCONbits.PTEN = 1;
#endif


}

void TMR1_Init()
{
#ifdef __33EP512MU810 
    T3CONbits.TON = 0; // Disable Timer
    T3CONbits.TCS = 0; // Select internal instruction cycle clock
    T3CONbits.TGATE = 0; // Disable Gated Timer mode
    T3CONbits.TCKPS = 0b11; // Select 1:256 Prescaler
    TMR3 = 0x00; // Clear timer register
    //PR1 = 9; // Load the period value
    IPC2bits.T3IP = 0x01; // Set Timer 1 Interrupt Priority Level
    IFS0bits.T3IF = 0; // Clear Timer 1 Interrupt Flag
    IEC0bits.T3IE = 1; // Enable Timer1 interrupt
#endif
}


#ifdef __33EP512MU810 
/* Example code for Timer1 ISR*/
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
    P1_P40 =1;
	P2_P41 =1;
	P3_P42 =1;
	P4_P43 =1;
	P5_P44 =1;
	LATAbits.LATA0 =1;
	T3CONbits.TON = 0; // Stop Timer
	TMR3 = 0x00; // Clear timer register
	/* Interrupt Service Routine code goes here */
	IFS0bits.T3IF = 0; //Clear Timer1 interrupt flag
    
#ifdef WITHOUT_MOTOR
	if(PDC4 != MIN_DUTY)
	{
		PDC4 = MIN_DUTY;
		SDC4 = MIN_DUTY;
		PDC5 = MIN_DUTY;
		SDC5 = MIN_DUTY;
		PDC6 = MIN_DUTY;
		SDC6 = MIN_DUTY;
		TMR3 = 0x0000; // Clear timer register
	}
	else
	{
		PWMUH_DC =PWM_FCY/2;
		PWMUL_DC =PWM_FCY/2;
		PWMVH_DC =PWM_FCY/2;
		PWMVL_DC =PWM_FCY/2;
		PWMWH_DC =PWM_FCY/2;
		PWMWL_DC =PWM_FCY/2;
		TMR3     = 0x0000; // Clear timer register
	}
	PR3 = (uint16_t)(0x44C5*(double)(0x3FF - Read_ADC())/0x3FF);
	if (PR3>0x44C5)
	{
		PR3 =0x44C5;
	}else if(PR3<0x1B8)
	{
		PR3 =0x1B8;
	}
#endif
#ifdef WITH_MOTOR
    if (H1_P61 == 1)
		{if (H2_P60 == 0)
		{if (H3_P59 == 1)
		{
			PWMUH_DC =PWM_FCY/2;
			PWMUL_DC =MIN_DUTY;
			PWMVH_DC =MIN_DUTY;
			PWMVL_DC =PWM_FCY/2;
			PWMWH_DC =MIN_DUTY;
			PWMWL_DC =MIN_DUTY;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//2
		if (H1_P61 == 0)
		{if (H2_P60 == 0)
		{if (H3_P59 == 1)
		{
			PWMUH_DC =MIN_DUTY;
			PWMUL_DC =MIN_DUTY;
			PWMVH_DC =MIN_DUTY;
			PWMVL_DC =PWM_FCY/2;
			PWMWH_DC =PWM_FCY/2;
			PWMWL_DC =MIN_DUTY;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//3
		if (H1_P61 == 0)
		{if (H2_P60 == 1)
		{if (H3_P59 == 1)
		{
			PWMUH_DC =MIN_DUTY;
			PWMUL_DC =PWM_FCY/2;
			PWMVH_DC =MIN_DUTY;
			PWMVL_DC =MIN_DUTY;
			PWMWH_DC =PWM_FCY/2;
			PWMWL_DC =MIN_DUTY;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//4
		if (H1_P61 == 0)
		{if (H2_P60 == 1)
		{if (H3_P59 == 0)
		{
			PWMUH_DC =MIN_DUTY;
			PWMUL_DC =PWM_FCY/2;
			PWMVH_DC =PWM_FCY/2;
			PWMVL_DC =MIN_DUTY;
			PWMWH_DC =MIN_DUTY;
			PWMWL_DC =MIN_DUTY;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//5
		if (H1_P61 == 1)
		{if (H2_P60 == 1)
		{if (H3_P59 == 0)
		{
			PWMUH_DC =MIN_DUTY;
			PWMUL_DC =MIN_DUTY;
			PWMVH_DC =PWM_FCY/2;
			PWMVL_DC =MIN_DUTY;
			PWMWH_DC =MIN_DUTY;
			PWMWL_DC =PWM_FCY/2;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//6
		if (H1_P61 == 1)
		{if (H2_P60 == 0)
		{if (H3_P59 == 0)
		{
			PWMUH_DC =PWM_FCY/2;
			PWMUL_DC =MIN_DUTY;
			PWMVH_DC =MIN_DUTY;
			PWMVL_DC =MIN_DUTY;
			PWMWH_DC =MIN_DUTY;
			PWMWL_DC =PWM_FCY/2;
			LATAbits.LATA0 =0; // Set the RA0 value as 1
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//default
		if (H1_P61 == 0)
		{if (H2_P60 == 0)
		{if (H3_P59 == 0)
		{
			PWMUH_DC =MIN_DUTY;
			PWMUL_DC =MIN_DUTY;
			PWMVH_DC =MIN_DUTY;
			PWMVL_DC =MIN_DUTY;
			PWMWH_DC =MIN_DUTY;
			PWMWL_DC =MIN_DUTY;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
#endif
	P1_P40 =0;
	P2_P41 =0;
	P3_P42 =0;
	P4_P43 =0;
	P5_P44 =0;
	T3CONbits.TON = 1;
	LATAbits.LATA0 =0;
}
#endif

void Osc_Init()
{
#ifdef __33EP512MU810 
    // Configure PLL prescaler, PLL postscaler, PLL divisor
	PLLFBD=97; // M=95
	CLKDIVbits.PLLPOST=0; // N2=2
	CLKDIVbits.PLLPRE=1; // N1=3
	// Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)
	__builtin_write_OSCCONH(0x01);
	__builtin_write_OSCCONL(OSCCON | 0x01);
	// Wait for Clock switch to occur
	while (OSCCONbits.COSC!= 0b001);
	// Wait for PLL to lock
	while (OSCCONbits.LOCK!= 1);
#endif

}


void Hall_Pins_Init()
{
#ifdef __33EP512MU810 
    TRISBbits.TRISB8 = 1;
    TRISBbits.TRISB9 = 1;
    TRISBbits.TRISB10= 1;
    TRISBbits.TRISB11= 0b0;
    TRISFbits.TRISF12= 0b0;
    TRISBbits.TRISB12= 0b0;
    TRISBbits.TRISB13= 0b0;
    TRISBbits.TRISB14= 0b0;
    TRISBbits.TRISB15= 0b0;
    SD_P24 = 0;
#endif
}

int main()
{
uint16_t i=0;

	Osc_Init();
	initAdc1();
	PWM123_Init();
	TMR1_Init();
	Hall_Pins_Init();
	
	
	//PIN Toggle
	TRISAbits.TRISA0= 0b0; //Initialise the PIN RA0 connected to LED as Output
	LATAbits.LATA0 =0; // Set the RA0 value as 1
#ifdef __33EP512MU810 
	T3CONbits.TON = 0;

 //1
    PWMUH_DC =PWM_FCY/2;
    PWMUL_DC =PWM_FCY/2;
    PWMVH_DC =PWM_FCY/2;
    PWMVL_DC =PWM_FCY/2;
    PWMWH_DC =PWM_FCY/2;
    PWMWL_DC =PWM_FCY/2;
	while(1)
	{
		__asm__ volatile ("nop");
	
	
	
		
#if 0
		if (H1_P61 == 1)
		{if (H2_P60 == 0)
		{if (H3_P59 == 1)
		{
			PWMUH_DC =PWM_FCY/2;
			PWMUL_DC =MIN_DUTY;
			PWMVH_DC =MIN_DUTY;
			PWMVL_DC =PWM_FCY/2;
			PWMWH_DC =MIN_DUTY;
			PWMWL_DC =MIN_DUTY;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//2
		if (H1_P61 == 0)
		{if (H2_P60 == 0)
		{if (H3_P59 == 1)
		{
			PWMUH_DC =MIN_DUTY;
			PWMUL_DC =MIN_DUTY;
			PWMVH_DC =MIN_DUTY;
			PWMVL_DC =PWM_FCY/2;
			PWMWH_DC =PWM_FCY/2;
			PWMWL_DC =MIN_DUTY;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//3
		if (H1_P61 == 0)
		{if (H2_P60 == 1)
		{if (H3_P59 == 1)
		{
			PWMUH_DC =MIN_DUTY;
			PWMUL_DC =PWM_FCY/2;
			PWMVH_DC =MIN_DUTY;
			PWMVL_DC =MIN_DUTY;
			PWMWH_DC =PWM_FCY/2;
			PWMWL_DC =MIN_DUTY;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//4
		if (H1_P61 == 0)
		{if (H2_P60 == 1)
		{if (H3_P59 == 0)
		{
			PWMUH_DC =MIN_DUTY;
			PWMUL_DC =PWM_FCY/2;
			PWMVH_DC =PWM_FCY/2;
			PWMVL_DC =MIN_DUTY;
			PWMWH_DC =MIN_DUTY;
			PWMWL_DC =MIN_DUTY;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//5
		if (H1_P61 == 1)
		{if (H2_P60 == 1)
		{if (H3_P59 == 0)
		{
			PWMUH_DC =MIN_DUTY;
			PWMUL_DC =MIN_DUTY;
			PWMVH_DC =PWM_FCY/2;
			PWMVL_DC =MIN_DUTY;
			PWMWH_DC =MIN_DUTY;
			PWMWL_DC =PWM_FCY/2;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//6
		if (H1_P61 == 1)
		{if (H2_P60 == 0)
		{if (H3_P59 == 0)
		{
			PWMUH_DC =PWM_FCY/2;
			PWMUL_DC =MIN_DUTY;
			PWMVH_DC =MIN_DUTY;
			PWMVL_DC =MIN_DUTY;
			PWMWH_DC =MIN_DUTY;
			PWMWL_DC =PWM_FCY/2;
			LATAbits.LATA0 =0; // Set the RA0 value as 1
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
		//default
		if (H1_P61 == 0)
		{if (H2_P60 == 0)
		{if (H3_P59 == 0)
		{
			PWMUH_DC =MIN_DUTY;
			PWMUL_DC =MIN_DUTY;
			PWMVH_DC =MIN_DUTY;
			PWMVL_DC =MIN_DUTY;
			PWMWH_DC =MIN_DUTY;
			PWMWL_DC =MIN_DUTY;
			TMR3 = 0x0000; // Clear timer register
			T3CONbits.TON = 1; // Start Timer
		}}}
#endif
	}
#endif
return 0;
}