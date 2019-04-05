#ifndef ESM_H
#define ESM_H
/**
	@file
	@brief File to make elevator state machine
*/

// definerte navn på de forskjellige tilstandende til tilstandsmaskinen
typedef enum {WAITING_FOR_INIT, NOT_MOVING_AT_FLOOR, MOVING, AT_FLOOR, NOT_MOVING_BETWEEN_FLOORS} state;

//endrer tilstander (i praksis tilstandsmaskinen)
void esm_stateSwitch(state CurrentState);

#endif
