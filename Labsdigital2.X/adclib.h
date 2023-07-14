/* 
 * File:   adclib.h
 * Author: diego
 *
 * Created on 13 de julio de 2023, 04:04 PM
 */

#ifndef      ADCLIB_H
#define	ADCLIB_H
#include <xc.h>
#include <stdint.h>
#include <stdio.h>         // for sprintf
#define _XTAL_FREQ 8000000

void adc_init(int channel, int justf,int vcf0,int vcf1,char adcs); //Función para la configuración del adc
int  adc_read(); //Función para leer el valor del adc
void adc_cchange(int channel);//Función para cambiar el canal de lectura del adc
int adc_get_channel(); //Función para obtener el valor del canal que está utilizando el adc
#endif	/* USARTMODL_H */

