/*
 * bridge.c
 *
 * Created: 2020-07-20 20:25:42
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 * AVR/GNU C Compiler : 4.8.1
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 

#include "bridge.h"
#include "config.h"
#include "macro.h"


void bridge_SetMotorOnLeft(void);
void bridge_SetMotorOnRight(void);
void bridge_SetMotorOff(void);
void bridge_SetMotorBrake(void);

#define BRIDGE_PULSE_MIN_LENGTH		3
#define BRIDGE_PULSE_MAX_LENGTH		(0xff - BRIDGE_PULSE_MIN_LENGTH)

enum {
	BRIDGE_PULSE_BASE,
	BRIDGE_PULSE_PAUSE
};

uint8_t motor_running_direction = BRIDGE_DIRECTION_UNKNOWN;
uint8_t phase = BRIDGE_PULSE_BASE;
uint8_t pause;


void bridge_Init(BRIDGE_t *rotation)
{
	SET_PIN_LEVEL_LOW(CONFIG_DIR_L);
	SET_PIN_AS_OUT(CONFIG_DIR_L);
	SET_PIN_LEVEL_LOW(CONFIG_DIR_R);
	SET_PIN_AS_OUT(CONFIG_DIR_R);
	SET_PIN_LEVEL_LOW(CONFIG_PULS_L);
	SET_PIN_AS_OUT(CONFIG_PULS_L);
	SET_PIN_LEVEL_LOW(CONFIG_PULS_R);
	SET_PIN_AS_OUT(CONFIG_PULS_R);
	
	rotation->speed = 0;
	rotation->dir = BRIDGE_DIRECTION_UNKNOWN;
	rotation->brake = false;
}

void bridge_SetMotorOnLeft(void)
{
	SET_PIN_LEVEL_LOW(CONFIG_DIR_R);
	SET_PIN_LEVEL_LOW(CONFIG_PULS_R);
	motor_running_direction = BRIDGE_DIRECTION_LEFT;
	nop();
	nop();
	SET_PIN_LEVEL_HIGH(CONFIG_DIR_L);
	SET_PIN_LEVEL_HIGH(CONFIG_PULS_L);
}

void bridge_SetMotorOnRight(void)
{
	SET_PIN_LEVEL_LOW(CONFIG_DIR_L);
	SET_PIN_LEVEL_LOW(CONFIG_PULS_L);
	motor_running_direction = BRIDGE_DIRECTION_RIGHT;
	nop();
	nop();
	SET_PIN_LEVEL_HIGH(CONFIG_DIR_R);
	SET_PIN_LEVEL_HIGH(CONFIG_PULS_R);
}

void bridge_SetMotorOff(void)
{
	SET_PIN_LEVEL_LOW(CONFIG_PULS_L);
	SET_PIN_LEVEL_LOW(CONFIG_PULS_R);
	SET_PIN_LEVEL_LOW(CONFIG_DIR_L);
	SET_PIN_LEVEL_LOW(CONFIG_DIR_R);
	motor_running_direction = BRIDGE_DIRECTION_STOP;
}

void bridge_SetMotorBrake(void)
{
	SET_PIN_LEVEL_LOW(CONFIG_DIR_L);
	SET_PIN_LEVEL_LOW(CONFIG_DIR_R);
	SET_PIN_LEVEL_HIGH(CONFIG_PULS_L);
	SET_PIN_LEVEL_HIGH(CONFIG_PULS_R);
}

void bridge_InterruptHandler(BRIDGE_t rotation, void (*start_timer)(uint8_t))
{
	// prevent quick change of direction
	if(motor_running_direction != BRIDGE_DIRECTION_STOP) {
		if (motor_running_direction != rotation.dir) rotation.speed = 0;
	}
	switch(phase) {
		case BRIDGE_PULSE_BASE:
			if (rotation.speed <= BRIDGE_PULSE_MIN_LENGTH) {
				if ((rotation.speed == 0) && rotation.brake && (motor_running_direction == BRIDGE_DIRECTION_STOP)) bridge_SetMotorBrake();
				else bridge_SetMotorOff();
				start_timer(0xff);
			} else if (rotation.speed >= BRIDGE_PULSE_MAX_LENGTH) {
				if (rotation.dir == BRIDGE_DIRECTION_RIGHT) {
					bridge_SetMotorOnRight();
				} else if (rotation.dir == BRIDGE_DIRECTION_LEFT) {
					bridge_SetMotorOnLeft();
				}
				start_timer(0xff);
			} else {
				if (rotation.dir == BRIDGE_DIRECTION_RIGHT) {
					bridge_SetMotorOnRight();
				} else if (rotation.dir == BRIDGE_DIRECTION_LEFT) {
					bridge_SetMotorOnLeft();
				}
				phase = BRIDGE_PULSE_PAUSE;
				pause = 0xff - rotation.speed;
				start_timer(rotation.speed);
			}
			break;
		case BRIDGE_PULSE_PAUSE:
 			bridge_SetMotorOff();
			phase = BRIDGE_PULSE_BASE;
 			start_timer(pause);
			break;
	}
}

