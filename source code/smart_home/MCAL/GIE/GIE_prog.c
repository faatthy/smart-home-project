/*
 * GIE_prog.c
 *
 *  Created on: Jan 30, 2023
 *      Author: fathy
 */
#include"../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include"GIE_conf.h"
#include"GIE_priv.h"
ES_t GIE_enuEnable(void){
	ES_t Local_enuErrorState=ES_OK;
	SREG|=(1<<7);
	return Local_enuErrorState;
}
ES_t GIE_enuDisable(void){
	ES_t Local_enuErrorState=ES_OK;
	SREG&=~(1<<7);
	return Local_enuErrorState;
}
