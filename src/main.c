

#include "../include/main.h"
#include "../include/initialiseur.h"
#include "../include/menus.h"
#include "../include/moteur.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/main.h"

int main() {

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
