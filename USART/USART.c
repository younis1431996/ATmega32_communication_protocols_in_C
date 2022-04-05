/*
 * USART.c
 *
 *  Created on: Apr 5, 2022
 *      Author: Hoda
 */
/* inclusions */
#include "USART.h"

//*  Static functions *//
/* Function to check the state of a bit if one or zero. */
static char bit_check(volatile uint8_t *reg, uint8_t bit){
	return ( ( *reg&(1<<bit) ) >> bit );
}

/* baudrate initialization */
void _usart_baudrate_init_(uint32_t baudrate){
	/* Load lower 8-bits of the baud rate */
	UBRRL = BAUD_PRESCALE(baudrate);

	/* Load upper 8-bits*/
	UBRRH = (BAUD_PRESCALE(baudrate) >> 8);
	return;
}

/* USART enable the receiver */
void _usart_RX_enable_(void){
	UCSRB |= (1 << RXEN);
	return;
}

/* USART disable the receiver */
void _usart_RX_disable_(void){
	UCSRB &= ~(1 << RXEN);
	return;
}

/* USART enable the transmitter */
void _usart_TX_enable_(void){
	UCSRB |= (1 << TXEN);
	return;
}

/* USART disable the transmitter */
void _usart_TX_disable_(void){
	UCSRB &= ~(1 << TXEN);
	return;
}

/* set character size */
void _usart_char_size(uint8_t __size){
	// The URSEL must be one when writing the UCSRC.
	UCSRC |= (1<<URSEL);

	if(__size == 5){
		UCSRC &= ~(1<<UCSZ0);
		UCSRC &= ~(1<<UCSZ1);
		UCSRB &= ~(1<<UCSZ2);
		return;
	}else if(__size == 6){
		UCSRC |=  (1<<UCSZ0);
		UCSRC &= ~(1<<UCSZ1);
		UCSRB &= ~(1<<UCSZ2);
		return;
	}else if(__size == 7){
		UCSRC &= ~(1<<UCSZ0);
		UCSRC |=  (1<<UCSZ1);
		UCSRB &= ~(1<<UCSZ2);
		return;
	}else if(__size == 8){
		UCSRC |=  (1<<UCSZ0);
		UCSRC |=  (1<<UCSZ1);
		UCSRB &= ~(1<<UCSZ2);
		return;
	}else if(__size == 9){
		UCSRC |=  (1<<UCSZ0);
		UCSRC |=  (1<<UCSZ1);
		UCSRB |=  (1<<UCSZ2);
		return;
	}
}

/* receive character */
void _usart_receive_char(char *character){
	/* Wait till data is received */
	while (bit_check(&UCSRA, RXC) == 0);

	/* Return the byte */
	*character = UDR;
	return;
}

/* receive string */
void _usart_receive_str(char *str){
	int i=0;
	do{
		_usart_receive_char(&str[i]);
		i++;
	}while(str[i]!='\0');
	return;
}

/* transmit character */
void _usart_transmit_char(char character){
	/* Wait for empty transmit buffer */
	while (! (bit_check(&UCSRA, UDRE)) );

	/* send character*/
	UDR = character;
	return;
}

/* transmit string */
void _usart_transmit_str(char *str){
	for(int i=0; str[i]!='\0'; i++){
		_usart_transmit_char(str[i]);
	}
	return;
}

/* send new line */
void _usart_transmit_new_line(void){
	_usart_transmit_char('\r');
	return;
}

// enable synchronous mode.
void _usart_sync_mode_enable(void){
	UCSRC |= (1<<URSEL) | (1<<UMSEL);\
	return;
}

// disable synchronous mode.
void _usart_sync_mode_disable(void){
	UCSRC |= (1<<URSEL);
	UCSRC &= ~(1<<UMSEL);
	return;
}

