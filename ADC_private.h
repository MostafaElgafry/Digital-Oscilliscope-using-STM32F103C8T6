/*****************************************/
/* Author  :  Ahmed Fawzy                */
/* Version :  V01                        */
/* Date    : 26 october 2020             */
/*****************************************/
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


/* Analog watchdog enable on regular channels */
#define 	ADC_REGULAR_WATCHDOG_DISABLE		0
#define 	ADC_REGULAR_WATCHDOG_ENABLE			1

/* Analog watchdog enable on injected channels */
#define 	ADC_INJECTED_WATCHDOG_DISABLE		0
#define 	ADC_INJECTED_WATCHDOG_ENABLE		1

/* Analog watchdog interrupt enable */
#define		ADC_WATCHDOG_INTERRUPT_DISABLE		0
#define     ADC_WATCHDOG_INTERRUPT_ENABLE		1
/* Interrupt enable for EOC */
#define 	ADC_END_OF_CONV_INTERRUPT_ENABLE	1
#define 	ADC_END_OF_CONV_INTERRUPT_DISABLE	0
/* Data alignment */
#define		ADC_DATA_ALIGNMENT_RIGHT			0
#define		ADC_DATA_ALIGNMENT_FALSE			1
/* Direct memory access mode */
#define		ADC_DMA_MODE_ENABLE					1
#define		ADC_DMA_MODE_DISABLE				0
/* A/D Calibration */
#define		ADC_CAL_ENABLE						1
#define		ADC_CAL_DISABLE						0
/* Reset calibration */
#define		ADC_RESET_CALIBRATION_ENABLE		1
#define		ADC_RESET_CALIBRATION_DISABLE		0
/* Continuous conversion */
#define		ADC_CONT_CON_ENABLE					1
#define		ADC_CONT_CON_DISABLE				0
/* A/D converter ON / OFF */
#define		ADC_ON								1
#define		ADC_OFF								0
/* A/D converter ON / OFF */
#define		ADC_SAMPLE_1_5_CYCLES				000
#define		ADC_SAMPLE_7_5_CYCLES				001
#define		ADC_SAMPLE_13_5_CYCLES				010
#define		ADC_SAMPLE_28_5_CYCLES				011
#define		ADC_SAMPLE_41_5_CYCLES				100
#define		ADC_SAMPLE_55_5_CYCLES				101
#define		ADC_SAMPLE_71_5_CYCLES				110
#define		ADC_SAMPLE_239_5_CYCLES				111




static void (*ADC_pCallBack )(u16) = 0 ;



/* Channel registers */
typedef struct
{
	volatile u32 SR     ;
	volatile u32 CR1    ;
	volatile u32 CR2    ;
	volatile u32 SMPRA1 ;
	volatile u32 SMPRA2 ;
	volatile u32 JOFR[4];
	volatile u32 HTR    ;
	volatile u32 LTR	;
	volatile u32 SQR[3]	;
	volatile u32 JSQR	;
	volatile u32 JDR[4]	;
	volatile u32 DR		;
	
}ADC_t;

/* Register definition */
#define ADC	((volatile ADC_t*)0x40012400)


/* End OF conversion Interrupt  */
#define  	ADC_EOC					0x00000002

#endif
