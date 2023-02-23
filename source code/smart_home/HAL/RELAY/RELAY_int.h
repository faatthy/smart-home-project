/*
 * RELAY_int.h
 *
 *  Created on: Feb 5, 2023
 *      Author: fathy
 */

#ifndef HAL_RELAY_RELAY_INT_H_
#define HAL_RELAY_RELAY_INT_H_

ES_t RELAY_enuInit(void);
ES_t RELAY_enuON(u8 Copy_u8NumLed);
ES_t RELAY_enuOF(u8 Copy_u8NumLed);
ES_t RELAY_enuToggle(u8 Copy_u8NumLed);


#define LED_1  1
#define LED_2  2
#define LED_3  3
#define LED_4  4
#define LED_5  5
#endif /* HAL_RELAY_RELAY_INT_H_ */
