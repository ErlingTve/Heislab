#ifndef ORDERS_H
#define ORDERS_H
#include "channels.h"
#include "esm.h"
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
 @brief Gir om det finnes bestillinger i det hele tatt
 @return 1 om det finnes bestillinger, 0 hvis ikke
 */
int orders_existOrders(void);


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
int orders_commandAtFloor(posisjon pos);

/**
 @brief Sier om det er noen som har trykket 'opp' i etasjen heisen er i
 @return 1 hvis noen har trykket på up i etasjen heisen er i
 @return 0 hvis ikke
 */
int orders_upAtFloor(posisjon pos);

/**
 @brief Sier om det er noen som har trykket 'ned' i etasjen heisen er i
 @return 1 hvis noen har trykket på ned i etasjen heisen er i
 @return 0 hvis ikke
*/
int orders_downAtFloor(posisjon pos);


#endif
