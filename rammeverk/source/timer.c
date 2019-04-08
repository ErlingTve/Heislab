#include "timer.h"

<<<<<<< HEAD
=======
#include <stdio.h>
>>>>>>> eaf799c51f0009a30bb529771d0d01110e8bc46c
#include <time.h>


time_t time (time_t *second)


void timer_startTimer(void){
	Timestamp = time(NULL);
}

bool timer_timerExpired(void){
	if(difftime(time(NULL), Timestamp) < 3){
		return false;
	}
	return true;
}