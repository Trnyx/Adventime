/**
 * @file inputs_manager.c
 * 
 * @brief Module qui gère tous les inputs du joueur
 * 
 * Clavier et souris
 *
 * @author Clément Hibon
 * @date 6 février
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../include/input_manager.h"
#include "../include/menus.h"





/**
 * @brief Regarde l'état du clavier et de la souris et met à jour les états des inputs dans le joueur
 * 
 * @param joueur Un pointeur sur le joueur où sont stockés les différentes informations sur l'état actuel des inputs du joueur
 * 
 * @return L'état du jeu (J_MORT, M_PAUSE, M_QUIT)
 */
int inputManager(t_joueur *joueur) {
    t_controles controles = moteur->controles;
    SDL_Event event;


    /* ----------------------------- Position Souris ---------------------------- */
    // Les positions x et y de la souris sur l'écran
    int x, y;
    SDL_GetMouseState(&x, &y);

    moteur->positionSouris.x = x;
    moteur->positionSouris.y = y;
    
    if(joueur->statistiques.pv <= 0) {
      moteur->state = J_MORT;
      return J_MORT;
    }

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return M_MENU;
                break;
            
            
            /* -------------------------------------------------------------------------- */
            /*                                   Clavier                                  */
            /* -------------------------------------------------------------------------- */


            /* -------------------------- Appuie sur la touche -------------------------- */

            case SDL_KEYDOWN:
                // Deplacement
                if (controles.key_up == event.key.keysym.scancode) {
                    joueur->actionFlags->up = 1;
                }
                else if (controles.key_down == event.key.keysym.scancode) {
                    joueur->actionFlags->down = 1;
                }
                else if (controles.key_left == event.key.keysym.scancode) {
                    joueur->actionFlags->left = 1;
                }
                else if (controles.key_right == event.key.keysym.scancode) {
                    joueur->actionFlags->right = 1;
                }

                // Interaction
                else if (controles.interaction == event.key.keysym.scancode) {
                    joueur->actionFlags->interaction = 1;
                }

                // Minimap
                else if (controles.miniMap == event.key.keysym.scancode) {
                    joueur->actionFlags->miniMap = 1;
                }

                // Echap
                else if (controles.escape == event.key.keysym.scancode) {
		  moteur->state = M_PAUSE;
		  return M_PAUSE;
                }

		else if (event.key.keysym.scancode == SDL_SCANCODE_K) {
		  joueur->statistiques.pv = 0;
		}

                break;



            /* ------------------------ Relachement de la touche ------------------------ */

            case SDL_KEYUP:
                // Deplacement
                if (controles.key_up == event.key.keysym.scancode) {
                    joueur->actionFlags->up = 0;
                }
                else if (controles.key_down == event.key.keysym.scancode) {
                    joueur->actionFlags->down = 0;
                }
                else if (controles.key_left == event.key.keysym.scancode) {
                    joueur->actionFlags->left = 0;
                }
                else if (controles.key_right == event.key.keysym.scancode) {
                    joueur->actionFlags->right = 0;
                }

                // Interaction
                else if (controles.interaction == event.key.keysym.scancode) {
                    joueur->actionFlags->interaction = 0;
                }

                // Minimap
                else if (controles.miniMap == event.key.keysym.scancode) {
                    joueur->actionFlags->miniMap = 0;
                }

                break;
            

            /* -------------------------------------------------------------------------- */
            /*                                   Souris                                   */
            /* -------------------------------------------------------------------------- */


            /* --------------------------- Clique de la souris -------------------------- */

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    // Attaque
                    case SDL_BUTTON_LEFT:
                        // Si le clique de la souris reste enfoncé on ignore en mettant à -1
                        if (joueur->actionFlags->attack == 0)
                            joueur->actionFlags->attack = 1;
                        else
                            joueur->actionFlags->attack = -1;
                        break;

                }
                break;



            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    // 
                    case SDL_BUTTON_LEFT:
                        joueur->actionFlags->attack = 0;
                        break;

                }
                break;



            /* --------------------------- Scroll de la souris -------------------------- */


            case SDL_MOUSEWHEEL:
                // Scroll vers le haut
                if (event.wheel.y > 0) {

                }
                // Scroll vers le bas
                else if (event.wheel.y < 0) {

                }
                
                break;


        }


        return 1;
    }

    return 1;
}
