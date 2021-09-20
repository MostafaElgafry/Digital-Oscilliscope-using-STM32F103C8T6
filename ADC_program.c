/*****************************************/
/* Author  :  Ahmed Fawzy                */
/* Version :  V01                        */
/* Date    : 26 october 2020             */
/*****************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
 

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"



/* Configure the type of transfer */
void MADC_voidInit(void)
{
	/*
		Enable Interrupt of end of conversion 
		Conversion Sampling
		Data Right Alignment
		Enable DMA
		power on
		Enable callibration	
	*/
	ADC -> CR1    |= (ADC_END_OF_CONV_INTERRUPT << 5) | (1<<11);
	ADC -> SMPRA2 |= (ADC_SAMPLE);
	ADC -> CR2    |= (ADC_CONT_CON << 1) | (ADC_DMA_MODE << 8) | (ADC_DATA_ALIGNMENT << 11) | (ADC_POWER) ;
	MSTK_voidSetBusyWait(1000); // Delay 1 microsecond for first time power on

	MSTK_voidSetBusyWait(10); // Delay 1 microsecond for stablity time for power
	ADC -> CR2    |= (ADC_CAL << 2) ;
	MSTK_voidSetBusyWait(10); // Delay 1 microsecond for calibration cycles

	ADC->CR2 |= 7<<17;			//manual trigger
	ADC->CR2 |= (ADC_POWER) ;
}

u16	MADC_u16GetData(u8 Copy_u8Channel)
{
	/*Select Channel*/
	ADC->CR1 &= ~(0xF);
	ADC->CR1 |= Copy_u8Channel & 0xF;

	/*Start the Conversion*/
	SET_BIT(ADC->CR2,0);
	/*wait till it finishes*/
	while(!GET_BIT(ADC->SR,1));

	/*clear end of conversion flag*/
	CLR_BIT(ADC->SR,1);

	/*return the result*/
	return ADC->DR;
}

/* Callback function */
void MADC_voidCallBack(void(*ptr)(u16 Copy_u16ADCRead))
{
	ADC_pCallBack = ptr ;
}

/* ISR interrupt function for channel 1 */
void ADC1_2_IRQHandler(void)
{
	if((GET_BIT(ADC->SR,1)) && ADC_pCallBack != 0 ) /*Clear Interrupt flag*/
	{
		ADC_pCallBack(ADC->DR);  /* process the callback function at the end of conversion */
	}
	
};
