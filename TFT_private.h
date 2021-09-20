/*
*Author     : Moustafa ElGafry
*Date       : 27 SEP 2020
*Version    : V01
*/
#ifndef TFT_PRIVATE_H
#define TFT_PRIVATE_H



/* Private defines */
#define		 X_ADDRESS			0x2A
#define 	 Y_ADDRESS			0x2B
#define 	 WRITE_COMMAND		0x2C
#define      SLEEP_OUT			0x11
#define      PIXEL_FORMAT		0x3A
#define      DISPLAY_ON			0x29
#define 	 DISPLAY_OFF		0x28
#define 	 RESET				0x01
#define 	 MADCTL			    0x36

#define 	 MADCTL_MY  0x80  //row address order
#define		 MADCTL_MX  0x40  //column address order
#define		 MADCTL_MV  0x20  //row and column exchange

static void voidWriteCommand(u8 Copy_u8Command);
static void voidWriteData(u8 Copy_u8Data);
static void SetCursorPosition(u8 Copy_u8X1, u8 Copy_u8Y1, u8 Copy_u8X2, u8 Copy_u8Y2);

#endif
