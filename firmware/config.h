/*
 * config.h
 *
 * Created: 30.08.2019 12:09:12
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 * AVR/GNU C Compiler : 4.8.1
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_


// State LED
#define CONFIG_LED				D,3


// I/O port for motor bridge
#define CONFIG_DIR_L			B,1
#define CONFIG_PULS_L			C,2
#define CONFIG_DIR_R			B,2
#define CONFIG_PULS_R			C,1


// Configuration pinhead (P1 - P3)
#define CONFIG_P1				B,0
#define CONFIG_P2				D,7
#define CONFIG_P3				D,6


// Channel signal (CH1)
#define CONFIG_CH1				D,5


// Battery voltage measure
#define CONFIG_BAT_PORTC_PIN	3



#endif /* CONFIG_H_ */