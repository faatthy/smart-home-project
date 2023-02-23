/*
 * BUTTON_int.h
 *
 *  Created on: Feb 8, 2023
 *      Author: fathy
 */

#ifndef HAL_BUTTON_BUTTON_INT_H_
#define HAL_BUTTON_BUTTON_INT_H_

ES_t BUTTON_enuInit(void);
ES_t BUTTON_enuGetValue(u8 * Copy_u8Value);

#define PRESSED  1
#endif /* HAL_BUTTON_BUTTON_INT_H_ */
