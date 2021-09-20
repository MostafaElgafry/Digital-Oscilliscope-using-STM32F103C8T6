/*
*Author     : Moustafa ElGafry
*Date       : 14 AUG 2020
*Version    : V01
*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"

void (*CallBack)(u8);

void MSPI1_voidInit(void)
{
	/* CPOL = 1/ CPHA = 1 / Prescaller = CLK/ 4 /SPI Enable /MSB First */
	MSPI1->CR1 = 0x034F;
}

void MSPI1_voidSendReceiveSynch(u8 Copy_u8DataToTransmit, u8 *Copy_DataToReceive)
{
	/* Clear For Slave Select Pin */
	MGPIO_voidSetPinValue(MSPI1_SLAVE_PIN,LOW);
	
	/* Send Data */
	MSPI1 -> DR = Copy_u8DataToTransmit;
	
	/* Wait Busy Flag to finish */
	while (GET_BIT(MSPI1 -> SR, 7) == 1);

 	/* Return to the received data */
	*Copy_DataToReceive = MSPI1 -> DR;
	
	/* Set Salve Select Pin */
	MGPIO_voidSetPinValue(MSPI1_SLAVE_PIN,HIGH);
}
void MSPI2_voidInit(void)
{
	/* CPOL = 1/ CPHA = 1 / Prescaller = CLK/ 2 /SPI Enable /MSB First */
	MSPI2->CR1 = 0x0347;
}

void MSPI2_voidSendReceiveSynch(u8 Copy_u8DataToTransmit, u8 *Copy_DataToReceive)
{
	/* Clear For Slave Select Pin */
	MGPIO_voidSetPinValue(MSPI2_SLAVE_PIN,LOW);

	/* Send Data */
	MSPI2 -> DR = Copy_u8DataToTransmit;

	/* Wait Busy Flag to finish */
	while (GET_BIT(MSPI2 -> SR, 7) == 1);

 	/* Return to the received data */
	*Copy_DataToReceive = MSPI2 -> DR;

	/* Set Salve Select Pin */
	MGPIO_voidSetPinValue(MSPI2_SLAVE_PIN,HIGH);
}


