/*
 * IIC_prog.c
 *
 *  Created on: Feb 7, 2023
 *      Author: fathy
 */
#include "../../LIBRARY/stdTypes.h"
#include "../../LIBRARY/errorState.h"
#include "IIC_priv.h"
#include"IIC_conf.h"
#include <util/delay.h>
ES_t IIC_enuInit(void)
{
	ES_t Local_enuErrorState=ES_OK;
	TWCR&=~(1<<2);
	#if    I2C_MODE      ==   I2C_MASTER
	TWBR = 12;           // 400KHZ
	#elif  I2C_MODE      ==   I2C_SLAVE
	TWAR = ((SLAVE_ADDRESS << 1) | GENERAL_CALL);
	#endif
	TWCR|=(1<<2);
	_delay_ms(10);
	return Local_enuErrorState;
}
ES_t IIC_enuStartCondition(void)
{
	ES_t Local_enuErrorState=ES_OK;
	TWCR|=(1<<5);
	TWCR|=(1<<7);
	while((TWCR>>7) == 0);
	while((TWSR & 0xF8) != START_CONDITION_TRANSMITTED);
	_delay_ms(10);
	return Local_enuErrorState;
}
ES_t IIC_enuSendSlaveAddressWrite(u8 Copy_u8Address)
{
	ES_t Local_enuErrorState=ES_OK;
	TWDR = (Copy_u8Address << 1);
    TWCR|=(1<<7);
	while((TWCR>>7) == 0);
	while((TWSR & 0xF8) != SLAVE_AD_AND_WR_ACK);
	_delay_ms(10);
	return Local_enuErrorState;
}
ES_t IIC_enuSendSlaveAddressRead(u8 Copy_u8Address)
{
	ES_t Local_enuErrorState=ES_OK;
	TWDR = ((Copy_u8Address << 1) | 1);
	TWCR|=(1<<7);
	while((TWCR>>7) == 0);
	while((TWSR & 0xF8) != SLAVE_AD_AND_RD_ACK);
	_delay_ms(10);
	return Local_enuErrorState;
}
ES_t IIC_enuSendData(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_OK;
	TWDR = Copy_u8Data;
    TWCR&=~(1<<5);
	TWCR|=(1<<7);
	while((TWCR>>7)== 0);
	while((TWSR & 0xF8) != WR_BYTE_ACK);
	_delay_ms(100);
	return Local_enuErrorState;
}
ES_t IIC_enuReadData(u8* Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_OK;
	TWCR = 0xC4;
	while((TWCR>>7)==0);
	*Copy_u8Data=TWDR;
	return Local_enuErrorState;

}
ES_t IIC_enuReadDataNoAck(u8* Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_OK;
	TWCR = 0x84;;
	while((TWCR>>7) == 0);
	*Copy_u8Data=TWDR;
	return Local_enuErrorState;
}
ES_t IIC_enuRepeatedStart(void)
{
	ES_t Local_enuErrorState=ES_OK;
	TWCR|=(1<<5);
	TWCR|=(1<<7);
	while((TWCR>>7) == 0);
	while((TWSR & 0xF8) != REP_START_ACK);
	return Local_enuErrorState;
}
ES_t IIC_enuStopCondition(void)
{
	ES_t Local_enuErrorState=ES_OK;
	TWCR|=(1<<4);
		TWCR|=(1<<7);
	_delay_ms(1);
	return Local_enuErrorState;
}
