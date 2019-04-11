#ifndef FSM_H
#define FSM_H
/**
	@file
	@brief H-file to make the finite state machine for the elevator.
*/

/**
 @brief Enum to define the different states of the finite state machine.
 */
typedef enum {WAITING_AFTER_INIT, NOT_MOVING_AT_FLOOR, MOVING, AT_FLOOR, EMERGENCY_STOP, NOT_MOVING_BETWEEN_FLOORS} state;

/**
 @brief Changes between states, and defines what to do in each state.
*/
void fsm_state_switch(void);

/**
 @brief Private variable containing the state machine's current state.
 */
static state CurrentState=WAITING_AFTER_INIT;


#endif
