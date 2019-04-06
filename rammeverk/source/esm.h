#ifndef ESM_H
#define ESM_H
/**
	@file
	@brief File to make elevator state machine
*/

/**
 @brief definerer navn på de forskjellige tilstandende til tilstandsmaskinen
 */
typedef enum {WAITING_FOR_INIT, NOT_MOVING_AT_FLOOR, MOVING, AT_FLOOR, NOT_MOVING_BETWEEN_FLOORS} state;

/**
 @brief Endrer tilstander (i praksis tilstandsmaskinen)
 @param CurrentState Nåværende tilstand
*/
void esm_stateSwitch(state CurrentState);

/**
 @brief Enum for hvilken posisjon heisen er i
 */
typedef enum {FØRSTE, MELLOM_FØRSTE_OG_ANDRE, ANDRE, MELLOM_ANDRE_OG_TREDJE, TREDJE, MELLOM_TREDJE_OG_FJERDE, FJERDE} posisjon;

/**
 @brief Global variabel som sier hvilken posisjon heisen til enhver tid er i
 */
posisjon Posisjon;

#endif
