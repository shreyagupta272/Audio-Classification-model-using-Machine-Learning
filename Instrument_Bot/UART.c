/*
 * UART.c
 *
 * Created: 15-01-2019 16:08:54
 *  Author: ERTS
 */ 


#include "UART.h"


// initializes UART0, sets baud rate, enables receiver and transmit, setting data frame
void uart0_init()
{
	// disable while setting baud rate
	UCSR0B = 0x00;
	
	// for F_CPU = 14.7456 MHz and baud rate = 9600, UBBR = 95
	UBRR0  = 95;
	
	UCSR0C = UCSR0C | (1 << UCSZ01) | (1 << UCSZ00);
	
	UCSR0B = UCSR0B | (1 << RX_EN) | (1 << TX_EN);
}


// sends a character byte
void uart_tx(char data)
{
	// waiting to transmit
	while(!(UCSR0A & (1 << UDR_EMPTY)));
	
	UDR0 = data;
}


// sends a string
void uart_tx_string(char *data)
{
	while (*data != '\0')
	{
		uart_tx(*data);
		data++;
	}
}




