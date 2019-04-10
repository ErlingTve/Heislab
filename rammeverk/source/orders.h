#ifndef ORDERS_H
#define ORDERS_H
#include "channels.h"
/**
	@file
	@brief File to manage orders
*/

/**
 @brief Enum for hvilken posisjon heisen er i. 0-3 for etasje (for enkel bruk i andre funksjoner). 4-6 for mellom etasjene.
 */
typedef enum {FØRSTE = 0, ANDRE = 1, TREDJE = 2, FJERDE = 3, MELLOM_FØRSTE_OG_ANDRE = 4, MELLOM_ANDRE_OG_TREDJE = 5,  MELLOM_TREDJE_OG_FJERDE = 6} posisjon;

/**
 @brief Global variabel som sier hvilken posisjon heisen til enhver tid er i
 */
static posisjon Posisjon = 0;

/**
 @brief Matrise med bestillingene til heisen
*/
static int order_matrix[N_FLOORS][N_BUTTONS];

/**
 @brief Itererer gjennom alle knappene for å se om de er trykket inn og oppdaterer bestillingsmatrisen
*/
void orders_update_order_matrix(void);

/**
 @brief Gir om det finnes bestillinger i det hele tatt
 @return 1 om det finnes bestillinger, 0 hvis ikke
 */
int orders_exist_orders(void);


/**
 @brief sjekker om det er noen bestillinger fra etasjene under nåværende posisjon
 @return 1 hvis det finnes bestilling i valgt etasjer under, 0 hvis ikke
*/
int orders_order_below_position(void);

/**
 @brief sjekker om det er noen bestillinger fra etasjene over nåværende posisjon
 @return 1 hvis det finnes bestilling i valgt etasjer over, 0 hvis ikke
*/
int orders_order_above_position(void);

/**
 @brief Returnerer om det er bestillinger i valgt etasje
 @param floor Etasjenummer
 @return 1 hvis det finnes bestilling i valgt etasje, 0 hvis ikke
*/
int orders_order_at_this_floor(int floor);

/**
 @brief Sletter besillinger i gitt etasje
 @param floor Etasjenummer
 */
void orders_delete_orders_at_this_floor(int floor);

/**
 @brief Sletter alle bestillinger
 */
void orders_delete_all_orders(void);

/**
 @brief Ser om det er en bestilling fra inne i heisen til etasjen heisen er i
 @return 1 om det er en bestilling fra inne i heisen til etasjen heisen er i
 @return 0 hvis ikke
 */
int orders_command_at_floor(posisjon pos);

/**
 @brief Sier om det er noen som har trykket 'opp' i etasjen heisen er i
 @return 1 hvis noen har trykket på up i etasjen heisen er i
 @return 0 hvis ikke
 */
int orders_up_at_floor(posisjon pos);

/**
 @brief Sier om det er noen som har trykket 'ned' i etasjen heisen er i
 @return 1 hvis noen har trykket på ned i etasjen heisen er i
 @return 0 hvis ikke
*/
int orders_down_at_floor(posisjon pos);

/**
 @brief Gir esm tilgang på nåværende heispoisjon
 @return Variabel av type posisjon
*/
posisjon orders_get_posisjon(void);
/**
 @brief Gir esm tilgang til å endre posisjon, når den beveger seg inn eller ut av en etasje
 @param Tar inn variabel av type posisjon
*/
void orders_set_posisjon(posisjon pos);

#endif
