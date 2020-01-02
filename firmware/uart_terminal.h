/*
 * usart_terminal.h
 *
 * Created: 27.08.2019 13:53:31
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 * AVR/GNU C Compiler : 4.8.1
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 


#ifndef UART_TERMINAL_H_
#define UART_TERMINAL_H_

#include <stdbool.h>
#include <avr/io.h>
#include "config.h"
#include "macro.h"
#include "types.h"


#define UART_BAUDRATE		(9600)
#define UART_PRESCALE		(((F_CPU / (16UL * UART_BAUDRATE))) - 1)

#define TERMINAL_NEW_LINE				(0x0d)
#define TERMINAL_NEW_COMMAND			(0x40)
#define TERMINAL_HELP					(0x3f)
#define TERMINAL_SPACE					(0x20)

#define UART_INPUT_BUFFER_LENGTH		(24)
#define UART_OUTPUT_BUFFER_LENGTH		(76)
#define UART_OPTION_LENGTH				(16)
	
typedef struct CircularBuffer {
	volatile char data[UART_OUTPUT_BUFFER_LENGTH];
	volatile uint8_t start;
	volatile uint8_t end;	
} CircularBuffer_t; 

typedef struct UART_Terminal {
	volatile char input_buffer[UART_INPUT_BUFFER_LENGTH];
	volatile uint8_t input_buffer_position;
	volatile bool input_is_empty;
	volatile bool input_is_full;
	bool change_to_write;
	char command_option[UART_OPTION_LENGTH];
	CircularBuffer_t output_buffer;
	bool silent;
	DCCON_t *state;
} DCTERMINAL_t;


void uart_Init(DCTERMINAL_t *terminal, DCCON_t *state);
void uart_InterruptHandler(DCTERMINAL_t *terminal);
void uart_SendOutputBuffer(CircularBuffer_t *buffer);
void uart_DropInputBuffer(DCTERMINAL_t *terminal);
bool terminal_FindNewLine(DCTERMINAL_t *terminal, uint8_t *len);
void terminal_ParseCommand(DCTERMINAL_t *terminal, uint8_t len);



#endif /* USART_TERMINAL_H_ */