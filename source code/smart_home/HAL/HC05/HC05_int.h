/*
 * HC05_int.h
 *
 *  Created on: Feb 6, 2023
 *      Author: fathy
 */

#ifndef HAL_HC05_HC05_INT_H_
#define HAL_HC05_HC05_INT_H_
ES_t HC05_enuInit(void);
ES_t HC05_enuSendString(const char* Copy_Data);
ES_t HC05_enuRecieveString(u8* Copy_u8Data);
ES_t HC05_enuRecieveChar(u8* Copy_u8Data);

#endif /* HAL_HC05_HC05_INT_H_ */
