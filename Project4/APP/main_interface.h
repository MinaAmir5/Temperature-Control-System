/*
 * main_interface.h
 *
 *  Created on: Oct 22, 2022
 *      Author: HODA2
 */

#ifndef APP_MAIN_INTERFACE_H_
#define APP_MAIN_INTERFACE_H_

/**************************USERS*****************************/
#define UNSIGNED_USER	0
#define KEYPAD_USER	    1
#define UART_USER		2
#define ADMIN_USER		3
/***************************KEYPAD_OPTIONS**************************/
#define KP_SIGN_OUT		    48
#define KP_TOGGLE_LAMP1		49
#define KP_TOGGLE_LAMP2		50
#define KP_TOGGLE_LAMP3		51
#define KP_TOGGLE_LAMP4		52
#define KP_TOGGLE_LAMP5		53
#define KP_TOGGLE_DIMLAMP	54
#define KP_TOGGLE_AC		55
#define KP_TOGGLE_DOOR      56
#define KP_ALARM_ENABLE     57
/******************************UART_OPTIONS**********************************/
#define ADMIN_LOGIN				48
#define USER_LOGIN				49
#define NEW_UART_USER			50
#define NEW_KEYPAD_USER			51
#define UART_TOGGLE_LAMP1		52
#define UART_TOGGLE_LAMP2		53
#define UART_TOGGLE_LAMP3		54
#define UART_TOGGLE_LAMP4		55
#define UART_TOGGLE_LAMP5		56
#define UART_TOGGLE_DIMLAMP		57
#define UART_TOGGLE_AC			65
#define UART_TOGGLE_DOOR		66
#define ADMIN_KEYPAD_ENABLE		67
#define DELETE_USER				68
#define UART_ALARM_ENABLE		69
#define UART_SIGN_OUT			70
/******************************Macros**********************************/
#define VALID_ADMIN_USER        1
#define VALID_UART_USER         2
#define INVALID_USER            0
#define KEYPAD_ACCESS_DENIED 	0
#define KEYPAD_ACCESS_ACCEPTED 	1
#define DOOR_CLOSED				0
#define DOOR_OPEN				1
#define DIMMER_ON		     	1
#define DIMMER_OFF			    0
#define SECOND		        	1000
#define INITIAL_VALUE	        0
#define TIMER_INTERVAL          1000
#define ALLOWED_TRIALS          2
#define AC_OFF                  0
#define AC_ON                   1
#define DOOR_OPEN_DEGREE		180
#define DOOR_CLOSED_DEGREE		0
#define USER_ARRAY_SIZE         8
#define USERNAME_SIZE           4
#define PASSWORD_SIZE           4
#define AC_ON_TEMP              512
#define UART_STRING_SIZE1       29
#define UART_STRING_SIZE2       12
#define UART_STRING_SIZE3       16
#define UART_STRING_SIZE4       26
#define UART_STRING_SIZE5       28
#define UART_STRING_SIZE6       24






#endif /* APP_MAIN_INTERFACE_H_ */
