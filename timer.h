/*
 * timer.h
 *
 *  Created on: 15 mar 2023
 *      Author: Grzegorz Gibek
 */

#ifndef TIMER_H_
#define TIMER_H_
// definicje pinów portów przycisków
#define KEY_ONOFF (1<<PD2)
#define KEY_RESET (1<<PD3)
// deklaracje funkcji
void initTimer(void);
void startTimer(void);
void stopTimer(void);
void setTimer(uint16_t nr);
void resetTimer(void);


#endif /* TIMER_H_ */
