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
	

	initAll(&moteur, &audio);
	ctx = nk_sdl_init(moteur->window, moteur->renderer);
	
	
	play_music(audio->musiques->menu_principal, VRAI);

	while (moteur->state != JEU_QUITTER) {
		
		switch (moteur->state) {
			case M_MENU: moteur->state = main_menu(ctx); break;
			case M_JOUER: 
				moteur->state = jouer(MONDE_CREER); 
				if (moteur->state != JEU_QUITTER) 
					play_music(audio->musiques->menu_principal, VRAI);
				break;
			case M_OPTIONS: moteur->state = menu_options(ctx); break;
			default: moteur->state = JEU_QUITTER; break;
		}

	}

	

	detruireAll(moteur, audio);
	SDL_Quit();

	return 0;
}
