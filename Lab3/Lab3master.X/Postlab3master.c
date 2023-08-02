/*
 * File:   Postlab3master.c
 * Author: Diego
 *
 * Created on 26 de julio de 2023, 11:52 PM
 */
#pragma config FOSC = EXTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "SPI.h"
#include "LCD.h"
#include "stdio.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
uint8_t pot1;
uint8_t pot2;
uint8_t valcont;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);

//*****************************************************************************
// Código Principal
//*****************************************************************************
void main(void) {
    setup();
     Lcd_Init();
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
     
        //Envío de datos del primer esclavo
       //Primer envío y recepción del esclavo 1 
        PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(0);
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect 
//-----------------------------------------------
       PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       //spiWrite(0);
       __delay_ms(100);
       
       valcont = spiRead();
       PORTB = valcont;
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect 
       __delay_ms(100);
       //-----------------------------------------
       
       
       
       
       
       
       PORTCbits.RC1 = 0;       //Slave Select
        __delay_ms(1);
       
       spiWrite(15);
       pot2 = spiRead();
       //-------------------------------------
       PORTCbits.RC1 = 1;       //Slave Deselect 
       
       __delay_ms(250);
       
       
       PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(1);
   __delay_ms(250);
       PORTCbits.RC2 = 1;  
       __delay_ms(50);
       
       
       PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
      //spiWrite(1);
       pot1 = spiRead();
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect 
       
       __delay_ms(250);
       
     // Envío de datos a la LCD
        char s[20];
        char s2[20];
        char s3[20];
      Lcd_Clear();
    
//float  varvolt2 = (varvolt*5)/255 ;
      
        
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Pot1");
    
    sprintf(s, "%u", pot1);
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String(s);
    
    Lcd_Set_Cursor(1,7);
    Lcd_Write_String("Pot2");
    
    sprintf(s2, "%u", pot2);
    Lcd_Set_Cursor(2,7);
    Lcd_Write_String(s2);
   
       
        Lcd_Set_Cursor(1,13);
    Lcd_Write_String("Cont");
    
    sprintf(s3, "%u", valcont);
    Lcd_Set_Cursor(2,13);
    Lcd_Write_String(s3);
    __delay_ms(500);
       
    }

}
//*****************************************************************************
// Función de Inicialización
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
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
// Configuración del oscilador
    OSCCONbits.IRCF =   0b0111; //8MHz
    OSCCONbits.SCS = 1;
}