/* 	**************************************/
/* Author  :  Ahmed Fawzy                */
/* Version :  V01                        */
/* Date    : 26 october   2020           */
/*****************************************/
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/* Configuration of the adc */
void  MADC_voidInit(void);

/* Get data after conversion */
u16	MADC_u16GetData(u8 Copy_u8Channel);

/* Collect the function will process in the interrupt */
void  MADC_voidCallBack(void(*ptr)(u16));



#endif
