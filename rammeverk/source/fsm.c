#include "elev.h"
#include "orders.h"
#include "fsm.h"
#include "timer.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
/**
	@file
	@brief C-file to make elevator state machine.
*/
/**
	@brief Sets Position from "on floor" to "between floors"
*/

void fsm_change_position_between_floors() {
    switch (elev_get_motor_direction()) {
        case DIRN_DOWN:
        	orders_set_position(orders_get_position()+3);
            break;

        case DIRN_UP:
        	orders_set_position(orders_get_position()+4);
            break;
        default:
            printf("MotorDirection er satt til DIRN_STOP selv om du vil endre position til noe mellom etasjer.");
            break;
    }
}
/**
	@brief Checks if elevator should stop at the current floor.
	@return 1 If elevator should stop.
	@return 0 If not.
*/
int fsm_stop_at_floor() {
    if ((orders_command_at_floor(orders_get_position())) ||
     (orders_button_up_at_floor(orders_get_position()) && elev_get_motor_direction() == DIRN_UP) ||
     (orders_button_down_at_floor(orders_get_position()) && elev_get_motor_direction() == DIRN_DOWN)) {
        return 1;
    }
    if((orders_order_below_position() == 0) && elev_get_motor_direction() == DIRN_DOWN){
        return 1;
    }
    if((orders_order_above_position() == 0) && elev_get_motor_direction() == DIRN_UP){
    	return 1;
    }
    return 0;
}
/**
	@brief Sets the most prioritized direction for the elevator. (UP/DOWN)
*/
void fsm_set_priority_direction(){
	//Checks that the elvator is still. Secures that it wont change direction momentarily.
	if (elev_get_motor_direction() != DIRN_STOP){
		return;
	}
	//Checks for orders in direction of the motor, if there is; keep MotorDirection, if not; switch MotorDirection.
	if(elev_get_last_moving_direction()==DIRN_UP){
		if(orders_order_above_position()){
			elev_set_motor_direction(DIRN_UP);
			return;
		}
		elev_set_motor_direction(DIRN_DOWN);
		return;
	}
	//If elev_get_last_moving_direction() == DIRN_DOWN
	if(orders_order_below_position()){
		elev_set_motor_direction(DIRN_DOWN);
		return;
	}
	elev_set_motor_direction(DIRN_UP);
	return;
}


void fsm_state_switch(){
	printf("CurrentState: ");
	printf("%d", CurrentState);
	printf("\n");
	switch (CurrentState){

        case WAITING_FOR_INIT:
        	while(!orders_exist_orders()){
        		if(elev_get_stop_signal()){
        			CurrentState=EMERGENCY_STOP;
        			return;
        		}
        	orders_update_order_matrix();
        	}
        	if(orders_order_above_position()){
        		CurrentState=MOVING;
        		return;
        	}
			CurrentState=NOT_MOVING_AT_FLOOR;
			return;

		case NOT_MOVING_AT_FLOOR:
			elev_set_motor_direction(DIRN_STOP);
			orders_delete_orders_at_this_floor(elev_get_floor_sensor_signal());
			elev_set_door_open_lamp(1);
			timer_start_timer();
			while(timer_timer_expired(3.0) == 0){
				if(elev_get_stop_signal()){
					CurrentState=EMERGENCY_STOP;
					return;
				}
				orders_update_order_matrix();
				if (orders_order_at_this_floor(orders_get_position())){
					return;
				}
			}
			elev_set_door_open_lamp(0);
			while(orders_exist_orders() == 0){
				orders_update_order_matrix();
				if (elev_get_stop_signal()){
					CurrentState=EMERGENCY_STOP;
					return;
				}
			}
			//FSM enters the same state "NOT_MOVING_AT_FLOOR" if there is a new order at the same floor
            if (orders_order_at_this_floor(orders_get_position())){
				CurrentState = NOT_MOVING_AT_FLOOR;
				return;
			}
			 	CurrentState = MOVING;
			return;

        case MOVING:
        	fsm_set_priority_direction();
            if (orders_get_position() < N_FLOORS) {
                fsm_change_position_between_floors();
            }
       		while(elev_get_floor_sensor_signal() == -1) {
				orders_update_order_matrix();
				if(elev_get_stop_signal()){
	                CurrentState = EMERGENCY_STOP;
	                return;
				}
			}

			CurrentState=AT_FLOOR;
			return;

        case AT_FLOOR:
            orders_set_position(elev_get_floor_sensor_signal());
			elev_set_floor_indicator(orders_get_position());

			if (fsm_stop_at_floor()){
				CurrentState = NOT_MOVING_AT_FLOOR;
				return;
			}
			while(elev_get_floor_sensor_signal() != -1){
				if (elev_get_stop_signal()){
					CurrentState = EMERGENCY_STOP;
					return;
				}
				orders_update_order_matrix();
			}
			CurrentState = MOVING;
			return;

		case EMERGENCY_STOP:
			elev_set_stop_lamp(1);
			elev_set_motor_direction(DIRN_STOP);
			orders_delete_all_orders();
			if (orders_get_position()<4){ //at floor
				elev_set_door_open_lamp(1);
				while(elev_get_stop_signal()){
					//do nothing
				}
				CurrentState=NOT_MOVING_AT_FLOOR;
				elev_set_stop_lamp(0);
				return;
			}
				while(elev_get_stop_signal()){
					//do nothing
				}
			CurrentState=NOT_MOVING_BETWEEN_FLOORS;
			elev_set_stop_lamp(0);
			return;

		case NOT_MOVING_BETWEEN_FLOORS:
			while((orders_exist_orders() == 0) && (elev_get_stop_signal() == 0)){
				orders_update_order_matrix();
			}
			CurrentState = MOVING;
			return;
	}
}
