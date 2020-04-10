# 1 "main.c"
# 1 "C:\\Users\\Selva\\Desktop\\Motor_Control_V2.X//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "main.c"
# 15 "main.c"
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
# 44 "main.c"
}
uint16_t Read_ADC()
{
# 58 "main.c"
}


void PWM123_Init()
{
# 109 "main.c"
}

void TMR1_Init()
{
# 124 "main.c"
}
# 144 "main.c"
void Osc_Init()
{
# 160 "main.c"
}


void Hall_Pins_Init()
{







}

int main()
{
uint16_t i=0;

Osc_Init();
initAdc1();
PWM123_Init();
TMR1_Init();
Hall_Pins_Init();



TRISAbits.TRISA0= 0b0;
LATAbits.LATA0 =1;
# 305 "main.c"
return 0;
}
