/*
 * DR_UART.c
 *
 *  Created on: Oct 17, 2019
 *      Author: Bruno
 */

#include "DR_UART.h"

int16_t UART_SendStr(const char * str){
	uint8_t	i;

	for ( i = 0 ; str[i] != '\0' ; i++){
		PushTX( str[i] );
	}
	return 0 ;
}

int16_t UART_PopRX(){
	return PopRX();

}
