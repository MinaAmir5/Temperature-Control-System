/*
 * Timer_Config.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_
/*
 * TIMER_PRESCALER_DV OPTIONS : [ 1024 , 256 ]
 */
#define TIMER_PRESCALER_DV            1024
/*
 * SELECT F_OSC IN MEGA HERTZ
 */
#define F_OSC                         16
/*
 * TIMER0_MODE OPTIONS : [ NORMAL_MODE , CTC_MODE ]
 */
#define TIMER0_MODE          NORMAL_MODE
/*
 * PWM0_MODE OPTIONS : [ FAST_PWM , PHASE_CORRECT ]
 */
#define PWM0_MODE            FAST_PWM
/*
 * FAST_PWM_MODE OPTIONS : [ INVERTED , NON_INVERTED ]
 */
#define PWM0_MODE2           NON_INVERTED
#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
