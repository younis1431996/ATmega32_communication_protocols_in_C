/*
 * SPI.h
 *
 *  Created on: Apr 5, 2022
 *      Author: Mahmoude Mohamed Younis.
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * $ When the device is in master mode:-
 *  > Master writes data byte in SPDR.
 *  > Writing to SPDR starts data transmission.
 *  > 8-bit data starts shifting out towards slave and
 *    after the complete byte is shifted, SPI clock
 *    generator stops, and SPIF bit gets set.
 *------------------------------------------------------------*
 * $ When the device is in slave mode:-
 *  > THE Slave SPI interface remains in sleep as long as
 *    the SS pin is held high by the master.
 *  > It activates only when the SS pin is driven low.
 *  > Data is shifted out with incoming SCK clock from master
 *    during a write operation.
 *  > SPIF is set after the complete shifting of a byte.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * $ SS pin functionality Master mode:-
 *  > In master mode, the SS pin is used as a GPIO pin.
 *  > Make the SS pin direction as output to select a slave
 *    device using this pin.
 *  > Note that if the SS pin configured as input
 *    then it must be set high for master operation.
 *  > If it is set as input in master mode and gets driven
 *    low by an external circuit, then the SPI system recognizes this
 *    as another master selecting SPI as a slave due to its active low behavior.
 *  > This will clear the MSTR bit in the SPCR register and SPI turns in slave mode.
 *----------------------------------------------------------------------------------
 * $ SS pin functionality Slave mode:-
 *  > In slave mode, the SS pin is always configured as an input.
 *  > When it is low SPI activates.
 *  > And when it is driven high SPI logic gets reset
 *    and does not receive any incoming data.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* inclusions */
#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

// master initialization.
void _spi_master_init(uint8_t prescaler);

// master write.
void _spi_master_write(int8_t character);

// master read.
void _spi_master_read(int8_t *character);

// slave initialization.
void _spi_slave_init(void);

// slave write.
void _spi_slave_write(int8_t character);

// slave read.
void _spi_slave_read(int8_t *character);


#endif /* SPI_SPI_H_ */
