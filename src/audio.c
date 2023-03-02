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





#include <stdio.h>
#include <stdlib.h>

#include "../include/audio.h"




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
 * @param music 
 */
void play_music(Mix_Music *music, boolean repeat) {
    Mix_PlayMusic(music, repeat ? -1 : 0);
}


/**
 * @brief 
 * 
 * @param sound 
 * @param channel 
 */
void play_bruitage(Mix_Chunk *sound, int channel) {
    Mix_PlayChannel(channel, sound, 0);
}





void selectionMusique(t_audio *audio) {
    t_musiques *musiques = audio->musiques;
    Mix_Music *musique = NULL;


    switch (audio->musiqueType) {
        case MUSIC_MENU:
            musique = musiques->menu_principal;
            break;

        case MUSIC_AMBIANCE:
            musique = musiques->ambiance_nuit;
            break;
            
        case MUSIC_COMBAT:
            musique = musiques->combat;
            break;
        
        default:
            musique = musiques->menu_principal;
            break;
    }


    play_music(musique, FAUX);
}





/* -------------------------------------------------------------------------- */
/*                                 Chargement                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param volume 
 * @param musiques 
 * @param bruitages 
 * @return int 
 */
int chargerAudio(const int volume, t_musiques **musiques, t_bruitages **bruitages) {
    t_musiques *m = malloc(sizeof(t_musiques));
    if (m == NULL) {
        printf("Impossible d'allouer la mémoire pour les musiques");
        free(m);
        return -1;
    }


    t_bruitages *b = malloc(sizeof(t_bruitages));
    if (b == NULL) {
        printf("Impossible d'allouer la mémoire pour les bruitages");
        free(b);
        return -1;
    }



    /* -------------------------------- Musiques -------------------------------- */
    // Menu
    m->menu_principal = Mix_LoadMUS("assets/audio/musiques/menu.mp3");

    // Ambiance
    m->ambiance_jour = Mix_LoadMUS("assets/audio/musiques/.mp3");
    m->ambiance_nuit = Mix_LoadMUS("assets/audio/musiques/ambiance_nuit.mp3");

    // Combat
    m->combat = Mix_LoadMUS("assets/audio/musiques/combat.mp3");
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





/* -------------------------------------------------------------------------- */
/*                                    Init                                    */
/* -------------------------------------------------------------------------- */


t_audio* initAudio() {
    t_audio *audio = malloc(sizeof(t_audio));


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("WARNING : Erreur d'initialisation de SDL MIXER : %s\n", Mix_GetError());
    }


    chargerAudio(MIX_MAX_VOLUME, &audio->musiques, &audio->bruitages);
    audio->musiqueType = MUSIC_MENU;


    return audio;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param musique 
 * @param bruitage 
 */
int detruireAudio(t_audio **audio) {
    if (audio == NULL || *audio == NULL) return -1;
    t_musiques *musiques = (*audio)->musiques;
    t_bruitages *bruitages = (*audio)->bruitages;

    if (musiques == NULL) return -1;
    if (bruitages == NULL) return -1;



    /* -------------------------------- Musiques -------------------------------- */
    // Mix_FreeMusic((*musiques)->);

    free(musiques);
    musiques = NULL;


    /* -------------------------------- Bruitages ------------------------------- */
    // Mix_FreeChunk((*bruitages)->);

    free(bruitages);
    bruitages = NULL;



    free(*audio);
    *audio = NULL;

    return 0;
}


