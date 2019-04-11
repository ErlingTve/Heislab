#ifndef ORDERS_H
#define ORDERS_H
/**
	@file
	@brief File to manage orders.
*/

/**
    @brief Enum for the elevators current position, 0-3 are floors, 4-6 are between floors.
 */
typedef enum {
	FIRST = 0,
	SECOND = 1,
	THIRD = 2,
	FOURTH = 3,
	BETWEEN_FIRST_AND_SECOND = 4,
	BETWEEN_SECOND_AND_THIRD = 5,
	BETWEEN_THIRD_AND_FOURTH = 6
	} position;

/**
    @brief Local variable containing the elevators position.
 */
static position Position = FIRST;

/**
    @brief Array containing the elevators current orders.
*/
static int order_matrix[N_FLOORS][N_BUTTONS];

/**
    @brief Iterate through all the buttons to check if they are pressed, if a button is pressed, this function updates the order matrix.
*/
void orders_update_order_matrix(void);

/**
    @brief Tells if there is any current orders in order matrix.
    @return 1 If there are any orders in order matrix.
    @return 0 If order matrix is empty.
 */
int orders_exist_orders(void);


/**
    @brief Checks if there are any orders, in order matrix, below the elevators current position.
    @return 1 If there are any orders below the current position.
    @return 0 If no orders below.
*/
int orders_order_below_position(void);

/**
    @brief Checks if there are any orders, in order matrix, above the elevators current position.
    @return 1 If there are any orders above the current position.
    @return 0 If no orders above.
*/
int orders_order_above_position(void);

/**
    @brief Checks if there are any orders on the current floor.
    @param floor Current floor.
    @return 1 If there is an order on the current floor.
    @return 0 If no orders on the current floor.
*/
int orders_order_at_this_floor(int floor);

/**
 @brief Deletes orders in order matrix on the current floor.
 @param floor Current floor.
 */
void orders_delete_orders_at_this_floor(int floor);

/**
 @brief Deletes all orders in order matrix.
 */
void orders_delete_all_orders(void);

/**
 @brief Checks if there are any commands in order matrix on the floor "pos".
 @param pos The floor you want to check at.
 @return 1 If there are any commands on the current floor.
 @return 0 If no commands on the current floor.
 */
int orders_command_at_floor(position pos);

/**
 @brief Checks if there are any up-orders, in order matrix, on the floor "pos".
 @param pos The floor you want to check at.
 @return 1 If there are any up-orders on the current floor.
 @return 0 If no up-orders on the current floor.
 */
int orders_button_up_at_floor(position pos);

/**
 @brief Checks if there are any down-orders, in order matrix, on the floor "pos".
 @param pos The floor you want to check at.
 @return 1 If there are any down-orders on the current floor.
 @return 0 If no down-orders on the current floor.
 */
int orders_button_down_at_floor(position pos);

/**
 @brief Checks current postiton.
 @return The position variable; Position.
*/
position orders_get_position(void);
/**
 @brief Changes the current postion.
 @param pos The position you want Position to be.
*/
void orders_set_position(position pos);

#endif
