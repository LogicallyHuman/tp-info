/*
 * DW_MOTORS.c
 *
 *  Created on: Oct 23, 2019
 *      Author: Bruno
 */


#include "DR_MOTORS.h"

volatile int XInterval = 0;
volatile int XIntervalCount = 0;
volatile int YInterval = 0;
volatile int YIntervalCount = 0;

volatile long XPos = 0;
volatile long YPos = 0;

long XSpeed = 0;
long YSpeed = 0;

#define IDLE 0
#define GOING_TO_ORIGIN_X 1
#define GOING_TO_ORIGIN_Y 2
#define GOING_TO_POS 3



volatile char MotorFSMState = IDLE;

volatile char GoToXOriginFlag = 0;
volatile char GoToYOriginFlag = 0;

volatile char GoToPosFlag = 0;

volatile long XStepCount = 0;
volatile long YStepCount = 0;

long FutureXPos = 0;
long FutureYPos = 0;


void HandleMotors(){
	if(XInterval > 0){
		if(XIntervalCount >= XInterval){
			if((MotorFSMState == GOING_TO_ORIGIN_X)
			|| (MotorFSMState == GOING_TO_ORIGIN_Y)
			|| (XStepCount > 0) ){

				SetPIN(X_STEP, 0);
				SetPIN(X_STEP, 1);
				XIntervalCount = 0;
				XStepCount--;

			}
		}
		else{
			XIntervalCount++;
		}
	}
	if(YInterval > 0){
		if(YIntervalCount >= YInterval){
			if((MotorFSMState == GOING_TO_ORIGIN_X)
			|| (MotorFSMState == GOING_TO_ORIGIN_Y)
			|| (YStepCount > 0) ){

				SetPIN(Y_STEP, 0);
				SetPIN(Y_STEP, 1);
				YIntervalCount = 0;
				YStepCount--;

			}
		}
		else{
			YIntervalCount++;
		}
	}

	switch(MotorFSMState){
	case IDLE:
		if(GoToXOriginFlag){
			MotorFSMState = GOING_TO_ORIGIN_X;
			SetSpeed(MOTOR_ORIGIN_SPEED, 0);
		}
		if(GoToPosFlag){
			MotorFSMState = GOING_TO_POS;

			SetSpeed(XSpeed, YSpeed);
		}
		break;

	case GOING_TO_ORIGIN_X:
		if(GetPIN(X_ENDSTOP) == 0){
			SetSpeed(0, MOTOR_ORIGIN_SPEED);
			GoToXOriginFlag = 0;
			MotorFSMState = GOING_TO_ORIGIN_Y;
		}
		break;

	case GOING_TO_ORIGIN_Y:
		if(GetPIN(Y_ENDSTOP) == 0){
			SetSpeed(0,0);
			MotorFSMState = IDLE;
		}
		break;

	case GOING_TO_POS:

		if((XStepCount <= 0) && (YStepCount <= 0)){
			SetSpeed(0,0);
			MotorFSMState = IDLE;
			GoToPosFlag = 0;
		}
		break;
	}
}

void GoToOrigin(){
	GoToXOriginFlag = 1;

}

void SetSpeed(int XSpeed, int YSpeed){
	if(XSpeed > 0){
		XInterval = 1000/XSpeed;
		SetPIN(X_DIR, 1);
	}
	else if(XSpeed < 0){
		XInterval = -1000/XSpeed;
		SetPIN(X_DIR, 0);
	}
	else{
		XInterval = 0;
	}

	if(YSpeed > 0){
		YInterval = 1000/YSpeed;
		SetPIN(Y_DIR, 1);
	}
	else if(YSpeed < 0){
		YInterval = -1000/YSpeed;
		SetPIN(Y_DIR, 0);
	}
	else{
		YInterval = 0;
	}
}

void InitMotors(){
	SetPINSEL(X_DIR, 0);
	SetPINSEL(X_STEP, 0);
	SetPINSEL(X_ENDSTOP, 0);

	SetPINSEL(Y_DIR, 0);
	SetPINSEL(Y_STEP, 0);
	SetPINSEL(Y_ENDSTOP, 0);


	SetDIR(X_DIR, OUTPUT);
	SetDIR(X_STEP, OUTPUT);
	SetDIR(X_ENDSTOP, INPUT);

	SetDIR(Y_DIR, OUTPUT);
	SetDIR(Y_STEP, OUTPUT);
	SetDIR(Y_ENDSTOP, INPUT);

	SetPINSEL(MAGNET, 0);
	SetDIR(MAGNET, OUTPUT);


	SetSpeed(0, 0);
}

void GoToPos(int xGoToPos, int yGoToPos){//mm

	int xDir = xGoToPos - XPos;
	int yDir = yGoToPos - YPos;


	XStepCount = STEP_PER_MM * (long)xDir;
	YStepCount = STEP_PER_MM * (long)yDir;

	if(XStepCount < 0){
		XStepCount = -XStepCount;
	}
	if(YStepCount < 0){
		YStepCount = -YStepCount;
	}


	XSpeed = MOVEMENT_SPEED/sqrt(1.0 + (float)yDir*yDir/(xDir*xDir));
	YSpeed = MOVEMENT_SPEED/sqrt(1.0 + (float)xDir*xDir/(yDir*yDir));

	if(xDir > 0)XSpeed = -XSpeed;
	if(yDir > 0)YSpeed = -YSpeed;

	GoToPosFlag = 1;

	XPos = xGoToPos;
	YPos = yGoToPos;

}


char IsIdle(){
	if((MotorFSMState == IDLE) && !GoToPosFlag && !GoToXOriginFlag){
		return 1;
	}
	else{
		return 0;
	}
}

