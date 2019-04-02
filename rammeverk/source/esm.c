#include "channels.h"
#include "elev.h"
#include "io.h"
#include "orders.h"
#include "esm.h"

#include <assert.h>
#include <stdlib.h>



void esm_stateSwitch(state CurrentState){
	switch (CurrentState){
		case Waiting_for_init:
			CurrentState=Not_moving_at_floor;			
		case Not_moving_at_floor:
			elev_set_motor_direction(DIRN_STOP);
			orders_deleteOrdersAtThisFloor(elev_get_floor_sensor_signal);
			elev_set_door_open_lamp(1);
			//Timerfunksjon inn her
			//husk å resette timer
			elev_set_door_open_lamp(0);
			orders_updateOrderMatrix(); //tar bestilling
			//får heisen til å bevege seg mot prioritert bestilling
			while(orders_setPriorityDirection() == -1){
				orders_updateOrderMatrix();
				if (elev_get_stop_signal()){
					orders_deleteAllOrders();
					//RESET TIMER!!!!
					break;
				}
			}
			if (!orders_setPriorityDirection()){
				CurrentState = Not_moving_at_floor;
				break;
			} 
			CurrentState = Moving;
		case Moving:
			while(elev_get_floor_sensor_signal() == -1) {
				orders_updateOrderMatrix();
			if(elev_get_stop_signal()){
					CurrentState = Not_moving_between_floors;
					break;
				}
			}
			CurrentState=At_floor;
		case At_floor:
			int CurrentFloor=elev_get_floor_sensor_signal();
			if (elev_get_stop_signal()){
				orders_deleteAllOrders();
				CurrentState = Not_moving_at_floor;
				break;
			}
			orders_updateOrderMatrix();
			elev_set_floor_indicator(CurrentFloor);
			if (orders_orderAtThisFloor(CurrentFloor)){
				CurrentState = Not_moving_at_floor;
				break;
			}
			CurrentState = Moving;
			break;			

		//hvis endring i planene
		case Not_moving_between_floors:
			float position = orders_savePositionBetweenFloors();
			elev_set_motor_direction(DIRN_STOP);
			orders_deleteAllOrders();
			while((orders_setPriorityDirection() == -1) && (!elev_get_stop_signal)){
				orders_updateOrderMatrix();
				}
			orders_setDirectionBetweenFloors(position);
			CurrentState = Moving;
			break;	
	}
}
