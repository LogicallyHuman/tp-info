/*
 * DR_COM.c
 *
 *  Created on: Nov 20, 2019
 *      Author: Bruno
 */


/*

 CONECTADO : Conectado

 LISTO

 VALIDO X

 NOVALIDO

 SEMOVIO xXxX

 MOVER xXxX X  (xXxX=move  X=jaque(N/B/-))

 RESET



 */

#include "DR_COM.h"






RxCommand IdentifyCommand(char * CommandStr){
	char CommandFirstPart[12];
	int i = 0;
	for(i = 0; CommandStr[i] != ' ' && CommandStr[i] != '\0'; i++){
		CommandFirstPart[i] = CommandStr[i];
	}
	CommandFirstPart[i] = '\0';

	char command;
	RxCommand ret;
	ret.command = -1;

	     if(strcmp(CommandFirstPart, CONNECTED_COMMAND) == 0)    command = CONNECTED;
	else if(strcmp(CommandFirstPart, READY_COMMAND) == 0)        command = READY;
	else if(strcmp(CommandFirstPart, IS_VALID_COMMAND) == 0)     command = IS_VALID;
	else if(strcmp(CommandFirstPart, VALID_COMMAND) == 0)        command = VALID;
	else if(strcmp(CommandFirstPart, NOT_VALID_COMMAND) == 0)    command = NOT_VALID;
	else if(strcmp(CommandFirstPart, MOVE_COMMAND) == 0)         command = MOVE;
	else if(strcmp(CommandFirstPart, MOVED_COMMAND) == 0)        command = MOVED;

	else return ret;

	ret.command = command;

	if(command == MOVE){
		ret.fromCol = CommandStr[6];
		ret.fromRow = CommandStr[7];
		ret.toCol = CommandStr[8];
		ret.toRow = CommandStr[9];
		if(CommandStr[11] == 'B'){
			ret.whiteCheck = 1;
			ret.blackCheck = 0;
		}
		else if(CommandStr[11] == 'N'){
			ret.whiteCheck = 0;
			ret.blackCheck = 1;
		}
		else{
			ret.whiteCheck = 0;
			ret.blackCheck = 0;
		}
	}

	return ret;

}



int CommandBufInPointer = 0;
int CommandBufOutPointer = 0;

RxCommand CommandBuffer[10];

RxCommand PopCommand(){
	RxCommand command = CommandBuffer[CommandBufOutPointer];
	RxCommand defaultRxCommand = {-1, -1, -1, -1, -1, -1, -1};
	if(command.command == -1 || CommandBufOutPointer == CommandBufInPointer){
		return defaultRxCommand;
	}
	CommandBufOutPointer++;
	CommandBufOutPointer %= 10;

	return command;
}

void PushCommand(RxCommand command){

	CommandBuffer[CommandBufInPointer] = command;

	CommandBufInPointer++;
	CommandBufInPointer %= 10;

}

enum SerialComStates{ WAITING, RECIEVING };

void InitComunication(){
	for(int i = 0; i < 10; i++){
		RxCommand defaultRxCommand = {-1, -1, -1, -1, -1, -1, -1};
		CommandBuffer[i] = defaultRxCommand;

	}
}

void SerialComFSM(){
	static char Command[16];
	static int CommandPointer = 0;
	int RxChar = PopRX();


	if(RxChar != -1){
		if(RxChar == '\n'){
			Command[CommandPointer] = '\0';
			PushCommand(IdentifyCommand(Command));
			CommandPointer = 0;
		}
		else{
			Command[CommandPointer] = (char)RxChar;
			CommandPointer++;
		}
	}
}
