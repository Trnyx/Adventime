/**
 * @file moteur.c
 *
 * @brief Gestion du moteur du jeu
 * 
 * Le moteur contient toutes les informations nécessaire pour le renderer, la caméra, les textures 
 * ainsi que le cache du jeu
 *
 * @author Eliott Remars & Clément Hibon
 * @date 3 février
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>
#include "../include/moteur.h"
#include "../include/window.h"





/* ----------------------------- Pointeur Global ---------------------------- */

t_moteur *moteur = NULL;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Cette fonction permet de faire en sorte que le jeu soit constamment à 60 images par secondes
 * 
 */
void regulerFPS() {
    int tempsEcoule = SDL_GetTicks() - moteur->frame;
    if (TPS > tempsEcoule) 
        SDL_Delay(TPS - tempsEcoule);
    moteur->frame = SDL_GetTicks();
}





/**
 * @brief Initialise les controles du jeu
 * 
 * @param controles Un pointeur sur une structure où sont stocké les controles du jeu
 */
void initControles(t_controles *controles) {
    // Deplacements
    controles->key_up = SDL_SCANCODE_W;
    controles->key_down = SDL_SCANCODE_S;
    controles->key_left = SDL_SCANCODE_A;
    controles->key_right = SDL_SCANCODE_D;

    // Inventaire
    controles->inventory = SDL_SCANCODE_E;

    // Interactions
    controles->interaction = SDL_SCANCODE_F;
    controles->attack = SDL_BUTTON_LEFT;

    // Autres
    controles->escape = SDL_SCANCODE_ESCAPE;
    controles->miniMap = SDL_SCANCODE_TAB;
}





/**
 * @brief Alloue l'espace nécessaire pour le moteur et le créer
 * 
 * @return Un pointeur sur le moteur, NULL en cas d'echec
 */
t_moteur* initMoteur() {
    t_moteur *m = malloc(sizeof(t_moteur));

    if (m == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour le moteur\n");
        return NULL;
    }

    initSDL(m);

    m->camera = NULL;
    m->textures = NULL;;
    initControles(&m->controles);
    
    m->temps = NULL;

    m->cache = NULL;
    m->frame = SDL_GetTicks();


    return m;
}





/**
 * @brief Detruit le moteur est libère la mémoire allouée pour ce dernier
 * 
 * @param moteur L'adresse du pointeur sur le moteur 
 */
void detruireMoteur(t_moteur **moteur) {
    if (moteur != NULL && *moteur != NULL) {

        free((*moteur));
        *moteur = NULL;
        
    }
}





/**
 * @brief Calcule la taille en pixel d'un bloc selon la taille de l'écran et
 * actualise les informations de la caméra pour le rendu
 * 
 */
void updateEchelle() {

    SDL_GetWindowSize(moteur->window, &moteur->window_width, &moteur->window_height);

  
    int tailleRendu = moteur->window_width / TAILLE_CAMERA_LARGEUR;

    // int tailleLargeur = moteur->window_width / TAILLE_CAMERA_LARGEUR;
    // int tailleHauteur = moteur->window_height / TAILLE_CAMERA_HAUTEUR;


    moteur->camera->tailleRendu.x = tailleRendu;
    moteur->camera->tailleRendu.y = tailleRendu;
}





