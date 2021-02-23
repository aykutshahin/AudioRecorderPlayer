/*
* lc512driver.c
* Created for GTU MICROCONTROLLER CLASS PROJECT 3
* Author: Aykut Sahin
* Student ID:171024034
*
*/
#include "lc512driver.h"

//Initializing EEPROM
void INIT_EEPROM_512()
{
	//PB8-PB9 pins will activate
	//alternate function 6

	//PB8 as AF6
	GPIOB->MODER &= ~(3U << 2*8);
	GPIOB->MODER |= (2U << 2*8);
	GPIOB->OTYPER|= (1U << 8);

	//choose AF from mux
	GPIOB->AFR[1] &= ~(0xFU << 4*0);
	GPIOB->AFR[1] |= (6 << 4*0);


	//PB9 as AF6
	GPIOB->MODER &= ~(3U << 2*9);
	GPIOB->MODER |= (2U << 2*9);
	GPIOB->OTYPER|= (1U << 9);

	//choose AF from mux
	GPIOB->AFR[1] &= ~(0xFU << 4*1);
	GPIOB->AFR[1] |= (6 << 4*1);

	//enable I2C1
	RCC->APBENR1 |= (1U << 21);

	I2C1->CR1 = 0;
	I2C1->CR1 |= (1 << 7);//ERR1, error interrupt


	//TIMING REGISTERS FOR STANDART MODE
	I2C1->TIMINGR |= (3 << 28);//PRESC
	I2C1->TIMINGR |= (0x13 << 0);//SCLL
	I2C1->TIMINGR |= (0xF << 8);//SCLR
	I2C1->TIMINGR |= (0x2 << 16);//SDADEL
	I2C1->TIMINGR |= (0x4 << 20);//SCLDEL

	I2C1->CR1 = (1U << 0);//PE=0

	NVIC_SetPriority(I2C1_IRQn,0);
	NVIC_EnableIRQ(I2C1_IRQn);
}

//Writing single byte
void WriteSingleByte(uint8_t devAddr, uint16_t destAddr, uint8_t data)
{
	//Data sheet pattern applied
	//Write operation
	I2C1->CR2=0;
	//Slave address
	I2C1->CR2 |= ((uint32_t)(devAddr << 1));
	//Number of bytes that will send
	I2C1->CR2 |= (3U << 16);
	I2C1->CR2 |= (1U << 25);//AUTOEND
	I2C1->CR2 |= (1U << 13);//Start condition


	while(!(I2C1->ISR & (1 << 1)));//TXIS
	I2C1->TXDR = (uint32_t)(destAddr >> 8);//transmit data register

	while(!(I2C1->ISR & (1 << 1)));//TXIS
	I2C1->TXDR = (uint32_t)(destAddr & 0xFF);//transmit data register

	while(!(I2C1->ISR & (1 << 1)));//TXIS
	I2C1->TXDR = (uint32_t)data;//transmit data register
}

//Writing 128 bytes
void WriteMultipleByte(uint8_t devAddr, uint16_t startAddr, uint8_t* data, uint8_t size)
{
	//Avoid writing more than 128 byte and less than 0 byte
	if(size > 128 && size <= 0)
	{
		return;
	}
	//Data sheet pattern applied
	//Write operation
	I2C1->CR2=0;
	//Slave address
	I2C1->CR2 |= ((uint32_t)(devAddr << 1));
	//Number of bytes that will send
	I2C1->CR2 |= ((uint32_t)(2U + size) << 16);
	I2C1->CR2 |= (1U << 25);//AUTOEND
	I2C1->CR2 |= (1U << 13);//Start condition


	while(!(I2C1->ISR & (1 << 1)));//TXIS
	I2C1->TXDR = (uint32_t)(startAddr >> 8);//transmit data register

	while(!(I2C1->ISR & (1 << 1)));//TXIS
	I2C1->TXDR = (uint32_t)(startAddr & 0xFF);//transmit data register

	uint8_t i;
	for(i = 0; i < size; i++)
	{
		while(!(I2C1->ISR & (1 << 1)));//TXIS
		I2C1->TXDR = (uint32_t)data[i];//transmit data register
	}
}

//Reading single byte
void ReadSingleByte(uint8_t devAddr, uint16_t resAddr, uint8_t* data)
{
	//Data sheet pattern applied
	//Write operation
	I2C1->CR2 = 0;
	//Slave address
	I2C1->CR2 |= ((uint32_t)(devAddr << 1));
	//Number of bytes that will send
	I2C1->CR2 |= (2U << 16);
	I2C1->CR2 |= (1U << 13);//Start condition

	while(!(I2C1->ISR & (1 << 1)));//TXIS
	I2C1->TXDR = (uint32_t)(resAddr >> 8);//transmit data register

	while(!(I2C1->ISR & (1 << 1)));//TXIS
	I2C1->TXDR = (uint32_t)(resAddr & 0xFF);//transmit data register

	while(!(I2C1->ISR & (1 << 6)));//TC

	//read operation(read data)
	I2C1->CR2=0;
	I2C1->CR2 |= ((uint32_t)(devAddr << 1));
	I2C1->CR2 |= (1U << 10);//READ MODE
	I2C1->CR2 |= (1U << 16);//NUMBER OF BYTES
	I2C1->CR2 |= (1U << 15);//NACK
	I2C1->CR2 |= (1U << 25);//AUTOEND
	I2C1->CR2 |= (1U << 13);//start condition
	while(!(I2C1->ISR & (1 << 2)));//wait until RXNE=1
	*data = (uint8_t)I2C1->RXDR;

}

//Reading 128 bytes
void ReadMultipleByte(uint8_t devAddr, uint16_t resAddr, uint8_t* data, uint16_t size)
{
	//Data sheet pattern applied
	//Write operation
	I2C1->CR2 = 0;
	//Slave address
	I2C1->CR2 |= ((uint32_t)(devAddr << 1));
	//Number of bytes that will send
	I2C1->CR2 |= (2U << 16);
	I2C1->CR2 |= (1U << 13);//Start condition

	while(!(I2C1->ISR & (1 << 1)));//TXIS
	I2C1->TXDR = (uint32_t)(resAddr >> 8);//transmit data register

	while(!(I2C1->ISR & (1 << 1)));//TXIS
	I2C1->TXDR = (uint32_t)(resAddr & 0xFF);//transmit data register

	while(!(I2C1->ISR & (1 << 6)));//TC

	//Read operation
	I2C1->CR2=0;
	//Slave address
	I2C1->CR2 |= ((uint32_t)(devAddr << 1));
	I2C1->CR2 |= (1U << 10);//READ MODE
	//Number of bytes that will send
	I2C1->CR2 |= ((1U * size) << 16);
	I2C1->CR2 |= (1U << 25);//AUTOEND
	I2C1->CR2 |= (1U << 13);//Start condition

	uint16_t i;
	for(i = 0; i < size; ++i)
	{
		while(!(I2C1->ISR & (1 << 2)));//wait until RXNE=1
		data[i] = (uint8_t)I2C1->RXDR;
	}
	I2C1->CR2 |= (1U << 15);//NACK
}
