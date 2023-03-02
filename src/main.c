#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "../include/menus.h"
#include "../include/physique.h"
#include "../include/initialiseur.h"
#include "../include/textures.h"
#include "../include/moteur.h"
#include "../include/audio.h"
#include "../include/main.h"
#include "../include/monde.h"
#include "../include/joueur.h"
#include "../include/input_manager.h"










int main(int argc, char* argv[]) {

  t_moteur * moteur;
  struct nk_context *ctx = NULL;
  
  state_main state = 1;
  
  initAll(&moteur);
  ctx = nk_sdl_init(moteur->window, moteur->renderer);
  
  while (state != JEU_QUITTER) {

    switch (state) {
    case M_MENU: state = main_menu(ctx, moteur); break;
    case M_JOUER: state = main_menu(ctx, moteur); break;
    case M_OPTIONS: state = menu_options(ctx, moteur); break;
    default: state = JEU_QUITTER; break;
    }

  }

  nk_sdl_shutdown();
  SDL_DestroyRenderer(moteur->renderer);
  SDL_DestroyWindow(moteur->window);
  SDL_Quit();
  detruireMoteur(&moteur);

  return 0;
}
