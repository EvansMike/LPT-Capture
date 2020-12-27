/*
 * main.c
 *
 * Copyright 2020 Mike Evans <mikee@saxicola.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
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
#include <string.h>
#include <time.h>

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



/*
Set to 9600 8 N 1
*/
static void USART_Init ()
{
  #define BAUD 9600
  #include <util/setbaud.h>
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  UCSR0C = 0x06;       /* Set frame format: 8data, 1stop bit  */
  UCSR0B = (1<<TXEN0); /* Enable  transmitter                 */
}


static void USART_Transmit (unsigned char data)
{
/* Wait for empty transmit buffer */
while (!(UCSR0A & (1<<UDRE0)));
/* Put data into buffer, sends the data */
UDR0 = data;
}


static void USART_Tx_string(char * string)
{
  while( *string )
  {
    USART_Transmit( *string++ );
  }
}

/***********************************************************************
Interrupt to detect nStrobe
 **********************************************************************/
ISR(INT0_vect)
{
    state = BUSY;
    cli();
}


/***********************************************************************
 * MAIN YAAYYYY
 *
 **********************************************************************/
int main()
{
    DDRC |= _BV(nAck) | _BV(busy);
    unsigned char data;
    USART_Init ();
    state = READY;
    EIMSK |= _BV(INT0);
    EICRA |= _BV(ISC11); // Trigger on falling edge
    PORTC |= _BV(nStrobe) | _BV(busy); // Pull these UP
    PORTD |= _BV(PD2); // Pull UP

    sei();

    USART_Tx_string("Hello World");


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
          sei();
          break;
        case BUSY: // nStrobe signal received by interrupt handler
          //digitalWrite(Busy, HIGH);
          PORTC |= _BV(busy);
          //digitalWrite(led, LOW);
          PORTB &= ~_BV(LED); // OFF
          data = 0;
          data = ((PIND & 0b11111000) >> 3) | ((PINB & 0b00000111) << 5) ;
          USART_Transmit(data);
          state = ACK;
          break;
        case ACK:
          //digitalWrite(nAck,LOW);
          PORTC &= ~_BV(nAck);
          _delay_us(15); //milliseconds. Specification minimum = 5 us
          state = READY;

          break;
        }
    }
while(1);
}
