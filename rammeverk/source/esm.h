#ifndef ESM_H
#define ESM_H
/**
	@file
	@brief File to make elevator state machine
*/

/**
 @brief definerer navn på de forskjellige tilstandende til tilstandsmaskinen
 */
typedef enum {WAITING_FOR_INIT, NOT_MOVING_AT_FLOOR, MOVING, AT_FLOOR, EMERGENCY_STOP, NOT_MOVING_BETWEEN_FLOORS} state;

/**
 @brief Endrer tilstander (i praksis tilstandsmaskinen)
*/
void esm_stateSwitch(void);

/**
 @brief Privat variabel som sier hvilken state tilstandmaskinen er i
 */
static state CurrentState=WAITING_FOR_INIT;


#endif
