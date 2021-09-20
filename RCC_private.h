//AUTHOR	:Mohamed Gamal
//VERSION	:V01
//DATE		:8-August-2020

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/*Register definitions*/
typedef struct{
	volatile u32 CR,
		CFGR,
		CIR,
		APB2RSTR,
		APB1RSTR,
		AHBENR,
		APB2ENR,
		APB1ENR,
		BDCR,
		CSR;
}RCC_t;

#define RCC				((volatile RCC_t *)(0x40021000))
/*
#define RCC_CR          *((u32*)0x40021000)  //clock selection for processor
#define RCC_CFGR        *((u32*)0x40021004)  //clock selection for processor
#define RCC_CIR         *((u32*)0x40021008)
#define RCC_APB2RSTR    *((u32*)0x4002100C)
#define RCC_APB1RSTR    *((u32*)0x40021010)
#define RCC_AHBENR      *((u32*)0x40021014)   //E/D clocks for peripherals
#define RCC_APB2ENR     *((u32*)0x40021018)   //E/D clocks for peripherals
#define RCC_APB1ENR     *((u32*)0x4002101C)   //E/D clocks for peripherals
#define RCC_BDCR        *((u32*)0x40021020)
#define RCC_CSR         *((u32*)0x40021024)
*/
/*Clock Types*/
#define RCC_HSE_CRYSTAL     0
#define RCC_HSE_RC          1
#define RCC_HSI             2
#define RCC_PLL             3

/* PLL Options*/
#define RCC_PLL_IN_HSI_DIV_2	0
#define RCC_PLL_IN_HSE			1
#define RCC_TRUE					1
#define RCC_FALSE					0
#define RCC_CRYSTAL					1
#define RCC_RC 						0


/*AHB Prescalar Options*/
#define RCC_SYSCLK_DIV_1			0
#define RCC_SYSCLK_DIV_2			8
#define RCC_SYSCLK_DIV_4			9
#define RCC_SYSCLK_DIV_8			10
#define RCC_SYSCLK_DIV_16			11
#define RCC_SYSCLK_DIV_64			12
#define RCC_SYSCLK_DIV_128			13
#define RCC_SYSCLK_DIV_256			14
#define RCC_SYSCLK_DIV_512			15


/*APB1, APB2 Prescalar Options*/
#define RCC_HCLK_DIV_1				0
#define RCC_HCLK_DIV_2				4
#define RCC_HCLK_DIV_4				5
#define RCC_HCLK_DIV_8				6
#define RCC_HCLK_DIV_16				7


#define RCC_APB2_DIV_2				0
#define RCC_APB2_DIV_4				1
#define RCC_APB2_DIV_6				2
#define RCC_APB2_DIV_8				3
#endif // RCC_PRIVATE_H
