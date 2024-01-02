/*
 * SSD_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "SSD_Interface.h"
#include "SSD_Private.h"

void H_SSD_Void_SSDInit(void)
{
	M_DIO_Void_SetPinDirection(SSD_A_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(SSD_B_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(SSD_C_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(SSD_D_PIN,OUTPUT);

	M_DIO_Void_SetPinDirection(SSD_EN1_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(SSD_EN2_PIN,OUTPUT);
}
void H_SSD_Void_SSDWriteNumber(u8 Copy_U8_Number)
{
	u32 Local_U32_Counter = 0;
	for(;Local_U32_Counter < 500;Local_U32_Counter++)
	{
	u8 Local_U8_Ones = Copy_U8_Number % 10;
	u8 Local_U8_Tens = Copy_U8_Number / 10;
	H_SSD_Void_SSDDigitDisplay(Local_U8_Tens);
	M_DIO_Void_SetPinValue(SSD_EN2_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(SSD_EN2_PIN,LOW);
	H_SSD_Void_SSDDigitDisplay(Local_U8_Ones);
	M_DIO_Void_SetPinValue(SSD_EN1_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(SSD_EN1_PIN,LOW);
	}
}

static void H_SSD_Void_SSDDigitDisplay(u8 Copy_U8_Number)
{
	switch(Copy_U8_Number)
	{
	case 0:
		M_DIO_Void_SetPinValue(SSD_A_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_B_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_C_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_D_PIN,LOW);
		break;
	case 1:
		M_DIO_Void_SetPinValue(SSD_A_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_B_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_C_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_D_PIN,LOW);
		break;
	case 2:
		M_DIO_Void_SetPinValue(SSD_A_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_B_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_C_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_D_PIN,LOW);
		break;
	case 3:
		M_DIO_Void_SetPinValue(SSD_A_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_B_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_C_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_D_PIN,LOW);
		break;
	case 4:
		M_DIO_Void_SetPinValue(SSD_A_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_B_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_C_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_D_PIN,LOW);
		break;
	case 5:
		M_DIO_Void_SetPinValue(SSD_A_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_B_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_C_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_D_PIN,LOW);
		break;
	case 6:
		M_DIO_Void_SetPinValue(SSD_A_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_B_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_C_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_D_PIN,LOW);
		break;
	case 7:
		M_DIO_Void_SetPinValue(SSD_A_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_B_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_C_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_D_PIN,LOW);
		break;
	case 8:
		M_DIO_Void_SetPinValue(SSD_A_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_B_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_C_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_D_PIN,HIGH);
		break;
	case 9:
		M_DIO_Void_SetPinValue(SSD_A_PIN,HIGH);
		M_DIO_Void_SetPinValue(SSD_B_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_C_PIN,LOW);
		M_DIO_Void_SetPinValue(SSD_D_PIN,HIGH);
		break;
	default: break;
	}
}

