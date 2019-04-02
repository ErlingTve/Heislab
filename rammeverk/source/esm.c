#include "esm.h"
#include "elev.h"
#include <stdlib.h>




void esm_stateSwitch(state CurrentState){
	switch (CurrentState){
		case Waiting_for_init:
			CurrentState=Not_moving_at_floor;			
		case Not_moving_at_floor:
			elev_set_motor_direction(DIRN_STOP);
			elev_set_door_open_lamp(1);
			//Timerfunksjon inn her
			//husk å resette timer
			elev_set_door_open_lamp(0);
			orders_updateOrderMatrix(); //tar bestilling
			//får heisen til å bevege seg mot prioritert bestilling
			while(orders_setPriorityDirection() == -1){
				orders_updateOrderMatrix();
				}
			if (!orders_setPriorityDirection()){
				CurrentState = Not_moving_at_floor;
				break;
			} 
			CurrentState = Moving;
		case Moving:

		case At_floor:
		case Not_moving_between_floors:

	}

}
