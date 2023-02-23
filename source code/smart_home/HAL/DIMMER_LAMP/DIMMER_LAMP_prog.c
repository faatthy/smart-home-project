/*
 * DIMMER_LAMP_prog.c
 *
 *  Created on: Feb 4, 2023
 *      Author: fathy
 */
#include"../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include"../../MCAL/TIMER1/TIMER1_int.h"
#include"DIMMER_LAMP_priv.h"
#include"DIMMER_LAMP_conf.h"
#include "../../MCAL/DIO/DIO_int.h"
ES_t DIMMER_LAMP_enuInit(void){
	ES_t Local_enuErrorState=ES_OK;
	Pwm1_enuInit();
	Pwm1_enuSetFrequency(50);

	return Local_enuErrorState;
}
ES_t DIMMER_LAMP_enuSetIntensity(u8 Copy_u8Intensity){
ES_t Local_enuErrorState=ES_OK;
if(Copy_u8Intensity<0){
	Copy_u8Intensity=0;
}
else if(Copy_u8Intensity>100){
	Copy_u8Intensity=100;
}
Pwm1_enuSetDutyCycleChannel_1(Copy_u8Intensity);
Pwm1_enuStart();
return Local_enuErrorState;
}
ES_t DIMMER_LAMP_enuStart(void){
	Pwm1_enuStart();
	DIO_enuSetPinValue(Dimmer_GROUP,Dimmer_PIN,DIO_u8HIGH);

	return ES_OK;
}
ES_t DIMMER_LAMP_enuStop(void){

    Pwm1_enuStop();
	return ES_OK;
}
