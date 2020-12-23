

/********************************************************************************
 * PrinterCaptureInterrupt.ino
 * ------------------
 * Wiring Layout
 * -------------
 *
 * Parallel Port Output               Mega168 Pins                  UNO pins
 * --------------------               -------------
 * Name      Dir.   Pin                Name     Pin
 * ----      ----   ---                ----     ---
 * nSTROBE    >       1................INT0     PD2 (INT0)
 * DATA BYTE  >     2-9....................
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
//#include "serial.h"


#define nStrobe PD2 // To INT0 pin
#define nAck    PC0 //
#define busy    PC1 //
#define LED     PB5

enum States {
  READY,
  BUSY,
  ACK,
  STDBY
} state;


static void USART_Init (unsigned int baud)
{
/* Set baud rate */
UBRR0H = (unsigned char)(baud>>8);
UBRR0L = (unsigned char)baud;
/* Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}


static void USART_Transmit (unsigned char data)
{
/* Wait for empty transmit buffer */
while (!(UCSR0A & (1<<UDRE0)))
;
/* Put data into buffer, sends the data */
UDR0 = data;
}


/***********************************************************************
Interrupt to detect nStrobe
 **********************************************************************/
ISR(INT0_vect)
{
    state = BUSY;
}


/***********************************************************************
 * MAIN YAAYYYY
 *
 **********************************************************************/
int main()
{
    DDRC |= _BV(nAck) | _BV(busy);
    char data;
    USART_Init (9600);
    state = READY;
    EIMSK |= _BV(INT0);
    EICRA |= _BV(ISC11); // Trigger on falling edge
    PORTC |= _BV(nStrobe) | _BV(busy); // Pull these UP
    sei();

    while(1)
    {
        switch (state) {
        case READY:
          //digitalWrite(Busy, LOW);
          PORTC &= ~_BV(busy);
          //digitalWrite(nAck,HIGH);
          PORTC |= _BV(nAck);
          //digitalWrite(led, HIGH);
          PORTB |= _BV(LED); // ON
          break;
        case BUSY: // nStrobe signal received by interrupt handler
          //digitalWrite(Busy, HIGH);
          PORTC |= _BV(busy);
          //digitalWrite(led, LOW);
          PORTB &= ~_BV(LED); // OFF
          data = (PIND & 0b11111100) & (PINB & 0b00000111);
          //UART_tx(data);
          state = ACK;
          break;
        case ACK:
          //digitalWrite(nAck,LOW);
          PORTC &= ~_BV(nAck);
          _delay_ms(5); //milliseconds. Specification minimum = 5 us
          state = READY;
          break;
        }
    }
}

