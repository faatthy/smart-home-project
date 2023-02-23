/*
 * SERVO_MOTOR_prog.c
 *
 *  Created on: Feb 3, 2023
 *      Author: fathy
 */
#include"../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include"../../MCAL/TIMER1/TIMER1_int.h"
#include "SERVO_MOTOR_priv.h"
#include "SERVO_MOTOR_conf.h"
ES_t SERVO_MOTOR_enuInit(void){
	Pwm1_enuInit();
	Pwm1_enuSetFrequency(50);
	return ES_OK;
}

ES_t SERVO_MOTOR_enuSetPosition(u8 Copy_u8Position){
	ES_t local_enuErrorState=ES_OK;



	 	Pwm1_enuSetDutyCycleChannel_2(Copy_u8Position);


	 	Pwm1_enuStart();
        return local_enuErrorState;
}

ES_t SERVO_MOTOR_enuTurnOff(void){
	Pwm1_enuStop();
	return ES_OK;
}
