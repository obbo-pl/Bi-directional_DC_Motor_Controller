/*
 * main.c
 *
 * Created: 12.08.2019 13:17:11
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 * AVR/GNU C Compiler : 4.8.1
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lowpass_filter.h"
#include "bitlib.h"
#include "uart_terminal.h"
#include "main.h"
#include "types.h"
#include "delays.h"

// resource:
// timer0 - common timers
// timer1 - checks the signal from the receiver
// timer2 - motor PWM
// ADC - checks battery voltage
// UART - serial communication (9600) for advanced configuration

// Program Memory Usage :	7550 bytes  92,2 % Full
// Data Memory Usage 	:	917 bytes   89,6 % Full
// EEPROM Memory Usage 	:	260 bytes   50,8 % Full


#define DEVICE_INFO_SIZE			40
const char DEVICE_INFO[DEVICE_INFO_SIZE]	PROGMEM = "DC (build: " __DATE__ " " __TIME__ ")";
char device_info[DEVICE_INFO_SIZE];

uint8_t EEMEM EEMEM_curve[256] = {0x00, 0x06, 0x0c, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13,
								0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x14, 0x14, 0x14, 0x14, 0x15, 0x15, 0x15, 0x15, 0x16, 0x16,
								0x16, 0x16, 0x17, 0x17, 0x17, 0x18, 0x18, 0x18, 0x19, 0x19, 0x19, 0x1a, 0x1a, 0x1b, 0x1b, 0x1b,
								0x1c, 0x1c, 0x1d, 0x1d, 0x1e, 0x1e, 0x1e, 0x1f, 0x1f, 0x20, 0x20, 0x21, 0x21, 0x22, 0x23, 0x23,
								0x24, 0x24, 0x25, 0x25, 0x26, 0x27, 0x27, 0x28, 0x28, 0x29, 0x2a, 0x2a, 0x2b, 0x2c, 0x2c, 0x2d,
								0x2e, 0x2e, 0x2f, 0x30, 0x30, 0x31, 0x32, 0x33, 0x33, 0x34, 0x35, 0x36, 0x37, 0x37, 0x38, 0x39,
								0x3a, 0x3b, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
								0x48, 0x49, 0x4a, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56,
								0x57, 0x58, 0x59, 0x5a, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x68,
								0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x77, 0x78, 0x79, 0x7a,
								0x7b, 0x7d, 0x7e, 0x7f, 0x80, 0x82, 0x83, 0x84, 0x85, 0x87, 0x88, 0x89, 0x8a, 0x8c, 0x8d, 0x8e,
								0x90, 0x91, 0x92, 0x93, 0x95, 0x96, 0x97, 0x99, 0x9a, 0x9b, 0x9d, 0x9e, 0x9f, 0xa1, 0xa2, 0xa3,
								0xa5, 0xa6, 0xa7, 0xa9, 0xaa, 0xac, 0xad, 0xae, 0xb0, 0xb1, 0xb2, 0xb4, 0xb5, 0xb7, 0xb8, 0xb9,
								0xbb, 0xbc, 0xbe, 0xbf, 0xc0, 0xc2, 0xc3, 0xc5, 0xc6, 0xc7, 0xc9, 0xca, 0xcc, 0xcd, 0xcf, 0xd0,
								0xd1, 0xd3, 0xd4, 0xd6, 0xd7, 0xd9, 0xda, 0xdc, 0xdd, 0xde, 0xe0, 0xe1, 0xe3, 0xe4, 0xe6, 0xe7,
								0xe9, 0xea, 0xec, 0xed, 0xee, 0xf0, 0xf1, 0xf3, 0xf4, 0xf6, 0xf7, 0xf9, 0xfa, 0xfc, 0xfd, 0xff
};
								
uint8_t curve[256];
uint8_t EEMEM EEMEM_battery_cut = 0xaa;
uint8_t EEMEM EEMEM_battery_divider = 0x12; 
uint8_t EEMEM EEMEM_custom_filter_length = 0x05;
uint8_t EEMEM EEMEM_speed_limit = 0x80;
 
uint8_t configuration_jumpers = 0x00;
bool motor_running_right = true;
bool motor_running_left = true;
LPFu16_t filter_speed;
LPFu16_t filter_adc;

uint8_t calibration_progres = 0;

DCCON_t state = {.errors = 0,
				 .rotation.speed = 0,
				 .rotation.dir = MOTOR_DIRECTION_RIGHT,
				 .channel_neutral = 0x0000,
				 .channel_maximum = 0x0000,
				 .channel_minimum = 0xffff,
				 .channel_move_maximum = 0,
				 .channel_move_minimum = 0,
				 .speed_max = SPEED_MAX,
				 .device_info = device_info,
};

DELAY_t timer_adc;
DELAY_t timer_signal_ms;
DELAY_t timer_recalc_ms;

DCTERMINAL_t terminal;


void main_InitTimers(void);
void main_InitPulseTimer(void);
void main_InitInfo(void);
void main_StartPulseTimer(void);
void main_StopPulseTimer(void);
uint16_t main_ReadPulseTimer(void);
bool main_IsPulseTimerOverload(void);
void main_InitMotorTimer(void);
void main_StartMotorTimer(void);
uint8_t main_ReadMotorTimer(void);
void main_InitCommonTimer(void);
void main_InitADC(void);
bool main_ReadADC(uint8_t *val);
void main_InitExpCurve(void);
bool main_CheckChannelInput(uint16_t *val, bool verify);
bool main_VerifyChannelValue(uint16_t *val);
void main_UpdateRecovery(int recovery_delay);
void main_CheckBattery(void);
void main_InitIO(void);
void main_FlashLedShort(void);
void main_FlashLedLong(void);
void main_SetLedOff(void);
void main_SetLedOn(void);
void main_ShowStatus(uint8_t status, uint8_t count);
void main_InitSetup(void);
void main_SetChannelConstants(void);
void main_SetMotorOnLeft(uint8_t *speed);
void main_SetMotorOnRight(uint8_t *speed);
void main_SetMotorOff(void);
void main_SetMotorToChangeDirection(uint8_t *speed);
void main_SetMotorSpeedPWM(DCROTATION_t *rotation);
bool main_IsMotorDirectionRight(uint8_t *direction);
bool main_IsMotorDirectionLeft(uint8_t *direction);
void main_ApplyReduceSpeed(uint8_t *speed);
uint32_t main_ApplyZoneNeutral(uint32_t pulse);
void main_ApplySpeedFilter(uint32_t *speed, uint16_t new_speed);
void main_ApplySpeedCurve(uint8_t *speed);
void main_RecalculateSpeed(DCROTATION_t *rotation, uint16_t pulse_length);
void main_ReadConfigurationJumper(void);
void main_SaveSetup(void);


int main(void) 
{
	main_InitIO();
	main_InitExpCurve();
	main_ReadConfigurationJumper();
	main_InitADC();
	main_InitSetup();
	main_InitInfo();
	uart_Init(&terminal, &state);
	delays_Init(&timer_signal_ms, SIGNAL_LOST_TIMEOUT_MS);
	delays_Pause(&timer_signal_ms);
	delays_Init(&timer_recalc_ms, RECALCULATE_INTERVAL_MS);
	delays_Pause(&timer_recalc_ms);
	delays_Init(&timer_adc, ADC_CONVERSION_TIMEOUT_MS);
	lpfilter_Set(&filter_adc, ADC_FILTER);
	lpFilter_Fill(&filter_adc, 0xff);
	main_InitTimers();
	main_FlashLedShort();
	_delay_ms(400);
	if (testbit(configuration_jumpers, JUMPER_SERVICE_MODE_bp)) {
		state.channel_neutral = CHANNEL_PULSE_NEUTRAL;
		state.channel_maximum = CHANNEL_PULSE_MAXIMUM + CHANNEL_PULSE_ZONE_NEUTRAL + CHANNEL_PULSE_ERROR;
		state.channel_minimum = CHANNEL_PULSE_MINIMUM - CHANNEL_PULSE_ZONE_NEUTRAL - CHANNEL_PULSE_ERROR;
		delays_Pause(&timer_adc);
		goto READY_TO_RUN;
	}
	main_CheckBattery();
	if (state.errors) {
		while (1) {
			main_ShowStatus(state.errors, 8);
			_delay_ms(3000);
		}
	}
	delays_Pause(&timer_adc);
	// wait for pulse from receiver
	uint8_t pulses = 0;
	while (pulses < (25)) {
		if (main_CheckChannelInput(&state.channel_value, false)) pulses += 1;
	}
	setbit(calibration_progres, CALIBRATION_SIGNAL_bp);
	main_ShowStatus(calibration_progres, 1);
	_delay_ms(1000);
	// wait for stable pulse in zone "neutral"
	pulses = 0;
	while (pulses < (25)) {
		if (main_CheckChannelInput(&state.channel_value, false)) {
			if ((state.channel_value > (CHANNEL_PULSE_NEUTRAL - CHANNEL_PULSE_ERROR)) 
				&& (state.channel_value < (CHANNEL_PULSE_NEUTRAL + CHANNEL_PULSE_ERROR))) {
				pulses += 1;
			} else {
				pulses = 0;
			}
		}
	}
	// measure length of "neutral" position
	pulses = 0;
	while (pulses < (16)) {
		if (main_CheckChannelInput(&state.channel_value, false)) {
			if ((state.channel_value > (CHANNEL_PULSE_NEUTRAL - CHANNEL_PULSE_ERROR)) 
				&& (state.channel_value < (CHANNEL_PULSE_NEUTRAL + CHANNEL_PULSE_ERROR))) {
				pulses += 1;
				state.channel_neutral += state.channel_value;
			} else {
				pulses = 0;
				state.channel_neutral = 0;
			}
		}
	}
	state.channel_neutral = state.channel_neutral >> 4;
	setbit(calibration_progres, CALIBRATION_NEUTRAL_bp);
	main_ShowStatus(calibration_progres, 2);
	// wait for stable pulse in zone "maximum" and measure maximum pulse length 
	pulses = 0;
	while (pulses < (25)) {
		if (main_CheckChannelInput(&state.channel_value, false)) {
			if (state.channel_value > CHANNEL_PULSE_MAXIMUM) {
				pulses += 1;
				if (state.channel_value > state.channel_maximum) state.channel_maximum = state.channel_value;
			} else {
				pulses = 0;
				state.channel_maximum = 0x0000;
			}
		}
	}
	setbit(calibration_progres, CALIBRATION_MAXIMUM_bp);
	main_ShowStatus(calibration_progres, 3);
	// wait for stable pulse in zone "minimum" and measure minimum pulse length
	pulses = 0;
	while (pulses < (25)) { 
		if (main_CheckChannelInput(&state.channel_value, false)) {
			if (state.channel_value < CHANNEL_PULSE_MINIMUM) {
				pulses += 1;
				if (state.channel_value < state.channel_minimum) state.channel_minimum = state.channel_value;
			} else {
				pulses = 0;
				state.channel_minimum = 0xffff;
			}
		}
	}
	setbit(calibration_progres, CALIBRATION_MINIMUM_bp);
	main_ShowStatus(calibration_progres, 4);
	// wait for return to zone "neutral"
	pulses = 0;
	while (pulses < (25)) {
		if (main_CheckChannelInput(&state.channel_value, false)) {
			if ((state.channel_value > (state.channel_neutral - CHANNEL_PULSE_ZONE_NEUTRAL)) 
				&& (state.channel_value < (state.channel_neutral + CHANNEL_PULSE_ZONE_NEUTRAL))) {
				pulses += 1;
			} else {
				pulses = 0;
			}
		}
	}
	setbit(calibration_progres, CALIBRATION_READY_bp);
READY_TO_RUN:
	if (testbit(configuration_jumpers, JUMPER_SPEED_FILTER_bp)) {
		lpfilter_Set(&filter_speed, state.custom_filter_length);
	} else {
		lpfilter_Set(&filter_speed, SPEED_FILTER_DEFAULT); 
	}
	state.rotation.speed = 0;
	main_StartMotorTimer();
	main_SetChannelConstants();	
	lpFilter_Fill(&filter_speed, state.channel_neutral_x2);
	delays_Reset(&timer_signal_ms);
	delays_Reset(&timer_recalc_ms);
	main_SetLedOn();
	sei();
	uint8_t command_length;
    while (1) {
		// check signal
		main_CheckChannelInput(&(state.channel_value), true);
		// fail-safe
		if (delays_Check(&timer_signal_ms) || (state.recovery > 0)) {
 			setbit(state.errors, ERROR_CHANNEL_LOST_bp);
			state.channel_value = state.channel_neutral;
		}
		// convert pulse length to rotation
		if (delays_Check(&timer_recalc_ms)) {
			main_RecalculateSpeed(&state.rotation, state.channel_value);
			delays_Reset(&timer_recalc_ms);
		}
		// check terminal buffer
		uart_SendOutputBuffer(&(terminal.output_buffer));
		if (terminal.change_to_write) main_SaveSetup();
		if (terminal.input_is_full) uart_DropInputBuffer(&terminal);
		if (terminal_FindNewLine(&terminal, &command_length)) terminal_ParseCommand(&terminal, command_length);
		// set rotation
		main_SetMotorSpeedPWM(&state.rotation);
		// check state
		if (delays_Check(&timer_adc)) setbit(state.errors, ERROR_ADC_TIMEOUT_bp);
	    main_CheckBattery();
    }
}

ISR(USART_RXC_vect)
{
	uart_InterruptHandler(&terminal);
}

ISR(TIMER0_OVF_vect)
{
	delays_Update(&timer_signal_ms, TIMER_COMMON_OVF_MS);
	delays_Update(&timer_recalc_ms, TIMER_COMMON_OVF_MS);
	delays_Update(&timer_adc, TIMER_COMMON_OVF_MS);
}

void main_InitIO(void)
{
	OUT_STATUS_LED;
	CLR_STATUS_LED;

	PULL_CFG1;
	PULL_CFG2;
	PULL_CFG3;

	CLR_DIR_L;
	OUT_DIR_L;
	CLR_DIR_R;
	OUT_DIR_R;
	CLR_PULS_L;
	OUT_PULS_L;
	CLR_PULS_R;
	OUT_PULS_R;

	PULL_CHANNEL1;
}

void main_InitSetup(void)
{
	state.battery_cut = eeprom_read_byte(&EEMEM_battery_cut);
	state.battery_divider = eeprom_read_byte(&EEMEM_battery_divider);
	state.custom_filter_length = eeprom_read_byte(&EEMEM_custom_filter_length);
	state.speed_limit = eeprom_read_byte(&EEMEM_speed_limit);
}

void main_InitInfo(void)
{
	char *dest = device_info;
	const char *src = DEVICE_INFO;
	for (int i = 0; i < DEVICE_INFO_SIZE; i++) {
		*dest++ = (char)pgm_read_byte(src++);
	}
}

void main_InitTimers(void)
{
	main_InitPulseTimer();
	main_InitMotorTimer();
	main_InitCommonTimer();
}

void main_InitPulseTimer(void)
{
	// Timer1 (16-bit)
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
	TIFR |= (1 << TOV1);
}

void main_StartPulseTimer(void)
{
	TCNT1H = 0;
	TCNT1L = 0;
	TIFR |= (1 << TOV1);
	TCCR1B |= (1 << CS11) | (1 << CS10);
}

void main_StopPulseTimer(void)
{
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}

uint16_t main_ReadPulseTimer(void)
{
	uint16_t result;
	unsigned char sreg;
	sreg = SREG;
	cli();
	result = TCNT1;
	SREG = sreg;
	sei();
	return result;
}

bool main_IsPulseTimerOverload(void)
{
	return (TIFR >> TOV1) & 0x01;
}

void main_InitMotorTimer(void)
{
	// Timer2 (8-bit)
	TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
	TIFR |= (1 << TOV2) | (1 << OCF2);
}

void main_StartMotorTimer(void)
{
 	TCNT2 = 0;
 	TCCR2 |= (1 << CS22);
}

uint8_t main_ReadMotorTimer(void)
{
	return TCNT2;
}

void main_InitCommonTimer(void)
{
	TIMSK |= (1 << TOIE0);
	TCCR0 = (1 << CS02);
}

void main_InitADC(void)
{
	ADMUX = (1 << REFS0) | (1 << REFS1);					// Internal 2.56V Voltage Reference with external capacitor at AREF pin
	ADMUX |= CONFIG_BAT_PORTC_PIN;
	ADMUX |= (1 << ADLAR);									// ADC Left Adjust Result
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	// ADC Prescaler Select Bits, /128
	ADCSRA |= (1 << ADFR);									// ADC Free Running Select
	ADCSRA |= (1 << ADEN);									// ADC Enable
	ADCSRA |= (1 << ADSC);									// ADC Start Conversion
}

 bool main_ReadADC(uint8_t *val)
{
	bool result = false;
	if ((ADCSRA >> ADIF) & 0x01) {
		*val = ADCH;
		ADCSRA |= (1 << ADIF);
		result = true;
	}
	return result; 
}

bool main_CheckChannelInput(uint16_t *val, bool verify)
{
	// check the channel pulse length, it should be between 1ms and 2ms 
	// timer prescaler is set to 4us per tick
	// then should count from 250 to 500 tick per pulse
	// returns "true" and updates "value" when a new pulse occurs
	bool changed = false;
	uint8_t channel_level = READ_CHANNEL1;
	if (state.channel_level_prev != channel_level) {
		if (channel_level == CHANNEL_LEVEL_ACTIVE) {
		    main_StartPulseTimer();
		} else {
			main_StopPulseTimer();
			if (main_IsPulseTimerOverload()) {
				setbit(state.errors, ERROR_TIMER_OVERLOAD_bp);
				state.channel_last = 0xffff;
				main_UpdateRecovery(RECOVERY_DELAY_PL);
   			} else {
				state.channel_last = main_ReadPulseTimer();
				if (main_VerifyChannelValue(&(state.channel_last)) || !verify) {
					*val = state.channel_last;
					main_UpdateRecovery(-1);
					delays_Reset(&timer_signal_ms);
					changed = true;
				} else {
					setbit(state.errors, ERROR_CHANNEL_OVERRANGE_bp);
					main_UpdateRecovery(RECOVERY_DELAY_PL);
				}
			}
	    }
		state.channel_level_prev = channel_level;
    }
	return changed;
}

bool main_VerifyChannelValue(uint16_t *val)
{
	if ((*val < (state.channel_maximum + CHANNEL_PULSE_ERROR)) && (*val > (state.channel_minimum - CHANNEL_PULSE_ERROR))) return true;
	else return false;
}

void main_UpdateRecovery(int recovery)
{
	if (recovery < 0) {
		if (state.recovery > -(ACCEPTED_ERRORS * RECOVERY_DELAY_PL)) state.recovery += recovery;
	} else {
		if (state.recovery < RECOVERY_DELAY_PL) state.recovery += recovery;
	}
}

void main_CheckBattery(void)
{
	uint8_t bat;
	if (main_ReadADC(&bat)) {
		delays_Reset(&timer_adc);
		state.battery_voltage = lpfilter_Filter(&filter_adc, bat);
		if (state.battery_voltage < state.battery_cut) {
			state.speed_max = state.speed_limit;
			setbit(state.errors, ERROR_BATTERY_LOW_bp);
		}
	}
}

void main_SetLedOff(void)
{
	CLR_STATUS_LED;
}

void main_SetLedOn(void)
{
	SET_STATUS_LED;
};
	
void main_FlashLedShort(void)
{
	main_SetLedOn();
	_delay_ms(60);
	main_SetLedOff();
	_delay_ms(500);
}

void main_FlashLedLong(void)
{
	main_SetLedOn();
	_delay_ms(500);
	main_SetLedOff();
	_delay_ms(500);
}

void main_ShowStatus(uint8_t status, uint8_t count)
{
	if ((count == 0) || (count > 8)) count = 8;
	for (int i = 0; i < count; i++) {
		if ((status >> i) & 0x01) {
			main_FlashLedLong();
		} else {
			main_FlashLedShort();
		}
	}
}

void main_SetMotorOnLeft(uint8_t *speed)
{
	if (motor_running_right) {
		main_SetMotorToChangeDirection(speed);
		return;
	}
	motor_running_left = true;
	CLR_DIR_R;
	CLR_PULS_R;
	SET_DIR_L;
	SET_PULS_L;
}

void main_SetMotorOnRight(uint8_t *speed)
{
	if (motor_running_left) {
		main_SetMotorToChangeDirection(speed);
		return;
	}
	motor_running_right = true;
	CLR_DIR_L;
	CLR_PULS_L;
	SET_DIR_R;
	SET_PULS_R;
}

void main_SetMotorToChangeDirection(uint8_t *speed)
{
	motor_running_left = false;
	motor_running_right = false;
	main_SetMotorOff();
	*speed = 0;
}

void main_SetMotorOff(void)
{
	CLR_PULS_L;
	CLR_PULS_R;
	CLR_DIR_L; 
	CLR_DIR_R;
}

void main_SetMotorSpeedPWM(DCROTATION_t *rotation)
{
	// prevent fast direction change
 	if (main_IsMotorDirectionRight(&((*rotation).dir)) && motor_running_left) {
		main_SetMotorToChangeDirection(&((*rotation).speed));
		return;
	}
	if (main_IsMotorDirectionLeft(&((*rotation).dir)) && motor_running_right) {
		main_SetMotorToChangeDirection(&((*rotation).speed));
		return;
	}
	// reduce power consumption
	main_ApplyReduceSpeed(&((*rotation).speed));
	// set bridge I/O
	if ((main_ReadMotorTimer() <= (*rotation).speed) && ((*rotation).speed > 0)) {
		if (main_IsMotorDirectionRight(&((*rotation).dir))) {
			main_SetMotorOnRight(&((*rotation).speed));
		} else {
 			main_SetMotorOnLeft(&((*rotation).speed));
		}
	} else {
		main_SetMotorOff();
	}
}

bool main_IsMotorDirectionRight(uint8_t *direction)
{
	if ((*direction && 0x01) == MOTOR_DIRECTION_RIGHT) return true;
	return false;
}

bool main_IsMotorDirectionLeft(uint8_t *direction)
{
	if ((*direction && 0x01) == MOTOR_DIRECTION_LEFT) return true;
	return false;
}

void main_ApplyReduceSpeed(uint8_t *speed)
{
	if (*speed >= state.speed_max) *speed = state.speed_max;
}

void main_ApplySpeedFilter(uint32_t *speed, uint16_t new_speed)
{
	*speed = 0x0000ffff & lpfilter_Filter(&filter_speed, new_speed);
}

void main_ApplySpeedCurve(uint8_t *speed)
{
	*speed = curve[*speed];
}

void main_SetChannelConstants(void)
{
	state.channel_move_maximum = state.channel_maximum - state.channel_neutral - CHANNEL_PULSE_ZONE_NEUTRAL - CHANNEL_PULSE_ZONE_EXTREMUM;
	state.channel_move_minimum = state.channel_neutral - state.channel_minimum - CHANNEL_PULSE_ZONE_NEUTRAL - CHANNEL_PULSE_ZONE_EXTREMUM;
	state.channel_neutral_x2 = state.channel_neutral << 1;
	state.zone_neutral = CHANNEL_PULSE_ZONE_NEUTRAL;
	state.zone_neutral = (state.zone_neutral * 0x1fe) / (state.channel_maximum - state.channel_minimum);
	state.zone_neutral = (state.zone_neutral * (state.channel_maximum - state.channel_minimum)) / (state.channel_move_minimum + state.channel_move_maximum);

}

void main_RecalculateSpeed(DCROTATION_t *rotation, uint16_t pulse_length)
{
	uint32_t pulse_filtered;
	// apply filter, 
	// for greater accuracy, filter works on double value of pulse length
	main_ApplySpeedFilter(&pulse_filtered, (pulse_length << 1));
	// convert pulse length to motor direction and speed
	if (pulse_filtered > state.channel_neutral_x2) {
		(*rotation).dir = MOTOR_DIRECTION_RIGHT;
		pulse_filtered = pulse_filtered - state.channel_neutral_x2;
		pulse_filtered = (pulse_filtered << 8) / state.channel_move_maximum;
	} else {
		(*rotation).dir = MOTOR_DIRECTION_LEFT;
		pulse_filtered = state.channel_neutral_x2 - pulse_filtered;
		pulse_filtered = (pulse_filtered << 8) / state.channel_move_minimum;
	}
	pulse_filtered = pulse_filtered >> 1;
	pulse_filtered = main_ApplyZoneNeutral(pulse_filtered);
	if (pulse_filtered > SPEED_MAX) pulse_filtered = SPEED_MAX;
	uint8_t result = (uint8_t)pulse_filtered;
	// apply curve
	if (testbit(configuration_jumpers, JUMPER_SPEED_CURVE_bp)) {
		main_ApplySpeedCurve(&result);
	}
	(*rotation).speed = result;
}

uint32_t main_ApplyZoneNeutral(uint32_t pulse)
{
	if (pulse > state.zone_neutral) {
		return (pulse - state.zone_neutral);
	} else {
		return 0;
	}
}

void main_InitExpCurve(void)
{
	uint8_t i = 0;
	do {
		curve[i] = eeprom_read_byte(&EEMEM_curve[i]);
		i++;
	} while (i);
}

void main_ReadConfigurationJumper(void)
{
	if (!(READ_CFG1)) setbit(configuration_jumpers, JUMPER_SPEED_FILTER_bp);
	if (!(READ_CFG2)) setbit(configuration_jumpers, JUMPER_SPEED_CURVE_bp);
	if (!(READ_CFG3)) setbit(configuration_jumpers, JUMPER_SERVICE_MODE_bp);
}

void main_SaveSetup(void)
{
	terminal.change_to_write = false;
	eeprom_write_byte(&EEMEM_battery_cut, state.battery_cut);
	eeprom_write_byte(&EEMEM_battery_divider, state.battery_divider);
	eeprom_write_byte(&EEMEM_custom_filter_length, state.custom_filter_length);
	eeprom_write_byte(&EEMEM_speed_limit, state.speed_limit);

}