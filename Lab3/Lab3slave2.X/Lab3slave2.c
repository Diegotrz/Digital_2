/*
 * File:   Lab3slave2.c
 * Author: Diego
 *
 * Created on 26 de julio de 2023, 11:00 PM
 */

//*****************************************************************************
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
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
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
uint16_t map(uint16_t varmap,uint16_t minval,uint16_t maxval, uint16_t minsal, uint16_t maxsal);
uint8_t temporal = 0;
int i;
int valpot0;
int valpot1;
int val;
float varvolt;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
//*****************************************************************************
// Código de Interrupción 
//*****************************************************************************
void __interrupt() isr(void){
   if(SSPIF == 1){
       // PORTD = spiRead();
        spiWrite(varvolt);
        SSPIF = 0;
    }
   if(PIR1bits.ADIF){
        //Interrupción
       if (ADCON0bits.CHS ==1){
           
              valpot0 =5/ ADRESH;
      
        }
        else if (ADCON0bits.CHS ==0){
        
         varvolt = ADRESH;
        }
      else if (ADCON0bits.CHS == 2)
            val = ADRESH;
        
            PIR1bits.ADIF =0;
       
    }
}
//*****************************************************************************
// Código Principal
//*****************************************************************************
void main(void) {
    setup();
    ADCON0bits.GO =1;
    i=0;
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
      
       __delay_ms(250);
       if (ADCON0bits.GO ==0){
           for (i=0;i<=2;i++){
           ADCON0bits.CHS = i;
           ADCON0bits.GO =1;
        }
     }
       char s[20];
 
//float  varvolt2 = (varvolt*5)/255 ;
  
     float varvolt2 = map(varvolt,0,255,0,5);
       
       
    }
  
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0b00000011;
    ANSELH = 0;
    
    TRISB = 0;
    TRISD = 0;
    
    PORTB = 0;
    PORTD = 0;
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    // Configuración del oscilador
    OSCCONbits.IRCF =   0b0111; //8MHz
    OSCCONbits.SCS = 1;
     // Configuración del ADC
    ADCON1bits.ADFM = 0; //Justificado a la izquierda
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    
    ADCON0bits.ADCS = 0b01; //FOSC/32
    ADCON0bits.CHS = 0;
    ADCON0bits.ADON= 1;
    __delay_us(50);
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
}
uint16_t  map(uint16_t varmap,uint16_t minval,uint16_t maxval, uint16_t minsal, uint16_t maxsal){
  float  valmap =((varmap - minval) * (maxsal - minsal)) / (maxval - minval) + minsal;
  return valmap;
}