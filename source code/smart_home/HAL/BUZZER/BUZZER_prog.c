/*
 * BUZZER_prog.c
 *
 *  Created on: Feb 5, 2023
 *      Author: fathy
 */
#include <util/delay.h>
#include"../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include"../../MCAL/DIO/DIO_int.h"
#include"BUZZER_priv.h"
#include"BUZZER_conf.h"

ES_t BUZZER_enuInit(void){
ES_t Local_enuErrorState=ES_OK;
DIO_enuSetPinDirection(BUZZER_GROUP,BUZZER_PIN,DIO_u8OUTPUT);
return Local_enuErrorState;
}
ES_t BUZZER_enuON(void){
	ES_t Local_enuErrorState=ES_OK;
	DIO_enuSetPinValue(BUZZER_GROUP,BUZZER_PIN,DIO_u8HIGH);
	return Local_enuErrorState;
}
ES_t BUZZER_enuOFF(void){
	ES_t Local_enuErrorState=ES_OK;
		DIO_enuSetPinValue(BUZZER_GROUP,BUZZER_PIN,DIO_u8LOW);
		return Local_enuErrorState;
}
ES_t BUZZER_enuFireAlarm(void){
	ES_t Local_enuErrorState=ES_OK;
	BUZZER_enuON();
	_delay_ms(50);
	BUZZER_enuOFF();
	_delay_ms(50);
	return Local_enuErrorState;
}
