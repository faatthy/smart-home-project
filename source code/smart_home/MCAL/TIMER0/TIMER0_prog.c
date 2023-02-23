#include"../../LIBRARY/errorState.h"
#include"../../LIBRARY/stdTypes.h"
#include"../DIO/DIO_int.h"
#include<math.h>

#include "../TIMER0/TIMER_priv.h"
#include "../TIMER0/TIMER0_conf.h"
static void (*ptr_ovf)(void)=NULL;
static void (*ptr_Ctc)(void)=NULL;
u16 Timer0_Num_OVF = 0;
u8 Timer0_Init_Value = 0;
ES_t TIMER0_enuInit(void){
	ES_t local_enuErrorState=ES_OK;

#if TIMER0_MODE==NORMAL_MODE
	TCCR0=0X00;
	//TIMSK|=(1<<0);
#elif TIMER0_MODE==CTC_MODE
	TCCR0|=(1<<3);
//	TIMSK|=(1<<1);
#elif
	local_enuErrorState=ES_NOK;
#endif
	return local_enuErrorState;
}
ES_t TIMER0_enuStart(void){
	ES_t local_enuErrorState=ES_OK;
	TCCR0&=~(7<<0);
#if TIMER0_PRES ==PRES_0
	//do nothing
#elif TIMER0_PRES==PRES_1
	TCCR0|=(1<<0);
#elif TIMER0_PRES==PRES_8
	TCCR0|=(1<<1);
#elif TIMER0_PRES==PRES_64
	TCCR0|=(3<<0);
#elif TIMER0_PRES==PRES_256
	TCCR0|=(1<<2);
#elif TIMER0_PRES==PRES_1024
	TCCR0|=(5<<0);
#elif TIMER0_PRES==PRES_FALL
	TCCR0|=(6<<0);
#elif TIMER0_PRES==PRES_RISE
	TCCR0|=(7<<0);
#elif
	local_enuErrorState=ES_NOK;
#endif
#if TIMER0_MODE==CTC_MODE
#if OC0_MODE==DISCONNECTED
	TCCR0&=~(3<<4);
#elif OC0_MODE==TOGGLE
	TCCR0|=(1<<4);
#elif OC0_MODE==CLEAR
	TCCR0|=(1<<5);
#elif OC0_MODE==SET
	TCCR0|=(3<<4);
#elif
	local_EnuErrorState=ES_NOK;
#endif
#endif
	return local_enuErrorState;

	}
ES_t TIMER0_enuStop(void){
	TCCR0&=~(7<<0);
	return ES_OK;
}
ES_t TIMER0_enuDelay(u16 copy_u16millisec){
	ES_t local_enuerrorState=ES_OK;
	u16 local_u16Num_ov,local_u16TimeInitial;
	double local_doubleTimeMaxDelay,local_doubleTimetick;
	u32 local_u32OverFlowCounnt=0;

	local_doubleTimetick = 1024.0/16000.0;   // pres/F_CPU

	local_doubleTimeMaxDelay= 256.0*1024.0/16000.0; //ms		Tmaxdelay = Ttick * 2^8
	if(copy_u16millisec<local_doubleTimeMaxDelay){
		local_u16TimeInitial = (local_doubleTimeMaxDelay-copy_u16millisec)/local_doubleTimetick;
		local_u16Num_ov = 1;

	}else if(copy_u16millisec == (int)local_doubleTimeMaxDelay){
		local_u16TimeInitial=0;
		local_u16Num_ov=1;
	}else{
		local_u16Num_ov = ceil((double)copy_u16millisec/local_doubleTimeMaxDelay);
		local_u16TimeInitial= (1<<8) - ((double)copy_u16millisec/local_doubleTimetick)/local_u16Num_ov;

	}
	TCNT0 = local_u16TimeInitial;
	TIMER0_enuStart();

	while(local_u32OverFlowCounnt<local_u16Num_ov){

		while(((TIFR>>0)&1)==0);

		TIFR|=(1<<0);

		local_u32OverFlowCounnt++;
	}

	TCCR0=0x00;
	return local_enuerrorState;
}






ES_t TIMER0_enuCallBack(void (*fun)(void)){
	ES_t Local_enuErrorState=ES_OK;
#if TIMER0_MODE==NORMAL_MODE
	ptr_ovf=fun;
#elif TIMER0_MODE==CTC_MODE
	ptr_Ctc=fun;
#elif
	Local_enuErrorState=ES_NOK;
#endif
	return Local_enuErrorState;

}
ES_t PWM0_enuInit(void){
ES_t Local_enuErrorState=ES_OK;
#if PWM0_MODE==FAST_PWM_MODE
TCCR0|=(1<<3);
TCCR0|=(1<<6);
#elif PWM0_MODE==PHASE_PWM_MODE
TCCR0|=(1<<6);
#elif
Local_enuErrorState=ES_NOK;
#endif
#if OUTPUT_MODE==NON_INVERTED
TCCR0|=(1<<5);
#elif OUTPUT_MODE==INVERTED
TCCR0|=(3<<4);
#elif
Local_enuErrorState=ES_NOK;
#endif
return Local_enuErrorState;

	}
ES_t PWM0_enuSetDuty(u8 Copy_u8Duty){
	ES_t Local_enuErrorState=ES_OK;
	if(Copy_u8Duty < 0)
			Copy_u8Duty = 0;
		else if(Copy_u8Duty > 100)
			Copy_u8Duty = 100;

		#if TIMER0_MODE==FAST_PWM_MODE
			#if OUTPUT_MODE == NON_INVERTED
				OCR0 = !Duty_Cycle? 0 : ((Duty_Cycle / 100) * 256) - 1;

			#elif OUTPUT_MODE == INVERTED
				OCR0 = Duty_Cycle == 100? 0 : 255 - ((Duty_Cycle / 100) * 256);

			#endif
		#elif TIMER0_MODE == PHASE_PWM_MODE
			#if OUTPUT_MODE == NON_INVERTED
				OCR0 = Duty_Cycle * 255 / 100;

			#elif OUTPUT_MODE== INVERTED
				OCR0 = 255 - (Duty_Cycle * 255 / 100);

			#endif
		#endif

return Local_enuErrorState;
}
ES_t PWM0_enuStart(){
	TIMER0_enuStart();
	return ES_OK;
}
ES_t PWM0_enuStop(){
	TIMER0_enuStop();
	return ES_OK;
}
void __vector_10(void)__attribute__((signal));
	void __vector_10 (void)
	{static u32 local_enu32count=0;
	local_enu32count++;

		if (ptr_Ctc != NULL)
		{

			if(local_enu32count == 1 && Timer0_Num_OVF ==local_enu32count)
				{

					ptr_Ctc();

					local_enu32count = 0;
					OCR0 = Timer0_Init_Value;
				}
				else if(local_enu32count== 1)
					OCR0 = 255;
				else if(Timer0_Num_OVF == local_enu32count)
				{
					// Write your code here


					local_enu32count= 0;
					OCR0 = Timer0_Init_Value;
				}
		}
	}

/******************OVF*************/
void __vector_11 (void)__attribute__((signal));
void __vector_11(void)
{static u32 local_enu32counter=0;

     local_enu32counter++;
	if (ptr_ovf != NULL)
	{

		if(local_enu32counter==Timer0_Num_OVF){
			TCNT0=Timer0_Init_Value;
			local_enu32counter=0;
			ptr_ovf();
		}
	}


}
