/*
 * File:   Prelab3masterp.c
 * Author: diego
 *
 * Created on 26 de julio de 2023, 01:43 PM
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

void delay(unsigned int nMilliseconds)
{
#define CYCLES_PER_MS 100 /* Number of decrement-and-test cycles. */
unsigned long nCycles = nMilliseconds * CYCLES_PER_MS;
while (nCycles--);
}
void SPI_init()
{
    
// this setting selects master mode with frequency fosc/4
  
SSPCONbits.SSPM0 = 0;
SSPCONbits.SSPM1 = 0;
SSPCONbits.SSPM2 = 0;
SSPCONbits.SSPM3 = 0;
// Enable SPI Port
SSPCONbits.SSPEN = 1;
// Configure The Clock Polarity & Phase
SSPCONbits.CKP = 0;

    
SSPSTATbits.CKE = 0;
//  Slew rate control enabled for High Speed mode
SSPSTATbits.SMP = 0;
     
// Set SPI pins as digital I/O
TRISC5 = 0; // SDO -> Output
TRISC4 = 1; // SDI -> Input
TRISC3 = 0; // SCK -> Output
//Uncommnent this line, if you want to send send over interrupt
// SSPIE = 1; PEIE = 1; GIE = 1;
}
//------------------------------------------------------------------------------
void SPI_write(char data)
{
SSPBUF = data;
while(BF == 0);
}
//-----------------------------------------------------------------------------

void main(void) 
{
SPI_init();
TRISB=0x00;
while(1)
{ 
if(RB0) 
SPI_write(0x01);    // if switch pressed, send 0x01
else 
SPI_write(0x02);    // if switch is pressed pressed, send 0x02
}
return;
}