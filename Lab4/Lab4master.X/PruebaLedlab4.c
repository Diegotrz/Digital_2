/*
 * File:   PruebaLedlab4.c
 * Author: Diego
 *
 * Created on 6 de agosto de 2023, 08:52 PM
 */


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
// Definici�n e importaci�n de librer�as
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#include "stdio.h"
#include "I2C.h"
//*****************************************************************************
// Definici�n de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
uint8_t pot1;
uint8_t pot2;
uint8_t valcont;
int POT1;
char cPOT1[4];
int SEG;
char cSEG[4];

//*****************************************************************************
// Definici�n de funciones para que se puedan colocar despu�s del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
uint8_t Bcd_to_Dec(uint8_t bcd);

//*****************************************************************************
// C�digo Principal
//*****************************************************************************
void main(void) {
   setup();
    Lcd_Init();
    Lcd_Clear();
     I2C_Master_Init(100000);
  //  Lcd_Set_Cursor(1, 1);
    //Lcd_Write_String("POT1");
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("SEG");

    while(1){
        I2C_Master_Start();
        I2C_Master_Write(0x11);
        POT1 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x00);
        I2C_Master_Stop();
        
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x00);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        SEG = Bcd_to_Dec(I2C_Master_Read(0));
        I2C_Master_Stop();
        __delay_ms(200);
                
       // Lcd_Set_Cursor(2, 1);
        sprintf(cPOT1, "%d", POT1);                          //Convertir ADC en tipo char
        if(POT1 < 10){
            cPOT1[2] = cPOT1[0];
            cPOT1[1] = '0';
            cPOT1[0] = '0';
        }
        else if(POT1 < 100){
            cPOT1[2] = cPOT1[1];
            cPOT1[1] = cPOT1[0];
            cPOT1[0] = '0';
        }
    //    Lcd_Write_String(cPOT1);
        
        
        sprintf(cSEG, "%d", SEG);                          //Convertir valor en tipo char
        if(POT1 < 10){
            cSEG[2] = cSEG[0];
            cSEG[1] = '0';
            cSEG[0] = '0';
        }
        else if(SEG < 100){
            cSEG[2] = cSEG[1];
            cSEG[1] = cSEG[0];
            cSEG[0] = '0';
        }
       Lcd_Set_Cursor(2, 1); 
      Lcd_Write_String(cSEG);        
     // Lcd_Write_String( "hola");     
    }
}
//*****************************************************************************
// Funci�n de Inicializaci�n
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISC6 = 0;
    TRISC7 = 0;
    TRISA =0;
    TRISB = 0;
    TRISD = 0;
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    PORTCbits.RC1 = 1;  
    PORTCbits.RC2 = 1;
 
// Configuraci�n del oscilador
    OSCCONbits.IRCF =   0b0111; //8MHz
    OSCCONbits.SCS = 1;
}
//Funciones
uint8_t Bcd_to_Dec(uint8_t bcd){                            //Funci�n para pasar n�meros de bcd a decimal
    uint8_t dec;                                            //Variable para guardar valor
    dec = ((bcd>>4)*10)+(bcd & 0b00001111);                 //Hacer un corrimiento de bits y sumar con la unidad
    return dec;                                             //Retornar valor
}