/*
*Author     : Moustafa ElGafry
*Date       : 27 SEP 2020
*Version    : V01
*/
#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H
/* Colors */
#define BLACK       0x0000
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xF81F

#define vertical	0
#define Horizontal 	1


void 	HTFT_voidInit(void);
void    HTFT_DisplayOff(void);
void 	HTFT_voidDisplayImage(const u16 * Copy_p8Image);
void 	HTFT_voidFillScreen( u16 Copy_u8Color);
void 	HTFT_voidFill( u8 Copy_u8X1,u8 Copy_u8Y1,u8 Copy_u8X2 ,u16 Copy_u8Y2, u16 Copy_u16Color);
void	HTFT_DrawPixel(u8 Copy_u8X, u8 Copy_u8Y, u16 Copy_u16Color);
void 	HTFT_DrawLine(u8 Copy_u8X1, u8 Copy_u8Y1, u8 Copy_u8X2, u8 Copy_u8Y2,u16 Copy_u8Color);
void 	HTFT_DrawRectangle(u8 Copy_u8X1, u8 Copy_u8Y1, u8 Copy_u8X2,u8 Copy_u8Y2, u16 Copy_u8Color);
void 	HTFT_DrawChar(char Character, u8 Copy_u8X, u8 Copy_u8Y, u16 Copy_u16Color);
void	HTFT_DrawText(const char* Text, u8 Copy_u8X, u8 Copy_u8Y, u16 Copy_u16Color);
void 	HTFT_DrawFilledCircle(u16 Copy_u16X, u16 Copy_u16Y, u16 Copy_u16Radius, u16 Copy_u16Colour);
void 	HTFT_DrawHollowCircle(u16 Copy_u16X, u16 Copy_u16Y,u16 Copy_u16Radius,u16 Copy_u16Colour);
void 	HTFT_SetRotation(u8 Copy_u8Rotation );


#endif
