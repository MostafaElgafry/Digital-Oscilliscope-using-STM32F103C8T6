/*****************************************/
/* Author  :  Ahmed Fawzy                */
/* Version :  V01                        */
/* Date    : 26 october 2020             */
/*****************************************/
#ifndef ADC_CONFIGURE_H_
#define ADC_CONFIGURE_H_

/* Analog watchdog enable on regular channels
	Options:	ADC_REGULAR_WATCHDOG_DISABLE
				ADC_REGULAR_WATCHDOG_ENABLE
 */
#define 	ADC_REGULAR_WATCHDOG				ADC_REGULAR_WATCHDOG_DISABLE
/* Analog watchdog enable on injected channels 
	Options:	ADC_INJECTED_WATCHDOG_DISABLE
				ADC_INJECTED_WATCHDOG_ENABLE
*/
#define 	ADC_INJECTED_WATCHDOG				ADC_INJECTED_WATCHDOG_DISABLE
/* Analog watchdog interrupt enable 
	Options:	ADC_WATCHDOG_INTERRUPT_DISABLE
				ADC_WATCHDOG_INTERRUPT_ENABLE
*/	
#define 	ADC_WATCHDOG_INTERRUPT 				ADC_WATCHDOG_INTERRUPT_DISABLE
/* Interrupt enable for EOC 
	Options:	ADC_END_OF_CONV_INTERRUPT_ENABLE
				ADC_END_OF_CONV_INTERRUPT_DISABLE
*/
#define 	ADC_END_OF_CONV_INTERRUPT			ADC_END_OF_CONV_INTERRUPT_DISABLE

/* Data alignment
	Options:	ADC_DATA_ALIGNMENT_RIGHT
				ADC_DATA_ALIGNMENT_FALSE
 */
#define 	ADC_DATA_ALIGNMENT					ADC_DATA_ALIGNMENT_RIGHT	
/* Direct memory access mode
	Options:	ADC_DMA_MODE_ENABLE
				ADC_DMA_MODE_DISABLE
*/
#define		ADC_DMA_MODE						ADC_DMA_MODE_DISABLE
/* A/D Calibration 
	Options:	ADC_CAL_ENABLE
				ADC_CAL_DISABLE
*/
#define		ADC_CAL								ADC_CAL_ENABLE
					
/* Reset calibration 
	Options:	ADC_RESET_CALIBRATION_ENABLE
				ADC_RESET_CALIBRATION_DISABLE
*/
#define 	ADC_RESET_CALIBRATION				ADC_RESET_CALIBRATION_DISABLE
/* Continuous conversion
	Options:	ADC_CONT_CON_ENABLE
				ADC_CONT_CON_DISABLE
 */
#define 	ADC_CONT_CON						ADC_CONT_CON_DISABLE
/* A/D converter ON / OFF 
	Options:	ADC_ON
				ADC_OFF
*/
#define 	ADC_POWER							ADC_ON	
/* A/D converter ON / OFF 
	Options:	ADC_SAMPLE_1_5_CYCLES
				ADC_SAMPLE_7_5_CYCLES
				ADC_SAMPLE_13_5_CYCLES
				ADC_SAMPLE_28_5_CYCLES
				ADC_SAMPLE_41_5_CYCLES
				ADC_SAMPLE_55_5_CYCLES
				ADC_SAMPLE_71_5_CYCLES
				ADC_SAMPLE_239_5_CYCLES
*/
#define 	ADC_SAMPLE							ADC_SAMPLE_1_5_CYCLES

#endif
