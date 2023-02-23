/*
 * TEMP_SENSOR_prog.c
 *
 *  Created on: Feb 5, 2023
 *      Author: fathy
 */
#include"../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include"../../MCAL/DIO/DIO_int.h"
#include"TEMP_SENSOR_priv.h"
#include"TEMP_SENSOR_conf.h"
#include"../../MCAL/ADC/ADC_int.h"
u16 read;

ES_t TEMP_SENSOR_enuInit(void){
	ES_t Local_enuErrorState=ES_OK;
	ADC_enuInit();
	ADC_enuStartConversion();
		ADC_enuPollingRead(&read);
	return Local_enuErrorState;
}
u16 TEMP_SENSOR_enuRead(void){
//	ES_t Local_enuErrorState=ES_OK;
//u16 Local_u16Read;

	ADC_enuStartConversion();
	ADC_enuPollingRead(&read);
//	LCD_enuWritInteger(Local_u16Read);
	read=(read*500ul)/1024;
	//*Copy_u16Temp=Local_u16Read;
	//return Local_enuErrorState;
    //LCD_enuWritInteger(Local_u16Read);
return read;

}
