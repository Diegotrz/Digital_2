/* 
 * File: display8bits.h
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DISPLAY8BITS_H
#define	DISPLAY8BITS_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#ifndef RS
#define RS PORTCbits.RC6
#endif

#ifndef EN
#define EN RC7
#endif

#ifndef D0
#define D0 RD0
#endif

#ifndef D1
#define D1 RD1
#endif

#ifndef D2
#define D2 RD2
#endif

#ifndef D3
#define D3 RD3
#endif

#ifndef D4
#define D4 RD4
#endif

#ifndef D5
#define D5 RD5
#endif

#ifndef D6
#define D6 RD6
#endif

#ifndef D7
#define D7 RD7
#endif

#include <xc.h> // include processor files - each processor file is guarded.  

//LCD Functions Developed by electroSome


void LCD8_PORT(char a);

void LCD8_CMD(char a);

void LCD8_CLEAR(void);

void LCD8_SET_CURSOR(char a, char b);

void LCD8_INIT(void);

void LCD8_WRITE_CHAR(char a);

void LCD8_WRITE_STRING(char *a);

void LCD8_SHIFT_RIGHT(void);

void LCD8_SHIFT_LEFT(void);

#endif	

