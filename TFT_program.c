/*
*Author     : Moustafa ElGafry
*Date       : 27 SEP 2020
*Version    : V01
*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SPI_interface.h"
#include "STK_interface.h"

#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"
#include "Font.h"

static void voidWriteCommand(u8 Copy_u8Command)
{
	u8 Local_u8Temp;
	/* Set A0 Pin to low */
	MGPIO_voidSetPinValue(TFT_A0_PIN,LOW);

	/* Send Command over SPI*/
	MSPI2_voidSendReceiveSynch(Copy_u8Command, &Local_u8Temp);

}
static void voidWriteData(u8 Copy_u8Data)
{
	u8 Local_u8Temp;
	/* Set A0 Pin to High */
	MGPIO_voidSetPinValue(TFT_A0_PIN,HIGH);
	/* Send Data over SPI*/
	MSPI2_voidSendReceiveSynch(Copy_u8Data, &Local_u8Temp);
}
void HTFT_voidInit(void)
{
	/*Reset Pulse*/
	MGPIO_voidSetPinValue(TFT_RST_PIN,HIGH);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RST_PIN,LOW);
	MSTK_voidSetBusyWait(1);
	MGPIO_voidSetPinValue(TFT_RST_PIN,HIGH);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RST_PIN,LOW);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RST_PIN,HIGH);
	MSTK_voidSetBusyWait(120000);

	/*Sleep Out Command*/
	voidWriteCommand(SLEEP_OUT);
	
	/*Wait 150 ms*/
	MSTK_voidSetBusyWait(150000);
	
	/*Color Mode Command*/
	voidWriteCommand(PIXEL_FORMAT);
	voidWriteData(0x05);
	
	/*Display ON Command*/
	voidWriteCommand(DISPLAY_ON);
	
	
}
void HTFT_DisplayOff(void)
{
	voidWriteCommand(DISPLAY_OFF);
}
void HTFT_voidDisplayImage(const u16 * Copy_p8Image)
{	
	u16 Local_u8Counter;
	u8 Data;
	
	/*Set X address*/
	voidWriteCommand(X_ADDRESS);
	//MSB First
	//Start X
	voidWriteData(0);
	voidWriteData(0);
	//End X
	voidWriteData(0);
	voidWriteData(127);
	
	/*Set Y address*/
	voidWriteCommand(Y_ADDRESS);
	//MSB First
	//Start Y
	voidWriteData(0);
	voidWriteData(0);
	//End Y
	voidWriteData(0);
	voidWriteData(159);
	
	/*RAM write*/
	voidWriteCommand(WRITE_COMMAND);
	
	for(Local_u8Counter = 0; Local_u8Counter < 20480;Local_u8Counter++)
	{
		Data = Copy_p8Image[Local_u8Counter] >> 8;

		/* Write the high byte */
		voidWriteData(Data);
		/* Write the low byte */
		Data = Copy_p8Image[Local_u8Counter] & 0x00ff;
		voidWriteData(Data);
	}
	
	
}
void HTFT_voidFill( u8 Copy_u8X1,u8 Copy_u8Y1,u8 Copy_u8X2,u16 Copy_u8Y2, u16 Copy_u16Color)
{
	u16 Local_u8Counter;
	u16 size = (Copy_u8X2-Copy_u8X1 + 1) * (Copy_u8Y2-Copy_u8Y1 + 1);
	SetCursorPosition(Copy_u8X1,Copy_u8Y1,Copy_u8X2,Copy_u8Y2);
	voidWriteCommand(WRITE_COMMAND);
	for(Local_u8Counter = 0; Local_u8Counter < size;Local_u8Counter++)
	{
		/* Write the high byte */
		voidWriteData(Copy_u16Color >> 8);

		/* Write the low byte */
		voidWriteData(Copy_u16Color & 0x00ff);
	}
}

void HTFT_voidFillScreen( u16 Copy_u8Color)
{	
	u16 Local_u8Counter;
	u8 Data;
	
	/*Set X address*/
	voidWriteCommand(X_ADDRESS);
	//MSB First
	//Start X
	voidWriteData(0);
	voidWriteData(0);
	//End X
	voidWriteData(0);
	voidWriteData(127);
	
	/*Set Y address*/
	voidWriteCommand(Y_ADDRESS);
	//MSB First
	//Start Y
	voidWriteData(0);
	voidWriteData(0);
	//End Y
	voidWriteData(0);
	voidWriteData(159);
	
	/*RAM write*/
	voidWriteCommand(WRITE_COMMAND);
	
	for(Local_u8Counter = 0; Local_u8Counter < 20480;Local_u8Counter++)
	{	
		/* Write the high byte */
		Data = Copy_u8Color>> 8;
		voidWriteData(Data);
		
		/* Write the low byte */
		Data = Copy_u8Color & 0x00ff;
		voidWriteData(Data);
		
		
	}
	
	
}
static void SetCursorPosition(u8 Copy_u8X1, u8 Copy_u8Y1, u8 Copy_u8X2, u8 Copy_u8Y2)
{
	
	voidWriteCommand(X_ADDRESS);
	voidWriteData(0);
	voidWriteData(Copy_u8X1);
	voidWriteData(0);
	voidWriteData(Copy_u8X2);
	
	voidWriteCommand(Y_ADDRESS);
	voidWriteData(0);
	voidWriteData(Copy_u8Y1);
	voidWriteData(0);
	voidWriteData(Copy_u8Y2);
	
}
void HTFT_DrawPixel(u8 Copy_u8X, u8 Copy_u8Y, u16 Copy_u16Color)
{
	SetCursorPosition(Copy_u8X,Copy_u8Y,Copy_u8X,Copy_u8Y);
	voidWriteCommand(WRITE_COMMAND);
	voidWriteData(Copy_u16Color >> 8);
	voidWriteData(Copy_u16Color & 0x00ff);
}
void HTFT_DrawLine(u8 Copy_u8X1, u8 Copy_u8Y1,u8 Copy_u8X2,  u8 Copy_u8Y2,u16 Copy_u16Color)
{
	/* Vertical or horizontal line */
	HTFT_voidFill(Copy_u8X1, Copy_u8Y1, Copy_u8X2, Copy_u8Y2,Copy_u16Color);
	
}
void HTFT_DrawRectangle(u8 Copy_u8X1, u8 Copy_u8Y1, u8 Copy_u8X2, u8 Copy_u8Y2, u16  Copy_u16Color)
{
	HTFT_DrawLine(Copy_u8X1, Copy_u8Y2, Copy_u8X2, Copy_u8Y2, Copy_u16Color); //Top
	HTFT_DrawLine(Copy_u8X2, Copy_u8Y1, Copy_u8X2, Copy_u8Y2, Copy_u16Color);//Left
	HTFT_DrawLine(Copy_u8X1, Copy_u8Y1, Copy_u8X1, Copy_u8Y2, Copy_u16Color);//Right
	HTFT_DrawLine(Copy_u8X1, Copy_u8Y1, Copy_u8X2, Copy_u8Y1, Copy_u16Color);//Bottom
}
void HTFT_DrawChar(char Character, u8 Copy_u8X, u8 Copy_u8Y, u16 Copy_u16Color)
{
	u8 	Local_u8Char;
    u8 	i,j;

    Local_u8Char = Character;

    if (Local_u8Char < ' ')
    {
        Character = 0;
    }
    else
    {
    	Local_u8Char -= 32;
	}

	char temp[CHAR_WIDTH];
	for(u8 k = 0; k<CHAR_WIDTH; k++)
	{
		temp[k] = font[Local_u8Char][k];
	}

    for (j=0; j<CHAR_WIDTH; j++)
    {
        for (i=0; i<CHAR_HEIGHT; i++)
        {
            if (temp[j] & (1<<i))
            {
            	HTFT_DrawPixel(Copy_u8X+j, Copy_u8Y+i, Copy_u16Color);
            }
        }
    }
}
void HTFT_DrawText(const char* Text, u8 Copy_u8X, u8 Copy_u8Y, u16 Copy_u16Color)
{
    while (*Text)
    {
    	HTFT_DrawChar(*Text++, Copy_u8X, Copy_u8Y,Copy_u16Color);
        Copy_u8X += CHAR_WIDTH;
    }
}
void HTFT_DrawFilledCircle(u16 Copy_u16X, u16 Copy_u16Y, u16 Copy_u16Radius, u16 Copy_u16Colour)
{

	s16 x = Copy_u16Radius;
    s16 y = 0;
    s16 xChange = 1 - (Copy_u16Radius << 1);
    s16 yChange = 0;
    s16 radiusError = 0;

    while (x >= y)
    {
        for (int i = Copy_u16X - x; i <= Copy_u16X + x; i++)
        {
        	HTFT_DrawPixel(i, Copy_u16Y + y,Copy_u16Colour);
        	HTFT_DrawPixel(i, Copy_u16Y - y,Copy_u16Colour);
        }
        for (int i = Copy_u16X - y; i <= Copy_u16X + y; i++)
        {
        	HTFT_DrawPixel(i, Copy_u16Y + x,Copy_u16Colour);
        	HTFT_DrawPixel(i, Copy_u16Y - x,Copy_u16Colour);
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }

}
void HTFT_DrawHollowCircle(u16 Copy_u16X, u16 Copy_u16Y,u16 Copy_u16Radius,u16 Copy_u16Colour)
{
	s16 x = Copy_u16Radius-1;
	s16 y = 0;
	s16 dx = 1;
	s16 dy = 1;
	s16 err = dx - (Copy_u16Radius << 1);

    while (x >= y)
    {
    	HTFT_DrawPixel(Copy_u16X + x, Copy_u16Y + y,  Copy_u16Colour);
    	HTFT_DrawPixel(Copy_u16X + y, Copy_u16Y + x,  Copy_u16Colour);
    	HTFT_DrawPixel(Copy_u16X - y, Copy_u16Y + x,  Copy_u16Colour);
    	HTFT_DrawPixel(Copy_u16X - x, Copy_u16Y + y,  Copy_u16Colour);
    	HTFT_DrawPixel(Copy_u16X - x, Copy_u16Y - y,  Copy_u16Colour);
    	HTFT_DrawPixel(Copy_u16X - y, Copy_u16Y - x,  Copy_u16Colour);
    	HTFT_DrawPixel(Copy_u16X + y, Copy_u16Y - x,  Copy_u16Colour);
    	HTFT_DrawPixel(Copy_u16X + x, Copy_u16Y - y,  Copy_u16Colour);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += (-Copy_u16Radius << 1) + dx;
        }
    }
}

void HTFT_SetRotation(u8 Copy_u8Rotation )
{
	u8 data;
	switch (Copy_u8Rotation)
	{
	case vertical:
		data = MADCTL_MX | MADCTL_MY;
		break;
	case Horizontal:
		data = MADCTL_MY | MADCTL_MV;
		break;
	}

	voidWriteCommand(MADCTL);
	voidWriteData(data);

}



