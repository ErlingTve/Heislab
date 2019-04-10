#include "timer.h"


#include <stdio.h>
#include <time.h>

void timer_start_timer(void){
	Timestamp = time(NULL);
}

int timer_timer_expired(double sek){
	if(difftime(time(NULL), Timestamp) < sek){
		return 0;
	}
	return 1;
}
