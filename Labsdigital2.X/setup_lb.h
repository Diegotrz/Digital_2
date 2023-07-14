
#ifndef      SETUP_LB_H
#define	SETUP_LB_H
#include <xc.h>
#include <stdint.h>
#include <stdio.h>         // for sprintf
#define _XTAL_FREQ 8000000

void config_pines(char ans,int ansh); //Funci�n para la configuraci�n del ansel, anselh, y los dem�s pines
void config_tris(char tris_a,char tris_b,char tris_c,char tris_d,char tris_e);
void config_ports(char port_a,char port_c,char port_d,char port_e);
void config_pullup(int pulles, char pinpull);
/* tris_# representa la configuraci�n de los TRIS
* port_# representa la configuraci�n de los puertos para poder reiniciarlos al iniciar el setup
* pulles es el estado del pull up para configurar el   OPTION_REGbits.nRBPU
* pinpull es para configurar qu� pines del puerto B configuramos como pullup
*/
int  config_osc(char valosc); //Funci�n para colocar el valor del oscilador
int config_interrupt(int adcif, int adcie,int rbie, int rbif, int pie, int gie ); //Configuraci�n de las banderas de interrupci�n

#endif	

