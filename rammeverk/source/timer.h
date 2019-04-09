#ifndef TIMER_H
#define TIMER_H

/**
	@file
	@brief Denne modulen inneholder alle timerfunksjoner og -variablecd ra	
*/

#include <time.h>

/**
@brief Setter et timestamp til nåtid
*/
void timer_startTimer(void);

/**
@brief Sjekker om det har gått over tre sekunder siden timestamp ble satt
*/
int timer_timerExpired(void);

/**
@brief Lokal variabel for antall sekunder gått
*/
static time_t Timestamp = 0;

#endif
