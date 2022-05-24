/**
 * ADC routines for the atmega8
 *
 * */


#include "adc.h"

static void ADC_328_init(void);

/*******************************************************************
 * Left shift the data to give 8 bit result in ADCH
 * @param char Channel number
 * @return void
 *
 *******************************************************************/
static void ADC_8_init(char channel)
{
    //ADCSRA = 0x00; //disable adc
    ADMUX = 0; // CLear it
    ADMUX |=  (unsigned char)channel;
    ADCSRB |= (1 << ADLAR); // Left adjust
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // Set prescaler manual p148
    //ADMUX |= 0x40; // External reference mode
    //ADCSRA = 0x86;
}

/*******************************************************************
 *
 * @param char Channel number
 * @return void
 *
 *******************************************************************/
static void ADC_10_init(char channel)
{
    //ADCSRA = 0x00; //disable adc
    ADMUX = 0; // CLear it
    ADMUX |= (unsigned char)channel;
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // Set prescaler manual p148
    //ADMUX |= 0x40; // External reference mode
    //ADCSRA = 0x86;
}



static void ADC_328_init()
{
    ADMUX = 0; // CLear it
    // Vref = Vcc
    ADMUX |= (0 << ADLAR) | (1<<REFS0);
    //set prescaller to 128 and enable ADC
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}


uint16_t ADC_328_read(uint8_t ADCchannel)
{
    int ADC_mean = 0;
    ADC_328_init();

    //select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
    //single conversion mode
    ADCSRA |= (1<<ADSC);
    // wait until ADC conversion is complete
    while( ADCSRA & (1<<ADSC) );
    return ADC;
}
/*******************************************************************
 * @todo Make this take a param for channel number
 * @param char Channel number
 * @return uint8_t ADC value 0-255
 *
 *******************************************************************/
uint8_t ADC_8_read(uint8_t channel)
{
    char i;
    int ADC_temp, ADCH_temp;
    int ADC_var = 0;
    ADC_8_init(channel);
    ADC_ENABLE;
    ADC_START_CONVERSION; //do a dummy readout first
    while(!(ADCSRA & 0x10)); // wait for conversion done, ADIF flag active
    ADCSRA|=(1 << ADIF);

    ADC_START_CONVERSION;
    while(!(ADCSRA & 0x10)); // wait for conversion done, ADIF flag set
    ADCSRA|=(1 << ADIF);
    //ADC_DISABLE;
    return ADCH;
}

/*******************************************************************
 * @todo Make this take a param for channel number
 * @param char Channel number
 * @return int ADC value 0-1024
 *
 *******************************************************************/
uint16_t ADC_10_read(uint8_t channel)
{
    char i;
    int ADC_temp, ADCH_temp;
    int ADC_var = 0;
    ADC_10_init(channel);
    ADC_ENABLE;
    ADC_START_CONVERSION; //do a dummy readout first
    while(!(ADCSRA & 0x10)); // wait for conversion done, ADIF flag active
    ADCSRA|=(1<<ADIF);

    ADC_START_CONVERSION;
    while(!(ADCSRA & 0x10)); // wait for conversion done, ADIF flag set
    ADCSRA|=(1<<ADIF);
    ADC_DISABLE;
    return ADC;
}
