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





int main(void) {
	InitPLL();
	InitUART();
	InitSystick();
	InitMotors();
	InitSensors();
	InitComunication();
/*
	GoToOrigin();

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
	/*while(1){
		RxCommand command = PopCommand();
		SerialComFSM();
		if(command.command == NOT_VALID){
			UART_SendStr("hi!\n");
		}
	}*/

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
	}



}

