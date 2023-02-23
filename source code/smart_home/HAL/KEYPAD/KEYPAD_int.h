/*
 * KEYPAD_int.h
 *
 *  Created on: Jan 28, 2023
 *      Author: fathy
 */

#ifndef HAL_KEYPAD_KEYPAD_INT_H_
#define HAL_KEYPAD_KEYPAD_INT_H_

ES_t KEYPAD_enuInit(void);
ES_t KEYPAD_enuGetPressedKey(u8 * Copy_u8Value);
#define KEY_NOT_PRESSED 255

#endif /* HAL_KEYPAD_KEYPAD_INT_H_ */
