/*
 * FW_UART.h
 *
 *  Created on: Oct 16, 2019
 *      Author: Bruno
 */

#ifndef FIRMWARE_FW_UART_H_
#define FIRMWARE_FW_UART_H_

#include "FW_Regs.h"
#include "FW_Pins.h"
#include "FW_GPIO.h"

#define UART_RX_BUFFER_SIZE 128
#define UART_TX_BUFFER_SIZE 128

void InitUART();

void PushRX( uint8_t data );
int16_t PopRX( void );

void PushTX( uint8_t data );
int16_t PopTX( void );

#endif /* FIRMWARE_FW_UART_H_ */
