/*
 * TIMER_int.h
 *
 *  Created on: Oct 8, 2022
 *      Author: fathy
 */

#ifndef MCAL_TIMER0_TIMER0_INT_H_
#define MCAL_TIMER0_TIMER0_INT_H_

ES_t TIMER0_enuInit(void);
ES_t TIMER0_enuStart(void);
ES_t TIMER0_enuDelay(u16 copy_u16millisec);





ES_t TIMER0_enuCallBack(void (*fun)(void),u8 timerID ,u8 mode);
ES_t PWM0_enuInit(void);
ES_t PWM0_enuSetDuty(u8 Copy_u8Duty);
ES_t PWM0_enuStart(void);

ES_t TIMER0_enuStop(void);
ES_t PWM0_enuStop(void);
#endif /* MCAL_TIMER0_TIMER0_INT_H_ */
