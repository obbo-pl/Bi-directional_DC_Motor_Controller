/*
 * bridge.h
 *
 * Created: 2020-07-20 20:25:29
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 * AVR/GNU C Compiler : 4.8.1
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 


#ifndef BRIDGE_H_
#define BRIDGE_H_


#include <avr/io.h>
#include <stdbool.h>


enum {
	BRIDGE_DIRECTION_STOP,	
	BRIDGE_DIRECTION_RIGHT,
	BRIDGE_DIRECTION_LEFT,
	BRIDGE_DIRECTION_UNKNOWN
};


typedef struct {
	uint8_t speed;
	uint8_t dir;
	uint8_t brake;
} BRIDGE_t;


void bridge_Init(BRIDGE_t *rotation);
void bridge_UpdatePWM(BRIDGE_t *rotation, uint8_t timer);




#endif /* BRIDGE_H_ */
