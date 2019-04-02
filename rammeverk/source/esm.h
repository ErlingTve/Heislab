#ifndef ESM_H
#define ESM_H
/**
	@file
	@brief File to make elevator state machine
*/

// definerte navn på de forskjellige tilstandende til tilstandsmaskinen
typedef enum state {Waiting_for_init, Not_moving_at_floor, Moving, At_floor, Not_moving_between_floors};

//endrer tilstander (i praksis tilstandsmaskinen)
state esm_stateSwitch(state CurrentState);

#endif