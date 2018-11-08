#ifndef _LCD_HEADER
#define _LCD_HEADER

// Numeracja wyswietlacza:

//		   /$$$$$$        /$$$$$$          /$$          /$$$$$$     
//		 /$$__  $$      /$$__  $$  /$$  /$$$$         /$$$_  $$    
//		|__/  \ $$     |__/  \ $$ |__/ |_  $$        | $$$$\ $$
//		   /$$$$$/       /$$$$$$/        | $$        | $$ $$ $$
//		  |___  $$      /$$____/   /$$   | $$        | $$\ $$$$
//		 /$$  \ $$     | $$       |__/   | $$        | $$ \ $$$
//		|  $$$$$$/ /$$ | $$$$$$$$  /$$  /$$$$$$  /$$ |  $$$$$$/
//		 \______/ |__/ |________/ |__/ |______/ |__/  \______/     

// dwukropek nalezy do "zera"



#include "MKL46Z4.h"   /* Device header */
// zdefiniowanie ilosci pinów na poszczególnych plaszczyznach
#define LCD_N_FRONT 8
#define LCD_N_BACK 4
// Makra dla segmentów, kazdy znak sterowany jest przez dwa piny
// Pin 1 -> (Digit*2 - 1), Pin 2 -> Digit*2
// Pin 1 Pin 2
// COM0 D Dec
// COM1 E C
// COM2 G B
// COM3 F A
#define LCD_S_D 0x11 // segment D
#define LCD_S_E 0x22 // segment E
#define LCD_S_G 0x44 // segment G
#define LCD_S_F 0x88 // segment F
#define LCD_S_DEC 0x11
#define LCD_S_C 0x22
#define LCD_S_B 0x44
#define LCD_S_A 0x88
#define LCD_C 0x00 // clear
// Makra dla kazdego pinu
#define LCD_FRONT0 37u
#define LCD_FRONT1 17u
#define LCD_FRONT2 7u
#define LCD_FRONT3 8u
#define LCD_FRONT4 53u
#define LCD_FRONT5 38u
#define LCD_FRONT6 10u
#define LCD_FRONT7 11u

#define LCD_BACK0 40u
#define LCD_BACK1 51u
#define LCD_BACK2 19u
#define LCD_BACK3 18u
// Zmienne tworzace dwie tablice
// const static uint8_t LCD_Front_Pin[8] = {LCD_FRONT0, LCD_FRONT1, LCD_FRONT2, LCD_FRONT3, LCD_FRONT4, LCD_FRONT5, LCD_FRONT6, LCD_FRONT7};
// const static uint8_t LCD_Back_Pin[4] = {LCD_BACK0, LCD_BACK1, LCD_BACK2, LCD_BACK3};

const static uint16_t LCD_WF8B_HIGH[16] = {	LCD_S_D | LCD_S_E | LCD_S_F, 					// 0
																						0, 																		// 1
																						LCD_S_D | LCD_S_E | LCD_S_G, 					// 2
																						LCD_S_D | LCD_S_G, 										// 3
																						LCD_S_G | LCD_S_F, 										// 4
																						LCD_S_D | LCD_S_G | LCD_S_F, 					// 5
																						LCD_S_D | LCD_S_E | LCD_S_G | LCD_S_F,// 6
																						0, 																		// 7
																						LCD_S_D | LCD_S_E | LCD_S_G | LCD_S_F,// 8
																						LCD_S_D | LCD_S_G | LCD_S_F, 					// 9
																						LCD_S_E | LCD_S_G | LCD_S_F, 					// A
																						LCD_S_D | LCD_S_E | LCD_S_G | LCD_S_F,// b
																						LCD_S_D | LCD_S_E | LCD_S_F, 					// C
																						LCD_S_D | LCD_S_E | LCD_S_G, 					// d
																						LCD_S_D | LCD_S_E | LCD_S_G | LCD_S_F,// E
																						LCD_S_E | LCD_S_G | LCD_S_F}; 				// F

const static uint16_t LCD_WF8B_LOW[16] = {	LCD_S_C | LCD_S_B | LCD_S_A, 					// 0
																						LCD_S_C | LCD_S_B, 										// 1
																						LCD_S_B | LCD_S_A, 										// 2
																						LCD_S_C | LCD_S_B | LCD_S_A, 					// 3
																						LCD_S_C | LCD_S_B, 										// 4
																						LCD_S_C | LCD_S_A, 										// 5
																						LCD_S_C | LCD_S_A, 										// 6
																						LCD_S_C | LCD_S_B | LCD_S_A, 					// 7
																						LCD_S_C | LCD_S_B | LCD_S_A, 					// 8
																						LCD_S_C | LCD_S_B | LCD_S_A, 					// 9
																						LCD_S_C | LCD_S_B | LCD_S_A, 					// A
																						LCD_S_C, 															// b
																						LCD_S_A, 															// C
																						LCD_S_C | LCD_S_B, 										// d
																						LCD_S_A, 															// E
																						LCD_S_A  															// F

};

const static uint8_t digit_ABC[4] = {LCD_FRONT7,LCD_FRONT5,LCD_FRONT3,LCD_FRONT1};
const static uint8_t digit_DEFG[4]= {LCD_FRONT6,LCD_FRONT4,LCD_FRONT2,LCD_FRONT0};

void LCD_Init(void);
void LCD_setNumber(uint8_t number, uint8_t digit, uint8_t dot);
void LCD_setDot(uint8_t digit);
void LCD_resetDot(uint8_t digit);













#endif
