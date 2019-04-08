#include "channels.h"
#include "elev.h"
#include "io.h"
#include "orders.h"
#include "esm.h"

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

void orders_deleteOrdersAtThisFloor(int floor) {
	for (int i = 0; i < N_BUTTONS; ++i){
		order_matrix[floor][i] = 0;
	}
}

void orders_deleteAllOrders() {
	for (int i = 0; i < N_FLOORS; ++i){
		for (int j = 0; j < N_BUTTONS; ++j){
			order_matrix[i][j] = 0;
		}
	}
}
