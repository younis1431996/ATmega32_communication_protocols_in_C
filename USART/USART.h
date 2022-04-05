/*
 * USART.h
 *
 *  Created on: Apr 5, 2022
 *      Author: Hoda
 */

#ifndef USART_USART_H_
#define USART_USART_H_

/* inclusions */
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

/* definitions */
#define BAUD_PRESCALE(USART_BAUDRATE) ( (F_CPU / (USART_BAUDRATE * 16UL)) - 1)

							/* USART functions */

/* baudrate initialization */
void _usart_baudrate_init_(uint32_t baudrate);

/* USART enable the receiver */
void _usart_RX_enable_(void);

/* USART disable the receiver */
void _usart_RX_disable_(void);

/* USART enable the transmitter */
void _usart_TX_enable_(void);

/* USART disable the transmitter */
void _usart_TX_disable_(void);

/* set character size */
void _usart_char_size(uint8_t __size);

/* receive character */
void _usart_receive_char(char *character);

/* receive string */
void _usart_receive_str(char *str);

/* transmit character */
void _usart_transmit_char(char character);

/* transmit string */
void _usart_transmit_str(char *str);

/* send new line */
void _usart_transmit_new_line(void);

/* enable synchronous mode */
void _usart_sync_mode_enable(void);

/* disable synchronous mode*/
void _usart_sync_mode_disable(void);

#endif /* USART_USART_H_ */
