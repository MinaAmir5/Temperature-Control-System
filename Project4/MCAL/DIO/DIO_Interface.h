/*
 * DIO_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef DIO_DIO_INTERFACE_H_
#define DIO_DIO_INTERFACE_H_

/**************************************************_MACROS_*******************/
#define INPUT             0
#define OUTPUT            1
#define LOW               0
#define HIGH              1
#define DISABLE           0
#define ENABLE            1

#define PA0_PIN           10
#define PA1_PIN           11
#define PA2_PIN           12
#define PA3_PIN           13
#define PA4_PIN           14
#define PA5_PIN           15
#define PA6_PIN           16
#define PA7_PIN           17

#define PB0_PIN           20
#define PB1_PIN           21
#define PB2_PIN           22
#define PB3_PIN           23
#define PB4_PIN           24
#define PB5_PIN           25
#define PB6_PIN           26
#define PB7_PIN           27

#define PC0_PIN           30
#define PC1_PIN           31
#define PC2_PIN           32
#define PC3_PIN           33
#define PC4_PIN           34
#define PC5_PIN           35
#define PC6_PIN           36
#define PC7_PIN           37

#define PD0_PIN           40
#define PD1_PIN           41
#define PD2_PIN           42
#define PD3_PIN           43
#define PD4_PIN           44
#define PD5_PIN           45
#define PD6_PIN           46
#define PD7_PIN           47
/**************************************************_INCLUDES_*****************/
#include "STD.h"
#include "BitMath.h"
/**************************************************_PROTOTYPES_***************/
void M_DIO_Void_SetPinDirection(u8,u8);
void M_DIO_Void_SetPinValue(u8,u8);
void M_DIO_Void_TogPin(u8);
u8   M_DIO_U8_GetPinValue(u8);
void M_DIO_Void_SetPinPullUpRes(u8,u8);


#endif /* DIO_DIO_INTERFACE_H_ */
