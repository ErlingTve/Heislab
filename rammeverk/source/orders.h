#ifndef ORDERS_H
#define ORDERS_H
#include "channels.h"
/**
	@file
	@brief File to manage orders
*/

//Matrise med bestillingene til heisen
static int order_matrix[N_FLOORS][N_BUTTONS];

//iterere gjennom alle knappene for å se om de er trykket inn og oppdaterer bestillingsmatrisen
void orders_updateOrderMatrix();

//Setter motorretning til den prioriterte retningen
//Returnerer -1 hvis ingen bestillinger, 0 hvis bestilling i samme 
//etasje og 1 hvis det er i en annen etasje
int orders_setPriorityDirectionAndReturnIfOrders();

//Returnerer 1 hvis det er bestillinger til valgt etasje
//0 hvis ikke
int orders_orderAtThisFloor(int floor);

void orders_deleteOrdersAtThisFloor(int floor);

void orders_deleteAllOrders();

//Kanskje i egen modul??
float orders_savePositionBetweenFloors(void);

void orders_setDirectionBetweenFloors(float position);

#endif