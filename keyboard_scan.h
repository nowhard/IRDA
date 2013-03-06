#ifndef KEYBOARD_SCAN_H
#define KEYBOARD_SCAN_H

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "pt/pt.h"

//--------------key_kodes-----------------
#define KEY_1 		64
#define KEY_2		76
#define KEY_3		4	
#define KEY_4		0
#define KEY_5		10	
#define KEY_6		30
#define KEY_7		14
#define KEY_8		26
#define KEY_9		28
#define KEY_0		20
#define KEY_CH_UP	31
#define KEY_CH_DOWN	22
#define KEY_V_UP	21
#define KEY_V_DOWN	27
#define KEY_MENU	17
#define KEY_POWER	9
//----------------------------------------

PT_THREAD(Keyboard_Scan_Process(struct pt *pt));
PT_THREAD(Delay_Key_Process(struct pt *pt));

#endif
