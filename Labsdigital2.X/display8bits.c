/* 
 * File: LCD.c  
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

//LCD Functions Developed by electroSome

#include "display8bits.h"

void LCD8_PORT(char a) {
    if (a & 1)
        D4 = 1;
    else
        D4 = 0;

    if (a & 2)
        D5 = 1;
    else
        D5 = 0;

    if (a & 4)
        D6 = 1;
    else
        D6 = 0;

    if (a & 8)
        D7 = 1;
    else
        D7 = 0;
}

void LCD8_CMD(char a) {
    RS = 0; // => RS = 0 // Dato en el puerto lo va interpretar como comando
    LCD8_PORT(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void LCD8_CLEAR(void) {
    LCD8_CMD(0);
   LCD8_CMD(1);
}

void LCD8_SET_CURSOR(char a, char b) {
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        LCD8_CMD(z);
        LCD8_CMD(y);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        LCD8_CMD(z);
        LCD8_CMD(y);
    }
}

void LCD8_INIT(void) {
    LCD8_PORT(0x00);
    __delay_ms(20);
    LCD8_CMD(0x03);
    __delay_ms(5);
    LCD8_CMD(0x03);
    __delay_ms(11);
    LCD8_CMD(0x03);
    /////////////////////////////////////////////////////
    LCD8_CMD(0x02);
    LCD8_CMD(0x02);
    LCD8_CMD(0x08);
    LCD8_CMD(0x00);
    LCD8_CMD(0x0C);
    LCD8_CMD(0x00);
    LCD8_CMD(0x06);
}

void LCD8_WRITE_CHAR(char a) {
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    RS = 1; // => RS = 1
    LCD8_PORT(y >> 4); //Data transfer
    EN = 1;
    __delay_us(40);
    EN = 0;
    LCD8_PORT(temp);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void LCD8_WRITE_STRING(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        LCD8_WRITE_CHAR(a[i]);
}

void LCD8_SHIFT_RIGHT(void) {
    LCD8_CMD(0x01);
    LCD8_CMD(0x0C);
}

void LCD8_SHIFT_LEFT(void) {
    LCD8_CMD(0x01);
    LCD8_CMD(0x08);
}

