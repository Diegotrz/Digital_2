
/*
 * File:   setup_lb
 * Author: Diego Terraza 
 *
 * Created on 13 de julio de 2023, 04:04 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdio.h>         // for sprintf
#include "setup_lb.h"

void config_pines(char ans,int ansh){
ANSEL = ans;
 ANSELH = ansh;
}
void config_tris(char tris_a,char tris_b,char tris_c,char tris_d,char tris_e){
    TRISA= tris_a;
    TRISB = tris_b;
    TRISC = tris_c;
    TRISD = tris_d;
    TRISE = tris_e;
}

void config_ports(char port_a,char port_c,char port_d,char port_e){
    PORTA = port_a;
    PORTC = port_c;
    PORTD = port_d;
    PORTE = port_e;
}
void config_pullup(int pulles, char pinpull){
 OPTION_REGbits.nRBPU =  pulles;
    WPUB = pinpull;
}


void  config_osc(char valosc){
 // Configuración del oscilador
    OSCCONbits.IRCF =   valosc; //8MHz
    OSCCONbits.SCS = 1;
}
void  config_interrupt(int adcif, int adcie,int rbie, int rbif, int pie, int gie ){
//Configuración para la interrupción del ADC      
    PIR1bits.ADIF = adcif;
    PIE1bits.ADIE = adcie;
    //Configuración para la interrupción de los botones
    INTCONbits.RBIE = rbie;
    INTCONbits.RBIF = rbif;
    //Configuración para las interrupciones globales
    INTCONbits.PEIE = pie;
    INTCONbits.GIE = gie;
}
