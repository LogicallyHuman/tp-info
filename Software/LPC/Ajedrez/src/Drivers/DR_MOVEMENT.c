/*
 * DR_MOVEMENT.c
 *
 *  Created on: Nov 11, 2019
 *      Author: Bruno
 */


enum MovementFSMStates{IDLE, GOING_TO_EDGE, GOING_THROUGH_X, GOING_THROUGH_Y, GOING_TO_CENTER};
char MovementFSMState = IDLE;

#include "DR_MOVEMENT.h"

void MovementFSM(){

}

void MovePiece(int fromX, int fromY, int toX, int toY){
	int fromXEdge;
	int fromYEdge;
	int toXEdge;
	int toYEdge;

		if(toX > fromX){
			fromXEdge = fromX;
		}
		else if(toX < fromX){
			fromXEdge = fromX - 1;
		}
		else{
			fromXEdge = fromX%2 == 0 ? fromX-1 : fromX;
		}

		if(toY > fromY){
			fromYEdge = fromY;
		}
		else if(toY < fromY){
			fromYEdge = fromY - 1;
		}
		else{
			fromYEdge = fromY%2 == 0 ? fromY-1 : fromY;
		}

		if(toX > fromX){
			toXEdge = toX - 1;
		}
		else if(toX < fromX){
			toXEdge = toX;
		}
		else{
			toXEdge = toX%2 == 0 ? toX-1 : toX;
		}


		if(toY > fromY){
			toYEdge = toY - 1;
		}
		else if(toY < fromY){
			toYEdge = toY;
		}
		else{
			toYEdge = toY%2 == 0 ? toY-1 : toY;
		}

		fromXEdge = 40*fromXEdge - 20;
		fromYEdge = 40*fromYEdge - 20;
		toXEdge   = 40*toXEdge - 20;
		toYEdge   = 40*toYEdge - 20;
		fromX = 40*(fromX - 1);
		fromY = 40*(fromY - 1);
		toX   = 40*(toX - 1);
		toY   = 40*(toY - 1);


		GoToPos(fromX, fromY);

		while(!IsIdle()){ }

		SetPIN(2,4, 1);

		GoToPos(fromXEdge, fromYEdge);

		while(!IsIdle()){ }

		GoToPos(toXEdge, fromYEdge);

		while(!IsIdle()){ }

		GoToPos(toXEdge, toYEdge);

		while(!IsIdle()){ }

		GoToPos(toX, toY);

		while(!IsIdle()){ }
		SetPIN(2,4, 0);

}
