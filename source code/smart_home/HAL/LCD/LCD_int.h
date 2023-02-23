/*
 * LCD_int.h
 *
 *  Created on: Jan 28, 2023
 *      Author: fathy
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_

ES_t LCD_enuInit(void);
ES_t LCD_enuWriteData(u8 Copy_u8Data);
ES_t LCD_enuWriteCommand(u8 Copy_u8Command);
ES_t LCD_enuWriteNLatch(u8 Copy_u8Byte);
ES_t LCD_enuWriteString(const char*Copy_String);
ES_t LCD_enuClearScreen(void);
ES_t LCD_enuShiftDisplayRight(void);
ES_t LCD_enuShiftDisplayLeft(void);
ES_t LCD_enuSetCgram(u8 * Copy_u8Array,u8 Copy_u8Position,u8 Copy_u8Num_Char);
ES_t LCD_enuSetDdram(u8 Copy_u8Position);
ES_t LCD_enuWriteCharacter(u8 Copy_u8Char);
ES_t LCD_enuWritInteger(u16 Copy_intNumber);
ES_t LCD_enuWriteFloat(float Copy_floatNumber);
ES_t LCD_enuGoToPosition(u8 Copy_u8Row,u8 Copy_u8Col);

#endif /* HAL_LCD_LCD_INT_H_ */
