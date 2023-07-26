/* Name     : main.c
*  Purpose  : Main file for using LCD with PIC16F628A in 8bit mode.
*  Author   : Amlendra Kumar
*  Website  : https://aticleworld.com
*/
#include<htc.h>
// Configuration word for PIC16F877A
__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_ON & CP_OFF & BOREN_ON
          & LVP_OFF & CPD_OFF & WRT_OFF & DEBUG_OFF);
// Define CPU Frequency
// This must be defined, if __delay_ms() or
// __delay_us() functions are used in the code
#define _XTAL_FREQ   20000000
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
// Function Declarations
void WriteCommandToLCD(unsigned char);
void WriteDataToLCD(char);
void InitLCD(void);
void WriteStringToLCD(const char*);
void ClearLCDScreen(void);
//Program start from here
int CMCON;
int main(void)
{
    CMCON = 0x07;            // Turn comparator off
    InitLCD();                // Initialize LCD in 8bit mode
    const char msg[] = "AticleWorld.com";
    ClearLCDScreen();          // Clear LCD screen
    WriteStringToLCD(msg);  // Write Hello World on LCD
    while(1)
    {
    }
    return 0;
}
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