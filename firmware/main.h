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



#define TIMER_COMMON_OVF_MS			(4)
#define RECALCULATE_INTERVAL_MS			(20)
#define SIGNAL_LOST_TIMEOUT_MS			(500)
#define ADC_CONVERSION_TIMEOUT_MS		(1000)
#define ADC_FILTER				(3)

#define RECOVERY_DELAY_PL			(50)
#define ACCEPTED_ERRORS				(2)
#if (RECOVERY_DELAY_PL * ACCEPTED_ERRORS) >= 32767
#error "Decrease RECOVERY_DELAY_PL or ACCEPTED_ERRORS" 
#endif

#define SPEED_MAX				(0xff)
#define SPEED_FILTER_DEFAULT			(2)
#define MOTOR_DIRECTION_RIGHT			(1)
#define MOTOR_DIRECTION_LEFT			(0)

// Sanwa VG6DR
#define CHANNEL_PULSE_NEUTRAL			(365)
#define CHANNEL_PULSE_MAXIMUM			(440)
#define CHANNEL_PULSE_MINIMUM			(290)
#define CHANNEL_PULSE_ZONE_NEUTRAL		(10)
#define CHANNEL_PULSE_ZONE_EXTREMUM		(5)
#define CHANNEL_PULSE_ZONE_BRAKE		(6)
#define CHANNEL_PULSE_ERROR			(20)
#define CHANNEL_PULSE_POSITIVE

#ifdef CHANNEL_PULSE_POSITIVE
	#define CHANNEL_LEVEL_ACTIVE		(1)
#else
	#define CHANNEL_LEVEL_ACTIVE		(0)
#endif


enum {
	JUMPER_P1_SPEED_FILTER_bp,
	JUMPER_P2_SPEED_CURVE_bp,
	JUMPER_P3_SERVICE_MODE_bp
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