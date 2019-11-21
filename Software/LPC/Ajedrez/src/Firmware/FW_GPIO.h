/*
 * FW_GPIO.h
 *
 *  Created on: Oct 8, 2019
 *      Author: Bruno
 */

#ifndef FIRMWARE_FW_GPIO_H_
#define FIRMWARE_FW_GPIO_H_

#include "FW_Regs.h"

void 		SetPINSEL 	( uint8_t  , uint8_t  ,uint8_t );
void 		SetPINMODE	( uint8_t  , uint8_t  ,uint8_t );
void        SetMODE_OD( uint8_t port , uint8_t pin , uint8_t dir );
void 		SetDIR		( uint8_t  , uint8_t  , uint8_t  );
void 		SetPIN		( uint8_t  , uint8_t  , uint8_t  );
uint8_t 	GetPIN(uint8_t port, uint8_t pin);

#define 	PORT0			0
#define 	PORT1			1
#define 	PORT2			2
#define 	PORT3			3
#define 	PORT4			4

#endif /* FIRMWARE_FW_GPIO_H_ */
