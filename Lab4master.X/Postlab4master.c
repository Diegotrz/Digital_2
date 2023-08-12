/*
 * File:   Postlab4master.c
 * Author: Diego
 *
 * Created on 6 de agosto de 2023, 10:57 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include "LCD.h"
#include "stdio.h"
#include <xc.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
uint8_t  i, second, minute, hour, m_day, month, year;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
void I2C_Init(uint32_t i2c_clk_freq)
{
  SSPCON  = 0x28;  // configure MSSP module to work in I2C mode
  SSPADD  = (_XTAL_FREQ/(4 * i2c_clk_freq)) - 1;  // set I2C clock frequency
  SSPSTAT = 0;
}
uint8_t bcd_to_decimal(uint8_t number) {
  return((number >> 4) * 10 + (number & 0x0F));
}
 
// convert decimal to BCD function
uint8_t decimal_to_bcd(uint8_t number) {
  return(((number / 10) << 4) + (number % 10));
}
void RTC_display()
{
  static char Time[] = "TIME: 00:00:00";
  static char Date[] = "DATE: 00/00/2000";
 
  // convert data from BCD format to decimal format
  second = bcd_to_decimal(second);
  minute = bcd_to_decimal(minute);
  hour   = bcd_to_decimal(hour);
  m_day  = bcd_to_decimal(m_day);
  month  = bcd_to_decimal(month);
  year   = bcd_to_decimal(year);
  // end conversion
 
  // update time
  Time[6]  = hour   / 10 + '0';
  Time[7]  = hour   % 10 + '0';
  Time[9]  = minute / 10 + '0';
  Time[10] = minute % 10 + '0';
  Time[12] = second / 10 + '0';
  Time[13] = second % 10 + '0';
  // update date
  Date[6]  = m_day  / 10 + '0';
  Date[7]  = m_day  % 10 + '0';
  Date[9]  = month  / 10 + '0';
  Date[10] = month  % 10 + '0';
  Date[14] = year   / 10 + '0';
  Date[15] = year   % 10 + '0';
  //Lcd_Clear();
 Lcd_Set_Cursor(1,1);
  Lcd_Write_String(Time);
  Lcd_Set_Cursor(2,1);
  Lcd_Write_String(Date);
  
}
//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    Lcd_Init();
    //I2C_Init(100000);
     I2C_Master_Init(100000);   
    minute = decimal_to_bcd(0);
    second = decimal_to_bcd(0);
    hour = decimal_to_bcd(0);
    m_day = decimal_to_bcd(6);
    month= decimal_to_bcd(8);
    year= decimal_to_bcd(23);
    /*
    I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x01);    
        I2C_Master_Write(minute);   
        
        I2C_Master_Stop();
        __delay_ms(200);
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x00);    
        I2C_Master_Write(second);   
        
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x02);    
        I2C_Master_Write(hour);   
        I2C_Master_Write(0x03);    
        I2C_Master_Write(m_day);  
        I2C_Master_Write(0x04);    
        I2C_Master_Write(month);
        I2C_Master_Write(0x05);    
        I2C_Master_Write(year);
        I2C_Master_Stop();
        __delay_ms(200);
        */
    while(1){
       I2C_Master_Start();
        I2C_Master_Write(0x24);
        I2C_Master_Write(PORTB);
        I2C_Master_Stop();
        __delay_ms(200);
       
        I2C_Master_Start();
        I2C_Master_Write(0x25);
        PORTA = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
       /*  
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x00);
        I2C_Master_Stop();
        
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x00);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        second = I2C_Master_Read(0);
        I2C_Master_Write(0x01);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        minute = I2C_Master_Read(0);
        I2C_Master_Write(0x02);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        hour = I2C_Master_Read(0);
        I2C_Master_Write(0x03);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        m_day = I2C_Master_Read(0);
        I2C_Master_Write(0x04);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        month = I2C_Master_Read(0);
        I2C_Master_Write(0x05);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        year = I2C_Master_Read(0);
        I2C_Master_Stop();
        */ 
         
      
        __delay_ms(200);
             
    
       
        RTC_display();
      
 
    }
    
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISC6 = 0;
    TRISC7 = 0;
    TRISA =0;
    TRISB = 0;
    TRISD = 0;
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
  
 
// Configuración del oscilador
    OSCCONbits.IRCF =   0b0111; //8MHz
    OSCCONbits.SCS = 1;
    
   
}