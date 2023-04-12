/*
 * timer.c
 *
 *  Created on: 15 mar 2023
 *      Author: Grzegorz Gibek
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "timer.h"
#include "led.h"
// zmienna przechowuj¹ca aktualny czas stopera
volatile uint16_t time;
// funkcja inicjalizuj¹ca stoper
void initTimer(void)
{
	// ustawienia Timer1
	TCCR1B |= (1<<WGM12); 	// ustawienie trybu CTC
//	TCCR1B &= ~(1<<CS12); // preskaler - 64
//	TCCR1B |= (1<<CS11) | (1<<CS10);
	OCR1A = 1249; // wartoœæ ³adowana do rejestru licznika, ¿eby przerwanie by³o z f = 100 Hz
	TIMSK |= (1<<OCIE1A); // odblokowanie przerwania od porównania licznika z rejestrem OCR - start
	setTimer(0);
	// ustawienia INT0
	DDRD &= ~(KEY_ONOFF);
	PORTD |= KEY_ONOFF;
	MCUCR &= ~(1<<ISC00); // zbocze opadaj¹ce wyzwala przerwanie
	MCUCR |= (1<<ISC01);
	GICR |= (1<<INT0); // odblokowanie przerwania dla INT0
	// ustawienia INT1
	DDRD &= ~(KEY_RESET);
	PORTD |= KEY_RESET;
	MCUCR &= ~(1<<ISC10); // zobacze opadaj¹ce wyzwala przerwanie
	MCUCR |= (1<<ISC11);
	GICR |= (1<<INT1); // odblokowanie przerwania dla INT1
}
// funkcja startuj¹ca stoper
void startTimer(void)
{
	TCCR1B |= (1<<CS11) | (1<<CS10);
}
// funkcja zatrzymuj¹ca stoper
void stopTimer(void)
{
	TCCR1B &= ~((1<<CS11) | (1<<CS10));
}
// funkcja wypisuj¹ca ci¹g liczb na wyœwietlaczy (wersja dla stopera)
void setTimer(uint16_t nr)
{
	if(nr > 9999)
	{
		d0 = 9;
		d1 = 9;
		d2 = 9;
		d3 = 9;
	}
	d0 = nr / 1000;
	d1 = (nr / 100 - d0*10) + 10;
	d2 = nr / 10 - d0*100 - (d1 - 10)*10;
	d3 = nr / 1 - d0*1000 - (d1 - 10)*100 - d2*10;
}
// funkcja zeruj¹ca stoper
void resetTimer(void)
{
	time = 0;
	setTimer(time);
}
// procedura obs³ugi przerwania dla Timera1
ISR(TIMER1_COMPA_vect)
{
	setTimer(time);
	time++;
	if(time > 5999) time = 0;
}
// procedura obs³ugi przerwania przycisku on/off
ISR(INT0_vect)
{
	static bool on = true;
	if(on) startTimer();
	else stopTimer();
	on = !on;
}
// procedura obs³ugi przerwania przycisku reset
ISR(INT1_vect)
{
	resetTimer();
}
