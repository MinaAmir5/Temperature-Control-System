/*
 * GIE_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "GIE_Interface.h"
#include "GIE_Private.h"

void M_GIE_Void_GlobalInterruptEnable(void)
{
	SET_BIT(SREG_REG,I_BIT);
}
void M_GIE_Void_GlobalInterruptDisable(void)
{
	CLR_BIT(SREG_REG,I_BIT);
}
