#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>


#include "Firmware/FW_GPIO.h"
#include "Firmware/FW_CPUOSC.h"
#include "Firmware/FW_SYSTICK.h"
#include "Drivers/DR_UART.h"
#include "Drivers/DR_MOTORS.h"
#include "Drivers/DR_MOVEMENT.h"
#include "Drivers/DR_SENSORS.h"
#include "Drivers/DR_COM.h"


volatile int count = 0;

#define DATA  2,8
#define CLOCK  2,12
#define LATCH   2,11

void SetLEDs(char BlackTurn, char BlackCheck, char BlackWin, char WhiteTurn, char WhiteCheck, char WhiteWin, char Turn, char Connected){
	  SetPIN(LATCH, 0);
	  SetPIN(DATA, 0);
	  SetPIN(CLOCK, 0);

	  for (int i=0; i < 8; i++)  {
			SetPIN(CLOCK, 0);

		     if(i == 0) SetPIN(DATA, BlackTurn);
		else if(i == 1) SetPIN(DATA, BlackCheck);
		else if(i == 2) SetPIN(DATA, BlackWin);
		else if(i == 3) SetPIN(DATA, Turn);
		else if(i == 4) SetPIN(DATA, Connected);
		else if(i == 5) SetPIN(DATA, WhiteTurn);
		else if(i == 6) SetPIN(DATA, WhiteCheck);
		else if(i == 7) SetPIN(DATA, WhiteWin);
		SetPIN(CLOCK, 1);
		SetPIN(DATA, 0);
	  }
		SetPIN(CLOCK, 0);
	    SetPIN(LATCH, 1);

}

void InitIO(){
	SetPINSEL(DATA, 0);
	SetPINSEL(CLOCK, 0);
	SetPINSEL(LATCH, 0);

	SetDIR(DATA, OUTPUT);
	SetDIR(CLOCK, OUTPUT);
	SetDIR(LATCH, OUTPUT);

	SetMODE_OD(DATA, 1);
	SetMODE_OD(CLOCK, 1);
	SetMODE_OD(LATCH, 1);

	SetLEDs(0, 0, 0, 0, 0, 0, 0, 0);

}




int main(void) {
	InitPLL();
	InitUART();
	InitSystick();
	InitMotors();
	InitSensors();
	InitComunication();
	InitIO();

	/*while(1){
		SetLEDs(1,0,0,0,0,0,0,0);
		for(long i = 0; i < 1000000; i++){

		}
		SetLEDs(0,1,0,0,0,0,0,0);
		for(long i = 0; i < 1000000; i++){

		}
		SetLEDs(0,0,1,0,0,0,0,0);
		for(long i = 0; i < 1000000; i++){

		}
		SetLEDs(0,0,0,1,0,0,0,0);
		for(long i = 0; i < 1000000; i++){

		}
	}*/


	/*GoToOrigin();

	SetPINSEL(2, 4, 0);
	SetDIR(2, 4, OUTPUT);

	while(!IsIdle()){

	}
	MovePiece(2,3,  5,5);
	//SetPIN(2,4, 0);
	while(1){

	}*/


	//SetPINSEL(2, 4, 0);
	//SetDIR(2, 4, OUTPUT);
	//SetPIN(2, 4, 0);

	//GoToOrigin();
	//while(!IsIdle()){

	//}
	//MovePiece(7,7,  2,3);

	char fromRow, fromCol, toRow, toCol;
	UpdateOriginBoard();
	while(1){
		if(CheckPieces(&fromRow, &fromCol, &toRow, &toCol) == 1){
			char str[8];
			str[0] = fromCol + 'a';
			str[1] = fromRow + '1';
			str[2] = toCol + 'a';
			str[3] = toRow + '1';
			str[4] = '\n';
			str[5] = '\0';
			UART_SendStr(str);
		}


	}

	while(1){
		RxCommand command = PopCommand();
		SerialComFSM();
		if(command.command == MOVE){
			char str[7];
			str[0] = command.fromCol;
			str[1] = command.fromRow;
			str[2] = command.toCol;
			str[3] = command.toRow;
			if(command.blackCheck){
				str[4] = 'B';
			}
			else if(command.whiteCheck){
				str[4] = 'W';
			}
			else{
				str[4] = '#';
			}
			str[5] = '\n';
			str[6] = '\0';
			UART_SendStr(str);
		}

	}
/*
	while(1){
		ReadSensors();

		for(int row = 0; row < 8; row++){
			for(int col = 0; col < 8; col++){
				if(SensorValues[row] & (1 << col))
					UART_SendStr("#");
				else
					UART_SendStr(".");
			}
			UART_SendStr("\n");
		}
		UART_SendStr("\n\n\n\n\n\n\n\n\n\n\n\n\n");

		for(long i = 0; i < 5000000; i++){

		}
	}*/



}

