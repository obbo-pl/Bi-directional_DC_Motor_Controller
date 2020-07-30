/*
 * led.h
 *
 * Created: 2018-12-25 22:39:18
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 


#ifndef LED_H_
#define LED_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint8_t volatile *regddr;
	uint8_t volatile *regport;
	uint8_t pin;
} LED_Port_t;
		
typedef struct {
	LED_Port_t port;
	uint8_t counter;
	uint8_t setup;
	uint8_t period;
	uint8_t duty;
} LED_t;
	

void led_Init(LED_t *led, uint8_t volatile *led_regddr, uint8_t volatile *led_regport, uint8_t pin);
void led_Update(LED_t *led);
void led_Clear(LED_t *led);
void led_SetEnabled(LED_t *led, bool enabled);
void led_SetBlink(LED_t *led, bool blink);
void led_SetLed(LED_t *led, bool enabled, bool blink);
void led_SetTimers(LED_t *led, uint8_t period, uint8_t duty);
void led_SetBlinkInverted(LED_t *led, bool state);

#endif /* LED_H_ */

