/* 
 * File: LCD.c  
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

//LCD Functions Developed by electroSome

#include "display8bits.h"


void ToggleEpinOfLCD(void)
{
    LCD_E = 1;                // Give a pulse on E pin
    __delay_us(E_Delay);      // so that LCD can latch the
    LCD_E = 0;                // data from data bus
    __delay_us(E_Delay);
}
void WriteCommandToLCD(unsigned char Command)
{
    LCD_RS = 0;               // It is a command
    LCD_Data_Bus = Command;   // Write Command value on data bus
    ToggleEpinOfLCD();
}
void WriteDataToLCD(char LCDChar)
{
    LCD_RS = 1;               // It is data
    LCD_Data_Bus = LCDChar;   // Write Data value on data bus
    ToggleEpinOfLCD();
}
void InitLCD(void)
{
    // Firstly make all pins output
    LCD_E          = 0;      // E = 0
    LCD_RS           = 0;      // D = 0
    LCD_Data_Bus     = 0;      // CLK = 0
    LCD_E_Dir        = 0;      // Make Output
    LCD_RS_Dir       = 0;      // Make Output
    LCD_Data_Bus_Dir = 0;      // Make Output
    WriteCommandToLCD(0x38);    //function set
    WriteCommandToLCD(0x0c);    //display on,cursor off,blink off
    WriteCommandToLCD(0x01);    //clear display
    WriteCommandToLCD(0x06);    //entry mode, set increment
}
void WriteStringToLCD(const char *s)
{
    while(*s)
    {
        WriteDataToLCD(*s++);   // print first character on LCD
    }
}
void ClearLCDScreen(void)
{
    WriteCommandToLCD(0x01);    // Clear the screen
    __delay_ms(2);              // Delay for cursor to return at zero position
}