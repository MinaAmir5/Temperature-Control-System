/*
 * Timer_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "Timer_Interface.h"
#include "Timer_Private.h"

u32 Timer_U32_NumOfOverFlows    = 0;
u8  Timer_U8_RemTicks           = 0;
u32 Timer_U32_NumOfCompareMatch = 0;

void (*Timer0_CallBack) (void);
void (*Timer1_CallBack) (void);
void (*Timer2_CallBack) (void);

void M_Timer_Void_TimerInit(u8 Copy_U8_TimerChannel)
{
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
#if   TIMER0_MODE   ==   NORMAL_MODE
		CLR_BIT(TCCR0_REG,WGM00_BIT);
		CLR_BIT(TCCR0_REG,WGM01_BIT);
		/* TO ENABLE TIMER0 OVERFLOW INT */
		SET_BIT(TIMSK_REG,TOIE0_BIT);
#elif TIMER0_MODE   ==   CTC_MODE
		CLR_BIT(TCCR0_REG,WGM00_BIT);
		SET_BIT(TCCR0_REG,WGM01_BIT);
		/* TO ENABLE TIMER0 COMPARE MATCH INT */
		SET_BIT(TIMSK_REG,OCIE0_BIT);
#endif
		break;
	case TIMER1_CHANNEL:

		break;
	case TIMER2_CHANNEL:

		break;
	default:
		break;
	}
}
void M_Timer_Void_TimerSetTime(u8 Copy_U8_TimerChannel,u32 Copy_U32_DesiredTime)
{
	u32 Local_U32_TickTime   = TIMER_PRESCALER_DV / F_OSC;       /* result will be in micro second */
	u32 Local_U32_TotalTicks = (Copy_U32_DesiredTime * 1000) / Local_U32_TickTime;
	u8 Local_U8_DF  = 255;
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
#if TIMER0_MODE   ==   NORMAL_MODE
		Timer_U32_NumOfOverFlows = Local_U32_TotalTicks / 256;
		u8 Timer_U8_RemTicks     = Local_U32_TotalTicks % 256 ;
		if(Timer_U8_RemTicks != 0)
		{
			TCNT0_REG = 256 - Timer_U8_RemTicks;
			Timer_U32_NumOfOverFlows++;
		}
#elif TIMER0_MODE   ==   CTC_MODE     // 500 tick
		while(Local_U32_TotalTicks % Local_U8_DF)
		{
			--Local_U8_DF;
		}
		Timer_U32_NumOfCompareMatch = Local_U32_TotalTicks / Local_U8_DF;
		OCR0_REG = Local_U8_DF - 1;

#endif
		break;
	case TIMER1_CHANNEL:

		break;
	case TIMER2_CHANNEL:

		break;
	default: break;
	}

}

void M_Timer_Void_TimerStart(u8 Copy_U8_TimerChannel)
{
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
#if   TIMER_PRESCALER_DV   ==   1024
		SET_BIT(TCCR0_REG,CS00_BIT);
		CLR_BIT(TCCR0_REG,CS01_BIT);
		SET_BIT(TCCR0_REG,CS02_BIT);
#elif TIMER_PRESCALER_DV   ==   256
		CLR_BIT(TCCR0_REG,CS00_BIT);
		CLR_BIT(TCCR0_REG,CS01_BIT);
		SET_BIT(TCCR0_REG,CS02_BIT);
#endif
		break;
	case TIMER1_CHANNEL:
		/* TO SELECT TIMER1 PRESCALER DV -> 256 */
		CLR_BIT(TCCR1B_REG,CS10_BIT);
		CLR_BIT(TCCR1B_REG,CS11_BIT);
		SET_BIT(TCCR1B_REG,CS12_BIT);
		break;
	case TIMER2_CHANNEL:
		SET_BIT(TCCR2_REG,CS20_BIT);
		CLR_BIT(TCCR2_REG,CS21_BIT);
		SET_BIT(TCCR2_REG,CS22_BIT);
		break;
	default : break;
	}
}
void M_Timer_Void_TimerStop(u8 Copy_U8_TimerChannel)
{
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
		CLR_BIT(TCCR0_REG,CS00_BIT);
		CLR_BIT(TCCR0_REG,CS01_BIT);
		CLR_BIT(TCCR0_REG,CS02_BIT);
		break;
	case TIMER1_CHANNEL:
		CLR_BIT(TCCR1B_REG,CS10_BIT);
		CLR_BIT(TCCR1B_REG,CS11_BIT);
		CLR_BIT(TCCR1B_REG,CS12_BIT);
		break;
	case TIMER2_CHANNEL:
		CLR_BIT(TCCR2_REG,CS00_BIT);
		CLR_BIT(TCCR2_REG,CS01_BIT);
		CLR_BIT(TCCR2_REG,CS02_BIT);
		break;
	default : break;
	}
}



void M_Timer_Void_PWMInit(u8 Copy_U8_TimerChannel)
{
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
		M_DIO_Void_SetPinDirection(PB3_PIN,OUTPUT);
#if   PWM0_MODE   ==   FAST_PWM
		SET_BIT(TCCR0_REG,WGM00_BIT);
		SET_BIT(TCCR0_REG,WGM01_BIT);
#elif PWM0_MODE   ==   PHASE_CORRECT_PWM
		SET_BIT(TCCR0_REG,WGM00_BIT);
		CLR_BIT(TCCR0_REG,WGM01_BIT);
#endif
#if   PWM0_MODE2   ==   NON_INVERTED
		CLR_BIT(TCCR0_REG,COM00_BIT);
		SET_BIT(TCCR0_REG,COM01_BIT);
#elif PWM0_MODE2   ==   INVERTED
		SET_BIT(TCCR0_REG,COM00_BIT);
		SET_BIT(TCCR0_REG,COM01_BIT);
#endif
		break;
	case TIMER1_CHANNEL:
		M_DIO_Void_SetPinDirection(PD5_PIN,OUTPUT);
		/* TO SELECT MODE NUMBER 14 AT TABLE (47) */
		CLR_BIT(TCCR1A_REG,WGM10_BIT);
		SET_BIT(TCCR1A_REG,WGM11_BIT);
		SET_BIT(TCCR1B_REG,WGM12_BIT);
		SET_BIT(TCCR1B_REG,WGM13_BIT);
		/* TO SELECT NON INVERTED MODE */
		CLR_BIT(TCCR1A_REG,COM1A0_BIT);
		SET_BIT(TCCR1A_REG,COM1A1_BIT);
		break;
	case TIMER2_CHANNEL:
		M_DIO_Void_SetPinDirection(PD7_PIN,OUTPUT);
		SET_BIT(TCCR2_REG,WGM20_BIT);
		SET_BIT(TCCR2_REG,WGM21_BIT);
		CLR_BIT(TCCR2_REG,COM20_BIT);
		SET_BIT(TCCR2_REG,COM21_BIT);

		break;
	default : break;
	}
}
void M_Timer_Void_PWMSetDutyCycle(u8 Copy_U8_TimerChannel,f32 Copy_F32_DutyCycle)
{
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
#if   PWM0_MODE   ==   FAST_PWM
#if   PWM0_MODE2   ==   NON_INVERTED
		if(Copy_F32_DutyCycle == 0)
		{
			OCR0_REG = 0;
		}
		else
		{
			OCR0_REG = ((Copy_F32_DutyCycle * 256) / 100) - 1;
		}
#elif   PWM0_MODE2   ==   INVERTED

#endif
#elif PWM0_MODE   ==   PHASE_CORRECT_PWM
#if   PWM0_MODE2   ==   NON_INVERTED

		OCR0_REG = (Copy_F32_DutyCycle * 255) / 100;

#elif   PWM0_MODE2   ==   INVERTED

#endif
#endif
		break;
	case TIMER1_CHANNEL:
		OCR1A_REG = ((Copy_F32_DutyCycle * ICR1_REG) / 100) - 1;
		break;
	case TIMER2_CHANNEL:
		OCR2_REG = ((Copy_F32_DutyCycle * 256) / 100) - 1;
		break;
	default:  break;
	}
}
void M_Timer_Void_PWMSetFreaquancy(u8 Copy_U8_Freq)
{
	ICR1_REG = ((F_OSC * 1000000 / 256) / Copy_U8_Freq);
}
void M_Timer_Void_PWMStart(u8 Copy_U8_TimerChannel)
{
	M_Timer_Void_TimerStart(Copy_U8_TimerChannel);
}
void M_Timer_Void_PWMStop(u8 Copy_U8_TimerChannel)
{
	M_Timer_Void_TimerStop(Copy_U8_TimerChannel);
}

void M_Timer_Void_SetCallBack(u8 Copy_U8_TimerChannel,void(*Copy_Ptr)(void))
{
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
		Timer0_CallBack = Copy_Ptr;
		break;
	case TIMER1_CHANNEL:
		Timer1_CallBack = Copy_Ptr;
		break;
	case TIMER2_CHANNEL:
		Timer2_CallBack = Copy_Ptr;
		break;
	}
}
#if TIMER0_MODE   ==   NORMAL_MODE
ISR(TIMER0_OVF_vect)
{
	static u32 Local_U32_Counter = 0;
	Local_U32_Counter++;
	if(Local_U32_Counter == Timer_U32_NumOfOverFlows)
	{
		Timer0_CallBack();
		TCNT0_REG = 256 - Timer_U8_RemTicks;
		Local_U32_Counter = 0;
	}
}
#elif TIMER0_MODE   ==   CTC_MODE
ISR(TIMER0_COMP_vect)
{
	static u32 Local_U32_Counter = 0;
	Local_U32_Counter++;
	if(Local_U32_Counter == Timer_U32_NumOfCompareMatch)
	{
		Timer0_CallBack();
		Local_U32_Counter = 0;
	}
}
#endif
