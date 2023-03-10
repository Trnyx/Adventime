/**
 * @file	main.h
 *
 * @brief	A Documented file.
 *
 * @author	Eliott Remars
 * @date 	2023-02-09
 * @version 	1.0
 */

#ifndef _JEU_MAIN_
#define _JEU_MAIN_





/* -------------------------------------------------------------------------- */
/*                                Enumerations                                */
/* -------------------------------------------------------------------------- */


typedef enum {
  JEU_QUITTER = -1, M_MENU = 1, M_OPTIONS, M_JOUER
} state_main;


typedef enum {
  MONDE_CREER,
  MONDE_CHARGER
} e_actionMonde;





#endif
