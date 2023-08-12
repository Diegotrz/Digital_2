/*
 * File:   Lab4prueba.c
 * Author: Diego
 *
 * Created on 6 de agosto de 2023, 06:58 PM
 */


#include <xc.h>
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include "LCD.h"
#include "stdio.h"
#define button1      RB0   // button B1 is connected to RB0 pin
#define button2      RB1   // button B2 is connected to RB1 pin
// variables declaration
uint8_t  i, second, minute, hour, m_day, month, year;
 
/********************** I2C functions **************************/
 void setup(void);
void I2C_Init(uint32_t i2c_clk_freq)
{
  SSPCON  = 0x28;  // configure MSSP module to work in I2C mode
  SSPADD  = (_XTAL_FREQ/(4 * i2c_clk_freq)) - 1;  // set I2C clock frequency
  SSPSTAT = 0;
}
 
void I2C_Start()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  SEN = 1;  // initiate start condition
}
 
void I2C_Repeated_Start()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  RSEN = 1;  // initiate repeated start condition
}
 
void I2C_Stop()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  PEN = 1;  // initiate stop condition
}
 
void I2C_Write(uint8_t i2c_data)
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  SSPBUF = i2c_data;  // update buffer
}
 
uint8_t I2C_Read(uint8_t ack)
{
  uint8_t _data;
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  RCEN = 1;
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  _data = SSPBUF;  // read data from buffer
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  // send acknowledge pulse ? (depends on ack, if 1 send, otherwise don't send)
  ACKDT = !ack;
  ACKEN = 1;
  return _data;  // return data read
}
 
/********************** end I2C functions **********************/
 
// a small function for button1 (B1) debounce
__bit debounce ()
{
  uint8_t count = 0;
  for(uint8_t i = 0; i < 5; i++) {
    if (button1 == 0)
      count++;
    __delay_ms(10);
  }
  if(count > 2)  return 1;
  else           return 0;
}
 
/********************** RTC chip functions *********************/
// convert BCD to decimal function
uint8_t bcd_to_decimal(uint8_t number) {
  return((number >> 4) * 10 + (number & 0x0F));
}
 
// convert decimal to BCD function
uint8_t decimal_to_bcd(uint8_t number) {
  return(((number / 10) << 4) + (number % 10));
}
 
// display time and date function
void RTC_display()
{
  static char Time[] = "TIME: 00:00:00";
  static char Date[] = "DATE: 00/00/2000";
 
  // convert data from BCD format to decimal format
  second = bcd_to_decimal(second);
  minute = bcd_to_decimal(minute);
  hour   = bcd_to_decimal(hour);
  m_day  = bcd_to_decimal(m_day);
  month  = bcd_to_decimal(month);
  year   = bcd_to_decimal(year);
  // end conversion
 
  // update time
  Time[6]  = hour   / 10 + '0';
  Time[7]  = hour   % 10 + '0';
  Time[9]  = minute / 10 + '0';
  Time[10] = minute % 10 + '0';
  Time[12] = second / 10 + '0';
  Time[13] = second % 10 + '0';
  // update date
  Date[6]  = m_day  / 10 + '0';
  Date[7]  = m_day  % 10 + '0';
  Date[9]  = month  / 10 + '0';
  Date[10] = month  % 10 + '0';
  Date[14] = year   / 10 + '0';
  Date[15] = year   % 10 + '0';
 
   Lcd_Set_Cursor(1,1);
  
  Lcd_Write_String(Time);
}
 
// make editing parameter blinks function
void blink()
{
  uint8_t j = 0;
  while(j < 100 && button1 && button2) {
    j++;
    __delay_ms(5);
  }
}
 
// Edit time and date function
uint8_t edit(uint8_t x, uint8_t y, uint8_t parameter)
{
  while(debounce());  // call debounce function (wait for B1 to be released)
 
  while(1) {
 
    while(!button2)    // if button B2 is pressed
    {
      parameter++;
      if(i == 0 && parameter > 23)   // if hours > 23 ==> hours = 0
        parameter = 0;
      if(i == 1 && parameter > 59)   // if minutes > 59 ==> minutes = 0
        parameter = 0;
      if(i == 2 && parameter > 31)   // if date > 31 ==> date = 1
        parameter = 1;
      if(i == 3 && parameter > 12)   // if month > 12 ==> month = 1
        parameter = 1;
      if(i == 4 && parameter > 99)   // if year > 99 ==> year = 0
        parameter = 0;
 /*
      LCD_Goto(x, y);
      LCD_PutC(parameter / 10 + '0');
      LCD_PutC(parameter % 10 + '0');
      __delay_ms(200);
      */
 
    }
    /*
    LCD_Goto(x, y);
    LCD_Print("  ");  // print 2 spaces
    blink();
 
    LCD_Goto(x, y);
    LCD_PutC(parameter / 10 + '0');
    LCD_PutC(parameter % 10 + '0');
    blink();
    */
    if(!button1)     // if button B1 is pressed
    if(debounce())   // call debounce function (make sure if B1 is pressed)
    {
      i++;   // increment 'i' for the next parameter
      return parameter;     // return parameter value and exit
    }
 
  }
 
}
/********************** end RTC chip functions *****************/
 
/*************************** main function *********************/
void main(void)
{
    setup();

  __delay_ms(1000);
 
  I2C_Init(100000);   // initialize I2C bus with clock frequency of 100kHz
 
  Lcd_Init();
 
  while(1) {
 
    if(!button1)     // if button B1 is pressed
    if(debounce())   // call debounce function (make sure if B1 is pressed)
    {
      i = 0;
      hour   = edit(7,  1, hour);
      minute = edit(10, 1, minute);
      m_day  = edit(7,  2, m_day);
      month  = edit(10, 2, month);
      year   = edit(15, 2, year);
 
      while(debounce());  // call debounce function (wait for button B1 to be released)
 
      // convert decimal to BCD
      minute = decimal_to_bcd(minute);
      hour   = decimal_to_bcd(hour);
      m_day  = decimal_to_bcd(m_day);
      month  = decimal_to_bcd(month);
      year   = decimal_to_bcd(year);
      // end conversion
 
      // Write data to DS3231 RTC
      I2C_Start();         // start I2C
      I2C_Write(0xD0);     // RTC chip address
      I2C_Write(0);        // send register address
      I2C_Write(0);        // reset seconds and start oscillator
      I2C_Write(minute);   // write minute value to RTC chip
      I2C_Write(hour);     // write hour value to RTC chip
      I2C_Write(1);        // write day value (not used)
      I2C_Write(m_day);    // write date value to RTC chip
      I2C_Write(month);    // write month value to RTC chip
      I2C_Write(year);     // write year value to RTC chip
      I2C_Stop();          // stop I2C
 
      __delay_ms(200);
 
    }
 
    // read current time and date from the RTC chip
    I2C_Start();           // start I2C
    I2C_Write(0xD0);       // RTC chip address
    I2C_Write(0);          // send register address
    I2C_Repeated_Start();  // restart I2C
    I2C_Write(0xD1);       // initialize data read
    second = I2C_Read(1);  // read seconds from register 0
    minute = I2C_Read(1);  // read minutes from register 1
    hour   = I2C_Read(1);  // read hour from register 2
    I2C_Read(1);           // read day from register 3 (not used)
    m_day  = I2C_Read(1);  // read date from register 4
    month  = I2C_Read(1);  // read month from register 5
    year   = I2C_Read(0);  // read year from register 6
    I2C_Stop();            // stop I2C
 
    RTC_display();    // print time & date
 
    __delay_ms(50);   // wait 50 ms
 
  }
 
}
 
/*************************** end main function ********************************/
void setup(void){
   ANSEL = 0;
    ANSELH = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISC6 = 0;
    TRISC7 = 0;
    TRISA =0;
    TRISB = 0;
    TRISD = 0;
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;

// Configuración del oscilador
    OSCCONbits.IRCF =   0b0111; //8MHz
    OSCCONbits.SCS = 1;

    
   
}