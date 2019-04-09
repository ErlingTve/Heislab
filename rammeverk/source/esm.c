#include "elev.h"
#include "orders.h"
#include "esm.h"
#include "timer.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


//Endrer posisjon til noe mellom etasjer
//Kalles kun når man går inn i MOVING og posisjonen er satt til "i etasje" fra før
void esm_changePositionBetweenFloors() {
    switch (MotorDirection) {
        case DIRN_DOWN:
        	orders_setPosisjon(orders_getPosisjon()+3);
            //Posisjon += 3;
            break;
        
        case DIRN_UP:
        	orders_setPosisjon(orders_getPosisjon()+4);
            //Posisjon += 4;
            break;
        default: 
            printf("MotorDirection er satt til DIRN_STOP selv om du vil endre posisjon til noe mellom etasjer.");
            break;
    }
}

//Returnerer 1 om heisen skal stoppe, 0 hvis ikke
int esm_stopAtFloor() {
    if ((orders_commandAtFloor(orders_getPosisjon())) || (orders_upAtFloor(orders_getPosisjon()) && MotorDirection == DIRN_UP) || (orders_downAtFloor(orders_getPosisjon()) && MotorDirection == DIRN_DOWN)) {
        return 1;
    }
    if((orders_orderBelowPosition() == 0) && MotorDirection == DIRN_DOWN){

    }
    if((orders_orderAbovePosition() == 0) && MotorDirection == DIRN_UP){
    	return 1;
    }
    return 0;
}

// HUSK Å ENDRE MED ORDERSBELOWPOSITION OG ORDERSABOVEPOSISTION
void esm_setPriorityDirection(){
	//sjekker om bestillinger i retning motorretning, hvis det er det; behold mottorretning, hvis ikke, bytt motorretning
	if(LastMovingDirection==DIRN_UP){
		if(orders_orderAbovePosition()){
			elev_set_motor_direction(DIRN_UP);
			return;
		}
		elev_set_motor_direction(DIRN_DOWN);
		return;
	}
	//Hvis LastMovingDirection == DIRN_DOWN
	if(orders_orderBelowPosition()){
		elev_set_motor_direction(DIRN_DOWN);
		return;
	}
	elev_set_motor_direction(DIRN_UP);
	return;
}


void esm_stateSwitch(){
	printf("CurrentState: ");
	printf("%d", CurrentState);
	printf("\n");
	switch (CurrentState){	
		
        case WAITING_FOR_INIT:
        	while(!orders_existOrders()){
        		if(elev_get_stop_signal()){
        			CurrentState=EMERGENCY_STOP;
        			return;
        		}
        	orders_updateOrderMatrix();
        	}
        	if(orders_orderAbovePosition()){
        		CurrentState=MOVING;
        		return;
        	}
			CurrentState=NOT_MOVING_AT_FLOOR;
			return;

		case NOT_MOVING_AT_FLOOR:
			elev_set_motor_direction(DIRN_STOP);
			orders_deleteOrdersAtThisFloor(elev_get_floor_sensor_signal());
			elev_set_door_open_lamp(1);
			// lag funksjon for å sette timestamp
			timer_startTimer();
			while(timer_timerExpired() == 0){
				if(elev_get_stop_signal()){
					CurrentState=EMERGENCY_STOP;
					return;
				}
				orders_updateOrderMatrix();
			}
			//Timerfunksjon inn her
			//husk å resette timer
			elev_set_door_open_lamp(0); //DETTE VIL VEL GJØRE AT DØREN LUKKER SEG OGSÅ VED TRYKKET STOPPKNAPP kan fikses vha egen EMERGENCY_STOP-modul
			while(orders_existOrders() == 0){
				orders_updateOrderMatrix();
				if (elev_get_stop_signal()){
					CurrentState=EMERGENCY_STOP;
					return;
				}
			}
			//Heisen går inn i samme tilstand på nytt om det er ny bestilling i samme etasje
            if (orders_orderAtThisFloor(orders_getPosisjon())){
				CurrentState = NOT_MOVING_AT_FLOOR;
				return;
			}
			 	CurrentState = MOVING;
			return;
		
        case MOVING:
        	esm_setPriorityDirection();
            if (orders_getPosisjon() < 4) {
                esm_changePositionBetweenFloors();
            }
			while(elev_get_floor_sensor_signal() == -1) {
				//printf("Movingstate");
				orders_updateOrderMatrix();
				if(elev_get_stop_signal()){
	                CurrentState = EMERGENCY_STOP;
	                return;
				}
			}
			CurrentState=AT_FLOOR;
			return;

        case AT_FLOOR:
            orders_setPosisjon(elev_get_floor_sensor_signal()); //test at ikke oppstår problem når den returnerer -1 fordi heisen er mellom etasjer
			elev_set_floor_indicator(orders_getPosisjon());

			if (esm_stopAtFloor()){ 
				CurrentState = NOT_MOVING_AT_FLOOR;
				return;
			}
			while(elev_get_floor_sensor_signal() != -1){
				if (elev_get_stop_signal()){
					CurrentState = EMERGENCY_STOP;
					return;
				}
				orders_updateOrderMatrix();
			}
			CurrentState = MOVING;
			return;

		case EMERGENCY_STOP:
			elev_set_stop_lamp(1);
			elev_set_motor_direction(DIRN_STOP);
			orders_deleteAllOrders();
			if (orders_getPosisjon()<4){
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
			while((orders_existOrders() == 0) && (elev_get_stop_signal() == 0)){
				orders_updateOrderMatrix();
			}
			CurrentState = MOVING;
			return;	
	}
}

