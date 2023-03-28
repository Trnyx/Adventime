/**
 * @file initialiseur.c
 * 
 * @brief Module d'initialisation
 * 
 * @author Eliott Remars & Clément Hibon
 * @date 3 février
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../include/initialiseur.h"
#include "../include/menus.h"
// #include image.h





/**
 * @brief Initialise tout ce qui est nécessaire pour le bon fonctionnement du jeu
 * 
 * @param moteur L'adresse du pointeur sur le moteur qui sera intialisé 
 * @param audio L'adresse du pointeur sur l'audio qui sera intialisé 
 */
void initAll(t_moteur **moteur, t_audio **audio) {
    // Moteur
    *moteur = initMoteur();
    
    const t_vecteur2 positionCamera = { 0, 0 };
    (*moteur)->camera = creerCamera(positionCamera);
    updateEchelle();
    
    (*moteur)->textures = initTextures((*moteur)->renderer);
    (*moteur)->cache = initCache();
    (*moteur)->temps = initTemps(time(NULL));


    // Methode d'affichage
    // Pour le filtre d'ambiance
    SDL_SetRenderDrawBlendMode((*moteur)->renderer, SDL_BLENDMODE_BLEND);


    // Pour afficher le logo en tant qu'icon dans la barre des tâches lorsque le jeu est allumé
    SDL_Surface *logo = NULL;
    logo = IMG_Load("assets/images/logo.png");
    SDL_SetWindowIcon((*moteur)->window, logo);
    SDL_FreeSurface(logo);


    // Audio
    *audio = initAudio();
    
    
    // SDL Image
    

    // SDL TTF
    TTF_Init();
    (*moteur)->font = TTF_OpenFont("assets/font/NewHiScore.ttf", 45);
}



/**
 * @brief Detruit tout ce qui à été initialisé pour le fonctionnement du jeu
 * 
 * @param moteur Le pointeur sur le moteur qui sera détruit
 * @param audio Le pointeur sur l'audio qui sera détruit
 */
void detruireAll(t_moteur *moteur, t_audio *audio) {
    nk_sdl_shutdown();
    t_cache *cache = moteur->cache;

    if (cache->monde != NULL) {
        
        if (cache->monde->joueur != NULL) 
            detruireJoueur(&cache->monde->joueur);

        detruireCache(&cache);
        detruireTemps(&moteur->temps);
    }
    TTF_Quit();
    detruireCamera(&moteur->camera);
    detruireTextures(&moteur->textures);

    SDL_DestroyRenderer(moteur->renderer);
    SDL_DestroyWindow(moteur->window);
    detruireMoteur(&moteur);

    detruireAudio(&audio);
}
