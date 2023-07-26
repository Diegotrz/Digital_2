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

// Define Pins
#define LCD_E        RC7   // Enable pin for LCD
#define LCD_RS       RC6   // RS pin for LCD
#define LCD_Data_Bus   PORTD // Data bus for LCD
// Define Pins direction register
#define LCD_E_Dir         TRISC7
#define LCD_RS_Dir        TRISC6
#define LCD_Data_Bus_Dir   TRISD
// Constants
#define E_Delay       500
#include <xc.h> // include processor files - each processor file is guarded.  

int CMCON;
//LCD Functions Developed by electroSome


void WriteCommandToLCD(unsigned char);
void WriteDataToLCD(char);
void InitLCD(void);
void WriteStringToLCD(const char*);
void ClearLCDScreen(void);
void ToggleEpinOfLCD(void);

#endif	

