//Author	:		Mohamed Gamal
//Date		:		22 August 2020
//Version	:		V01


#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

typedef struct{
	volatile u32 IMR,
	EMR,
	RTSR,
	FTSR,
	SWIER,
	PR;

}EXTI_t;

#define EXTI	((volatile EXTI_t *)(0x40010400))

#define 	EXTI_LINE0		0
#define 	EXTI_LINE1		1
#define 	EXTI_LINE2		2
#define 	EXTI_LINE3		3
#define 	EXTI_LINE4		4
#define 	EXTI_LINE5		5
#define 	EXTI_LINE6		6
#define 	EXTI_LINE7		7
#define 	EXTI_LINE8		8
#define 	EXTI_LINE9		9
#define 	EXTI_LINE10		10
#define 	EXTI_LINE11		11
#define 	EXTI_LINE12		12
#define 	EXTI_LINE13		13
#define 	EXTI_LINE14		14

#define 	RISING		0
#define 	Falling 	1
#define 	CHANGE	2

static void (* EXTI_CallBack[16])(void);


#endif
