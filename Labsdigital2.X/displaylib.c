

/*
 * File:   displaylib
 * Author: Diego Terraza 
 *
 * Created on 18 de julio de 2023, 11:02 AM
 */


#include <xc.h>
#include <stdint.h>
#include <stdio.h>         // for sprintf
#include "displaylib.h"

void valdisplay(char val){
    switch (val){
        case '0':
        portval = 0b00000010;    
            break;
        case '1':
         portval = 0b01100000;      
            break;
        case '2':
            portval = 0b11011010;   
            break;    
        case '3':
            portval = 0b11110010;   
            break;
        case '4':
            portval = 0b01100110;   
            break;   
        case '5':
            portval = 0b10110110;   
            break;
        case '6':
            portval = 0b10111110;   
            break;
        case '7':
            portval = 0b11100000;   
            break;
        case '8':
            portval = 0b11111110;   
            break;
        case '9':
            portval = 0b11110110;
            break;
         case '10':
            portval = 0b11101110; //A
            break;   
             case '11':
            portval =0b00111110 ; //B
            break;
            case '12':
            portval = 0b10011100; //C
            break;
            case '13':
            portval = 0b01111010; //D
            break;
            case '14':
            portval = 0b10011110; //E
            break;
            case '15':
            portval = 0b10001110; //F
            break;
    }

  //  return portval;

}