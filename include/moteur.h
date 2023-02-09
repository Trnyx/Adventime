/**
 * @file moteur.h
 *
 * @brief
 *
 * @author Eliott Remars & Clément Hibon
 * @date 3 février
 * @version 1.1
 */



#ifndef _JEU_MOTEUR_
#define _JEU_MOTEUR_




#include <SDL2/SDL.h>

#include "textures.h"
#include "camera.h"
#include "monde.h"





#define FPS 60
#define TPS ((float)1000/FPS)





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 */
typedef struct s_controles {
    // Directions
    SDL_Scancode key_up;
    SDL_Scancode key_down;
    SDL_Scancode key_left;
    SDL_Scancode key_right;

    // Interactions
    SDL_Scancode interaction;
    int attack;

    // Autres
    SDL_Scancode escape;
    SDL_Scancode miniMap;

} t_controles;



/**
 * @brief 
 * 
 */
typedef struct s_moteur {

    SDL_Window *window;         /**< La fenetre du jeu*/
    SDL_Renderer *renderer;     /**< Le renderer du jeu*/

    int window_width;           /**< Largeur de la fenêtre */
    int window_height;          /**< Hauteur de la fenêtre */


    t_monde *monde;             /**< Le monde chargé */
    
    t_camera *camera;           /**< La caméra */
    t_textures *textures;       /**< Toutes les textures du jeu */
    t_controles controles;     /**< Les contrôles du jeu */
    

} t_moteur;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void regulerFPS(t_moteur *moteur);
t_moteur* initMoteur();
void detruireMoteur(t_moteur **moteur);
void updateEchelle(t_moteur *moteur);





#endif
