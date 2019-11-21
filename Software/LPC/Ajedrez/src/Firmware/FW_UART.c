/*
 * FW_UART.c
 *
 *  Created on: Oct 16, 2019
 *      Author: Bruno
 */
#include "FW_UART.h"

volatile static uint8_t RXBuffer[UART_RX_BUFFER_SIZE];
volatile static uint8_t RXInPointer = 0;
volatile static uint8_t RXOutPointer = 0;

volatile static uint8_t TXBuffer[UART_TX_BUFFER_SIZE];
volatile static uint8_t TXInPointer = 0;
volatile static uint8_t TXOutPointer = 0;

volatile static int16_t TXFlag = 0;



void PushRX( uint8_t data ){
	RXBuffer[RXInPointer] = data;
	RXInPointer ++;
	RXInPointer %= UART_RX_BUFFER_SIZE;
}


int16_t PopRX( void ){
	int16_t salida = -1;

	if ( RXInPointer != RXOutPointer )
	{
		salida = RXBuffer[RXOutPointer] ;

		RXOutPointer ++;
		RXOutPointer %= UART_RX_BUFFER_SIZE;
	}
	return salida;
}

void PushTX( uint8_t data )
{
	if ( !TXFlag )
	{
		TXFlag = 1;
		U2THR = data;
		return;
	}

	TXBuffer[TXInPointer] = data;
	TXInPointer ++;
	TXInPointer %= UART_TX_BUFFER_SIZE;
}

int16_t PopTX( void )
{
	int16_t ret = -1;

	if ( TXInPointer != TXOutPointer )
	{
		ret = TXBuffer[TXOutPointer] ;

		TXOutPointer ++;
		TXOutPointer %= UART_TX_BUFFER_SIZE;
	}
	return ret;
}



void UART2_IRQHandler (void){
	uint8_t iir, aux;
	int16_t TXData;

	do{
		iir = U2IIR;//IIR es reset por HW, una vez que lo lei se resetea.

		if (iir & 0x04){//Recibio un dato
			aux = U2RBR;
			PushRX ( aux );
		}

		if (iir & 0x02){ //Termino de mandar el contenido de U2THR
			TXData = PopTX();
			if ( TXData != -1 )
				U2THR = (uint8_t) TXData;
			else
				TXFlag = 0;
		}
	}
	while( ! ( iir & 0x01 ) );
}

void InitUART(){


	PCONP |= 0x01<<24; //Pone en 1 el bit PCUART2 del registro PCONP (Power Control for Peripherals)

	PCLKSEL1 &= ~(0x03<<16);//Pone en 0 los bits de PCLK_UART2 del registro PCLKSEL1 (Peripheral Clock Selection register 1)



	U2LCR = 0x00000083;//Configura el registro U2LCR (UART2 Line Control Register) para 8 bits, 1 bit de stop, sin paridad sin break cond. Y DLAB = 1

	//Con un CCLOK=100Mhz el resulta PCLOCK=25Mhz
	//Configura los registros U2DLM y U2DLL para un baud rate de 9600
	int baudios =  25000000 / ( 16 * 9600 );
	U2DLM = (baudios >> 8 ) & 0x000000ff;
	U2DLL = baudios & 0x000000ff;


	SetPINSEL(TXD2 , 1);//Configura los pines de TX y RX para modo UART
	SetPINSEL(RXD2 , 1);

	U2LCR = 0x00000003;//Pone DLAB en 0

	//Habilito las interrupciones (En la UART -IER- y en el NVIC -ISER)
	U2IER = 0x00000003;
	ISER0 |= ( 1 << 7);

}


