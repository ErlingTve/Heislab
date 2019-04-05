#include "channels.h"
#include "elev.h"
#include "io.h"
#include "orders.h"
#include "esm.h"

#include <assert.h>
#include <stdlib.h>



void esm_stateSwitch(state CurrentState){
	switch (CurrentState){
		case WAITING_FOR_INIT:
			CurrentState=NOT_MOVING_AT_FLOOR;
		case NOT_MOVING_AT_FLOOR:
			elev_set_motor_direction(DIRN_STOP);
			orders_deleteOrdersAtThisFloor(elev_get_floor_sensor_signal());
			elev_set_door_open_lamp(1);
			//Timerfunksjon inn her
			//husk å resette timer
			elev_set_door_open_lamp(0);
			orders_updateOrderMatrix(); //tar bestilling
			//får heisen til å bevege seg mot prioritert bestilling
			while(orders_setPriorityDirectionAndReturnIfOrders() == -1){
				orders_updateOrderMatrix();
				if (elev_get_stop_signal()){
					orders_deleteAllOrders();
					//RESET TIMER!!!!
					break;
				}
			}
			if (!orders_setPriorityDirectionAndReturnIfOrders()){
				CurrentState = NOT_MOVING_AT_FLOOR;
				break;
			} 
			CurrentState = MOVING;
		case MOVING:
			while(elev_get_floor_sensor_signal() == -1) {
				orders_updateOrderMatrix();
			if(elev_get_stop_signal()){
					CurrentState = NOT_MOVING_BETWEEN_FLOORS;
					break;
				}
			}

			CurrentState=AT_FLOOR;
		case AT_FLOOR:
			int CurrentFloor = elev_get_floor_sensor_signal();
			if (elev_get_stop_signal()){
				orders_deleteAllOrders();
				CurrentState = NOT_MOVING_AT_FLOOR;
				break;
			}
			orders_updateOrderMatrix();
			elev_set_floor_indicator(CurrentFloor);
			if (orders_orderAtThisFloor(CurrentFloor)){
				CurrentState = NOT_MOVING_AT_FLOOR;
				break;
			}
			CurrentState = MOVING;
			break;			

		//hvis endring i planene
		case NOT_MOVING_BETWEEN_FLOORS:
			float position = orders_savePositionBetweenFloors();
			elev_set_motor_direction(DIRN_STOP);
			orders_deleteAllOrders();
			while((orders_setPriorityDirectionAndReturnIfOrders() == -1) && (!elev_get_stop_signal)){
				orders_updateOrderMatrix();
				}
			orders_setDirectionBetweenFloors(position);
			CurrentState = MOVING;
			break;	
	}
}
