/*
 * BUTTON_prog.c
 *
 *  Created on: Feb 8, 2023
 *      Author: fathy
 */
#include "../../LIBRARY/errorState.h"
#include "../../LIBRARY/stdTypes.h"
#include"../../MCAL/DIO/DIO_int.h"
#include "BUTTON_priv.h"
#include "BUTTON_conf.h"
#include <util/delay.h>

ES_t BUTTON_enuInit(void){
	ES_t Local_enuErrorState=ES_OK;
	DIO_enuSetPinDirection(BUTTON_GROUP,BUTTON_PIN,DIO_u8INPUT);
	DIO_enuSetPinValue(BUTTON_GROUP,BUTTON_PIN,DIO_u8FLOAT);
	return Local_enuErrorState;
}
ES_t BUTTON_enuGetValue(u8 * Copy_u8Value){
	ES_t Local_enuErrorState=ES_OK;
	u8 Local_u8Value=0;
			DIO_enuGetPinValue(BUTTON_GROUP,BUTTON_PIN,&Local_u8Value);
			if(Local_u8Value){
				_delay_ms(10);
				DIO_enuGetPinValue(BUTTON_GROUP,BUTTON_PIN,&Local_u8Value);


			}
	*Copy_u8Value=Local_u8Value;
	return Local_enuErrorState;
}
