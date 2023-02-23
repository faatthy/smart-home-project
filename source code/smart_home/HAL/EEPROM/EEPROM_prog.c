/*
 * EEPROM_prog.c
 *
 *  Created on: Feb 7, 2023
 *      Author: fathy
 */
#include "../../LIBRARY/errorState.h"
#include "../../LIBRARY/stdTypes.h"
#include"../../MCAL/IIC/IIC_int.h"
#include"EEPROM_priv.h"
#include "EEPROM_conf.h"

ES_t EEPROM_enuInit(void)
{
	ES_t Local_enuErrorState=ES_OK;
	IIC_enuInit();
	return Local_enuErrorState;
}
ES_t EEPROM_enuWrite(u8 Copy_u8Data,u8 Copy_u8PageAddress,u8 Copy_u8ByteAddress)
{
	ES_t Local_enuErrorState=ES_OK;
	if(Copy_u8PageAddress < 8)
	{
		IIC_enuStartCondition();
		IIC_enuSendSlaveAddressWrite((0x50 | Copy_u8PageAddress));
		IIC_enuSendData(Copy_u8ByteAddress);
		IIC_enuSendData(Copy_u8Data);
		IIC_enuStopCondition();
	}
	else{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}
ES_t EEPROM_enuRead(u8* Copy_u8Data,u8 Copy_u8PageAddress,u8 Copy_u8ByteAddress)
{
	ES_t Local_enuErrorState=ES_OK;
		if(Copy_u8PageAddress < 8)
		{
	u8 Local_u8Data = 0;
	IIC_enuStartCondition();
	IIC_enuSendSlaveAddressWrite((0x50 | Copy_u8PageAddress));
	IIC_enuSendData(Copy_u8ByteAddress);
	IIC_enuRepeatedStart();
	IIC_enuSendSlaveAddressRead((0x50 | Copy_u8PageAddress));
	IIC_enuReadDataNoAck(&Local_u8Data);
	*Copy_u8Data=Local_u8Data;
	IIC_enuStopCondition();
		}
		else{
				Local_enuErrorState=ES_OUT_OF_RANGE;
			}

	return Local_enuErrorState;
}
