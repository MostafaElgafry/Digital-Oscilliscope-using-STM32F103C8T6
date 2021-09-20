//Author	:		Mohamed Gamal
//Date		:		19-August-2020
//Version	:		V01

#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

// 0xE000E100

//ISER : Interrupt Set Enable Register

#define NVIC_ISER0		(*(volatile u32*)(0xE000E100))
#define NVIC_ISER1		(*(volatile u32*)(0xE000E104))

// ICER	:	Interrupt Clear Enable Register
#define NVIC_ICER0		(*(volatile u32*)(0xE000E180))
#define NVIC_ICER1		(*(volatile u32*)(0xE000E184))

//ISPR	:	Interrupt Set Pending Register
#define NVIC_ISPR0		(*(volatile u32*)(0xE000E200))
#define NVIC_ISPR1		(*(volatile u32*)(0xE000E204))

//ICPR	:	Interrupt Clear Pending Register
#define NVIC_ICPR0		(*(volatile u32*)(0xE000E280))
#define NVIC_ICPR1		(*(volatile u32*)(0xE000E284))

//IABR	:	Interrupt Active Bit Register
#define NVIC_IABR0		(*(volatile u32*)(0xE000E300))
#define NVIC_IABR1		(*(volatile u32*)(0xE000E304))

#define NVIC_IPR		((volatile u8*)(0xE000E400))

#define		MNVIC_16_GROUP_1_SUB 			0x05FA0300	//4 bits for group priority, 0 for sub group
#define		MNVIC_8_GROUP_2_SUB 			0x05FA0400	//3 bits for group priority, 1 for sub group
#define		MNVIC_4_GROUP_4_SUB 			0x05FA0500	//2 bits for group priority, 2 for sub group
#define		MNVIC_2_GROUP_8_SUB 			0x05FA0600	//1 bits for group priority, 3 for sub group
#define		MNVIC_1_GROUP_16_SUB 			0x05FA0700	//0 bits for group priority, 4 for sub group

#endif
