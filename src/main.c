/**
 * @file main.c
 *
 * @brief Programme principal
 * 
 * 1. Création et initialisation des variables de travail
 * 2. Menu & jeu principal
 * 3. Destruction des variables de travail et fermeture du programme
 *
 * @author Clément Hibon & Julien Houget & Eliott Remars
 * @date 20 janvien
 */






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










int main(int argc, char* argv[]) {
	

	initAll(&moteur, &audio);
	ctx = nk_sdl_init(moteur->window, moteur->renderer);

	moteur->state = M_MENU;
	


	play_music(audio->musiques->menu_principal, VRAI, FAUX);


	while (moteur->state != JEU_QUITTER) {
		
		switch (moteur->state) {
			case M_MENU: moteur->state = main_menu(ctx); break;
			case M_JOUER: 
				moteur->state = jouer(MONDE_CREER); 
				if (moteur->state != JEU_QUITTER) {
				  	play_music(audio->musiques->menu_principal, VRAI, FAUX);
					audio->musiqueType = MUSIC_MENU;
				}
				break;
			case M_OPTIONS: moteur->state = menu_options(ctx); break;
			default: moteur->state = JEU_QUITTER; break;
		}

	}

	

	detruireAll(moteur, audio);
	SDL_Quit();
 
	return 0;
}
