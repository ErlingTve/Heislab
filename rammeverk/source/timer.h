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
static time_t Timestamp = time(NULL);