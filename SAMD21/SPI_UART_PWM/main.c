#include <atmel_start.h>


struct  
{
	//double sam;
	char sampl;			//1
	int sam;			//4 + //3 padding
	double samp;		//8
}sample1;  //16

struct
{
	short sample;     //2 + 6 padding
	double samo;	//8 
	char sam;		//1 + 7 padding
}sample2;   //24

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	struct io_descriptor *UARTio, *SPIio,*I2Cio;
	atmel_start_init();
	USART_0_example();
	TIMER_0_example();	
	SPI_0_example();
	PWM_0_example();
	I2C_0_example();
	usart_sync_get_io_descriptor(&USART_0, &UARTio);
	i2c_m_sync_get_io_descriptor(&I2C_0,&I2Cio);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0xAE, I2C_M_SEVEN);
	spi_m_sync_get_io_descriptor(&SPI_0, &SPIio);
	/* Replace with your application code */
	while (1) {
		sample1.sam++;
		sample2.sample++;
		io_write(UARTio, (uint8_t *)"Welcome to Motor_Controller_V3", 30);
		io_write(SPIio, (uint8_t *)"Welcome to Motor_Controller_V3", 30);
		io_write(I2Cio, (uint8_t *)"Welcome to Motor_Controller_V3", 30);
		delay_ms(1000);
	}
	return 0;
}
