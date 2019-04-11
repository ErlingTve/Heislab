#include "elev.h"
#include "orders.h"


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void orders_update_order_matrix(){
	for (int floor=0; floor<N_FLOORS; floor++){
		for (int button=0; button<N_BUTTONS; button++){
            if (((floor != FIRST) && (button == BUTTON_CALL_DOWN)) ||
            	((floor != FOURTH) && (button == BUTTON_CALL_UP)) ||
            	button == BUTTON_COMMAND)
            {
                if(elev_get_button_signal(button,floor)){
                order_matrix[floor][button] = 1;
                elev_set_button_lamp(button, floor, 1);
                }
            }
		}
	}
}

int orders_exist_orders() {
    int order = 0;
    for (int floor = 0; floor < N_FLOORS; floor++) {
        order += orders_order_at_this_floor(floor);
    }
    if (order) {
        return 1;
    }return 0;
}

int orders_order_below_position(){
	int pos = orders_get_position();
	if(pos > 3){
		pos -= 3;
	}
	for (int i = 0; i < pos; ++i){
		if(orders_order_at_this_floor(i)){
			return 1;
		}
	}
	return 0;
}

int orders_order_above_position(){
	int pos =orders_get_position();
	if (pos > 3){
		pos -= 4;
	}
	for (int i = pos+1; i < N_FLOORS; ++i){
		if(orders_order_at_this_floor(i)){
			return 1;
		}
	}
	return 0;
}

int orders_order_at_this_floor(int floor) {
	for (int i = 0; i < N_BUTTONS; ++i){
		if (order_matrix[floor][i]) {
			return 1;
		}
	}return 0;
}

void orders_delete_orders_at_this_floor(int floor) {
	for (int button = 0; button < N_BUTTONS; ++button){
		order_matrix[floor][button] = 0;
		if (((floor != FIRST) && (button == BUTTON_CALL_DOWN)) ||
			((floor != FOURTH) && (button == BUTTON_CALL_UP)) ||
			button == BUTTON_COMMAND)
		{
			elev_set_button_lamp(button, floor, 0);
		}
	}
}

void orders_delete_all_orders() {
	for (int floor = 0; floor < N_FLOORS; ++floor){
		for (int button = 0; button < N_BUTTONS; ++button){
			order_matrix[floor][button] = 0;
			if (((floor != FIRST) && (button == BUTTON_CALL_DOWN)) ||
				((floor != FOURTH) && (button == BUTTON_CALL_UP)) ||
				button == BUTTON_COMMAND)
			{
				elev_set_button_lamp(button, floor, 0);
			}
		}
	}
}

int orders_command_at_floor(position pos) {
    if (pos > 3) {
        printf("order_commandAtFloor er kalt mens Position ikke er i en etasje");
        return -1;
    }return order_matrix[pos][BUTTON_COMMAND];
}

int orders_button_up_at_floor(position pos) {
    if (pos > 3) {
        printf("order_upAtFloor er kalt mens Position ikke er i en etasje");
        return -1;
    }return order_matrix[Position][BUTTON_CALL_UP];
}

int orders_button_down_at_floor(position pos) {
    if (pos > 3) {
        printf("order_downAtFloor er kalt mens Position ikke er i en etasje");
        return -1;
    }return order_matrix[pos][BUTTON_CALL_DOWN];
}

position orders_get_position(void){
	return Position;
}

void orders_set_position(position pos){
	Position=pos;
	printf("Position: ");
	printf("%d", pos);
	printf("\n" );
}
