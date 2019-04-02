#ifndef ESM_H
#define ESM_H
/**
	@file
	@brief File to make elevator state machine
*/

// definerte navn på de forskjellige tilstandende til tilstandsmaskinen
enum state {Waiting_for_init, Not_moving_at_floor, Moving, At_floor, Not_moving_between_floors};

//initalisering av tilstandsmaskin
void esm_initState()


//endrer tilstander (i praksis tilstandsmaskinen)
void esm_stateSwitch();

#endif