//Author	:		Mohamed Gamal
//Date		:		22 August 2020
//Version	:		V01

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_private.h"
#include "EXTI_interface.h"
#include "EXTI_config.h"




void MEXTI_voidInit(){
	
		
	#if 	EXTI_MODE == RISING
		SET_BIT((EXTI->RTSR),EXTI_LINE);
	#elif	EXT_MODE == FALLING
		SET_BIT((EXTI->FTSR),EXTI_LINE);
	#elif 	EXT_MODE == ON_CHANGE
		SET_BIT((EXTI->RTSR),EXTI_LINE);
		SET_BIT((EXTI->FTSR),EXTI_LINE);
	#else 
		#error "Wrong MODE OR LINE !!"
	#endif
	/*disable interrupt*/
	CLR_BIT(EXTI->IMR,EXTI_LINE);
	for (u8 i=0;i<16;i++)
		EXTI_CallBack[i] = 0;
}
void MEXTI_voidEnableEXTI(u8 Copy_u8Line){
	SET_BIT(EXTI->IMR, Copy_u8Line);
}

void MEXTI_voidDisableEXTI(u8 Copy_u8Line){
	CLR_BIT(EXTI->IMR,Copy_u8Line);
}

void MEXTI_voidSwTrigger(u8 Copy_u8Line){
	SET_BIT(EXTI->IMR,Copy_u8Line);
	SET_BIT(EXTI->SWIER,Copy_u8Line);
}

void MEXTI_voidSetSignalLatch(u8 Copy_u8Line, u8 Copy_u8Mode){
	switch (Copy_u8Mode){
		case RISING_EDGE	:	SET_BIT(EXTI->RTSR, Copy_u8Line); break;
		case FALLING_EDGE	:	SET_BIT(EXTI->FTSR, Copy_u8Line); break;
		case ON_CHANGE		:	SET_BIT(EXTI->RTSR, Copy_u8Line);
								SET_BIT(EXTI->FTSR, Copy_u8Line); break;
		default:	/*return error*/	break;
	}
	SET_BIT(EXTI->IMR,Copy_u8Line);
}

void MEXTI_voidSetCallBack(u8 Copy_u8Line,void (*Copy_ptr)(void)){
	if (Copy_u8Line > 16)
		return;
	EXTI_CallBack[Copy_u8Line] = Copy_ptr;
}

u8 MEXTI_u8GetInterruptStatus(u8 Copy_u8IntID)
{
	return GET_BIT(EXTI->PR,Copy_u8IntID);
}

void EXTI0_IRQHandler(void){

	EXTI_CallBack[0]();
	SET_BIT(EXTI->PR,0);
}

void EXTI1_IRQHandler(void){

	EXTI_CallBack[1]();
	SET_BIT(EXTI->PR,1);
}
void EXTI2_IRQHandler(void){
	EXTI_CallBack[2]();
	SET_BIT(EXTI -> PR,2);
}

void EXTI3_IRQHandler(void){
	EXTI_CallBack[3]();
	SET_BIT(EXTI -> PR,3);
}

void EXTI4_IRQHandler(void){
	EXTI_CallBack[4]();
	SET_BIT(EXTI -> PR,4);
}

void EXTI9_5_IRQHandler(void){
	if (GET_BIT(EXTI -> PR,5) && EXTI_CallBack[5] != 0)
		{
			 EXTI_CallBack[5]();
			 SET_BIT(EXTI -> PR,5);
			 return;
		}
	if (GET_BIT(EXTI -> PR,6) && EXTI_CallBack[6] != 0)
		{
				 EXTI_CallBack[6]();
				 SET_BIT(EXTI -> PR,6);
				 return;
		}
	if (GET_BIT(EXTI -> PR,7) && EXTI_CallBack[7] != 0)
		{
				 EXTI_CallBack[7]();
				 SET_BIT(EXTI -> PR,7);
				 return;
		}
	if (GET_BIT(EXTI -> PR,8) && EXTI_CallBack[8] != 0)
		{
				 EXTI_CallBack[8]();
				 SET_BIT(EXTI -> PR,8);
				 return;
		}
	if (GET_BIT(EXTI -> PR,9) && EXTI_CallBack[9] != 0)
		{
				 EXTI_CallBack[9]();
				 SET_BIT(EXTI -> PR,9);
				 return;
		}
}
void EXTI15_10_IRQHandler(void){
	 if (GET_BIT(EXTI -> PR,10) && EXTI_CallBack[10] != 0)
	 	 {
		 EXTI_CallBack[10]();
		 SET_BIT(EXTI -> PR,10);
		 return;
	 	 }
	 if (GET_BIT(EXTI -> PR,11) && EXTI_CallBack[11] != 0)
	 	 {
	 		 EXTI_CallBack[11]();
	 		 SET_BIT(EXTI -> PR,11);
	 		return;
	 	 }
	 if (GET_BIT(EXTI -> PR,12) && EXTI_CallBack[12] != 0)
	 	 {
	 		 EXTI_CallBack[12]();
	 		 SET_BIT(EXTI -> PR,12);
	 		return;
	 	 }
	 if (GET_BIT(EXTI -> PR,13) && EXTI_CallBack[13] != 0)
	 	 {
	 		 EXTI_CallBack[13]();
	 		 SET_BIT(EXTI -> PR,13);
	 		return;
	 	 }
	 if (GET_BIT(EXTI -> PR,14) && EXTI_CallBack[14] != 0)
	 	 {
	 		 EXTI_CallBack[14]();
	 		 SET_BIT(EXTI -> PR,14);
	 		return;
	 	 }
	 if (GET_BIT(EXTI -> PR,15) && EXTI_CallBack[15] != 0)
	 	 {
	 		 EXTI_CallBack[15]();
	 		 SET_BIT(EXTI -> PR,15);
	 		return;
	 	 }
}
