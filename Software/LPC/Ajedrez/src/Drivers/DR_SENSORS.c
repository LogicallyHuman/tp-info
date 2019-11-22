/*
 * DR_SENSORS.c
 *
 *  Created on: Nov 11, 2019
 *      Author: Bruno
 */

#include "DR_SENSORS.h"

char SensorValues[8];

const uint8_t ColumnPins[8][2] = {{PIN_A}, {PIN_B}, {PIN_C}, {PIN_D}, {PIN_E}, {PIN_F}, {PIN_G}, {PIN_H}};
const uint8_t RowPins[8][2] = {{PIN_1}, {PIN_2}, {PIN_3}, {PIN_4}, {PIN_5}, {PIN_6}, {PIN_7}, {PIN_8}};

char PrevSensorValues[8];

void InitSensors(){

	for(int i = 0; i < 8; i++){
		SetPINSEL   (ColumnPins[i][0], ColumnPins[i][1], 0);
		SetDIR      (ColumnPins[i][0], ColumnPins[i][1], OUTPUT);
		SetPIN      (ColumnPins[i][0], ColumnPins[i][1], 1);
		SetPINMODE  (ColumnPins[i][0], ColumnPins[i][1], PINMODE_PULLUP);

		SetPINSEL   (RowPins[i][0], RowPins[i][1], 0);
		SetDIR      (RowPins[i][0], RowPins[i][1], INPUT);
		SetPINMODE  (RowPins[i][0], RowPins[i][1], PINMODE_PULLDOWN);
	}
	ReadSensors();
    PrevSensorValues[0] = SensorValues[0];
    PrevSensorValues[1] = SensorValues[1];
    PrevSensorValues[2] = SensorValues[2];
    PrevSensorValues[3] = SensorValues[3];
    PrevSensorValues[4] = SensorValues[4];
    PrevSensorValues[5] = SensorValues[5];
    PrevSensorValues[6] = SensorValues[6];
    PrevSensorValues[7] = SensorValues[7];

}

void ReadSensors(){
	for(int col = 0; col < 8; col++){

			/*for(int x = 0; x < 1000; x++){//Spamear sensores
				for(int row = 0; row < 8; row++){
					SetPIN(ColumnPins[row][0], ColumnPins[row][1], 1);
				}
				for(int row = 7; row >= 0 ; row--){
					SetPIN(ColumnPins[row][0], ColumnPins[row][1], 0);
				}
			}*/


			for(int i = 0; i < 8; i++){	//Setear salidas
				SetPIN(ColumnPins[i][0], ColumnPins[i][1], 0);
			}
			SetPIN(ColumnPins[col][0], ColumnPins[col][1], 1);
			//for(long i = 0; i < 5000; i++){

			//}



			for(int row = 0; row < 8; row++){//leer
				if(GetPIN(RowPins[row][0], RowPins[row][1]) == 1){
					SensorValues[row] |= 1 << col;
				}
				else{
					SensorValues[row] &= ~(1 << col);
				}
			}
		}
		for(int row = 0; row < 8; row++){	//Setear salidas
			SetPIN(ColumnPins[row][0], ColumnPins[row][1], 0);
		}
}

#define WAITING_FOR_LIFT 0
#define WAITING_FOR_DROP 1

void UpdateOriginBoard(){

    PrevSensorValues[0] = SensorValues[0];
    PrevSensorValues[1] = SensorValues[1];
    PrevSensorValues[2] = SensorValues[2];
    PrevSensorValues[3] = SensorValues[3];
    PrevSensorValues[4] = SensorValues[4];
    PrevSensorValues[5] = SensorValues[5];
    PrevSensorValues[6] = SensorValues[6];
    PrevSensorValues[7] = SensorValues[7];

}

char CheckPieces(char * fromRow, char * fromCol, char * toRow, char * toCol){

	static char PieceRemovedRow;
	static char PieceRemovedCol;
	static char PiecePlacedRow;
	static char PiecePlacedCol;
	static char PrevPiecePlacedRow;
	static char PrevPiecePlacedCol;

	static char State = WAITING_FOR_LIFT;
	ReadSensors();

	char FoundChangedPiece = 0;
	if(State == WAITING_FOR_LIFT){
		for(int row = 0; row < 8; row++){
			for(int col = 0; col < 8; col++){
				if(((SensorValues[row]&(1<<col)) == 0) && ((PrevSensorValues[row]&(1<<col)) != 0)){
					if(FoundChangedPiece){
						return -1;
					}
					else{
						PieceRemovedRow = row;
						PieceRemovedCol = col;
						FoundChangedPiece = 1;
					}
				}
			}
		}
		if(FoundChangedPiece)State = WAITING_FOR_DROP;
	}
	else if(State == WAITING_FOR_DROP){
		for(int row = 0; row < 8; row++){
			for(int col = 0; col < 8; col++){
				if(((SensorValues[row]&(1<<col)) != 0) && ((PrevSensorValues[row]&(1<<col)) == 0)){
					if(FoundChangedPiece){
						return -1;
					}
					else{
						PiecePlacedRow = row;
						PiecePlacedCol = col;
						FoundChangedPiece = 1;
					}
				}
			}
		}
		if(FoundChangedPiece){
			if(PrevPiecePlacedRow == PiecePlacedRow && PrevPiecePlacedCol == PiecePlacedCol){
				return 0;
			}
			else{
				State = WAITING_FOR_LIFT;
				*fromRow = PieceRemovedRow;
				*fromCol = PieceRemovedCol;
				*toRow = PiecePlacedRow;
				*toCol = PiecePlacedCol;
				PrevPiecePlacedRow = PiecePlacedRow;
				PrevPiecePlacedCol = PiecePlacedCol;

				return 1;
			}

		}
	}
	if(
	PrevSensorValues[0] == SensorValues[0] &&
	PrevSensorValues[1] == SensorValues[1] &&
	PrevSensorValues[2] == SensorValues[2] &&
	PrevSensorValues[3] == SensorValues[3] &&
	PrevSensorValues[4] == SensorValues[4] &&
	PrevSensorValues[5] == SensorValues[5] &&
	PrevSensorValues[6] == SensorValues[6] &&
	PrevSensorValues[7] == SensorValues[7]){
		PrevPiecePlacedRow = -1;
		PrevPiecePlacedCol = -1;
		State = WAITING_FOR_LIFT;

	}
	return 0;
}

