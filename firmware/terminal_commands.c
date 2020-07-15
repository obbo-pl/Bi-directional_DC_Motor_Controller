/*
 * terminal_commands.cpp
 *
 * Created: 2020-06-15 19:33:07
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 * AVR/GNU C Compiler : 4.8.1
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 

#include <stdlib.h>
#include <avr/eeprom.h>
#include "terminal_commands.h"
#include "adconversion.h"



void ftoa(float f, char *buffer, uint8_t length);
void command_SystemVersion(DCTERMINAL_t *terminal);
void command_ShowErrors(DCTERMINAL_t *terminal);
void command_ClearErrors(DCTERMINAL_t *terminal);
void command_SetModeSilent(DCTERMINAL_t *terminal);
void command_ShowChannelValue(DCTERMINAL_t *terminal);
void command_ShowChannelLast(DCTERMINAL_t *terminal);
void command_ShowChannelRange(DCTERMINAL_t *terminal);
void command_BatteryVoltageValue(DCTERMINAL_t *terminal);
void command_BatteryVoltageDivider(DCTERMINAL_t *terminal);
void command_BatteryVoltageCut(DCTERMINAL_t *terminal);
void command_BatterySpeedLimit(DCTERMINAL_t *terminal);
void command_SpeedFilterCustom(DCTERMINAL_t *terminal);

#define TERMINAL_BASE_COMMANDS_COUNT		12

#define TERMINAL_COMMANDS_COUNT			(TERMINAL_BASE_COMMANDS_COUNT)

TERMINAL_COMMAND_t cabell_commands[TERMINAL_COMMANDS_COUNT] = {
	{ .pattern = "@VER", .callback = command_SystemVersion,},
	{ .pattern = "@ERR", .callback = command_ShowErrors,},
	{ .pattern = "@ERC", .callback = command_ClearErrors,},
	{ .pattern = "@MDS", .callback = command_SetModeSilent,},
	{ .pattern = "@CHV", .callback = command_ShowChannelValue,},
	{ .pattern = "@CHL", .callback = command_ShowChannelLast,},
	{ .pattern = "@CHR", .callback = command_ShowChannelRange,},
	{ .pattern = "@BVV", .callback = command_BatteryVoltageValue,},
	{ .pattern = "@BVD", .callback = command_BatteryVoltageDivider,},
	{ .pattern = "@BVC", .callback = command_BatteryVoltageCut,},
	{ .pattern = "@BSL", .callback = command_BatterySpeedLimit,},
	{ .pattern = "@SFC", .callback = command_SpeedFilterCustom,},
};

DCCON_t *dc_state;
bool silent = false;

const char EEMEM eeprom_terminal_message_001[] = "Battery voltage [A/D, volt]: ";
const char EEMEM eeprom_terminal_message_002[] = "Battery voltage divider: ";
const char EEMEM eeprom_terminal_message_003[] = "Errors: ";
const char EEMEM eeprom_terminal_message_004[] = "Current channel value [tick]: ";
const char EEMEM eeprom_terminal_message_005[] = "Last pulse length [tick]: ";
const char EEMEM eeprom_terminal_message_006[] = "Calibrated pulse length [tick]: ";
const char EEMEM eeprom_terminal_message_007[] = "Battery voltage cut level [A/D, volt]: ";



void terminal_commands_Init(DCCON_t *state)
{
	terminal_BindCommands(cabell_commands, TERMINAL_COMMANDS_COUNT);
	dc_state = state;
}


// in special cases an alternative to sprintf
void ftoa(float f, char *buffer, uint8_t length)
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

void command_SystemVersion(DCTERMINAL_t *terminal)
{
	cbuffer_AppendPMString(terminal->output_buffer, dc_state->device_info);
}

void command_BatteryVoltageValue(DCTERMINAL_t *terminal)
{
	if (!silent) cbuffer_AppendEEString(terminal->output_buffer, eeprom_terminal_message_001);
	char buffer[8];
	itoa(dc_state->battery_voltage, buffer, 10);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	cbuffer_AppendString(terminal->output_buffer, ", ");
	float volt_f = dc_state->battery_voltage;
	volt_f /= dc_state->battery_divider;
	ftoa(volt_f, buffer, 8);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	cbuffer_AppendString(terminal->output_buffer, "V");
	terminal_SendNL(terminal->output_buffer, false);
}

void command_BatteryVoltageDivider(DCTERMINAL_t *terminal)
{
	if (terminal->command_option[0] == TERMINAL_SPACE) {
		int temp = atoi(terminal->command_option);
		if ((temp > 0) && (temp <= 100)) {
			dc_state->battery_divider = temp;
			terminal->change_to_write = true;
			} else {
			terminal_SendBadArgument(terminal->output_buffer);
		}
	}
	cbuffer_AppendEEString(terminal->output_buffer, eeprom_terminal_message_002);
	char buffer [4];
	itoa(dc_state->battery_divider, buffer, 10);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	terminal_SendNL(terminal->output_buffer, false);
}

void command_ShowErrors(DCTERMINAL_t *terminal)
{
	if (!silent) cbuffer_AppendEEString(terminal->output_buffer, eeprom_terminal_message_003);
	char buffer [10];
	int i = 0x80;
	while (i > dc_state->errors)  {
		i = i >> 1;
		cbuffer_AppendString(terminal->output_buffer, "0");
	}
	if (dc_state->errors > 0) {
		itoa(dc_state->errors, buffer, 2);
		cbuffer_AppendString(terminal->output_buffer, buffer);
	}
	terminal_SendNL(terminal->output_buffer, false);
}

void command_ClearErrors(DCTERMINAL_t *terminal)
{
	dc_state->errors = 0x00;
	if (!silent) terminal_SendOK(terminal->output_buffer);
}

void command_SetModeSilent(DCTERMINAL_t *terminal)
{
	silent = !(silent);
	if (silent) terminal_SendNL(terminal->output_buffer, false);
	else terminal_SendOK(terminal->output_buffer);
}

void command_ShowChannelValue(DCTERMINAL_t *terminal)
{
	if (!silent) cbuffer_AppendEEString(terminal->output_buffer, eeprom_terminal_message_004);
	char buffer [6];
	itoa(dc_state->channel_value, buffer, 10);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	terminal_SendNL(terminal->output_buffer, false);
}

void command_ShowChannelLast(DCTERMINAL_t *terminal)
{
	if (!silent) cbuffer_AppendEEString(terminal->output_buffer, eeprom_terminal_message_005);
	char buffer [6];
	itoa(dc_state->channel_last, buffer, 10);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	terminal_SendNL(terminal->output_buffer, false);
}

void command_ShowChannelRange(DCTERMINAL_t *terminal)
{
	if (!silent) cbuffer_AppendEEString(terminal->output_buffer, eeprom_terminal_message_006);
	char buffer [6];
	itoa(dc_state->channel_minimum, buffer, 10);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	cbuffer_AppendString(terminal->output_buffer, ", ");
	itoa(dc_state->channel_neutral, buffer, 10);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	cbuffer_AppendString(terminal->output_buffer, ", ");
	itoa(dc_state->channel_maximum, buffer, 10);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	terminal_SendNL(terminal->output_buffer, false);
}

void command_BatteryVoltageCut(DCTERMINAL_t *terminal)
{
	if (terminal->command_option[0] == TERMINAL_SPACE) {
		int temp = atoi(terminal->command_option);
#ifdef ADCONVERSION_8_BIT_PRECISION
		if ((temp > 0) && (temp <= 255)) {
#else
		if ((temp > 0) && (temp <= 1023)) {
#endif
			dc_state->battery_cut = temp;
			terminal->change_to_write = true;
		} else {
			terminal_SendBadArgument(terminal->output_buffer);
		}
	}
	if (!silent) cbuffer_AppendEEString(terminal->output_buffer, eeprom_terminal_message_007);
	char buffer [8];
	itoa(dc_state->battery_cut, buffer, 10);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	cbuffer_AppendString(terminal->output_buffer, ", ");
	float volt_f = dc_state->battery_cut;
	volt_f /= dc_state->battery_divider;
	ftoa(volt_f, buffer, 8);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	cbuffer_AppendString(terminal->output_buffer, "V");
	terminal_SendNL(terminal->output_buffer, false);
}

void command_BatterySpeedLimit(DCTERMINAL_t *terminal)
{
	if (terminal->command_option[0] == TERMINAL_SPACE) {
		int temp = atoi(terminal->command_option);
		if ((temp >= 0) && (temp <= 255)) {
			dc_state->speed_limit = temp;
			terminal->change_to_write = true;
		} else {
			terminal_SendBadArgument(terminal->output_buffer);
		}
	}
	if (!silent) cbuffer_AppendString(terminal->output_buffer, "Speed limit at low battery voltage (0-255): ");
	char buffer [4];
	itoa(dc_state->speed_limit, buffer, 10);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	terminal_SendNL(terminal->output_buffer, false);
}

void command_SpeedFilterCustom(DCTERMINAL_t *terminal)
{
	if (terminal->command_option[0] == TERMINAL_SPACE) {
		int temp = atoi(terminal->command_option);
		if ((temp >= 2) && (temp <= 10)) {
			dc_state->custom_filter_length = temp;
			terminal->change_to_write = true;
			} else {
			terminal_SendBadArgument(terminal->output_buffer);
		}
	}
	if (!silent) cbuffer_AppendString(terminal->output_buffer, "Custom speed filter length (2-10): ");
	char buffer [4];
	itoa(dc_state->custom_filter_length, buffer, 10);
	cbuffer_AppendString(terminal->output_buffer, buffer);
	terminal_SendNL(terminal->output_buffer, false);
}


