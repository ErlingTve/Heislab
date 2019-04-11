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
    printf("Press CTRL + C to exit program.\n");
	//While loop to always run the finite state machine.
    while (1) {
    	fsm_state_switch();
 	}
    return 0;
}
