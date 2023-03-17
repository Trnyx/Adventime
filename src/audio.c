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

#include "../include/physique.h"
#include "../include/audio.h"
#include "../include/moteur.h"
#include "../include/entite.h"




/* ----------------------------- Pointeur Global ---------------------------- */

t_audio *audio = NULL;




/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


/* --------------------------------- Volume --------------------------------- */

/**
 * @brief Fonction permettant de changer le volume du channel spécifié
 * 
 * La channel ici n'est pas une piste audio mais plus une catégorie
 * 
 * @param channel Le channel où le volume sera modifié
 * @param nouveauVolume Le nouveau volume (en %)
 */
void changerVolume(const e_audio_channel channel, const float nouveauVolume) {
    switch (channel) {
        case CHANNEL_MASTER: 
            audio->masterVolume = nouveauVolume; 
            break;
        case CHANNEL_MUSIQUE: audio->musiqueVolume = nouveauVolume; break;
        case CHANNEL_BRUITAGE: audio->bruitageVolume = nouveauVolume; break;
    }
    

    Mix_Volume(-1, audio->bruitageVolume * audio->masterVolume * MIX_MAX_VOLUME);
    Mix_VolumeMusic(audio->musiqueVolume * audio->masterVolume * MIX_MAX_VOLUME * 0.75);
    Mix_MasterVolume(audio->masterVolume * MIX_MAX_VOLUME);
    
}





/* ---------------------------------- Play ---------------------------------- */

/**
 * @brief 
 * 
 * @param music 
 */
void play_music(Mix_Music *music, boolean repeat, boolean estLaSuite) {
    Mix_PlayMusic(music, repeat ? -1 : 0);
    double tempsEcoule = 0.0;

    if (estLaSuite) 
        tempsEcoule = (moteur->frame - audio->timestampDebutMusique) / 1000;

    Mix_SetMusicPosition(tempsEcoule);
    audio->timestampDebutMusique = moteur->frame;
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



/**
 * @brief 
 * 
 * @param tag 
 * @param angle 
 * @param distance 
 */
void play_sonAmbiance(e_entiteTag tag, float angle, float distance) {
    Mix_Chunk *bruitage = NULL;
    int channel = -1;


    switch (tag) {
        case TAG_ANIMAL_VACHE: bruitage = audio->bruitages->vache; break;
        case TAG_ANIMAL_COCHON: bruitage = audio->bruitages->cochon; break;
        
        default: break;
    }



    if (bruitage != NULL) {
        printf("BRUIT => ");
        // On ajuste l'angle
        angle = revolution(angle - 90);

        // On converti la distance entre 0 et 255
        distance = (distance * 255) / 16;
        if (distance > 255)
            distance = 255;

        // Récupère le premier channel libre
        channel = Mix_PlayChannel(channel, bruitage, 1);

        
        Mix_UnregisterAllEffects(channel);
        Mix_SetPosition(channel, angle, distance);
    }
}





/**
 * @brief 
 * 
 * @param temps 
 */
void selectionMusique(t_temps *temps) {
    t_musiques *musiques = audio->musiques;
    Mix_Music *musique = NULL;
    boolean estLaSuite = FAUX;

    audio->tempsEcoulee = moteur->frame - audio->timestampDebutMusique;


    switch (audio->musiqueType) {
        case MUSIC_AMBIANCE:
            switch (temps->periode) {
                case PERIODE_NUIT: musique = musiques->ambiance_nuit; break;

                case PERIODE_JOUR_MATIN: 
                    musique = musiques->ambiance_jour_matin; 
                    break;
                case PERIODE_JOUR_APRES_MIDI: 
                    musique = musiques->ambiance_jour_apres_midi; 
                    break;
                case PERIODE_JOUR_COUCHE_SOLEIL: 
                    musique = musiques->ambiance_jour_couche_soleil; 
                    estLaSuite = VRAI; 
                    break;

                default: musique = musiques->ambiance_jour_matin; break;
            }
            break;
            

        case MUSIC_COMBAT: musique = musiques->combat; break;

        case MUSIC_BOSS: musique = musiques->boss; break;
        
        
        default: musique = musiques->menu_principal; break;
    }


    play_music(musique, VRAI, estLaSuite);
}





/* -------------------------------------------------------------------------- */
/*                                 Chargement                                 */
/* -------------------------------------------------------------------------- */


void loadMusiqueBoss(t_musiques *musiques, e_jour jour) {
    char buffer[64];
    sprintf(buffer, "assets/audio/musiques/boss/boss_%i.mp3", jour);

    if (musiques->boss != NULL) 
        Mix_FreeMusic(musiques->boss);

    musiques->boss = Mix_LoadMUS(buffer);
    if (musiques->boss == NULL) printf("ERROR");
    else printf("Succes\n");
}


/**
 * @brief 
 * 
 * @param volume 
 * @param musiques 
 * @param bruitages 
 * @return int 
 */
int chargerAudio(const float volume, t_musiques **musiques, t_bruitages **bruitages) {
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
    m->ambiance_jour_matin = Mix_LoadMUS("assets/audio/musiques/ambiance_jour_matin.ogg");
    m->ambiance_jour_apres_midi = Mix_LoadMUS("assets/audio/musiques/ambiance_jour_apres_midi.ogg");
    m->ambiance_jour_couche_soleil = Mix_LoadMUS("assets/audio/musiques/ambiance_jour_couche_soleil.ogg");
    m->ambiance_nuit = Mix_LoadMUS("assets/audio/musiques/ambiance_nuit.mp3");

    // Combat
    m->combat = Mix_LoadMUS("assets/audio/musiques/combat.mp3");
    // m->combat_nuit = Mix_LoadMUS("assets/audio/musiques/.mp3");
    m->boss = NULL;
    loadMusiqueBoss(m, getJourDeLaSemaine(time(NULL)));
    // m->combat_boss = Mix_LoadMUS("assets/audio/musiques/.mp3");
    
    
    /* -------------------------------- Bruitages ------------------------------- */
    // Menu
    b->menu_selection = Mix_LoadWAV("assets/audio/bruitages/menu_selection.wav");

    // Joueur
    // b->joueur_attaque = Mix_LoadWAV("assets/audio/bruitages/.wav");
    // b->joueur_degat = Mix_LoadWAV("assets/audio/bruitages/.wav");
    // b->joueur_mort = Mix_LoadWAV("assets/audio/bruitages/.wav");

    // Monstre
    // b->monstre_attaque = Mix_LoadWAV("assets/audio/bruitages/.wav");
    // b->monstre_degat = Mix_LoadWAV("assets/audio/bruitages/.wav");
    // b->monstre_mort = Mix_LoadWAV("assets/audio/bruitages/.wav");

    // Animaux
    b->vache = Mix_LoadWAV("assets/audio/bruitages/vache.wav");
    b->cochon = Mix_LoadWAV("assets/audio/bruitages/cochon.wav");

    // Autres
    // b->item_recuperation = Mix_LoadMUS("assets/audio/bruitages/.wav");



    // changerVolume(CHANNEL_MASTER, volume);


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

    a->masterVolume = 1.0;
    a->musiqueVolume = 1.0;
    a->bruitageVolume = 1.0;


    chargerAudio(a->masterVolume, &a->musiques, &a->bruitages);
    a->musiqueType = MUSIC_MENU;
    a->timestampDebutMusique = 0;
    a->tempsEcoulee = 0.0;



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

            Mix_FreeMusic((*audio)->musiques->menu_principal);
            Mix_FreeMusic((*audio)->musiques->ambiance_jour_matin);
            Mix_FreeMusic((*audio)->musiques->ambiance_jour_apres_midi);
            Mix_FreeMusic((*audio)->musiques->ambiance_nuit);
            Mix_FreeMusic((*audio)->musiques->combat);
            Mix_FreeMusic((*audio)->musiques->boss);

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


