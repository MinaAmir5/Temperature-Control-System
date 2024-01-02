/*
 * UART_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

#include "DIO_Interface.h"
#include "UART_Config.h"
#include "BitMath.h"
#include "STD.h"

#define UDR_REG                 *(volatile u8*)0x2C

void M_UART_Void_UARTInit(void);
void M_UART_Void_UARTDeinit(void);
void M_UART_Void_UARTSetBaudRate(u32);
void M_UART_Void_UARTSend(u8);
void M_UART_Void_UARTSendString(u8 Copy_U8_CharNum,u8*);
u8   M_UART_Void_UARTRec(void);
void M_UART_Void_UARTClear(void);
void M_UART_Void_UARTSetCallBack(void(*Copy_Ptr)(void));


#endif /* MCAL_UART_UART_INTERFACE_H_ */
