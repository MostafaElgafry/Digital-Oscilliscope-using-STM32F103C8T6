#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER2_interface.h"
#include "TIMER2_private.h"
#include "TIMER2_config.h"


void (*HHH)(void) = 0;

void SH(void (*func)(void))
{
	HHH=func;
}

void MTIMER2_voidInit()
{

	/*TIMER2->CR1 |= 1<<2;
		TIMER2->DIER = 1;
		TIMER2->PSC = 23999;
		TIMER2->ARR = 1000;
		TIMER2->CR1 = 1;
		*/

	TIMER2->CCMR2 = (1<<8);
	

	TIMER2->CCER = 1<<12;
	

	TIMER2->PSC = 0;

	TIMER2->CR1 = 1;

}

void MTIMER2_voidClearFlags(void)
{
	TIMER2->SR = 0;
}

u16 MTIMER2_u16ReadCapture(u8 Copy_u8Channel)
{
	if (Copy_u8Channel == 1)
		return TIMER2->CCR1;
	else if (Copy_u8Channel == 2)
		return TIMER2->CCR2;
	else if (Copy_u8Channel == 3)
		return TIMER2->CCR3;
	else if (Copy_u8Channel == 4)
		return TIMER2->CCR4;
	else 
		return 0;
}

void MTIMER2_voidSetCallBack(u8 Copy_u8Interrupt, void (*Copy_ptrCall)(void))
{
	if (Copy_u8Interrupt == TIMER2_UPDATE_INTERRUPT)
		UpdateCall = Copy_ptrCall;
	else if (Copy_u8Interrupt>=TIMER2_CH1_CAPT && Copy_u8Interrupt<=TIMER2_CH4_CAPT)
		CaptureCompareCall[Copy_u8Interrupt-1] = Copy_ptrCall;
	else if (Copy_u8Interrupt == TIMER2_TRIGGER_INTERRUPT)
		TriggerCall = Copy_ptrCall;
	else if (Copy_u8Interrupt>=TIMER2_CH1_OVCAPT && Copy_u8Interrupt<=TIMER2_CH4_OVCAPT)
		OverCaptureCompareCall[Copy_u8Interrupt-9]=Copy_ptrCall;
}

void MTIMER2_voidEnableInterrupt(u8 Copy_u8Interrupt)
{
	TIMER2->DIER |= 1<<Copy_u8Interrupt;
}

void MTIMER2_voidDisableInterrupt(u8 Copy_u8Interrupt)
{
	TIMER2->DIER &= ~(1<<Copy_u8Interrupt);
}
void MTIMER2_voidClearCounter(void)
{
	TIMER2->CNT =0;
}
void TIM2_IRQHandler(void)
{
	if (GET_BIT(TIMER2->SR,0))
	{
		if(UpdateCall !=0)
			UpdateCall();
		CLR_BIT(TIMER2->SR,0);
	}
	else if(GET_BIT(TIMER2->SR,1))
	{
		if(CaptureCompareCall[0] !=0)
			CaptureCompareCall[0]();
		CLR_BIT(TIMER2->SR,1);
	}
	else if(GET_BIT(TIMER2->SR,2))
		{
			if(CaptureCompareCall[1] !=0)
				CaptureCompareCall[1]();
			CLR_BIT(TIMER2->SR,2);
		}
	else if(GET_BIT(TIMER2->SR,3))
		{
			if(CaptureCompareCall[2] !=0)
				CaptureCompareCall[2]();
			CLR_BIT(TIMER2->SR,3);
		}
	else if (GET_BIT(TIMER2->SR,4))
	{
		if (CaptureCompareCall[3] !=0)
				CaptureCompareCall[3]();
		CLR_BIT(TIMER2->SR,4);
	}
	else if(GET_BIT(TIMER2->SR,6))
		{
			if(TriggerCall !=0)
				TriggerCall();
			CLR_BIT(TIMER2->SR,6);
		}
	else if(GET_BIT(TIMER2->SR,9))
		{
			if(OverCaptureCompareCall[0] !=0)
				OverCaptureCompareCall[0]();
			CLR_BIT(TIMER2->SR,9);
		}
	else if(GET_BIT(TIMER2->SR,10))
		{
			if(OverCaptureCompareCall[1] !=0)
				OverCaptureCompareCall[1]();
			CLR_BIT(TIMER2->SR,10);
		}
	else if(GET_BIT(TIMER2->SR,11))
		{
			if(OverCaptureCompareCall[2] !=0)
				OverCaptureCompareCall[2]();
			CLR_BIT(TIMER2->SR,11);
		}
	else if(GET_BIT(TIMER2->SR,12))
		{
			if(OverCaptureCompareCall[3] !=0)
				OverCaptureCompareCall[3]();
			CLR_BIT(TIMER2->SR,12);
		}
}
