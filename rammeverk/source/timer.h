#ifndef TIMER_H
#define TIMER_H

/**
	@file
	@brief These functions and variables keep track of elapsed time since timer was set and reseting the timer.
*/

#include <time.h>

/**
    @brief Setter et timestamp til nåtid
*/
void timer_start_timer(void);

/**
    @brief Sjekker om det har gått over tre sekunder siden timestamp ble satt
    @return
*/
int timer_timer_expired(double sek);

/**
@brief Lokal variabel for antall sekunder gått
*/
static time_t Timestamp = 0;

#endif
