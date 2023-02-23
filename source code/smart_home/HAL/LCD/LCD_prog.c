/*
 * LCD_prog.c
 *
 *  Created on: Jan 28, 2023
 *      Author: fathy
 */
#include"../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include"../../MCAL/DIO/DIO_int.h"
#include"LCD_priv.h"
#include"LCD_conf.h"
#include<util/delay.h>
ES_t LCD_enuWriteNLatch(u8 Copy_u8Byte){
	ES_t Local_enuErrorState=ES_OK;
	DIO_enuSetPinValue(LCD_u8RW_GROUP,LCD_u8RW_PIN,DIO_u8LOW);
	DIO_enuSetPinValue(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8LOW);

#if LCD_MODE==EIGHT_BIT
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D7_PIN,(Copy_u8Byte>>7)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D6_PIN,(Copy_u8Byte>>6)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D5_PIN,(Copy_u8Byte>>5)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D4_PIN,(Copy_u8Byte>>4)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D3_PIN,(Copy_u8Byte>>3)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D2_PIN,(Copy_u8Byte>>2)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D1_PIN,(Copy_u8Byte>>1)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D0_PIN,(Copy_u8Byte>>0)&DIO_u8BIT_MASK);
#elif LCD_MODE==FOUR_BIT
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D7_PIN,(Copy_u8Byte>>7)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D6_PIN,(Copy_u8Byte>>6)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D5_PIN,(Copy_u8Byte>>5)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D4_PIN,(Copy_u8Byte>>4)&DIO_u8BIT_MASK);
	DIO_enuSetPinValue(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8HIGH);
	_delay_ms(1);
	DIO_enuSetPinValue(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8LOW);
	_delay_ms(2);
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D7_PIN,((Copy_u8Byte>>3)&1));
	DIO_enuSetPinValue(LCD_u8D6_GROUP,LCD_u8D6_PIN,((Copy_u8Byte>>2)&1));
	DIO_enuSetPinValue(LCD_u8D5_GROUP,LCD_u8D5_PIN,((Copy_u8Byte>>1)&1));
	DIO_enuSetPinValue(LCD_u8D4_GROUP,LCD_u8D4_PIN,((Copy_u8Byte>>0)&1));
	DIO_enuSetPinValue(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8HIGH);
	_delay_ms(1);
	DIO_enuSetPinValue(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8LOW);
	_delay_ms(2);
	#else
					Local_enuErrorState=ES_OUT_OF_RANGE;
	#endif

					return Local_enuErrorState;
}
ES_t LCD_enuInit(void){
	ES_t Local_enuErrorState=ES_OK;
	DIO_enuSetPinDirection(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(LCD_u8RW_GROUP,LCD_u8RW_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8OUTPUT);

	DIO_enuSetPinDirection(LCD_u8D7_GROUP,LCD_u8D7_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(LCD_u8D6_GROUP,LCD_u8D6_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(LCD_u8D5_GROUP,LCD_u8D5_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(LCD_u8D4_GROUP,LCD_u8D4_PIN,DIO_u8OUTPUT);
#if LCD_MODE== EIGHT_BIT
	DIO_enuSetPinDirection(LCD_u8D3_GROUP,LCD_u8D3_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(LCD_u8D2_GROUP,LCD_u8D2_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(LCD_u8D1_GROUP,LCD_u8D1_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(LCD_u8D0_GROUP,LCD_u8D0_PIN,DIO_u8OUTPUT);

	DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8OW);
	LCD_enuWriteNLatch(0x38);
#elif LCD_MODE==FOUR_BIT
	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D7_PIN,0);
	DIO_enuSetPinValue(LCD_u8D6_GROUP,LCD_u8D6_PIN,0);
	DIO_enuSetPinValue(LCD_u8D5_GROUP,LCD_u8D5_PIN,1);
	DIO_enuSetPinValue(LCD_u8D4_GROUP,LCD_u8D4_PIN,0);
	DIO_enuSetPinValue(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8HIGH);
	_delay_ms(1);
	DIO_enuSetPinValue(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8LOW);
		_delay_ms(2);
		DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);

	      LCD_enuWriteNLatch(0x28);
#else
	      Local_enuErrorState=ES_outES_OUT_OF_RANGE;
#endif
	      //desplay on off

	     	      DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);
	     	      LCD_enuWriteNLatch(0X0F);
	     	      //desplay clear
	     	     DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);
	     	    	     	      LCD_enuWriteNLatch(0X01);
	     	    	     	      //set mode (increasing or decreasing)and the cursor
	     	    	     	     DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);
	     	    	     	    	      LCD_enuWriteNLatch(0X06);
	      return Local_enuErrorState;
}
ES_t LCD_enuWriteData(u8 Copy_u8Data){
	ES_t Local_enuErrorState=ES_OK;
	DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8HIGH);
	LCD_enuWriteNLatch(Copy_u8Data);
	return Local_enuErrorState;
}
ES_t LCD_enuWriteCommand(u8 Copy_u8Command){
	ES_t Local_enuErrorState=ES_OK;
	DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);
			      LCD_enuWriteNLatch(Copy_u8Command);
			      return Local_enuErrorState;
}

ES_t LCD_enuWriteString(const char*Copy_String){
	ES_t Local_enuErrorState=ES_OK;
	while(*Copy_String!=0){
			DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8HIGH);
			LCD_enuWriteNLatch(*Copy_String++);
		}
	return Local_enuErrorState;
}
ES_t LCD_enuClearScreen(void){
	ES_t Local_enuErrorState=ES_OK;
	DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);
	LCD_enuWriteNLatch(0x01);
	LCD_enuWriteCommand(0x80);           //GO TO POSITION ZER0
	return Local_enuErrorState;
}
ES_t LCD_enuShiftDisplayRight(void){
	ES_t Local_enuErrorState=ES_OK;
	LCD_enuWriteCommand(0x18);
	return Local_enuErrorState;
}
ES_t LCD_enuShiftDisplayLeft(void){
	ES_t Local_enuErrorState=ES_OK;
	LCD_enuWriteCommand(0x1c);
	return Local_enuErrorState;
}
ES_t LCD_enuSetCgram(u8 * Copy_u8Array,u8 Copy_u8Position,u8 Copy_u8Num_Char){
	ES_t Local_enuErrorState=ES_OK;
	LCD_enuWriteCommand(0x40+8*Copy_u8Position);
		u8 i;
		for(i=0;i<8*Copy_u8Num_Char;i++){
			LCD_enuWriteData(Copy_u8Array[i]);

		}
		return Local_enuErrorState;
}
ES_t LCD_enuSetDdram(u8 Copy_u8Position){
	ES_t local_enuerrorState=ES_NOK;
		LCD_enuWriteCommand(0X80+(8*Copy_u8Position));
		return local_enuerrorState;
}
ES_t LCD_enuWriteCharacter(u8 Copy_u8Char){
	ES_t Local_enuErrorState=ES_OK;
	LCD_enuWriteData(Copy_u8Char);
	return Local_enuErrorState;
}
ES_t LCD_enuWritInteger(u16 Copy_intNumber){
	ES_t Local_enuErrorState=ES_NOK;
int local_intTempNum=Copy_intNumber;
u8 local_u8Length=0;
if(Copy_intNumber==0){
	LCD_enuWriteCharacter('0');
	return Local_enuErrorState;
}
while(local_intTempNum!=0){
	local_intTempNum/=10;
	local_u8Length++;
}
u8 array[local_u8Length];
local_intTempNum=Copy_intNumber;
for(u8 i=local_u8Length;i>0;i--){
	array[i-1]=local_intTempNum%10+'0';
	local_intTempNum/=10;
}
for(u8 i=0;i<local_u8Length;i++){
	LCD_enuWriteCharacter(array[i]);
}
return Local_enuErrorState;
}
ES_t LCD_enuWriteFloat(f32 Copy_floatNumber){
	ES_t Local_enuErrorState=ES_OK;
	u32 Local_u32int=(u32)(Copy_floatNumber);
	LCD_enuWritInteger(Local_u32int);
	LCD_enuWriteCharacter('.');
	u32 Local_u32float=(u32)(1000.0*(Copy_floatNumber-(u32)(Local_u32int)));
    LCD_enuWritInteger(Local_u32float);

	return Local_enuErrorState;
}
ES_t LCD_enuGoToPosition(u8 Copy_u8Row,u8 Copy_u8Col){
	ES_t Local_enuErrorState=ES_OK;
	if(Copy_u8Row<=1&&Copy_u8Col<=16){
		if(Copy_u8Row==0){
			LCD_enuWriteCommand((0x80+Copy_u8Col));
		}
		else if(Copy_u8Row==1){
			LCD_enuWriteCommand((0xC0+Copy_u8Col));
		}
	}
		else{
			Local_enuErrorState=ES_NOK;
		}
		return Local_enuErrorState;

}
