/*
 * DR_UART.h
 *
 *  Created on: Oct 17, 2019
 *      Author: Bruno
 */

#ifndef DRIVERS_DR_UART_H_
#define DRIVERS_DR_UART_H_

#include "../Firmware/FW_UART.h"



int16_t UART_SendStr(const char * str);
int16_t UART_PopRX();


#endif /* DRIVERS_DR_UART_H_ */
