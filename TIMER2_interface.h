//Author	:		Mohamed G. Eleish
//Version	:		V01
//Date		:		7\12\2020

#ifndef	TIMER2_INTERFACE_H
#define TIMER2_INTERFACE_H

#define TIMER2_UPDATE_INTERRUPT			0
#define TIMER2_CH1_CAPT					1
#define TIMER2_CH2_CAPT					2
#define TIMER2_CH3_CAPT					3
#define TIMER2_CH4_CAPT					4
#define TIMER2_TRIGGER_INTERRUPT		6
#define TIMER2_CH1_OVCAPT				9
#define TIMER2_CH2_OVCAPT				10
#define TIMER2_CH3_OVCAPT				11
#define TIMER2_CH4_OVCAPT				12

void MTIMER2_voidInit();
u16 MTIMER2_u16ReadCapture(u8 Copy_u8Channel);
void MTIMER2_voidSetCallBack(u8 Copy_u8Interrupt, void (*Copy_ptrCall)(void));
void MTIMER2_voidEnableInterrupt(u8 Copy_u8Interrupt);
void MTIMER2_voidDisableInterrupt(u8 Copy_u8Interrupt);
void MTIMER2_voidClearCounter(void);
void MTIMER2_voidClearFlags(void);

void SH(void (*func)(void));

#endif

