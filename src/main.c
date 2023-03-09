#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "../include/moteur.h"
#include "../include/audio.h"
#include "../include/main.h"
#include "../include/physique.h"
#include "../include/menus.h"
#include "../include/initialiseur.h"
#include "../include/jeu.h"
// #include "../include/textures.h"
// #include "../include/monde.h"
// #include "../include/joueur.h"
// #include "../include/input_manager.h"










int main(int argc, char* argv[]) {

	// moteur = NULL;
	// audio = NULL;

	
	state_main state = 1;
	

	initAll(&moteur, &audio);
	ctx = nk_sdl_init(moteur->window, moteur->renderer);
	
	
	play_music(audio->musiques->menu_principal, VRAI);

	while (state != JEU_QUITTER) {
		
		switch (state) {
			case M_MENU: state = main_menu(ctx); break;
			case M_JOUER: 
				state = jouer(MONDE_CREER); 
				if (state != JEU_QUITTER) 
					play_music(audio->musiques->menu_principal, VRAI);
				break;
			case M_OPTIONS: state = menu_options(ctx); break;
			default: state = JEU_QUITTER; break;
		}

	}

	

	detruireAll(moteur, audio);
	SDL_Quit();

	return 0;
}
