/*
 * HC05_prog.c
 *
 *  Created on: Feb 6, 2023
 *      Author: fathy
 */
#include"../../LIBRARY/errorState.h"
#include "../../LIBRARY/stdTypes.h"
#include"../../MCAL/UART/UART_int.h"
#include"HC05_priv.h"
#include "HC05_conf.h"

ES_t HC05_enuInit(void){
	ES_t Local_enuErrorState=ES_OK;
UART_enuInit();
return Local_enuErrorState;
}
ES_t HC05_enuSendString(const char *Copy_Data){
	ES_t Local_enuErrorState=ES_OK;
	UART_enuSendString(Copy_Data);
	return Local_enuErrorState;
}
ES_t HC05_enuRecieveString(u8* Copy_u8Data){
	ES_t Local_enuErrorState=ES_OK;
	UART_enuRecieveString(Copy_u8Data);
	return Local_enuErrorState;
}
ES_t HC05_enuRecieveChar(u8* Copy_u8Data){
	ES_t Local_enuErrorState=ES_OK;
	UART_enuRecieveChar(Copy_u8Data);
	return Local_enuErrorState;
}

