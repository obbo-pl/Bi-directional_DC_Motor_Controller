/*
 * types.h
 *
 * Created: 2019-11-10 23:52:36
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 * AVR/GNU C Compiler : 4.8.1
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 


#ifndef TYPES_H_
#define TYPES_H_


typedef struct dc_rotation {
	uint8_t speed;
	uint8_t dir;
} DCROTATION_t; 

typedef struct dc_controller {
	const char *device_info;
	volatile uint8_t errors;
	uint16_t channel_value;
	uint16_t channel_last;
	uint16_t channel_prev;
	uint8_t channel_level_prev;
	DCROTATION_t rotation;
	uint8_t battery_voltage;
	uint8_t battery_divider;
	uint8_t battery_cut;
	uint8_t zone_neutral;
	uint16_t channel_neutral;
	uint16_t channel_maximum;
	uint16_t channel_minimum;
	uint16_t channel_move_maximum;
	uint16_t channel_move_minimum;
	uint16_t channel_neutral_x2;
	uint8_t custom_filter_length;
	int recovery;
	uint8_t speed_max;
	uint8_t speed_limit;
} DCCON_t;



#endif /* TYPES_H_ */