#include "MKL46Z4.h"
#include "lcd.h"
#include "math.h"

void LCD_Init(void)
{
// konfiguracja zegara dla portów wykorzystywanych przy obsludze wyswietlacza
	// i modulu sLCD
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_SLCD_MASK;
	// wstepne wylaczenie i reset kontrolera
	LCD->GCR |= LCD_GCR_PADSAFE_MASK; // !!!!!!
	LCD->GCR &= ~LCD_GCR_LCDEN_MASK; // Clear LCDEN w trakcie konfiguracji
		// konfiguracja multiplekserów do operacji portów jako kontroler LCD
	PORTD->PCR[0 ] = PORT_PCR_MUX(0u);
	PORTE->PCR[4 ] = PORT_PCR_MUX(0u);
	PORTB->PCR[23] = PORT_PCR_MUX(0u);
	PORTB->PCR[22] = PORT_PCR_MUX(0u);
	PORTC->PCR[17] = PORT_PCR_MUX(0u);
	PORTB->PCR[21] = PORT_PCR_MUX(0u);
	PORTB->PCR[7 ] = PORT_PCR_MUX(0u);
	PORTB->PCR[8 ] = PORT_PCR_MUX(0u);
	PORTE->PCR[5 ] = PORT_PCR_MUX(0u);
	PORTC->PCR[18] = PORT_PCR_MUX(0u);
	PORTB->PCR[10] = PORT_PCR_MUX(0u);
	PORTB->PCR[11] = PORT_PCR_MUX(0u);
	// konfiguracja rejestrów LCD
	LCD->GCR = // !!!!!!
		LCD_GCR_RVTRIM(0x00) |
		LCD_GCR_CPSEL_MASK |
		LCD_GCR_LADJ(0x03) |
		LCD_GCR_VSUPPLY_MASK |
		LCD_GCR_ALTDIV(0x00) |
		LCD_GCR_SOURCE_MASK |
		LCD_GCR_LCLK(0x01) |
		LCD_GCR_DUTY(0x03);
	// konfiguracja migania wyswietlacza
	LCD->AR = LCD_AR_BRATE(0x03); // !!!!!!
	// konfiguracja rejestru FDCR
	LCD->FDCR = 0x00000000; // !!!!!!
	// aktywowanie 12 pinów do kontroli wyswietlaczem (dwa rejestry po 32 bity)
	LCD->PEN[0] =
		LCD_PEN_PEN(1u << 7 ) | // LCD_P7
		LCD_PEN_PEN(1u << 8 ) | // LCD_P8
		LCD_PEN_PEN(1u << 10) | // LCD_P10
		LCD_PEN_PEN(1u << 11) | // LCD_P11
		LCD_PEN_PEN(1u << 17) | // LCD_P17
		LCD_PEN_PEN(1u << 18) | // LCD_P18
		LCD_PEN_PEN(1u << 19);  // LCD_P19
	LCD->PEN[1] =
		LCD_PEN_PEN(1u << (LCD_FRONT0 - 32) ) | // LCD_P37
		LCD_PEN_PEN(1u << 6 ) | // LCD_P38
		LCD_PEN_PEN(1u << 8 ) | // LCD_P40
		LCD_PEN_PEN(1u << 20) | // LCD_P52
		LCD_PEN_PEN(1u << 21);  // LCD_P53
	// skonfigurowanie 4 pinów plaszczyzny tylnej (dwa rejestry po 32 bity)
	LCD->BPEN[0] =
		LCD_BPEN_BPEN(1u << 18) | // LCD_P18
		LCD_BPEN_BPEN(1u << 19);  // LCD_P19
	LCD->BPEN[1] =
		LCD_BPEN_BPEN(1u << 8 ) | // LCD_P40
		LCD_BPEN_BPEN(1u << 20);  // LCD_P52
	// konfiguracja rejestrów przebiegów (Waveform register) – 4 aktywne, reszta nie
	// konfiguracja polega na równomiernym rozlozeniu faz, w tym przypadku 4, na 8 bitach
	// (44.3.7 w KL46 Reference Manual)
	LCD->WF[0] =
		LCD_WF_WF0(0x00) |
		LCD_WF_WF1(0x00) |
		LCD_WF_WF2(0x00) |
		LCD_WF_WF3(0x00);
	LCD->WF[1] =
		LCD_WF_WF4(0x00) |
		LCD_WF_WF5(0x00) |
		LCD_WF_WF6(0x00) |
		LCD_WF_WF7(0x00);
	LCD->WF[2] =
		LCD_WF_WF8(0x00) |
		LCD_WF_WF9(0x00) |
		LCD_WF_WF10(0x00) |
		LCD_WF_WF11(0x00);
	LCD->WF[3] =
		LCD_WF_WF12(0x00) |
		LCD_WF_WF13(0x00) |
		LCD_WF_WF14(0x00) |
		LCD_WF_WF15(0x00);
	LCD->WF[4] =
		LCD_WF_WF16(0x00) |
		LCD_WF_WF17(0x00) |
		LCD_WF_WF18(0x88) | // COM3 (10001000)
		LCD_WF_WF19(0x44); // COM2 (01000100)
	LCD->WF[5] =
		LCD_WF_WF20(0x00) |
		LCD_WF_WF21(0x00) |
		LCD_WF_WF22(0x00) |
		LCD_WF_WF23(0x00);
	LCD->WF[6] =
		LCD_WF_WF24(0x00) |
		LCD_WF_WF25(0x00) |
		LCD_WF_WF26(0x00) |
		LCD_WF_WF27(0x00);
	LCD->WF[7] =
		LCD_WF_WF28(0x00) |
		LCD_WF_WF29(0x00) |
		LCD_WF_WF30(0x00) |
		LCD_WF_WF31(0x00);
	LCD->WF[8] =
		LCD_WF_WF32(0x00) |
		LCD_WF_WF33(0x00) |
		LCD_WF_WF34(0x00) |
		LCD_WF_WF35(0x00);
	LCD->WF[9] =
		LCD_WF_WF36(0x00) |
		LCD_WF_WF37(0x00) |
		LCD_WF_WF38(0x00) |
		LCD_WF_WF39(0x00);
	LCD->WF[10] =
		LCD_WF_WF40(0x11) | // COM0 (00010001)
		LCD_WF_WF41(0x00) |
		LCD_WF_WF42(0x00) |
		LCD_WF_WF43(0x00);
	LCD->WF[11] =
		LCD_WF_WF44(0x00) |
		LCD_WF_WF45(0x00) |
		LCD_WF_WF46(0x00) |
		LCD_WF_WF47(0x00);
	LCD->WF[12] =
		LCD_WF_WF48(0x00) |
		LCD_WF_WF49(0x00) |
		LCD_WF_WF50(0x00) |
		LCD_WF_WF51(0x00);
	LCD->WF[13] =
		LCD_WF_WF52(0x22) | // COM1 (00100010)
		LCD_WF_WF53(0x00) |
		LCD_WF_WF54(0x00) |
		LCD_WF_WF55(0x00);
	LCD->WF[14] =
		LCD_WF_WF56(0x00) |
		LCD_WF_WF57(0x00) |
		LCD_WF_WF58(0x00) |
		LCD_WF_WF59(0x00);
	LCD->WF[15] =
		LCD_WF_WF60(0x00) |
		LCD_WF_WF61(0x00) |
		LCD_WF_WF62(0x00) |
		LCD_WF_WF63(0x00);
		
		// MCG->C1  |= MCG_C1_IRCLKEN_MASK | MCG_C1_IREFSTEN_MASK;
    // MCG->C2  |= MCG_C2_IRCS_MASK ;
		
	// koniec konfiguracji, wiec clear PADSAFE i wlaczenie wyswietlacza
	LCD->GCR &= ~LCD_GCR_PADSAFE_MASK; // !!!!!!
	LCD->GCR |= LCD_GCR_LCDEN_MASK; // wlaczenie wyswietlacza
	 
}
//--------------------------------------------------------------------------//
// number - znak jaki ma byc wyswietlony, od 0 do F (0 do 15)
// digit - numer wyswietlacza, na którzym ma byc znak
// dot - kropka, 0-gasi kropke, 1-zaswieca kropke, 2-ignoruje kropke
//--------------------------------------------------------------------------//
void LCD_setNumber(uint8_t number, uint8_t digit, uint8_t dot)
{
	 digit &= 3;  // zabezpieczenie zeby nie przekroczyc liczby 3, bo numercja jest od 0 do 3
	// number &= 15; // zabezpieczenie zeby nie przekrocznyc liczby 15, bo znaków jest od 0 do 15
	if (dot == 2)
	{
		uint8_t oldDot = LCD->WF8B[digit_FRONT_ABC[digit]] & 1;
		LCD->WF8B[digit_FRONT_ABC[digit]] = LCD_WF8B_LOW[number & 15] | oldDot;
	}
	else LCD->WF8B[digit_FRONT_ABC[digit]] = LCD_WF8B_LOW[number & 15] | (dot & 1);
	LCD->WF8B[digit_FRONT_DEFG[digit]] = LCD_WF8B_HIGH[number & 15];
}

void LCD_setDot(uint8_t digit)
{
	LCD->WF8B[digit_FRONT_ABC[digit & 3]] |= 1;
}

void LCD_resetDot(uint8_t digit)
{
	LCD->WF8B[digit_FRONT_ABC[digit & 3]] &= ~1;
}
//--------------------------------------------------------------------------//
// errNumber = 1 - przekroczenie dodatnieko zakresu przy wejsciowym int //
// errNumber = 2 - przekroczenie ujemnego zakresu przy wejsciowym int //
// errNumber = 3 - podanie ujemnej wartosci przy wejsciowym int // 
void LCD_Error(uint8_t errNumber)
{
	LCD->WF8B[LCD_FRONT0] = LCD_S_F | LCD_S_G | LCD_S_E | LCD_S_D; //E
	LCD->WF8B[LCD_FRONT1] = LCD_S_A;
	
	LCD->WF8B[LCD_FRONT2] =  LCD_S_G | LCD_S_E ;									// r
	LCD->WF8B[LCD_FRONT4] =  LCD_S_G | LCD_S_E ;									// r
	
	LCD_setNumber(errNumber, 0, 2);
}
//--------------------------------------------------------------------------//
// number - liczba, jaka musi byc wyswietlona na wyswietlaczu
// form - rormat wyswietlania, 16-HEX, 10-DEC, 8-OCT, 2-BIN
//--------------------------------------------------------------------------//
void LCD_setUInt(uint16_t number, uint8_t form)
{	if(number<0)
	{
		LCD_Error(3);
		return;
	}
	
	uint16_t maxNumber = (uint16_t)pow((double)form,4.0) - 1;
	if (number > maxNumber)
	{
		LCD_Error(1);
		return;
	}		
	
	if (form <= 1 || form > 16) return;
	for (uint8_t i = 0; i < 4; i++)
	{
		LCD_setNumber(number % form, i, 2);
		number /= form;
	}
}

//--------------------------------------------------------------------------//
// number - liczba, jaka musi byc wyswietlona na wyswietlaczu, moze byc ujemna
//--------------------------------------------------------------------------//
void LCD_setInt(int number)
{
	if (number < 0)
	{
		number = - number;
		LCD->WF8B[LCD_FRONT0] = LCD_S_G; // napisanie minusa na 3 wyswietlaczu,  najbardzije z lewej
	}

	if (number > 999)
	{
		LCD_Error(2);
		return;
	}
	for (uint8_t i = 0; i < 3; i++)
	{
		LCD_setNumber(number % 10, i, 2);
		number /= 10;
	}
}

