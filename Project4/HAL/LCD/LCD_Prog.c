/*
 * LCD_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "LCD_Interface.h"
#include "LCD_Private.h"

u8 (*LCD_CallBack) (void);
extern u32 Global_A_U32_Timer_s;
extern u8 Global_A_U8_Status;
extern u8 Global_U8_UARTOut;

void H_LCD_Void_LCDInit(void)
{
#if   LCD_MODE   ==   _8_BIT_MODE
	M_DIO_Void_SetPinDirection(LCD_D0_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D1_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D2_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D3_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D4_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D5_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D6_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D7_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_RS_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_EN_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_RW_PIN,OUTPUT);
	M_DIO_Void_SetPinValue(LCD_RW_PIN,LOW);
	H_LCD_Void_LCDWriteCommand(LCD_8_BIT_MODE);
	H_LCD_Void_LCDWriteCommand(LCD_DISPLAY_ON_CURSOR_OFF);
#elif LCD_MODE   ==   _4_BIT_MODE
	M_DIO_Void_SetPinDirection(LCD_D4_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D5_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D6_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D7_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_RS_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_EN_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_RW_PIN,OUTPUT);
	M_DIO_Void_SetPinValue(LCD_RW_PIN,LOW);

	H_LCD_Void_LCDWriteCommand(LCD_4_BIT_MODE_1);
	H_LCD_Void_LCDWriteCommand(LCD_4_BIT_MODE_2);
	H_LCD_Void_LCDWriteCommand(LCD_4_BIT_MODE_3);

	H_LCD_Void_LCDWriteCommand(LCD_DISPLAY_ON_CURSOR_OFF);
	H_LCD_Void_LCDWriteCommand(LCD_CLEAR);
	H_LCD_Void_LCDWriteCommand(LCD_RETURN_HOME);
#endif

}
void H_LCD_Void_LCDWriteCharacter(u8 Copy_U8_Character)
{
	M_DIO_Void_SetPinValue(LCD_RS_PIN,HIGH);
#if   LCD_MODE   ==   _8_BIT_MODE
	H_LCD_Void_SetLCDPins(Copy_U8_Character);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
#elif LCD_MODE   ==   _4_BIT_MODE
	H_LCD_Void_SetLCDPins(Copy_U8_Character >> 4);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
	_delay_ms(1);
	H_LCD_Void_SetLCDPins(Copy_U8_Character);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
#endif
	_delay_ms(1);
}
void H_LCD_Void_LCDWriteCommand(u8 Copy_U8_Command)
{
	M_DIO_Void_SetPinValue(LCD_RS_PIN,LOW);
#if   LCD_MODE   ==   _8_BIT_MODE
	H_LCD_Void_SetLCDPins(Copy_U8_Command);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
#elif LCD_MODE   ==   _4_BIT_MODE
	H_LCD_Void_SetLCDPins(Copy_U8_Command >> 4);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
	_delay_ms(1);
	H_LCD_Void_SetLCDPins(Copy_U8_Command);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
#endif
	_delay_ms(1);
}
void H_LCD_Void_LCDWriteString(u8* Copy_U8_P)
{
	u8 Local_U8_Counter = 0;
	while(Copy_U8_P[Local_U8_Counter] != '\0')
	{
		H_LCD_Void_LCDWriteCharacter(Copy_U8_P[Local_U8_Counter]);
		Local_U8_Counter++;
	}
}
void H_LCD_Void_LCDWriteNumber(s32 Copy_S32_Num)
{
	s8 Local_S8_Counter = -1;
	u8 Local_U8_Arr[16];
	if(Copy_S32_Num < 0)
	{
		Copy_S32_Num = Copy_S32_Num * -1;
		H_LCD_Void_LCDWriteCharacter('-');
	}
	do
	{
		Local_S8_Counter++;
		Local_U8_Arr[Local_S8_Counter]  =  Copy_S32_Num % 10;
		Copy_S32_Num = Copy_S32_Num / 10;
	}while(Copy_S32_Num != 0);
	while(Local_S8_Counter >= 0)
	{
		H_LCD_Void_LCDWriteCharacter(Local_U8_Arr[Local_S8_Counter] + 48);
		Local_S8_Counter--;
	}
}

void H_LCD_Void_LCDWriteFloat(f32 Copy_F32_Num)
{
	s8 Local_S8_Counter = -1;
	u8 Local_U8_Arr[16];
	u32 Local_U32_Num = Copy_F32_Num;

	do
	{
		Local_S8_Counter++;
		Local_U8_Arr[Local_S8_Counter]  =  Local_U32_Num % 10;
		Local_U32_Num = Local_U32_Num / 10;
	}while(Local_U32_Num != 0);
	while(Local_S8_Counter >= 0)
	{
		H_LCD_Void_LCDWriteCharacter(Local_U8_Arr[Local_S8_Counter] + 48);
		Local_S8_Counter--;
	}
		H_LCD_Void_LCDWriteCharacter(46);
		H_LCD_Void_LCDWriteNumber((f32)(Copy_F32_Num-(u32)Copy_F32_Num)*1000);
}

void H_LCD_Void_LCDGoTo(u8 Copy_U8_Row,u8 Copy_U8_Col)
{
	u8 Local_U8Arr [2] = {0x80 , 0xC0};
	H_LCD_Void_LCDWriteCommand(Local_U8Arr[Copy_U8_Row] + Copy_U8_Col);
}

void H_LCD_Void_LCDClear(void)
{
	H_LCD_Void_LCDWriteCommand(LCD_CLEAR);
}

static void H_LCD_Void_SetLCDPins(u8 Copy_U8_Pins)
{
#if   LCD_MODE   ==   _8_BIT_MODE
	M_DIO_Void_SetPinValue(LCD_D0_PIN,Copy_U8_Pins >> 0 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D1_PIN,Copy_U8_Pins >> 1 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D2_PIN,Copy_U8_Pins >> 2 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D3_PIN,Copy_U8_Pins >> 3 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D4_PIN,Copy_U8_Pins >> 4 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D5_PIN,Copy_U8_Pins >> 5 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D6_PIN,Copy_U8_Pins >> 6 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D7_PIN,Copy_U8_Pins >> 7 & 0x01);
#elif LCD_MODE   ==   _4_BIT_MODE
	M_DIO_Void_SetPinValue(LCD_D4_PIN,Copy_U8_Pins >> 0 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D5_PIN,Copy_U8_Pins >> 1 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D6_PIN,Copy_U8_Pins >> 2 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D7_PIN,Copy_U8_Pins >> 3 & 0x01);
#endif
}

u8 H_LCD_Void_LCDWelcome(void)
{
	while(1)
	{
		u32 Local_U32_Counter=0;
		u8 Local_U8_Read=0;
		H_LCD_Void_LCDClear();
		switch(Global_A_U8_Status)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}
		H_LCD_Void_LCDGoTo(1,0);
		Local_U32_Counter=Global_A_U32_Timer_s+5;
		while(Global_A_U32_Timer_s <=Local_U32_Counter)
		{
			Local_U8_Read=LCD_CallBack();
			if(Local_U8_Read!=0)
				return Local_U8_Read;
		}
		H_LCD_Void_LCDClear();
		H_LCD_Void_LCDGoTo(0,0);
		H_LCD_Void_LCDGoTo(1,0);
		switch(Global_A_U8_Status)
		{
		case 0:
			H_LCD_Void_LCDGoTo(1,8);
			break;
		case 3:
			H_LCD_Void_LCDGoTo(1,9);
			break;
		}
		Local_U32_Counter=Global_A_U32_Timer_s+5;
		while(Global_A_U32_Timer_s <=Local_U32_Counter)
		{
			Local_U8_Read=LCD_CallBack();
			if(Local_U8_Read!=0)
				return Local_U8_Read;
		}
		switch(Global_A_U8_Status)
		{
		case 0:
			H_LCD_Void_LCDGoTo(0,0);
			H_LCD_Void_LCDGoTo(1,0);
			Local_U32_Counter=Global_A_U32_Timer_s+5;
			while(Global_A_U32_Timer_s <=Local_U32_Counter)
			{
				Local_U8_Read=LCD_CallBack();
				if(Local_U8_Read!=0)
					return Local_U8_Read;
			}
			break;
		}
	}
}

void H_LCD_Void_SetCallBack(u8(*Copy_Ptr)(void))
{
	LCD_CallBack=Copy_Ptr;
}

void H_LCD_Void_LCDUserCheck(u8* Copy_U8_User)
{
	if(Global_A_U8_Status==1 || Global_A_U8_Status==2)
	{
		H_LCD_Void_LCDClear();
		H_LCD_Void_LCDGoTo(0,0);
		H_LCD_Void_LCDWriteString(Copy_U8_User);
		H_LCD_Void_LCDGoTo(0,12);
		_delay_ms(3000);
	}
	else
	{
		H_LCD_Void_LCDClear();
		H_LCD_Void_LCDGoTo(0,0);
		_delay_ms(3000);
	}
}

void H_LCD_Void_LCDAccessDenied(void)
{
	H_LCD_Void_LCDClear();
	H_LCD_Void_LCDGoTo(0,0);
	_delay_ms(1000);
}
