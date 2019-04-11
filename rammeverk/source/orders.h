#ifndef ORDERS_H
#define ORDERS_H
/**
	@file
	@brief File to manage orders.
*/

/**
    @brief Enum for the elevators current position, 0-3 are floors, 4-6 are between floors.
 */
typedef enum {FIRST = 0, SECOND = 1, THIRD = 2, FOURTH = 3, BETWEEN_FIRST_AND_SECOND = 4, BETWEEN_SECOND_AND_THIRD = 5,  BETWEEN_THIRD_AND_FOURTH = 6} position;

/**
    @brief Local variable containing the elevators position.
 */
static position Position = 0;

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
    @return 1 if there are any orders in order matrix
    @return 0 if order matrix is empty.
 */
int orders_exist_orders(void);


/**
    @brief Checks if there are any orders, in order matrix, below the elevators current position.
    @return 1 if there are any orders below the current position.
    @return 0 if no orders below.
*/
int orders_order_below_position(void);

/**
    @brief Checks if there are any orders, in order matrix, above the elevators current position.
    @return 1 if there are any orders above the current position.
    @return 0 if no orders above.
*/
int orders_order_above_position(void);

/**
    @brief Checks if there are any orders on the current floor
    @param floor Current floor.
    @return 1 if there is an order on the current floor.
    @return 0 if no orders on the current floor.
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
 @brief Checks if there are any orders in order matrix on the current floor.
 @return 1 if there are any orders on the current floor.
 @return 0 if no orders on the current floor.
 */
int orders_command_at_floor(position pos);

/**
 @brief Checks if there are any orders, in order matrix, above the current floor.
 @return 1 if there are any orders above the current floor.
 @return 0 if no orders above the current floor.
 */
int orders_button_up_at_floor(position pos);

/**
 @brief Checks if there are any orders, in order matrix, below the current floor.
 @return 1 if there are any orders below the current floor.
 @return 0 if no orders below the current floor.
 */
int orders_button_down_at_floor(position pos);

/**
 @brief Checks current postiton.
 @return Variable of type position.
*/
position orders_get_position(void);
/**
 @brief Changes the current postion.
 @param pos of type postion.
*/
void orders_set_position(position pos);

#endif
