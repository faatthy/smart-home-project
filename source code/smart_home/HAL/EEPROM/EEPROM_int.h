/*
 * EEPROM_int.h
 *
 *  Created on: Feb 7, 2023
 *      Author: fathy
 */

#ifndef HAL_EEPROM_EEPROM_INT_H_
#define HAL_EEPROM_EEPROM_INT_H_

ES_t EEPROM_enuInit(void);
ES_t EEPROM_enuWrite(u8 Copy_u8Data,u8 Copy_u8PageAddress,u8 Copy_u8ByteAddress);
ES_t EEPROM_enuRead(u8* Copy_u8Data,u8 Copy_u8PageAddress,u8 Copy_u8ByteAddress);
#endif /* HAL_EEPROM_EEPROM_INT_H_ */
