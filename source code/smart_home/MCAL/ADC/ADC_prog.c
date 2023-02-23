/*
 * ADC_prog.c
 *
 *  Created on: Oct 7, 2022
 *      Author: fathy
 */
#include"../../LIBRARY/stdTypes.h"
#include "../../LIBRARY/errorState.h"
#include"ADC_priv.h"
#include "ADC_conf.h"

static void(*ADC_pFunISRFun)(void) =NULL;


ES_t ADC_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	ADCSRA &= 0xF8;
#if ADC_PRES == PRES_64
	ADCSRA |= 6;
#endif

	ADMUX &= 0x3F;
#if ADC_VREF == AVCC_REF
	ADMUX |= (1<<6);
#endif

#if ADC_ADJUST == LEFT_ADJUST
	ADMUX |= (1<<5);
#endif

#if INIT_CHNNL >=0 && INIT_CHNNL <=31
	ADMUX &= 0xE0;
	ADMUX |= INIT_CHNNL;
#endif

#if ADC_INTERRUPT_MODE == INTERRUPT
	ADCSRA |= (1<<3);
#elif ADC_INTERRUPT_MODE == POLLING
	ADCSRA &=~ (1<<3);
#endif

#if ADC_TRIGGER_SOURCE == SINGLE
	ADCSRA &= ~(1<<5);
#endif

	//enable ADC peripheral
	ADCSRA |= (1<<7);

	return Local_enuErrorState;
}
ES_t ADC_enuSelectChannel(u8 Copy_u8ChannelID)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_u8ChannelID < 32 )
	{
		ADMUX &= 0xE0; // ADMUX &= ~ 0x1F; //ADMUX &= ~(31<<0) ;
		ADMUX |= Copy_u8ChannelID;
	}

	return Local_enuErrorState;
}
ES_t ADC_enuStartConversion(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	ADCSRA |= (1<<6);

	return Local_enuErrorState;
}
ES_t ADC_enuEnableAutoTrigger(u8 Copy_u8TiggerSource)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_u8TiggerSource <= 7)
	{
		ADCSRA &=~(1<<5);

		SFIOR &= 0x1F ; // SFIOR &= ~0xE0 ; SFIOR &= ~(7<<5) ;
		SFIOR |= (Copy_u8TiggerSource << 5);

		ADCSRA |= (1<<5);
	}

	return Local_enuErrorState;
}

ES_t ADC_enuDisableAutoTrigger(void)
{
	ADCSRA &=~(1<<5);
	return ES_OK;
}

ES_t ADC_enuRead(u16 * Copy_u16ADCValue)
{
	ES_t Local_enuErrorState = ES_NOK;

#if ADC_ADJUST == RIGHT_ADJUST
	*Copy_u16ADCValue  = ADCL;
	*Copy_u16ADCValue |= ((u16)ADCH << 8);
#elif ADC_ADJUST == LEFT_ADJUST
	*Copy_u16ADCValue  = (ADCL>>6);
	*Copy_u16ADCValue |= ((u16)ADCH<<2);

#else
#error"ADC adjustment is wrong"
#endif

	return Local_enuErrorState;
}

ES_t ADC_enuReadHigh(u8 * Copy_u8ADCValue)
{
	ES_t Local_enuErrorState = ES_NOK;

#if ADC_ADJUST == RIGHT_ADJUST
	*Copy_u8ADCValue  = (ADCL>>2);
	*Copy_u8ADCValue |= ((u16)ADCH << 6);
#warning "to high resolution, it should be left adjust, but now it works"
#elif ADC_ADJUST == LEFT_ADJUST
	*Copy_u8ADCValue  = ADCH;
#else
#error"ADC adjustment is wrong"
#endif

	return Local_enuErrorState;
}

ES_t ADC_enuPollingRead(u16 * Copy_u16ADCValue)
{
	ES_t Local_enuErrorState = ES_NOK;

	while (! ((ADCSRA >> 4) & 1 ));

#if ADC_ADJUST == RIGHT_ADJUST
	*Copy_u16ADCValue  = ADCL;
	*Copy_u16ADCValue |= ((u16)ADCH << 8);
#elif ADC_ADJUST == LEFT_ADJUST
	*Copy_u16ADCValue  = (ADCL>>6);
	*Copy_u16ADCValue |= ((u16)ADCH<<2);
//#warning "to read full resolution, it should be right adjust, but now it works"
#else
#error"ADC adjustment is wrong"
#endif

	ADCSRA |= (1<<4);

	return Local_enuErrorState;
}

ES_t ADC_enuCallBack(void (* Copy_pFunAppFun)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_pFunAppFun != NULL)
	{
		ADC_pFunISRFun = Copy_pFunAppFun;
	}

	return Local_enuErrorState;
}

ES_t ADC_enuEnable(void)
{
	ES_t Local_enuErrorState = ES_NOK;



	return Local_enuErrorState;
}

ES_t ADC_enuDisable(void)

{
	ES_t Local_enuErrorState = ES_NOK;



	return Local_enuErrorState;
}

ES_t ADC_enuEnableInterrupt(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	ADCSRA |= (1<<3);

	return Local_enuErrorState;
}

ES_t ADC_enuDisableInterrupt(void)
{
	ES_t Local_enuErrorState = ES_NOK;



	return Local_enuErrorState;
}




void __vector_16(void)__attribute__((signal));
void __vector_16(void)
{
	if (ADC_pFunISRFun != NULL)
	{
		ADC_pFunISRFun (  );
	}
}
