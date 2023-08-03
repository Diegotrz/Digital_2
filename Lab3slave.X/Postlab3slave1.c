/*
 * File:   Postlab3slave1.c
 * Author: Diego
 *
 * Created on 26 de julio de 2023, 11:52 PM
 */
//*****************************************************************************
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
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
uint8_t valmaster; 
uint8_t valcont2;
uint8_t valsend;
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
       
        valmaster = spiRead();  
       
        
            
        if (valmaster == 0){
            valsend = varvolt;
       
        }
        if (valmaster == 1){
             valsend = PORTD;
        
        }
        spiWrite(valsend);
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
        valcont2 = PORTD;
       
        
      if (!PORTBbits.RB0){ //Verifica si la interrupción del puerto RB0 ha cambiado
            while (!RB0);
                PORTD ++;   
        }
    if (!PORTBbits.RB1){
            while (!RB1) ;
                PORTD  --; 
                
                         
        }
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
    TRISB = 0b11111111;
    
    OPTION_REGbits.nRBPU =  0;
    WPUB = 0b11111111;
    TRISD = 0;
    
    
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
    //Configuración para la interrupción de los botones
    INTCONbits.RBIE = 0;
    INTCONbits.RBIF = 1;
}   
uint16_t  map(uint16_t varmap,uint16_t minval,uint16_t maxval, uint16_t minsal, uint16_t maxsal){
  float  valmap =((varmap - minval) * (maxsal - minsal)) / (maxval - minval) + minsal;
  return valmap;
}