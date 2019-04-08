#include "timer.h"


#include <stdio.h>
#include <time.h>


time_t time (time_t *second);


void timer_startTimer(void){
	Timestamp = time(NULL);
}

bool timer_timerExpired(void){
	if(difftime(time(NULL), Timestamp) < 3){
		return false;
	}
	return true;
}
