#ifndef TIMER_H
#define TIMER_H

/**
	@file
	@brief These functions and variables keep track of elapsed time since timer was set, and reseting the timer.
*/

#include <time.h>

/**
    @brief Sets timestamp to current time.
*/
void timer_start_timer(void);

/**
    @brief Checks if sec seconds has passed since last updated timestamp.
    @param sec Number of seconds you want to check has passed since starting timer.
    @return 1 If sec seconds has passed.
    @return 0 If sec seconds hasn't passed.
*/
int timer_timer_expired(double sec);

/**
@brief Local variable for time passed since last updated timestamp.
*/
static time_t Timestamp = 0;

#endif
