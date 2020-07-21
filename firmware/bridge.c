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
void bridge_SetMotorToChangeDirection(uint8_t *speed);


uint8_t motor_running_direction = BRIDGE_DIRECTION_UNKNOWN;


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

void bridge_SetMotorToChangeDirection(uint8_t *speed)
{
	bridge_SetMotorOff();
	*speed = 0;
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

void bridge_UpdatePWM(BRIDGE_t *rotation, uint8_t timer)
{
	// prevent quick change of direction
	if (rotation->dir == BRIDGE_DIRECTION_RIGHT) {
		if ((motor_running_direction == BRIDGE_DIRECTION_LEFT) && (motor_running_direction == BRIDGE_DIRECTION_UNKNOWN)) {
			bridge_SetMotorToChangeDirection(&(rotation->speed));
			return;
		}
	}
	if (rotation->dir == BRIDGE_DIRECTION_LEFT) {
		if ((motor_running_direction == BRIDGE_DIRECTION_RIGHT) && (motor_running_direction == BRIDGE_DIRECTION_UNKNOWN)) {
			bridge_SetMotorToChangeDirection(&(rotation->speed));
			return;
		}
	}
	// set bridge I/O
	if (rotation->speed > 0) {
		if (timer <= rotation->speed) {
			if (rotation->dir == BRIDGE_DIRECTION_RIGHT) {
				bridge_SetMotorOnRight();
			} else if (rotation->dir == BRIDGE_DIRECTION_LEFT) {
				bridge_SetMotorOnLeft();
			}
		} else {
			bridge_SetMotorOff();
		}
	} else if (rotation->brake && (motor_running_direction == BRIDGE_DIRECTION_STOP)) {
		bridge_SetMotorBrake();
	} else {
		bridge_SetMotorOff();
	}
}


