#include "timer.h"


#include <stdio.h>
#include <time.h>

void timer_startTimer(void){
	Timestamp = time(NULL);
}

int timer_timerExpired(double sek){
	if(difftime(time(NULL), Timestamp) < sek){
		return 0;
	}
	return 1;
}

