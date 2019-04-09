#include "elev.h"
#include "orders.h"


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


int orders_commandAtFloor(posisjon pos) {
    if (pos > 3) {
        printf("order_commandAtFloor er kalt mens Posisjon ikke er i en etasje");
        return -1;
    }return order_matrix[pos][BUTTON_COMMAND];
}

int orders_upAtFloor(posisjon pos) {
    if (pos > 3) {
        printf("order_upAtFloor er kalt mens Posisjon ikke er i en etasje");
        return -1;
    }return order_matrix[Posisjon][BUTTON_CALL_UP];
}

//Returnerer om det er noen som har trykket 'ned' i etasjen heisen er i
int orders_downAtFloor(posisjon pos) {
    if (pos > 3) {
        printf("order_downAtFloor er kalt mens Posisjon ikke er i en etasje");
        return -1;
    }return order_matrix[pos][BUTTON_CALL_DOWN];
}

void orders_updateOrderMatrix(){
	for (int floor=0; floor<N_FLOORS; floor++){
		for (int button=0; button<N_BUTTONS; button++){ 
            if (((floor != FØRSTE) && (button == BUTTON_CALL_DOWN)) || ((floor != FJERDE) && (button == BUTTON_CALL_UP)) || button == BUTTON_COMMAND) {
                if(elev_get_button_signal(button,floor)){
                order_matrix[floor][button] = 1;
                elev_set_button_lamp(button, floor, 1);
                }
            }	
		}
	}
}

int orders_existOrders() {
    int order = 0;
    for (int floor = 0; floor < N_FLOORS; floor++) {
        order += orders_orderAtThisFloor(floor);
    }
    if (order) {
        return 1;
    }return 0;
}

int orders_orderAtThisFloor(int floor) {
	for (int i = 0; i < N_BUTTONS; ++i){
		if (order_matrix[floor][i]) {
			return 1;
		}
	}return 0;
}

//Sjekker om det er noen bestillinger under den nåværende posisjonen, returnere 1 hvis det er bestilling under, 0 hvis det ikke er noen bestillinger under
int orders_orderBelowPosition(){
	int pos = orders_getPosisjon();
	if(pos > 3){
		pos -= 3;
	}
	for (int i = 0; i < pos; ++i){
		if(orders_orderAtThisFloor(i)){
			return 1;
		}
	}
	return 0;
}	

//Sjekker om det er noen bestillinger over den nåværende posisjonen, returnere 1 hvis det er bestilling over, 0 hvis det ikke er noen bestillinger over
int orders_orderAbovePosition(){
	int pos =orders_getPosisjon();
	if (pos > 3){
		pos -= 4;
	}
	for (int i = pos+1; i < N_FLOORS; ++i){
		if(orders_orderAtThisFloor(i)){
			return 1;
		}
	}
	return 0;
}	



void orders_deleteOrdersAtThisFloor(int floor) {
	for (int button = 0; button < N_BUTTONS; ++button){
		order_matrix[floor][button] = 0;
		if (((floor != FØRSTE) && (button == BUTTON_CALL_DOWN)) || ((floor != FJERDE) && (button == BUTTON_CALL_UP)) || button == BUTTON_COMMAND) {
			elev_set_button_lamp(button, floor, 0);
		}
	}
}

void orders_deleteAllOrders() {
	for (int floor = 0; floor < N_FLOORS; ++floor){
		for (int button = 0; button < N_BUTTONS; ++button){
			order_matrix[floor][button] = 0;
			if (((floor != FØRSTE) && (button == BUTTON_CALL_DOWN)) || ((floor != FJERDE) && (button == BUTTON_CALL_UP)) || button == BUTTON_COMMAND) {
				elev_set_button_lamp(button, floor, 0);
			}
		}
	}
}

posisjon orders_getPosisjon(void){
	return Posisjon;
}

void orders_setPosisjon(posisjon pos){
	Posisjon=pos;
	printf("Posisjon: ");
	printf("%d", pos);
	printf("\n" );
}