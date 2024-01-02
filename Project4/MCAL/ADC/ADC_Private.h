/*
 * ADC_Private.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define ADMUX_REG               *(volatile u8*)0x27
#define ADCSRA_REG              *(volatile u8*)0x26
#define ADCL_REG                *(volatile u16*)0x24

/* ADMUX_BITS */
#define REFS1_BIT                7
#define REFS0_BIT                6
#define ADLAR_BIT                5
#define MUX4_BIT                 4
#define MUX3_BIT                 3
#define MUX2_BIT                 2
#define MUX1_BIT                 1
#define MUX0_BIT                 0
/* ADCSRA_BITS */
#define ADEN_BIT                 7
#define ADSC_BIT                 6
#define ADATE_BIT                5
#define ADIF_BIT                 4
#define ADPS2_BIT                2
#define ADPS1_BIT                1
#define ADPS0_BIT                0


#define AVCC                     1
#define AREF_PIN                 2
#define _2V5                     3
#define ADC_CONVERSION_COMPLETE  1
#define POLLING_TIME             20000000

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
