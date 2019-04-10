#ifndef ORDERS_H
#define ORDERS_H
#include "channels.h"
/**
	@file
	@brief File to manage orders.
*/

/**
    @brief Enum for the elevators current position, 0-3 are floors, 4-6 are between floors.
 */
typedef enum {FØRSTE = 0, ANDRE = 1, TREDJE = 2, FJERDE = 3, MELLOM_FØRSTE_OG_ANDRE = 4, MELLOM_ANDRE_OG_TREDJE = 5,  MELLOM_TREDJE_OG_FJERDE = 6} posisjon;

/**
    @brief Local variable containing the elevators position.
 */
static posisjon Posisjon = 0;

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
int orders_command_at_floor(posisjon pos);

/**
 @brief Checks if there are any orders, in order matrix, above the current floor.
 @return 1 if there are any orders above the current floor.
 @return 0 if no orders above the current floor.
 */
int orders_up_at_floor(posisjon pos);

/**
 @brief Checks if there are any orders, in order matrix, below the current floor.
 @return 1 if there are any orders below the current floor.
 @return 0 if no orders below the current floor.
 */
int orders_down_at_floor(posisjon pos);

/**
 @brief Checks current postiton.
 @return Variable of type position.
*/
posisjon orders_get_posisjon(void);
/**
 @brief Changes the current postion.
 @param pos of type postion.
*/
void orders_set_posisjon(posisjon pos);

#endif
