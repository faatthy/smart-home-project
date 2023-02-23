/*
 * TIMER1_int.h
 *
 *  Created on: Feb 3, 2023
 *      Author: fathy
 */

#ifndef MCAL_TIMER1_TIMER1_INT_H_
#define MCAL_TIMER1_TIMER1_INT_H_
ES_t TIMER1_enuControlMode(u8 Copy_u8Mode);
ES_t Pwm1_enuInit(void);
ES_t Pwm1_enuSetDutyCycleChannel_1(u8 Local_u8DutyCycle);
ES_t Pwm1_enuSetFrequency(u16 Local_u16Frequency);
ES_t Pwm1_enuStart(void);
ES_t Pwm1_enuStop(void);



#define DOOR_MODE         44
#define LAMP_DIMMER_MODE  55
#endif /* MCAL_TIMER1_TIMER1_INT_H_ */
