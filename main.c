/*
 * main.c
 *
 *  Created on: Apr 5, 2022
 *      Author: Mahmoude Mohamed Younis.
 */
/* Inclusions */
#include <avr/io.h>
#include <util/delay.h>

// USART module.
#include "USART/USART.h"

// SPI module.
#include "SPI/SPI.h"

// I2C module
#include "I2C/ATmega32_TWI.h"

/* Main function */
int main(void){
		    /* 1.USART */
	// initialize USART protocol.
	_usart_baudrate_init_(9600);
	// enable transmitter.
	_usart_TX_enable_();

	// USART transmitted string.
	char usart_str[50] = "Hello valeo \r";
	char spi_str[50] = "0123456789";
	char i2c_str[50] = "abcdefg";

		    /* 2.SPI */
	// initialize SPI protocol.
	_spi_master_init(16);

		    /* 3.I2C */
	// initialize I2C protocol.
	TWI_int(0x11);

	// endless loop.
	for(;;){
		// USART
		_usart_transmit_str(usart_str);

		//SPI
		for(int i=0; spi_str[i]!='\0'; i++){
			_spi_master_write(spi_str[i]);
		}

		// I2C
		for (int i=0; i2c_str[i]!='\0'; ++i) {
			TWI_master_write_byte(0x11, i2c_str[i]);
			_delay_ms(1);
		}
	}
	return 0;
}


