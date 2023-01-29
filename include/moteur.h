/**
 * @file 
 *
 * @brief
 *
 * @author
 */



#ifndef _JEU_MOTEUR_
#define _JEU_MOTEUR_





#define FPS 60
#define TPS ((float)1000/FPS)



typedef struct {

    SDL_Window *window;         /**< La fenetre du jeu*/
    SDL_Renderer *renderer;     /**< Le renderer du jeu*/



    int window_width;           /**< Largeur de la fenêtre */
    int window_height;          /**< Hauteur de la fenêtre */

} t_moteur;



void regulerFPS(t_moteur * moteur);
t_moteur * chargerMoteur(unsigned int temps);
void detruireMoteur(t_moteur ** moteur);
void updateEchelle(t_moteur * moteur);





#endif
