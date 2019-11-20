/*
 * macro.h
 *
 * Created: 2019-10-27 22:10:50
 * Atmel Studio 6 (Version: 6.2.1563 - Service Pack 2)
 * AVR/GNU C Compiler : 4.8.1
 *  Author: Krzysztof Markiewicz
 *  www.obbo.pl
 *
 * This program is distributed under the terms of the GNU General Public License
 */ 


#ifndef MACRO_H_
#define MACRO_H_


#define glue2_(x, y)			x ## y
#define glue2(x, y)				glue2_(x, y)
#define glue3_(x, y, z)			x ## y ## z
#define glue3(x, y, z)			glue3_(x, y, z)


#endif /* MACRO_H_ */