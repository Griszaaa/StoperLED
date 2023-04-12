/*
 * led.c
 *
 *  Created on: 11 mar 2023
 *      Author: Grzegorz Gibek
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "led.h"
// definicje zmiennych przechowuj¹cych cyfry wyœwietlane na wyœwietlaczach
volatile uint8_t d0;
volatile uint8_t d1;
volatile uint8_t d2;
volatile uint8_t d3;

// tablica zdefiniowanych znaków (w pamiêci FLASH - oszczêdnoœæ pamiêci RAM)
const uint16_t characters[] PROGMEM = {
		~(A | B | C | D | E | F ),			// 0
		~(B | C),							// 1
		~(A | B | G | E | D),				// 2
		~(A | B | G | C | D),				// 3
		~(F | G | B | C),					// 4
		~(A | F | G | C | D),				// 5
		~(A | F | G | C | D | E),			// 6
		~(A | B | C),						// 7
		~(A | B | C | D | E | F | G),		// 8
		~(A | B | F | G | C | D),			// 9
		~(A | B | C | D | E | F | DP ),		// 0. (10)
		~(B | C | DP),						// 1. (11)
		~(A | B | G | E | D | DP),			// 2. (12)
		~(A | B | G | C | D | DP),			// 3. (13)
		~(F | G | B | C | DP),				// 4. (14)
		~(A | F | G | C | D | DP),			// 5. (15)
		~(A | F | G | C | D | E | DP),		// 6. (16)
		~(A | B | C | DP),					// 7. (17)
		~(A | B | C | D | E | F | G | DP),	// 8. (18)
		~(A | B | F | G | C | D | DP),		// 9. (19)
};
// inicjalizacja wyœwietlacza LED
void initLed(void)
{
	LED_DATA_DIR = 0xff; // kierunek portu danych wyœwietlacza na wyjœciowy
	LED_DATA = 0xff; // wygaszenie wszystkich katod - stan wysoki

	LED_ANODES_DIR |= ANODE0 | ANODE1 | ANODE2 | ANODE3;  // kierunek portu katod wyœwietlacza na wyjœciowy
	LED_ANODES |=  ANODE0 | ANODE1 | ANODE2 | ANODE3; // wygaszenie wszystkich anod (wyœwietlaczy)

	// ustawienia Timer2
	TCCR2 |= (1<<WGM21); // ustawienie trybu CTC
	TCCR2 |= (1<<CS22) | (1<<CS21) | (1<<CS20); // preskaler - 1024
	OCR2 = 38; // 38 do rejestru porównania (podzia³ przez 39) - przerwanie z czêstotliwoœci¹ ~200 Hz (50 Hz na ka¿dy wyœwietlacz)
	TIMSK |= (1<<OCIE2); // odblokowanie przerwaia od porównania licznika z rejestrem OCR
}
// funkcja wypisuj¹ca ci¹g liczb na wyœwietlaczu
void setLed(uint16_t nr)
{
	if(nr > 9999)
	{
		d0 = 9;
		d1 = 9;
		d2 = 9;
		d3 = 9;
	}
	d0 = nr / 1000;
	d1 = nr / 100 - d0*10;
	d2 = nr / 10 - d0*100 - d1*10;
	d3 = nr / 1 - d0*1000 - d1*100 - d2*10;
}
// procedura obs³ugi przerwania dla Timera2
ISR(TIMER2_COMP_vect)
{
	static uint8_t counter = 1; // zmienna do prze³¹czania wyœwietlaczy

	LED_ANODES = (0xf0 & LED_ANODES) | (0x0f & ~counter); // za³¹czenie konkretnego wyœwietlacza z maskowaniem

	switch(counter)
	{
	case 1:
		LED_DATA = pgm_read_byte(&characters[d0]);
		break;
	case 2:
		LED_DATA = pgm_read_byte(&characters[d1]);
		break;
	case 4:
		LED_DATA = pgm_read_byte(&characters[d2]);
		break;
	case 8:
		LED_DATA = pgm_read_byte(&characters[d3]);
		break;
	}

	counter <<= 1;
	if(counter > 8) counter = 1;
}

