
#ifndef      SETUP_LB_H
#define	SETUP_LB_H
#include <xc.h>
#include <stdint.h>
#include <stdio.h>         // for sprintf
#define _XTAL_FREQ 8000000

void config_pines(char ans,int ansh); //Función para la configuración del ansel, anselh, y los demás pines
void config_tris(char tris_a,char tris_b,char tris_c,char tris_d,char tris_e);
void config_ports(char port_a,char port_c,char port_d,char port_e);
void config_pullup(int pulles, char pinpull);
/* tris_# representa la configuración de los TRIS
* port_# representa la configuración de los puertos para poder reiniciarlos al iniciar el setup
* pulles es el estado del pull up para configurar el   OPTION_REGbits.nRBPU
* pinpull es para configurar qué pines del puerto B configuramos como pullup
*/
int  config_osc(char valosc); //Función para colocar el valor del oscilador
int config_interrupt(int adcif, int adcie,int rbie, int rbif, int pie, int gie ); //Configuración de las banderas de interrupción

#endif	

