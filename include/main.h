/**
 * @file	main.h
 *
 * @brief	A Documented file.
 *
 * @author	Eliott Remars
 * @date 	2023-02-09
 */

#ifndef _JEU_MAIN_
#define _JEU_MAIN_





/* -------------------------------------------------------------------------- */
/*                                Enumerations                                */
/* -------------------------------------------------------------------------- */


/**
 * @enum state_main
 * @brief 
 * 
 */
typedef enum {
  	JEU_QUITTER = -1, 
  	M_JOUER = 1,
  	M_MENU,
  	M_OPTIONS,
  	M_PAUSE, 
  	J_MORT
} state_main;


/**
 * @enum e_actionMonde
 * @brief 
 * 
 */
typedef enum {
  	MONDE_CREER,
  	MONDE_CHARGER
} e_actionMonde;





#endif
