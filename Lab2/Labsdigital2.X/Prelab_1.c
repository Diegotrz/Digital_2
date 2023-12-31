/*
 * File:   Prelab 1
 * Author: Diego Terraza
 *
 * Created on 13 de julio de 2023, 11:10 AM
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


/*
 *Variables
 */

/*
 * Prototipos de funciones
 */
void setup(void); //Prototipo de la función que contiene todo el setup
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
    setup(); //Mandamos a llamar la función del setup
    while(1)
    {
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
void setup(void){
    ANSEL = 0b00000011;
    ANSELH = 0;
    
    TRISC = 0;
    TRISB = 0b11111111;
    
    OPTION_REGbits.nRBPU =  0;
    WPUB = 0b11111111;
    PORTC = 0;
    // Configuración del oscilador
    OSCCONbits.IRCF =   0b0111; //8MHz
    OSCCONbits.SCS = 1;
    
    //Configuración de las interrupciones

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
}