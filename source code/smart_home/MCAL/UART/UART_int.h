/*
 * UART_int.h
 *
 *  Created on: Feb 6, 2023
 *      Author: fathy
 */

#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_

ES_t UART_enuInit(void);

ES_t UART_enuSendChar(u8 Copy_u8Data);

ES_t UART_enuRecieveChar(u8 *Copy_pu8Data);

ES_t UART_enuSendString(const char* Copy_pcData);

ES_t UART_enuRecieveString(char * Copy_pcData);

#endif /* MCAL_UART_UART_INT_H_ */
