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

/* Main function */
int main(void){
		    /* 1.USART */
	// initialize USART protocol.
	_usart_baudrate_init_(9600);
	// enable transmitter.
	_usart_TX_enable_();

	// USART transmitted string.
	char str[50] = "Hello valeo \r";

		   /* 2.SPI */
	// initialize SPI protocol.
	_spi_master_init(16);


	// endless loop.
	for(;;){
		// USART
		_usart_transmit_str(str);

		//SPI
		for(int i=0; str[i]!='\0'; i++){
			_spi_master_write(str[i]);
		}
	}
	return 0;
}


