//Author	:		Mohamed Gamal
//Date		:		22 August 2020
//Version	:		V01


#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H

#define AFIO_MODE0			0
#define AFIO_MODE1			1
#define AFIO_MODE2			2
#define AFIO_MODE3			3
#define AFIO_MODE4			4


#define 	LINE0		0
#define 	LINE1		1
#define 	LINE2		2
#define 	LINE3		3
#define 	LINE4		4
#define 	LINE5		5
#define 	LINE6		6
#define 	LINE7		7
#define 	LINE8		8
#define 	LINE9		9
#define 	LINE10		10
#define 	LINE11		11
#define 	LINE12		12
#define 	LINE13		13
#define 	LINE14		14
#define 	LINE15		15

#define 	AFIO_PORTA		0
#define		AFIO_PORTB		1
#define 	AFIO_PORTC		2
#define 	AFIO_PORTD		3

#define AFIO_SP1			0
#define AFIO_I2C1			1
#define AFIO_USART1			2
#define AFIO_USART2			3
#define AFIO_USART3			4
#define AFIO_TIM1			6
#define AFIO_TIM2			8
#define AFIO_TIM3			10
#define AFIO_TIM4			12
#define AFIO_CAN			13
#define AFIO_PD01			15
#define AFIO_TIM5CH4		16
#define AFIO_ADC1ETRGINJ	17
#define AFIO_ADC1ETRGREG	18
#define AFIO_ADC2ETRGINJ	19
#define AFIO_ADC2ETRGREG	20
#define AFIO_SWJCFG			24

void MAFIO_voidSetEXTIConfiguration(u8 Copy_u8Line, u8 Copy_u8PortMap);
void MAFIO_voidRemap(u8 Copy_u8Peripheral, u8 Copy_u8Mode);
void MAFIO_voidUnMap(u8 Copy_u8Peripheral);
#endif
