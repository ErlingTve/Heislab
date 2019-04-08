#include "channels.h"
#include "elev.h"
#include "io.h"
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

//Returnerer 1 om heisen skal stoppe, 0 hvis ikke
int esm_stopAtFloor() {
    if ((orders_commandAtFloor(Posisjon)) || (orders_upAtFloor(Posisjon) && MotorDirection == DIRN_UP) || (orders_downAtFloor(Posisjon) && MotorDirection == DIRN_DOWN)) {
        return 1;
    }return 0;
}

void esm_setPriorityDirection(){
	//sjekker om bestillinger i retning motorretning, hvis det er det; behold mottorretning, hvis ikke, bytt motorretning
	if(LastMovingDirection==DIRN_UP){
		for (int i = Posisjon+1; i < N_FLOORS; ++i){
			if(orders_orderAtThisFloor(i)){
				elev_set_motor_direction(DIRN_UP);
				return;
			}
		}
	}
	if(LastMovingDirection==DIRN_DOWN){
		for (int i = 0; i < Posisjon; ++i){
			if(orders_orderAtThisFloor(i)){
				elev_set_motor_direction(DIRN_DOWN);
				return;
			}
		}
	}
}


void esm_stateSwitch(){
	switch (CurrentState){
		
        case WAITING_FOR_INIT:
			CurrentState=NOT_MOVING_AT_FLOOR;
		case NOT_MOVING_AT_FLOOR:
			elev_set_motor_direction(DIRN_STOP);
			orders_deleteOrdersAtThisFloor(elev_get_floor_sensor_signal());
			elev_set_door_open_lamp(1);
			// lag funksjon for å sette timestamp
			timer_startTimer();
			while(!timer_timerExpired()){
				if(elev_get_stop_signal()){
					CurrentState=EMERGENCY_STOP;
					break;
				}
				orders_updateOrderMatrix();
			}
			//Timerfunksjon inn her
			//husk å resette timer
			elev_set_door_open_lamp(0); //DETTE VIL VEL GJØRE AT DØREN LUKKER SEG OGSÅ VED TRYKKET STOPPKNAPP kan fikses vha egen EMERGENCY_STOP-modul
			while(!orders_existOrders()){
				orders_updateOrderMatrix();
				if (elev_get_stop_signal()){
					CurrentState=EMERGENCY_STOP;
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
        	esm_setPriorityDirection();
            if (Posisjon < 4) {
                esm_changePositionBetweenFloors();
            }
			while(elev_get_floor_sensor_signal() == -1) {
				orders_updateOrderMatrix();
				if(elev_get_stop_signal()){
	                CurrentState = EMERGENCY_STOP;
	                break;
				}
			}
            CurrentState=AT_FLOOR;
		
        case AT_FLOOR:
            Posisjon = elev_get_floor_sensor_signal(); //test at ikke oppstår problem når den returnerer -1 fordi heisen er mellom etasjer
			elev_set_floor_indicator(Posisjon);
			if (elev_get_stop_signal()){
				CurrentState = EMERGENCY_STOP;
				break;
			}
			orders_updateOrderMatrix();
			if (esm_stopAtFloor()){ 
				CurrentState = NOT_MOVING_AT_FLOOR;
				break;
			}
			CurrentState = MOVING;
			break;
		case EMERGENCY_STOP:
			elev_set_motor_direction(DIRN_STOP);
			orders_deleteAllOrders();
			if (Posisjon<4){
				//i etasje
				elev_set_door_open_lamp(1);
				while(elev_get_stop_signal()){
					//ingenting
				}
				CurrentState=NOT_MOVING_AT_FLOOR;
				break;
			}
			CurrentState=NOT_MOVING_BETWEEN_FLOORS;
			break;
		//hvis endring i planene
		case NOT_MOVING_BETWEEN_FLOORS:
			while(!orders_existOrders() && (!elev_get_stop_signal())){
				orders_updateOrderMatrix();
				}
			//LAG FUNKSJON FOR Å VELGE RETNING OG SETTE MOTOR DIRECTION
			CurrentState = MOVING;
			break;	
	}
}

