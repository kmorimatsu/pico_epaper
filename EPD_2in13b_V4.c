#include <stdlib.h>
#include "GUI_Paint.h"
#include "lib/e-Paper/EPD_2in13b_V4.h"

int EPD_2in13b_V4_test(void)
{
	stdio_init_all();
	DEV_Delay_ms(3000); 

	int t=time_us_32();
	printf("EPD_2IN13B_V4_test Demo\r\n");
	if(DEV_Module_Init()!=0){
		return -1;
	}

	//printf("e-Paper Init and Clear...\r\n");
	printf("e-Paper Init...\r\n");
	EPD_2IN13B_V4_Init();
	//EPD_2IN13B_V4_Clear(); // This takes ~17.8 secs
	//DEV_Delay_ms(500);

	//Create a new image cache named IMAGE_BW and fill it with white
	UBYTE *BlackImage, *RYImage; // Red or Yellow
	UWORD Imagesize = ((EPD_2IN13B_V4_WIDTH % 8 == 0)? (EPD_2IN13B_V4_WIDTH / 8 ): (EPD_2IN13B_V4_WIDTH / 8 + 1)) * EPD_2IN13B_V4_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
		return -1;
	}
	if((RYImage = (UBYTE *)malloc(Imagesize)) == NULL) {
		printf("Failed to apply for red memory...\r\ngImage_2in13b_V4b");
		return -1;
	}
	printf("NewImage:BlackImage and RYImage\r\n");
	Paint_NewImage(BlackImage, EPD_2IN13B_V4_WIDTH, EPD_2IN13B_V4_HEIGHT, 90, WHITE);
	Paint_NewImage(RYImage, EPD_2IN13B_V4_WIDTH, EPD_2IN13B_V4_HEIGHT, 90, WHITE);

	//Select Image
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_SelectImage(RYImage);
	Paint_Clear(WHITE);

	/*Horizontal screen*/
	//1.Draw black image
	printf("Draw black image\r\n");
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	//Paint_DrawString_EN(5, 0, "Hello,", &Font24, BLACK, WHITE);
	//Paint_DrawString_EN(5, 24, "Hello,", &Font24, WHITE, BLACK);
	Paint_DrawString_EN(0, 20, " ", &Font82, WHITE, BLACK);
	Paint_DrawString_EN(0+56, 0, "45", &Font107, WHITE, BLACK);
	Paint_DrawString_EN(0+56+70*2, 20, "%", &Font82, WHITE, BLACK);
	Paint_DrawString_EN(17*5-3,98,"o",&Font8, WHITE, BLACK);
	Paint_DrawString_EN(17*12-3,98,"o",&Font8, WHITE, BLACK);
	Paint_DrawString_EN(0,98," 25.1C  77.2F",&Font24, WHITE, BLACK);
	Paint_DrawString_EN(0,0,"%",&Battery32, WHITE, BLACK);

	//2.Draw red image
	printf("Draw red image\r\n");
	Paint_SelectImage(RYImage);
	Paint_Clear(WHITE);
	//Paint_DrawString_EN(5+17*6, 0, " World!", &Font24, BLACK, WHITE);
	//Paint_DrawString_EN(5+17*6, 24, " World!", &Font24, WHITE, BLACK);
	//Paint_DrawString_EN(68, 0, "W", &Font96, WHITE, BLACK);

	printf("EPD_Display\r\n");
	EPD_2IN13B_V4_Display(BlackImage, RYImage);

	printf("Goto Sleep...\r\n");
	EPD_2IN13B_V4_Sleep();
	free(BlackImage);
	free(RYImage);
	BlackImage = NULL;
	RYImage = NULL;
	DEV_Delay_ms(2000);//important, at least 2s
	// close 5V
	printf("close 5V, Module enters 0 power consumption ...\r\n");
	DEV_Module_Exit();

	return 0;
}
