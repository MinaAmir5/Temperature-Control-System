/*
 * LCD_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_


#include "LCD_Config.h"
#include "DIO_Interface.h"
#define F_CPU 16000000
#include <util/delay.h>

void H_LCD_Void_LCDInit(void);
void H_LCD_Void_LCDWriteCharacter(u8);
void H_LCD_Void_LCDWriteCommand(u8);
void H_LCD_Void_LCDWriteString(u8*);
void H_LCD_Void_LCDWriteNumber(s32);
void H_LCD_Void_LCDGoTo(u8,u8);
void H_LCD_Void_LCDClear(void);
u8 H_LCD_Void_LCDWelcome(void);
void H_LCD_Void_SetCallBack(u8(*)(void));
void H_LCD_Void_LCDUserCheck(u8*);
void H_LCD_Void_LCDAccessDenied(void);
void H_LCD_Void_LCDWriteFloat(f32);

#endif /* HAL_LCD_LCD_INTERFACE_H_ */
