#include "channels.h"
#include "elev.h"
#include "io.h"
#include "orders.h"
#include "esm.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//Endrer posisjon til noe mellom etasjer
//Kalles kun når man går inn i MOVING og posisjonen er satt til "i etasje fra før"
void esm_changePositionBetweenFloors() {
    switch (MotorDirection) {
        case DIRN_DOWN:
            Posisjon += 3;
            break;
        
        case DIRN_UP:
            Posisjon += 4;
            break;
        default:
            printf("MotorDirection er satt til DIRN_STOP selv om du vil endre posisjon til noe mellom etasjer.");
            break;
    }
}

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
			elev_set_door_open_lamp(0); //DETTE VIL VEL GJØRE AT DØREN LUKKER SEG OGSÅ VED TRYKKET STOPPKNAPP
			orders_updateOrderMatrix(); //tar bestilling
			//får heisen til å bevege seg mot prioritert bestilling
			while(!orders_existOrders()){
				orders_updateOrderMatrix();
				if (elev_get_stop_signal()){
					orders_deleteAllOrders();
					//RESET TIMER!!!!
					break;
				}
			}
			//Heisen går inn i samme tilstand på nytt om det er ny bestilling i samme etasje
            if (orders_orderAtThisFloor(Posisjon)){
				CurrentState = NOT_MOVING_AT_FLOOR;
				break;
			} 
			CurrentState = MOVING;
		
        case MOVING:
            if (Posisjon < 4) {
                esm_changePositionBetweenFloors();
            }
			while(elev_get_floor_sensor_signal() == -1) {
				orders_updateOrderMatrix();
			if(elev_get_stop_signal()){
                CurrentState = NOT_MOVING_BETWEEN_FLOORS;
                break;
				}
			}
            CurrentState=AT_FLOOR;
		
        case AT_FLOOR:
			//int CurrentFloor = elev_get_floor_sensor_signal();
            Posisjon = elev_get_floor_sensor_signal();
			if (elev_get_stop_signal()){
				orders_deleteAllOrders();
				CurrentState = NOT_MOVING_AT_FLOOR;
				break;
			}
			orders_updateOrderMatrix();
			elev_set_floor_indicator(Posisjon);
			if (orders_orderAtThisFloor(Posisjon)){
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
			while((orders_setPriorityDirectionAndReturnIfOrders() == -1) && (!elev_get_stop_signal())){
				orders_updateOrderMatrix();
				}
			orders_setDirectionBetweenFloors(position);
			CurrentState = MOVING;
			break;	
	}
}

