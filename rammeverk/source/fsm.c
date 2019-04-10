#include "elev.h"
#include "orders.h"
#include "fsm.h"
#include "timer.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


//Endrer posisjon til noe mellom etasjer
//Kalles kun når man går inn i MOVING og posisjonen er satt til "i etasje" fra før
void fsm_change_position_between_floors() {
    switch (elev_get_motor_direction()) {
        case DIRN_DOWN:
        	orders_set_posisjon(orders_get_posisjon()+3);
            //Posisjon += 3;
            break;

        case DIRN_UP:
        	orders_set_posisjon(orders_get_posisjon()+4);
            //Posisjon += 4;
            break;
        default:
            printf("MotorDirection er satt til DIRN_STOP selv om du vil endre posisjon til noe mellom etasjer.");
            break;
    }
}

//Returnerer 1 om heisen skal stoppe, 0 hvis ikke
int fsm_stop_at_floor() {
    if ((orders_command_at_floor(orders_get_posisjon())) || (orders_up_at_floor(orders_get_posisjon()) && elev_get_motor_direction() == DIRN_UP) || (orders_down_at_floor(orders_get_posisjon()) && elev_get_motor_direction() == DIRN_DOWN)) {
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

void fsm_set_priority_direction(){
	//Sjekker at heisen nå står stille. Sikrer at ikke heisen momentant skifter retning
	if (elev_get_motor_direction() != DIRN_STOP){
		return;
	}
	//sjekker om bestillinger i retning motorretning, hvis det er det; behold mottorretning, hvis ikke, bytt motorretning
	if(elev_get_last_moving_direction()==DIRN_UP){
		if(orders_order_above_position()){
			elev_set_motor_direction(DIRN_UP);
			return;
		}
		elev_set_motor_direction(DIRN_DOWN);
		return;
	}
	//Hvis elev_get_last_moving_direction() == DIRN_DOWN
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
			// lag funksjon for å sette timestamp
			timer_start_timer();
			while(timer_timer_expired(3.0) == 0){
				if(elev_get_stop_signal()){
					CurrentState=EMERGENCY_STOP;
					return;
				}
				orders_update_order_matrix();
				if (orders_order_at_this_floor(orders_get_posisjon())){
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
			//Heisen går inn i samme tilstand på nytt om det er ny bestilling i samme etasje
            if (orders_order_at_this_floor(orders_get_posisjon())){
				CurrentState = NOT_MOVING_AT_FLOOR;
				return;
			}
			 	CurrentState = MOVING;
			return;

        case MOVING:
        	fsm_set_priority_direction();
            if (orders_get_posisjon() < 4) {
                fsm_change_position_between_floors();
            }
       		while(elev_get_floor_sensor_signal() == -1) {
				//printf("Movingstate");
				orders_update_order_matrix();
				if(elev_get_stop_signal()){
	                CurrentState = EMERGENCY_STOP;
	                return;
				}
			}

			CurrentState=AT_FLOOR;
			return;

        case AT_FLOOR:
            orders_set_posisjon(elev_get_floor_sensor_signal()); //test at ikke oppstår problem når den returnerer -1 fordi heisen er mellom etasjer
			elev_set_floor_indicator(orders_get_posisjon());

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
			if (orders_get_posisjon()<4){
				//i etasje
				elev_set_door_open_lamp(1);
				while(elev_get_stop_signal()){
					//ingenting
				}
				CurrentState=NOT_MOVING_AT_FLOOR;
				elev_set_stop_lamp(0);
				return;
			}
				while(elev_get_stop_signal()){
					//ingenting
				}
			CurrentState=NOT_MOVING_BETWEEN_FLOORS;
			elev_set_stop_lamp(0);
			return;

		//hvis endring i planene
		case NOT_MOVING_BETWEEN_FLOORS:
			while((orders_exist_orders() == 0) && (elev_get_stop_signal() == 0)){
				orders_update_order_matrix();
			}
			CurrentState = MOVING;
			return;
	}
}
