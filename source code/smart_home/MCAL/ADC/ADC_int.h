/*
 * ADC_int.h
 *
 *  Created on: Oct 7, 2022
 *      Author: fathy
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

ES_t ADC_enuInit(void);

ES_t ADC_enuSelectChannel(u8 Copy_u8ChannelID);

ES_t ADC_enuStartConversion(void);

ES_t ADC_enuEnableAutoTrigger(u8 Copy_u8TiggerSource);

ES_t ADC_enuDisableAutoTrigger(void);

ES_t ADC_enuRead(u16 * Copy_u16ADCValue);

ES_t ADC_enuReadHigh(u8 * Copy_u8ADCValue);

ES_t ADC_enuPollingRead(u16 * Copy_u16ADCValue);

ES_t ADC_enuCallBack(void (* Copy_pFunAppFun)(void));

ES_t ADC_enuEnable(void);
ES_t ADC_enuDisable(void);

ES_t ADC_enuEnableInterrupt(void);
ES_t ADC_enuDisableInterrupt(void);



#endif /* MCAL_ADC_ADC_INT_H_ */
