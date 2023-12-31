/*
 * File:   Lab1.c
 * Author: Diego Terraza
 *
 * Created on 13 de julio de 2023, 03:57 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

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
#include <xc.h>
#include <stdint.h>
#include <pic16f887.h>
#include "adclib.h"
#include "setup_lb.h"


/*
 *Variables
 */

/*
 * Prototipos de funciones
 */

/*
 /*
 *Interrupción
 */
void __interrupt() isr (void)
{
    if (INTCONbits.RBIF ){

        
        NOP();
    }
    
}
/*
 *---------------Main-------------
 */
void main (void)
{
 config_pines ( 0b00000011,  0);
  config_tris ( 0xFF, 0b11111111, 0, 0, 0);
 config_ports ( 0, 0, 0, 0);
 config_pullup (0, 0b11111111);
 
 //Llamada del adc
adc_init( 0, 0,0,0,0b01); //Función para la configuración del adc

 __delay_ms(2000);  // wait 2 seconds
    while(1)
    {
        PORTD =   adc_read(); 
        if (!PORTBbits.RB0){ //Verifica si la interrupción del puerto RB0 ha cambiado
            while (!RB0);
                PORTC ++;   
        }
    if (!PORTBbits.RB1){
            while (!RB1) ;
                PORTC  --; 
                
                         
        }
    }
    
    
    
}
/*
 * Funciones
 */
