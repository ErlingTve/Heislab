#include "timer.h"

#include <time.h>

void timer_start_timer(void){
	Timestamp = time(NULL);
}

int timer_timer_expired(double sec){
	if(difftime(time(NULL), Timestamp) < sec){
		return 0;
	}
	return 1;
}
