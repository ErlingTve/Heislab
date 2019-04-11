//Wrapper for libComedi Elevator control.
/**
 @file
 @brief These functions provides an interface to the elevators in the real time lab
*/
// 2007, Martin Korsgaard
#ifndef __INCLUDE_DRIVER_H__
#define __INCLUDE_DRIVER_H__


// Number of floors
#define N_FLOORS 4
// Number of signals and lamps on a per-floor basis (excl sensor)
#define N_BUTTONS 3

/**
  @brief Initialize elevator to FIRST floor.
  @return Non-zero on success, 0 on failure.
*/
int elev_init(void);



/**
  @brief Motor direction for function elev_set_motor_direction().
*/
typedef enum tag_elev_motor_direction {
    DIRN_DOWN = -1,
    DIRN_STOP = 0,
    DIRN_UP = 1
} elev_motor_direction_t;

/**
 @brief Local variable for motor direction. Is set by elev_set_motor_direction().
 */
static elev_motor_direction_t MotorDirection;

/**
@brief Local variable for the last MOVING directon. Is set by elev_set_motor_direction().
*/
static elev_motor_direction_t LastMovingDirection;

/**
  @brief Sets the motor direction of the elevator and the local variables MotorDirection and LastMovingDirection.
  @param dirn New direction of the elevator.
*/
void elev_set_motor_direction(elev_motor_direction_t dirn);

/**
  @brief Gives the current moving direction.
  @return int Current moving direction
*/
int elev_get_motor_direction(void);
/**
  @brief Gives the last moving direction.
  @return int Last moving direction
*/
int elev_get_last_moving_direction(void);

/**
  @brief Turn door-open lamp on or off.
  @param value Non-zero value turns lamp on, 0 turns lamp off.
*/
void elev_set_door_open_lamp(int value);



/**
  @brief Get signal from obstruction switch.
  @return 1 if obstruction is enabled. 0 if not.
*/
int elev_get_obstruction_signal(void);



/**
  @brief Get signal from stop button.
  @return 1 if stop button is pushed, 0 if not.
*/
int elev_get_stop_signal(void);



/**
  @brief Turn stop lamp on or off.
  @param value Non-zero value turns lamp on, 0 turns lamp off.
*/
void elev_set_stop_lamp(int value);



/**
  @brief Get floor sensor signal.
  @return -1 if elevator is not on a floor. 0-3 if elevator is on floor. 0 is
    ground floor, 3 is top floor.
*/
int elev_get_floor_sensor_signal(void);

/**
  @brief Set floor indicator lamp for a given floor and the global variable FloorIndicator.
  @param floor Which floor lamp to turn on. Other floor lamps are turned off.
*/
void elev_set_floor_indicator(int floor);

/**
  @brief Button types for function elev_set_button_lamp() and elev_get_button().
*/
typedef enum tag_elev_lamp_type {
    BUTTON_CALL_UP = 0,
    BUTTON_CALL_DOWN = 1,
    BUTTON_COMMAND = 2
} elev_button_type_t;

/**
  @brief Gets a button signal.
  @param button Which button type to check. Can be BUTTON_CALL_UP,
    BUTTON_CALL_DOWN or BUTTON_COMMAND (button "inside the elevator).
  @param floor Which floor to check button. Must be 0-3.
  @return 0 if button is not pushed. 1 if button is pushed.
*/
int elev_get_button_signal(elev_button_type_t button, int floor);



/**
  @brief Set a button lamp.
  @param button Which type of lamp to set. Can be BUTTON_CALL_UP,
    BUTTON_CALL_DOWN or BUTTON_COMMAND (button "inside" the elevator).
  @param floor Floor of lamp to set. Must be 0-3
  @param value Non-zero value turns lamp on, 0 turns lamp off.
*/

void elev_set_button_lamp(elev_button_type_t button, int floor, int value);



#endif // #ifndef __INCLUDE_DRIVER_H__
