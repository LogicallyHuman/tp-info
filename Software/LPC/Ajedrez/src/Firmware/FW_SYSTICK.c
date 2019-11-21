/*
 * FW_SYSTICK.c
 *
 *  Created on: Oct 18, 2019
 *      Author: Bruno
 */

#include "FW_SYSTICK.h"
#include "../Drivers/DR_MOTORS.h"

#include "FW_GPIO.h"

void SysTick_Handler(){
	SetPIN(4, 29, 1);
	HandleMotors();
	SetPIN(4, 29, 0);
}
void InitSystick(){
	STRELOAD  = (STCALIB/100) - 1;
	STCURR = 0;

	ENABLE = 1;
	TICKINT = 1;
	CLKSOURCE = 1;


	SetPINSEL(4, 29, 0);
	SetDIR(4, 29, OUTPUT);
}
