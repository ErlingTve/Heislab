#ifndef FSM_H
#define FSM_H
/**
	@file
	@brief H-file to make elevator state machine
*/

/**
 @brief enum to define the different states of the finite statemachine
 */
typedef enum {WAITING_FOR_INIT, NOT_MOVING_AT_FLOOR, MOVING, AT_FLOOR, EMERGENCY_STOP, NOT_MOVING_BETWEEN_FLOORS} state;

/**
 @brief changes between states, and defines what to do in each state
*/
void fsm_state_switch(void);

/**
 @brief Private variable containing the statemachines current state
 */
static state CurrentState=WAITING_FOR_INIT;


#endif
