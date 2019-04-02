#ifndef ORDERS_H
#define ORDERS_H

/**
	@file
	@brief File to manage orders
*/

//Matrise med bestillingene til heisen
static int order_matrix[N_FLOORS][N_BUTTONS];

//iterere gjennom alle knappene for å se om de er trykket inn og oppdaterer bestillingsmatrisen
void orders_updateOrderMatrix();

//Setter motorretning til den prioriterte retningen
void orders_setPriorityDirection();

#endif