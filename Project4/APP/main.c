/*
 * main.c
 *
 *  Created on: 2/10/2022
 *      Author: RUNTIME_TERRROR
 *      		MINA AMIR GIRGIS
 */

/*************************************************-FUNCTIONS_PROTOTYPES-********************************************/
#define F_CPU 16000000
#include "ADC_Interface.h"
#include "LCD_Interface.h"
#include "DCMotor_Interface.h"
#include "LED_Interface.h"
#include "KeyPad_Interface.h"
#include "Buzzer_Interface.h"
#include "UART_Interface.h"
#include "GIE_Interface.h"

void A_UART_Void_UARTExecution(void);

f32 Global_A_F32_Temp = 0;
u8 Global_A_U8P_InputLow[2] = {0,0};
u8 Global_A_U8P_InputHigh[2] = {0,0};
u8 Global_A_U8P_TempLow;
u8 Global_A_U8P_TempHigh;
u8 Global_A_U8_SetLow = 22;
u8 Global_A_U8_SetHigh = 25;
u8 Global_A_U8_UARTInput;
u8 Local_U8_Switch = 0;
u8 Local_U8_UARTSwitch = 0;
u8 Local_U8_CounterLow = 0;
u8 Local_U8_CounterHigh = 0;


int main()
{
	M_ADC_Void_ADCInit();
	H_LCD_Void_LCDInit();
	H_DCMotor_Void_ACMotorInit();
	H_LED_Void_LedInit(1);
	H_LED_Void_LedInit(2);
	H_LED_Void_LedInit(3);
	H_Buzzer_Void_BuzzerInit();
	H_KeyPad_Void_KeyPadInit();
	M_GIE_Void_GlobalInterruptEnable();
	M_UART_Void_UARTInit();
	M_UART_Void_UARTSetCallBack(A_UART_Void_UARTExecution);
	M_DIO_Void_SetPinDirection(20,1);
	M_DIO_Void_SetPinDirection(32,1);
	M_DIO_Void_SetPinDirection(42,1);
	M_DIO_Void_SetPinValue(42,0);
	M_DIO_Void_SetPinValue(20,1);

	
	f32 Local_F32_Resistance = 9.1;
	f32 Local_F32_Voltage = 25;

	u8 Temp[]="Temp: ";
	u8 TempLow[]="Tl:";
	u8 TempHigh[]="Th:";
	u8 Low[]="Low";
	u8 Norm[]="Norm";
	u8 High[]="High";


	while(1)
	{
		Local_F32_Voltage = M_ADC_U16_ADCRead(ADC_CHANNEL_0);
		Local_F32_Voltage = (f32)((f32)(Local_F32_Voltage*0.0048828125)/101.3425926);
		Local_F32_Resistance = Local_F32_Voltage/0.0004905862088;
		Global_A_F32_Temp = Local_F32_Resistance/0.385;
		
		H_LCD_Void_LCDClear();
		H_LCD_Void_LCDGoTo(0,0);
		H_LCD_Void_LCDWriteString(Temp);
		H_LCD_Void_LCDWriteFloat(Global_A_F32_Temp);
		H_LCD_Void_LCDWriteCharacter(' ');
		H_LCD_Void_LCDWriteCharacter('C');
		
		H_LCD_Void_LCDGoTo(1,0);
		H_LCD_Void_LCDWriteString(TempLow);
		H_LCD_Void_LCDWriteNumber(Global_A_U8_SetLow);
		H_LCD_Void_LCDWriteCharacter(' ');
		H_LCD_Void_LCDWriteString(TempHigh);
		H_LCD_Void_LCDWriteNumber(Global_A_U8_SetHigh);
		H_LCD_Void_LCDWriteCharacter(' ');

		
		if(Global_A_F32_Temp < Global_A_U8_SetLow)
		{
			H_LED_Void_LedSetOn(1);
			H_LED_Void_LedSetOff(2);
			M_DIO_Void_SetPinValue(20,1);
			M_DIO_Void_SetPinValue(42,0);
			H_LCD_Void_LCDWriteString(Low);
		}	
		/*else if (Global_A_F32_Temp > Global_A_U8_SetLow && Global_A_F32_Temp < Global_A_U8_SetHigh)
		{
			H_LED_Void_LedSetOff(1);
			H_LED_Void_LedSetOff(2);
			M_DIO_Void_SetPinValue(20,0);
			M_DIO_Void_SetPinValue(42,0);
			H_LCD_Void_LCDWriteString(Norm);
		}*/
		else if (Global_A_F32_Temp > Global_A_U8_SetHigh)
		{
			H_LED_Void_LedSetOff(1);
			H_LED_Void_LedSetOn(2);
			M_DIO_Void_SetPinValue(20,0);
			M_DIO_Void_SetPinValue(42,1);
			H_LCD_Void_LCDWriteString(High);
		}
		
		if(H_KeyPad_U8_KeyPadRead() == 65 || Local_U8_Switch == 1)
		{
			H_Buzzer_Void_BuzzerSetOn();
			_delay_ms(200);
			H_Buzzer_Void_BuzzerSetOff();
			Local_U8_Switch = 1;
			if ((Global_A_U8P_InputLow[Local_U8_CounterLow] = H_KeyPad_U8_KeyPadRead()) != 0)
				Local_U8_CounterLow++;
			if(Local_U8_CounterLow == 2)
			{
				Local_U8_CounterLow = 0;
				Local_U8_Switch = 0;
				Global_A_U8_SetLow = ((Global_A_U8P_InputLow[0]-48)*10) + (Global_A_U8P_InputLow[1]-48);
			}
		}
		else if(H_KeyPad_U8_KeyPadRead() == 66 || Local_U8_Switch == 2)
		{
			H_Buzzer_Void_BuzzerSetOn();
			_delay_ms(200);
			H_Buzzer_Void_BuzzerSetOff();
			Local_U8_Switch = 2;
			if ((Global_A_U8P_InputHigh[Local_U8_CounterHigh] = H_KeyPad_U8_KeyPadRead()) != 0)
			{
				Local_U8_CounterHigh++;
				H_Buzzer_Void_BuzzerOnce();
			}
			if(Local_U8_CounterHigh == 2)
			{
				Local_U8_CounterHigh = 0;
				Local_U8_Switch = 0;
				Global_A_U8_SetHigh = ((Global_A_U8P_InputHigh[0]-48)*10) + (Global_A_U8P_InputHigh[1]-48);
			}
		}
		
		
		

		
		_delay_ms(200);
	}
		
}

void A_UART_Void_UARTExecution(void)
{
	Global_A_U8_UARTInput=UDR_REG;
	if (Global_A_U8_UARTInput !=69)
	{
		H_Buzzer_Void_BuzzerSetOn();
		_delay_ms(200);
		H_Buzzer_Void_BuzzerSetOff();
		if (Global_A_U8_UARTInput == 67 || Local_U8_UARTSwitch == 1)
		{
			if(Local_U8_UARTSwitch == 1)
			{
				Global_A_U8P_InputLow[Local_U8_CounterLow] = Global_A_U8_UARTInput;
				Local_U8_CounterLow++;
			}
			Local_U8_UARTSwitch = 1;
			if(Local_U8_CounterLow == 2)
			{
				Local_U8_CounterLow = 0;
				Local_U8_UARTSwitch = 0;
				Global_A_U8_SetLow = ((Global_A_U8P_InputLow[0]-48)*10) + (Global_A_U8P_InputLow[1]-48);
			}
		}
		else if (Global_A_U8_UARTInput == 68 || Local_U8_UARTSwitch == 2)
		{
			if(Local_U8_UARTSwitch == 2)
			{
				Global_A_U8P_InputHigh[Local_U8_CounterHigh] = Global_A_U8_UARTInput;
				Local_U8_CounterHigh++;
			}
			Local_U8_UARTSwitch = 2;
			if(Local_U8_CounterHigh == 2)
			{
				Local_U8_CounterHigh = 0;
				Local_U8_UARTSwitch = 0;
				Global_A_U8_SetHigh = ((Global_A_U8P_InputHigh[0]-48)*10) + (Global_A_U8P_InputHigh[1]-48);
			}
		}
	}
}