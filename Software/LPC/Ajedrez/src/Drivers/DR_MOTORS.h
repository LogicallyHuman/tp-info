/*
 * FW_MOTORS.h
 *
 *  Created on: Oct 23, 2019
 *      Author: Bruno
 */

#ifndef DRIVERS_DR_MOTORS_H_
#define DRIVERS_DR_MOTORS_H_


#include "../Firmware/FW_Pins.h"
#include "../Firmware/FW_GPIO.h"
#include <math.h>

#define STEP_PER_MM 80//(StepsPerRev * MicroSteps) / (BeltPitch [mm] * PulleyTeethCount)

#define MOTOR_ORIGIN_SPEED 400
#define MOVEMENT_SPEED 400

void HandleMotors();
void SetSpeed(int XSpeed, int YSpeed);

void InitMotors();
void GoToOrigin();

void GoToPos(int xGoToPos, int yGoToPos);
char IsIdle();

#endif
