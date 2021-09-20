//AUTHOR	:Mohamed Gamal
//VERSION	:V01
//DATE		:8-August-2020

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/*options:  RCC_HSE_CRYSTAL
            RCC_HSE_RC
            RCC_HSI
            RCC_PLL             */
#define RCC_CLOCK_TYPE    RCC_PLL

/* Options:		RCC_PLL_IN_HSI_DIV_2
				RCC_PLL_IN_HSE			*/

#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_INPUT	RCC_PLL_IN_HSE

/*Options1:	RCC_TRUE
			RCC_FALSE
Options:	RCC_CRYSTAL
			RCC_RC 					*/
#if RCC_PLL_INPUT == RCC_PLL_IN_HSE
	#define RCC_PLL_HSE_DIV_2	RCC_FALSE
	#define RCC_PLL_HSE_TYPE	RCC_CRYSTAL
#endif

/*Options:	2-16*/
#define RCC_PLL_MUL_VALUE		6
#endif

/*Options for AHB Prescalar:
 *RCC_SYSCLK_DIV_1
 *RCC_SYSCLK_DIV_2
 *RCC_SYSCLK_DIV_4
 *RCC_SYSCLK_DIV_8
 *RCC_SYSCLK_DIV_16
 *RCC_SYSCLK_DIV_64
 *RCC_SYSCLK_DIV_128
 *RCC_SYSCLK_DIV_256
 *RCC_SYSCLK_DIV_512 */
#define RCC_AHB_PRESCALAR		RCC_SYSCLK_DIV_1

/*Options for APB1, APB2 Prescalars:
 *RCC_HCLK_DIV_1
 *RCC_HCLK_DIV_2
 *RCC_HCLK_DIV_4
 *RCC_HCLK_DIV_8
 *RCC_HCLK_DIV_16*/
#define RCC_APB1_PRESCALAR		RCC_HCLK_DIV_2
#define RCC_APB2_PRESCALAR		RCC_HCLK_DIV_1

/*Options for ADC Prescalar:
 * RCC_APB2_DIV_2
 * RCC_APB2_DIV_4
 * RCC_APB2_DIV_6
 * RCC_APB2_DIV_8*/
#define RCC_ADC_PRESCALAR		RCC_APB2_DIV_6



#endif // RCC_CONFIG_H
