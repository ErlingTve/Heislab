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
	for (int i = 0; i < N_BUTTONS; ++i){
		if (order_matrix[CurrentFloor][i]) {
			elev_set_motor_direction(0);
			//CurrentState = Not_moving_at_floor;
			return 0;
		}
	}
	//Legg inn logikk for når den skal kjøre opp og ned
	//returner 1
}