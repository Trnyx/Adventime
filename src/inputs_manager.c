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





int inputManager(t_joueur *joueur, t_controles *controles) {
    SDL_Event event;

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
                if (controles->key_up == event.key.keysym.scancode) {
                    joueur->actionFlags->up = joueur->actionFlags->down + 1;
                }
                else if (controles->key_down == event.key.keysym.scancode) {
                    joueur->actionFlags->down = joueur->actionFlags->up + 1;
                }
                else if (controles->key_left == event.key.keysym.scancode) {
                    joueur->actionFlags->left = joueur->actionFlags->right + 1;
                }
                else if (controles->key_right == event.key.keysym.scancode) {
                    joueur->actionFlags->right = joueur->actionFlags->left + 1;
                }

                // Interaction
                else if (controles->interaction == event.key.keysym.scancode) {
                    joueur->actionFlags->interaction = 1;
                }

                // Minimap
                else if (controles->miniMap == event.key.keysym.scancode) {
                    joueur->actionFlags->miniMap = 1;
                }

                break;



            /* ------------------------ Relachement de la touche ------------------------ */

            case SDL_KEYUP:
                // Deplacement
                if (controles->key_up == event.key.keysym.scancode) {
                    joueur->actionFlags->up = 0;
                }
                else if (controles->key_down == event.key.keysym.scancode) {
                    joueur->actionFlags->down = 0;
                }
                else if (controles->key_left == event.key.keysym.scancode) {
                    joueur->actionFlags->left = 0;
                }
                else if (controles->key_right == event.key.keysym.scancode) {
                    joueur->actionFlags->right = 0;
                }

                // Interaction
                else if (controles->interaction == event.key.keysym.scancode) {
                    joueur->actionFlags->interaction = 0;
                }

                // Minimap
                else if (controles->miniMap == event.key.keysym.scancode) {
                    joueur->actionFlags->miniMap = 0;
                }

                break;
            

            /* -------------------------------------------------------------------------- */
            /*                                   Souris                                   */
            /* -------------------------------------------------------------------------- */


            /* ------------------------- Position de las souris ------------------------- */
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
}