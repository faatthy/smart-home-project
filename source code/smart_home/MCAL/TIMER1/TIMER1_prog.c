/*
 * TIMER1_prog.c
 *
 *  Created on: Feb 3, 2023
 *      Author: fathy
 */
#include"../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include"../DIO/DIO_int.h"
#include"TIMER1_priv.h"
#include"TIMER1_conf.h"
#include "../../HAL/LCD/LCD_int.h"
#include "util/delay.h"
ES_t Pwm1_enuInit(void){
	ES_t Local_enuErrorState=ES_OK;
#if PWM1_MODE ==FAST_PWM
	TCCR1A&=~(1<<0);
	TCCR1A|=(1<<1);
	TCCR1B|=(1<<3);
	TCCR1B|=(1<<4);
#endif

#if OUTPUT_MODE==NON_INVERTED
	TCCR1A|=(1<<7);
	TCCR1A&=~(1<<6);
#endif
	DIO_enuSetPinDirection(DIO_u8GROUP_D,DIO_u8PIN5,DIO_u8OUTPUT);


	//CHANNEL 2 INIT
  DIO_enuSetPinDirection(DIO_u8GROUP_D,DIO_u8PIN4,DIO_u8OUTPUT);
	TCCR1A|=(1<<5);
	TCCR1A&=~(1<<4);

	return Local_enuErrorState;
}

ES_t Pwm1_enuSetFrequency(u16 Copy_u16Frequency){

	ICR1 = ((CRYSTAL_FREQUENCY * 1000000) / (Copy_u16Frequency* TIMER1_PRESCALER));
	return ES_OK;
}
ES_t Pwm1_enuSetDutyCycleChannel_1(u8 Copy_f32DutyCycle){
	ES_t Local_enuErrorState=ES_OK;
	if (Copy_f32DutyCycle<0){
		Copy_f32DutyCycle=0;
	}
	else if(Copy_f32DutyCycle>100){
		Copy_f32DutyCycle=100;
	}
	OCR1A = (u16)(Copy_f32DutyCycle *( ICR1/100));


		return Local_enuErrorState;
	}
ES_t Pwm1_enuSetDutyCycleChannel_2(u8 Copy_f32DutyCycle){
	ES_t Local_enuErrorState=ES_OK;
	if (Copy_f32DutyCycle<0){
		Copy_f32DutyCycle=0;
	}
	else if(Copy_f32DutyCycle>100){
		Copy_f32DutyCycle=100;
	}

		OCR1B = (u16)(Copy_f32DutyCycle *( ICR1/100)-1);


		return Local_enuErrorState;
	}


ES_t Pwm1_enuStart(void){
	ES_t local_enuErrorState=ES_OK;

	#if TIMER1_PRESCALER ==NO_CLK
		//do nothing
	#elif TIMER1_PRESCALER==PRESCLNG_1

		TCCR1B|=(1<<0);
	#elif TIMER1_PRESCALER==PRESCLNG_8
		TCCR1B|=(1<<1);
	#elif TIMER1_PRESCALER==PRESCLNG_64
		TCCR1B|=(3<<0);
	#elif TIMER1_PRESCALER==PRESCLNG_256
		TCCR1B|=(1<<2);
	#elif TIMER1_PRESCALER==PRESCLNG_1024
		TCCR1B|=(5<<0);
	#elif TIMER1_PRESCALER=FALLING
		TCCR1B|=(6<<0);
	#elif TIMER0_PRES==RISING
		TCCR1B|=(7<<0);
	#elif
		local_enuErrorState=ES_NOK;
	#endif

		return local_enuErrorState;
}
ES_t Pwm1_enuStop(void){
	TCCR1B&=~(7<<0);
	return ES_OK;
}
