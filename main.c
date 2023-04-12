/*
 * main.c
 *
 *  Created on: 11 mar 2023
 *      Author: Grzegorz Gibek
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "led.h"
#include "timer.h"


int main(void)
{
	initLed(); // inicjalizacja wy�wietlacza
	initTimer(); // inicjalizacja stopera
	sei(); // globalne zezwolenie na przerwania
	while(1)
	{

	}
}


