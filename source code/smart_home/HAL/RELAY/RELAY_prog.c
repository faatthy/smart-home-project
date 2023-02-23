/*
 * RELAY_prog.c
 *
 *  Created on: Feb 5, 2023
 *      Author: fathy
 */
#include "../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include  "RELAY_priv.h"
#include "RELAY_conf.h"
#include "../../MCAL/DIO/DIO_int.h"
ES_t RELAY_enuInit(void){
	ES_t Local_EnuErrorState=ES_OK;
	DIO_enuSetPinDirection(RELAY1_GROUP,RELAY1_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(RELAY2_GROUP,RELAY2_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(RELAY3_GROUP,RELAY3_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(RELAY4_GROUP,RELAY4_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(RELAY5_GROUP,RELAY5_PIN,DIO_u8OUTPUT);


    DIO_enuSetPinValue(RELAY1_GROUP,RELAY1_PIN,DIO_u8LOW);
	DIO_enuSetPinValue(RELAY2_GROUP,RELAY2_PIN,DIO_u8LOW);
	DIO_enuSetPinValue(RELAY3_GROUP,RELAY3_PIN,DIO_u8LOW);
	DIO_enuSetPinValue(RELAY4_GROUP,RELAY4_PIN,DIO_u8LOW);
	DIO_enuSetPinValue(RELAY5_GROUP,RELAY5_PIN,DIO_u8LOW);

	return Local_EnuErrorState;
}
ES_t RELAY_enuON(u8 Copy_u8NumLed){
	ES_t Local_enuErrorState=ES_OK;
	switch(Copy_u8NumLed){
	case LED_1:
		DIO_enuSetPinValue(RELAY1_GROUP,RELAY1_PIN,DIO_u8HIGH);
		break;
	case LED_2:
		DIO_enuSetPinValue(RELAY2_GROUP,RELAY2_PIN,DIO_u8HIGH);
		break;
	case LED_3:
			DIO_enuSetPinValue(RELAY3_GROUP,RELAY3_PIN,DIO_u8HIGH);
			break;
	case LED_4:
			DIO_enuSetPinValue(RELAY4_GROUP,RELAY4_PIN,DIO_u8HIGH);
			break;
	case LED_5:
			DIO_enuSetPinValue(RELAY5_GROUP,RELAY5_PIN,DIO_u8HIGH);
			break;
	default:
		Local_enuErrorState=ES_OUT_OF_RANGE;





	}
	return Local_enuErrorState;
}
ES_t RELAY_enuOF(u8 Copy_u8NumLed){
	ES_t Local_enuErrorState=ES_OK;
		switch(Copy_u8NumLed){
		case LED_1:
			DIO_enuSetPinValue(RELAY1_GROUP,RELAY1_PIN,DIO_u8LOW);
			break;
		case LED_2:
			DIO_enuSetPinValue(RELAY2_GROUP,RELAY2_PIN,DIO_u8LOW);
			break;
		case LED_3:
				DIO_enuSetPinValue(RELAY3_GROUP,RELAY3_PIN,DIO_u8LOW);
				break;
		case LED_4:
				DIO_enuSetPinValue(RELAY4_GROUP,RELAY4_PIN,DIO_u8LOW);
				break;
		case LED_5:
				DIO_enuSetPinValue(RELAY5_GROUP,RELAY5_PIN,DIO_u8LOW);
				break;
		default:
			Local_enuErrorState=ES_OUT_OF_RANGE;





		}
		return Local_enuErrorState;
}
ES_t RELAY_enuToggle(u8 Copy_u8NumLed){
	ES_t Local_enuErrorState=ES_OK;
		switch(Copy_u8NumLed){
		case LED_1:
			DIO_enuTogglePinValue(RELAY1_GROUP,RELAY1_PIN);
			break;
		case LED_2:
			DIO_enuTogglePinValue(RELAY2_GROUP,RELAY2_PIN);
			break;
		case LED_3:
				DIO_enuTogglePinValue(RELAY3_GROUP,RELAY3_PIN);
				break;
		case LED_4:
				DIO_enuTogglePinValue(RELAY4_GROUP,RELAY4_PIN);
				break;
		case LED_5:
				DIO_enuTogglePinValue(RELAY5_GROUP,RELAY5_PIN);
				break;
		default:
			Local_enuErrorState=ES_OUT_OF_RANGE;

		}
		return Local_enuErrorState;
}
