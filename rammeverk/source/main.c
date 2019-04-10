#include "elev.h"
#include "fsm.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    //elev_set_motor_direction(DIRN_UP);

    while (1) {
    	fsm_state_switch();
 	   }

    return 0;
}
