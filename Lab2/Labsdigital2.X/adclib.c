
/*
 * File:   adclib.c
 * Author: Diego Terraza 
 *
 * Created on 13 de julio de 2023, 04:04 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdio.h>         // for sprintf
#include "adclib.h"

void adc_init(int channel,int justf,int vcf0,int vcf1,char adcs){
    
  ADCON1bits.ADFM = justf; //Justificado a la izquierda
   ADCON1bits.VCFG0 = vcf0;
   ADCON1bits.VCFG1 = vcf1;   
   ADCON0bits.ADON= 1;
   __delay_us(50);
ADCON0bits.ADCS = adcs;   
ADCON0bits.CHS = channel; //Configuración del canal
}
int  adc_read(){
return ADRESH;

}
void adc_cchange(int channel){
ADCON0bits.CHS = channel; //Configuración del canal
}
int adc_get_channel(){
    return ADCON0bits.CHS;


}