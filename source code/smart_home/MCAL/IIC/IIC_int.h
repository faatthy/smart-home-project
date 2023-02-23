/*
 * IIC_int.h
 *
 *  Created on: Feb 7, 2023
 *      Author: fathy
 */

#ifndef MCAL_IIC_IIC_INT_H_
#define MCAL_IIC_IIC_INT_H_
/*
#define I2C_MASTER                        1
#define I2C_SLAVE                         2
#define START_CONDITION_TRANSMITTED       0x08
#define REP_START_ACK                     0x10		// repeated start
#define SLAVE_AD_AND_WR_ACK               0x18		// master transmit [ slave address + write request ] ACK
#define SLAVE_AD_AND_RD_ACK               0x40		// master transmit [ slave address + read  request ] ACK
#define WR_BYTE_ACK                       0x28		// master transmit data ACK
#define RD_BYTE_WITH_NACK			      0x58		// master received data with NACK
#define RD_BYTE_WITH_ACK			      0x50		// master received data with  ACK
#define SLAVE_ADD_REC_RD_REQ		      0xA8		// slave address received with write request
#define SLAVE_ADD_REC_WR_REQ              0x60		// slave address received with read  request
#define SLAVE_DATA_REC                    0x80		// read  byte request received
#define SLAVE_BYTE_TRANSMITTED            0xC0		// write byte request received
*/
/********************************_PROTOTYPES_***************************************/
ES_t IIC_enuInit(void);
ES_t IIC_enuStartCondition(void);
ES_t IIC_enuSendSlaveAddressWrite(u8 Copy_u8Address);
ES_t IIC_enuSendSlaveAddressRead(u8 Copy_u8Address);
ES_t IIC_enuSendData(u8 Copy_u8Data);
ES_t IIC_enuReadData(u8* Copy_u8Data);
ES_t IIC_enuRepeatedStart(void);
ES_t IIC_enuStopCondition(void);
ES_t IIC_enuReadDataNoAck(u8* Copy_u8Data);


#endif /* MCAL_IIC_IIC_INT_H_ */
