/**
 * @file audio.c
 * 
 * @brief 
 * 
 * 
 * @author Clément Hibon
 * @date 1 février
 * @version 1.1
 */





#include <stdlib.h>
#include <audio.h>




/**
 * @brief 
 * 
 * @param nouveauVolume 
 */
void changerVolume(int nouveauVolume) {
    Mix_VolumeMusic(3 * nouveauVolume / 4);
    Mix_Volume(-1, nouveauVolume);
}





/**
 * @brief 
 * 
 * @param volume 
 * @param musiques 
 * @param bruitages 
 * @return int 
 */
int chargerAudio(int volume, t_musiques **musiques, t_bruitages **bruitages) {
    t_musiques *m = malloc(sizeof(t_musiques));
    if (m == NULL) {
        printf("Impossible d'allouer la mémoire pour les musiques");;
        return -1;
    }


    t_bruitages *b = malloc(sizeof(t_bruitages));
    if (b == NULL) {
        printf("Impossible d'allouer la mémoire pour les bruitages");;
        return -1;
    }



    /* -------------------------------- Musiques -------------------------------- */
    // Menu
    m->menu_principal = Mix_LoadMUS("assets/audio/musiques/.mp3");

    // Ambiance
    m->ambiance = Mix_LoadMUS("assets/audio/musiques/.mp3");
    // m->ambiance_nuit = Mix_LoadMUS("assets/audio/musiques/.mp3");

    // Combat
    m->combat = Mix_LoadMUS("assets/audio/musiques/.mp3");
    // m->combat_nuit = Mix_LoadMUS("assets/audio/musiques/.mp3");
    // m->combat_boss = Mix_LoadMUS("assets/audio/musiques/.mp3");
    
    
    /* -------------------------------- Bruitages ------------------------------- */
    // Menu
    // b->menu_selection = Mix_LoadWAV("assets/audio/bruitages/.wav");

    // Joueur
    // b->joueur_attaque = Mix_LoadWAV("assets/audio/bruitages/.wav");
    // b->joueur_degat = Mix_LoadWAV("assets/audio/bruitages/.wav");
    // b->joueur_mort = Mix_LoadWAV("assets/audio/bruitages/.wav");

    // Monstre
    // b->monstre_attaque = Mix_LoadWAV("assets/audio/bruitages/.wav");
    // b->monstre_degat = Mix_LoadWAV("assets/audio/bruitages/.wav");
    // b->monstre_mort = Mix_LoadWAV("assets/audio/bruitages/.wav");

    // Autres
    // b->item_recuperation = Mix_LoadWAV("assets/audio/bruitages/.wav");



    changerVolume(volume);


    *musiques = m;
    *bruitages = b;


    return 0;
}





/**
 * @brief 
 * 
 * @param musique 
 * @param bruitage 
 */
int detruireAudio(t_musiques **musiques, t_bruitages **bruitages) {
    if (musiques == NULL || *musiques == NULL) return -1;
    if (bruitages == NULL || *bruitages == NULL) return -1;



    /* -------------------------------- Musiques -------------------------------- */
    // Mix_FreeMusic((*musiques)->);

    free(*musiques);
    *musiques == NULL;


    /* -------------------------------- Bruitages ------------------------------- */
    // Mix_FreeChunk((*bruitages)->);

    free(*bruitages);
    *bruitages == NULL;



    return 0;
}


