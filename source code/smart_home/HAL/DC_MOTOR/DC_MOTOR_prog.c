/*
 * DC_MOTOR_prog.c
 *
 *  Created on: Feb 3, 2023
 *      Author: fathy
 */
#include"../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include"../../MCAL/DIO/DIO_int.h"
#include"../../MCAL/TIMER0/TIMER0_int.h"
#include"DC_MOTOR_priv.h"
#include "DC_MOTOR_conf.h"

ES_t DC_MOTOR_enuInit(void){
	ES_t Local_EnuErrorState=ES_OK;
	DIO_enuSetPinDirection(DC_MOTOR_PIN0_GROUP,DC_MOTOR_PIN0_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(DC_MOTOR_PIN1_GROUP,DC_MOTOR_PIN1_PIN,DIO_u8OUTPUT);
	//PWM0_enuInit();
	return Local_EnuErrorState;
}
ES_t DC_MOTOR_enuSetDirection(u8 Copy_u8Direction){
	ES_t Local_EnuErrorState=ES_OK;
	if (Copy_u8Direction==CLOCKWISE){
		DIO_enuSetPinValue(DC_MOTOR_PIN0_GROUP,DC_MOTOR_PIN0_PIN,DIO_u8HIGH);
		DIO_enuSetPinValue(DC_MOTOR_PIN1_GROUP,DC_MOTOR_PIN1_PIN,DIO_u8LOW);
	}
	else if (Copy_u8Direction==ANTI_CLOCKWISE){
		DIO_enuSetPinValue(DC_MOTOR_PIN0_GROUP,DC_MOTOR_PIN0_PIN,DIO_u8LOW);
				DIO_enuSetPinValue(DC_MOTOR_PIN1_GROUP,DC_MOTOR_PIN1_PIN,DIO_u8HIGH);
	}
	else
		Local_EnuErrorState=ES_NOK;
	return Local_EnuErrorState;
}
ES_t DC_MOTOR_enuSetSpeed(u8 Copy_u8Speed){
	ES_t Local_EnuErrorState=ES_OK;
	PWM0_enuSetDuty(Copy_u8Speed);
	return Local_EnuErrorState;

}
ES_t DC_MOTOR_enuStart(void){
	ES_t Local_EnuErrorState=ES_OK;
	PWM0_enuStart();

	return Local_EnuErrorState;
}
ES_t DC_MOTORenuStop(void){
	ES_t Local_EnuErrorState=ES_OK;
	PWM0_enuStop();
	DIO_enuSetPinValue(DC_MOTOR_PIN0_GROUP,DC_MOTOR_PIN0_PIN,DIO_u8LOW);
		DIO_enuSetPinValue(DC_MOTOR_PIN1_GROUP,DC_MOTOR_PIN1_PIN,DIO_u8LOW);
	return Local_EnuErrorState;
}
