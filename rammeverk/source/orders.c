#include "orders.h"
#include "elev.h"
#include "io.h"




void orders_updateOrderMatrix(){
	for (int i=0; i<N_FLOORS; i++){
		for (int j=0; j<N_BUTTONS;j++){ 
			if(elev_get_button_signal(i,j))
				order_matrix[i][j] = 1;
		}
	}
}

//Returnerer -1 hvis ingen bestillinger, 0 hvis bestilling i samme 
//etasje og 1 hvis det er i en annen etasje
int orders_setPriorityDirection() {
	//Stoppknappfunksjon
	int CurrentFloor = elev_get_floor_sensor_signal();
	int NumberOfOrders = 0;
	for (int i = 0; i < N_FLOORS; ++i){
		for (int j = 0; j < N_BUTTONS; ++j){
			NumberOfOrders += order_matrix[i][j];
		}
	}
	if (!NumberOfOrders){
		elev_set_motor_direction(0); //Denne trengs nok egentlig ikke
		return -1;
	}
	
	if (orders_orderAtThisFloor){
		elev_set_motor_direction(DIRN_STOP);
		return 0;
	}

	//Legg inn logikk for når den skal kjøre opp og ned
	//returner 1
}

int orders_orderAtThisFloor(int floor) {
	for (int i = 0; i < N_BUTTONS; ++i){
		if (order_matrix[floor][i]) {
			return 1;
		}
	return 0;
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

float orders_savePositionBetweenFloors(void) {
	switch (MotorDirection) {
		case DIRN_DOWN :
			return FloorIndicator - 0.5;
			break;
		case DIRN_UP ;
			return FloorIndicator + 0.5;
			break;
	}
}

void orders_setDirectionBetweenFloors(float position) {
	int OrderFloor;
	for (int i = 0; i < N_FLOORS; ++i){
		for (int j = 0; j < N_BUTTONS; ++j){
			if (order_matrix[i][j]){
				OrderFloor = i;
				if ((OrderFloor - position)>0){
					elev_set_motor_direction(DIRN_UP);
				}else
					elev_set_motor_direction(DIRN_DOWN);
				return;
			}
		}
	}
}