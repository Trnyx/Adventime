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




/* ----------------------------- Pointeur Global ---------------------------- */

t_audio *audio = NULL;




/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


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





void selectionMusique() {
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
    t_audio *a = malloc(sizeof(t_audio));


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("WARNING : Erreur d'initialisation de SDL MIXER : %s\n", Mix_GetError());
    }


    chargerAudio(MIX_MAX_VOLUME, &a->musiques, &a->bruitages);
    a->musiqueType = MUSIC_MENU;


    return a;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param audio 
 */
void detruireAudio(t_audio **audio) {
    printf("Destruction Audio => ");
    if (audio != NULL && *audio != NULL) {

        t_musiques *musiques = (*audio)->musiques;
        t_bruitages *bruitages = (*audio)->bruitages;





        /* -------------------------------- Musiques -------------------------------- */
        if (musiques != NULL) {
            printf("Destruction musiques => ");
            // Mix_FreeMusic((*musiques)->);

            Mix_FreeMusic((*audio)->musiques->ambiance_jour);
            Mix_FreeMusic((*audio)->musiques->ambiance_nuit);
            Mix_FreeMusic((*audio)->musiques->combat);
            Mix_FreeMusic((*audio)->musiques->menu_principal);

            free(musiques);
            musiques = NULL;
        }
        else {
            printf("Pas de musique => ");
        }


        /* -------------------------------- Bruitages ------------------------------- */
        if (bruitages != NULL) {
            printf("Destruction bruitages => ");
            // Mix_FreeChunk((*bruitages)->);

            // Mix_FreeChunk((*audio)->bruitages->menu_selection);
            // Mix_FreeChunk((*audio)->bruitages->joueur_attaque);
            // Mix_FreeChunk((*audio)->bruitages->joueur_degat);
            // Mix_FreeChunk((*audio)->bruitages->joueur_mort);
            // Mix_FreeChunk((*audio)->bruitages->monstre_attaque);
            // Mix_FreeChunk((*audio)->bruitages->monstre_degat);
            // Mix_FreeChunk((*audio)->bruitages->monstre_mort);
            // Mix_FreeChunk((*audio)->bruitages->item_recuperation);

            free(bruitages);
            bruitages = NULL;
        }
        else {
            printf("Pas de bruitage => ");
        }


        printf("Destruction global => ");
        free(*audio);
        *audio = NULL;

        Mix_CloseAudio();

    }
    printf("Succes\n");
}


