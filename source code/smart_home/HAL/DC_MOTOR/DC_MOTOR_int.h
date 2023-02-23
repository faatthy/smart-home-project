/*
 * DC_MOTOR_int.h
 *
 *  Created on: Feb 3, 2023
 *      Author: fathy
 */

#ifndef HAL_DC_MOTOR_DC_MOTOR_INT_H_
#define HAL_DC_MOTOR_DC_MOTOR_INT_H_

ES_t DC_MOTOR_enuInit(void);
ES_t DC_MOTOR_enuSetDirection(u8 Copy_u8Direction);
ES_t DC_MOTOR_enuSetSpeed(u8 Copy_u8Speed);
ES_t DC_MOTOR_enuStart(void);
ES_t DC_MOTORenuStop(void);


#define CLOCKWISE 1
#define ANTI_CLOCKWISE 2

#endif /* HAL_DC_MOTOR_DC_MOTOR_INT_H_ */
