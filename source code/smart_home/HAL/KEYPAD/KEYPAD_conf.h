/*
 * KEYPAD_conf.h
 *
 *  Created on: Jan 28, 2023
 *      Author: fathy
 */

#ifndef HAL_KEYPAD_KEYPAD_CONF_H_
#define HAL_KEYPAD_KEYPAD_CONF_H_

#define COL_NUM				4
#define ROW_NUM				4

#define KEYPAD_u8R1_GRPOUP				 DIO_u8GROUP_C
#define KEYPAD_u8R1_PIN                  DIO_u8PIN2

#define KEYPAD_u8R2_GRPOUP               DIO_u8GROUP_C
#define KEYPAD_u8R2_PIN                  DIO_u8PIN3

#define KEYPAD_u8R3_GRPOUP               DIO_u8GROUP_C
#define KEYPAD_u8R3_PIN                  DIO_u8PIN4

#define KEYPAD_u8R4_GRPOUP               DIO_u8GROUP_C
#define KEYPAD_u8R4_PIN                  DIO_u8PIN5

#define KEYPAD_u8C1_GRPOUP               DIO_u8GROUP_B
#define KEYPAD_u8C1_PIN                  DIO_u8PIN4

#define KEYPAD_u8C2_GRPOUP               DIO_u8GROUP_B
#define KEYPAD_u8C2_PIN                  DIO_u8PIN5

#define KEYPAD_u8C3_GRPOUP               DIO_u8GROUP_B
#define KEYPAD_u8C3_PIN                  DIO_u8PIN6

#define KEYPAD_u8C4_GRPOUP               DIO_u8GROUP_B
#define KEYPAD_u8C4_PIN                  DIO_u8PIN7


#define KEY_VALUES			{  {'7','8','9','/'},\
							   {'4','5','6','*'},\
							   {'1','2','3','-'},\
							   {'c','0','=','+'}  }



#endif /* HAL_KEYPAD_KEYPAD_CONF_H_ */
