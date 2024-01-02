/*
 * KeyPad_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "KeyPad_Interface.h"

void (*KeyPad_CallBack) (u8,u8,u8*);

void H_KeyPad_Void_KeyPadInit(void)
{
	M_DIO_Void_SetPinDirection(KEYPAD_R0_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_R1_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_R2_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_R3_PIN,OUTPUT);

	M_DIO_Void_SetPinDirection(KEYPAD_C0_PIN,INPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_C1_PIN,INPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_C2_PIN,INPUT);
	M_DIO_Void_SetPinDirection(KEYPAD_C3_PIN,INPUT);
	// to activate internal pull up res
	M_DIO_Void_SetPinPullUpRes(KEYPAD_C0_PIN,ENABLE);
	M_DIO_Void_SetPinPullUpRes(KEYPAD_C1_PIN,ENABLE);
	M_DIO_Void_SetPinPullUpRes(KEYPAD_C2_PIN,ENABLE);
	M_DIO_Void_SetPinPullUpRes(KEYPAD_C3_PIN,ENABLE);

	M_DIO_Void_SetPinValue(KEYPAD_R0_PIN,HIGH);
	M_DIO_Void_SetPinValue(KEYPAD_R1_PIN,HIGH);
	M_DIO_Void_SetPinValue(KEYPAD_R2_PIN,HIGH);
	M_DIO_Void_SetPinValue(KEYPAD_R3_PIN,HIGH);
}
u8   H_KeyPad_U8_KeyPadRead(void)
{
	u8 Local_U8_Arr [4][4] = { { '1' , '2' , '3' , 'A' },
			{ '4' , '5' , '6' , 'B' },
			{ '7' , '8' , '9' , 'C' },
			{ '*' , '0' , '#' , 'D' }};
	u8 Local_U8_Reading = 0;
	u8 Local_U8_Row = 0;
	u8 Local_U8_Col = 0;
	for(Local_U8_Row=KEYPAD_R0_PIN;Local_U8_Row<=KEYPAD_R3_PIN;Local_U8_Row++)
	{
		M_DIO_Void_SetPinValue(Local_U8_Row,LOW);
		for(Local_U8_Col=KEYPAD_C0_PIN;Local_U8_Col<=KEYPAD_C3_PIN;Local_U8_Col++)
		{
			if(M_DIO_U8_GetPinValue(Local_U8_Col) == KEYPAD_PRESSED)
			{
				_delay_ms(KEYPAD_DEBOUNCING_TIME);
				if(M_DIO_U8_GetPinValue(Local_U8_Col) == KEYPAD_PRESSED)
				{
					Local_U8_Reading = Local_U8_Arr[Local_U8_Row-KEYPAD_R0_PIN][Local_U8_Col-KEYPAD_C0_PIN];
					break;
				}
			}
		}
		M_DIO_Void_SetPinValue(Local_U8_Row,HIGH);
	}
	return Local_U8_Reading;
}

u8 *H_KeyPad_U8_KeyPadGetUser(u8 Local_U8_FirstElement)
{
	static u8 Local_U8_ArrUser[8];
	Local_U8_ArrUser[0]=0;
	Local_U8_ArrUser[1]=0;
	Local_U8_ArrUser[2]=0;
	Local_U8_ArrUser[3]=0;
	Local_U8_ArrUser[4]=0;
	Local_U8_ArrUser[5]=0;
	Local_U8_ArrUser[6]=0;
	Local_U8_ArrUser[7]=0;
	Local_U8_ArrUser[0]=Local_U8_FirstElement;
	KeyPad_CallBack(0,9,Local_U8_ArrUser);
	_delay_ms(1000);
	while(1)
	{
		Local_U8_ArrUser[1]=H_KeyPad_U8_KeyPadRead();
		if(Local_U8_ArrUser[1]!=0)
			break;
	}
	KeyPad_CallBack(0,10,Local_U8_ArrUser+1);
	_delay_ms(500);
	while(1)
	{
		Local_U8_ArrUser[2]=H_KeyPad_U8_KeyPadRead();
		if(Local_U8_ArrUser[2]!=0)
			break;
	}
	KeyPad_CallBack(0,11,Local_U8_ArrUser+2);
	_delay_ms(500);
	while(1)
	{
		Local_U8_ArrUser[3]=H_KeyPad_U8_KeyPadRead();
		if(Local_U8_ArrUser[3]!=0)
			break;
	}
	KeyPad_CallBack(0,12,Local_U8_ArrUser+3);
	_delay_ms(500);
	while(1)
	{
		Local_U8_ArrUser[4]=H_KeyPad_U8_KeyPadRead();
		if(Local_U8_ArrUser[4]!=0)
			break;
	}
	KeyPad_CallBack(1,9,Local_U8_ArrUser+4);
	_delay_ms(500);
	while(1)
	{
		Local_U8_ArrUser[5]=H_KeyPad_U8_KeyPadRead();
		if(Local_U8_ArrUser[5]!=0)
			break;
	}
	KeyPad_CallBack(1,10,Local_U8_ArrUser+5);
	_delay_ms(500);
	while(1)
	{
		Local_U8_ArrUser[6]=H_KeyPad_U8_KeyPadRead();
		if(Local_U8_ArrUser[6]!=0)
			break;
	}
	KeyPad_CallBack(1,11,Local_U8_ArrUser+6);
	_delay_ms(500);
	while(1)
	{
		Local_U8_ArrUser[7]=H_KeyPad_U8_KeyPadRead();
		if(Local_U8_ArrUser[7]!=0)
			break;
	}
	KeyPad_CallBack(1,12,Local_U8_ArrUser+7);
	_delay_ms(500);
	return Local_U8_ArrUser;
}

void H_KeyPad_Void_SetCallBack(void(*Copy_Ptr)(u8,u8,u8*))
{
	KeyPad_CallBack=Copy_Ptr;
}

