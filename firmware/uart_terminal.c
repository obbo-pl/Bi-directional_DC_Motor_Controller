/*
 * usart_terminal.c
 *
 * Created: 27.08.2019 13:54:28
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 * AVR/GNU C Compiler : 4.8.1
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 

#include "uart_terminal.h"
#include <stdlib.h>
#include <stdio.h>


bool uart_SendChar(char data);

uint8_t circular_buffer_Next(uint8_t pointer, uint8_t length);
bool circular_buffer_IsFull(const uint8_t start, const uint8_t end, uint8_t length);
bool circular_buffer_StringCopy(CircularBuffer_t *dest, const char *src);
bool circular_buffer_AddChar(CircularBuffer_t *dest, const char *src);

void terminal_SendOK(CircularBuffer_t *output);
void terminal_SendBadArgument(CircularBuffer_t *output);
void terminal_SendUnknown(CircularBuffer_t *output);
void terminal_ClearInputBuffer(DCTERMINAL_t *terminal);
void terminal_ClearCommandOptionBuffer(char *buffer);
void terminal_InitOutputBuffer(DCTERMINAL_t *terminal);
bool terminal_FindCommand(DCTERMINAL_t *terminal, uint8_t len);
void terminal_ShrinkBuffer(DCTERMINAL_t *terminal, uint8_t len);
void terminal_SendNL(CircularBuffer_t *output);

void command_SendSystemInfo(DCTERMINAL_t *terminal);
void command_SendHelp(DCTERMINAL_t *terminal);
void command_ShowErrors(DCTERMINAL_t *terminal);
void command_ClearErrors(DCTERMINAL_t *terminal);
void command_ShowChannelValue(DCTERMINAL_t *terminal);
void command_ShowChannelLast(DCTERMINAL_t *terminal);
void command_ShowChannelRange(DCTERMINAL_t *terminal);
void command_BatteryVoltageValue(DCTERMINAL_t *terminal);
void command_BatteryVoltageDivider(DCTERMINAL_t *terminal);
void command_BatteryVoltageCut(DCTERMINAL_t *terminal);
void command_BatterySpeedLimit(DCTERMINAL_t *terminal);
void command_SpeedFilterCustom(DCTERMINAL_t *terminal);

void ftoa(float f, char *buffer, uint8_t length);


typedef struct terminal_command {
	const char *pattern;
	void (*callback)(DCTERMINAL_t *);
} TERMINAL_COMMAND_t;

#define COMMANDS_COUNT		11
#define COMMAND_LENGTH		4
const TERMINAL_COMMAND_t terminal_commands[COMMANDS_COUNT] = {
	{ .pattern = "@VER", .callback = command_SendSystemInfo,},
	{ .pattern = "@ERR", .callback = command_ShowErrors,},
    { .pattern = "@ERC", .callback = command_ClearErrors,},
	{ .pattern = "@CHV", .callback = command_ShowChannelValue,},
	{ .pattern = "@CHL", .callback = command_ShowChannelLast,},
	{ .pattern = "@CHR", .callback = command_ShowChannelRange,},
	{ .pattern = "@BVV", .callback = command_BatteryVoltageValue,},
	{ .pattern = "@BVC", .callback = command_BatteryVoltageCut,},
	{ .pattern = "@BVD", .callback = command_BatteryVoltageDivider,},
	{ .pattern = "@BSL", .callback = command_BatterySpeedLimit,},
	{ .pattern = "@SFC", .callback = command_SpeedFilterCustom,},
};

#define SET_UART_TX_OUT	 		(glue2(DDR, CONFIG_SERIAL_PORT) |= (1 << glue3(DD, CONFIG_SERIAL_PORT, CONFIG_SERIAL_Tx_PIN)))
#define SET_UART_RX_IN			(glue2(DDR, CONFIG_SERIAL_PORT) &= ~(1 << glue3(DD, CONFIG_SERIAL_PORT, CONFIG_SERIAL_Rx_PIN)))
#define SET_UART_RX_PULLUP		(glue2(PORT, CONFIG_SERIAL_PORT) |= (1 << glue3(P, CONFIG_SERIAL_PORT, CONFIG_SERIAL_Rx_PIN)))


uint8_t circular_buffer_Next(uint8_t pointer, uint8_t length)
{
	pointer++;
	if (pointer == length) pointer = 0;
	return pointer;
}

bool circular_buffer_IsFull(const uint8_t start, const uint8_t end, uint8_t length)
{
	if (start == circular_buffer_Next(end, length)) return true;
	return false;
}

bool circular_buffer_StringCopy(CircularBuffer_t *dest, const char *src)
{
	bool result = true;
	const char *s = src;
	while (result && !(*s == 0x00)) {
		dest->data[dest->end] = *s++;
		dest->end = circular_buffer_Next(dest->end, UART_OUTPUT_BUFFER_LENGTH);
		result = !(circular_buffer_IsFull(dest->start, dest->end, UART_OUTPUT_BUFFER_LENGTH));
	}
	return result;
}

bool circular_buffer_AddChar(CircularBuffer_t *dest, const char *src)
{
	bool result = true;
	dest->data[dest->end] = *src;
	dest->end = circular_buffer_Next(dest->end, UART_OUTPUT_BUFFER_LENGTH);
	result = !(circular_buffer_IsFull(dest->start, dest->end, UART_OUTPUT_BUFFER_LENGTH));
	return result;
}

void uart_Init(DCTERMINAL_t *terminal, DCCON_t *state)
{
	SET_UART_TX_OUT;
	SET_UART_RX_IN;
	SET_UART_RX_PULLUP;

	UBRRH = (uint8_t)(UART_PRESCALE >> 8);
	UBRRL = (uint8_t)(UART_PRESCALE);
	
	UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);		// RX Complete Interrupt Enable, Receiver Enable, Transmitter Enable
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);     // Asynchronous Operation, Parity Mode Disabled, Stop Bit: 1-bit, Character Size: 8-bit
	terminal->state = state;
	terminal_ClearInputBuffer(terminal);
	terminal_InitOutputBuffer(terminal);
}

void uart_InterruptHandler(DCTERMINAL_t *terminal)
{
	char new_char;
	if (terminal->input_buffer_position < UART_INPUT_BUFFER_LENGTH) {
		new_char = UDR;
		if ((new_char > 0x20) && (new_char < 0x7f)) {
			terminal->input_buffer[terminal->input_buffer_position] = new_char;
			terminal->input_buffer_position++;
			circular_buffer_AddChar(&(terminal->output_buffer), &new_char);
		} else if (new_char == 0x20) {
			if (terminal->input_buffer_position > 0) {
				terminal->input_buffer[terminal->input_buffer_position] = new_char;
				terminal->input_buffer_position++;
			}
			circular_buffer_AddChar(&(terminal->output_buffer), &new_char);
		} else if (new_char == 0x08) {
			if (terminal->input_buffer_position > 0) {
				terminal->input_buffer[terminal->input_buffer_position] = 0x00;
				terminal->input_buffer_position--;
			}
			circular_buffer_AddChar(&(terminal->output_buffer), &new_char);
		} else if ((new_char == 0x0a) || (new_char == 0x0d)) {
			if (!(terminal->input_is_empty)) {
				terminal->input_buffer[terminal->input_buffer_position] = TERMINAL_NEW_LINE;
				terminal->input_buffer_position++;
			}
			terminal_SendNL(&(terminal->output_buffer));
		}
		if (terminal->input_buffer_position > 0) terminal->input_is_empty = false;
	}
	if (terminal->input_buffer_position >= UART_INPUT_BUFFER_LENGTH) terminal->input_is_full = true;
}

bool uart_SendChar(char data)
{
	if (UCSRA & (1 << UDRE)) {
		UDR = data;
		return true;
	}
	return false;
}

void uart_SendOutputBuffer(CircularBuffer_t *buffer)
{
	bool send_status;
	if (buffer->start != buffer->end) {
		do {		
			send_status = uart_SendChar(buffer->data[buffer->start]);
			if (send_status) buffer->start = circular_buffer_Next(buffer->start, UART_OUTPUT_BUFFER_LENGTH);
		} while (send_status && (buffer->start != buffer->end));
	}
}

void uart_DropInputBuffer(DCTERMINAL_t *terminal)
{
	terminal_ClearInputBuffer(terminal);
	terminal_SendUnknown(&terminal->output_buffer);
}

void terminal_ParseCommand(DCTERMINAL_t *terminal, uint8_t len)
{
	terminal_FindCommand(terminal, len);
	terminal_ShrinkBuffer(terminal, len);
	if (terminal->input_buffer_position == 0) terminal_ClearInputBuffer(terminal);
}

bool terminal_FindNewLine(DCTERMINAL_t *terminal, uint8_t *len)
{
	for (int i = 0; i < UART_INPUT_BUFFER_LENGTH; i++) {
		if (terminal->input_buffer[i] == TERMINAL_NEW_LINE) {
			*len = i + 1;
			return true;
		}
	}
	return false;
}

void terminal_ClearInputBuffer(DCTERMINAL_t *terminal)
{
	for (int i = 0; i < UART_INPUT_BUFFER_LENGTH; i++) {
		terminal->input_buffer[i] = 0x00;
	}
	terminal->input_buffer_position = 0;
	terminal->input_is_empty = true;
	terminal->input_is_full = false;
}

void terminal_InitOutputBuffer(DCTERMINAL_t *terminal)
{
	terminal->output_buffer.start = 0;
	terminal->output_buffer.end = 0;
}

void terminal_ShrinkBuffer(DCTERMINAL_t *terminal, uint8_t len)
{
	terminal->input_buffer[len - 1] = 0x00;
	for (int i = len; i < UART_INPUT_BUFFER_LENGTH; i++) {
		terminal->input_buffer[i - len] = terminal->input_buffer[i];
		terminal->input_buffer[i] = 0x00;
	}
	terminal->input_buffer_position -= len;
}

bool terminal_FindCommand(DCTERMINAL_t *terminal, uint8_t len)
{
	bool result = false; 
	if ((len == 2) && (terminal->input_buffer[0] == '?')) {
			command_SendHelp(terminal);
			result = true;
	}
	if (terminal->input_buffer[0] == TERMINAL_NEW_COMMAND) {
		for (int i = 0; i < COMMANDS_COUNT; i++) {
			const char *patern;
			patern = terminal_commands[i].pattern;
			bool match = true;
			for (int j = 1; j < COMMAND_LENGTH; j++) {
				if (terminal->input_buffer[j] != patern[j]) match = false;
			}
			if (!((terminal->input_buffer[COMMAND_LENGTH] == TERMINAL_HELP) 
				|| (terminal->input_buffer[COMMAND_LENGTH] == TERMINAL_NEW_LINE) 
				|| (terminal->input_buffer[COMMAND_LENGTH] == TERMINAL_SPACE))) match = false;
			if (match) {
				for (int j = 0; j < (len - COMMAND_LENGTH); j++) {
					if (j >= (UART_OPTION_LENGTH - 1)) break;
					terminal->command_option[j] = terminal->input_buffer[j + COMMAND_LENGTH];
				}
				terminal_commands[i].callback(terminal);
				terminal_ClearCommandOptionBuffer(terminal->command_option);
				result = true;
			} 
		}
	}
	if (!(result)) terminal_SendUnknown(&terminal->output_buffer);
	return result;
}

void terminal_ClearCommandOptionBuffer(char *buffer)
{
	for (int i = 0; i < UART_OPTION_LENGTH; i++) {
		buffer[i] = 0x00;
	}
}

void command_ShowErrors(DCTERMINAL_t *terminal)
{
	circular_buffer_StringCopy(&(terminal->output_buffer), "Errors: ");
	char buffer [10];
	int i = 0x80;
	while (i > terminal->state->errors)  {
		i = i >> 1;
		circular_buffer_StringCopy(&(terminal->output_buffer), "0");
	}
	if (terminal->state->errors > 0) {
		itoa(terminal->state->errors, buffer, 2);
		circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	}
	terminal_SendNL(&(terminal->output_buffer));
}

void command_ClearErrors(DCTERMINAL_t *terminal)
{
	circular_buffer_StringCopy(&(terminal->output_buffer), "Cleared");
	terminal->state->errors = 0x00;
	terminal_SendNL(&(terminal->output_buffer));
}

void command_ShowChannelValue(DCTERMINAL_t *terminal)
{
	circular_buffer_StringCopy(&(terminal->output_buffer), "Current channel value [tick]: ");
	char buffer [6];
	itoa(terminal->state->channel_value, buffer, 10);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	terminal_SendNL(&(terminal->output_buffer));
}

void command_ShowChannelLast(DCTERMINAL_t *terminal)
{
	circular_buffer_StringCopy(&(terminal->output_buffer), "Last pulse length [tick]: ");
	char buffer [6];
	itoa(terminal->state->channel_last, buffer, 10);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	terminal_SendNL(&(terminal->output_buffer));
}

void command_ShowChannelRange(DCTERMINAL_t *terminal)
{
	circular_buffer_StringCopy(&(terminal->output_buffer), "Calibrated pulse length [tick]: ");
	char buffer [6];
	itoa(terminal->state->channel_minimum, buffer, 10);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	circular_buffer_StringCopy(&(terminal->output_buffer), ", ");
	itoa(terminal->state->channel_neutral, buffer, 10);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	circular_buffer_StringCopy(&(terminal->output_buffer), ", ");
	itoa(terminal->state->channel_maximum, buffer, 10);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	terminal_SendNL(&(terminal->output_buffer));
}

void command_BatteryVoltageValue(DCTERMINAL_t *terminal)
{
	circular_buffer_StringCopy(&(terminal->output_buffer), "Battery voltage [A/D, volt]: ");
	char buffer[8];
	itoa(terminal->state->battery_voltage, buffer, 10);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	circular_buffer_StringCopy(&(terminal->output_buffer), ", ");
	float volt_f = terminal->state->battery_voltage;
	volt_f /= terminal->state->battery_divider;
	ftoa(volt_f, buffer, 8);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	circular_buffer_StringCopy(&(terminal->output_buffer), "V");
	terminal_SendNL(&(terminal->output_buffer));
}

void command_BatteryVoltageDivider(DCTERMINAL_t *terminal)
{
	if (terminal->command_option[0] == TERMINAL_SPACE) {
		int temp = atoi(terminal->command_option);
		if ((temp > 0) && (temp <= 100)) {
			terminal->state->battery_divider = temp;
			terminal->change_to_write = true;
		} else {
			terminal_SendBadArgument(&terminal->output_buffer);
		}
	}
	circular_buffer_StringCopy(&(terminal->output_buffer), "Battery voltage divider: ");
	char buffer [4];
	itoa(terminal->state->battery_divider, buffer, 10);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	terminal_SendNL(&(terminal->output_buffer));
}

void command_BatteryVoltageCut(DCTERMINAL_t *terminal)
{
	if (terminal->command_option[0] == TERMINAL_SPACE) {
		int temp = atoi(terminal->command_option);
		if ((temp > 0) && (temp <= 255)) {
			terminal->state->battery_cut = temp;
			terminal->change_to_write = true;
		} else {
			terminal_SendBadArgument(&terminal->output_buffer);
		}
	}
	circular_buffer_StringCopy(&(terminal->output_buffer), "Battery voltage cut level [A/D, volt]: ");
	char buffer [8];
	itoa(terminal->state->battery_cut, buffer, 10);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	circular_buffer_StringCopy(&(terminal->output_buffer), ", ");
	float volt_f = terminal->state->battery_cut;
	volt_f /= terminal->state->battery_divider;
	ftoa(volt_f, buffer, 8);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	circular_buffer_StringCopy(&(terminal->output_buffer), "V");
	terminal_SendNL(&(terminal->output_buffer));
}

void command_BatterySpeedLimit(DCTERMINAL_t *terminal)
{
	if (terminal->command_option[0] == TERMINAL_SPACE) {
		int temp = atoi(terminal->command_option);
		if ((temp >= 0) && (temp <= 255)) {
			terminal->state->speed_limit = temp;
			terminal->change_to_write = true;
		} else {
			terminal_SendBadArgument(&terminal->output_buffer);
		}
	}
	circular_buffer_StringCopy(&(terminal->output_buffer), "Speed limit at low battery voltage (0-255): ");
	char buffer [4];
	itoa(terminal->state->speed_limit, buffer, 10);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	terminal_SendNL(&(terminal->output_buffer));
}

void command_SpeedFilterCustom(DCTERMINAL_t *terminal)
{
	if (terminal->command_option[0] == TERMINAL_SPACE) {
		int temp = atoi(terminal->command_option);
		if ((temp > 2) && (temp <= 16)) {
			terminal->state->custom_filter_length = temp;
			terminal->change_to_write = true;
		} else {
			terminal_SendBadArgument(&terminal->output_buffer);
		}
	}
	circular_buffer_StringCopy(&(terminal->output_buffer), "Custom speed filter length (3-16): ");
	char buffer [4];
	itoa(terminal->state->custom_filter_length, buffer, 10);
	circular_buffer_StringCopy(&(terminal->output_buffer), buffer);
	terminal_SendNL(&(terminal->output_buffer));
}

void command_SendSystemInfo(DCTERMINAL_t *terminal)
{
	circular_buffer_StringCopy(&(terminal->output_buffer), terminal->state->device_info);
	terminal_SendNL(&(terminal->output_buffer));
}

void command_SendHelp(DCTERMINAL_t *terminal)
{
	for (int i = 0; i < COMMANDS_COUNT; i++) {
		circular_buffer_StringCopy(&(terminal->output_buffer), terminal_commands[i].pattern);
		terminal_SendNL(&(terminal->output_buffer));
	}
	terminal_SendNL(&(terminal->output_buffer));
}

void terminal_SendUnknown(CircularBuffer_t *output)
{
	circular_buffer_StringCopy(output, "? unknown command");
	terminal_SendNL(output);
}

void terminal_SendBadArgument(CircularBuffer_t *output)
{
	circular_buffer_StringCopy(output, "? bad argument");
	terminal_SendNL(output);
}

void terminal_SendOK(CircularBuffer_t *output)
{
	circular_buffer_StringCopy(output, "OK");
	terminal_SendNL(output);
}

void terminal_SendNL(CircularBuffer_t *output)
{
	circular_buffer_StringCopy(output, "\n\r");
}

void ftoa(float f, char *buffer, uint8_t length)
// in special cases an alternative to sprintf
{
	char *start = buffer;
	f += 0.05;
	int major = (int)f;
	itoa(major, start, 10);
	for (uint8_t i = 0; i < length; i++) {
		start++;
		if (*start == 0x00) break;
	}
	*(start++) = '.';
	int minor = (int)((f - major) * 10);
	itoa(minor, start, 10);
}

