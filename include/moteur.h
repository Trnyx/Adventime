/**
 * @file moteur.h
 *
 * @brief Module de manipulation du moteur du jeu
 *
 * @author Eliott Remars & Clément Hibon
 * @date 3 février
 */



#ifndef _JEU_MOTEUR_
#define _JEU_MOTEUR_




#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "utilitaire.h"
#include "textures.h"
#include "camera.h"
#include "monde.h"
#include "main.h"
#include "cache.h"





#define FPS 60
#define TPS ((float)1000/FPS)





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_controles
 * @brief Struture contenant les touches pour les contrôles du jeu
 * 
 */
typedef struct s_controles {
    // Directions
    SDL_Scancode key_up;        /**< La touche de direction vers le haut */
    SDL_Scancode key_down;      /**< La touche de direction vers le bas */
    SDL_Scancode key_left;      /**< La touche de direction vers la gauche */
    SDL_Scancode key_right;     /**< La touche de direction vers la droite */

    // Inventaire
    SDL_Scancode inventory;    /**< La touche pour ouvrir et fermer l'inventaire */

    // Interactions
    SDL_Scancode interaction;   /**< La touche d'interaction */
    int attack;                 /**< Le clique pour l'attaque */

    // Autres
    SDL_Scancode escape;        /**< La touche echap */
    SDL_Scancode miniMap;       /**< La touche pour afficher la mini map */

} t_controles;



/**
 * @struct t_moteur
 * @brief Structure contenant les informations globales du jeu
 * 
 */
typedef struct s_moteur {

    SDL_Window *window;             /**< La fenetre du jeu*/
    SDL_Renderer *renderer;         /**< Le renderer du jeu*/

    int window_width;               /**< Largeur de la fenêtre */
    int window_height;              /**< Hauteur de la fenêtre */
    t_vecteur2 positionSouris;      /**< La position de la souris sur l'écran*/

    
    t_camera *camera;               /**< La caméra */
    t_textures *textures;           /**< Toutes les textures du jeu */
    t_controles controles;          /**< Les contrôles du jeu */
    

    t_cache *cache;                 /**< Cache du jeu */
    t_temps *temps;                 /**< Le temps dans le jeu */
    unsigned int frame;             /**< Le timestamp (tick) de la drame actuelle */
    state_main state;               /**< L'état du jeu (écran à afficher) */
    TTF_Font * font;                /**< La police d'écriture */
    

} t_moteur;


// Le moteur est en global pour faciliter l'accès
extern t_moteur *moteur;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void regulerFPS();
t_moteur* initMoteur();
void detruireMoteur(t_moteur **moteur);
void updateEchelle();





#endif
