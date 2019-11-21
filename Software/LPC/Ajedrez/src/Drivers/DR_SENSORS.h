/*
 * DR_SENSORS.h
 *
 *  Created on: Nov 11, 2019
 *      Author: Bruno
 */

#ifndef DRIVERS_DR_SENSORS_H_
#define DRIVERS_DR_SENSORS_H_

#include "../Firmware/FW_GPIO.h"
#include "../Firmware/FW_Pins.h"

extern char SensorValues[8];

void InitSensors();
void ReadSensors();


#endif /* DRIVERS_DR_SENSORS_H_ */
