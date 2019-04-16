/*
 * UART.h
 *
 * Created: 15-01-2019 16:08:39
 *  Author: ERTS
 */ 


#include <avr/io.h>


#ifndef UART_H_
#define UART_H_


#define RX_EN		4
#define TX_EN		3
#define UDR_EMPTY	5


// initializes UART0, sets baud rate, enables receiver and transmit, setting data frame
void uart0_init();

// sends a character byte
void uart_tx(char data);

// sends a string
void uart_tx_string(char *data);


#endif /* UART_H_ */