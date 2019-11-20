/*
 * main.h
 *
 * Created: 12.08.2019 13:27:43
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 * AVR/GNU C Compiler : 4.8.1
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include "config.h"
#include "macro.h"


// STATUS LED port
#define OUT_STATUS_LED				(glue2(DDR, CONFIG_LED_PORT) |= (1 << glue3(DD, CONFIG_LED_PORT, CONFIG_LED_PIN)))
#define SET_STATUS_LED				(glue2(PORT, CONFIG_LED_PORT) |= (1 << glue3(P, CONFIG_LED_PORT, CONFIG_LED_PIN)))
#define CLR_STATUS_LED				(glue2(PORT, CONFIG_LED_PORT) &= ~(1 << glue3(P, CONFIG_LED_PORT, CONFIG_LED_PIN)))


// I/O port for motor bridge
#define OUT_DIR_L					(glue2(DDR, CONFIG_DIR_L_PORT) |= (1 << glue3(DD, CONFIG_DIR_L_PORT, CONFIG_DIR_L_PIN)))
#define SET_DIR_L					(glue2(PORT, CONFIG_DIR_L_PORT) |= (1 << glue3(P, CONFIG_DIR_L_PORT, CONFIG_DIR_L_PIN)))
#define CLR_DIR_L					(glue2(PORT, CONFIG_DIR_L_PORT) &= ~(1 << glue3(P, CONFIG_DIR_L_PORT, CONFIG_DIR_L_PIN)))

#define OUT_PULS_L					(glue2(DDR, CONFIG_PULS_L_PORT) |= (1 << glue3(DD, CONFIG_PULS_L_PORT, CONFIG_PULS_L_PIN)))
#define SET_PULS_L					(glue2(PORT, CONFIG_PULS_L_PORT) |= (1 << glue3(P, CONFIG_PULS_L_PORT, CONFIG_PULS_L_PIN)))
#define CLR_PULS_L					(glue2(PORT, CONFIG_PULS_L_PORT) &= ~(1 << glue3(P, CONFIG_PULS_L_PORT, CONFIG_PULS_L_PIN)))

#define OUT_DIR_R					(glue2(DDR, CONFIG_DIR_R_PORT) |= (1 << glue3(DD, CONFIG_DIR_R_PORT, CONFIG_DIR_R_PIN)))
#define SET_DIR_R					(glue2(PORT, CONFIG_DIR_R_PORT) |= (1 << glue3(P, CONFIG_DIR_R_PORT, CONFIG_DIR_R_PIN)))
#define CLR_DIR_R					(glue2(PORT, CONFIG_DIR_R_PORT) &= ~(1 << glue3(P, CONFIG_DIR_R_PORT, CONFIG_DIR_R_PIN)))

#define OUT_PULS_R					(glue2(DDR, CONFIG_PULS_R_PORT) |= (1 << glue3(DD, CONFIG_PULS_R_PORT, CONFIG_PULS_R_PIN)))
#define SET_PULS_R					(glue2(PORT, CONFIG_PULS_R_PORT) |= (1 << glue3(P, CONFIG_PULS_R_PORT, CONFIG_PULS_R_PIN)))
#define CLR_PULS_R					(glue2(PORT, CONFIG_PULS_R_PORT) &= ~(1 << glue3(P, CONFIG_PULS_R_PORT, CONFIG_PULS_R_PIN)))


// Configuration pinhead (CFG1 - CFG3)
#define PULL_CFG1					(glue2(PORT, CONFIG_CFG1_PORT) |= (1 << glue3(P, CONFIG_CFG1_PORT, CONFIG_CFG1_PIN)))
#define READ_CFG1					((glue2(PIN, CONFIG_CFG1_PORT) >> glue3(P, CONFIG_CFG1_PORT, CONFIG_CFG1_PIN)) & 0x01)

#define PULL_CFG2					(glue2(PORT, CONFIG_CFG2_PORT) |= (1 << glue3(P, CONFIG_CFG2_PORT, CONFIG_CFG2_PIN)))
#define READ_CFG2					((glue2(PIN, CONFIG_CFG2_PORT) >> glue3(P, CONFIG_CFG2_PORT, CONFIG_CFG2_PIN)) & 0x01)

#define PULL_CFG3					(glue2(PORT, CONFIG_CFG3_PORT) |= (1 << glue3(P, CONFIG_CFG3_PORT, CONFIG_CFG3_PIN)))
#define READ_CFG3					((glue2(PIN, CONFIG_CFG3_PORT) >> glue3(P, CONFIG_CFG3_PORT, CONFIG_CFG3_PIN)) & 0x01)


// Channel signal (CH1)
#define PULL_CHANNEL1				(glue2(PORT, CONFIG_CH1_PORT) |= (1 << glue3(P, CONFIG_CH1_PORT, CONFIG_CH1_PIN)))
#define READ_CHANNEL1				((glue2(PIN, CONFIG_CH1_PORT) >> glue3(P, CONFIG_CH1_PORT, CONFIG_CH1_PIN)) & 0x01)

#define TIMER_COMMON_OVF_MS			(4)
#define RECALCULATE_INTERVAL_MS		(20)
#define SIGNAL_LOST_TIMEOUT_MS		(500)
#define ADC_CONVERSION_TIMEOUT_MS	(1000)
#define ADC_FILTER					(3)

#define RECOVERY_DELAY_PL			(50)
#define ACCEPTED_ERRORS_RV			(2)
#if (RECOVERY_DELAY_PL * ACCEPTED_ERRORS) >= 32767
#error "Decrease RECOVERY_DELAY_PL or ACCEPTED_ERRORS" 
#endif

#define SPEED_MAX					(0xff)
#define SPEED_FILTER_DEFAULT		(2)
#define MOTOR_DIRECTION_RIGHT		(1)
#define MOTOR_DIRECTION_LEFT		(0)

// Sanwa VG6DR
#define CHANNEL_PULSE_NEUTRAL		(360)
#define CHANNEL_PULSE_MAXIMUM		(430)
#define CHANNEL_PULSE_MINIMUM		(290)
#define CHANNEL_PULSE_ZONE_NEUTRAL	(10)
#define CHANNEL_PULSE_ZONE_EXTREMUM (5)
#define CHANNEL_PULSE_ERROR			(10)
#define CHANNEL_PULSE_POSITIVE

#ifdef CHANNEL_PULSE_POSITIVE
	#define CHANNEL_LEVEL_ACTIVE	(1)
#else
	#define CHANNEL_LEVEL_ACTIVE	(0)
#endif


enum {
	JUMPER_SPEED_FILTER_bp,
	JUMPER_SPEED_CURVE_bp,
	JUMPER_SERVICE_MODE_bp
};

enum {
	ERROR_BATTERY_LOW_bp,
	ERROR_ADC_TIMEOUT_bp,
	ERROR_TIMER_OVERLOAD_bp,
	ERROR_CHANNEL_OVERRANGE_bp,
	ERROR_CHANNEL_LOST_bp
};

enum {
	CALIBRATION_SIGNAL_bp,
	CALIBRATION_NEUTRAL_bp,
	CALIBRATION_MAXIMUM_bp,
	CALIBRATION_MINIMUM_bp,
	CALIBRATION_READY_bp
};


#endif /* MAIN_H_ */