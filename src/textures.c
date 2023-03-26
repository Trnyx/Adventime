/**
 * @file textures.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 3 février
 * @version 1.0
 */





#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

#include "../include/textures.h"
#include "../include/monde.h"





/**
 * @brief 
 * 
 * @param source 
 * @param x 
 * @param y 
 * @param tailleX 
 * @param tailleY 
 */
void splitTexture(SDL_Rect *source, const int x, const int y, const int tailleX, const int tailleY) {
    source->x = x;
    source->y = y;
    source->w = tailleX;
    source->h = tailleY;
}





/**
 * @brief 
 * 
 * @param tag Le tag de la texture à afficher
 * @param textures Un pointeur sur la structure stoccant les textures
 * 
 * @return La te
 */
SDL_Texture* getTexture(const int tag, t_textures *textures) {    
    switch (tag) {
        // case SOL_EAU_PROFONDE: return textures->sol_profondeur;
        // case SOL_EAU: return textures->sol_eau;
        // case SOL_SABLE: return textures->sol_sable;
        // case SOL_HERBE_1: return textures->sol_herbe_1;
        // case SOL_HERBE_2: return textures->sol_herbe_2;
        // case SOL_HERBE_3: return textures->sol_herbe_3;
        // case SOL_MONTAGNE_1: return textures->sol_montagne_1;
        // case SOL_MONTAGNE_2: return textures->sol_montagne_2;
        // case SOL_NEIGE: return textures->sol_profondeur;
        
        default: return NULL;
    }
}





/* -------------------------------------------------------------------------- */
/*                                  Création                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Alloue l'espace nécessaire pour les textures et les chargent
 * 
 * @param renderer Le renderer SDL nécessaire pour le rendu du jeu
 * 
 * @return Un pointeur sur les textures, NULL en cas d'echec
 */
t_textures* initTextures(SDL_Renderer *renderer) {
    t_textures *textures = malloc(sizeof(t_textures));

    if (textures == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour les textures\n");
        return NULL;
    }

    
    SDL_Surface *surface = NULL;


    surface = IMG_Load("assets/images/null.png");
    textures->null = SDL_CreateTextureFromSurface(renderer, surface);
    if (surface == NULL) {
        printf("Erreur Chargement Texture : Impossible de charger null.png\n%s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);


    /* ----------------------------------- Map ---------------------------------- */
    // assets/images/.png

    surface = IMG_Load("assets/images/sol_tileset.png");
    textures->sol = SDL_CreateTextureFromSurface(renderer, surface);
    if (surface == NULL) {
        printf("Erreur Chargement Texture : Impossible de charger sol_tileset.png\n%s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);
    

    /* -------------------------------- Végétaux -------------------------------- */

    surface = IMG_Load("assets/images/vegetaux_tileset.png");
    textures->vegetaux = SDL_CreateTextureFromSurface(renderer, surface);
    if (surface == NULL) {
        printf("Erreur Chargement Texture : Impossible de charger vegetaux_tileset.png\n%s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);
    

    /* ------------------------------- Structures ------------------------------- */

    surface = IMG_Load("assets/images/structures_tileset.png");
    textures->structures = SDL_CreateTextureFromSurface(renderer, surface);
    if (surface == NULL) {
        printf("Erreur Chargement Texture : Impossible de charger structures_tileset.png\n%s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);


    /* --------------------------------- Joueur --------------------------------- */

    surface = IMG_Load("assets/images/joueur_tileset.png");
    textures->joueur = SDL_CreateTextureFromSurface(renderer, surface);
    if (surface == NULL) {
        printf("Erreur Chargement Texture : Impossible de charger joueur_tileset.png\n%s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);


    /* -------------------------------- Monstres -------------------------------- */

    surface = IMG_Load("assets/images/monstres_tileset.png");
    textures->monstres = SDL_CreateTextureFromSurface(renderer, surface);
    if (surface == NULL) {
        printf("Erreur Chargement Texture : Impossible de charger monstres_tileset.png\n%s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);


    /* --------------------------------- Animaux -------------------------------- */

    surface = IMG_Load("assets/images/animaux_tileset.png");
    textures->animaux = SDL_CreateTextureFromSurface(renderer, surface);
    if (surface == NULL) {
        printf("Erreur Chargement Texture : Impossible de charger animaux_tileset.png\n%s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);


    /* --------------------------------- Autres --------------------------------- */

    surface = IMG_Load("assets/images/items_tileset.png");
    textures->items = SDL_CreateTextureFromSurface(renderer, surface);
    if (surface == NULL) {
        printf("Erreur Chargement Texture : Impossible de charger items_tileset.png\n%s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);


    return textures;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Detruit les textures est libère la mémoire allouée pour ces dernières
 * 
 * @param textures L'adresse du pointeur sur les textures 
 */
void detruireTextures(t_textures **textures) {
    printf("Destruction Textures => ");
    if (textures != NULL && *textures != NULL) {

        if ((*textures)->null != NULL) 
            SDL_DestroyTexture((*textures)->null);

        // Map
        if ((*textures)->sol != NULL) 
            SDL_DestroyTexture((*textures)->sol);
        
        // Végétaux
        if ((*textures)->vegetaux != NULL) 
            SDL_DestroyTexture((*textures)->vegetaux);

        // Structures
        if ((*textures)->structures != NULL) 
            SDL_DestroyTexture((*textures)->structures);
        
        // Joueur
        if ((*textures)->joueur != NULL) 
            SDL_DestroyTexture((*textures)->joueur);

        // Monstres
        if ((*textures)->monstres != NULL) 
            SDL_DestroyTexture((*textures)->monstres);

        // Animaux
        if ((*textures)->animaux != NULL) 
            SDL_DestroyTexture((*textures)->animaux);

        // Autres
        if ((*textures)->items != NULL) 
            SDL_DestroyTexture((*textures)->items);


        free(*textures);
        *textures = NULL;

    }
    printf("Succes\n");
}
