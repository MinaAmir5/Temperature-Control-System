/*
 * UART_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "UART_Interface.h"
#include "UART_Private.h"
#include <util/delay.h>
#include <avr/interrupt.h>

void (*UART_CallBack) (void);


#define UCSRA_REG               *(volatile u8*)0x2B
#define UCSRB_REG               *(volatile u8*)0x2A
#define UCSRC_REG               *(volatile u8*)0x40
#define UBRRL_REG               *(volatile u8*)0x29

/* UCSRA BITS */
#define RXC_BIT         7
#define TXC_BIT         6

/* UCSRB BITS */
#define RXEN_BIT        4
#define TXEN_BIT        3
#define UCSZ2_BIT       2

/* UCSRC BITS */
#define UMSEL_BIT       6
#define UPM1_BIT        5
#define UPM0_BIT        4
#define USBS_BIT        3
#define UCSZ1_BIT       2
#define UCSZ0_BIT       1

#define UART_PARITY_DISABLE                1
#define UART_PARITY_EVEN                   2
#define UART_PARITY_ODD                    3
#define UART_1_STOP_BIT                    1
#define UART_2_STOP_BIT                    2

#define UART_FINISHED_RECEIVING            1
#define UART_FINISHED_TRANSMITTING         1
#define POLLING_TIME                    20000

void (*UART_CallBack) (void);

void M_UART_Void_UARTInit(void)
{
	u8 Local_U8_UCSRCValue = 0b10000000;

	M_DIO_Void_SetPinDirection(PD0_PIN,INPUT);
	M_DIO_Void_SetPinDirection(PD1_PIN,OUTPUT);

	/* TO SELECT CHARACTER SIZE -> 8 BITS */
	CLR_BIT(UCSRB_REG,UCSZ2_BIT);
	SET_BIT(Local_U8_UCSRCValue,UCSZ1_BIT);
	SET_BIT(Local_U8_UCSRCValue,UCSZ0_BIT);
	/* TO SELECT ASYNCH. MODE */
	CLR_BIT(Local_U8_UCSRCValue,UMSEL_BIT);

#if   UART_PARITY_MODE   ==   UART_PARITY_DISABLE
	CLR_BIT(Local_U8_UCSRCValue,UPM0_BIT);
	CLR_BIT(Local_U8_UCSRCValue,UPM1_BIT);
#elif UART_PARITY_MODE   ==   UART_PARITY_EVEN
	CLR_BIT(Local_U8_UCSRCValue,UPM0_BIT);
	SET_BIT(Local_U8_UCSRCValue,UPM1_BIT);
#elif UART_PARITY_MODE   ==   UART_PARITY_ODD
	SET_BIT(Local_U8_UCSRCValue,UPM0_BIT);
	SET_BIT(Local_U8_UCSRCValue,UPM1_BIT);
#endif
#if   UART_STOP_BITS   ==   UART_1_STOP_BIT
	CLR_BIT(Local_U8_UCSRCValue,USBS_BIT);
#elif UART_STOP_BITS   ==   UART_2_STOP_BIT
	SET_BIT(Local_U8_UCSRCValue,USBS_BIT);
#endif
	UCSRC_REG = Local_U8_UCSRCValue;
	/* TO SELECT BAUDRATE -> 9600 */
	UBRRL_REG = ((F_OSC * (u32)1000000) / ((u32)16 * UART_BAUDRATE)) - 1;
	SET_BIT(UCSRB_REG,7);
	/* TO ENABLE RX CICUIT */
	SET_BIT(UCSRB_REG,RXEN_BIT);
	/* TO ENABLE TX CIRCUIT */
	SET_BIT(UCSRB_REG,TXEN_BIT);
}

void M_UART_Void_UARTSend(u8 Copy_U8_Data)
{
	u32 Local_U32_Counter = 0;
	UDR_REG = Copy_U8_Data;
	while(Local_U32_Counter < POLLING_TIME)
	{
		Local_U32_Counter++;
		if(GET_BIT(UCSRA_REG,TXC_BIT) == UART_FINISHED_TRANSMITTING)
		{
			break;
		}
	}
}
u8   M_UART_Void_UARTRec(void)
{
	u32 Local_U32_Counter = 0;
	while(1)
	{
		Local_U32_Counter++;
		if(GET_BIT(UCSRA_REG,RXC_BIT) == UART_FINISHED_RECEIVING)
		{
			return UDR_REG;
			break;
		}
	}
	return 0;
}

void M_UART_Void_UARTClear(void)
{
	UDR_REG=0;
}
void M_UART_Void_UARTSetCallBack(void(*Copy_Ptr)(void))
{
	UART_CallBack = Copy_Ptr;
}

void M_UART_Void_UARTSendString(u8 Copy_U8_CharNum,u8* Copy_U8_String)
{
	u8 Local_U8_Counter = 0;
	while(Local_U8_Counter<=Copy_U8_CharNum)
	{
		M_UART_Void_UARTSend((u16)Copy_U8_String[Local_U8_Counter]);
		Local_U8_Counter++;
		_delay_ms(1);
	}
}

ISR(USART_RXC_vect){


	UART_CallBack();
}

void M_UART_Void_UARTDeinit(void)
{
	CLR_BIT(UCSRB_REG,RXEN_BIT);
	CLR_BIT(UCSRB_REG,TXEN_BIT);
}
