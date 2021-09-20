//Author	:		Mohamed Gamal
//Date		:		22 August 2020
//Version	:		V01

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "AFIO_interface.h"
#include "AFIO_config.h"
#include "AFIO_private.h"

void MAFIO_voidSetEXTIConfiguration(u8 Copy_u8Line, u8 Copy_u8PortMap){
	u8 Local_u8RegIndex = 0;
	Local_u8RegIndex = Copy_u8Line / 4;
	Copy_u8Line %= 4;
	AFIO->EXTICR[Local_u8RegIndex] &= ~((0b1111) << (Copy_u8Line*4));
	AFIO->EXTICR[Local_u8RegIndex] |=  ((Copy_u8PortMap) << (Copy_u8Line*4));
}

void MAFIO_voidRemap(u8 Copy_u8Peripheral, u8 Copy_u8Mode)
{
	if ((Copy_u8Peripheral>=0 && Copy_u8Peripheral<=3)
			|| (Copy_u8Peripheral>=15 && Copy_u8Peripheral<=20)
			|| (Copy_u8Peripheral == 12))
	{
		AFIO->MAPR = 1<<Copy_u8Peripheral;
		return;
	}
	AFIO->MAPR &= (0b11<<Copy_u8Peripheral);
	AFIO->MAPR |= Copy_u8Mode<<Copy_u8Peripheral;
}

void MAFIO_voidUnMap(u8 Copy_u8Peripheral)
{
	if ((Copy_u8Peripheral>=0 && Copy_u8Peripheral<=3)
			|| (Copy_u8Peripheral>=15 && Copy_u8Peripheral<=20)
			|| (Copy_u8Peripheral == 12))
	{
		AFIO->MAPR &= ~(1<<Copy_u8Peripheral);
		return;
	}
	AFIO->MAPR &= (0b11<<Copy_u8Peripheral);

}
