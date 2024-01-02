/*
 * LED_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "LED_Interface.h"


void H_LED_Void_LedInit(u8 Copy_U8_Led)
{
	switch(Copy_U8_Led)
	{
	case LED0: M_DIO_Void_SetPinDirection(LED0_PIN,OUTPUT); break;
	case LED1: M_DIO_Void_SetPinDirection(LED1_PIN,OUTPUT); break;
	case LED2: M_DIO_Void_SetPinDirection(LED2_PIN,OUTPUT); break;
	case LED3: M_DIO_Void_SetPinDirection(LED3_PIN,OUTPUT); break;
	case LED4: M_DIO_Void_SetPinDirection(LED4_PIN,OUTPUT); break;
	case LED5: M_DIO_Void_SetPinDirection(LED5_PIN,OUTPUT); break;
	default:                                                break;
	}
}
void H_LED_Void_LedSetOn(u8 Copy_U8_Led)
{
	switch(Copy_U8_Led)
	{
	case LED0: M_DIO_Void_SetPinValue(LED0_PIN,HIGH); break;
	case LED1: M_DIO_Void_SetPinValue(LED1_PIN,HIGH); break;
	case LED2: M_DIO_Void_SetPinValue(LED2_PIN,HIGH); break;
	case LED3: M_DIO_Void_SetPinValue(LED3_PIN,HIGH); break;
	case LED4: M_DIO_Void_SetPinValue(LED4_PIN,HIGH); break;
	case LED5: M_DIO_Void_SetPinValue(LED5_PIN,HIGH); break;
	default:                                          break;
	}
}
void H_LED_Void_LedSetOff(u8 Copy_U8_Led)
{
	switch(Copy_U8_Led)
	{
	case LED0: M_DIO_Void_SetPinValue(LED0_PIN,LOW); break;
	case LED1: M_DIO_Void_SetPinValue(LED1_PIN,LOW); break;
	case LED2: M_DIO_Void_SetPinValue(LED2_PIN,LOW); break;
	case LED3: M_DIO_Void_SetPinValue(LED3_PIN,LOW); break;
	case LED4: M_DIO_Void_SetPinValue(LED4_PIN,LOW); break;
	case LED5: M_DIO_Void_SetPinValue(LED5_PIN,LOW); break;
	default:                                         break;
	}
}
void H_LED_Void_LedTog(u8 Copy_U8_Led)
{
	switch(Copy_U8_Led)
	{
	case LED0: M_DIO_Void_TogPin(LED0_PIN); break;
	case LED1: M_DIO_Void_TogPin(LED1_PIN); break;
	case LED2: M_DIO_Void_TogPin(LED2_PIN); break;
	case LED3: M_DIO_Void_TogPin(LED3_PIN); break;
	case LED4: M_DIO_Void_TogPin(LED4_PIN); break;
	case LED5: M_DIO_Void_TogPin(LED5_PIN); break;
	default:                                break;
	}
}
