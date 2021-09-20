//Author	:		Mohamed G. Eleish
//Version	:		V01
//Date		:		7\12\2020

#ifndef	TIMER2_PRIVATE_H
#define TIMER2_PRIVATE_H

typedef struct{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR1;
	volatile u32 CCMR2;
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 RESERVED;
	volatile u32 CCR1;
	volatile u32 CCR2;
	volatile u32 CCR3;
	volatile u32 CCR4;
	volatile u32 DCR;
	volatile u32 DMAR;
	

} TIMER2_t;

#define TIMER2		((volatile TIMER2_t *)(0x40000000))

void (*CaptureCompareCall[4])(void) = {0};
void (*OverCaptureCompareCall[4])(void) = {0};
void (*UpdateCall)(void) = 0;
void (*TriggerCall)(void) = 0;
#endif

