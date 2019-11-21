/*
 * DR_COM.h
 *
 *  Created on: Nov 20, 2019
 *      Author: Bruno
 */

#ifndef DRIVERS_DR_COM_H_
#define DRIVERS_DR_COM_H_


#include "DR_UART.h"
#include "string.h"

#define CONNECTED   0
#define READY       1
#define NOT_VALID   2
#define VALID       3
#define MOVE        4
#define RESET       5


#define CONNECTED_COMMAND "CONECTADO"
#define READY_COMMAND "LISTO"
#define NOT_VALID_COMMAND "NOVALIDO"
#define VALID_COMMAND "VALIDO"
#define MOVE_COMMAND "MOVER"
#define RESET_COMMAND "RESET"

struct RxCommand{
	char command;
	char fromRow;
	char fromCol;
	char toRow;
	char toCol;
	char blackCheck;
	char whiteCheck;
} ;

typedef struct RxCommand RxCommand;


RxCommand IdentifyCommand(char * CommandStr);
RxCommand PopCommand();
void PushCommand(RxCommand command);
void SerialComFSM();
void InitComunication();




#endif /* DRIVERS_DR_COM_H_ */
