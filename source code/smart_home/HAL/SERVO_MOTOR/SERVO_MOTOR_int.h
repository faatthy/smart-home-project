/*
 * SERVO_MOTOR_int.h
 *
 *  Created on: Feb 3, 2023
 *      Author: fathy
 */

#ifndef HAL_SERVO_MOTOR_SERVO_MOTOR_INT_H_
#define HAL_SERVO_MOTOR_SERVO_MOTOR_INT_H_

ES_t SERVO_MOTOR_enuInit(void);
ES_t SERVO_MOTOR_enuSetPosition(u8 Copy_u8Position);
//ES_t SERVO_MOTOR_enuStart(void);
ES_t SERVO_MOTOR_enuTurnOff(void);


#define  OPEN  10
#define  CLOSE 5
#endif /* HAL_SERVO_MOTOR_SERVO_MOTOR_INT_H_ */
