//AUTHOR	:Mohamed Gamal
//VERSION	:V01
//DATE		:8-August-2020

/*Library Includes*/
#include        "STD_TYPES.h"
#include        "BIT_MATH.h"

/*Driver Files Includes*/
#include        "RCC_interface.h"
#include        "RCC_private.h"
#include        "RCC_config.h"

void RCC_voidClockInit(void){
    #if     RCC_CLOCK_TYPE  == RCC_HSE_CRYSTAL
		while(!GET_BIT(RCC->CR, 17));
        RCC->CR   = 0x00010000;		// 1<<HSEON = 0x00010000
		RCC->CFGR = 0x00000001;		// (01)<<SW0 (select High speed external clock) = 1
    #elif   RCC_CLOCK_TYPE  ==  RCC_HSE_RC
		while(!GET_BIT(RCC->CR, 17));
        RCC->CR 	 = 0x00050000;		// (1<<HSEBYP)|(1<<HSEON) = 0x00050000
		RCC->CFGR = 0x00000001;		// (01)<<SW (select High speed external clock) = 1
    #elif   RCC_CLOCK_TYPE  ==  RCC_HSI
		while(!GET_BIT(RCC->CR, 1));
        RCC->CR   = 0x00000081;		// (16<<HSITRIM0)|(HSION) = 0x00000081
		RCC->CFGR = 0x00000000;		// (00<<SW0)	= 0
    #elif   RCC_CLOCK_TYPE  ==  RCC_PLL
		# if RCC_PLL_MUL_VALUE <2 || RCC_PLL_MUL_VALUE >16 
			#error "Wrong Multiplier value"
		#endif
		
		#if RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
			while(!GET_BIT(RCC->CR, 1));
			RCC->CFGR = 2 | ((RCC_PLL_MUL_VALUE-2) << 18);	//SW = 10
			while(!GET_BIT(RCC->CR, 25));
			RCC->CR = 0x01000080;//(1<<HSION)|(16<<HSITRIM0)|(1<<PLLON) = 0x01000081
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE && RCC_PLL_HSE_DIV_2 == RCC_TRUE
			while (!GET_BIT(RCC->CR, 17));
			RCC->CFGR = 0x00030002|((RCC_PLL_MUL_VALUE-2) << 18); //(2<<SW0)|(1<<PLLSRC)|(1<<PLLXTPRE)=0x00030002
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE && RCC_PLL_HSE_DIV_2 == RCC_FALSE
			while (!GET_BIT(RCC->CR, 17));
			RCC->CFGR &= ~(0b11);
			RCC->CFGR |= 1;
			CLR_BIT(RCC->CR,24);
			RCC->CFGR = 0x00010002|((RCC_PLL_MUL_VALUE-2) << 18); //(2<<SW0)|(1<<PLLSRC) = 0x00010002
		#else 
			#error ("Wrong PLL options!")
		#endif
		
		#if	RCC_PLL_INPUT != RCC_PLL_IN_HSI_DIV_2
			SET_BIT(RCC->CR,24);
			while(!GET_BIT(RCC->CR,25));
			#if RCC_PLL_HSE_TYPE == RCC_CRYSTAL
				RCC->CR = 0x01010000;			//(1<<HSEON)|(1<<PLLON) = 0x01010000
			#elif RCC_PLL_HSE_TYPE == RCC_RC
				RCC->CR = 0x01050000;			//(1<<HSEON)|(1<<HSEBYP)|(1<<PLLON) = 0x01050000
			//#else
				//#error "Wrong PLL options!"
			#endif
		#endif
		
    #else
        #error("Wrong Clock Type!")

    #endif // RCC_CLOCK_TYPE


	RCC->CFGR |= (RCC_AHB_PRESCALAR<<4) | (RCC_APB1_PRESCALAR<<8) | (RCC_APB2_PRESCALAR<<11)
				| (RCC_ADC_PRESCALAR<<14);
	RCC->CFGR &= ~(0b1111<<18);
	RCC->CFGR |= 4<<18;
}
void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId){

    if (Copy_u8PerId >31){
        //return error
    }
    switch (Copy_u8BusId){
        case RCC_AHB    :   SET_BIT(RCC->AHBENR  , Copy_u8PerId); break;
        case RCC_APB1   :   SET_BIT(RCC->APB1ENR , Copy_u8PerId); break;
        case RCC_APB2   :   SET_BIT(RCC->APB2ENR , Copy_u8PerId); break;
        default         :/*return error*/   break;
    }
}

void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId){

    if (Copy_u8PerId >31){
        return;
    }
    switch (Copy_u8BusId){
        case RCC_AHB    :   CLR_BIT(RCC->AHBENR  , Copy_u8PerId); break;
        case RCC_APB1   :   CLR_BIT(RCC->APB1ENR , Copy_u8PerId); break;
        case RCC_APB2   :   CLR_BIT(RCC->APB2ENR , Copy_u8PerId); break;
        default         :/*return error*/   break;
    }
}

void RCC_voidResetClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if (Copy_u8PerId >31)
		return;
	switch (Copy_u8BusId){
	        case RCC_APB1   :   RCC->APB1RSTR = 1<<Copy_u8PerId; break;
	        case RCC_APB2   :   RCC->APB2RSTR = 1<<Copy_u8PerId; break;
	        default         :/*return error*/   break;
	    }
}
