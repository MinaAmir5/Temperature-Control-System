/*
 * KeyPad_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef HAL_KEYPAD_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_KEYPAD_INTERFACE_H_

#include "KeyPad_Config.h"
#include "DIO_Interface.h"
#include "STD.h"
#include <util/delay.h>

#define KEYPAD_PRESSED              0
#define KEYPAD_RELEASED             1

void H_KeyPad_Void_KeyPadInit(void);
u8   H_KeyPad_U8_KeyPadRead(void);
u8   *H_KeyPad_U8_KeyPadGetUser(u8);
void H_KeyPad_Void_SetCallBack(void(*Copy_Ptr)(u8,u8,u8*));
#endif /* HAL_KEYPAD_KEYPAD_INTERFACE_H_ */
