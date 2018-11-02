#include "MKL46Z4.h"
#include "lcd.h"

int main(void)
{
	LCD_Init();
	//LCD_setNumber(13,0,0);
	//LCD_setNumber(20,1,0);
	//LCD_setNumber(15,2,0);
	//LCD_setNumber(12,3,0);
	/*
	LCD_setDot(2);
	for (uint16_t i = 0; i < 10000; i++)
	{
		for (uint16_t k = 0; k < 1000; k++){};
	}
	//LCD_resetDot(2
	LCD_setNumber(15,2,1);
	for (uint16_t i = 0; i < 10000; i++)
	{
		for (uint16_t k = 0; k < 1000; k++){};
	}
	LCD_setNumber(15,2,0);
	*/
	LCD_setInt(-234);
	while(1) //petla zdarzen
	{
		//for (uint16_t i = 0; i < 10000; i++);
		//
	}
}
