/*
 * led.h
 *
 *  Created on: 11 mar 2023
 *      Author: Grzegorz Gibek
 */

#ifndef LED_H_
#define LED_H_
// definicje portów i pinów wyœwietlacza
#define LED_DATA_DIR DDRB
#define LED_DATA PORTB
#define LED_ANODES_DIR DDRC
#define LED_ANODES PORTC

#define ANODE0 (1<<PC0)
#define ANODE1 (1<<PC1)
#define ANODE2 (1<<PC2)
#define ANODE3 (1<<PC3)
// definicje segmentów wyœwietlacza
#define A (1<<0)
#define B (1<<1)
#define C (1<<2)
#define D (1<<3)
#define E (1<<4)
#define F (1<<5)
#define G (1<<6)
#define DP (1<<7)
// deklaracje zmiennych i funkcji
extern volatile uint8_t d0;
extern volatile uint8_t d1;
extern volatile uint8_t d2;
extern volatile uint8_t d3;

void initLed(void);
void setLed(uint16_t nr);

#endif /* LED_H_ */
