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
void orders_updateOrderMatrix();

/**
 @brief Setter motorretning til den prioriterte retningen og returnerer om det er bestillinger.
@return -1 hvis ingen bestillinger, 0 hvis bestilling i samme etasje og 1 hvis det er i en annen etasje
*/
int orders_setPriorityDirectionAndReturnIfOrders();

/**
 @brief Returnerer om det er bestillinger i valgt etasje
 @param floor Etasjenummer
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
void orders_deleteAllOrders();

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
