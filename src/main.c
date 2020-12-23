

/********************************************************************************
 * PrinterCaptureInterrupt.ino
 * ------------------
 * Wiring Layout
 * -------------
 *
 * Parallel Port Output               AVR Pins
 * --------------------               -------------
 * Name      Dir.   Pin                Name     Pin
 * ----      ----   ---                ----     ---
 * nSTROBE    >       1................INT0     PA1 (as interrupt)
 * DATA BYTE  >     2-9....................     PORTA
 * nACK       <      10....................     3
 * BUSY       <      11....................     4
 * OutofPaper <      12................GND
 * Selected   <      13.................5v
 * GND        <>  18-25................GND
 *-------------------------------------------------------------------------------
 *
 * CS:      pin 10
 * MOSI:    pin 11
 * MISO:    pin 12
 * SCK:     pin 13
 *
 ********************************************************************************/



#include <stdio.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "gitversion.h"
#include "adc.h"
#include "serial.h"


#define LEN 256

#define PWR_ON   7
#define PWR_STAT 8
#define LED_ON   9

#define SD_CS   10

// connect these to an 8 bit port
#define Data0   5
#define Data1   6
#define Data2   14
#define Data3   15
#define Data4   16
#define Data5   17
#define Data6   18
#define Data7   19

#define nStrobe 2 // To INT0 pin
#define nAck    3 //
#define Busy    4 //

enum States {
  READY,
  BUSY,
  ACK,
  STDBY
} state;



/***********************************************************************


 **********************************************************************/
ISR(EXT_INT0_vect)
{

}


/***********************************************************************
 * MAIN YAAYYYY
 *
 **********************************************************************/
int main()
{
    state = READY;
    char data;
    UART_init();
    while(1)
    {
        switch (state) {
        case READY:
          //digitalWrite(Busy, LOW);
          //digitalWrite(nAck,HIGH);
          //digitalWrite(led, HIGH);
          break;
        case BUSY: // nStrobe signal received by interrupt handler
          //digitalWrite(Busy, HIGH);
          //digitalWrite(led, LOW);
          //ProcessChar();
          data = PINA;
          UART_tx(data);
          state = ACK;
          break;
        case ACK:
          //digitalWrite(nAck,LOW);
          _delay_ms(5); //milliseconds. Specification minimum = 5 us
          state = READY;
          break;
  }


    }


}

