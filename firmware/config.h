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


// State LED port
#define CONFIG_LED_PORT			D
#define CONFIG_LED_PIN			3


// I/O port for motor bridge
#define CONFIG_DIR_L_PORT		B
#define CONFIG_DIR_L_PIN		1

#define CONFIG_PULS_L_PORT		C
#define CONFIG_PULS_L_PIN		2

#define CONFIG_DIR_R_PORT		B
#define CONFIG_DIR_R_PIN		2

#define CONFIG_PULS_R_PORT		C
#define CONFIG_PULS_R_PIN		1


// Configuration pinhead (CFG1 - CFG3)
#define CONFIG_CFG1_PORT		B
#define	CONFIG_CFG1_PIN			0

#define CONFIG_CFG2_PORT		D
#define	CONFIG_CFG2_PIN			7

#define CONFIG_CFG3_PORT		D
#define	CONFIG_CFG3_PIN			6


// Channel signal (CH1)
#define CONFIG_CH1_PORT			D
#define CONFIG_CH1_PIN			5


// Battery voltage measure
#define CONFIG_BAT_PORTC_PIN	3

// Serial port
#define CONFIG_SERIAL_PORT		D
#define CONFIG_SERIAL_Tx_PIN	1	
#define CONFIG_SERIAL_Rx_PIN	0


#endif /* CONFIG_H_ */