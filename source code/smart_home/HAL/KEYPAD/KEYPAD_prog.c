/*
 * KEYPAD_prog.c
 *
 *  Created on: Jan 28, 2023
 *      Author: fathy
 */

#include"../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include"../../MCAL/DIO/DIO_int.h"
#include"KEYPAD_conf.h"
#include "KEYPAD_priv.h"
#include<util/delay.h>
ES_t KEYPAD_enuInit(void){
	ES_t local_errorState=ES_NOK;
	DIO_enuSetPinDirection(KEYPAD_u8C1_GRPOUP,KEYPAD_u8C1_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(KEYPAD_u8C2_GRPOUP,KEYPAD_u8C2_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(KEYPAD_u8C3_GRPOUP,KEYPAD_u8C3_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(KEYPAD_u8C4_GRPOUP,KEYPAD_u8C4_PIN,DIO_u8OUTPUT);


	DIO_enuSetPinDirection(KEYPAD_u8R1_GRPOUP,KEYPAD_u8R1_PIN,DIO_u8INPUT);
	DIO_enuSetPinDirection(KEYPAD_u8R2_GRPOUP,KEYPAD_u8R2_PIN,DIO_u8INPUT);
	DIO_enuSetPinDirection(KEYPAD_u8R3_GRPOUP,KEYPAD_u8R3_PIN,DIO_u8INPUT);
	DIO_enuSetPinDirection(KEYPAD_u8R4_GRPOUP,KEYPAD_u8R4_PIN,DIO_u8INPUT);



	    DIO_enuSetPinValue(KEYPAD_u8C1_GRPOUP,KEYPAD_u8C1_PIN,DIO_u8HIGH);
		DIO_enuSetPinValue(KEYPAD_u8C2_GRPOUP,KEYPAD_u8C2_PIN,DIO_u8HIGH);
		DIO_enuSetPinValue(KEYPAD_u8C3_GRPOUP,KEYPAD_u8C3_PIN,DIO_u8HIGH);
		DIO_enuSetPinValue(KEYPAD_u8C4_GRPOUP,KEYPAD_u8C4_PIN,DIO_u8HIGH);


		DIO_enuSetPinValue(KEYPAD_u8R1_GRPOUP,KEYPAD_u8R1_PIN,DIO_u8PULL_UP);
		DIO_enuSetPinValue(KEYPAD_u8R2_GRPOUP,KEYPAD_u8R2_PIN,DIO_u8PULL_UP);
		DIO_enuSetPinValue(KEYPAD_u8R3_GRPOUP,KEYPAD_u8R3_PIN,DIO_u8PULL_UP);
		DIO_enuSetPinValue(KEYPAD_u8R4_GRPOUP,KEYPAD_u8R4_PIN,DIO_u8PULL_UP);

		return local_errorState;
}
ES_t KEYPAD_enuGetPressedKey(u8 * Copy_u8Value){
	ES_t local_enuerrorState=ES_NOK;
	u8 Col_Group[]={KEYPAD_u8C1_GRPOUP,KEYPAD_u8C2_GRPOUP,KEYPAD_u8C3_GRPOUP,KEYPAD_u8C4_GRPOUP};
	u8 Col_Pin[]={KEYPAD_u8C1_PIN,KEYPAD_u8C2_PIN,KEYPAD_u8C3_PIN,KEYPAD_u8C4_PIN};

	u8 Row_Group[]={KEYPAD_u8R1_GRPOUP,KEYPAD_u8R2_GRPOUP,KEYPAD_u8R3_GRPOUP,KEYPAD_u8R4_GRPOUP};
	u8 Row_Pin[]={KEYPAD_u8R1_PIN,KEYPAD_u8R2_PIN,KEYPAD_u8R3_PIN,KEYPAD_u8R4_PIN};
	// intile value to variable means neither button pressed
	*Copy_u8Value=0xff;

	u8 local_Value=0;
	u8 Col_Selector=0;
	u8 Row_Selector=0;
	 		u8 flag =0;
for(; Col_Selector<COL_NUM; Col_Selector++)
{
		DIO_enuSetPinValue(Col_Group[Col_Selector],Col_Pin[Col_Selector],DIO_u8LOW);
		for(Row_Selector=0;Row_Selector<ROW_NUM;Row_Selector++){
			DIO_enuGetPinValue(Row_Group[Row_Selector],Row_Pin[Row_Selector],&local_Value);
			// confirm the button is pressed
			if(!local_Value){
				_delay_ms(10);
				DIO_enuGetPinValue(Row_Group[Row_Selector],Row_Pin[Row_Selector],&local_Value);
				if(!local_Value){
					//prevent holding the button
					while(!local_Value){
						DIO_enuGetPinValue(Row_Group[Row_Selector],Row_Pin[Row_Selector],&local_Value);
					}
					u8 local_MatKeyPad[COL_NUM][ROW_NUM]=KEY_VALUES;
					flag=1;
				*Copy_u8Value=local_MatKeyPad[Row_Selector][Col_Selector];
				break;
				}
			}
			}
			DIO_enuSetPinValue(Col_Group[Col_Selector],Col_Pin[Col_Selector],DIO_u8HIGH);
			if(flag){
				local_enuerrorState=ES_OK;
				break;
			}
		}
		return local_enuerrorState;
}


