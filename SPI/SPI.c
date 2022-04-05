/*
 * SPI.c
 *
 *  Created on: Apr 5, 2022
 *      Author: Mahmoude Mohamed Younis.
 */
/* inclusions */
#include "SPI.h"

/* definitions */
#define SS		PB4
#define MOSI	PB5
#define MISO	PB6
#define SCK		PB7

// master initialization.
void _spi_master_init(uint8_t prescaler){
	/* Make MOSI, SCK, SS as Output pin. */
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);

	/* Make MISO pin as input pin. */
	DDRB &= ~(1<<MISO);

	/* Make high on SS pin. */
	PORTB |= (1<<SS);

	/* Enable SPI in master mode. */
	SPCR = (1<<SPE)|(1<<MSTR);

	/* Disable speed doubler. */
	SPSR &= ~(1<<SPI2X);

	/* Frequency selection. */
	if(prescaler == 4){
		SPCR &= ~(1<<SPR1) & ~(1<<SPR0);
	}
	else if(prescaler == 16){
		SPCR |=  (1<<SPR0);
		SPCR &= ~(1<<SPR1);
	}
	else if(prescaler == 64){
		SPCR &= ~(1<<SPR0);
		SPCR |=  (1<<SPR1);
	}
	else if(prescaler == 128){
		SPCR |= (1<<SPR0);
		SPCR |= (1<<SPR1);
	}
	return;
}

// master write.
void _spi_master_write(int8_t character){
	// SS low..
	PORTB &= ~(1<<SS);

	int8_t flush_buffer;

	/* Write data to SPI data register */
	SPDR = character;

	/* Wait till transmission complete */
	while(!(SPSR & (1<<SPIF)));

	/* Flush received data */
	flush_buffer = SPDR;

	/* Note: SPIF flag is cleared by first reading SPSR
	 * (with SPIF set) and then accessing SPDR hence flush
	 * buffer used here to access SPDR after SPSR read */
	return;
}

// master read.
void _spi_master_read(int8_t *character){
	// SS low..
	PORTB &= ~(1<<SS);

	SPDR = 0xFF;

	/* Wait till reception complete */
	while(!(SPSR & (1<<SPIF)));

	/* Return received data */
	*character = SPDR;
	return;
}

// slave initialization.
void _spi_slave_init(void){
	 /* Make MOSI, SCK, SS as input pins */
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));

	/* Make MISO pin as output pin */
	DDRB |= (1<<MISO);

	/* Enable SPI in slave mode */
	SPCR = (1<<SPE);
}

// slave write.
void _spi_slave_write(int8_t character){
	SPDR = character;
	return;
}

// slave read.
void _spi_slave_read(int8_t *character){
	/* Wait till reception complete */
	while(!(SPSR & (1<<SPIF)));

	/* Return received data */
	*character = SPDR;
	return;
}




