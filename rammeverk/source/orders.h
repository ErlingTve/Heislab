#ifndef ORDERS_H
#define ORDERS_H
#include "channels.h"
/**
	@file
	@brief File to manage orders
*/

/**
 @brief Matrise med bestillingene til heisen
*/
static int order_matrix[N_FLOORS][N_BUTTONS];

/**
 @brief Itererer gjennom alle knappene for å se om de er trykket inn og oppdaterer bestillingsmatrisen
*/
void orders_updateOrderMatrix(void);

/**
 @brief Setter motorretning til den prioriterte retningen og returnerer om det er bestillinger.
@return -1 hvis ingen bestillinger, 0 hvis bestilling i samme etasje og 1 hvis det er i en annen etasje
*/
int orders_setPriorityDirectionAndReturnIfOrders(void);

/**
 @brief Gir om det finnes bestillinger i det hele tatt
 @return 1 om det finnes bestillinger, 0 hvis ikke
 */
int orders_existOrders(void);

/**
 @brief Setter motorretningen til den prioriterte retningen, kun opp eller ned
 */
void orders_setPriorityDirection(void);

/**
 @brief Returnerer om det er bestillinger i valgt etasje
 @param floor Etasjenummer
 @return 1 hvis det finnes bestilling i valgt etasje, 0 hvis ikke
*/
int orders_orderAtThisFloor(int floor);

/**
 @brief Sletter besillinger i gitt etasje
 @param floor Etasjenummer
 */
void orders_deleteOrdersAtThisFloor(int floor);

/**
 @brief Sletter alle bestillinger
 */
void orders_deleteAllOrders(void);

/**
 @brief Ser om det er en bestilling fra inne i heisen til etasjen heisen er i
 @return 1 om det er en bestilling fra inne i heisen til etasjen heisen er i
 @return 0 hvis ikke
 */
int orders_commandAtFloor(void);

/**
 @brief Sier om det er noen som har trykket 'opp' i etasjen heisen er i
 @return 1 hvis noen har trykket på up i etasjen heisen er i
 @return 0 hvis ikke
 */
int orders_upAtFloor(void);

/**
 @brief Sier om det er noen som har trykket 'ned' i etasjen heisen er i
 @return 1 hvis noen har trykket på ned i etasjen heisen er i
 @return 0 hvis ikke
*/
int orders_downAtFloor(void);

//FUNKSJONENE UNDER SKAL SLETTES
/**
 @brief DENNE SKAL ENDRES
 */
float orders_savePositionBetweenFloors(void);

/**
 @brief Setter retning når heisen har stoppet mellom to etasjer. MÅ ENDRES ETTERSOM POSISJONSLOGIKKEN ENDRES
 @param position Et flyttall som sier mellom hvilke etasjer heisen er
 */
void orders_setDirectionBetweenFloors(float position);

#endif
