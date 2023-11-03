/*

	This file was copied from Pi Pico examples and modified by Katsumi.

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "EPD_2in13b_V4.h"

extern const unsigned char gImage_2in13b_V4b[];
extern const unsigned char gImage_2in13b_V4r[];

int main() {
	int i;
	stdio_init_all();
	for(i=5;0<i;i--){
		printf("%d\n",i);
		sleep_ms(1000);	
	}

    printf("EPD_2in13B_V4_test Demo\n");
    if(DEV_Module_Init()!=0){
	    printf("DEV_Module_Init() error!\n");
        return -1;
    }

    printf("e-Paper Init and Clear...\n");
	EPD_2IN13B_V4_Init();
    EPD_2IN13B_V4_Clear();
    printf("show image for array\n");
    EPD_2IN13B_V4_Display(gImage_2in13b_V4b, gImage_2in13b_V4r);
	printf("Goto Sleep...\n");
    EPD_2IN13B_V4_Sleep();
    DEV_Module_Exit();

	while (true) {
		printf(".");
		sleep_ms(1000);
	}
	return 0;
}
