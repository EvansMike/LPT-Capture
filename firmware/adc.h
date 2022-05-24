

#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

#define ADC_ENABLE ADCSRA |= (1 << ADEN)
#define ADC_DISABLE ADCSRA &= 0x7F
#define ADC_START_CONVERSION ADCSRA |= (1 << ADSC)
uint16_t ADC_328_read(uint8_t ADCchannel);
uint8_t ADC_8_read(uint8_t ADCchannel);
uint16_t ADC_10_read(uint8_t ADCchannel);

#endif
