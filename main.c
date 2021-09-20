/*
 * main.c
 *
 *  Created on: Sep 27, 2020
 *      Author: G3fry
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <stdio.h>


#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "ADC_interface.h"
#include "AFIO_interface.h"
#include "Scope screen.h"
#include "TFT_interface.h"
#include "TIMER2_interface.h"
#include "FLOAT_ARRAY.h"

u16 TIME_DIVISION = 1;
f32 VOLTAGE_DIVISION = 2;
u8 FrequencyMeasured = 0;
u32 SignalFrequency = 0;


void Read_Record(s16 * Record);
void Process_Record(s16 *Record, f32 *Stats);
void Display_Record(s16 *Record, f32 *Stats);
void Peripheral_Enable(void);
void Pin_init(void);
void ExternalInterruptConfig(void);
void EnableInterrupts(void);
void Delay(u16);
void ADC_Call(u16);
void MeasureFrequency(void);
void Init_Osciliscope(void);
void Sleep_Oscilloscope(void);
void Start_Oscilloscope(void);
void HorizontalZoomIn(void);
void HorizontalZoomOut(void);
void VerticalZoomIn(void);
void VerticalZoomOut(void);
void Map (s16 *ValueArr,u8 n, s16 a1, s16 a2, s16 b1, s16 b2);
u16 average(volatile u16 *L,u8 N_Elements);


int main(void)
{
	/*Enable Peripherals from RCC*/
	Peripheral_Enable();

	/*PIN INIT*/
	Pin_init();

	/*STK INIT*/
	MSTK_voidInit();

	/*SPI INIT*/
	MSPI2_voidInit();

	/*TFT INIT*/
	HTFT_voidInit();

	/*Start Oscilloscope Screen*/
	Start_Oscilloscope();

	/*ACD INIT*/
	MADC_voidInit();

	/*Configure The External Interrupts*/
	ExternalInterruptConfig();

	/*Timer2 INIT*/
	MTIMER2_voidInit();

	/*Set Ch4 Capture Interrupt CallBack*/
	MTIMER2_voidSetCallBack(TIMER2_CH4_CAPT,MeasureFrequency);

	/*Full Re-map for Timer2 Pins*/
	MAFIO_voidRemap(AFIO_TIM2,AFIO_MODE3);

	/*NVIC INIT*/
	MNVIC_voidInit();

	/*Enable All Interrupts*/
	EnableInterrupts();

	/*Record Array to store the readings from the ADC*/
	s16 Record[159];

	/*Stats of the Signal*/
	f32 Stats[5];


	while (1)
	{
		//Read Record
		Read_Record(Record);

		//Process Record
		Process_Record(Record, Stats);

		//Display record
		Display_Record(Record, Stats);
	}
}

void Process_Record(s16 *Record, f32 *Stats)
{
	/*Initialize the Stats to be the first element of the Record*/
	Stats[0] = Stats[1] = Record[0];
	for (u8 i= 0; i<158; i++)
	{
		/*Get the Max and Min Valuse from the record*/
		if (Stats[0] < Record[i])
			Stats[0] = Record[i];
		if (Stats[1] > Record[i])
			Stats[1] = Record[i];
		/*Apply the Voltage division*/
		Record[i] *= VOLTAGE_DIVISION;
	}
	/*Measure the frequency*/
	/*Timeout is 65535*/
	u16 i = 0xFFFF;
	/*Clear Interrupt flags of Timer2*/
	MTIMER2_voidClearFlags();
	/*Enable Timer2 Capture interrupt*/
	MTIMER2_voidEnableInterrupt(TIMER2_CH4_CAPT);

	/*wait till the frequency is measured*/
	while(!FrequencyMeasured && --i);
	/*Clear Measure flag*/
	FrequencyMeasured = 0;
	/*Disable Timer2 Capture Flag*/
	MTIMER2_voidDisableInterrupt(TIMER2_CH4_CAPT);

	/*If Timeout, frequency is zero*/
	if (i == 0)
		SignalFrequency = 0;
	/*Store the frequency*/
	Stats[2] = SignalFrequency;

}

void Read_Record(s16 * Record)
{
	/*Limit the Timer Division between 1 and 10*/
	if (TIME_DIVISION <= 0 )
		TIME_DIVISION = 1;
	if (TIME_DIVISION >10)
		TIME_DIVISION = 10;

	/*Read the Record if the Division is 1*/
	if (TIME_DIVISION == 1)
	{
		for (u8 i = 0; i < 158;i++)
		{
			Record[i] = MADC_u16GetData(0);
		}
	}
	/*else read multiple records and get the average*/
	else if (TIME_DIVISION > 1)
	{
		for(u8 i = 0; i < 158 ; i++)
		{
			u16 Temp=0;
			for (u8 j = 0; j<TIME_DIVISION;j++)
			{
				Temp+= MADC_u16GetData(0);
			}
			Record[i] = Temp/TIME_DIVISION;
		}
	}
}

void Display_Record(s16 *Record, f32 *Stats)
{
	/*LocalPixels to store the last record*/
	static s16 LocalPixels[159];

	for (u8 i = 1; i<159; i++)
	{
		/*Map the Readings to pixel positions on the screen*/
		Record[i] *= 120.0/4096;
		/*Redraw the Oscilloscope screen where the last record was drawn*/
		HTFT_DrawPixel(i,60-LocalPixels[i], ScopeScreen[i-1][LocalPixels[i]-1]);
		/*Draw the new record*/
		HTFT_DrawPixel(i,60-Record[i],RED);
		/*Store the current record in the old record array*/
		LocalPixels[i] = Record[i];
	}

	/*Convert Stats valuse to Chars to display on the screen*/
	/*The frequency first*/
	char F[5];
	sprintf(F,"%u",(u16)(Stats[2]));

	HTFT_voidFill(102,121,145,126,BLACK);
	HTFT_DrawText(F,108,120,YELLOW);

	HTFT_DrawText("HZ",140,120,WHITE);

	/*Then the P-P voltage*/
	f32 Local_f32MaxSample =(Stats[0])*3.3/4096.0;
	f32 Local_f32MinSample =(Stats[1])*3.3/4096.0;
	char VPP[10];
	ftoa(Local_f32MaxSample-Local_f32MinSample,VPP,2);

	/*Put a zero at first if the first element is . */
	if(VPP[0] == '.')
	{
		VPP[4]=VPP[3];
		VPP[3]=VPP[2];
		VPP[2]=VPP[1];
		VPP[1]=VPP[0];
		VPP[0]='0';
	}

	HTFT_voidFill(37,121,65,126,BLACK);
	HTFT_DrawText(VPP,40,120,YELLOW);
	HTFT_DrawText("V",70,120,WHITE);
	HTFT_DrawText(VPP,40,120,YELLOW);
}

void Peripheral_Enable(void)
{
	/*Clock Initialization*/
	RCC_voidClockInit();
	/*PORTA, PORTB Enable*/
	RCC_voidEnableClock(RCC_APB2,RCC_PORTB);
	RCC_voidEnableClock(RCC_APB2,RCC_PORTA);
	/*SPI2 Enable*/
	RCC_voidEnableClock(RCC_APB1,RCC_SPI2); //SPI ENABLE CLOCK
	/*Timer2 Enable*/
	RCC_voidEnableClock(RCC_APB1,RCC_TIM2);
	/*Alternative Function Enable*/
	RCC_voidEnableClock(RCC_APB2,RCC_AFIO);
	/*ADC1 Enable*/
	RCC_voidEnableClock(RCC_APB2,RCC_ADC1);
}

void Pin_init(void)
{
	/*TFT Screen Pins*/
	MGPIO_voidSetPinDirection(GPIOB,PIN6,OUTPUT_SPEED_2MHZ_PP); //A0
	MGPIO_voidSetPinDirection(GPIOB,PIN7,OUTPUT_SPEED_2MHZ_PP); //RST
	MGPIO_voidSetPinDirection(GPIOB,PIN13,OUTPUT_SPEED_50MHZ_AFPP); //CLK
	MGPIO_voidSetPinDirection(GPIOB,PIN15,OUTPUT_SPEED_50MHZ_AFPP);//MOSI

	/*External Push Buttons Pins*/
	MGPIO_voidSetPinDirection(GPIOB,0,INPUT_PULLUP_PULLDOWN);
	MGPIO_voidSetPinDirection(GPIOB,1,INPUT_PULLUP_PULLDOWN);
	MGPIO_voidSetPinDirection(GPIOB,3,INPUT_PULLUP_PULLDOWN);
	MGPIO_voidSetPinDirection(GPIOB,5,INPUT_PULLUP_PULLDOWN);

	MGPIO_voidSetPinValue(GPIOB,0,HIGH);
	MGPIO_voidSetPinValue(GPIOB,1,HIGH);
	MGPIO_voidSetPinValue(GPIOB,4,HIGH);
	MGPIO_voidSetPinValue(GPIOB,5,HIGH);
}

void ExternalInterruptConfig(void)
{
	/*Re-map of EXTIs to PORTB pins*/
	MAFIO_voidSetEXTIConfiguration(LINE0,AFIO_PORTB);
	MAFIO_voidSetEXTIConfiguration(LINE1,AFIO_PORTB);
	MAFIO_voidSetEXTIConfiguration(LINE4,AFIO_PORTB);
	MAFIO_voidSetEXTIConfiguration(LINE5,AFIO_PORTB);


	/*Set CallBacks for every interrupt*/
	MEXTI_voidSetCallBack(LINE0,HorizontalZoomIn);
	MEXTI_voidSetCallBack(LINE1,HorizontalZoomOut);
	MEXTI_voidSetCallBack(LINE4,VerticalZoomIn);
	MEXTI_voidSetCallBack(LINE5,VerticalZoomOut);

	/*Interrupt on Falling Edge*/
	MEXTI_voidSetSignalLatch(LINE0,FALLING_EDGE);
	MEXTI_voidSetSignalLatch(LINE1,FALLING_EDGE);
	MEXTI_voidSetSignalLatch(LINE4,FALLING_EDGE);
	MEXTI_voidSetSignalLatch(LINE5,FALLING_EDGE);
}

void EnableInterrupts(void)
{
	/*Set the Priority for the External Interrupts*/
	MNVIC_voidSetPriority(NVIC_EXTI0,0,0,0);
	MNVIC_voidSetPriority(NVIC_EXTI1,0,1,0);
	MNVIC_voidSetPriority(NVIC_EXTI4,0,2,0);
	MNVIC_voidSetPriority(NVIC_EXTI9_5,0,3,0);

	/*Set Priority for TIMER2 Interrupt*/
	MNVIC_voidSetPriority(NVIC_TIM2,1,0,0);

	/*Enable All Interrupts*/
	MNVIC_voidEnableInterrupt(NVIC_EXTI0);
	MNVIC_voidEnableInterrupt(NVIC_EXTI1);
	MNVIC_voidEnableInterrupt(NVIC_EXTI4);
	MNVIC_voidEnableInterrupt(NVIC_EXTI9_5);

	MNVIC_voidEnableInterrupt(NVIC_TIM2);

	/*wait*/
	MSTK_voidSetBusyWait(10000);

}

void MeasureFrequency(void)
{
	/*Check for first edge*/
	static u8 FirstEdge = 0;
	if (FirstEdge == 0)
	{
		/*If yes, clear the counter*/
		FirstEdge = 1;
		MTIMER2_voidClearCounter();
	}
	else
	{
		/*If no, Calculate the frequency then clear the counter and set the Measure flag*/
		SignalFrequency = 48000000/MTIMER2_u16ReadCapture(TIMER2_CH4_CAPT);
		MTIMER2_voidClearCounter();
		FirstEdge = 0;
		FrequencyMeasured = 1;
	}

}
void Init_Osciliscope(void)
{
	/*TFT INIT*/
	HTFT_voidInit();
	/*Fill Screen with white color*/
	HTFT_voidFillScreen(BLACK);

	HTFT_SetRotation(Horizontal);
	HTFT_DrawText("oscilloscope",45,15,WHITE);

	HTFT_voidFill(52,33,108,58,WHITE);
	HTFT_DrawText("Start",67,42,BLACK );

	HTFT_voidFill(52,68,108,93,WHITE);
	HTFT_DrawText("Sleep",68,77,BLACK );

	HTFT_DrawRectangle(50,31,110,60,BLUE);
}
void Sleep_Oscilloscope(void)
{
	HTFT_voidInit();
	HTFT_voidFillScreen(BLACK);
	HTFT_SetRotation(Horizontal);
	HTFT_DrawText("Sleeping",57,65,WHITE);
	HTFT_DrawText("Z",108,60,WHITE);
	HTFT_DrawText("Z",115,55,WHITE);
	HTFT_DrawText("Z",122,50,WHITE);
}

void Start_Oscilloscope(void)
{


	/*Fill Screen with white color*/
	HTFT_voidFillScreen(BLACK);

	HTFT_SetRotation(Horizontal);

	/*Blue Border*/
	HTFT_DrawRectangle(0,0,159,127,BLUE);

	/*   Horizontal lines  */
	HTFT_DrawLine(0,12,159,12,LIGHTGREY );
	HTFT_DrawLine(0,24,159,24,LIGHTGREY );
	HTFT_DrawLine(0,36,159,36,LIGHTGREY );
	HTFT_DrawLine(0,48,159,48,LIGHTGREY );

	HTFT_DrawLine(0,60,159,60,BLUE);

	HTFT_DrawLine(0,72,159,72,LIGHTGREY);
	HTFT_DrawLine(0,84,159,84,LIGHTGREY);
	HTFT_DrawLine(0,96,159,96,LIGHTGREY);
	HTFT_DrawLine(0,108,159,108,LIGHTGREY);

	HTFT_voidFill(0,120,159,128,BLUE);
	/*   VPP   */
	HTFT_DrawText("Vpp",15,120,WHITE);

	HTFT_voidFill(37,121,65,126,BLACK);
	HTFT_DrawText("0.00",40,120,YELLOW);

	HTFT_DrawText("V",70,120,WHITE);
	/*  Frequency  */
	HTFT_DrawText("F",90,120,WHITE);

	HTFT_voidFill(102,121,135,126,BLACK);
	HTFT_DrawText("0.00",108,120,YELLOW);

	HTFT_DrawText("HZ",140,120,WHITE);

	/*   Vertical lines  */
	HTFT_DrawLine(20,0,20,120,LIGHTGREY);
	HTFT_DrawLine(40,0,40,120,LIGHTGREY);
	HTFT_DrawLine(60,0,60,120,LIGHTGREY);

	HTFT_DrawLine(80,0,80,120,BLUE);

	HTFT_DrawLine(100,0,100,120,LIGHTGREY);
	HTFT_DrawLine(120,0,120,120,LIGHTGREY);
	HTFT_DrawLine(140,0,140,120,LIGHTGREY);
}

void HorizontalZoomIn(void)
{
	/*Decrease the Time division*/
	while(!MGPIO_u8GetPinValue(GPIOB,0));
	TIME_DIVISION -=1;
	if (!TIME_DIVISION)
		TIME_DIVISION =1;
}

void HorizontalZoomOut(void)
{
	/*Increase the Time Division*/
	while(!MGPIO_u8GetPinValue(GPIOB,1));
	TIME_DIVISION +=1;
	if (TIME_DIVISION > 10)
		TIME_DIVISION =10;

}

void VerticalZoomIn(void)
{
	/*Decrease The Voltage division*/
	while(!MGPIO_u8GetPinValue(GPIOB,5));
	VOLTAGE_DIVISION /=2;
	if(!VOLTAGE_DIVISION)
		VOLTAGE_DIVISION = 1;
}

void VerticalZoomOut(void)
{
	/*Increase the voltage division*/
	while(!MGPIO_u8GetPinValue(GPIOB,4));
	VOLTAGE_DIVISION *=2;
	if(VOLTAGE_DIVISION >16)
		VOLTAGE_DIVISION = 16;
}
/*
u16 average(volatile u16 *L,u8 N_Elements)
{
	u32 Sum = 0;
	for (u8 i = 0; i<N_Elements;i++)
		Sum+= L[i];
	return Sum/N_Elements;
}
void Map (s16 *ValueArr,u8 n, s16 a1, s16 a2, s16 b1, s16 b2)
{
	for (u8 i=0; i<n; i++)
		ValueArr[i] = (ValueArr[i]-a1)*((b2-b1)/(a2-a1))+b1;
}
*/
