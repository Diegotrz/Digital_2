/*
 * File:   Lab 2.c
 * Author: Diego
 *
 * Created on 24 de julio de 2023, 12:55 AM
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


#include <xc.h>
#include "setup_lb.h"
#include "adclib.h"
#include "stdio.h"
#include "display8bits.h"
void setup(void);
int i;
int valpot0;
int valpot1;
int val;
float varvolt;
uint16_t map(uint16_t varmap,uint16_t minval,uint16_t maxval, uint16_t minsal, uint16_t maxsal);
void __interrupt() isr (void)
{
if(PIR1bits.ADIF){
        //Interrupci�n
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



void main(void) {
  //   config_pines ( 0b00000011,  0);
//  config_tris ( 0xFF, 0b11111111, 0, 0, 0);
// config_ports ( 0, 0, 0, 0);
// config_pullup (0, 0b11111111);
 //Llamada del adc
//adc_init( 0, 0,0,0,0b01); //Funci�n para la configuraci�n del adc
 //config_interrupt(0, 1,0, 1, 1, 1 );
 setup();
 ADCON0bits.GO =1;
 i=0;
CMCON = 0x07;            // Turn comparator off
    InitLCD();                // Initialize LCD in 8bit mode
     ClearLCDScreen();          
    while(1){
    //  Lcd_Set_Cursor(1,1);
      //Lcd_Write_String( 'h');
     if (ADCON0bits.GO ==0){
           for (i=0;i<=2;i++){
           ADCON0bits.CHS = i;
           ADCON0bits.GO =1;
        }
     }
     
     char s[20];
 
//float  varvolt2 = (varvolt*5)/255 ;
  
     float varvolt2 = map(varvolt,0,255,0,5);
     sprintf(s, "volt= %f", varvolt2);
        // Clear LCD screen
        const char msg[] = "AticleWorld.com";
    
    ClearLCDScreen();  
    WriteStringToLCD(s);  // Write Hello World on LCD
     __delay_ms(1000);   
    }
    
    
}
void setup(void){
    ANSEL = 0b00000011;
    ANSELH = 0;
    
    TRISA = 0xFF;
    TRISB = 0b11111111;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    OPTION_REGbits.nRBPU =  0;
    WPUB = 0b111111;
    //PORTB = 0;
    //PORTC = 0;
    PORTD = 0;
    PORTE = 0;
   PORTC = 0;
   
    
    
    // Configuraci�n del oscilador
    OSCCONbits.IRCF =   0b0111; //8MHz
    OSCCONbits.SCS = 1;
    
    // Configuraci�n del ADC
    ADCON1bits.ADFM = 0; //Justificado a la izquierda
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    
    ADCON0bits.ADCS = 0b01; //FOSC/32
    ADCON0bits.CHS = 0;
    ADCON0bits.ADON= 1;
    __delay_us(50);
    
    //Configuraci�n de las interrupciones
    //Configuraci�n para la interrupci�n del ADC      
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    //Configuraci�n para la interrupci�n de los botones
    INTCONbits.RBIE = 0;
    INTCONbits.RBIF = 1;
    //Configuraci�n para las interrupciones globales
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    
}
uint16_t  map(uint16_t varmap,uint16_t minval,uint16_t maxval, uint16_t minsal, uint16_t maxsal){
  float  valmap =((varmap - minval) * (maxsal - minsal)) / (maxval - minval) + minsal;
  return valmap;
}