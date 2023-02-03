/**
<<<<<<< HEAD
 * @file 
 *
 * @brief
 *
 * @author
=======
 * @file moteur.h
 *
 * @brief
 *
 * @author Eliott Remars & Clément Hibon
 * @date 3 février
 * @version 1.1
>>>>>>> main
 */



#ifndef _JEU_MOTEUR_
#define _JEU_MOTEUR_




#include <SDL2/SDL.h>





#define FPS 60
#define TPS ((float)1000/FPS)





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 */
typedef struct s_moteur {

    SDL_Window *window;         /**< La fenetre du jeu*/
    SDL_Renderer *renderer;     /**< Le renderer du jeu*/

    int window_width;           /**< Largeur de la fenêtre */
    int window_height;          /**< Hauteur de la fenêtre */



    

} t_moteur;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void regulerFPS(t_moteur *moteur);
t_moteur* initMoteur();
void detruireMoteur(t_moteur **moteur);
void updateEchelle(t_moteur *moteur);





#endif
