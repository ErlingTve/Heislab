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
 @brief Enum for hvilken posisjon heisen er i. 0-3 for etasje (for enkel bruk i andre funksjoner). 4-6 for mellom etasjene. 
 */
typedef enum {FØRSTE = 0, ANDRE = 1, TREDJE = 2, FJERDE = 3, MELLOM_FØRSTE_OG_ANDRE = 4, MELLOM_ANDRE_OG_TREDJE = 5,  MELLOM_TREDJE_OG_FJERDE = 6} posisjon;

/**
 @brief Global variabel som sier hvilken posisjon heisen til enhver tid er i
 */
posisjon Posisjon;

#endif
