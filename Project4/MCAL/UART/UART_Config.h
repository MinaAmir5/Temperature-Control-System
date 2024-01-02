/*
 * UART_Config.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_UART_UART_CONFIG_H_
#define MCAL_UART_UART_CONFIG_H_
/*
 * UART_PARITY_MODE OPTIONS : [ UART_PARITY_DISABLE , UART_PARITY_EVEN , UART_PARITY_ODD ]
 */
#define UART_PARITY_MODE        UART_PARITY_DISABLE
/*
 * UART_STOP_BITS OPTIONS : [ UART_1_STOP_BIT , UART_2_STOP_BIT ]
 */
#define UART_STOP_BITS          UART_1_STOP_BIT
/*
 * SELECT F_OSC IN MEGA HZ
 */
#define F_OSC                   16
/*
 * SELECT UART_BAUDRATE
 */
#define UART_BAUDRATE           9600
#endif /* MCAL_UART_UART_CONFIG_H_ */
