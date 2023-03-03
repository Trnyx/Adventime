/**
 * @file inputs_manager.c
 * @brief
 *
 * @author Clément Hibon
 * @date 6 février
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../include/input_manager.h"





int inputManager(t_joueur *joueur) {
    t_controles controles = moteur->controles;
    SDL_Event event;


    /* ----------------------------- Position Souris ---------------------------- */
    int x, y;
    SDL_GetMouseState(&x, &y);

    moteur->positionSouris.x = x;
    moteur->positionSouris.y = y;



    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return -1;
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
                    return -1;
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
                        break;

                }
                break;


        }


        return 1;
    }

    return 1;
}